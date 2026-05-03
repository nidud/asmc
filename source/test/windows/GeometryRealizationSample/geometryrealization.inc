
; The maximum granularity of bitmap sizes we allow for AA realizations.

define sc_bitmapChunkSize 64.0

ifndef REALIZATIONS_DECLARE_INTERFACE
REALIZATIONS_DECLARE_INTERFACE macro X
    DECLSPEC_UUID(X) DECLSPEC_NOVTABLE
    endm
endif

.enum REALIZATION_CREATION_OPTIONS {
    REALIZATION_CREATION_OPTIONS_ALIASED = 1,
    REALIZATION_CREATION_OPTIONS_ANTI_ALIASED = 2,
    REALIZATION_CREATION_OPTIONS_UNREALIZED = 4,
    REALIZATION_CREATION_OPTIONS_FILLED = 8,
    REALIZATION_CREATION_OPTIONS_STROKED = 16
    }

.enum REALIZATION_RENDER_MODE {
    REALIZATION_RENDER_MODE_FORCE_REALIZED = 0,
    REALIZATION_RENDER_MODE_FORCE_UNREALIZED = 1,
    REALIZATION_RENDER_MODE_DEFAULT = 2
    }


.comdef IGeometryRealization : public IUnknown

    Fill proc :ptr ID2D1RenderTarget, :ptr ID2D1Brush, :REALIZATION_RENDER_MODE
    Draw proc :ptr ID2D1RenderTarget, :ptr ID2D1Brush, :REALIZATION_RENDER_MODE
    Update proc :ptr ID2D1Geometry, :REALIZATION_CREATION_OPTIONS, :ptr D2D1_MATRIX_3X2_F, :real4, :ptr ID2D1StrokeStyle
   .ends


.comdef IGeometryRealizationFactory : public IUnknown

    CreateGeometryRealization proc :ptr ptr IGeometryRealization
   .ends

.class GeometryRealization : public IGeometryRealization

    m_pFillMesh                         ptr ID2D1Mesh ?
    m_pStrokeMesh                       ptr ID2D1Mesh ?
    m_pFillRT                           ptr ID2D1BitmapRenderTarget ?
    m_pStrokeRT                         ptr ID2D1BitmapRenderTarget ?
    m_pGeometry                         ptr ID2D1Geometry ?
    m_pStrokeStyle                      ptr ID2D1StrokeStyle ?
    m_strokeWidth                       float ?
    m_fillMaskDestBounds                D2D1_RECT_F <>
    m_fillMaskSourceBounds              D2D1_RECT_F <>
    m_strokeMaskDestBounds              D2D1_RECT_F <>
    m_strokeMaskSourceBounds            D2D1_RECT_F <>
    m_pRT                               ptr ID2D1RenderTarget ?
    m_realizationTransformIsIdentity    BOOL ?
    m_realizationTransform              Matrix3x2F <>
    m_realizationTransformInv           Matrix3x2F <>
    m_swRT                              BOOL ?
    m_maxRealizationDimension           UINT ?
    m_cRef                              ULONG ?

    GeometryRealization proc

    Initialize proc :ptr ID2D1RenderTarget, :UINT, :ptr ID2D1Geometry, :REALIZATION_CREATION_OPTIONS,
                :ptr D2D1_MATRIX_3X2_F, :float, :ptr ID2D1StrokeStyle
    RenderToTarget proc :BOOL, :ptr ID2D1RenderTarget, :ptr ID2D1Brush, :REALIZATION_RENDER_MODE
   .ends

.class GeometryRealizationFactory : public IGeometryRealizationFactory

    m_pRT                       ptr ID2D1RenderTarget ?
    m_cRef                      ULONG ?
    m_maxRealizationDimension   UINT ?

    GeometryRealizationFactory  proc
    Initialize                  proc :ptr ID2D1RenderTarget, :UINT
   .ends


CreateGeometryRealizationFactory proto :ptr ID2D1RenderTarget, :UINT, :ptr ptr IGeometryRealizationFactory
GenerateOpacityMask proto :BOOL, :ptr ID2D1RenderTarget, :UINT, :ptr ptr ID2D1BitmapRenderTarget, :ptr ID2D1Geometry,
        :ptr D2D1_MATRIX_3X2_F, :float, :ptr ID2D1StrokeStyle, :ptr D2D1_RECT_F, :ptr D2D1_RECT_F


ifdef _MSVCRT
.data
 IID_IUnknown            IID _IID_IUnknown
 IID_ID2D1Factory        IID _IID_ID2D1Factory
 IID_IWICImagingFactory  IID _IID_IWICImagingFactory
 CLSID_WICImagingFactory IID _CLSID_WICImagingFactory
 IID_IDWriteFactory      IID _IID_IDWriteFactory
endif
