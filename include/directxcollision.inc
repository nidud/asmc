include DirectXMath.inc

.enum ContainmentType {
    DISJOINT = 0,
    INTERSECTS = 1,
    CONTAINS = 2,
    }

.enum PlaneIntersectionType {
    FRONT = 0,
    INTERSECTING = 1,
    BACK = 2,
    }


.template BoundingSphere XM_CALLCONV

    Center  XMFLOAT3 <> ;; Center of the sphere.
    Radius  float ?     ;; Radius of the sphere.

    .static BoundingSphere center:ptr XMFLOAT3, radius:float {
        mov     this.Center,[center]
        movss   this.Radius,radius
        }
    .static Transform :abs, :abs {
        typeid(BoundingSphere_Transform, _2)(&this, _1, _2, _3)
        }
    .static Contains :abs {
        typeid(BoundingSphere_Contains, _1)(&this, _1, _2)
        }
    .static Intersects :abs {
        typeid(BoundingSphere_Intersects, _1)(&this, _1, _2)
        }
    .static ContainedBy {
        BoundingSphere_ContainedBy(&this, _1)
        }
    .static CreateMerged {
        BoundingSphere_CreateMerged(&this, _1)
        }
    .static CreateFromBoundingBox :abs, :abs {
        typeid(BoundingSphere_CreateFromBoundingBox, _2)(&this, _1, _2)
        }
    .static CreateFromPoints {
        BoundingSphere_CreateFromPoints(&this, _1)
        }
    .static CreateFromFrustum {
        BoundingSphere_CreateFromFrustum(&this, _1)
        }
    .ends


CORNER_COUNT equ 8

.template BoundingBox XM_CALLCONV

    Center  XMFLOAT3 <> ;; Center of the box.
    Extents XMFLOAT3 <> ;; Distance from the center to each side.

    .static BoundingBox {
        }
    .static Transform :abs, :abs {
        typeid(BoundingBox_Transform, _2)(&this, _1, _2, _3)
        }
    .static GetCorners {
        BoundingBox_GetCorners(&this, _1)
        }
    .static Contains :abs {
        typeid(BoundingBox_Contains, _1)(&this, _1, _2)
        }
    .static Intersects :abs {
        typeid(BoundingBox_Intersects, _1)(&this, _1, _2)
        }
    .static ContainedBy {
        BoundingBox_ContainedBy(&this, _1)
        }
    .static CreateMerged {
        BoundingBox_CreateMerged(&this, _1)
        }
    .static CreateFromSphere {
        BoundingBox_CreateFromSphere(&this, _1)
        }
    .static CreateFromPoints :abs, :abs {
        typeid(BoundingBox_CreateFromPoints, _2)(&this, _1, _2)
        }
    .ends


.template BoundingOrientedBox XM_CALLCONV

    Center      XMFLOAT3 <>  ;; Center of the box.
    Extents     XMFLOAT3 <>  ;; Distance from the center to each side.
    Orientation XMFLOAT4 <>  ;; Unit quaternion representing rotation (box -> world).

    .static BoundingOrientedBox {
        }
    .static Transform :abs, :abs {
        typeid(BoundingOrientedBox_Transform, _2)(&this, _1, _2, _3)
        }
    .static GetCorners {
        BoundingOrientedBox_GetCorners(&this, _1)
        }
    .static Contains :abs {
        typeid(BoundingOrientedBox_Contains, _1)(&this, _1, _2)
        }
    .static Intersects :abs {
        typeid(BoundingOrientedBox_Intersects, _1)(&this, _1, _2)
        }
    .static ContainedBy {
        BoundingOrientedBox_ContainedBy(&this, _1)
        }
    .static CreateFromBoundingBox {
        BoundingOrientedBox_CreateFromBoundingBox(&this, _1)
        }
    .static CreateFromPoints {
        BoundingOrientedBox_CreateFromPoints(&this, _1)
        }
    .ends


.template BoundingFrustum XM_CALLCONV

    Origin          XMFLOAT3 <> ;; Origin of the frustum (and projection).
    Orientation     XMFLOAT4 <> ;; Quaternion representing rotation.

    RightSlope      float ? ;; Positive X slope (X/Z).
    LeftSlope       float ? ;; Negative X slope.
    TopSlope        float ? ;; Positive Y slope (Y/Z).
    BottomSlope     float ? ;; Negative Y slope.
    _Near           float ? ;; Z of the near plane and far plane.
    _Far            float ?

    .static BoundingFrustum {
        }
    .static Transform :abs, :abs {
        typeid(BoundingFrustum_Transform, _2)(&this, _1, _2, _3)
        }
    .static GetCorners {
        BoundingFrustum_GetCorners(&this, _1)
        }
    .static Contains :abs {
        typeid(BoundingFrustum_Contains, _1)(&this, _1, _2)
        }
    .static Intersects :abs {
        typeid(BoundingFrustum_Intersects, _1)(&this, _1, _2)
        }
    .static ContainedBy {
        BoundingFrustum_ContainedBy(&this, _1)
        }
    .static GetPlanes {
        BoundingFrustum_GetPlanes(&this, _1)
        }
    .static CreateFromMatrix {
        BoundingFrustum_CreateFromMatrix(&this, _1)
        }
    .ends


include DirectXCollision.inl
