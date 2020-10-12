
ifndef REALIZATIONS_DECLARE_INTERFACE
REALIZATIONS_DECLARE_INTERFACE macro X
    DECLSPEC_UUID(X) DECLSPEC_NOVTABLE
    endm
endif

.enum REALIZATION_CREATION_OPTIONS {

    ;;
    ;; Generate mesh
    ;;
    REALIZATION_CREATION_OPTIONS_ALIASED = 1,

    ;;
    ;; Generate opacity mask
    ;;
    REALIZATION_CREATION_OPTIONS_ANTI_ALIASED = 2,

    ;;
    ;; Retain pointer to original geometry for unrealized rendering
    ;;
    REALIZATION_CREATION_OPTIONS_UNREALIZED = 4,

    ;;
    ;; Generate fill realization
    ;;
    REALIZATION_CREATION_OPTIONS_FILLED = 8,

    ;;
    ;; Generate stroke realization
    ;;
    REALIZATION_CREATION_OPTIONS_STROKED = 16
    }

.enum REALIZATION_RENDER_MODE {
    ;;
    ;; Force the use of the realization
    ;;
    REALIZATION_RENDER_MODE_FORCE_REALIZED = 0,

    ;;
    ;; Force the use of the original geometry
    ;;
    REALIZATION_RENDER_MODE_FORCE_UNREALIZED = 1,

    ;;
    ;; Key off of the render-target to decide:
    ;;  SW: Unrealized
    ;;  HW: Realized
    ;;
    REALIZATION_RENDER_MODE_DEFAULT = 2
    }


;;+-----------------------------------------------------------------------------
;;
;;  Interface:
;;      IGeometryRealization
;;
;;  Description:
;;      Encapsulates various mesh and/or opacity mask instances to provide
;;      efficient rendering of complex primitives.
;;
;;------------------------------------------------------------------------------

.comdef IGeometryRealization : public IUnknown

    ;;
    ;; Render the fill realization to the render target
    ;;
    Fill proc :ptr ID2D1RenderTarget, :ptr ID2D1Brush, :REALIZATION_RENDER_MODE

    ;;
    ;; Render the stroke realization to the render target
    ;;
    Draw proc :ptr ID2D1RenderTarget, :ptr ID2D1Brush, :REALIZATION_RENDER_MODE

    ;;
    ;; Discard the current realization's contents and replace with new contents.
    ;;
    ;; Note: This method will attempt to reuse the existing bitmaps (but will
    ;; replace the bitmaps if they aren't large enough). Since the cost of
    ;; destroying a texture can be surprisingly astronomical, using this method
    ;; can be substantially more performant than recreating a new realization
    ;; every time.
    ;;
    ;; Note: pWorldTransform is the transform that the realization will
    ;; be optimized for. If, at the time of rendering, the render target's
    ;; transform is the same as pWorldTransform,
    ;; the realization will appear identical to the unrealized version. Otherwise,
    ;; quality will be degraded.
    ;;
    Update proc :ptr ID2D1Geometry,
                :REALIZATION_CREATION_OPTIONS,
                :ptr D2D1_MATRIX_3X2_F,
                :real4,
                :ptr ID2D1StrokeStyle

    .ends


;;+-----------------------------------------------------------------------------
;;
;;  Interface:
;;      IGeometryRealizationFactory
;;
;;------------------------------------------------------------------------------

.comdef IGeometryRealizationFactory : public IUnknown

    ;;
    ;; Create a realization object with no content (should be populated with
    ;; Update() before use).
    ;;
    CreateGeometryRealization proc :ptr ptr IGeometryRealization

    ;;
    ;; Create a geometry realization.
    ;;
    ;; Note: Here, pWorldTransform is the transform that the realization will
    ;; be optimized for. If, at the time of rendering, the render target's
    ;; transform is the same as the pWorldTransform passed in here then
    ;; the realization will look identical to the unrealized version. Otherwise,
    ;; quality will be degraded.
    ;;

    .ends

;;+-----------------------------------------------------------------------------
;;
;;  Function:
;;      CreateGeometryRealizationFactory
;;
;;------------------------------------------------------------------------------

CreateGeometryRealizationFactory proto \
        : ptr ID2D1RenderTarget,
        : UINT,
        : ptr ptr IGeometryRealizationFactory

ifdef _MSVCRT

    .data

    IID_IUnknown            IID _IID_IUnknown
    IID_ID2D1Factory        IID _IID_ID2D1Factory
    IID_IWICImagingFactory  IID _IID_IWICImagingFactory
    CLSID_WICImagingFactory IID _CLSID_WICImagingFactory
    IID_IDWriteFactory      IID _IID_IDWriteFactory
    @CurSeg ends

endif
