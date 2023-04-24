#pragma once
#include "LNLibDefinitions.h"
#include <vector>

namespace LNLib
{
	class XYZ;
	class LNLIB_EXPORT NurbsSurface
	{
	public:

		/// <summary>
		/// The NURBS Book 2nd Edition Page134
		/// Algorithm A4.3
		/// Compute point on rational B-spline surface.
		/// </summary>
		static void GetPointOnSurface(const std::vector<std::vector<XYZ>>& controlPoints, const std::vector<std::vector<double>>& weights, const std::vector<double>& knotVectorU, const std::vector<double>& knotVectorV, unsigned int degreeU, unsigned int degreeV, double paramU, double paramV, XYZ& point);

		/// <summary>
		/// The NURBS Book 2nd Edition Page137
		/// Algorithm A4.4
		/// Compute S(paramU,paramV) derivatives.
		/// </summary>
		static void ComputeRationalSurfaceDerivatives(const std::vector<std::vector<XYZ>>& controlPoints, const std::vector<std::vector<double>>& weights, const std::vector<double>& knotVectorU, const std::vector<double>& knotVectorV, unsigned int degreeU, unsigned int degreeV, double paramU, double paramV, unsigned int derivative, std::vector<std::vector<XYZ>>& derivatives);
	};
}


