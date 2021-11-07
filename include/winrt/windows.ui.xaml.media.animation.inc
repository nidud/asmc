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

ifndef __windows2Eui2Examl2Emedia2Eanimation_h__
define __windows2Eui2Examl2Emedia2Eanimation_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.UI.inc
include Windows.UI.Xaml.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame, "36a6440d-aa86-5bce-8df2-5de99206f151")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame, "1859dd08-582d-51dc-82a1-466111caf944")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame, "ca007bbd-84a1-512f-977f-9bd728e1e73f")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame, "5f1676da-a405-5b7a-baf1-968de4391fb7")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame, "69c69834-8951-54a7-a2ca-922bacf9fc70")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame, "9084a8e1-8f4d-5de3-b1c6-e5f05724caed")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame, "e55a65ad-e742-5f78-876b-64d1681fc9e2")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame, "b8de4dc9-8c69-55f3-af58-040f1319649c")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline, "b0c22c25-ae1a-5326-bf81-394246cc3076")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline, "a122a346-e6d5-5c54-857d-038e60f5d9c1")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition, "0f149913-d622-5dde-b6e3-7835c2ab54b7")

.comdef __FIIterator_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition, "feb51398-4fdb-5112-8a9b-6a8786ca01ce")

.comdef __FIIterable_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame, "8d66a3ca-480c-5a76-98a2-9036c03ed7bd")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame, "c12407b6-145f-5420-9e16-d0a20bf13176")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame, "19130523-0862-5631-bc2e-097614b38b6d")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame, "b366e321-df42-500b-8ada-99854f6406ff")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline, "541af22b-280b-5276-bfcb-3e60a157d62c")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition, "43b475a1-3811-5992-be44-ab41a825d355")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame, "92d24fb8-af54-5180-9888-5756566a13ff")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CColorKeyFrame : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame, "d7cbde22-86bf-572f-8473-079d15076c3e")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CDoubleKeyFrame : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame, "5f733d3f-72a6-5303-9727-2b03eae7dd4c")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CObjectKeyFrame : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame, "b17e26de-9cd7-5456-bee0-49882a87f945")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CPointKeyFrame : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline, "2005c7f9-c7d7-521b-a81c-2c9dad77a9e8")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTimeline : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition, "e798571f-7e3e-5e1a-aa55-cbc93b83f821")

.comdef __FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition : public IInspectable

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

define InterfaceName_Windows_UI_Xaml_Media_Animation_IKeyTimeHelper <L"Windows.UI.Xaml.Media.Animation.IKeyTimeHelper">

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Media
.namespace Animation

.enum ClockState {
    ClockState_Active	= 0,
    ClockState_Filling	= 1,
    ClockState_Stopped	= 2
    }

.enum EasingMode {
    EasingMode_EaseOut	= 0,
    EasingMode_EaseIn	= 1,
    EasingMode_EaseInOut	= 2
    }

.enum FillBehavior {
    FillBehavior_HoldEnd	= 0,
    FillBehavior_Stop	= 1
    }

.enum RepeatBehaviorType {
    RepeatBehaviorType_Count	= 0,
    RepeatBehaviorType_Duration = 1,
    RepeatBehaviorType_Forever	= 2
    }

.template KeyTime
    TimeSpan		Windows::Foundation::TimeSpan <>
   .ends

.template RepeatBehavior
    Count		DOUBLE ?
    Duration		Windows::Foundation::TimeSpan <>
    Type		Windows::UI::Xaml::Media::Animation::RepeatBehaviorType ?
   .ends

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIKeyTimeHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIKeyTimeHelper_INTERFACE_DEFINED__
DEFINE_IIDX(IKeyTimeHelper, "3643E480-4823-466A-ABE5-5E79C8ED77ED")

.comdef IKeyTimeHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIKeyTimeHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIKeyTimeHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IKeyTimeHelperStatics <L"Windows.UI.Xaml.Media.Animation.IKeyTimeHelperStatics">
DEFINE_IIDX(IKeyTimeHelperStatics, "7FA2612C-22A9-45E9-9AF7-C7416EFFF7A5")

.comdef IKeyTimeHelperStatics : public IInspectable

    FromTimeSpan	proc :Windows::Foundation::TimeSpan, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepeatBehaviorHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepeatBehaviorHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IRepeatBehaviorHelper <L"Windows.UI.Xaml.Media.Animation.IRepeatBehaviorHelper">
DEFINE_IIDX(IRepeatBehaviorHelper, "6863AB72-4997-47F9-87AD-37EFB75993EA")

.comdef IRepeatBehaviorHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepeatBehaviorHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepeatBehaviorHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IRepeatBehaviorHelperStatics <L"Windows.UI.Xaml.Media.Animation.IRepeatBehaviorHelperStatics">
DEFINE_IIDX(IRepeatBehaviorHelperStatics, "7A795033-79F3-4DD9-B267-9CF50FB51F84")

.comdef IRepeatBehaviorHelperStatics : public IInspectable

    get_Forever		proc :ptr
    FromCount		proc :DOUBLE, :ptr
    FromDuration	proc :Windows::Foundation::TimeSpan, :ptr
    GetHasCount		proc :Windows::UI::Xaml::Media::Animation::RepeatBehavior, :ptr
    GetHasDuration	proc :Windows::UI::Xaml::Media::Animation::RepeatBehavior, :ptr
    Equals		proc :Windows::UI::Xaml::Media::Animation::RepeatBehavior, :Windows::UI::Xaml::Media::Animation::RepeatBehavior, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIAddDeleteThemeTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIAddDeleteThemeTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IAddDeleteThemeTransition <L"Windows.UI.Xaml.Media.Animation.IAddDeleteThemeTransition">
DEFINE_IIDX(IAddDeleteThemeTransition, "ADEC852E-4424-4DAB-99C1-3A04E36A3C48")

.comdef IAddDeleteThemeTransition : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBackEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBackEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IBackEase <L"Windows.UI.Xaml.Media.Animation.IBackEase">
DEFINE_IIDX(IBackEase, "E47796E7-F805-4A8F-81C9-38E6472CAA94")

.comdef IBackEase : public IInspectable

    get_Amplitude	proc :ptr
    put_Amplitude	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBackEaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBackEaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IBackEaseStatics <L"Windows.UI.Xaml.Media.Animation.IBackEaseStatics">
DEFINE_IIDX(IBackEaseStatics, "3C70A2FF-A0A0-4786-926C-22321F8F25B7")

.comdef IBackEaseStatics : public IInspectable

    get_AmplitudeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBeginStoryboard_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBeginStoryboard_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IBeginStoryboard <L"Windows.UI.Xaml.Media.Animation.IBeginStoryboard">
DEFINE_IIDX(IBeginStoryboard, "64189FCD-49EC-4E52-A6F6-55324C921053")

.comdef IBeginStoryboard : public IInspectable

    get_Storyboard	proc :ptr
    put_Storyboard	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBeginStoryboardStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBeginStoryboardStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IBeginStoryboardStatics <L"Windows.UI.Xaml.Media.Animation.IBeginStoryboardStatics">
DEFINE_IIDX(IBeginStoryboardStatics, "12CFF18C-AA91-4C4A-B82F-DF34FC57F94B")

.comdef IBeginStoryboardStatics : public IInspectable

    get_StoryboardProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBounceEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBounceEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IBounceEase <L"Windows.UI.Xaml.Media.Animation.IBounceEase">
DEFINE_IIDX(IBounceEase, "2BF1464E-FC71-47ED-85A1-3BA9577718B4")

.comdef IBounceEase : public IInspectable

    get_Bounces		proc :ptr
    put_Bounces		proc :INT32
    get_Bounciness	proc :ptr
    put_Bounciness	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBounceEaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIBounceEaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IBounceEaseStatics <L"Windows.UI.Xaml.Media.Animation.IBounceEaseStatics">
DEFINE_IIDX(IBounceEaseStatics, "C0701DA2-4F73-41C9-B2CB-2EA3105107FF")

.comdef IBounceEaseStatics : public IInspectable

    get_BouncesProperty proc :ptr
    get_BouncinessProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CICircleEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CICircleEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ICircleEase <L"Windows.UI.Xaml.Media.Animation.ICircleEase">
DEFINE_IIDX(ICircleEase, "53A3BDB2-9177-4E6E-A043-5082D889AB1F")

.comdef ICircleEase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IColorAnimation <L"Windows.UI.Xaml.Media.Animation.IColorAnimation">
DEFINE_IIDX(IColorAnimation, "B8AE8A15-0F63-4694-9467-BDAFAC1253EA")

.comdef IColorAnimation : public IInspectable

    get_From		proc :ptr
    put_From		proc :ptr
    get_To		proc :ptr
    put_To		proc :ptr
    get_By		proc :ptr
    put_By		proc :ptr
    get_EasingFunction	proc :ptr
    put_EasingFunction	proc :ptr
    get_EnableDependentAnimation proc :ptr
    put_EnableDependentAnimation proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IColorAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IColorAnimationStatics">
DEFINE_IIDX(IColorAnimationStatics, "55EAF6E2-87E3-4F48-958F-855B2F9EA9EC")

.comdef IColorAnimationStatics : public IInspectable

    get_FromProperty	proc :ptr
    get_ToProperty	proc :ptr
    get_ByProperty	proc :ptr
    get_EasingFunctionProperty proc :ptr
    get_EnableDependentAnimationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorAnimationUsingKeyFrames_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorAnimationUsingKeyFrames_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IColorAnimationUsingKeyFrames <L"Windows.UI.Xaml.Media.Animation.IColorAnimationUsingKeyFrames">
DEFINE_IIDX(IColorAnimationUsingKeyFrames, "F5C82640-13C3-42AA-9AE2-7E6B51C92F95")

.comdef IColorAnimationUsingKeyFrames : public IInspectable

    get_KeyFrames	proc :ptr
    get_EnableDependentAnimation proc :ptr
    put_EnableDependentAnimation proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorAnimationUsingKeyFramesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorAnimationUsingKeyFramesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IColorAnimationUsingKeyFramesStatics <L"Windows.UI.Xaml.Media.Animation.IColorAnimationUsingKeyFramesStatics">
DEFINE_IIDX(IColorAnimationUsingKeyFramesStatics, "B4723CDC-96E9-48F9-8D92-9B648B2F1CC6")

.comdef IColorAnimationUsingKeyFramesStatics : public IInspectable

    get_EnableDependentAnimationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.IColorKeyFrame">
DEFINE_IIDX(IColorKeyFrame, "B51D82D9-0910-4589-A284-B0C9205858E9")

.comdef IColorKeyFrame : public IInspectable

    get_Value		proc :ptr
    put_Value		proc :Windows::UI::Color
    get_KeyTime		proc :ptr
    put_KeyTime		proc :Windows::UI::Xaml::Media::Animation::KeyTime
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IColorKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.IColorKeyFrameStatics">
DEFINE_IIDX(IColorKeyFrameStatics, "C043AE99-210C-430F-9DA5-DF1082692055")

.comdef IColorKeyFrameStatics : public IInspectable

    get_ValueProperty	proc :ptr
    get_KeyTimeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorKeyFrameFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIColorKeyFrameFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IColorKeyFrameFactory <L"Windows.UI.Xaml.Media.Animation.IColorKeyFrameFactory">
DEFINE_IIDX(IColorKeyFrameFactory, "769BD88A-9CFB-4A7D-96C4-A1E7DE6FDB4B")

.comdef IColorKeyFrameFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIContentThemeTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIContentThemeTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IContentThemeTransition <L"Windows.UI.Xaml.Media.Animation.IContentThemeTransition">
DEFINE_IIDX(IContentThemeTransition, "F66FC5C3-5915-437D-8E3B-ADF8E7F0AB57")

.comdef IContentThemeTransition : public IInspectable

    get_HorizontalOffset proc :ptr
    put_HorizontalOffset proc :DOUBLE
    get_VerticalOffset	proc :ptr
    put_VerticalOffset	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIContentThemeTransitionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIContentThemeTransitionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IContentThemeTransitionStatics <L"Windows.UI.Xaml.Media.Animation.IContentThemeTransitionStatics">
DEFINE_IIDX(IContentThemeTransitionStatics, "0E8EE385-9A42-4459-AFA9-337DC41E1587")

.comdef IContentThemeTransitionStatics : public IInspectable

    get_HorizontalOffsetProperty proc :ptr
    get_VerticalOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CICubicEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CICubicEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ICubicEase <L"Windows.UI.Xaml.Media.Animation.ICubicEase">
DEFINE_IIDX(ICubicEase, "1B94FC76-DAD7-4354-B1A2-7969FBF6A70D")

.comdef ICubicEase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDiscreteColorKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDiscreteColorKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDiscreteColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.IDiscreteColorKeyFrame">
DEFINE_IIDX(IDiscreteColorKeyFrame, "230C08F4-E062-4CB1-8E2A-14093D73ED8C")

.comdef IDiscreteColorKeyFrame : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDiscreteDoubleKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDiscreteDoubleKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDiscreteDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.IDiscreteDoubleKeyFrame">
DEFINE_IIDX(IDiscreteDoubleKeyFrame, "F5F51F3A-AD11-49CE-8E1C-08FDF1447446")

.comdef IDiscreteDoubleKeyFrame : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDiscreteObjectKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDiscreteObjectKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDiscreteObjectKeyFrame <L"Windows.UI.Xaml.Media.Animation.IDiscreteObjectKeyFrame">
DEFINE_IIDX(IDiscreteObjectKeyFrame, "C7DCDE89-F12D-4A9C-8199-E7A9ECE3A473")

.comdef IDiscreteObjectKeyFrame : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDiscretePointKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDiscretePointKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDiscretePointKeyFrame <L"Windows.UI.Xaml.Media.Animation.IDiscretePointKeyFrame">
DEFINE_IIDX(IDiscretePointKeyFrame, "E0A9070D-4C42-4A90-983A-75F5A83A2FBE")

.comdef IDiscretePointKeyFrame : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDoubleAnimation <L"Windows.UI.Xaml.Media.Animation.IDoubleAnimation">
DEFINE_IIDX(IDoubleAnimation, "7E9F3D59-0F07-4BC9-977D-03763FF8154F")

.comdef IDoubleAnimation : public IInspectable

    get_From		proc :ptr
    put_From		proc :ptr
    get_To		proc :ptr
    put_To		proc :ptr
    get_By		proc :ptr
    put_By		proc :ptr
    get_EasingFunction	proc :ptr
    put_EasingFunction	proc :ptr
    get_EnableDependentAnimation proc :ptr
    put_EnableDependentAnimation proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDoubleAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IDoubleAnimationStatics">
DEFINE_IIDX(IDoubleAnimationStatics, "E27A935D-F111-43B7-B824-832B58D7786B")

.comdef IDoubleAnimationStatics : public IInspectable

    get_FromProperty	proc :ptr
    get_ToProperty	proc :ptr
    get_ByProperty	proc :ptr
    get_EasingFunctionProperty proc :ptr
    get_EnableDependentAnimationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleAnimationUsingKeyFrames_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleAnimationUsingKeyFrames_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDoubleAnimationUsingKeyFrames <L"Windows.UI.Xaml.Media.Animation.IDoubleAnimationUsingKeyFrames">
DEFINE_IIDX(IDoubleAnimationUsingKeyFrames, "4FEE628F-BFEE-4F75-83C2-A93B39488473")

.comdef IDoubleAnimationUsingKeyFrames : public IInspectable

    get_KeyFrames	proc :ptr
    get_EnableDependentAnimation proc :ptr
    put_EnableDependentAnimation proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleAnimationUsingKeyFramesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleAnimationUsingKeyFramesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDoubleAnimationUsingKeyFramesStatics <L"Windows.UI.Xaml.Media.Animation.IDoubleAnimationUsingKeyFramesStatics">
DEFINE_IIDX(IDoubleAnimationUsingKeyFramesStatics, "109BF2F6-C60F-49AA-ABF6-F696D492116B")

.comdef IDoubleAnimationUsingKeyFramesStatics : public IInspectable

    get_EnableDependentAnimationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.IDoubleKeyFrame">
DEFINE_IIDX(IDoubleKeyFrame, "674456FD-E81E-4F4E-B4AD-0ACFED9ECD68")

.comdef IDoubleKeyFrame : public IInspectable

    get_Value		proc :ptr
    put_Value		proc :DOUBLE
    get_KeyTime		proc :ptr
    put_KeyTime		proc :Windows::UI::Xaml::Media::Animation::KeyTime
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDoubleKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.IDoubleKeyFrameStatics">
DEFINE_IIDX(IDoubleKeyFrameStatics, "324641B0-7D37-427A-ADEB-43F38BB61A4D")

.comdef IDoubleKeyFrameStatics : public IInspectable

    get_ValueProperty	proc :ptr
    get_KeyTimeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleKeyFrameFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDoubleKeyFrameFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDoubleKeyFrameFactory <L"Windows.UI.Xaml.Media.Animation.IDoubleKeyFrameFactory">
DEFINE_IIDX(IDoubleKeyFrameFactory, "AC97DEC3-7538-40B9-B152-696F7FBF4722")

.comdef IDoubleKeyFrameFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDragItemThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDragItemThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDragItemThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IDragItemThemeAnimation">
DEFINE_IIDX(IDragItemThemeAnimation, "0C7D5DB5-7ED6-4949-B4E6-A78C9F4F978D")

.comdef IDragItemThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDragItemThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDragItemThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDragItemThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IDragItemThemeAnimationStatics">
DEFINE_IIDX(IDragItemThemeAnimationStatics, "6218B9F5-013A-4FB1-86FC-92BC4E8D0241")

.comdef IDragItemThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDragOverThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDragOverThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDragOverThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IDragOverThemeAnimation">
DEFINE_IIDX(IDragOverThemeAnimation, "72F762F7-7E51-4A6B-B937-DC4B4C1C5458")

.comdef IDragOverThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
    get_ToOffset	proc :ptr
    put_ToOffset	proc :DOUBLE
    get_Direction	proc :ptr
    put_Direction	proc :Windows::UI::Xaml::Controls::Primitives::AnimationDirection
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDragOverThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDragOverThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDragOverThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IDragOverThemeAnimationStatics">
DEFINE_IIDX(IDragOverThemeAnimationStatics, "146FFE57-3C9D-41D9-A5FF-8D7239516810")

.comdef IDragOverThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
    get_ToOffsetProperty proc :ptr
    get_DirectionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDropTargetItemThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDropTargetItemThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDropTargetItemThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IDropTargetItemThemeAnimation">
DEFINE_IIDX(IDropTargetItemThemeAnimation, "1881C968-1824-462B-87E8-C357212B977B")

.comdef IDropTargetItemThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDropTargetItemThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIDropTargetItemThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IDropTargetItemThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IDropTargetItemThemeAnimationStatics">
DEFINE_IIDX(IDropTargetItemThemeAnimationStatics, "AE80F486-2E56-4513-BF18-D77470164AE5")

.comdef IDropTargetItemThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingColorKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingColorKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.IEasingColorKeyFrame">
DEFINE_IIDX(IEasingColorKeyFrame, "C733D630-F4B9-4934-9BDD-27AC5ED1CFD8")

.comdef IEasingColorKeyFrame : public IInspectable

    get_EasingFunction	proc :ptr
    put_EasingFunction	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingColorKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingColorKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingColorKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.IEasingColorKeyFrameStatics">
DEFINE_IIDX(IEasingColorKeyFrameStatics, "6F3837FC-8E3D-4522-9B0F-003DB8609851")

.comdef IEasingColorKeyFrameStatics : public IInspectable

    get_EasingFunctionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingDoubleKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingDoubleKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.IEasingDoubleKeyFrame">
DEFINE_IIDX(IEasingDoubleKeyFrame, "965ADB8D-9A54-4108-B4FF-B5A5212CB338")

.comdef IEasingDoubleKeyFrame : public IInspectable

    get_EasingFunction	proc :ptr
    put_EasingFunction	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingDoubleKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingDoubleKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingDoubleKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.IEasingDoubleKeyFrameStatics">
DEFINE_IIDX(IEasingDoubleKeyFrameStatics, "C8D3D845-DBAE-4E5B-8B84-D9537398E5B1")

.comdef IEasingDoubleKeyFrameStatics : public IInspectable

    get_EasingFunctionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingFunctionBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingFunctionBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingFunctionBase <L"Windows.UI.Xaml.Media.Animation.IEasingFunctionBase">
DEFINE_IIDX(IEasingFunctionBase, "C108383F-2C02-4151-8ECD-68DDAA3F0D9B")

.comdef IEasingFunctionBase : public IInspectable

    get_EasingMode	proc :ptr
    put_EasingMode	proc :Windows::UI::Xaml::Media::Animation::EasingMode
    Ease		proc :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingFunctionBaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingFunctionBaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingFunctionBaseStatics <L"Windows.UI.Xaml.Media.Animation.IEasingFunctionBaseStatics">
DEFINE_IIDX(IEasingFunctionBaseStatics, "2A5031AA-2C50-4A1D-BB04-D75E07B71548")

.comdef IEasingFunctionBaseStatics : public IInspectable

    get_EasingModeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingFunctionBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingFunctionBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingFunctionBaseFactory <L"Windows.UI.Xaml.Media.Animation.IEasingFunctionBaseFactory">
DEFINE_IIDX(IEasingFunctionBaseFactory, "1830FE6A-F01B-43E0-B61F-B452A1C66FD2")

.comdef IEasingFunctionBaseFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingPointKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingPointKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingPointKeyFrame <L"Windows.UI.Xaml.Media.Animation.IEasingPointKeyFrame">
DEFINE_IIDX(IEasingPointKeyFrame, "B3C91380-6868-4225-A70B-3981CC0B2947")

.comdef IEasingPointKeyFrame : public IInspectable

    get_EasingFunction	proc :ptr
    put_EasingFunction	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingPointKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEasingPointKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEasingPointKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.IEasingPointKeyFrameStatics">
DEFINE_IIDX(IEasingPointKeyFrameStatics, "E22DBFC4-080C-402C-A6B5-F48D0A98116B")

.comdef IEasingPointKeyFrameStatics : public IInspectable

    get_EasingFunctionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEdgeUIThemeTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEdgeUIThemeTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEdgeUIThemeTransition <L"Windows.UI.Xaml.Media.Animation.IEdgeUIThemeTransition">
DEFINE_IIDX(IEdgeUIThemeTransition, "5C86C19B-49D7-19EC-CF19-83A73C6DE75E")

.comdef IEdgeUIThemeTransition : public IInspectable

    get_Edge		proc :ptr
    put_Edge		proc :Windows::UI::Xaml::Controls::Primitives::EdgeTransitionLocation
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEdgeUIThemeTransitionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEdgeUIThemeTransitionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEdgeUIThemeTransitionStatics <L"Windows.UI.Xaml.Media.Animation.IEdgeUIThemeTransitionStatics">
DEFINE_IIDX(IEdgeUIThemeTransitionStatics, "16A2B13B-4705-302B-27C6-2AAC92F645AC")

.comdef IEdgeUIThemeTransitionStatics : public IInspectable

    get_EdgeProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIElasticEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIElasticEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IElasticEase <L"Windows.UI.Xaml.Media.Animation.IElasticEase">
DEFINE_IIDX(IElasticEase, "EF5BA58C-B0B6-4A6C-9CA8-FB4233F12459")

.comdef IElasticEase : public IInspectable

    get_Oscillations	proc :ptr
    put_Oscillations	proc :INT32
    get_Springiness	proc :ptr
    put_Springiness	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIElasticEaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIElasticEaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IElasticEaseStatics <L"Windows.UI.Xaml.Media.Animation.IElasticEaseStatics">
DEFINE_IIDX(IElasticEaseStatics, "A9F566EC-FE9C-4B2B-8E52-BB785D562185")

.comdef IElasticEaseStatics : public IInspectable

    get_OscillationsProperty proc :ptr
    get_SpringinessProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEntranceThemeTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEntranceThemeTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEntranceThemeTransition <L"Windows.UI.Xaml.Media.Animation.IEntranceThemeTransition">
DEFINE_IIDX(IEntranceThemeTransition, "07698C09-A8E3-419A-A01D-7410A0AE8EC8")

.comdef IEntranceThemeTransition : public IInspectable

    get_FromHorizontalOffset proc :ptr
    put_FromHorizontalOffset proc :DOUBLE
    get_FromVerticalOffset proc :ptr
    put_FromVerticalOffset proc :DOUBLE
    get_IsStaggeringEnabled proc :ptr
    put_IsStaggeringEnabled proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEntranceThemeTransitionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIEntranceThemeTransitionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IEntranceThemeTransitionStatics <L"Windows.UI.Xaml.Media.Animation.IEntranceThemeTransitionStatics">
DEFINE_IIDX(IEntranceThemeTransitionStatics, "37CC0577-FF98-4AED-B86E-5EC23702F877")

.comdef IEntranceThemeTransitionStatics : public IInspectable

    get_FromHorizontalOffsetProperty proc :ptr
    get_FromVerticalOffsetProperty proc :ptr
    get_IsStaggeringEnabledProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIExponentialEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIExponentialEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IExponentialEase <L"Windows.UI.Xaml.Media.Animation.IExponentialEase">
DEFINE_IIDX(IExponentialEase, "7CB9E41D-F0BB-4BCA-9DA5-9BA3A11734C4")

.comdef IExponentialEase : public IInspectable

    get_Exponent	proc :ptr
    put_Exponent	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIExponentialEaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIExponentialEaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IExponentialEaseStatics <L"Windows.UI.Xaml.Media.Animation.IExponentialEaseStatics">
DEFINE_IIDX(IExponentialEaseStatics, "F37EE7E3-A761-4352-9AD6-70794567581A")

.comdef IExponentialEaseStatics : public IInspectable

    get_ExponentProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIFadeInThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIFadeInThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IFadeInThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IFadeInThemeAnimation">
DEFINE_IIDX(IFadeInThemeAnimation, "6D4BC8F5-A918-4477-8078-554C68812AB8")

.comdef IFadeInThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIFadeInThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIFadeInThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IFadeInThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IFadeInThemeAnimationStatics">
DEFINE_IIDX(IFadeInThemeAnimationStatics, "7F0117E1-BEA9-4923-B23A-0DDF4D7B8737")

.comdef IFadeInThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIFadeOutThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIFadeOutThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IFadeOutThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IFadeOutThemeAnimation">
DEFINE_IIDX(IFadeOutThemeAnimation, "89276BA9-FFD4-45B6-9B9A-CED48951E712")

.comdef IFadeOutThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIFadeOutThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIFadeOutThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IFadeOutThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IFadeOutThemeAnimationStatics">
DEFINE_IIDX(IFadeOutThemeAnimationStatics, "FE17A81A-4168-4F68-A28C-E5DD98CF680F")

.comdef IFadeOutThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIKeySpline_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIKeySpline_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IKeySpline <L"Windows.UI.Xaml.Media.Animation.IKeySpline">
DEFINE_IIDX(IKeySpline, "77A163BB-D5CA-4A32-BA0B-7DFF988E58A0")

.comdef IKeySpline : public IInspectable

    get_ControlPoint1	proc :ptr
    put_ControlPoint1	proc :Windows::Foundation::Point
    get_ControlPoint2	proc :ptr
    put_ControlPoint2	proc :Windows::Foundation::Point
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CILinearColorKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CILinearColorKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ILinearColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.ILinearColorKeyFrame">
DEFINE_IIDX(ILinearColorKeyFrame, "66FDB6EF-AC81-4611-B1D2-61F545983F03")

.comdef ILinearColorKeyFrame : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CILinearDoubleKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CILinearDoubleKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ILinearDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.ILinearDoubleKeyFrame">
DEFINE_IIDX(ILinearDoubleKeyFrame, "8EFDF265-9A7B-431D-8F0C-14C56B5EA4D9")

.comdef ILinearDoubleKeyFrame : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CILinearPointKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CILinearPointKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ILinearPointKeyFrame <L"Windows.UI.Xaml.Media.Animation.ILinearPointKeyFrame">
DEFINE_IIDX(ILinearPointKeyFrame, "E7C9B8EF-AF24-49EE-84F1-A86600A4E319")

.comdef ILinearPointKeyFrame : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_INavigationTransitionInfo <L"Windows.UI.Xaml.Media.Animation.INavigationTransitionInfo">
DEFINE_IIDX(INavigationTransitionInfo, "A9B05091-AE4A-4372-8625-21B7A8B98CA4")

.comdef INavigationTransitionInfo : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfoOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfoOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_INavigationTransitionInfoOverrides <L"Windows.UI.Xaml.Media.Animation.INavigationTransitionInfoOverrides">
DEFINE_IIDX(INavigationTransitionInfoOverrides, "D9517E6A-A9D0-4BF7-9DB0-4633A69DAFF2")

.comdef INavigationTransitionInfoOverrides : public IInspectable

    GetNavigationStateCore proc :ptr
    SetNavigationStateCore proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfoFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfoFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_INavigationTransitionInfoFactory <L"Windows.UI.Xaml.Media.Animation.INavigationTransitionInfoFactory">
DEFINE_IIDX(INavigationTransitionInfoFactory, "EDF4F8D5-AF63-4FAB-9D4A-87927F82DD6B")

.comdef INavigationTransitionInfoFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectAnimationUsingKeyFrames_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectAnimationUsingKeyFrames_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IObjectAnimationUsingKeyFrames <L"Windows.UI.Xaml.Media.Animation.IObjectAnimationUsingKeyFrames">
DEFINE_IIDX(IObjectAnimationUsingKeyFrames, "334A2D92-B74A-4C64-B9A6-58BCFA314F22")

.comdef IObjectAnimationUsingKeyFrames : public IInspectable

    get_KeyFrames	proc :ptr
    get_EnableDependentAnimation proc :ptr
    put_EnableDependentAnimation proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectAnimationUsingKeyFramesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectAnimationUsingKeyFramesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IObjectAnimationUsingKeyFramesStatics <L"Windows.UI.Xaml.Media.Animation.IObjectAnimationUsingKeyFramesStatics">
DEFINE_IIDX(IObjectAnimationUsingKeyFramesStatics, "EB736182-6AF1-49A3-97B6-783ED97400FE")

.comdef IObjectAnimationUsingKeyFramesStatics : public IInspectable

    get_EnableDependentAnimationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IObjectKeyFrame <L"Windows.UI.Xaml.Media.Animation.IObjectKeyFrame">
DEFINE_IIDX(IObjectKeyFrame, "9852A851-8593-48EE-A6A4-D5D4720F029A")

.comdef IObjectKeyFrame : public IInspectable

    get_Value		proc :ptr
    put_Value		proc :ptr
    get_KeyTime		proc :ptr
    put_KeyTime		proc :Windows::UI::Xaml::Media::Animation::KeyTime
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IObjectKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.IObjectKeyFrameStatics">
DEFINE_IIDX(IObjectKeyFrameStatics, "2CD6AB00-5319-4286-8EED-4E755EA0CF9C")

.comdef IObjectKeyFrameStatics : public IInspectable

    get_ValueProperty	proc :ptr
    get_KeyTimeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectKeyFrameFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIObjectKeyFrameFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IObjectKeyFrameFactory <L"Windows.UI.Xaml.Media.Animation.IObjectKeyFrameFactory">
DEFINE_IIDX(IObjectKeyFrameFactory, "1626143E-3E6D-44D8-9B9A-04AEA70F8492")

.comdef IObjectKeyFrameFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPaneThemeTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPaneThemeTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPaneThemeTransition <L"Windows.UI.Xaml.Media.Animation.IPaneThemeTransition">
DEFINE_IIDX(IPaneThemeTransition, "4708EB8E-4BFC-EE46-D4F9-708DEF3FBB2B")

.comdef IPaneThemeTransition : public IInspectable

    get_Edge		proc :ptr
    put_Edge		proc :Windows::UI::Xaml::Controls::Primitives::EdgeTransitionLocation
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPaneThemeTransitionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPaneThemeTransitionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPaneThemeTransitionStatics <L"Windows.UI.Xaml.Media.Animation.IPaneThemeTransitionStatics">
DEFINE_IIDX(IPaneThemeTransitionStatics, "316B382F-4BE4-1797-B45C-CD900BBE0CAA")

.comdef IPaneThemeTransitionStatics : public IInspectable

    get_EdgeProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointAnimation <L"Windows.UI.Xaml.Media.Animation.IPointAnimation">
DEFINE_IIDX(IPointAnimation, "30F04312-7726-4F88-B8E2-2FA54518963B")

.comdef IPointAnimation : public IInspectable

    get_From		proc :ptr
    put_From		proc :ptr
    get_To		proc :ptr
    put_To		proc :ptr
    get_By		proc :ptr
    put_By		proc :ptr
    get_EasingFunction	proc :ptr
    put_EasingFunction	proc :ptr
    get_EnableDependentAnimation proc :ptr
    put_EnableDependentAnimation proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IPointAnimationStatics">
DEFINE_IIDX(IPointAnimationStatics, "2F99B356-E737-408B-A0FD-327826D32255")

.comdef IPointAnimationStatics : public IInspectable

    get_FromProperty	proc :ptr
    get_ToProperty	proc :ptr
    get_ByProperty	proc :ptr
    get_EasingFunctionProperty proc :ptr
    get_EnableDependentAnimationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointAnimationUsingKeyFrames_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointAnimationUsingKeyFrames_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointAnimationUsingKeyFrames <L"Windows.UI.Xaml.Media.Animation.IPointAnimationUsingKeyFrames">
DEFINE_IIDX(IPointAnimationUsingKeyFrames, "9B944F72-446A-41D0-A129-41A620F4595D")

.comdef IPointAnimationUsingKeyFrames : public IInspectable

    get_KeyFrames	proc :ptr
    get_EnableDependentAnimation proc :ptr
    put_EnableDependentAnimation proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointAnimationUsingKeyFramesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointAnimationUsingKeyFramesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointAnimationUsingKeyFramesStatics <L"Windows.UI.Xaml.Media.Animation.IPointAnimationUsingKeyFramesStatics">
DEFINE_IIDX(IPointAnimationUsingKeyFramesStatics, "5F454C87-2390-46EA-BAA7-762F4BC30D04")

.comdef IPointAnimationUsingKeyFramesStatics : public IInspectable

    get_EnableDependentAnimationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointerDownThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointerDownThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointerDownThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IPointerDownThemeAnimation">
DEFINE_IIDX(IPointerDownThemeAnimation, "B58E714E-C49D-4788-A233-0AE85D99DD5A")

.comdef IPointerDownThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointerDownThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointerDownThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointerDownThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IPointerDownThemeAnimationStatics">
DEFINE_IIDX(IPointerDownThemeAnimationStatics, "63A7CB7B-6D46-4494-B94A-E72F3B492A61")

.comdef IPointerDownThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointerUpThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointerUpThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointerUpThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IPointerUpThemeAnimation">
DEFINE_IIDX(IPointerUpThemeAnimation, "E9E9D07D-6340-4828-AD12-690694B9910B")

.comdef IPointerUpThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointerUpThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointerUpThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointerUpThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IPointerUpThemeAnimationStatics">
DEFINE_IIDX(IPointerUpThemeAnimationStatics, "7C618F9C-7992-4139-8BFC-0883B9727A7E")

.comdef IPointerUpThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointKeyFrame <L"Windows.UI.Xaml.Media.Animation.IPointKeyFrame">
DEFINE_IIDX(IPointKeyFrame, "FCC88D01-7F82-4DAE-8026-7B7E086878B3")

.comdef IPointKeyFrame : public IInspectable

    get_Value		proc :ptr
    put_Value		proc :Windows::Foundation::Point
    get_KeyTime		proc :ptr
    put_KeyTime		proc :Windows::UI::Xaml::Media::Animation::KeyTime
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.IPointKeyFrameStatics">
DEFINE_IIDX(IPointKeyFrameStatics, "95CF1B27-7965-4BEC-B9FB-FBE94B65518E")

.comdef IPointKeyFrameStatics : public IInspectable

    get_ValueProperty	proc :ptr
    get_KeyTimeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointKeyFrameFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPointKeyFrameFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPointKeyFrameFactory <L"Windows.UI.Xaml.Media.Animation.IPointKeyFrameFactory">
DEFINE_IIDX(IPointKeyFrameFactory, "CB214BDF-426A-4392-8355-C2AE52852623")

.comdef IPointKeyFrameFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopInThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopInThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPopInThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IPopInThemeAnimation">
DEFINE_IIDX(IPopInThemeAnimation, "196938C1-1C07-4C28-8847-F9F055B32855")

.comdef IPopInThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
    get_FromHorizontalOffset proc :ptr
    put_FromHorizontalOffset proc :DOUBLE
    get_FromVerticalOffset proc :ptr
    put_FromVerticalOffset proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopInThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopInThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPopInThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IPopInThemeAnimationStatics">
DEFINE_IIDX(IPopInThemeAnimationStatics, "EFAA99D3-218A-4701-977F-F1BFAE8BA649")

.comdef IPopInThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
    get_FromHorizontalOffsetProperty proc :ptr
    get_FromVerticalOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopOutThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopOutThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPopOutThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IPopOutThemeAnimation">
DEFINE_IIDX(IPopOutThemeAnimation, "4786AB49-0E48-4E81-A2E5-CC5AA19E48D3")

.comdef IPopOutThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopOutThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopOutThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPopOutThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IPopOutThemeAnimationStatics">
DEFINE_IIDX(IPopOutThemeAnimationStatics, "1D492C09-03C1-4490-99DC-909FEAB357FB")

.comdef IPopOutThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopupThemeTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopupThemeTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPopupThemeTransition <L"Windows.UI.Xaml.Media.Animation.IPopupThemeTransition">
DEFINE_IIDX(IPopupThemeTransition, "47843552-4283-545E-C791-268DCA22CE4B")

.comdef IPopupThemeTransition : public IInspectable

    get_FromHorizontalOffset proc :ptr
    put_FromHorizontalOffset proc :DOUBLE
    get_FromVerticalOffset proc :ptr
    put_FromVerticalOffset proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopupThemeTransitionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPopupThemeTransitionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPopupThemeTransitionStatics <L"Windows.UI.Xaml.Media.Animation.IPopupThemeTransitionStatics">
DEFINE_IIDX(IPopupThemeTransitionStatics, "E5A1640E-490D-1505-9F6B-8FAFC044DEC5")

.comdef IPopupThemeTransitionStatics : public IInspectable

    get_FromHorizontalOffsetProperty proc :ptr
    get_FromVerticalOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPowerEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPowerEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPowerEase <L"Windows.UI.Xaml.Media.Animation.IPowerEase">
DEFINE_IIDX(IPowerEase, "69C80579-EEDF-405B-8680-D9606880C937")

.comdef IPowerEase : public IInspectable

    get_Power		proc :ptr
    put_Power		proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPowerEaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIPowerEaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IPowerEaseStatics <L"Windows.UI.Xaml.Media.Animation.IPowerEaseStatics">
DEFINE_IIDX(IPowerEaseStatics, "A5955103-91A2-460C-9C41-D28F6A939BDA")

.comdef IPowerEaseStatics : public IInspectable

    get_PowerProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIQuadraticEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIQuadraticEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IQuadraticEase <L"Windows.UI.Xaml.Media.Animation.IQuadraticEase">
DEFINE_IIDX(IQuadraticEase, "E1510E91-EF6D-44F0-803D-68D16DE0DDFC")

.comdef IQuadraticEase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIQuarticEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIQuarticEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IQuarticEase <L"Windows.UI.Xaml.Media.Animation.IQuarticEase">
DEFINE_IIDX(IQuarticEase, "E8698814-FE42-4A05-B5B8-081F41157815")

.comdef IQuarticEase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIQuinticEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIQuinticEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IQuinticEase <L"Windows.UI.Xaml.Media.Animation.IQuinticEase">
DEFINE_IIDX(IQuinticEase, "92EE793B-3C49-4108-AA11-AB786603DA21")

.comdef IQuinticEase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIReorderThemeTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIReorderThemeTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IReorderThemeTransition <L"Windows.UI.Xaml.Media.Animation.IReorderThemeTransition">
DEFINE_IIDX(IReorderThemeTransition, "F2065C6C-D052-4AD1-8362-B71B36DF7497")

.comdef IReorderThemeTransition : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepositionThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepositionThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IRepositionThemeAnimation <L"Windows.UI.Xaml.Media.Animation.IRepositionThemeAnimation">
DEFINE_IIDX(IRepositionThemeAnimation, "ECDA24E8-8945-4949-A1BF-62109965A7E9")

.comdef IRepositionThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
    get_FromHorizontalOffset proc :ptr
    put_FromHorizontalOffset proc :DOUBLE
    get_FromVerticalOffset proc :ptr
    put_FromVerticalOffset proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepositionThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepositionThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IRepositionThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.IRepositionThemeAnimationStatics">
DEFINE_IIDX(IRepositionThemeAnimationStatics, "4D92B1B1-860B-4BF9-A59D-1EB1CCBE8FE0")

.comdef IRepositionThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
    get_FromHorizontalOffsetProperty proc :ptr
    get_FromVerticalOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepositionThemeTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIRepositionThemeTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IRepositionThemeTransition <L"Windows.UI.Xaml.Media.Animation.IRepositionThemeTransition">
DEFINE_IIDX(IRepositionThemeTransition, "88329B82-98F3-455A-AC53-2E7083B6E22C")

.comdef IRepositionThemeTransition : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISineEase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISineEase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISineEase <L"Windows.UI.Xaml.Media.Animation.ISineEase">
DEFINE_IIDX(ISineEase, "A9382962-230B-49DA-9E0D-664987892343")

.comdef ISineEase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplineColorKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplineColorKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplineColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.ISplineColorKeyFrame">
DEFINE_IIDX(ISplineColorKeyFrame, "1A4A5941-1FE0-473A-8EFE-4316D8C86229")

.comdef ISplineColorKeyFrame : public IInspectable

    get_KeySpline	proc :ptr
    put_KeySpline	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplineColorKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplineColorKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplineColorKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.ISplineColorKeyFrameStatics">
DEFINE_IIDX(ISplineColorKeyFrameStatics, "61D1D997-8589-4F2F-8FBB-7D03EDC98DD3")

.comdef ISplineColorKeyFrameStatics : public IInspectable

    get_KeySplineProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplineDoubleKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplineDoubleKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplineDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.ISplineDoubleKeyFrame">
DEFINE_IIDX(ISplineDoubleKeyFrame, "00D72D38-6B2B-4843-838E-C8B115EEC801")

.comdef ISplineDoubleKeyFrame : public IInspectable

    get_KeySpline	proc :ptr
    put_KeySpline	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplineDoubleKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplineDoubleKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplineDoubleKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.ISplineDoubleKeyFrameStatics">
DEFINE_IIDX(ISplineDoubleKeyFrameStatics, "060A8FFC-975F-4E4E-9EC7-13C5AEE02062")

.comdef ISplineDoubleKeyFrameStatics : public IInspectable

    get_KeySplineProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplinePointKeyFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplinePointKeyFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplinePointKeyFrame <L"Windows.UI.Xaml.Media.Animation.ISplinePointKeyFrame">
DEFINE_IIDX(ISplinePointKeyFrame, "0F19F306-7036-494F-BC3C-780DF0CC524A")

.comdef ISplinePointKeyFrame : public IInspectable

    get_KeySpline	proc :ptr
    put_KeySpline	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplinePointKeyFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplinePointKeyFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplinePointKeyFrameStatics <L"Windows.UI.Xaml.Media.Animation.ISplinePointKeyFrameStatics">
DEFINE_IIDX(ISplinePointKeyFrameStatics, "E97A32C2-0A7A-4766-95CB-0D692611CB4C")

.comdef ISplinePointKeyFrameStatics : public IInspectable

    get_KeySplineProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplitCloseThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplitCloseThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplitCloseThemeAnimation <L"Windows.UI.Xaml.Media.Animation.ISplitCloseThemeAnimation">
DEFINE_IIDX(ISplitCloseThemeAnimation, "4F799518-FF39-4E90-BB74-2ABD56027402")

.comdef ISplitCloseThemeAnimation : public IInspectable

    get_OpenedTargetName proc :ptr
    put_OpenedTargetName proc :HSTRING
    get_OpenedTarget	proc :ptr
    put_OpenedTarget	proc :ptr
    get_ClosedTargetName proc :ptr
    put_ClosedTargetName proc :HSTRING
    get_ClosedTarget	proc :ptr
    put_ClosedTarget	proc :ptr
    get_ContentTargetName proc :ptr
    put_ContentTargetName proc :HSTRING
    get_ContentTarget	proc :ptr
    put_ContentTarget	proc :ptr
    get_OpenedLength	proc :ptr
    put_OpenedLength	proc :DOUBLE
    get_ClosedLength	proc :ptr
    put_ClosedLength	proc :DOUBLE
    get_OffsetFromCenter proc :ptr
    put_OffsetFromCenter proc :DOUBLE
    get_ContentTranslationDirection proc :ptr
    put_ContentTranslationDirection proc :Windows::UI::Xaml::Controls::Primitives::AnimationDirection
    get_ContentTranslationOffset proc :ptr
    put_ContentTranslationOffset proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplitCloseThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplitCloseThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplitCloseThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.ISplitCloseThemeAnimationStatics">
DEFINE_IIDX(ISplitCloseThemeAnimationStatics, "7AA94DE9-CC9B-4E90-A11A-0050A2216A9E")

.comdef ISplitCloseThemeAnimationStatics : public IInspectable

    get_OpenedTargetNameProperty proc :ptr
    get_OpenedTargetProperty proc :ptr
    get_ClosedTargetNameProperty proc :ptr
    get_ClosedTargetProperty proc :ptr
    get_ContentTargetNameProperty proc :ptr
    get_ContentTargetProperty proc :ptr
    get_OpenedLengthProperty proc :ptr
    get_ClosedLengthProperty proc :ptr
    get_OffsetFromCenterProperty proc :ptr
    get_ContentTranslationDirectionProperty proc :ptr
    get_ContentTranslationOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplitOpenThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplitOpenThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplitOpenThemeAnimation <L"Windows.UI.Xaml.Media.Animation.ISplitOpenThemeAnimation">
DEFINE_IIDX(ISplitOpenThemeAnimation, "785FD7AA-5456-4639-8FD2-26BAE6A5FFE4")

.comdef ISplitOpenThemeAnimation : public IInspectable

    get_OpenedTargetName proc :ptr
    put_OpenedTargetName proc :HSTRING
    get_OpenedTarget	proc :ptr
    put_OpenedTarget	proc :ptr
    get_ClosedTargetName proc :ptr
    put_ClosedTargetName proc :HSTRING
    get_ClosedTarget	proc :ptr
    put_ClosedTarget	proc :ptr
    get_ContentTargetName proc :ptr
    put_ContentTargetName proc :HSTRING
    get_ContentTarget	proc :ptr
    put_ContentTarget	proc :ptr
    get_OpenedLength	proc :ptr
    put_OpenedLength	proc :DOUBLE
    get_ClosedLength	proc :ptr
    put_ClosedLength	proc :DOUBLE
    get_OffsetFromCenter proc :ptr
    put_OffsetFromCenter proc :DOUBLE
    get_ContentTranslationDirection proc :ptr
    put_ContentTranslationDirection proc :Windows::UI::Xaml::Controls::Primitives::AnimationDirection
    get_ContentTranslationOffset proc :ptr
    put_ContentTranslationOffset proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplitOpenThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISplitOpenThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISplitOpenThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.ISplitOpenThemeAnimationStatics">
DEFINE_IIDX(ISplitOpenThemeAnimationStatics, "8D4CFA89-3A91-458D-B0FB-4CAD625CBF8D")

.comdef ISplitOpenThemeAnimationStatics : public IInspectable

    get_OpenedTargetNameProperty proc :ptr
    get_OpenedTargetProperty proc :ptr
    get_ClosedTargetNameProperty proc :ptr
    get_ClosedTargetProperty proc :ptr
    get_ContentTargetNameProperty proc :ptr
    get_ContentTargetProperty proc :ptr
    get_OpenedLengthProperty proc :ptr
    get_ClosedLengthProperty proc :ptr
    get_OffsetFromCenterProperty proc :ptr
    get_ContentTranslationDirectionProperty proc :ptr
    get_ContentTranslationOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIStoryboard_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIStoryboard_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IStoryboard <L"Windows.UI.Xaml.Media.Animation.IStoryboard">
DEFINE_IIDX(IStoryboard, "D45C1E6E-3594-460E-981A-32271BD3AA06")

.comdef IStoryboard : public IInspectable

    get_Children	proc :ptr
    Seek		proc :Windows::Foundation::TimeSpan
    Stop		proc
    Begin		proc
    _Pause		proc
    Resume		proc
    GetCurrentState	proc :ptr
    GetCurrentTime	proc :ptr
    SeekAlignedToLastTick proc :Windows::Foundation::TimeSpan
    SkipToFill		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIStoryboardStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CIStoryboardStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_IStoryboardStatics <L"Windows.UI.Xaml.Media.Animation.IStoryboardStatics">
DEFINE_IIDX(IStoryboardStatics, "D82F07D8-73D5-4379-BD48-7E05184A8BAD")

.comdef IStoryboardStatics : public IInspectable

    get_TargetPropertyProperty proc :ptr
    GetTargetProperty	proc :ptr, :ptr
    SetTargetProperty	proc :ptr, :HSTRING
    get_TargetNameProperty proc :ptr
    GetTargetName	proc :ptr, :ptr
    SetTargetName	proc :ptr, :HSTRING
    SetTarget		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISwipeBackThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISwipeBackThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISwipeBackThemeAnimation <L"Windows.UI.Xaml.Media.Animation.ISwipeBackThemeAnimation">
DEFINE_IIDX(ISwipeBackThemeAnimation, "A38A4214-0BCA-4D2D-95F7-CEBA57FBAF60")

.comdef ISwipeBackThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
    get_FromHorizontalOffset proc :ptr
    put_FromHorizontalOffset proc :DOUBLE
    get_FromVerticalOffset proc :ptr
    put_FromVerticalOffset proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISwipeBackThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISwipeBackThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISwipeBackThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.ISwipeBackThemeAnimationStatics">
DEFINE_IIDX(ISwipeBackThemeAnimationStatics, "693F31BF-4DA6-468A-8CE0-996C9AAD42E0")

.comdef ISwipeBackThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
    get_FromHorizontalOffsetProperty proc :ptr
    get_FromVerticalOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISwipeHintThemeAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISwipeHintThemeAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISwipeHintThemeAnimation <L"Windows.UI.Xaml.Media.Animation.ISwipeHintThemeAnimation">
DEFINE_IIDX(ISwipeHintThemeAnimation, "CDD067C0-580E-4E40-BE98-F202D3D84365")

.comdef ISwipeHintThemeAnimation : public IInspectable

    get_TargetName	proc :ptr
    put_TargetName	proc :HSTRING
    get_ToHorizontalOffset proc :ptr
    put_ToHorizontalOffset proc :DOUBLE
    get_ToVerticalOffset proc :ptr
    put_ToVerticalOffset proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISwipeHintThemeAnimationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CISwipeHintThemeAnimationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ISwipeHintThemeAnimationStatics <L"Windows.UI.Xaml.Media.Animation.ISwipeHintThemeAnimationStatics">
DEFINE_IIDX(ISwipeHintThemeAnimationStatics, "23D61A57-9115-4D63-B04A-B89F1C744DC0")

.comdef ISwipeHintThemeAnimationStatics : public IInspectable

    get_TargetNameProperty proc :ptr
    get_ToHorizontalOffsetProperty proc :ptr
    get_ToVerticalOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITimeline_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITimeline_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ITimeline <L"Windows.UI.Xaml.Media.Animation.ITimeline">
DEFINE_IIDX(ITimeline, "0BC465DC-BE4D-4D0D-9549-2208B715F40D")

.comdef ITimeline : public IInspectable

    get_AutoReverse	proc :ptr
    put_AutoReverse	proc :boolean
    get_BeginTime	proc :ptr
    put_BeginTime	proc :ptr
    get_Duration	proc :ptr
    put_Duration	proc :Windows::UI::Xaml::Duration
    get_SpeedRatio	proc :ptr
    put_SpeedRatio	proc :DOUBLE
    get_FillBehavior	proc :ptr
    put_FillBehavior	proc :Windows::UI::Xaml::Media::Animation::FillBehavior
    get_RepeatBehavior	proc :ptr
    put_RepeatBehavior	proc :Windows::UI::Xaml::Media::Animation::RepeatBehavior
    add_Completed	proc :ptr, :ptr
    remove_Completed	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITimelineStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITimelineStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ITimelineStatics <L"Windows.UI.Xaml.Media.Animation.ITimelineStatics">
DEFINE_IIDX(ITimelineStatics, "A902ED4E-EF10-4D6F-9A40-93CB8895F4E5")

.comdef ITimelineStatics : public IInspectable

    get_AllowDependentAnimations proc :ptr
    put_AllowDependentAnimations proc :boolean
    get_AutoReverseProperty proc :ptr
    get_BeginTimeProperty proc :ptr
    get_DurationProperty proc :ptr
    get_SpeedRatioProperty proc :ptr
    get_FillBehaviorProperty proc :ptr
    get_RepeatBehaviorProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITimelineFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITimelineFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ITimelineFactory <L"Windows.UI.Xaml.Media.Animation.ITimelineFactory">
DEFINE_IIDX(ITimelineFactory, "1D56BB07-BDA4-478B-8ADA-EB04D580CD5E")

.comdef ITimelineFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ITransition <L"Windows.UI.Xaml.Media.Animation.ITransition">
DEFINE_IIDX(ITransition, "3C677C7C-01D0-4DCE-B333-976F93312B08")

.comdef ITransition : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITransitionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CAnimation_CITransitionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Animation_ITransitionFactory <L"Windows.UI.Xaml.Media.Animation.ITransitionFactory">
DEFINE_IIDX(ITransitionFactory, "DC9AB2CF-3BC9-44AA-B3FC-883A83233A2C")

.comdef ITransitionFactory : public IInspectable

   .ends

endif

.endn
.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_KeyTimeHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_KeyTimeHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_KeyTimeHelper <L"Windows.UI.Xaml.Media.Animation.KeyTimeHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_RepeatBehaviorHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_RepeatBehaviorHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_RepeatBehaviorHelper <L"Windows.UI.Xaml.Media.Animation.RepeatBehaviorHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_TransitionCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_TransitionCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_TransitionCollection <L"Windows.UI.Xaml.Media.Animation.TransitionCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_BeginStoryboard_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_BeginStoryboard_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_BeginStoryboard <L"Windows.UI.Xaml.Media.Animation.BeginStoryboard">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ColorKeyFrameCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ColorKeyFrameCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ColorKeyFrameCollection <L"Windows.UI.Xaml.Media.Animation.ColorKeyFrameCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ColorKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ColorKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.ColorKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DiscreteColorKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DiscreteColorKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DiscreteColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.DiscreteColorKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DoubleKeyFrameCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DoubleKeyFrameCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DoubleKeyFrameCollection <L"Windows.UI.Xaml.Media.Animation.DoubleKeyFrameCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DoubleKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DoubleKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.DoubleKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DiscreteDoubleKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DiscreteDoubleKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DiscreteDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.DiscreteDoubleKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EasingColorKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EasingColorKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_EasingColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.EasingColorKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EasingDoubleKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EasingDoubleKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_EasingDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.EasingDoubleKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EasingFunctionBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EasingFunctionBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_EasingFunctionBase <L"Windows.UI.Xaml.Media.Animation.EasingFunctionBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_BackEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_BackEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_BackEase <L"Windows.UI.Xaml.Media.Animation.BackEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_BounceEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_BounceEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_BounceEase <L"Windows.UI.Xaml.Media.Animation.BounceEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_CircleEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_CircleEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_CircleEase <L"Windows.UI.Xaml.Media.Animation.CircleEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_CubicEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_CubicEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_CubicEase <L"Windows.UI.Xaml.Media.Animation.CubicEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ElasticEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ElasticEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ElasticEase <L"Windows.UI.Xaml.Media.Animation.ElasticEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ExponentialEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ExponentialEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ExponentialEase <L"Windows.UI.Xaml.Media.Animation.ExponentialEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_KeySpline_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_KeySpline_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_KeySpline <L"Windows.UI.Xaml.Media.Animation.KeySpline">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_LinearColorKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_LinearColorKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_LinearColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.LinearColorKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_LinearDoubleKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_LinearDoubleKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_LinearDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.LinearDoubleKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_NavigationTransitionInfo_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_NavigationTransitionInfo_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_NavigationTransitionInfo <L"Windows.UI.Xaml.Media.Animation.NavigationTransitionInfo">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ObjectKeyFrameCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ObjectKeyFrameCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ObjectKeyFrameCollection <L"Windows.UI.Xaml.Media.Animation.ObjectKeyFrameCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ObjectKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ObjectKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ObjectKeyFrame <L"Windows.UI.Xaml.Media.Animation.ObjectKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DiscreteObjectKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DiscreteObjectKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DiscreteObjectKeyFrame <L"Windows.UI.Xaml.Media.Animation.DiscreteObjectKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointKeyFrameCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointKeyFrameCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PointKeyFrameCollection <L"Windows.UI.Xaml.Media.Animation.PointKeyFrameCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PointKeyFrame <L"Windows.UI.Xaml.Media.Animation.PointKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DiscretePointKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DiscretePointKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DiscretePointKeyFrame <L"Windows.UI.Xaml.Media.Animation.DiscretePointKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EasingPointKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EasingPointKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_EasingPointKeyFrame <L"Windows.UI.Xaml.Media.Animation.EasingPointKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_LinearPointKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_LinearPointKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_LinearPointKeyFrame <L"Windows.UI.Xaml.Media.Animation.LinearPointKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PowerEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PowerEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PowerEase <L"Windows.UI.Xaml.Media.Animation.PowerEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_QuadraticEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_QuadraticEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_QuadraticEase <L"Windows.UI.Xaml.Media.Animation.QuadraticEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_QuarticEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_QuarticEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_QuarticEase <L"Windows.UI.Xaml.Media.Animation.QuarticEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_QuinticEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_QuinticEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_QuinticEase <L"Windows.UI.Xaml.Media.Animation.QuinticEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SineEase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SineEase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_SineEase <L"Windows.UI.Xaml.Media.Animation.SineEase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplineColorKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplineColorKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_SplineColorKeyFrame <L"Windows.UI.Xaml.Media.Animation.SplineColorKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplineDoubleKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplineDoubleKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_SplineDoubleKeyFrame <L"Windows.UI.Xaml.Media.Animation.SplineDoubleKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplinePointKeyFrame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplinePointKeyFrame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_SplinePointKeyFrame <L"Windows.UI.Xaml.Media.Animation.SplinePointKeyFrame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_TimelineCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_TimelineCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_TimelineCollection <L"Windows.UI.Xaml.Media.Animation.TimelineCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_Timeline_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_Timeline_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_Timeline <L"Windows.UI.Xaml.Media.Animation.Timeline">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_Storyboard_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_Storyboard_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_Storyboard <L"Windows.UI.Xaml.Media.Animation.Storyboard">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ColorAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ColorAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ColorAnimation <L"Windows.UI.Xaml.Media.Animation.ColorAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ColorAnimationUsingKeyFrames_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ColorAnimationUsingKeyFrames_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ColorAnimationUsingKeyFrames <L"Windows.UI.Xaml.Media.Animation.ColorAnimationUsingKeyFrames">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DoubleAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DoubleAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DoubleAnimation <L"Windows.UI.Xaml.Media.Animation.DoubleAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DoubleAnimationUsingKeyFrames_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DoubleAnimationUsingKeyFrames_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DoubleAnimationUsingKeyFrames <L"Windows.UI.Xaml.Media.Animation.DoubleAnimationUsingKeyFrames">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DragItemThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DragItemThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DragItemThemeAnimation <L"Windows.UI.Xaml.Media.Animation.DragItemThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DragOverThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DragOverThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DragOverThemeAnimation <L"Windows.UI.Xaml.Media.Animation.DragOverThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DropTargetItemThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_DropTargetItemThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_DropTargetItemThemeAnimation <L"Windows.UI.Xaml.Media.Animation.DropTargetItemThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_FadeInThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_FadeInThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_FadeInThemeAnimation <L"Windows.UI.Xaml.Media.Animation.FadeInThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_FadeOutThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_FadeOutThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_FadeOutThemeAnimation <L"Windows.UI.Xaml.Media.Animation.FadeOutThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ObjectAnimationUsingKeyFrames_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ObjectAnimationUsingKeyFrames_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ObjectAnimationUsingKeyFrames <L"Windows.UI.Xaml.Media.Animation.ObjectAnimationUsingKeyFrames">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PointAnimation <L"Windows.UI.Xaml.Media.Animation.PointAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointAnimationUsingKeyFrames_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointAnimationUsingKeyFrames_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PointAnimationUsingKeyFrames <L"Windows.UI.Xaml.Media.Animation.PointAnimationUsingKeyFrames">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointerDownThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointerDownThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PointerDownThemeAnimation <L"Windows.UI.Xaml.Media.Animation.PointerDownThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointerUpThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PointerUpThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PointerUpThemeAnimation <L"Windows.UI.Xaml.Media.Animation.PointerUpThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PopInThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PopInThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PopInThemeAnimation <L"Windows.UI.Xaml.Media.Animation.PopInThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PopOutThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PopOutThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PopOutThemeAnimation <L"Windows.UI.Xaml.Media.Animation.PopOutThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_RepositionThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_RepositionThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_RepositionThemeAnimation <L"Windows.UI.Xaml.Media.Animation.RepositionThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplitCloseThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplitCloseThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_SplitCloseThemeAnimation <L"Windows.UI.Xaml.Media.Animation.SplitCloseThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplitOpenThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SplitOpenThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_SplitOpenThemeAnimation <L"Windows.UI.Xaml.Media.Animation.SplitOpenThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SwipeBackThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SwipeBackThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_SwipeBackThemeAnimation <L"Windows.UI.Xaml.Media.Animation.SwipeBackThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SwipeHintThemeAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_SwipeHintThemeAnimation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_SwipeHintThemeAnimation <L"Windows.UI.Xaml.Media.Animation.SwipeHintThemeAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_Transition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_Transition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_Transition <L"Windows.UI.Xaml.Media.Animation.Transition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_AddDeleteThemeTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_AddDeleteThemeTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_AddDeleteThemeTransition <L"Windows.UI.Xaml.Media.Animation.AddDeleteThemeTransition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ContentThemeTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ContentThemeTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ContentThemeTransition <L"Windows.UI.Xaml.Media.Animation.ContentThemeTransition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EdgeUIThemeTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EdgeUIThemeTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_EdgeUIThemeTransition <L"Windows.UI.Xaml.Media.Animation.EdgeUIThemeTransition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EntranceThemeTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_EntranceThemeTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_EntranceThemeTransition <L"Windows.UI.Xaml.Media.Animation.EntranceThemeTransition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PaneThemeTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PaneThemeTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PaneThemeTransition <L"Windows.UI.Xaml.Media.Animation.PaneThemeTransition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PopupThemeTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_PopupThemeTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_PopupThemeTransition <L"Windows.UI.Xaml.Media.Animation.PopupThemeTransition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ReorderThemeTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_ReorderThemeTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_ReorderThemeTransition <L"Windows.UI.Xaml.Media.Animation.ReorderThemeTransition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_RepositionThemeTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Animation_RepositionThemeTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Animation_RepositionThemeTransition <L"Windows.UI.Xaml.Media.Animation.RepositionThemeTransition">
endif

endif
