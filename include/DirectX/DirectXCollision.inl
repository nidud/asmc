; DIRECTXCOLLISION.INL--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

externdef g_BoxOffset               :XMVECTORF32 ; [8]
externdef g_RayEpsilon              :XMVECTORF32
externdef g_RayNegEpsilon           :XMVECTORF32
externdef g_FltMin                  :XMVECTORF32
externdef g_FltMax                  :XMVECTORF32

;;-----------------------------------------------------------------------------
;; Return true if any of the elements of a 3 vector are equal to 0xffffffff.
;; Slightly more efficient than using XMVector3EqualInt.
;;-----------------------------------------------------------------------------
XMVector3AnyTrue proto V:FXMVECTOR {
    xor eax,eax
    movaps [rsp],xmm0
    mov ecx,0xffffffff
    .if ecx == [rsp] || ecx == [rsp+4] || ecx == [rsp+8]
        inc eax
    .endif
    }

;;-----------------------------------------------------------------------------
;; Return true if all of the elements of a 3 vector are equal to 0xffffffff.
;; Slightly more efficient than using XMVector3EqualInt.
;;-----------------------------------------------------------------------------
XMVector3AllTrue proto V:FXMVECTOR {
    xor eax,eax
    movaps [rsp],xmm0
    mov ecx,0xffffffff
    .if ecx == [rsp] && ecx == [rsp+4] && ecx == [rsp+8]
        inc eax
    .endif
    }


if defined(_PREFAST_) or not defined(NDEBUG)

externdef g_UnitVectorEpsilon       :XMVECTORF32
externdef g_UnitQuaternionEpsilon   :XMVECTORF32
externdef g_UnitPlaneEpsilon        :XMVECTORF32

XMVector3IsUnit     proto XM_CALLCONV :FXMVECTOR
XMQuaternionIsUnit  proto XM_CALLCONV :FXMVECTOR
XMPlaneIsUnit       proto XM_CALLCONV :FXMVECTOR

endif

;XMPlaneTransform proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
PointOnLineSegmentNearestPoint proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
PointOnPlaneInsideTriangle proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR
SolveCubic proto XM_CALLCONV :float, :float, :float, :ptr float, :ptr float, :ptr float
CalculateEigenVector proto XM_CALLCONV :float, :float, :float, :float, :float, :float, :float
CalculateEigenVectors proto XM_CALLCONV :float, :float, :float, :float, :float,
        :float, :float, :float, :float, :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR
CalculateEigenVectorsFromCovarianceMatrix proto XM_CALLCONV :float, :float, :float,
        :float, :float, :float, :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR
FastIntersectTrianglePlane proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR,
        :ptr XMVECTOR, :ptr XMVECTOR
FastIntersectSpherePlane proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR,
        :ptr XMVECTOR, :ptr XMVECTOR
FastIntersectAxisAlignedBoxPlane proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR,
        :FXMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR
FastIntersectOrientedBoxPlane proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR,
        :FXMVECTOR, :GXMVECTOR, :HXMVECTOR, :HXMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR
FastIntersectFrustumPlane proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR,
        :GXMVECTOR, :HXMVECTOR, :HXMVECTOR, :CXMVECTOR, :CXMVECTOR, :CXMVECTOR,
        :ptr XMVECTOR, :ptr XMVECTOR

