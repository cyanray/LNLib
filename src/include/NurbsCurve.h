#pragma once

#include "LNLibDefinitions.h"
#include <vector>

namespace LNLib
{
	class XYZ;
	class XYZW;
	class LNLIB_EXPORT NurbsCurve
	{
	public:

		/// <summary>
		/// The NURBS Book 2nd Edition Page124
		/// Algorithm A4.1
		/// Compute point on rational B-spline curve.
		/// </summary>
		static void GetPointOnCurve(unsigned int degree, const std::vector<double>& knotVector, const std::vector<XYZW>& controlPoints, double paramT, XYZ& point);

		/// <summary>
		/// The NURBS Book 2nd Edition Page127
		/// Algorithm A4.2
		/// Compute C(paramT) derivatives from Cw(paramT) deraivatives.
		/// </summary>
		static void ComputeRationalCurveDerivatives(unsigned int degree, const std::vector<double>& knotVector, const std::vector<XYZW>& controlPoints, double paramT, unsigned int derivative, std::vector<XYZ>& derivatives);

		/// <summary>
		/// The NURBS Book 2nd Edition Page151
		/// Algorithm A5.1
		/// Curve knot insertion.
		/// Note that multiplicity + times <= degree.
		/// </summary>
		static void InsertKnot(unsigned int degree, const std::vector<double>& knotVector, const std::vector<XYZW>& controlPoints, double insertKnot, unsigned int times, std::vector<double>& insertedKnotVector, std::vector<XYZW>& updatedControlPoints);

		/// <summary>
		/// The NURBS Book 2nd Edition Page155
		/// Algorithm A5.2
		/// Computes a point on a curve by using knot insertion ("corner cutting").
		/// </summary>
		static void GetPointOnCurveByInsertKnot(unsigned int degree, const std::vector<double>& knotVector, std::vector<XYZW>& controlPoints, double insertKnot, XYZ& point);

		/// <summary>
		/// The NURBS Book 2nd Edition Page164
		/// Algorithm A5.4
		/// Refine curve knot vector.
		/// </summary>
		static void RefineKnotVector(unsigned int degree, const std::vector<double>& knotVector, const std::vector<XYZW>& controlPoints, std::vector<double>& insertKnotElements, std::vector<double>& insertedKnotVector, std::vector<XYZW>& updatedControlPoints);

		/// <summary>
		/// The NURBS Book 2nd Edition Page173
		/// Algorithm A5.6
		/// Decompose curve into Bezier segements.
		/// decomposedControlPoints[i][j] means ith segement jth control point.
		/// </summary>
		static void ToBezierCurves(unsigned int degree, const std::vector<double>& knotVector, const std::vector<XYZW>& controlPoints, int& bezierCurvesCount, std::vector<std::vector<XYZW>>& decomposedControlPoints);

		/// <summary>
		/// The NURBS Book 2nd Edition Page185
		/// Algorithm A5.8
		/// Curve knot removal.
		/// </summary>
		static void RemoveKnot(unsigned int degree, const std::vector<double>& knotVector, const std::vector<XYZW>& controlPoints, double removeKnot, unsigned int times, std::vector<double>& restKnotVector, std::vector<XYZW>& updatedControlPoints);

		/// <summary>
		/// The NURBS Book 2nd Edition Page206
		/// Algorithm A5.9
		/// Degree elevate a curve t times.
		/// </summary>
		static void ElevateDegree(unsigned int degree, const std::vector<double>& knotVector, const std::vector<XYZW>& controlPoints, unsigned int times, std::vector<double>& updatedKnotVector, std::vector<XYZW>& updatedControlPoints);

		/// <summary>
		/// The NURBS Book 2nd Edition Page223
		/// Algorithm A5.11
		/// Degree reduce a curve from degree to degree - 1.
		/// 
		/// return 0 means run successed;
		/// return 1 means run failed; 
		/// </summary>
		static int ReduceDegree(unsigned int degree, const std::vector<double>& knotVector, const std::vector<XYZW>& controlPoints, std::vector<double>& updatedKnotVector, std::vector<XYZW>& updatedControlPoints);
	};
}


