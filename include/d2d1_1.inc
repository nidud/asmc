ifndef _D2D1_1_H_
_D2D1_1_H_ equ <>

ifndef _D2D1_H_
include d2d1.inc
endif
ifndef _D2D1_EFFECTS_
include d2d1effects.inc
endif

include dxgi.inc

CALLBACK(PD2D1_EFFECT_FACTORY, effectImpl:ptr ptr)

D2D1_INVALID_PROPERTY_INDEX equ UINT_MAX

.enum D2D1_PROPERTY_TYPE {
    D2D1_PROPERTY_TYPE_UNKNOWN = 0,
    D2D1_PROPERTY_TYPE_STRING = 1,
    D2D1_PROPERTY_TYPE_BOOL = 2,
    D2D1_PROPERTY_TYPE_UINT32 = 3,
    D2D1_PROPERTY_TYPE_INT32 = 4,
    D2D1_PROPERTY_TYPE_FLOAT = 5,
    D2D1_PROPERTY_TYPE_VECTOR2 = 6,
    D2D1_PROPERTY_TYPE_VECTOR3 = 7,
    D2D1_PROPERTY_TYPE_VECTOR4 = 8,
    D2D1_PROPERTY_TYPE_BLOB = 9,
    D2D1_PROPERTY_TYPE_IUNKNOWN = 10,
    D2D1_PROPERTY_TYPE_ENUM = 11,
    D2D1_PROPERTY_TYPE_ARRAY = 12,
    D2D1_PROPERTY_TYPE_CLSID = 13,
    D2D1_PROPERTY_TYPE_MATRIX_3X2 = 14,
    D2D1_PROPERTY_TYPE_MATRIX_4X3 = 15,
    D2D1_PROPERTY_TYPE_MATRIX_4X4 = 16,
    D2D1_PROPERTY_TYPE_MATRIX_5X4 = 17,
    D2D1_PROPERTY_TYPE_COLOR_CONTEXT = 18,
    D2D1_PROPERTY_TYPE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_PROPERTY {
    D2D1_PROPERTY_CLSID = 0x80000000,
    D2D1_PROPERTY_DISPLAYNAME = 0x80000001,
    D2D1_PROPERTY_AUTHOR = 0x80000002,
    D2D1_PROPERTY_CATEGORY = 0x80000003,
    D2D1_PROPERTY_DESCRIPTION = 0x80000004,
    D2D1_PROPERTY_INPUTS = 0x80000005,
    D2D1_PROPERTY_CACHED = 0x80000006,
    D2D1_PROPERTY_PRECISION = 0x80000007,
    D2D1_PROPERTY_MIN_INPUTS = 0x80000008,
    D2D1_PROPERTY_MAX_INPUTS = 0x80000009,
    D2D1_PROPERTY_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_SUBPROPERTY {
    D2D1_SUBPROPERTY_DISPLAYNAME = 0x80000000,
    D2D1_SUBPROPERTY_ISREADONLY = 0x80000001,
    D2D1_SUBPROPERTY_MIN = 0x80000002,
    D2D1_SUBPROPERTY_MAX = 0x80000003,
    D2D1_SUBPROPERTY_DEFAULT = 0x80000004,
    D2D1_SUBPROPERTY_FIELDS = 0x80000005,
    D2D1_SUBPROPERTY_INDEX = 0x80000006,
    D2D1_SUBPROPERTY_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_BITMAP_OPTIONS {
    D2D1_BITMAP_OPTIONS_NONE = 0x00000000,
    D2D1_BITMAP_OPTIONS_TARGET = 0x00000001,
    D2D1_BITMAP_OPTIONS_CANNOT_DRAW = 0x00000002,
    D2D1_BITMAP_OPTIONS_CPU_READ = 0x00000004,
    D2D1_BITMAP_OPTIONS_GDI_COMPATIBLE = 0x00000008,
    D2D1_BITMAP_OPTIONS_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_COMPOSITE_MODE {
    D2D1_COMPOSITE_MODE_SOURCE_OVER = 0,
    D2D1_COMPOSITE_MODE_DESTINATION_OVER = 1,
    D2D1_COMPOSITE_MODE_SOURCE_IN = 2,
    D2D1_COMPOSITE_MODE_DESTINATION_IN = 3,
    D2D1_COMPOSITE_MODE_SOURCE_OUT = 4,
    D2D1_COMPOSITE_MODE_DESTINATION_OUT = 5,
    D2D1_COMPOSITE_MODE_SOURCE_ATOP = 6,
    D2D1_COMPOSITE_MODE_DESTINATION_ATOP = 7,
    D2D1_COMPOSITE_MODE_XOR = 8,
    D2D1_COMPOSITE_MODE_PLUS = 9,
    D2D1_COMPOSITE_MODE_SOURCE_COPY = 10,
    D2D1_COMPOSITE_MODE_BOUNDED_SOURCE_COPY = 11,
    D2D1_COMPOSITE_MODE_MASK_INVERT = 12,
    D2D1_COMPOSITE_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_BUFFER_PRECISION {
    D2D1_BUFFER_PRECISION_UNKNOWN = 0,
    D2D1_BUFFER_PRECISION_8BPC_UNORM = 1,
    D2D1_BUFFER_PRECISION_8BPC_UNORM_SRGB = 2,
    D2D1_BUFFER_PRECISION_16BPC_UNORM = 3,
    D2D1_BUFFER_PRECISION_16BPC_FLOAT = 4,
    D2D1_BUFFER_PRECISION_32BPC_FLOAT = 5,
    D2D1_BUFFER_PRECISION_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_MAP_OPTIONS {
    D2D1_MAP_OPTIONS_NONE = 0,
    D2D1_MAP_OPTIONS_READ = 1,
    D2D1_MAP_OPTIONS_WRITE = 2,
    D2D1_MAP_OPTIONS_DISCARD = 4,
    D2D1_MAP_OPTIONS_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_INTERPOLATION_MODE {
    D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR = D2D1_INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR,
    D2D1_INTERPOLATION_MODE_LINEAR = D2D1_INTERPOLATION_MODE_DEFINITION_LINEAR,
    D2D1_INTERPOLATION_MODE_CUBIC = D2D1_INTERPOLATION_MODE_DEFINITION_CUBIC,
    D2D1_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = D2D1_INTERPOLATION_MODE_DEFINITION_MULTI_SAMPLE_LINEAR,
    D2D1_INTERPOLATION_MODE_ANISOTROPIC = D2D1_INTERPOLATION_MODE_DEFINITION_ANISOTROPIC,
    D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC = D2D1_INTERPOLATION_MODE_DEFINITION_HIGH_QUALITY_CUBIC,
    D2D1_INTERPOLATION_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_UNIT_MODE {
    D2D1_UNIT_MODE_DIPS = 0,
    D2D1_UNIT_MODE_PIXELS = 1,
    D2D1_UNIT_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_COLOR_SPACE {
    D2D1_COLOR_SPACE_CUSTOM = 0,
    D2D1_COLOR_SPACE_SRGB = 1,
    D2D1_COLOR_SPACE_SCRGB = 2,
    D2D1_COLOR_SPACE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_DEVICE_CONTEXT_OPTIONS {
    D2D1_DEVICE_CONTEXT_OPTIONS_NONE = 0,
    D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS = 1,
    D2D1_DEVICE_CONTEXT_OPTIONS_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_STROKE_TRANSFORM_TYPE {
    D2D1_STROKE_TRANSFORM_TYPE_NORMAL = 0,
    D2D1_STROKE_TRANSFORM_TYPE_FIXED = 1,
    D2D1_STROKE_TRANSFORM_TYPE_HAIRLINE = 2,
    D2D1_STROKE_TRANSFORM_TYPE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_PRIMITIVE_BLEND {
    D2D1_PRIMITIVE_BLEND_SOURCE_OVER = 0,
    D2D1_PRIMITIVE_BLEND_COPY = 1,
    D2D1_PRIMITIVE_BLEND_MIN = 2,
    D2D1_PRIMITIVE_BLEND_ADD = 3,
    D2D1_PRIMITIVE_BLEND_MAX = 4,
    D2D1_PRIMITIVE_BLEND_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_THREADING_MODE {
    D2D1_THREADING_MODE_SINGLE_THREADED = D2D1_FACTORY_TYPE_SINGLE_THREADED,
    D2D1_THREADING_MODE_MULTI_THREADED = D2D1_FACTORY_TYPE_MULTI_THREADED,
    D2D1_THREADING_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_COLOR_INTERPOLATION_MODE {
    D2D1_COLOR_INTERPOLATION_MODE_STRAIGHT = 0,
    D2D1_COLOR_INTERPOLATION_MODE_PREMULTIPLIED = 1,
    D2D1_COLOR_INTERPOLATION_MODE_FORCE_DWORD = 0xffffffff
    }

LPID2D1ColorContext	typedef ptr ID2D1ColorContext
D2D1_BITMAP_PROPERTIES1 STRUC
pixelFormat		D2D1_PIXEL_FORMAT <>
dpiX			FLOAT ?
dpiY			FLOAT ?
bitmapOptions		D2D1_BITMAP_OPTIONS ?
colorContext		LPID2D1ColorContext ?
D2D1_BITMAP_PROPERTIES1 ENDS

D2D1_MAPPED_RECT	STRUC
pitch			UINT32 ?
bits			LPBYTE ?
D2D1_MAPPED_RECT	ENDS

D2D1_RENDERING_CONTROLS STRUC
bufferPrecision		D2D1_BUFFER_PRECISION ?
tileSize		D2D1_SIZE_U <>
D2D1_RENDERING_CONTROLS ENDS


LPID2D1Effect		typedef ptr ID2D1Effect
D2D1_EFFECT_INPUT_DESCRIPTION STRUC
effect			LPID2D1Effect ?
inputIndex		UINT32 ?
inputRectangle		D2D1_RECT_F <>
D2D1_EFFECT_INPUT_DESCRIPTION ENDS

D2D1_POINT_DESCRIPTION	STRUC
point			D2D1_POINT_2F <>
unitTangentVector	D2D1_POINT_2F <>
endSegment		UINT32 ?
endFigure		UINT32 ?
lengthToEndSegment	FLOAT ?
D2D1_POINT_DESCRIPTION	ENDS

D2D1_IMAGE_BRUSH_PROPERTIES STRUC
sourceRectangle		D2D1_RECT_F <>
extendModeX		D2D1_EXTEND_MODE ?
extendModeY		D2D1_EXTEND_MODE ?
interpolationMode	D2D1_INTERPOLATION_MODE ?
D2D1_IMAGE_BRUSH_PROPERTIES ENDS

D2D1_BITMAP_BRUSH_PROPERTIES1 STRUC
extendModeX		D2D1_EXTEND_MODE ?
extendModeY		D2D1_EXTEND_MODE ?
interpolationMode	D2D1_INTERPOLATION_MODE ?
D2D1_BITMAP_BRUSH_PROPERTIES1 ENDS


D2D1_STROKE_STYLE_PROPERTIES1 STRUC
startCap		D2D1_CAP_STYLE ?
endCap			D2D1_CAP_STYLE ?
dashCap			D2D1_CAP_STYLE ?
lineJoin		D2D1_LINE_JOIN ?
miterLimit		FLOAT ?
dashStyle		D2D1_DASH_STYLE ?
dashOffset		FLOAT ?
transformType		D2D1_STROKE_TRANSFORM_TYPE ?
D2D1_STROKE_STYLE_PROPERTIES1 ENDS

.enum D2D1_LAYER_OPTIONS1 {
    D2D1_LAYER_OPTIONS1_NONE = 0,
    D2D1_LAYER_OPTIONS1_INITIALIZE_FROM_BACKGROUND = 1,
    D2D1_LAYER_OPTIONS1_IGNORE_ALPHA = 2,
    D2D1_LAYER_OPTIONS1_FORCE_DWORD = 0xffffffff
    }

D2D1_LAYER_PARAMETERS1	STRUC
contentBounds		D2D1_RECT_F <>
geometricMask		LPID2D1Geometry ?
maskAntialiasMode	D2D1_ANTIALIAS_MODE ?
maskTransform		D2D1_MATRIX_3X2_F <>
opacity			FLOAT ?
opacityBrush		LPID2D1Brush ?
layerOptions		D2D1_LAYER_OPTIONS1 ?
D2D1_LAYER_PARAMETERS1	ENDS


.enum D2D1_PRINT_FONT_SUBSET_MODE {
    D2D1_PRINT_FONT_SUBSET_MODE_DEFAULT = 0,
    D2D1_PRINT_FONT_SUBSET_MODE_EACHPAGE = 1,
    D2D1_PRINT_FONT_SUBSET_MODE_NONE = 2,
    D2D1_PRINT_FONT_SUBSET_MODE_FORCE_DWORD = 0xffffffff
    }


D2D1_DRAWING_STATE_DESCRIPTION1 STRUC
antialiasMode		D2D1_ANTIALIAS_MODE ?
textAntialiasMode	D2D1_TEXT_ANTIALIAS_MODE ?
tag1			D2D1_TAG ?
tag2			D2D1_TAG ?
transform		D2D1_MATRIX_3X2_F <>
primitiveBlend		D2D1_PRIMITIVE_BLEND ?
unitMode		D2D1_UNIT_MODE ?
D2D1_DRAWING_STATE_DESCRIPTION1 ENDS


D2D1_PRINT_CONTROL_PROPERTIES STRUC
fontSubset		D2D1_PRINT_FONT_SUBSET_MODE ?
rasterDPI		FLOAT ?
colorSpace		D2D1_COLOR_SPACE ?
D2D1_PRINT_CONTROL_PROPERTIES ENDS

D2D1_CREATION_PROPERTIES STRUC
threadingMode		D2D1_THREADING_MODE ?
debugLevel		D2D1_DEBUG_LEVEL ?
options			D2D1_DEVICE_CONTEXT_OPTIONS ?
D2D1_CREATION_PROPERTIES ENDS


externdef		IID_ID2D1GdiMetafileSink:IID
externdef		IID_ID2D1GdiMetafile:IID
externdef		IID_ID2D1CommandSink:IID
externdef		IID_ID2D1CommandList:IID
externdef		IID_ID2D1PrintControl:IID
externdef		IID_ID2D1ImageBrush:IID
externdef		IID_ID2D1BitmapBrush1:IID
externdef		IID_ID2D1StrokeStyle1:IID
externdef		IID_ID2D1PathGeometry1:IID
externdef		IID_ID2D1Properties:IID
externdef		IID_ID2D1Effect:IID
externdef		IID_ID2D1Bitmap1:IID
externdef		IID_ID2D1ColorContext:IID
externdef		IID_ID2D1GradientStopCollection1:IID
externdef		IID_ID2D1DrawingStateBlock1:IID
externdef		IID_ID2D1DeviceContext:IID
externdef		IID_ID2D1Device:IID
externdef		IID_ID2D1Factory1:IID
externdef		IID_ID2D1Multithread:IID


ifndef D2D_USE_C_DEFINITIONS

DEFINE_IIDX(ID2D1GdiMetafileSink, "82237326-8111-4f7c-bcf4-b5c1175564fe")

.comdef ID2D1GdiMetafileSink : public IUnknown

    ProcessRecord	proc :DWORD, :ptr, :DWORD
    .ends


DEFINE_IIDX(ID2D1GdiMetafile, "2f543dc3-cfc1-4211-864f-cfd91c6f3395")

.comdef ID2D1GdiMetafile : public ID2D1Resource

    Stream		proc :ptr ID2D1GdiMetafileSink
    GetBounds		proc :ptr D2D1_RECT_F
    .ends


DEFINE_IIDX(ID2D1CommandSink, "54d7898a-a061-40a7-bec7-e465bcba2c4f")

.comdef ID2D1CommandSink : public IUnknown

    BeginDraw		proc
    EndDraw		proc
    SetAntialiasMode	proc :D2D1_ANTIALIAS_MODE
    SetTags		proc :D2D1_TAG, :D2D1_TAG
    SetTextAntialiasMode proc :D2D1_TEXT_ANTIALIAS_MODE
    SetTextRenderingParams proc :ptr IDWriteRenderingParams
    SetTransform	proc :ptr D2D1_MATRIX_3X2_F
    SetPrimitiveBlend	proc :D2D1_PRIMITIVE_BLEND
    SetUnitMode		proc :D2D1_UNIT_MODE
    Clear		proc :ptr D2D1_COLOR_F
    DrawGlyphRun	proc :D2D1_POINT_2F, :ptr DWRITE_GLYPH_RUN, :ptr DWRITE_GLYPH_RUN_DESCRIPTION, :ptr ID2D1Brush, :DWRITE_MEASURING_MODE
    DrawLine		proc :D2D1_POINT_2F, :D2D1_POINT_2F, :ptr ID2D1Brush, :FLOAT, :ptr ID2D1StrokeStyle
    DrawGeometry	proc :ptr ID2D1Geometry, :ptr ID2D1Brush, :FLOAT, :ptr ID2D1StrokeStyle
    DrawRectangle	proc :ptr D2D1_RECT_F, :ptr ID2D1Brush, :FLOAT, :ptr ID2D1StrokeStyle
    DrawBitmap		proc :ptr ID2D1Bitmap, :ptr D2D1_RECT_F, :FLOAT, :D2D1_INTERPOLATION_MODE, :ptr D2D1_RECT_F, :ptr D2D1_MATRIX_4X4_F
    DrawImage		proc :ptr ID2D1Imagee, :ptr D2D1_POINT_2F, :ptr D2D1_RECT_F, :D2D1_INTERPOLATION_MODE, :D2D1_COMPOSITE_MODE
    DrawGdiMetafile	proc :ptr ID2D1GdiMetafile, :ptr D2D1_POINT_2F
    FillMesh		proc :ptr ID2D1Mesh, :ptr ID2D1Brush
    FillOpacityMask	proc :ptr ID2D1Bitmap, :ptr ID2D1Brush, :ptr D2D1_RECT_F, :ptr D2D1_RECT_F
    FillGeometry	proc :ptr ID2D1Geometry, :ptr ID2D1Brush, :ptr ID2D1Brush
    FillRectangle	proc :ptr D2D1_RECT_F, :ptr ID2D1Brush
    PushAxisAlignedClip proc :ptr D2D1_RECT_F, :D2D1_ANTIALIAS_MODE
    PushLayer		proc :ptr D2D1_LAYER_PARAMETERS1, :ptr ID2D1Layer
    PopAxisAlignedClip	proc
    PopLayer		proc
    .ends


DEFINE_IIDX(ID2D1CommandList, "b4f34a19-2383-4d76-94f6-ec343657c3dc")

.comdef ID2D1CommandList  : public ID2D1Image

    Stream		proc :ID2D1CommandSink
    Close		proc
    .ends


DEFINE_IIDX(ID2D1PrintControl, "2c1d867d-c290-41c8-ae7e-34a98702e9a5")

.comdef ID2D1PrintControl  : public IUnknown

    AddPage		proc :ptr ID2D1CommandList, :D2D_SIZE_F, :ptr IStream, :ptr D2D1_TAG, :ptr D2D1_TAG
    Close		proc
    .ends


DEFINE_IIDX(ID2D1ImageBrush, "fe9e984d-3f95-407c-b5db-cb94d4e8f87c")

.comdef ID2D1ImageBrush	 : public ID2D1Brush

     SetImage		proc :ptr ID2D1Image
     SetExtendModeX	proc :D2D1_EXTEND_MODE
     SetExtendModeY	proc :D2D1_EXTEND_MODE
     SetInterpolationMode proc :D2D1_INTERPOLATION_MODE
     SetSourceRectangle proc :ptr D2D1_RECT_F
     GetImage		proc :ptr ptr ID2D1Image
     GetExtendModeX	proc
     GetExtendModeY	proc
     GetInterpolationMode proc
     GetSourceRectangle proc :ptr D2D1_RECT_F
    .ends


DEFINE_IIDX(ID2D1BitmapBrush1, "41343a53-e41a-49a2-91cd-21793bbb62e5")

.comdef ID2D1BitmapBrush1  : public ID2D1BitmapBrush

     SetInterpolationMode1 proc :D2D1_INTERPOLATION_MODE
     GetInterpolationMode1 proc
    .ends


DEFINE_IIDX(ID2D1StrokeStyle1, "10a72a66-e91c-43f4-993f-ddf4b82b0b4a")

.comdef ID2D1StrokeStyle1  : public ID2D1StrokeStyle

     GetStrokeTransformType proc
    .ends


DEFINE_IIDX(ID2D1PathGeometry1, "62baa2d2-ab54-41b7-b872-787e0106a421")

.comdef ID2D1PathGeometry1  : public ID2D1PathGeometry

    ComputePointAndSegmentAtLength proc :FLOAT, :UINT32, :ptr D2D1_MATRIX_3X2_F,
	:FLOAT, :ptr D2D1_POINT_DESCRIPTION

    .ends


DEFINE_IIDX(ID2D1Properties, "483473d7-cd46-4f9d-9d3a-3112aa80159d")

.comdef ID2D1Properties	 : public IUnknown

     GetPropertyCount	proc
     GetPropertyName	proc :UINT32, :UINT32
     GetPropertyNameLength proc :UINT32
     GetType		proc :UINT32
     GetPropertyIndex	proc :PCWSTR
     SetValueByName	proc :PCWSTR, :D2D1_PROPERTY_TYPE, :UINT32
     SetValue		proc :UINT32, :D2D1_PROPERTY_TYPE, :UINT32
     GetValueByName	proc :PCWSTR, :D2D1_PROPERTY_TYPE, :UINT32
     GetValue		proc :UINT32, :D2D1_PROPERTY_TYPE, :UINT32
     GetValueSize	proc :UINT32
     GetSubProperties	proc :UINT32, :ptr ptr ID2D1Properties
    .ends


DEFINE_IIDX(ID2D1Effect, "28211a43-7d89-476f-8181-2d6159b220ad")

.comdef ID2D1Effect : public ID2D1Properties

     SetInput		proc :UINT32, :ptr ID2D1Image, :BOOL
     SetInputCount	proc :UINT32
     GetInput		proc :UINT32, :ptr ptr ID2D1Image
     GetInputCount	proc
     GetOutput		proc :ptr ptr ID2D1Image

    .ends


DEFINE_IIDX(ID2D1Bitmap1, "a898a84c-3873-4588-b08b-ebbf978df041")

.comdef ID2D1Bitmap1 : public ID2D1Bitmap

     GetColorContext	proc :ptr ptr ID2D1ColorContext
     GetOptions		proc
     GetSurface		proc :ptr ptr IDXGISurface
     Map		proc :D2D1_MAP_OPTIONS, :ptr D2D1_MAPPED_RECT
     Unmap		proc
    .ends


DEFINE_IIDX(ID2D1ColorContext, "1c4820bb-5771-4518-a581-2fe4dd0ec657")

.comdef ID2D1ColorContext  : public ID2D1Resource

     GetColorSpace	proc
     GetProfileSize	proc
     GetProfile		proc :UINT32
    .ends


DEFINE_IIDX(ID2D1GradientStopCollection1, "ae1572f4-5dd0-4777-998b-9279472ae63b")

.comdef ID2D1GradientStopCollection1 : public ID2D1GradientStopCollection

     GetGradientStops1	proc :UINT32
     GetPreInterpolationSpace proc
     GetPostInterpolationSpace proc
     GetBufferPrecision proc
     GetColorInterpolationMode proc
    .ends


DEFINE_IIDX(ID2D1DrawingStateBlock1, "689f1f85-c72e-4e33-8f19-85754efd5ace")

.comdef ID2D1DrawingStateBlock1	 : public ID2D1DrawingStateBlock

     ;GetDescription	proc :ptr D2D1_DRAWING_STATE_DESCRIPTION1
     ;SetDescription	proc :ptr D2D1_DRAWING_STATE_DESCRIPTION1

    .ends


DEFINE_IIDX(ID2D1DeviceContext, "e8f7fe7a-191c-466d-ad95-975678bda998")

.comdef ID2D1DeviceContext : public ID2D1RenderTarget

    ;CreateBitmap	proc :D2D1_SIZE_U, :ptr, :UINT32, :ptr D2D1_BITMAP_PROPERTIES1, :ptr ptr ID2D1Bitmap1
    ;CreateBitmapFromWicBitmap proc :ptr IWICBitmapSource, :ptr D2D1_BITMAP_PROPERTIES1, :ptr ptr ID2D1Bitmap1
    CreateColorContext	proc :D2D1_COLOR_SPACE
    CreateColorContextFromFilename proc :PCWSTR, :ptr ptr ID2D1ColorContext
    CreateColorContextFromWicColorContext proc :ptr IWICColorContext, :ptr ptr ID2D1ColorContext
    ;CreateBitmapFromDxgiSurface :ptr IDXGISurface, :ptr D2D1_BITMAP_PROPERTIES1, :ptr ptr ID2D1Bitmap1
    CreateEffect	proc :REFCLSID, :ptr ptr ID2D1Effect
    ;CreateGradientStopCollection proc :UINT32, :D2D1_COLOR_SPACE, :D2D1_COLOR_SPACE, :D2D1_BUFFER_PRECISION, :D2D1_EXTEND_MODE, :D2D1_COLOR_INTERPOLATION_MODE, :ptr ptr ID2D1GradientStopCollection1
    CreateImageBrush	proc :ptr ID2D1Image, :ptr D2D1_IMAGE_BRUSH_PROPERTIES, :ptr D2D1_BRUSH_PROPERTIES, :ptr ptr ID2D1ImageBrush
    ;CreateBitmapBrush	proc :ptr ID2D1Bitmap, :ptr D2D1_BITMAP_BRUSH_PROPERTIES1, :ptr D2D1_BRUSH_PROPERTIES, :ptr ptr ID2D1BitmapBrush1
    CreateCommandList	proc :ptr ptr ID2D1CommandList
    IsDxgiFormatSupported proc :DXGI_FORMAT
    IsBufferPrecisionSupported proc :D2D1_BUFFER_PRECISION
    GetImageLocalBounds proc :ptr ID2D1Image, :ptr D2D1_RECT_F
    GetImageWorldBounds proc :ptr ID2D1Image, :ptr D2D1_RECT_F
    GetGlyphRunWorldBounds proc :D2D1_POINT_2F, :ptr DWRITE_GLYPH_RUN, :DWRITE_MEASURING_MODE, :ptr D2D1_RECT_F
    GetDevice		proc :ptr ptr ID2D1Device
    SetTarget		proc :ptr ID2D1Image
    GetTarget		proc :ptr ptr ID2D1Image
    SetRenderingControls proc :ptr D2D1_RENDERING_CONTROLS
    GetRenderingControls proc :ptr D2D1_RENDERING_CONTROLS
    SetPrimitiveBlend	proc :D2D1_PRIMITIVE_BLEND
    GetPrimitiveBlend	proc
    SetUnitMode		proc :D2D1_UNIT_MODE
    GetUnitMode		proc
    ;DrawGlyphRun	proc :D2D1_POINT_2F, :ptr DWRITE_GLYPH_RUN, :ptr DWRITE_GLYPH_RUN_DESCRIPTION, :ptr ID2D1Brush, :DWRITE_MEASURING_MODE
    DrawImage		proc :ptr ID2D1Image, :ptr D2D1_POINT_2F, :ptr D2D1_RECT_F, :D2D1_INTERPOLATION_MODE, :D2D1_COMPOSITE_MODE
    DrawGdiMetafile	proc :ptr ID2D1GdiMetafile, :ptr D2D1_POINT_2F
    ;DrawBitmap		proc :ptr ID2D1Bitmap, :ptr D2D1_RECT_F, :FLOAT, :D2D1_INTERPOLATION_MODE, :ptr D2D1_RECT_F, :ptr D2D1_MATRIX_4X4_F
    ;PushLayer		proc :D2D1_LAYER_PARAMETERS1 *layerParameters,,_In_opt_ ID2D1Layer *layer,
    InvalidateEffectInputRectangle proc :ptr ID2D1Effect, :UINT32, :ptr D2D1_RECT_F
    GetEffectInvalidRectangleCount proc :ptr ID2D1Effect, :ptr UINT32
    GetEffectInvalidRectangles proc :ptr ID2D1Effect, :UINT32
    GetEffectRequiredInputRectangles proc :ptr ID2D1Effect, :ptr D2D1_RECT_F, :ptr D2D1_RECT_F, :UINT32
    ;FillOpacityMask	proc :ptr ID2D1Bitmap, :ptr ID2D1Brush, :ptr D2D1_RECT_F, :ptr D2D1_RECT_F
    .ends


DEFINE_IIDX(ID2D1Device, "47dd575d-ac05-4cdd-8049-9b02cd16f44c")

.comdef ID2D1Device : public ID2D1Resource

    CreateDeviceContext proc :D2D1_DEVICE_CONTEXT_OPTIONS, :ptr ptr ID2D1DeviceContext
    CreatePrintControl	proc :ptr IWICImagingFactory, :ptr IPrintDocumentPackageTarget, :ptr D2D1_PRINT_CONTROL_PROPERTIES, :ptr ptr ID2D1PrintControl
    SetMaximumTextureMemory proc :UINT64
    GetMaximumTextureMemory proc
    ClearResources	proc :UINT32

    .ends


DEFINE_IIDX(ID2D1Factory1, "bb12d362-daee-4b9a-aa1d-14ba401cfa1f")

.comdef ID2D1Factory1 : public ID2D1Factory

    CreateDevice	proc :ptr IDXGIDevice, :ptr ptr
    ;CreateStrokeStyle	proc :ptr D2D1_STROKE_STYLE_PROPERTIES1, :UINT32, :ptr ptr ID2D1StrokeStyle1
    ;CreatePathGeometry proc :ptr ptr ID2D1PathGeometry1
    ;CreateDrawingStateBlock proc :ptr D2D1_DRAWING_STATE_DESCRIPTION1, :ptr IDWriteRenderingParams, :ptr ptr ID2D1DrawingStateBlock1
    CreateGdiMetafile	proc :ptr IStream, :ptr ptr ID2D1GdiMetafile
    RegisterEffectFromStream proc :REFCLSID, :ptr IStream, :UINT32, :PD2D1_EFFECT_FACTORY
    RegisterEffectFromString proc :REFCLSID, :PCWSTR, :UINT32, :PD2D1_EFFECT_FACTORY
    UnregisterEffect	proc :REFCLSID
    GetRegisteredEffects proc :UINT32, :ptr UINT32, :ptr UINT32
    GetEffectProperties proc :REFCLSID, :ptr ptr ID2D1Properties

    .ends

DEFINE_IIDX(,ID2D1Multithread "31e6e7bc-e0ff-4d46-8c64-a0a8c41c15d3")

.comdef ID2D1Multithread : public IUnknown

     GetMultithreadProtected proc
     _Enter		proc
     _Leave		proc

    .ends

endif

include d2d1_1helper.inc

endif
