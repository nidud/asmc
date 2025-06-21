ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __xpsobjectmodel_h__
define __xpsobjectmodel_h__

include oaidl.inc
include ocidl.inc
include msopc.inc
include winapifamily.inc

if (NTDDI_VERSION GE NTDDI_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum XPS_TILE_MODE {
    XPS_TILE_MODE_NONE	= 1,
    XPS_TILE_MODE_TILE	= ( XPS_TILE_MODE_NONE + 1 ) ,
    XPS_TILE_MODE_FLIPX = ( XPS_TILE_MODE_TILE + 1 ) ,
    XPS_TILE_MODE_FLIPY = ( XPS_TILE_MODE_FLIPX + 1 ) ,
    XPS_TILE_MODE_FLIPXY= ( XPS_TILE_MODE_FLIPY + 1 )
    }

.enum XPS_COLOR_INTERPOLATION {
    XPS_COLOR_INTERPOLATION_SCRGBLINEAR = 1,
    XPS_COLOR_INTERPOLATION_SRGBLINEAR	= ( XPS_COLOR_INTERPOLATION_SCRGBLINEAR + 1 )
    }

.enum XPS_SPREAD_METHOD {
    XPS_SPREAD_METHOD_PAD	= 1,
    XPS_SPREAD_METHOD_REFLECT	= ( XPS_SPREAD_METHOD_PAD + 1 ) ,
    XPS_SPREAD_METHOD_REPEAT	= ( XPS_SPREAD_METHOD_REFLECT + 1 )
    }

.enum XPS_STYLE_SIMULATION {
    XPS_STYLE_SIMULATION_NONE	= 1,
    XPS_STYLE_SIMULATION_ITALIC = ( XPS_STYLE_SIMULATION_NONE + 1 ) ,
    XPS_STYLE_SIMULATION_BOLD	= ( XPS_STYLE_SIMULATION_ITALIC + 1 ) ,
    XPS_STYLE_SIMULATION_BOLDITALIC	= ( XPS_STYLE_SIMULATION_BOLD + 1 )
    }

.enum XPS_LINE_CAP {
    XPS_LINE_CAP_FLAT	= 1,
    XPS_LINE_CAP_ROUND	= ( XPS_LINE_CAP_FLAT + 1 ) ,
    XPS_LINE_CAP_SQUARE = ( XPS_LINE_CAP_ROUND + 1 ) ,
    XPS_LINE_CAP_TRIANGLE	= ( XPS_LINE_CAP_SQUARE + 1 )
    }

.enum XPS_DASH_CAP {
    XPS_DASH_CAP_FLAT	= 1,
    XPS_DASH_CAP_ROUND	= ( XPS_DASH_CAP_FLAT + 1 ) ,
    XPS_DASH_CAP_SQUARE = ( XPS_DASH_CAP_ROUND + 1 ) ,
    XPS_DASH_CAP_TRIANGLE	= ( XPS_DASH_CAP_SQUARE + 1 )
    }

.enum XPS_LINE_JOIN {
    XPS_LINE_JOIN_MITER = 1,
    XPS_LINE_JOIN_BEVEL = ( XPS_LINE_JOIN_MITER + 1 ) ,
    XPS_LINE_JOIN_ROUND = ( XPS_LINE_JOIN_BEVEL + 1 )
    }

.enum XPS_IMAGE_TYPE {
    XPS_IMAGE_TYPE_JPEG = 1,
    XPS_IMAGE_TYPE_PNG	= ( XPS_IMAGE_TYPE_JPEG + 1 ) ,
    XPS_IMAGE_TYPE_TIFF = ( XPS_IMAGE_TYPE_PNG + 1 ) ,
    XPS_IMAGE_TYPE_WDP	= ( XPS_IMAGE_TYPE_TIFF + 1 ) ,
    XPS_IMAGE_TYPE_JXR	= ( XPS_IMAGE_TYPE_WDP + 1 )
    }

.enum XPS_COLOR_TYPE {
    XPS_COLOR_TYPE_SRGB = 1,
    XPS_COLOR_TYPE_SCRGB	= ( XPS_COLOR_TYPE_SRGB + 1 ) ,
    XPS_COLOR_TYPE_CONTEXT	= ( XPS_COLOR_TYPE_SCRGB + 1 )
    }

.enum XPS_FILL_RULE {
    XPS_FILL_RULE_EVENODD	= 1,
    XPS_FILL_RULE_NONZERO	= ( XPS_FILL_RULE_EVENODD + 1 )
    }

.enum XPS_SEGMENT_TYPE {
    XPS_SEGMENT_TYPE_ARC_LARGE_CLOCKWISE	= 1,
    XPS_SEGMENT_TYPE_ARC_LARGE_COUNTERCLOCKWISE = ( XPS_SEGMENT_TYPE_ARC_LARGE_CLOCKWISE + 1 ) ,
    XPS_SEGMENT_TYPE_ARC_SMALL_CLOCKWISE	= ( XPS_SEGMENT_TYPE_ARC_LARGE_COUNTERCLOCKWISE + 1 ) ,
    XPS_SEGMENT_TYPE_ARC_SMALL_COUNTERCLOCKWISE = ( XPS_SEGMENT_TYPE_ARC_SMALL_CLOCKWISE + 1 ) ,
    XPS_SEGMENT_TYPE_BEZIER	= ( XPS_SEGMENT_TYPE_ARC_SMALL_COUNTERCLOCKWISE + 1 ) ,
    XPS_SEGMENT_TYPE_LINE	= ( XPS_SEGMENT_TYPE_BEZIER + 1 ) ,
    XPS_SEGMENT_TYPE_QUADRATIC_BEZIER	= ( XPS_SEGMENT_TYPE_LINE + 1 )
    }

.enum XPS_SEGMENT_STROKE_PATTERN {
    XPS_SEGMENT_STROKE_PATTERN_ALL	= 1,
    XPS_SEGMENT_STROKE_PATTERN_NONE	= ( XPS_SEGMENT_STROKE_PATTERN_ALL + 1 ) ,
    XPS_SEGMENT_STROKE_PATTERN_MIXED	= ( XPS_SEGMENT_STROKE_PATTERN_NONE + 1 )
    }

.enum XPS_FONT_EMBEDDING {
    XPS_FONT_EMBEDDING_NORMAL	= 1,
    XPS_FONT_EMBEDDING_OBFUSCATED	= ( XPS_FONT_EMBEDDING_NORMAL + 1 ) ,
    XPS_FONT_EMBEDDING_RESTRICTED	= ( XPS_FONT_EMBEDDING_OBFUSCATED + 1 ) ,
    XPS_FONT_EMBEDDING_RESTRICTED_UNOBFUSCATED	= ( XPS_FONT_EMBEDDING_RESTRICTED + 1 )
    }

.enum XPS_OBJECT_TYPE {
    XPS_OBJECT_TYPE_CANVAS	= 1,
    XPS_OBJECT_TYPE_GLYPHS	= ( XPS_OBJECT_TYPE_CANVAS + 1 ) ,
    XPS_OBJECT_TYPE_PATH	= ( XPS_OBJECT_TYPE_GLYPHS + 1 ) ,
    XPS_OBJECT_TYPE_MATRIX_TRANSFORM	= ( XPS_OBJECT_TYPE_PATH + 1 ) ,
    XPS_OBJECT_TYPE_GEOMETRY	= ( XPS_OBJECT_TYPE_MATRIX_TRANSFORM + 1 ) ,
    XPS_OBJECT_TYPE_SOLID_COLOR_BRUSH	= ( XPS_OBJECT_TYPE_GEOMETRY + 1 ) ,
    XPS_OBJECT_TYPE_IMAGE_BRUSH = ( XPS_OBJECT_TYPE_SOLID_COLOR_BRUSH + 1 ) ,
    XPS_OBJECT_TYPE_LINEAR_GRADIENT_BRUSH	= ( XPS_OBJECT_TYPE_IMAGE_BRUSH + 1 ) ,
    XPS_OBJECT_TYPE_RADIAL_GRADIENT_BRUSH	= ( XPS_OBJECT_TYPE_LINEAR_GRADIENT_BRUSH + 1 ) ,
    XPS_OBJECT_TYPE_VISUAL_BRUSH	= ( XPS_OBJECT_TYPE_RADIAL_GRADIENT_BRUSH + 1 )
    }

.enum XPS_THUMBNAIL_SIZE {
    XPS_THUMBNAIL_SIZE_VERYSMALL	= 1,
    XPS_THUMBNAIL_SIZE_SMALL	= ( XPS_THUMBNAIL_SIZE_VERYSMALL + 1 ) ,
    XPS_THUMBNAIL_SIZE_MEDIUM	= ( XPS_THUMBNAIL_SIZE_SMALL + 1 ) ,
    XPS_THUMBNAIL_SIZE_LARGE	= ( XPS_THUMBNAIL_SIZE_MEDIUM + 1 )
    }

.enum XPS_INTERLEAVING {
    XPS_INTERLEAVING_OFF	= 1,
    XPS_INTERLEAVING_ON = ( XPS_INTERLEAVING_OFF + 1 )
    }

XPS_POINT		STRUC
x			FLOAT ?
y			FLOAT ?
XPS_POINT		ENDS

XPS_SIZE		STRUC
width			FLOAT ?
height			FLOAT ?
XPS_SIZE		ENDS

XPS_RECT		STRUC
x			FLOAT ?
y			FLOAT ?
width			FLOAT ?
height			FLOAT ?
XPS_RECT		ENDS

XPS_DASH		STRUC
length			FLOAT ?
gap			FLOAT ?
XPS_DASH		ENDS

XPS_GLYPH_INDEX		STRUC
index			LONG ?
advanceWidth		FLOAT ?
horizontalOffset	FLOAT ?
verticalOffset		FLOAT ?
XPS_GLYPH_INDEX		ENDS

XPS_GLYPH_MAPPING	STRUC
unicodeStringStart	UINT32 ?
unicodeStringLength	UINT16 ?
glyphIndicesStart	UINT32 ?
glyphIndicesLength	UINT16 ?
XPS_GLYPH_MAPPING	ENDS

XPS_MATRIX		STRUC
m11			FLOAT ?
m12			FLOAT ?
m21			FLOAT ?
m22			FLOAT ?
m31			FLOAT ?
m32			FLOAT ?
XPS_MATRIX		ENDS

XPS_COLOR		STRUC
colorType		XPS_COLOR_TYPE ?
UNION value
 STRUC sRGB
  alpha			UINT8 ?
  red			UINT8 ?
  green			UINT8 ?
  blue			UINT8 ?
 ENDS
 STRUC scRGB
  alpha			FLOAT ?
  red			FLOAT ?
  green			FLOAT ?
  blue			FLOAT ?
 ENDS
 STRUC context
  channelCount		UINT8 ?
  channels		FLOAT 9 dup(?)
 ENDS
ENDS
XPS_COLOR		ENDS


ifndef __IXpsOMShareable_INTERFACE_DEFINED__
define __IXpsOMShareable_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMShareable, "7137398F-2FC1-454D-8C6A-2C3115A16ECE")

.comdef IXpsOMShareable : public IUnknown

    GetOwner		proc :ptr
    GetType		proc :ptr
   .ends

endif


ifndef __IXpsOMVisual_INTERFACE_DEFINED__
define __IXpsOMVisual_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMVisual, "BC3E7333-FB0B-4af3-A819-0B4EAAD0D2FD")

.comdef IXpsOMVisual : public IXpsOMShareable

    GetTransform	proc :ptr
    GetTransformLocal	proc :ptr
    SetTransformLocal	proc :ptr
    GetTransformLookup	proc :ptr
    SetTransformLookup	proc :LPCWSTR
    GetClipGeometry	proc :ptr
    GetClipGeometryLocal proc :ptr
    SetClipGeometryLocal proc :ptr
    GetClipGeometryLookup proc :ptr
    SetClipGeometryLookup proc :LPCWSTR
    GetOpacity		proc :ptr
    SetOpacity		proc :FLOAT
    GetOpacityMaskBrush proc :ptr
    GetOpacityMaskBrushLocal proc :ptr
    SetOpacityMaskBrushLocal proc :ptr
    GetOpacityMaskBrushLookup proc :ptr
    SetOpacityMaskBrushLookup proc :LPCWSTR
    GetName		proc :ptr
    SetName		proc :LPCWSTR
    GetIsHyperlinkTarget proc :ptr
    SetIsHyperlinkTarget proc :BOOL
    GetHyperlinkNavigateUri proc :ptr
    SetHyperlinkNavigateUri proc :ptr
    GetLanguage		proc :ptr
    SetLanguage		proc :LPCWSTR
   .ends

endif


ifndef __IXpsOMPart_INTERFACE_DEFINED__
define __IXpsOMPart_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPart, "74eb2f0b-a91e-4486-afac-0fabeca3dfc6")

.comdef IXpsOMPart : public IUnknown

    GetPartName		proc :ptr
    SetPartName		proc :ptr
   .ends

endif


ifndef __IXpsOMGlyphsEditor_INTERFACE_DEFINED__
define __IXpsOMGlyphsEditor_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMGlyphsEditor, "A5AB8616-5B16-4B9F-9629-89B323ED7909")

.comdef IXpsOMGlyphsEditor : public IUnknown

    ApplyEdits		proc
    GetUnicodeString	proc :ptr
    SetUnicodeString	proc :LPCWSTR
    GetGlyphIndexCount	proc :ptr
    GetGlyphIndices	proc :ptr, :ptr
    SetGlyphIndices	proc :UINT32, :ptr
    GetGlyphMappingCount proc :ptr
    GetGlyphMappings	proc :ptr, :ptr
    SetGlyphMappings	proc :UINT32, :ptr
    GetProhibitedCaretStopCount proc :ptr
    GetProhibitedCaretStops proc :ptr, :ptr
    SetProhibitedCaretStops proc :UINT32, :ptr
    GetBidiLevel	proc :ptr
    SetBidiLevel	proc :UINT32
    GetIsSideways	proc :ptr
    SetIsSideways	proc :BOOL
    GetDeviceFontName	proc :ptr
    SetDeviceFontName	proc :LPCWSTR
   .ends

endif


ifndef __IXpsOMGlyphs_INTERFACE_DEFINED__
define __IXpsOMGlyphs_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMGlyphs, "819B3199-0A5A-4B64-BEC7-A9E17E780DE2")

.comdef IXpsOMGlyphs : public IXpsOMVisual

    GetUnicodeString	proc :ptr
    GetGlyphIndexCount	proc :ptr
    GetGlyphIndices	proc :ptr, :ptr
    GetGlyphMappingCount proc :ptr
    GetGlyphMappings	proc :ptr, :ptr
    GetProhibitedCaretStopCount proc :ptr
    GetProhibitedCaretStops proc :ptr, :ptr
    GetBidiLevel	proc :ptr
    GetIsSideways	proc :ptr
    GetDeviceFontName	proc :ptr
    GetStyleSimulations proc :ptr
    SetStyleSimulations proc :XPS_STYLE_SIMULATION
    GetOrigin		proc :ptr
    SetOrigin		proc :ptr
    GetFontRenderingEmSize proc :ptr
    SetFontRenderingEmSize proc :FLOAT
    GetFontResource	proc :ptr
    SetFontResource	proc :ptr
    GetFontFaceIndex	proc :ptr
    SetFontFaceIndex	proc :SWORD
    GetFillBrush	proc :ptr
    GetFillBrushLocal	proc :ptr
    SetFillBrushLocal	proc :ptr
    GetFillBrushLookup	proc :ptr
    SetFillBrushLookup	proc :LPCWSTR
    GetGlyphsEditor	proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMDashCollection_INTERFACE_DEFINED__
define __IXpsOMDashCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMDashCollection, "081613F4-74EB-48F2-83B3-37A9CE2D7DC6")

.comdef IXpsOMDashCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
   .ends

endif


ifndef __IXpsOMMatrixTransform_INTERFACE_DEFINED__
define __IXpsOMMatrixTransform_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMMatrixTransform, "B77330FF-BB37-4501-A93E-F1B1E50BFC46")

.comdef IXpsOMMatrixTransform : public IXpsOMShareable

    GetMatrix		proc :ptr
    SetMatrix		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMGeometry_INTERFACE_DEFINED__
define __IXpsOMGeometry_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMGeometry, "64FCF3D7-4D58-44BA-AD73-A13AF6492072")

.comdef IXpsOMGeometry : public IXpsOMShareable

    GetFigures		proc :ptr
    GetFillRule		proc :ptr
    SetFillRule		proc :XPS_FILL_RULE
    GetTransform	proc :ptr
    GetTransformLocal	proc :ptr
    SetTransformLocal	proc :ptr
    GetTransformLookup	proc :ptr
    SetTransformLookup	proc :LPCWSTR
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMGeometryFigure_INTERFACE_DEFINED__
define __IXpsOMGeometryFigure_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMGeometryFigure, "D410DC83-908C-443E-8947-B1795D3C165A")

.comdef IXpsOMGeometryFigure : public IUnknown

    GetOwner		proc :ptr
    GetSegmentData	proc :ptr, :ptr
    GetSegmentTypes	proc :ptr, :ptr
    GetSegmentStrokes	proc :ptr, :ptr
    SetSegments		proc :UINT32, :UINT32, :ptr, :ptr, :ptr
    GetStartPoint	proc :ptr
    SetStartPoint	proc :ptr
    GetIsClosed		proc :ptr
    SetIsClosed		proc :BOOL
    GetIsFilled		proc :ptr
    SetIsFilled		proc :BOOL
    GetSegmentCount	proc :ptr
    GetSegmentDataCount proc :ptr
    GetSegmentStrokePattern proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMGeometryFigureCollection_INTERFACE_DEFINED__
define __IXpsOMGeometryFigureCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMGeometryFigureCollection, "FD48C3F3-A58E-4B5A-8826-1DE54ABE72B2")

.comdef IXpsOMGeometryFigureCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
   .ends

endif


ifndef __IXpsOMPath_INTERFACE_DEFINED__
define __IXpsOMPath_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPath, "37D38BB6-3EE9-4110-9312-14B194163337")

.comdef IXpsOMPath : public IXpsOMVisual

    GetGeometry		proc :ptr
    GetGeometryLocal	proc :ptr
    SetGeometryLocal	proc :ptr
    GetGeometryLookup	proc :ptr
    SetGeometryLookup	proc :LPCWSTR
    GetAccessibilityShortDescription proc :ptr
    SetAccessibilityShortDescription proc :LPCWSTR
    GetAccessibilityLongDescription proc :ptr
    SetAccessibilityLongDescription proc :LPCWSTR
    GetSnapsToPixels	proc :ptr
    SetSnapsToPixels	proc :BOOL
    GetStrokeBrush	proc :ptr
    GetStrokeBrushLocal proc :ptr
    SetStrokeBrushLocal proc :ptr
    GetStrokeBrushLookup proc :ptr
    SetStrokeBrushLookup proc :LPCWSTR
    GetStrokeDashes	proc :ptr
    GetStrokeDashCap	proc :ptr
    SetStrokeDashCap	proc :XPS_DASH_CAP
    GetStrokeDashOffset proc :ptr
    SetStrokeDashOffset proc :FLOAT
    GetStrokeStartLineCap proc :ptr
    SetStrokeStartLineCap proc :XPS_LINE_CAP
    GetStrokeEndLineCap proc :ptr
    SetStrokeEndLineCap proc :XPS_LINE_CAP
    GetStrokeLineJoin	proc :ptr
    SetStrokeLineJoin	proc :XPS_LINE_JOIN
    GetStrokeMiterLimit proc :ptr
    SetStrokeMiterLimit proc :FLOAT
    GetStrokeThickness	proc :ptr
    SetStrokeThickness	proc :FLOAT
    GetFillBrush	proc :ptr
    GetFillBrushLocal	proc :ptr
    SetFillBrushLocal	proc :ptr
    GetFillBrushLookup	proc :ptr
    SetFillBrushLookup	proc :LPCWSTR
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMBrush_INTERFACE_DEFINED__
define __IXpsOMBrush_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMBrush, "56A3F80C-EA4C-4187-A57B-A2A473B2B42B")

.comdef IXpsOMBrush : public IXpsOMShareable

    GetOpacity		proc :ptr
    SetOpacity		proc :FLOAT
   .ends

endif


ifndef __IXpsOMGradientStopCollection_INTERFACE_DEFINED__
define __IXpsOMGradientStopCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMGradientStopCollection, "C9174C3A-3CD3-4319-BDA4-11A39392CEEF")

.comdef IXpsOMGradientStopCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
   .ends

endif


ifndef __IXpsOMSolidColorBrush_INTERFACE_DEFINED__
define __IXpsOMSolidColorBrush_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMSolidColorBrush, "A06F9F05-3BE9-4763-98A8-094FC672E488")

.comdef IXpsOMSolidColorBrush : public IXpsOMBrush

    GetColor		proc :ptr, :ptr
    SetColor		proc :ptr, :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMTileBrush_INTERFACE_DEFINED__
define __IXpsOMTileBrush_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMTileBrush, "0FC2328D-D722-4A54-B2EC-BE90218A789E")

.comdef IXpsOMTileBrush : public IXpsOMBrush

    GetTransform	proc :ptr
    GetTransformLocal	proc :ptr
    SetTransformLocal	proc :ptr
    GetTransformLookup	proc :ptr
    SetTransformLookup	proc :LPCWSTR
    GetViewbox		proc :ptr
    SetViewbox		proc :ptr
    GetViewport		proc :ptr
    SetViewport		proc :ptr
    GetTileMode		proc :ptr
    SetTileMode		proc :XPS_TILE_MODE
   .ends

endif


ifndef __IXpsOMVisualBrush_INTERFACE_DEFINED__
define __IXpsOMVisualBrush_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMVisualBrush, "97E294AF-5B37-46B4-8057-874D2F64119B")

.comdef IXpsOMVisualBrush : public IXpsOMTileBrush

    GetVisual		proc :ptr
    GetVisualLocal	proc :ptr
    SetVisualLocal	proc :ptr
    GetVisualLookup	proc :ptr
    SetVisualLookup	proc :LPCWSTR
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMImageBrush_INTERFACE_DEFINED__
define __IXpsOMImageBrush_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMImageBrush, "3DF0B466-D382-49EF-8550-DD94C80242E4")

.comdef IXpsOMImageBrush : public IXpsOMTileBrush

    GetImageResource	proc :ptr
    SetImageResource	proc :ptr
    GetColorProfileResource proc :ptr
    SetColorProfileResource proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMGradientStop_INTERFACE_DEFINED__
define __IXpsOMGradientStop_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMGradientStop, "5CF4F5CC-3969-49B5-A70A-5550B618FE49")

.comdef IXpsOMGradientStop : public IUnknown

    GetOwner		proc :ptr
    GetOffset		proc :ptr
    SetOffset		proc :FLOAT
    GetColor		proc :ptr, :ptr
    SetColor		proc :ptr, :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMGradientBrush_INTERFACE_DEFINED__
define __IXpsOMGradientBrush_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMGradientBrush, "EDB59622-61A2-42C3-BACE-ACF2286C06BF")

.comdef IXpsOMGradientBrush : public IXpsOMBrush

    GetGradientStops	proc :ptr
    GetTransform	proc :ptr
    GetTransformLocal	proc :ptr
    SetTransformLocal	proc :ptr
    GetTransformLookup	proc :ptr
    SetTransformLookup	proc :LPCWSTR
    GetSpreadMethod	proc :ptr
    SetSpreadMethod	proc :XPS_SPREAD_METHOD
    GetColorInterpolationMode proc :ptr
    SetColorInterpolationMode proc :XPS_COLOR_INTERPOLATION
   .ends

endif


ifndef __IXpsOMLinearGradientBrush_INTERFACE_DEFINED__
define __IXpsOMLinearGradientBrush_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMLinearGradientBrush, "005E279F-C30D-40FF-93EC-1950D3C528DB")

.comdef IXpsOMLinearGradientBrush : public IXpsOMGradientBrush

    GetStartPoint	proc :ptr
    SetStartPoint	proc :ptr
    GetEndPoint		proc :ptr
    SetEndPoint		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMRadialGradientBrush_INTERFACE_DEFINED__
define __IXpsOMRadialGradientBrush_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMRadialGradientBrush, "75F207E5-08BF-413C-96B1-B82B4064176B")

.comdef IXpsOMRadialGradientBrush : public IXpsOMGradientBrush

    GetCenter		proc :ptr
    SetCenter		proc :ptr
    GetRadiiSizes	proc :ptr
    SetRadiiSizes	proc :ptr
    GetGradientOrigin	proc :ptr
    SetGradientOrigin	proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMResource_INTERFACE_DEFINED__
define __IXpsOMResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMResource, "da2ac0a2-73a2-4975-ad14-74097c3ff3a5")

.comdef IXpsOMResource : public IXpsOMPart

   .ends

endif


ifndef __IXpsOMPartResources_INTERFACE_DEFINED__
define __IXpsOMPartResources_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPartResources, "f4cf7729-4864-4275-99b3-a8717163ecaf")

.comdef IXpsOMPartResources : public IUnknown

    GetFontResources	proc :ptr
    GetImageResources	proc :ptr
    GetColorProfileResources proc :ptr
    GetRemoteDictionaryResources proc :ptr
   .ends

endif


ifndef __IXpsOMDictionary_INTERFACE_DEFINED__
define __IXpsOMDictionary_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMDictionary, "897C86B8-8EAF-4AE3-BDDE-56419FCF4236")

.comdef IXpsOMDictionary : public IUnknown

    GetOwner		proc :ptr
    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr, :ptr
    GetByKey		proc :LPCWSTR, :ptr, :ptr
    GetIndex		proc :ptr, :ptr
    Append		proc :LPCWSTR, :ptr
    InsertAt		proc :UINT32, :LPCWSTR, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :LPCWSTR, :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMFontResource_INTERFACE_DEFINED__
define __IXpsOMFontResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMFontResource, "a8c45708-47d9-4af4-8d20-33b48c9b8485")

.comdef IXpsOMFontResource : public IXpsOMResource

    GetStream		proc :ptr
    SetContent		proc :ptr, :XPS_FONT_EMBEDDING, :ptr
    GetEmbeddingOption	proc :ptr
   .ends

endif


ifndef __IXpsOMFontResourceCollection_INTERFACE_DEFINED__
define __IXpsOMFontResourceCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMFontResourceCollection, "70B4A6BB-88D4-4FA8-AAF9-6D9C596FDBAD")

.comdef IXpsOMFontResourceCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    SetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    Append		proc :ptr
    RemoveAt		proc :UINT32
    GetByPartName	proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMImageResource_INTERFACE_DEFINED__
define __IXpsOMImageResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMImageResource, "3db8417d-ae50-485e-9a44-d7758f78a23f")

.comdef IXpsOMImageResource : public IXpsOMResource

    GetStream		proc :ptr
    SetContent		proc :ptr, :XPS_IMAGE_TYPE, :ptr
    GetImageType	proc :ptr
   .ends

endif


ifndef __IXpsOMImageResourceCollection_INTERFACE_DEFINED__
define __IXpsOMImageResourceCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMImageResourceCollection, "7A4A1A71-9CDE-4B71-B33F-62DE843EABFE")

.comdef IXpsOMImageResourceCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
    GetByPartName	proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMColorProfileResource_INTERFACE_DEFINED__
define __IXpsOMColorProfileResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMColorProfileResource, "67bd7d69-1eef-4bb1-b5e7-6f4f87be8abe")

.comdef IXpsOMColorProfileResource : public IXpsOMResource

    GetStream		proc :ptr
    SetContent		proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMColorProfileResourceCollection_INTERFACE_DEFINED__
define __IXpsOMColorProfileResourceCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMColorProfileResourceCollection, "12759630-5FBA-4283-8F7D-CCA849809EDB")

.comdef IXpsOMColorProfileResourceCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
    GetByPartName	proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMPrintTicketResource_INTERFACE_DEFINED__
define __IXpsOMPrintTicketResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPrintTicketResource, "e7ff32d2-34aa-499b-bbe9-9cd4ee6c59f7")

.comdef IXpsOMPrintTicketResource : public IXpsOMResource

    GetStream		proc :ptr
    SetContent		proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMRemoteDictionaryResource_INTERFACE_DEFINED__
define __IXpsOMRemoteDictionaryResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMRemoteDictionaryResource, "c9bd7cd4-e16a-4bf8-8c84-c950af7a3061")

.comdef IXpsOMRemoteDictionaryResource : public IXpsOMResource

    GetDictionary	proc :ptr
    SetDictionary	proc :ptr
   .ends

endif


ifndef __IXpsOMRemoteDictionaryResourceCollection_INTERFACE_DEFINED__
define __IXpsOMRemoteDictionaryResourceCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMRemoteDictionaryResourceCollection, "5C38DB61-7FEC-464A-87BD-41E3BEF018BE")

.comdef IXpsOMRemoteDictionaryResourceCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
    GetByPartName	proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMSignatureBlockResourceCollection_INTERFACE_DEFINED__
define __IXpsOMSignatureBlockResourceCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMSignatureBlockResourceCollection, "AB8F5D8E-351B-4D33-AAED-FA56F0022931")

.comdef IXpsOMSignatureBlockResourceCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
    GetByPartName	proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMDocumentStructureResource_INTERFACE_DEFINED__
define __IXpsOMDocumentStructureResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMDocumentStructureResource, "85febc8a-6b63-48a9-af07-7064e4ecff30")

.comdef IXpsOMDocumentStructureResource : public IXpsOMResource

    GetOwner		proc :ptr
    GetStream		proc :ptr
    SetContent		proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMStoryFragmentsResource_INTERFACE_DEFINED__
define __IXpsOMStoryFragmentsResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMStoryFragmentsResource, "c2b3ca09-0473-4282-87ae-1780863223f0")

.comdef IXpsOMStoryFragmentsResource : public IXpsOMResource

    GetOwner		proc :ptr
    GetStream		proc :ptr
    SetContent		proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMSignatureBlockResource_INTERFACE_DEFINED__
define __IXpsOMSignatureBlockResource_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMSignatureBlockResource, "4776ad35-2e04-4357-8743-ebf6c171a905")

.comdef IXpsOMSignatureBlockResource : public IXpsOMResource

    GetOwner		proc :ptr
    GetStream		proc :ptr
    SetContent		proc :ptr, :ptr
   .ends

endif


ifndef __IXpsOMVisualCollection_INTERFACE_DEFINED__
define __IXpsOMVisualCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMVisualCollection, "94D8ABDE-AB91-46A8-82B7-F5B05EF01A96")

.comdef IXpsOMVisualCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
   .ends

endif


ifndef __IXpsOMCanvas_INTERFACE_DEFINED__
define __IXpsOMCanvas_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMCanvas, "221D1452-331E-47c6-87E9-6CCEFB9B5BA3")

.comdef IXpsOMCanvas : public IXpsOMVisual

    GetVisuals		proc :ptr
    GetUseAliasedEdgeMode proc :ptr
    SetUseAliasedEdgeMode proc :BOOL
    GetAccessibilityShortDescription proc :ptr
    SetAccessibilityShortDescription proc :LPCWSTR
    GetAccessibilityLongDescription proc :ptr
    SetAccessibilityLongDescription proc :LPCWSTR
    GetDictionary	proc :ptr
    GetDictionaryLocal	proc :ptr
    SetDictionaryLocal	proc :ptr
    GetDictionaryResource proc :ptr
    SetDictionaryResource proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMPage_INTERFACE_DEFINED__
define __IXpsOMPage_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPage, "d3e18888-f120-4fee-8c68-35296eae91d4")

.comdef IXpsOMPage : public IXpsOMPart

    GetOwner		proc :ptr
    GetVisuals		proc :ptr
    GetPageDimensions	proc :ptr
    SetPageDimensions	proc :ptr
    GetContentBox	proc :ptr
    SetContentBox	proc :ptr
    GetBleedBox		proc :ptr
    SetBleedBox		proc :ptr
    GetLanguage		proc :ptr
    SetLanguage		proc :LPCWSTR
    GetName		proc :ptr
    SetName		proc :LPCWSTR
    GetIsHyperlinkTarget proc :ptr
    SetIsHyperlinkTarget proc :BOOL
    GetDictionary	proc :ptr
    GetDictionaryLocal	proc :ptr
    SetDictionaryLocal	proc :ptr
    GetDictionaryResource proc :ptr
    SetDictionaryResource proc :ptr
    Write		proc :ptr, :BOOL
    GenerateUnusedLookupKey proc :XPS_OBJECT_TYPE, :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMPageReference_INTERFACE_DEFINED__
define __IXpsOMPageReference_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPageReference, "ED360180-6F92-4998-890D-2F208531A0A0")

.comdef IXpsOMPageReference : public IUnknown

    GetOwner		proc :ptr
    GetPage		proc :ptr
    SetPage		proc :ptr
    DiscardPage		proc
    IsPageLoaded	proc :ptr
    GetAdvisoryPageDimensions proc :ptr
    SetAdvisoryPageDimensions proc :ptr
    GetStoryFragmentsResource proc :ptr
    SetStoryFragmentsResource proc :ptr
    GetPrintTicketResource proc :ptr
    SetPrintTicketResource proc :ptr
    GetThumbnailResource proc :ptr
    SetThumbnailResource proc :ptr
    CollectLinkTargets	proc :ptr
    CollectPartResources proc :ptr
    HasRestrictedFonts	proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMPageReferenceCollection_INTERFACE_DEFINED__
define __IXpsOMPageReferenceCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPageReferenceCollection, "CA16BA4D-E7B9-45C5-958B-F98022473745")

.comdef IXpsOMPageReferenceCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
   .ends

endif


ifndef __IXpsOMDocument_INTERFACE_DEFINED__
define __IXpsOMDocument_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMDocument, "2C2C94CB-AC5F-4254-8EE9-23948309D9F0")

.comdef IXpsOMDocument : public IXpsOMPart

    GetOwner		proc :ptr
    GetPageReferences	proc :ptr
    GetPrintTicketResource proc :ptr
    SetPrintTicketResource proc :ptr
    GetDocumentStructureResource proc :ptr
    SetDocumentStructureResource proc :ptr
    GetSignatureBlockResources proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMDocumentCollection_INTERFACE_DEFINED__
define __IXpsOMDocumentCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMDocumentCollection, "D1C87F0D-E947-4754-8A25-971478F7E83E")

.comdef IXpsOMDocumentCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
   .ends

endif


ifndef __IXpsOMDocumentSequence_INTERFACE_DEFINED__
define __IXpsOMDocumentSequence_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMDocumentSequence, "56492EB4-D8D5-425e-8256-4C2B64AD0264")

.comdef IXpsOMDocumentSequence : public IXpsOMPart

    GetOwner		proc :ptr
    GetDocuments	proc :ptr
    GetPrintTicketResource proc :ptr
    SetPrintTicketResource proc :ptr
   .ends

endif


ifndef __IXpsOMCoreProperties_INTERFACE_DEFINED__
define __IXpsOMCoreProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMCoreProperties, "3340FE8F-4027-4aa1-8F5F-D35AE45FE597")

.comdef IXpsOMCoreProperties : public IXpsOMPart

    GetOwner		proc :ptr
    GetCategory		proc :ptr
    SetCategory		proc :LPCWSTR
    GetContentStatus	proc :ptr
    SetContentStatus	proc :LPCWSTR
    GetContentType	proc :ptr
    SetContentType	proc :LPCWSTR
    GetCreated		proc :ptr
    SetCreated		proc :ptr
    GetCreator		proc :ptr
    SetCreator		proc :LPCWSTR
    GetDescription	proc :ptr
    SetDescription	proc :LPCWSTR
    GetIdentifier	proc :ptr
    SetIdentifier	proc :LPCWSTR
    GetKeywords		proc :ptr
    SetKeywords		proc :LPCWSTR
    GetLanguage		proc :ptr
    SetLanguage		proc :LPCWSTR
    GetLastModifiedBy	proc :ptr
    SetLastModifiedBy	proc :LPCWSTR
    GetLastPrinted	proc :ptr
    SetLastPrinted	proc :ptr
    GetModified		proc :ptr
    SetModified		proc :ptr
    GetRevision		proc :ptr
    SetRevision		proc :LPCWSTR
    GetSubject		proc :ptr
    SetSubject		proc :LPCWSTR
    GetTitle		proc :ptr
    SetTitle		proc :LPCWSTR
    GetVersion		proc :ptr
    SetVersion		proc :LPCWSTR
    Clone		proc :ptr
   .ends

endif


ifndef __IXpsOMPackage_INTERFACE_DEFINED__
define __IXpsOMPackage_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPackage, "18C3DF65-81E1-4674-91DC-FC452F5A416F")

.comdef IXpsOMPackage : public IUnknown

    GetDocumentSequence proc :ptr
    SetDocumentSequence proc :ptr
    GetCoreProperties	proc :ptr
    SetCoreProperties	proc :ptr
    GetDiscardControlPartName proc :ptr
    SetDiscardControlPartName proc :ptr
    GetThumbnailResource proc :ptr
    SetThumbnailResource proc :ptr
    WriteToFile		proc :LPCWSTR, :LPSECURITY_ATTRIBUTES, :DWORD, :BOOL
    WriteToStream	proc :ptr, :BOOL
   .ends

endif


ifndef __IXpsOMObjectFactory_INTERFACE_DEFINED__
define __IXpsOMObjectFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMObjectFactory, "f9b2a685-a50d-4fc2-b764-b56e093ea0ca")

.comdef IXpsOMObjectFactory : public IUnknown

    CreatePackage	proc :ptr
    CreatePackageFromFile proc :LPCWSTR, :BOOL, :ptr
    CreatePackageFromStream proc :ptr, :BOOL, :ptr
    CreateStoryFragmentsResource proc :ptr, :ptr, :ptr
    CreateDocumentStructureResource proc :ptr, :ptr, :ptr
    CreateSignatureBlockResource proc :ptr, :ptr, :ptr
    CreateRemoteDictionaryResource proc :ptr, :ptr, :ptr
    CreateRemoteDictionaryResourceFromStream proc :ptr, :ptr, :ptr, :ptr
    CreatePartResources proc :ptr
    CreateDocumentSequence proc :ptr, :ptr
    CreateDocument	proc :ptr, :ptr
    CreatePageReference proc :ptr, :ptr
    CreatePage		proc :ptr, :LPCWSTR, :ptr, :ptr
    CreatePageFromStream proc :ptr, :ptr, :ptr, :BOOL, :ptr
    CreateCanvas	proc :ptr
    CreateGlyphs	proc :ptr, :ptr
    CreatePath		proc :ptr
    CreateGeometry	proc :ptr
    CreateGeometryFigure proc :ptr, :ptr
    CreateMatrixTransform proc :ptr, :ptr
    CreateSolidColorBrush proc :ptr, :ptr, :ptr
    CreateColorProfileResource proc :ptr, :ptr, :ptr
    CreateImageBrush	proc :ptr, :ptr, :ptr, :ptr
    CreateVisualBrush	proc :ptr, :ptr, :ptr
    CreateImageResource proc :ptr, :XPS_IMAGE_TYPE, :ptr, :ptr
    CreatePrintTicketResource proc :ptr, :ptr, :ptr
    CreateFontResource	proc :ptr, :XPS_FONT_EMBEDDING, :ptr, :BOOL, :ptr
    CreateGradientStop	proc :ptr, :ptr, :FLOAT, :ptr
    CreateLinearGradientBrush proc :ptr, :ptr, :ptr, :ptr, :ptr
    CreateRadialGradientBrush proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    CreateCoreProperties proc :ptr, :ptr
    CreateDictionary	proc :ptr
    CreatePartUriCollection proc :ptr
    CreatePackageWriterOnFile proc :LPCWSTR, :LPSECURITY_ATTRIBUTES, :DWORD, :BOOL, :XPS_INTERLEAVING, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    CreatePackageWriterOnStream proc :ptr, :BOOL, :XPS_INTERLEAVING, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    CreatePartUri	proc :LPCWSTR, :ptr
    CreateReadOnlyStreamOnFile proc :LPCWSTR, :ptr
   .ends

endif


ifndef __IXpsOMNameCollection_INTERFACE_DEFINED__
define __IXpsOMNameCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMNameCollection, "4BDDF8EC-C915-421B-A166-D173D25653D2")

.comdef IXpsOMNameCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
   .ends

endif


ifndef __IXpsOMPartUriCollection_INTERFACE_DEFINED__
define __IXpsOMPartUriCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPartUriCollection, "57C650D4-067C-4893-8C33-F62A0633730F")

.comdef IXpsOMPartUriCollection : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT32, :ptr
    InsertAt		proc :UINT32, :ptr
    RemoveAt		proc :UINT32
    SetAt		proc :UINT32, :ptr
    Append		proc :ptr
   .ends

endif


ifndef __IXpsOMPackageWriter_INTERFACE_DEFINED__
define __IXpsOMPackageWriter_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPackageWriter, "4E2AA182-A443-42c6-B41B-4F8E9DE73FF9")

.comdef IXpsOMPackageWriter : public IUnknown

    StartNewDocument	proc :ptr, :ptr, :ptr, :ptr, :ptr
    AddPage		proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    AddResource		proc :ptr
    Close		proc
    IsClosed		proc :ptr
   .ends

endif


ifndef __IXpsOMPackageTarget_INTERFACE_DEFINED__
define __IXpsOMPackageTarget_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPackageTarget, "219A9DB0-4959-47D0-8034-B1CE84F41A4D")

.comdef IXpsOMPackageTarget : public IUnknown

    CreateXpsOMPackageWriter proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IXpsOMThumbnailGenerator_INTERFACE_DEFINED__
define __IXpsOMThumbnailGenerator_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMThumbnailGenerator, "15B873D5-1971-41E8-83A3-6578403064C7")

.comdef IXpsOMThumbnailGenerator : public IUnknown

    GenerateThumbnail	proc :ptr, :XPS_IMAGE_TYPE, :XPS_THUMBNAIL_SIZE, :ptr, :ptr
   .ends

endif


endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


ifndef __MSXPS_LIBRARY_DEFINED__
define __MSXPS_LIBRARY_DEFINED__

DEFINE_GUIDS(CLSID_XpsOMObjectFactory, "E974D26D-3D9B-4D47-88CC-3872F2DC3585")
DEFINE_GUIDS(CLSID_XpsOMThumbnailGenerator, "7E4A23E2-B969-4761-BE35-1A8CED58E323")

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
XPS_E_INVALID_LANGUAGE	equ MAKE_HRESULT(1, FACILITY_XPS, 0x000)
XPS_E_INVALID_NAME	equ MAKE_HRESULT(1, FACILITY_XPS, 0x001)
XPS_E_INVALID_RESOURCE_KEY equ MAKE_HRESULT(1, FACILITY_XPS, 0x002)
XPS_E_INVALID_PAGE_SIZE equ MAKE_HRESULT(1, FACILITY_XPS, 0x003)
XPS_E_INVALID_BLEED_BOX equ MAKE_HRESULT(1, FACILITY_XPS, 0x004)
XPS_E_INVALID_THUMBNAIL_IMAGE_TYPE equ MAKE_HRESULT(1, FACILITY_XPS, 0x005)
XPS_E_INVALID_LOOKUP_TYPE equ MAKE_HRESULT(1, FACILITY_XPS, 0x006)
XPS_E_INVALID_FLOAT	equ MAKE_HRESULT(1, FACILITY_XPS, 0x007)
XPS_E_UNEXPECTED_CONTENT_TYPE equ MAKE_HRESULT(1, FACILITY_XPS, 0x008)
XPS_E_INVALID_FONT_URI	equ MAKE_HRESULT(1, FACILITY_XPS, 0x00a)
XPS_E_INVALID_CONTENT_BOX equ MAKE_HRESULT(1, FACILITY_XPS, 0x00b)
XPS_E_INVALID_MARKUP	equ MAKE_HRESULT(1, FACILITY_XPS, 0x00c)
XPS_E_INVALID_XML_ENCODING equ MAKE_HRESULT(1, FACILITY_XPS, 0x00d)
XPS_E_INVALID_CONTENT_TYPE equ MAKE_HRESULT(1, FACILITY_XPS, 0x00e)
XPS_E_INVALID_OBFUSCATED_FONT_URI equ MAKE_HRESULT(1, FACILITY_XPS, 0x00f)
XPS_E_UNEXPECTED_RELATIONSHIP_TYPE equ MAKE_HRESULT(1, FACILITY_XPS, 0x010)
XPS_E_UNEXPECTED_RESTRICTED_FONT_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_XPS, 0x011)
XPS_E_MISSING_NAME	equ MAKE_HRESULT(1, FACILITY_XPS, 0x100)
XPS_E_MISSING_LOOKUP	equ MAKE_HRESULT(1, FACILITY_XPS, 0x101)
XPS_E_MISSING_GLYPHS	equ MAKE_HRESULT(1, FACILITY_XPS, 0x102)
XPS_E_MISSING_SEGMENT_DATA equ MAKE_HRESULT(1, FACILITY_XPS, 0x103)
XPS_E_MISSING_COLORPROFILE equ MAKE_HRESULT(1, FACILITY_XPS, 0x104)
XPS_E_MISSING_RELATIONSHIP_TARGET equ MAKE_HRESULT(1, FACILITY_XPS, 0x105)
XPS_E_MISSING_RESOURCE_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_XPS, 0x106)
XPS_E_MISSING_FONTURI	equ MAKE_HRESULT(1, FACILITY_XPS, 0x107)
XPS_E_MISSING_DOCUMENTSEQUENCE_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_XPS, 0x108)
XPS_E_MISSING_DOCUMENT	equ MAKE_HRESULT(1, FACILITY_XPS, 0x109)
XPS_E_MISSING_REFERRED_DOCUMENT equ MAKE_HRESULT(1, FACILITY_XPS, 0x10a)
XPS_E_MISSING_REFERRED_PAGE equ MAKE_HRESULT(1, FACILITY_XPS, 0x10b)
XPS_E_MISSING_PAGE_IN_DOCUMENT equ MAKE_HRESULT(1, FACILITY_XPS, 0x10c)
XPS_E_MISSING_PAGE_IN_PAGEREFERENCE equ MAKE_HRESULT(1, FACILITY_XPS, 0x10d)
XPS_E_MISSING_IMAGE_IN_IMAGEBRUSH equ MAKE_HRESULT(1, FACILITY_XPS, 0x10e)
XPS_E_MISSING_RESOURCE_KEY equ MAKE_HRESULT(1, FACILITY_XPS, 0x10f)
XPS_E_MISSING_PART_REFERENCE equ MAKE_HRESULT(1, FACILITY_XPS, 0x110)
XPS_E_MISSING_RESTRICTED_FONT_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_XPS, 0x111)
XPS_E_MISSING_DISCARDCONTROL equ MAKE_HRESULT(1, FACILITY_XPS, 0x112)
XPS_E_MISSING_PART_STREAM equ MAKE_HRESULT(1, FACILITY_XPS, 0x113)
XPS_E_UNAVAILABLE_PACKAGE equ MAKE_HRESULT(1, FACILITY_XPS, 0x114)
XPS_E_DUPLICATE_RESOURCE_KEYS equ MAKE_HRESULT(1, FACILITY_XPS, 0x200)
XPS_E_MULTIPLE_RESOURCES equ MAKE_HRESULT(1, FACILITY_XPS, 0x201)
XPS_E_MULTIPLE_DOCUMENTSEQUENCE_RELATIONSHIPS equ MAKE_HRESULT(1, FACILITY_XPS, 0x202)
XPS_E_MULTIPLE_THUMBNAILS_ON_PAGE equ MAKE_HRESULT(1, FACILITY_XPS, 0x203)
XPS_E_MULTIPLE_THUMBNAILS_ON_PACKAGE equ MAKE_HRESULT(1, FACILITY_XPS, 0x204)
XPS_E_MULTIPLE_PRINTTICKETS_ON_PAGE equ MAKE_HRESULT(1, FACILITY_XPS, 0x205)
XPS_E_MULTIPLE_PRINTTICKETS_ON_DOCUMENT equ MAKE_HRESULT(1, FACILITY_XPS, 0x206)
XPS_E_MULTIPLE_PRINTTICKETS_ON_DOCUMENTSEQUENCE equ MAKE_HRESULT(1, FACILITY_XPS, 0x207)
XPS_E_MULTIPLE_REFERENCES_TO_PART equ MAKE_HRESULT(1, FACILITY_XPS, 0x208)
XPS_E_DUPLICATE_NAMES	equ MAKE_HRESULT(1, FACILITY_XPS, 0x209)
XPS_E_STRING_TOO_LONG	equ MAKE_HRESULT(1, FACILITY_XPS, 0x300)
XPS_E_TOO_MANY_INDICES	equ MAKE_HRESULT(1, FACILITY_XPS, 0x301)
XPS_E_MAPPING_OUT_OF_ORDER equ MAKE_HRESULT(1, FACILITY_XPS, 0x302)
XPS_E_MAPPING_OUTSIDE_STRING equ MAKE_HRESULT(1, FACILITY_XPS, 0x303)
XPS_E_MAPPING_OUTSIDE_INDICES equ MAKE_HRESULT(1, FACILITY_XPS, 0x304)
XPS_E_CARET_OUTSIDE_STRING equ MAKE_HRESULT(1, FACILITY_XPS, 0x305)
XPS_E_CARET_OUT_OF_ORDER equ MAKE_HRESULT(1, FACILITY_XPS, 0x306)
XPS_E_ODD_BIDILEVEL	equ MAKE_HRESULT(1, FACILITY_XPS, 0x307)
XPS_E_ONE_TO_ONE_MAPPING_EXPECTED equ MAKE_HRESULT(1, FACILITY_XPS, 0x308)
XPS_E_RESTRICTED_FONT_NOT_OBFUSCATED equ MAKE_HRESULT(1, FACILITY_XPS, 0x309)
XPS_E_NEGATIVE_FLOAT	equ MAKE_HRESULT(1, FACILITY_XPS, 0x30a)
XPS_E_XKEY_ATTR_PRESENT_OUTSIDE_RES_DICT equ MAKE_HRESULT(1, FACILITY_XPS, 0x400)
XPS_E_DICTIONARY_ITEM_NAMED equ MAKE_HRESULT(1, FACILITY_XPS, 0x401)
XPS_E_NESTED_REMOTE_DICTIONARY equ MAKE_HRESULT(1, FACILITY_XPS, 0x402)
XPS_E_INDEX_OUT_OF_RANGE equ MAKE_HRESULT(1, FACILITY_XPS, 0x500)
XPS_E_VISUAL_CIRCULAR_REF equ MAKE_HRESULT(1, FACILITY_XPS, 0x501)
XPS_E_NO_CUSTOM_OBJECTS equ MAKE_HRESULT(1, FACILITY_XPS, 0x502)
XPS_E_ALREADY_OWNED	equ MAKE_HRESULT(1, FACILITY_XPS, 0x503)
XPS_E_RESOURCE_NOT_OWNED equ MAKE_HRESULT(1, FACILITY_XPS, 0x504)
XPS_E_UNEXPECTED_COLORPROFILE equ MAKE_HRESULT(1, FACILITY_XPS, 0x505)
XPS_E_COLOR_COMPONENT_OUT_OF_RANGE equ MAKE_HRESULT(1, FACILITY_XPS, 0x506)
XPS_E_BOTH_PATHFIGURE_AND_ABBR_SYNTAX_PRESENT equ MAKE_HRESULT(1, FACILITY_XPS, 0x507)
XPS_E_BOTH_RESOURCE_AND_SOURCEATTR_PRESENT equ MAKE_HRESULT(1, FACILITY_XPS, 0x508)
XPS_E_BLEED_BOX_PAGE_DIMENSIONS_NOT_IN_SYNC equ MAKE_HRESULT(1, FACILITY_XPS, 0x509)
XPS_E_RELATIONSHIP_EXTERNAL equ MAKE_HRESULT(1, FACILITY_XPS, 0x50a)
XPS_E_NOT_ENOUGH_GRADIENT_STOPS equ MAKE_HRESULT(1, FACILITY_XPS, 0x50b)
XPS_E_PACKAGE_WRITER_NOT_CLOSED equ MAKE_HRESULT(1, FACILITY_XPS, 0x50c)

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

endif ;; (NTDDI GE NTDDI_WIN7)
endif
