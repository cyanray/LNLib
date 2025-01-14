/*
 * Author:
 * 2023/10/17 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 * 微信公众号：BIMCoder梁老师
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#include "KnotVectorUtils.h"
#include "UV.h"
#include "MathUtils.h"
#include "Polynomials.h"
#include "ValidationUtils.h"
#include "LNLibExceptions.h"
#include <algorithm>

using namespace LNLib;

int LNLib::KnotVectorUtils::GetContinuity(int degree, const std::vector<double>& knotVector, double knot)
{
	VALIDATE_ARGUMENT(degree > 0, "degree", "Degree must greater than zero.");
	int multi = Polynomials::GetKnotMultiplicity(knotVector, knot);
	return degree - multi;
}

std::vector<double> LNLib::KnotVectorUtils::Rescale(const std::vector<double>& knotVector, double min, double max)
{
	double origintMin = knotVector[0];
	double origintMax = knotVector[knotVector.size() - 1];
	double k = (max - min) / (origintMax - origintMin);

	int size = knotVector.size();
	std::vector<double> result(size);
	for (int i = 0; i < size; i++)
	{
		result[i] = (k * knotVector[i] - origintMin) + min;
	}
	return result;
}

std::vector<double> LNLib::KnotVectorUtils::GetInsertedKnotElement(int degree, const std::vector<double>& knotVector, double startParam, double endParam)
{
	VALIDATE_ARGUMENT(degree >= 0, "degree", "Degree must greater than or equals zero.");
	VALIDATE_ARGUMENT(knotVector.size() > 0, "knotVector", "KnotVector size must greater than zero.");
	VALIDATE_ARGUMENT(ValidationUtils::IsValidKnotVector(knotVector), "knotVector", "KnotVector must be a nondecreasing sequence of real numbers.");

	std::vector<double> result;
	int startMulti = Polynomials::GetKnotMultiplicity(knotVector, startParam);
	if (startMulti < degree)
	{
		for (int i = 0; i < degree - startMulti; i++)
		{
			result.emplace_back(startParam);
		}
	}

	int endMulti = Polynomials::GetKnotMultiplicity(knotVector, endParam);
	if (endMulti < degree)
	{
		for (int i = 0; i < degree - endMulti; i++)
		{
			result.emplace_back(endParam);
		}
	}

	return result;
}

std::unordered_map<double, int, std::hash<double>, CustomDoubleEqual> LNLib::KnotVectorUtils::GetKnotMultiplicityMap(const std::vector<double>& knotVector)
{
	std::unordered_map<double, int, std::hash<double>, CustomDoubleEqual> result;

	for (int i = 0; i < knotVector.size(); i++)
	{
		auto got = result.find(knotVector[i]);
		if (got == result.end())
		{
			int multi = Polynomials::GetKnotMultiplicity(knotVector, knotVector[i]);
			result.insert({ knotVector[i], multi });
		}
	}
	return result;
}

std::unordered_map<double, int, std::hash<double>, CustomDoubleEqual> LNLib::KnotVectorUtils::GetInternalKnotMultiplicityMap(const std::vector<double>& knotVector)
{
	auto result = GetKnotMultiplicityMap(knotVector);
	if (!result.empty()) 
	{
		result.erase(result.begin());
		auto lastElementIterator = prev(result.end(), 1);
		result.erase(lastElementIterator);
	}
	return result;
}

void LNLib::KnotVectorUtils::GetInsertedKnotElement(const std::vector<double>& knotVector0, const std::vector<double>& knotVector1, std::vector<double>& insertElements0, std::vector<double>& insertElements1)
{
	std::unordered_map<double, int, std::hash<double>, CustomDoubleEqual> map0 = GetKnotMultiplicityMap(knotVector0);
	std::unordered_map<double, int, std::hash<double>, CustomDoubleEqual> map1 = GetKnotMultiplicityMap(knotVector1);

	for (auto it = map0.begin(); it != map0.end(); ++it)
	{
		double key0 = it->first;
		int count0 = it->second;

		auto got = map1.find(key0);
		if (got == map1.end())
		{
			for (int i = 0; i < count0; i++)
			{
				insertElements1.emplace_back(key0);
			}
		}
		else
		{
			int count1 = got->second;
			if (count0 > count1)
			{
				int times = count0 - count1;
				for (int j = 0; j < times; j++)
				{
					insertElements1.emplace_back(key0);
				}
			}
			else
			{
				int times = count1 - count0;
				for (int j = 0; j < times; j++)
				{
					insertElements0.emplace_back(key0);
				}
			}
		}
	}

	for (auto it = map1.begin(); it != map1.end(); ++it)
	{
		double key1 = it->first;
		int count1 = it->second;

		auto got = map0.find(key1);
		if (got == map0.end())
		{
			for (int i = 0; i < count1; i++)
			{
				insertElements0.emplace_back(key1);
			}
		}
	}

	std::sort(insertElements0.begin(), insertElements0.end());
	std::sort(insertElements1.begin(), insertElements1.end());
}

std::vector<std::vector<double>> LNLib::KnotVectorUtils::GetInsertedKnotElements(const std::vector<std::vector<double>>& knotVectors)
{
	std::unordered_map<double, int, std::hash<double>, CustomDoubleEqual> finalMap;
	for (int i = 0; i < knotVectors.size(); i++)
	{
		auto kv = knotVectors[i];
		std::unordered_map<double, int, std::hash<double>, CustomDoubleEqual> map = GetKnotMultiplicityMap(kv);
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			double key = it->first;
			int count = it->second;
			auto got = finalMap.find(key);
			if (got == finalMap.end())
			{
				finalMap.insert({ key, count });
			}
			else
			{
				int currentCount = got->second;
				if (currentCount < count)
				{
					finalMap[key] = count;
				}
			}
		}
	}

	std::vector<std::vector<double>> result;
	for (int i = 0; i < knotVectors.size(); i++)
	{
		auto kv = knotVectors[i];
		std::unordered_map<double, int, std::hash<double>, CustomDoubleEqual> map = GetKnotMultiplicityMap(kv);

		std::vector<double> insertElements;
		for (auto it = finalMap.begin(); it != finalMap.end(); ++it)
		{
			double key = it->first;
			int count = it->second;

			auto got = map.find(key);
			if (got == map.end())
			{
				for (int j = 0; j < count; j++)
				{
					insertElements.emplace_back(key);
				}
			}
			else
			{
				int currentCount = got->second;
				int times = count - currentCount;
				for (int j = 0; j < times; j++)
				{
					insertElements.emplace_back(key);
				}
			}
		}
		result.emplace_back(insertElements);
	}
	return result;
}

bool LNLib::KnotVectorUtils::IsUniform(const std::vector<double>& knotVector)
{
	auto map = GetKnotMultiplicityMap(knotVector);
	if (map.empty())
	{
		return false;
	}
	std::vector<double> knots;
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		double key = it->first;
		knots.emplace_back(key);
	}
	double standard = knots[1] - knots[0];
	for (int i = 1; i < knots.size() - 1; i++)
	{
		double current = knots[i];
		double next = knots[i + 1];

		double gap = next - current;
		if (!MathUtils::IsAlmostEqualTo(gap, standard))
		{
			return false;
		}
	}
	return true;
}



