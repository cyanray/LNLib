/*
 * Author:
 * 2023/06/08 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 * 微信公众号：BIMCoder梁老师
 *
 * Use of this source code is governed by a GPL-3.0 license that can be found in
 * the LICENSE file.
 */

#pragma once

#include "LNLibDefinitions.h"
#include "Polynomials.h"
#include "ValidationUtils.h"
#include "LNLibExceptions.h"
#include <vector>

namespace LNLib
{
	class XYZ;
	class XYZW;
	class LNLIB_EXPORT BsplineCurve
	{
	public:

		/// <summary>
		/// The NURBS Book 2nd Edition Page82
		/// Algorithm A3.1
		/// Compute Bspline curve point.
		/// </summary>
		template <typename T>
		static T GetPointOnCurve(int degree, const std::vector<double>& knotVector, double paramT, const std::vector<T>& controlPoints)
		{
			VALIDATE_ARGUMENT(degree > 0, "degree", "Degree must greater than zero.");
			VALIDATE_ARGUMENT(knotVector.size() > 0, "knotVector", "KnotVector size must greater than zero.");
			VALIDATE_ARGUMENT(ValidationUtils::IsValidKnotVector(knotVector), "knotVector", "KnotVector must be a nondecreasing sequence of real numbers.");
			VALIDATE_ARGUMENT_RANGE(paramT, knotVector[0], knotVector[knotVector.size() - 1]);
			VALIDATE_ARGUMENT(controlPoints.size() > 0, "controlPoints", "ControlPoints must contains one point at least.");
			VALIDATE_ARGUMENT(ValidationUtils::IsValidBspline(degree, knotVector.size(), controlPoints.size()), "controlPoints", "Arguments must fit: m = n + p + 1");

			T point;
			int spanIndex = Polynomials::GetKnotSpanIndex(degree, knotVector, paramT);
			std::vector<double> N = Polynomials::BasisFunctions(spanIndex, degree, knotVector, paramT);

			for (int i = 0; i <= degree; i++)
			{
				point += N[i] * controlPoints[spanIndex - degree + i];
			}
			return point;
		}

		/// <summary>
		/// The NURBS Book 2nd Edition Page88
		/// Compute the continuity.
		/// </summary>
		static int GetContinuity(int degree, const std::vector<double>& knotVector, double knot);

		/// <summary>
		/// The NURBS Book 2nd Edition Page93
		/// Algorithm A3.2
		/// Compute curve derivatives. (Usually Use)
		/// </summary>
		template<typename T>
		static std::vector<T> ComputeDerivatives(int degree, int derivative, const std::vector<double>& knotVector, double paramT, const std::vector<T>& controlPoints)
		{
			VALIDATE_ARGUMENT(degree > 0, "degree", "Degree must greater than zero.");
			VALIDATE_ARGUMENT(knotVector.size() > 0, "knotVector", "KnotVector size must greater than zero.");
			VALIDATE_ARGUMENT(ValidationUtils::IsValidKnotVector(knotVector), "knotVector", "KnotVector must be a nondecreasing sequence of real numbers.");
			VALIDATE_ARGUMENT_RANGE(paramT, knotVector[0], knotVector[knotVector.size() - 1]);
			VALIDATE_ARGUMENT(controlPoints.size() > 0, "controlPoints", "ControlPoints must contains one point at least.");
			VALIDATE_ARGUMENT(ValidationUtils::IsValidBspline(degree, knotVector.size(), controlPoints.size()), "controlPoints", "Arguments must fit: m = n + p + 1");
			
			std::vector<T> derivatives(derivative + 1);

			int du = std::min(derivative, degree);
			int spanIndex = Polynomials::GetKnotSpanIndex(degree, knotVector, paramT);
			std::vector<std::vector<double>> nders = 
				Polynomials::BasisFunctionsDerivatives(spanIndex, degree, du, knotVector, paramT);

			for (int k = 0; k <= du; k++)
			{
				for (unsigned int j = 0; j <= degree; j++)
				{
					derivatives[k] += nders[k][j] * controlPoints[spanIndex - degree + j];
				}
			}
			return derivatives;
		}

		/// <summary>
		/// The NURBS Book 2nd Edition Page98
		/// Algorithm A3.3
		/// Compute control points of curve derivatives.
		/// </summary>
		static std::vector<std::vector<XYZ>> ComputeControlPointsOfDerivatives(int degree, int derivative, int minSpanIndex, int maxSpanIndex, const std::vector<double>& knotVector, const std::vector<XYZ>& controlPoints);

		/// <summary>
		/// The NURBS Book 2nd Edition Page99
		/// Algorithm A3.4
		/// Compute curve detivatives.
		/// </summary>
		template<typename T>
		static std::vector<T> ComputeDerivativesByAllBasisFunctions(int degree, int derivative, const std::vector<double>& knotVector, double paramT, const std::vector<T>& controlPoints)
		{
			VALIDATE_ARGUMENT(degree > 0, "degree", "Degree must greater than zero.");
			VALIDATE_ARGUMENT(knotVector.size() > 0, "knotVector", "KnotVector size must greater than zero.");
			VALIDATE_ARGUMENT(ValidationUtils::IsValidKnotVector(knotVector), "knotVector", "KnotVector must be a nondecreasing sequence of real numbers.");
			VALIDATE_ARGUMENT_RANGE(paramT, knotVector[0], knotVector[knotVector.size() - 1]);
			VALIDATE_ARGUMENT(controlPoints.size() > 0, "controlPoints", "ControlPoints must contains one point at least.");
			VALIDATE_ARGUMENT(ValidationUtils::IsValidBspline(degree, knotVector.size(), controlPoints.size()), "controlPoints", "Arguments must fit: m = n + p + 1");

			int du = std::min(derivative, degree);
			std::vector<T> derivatives(derivative + 1);
			int spanIndex = Polynomials::GetKnotSpanIndex(degree, knotVector, paramT);
			std::vector<std::vector<double>> N(degree + 1, std::vector<double>(degree + 1));
			for (int i = 0; i < degree + 1; i++)
			{
				auto basis = Polynomials::BasisFunctions(spanIndex, i, knotVector, paramT);
				for (int j = 0; j < i + 1; j++)
				{
					N[j][i] = basis[j];
				}
			}
			
			std::vector<std::vector<T>> PK = ComputeControlPointsOfDerivatives(degree, du, spanIndex - degree, spanIndex, knotVector, controlPoints);

			for (int k = 0; k <= du; k++)
			{
				for (int j = 0; j <= degree - k; j++)
				{
					derivatives[k] += N[j][degree - k] * PK[k][j];
				}
			}

			return derivatives;
		}
	};
}


