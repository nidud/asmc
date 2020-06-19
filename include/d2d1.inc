.pragma list(push, 0)

ifndef _D2D1_H_
_D2D1_H_ equ <>

ifndef COM_NO_WINDOWS_H
include windows.inc
endif
include unknwn.inc
include dcommon.inc
include D2DErr.inc
include D2DBaseTypes.inc
include dxgiformat.inc
ifndef D2D_NO_INCLUDE_D3D10
include d3d10_1.inc
endif

.pragma comment(lib, d2d1)

D2D1_INVALID_TAG  equ ULONGLONG_MAX
D2D1_DEFAULT_FLATTENING_TOLERANCE equ 0.25

.enum D2D1_ALPHA_MODE {
    D2D1_ALPHA_MODE_UNKNOWN = 0,
    D2D1_ALPHA_MODE_PREMULTIPLIED = 1,
    D2D1_ALPHA_MODE_STRAIGHT = 2,
    D2D1_ALPHA_MODE_IGNORE = 3,
    D2D1_ALPHA_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_GAMMA {
    D2D1_GAMMA_2_2 = 0,
    D2D1_GAMMA_1_0 = 1,
    D2D1_GAMMA_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_OPACITY_MASK_CONTENT {
    D2D1_OPACITY_MASK_CONTENT_GRAPHICS = 0,
    D2D1_OPACITY_MASK_CONTENT_TEXT_NATURAL = 1,
    D2D1_OPACITY_MASK_CONTENT_TEXT_GDI_COMPATIBLE = 2,
    D2D1_OPACITY_MASK_CONTENT_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_EXTEND_MODE {
    D2D1_EXTEND_MODE_CLAMP = 0,
    D2D1_EXTEND_MODE_WRAP = 1,
    D2D1_EXTEND_MODE_MIRROR = 2,
    D2D1_EXTEND_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_ANTIALIAS_MODE {
    D2D1_ANTIALIAS_MODE_PER_PRIMITIVE = 0,
    D2D1_ANTIALIAS_MODE_ALIASED = 1,
    D2D1_ANTIALIAS_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_TEXT_ANTIALIAS_MODE {
    D2D1_TEXT_ANTIALIAS_MODE_DEFAULT = 0,
    D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE = 1,
    D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE = 2,
    D2D1_TEXT_ANTIALIAS_MODE_ALIASED = 3,
    D2D1_TEXT_ANTIALIAS_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_BITMAP_INTERPOLATION_MODE {
    D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
    D2D1_BITMAP_INTERPOLATION_MODE_LINEAR = 1,
    D2D1_BITMAP_INTERPOLATION_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_DRAW_TEXT_OPTIONS {
    D2D1_DRAW_TEXT_OPTIONS_NO_SNAP = 0x00000001,
    D2D1_DRAW_TEXT_OPTIONS_CLIP = 0x00000002,
    D2D1_DRAW_TEXT_OPTIONS_NONE = 0x00000000,
    D2D1_DRAW_TEXT_OPTIONS_FORCE_DWORD = 0xffffffff
    }

DEFINE_ENUM_FLAG_OPERATORS(D2D1_DRAW_TEXT_OPTIONS);


D2D1_PIXEL_FORMAT	STRUC
format			DXGI_FORMAT ?
alphaMode		D2D1_ALPHA_MODE ?
D2D1_PIXEL_FORMAT	ENDS

D2D1_POINT_2U		typedef D2D_POINT_2U
D2D1_POINT_2F		typedef D2D_POINT_2F
D2D1_RECT_F		typedef D2D_RECT_F
D2D1_RECT_U		typedef D2D_RECT_U
D2D1_SIZE_F		typedef D2D_SIZE_F
D2D1_SIZE_U		typedef D2D_SIZE_U
D2D1_COLOR_F		typedef D2D_COLOR_F
D2D1_MATRIX_3X2_F	typedef D2D_MATRIX_3X2_F
D2D1_TAG		typedef UINT64

D2D1_BITMAP_PROPERTIES	STRUC
pixelFormat		D2D1_PIXEL_FORMAT <>
dpiX			FLOAT ?
dpiY			FLOAT ?

D2D1_BITMAP_PROPERTIES	ENDS


D2D1_GRADIENT_STOP	STRUC
position		FLOAT ?
color			D2D1_COLOR_F <>

D2D1_GRADIENT_STOP	ENDS


D2D1_BRUSH_PROPERTIES	STRUC
opacity			FLOAT ?
transform		D2D1_MATRIX_3X2_F <>

D2D1_BRUSH_PROPERTIES	ENDS


D2D1_BITMAP_BRUSH_PROPERTIES STRUC
extendModeX		D2D1_EXTEND_MODE ?
extendModeY		D2D1_EXTEND_MODE ?
interpolationMode	D2D1_BITMAP_INTERPOLATION_MODE ?

D2D1_BITMAP_BRUSH_PROPERTIES ENDS


D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES STRUC
startPoint		D2D1_POINT_2F <>
endPoint		D2D1_POINT_2F <>

D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES ENDS


D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES STRUC
center			D2D1_POINT_2F <>
gradientOriginOffset	D2D1_POINT_2F <>
radiusX			FLOAT ?
radiusY			FLOAT ?

D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES ENDS


.enum D2D1_ARC_SIZE {
    D2D1_ARC_SIZE_SMALL = 0,
    D2D1_ARC_SIZE_LARGE = 1,
    D2D1_ARC_SIZE_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_CAP_STYLE {
    D2D1_CAP_STYLE_FLAT = 0,
    D2D1_CAP_STYLE_SQUARE = 1,
    D2D1_CAP_STYLE_ROUND = 2,
    D2D1_CAP_STYLE_TRIANGLE = 3,
    D2D1_CAP_STYLE_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_DASH_STYLE {
    D2D1_DASH_STYLE_SOLID = 0,
    D2D1_DASH_STYLE_DASH = 1,
    D2D1_DASH_STYLE_DOT = 2,
    D2D1_DASH_STYLE_DASH_DOT = 3,
    D2D1_DASH_STYLE_DASH_DOT_DOT = 4,
    D2D1_DASH_STYLE_CUSTOM = 5,
    D2D1_DASH_STYLE_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_LINE_JOIN {
    D2D1_LINE_JOIN_MITER = 0,
    D2D1_LINE_JOIN_BEVEL = 1,
    D2D1_LINE_JOIN_ROUND = 2,
    D2D1_LINE_JOIN_MITER_OR_BEVEL = 3,
    D2D1_LINE_JOIN_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_COMBINE_MODE {
    D2D1_COMBINE_MODE_UNION = 0,
    D2D1_COMBINE_MODE_INTERSECT = 1,
    D2D1_COMBINE_MODE_XOR = 2,
    D2D1_COMBINE_MODE_EXCLUDE = 3,
    D2D1_COMBINE_MODE_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_GEOMETRY_RELATION {
    D2D1_GEOMETRY_RELATION_UNKNOWN = 0,
    D2D1_GEOMETRY_RELATION_DISJOINT = 1,
    D2D1_GEOMETRY_RELATION_IS_CONTAINED = 2,
    D2D1_GEOMETRY_RELATION_CONTAINS = 3,
    D2D1_GEOMETRY_RELATION_OVERLAP = 4,
    D2D1_GEOMETRY_RELATION_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_GEOMETRY_SIMPLIFICATION_OPTION {
    D2D1_GEOMETRY_SIMPLIFICATION_OPTION_CUBICS_AND_LINES = 0,
    D2D1_GEOMETRY_SIMPLIFICATION_OPTION_LINES = 1,
    D2D1_GEOMETRY_SIMPLIFICATION_OPTION_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_FIGURE_BEGIN {
    D2D1_FIGURE_BEGIN_FILLED = 0,
    D2D1_FIGURE_BEGIN_HOLLOW = 1,
    D2D1_FIGURE_BEGIN_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_FIGURE_END {
    D2D1_FIGURE_END_OPEN = 0,
    D2D1_FIGURE_END_CLOSED = 1,
    D2D1_FIGURE_END_FORCE_DWORD = 0xffffffff
    }


D2D1_BEZIER_SEGMENT	STRUC
point1			D2D1_POINT_2F <>
point2			D2D1_POINT_2F <>
point3			D2D1_POINT_2F <>
D2D1_BEZIER_SEGMENT	ENDS


D2D1_TRIANGLE		STRUC
point1			D2D1_POINT_2F <>
point2			D2D1_POINT_2F <>
point3			D2D1_POINT_2F <>
D2D1_TRIANGLE		ENDS


.enum D2D1_PATH_SEGMENT {
    D2D1_PATH_SEGMENT_NONE = 0x00000000,
    D2D1_PATH_SEGMENT_FORCE_UNSTROKED = 0x00000001,
    D2D1_PATH_SEGMENT_FORCE_ROUND_LINE_JOIN = 0x00000002,
    D2D1_PATH_SEGMENT_FORCE_DWORD = 0xffffffff
    }

DEFINE_ENUM_FLAG_OPERATORS(D2D1_PATH_SEGMENT);


.enum D2D1_SWEEP_DIRECTION {
    D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE = 0,
    D2D1_SWEEP_DIRECTION_CLOCKWISE = 1,
    D2D1_SWEEP_DIRECTION_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_FILL_MODE {
    D2D1_FILL_MODE_ALTERNATE = 0,
    D2D1_FILL_MODE_WINDING = 1,
    D2D1_FILL_MODE_FORCE_DWORD = 0xffffffff
    }


D2D1_ARC_SEGMENT	STRUC
point			D2D1_POINT_2F <>
size			D2D1_SIZE_F <>
rotationAngle		FLOAT ?
sweepDirection		D2D1_SWEEP_DIRECTION ?
arcSize			D2D1_ARC_SIZE ?
D2D1_ARC_SEGMENT	ENDS


D2D1_QUADRATIC_BEZIER_SEGMENT STRUC
point1			D2D1_POINT_2F <>
point2			D2D1_POINT_2F <>
D2D1_QUADRATIC_BEZIER_SEGMENT ENDS


D2D1_ELLIPSE		STRUC
point			D2D1_POINT_2F <>
radiusX			FLOAT ?
radiusY			FLOAT ?
D2D1_ELLIPSE		ENDS


D2D1_ROUNDED_RECT	STRUC
rect			D2D1_RECT_F <>
radiusX			FLOAT ?
radiusY			FLOAT ?
D2D1_ROUNDED_RECT	ENDS


D2D1_STROKE_STYLE_PROPERTIES STRUC
startCap		D2D1_CAP_STYLE ?
endCap			D2D1_CAP_STYLE ?
dashCap			D2D1_CAP_STYLE ?
lineJoin		D2D1_LINE_JOIN ?
miterLimit		FLOAT ?
dashStyle		D2D1_DASH_STYLE ?
dashOffset		FLOAT ?
D2D1_STROKE_STYLE_PROPERTIES ENDS

.enum D2D1_LAYER_OPTIONS {
    D2D1_LAYER_OPTIONS_NONE = 0x00000000,
    D2D1_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE = 0x00000001,
    D2D1_LAYER_OPTIONS_FORCE_DWORD = 0xffffffff
    }

DEFINE_ENUM_FLAG_OPERATORS(D2D1_LAYER_OPTIONS)

LPID2D1Geometry typedef ptr ID2D1Geometry
LPID2D1Brush	typedef ptr ID2D1Brush

D2D1_LAYER_PARAMETERS	STRUC
contentBounds		D2D1_RECT_F <>
geometricMask		LPID2D1Geometry ?
maskAntialiasMode	D2D1_ANTIALIAS_MODE ?
maskTransform		D2D1_MATRIX_3X2_F <>
opacity			FLOAT ?
opacityBrush		LPID2D1Brush ?
layerOptions		D2D1_LAYER_OPTIONS ?
D2D1_LAYER_PARAMETERS	ENDS


.enum D2D1_WINDOW_STATE {
    D2D1_WINDOW_STATE_NONE = 0x0000000,
    D2D1_WINDOW_STATE_OCCLUDED = 0x0000001,
    D2D1_WINDOW_STATE_FORCE_DWORD = 0xffffffff
    }

DEFINE_ENUM_FLAG_OPERATORS(D2D1_WINDOW_STATE);


.enum D2D1_RENDER_TARGET_TYPE {
    D2D1_RENDER_TARGET_TYPE_DEFAULT = 0,
    D2D1_RENDER_TARGET_TYPE_SOFTWARE = 1,
    D2D1_RENDER_TARGET_TYPE_HARDWARE = 2,
    D2D1_RENDER_TARGET_TYPE_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_FEATURE_LEVEL {
    D2D1_FEATURE_LEVEL_DEFAULT = 0,
    D2D1_FEATURE_LEVEL_9 = D3D10_FEATURE_LEVEL_9_1,
    D2D1_FEATURE_LEVEL_10 = D3D10_FEATURE_LEVEL_10_0,
    D2D1_FEATURE_LEVEL_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_RENDER_TARGET_USAGE {
    D2D1_RENDER_TARGET_USAGE_NONE = 0x00000000,
    D2D1_RENDER_TARGET_USAGE_FORCE_BITMAP_REMOTING = 0x00000001,
    D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE = 0x00000002,
    D2D1_RENDER_TARGET_USAGE_FORCE_DWORD = 0xffffffff
    }

DEFINE_ENUM_FLAG_OPERATORS(D2D1_RENDER_TARGET_USAGE);


.enum D2D1_PRESENT_OPTIONS {
    D2D1_PRESENT_OPTIONS_NONE = 0x00000000,
    D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS = 0x00000001,
    D2D1_PRESENT_OPTIONS_IMMEDIATELY = 0x00000002,
    D2D1_PRESENT_OPTIONS_FORCE_DWORD = 0xffffffff
    }

DEFINE_ENUM_FLAG_OPERATORS(D2D1_PRESENT_OPTIONS);

.template D2D1_RENDER_TARGET_PROPERTIES

    type	D2D1_RENDER_TARGET_TYPE ?
    pixelFormat D2D1_PIXEL_FORMAT <>
    dpiX	FLOAT ?
    dpiY	FLOAT ?
    usage	D2D1_RENDER_TARGET_USAGE ?
    minLevel	D2D1_FEATURE_LEVEL ?

    .operator D2D1_RENDER_TARGET_PROPERTIES :abs=<D2D1_RENDER_TARGET_TYPE_DEFAULT>,\
	:abs=<0>, :abs=<0.0>, :abs=<0.0>, :abs=<D2D1_RENDER_TARGET_USAGE_NONE>,\
	:abs=<D2D1_FEATURE_LEVEL_DEFAULT>, :vararg {
	mov this.type,_1
	mov this.pixelFormat.format,DXGI_FORMAT_UNKNOWN
	mov this.pixelFormat.alphaMode,D2D1_ALPHA_MODE_UNKNOWN
	mov this.dpiX,_3
	mov this.dpiY,_4
	mov this.usage,_5
	mov this.minLevel,_6
	}
    .ends

.template D2D1_HWND_RENDER_TARGET_PROPERTIES

    hwnd	   HWND ?
    pixelSize	   D2D1_SIZE_U <>
    presentOptions D2D1_PRESENT_OPTIONS ?

    .operator D2D1_HWND_RENDER_TARGET_PROPERTIES :abs,\
	:abs=<0>, :abs=<0>, :abs=<D2D1_PRESENT_OPTIONS_NONE>, :vararg {
	mov this.hwnd,_1
	mov this.pixelSize.width,_2
	mov this.pixelSize.height,_3
	mov this.presentOptions,_4
	}

    .ends

.enum D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS {
    D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE = 0x00000000,
    D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_GDI_COMPATIBLE = 0x00000001,
    D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_FORCE_DWORD = 0xffffffff
    }

DEFINE_ENUM_FLAG_OPERATORS(D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS);


D2D1_DRAWING_STATE_DESCRIPTION STRUC
antialiasMode		D2D1_ANTIALIAS_MODE ?
textAntialiasMode	D2D1_TEXT_ANTIALIAS_MODE ?
tag1			D2D1_TAG ?
tag2			D2D1_TAG ?
transform		D2D1_MATRIX_3X2_F <>
D2D1_DRAWING_STATE_DESCRIPTION ENDS

.enum D2D1_DC_INITIALIZE_MODE {
    D2D1_DC_INITIALIZE_MODE_COPY = 0,
    D2D1_DC_INITIALIZE_MODE_CLEAR = 1,
    D2D1_DC_INITIALIZE_MODE_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_DEBUG_LEVEL {
    D2D1_DEBUG_LEVEL_NONE = 0,
    D2D1_DEBUG_LEVEL_ERROR = 1,
    D2D1_DEBUG_LEVEL_WARNING = 2,
    D2D1_DEBUG_LEVEL_INFORMATION = 3,
    D2D1_DEBUG_LEVEL_FORCE_DWORD = 0xffffffff
    }

.enum D2D1_FACTORY_TYPE {
    D2D1_FACTORY_TYPE_SINGLE_THREADED = 0,
    D2D1_FACTORY_TYPE_MULTI_THREADED = 1,
    D2D1_FACTORY_TYPE_FORCE_DWORD = 0xffffffff
    }

D2D1_FACTORY_OPTIONS	STRUC
debugLevel		D2D1_DEBUG_LEVEL ?
D2D1_FACTORY_OPTIONS	ENDS

ifndef D2D_USE_C_DEFINITIONS

DEFINE_IIDX(ID2D1Resource, "2cd90691-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1Resource : public IUnknown

    GetFactory		proc :ptr ptr ID2D1Factory
    .ends

DEFINE_IIDX(ID2D1Bitmap, "a2296057-ea42-4099-983b-539fb6505426")

.comdef ID2D1Bitmap : public ID2D1Resource

    GetSize		proc
    GetPixelSize	proc
    GetPixelFormat	proc
    GetDpi		proc :ptr, :ptr
    CopyFromBitmap	proc :ptr, :ptr, :ptr
    CopyFromRenderTarget proc :ptr, :ptr, :ptr
    CopyFromMemory	proc :ptr, :ptr, :UINT32
    .ends

DEFINE_IIDX(ID2D1GradientStopCollection, "2cd906a7-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1GradientStopCollection : public ID2D1Resource

    GetGradientStopCount proc
    GetGradientStops	proc :ptr, :UINT
    GetColorInterpolationGamma proc
    GetExtendMode	proc
    .ends


DEFINE_IIDX(ID2D1Brush, "2cd906a8-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1Brush  : public ID2D1Resource

    SetOpacity		proc :FLOAT
    SetTransform	proc :ptr
    GetOpacity		proc
    GetTransform	proc :ptr
    .ends


DEFINE_IIDX(ID2D1BitmapBrush, "2cd906aa-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1BitmapBrush : public ID2D1Brush

    SetExtendModeX	proc :D2D1_EXTEND_MODE
    SetExtendModeY	proc :D2D1_EXTEND_MODE
    SetInterpolationMode proc :D2D1_BITMAP_INTERPOLATION_MODE
    SetBitmap		proc :ptr
    GetExtendModeX	proc
    GetExtendModeY	proc
    GetInterpolationMode proc
    GetBitmap		proc :ptr
    .ends


DEFINE_IIDX(ID2D1SolidColorBrush, "2cd906a9-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1SolidColorBrush : public ID2D1Brush

    SetColor		proc :ptr
    GetColor		proc
    .ends



DEFINE_IIDX(ID2D1LinearGradientBrush, "2cd906ab-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1LinearGradientBrush : public ID2D1Brush

    SetStartPoint	proc :D2D1_POINT_2F
    SetEndPoint		proc :D2D1_POINT_2F
    GetStartPoint	proc
    GetEndPoint		proc
    GetGradientStopCollection proc :ptr
    .ends

DEFINE_IIDX(ID2D1RadialGradientBrush, "2cd906ac-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1RadialGradientBrush  : public ID2D1Brush

    SetCenter		proc :D2D1_POINT_2F
    SetGradientOriginOffset proc :D2D1_POINT_2F
    SetRadiusX		proc :FLOAT
    SetRadiusY		proc :FLOAT
    GetCenter		proc
    GetGradientOriginOffset proc
    GetRadiusX		proc
    GetRadiusY		proc
    GetGradientStopCollection proc :ptr
    .ends

DEFINE_IIDX(ID2D1StrokeStyle, "2cd9069d-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1StrokeStyle  : public ID2D1Resource

    GetStartCap		proc
    GetEndCap		proc
    GetDashCap		proc
    GetMiterLimit	proc
    GetLineJoin		proc
    GetDashOffset	proc
    GetDashStyle	proc
    GetDashesCount	proc
    GetDashes		proc :ptr, :UINT
    .ends

DEFINE_IIDX(ID2D1Geometry, "2cd906a1-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1Geometry  : public ID2D1Resource

    GetBounds		proc :ptr, :ptr
    GetWidenedBounds	proc :FLOAT, :ptr, :ptr, :FLOAT, :ptr
    StrokeContainsPoint proc :D2D1_POINT_2F, :FLOAT, :ptr, :ptr, :FLOAT, :ptr
    FillContainsPoint	proc :D2D1_POINT_2F, :ptr, :FLOAT, :ptr
    CompareWithGeometry proc :ptr, :ptr, :FLOAT, :ptr
    Simplify		proc :D2D1_GEOMETRY_SIMPLIFICATION_OPTION, :ptr, :FLOAT, :ptr
    Tessellate		proc :ptr, :FLOAT, :ptr
    CombineWithGeometry proc :ptr, :D2D1_COMBINE_MODE, :ptr, :FLOAT, :ptr
    Outline		proc :ptr, :FLOAT, :ptr
    ComputeArea		proc :ptr, :FLOAT, :ptr
    ComputeLength	proc :ptr, :FLOAT, :ptr
    ComputePointAtLength proc :FLOAT, :ptr, :FLOAT, :ptr, :ptr
    Widen		proc :FLOAT, :ptr, :ptr, :FLOAT, :ptr
    .ends


DEFINE_IIDX(ID2D1RectangleGeometry, "2cd906a2-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1RectangleGeometry	: public ID2D1Geometry

    GetRect		proc :ptr
    .ends

DEFINE_IIDX(ID2D1RoundedRectangleGeometry, "2cd906a3-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1RoundedRectangleGeometry  : public ID2D1Geometry

    GetRoundedRect	proc :ptr
    .ends


DEFINE_IIDX(ID2D1EllipseGeometry, "2cd906a4-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1EllipseGeometry  : public ID2D1Geometry

    GetEllipse		proc :ptr
    .ends


DEFINE_IIDX(ID2D1GeometryGroup, "2cd906a6-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1GeometryGroup  : public ID2D1Geometry

    GetFillMode		proc
    GetSourceGeometryCount proc
    GetSourceGeometries proc
    .ends


DEFINE_IIDX(ID2D1TransformedGeometry, "2cd906bb-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1TransformedGeometry  : public ID2D1Geometry

    GetSourceGeometry	proc :ptr
    GetTransform	proc :ptr
    .ends


DEFINE_IIDX(ID2D1SimplifiedGeometrySink, "2cd9069e-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1SimplifiedGeometrySink  : public IUnknown

    SetFillMode		proc :D2D1_FILL_MODE
    SetSegmentFlags	proc :D2D1_PATH_SEGMENT
    BeginFigure		proc :D2D1_POINT_2F, :D2D1_FIGURE_BEGIN
    AddLines		proc :ptr, :UINT
    AddBeziers		proc :ptr, :UINT
    EndFigure		proc :D2D1_FIGURE_END
    Close		proc
    .ends


DEFINE_IIDX(ID2D1GeometrySink, "2cd9069f-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1GeometrySink  : public ID2D1SimplifiedGeometrySink

    AddLine		proc :D2D1_POINT_2F
    AddBezier		proc :ptr
    AddQuadraticBezier	proc :ptr
    AddQuadraticBeziers proc
    AddArc		proc :ptr
    .ends


DEFINE_IIDX(ID2D1TessellationSink, "2cd906c1-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1TessellationSink  : public IUnknown

    AddTriangles	proc
    Close		proc
    .ends


DEFINE_IIDX(ID2D1PathGeometry, "2cd906a5-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1PathGeometry  : public ID2D1Geometry

    Open		proc :ptr
    Stream		proc :ptr
    GetSegmentCount	proc :ptr
    GetFigureCount	proc :ptr
    .ends


DEFINE_IIDX(ID2D1Mesh, "2cd906c2-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1Mesh  : public ID2D1Resource

    Open		proc :ptr
    .ends


DEFINE_IIDX(ID2D1Layer, "2cd9069b-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1Layer  : public ID2D1Resource

    GetSize		proc
    .ends


DEFINE_IIDX(ID2D1DrawingStateBlock, "28506e39-ebf6-46a1-bb47-fd85565ab957")

.comdef ID2D1DrawingStateBlock	: public ID2D1Resource

    GetDescription	proc :ptr
    SetDescription	proc :ptr
    SetTextRenderingParams proc :ptr
    GetTextRenderingParams proc :ptr
    .ends


DEFINE_IIDX(ID2D1RenderTarget, "2cd90694-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1RenderTarget  : public ID2D1Resource

    CreateBitmap	proc :D2D1_SIZE_U, :ptr, :UINT32, :ptr, :ptr
    CreateBitmapFromWicBitmap proc :ptr, :ptr, :ptr
    CreateSharedBitmap	proc :REFIID, :ptr, :ptr, :ptr
    CreateBitmapBrush	proc :ptr, :ptr, :ptr, :ptr
    CreateSolidColorBrush proc :ptr, :ptr, :ptr
    CreateGradientStopCollection proc :ptr, :UINT, :D2D1_GAMMA, :D2D1_EXTEND_MODE, :ptr
    CreateLinearGradientBrush proc :ptr, :ptr, :ptr, :ptr
    CreateRadialGradientBrush proc :ptr, :ptr, :ptr, :ptr
    CreateCompatibleRenderTarget proc :ptr, :ptr, :ptr, :D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS, :ptr
    CreateLayer		proc :ptr, :ptr
    CreateMesh		proc :ptr
    DrawLine		proc :D2D1_POINT_2F, :D2D1_POINT_2F, :ptr, :FLOAT, :ptr
    DrawRectangle	proc :ptr, :ptr, :FLOAT, :ptr
    FillRectangle	proc :ptr, :ptr
    DrawRoundedRectangle proc :ptr, :ptr, :FLOAT, :ptr
    FillRoundedRectangle proc :ptr, :ptr
    DrawEllipse		proc :ptr, :ptr, :FLOAT, :ptr
    FillEllipse		proc :ptr, :ptr
    DrawGeometry	proc :ptr, :ptr, :FLOAT, :ptr
    FillGeometry	proc :ptr, :ptr, :ptr
    FillMesh		proc :ptr, :ptr
    FillOpacityMask	proc :ptr, :ptr, :D2D1_OPACITY_MASK_CONTENT, :ptr, :ptr
    DrawBitmap		proc :ptr, :ptr, :FLOAT, :D2D1_BITMAP_INTERPOLATION_MODE, :ptr
    DrawText		proc :ptr, :UINT, :ptr, :ptr, :ptr, :D2D1_DRAW_TEXT_OPTIONS, :DWRITE_MEASURING_MODE
    DrawTextLayout	proc :D2D1_POINT_2F, :ptr, :ptr, :D2D1_DRAW_TEXT_OPTIONS
    DrawGlyphRun	proc :D2D1_POINT_2F, :ptr, :ptr, :DWRITE_MEASURING_MODE
    SetTransform	proc :ptr
    GetTransform	proc :ptr
    SetAntialiasMode	proc :D2D1_ANTIALIAS_MODE
    GetAntialiasMode	proc
    SetTextAntialiasMode proc :D2D1_TEXT_ANTIALIAS_MODE
    GetTextAntialiasMode proc
    SetTextRenderingParams proc :ptr
    GetTextRenderingParams proc :ptr
    SetTags		proc :D2D1_TAG, :D2D1_TAG
    GetTags		proc :ptr, :ptr
    PushLayer		proc :ptr, :ptr
    PopLayer		proc
    Flush		proc :ptr, :ptr
    SaveDrawingState	proc :ptr
    RestoreDrawingState proc :ptr
    PushAxisAlignedClip proc :ptr, :D2D1_ANTIALIAS_MODE
    PopAxisAlignedClip	proc
    Clear		proc :ptr
    BeginDraw		proc
    EndDraw		proc :ptr, :ptr
    GetPixelFormat	proc
    SetDpi		proc :FLOAT, :FLOAT
    GetDpi		proc :ptr, :ptr
    GetSize		proc
    GetPixelSize	proc
    GetMaximumBitmapSize proc
    IsSupported		proc :ptr
    .ends


DEFINE_IIDX(ID2D1BitmapRenderTarget, "2cd90695-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1BitmapRenderTarget	 : public ID2D1RenderTarget

    GetBitmap		proc :ptr
    .ends


DEFINE_IIDX(ID2D1HwndRenderTarget, "2cd90698-12e2-11dc-9fed-001143a055f9")

.comdef ID2D1HwndRenderTarget  : public ID2D1RenderTarget

    CheckWindowState	proc
    Resize		proc :ptr
    GetHwnd		proc
    .ends


DEFINE_IIDX(ID2D1GdiInteropRenderTarget, "e0db51c3-6f77-4bae-b3d5-e47509b35838")

.comdef ID2D1GdiInteropRenderTarget  : public IUnknown

    GetDC		proc :D2D1_DC_INITIALIZE_MODE, :ptr
    ReleaseDC		proc :ptr
    .ends


DEFINE_IIDX(ID2D1DCRenderTarget, "1c51bc64-de61-46fd-9899-63a5d8f03950")

.comdef ID2D1DCRenderTarget  : public ID2D1RenderTarget

    BindDC		proc :HDC, :ptr
    .ends


DEFINE_IIDX(ID2D1Factory, "06152247-6f50-465a-9245-118bfd3b6007")

.comdef ID2D1Factory  : public IUnknown

    ReloadSystemMetrics proc
    GetDesktopDpi	proc :ptr, :ptr
    CreateRectangleGeometry proc :ptr, :ptr
    CreateRoundedRectangleGeometry proc :ptr, :ptr
    CreateEllipseGeometry proc :ptr, :ptr
    CreateGeometryGroup proc :D2D1_FILL_MODE, :ptr, :UINT, :ptr
    CreateTransformedGeometry proc :ptr, :ptr, :ptr
    CreatePathGeometry	proc :ptr
    CreateStrokeStyle	proc :ptr, :ptr, :UINT, :ptr
    CreateDrawingStateBlock proc :ptr, :ptr, :ptr
    CreateWicBitmapRenderTarget proc :ptr, :ptr, :ptr
    CreateHwndRenderTarget proc :ptr, :ptr, :ptr
    CreateDxgiSurfaceRenderTarget proc :ptr, :ptr, :ptr
    CreateDCRenderTarget proc :ptr, :ptr
    .ends

endif

D2D1CreateFactory	proto WINAPI :D2D1_FACTORY_TYPE, :REFIID, :ptr D2D1_FACTORY_OPTIONS, :ptr
D2D1MakeRotateMatrix	proto WINAPI :FLOAT, :D2D1_POINT_2F, :ptr D2D1_MATRIX_3X2_F
D2D1MakeSkewMatrix	proto WINAPI :FLOAT, :FLOAT, :D2D1_POINT_2F, :ptr D2D1_MATRIX_3X2_F
D2D1IsMatrixInvertible	proto WINAPI :ptr D2D1_MATRIX_3X2_F
D2D1InvertMatrix	proto WINAPI :ptr D2D1_MATRIX_3X2_F

include d2d1helper.inc

endif
.pragma list(pop)
