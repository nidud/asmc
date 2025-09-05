ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Emedia_h__
define __windows2Eui2Examl2Emedia_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Media

.enum AlignmentX {
    AlignmentX_Left	= 0,
    AlignmentX_Center	= 1,
    AlignmentX_Right	= 2
    }

.enum AlignmentY {
    AlignmentY_Top	= 0,
    AlignmentY_Center	= 1,
    AlignmentY_Bottom	= 2
    }

.enum AudioCategory {
    AudioCategory_Other = 0,
    AudioCategory_ForegroundOnlyMedia	= 1,
    AudioCategory_BackgroundCapableMedia	= 2,
    AudioCategory_Communications	= 3,
    AudioCategory_Alerts	= 4,
    AudioCategory_SoundEffects	= 5,
    AudioCategory_GameEffects	= 6,
    AudioCategory_GameMedia	= 7
    }

.enum AudioDeviceType {
    AudioDeviceType_Console	= 0,
    AudioDeviceType_Multimedia	= 1,
    AudioDeviceType_Communications	= 2
    }

.enum BrushMappingMode {
    BrushMappingMode_Absolute	= 0,
    BrushMappingMode_RelativeToBoundingBox	= 1
    }

.enum ColorInterpolationMode {
    ColorInterpolationMode_ScRgbLinearInterpolation	= 0,
    ColorInterpolationMode_SRgbLinearInterpolation	= 1
    }

.enum ElementCompositeMode {
    ElementCompositeMode_Inherit	= 0,
    ElementCompositeMode_SourceOver	= 1,
    ElementCompositeMode_MinBlend	= 2
    }

.enum FillRule {
    FillRule_EvenOdd	= 0,
    FillRule_Nonzero	= 1
    }

.enum GradientSpreadMethod {
    GradientSpreadMethod_Pad	= 0,
    GradientSpreadMethod_Reflect	= 1,
    GradientSpreadMethod_Repeat = 2
    }

.enum MediaCanPlayResponse {
    MediaCanPlayResponse_NotSupported	= 0,
    MediaCanPlayResponse_Maybe	= 1,
    MediaCanPlayResponse_Probably	= 2
    }

.enum MediaElementState {
    MediaElementState_Closed	= 0,
    MediaElementState_Opening	= 1,
    MediaElementState_Buffering = 2,
    MediaElementState_Playing	= 3,
    MediaElementState_Paused	= 4,
    MediaElementState_Stopped	= 5
    }

.enum PenLineCap {
    PenLineCap_Flat	= 0,
    PenLineCap_Square	= 1,
    PenLineCap_Round	= 2,
    PenLineCap_Triangle = 3
    }

.enum PenLineJoin {
    PenLineJoin_Miter	= 0,
    PenLineJoin_Bevel	= 1,
    PenLineJoin_Round	= 2
    }

.enum Stereo3DVideoPackingMode {
    Stereo3DVideoPackingMode_None	= 0,
    Stereo3DVideoPackingMode_SideBySide = 1,
    Stereo3DVideoPackingMode_TopBottom	= 2
    }

.enum Stereo3DVideoRenderMode {
    Stereo3DVideoRenderMode_Mono	= 0,
    Stereo3DVideoRenderMode_Stereo	= 1
    }

.enum Stretch {
    Stretch_None	= 0,
    Stretch_Fill	= 1,
    Stretch_Uniform	= 2,
    Stretch_UniformToFill	= 3
    }

.enum StyleSimulations {
    StyleSimulations_None	= 0,
    StyleSimulations_BoldSimulation	= 1,
    StyleSimulations_ItalicSimulation	= 2,
    StyleSimulations_BoldItalicSimulation	= 3
    }

.enum SweepDirection {
    SweepDirection_Counterclockwise	= 0,
    SweepDirection_Clockwise	= 1
    }

.template Matrix
    M11			DOUBLE ?
    M12			DOUBLE ?
    M21			DOUBLE ?
    M22			DOUBLE ?
    OffsetX		DOUBLE ?
    OffsetY		DOUBLE ?
   .ends

.endn
.endn
.endn
.endn

include Windows.UI.inc
include Windows.UI.Xaml.inc
include Windows.UI.Xaml.Media.Media3D.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CGeometry_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CGeometry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CGeometry, "8726dcbf-961d-527a-a7cb-2db47e1c9092")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CGeometry : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CGeometry_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CGeometry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CGeometry, "35340039-0dfc-52b4-8748-0d9a755db8a8")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CGeometry : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CGradientStop_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CGradientStop_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CGradientStop, "01dca32b-0938-5e4a-94ad-bb4906f651ed")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CGradientStop : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CGradientStop_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CGradientStop_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CGradientStop, "9105bb93-ac26-5bae-8c1e-df8ecf00dee6")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CGradientStop : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CPathFigure_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CPathFigure_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CPathFigure, "71bd579b-088e-5e59-8876-80613dcff83e")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CPathFigure : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CPathFigure_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CPathFigure_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CPathFigure, "cd1dc421-d6e5-5b3f-a8c7-9938f28b2995")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CPathFigure : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CPathSegment_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CPathSegment_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CPathSegment, "3cfedcfb-7a75-5bc7-a7e2-95ee9bc6dd32")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CPathSegment : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CPathSegment_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CPathSegment_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CPathSegment, "37e2cb21-b9c9-5006-bed7-4c328981b551")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CPathSegment : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CTimelineMarker_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CTimelineMarker_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CTimelineMarker, "63e1e513-fca3-51c0-8c2b-09db5f8f4c40")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CTimelineMarker : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CTimelineMarker_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CTimelineMarker_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CTimelineMarker, "946c5af5-4c09-5784-9cf2-506947378e8e")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CTimelineMarker : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CTransform_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CTransform_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CTransform, "2cdbd536-4598-5f0f-a236-11ec053c8e4b")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CTransform : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CTransform_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CTransform_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CTransform, "fb8cacbc-d3ec-51b8-9778-99ede8463611")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CTransform : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CGeometry_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CGeometry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CGeometry, "1905e02c-de78-5136-b761-7b7a33402583")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CGeometry : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CGradientStop_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CGradientStop_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CGradientStop, "4c4a7b50-4bc3-52cb-8c81-2ea77702b566")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CGradientStop : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CPathFigure_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CPathFigure_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CPathFigure, "bfe78700-1265-548c-a06b-259cc2bd032b")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CPathFigure : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CPathSegment_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CPathSegment_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CPathSegment, "54735271-a3db-5e42-85be-4ff85432364b")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CPathSegment : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CTimelineMarker_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CTimelineMarker_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CTimelineMarker, "fef8133f-98e9-5ca3-a667-0d234c5d1d96")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CTimelineMarker : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CTransform_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CTransform_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CTransform, "b3a869c7-9c78-525b-943e-16a2c8979b03")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CTransform : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CGeometry_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CGeometry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CGeometry, "84c6ac3a-8207-5599-9583-606ac2139ddd")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CGeometry : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CGradientStop_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CGradientStop_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CGradientStop, "33422da4-24f3-5b52-9e8d-11dd71f08bb1")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CGradientStop : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CPathFigure_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CPathFigure_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CPathFigure, "de29d405-26dd-5e72-8bcb-495199d4e5b5")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CPathFigure : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CPathSegment_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CPathSegment_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CPathSegment, "11fdd506-b21d-564d-b6a8-ff991057b8f3")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CPathSegment : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CTimelineMarker_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CTimelineMarker_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CTimelineMarker, "b2d8ddb4-d2b8-5930-942d-26118756bd46")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CTimelineMarker : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CTransform_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CTransform_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CTransform, "62d7bbc1-71f5-5611-a984-e571c2de7baa")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CTransform : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Media

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRateChangedRoutedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRateChangedRoutedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IRateChangedRoutedEventHandler, "08E9A257-AE05-489B-8839-28C6225D2349")

.comdef IRateChangedRoutedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif
ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITimelineMarkerRoutedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITimelineMarkerRoutedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ITimelineMarkerRoutedEventHandler, "72E2FA9C-6DEA-4CBE-A159-06CE95FBECED")

.comdef ITimelineMarkerRoutedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrixHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrixHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IMatrixHelper <L"Windows.UI.Xaml.Media.IMatrixHelper">
DEFINE_IIDX(IMatrixHelper, "F3CF4882-06B5-48C8-9EB2-1763E9364038")

.comdef IMatrixHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrixHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrixHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IMatrixHelperStatics <L"Windows.UI.Xaml.Media.IMatrixHelperStatics">
DEFINE_IIDX(IMatrixHelperStatics, "C18606A6-39F4-4B8A-8403-28E5E5F033B4")

.comdef IMatrixHelperStatics : public IInspectable

    get_Identity	proc :ptr
    FromElements	proc :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :ptr
    GetIsIdentity	proc :Windows::UI::Xaml::Media::Matrix, :ptr
    Transform		proc :Windows::UI::Xaml::Media::Matrix, :Windows::Foundation::Point, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIArcSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIArcSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IArcSegment <L"Windows.UI.Xaml.Media.IArcSegment">
DEFINE_IIDX(IArcSegment, "07940C5F-63FB-4469-91BE-F1097C168052")

.comdef IArcSegment : public IInspectable

    get_Point		proc :ptr
    put_Point		proc :Windows::Foundation::Point
    get_Size		proc :ptr
    put_Size		proc :Windows::Foundation::Size
    get_RotationAngle	proc :ptr
    put_RotationAngle	proc :DOUBLE
    get_IsLargeArc	proc :ptr
    put_IsLargeArc	proc :boolean
    get_SweepDirection	proc :ptr
    put_SweepDirection	proc :Windows::UI::Xaml::Media::SweepDirection
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIArcSegmentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIArcSegmentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IArcSegmentStatics <L"Windows.UI.Xaml.Media.IArcSegmentStatics">
DEFINE_IIDX(IArcSegmentStatics, "82348F6E-8A69-4204-9C12-7207DF317643")

.comdef IArcSegmentStatics : public IInspectable

    get_PointProperty	proc :ptr
    get_SizeProperty	proc :ptr
    get_RotationAngleProperty proc :ptr
    get_IsLargeArcProperty proc :ptr
    get_SweepDirectionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBezierSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBezierSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IBezierSegment <L"Windows.UI.Xaml.Media.IBezierSegment">
DEFINE_IIDX(IBezierSegment, "AF4BB9EE-8984-49B7-81DF-3F35994B95EB")

.comdef IBezierSegment : public IInspectable

    get_Point1		proc :ptr
    put_Point1		proc :Windows::Foundation::Point
    get_Point2		proc :ptr
    put_Point2		proc :Windows::Foundation::Point
    get_Point3		proc :ptr
    put_Point3		proc :Windows::Foundation::Point
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBezierSegmentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBezierSegmentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IBezierSegmentStatics <L"Windows.UI.Xaml.Media.IBezierSegmentStatics">
DEFINE_IIDX(IBezierSegmentStatics, "C0287BAC-1410-4530-8452-1C9D0AD1F341")

.comdef IBezierSegmentStatics : public IInspectable

    get_Point1Property	proc :ptr
    get_Point2Property	proc :ptr
    get_Point3Property	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBitmapCache_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBitmapCache_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IBitmapCache <L"Windows.UI.Xaml.Media.IBitmapCache">
DEFINE_IIDX(IBitmapCache, "79C2219E-44D2-4610-9735-9BEC83809ECF")

.comdef IBitmapCache : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IBrush <L"Windows.UI.Xaml.Media.IBrush">
DEFINE_IIDX(IBrush, "8806A321-1E06-422C-A1CC-01696559E021")

.comdef IBrush : public IInspectable

    get_Opacity		proc :ptr
    put_Opacity		proc :DOUBLE
    get_Transform	proc :ptr
    put_Transform	proc :ptr
    get_RelativeTransform proc :ptr
    put_RelativeTransform proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBrushStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBrushStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IBrushStatics <L"Windows.UI.Xaml.Media.IBrushStatics">
DEFINE_IIDX(IBrushStatics, "E70C3102-0225-47F5-B22E-0467619F6A22")

.comdef IBrushStatics : public IInspectable

    get_OpacityProperty proc :ptr
    get_TransformProperty proc :ptr
    get_RelativeTransformProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBrushFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIBrushFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IBrushFactory <L"Windows.UI.Xaml.Media.IBrushFactory">
DEFINE_IIDX(IBrushFactory, "399658A2-14FB-4B8F-83E6-6E3DAB12069B")

.comdef IBrushFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CICacheMode_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CICacheMode_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ICacheMode <L"Windows.UI.Xaml.Media.ICacheMode">
DEFINE_IIDX(ICacheMode, "98DC8B11-C6F9-4DAB-B838-5FD5EC8C7350")

.comdef ICacheMode : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CICacheModeFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CICacheModeFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ICacheModeFactory <L"Windows.UI.Xaml.Media.ICacheModeFactory">
DEFINE_IIDX(ICacheModeFactory, "EB1F8C5B-0ABB-4E70-B8A8-620D0D953AB2")

.comdef ICacheModeFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CICompositeTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CICompositeTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ICompositeTransform <L"Windows.UI.Xaml.Media.ICompositeTransform">
DEFINE_IIDX(ICompositeTransform, "C8A4385B-F24A-4701-A265-A78846F142B9")

.comdef ICompositeTransform : public IInspectable

    get_CenterX		proc :ptr
    put_CenterX		proc :DOUBLE
    get_CenterY		proc :ptr
    put_CenterY		proc :DOUBLE
    get_ScaleX		proc :ptr
    put_ScaleX		proc :DOUBLE
    get_ScaleY		proc :ptr
    put_ScaleY		proc :DOUBLE
    get_SkewX		proc :ptr
    put_SkewX		proc :DOUBLE
    get_SkewY		proc :ptr
    put_SkewY		proc :DOUBLE
    get_Rotation	proc :ptr
    put_Rotation	proc :DOUBLE
    get_TranslateX	proc :ptr
    put_TranslateX	proc :DOUBLE
    get_TranslateY	proc :ptr
    put_TranslateY	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CICompositeTransformStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CICompositeTransformStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ICompositeTransformStatics <L"Windows.UI.Xaml.Media.ICompositeTransformStatics">
DEFINE_IIDX(ICompositeTransformStatics, "2F190C08-8266-496F-9653-A18BD4F836AA")

.comdef ICompositeTransformStatics : public IInspectable

    get_CenterXProperty proc :ptr
    get_CenterYProperty proc :ptr
    get_ScaleXProperty	proc :ptr
    get_ScaleYProperty	proc :ptr
    get_SkewXProperty	proc :ptr
    get_SkewYProperty	proc :ptr
    get_RotationProperty proc :ptr
    get_TranslateXProperty proc :ptr
    get_TranslateYProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIEllipseGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIEllipseGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IEllipseGeometry <L"Windows.UI.Xaml.Media.IEllipseGeometry">
DEFINE_IIDX(IEllipseGeometry, "D4F61BBA-4EA2-40D6-AA6C-8D38AA87651F")

.comdef IEllipseGeometry : public IInspectable

    get_Center		proc :ptr
    put_Center		proc :Windows::Foundation::Point
    get_RadiusX		proc :ptr
    put_RadiusX		proc :DOUBLE
    get_RadiusY		proc :ptr
    put_RadiusY		proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIEllipseGeometryStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIEllipseGeometryStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IEllipseGeometryStatics <L"Windows.UI.Xaml.Media.IEllipseGeometryStatics">
DEFINE_IIDX(IEllipseGeometryStatics, "1744DB47-F635-4B16-AEE6-E052A65DEFB2")

.comdef IEllipseGeometryStatics : public IInspectable

    get_CenterProperty	proc :ptr
    get_RadiusXProperty proc :ptr
    get_RadiusYProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIFontFamily_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIFontFamily_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IFontFamily <L"Windows.UI.Xaml.Media.IFontFamily">
DEFINE_IIDX(IFontFamily, "92467E64-D66A-4CF4-9322-3D23B3C0C361")

.comdef IFontFamily : public IInspectable

    get_Source		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIFontFamilyFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIFontFamilyFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IFontFamilyFactory <L"Windows.UI.Xaml.Media.IFontFamilyFactory">
DEFINE_IIDX(IFontFamilyFactory, "D5603377-3DAE-4DCD-AF09-F9498E9EC659")

.comdef IFontFamilyFactory : public IInspectable

    CreateInstanceWithName proc :HSTRING, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeneralTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeneralTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGeneralTransform <L"Windows.UI.Xaml.Media.IGeneralTransform">
DEFINE_IIDX(IGeneralTransform, "A06798B7-A2EC-415F-ADE2-EADE9333F2C7")

.comdef IGeneralTransform : public IInspectable

    get_Inverse		proc :ptr
    TransformPoint	proc :Windows::Foundation::Point, :ptr
    TryTransform	proc :Windows::Foundation::Point, :ptr, :ptr
    TransformBounds	proc :Windows::Foundation::Rect, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeneralTransformOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeneralTransformOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGeneralTransformOverrides <L"Windows.UI.Xaml.Media.IGeneralTransformOverrides">
DEFINE_IIDX(IGeneralTransformOverrides, "4F121083-24CF-4524-90AD-8A42B1C12783")

.comdef IGeneralTransformOverrides : public IInspectable

    get_InverseCore	proc :ptr
    TryTransformCore	proc :Windows::Foundation::Point, :ptr, :ptr
    TransformBoundsCore proc :Windows::Foundation::Rect, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeneralTransformFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeneralTransformFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGeneralTransformFactory <L"Windows.UI.Xaml.Media.IGeneralTransformFactory">
DEFINE_IIDX(IGeneralTransformFactory, "7A25C930-29C4-4E31-B6F9-DEDD52E4DF1B")

.comdef IGeneralTransformFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGeometry <L"Windows.UI.Xaml.Media.IGeometry">
DEFINE_IIDX(IGeometry, "FA123889-0ACD-417B-B62D-5CA1BF4DFC0E")

.comdef IGeometry : public IInspectable

    get_Transform	proc :ptr
    put_Transform	proc :ptr
    get_Bounds		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometryStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometryStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGeometryStatics <L"Windows.UI.Xaml.Media.IGeometryStatics">
DEFINE_IIDX(IGeometryStatics, "7A70AA8C-0B06-465F-B637-9A47E5A70111")

.comdef IGeometryStatics : public IInspectable

    get_Empty		proc :ptr
    get_StandardFlatteningTolerance proc :ptr
    get_TransformProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometryFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometryFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGeometryFactory <L"Windows.UI.Xaml.Media.IGeometryFactory">
DEFINE_IIDX(IGeometryFactory, "F65DAF23-D5FD-42F9-B32A-929C5A4B54E1")

.comdef IGeometryFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometryGroup_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometryGroup_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGeometryGroup <L"Windows.UI.Xaml.Media.IGeometryGroup">
DEFINE_IIDX(IGeometryGroup, "55225A61-8677-4C8C-8E46-EE3DC355114B")

.comdef IGeometryGroup : public IInspectable

    get_FillRule	proc :ptr
    put_FillRule	proc :Windows::UI::Xaml::Media::FillRule
    get_Children	proc :ptr
    put_Children	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometryGroupStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGeometryGroupStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGeometryGroupStatics <L"Windows.UI.Xaml.Media.IGeometryGroupStatics">
DEFINE_IIDX(IGeometryGroupStatics, "56C955F4-8496-4BB6-ABF0-617B1FE78B45")

.comdef IGeometryGroupStatics : public IInspectable

    get_FillRuleProperty proc :ptr
    get_ChildrenProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGradientBrush <L"Windows.UI.Xaml.Media.IGradientBrush">
DEFINE_IIDX(IGradientBrush, "2166E69F-935A-4191-8E3C-1C8DFDFCDC78")

.comdef IGradientBrush : public IInspectable

    get_SpreadMethod	proc :ptr
    put_SpreadMethod	proc :Windows::UI::Xaml::Media::GradientSpreadMethod
    get_MappingMode	proc :ptr
    put_MappingMode	proc :Windows::UI::Xaml::Media::BrushMappingMode
    get_ColorInterpolationMode proc :ptr
    put_ColorInterpolationMode proc :Windows::UI::Xaml::Media::ColorInterpolationMode
    get_GradientStops	proc :ptr
    put_GradientStops	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientBrushStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientBrushStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGradientBrushStatics <L"Windows.UI.Xaml.Media.IGradientBrushStatics">
DEFINE_IIDX(IGradientBrushStatics, "961661F9-8BB4-4E6C-B923-B5D787E0F1A9")

.comdef IGradientBrushStatics : public IInspectable

    get_SpreadMethodProperty proc :ptr
    get_MappingModeProperty proc :ptr
    get_ColorInterpolationModeProperty proc :ptr
    get_GradientStopsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientBrushFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientBrushFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGradientBrushFactory <L"Windows.UI.Xaml.Media.IGradientBrushFactory">
DEFINE_IIDX(IGradientBrushFactory, "ED4779CA-45BD-4131-B625-BE86E07C6112")

.comdef IGradientBrushFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientStop_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientStop_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGradientStop <L"Windows.UI.Xaml.Media.IGradientStop">
DEFINE_IIDX(IGradientStop, "665F44FE-2E59-4C4A-AB53-076A100CCD81")

.comdef IGradientStop : public IInspectable

    get_Color		proc :ptr
    put_Color		proc :Windows::UI::Color
    get_Offset		proc :ptr
    put_Offset		proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientStopStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIGradientStopStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IGradientStopStatics <L"Windows.UI.Xaml.Media.IGradientStopStatics">
DEFINE_IIDX(IGradientStopStatics, "602A6D75-6193-4FE5-8E82-C7C6F6FEBAFD")

.comdef IGradientStopStatics : public IInspectable

    get_ColorProperty	proc :ptr
    get_OffsetProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIImageBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIImageBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IImageBrush <L"Windows.UI.Xaml.Media.IImageBrush">
DEFINE_IIDX(IImageBrush, "9FD11377-C12A-4493-BF7D-F3A8AD74B554")

.comdef IImageBrush : public IInspectable

    get_ImageSource	proc :ptr
    put_ImageSource	proc :ptr
    add_ImageFailed	proc :ptr, :ptr
    remove_ImageFailed	proc :EventRegistrationToken
    add_ImageOpened	proc :ptr, :ptr
    remove_ImageOpened	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIImageBrushStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIImageBrushStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IImageBrushStatics <L"Windows.UI.Xaml.Media.IImageBrushStatics">
DEFINE_IIDX(IImageBrushStatics, "1255B1B2-DD18-42E5-892C-EAE30C305B8C")

.comdef IImageBrushStatics : public IInspectable

    get_ImageSourceProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIImageSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIImageSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IImageSource <L"Windows.UI.Xaml.Media.IImageSource">
DEFINE_IIDX(IImageSource, "737EF309-EA41-4D96-A71C-98E98EFCAB07")

.comdef IImageSource : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIImageSourceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIImageSourceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IImageSourceFactory <L"Windows.UI.Xaml.Media.IImageSourceFactory">
DEFINE_IIDX(IImageSourceFactory, "297EC001-2540-4E5A-AB66-88035DD3DDB5")

.comdef IImageSourceFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CILinearGradientBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CILinearGradientBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ILinearGradientBrush <L"Windows.UI.Xaml.Media.ILinearGradientBrush">
DEFINE_IIDX(__x_ABI_CWindows_CUI_CXaml_CMedia_CILinearGradientBrush, "8E96D16B-BB84-4C6F-9DBF-9D6C5C6D9C39")

.comdef __x_ABI_CWindows_CUI_CXaml_CMedia_CILinearGradientBrush : public IInspectable

    get_StartPoint	proc :ptr
    put_StartPoint	proc :Windows::Foundation::Point
    get_EndPoint	proc :ptr
    put_EndPoint	proc :Windows::Foundation::Point
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CILinearGradientBrushStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CILinearGradientBrushStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ILinearGradientBrushStatics <L"Windows.UI.Xaml.Media.ILinearGradientBrushStatics">
DEFINE_IIDX(ILinearGradientBrushStatics, "7AF6E504-2DC3-40E3-BE0B-B314C13CB991")

.comdef ILinearGradientBrushStatics : public IInspectable

    get_StartPointProperty proc :ptr
    get_EndPointProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CILinearGradientBrushFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CILinearGradientBrushFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ILinearGradientBrushFactory <L"Windows.UI.Xaml.Media.ILinearGradientBrushFactory">
DEFINE_IIDX(ILinearGradientBrushFactory, "0AE0861C-1E7A-4FED-9857-EA8CAA798490")

.comdef ILinearGradientBrushFactory : public IInspectable

    CreateInstanceWithGradientStopCollectionAndAngle proc :ptr, :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CILineGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CILineGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ILineGeometry <L"Windows.UI.Xaml.Media.ILineGeometry">
DEFINE_IIDX(ILineGeometry, "30EDD4A2-8FC5-40AF-A7A2-C27FE7AA1363")

.comdef ILineGeometry : public IInspectable

    get_StartPoint	proc :ptr
    put_StartPoint	proc :Windows::Foundation::Point
    get_EndPoint	proc :ptr
    put_EndPoint	proc :Windows::Foundation::Point
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CILineGeometryStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CILineGeometryStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ILineGeometryStatics <L"Windows.UI.Xaml.Media.ILineGeometryStatics">
DEFINE_IIDX(ILineGeometryStatics, "578AE763-5562-4EE4-8703-EA4036D891E3")

.comdef ILineGeometryStatics : public IInspectable

    get_StartPointProperty proc :ptr
    get_EndPointProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CILineSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CILineSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ILineSegment <L"Windows.UI.Xaml.Media.ILineSegment">
DEFINE_IIDX(ILineSegment, "EF6A2E25-3FF0-4420-A411-7182A4CECB15")

.comdef ILineSegment : public IInspectable

    get_Point		proc :ptr
    put_Point		proc :Windows::Foundation::Point
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CILineSegmentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CILineSegmentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ILineSegmentStatics <L"Windows.UI.Xaml.Media.ILineSegmentStatics">
DEFINE_IIDX(ILineSegmentStatics, "9FCAB141-04C0-4AFB-87B3-E800B969B894")

.comdef ILineSegmentStatics : public IInspectable

    get_PointProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrix3DProjection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrix3DProjection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IMatrix3DProjection <L"Windows.UI.Xaml.Media.IMatrix3DProjection">
DEFINE_IIDX(IMatrix3DProjection, "6F03E149-BFC9-4C01-B578-50338CEC97FC")

.comdef IMatrix3DProjection : public IInspectable

    get_ProjectionMatrix proc :ptr
    put_ProjectionMatrix proc :Windows::UI::Xaml::Media::Media3D::Matrix3D
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrix3DProjectionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrix3DProjectionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IMatrix3DProjectionStatics <L"Windows.UI.Xaml.Media.IMatrix3DProjectionStatics">
DEFINE_IIDX(IMatrix3DProjectionStatics, "AE9D5895-41EC-4E37-ABAA-69F41D2F876B")

.comdef IMatrix3DProjectionStatics : public IInspectable

    get_ProjectionMatrixProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrixTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrixTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IMatrixTransform <L"Windows.UI.Xaml.Media.IMatrixTransform">
DEFINE_IIDX(IMatrixTransform, "EDFDD551-5FED-45FC-AE62-92A4B6CF9707")

.comdef IMatrixTransform : public IInspectable

    get_Matrix		proc :ptr
    put_Matrix		proc :Windows::UI::Xaml::Media::Matrix
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrixTransformStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIMatrixTransformStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IMatrixTransformStatics <L"Windows.UI.Xaml.Media.IMatrixTransformStatics">
DEFINE_IIDX(IMatrixTransformStatics, "43E02E47-15B8-4758-BB97-7D52420ACC5B")

.comdef IMatrixTransformStatics : public IInspectable

    get_MatrixProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathFigure_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathFigure_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPathFigure <L"Windows.UI.Xaml.Media.IPathFigure">
DEFINE_IIDX(IPathFigure, "5D955C8C-5FA9-4DDA-A3CC-10FCDCAA20D7")

.comdef IPathFigure : public IInspectable

    get_Segments	proc :ptr
    put_Segments	proc :ptr
    get_StartPoint	proc :ptr
    put_StartPoint	proc :Windows::Foundation::Point
    get_IsClosed	proc :ptr
    put_IsClosed	proc :boolean
    get_IsFilled	proc :ptr
    put_IsFilled	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathFigureStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathFigureStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPathFigureStatics <L"Windows.UI.Xaml.Media.IPathFigureStatics">
DEFINE_IIDX(IPathFigureStatics, "B60591D9-2395-4317-9552-3A58526F8C7B")

.comdef IPathFigureStatics : public IInspectable

    get_SegmentsProperty proc :ptr
    get_StartPointProperty proc :ptr
    get_IsClosedProperty proc :ptr
    get_IsFilledProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPathGeometry <L"Windows.UI.Xaml.Media.IPathGeometry">
DEFINE_IIDX(IPathGeometry, "081B9DF8-BAE6-4BCB-813C-BDE0E46DC8B7")

.comdef IPathGeometry : public IInspectable

    get_FillRule	proc :ptr
    put_FillRule	proc :Windows::UI::Xaml::Media::FillRule
    get_Figures		proc :ptr
    put_Figures		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathGeometryStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathGeometryStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPathGeometryStatics <L"Windows.UI.Xaml.Media.IPathGeometryStatics">
DEFINE_IIDX(IPathGeometryStatics, "D9E58BBA-2CBA-4741-8F8D-3198CF5186B9")

.comdef IPathGeometryStatics : public IInspectable

    get_FillRuleProperty proc :ptr
    get_FiguresProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPathSegment <L"Windows.UI.Xaml.Media.IPathSegment">
DEFINE_IIDX(IPathSegment, "FCFA71CF-9CE3-474F-8157-10B6435A616B")

.comdef IPathSegment : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathSegmentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPathSegmentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPathSegmentFactory <L"Windows.UI.Xaml.Media.IPathSegmentFactory">
DEFINE_IIDX(IPathSegmentFactory, "2A1C0AAE-ECCD-4464-A148-6FFDB3AA281F")

.comdef IPathSegmentFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPlaneProjection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPlaneProjection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPlaneProjection <L"Windows.UI.Xaml.Media.IPlaneProjection">
DEFINE_IIDX(IPlaneProjection, "E6F82BFA-6726-469A-B259-A5188347CA8F")

.comdef IPlaneProjection : public IInspectable

    get_LocalOffsetX	proc :ptr
    put_LocalOffsetX	proc :DOUBLE
    get_LocalOffsetY	proc :ptr
    put_LocalOffsetY	proc :DOUBLE
    get_LocalOffsetZ	proc :ptr
    put_LocalOffsetZ	proc :DOUBLE
    get_RotationX	proc :ptr
    put_RotationX	proc :DOUBLE
    get_RotationY	proc :ptr
    put_RotationY	proc :DOUBLE
    get_RotationZ	proc :ptr
    put_RotationZ	proc :DOUBLE
    get_CenterOfRotationX proc :ptr
    put_CenterOfRotationX proc :DOUBLE
    get_CenterOfRotationY proc :ptr
    put_CenterOfRotationY proc :DOUBLE
    get_CenterOfRotationZ proc :ptr
    put_CenterOfRotationZ proc :DOUBLE
    get_GlobalOffsetX	proc :ptr
    put_GlobalOffsetX	proc :DOUBLE
    get_GlobalOffsetY	proc :ptr
    put_GlobalOffsetY	proc :DOUBLE
    get_GlobalOffsetZ	proc :ptr
    put_GlobalOffsetZ	proc :DOUBLE
    get_ProjectionMatrix proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPlaneProjectionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPlaneProjectionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPlaneProjectionStatics <L"Windows.UI.Xaml.Media.IPlaneProjectionStatics">
DEFINE_IIDX(IPlaneProjectionStatics, "AD919C67-3BDC-4855-8969-D1F9A3ADC27D")

.comdef IPlaneProjectionStatics : public IInspectable

    get_LocalOffsetXProperty proc :ptr
    get_LocalOffsetYProperty proc :ptr
    get_LocalOffsetZProperty proc :ptr
    get_RotationXProperty proc :ptr
    get_RotationYProperty proc :ptr
    get_RotationZProperty proc :ptr
    get_CenterOfRotationXProperty proc :ptr
    get_CenterOfRotationYProperty proc :ptr
    get_CenterOfRotationZProperty proc :ptr
    get_GlobalOffsetXProperty proc :ptr
    get_GlobalOffsetYProperty proc :ptr
    get_GlobalOffsetZProperty proc :ptr
    get_ProjectionMatrixProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyBezierSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyBezierSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPolyBezierSegment <L"Windows.UI.Xaml.Media.IPolyBezierSegment">
DEFINE_IIDX(IPolyBezierSegment, "36805271-38C4-4BCF-96CD-028A6D38AF25")

.comdef IPolyBezierSegment : public IInspectable

    get_Points		proc :ptr
    put_Points		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyBezierSegmentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyBezierSegmentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPolyBezierSegmentStatics <L"Windows.UI.Xaml.Media.IPolyBezierSegmentStatics">
DEFINE_IIDX(IPolyBezierSegmentStatics, "1D91A6DA-1492-4ACC-BD66-A496F3D829D6")

.comdef IPolyBezierSegmentStatics : public IInspectable

    get_PointsProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyLineSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyLineSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPolyLineSegment <L"Windows.UI.Xaml.Media.IPolyLineSegment">
DEFINE_IIDX(IPolyLineSegment, "4B397F87-A2E6-479D-BDC8-6F4464646887")

.comdef IPolyLineSegment : public IInspectable

    get_Points		proc :ptr
    put_Points		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyLineSegmentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyLineSegmentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPolyLineSegmentStatics <L"Windows.UI.Xaml.Media.IPolyLineSegmentStatics">
DEFINE_IIDX(IPolyLineSegmentStatics, "D64A2C87-33F1-4E70-A47F-B4981EF648A2")

.comdef IPolyLineSegmentStatics : public IInspectable

    get_PointsProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyQuadraticBezierSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyQuadraticBezierSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPolyQuadraticBezierSegment <L"Windows.UI.Xaml.Media.IPolyQuadraticBezierSegment">
DEFINE_IIDX(IPolyQuadraticBezierSegment, "DD5CED7D-E6DB-4C96-B6A1-3FCE96E987A6")

.comdef IPolyQuadraticBezierSegment : public IInspectable

    get_Points		proc :ptr
    put_Points		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyQuadraticBezierSegmentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIPolyQuadraticBezierSegmentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IPolyQuadraticBezierSegmentStatics <L"Windows.UI.Xaml.Media.IPolyQuadraticBezierSegmentStatics">
DEFINE_IIDX(IPolyQuadraticBezierSegmentStatics, "FDF5EB75-7AD5-4C89-8169-8C9786ABD9EB")

.comdef IPolyQuadraticBezierSegmentStatics : public IInspectable

    get_PointsProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIProjection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIProjection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IProjection <L"Windows.UI.Xaml.Media.IProjection">
DEFINE_IIDX(IProjection, "B3443557-7F39-4D04-A89C-844338CAC897")

.comdef IProjection : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIProjectionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIProjectionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IProjectionFactory <L"Windows.UI.Xaml.Media.IProjectionFactory">
DEFINE_IIDX(IProjectionFactory, "C4F29CAB-60AD-4F24-BD27-9D69C3127C9A")

.comdef IProjectionFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIQuadraticBezierSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIQuadraticBezierSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IQuadraticBezierSegment <L"Windows.UI.Xaml.Media.IQuadraticBezierSegment">
DEFINE_IIDX(IQuadraticBezierSegment, "2C509A5B-BF18-455A-A078-914B5232D8AF")

.comdef IQuadraticBezierSegment : public IInspectable

    get_Point1		proc :ptr
    put_Point1		proc :Windows::Foundation::Point
    get_Point2		proc :ptr
    put_Point2		proc :Windows::Foundation::Point
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIQuadraticBezierSegmentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIQuadraticBezierSegmentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IQuadraticBezierSegmentStatics <L"Windows.UI.Xaml.Media.IQuadraticBezierSegmentStatics">
DEFINE_IIDX(IQuadraticBezierSegmentStatics, "69C78278-3C0B-4B4F-B7A2-F003DED41BB0")

.comdef IQuadraticBezierSegmentStatics : public IInspectable

    get_Point1Property	proc :ptr
    get_Point2Property	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRateChangedRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRateChangedRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IRateChangedRoutedEventArgs <L"Windows.UI.Xaml.Media.IRateChangedRoutedEventArgs">
DEFINE_IIDX(IRateChangedRoutedEventArgs, "9016AA6F-3CA8-4C80-8E2F-8851A68F131F")

.comdef IRateChangedRoutedEventArgs : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRectangleGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRectangleGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IRectangleGeometry <L"Windows.UI.Xaml.Media.IRectangleGeometry">
DEFINE_IIDX(IRectangleGeometry, "A25A1F58-C575-4196-91CF-9FDFB10445C3")

.comdef IRectangleGeometry : public IInspectable

    get_Rect		proc :ptr
    put_Rect		proc :Windows::Foundation::Rect
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRectangleGeometryStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRectangleGeometryStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IRectangleGeometryStatics <L"Windows.UI.Xaml.Media.IRectangleGeometryStatics">
DEFINE_IIDX(IRectangleGeometryStatics, "377F8DBA-7902-48E3-83BE-7C8002A6653C")

.comdef IRectangleGeometryStatics : public IInspectable

    get_RectProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRenderingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRenderingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IRenderingEventArgs <L"Windows.UI.Xaml.Media.IRenderingEventArgs">
DEFINE_IIDX(IRenderingEventArgs, "5BF7D30D-9748-4AED-8380-D7890EB776A0")

.comdef IRenderingEventArgs : public IInspectable

    get_RenderingTime	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRotateTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRotateTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IRotateTransform <L"Windows.UI.Xaml.Media.IRotateTransform">
DEFINE_IIDX(IRotateTransform, "688EA9B9-1E4E-4596-86E3-428B27334FAF")

.comdef IRotateTransform : public IInspectable

    get_CenterX		proc :ptr
    put_CenterX		proc :DOUBLE
    get_CenterY		proc :ptr
    put_CenterY		proc :DOUBLE
    get_Angle		proc :ptr
    put_Angle		proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRotateTransformStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIRotateTransformStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IRotateTransformStatics <L"Windows.UI.Xaml.Media.IRotateTransformStatics">
DEFINE_IIDX(IRotateTransformStatics, "A131EB8A-51A3-41B6-B9D3-A10E429054AB")

.comdef IRotateTransformStatics : public IInspectable

    get_CenterXProperty proc :ptr
    get_CenterYProperty proc :ptr
    get_AngleProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIScaleTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIScaleTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IScaleTransform <L"Windows.UI.Xaml.Media.IScaleTransform">
DEFINE_IIDX(IScaleTransform, "ED67F18D-936E-43AB-929A-E9CD0A511E52")

.comdef IScaleTransform : public IInspectable

    get_CenterX		proc :ptr
    put_CenterX		proc :DOUBLE
    get_CenterY		proc :ptr
    put_CenterY		proc :DOUBLE
    get_ScaleX		proc :ptr
    put_ScaleX		proc :DOUBLE
    get_ScaleY		proc :ptr
    put_ScaleY		proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIScaleTransformStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIScaleTransformStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IScaleTransformStatics <L"Windows.UI.Xaml.Media.IScaleTransformStatics">
DEFINE_IIDX(IScaleTransformStatics, "9D9436F4-40A7-46DD-975A-07D337CD852E")

.comdef IScaleTransformStatics : public IInspectable

    get_CenterXProperty proc :ptr
    get_CenterYProperty proc :ptr
    get_ScaleXProperty	proc :ptr
    get_ScaleYProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CISkewTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CISkewTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ISkewTransform <L"Windows.UI.Xaml.Media.ISkewTransform">
DEFINE_IIDX(ISkewTransform, "4E8A3B15-7A0F-4617-9E98-1E65BDC92115")

.comdef ISkewTransform : public IInspectable

    get_CenterX		proc :ptr
    put_CenterX		proc :DOUBLE
    get_CenterY		proc :ptr
    put_CenterY		proc :DOUBLE
    get_AngleX		proc :ptr
    put_AngleX		proc :DOUBLE
    get_AngleY		proc :ptr
    put_AngleY		proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CISkewTransformStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CISkewTransformStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ISkewTransformStatics <L"Windows.UI.Xaml.Media.ISkewTransformStatics">
DEFINE_IIDX(ISkewTransformStatics, "ECD11D73-5614-4B31-B6AF-BEAE10105624")

.comdef ISkewTransformStatics : public IInspectable

    get_CenterXProperty proc :ptr
    get_CenterYProperty proc :ptr
    get_AngleXProperty	proc :ptr
    get_AngleYProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CISolidColorBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CISolidColorBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ISolidColorBrush <L"Windows.UI.Xaml.Media.ISolidColorBrush">
DEFINE_IIDX(ISolidColorBrush, "9D850850-66F3-48DF-9A8F-824BD5E070AF")

.comdef ISolidColorBrush : public IInspectable

    get_Color		proc :ptr
    put_Color		proc :Windows::UI::Color
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CISolidColorBrushStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CISolidColorBrushStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ISolidColorBrushStatics <L"Windows.UI.Xaml.Media.ISolidColorBrushStatics">
DEFINE_IIDX(ISolidColorBrushStatics, "E1A65EFA-2B23-41BA-B9BA-7094EC8E4E9F")

.comdef ISolidColorBrushStatics : public IInspectable

    get_ColorProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CISolidColorBrushFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CISolidColorBrushFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ISolidColorBrushFactory <L"Windows.UI.Xaml.Media.ISolidColorBrushFactory">
DEFINE_IIDX(ISolidColorBrushFactory, "D935CE0C-86F5-4DA6-8A27-B1619EF7F92B")

.comdef ISolidColorBrushFactory : public IInspectable

    CreateInstanceWithColor proc :Windows::UI::Color, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITileBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITileBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITileBrush <L"Windows.UI.Xaml.Media.ITileBrush">
DEFINE_IIDX(ITileBrush, "C201CF06-CD84-48A5-9607-664D7361CD61")

.comdef ITileBrush : public IInspectable

    get_AlignmentX	proc :ptr
    put_AlignmentX	proc :Windows::UI::Xaml::Media::AlignmentX
    get_AlignmentY	proc :ptr
    put_AlignmentY	proc :Windows::UI::Xaml::Media::AlignmentY
    get_Stretch		proc :ptr
    put_Stretch		proc :Windows::UI::Xaml::Media::Stretch
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITileBrushStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITileBrushStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITileBrushStatics <L"Windows.UI.Xaml.Media.ITileBrushStatics">
DEFINE_IIDX(ITileBrushStatics, "3497C25B-B562-4E68-8435-2399F6EB94D5")

.comdef ITileBrushStatics : public IInspectable

    get_AlignmentXProperty proc :ptr
    get_AlignmentYProperty proc :ptr
    get_StretchProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITileBrushFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITileBrushFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITileBrushFactory <L"Windows.UI.Xaml.Media.ITileBrushFactory">
DEFINE_IIDX(ITileBrushFactory, "AA159F7C-ED6A-4FB3-B014-B5C7E379A4DE")

.comdef ITileBrushFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITimelineMarker_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITimelineMarker_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITimelineMarker <L"Windows.UI.Xaml.Media.ITimelineMarker">
DEFINE_IIDX(ITimelineMarker, "A68EF02D-45BA-4E50-8CAD-AAEA3A227AF5")

.comdef ITimelineMarker : public IInspectable

    get_Time		proc :ptr
    put_Time		proc :Windows::Foundation::TimeSpan
    get_Type		proc :ptr
    put_Type		proc :HSTRING
    get_Text		proc :ptr
    put_Text		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITimelineMarkerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITimelineMarkerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITimelineMarkerStatics <L"Windows.UI.Xaml.Media.ITimelineMarkerStatics">
DEFINE_IIDX(ITimelineMarkerStatics, "C4AEF0C6-16A3-484B-87F5-6528B8F04A47")

.comdef ITimelineMarkerStatics : public IInspectable

    get_TimeProperty	proc :ptr
    get_TypeProperty	proc :ptr
    get_TextProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITimelineMarkerRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITimelineMarkerRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITimelineMarkerRoutedEventArgs <L"Windows.UI.Xaml.Media.ITimelineMarkerRoutedEventArgs">
DEFINE_IIDX(ITimelineMarkerRoutedEventArgs, "7C3B3EF3-2C88-4D9C-99B6-46CDBD48D4C1")

.comdef ITimelineMarkerRoutedEventArgs : public IInspectable

    get_Marker		proc :ptr
    put_Marker		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITransform <L"Windows.UI.Xaml.Media.ITransform">
DEFINE_IIDX(ITransform, "4DF74078-BFD6-4ED1-9682-D2FD8BF2FE6F")

.comdef ITransform : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITransformFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITransformFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITransformFactory <L"Windows.UI.Xaml.Media.ITransformFactory">
DEFINE_IIDX(ITransformFactory, "1A955A66-7CF4-4320-B416-6181192FCC6D")

.comdef ITransformFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITransformGroup_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITransformGroup_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITransformGroup <L"Windows.UI.Xaml.Media.ITransformGroup">
DEFINE_IIDX(ITransformGroup, "63418CCC-8D2D-4737-B951-2AFCE1DDC4C4")

.comdef ITransformGroup : public IInspectable

    get_Children	proc :ptr
    put_Children	proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITransformGroupStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITransformGroupStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITransformGroupStatics <L"Windows.UI.Xaml.Media.ITransformGroupStatics">
DEFINE_IIDX(ITransformGroupStatics, "25312F2A-CFAB-4B24-9713-5BDEAD1929C0")

.comdef ITransformGroupStatics : public IInspectable

    get_ChildrenProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITranslateTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITranslateTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITranslateTransform <L"Windows.UI.Xaml.Media.ITranslateTransform">
DEFINE_IIDX(ITranslateTransform, "C975905C-3C36-4229-817B-178F64C0E113")

.comdef ITranslateTransform : public IInspectable

    get_X		proc :ptr
    put_X		proc :DOUBLE
    get_Y		proc :ptr
    put_Y		proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CITranslateTransformStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CITranslateTransformStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ITranslateTransformStatics <L"Windows.UI.Xaml.Media.ITranslateTransformStatics">
DEFINE_IIDX(ITranslateTransformStatics, "F419AA91-E042-4111-9C2F-D201304123DD")

.comdef ITranslateTransformStatics : public IInspectable

    get_XProperty	proc :ptr
    get_YProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIVisualTreeHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIVisualTreeHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IVisualTreeHelper <L"Windows.UI.Xaml.Media.IVisualTreeHelper">
DEFINE_IIDX(IVisualTreeHelper, "24B935E3-52C7-4141-8BAC-A73D06130569")

.comdef IVisualTreeHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIVisualTreeHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIVisualTreeHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IVisualTreeHelperStatics <L"Windows.UI.Xaml.Media.IVisualTreeHelperStatics">
DEFINE_IIDX(IVisualTreeHelperStatics, "E75758C4-D25D-4B1D-971F-596F17F12BAA")

.comdef IVisualTreeHelperStatics : public IInspectable

    FindElementsInHostCoordinatesPoint proc :Windows::Foundation::Point, :ptr, :ptr
    FindElementsInHostCoordinatesRect proc :Windows::Foundation::Rect, :ptr, :ptr
    FindAllElementsInHostCoordinatesPoint proc :Windows::Foundation::Point, :ptr, :boolean, :ptr
    FindAllElementsInHostCoordinatesRect proc :Windows::Foundation::Rect, :ptr, :boolean, :ptr
    GetChild		proc :ptr, :INT32, :ptr
    GetChildrenCount	proc :ptr, :ptr
    GetParent		proc :ptr, :ptr
    DisconnectChildrenRecursive proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CIVisualTreeHelperStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CIVisualTreeHelperStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_IVisualTreeHelperStatics2 <L"Windows.UI.Xaml.Media.IVisualTreeHelperStatics2">
DEFINE_IIDX(IVisualTreeHelperStatics2, "07BCD176-869F-44A7-8797-2103A4C3E47A")

.comdef IVisualTreeHelperStatics2 : public IInspectable

    GetOpenPopups	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CICompositionTarget_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CICompositionTarget_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ICompositionTarget <L"Windows.UI.Xaml.Media.ICompositionTarget">
DEFINE_IIDX(ICompositionTarget, "26CFBFF0-713C-4BEC-8803-E101F7B14ED3")

.comdef ICompositionTarget : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CICompositionTargetStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CICompositionTargetStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_ICompositionTargetStatics <L"Windows.UI.Xaml.Media.ICompositionTargetStatics">
DEFINE_IIDX(ICompositionTargetStatics, "2B1AF03D-1ED2-4B59-BD00-7594EE92832B")

.comdef ICompositionTargetStatics : public IInspectable

    add_Rendering	proc :ptr, :ptr
    remove_Rendering	proc :EventRegistrationToken
    add_SurfaceContentsLost proc :ptr, :ptr
    remove_SurfaceContentsLost proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_MatrixHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_MatrixHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_MatrixHelper <L"Windows.UI.Xaml.Media.MatrixHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Brush_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Brush_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Brush <L"Windows.UI.Xaml.Media.Brush">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_CacheMode_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_CacheMode_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_CacheMode <L"Windows.UI.Xaml.Media.CacheMode">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_BitmapCache_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_BitmapCache_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_BitmapCache <L"Windows.UI.Xaml.Media.BitmapCache">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_DoubleCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_DoubleCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_DoubleCollection <L"Windows.UI.Xaml.Media.DoubleCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_FontFamily_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_FontFamily_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_FontFamily <L"Windows.UI.Xaml.Media.FontFamily">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_GeneralTransform_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_GeneralTransform_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_GeneralTransform <L"Windows.UI.Xaml.Media.GeneralTransform">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Geometry_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Geometry_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Geometry <L"Windows.UI.Xaml.Media.Geometry">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_EllipseGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_EllipseGeometry_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_EllipseGeometry <L"Windows.UI.Xaml.Media.EllipseGeometry">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_GeometryCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_GeometryCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_GeometryCollection <L"Windows.UI.Xaml.Media.GeometryCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_GeometryGroup_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_GeometryGroup_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_GeometryGroup <L"Windows.UI.Xaml.Media.GeometryGroup">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_GradientStopCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_GradientStopCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_GradientStopCollection <L"Windows.UI.Xaml.Media.GradientStopCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_GradientBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_GradientBrush_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_GradientBrush <L"Windows.UI.Xaml.Media.GradientBrush">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_GradientStop_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_GradientStop_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_GradientStop <L"Windows.UI.Xaml.Media.GradientStop">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_ImageSource_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_ImageSource_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_ImageSource <L"Windows.UI.Xaml.Media.ImageSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_LinearGradientBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_LinearGradientBrush_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_LinearGradientBrush <L"Windows.UI.Xaml.Media.LinearGradientBrush">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_LineGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_LineGeometry_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_LineGeometry <L"Windows.UI.Xaml.Media.LineGeometry">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PathSegmentCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PathSegmentCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PathSegmentCollection <L"Windows.UI.Xaml.Media.PathSegmentCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PathFigure_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PathFigure_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PathFigure <L"Windows.UI.Xaml.Media.PathFigure">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PathFigureCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PathFigureCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PathFigureCollection <L"Windows.UI.Xaml.Media.PathFigureCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PathGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PathGeometry_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PathGeometry <L"Windows.UI.Xaml.Media.PathGeometry">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PathSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PathSegment_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PathSegment <L"Windows.UI.Xaml.Media.PathSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_ArcSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_ArcSegment_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_ArcSegment <L"Windows.UI.Xaml.Media.ArcSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_BezierSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_BezierSegment_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_BezierSegment <L"Windows.UI.Xaml.Media.BezierSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_LineSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_LineSegment_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_LineSegment <L"Windows.UI.Xaml.Media.LineSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PointCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PointCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PointCollection <L"Windows.UI.Xaml.Media.PointCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PolyBezierSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PolyBezierSegment_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PolyBezierSegment <L"Windows.UI.Xaml.Media.PolyBezierSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PolyLineSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PolyLineSegment_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PolyLineSegment <L"Windows.UI.Xaml.Media.PolyLineSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PolyQuadraticBezierSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PolyQuadraticBezierSegment_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PolyQuadraticBezierSegment <L"Windows.UI.Xaml.Media.PolyQuadraticBezierSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Projection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Projection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Projection <L"Windows.UI.Xaml.Media.Projection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Matrix3DProjection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Matrix3DProjection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Matrix3DProjection <L"Windows.UI.Xaml.Media.Matrix3DProjection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_PlaneProjection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_PlaneProjection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_PlaneProjection <L"Windows.UI.Xaml.Media.PlaneProjection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_QuadraticBezierSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_QuadraticBezierSegment_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_QuadraticBezierSegment <L"Windows.UI.Xaml.Media.QuadraticBezierSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_RateChangedRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_RateChangedRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_RateChangedRoutedEventArgs <L"Windows.UI.Xaml.Media.RateChangedRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_RectangleGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_RectangleGeometry_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_RectangleGeometry <L"Windows.UI.Xaml.Media.RectangleGeometry">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_RenderingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_RenderingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_RenderingEventArgs <L"Windows.UI.Xaml.Media.RenderingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_SolidColorBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_SolidColorBrush_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_SolidColorBrush <L"Windows.UI.Xaml.Media.SolidColorBrush">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_TileBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_TileBrush_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_TileBrush <L"Windows.UI.Xaml.Media.TileBrush">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_ImageBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_ImageBrush_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_ImageBrush <L"Windows.UI.Xaml.Media.ImageBrush">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_TimelineMarker_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_TimelineMarker_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_TimelineMarker <L"Windows.UI.Xaml.Media.TimelineMarker">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_TimelineMarkerCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_TimelineMarkerCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_TimelineMarkerCollection <L"Windows.UI.Xaml.Media.TimelineMarkerCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_TimelineMarkerRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_TimelineMarkerRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_TimelineMarkerRoutedEventArgs <L"Windows.UI.Xaml.Media.TimelineMarkerRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Transform_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Transform_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Transform <L"Windows.UI.Xaml.Media.Transform">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_CompositeTransform_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_CompositeTransform_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_CompositeTransform <L"Windows.UI.Xaml.Media.CompositeTransform">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_MatrixTransform_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_MatrixTransform_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_MatrixTransform <L"Windows.UI.Xaml.Media.MatrixTransform">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_RotateTransform_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_RotateTransform_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_RotateTransform <L"Windows.UI.Xaml.Media.RotateTransform">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_ScaleTransform_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_ScaleTransform_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_ScaleTransform <L"Windows.UI.Xaml.Media.ScaleTransform">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_SkewTransform_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_SkewTransform_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_SkewTransform <L"Windows.UI.Xaml.Media.SkewTransform">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_TransformCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_TransformCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_TransformCollection <L"Windows.UI.Xaml.Media.TransformCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_TransformGroup_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_TransformGroup_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_TransformGroup <L"Windows.UI.Xaml.Media.TransformGroup">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_TranslateTransform_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_TranslateTransform_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_TranslateTransform <L"Windows.UI.Xaml.Media.TranslateTransform">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_VisualTreeHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_VisualTreeHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_VisualTreeHelper <L"Windows.UI.Xaml.Media.VisualTreeHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_CompositionTarget_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_CompositionTarget_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_CompositionTarget <L"Windows.UI.Xaml.Media.CompositionTarget">
endif

endif
