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
#include "LNObject.h"
#include <vector>

namespace LNLib
{
	class UV;
	class XYZ;
	class XYZW;
	class LNLIB_EXPORT NurbsSurface
	{
	public:

		/// <summary>
		/// The NURBS Book 2nd Edition Page134
		/// Algorithm A4.3
		/// Compute point on rational B-spline surface.
		/// </summary>
		static XYZ GetPointOnSurface(const LN_Surface& surface, UV uv);

		/// <summary>
		/// The NURBS Book 2nd Edition Page137
		/// Algorithm A4.4
		/// Compute S(paramU,paramV) derivatives.
		/// </summary>
		static std::vector<std::vector<XYZ>> ComputeRationalSurfaceDerivatives(const LN_Surface& surface, int derivative, UV uv);

		/// <summary>
		/// The NURBS Book 2nd Edition Page137
		/// Algorithm A5.3
		/// Surface knot insertion along U or V direction.
		/// </summary>
		static void InsertKnot(const LN_Surface& surface, double insertKnot, int times, bool isUDirection, LN_Surface& result);

		/// <summary>
		/// The NURBS Book 2nd Edition Page167
		/// Algorithm A5.5
		/// Refine surface knot vector.
		/// </summary>
		static void RefineKnotVector(const LN_Surface& surface, std::vector<double>& insertKnotElements, bool isUDirection, LN_Surface& result);

		/// <summary>
		/// The NURBS Book 2nd Edition Page177
		/// Algorithm A5.7
		/// Decompose surface into Bezier patches.
		/// decomposedControlPoints[i][j][k] means ith patch jth row kth column control point.
		/// </summary>
		static std::vector<std::vector<std::vector<XYZW>>> DecomposeToBeziers(const LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page186
		/// Surface knot removal.
		/// </summary>
		static void RemoveKnot(const LN_Surface& surface, double removeKnot, int times, bool isUDirection, LN_Surface& result);

		/// <summary>
		/// The NURBS Book 2nd Edition Page209
		/// Algorithm A5.10
		/// Degree elevate a surface t times.
		/// </summary>
		static void ElevateDegree(const LN_Surface& surface, int times, bool isUDirection, LN_Surface& result);

		/// <summary>
		/// The NURBS Book 2nd Edition Page227
		/// Degree reduce U or V Direction Bezier-shape nurbs curve from degree to degree - 1.
		/// </summary>
		static bool ReduceDegree(const LN_Surface& surface, bool isUDirection, LN_Surface& result);

		/// <summary>
		/// The NURBS Book 2nd Edition Page232
		/// Equally spaced parameter values on each candidate span.
		/// </summary>
		static void EquallyTessellate(const LN_Surface& surface, std::vector<XYZ>& tessellatedPoints, std::vector<UV>& correspondingKnots);

		/// <summary>
		/// The NURBS Book 2nd Edition Page232
		/// Point inversion:finding the corresponding parameter make S(u,v) = P.
		/// </summary>
		static UV GetParamOnSurface(const LN_Surface& surface, const XYZ& givenPoint);

		/// <summary>
		/// The NURBS Book 2nd Edition Page235
		/// Surface Tangent Vector Inversion: finding the corresponding UV tangent [du dv] make T = Su*du+Sv*dv.
		/// </summary>
		static bool GetUVTangent(const LN_Surface& surface, const UV param, const XYZ& tangent, UV& uvTangent);
		
		/// <summary>
		/// The NURBS Book 2nd Edition Page334
		/// construct a NURBS surface by four counter-clockwise points.
		/// point1 ~ point4 are counter-clock placement.
		/// </summary>
		static void CreateBilinearSurface(const XYZ& point1, const XYZ& point2, const XYZ& point3, const XYZ& point4, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page336
		/// Create a right cirular cylinder.
		/// </summary>
		static bool CreateCylindricalSurface(const XYZ& origin, const XYZ& xAxis, const XYZ& yAxis, double startRad, double endRad, double radius, double height, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page337
		/// Create a ruled surface.
		/// </summary>
		static void CreateRuledSurface(const LN_Curve& curve0, const LN_Curve& curve1, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page346
		/// Algorithm A8.1
		/// Create a revolved surface.
		/// </summary>
		static bool CreateRevolvedSurface(const XYZ& origin, const XYZ& axis, double rad, const LN_Curve& profile, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page348
		/// Nonuniform scaling of surface.
		/// </summary>
		static std::vector<std::vector<XYZW>> NonuniformScaling(const std::vector<std::vector<XYZW>>& controlPoints, double xFactor, double yFactor, double zFactor, const XYZ& referencePoint);

		/// <summary>
		/// The NURBS Book 2nd Edition Page359
		/// Create Nurbs corner fillet surface.
		/// </summary>
		static void MakeCornerFilletSurface();

		/// <summary>
		/// The NURBS Book 2nd Edition Page380
		/// Algorithm A9.4
		/// Global surface interpolation.
		/// </summary>
		static void GlobalInterpolation(const std::vector<std::vector<XYZ>>& throughPoints, int degreeU, int degreeV, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page404
		/// Algorithm A9.5
		/// Local surface interpolation through (n+1)*(m+1) points.
		/// </summary>
		static bool BicubicLocalInterpolation(const std::vector<std::vector<XYZ>>& throughPoints, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page422
		/// Algorithm A9.7
		/// Global surface approximation with fixed number of control points.
		/// </summary>
		static bool GlobalApproximation(const std::vector<std::vector<XYZ>>& throughPoints, int degreeU, int degreeV, int controlPointsRows, int controlPointsColumns, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page456
		/// Create Swung Surface.
		/// </summary>
		static bool CreateSwungSurface(const LN_Curve& profile, const LN_Curve& trajectory, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page457
		/// Create Loft Surface (called Skinned Surfaces in The NURBS Book).
		/// </summary>
		static bool CreateLoftSurface(const std::vector<LN_Curve>& sections, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page472
		/// Create Sweep Surface.
		/// Algorithm A10.1 & A10.2
		/// </summary>
		static bool CreateSweepSurface(const LN_Curve& path, const std::vector<LN_Curve>& profiles, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page494
		/// Algorithm A10.3
		/// Create Gordon Surface.
		/// Gordon Surface has a number of restrictions:
		/// 1. All input curves must be NURBS or NURBS-like. Only non-rational curves are supported - i.e., without weights (or all weights equal).
		/// 2. All U-curves must have “the same” direction; all V-curves must also have “the same” direction.
		/// 3. There must be N curves along one direction, and M curves along another direction, which must exactly intersect at N x M points.
		/// 4. Intersection points must be located evenly in parameter spaces of curves. 
		/// 5. U-curves must be ordered along direction of V-curves, and vice versa. 
		/// </summary>
		static bool CreateGordonSurface(const std::vector<LN_Curve>& uCurves, const std::vector<LN_Curve>& vCurves, const std::vector<std::vector<XYZ>>& intersectionPoints, LN_Surface& surface);

		/// <summary>
		/// The NURBS Book 2nd Edition Page502
		/// Algorithm A10.4
		/// Create Coons Surface.
		/// The difference between Coons and Gordon is that Coons Surface is created by 4 curves.
		/// The coons surface is the special case of Gordon Surface.
		/// 
		/// curve0 & curve2 are one side and curve1 & curve3 are another side.
		/// curve0,curve1,curve2,curve3 are anti-clock connected.
		/// 
		/// </summary>
		static void CreateCoonsSurface(const LN_Curve& curve0, const LN_Curve& curve1, const LN_Curve& curve2, const LN_Curve& curve3, LN_Surface& surface);
	};
}
