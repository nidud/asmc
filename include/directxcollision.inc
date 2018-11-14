include DirectXMath.inc

ContainmentType         typedef SDWORD
DISJOINT                equ 0
INTERSECTS              equ 1
CONTAINS                equ 2

PlaneIntersectionType   typedef SDWORD
FRONT                   equ 0
INTERSECTING            equ 1
BACK                    equ 2

.classdef BoundingSphere XM_CALLCONV :ptr XMFLOAT3, :float

    Center      XMFLOAT3 <> ;; Center of the sphere.
    Radius      float ?     ;; Radius of the sphere.

    operator    proc :ptr BoundingSphere

    TransformM  proc :ptr BoundingSphere, :FXMMATRIX
    TransformV  proc :ptr BoundingSphere, :float, :FXMVECTOR, :FXMVECTOR

    ContainsP   proc :FXMVECTOR
    ContainsV   proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
    ContainsS   proc :ptr BoundingSphere
    ContainsB   proc :ptr BoundingBox
    ContainsO   proc :ptr BoundingOrientedBox
    ContainsF   proc :ptr BoundingFrustum

    IntersectsS proc :ptr BoundingSphere
    IntersectsB proc :ptr BoundingBox
    IntersectsO proc :ptr BoundingOrientedBox
    IntersectsF proc :ptr BoundingFrustum

    IntersectsV proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
    Intersects1 proc :FXMVECTOR
    Intersects2 proc :FXMVECTOR, :FXMVECTOR, :float

    ContainedBy proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR, :HXMVECTOR
    CreateMerged proc :ptr BoundingSphere, :ptr BoundingSphere, :ptr BoundingSphere

    CreateFromBoundingBox proc :ptr BoundingSphere, :ptr BoundingBox
    CreateFromBoundingBoxO proc :ptr BoundingSphere, :ptr BoundingOrientedBox

    CreateFromPoints proc :ptr BoundingSphere, :size_t, :ptr XMFLOAT3, :size_t
    CreateFromFrustum proc :ptr BoundingSphere, :ptr BoundingFrustum
    .ends


CORNER_COUNT equ 8

.classdef BoundingBox XM_CALLCONV :XMFLOAT3, :XMFLOAT3

    Center      XMFLOAT3 <> ;; Center of the box.
    Extents     XMFLOAT3 <> ;; Distance from the center to each side.

    operator    proc :ptr BoundingBox

    Transform1  proc :ptr BoundingBox, :FXMMATRIX
    Transform2  proc :ptr BoundingBox, :float, :FXMVECTOR, :FXMVECTOR

    GetCorners  proc :ptr XMFLOAT3

    ContainsP   proc :FXMVECTOR
    ContainsV   proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
    ContainsS   proc :ptr BoundingSphere
    ContainsB   proc :ptr BoundingBox
    ContainsO   proc :ptr BoundingOrientedBox
    ContainsF   proc :ptr BoundingFrustum

    IntersectsS proc :ptr BoundingSphere
    IntersectsB proc :ptr BoundingBox
    IntersectsO proc :ptr BoundingOrientedBox
    IntersectsF proc :ptr BoundingFrustum
    IntersectsV proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
    Intersects1 proc :FXMVECTOR
    Intersects2 proc :FXMVECTOR, :FXMVECTOR, :ptr float

    ContainedBy proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR, :HXMVECTOR

    CreateMerged proc :ptr BoundingBox, :ptr BoundingBox, :ptr BoundingBox
    CreateFromSphere proc :ptr BoundingBox, :ptr BoundingSphere
    CreateFromPoints proc :ptr BoundingBox, :FXMVECTOR, :FXMVECTOR
    CreateFromPoints2 proc :ptr BoundingBox, :size_t, :ptr XMFLOAT3, :size_t
    .ends


.classdef BoundingOrientedBox XM_CALLCONV :XMFLOAT3, :XMFLOAT3, :XMFLOAT4

    Center      XMFLOAT3 <>  ;; Center of the box.
    Extents     XMFLOAT3 <>  ;; Distance from the center to each side.
    Orientation XMFLOAT4 <>  ;; Unit quaternion representing rotation (box -> world).

    operator    proc :ptr BoundingOrientedBox

    Transform1  proc :ptr BoundingOrientedBox, :FXMMATRIX
    Transform2  proc :ptr BoundingOrientedBox, :float, :FXMVECTOR, :FXMVECTOR

    GetCorners  proc :ptr XMFLOAT3

    ContainsP   proc :FXMVECTOR
    ContainsV   proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
    ContainsS   proc :ptr BoundingSphere
    ContainsB   proc :ptr BoundingBox
    ContainsO   proc :ptr BoundingOrientedBox
    ContainsF   proc :ptr BoundingFrustum

    IntersectsS proc :ptr BoundingSphere
    IntersectsB proc :ptr BoundingBox
    IntersectsO proc :ptr BoundingOrientedBox
    IntersectsF proc :ptr BoundingFrustum
    IntersectsV proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
    Intersects1 proc :FXMVECTOR
    Intersects2 proc :FXMVECTOR, :FXMVECTOR, :ptr float

    ContainedBy proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR, :HXMVECTOR
    CreateFromBoundingBox proc :ptr BoundingOrientedBox, :ptr BoundingBox

    CreateFromPoints proc :ptr BoundingOrientedBox, :size_t, :ptr XMFLOAT3, :size_t
    .ends


.classdef BoundingFrustum XM_CALLCONV :XMFLOAT3, :XMFLOAT4, :float, :float

    Origin          XMFLOAT3 <> ;; Origin of the frustum (and projection).
    Orientation     XMFLOAT4 <> ;; Quaternion representing rotation.

    RightSlope      float ? ;; Positive X slope (X/Z).
    LeftSlope       float ? ;; Negative X slope.
    TopSlope        float ? ;; Positive Y slope (Y/Z).
    BottomSlope     float ? ;; Negative Y slope.
    _Near           float ? ;; Z of the near plane and far plane.
    _Far            float ?

    operator        proc :ptr BoundingFrustum

    Transform1      proc :ptr BoundingFrustum, :FXMMATRIX
    Transform2      proc :ptr BoundingFrustum, :float, :FXMVECTOR, :FXMVECTOR

    GetCorners      proc :ptr XMFLOAT3

    ContainsP       proc :FXMVECTOR
    ContainsV       proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
    ContainsS       proc :ptr BoundingSphere
    ContainsB       proc :ptr BoundingBox
    ContainsO       proc :ptr BoundingOrientedBox
    ContainsF       proc :ptr BoundingFrustum

    IntersectsS     proc :ptr BoundingSphere
    IntersectsB     proc :ptr BoundingBox
    IntersectsO     proc :ptr BoundingOrientedBox
    IntersectsF     proc :ptr BoundingFrustum

    IntersectsV     proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
    Intersects1     proc :FXMVECTOR
    Intersects2     proc :FXMVECTOR, :FXMVECTOR, :ptr float

    ContainedBy     proc :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR, :HXMVECTOR
    GetPlanes       proc :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR
    CreateFromMatrix proc :ptr BoundingFrustum, :FXMMATRIX
    .ends


include DirectXCollision.inl
