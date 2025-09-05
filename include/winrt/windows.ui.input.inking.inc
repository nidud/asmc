ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Einput2Einking_h__
define __windows2Eui2Einput2Einking_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc
include Windows.UI.inc
include Windows.UI.Input.inc

ifndef ____FIIterator_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CInput__CInking__CInkRecognitionResult, "9abc247f-0223-5f44-8fa1-0d6d691bf9af")

.comdef __FIIterator_1_Windows__CUI__CInput__CInking__CInkRecognitionResult : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CInput__CInking__CInkRecognitionResult, "e29b658b-7cc1-561c-9912-001dbca86651")

.comdef __FIIterable_1_Windows__CUI__CInput__CInking__CInkRecognitionResult : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CInput__CInking__CInkRecognizer_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CInput__CInking__CInkRecognizer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CInput__CInking__CInkRecognizer, "f8bd3097-5262-5e7a-a19d-13c029d2d7e5")

.comdef __FIIterator_1_Windows__CUI__CInput__CInking__CInkRecognizer : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CInput__CInking__CInkRecognizer_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CInput__CInking__CInkRecognizer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CInput__CInking__CInkRecognizer, "611b7e84-a803-5071-aaea-4f2ce0151052")

.comdef __FIIterable_1_Windows__CUI__CInput__CInking__CInkRecognizer : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CInput__CInking__CInkStroke_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CInput__CInking__CInkStroke_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CInput__CInking__CInkStroke, "5608d5a9-e7e4-5a0b-941f-b7fed76b35bf")

.comdef __FIIterator_1_Windows__CUI__CInput__CInking__CInkStroke : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CInput__CInking__CInkStroke_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CInput__CInking__CInkStroke_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CInput__CInking__CInkStroke, "bbc11401-89d0-5305-a3b3-36c887714b9b")

.comdef __FIIterable_1_Windows__CUI__CInput__CInking__CInkStroke : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment, "d7d8c317-6f3f-5192-9210-65a263baf8d1")

.comdef __FIIterator_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment, "27000f47-2885-5da9-8923-16a3a58b7a55")

.comdef __FIIterable_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult, "ecfc4f0b-112c-5cd3-acf0-d746d6bdfeb5")

.comdef __FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognizer_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognizer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognizer, "8eadfa4f-27ef-5a5d-b0b8-7fd5c0ce6b39")

.comdef __FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognizer : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CInput__CInking__CInkStroke_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CInput__CInking__CInkStroke_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CInput__CInking__CInkStroke, "6744f458-b242-5767-a643-996e01dff0e4")

.comdef __FIVectorView_1_Windows__CUI__CInput__CInking__CInkStroke : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment, "f39ea41d-4714-5d80-87de-973dd26da269")

.comdef __FIVectorView_1_Windows__CUI__CInput__CInking__CInkStrokeRenderingSegment : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult, "ece8567f-8080-5ced-8988-bb0364c803d4")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult, "b1923f59-d674-5365-b99a-3f1e52268c7f")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CUI__CInput__CInking__CInkRecognitionResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Input
.namespace Inking

.enum InkManipulationMode {
    InkManipulationMode_Inking	= 0,
    InkManipulationMode_Erasing = 1,
    InkManipulationMode_Selecting	= 2
    }

.enum InkRecognitionTarget {
    InkRecognitionTarget_All	= 0,
    InkRecognitionTarget_Selected	= 1,
    InkRecognitionTarget_Recent = 2
    }

.enum PenTipShape {
    PenTipShape_Circle	= 0,
    PenTipShape_Rectangle	= 1
    }

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkDrawingAttributes_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkDrawingAttributes_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkDrawingAttributes <L"Windows.UI.Input.Inking.IInkDrawingAttributes">
DEFINE_IIDX(IInkDrawingAttributes, "97A2176C-6774-48AD-84F0-48F5A9BE74F9")

.comdef IInkDrawingAttributes : public IInspectable

    get_Color		proc :ptr
    put_Color		proc :Windows::UI::Color
    get_PenTip		proc :ptr
    put_PenTip		proc :Windows::UI::Input::Inking::PenTipShape
    get_Size		proc :ptr
    put_Size		proc :Windows::Foundation::Size
    get_IgnorePressure	proc :ptr
    put_IgnorePressure	proc :boolean
    get_FitToCurve	proc :ptr
    put_FitToCurve	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkStrokeRenderingSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkStrokeRenderingSegment_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkStrokeRenderingSegment <L"Windows.UI.Input.Inking.IInkStrokeRenderingSegment">
DEFINE_IIDX(IInkStrokeRenderingSegment, "68510F1F-88E3-477A-A2FA-569F5F1F9BD5")

.comdef IInkStrokeRenderingSegment : public IInspectable

    get_Position	proc :ptr
    get_BezierControlPoint1 proc :ptr
    get_BezierControlPoint2 proc :ptr
    get_Pressure	proc :ptr
    get_TiltX		proc :ptr
    get_TiltY		proc :ptr
    get_Twist		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkStroke_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkStroke_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkStroke <L"Windows.UI.Input.Inking.IInkStroke">
DEFINE_IIDX(IInkStroke, "15144D60-CCE3-4FCF-9D52-11518AB6AFD4")

.comdef IInkStroke : public IInspectable

    get_DrawingAttributes proc :ptr
    put_DrawingAttributes proc :ptr
    get_BoundingRect	proc :ptr
    get_Selected	proc :ptr
    put_Selected	proc :boolean
    get_Recognized	proc :ptr
    GetRenderingSegments proc :ptr
    Clone		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkStrokeBuilder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkStrokeBuilder_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkStrokeBuilder <L"Windows.UI.Input.Inking.IInkStrokeBuilder">
DEFINE_IIDX(IInkStrokeBuilder, "82BBD1DC-1C63-41DC-9E07-4B4A70CED801")

.comdef IInkStrokeBuilder : public IInspectable

    BeginStroke		proc :ptr
    AppendToStroke	proc :ptr, :ptr
    EndStroke		proc :ptr, :ptr
    CreateStroke	proc :ptr, :ptr
    SetDefaultDrawingAttributes proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkRecognitionResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkRecognitionResult_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkRecognitionResult <L"Windows.UI.Input.Inking.IInkRecognitionResult">
DEFINE_IIDX(IInkRecognitionResult, "36461A94-5068-40EF-8A05-2C2FB60908A2")

.comdef IInkRecognitionResult : public IInspectable

    get_BoundingRect	proc :ptr
    GetTextCandidates	proc :ptr
    GetStrokes		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkStrokeContainer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkStrokeContainer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkStrokeContainer <L"Windows.UI.Input.Inking.IInkStrokeContainer">
DEFINE_IIDX(IInkStrokeContainer, "22ACCBC6-FAA9-4F14-B68C-F6CEE670AE16")

.comdef IInkStrokeContainer : public IInspectable

    get_BoundingRect	proc :ptr
    AddStroke		proc :ptr
    DeleteSelected	proc :ptr
    MoveSelected	proc :Windows::Foundation::Point, :ptr
    SelectWithPolyLine	proc :ptr, :ptr
    SelectWithLine	proc :Windows::Foundation::Point, :Windows::Foundation::Point, :ptr
    CopySelectedToClipboard proc
    PasteFromClipboard	proc :Windows::Foundation::Point, :ptr
    CanPasteFromClipboard proc :ptr
    LoadAsync		proc :ptr, :ptr
    SaveAsync		proc :ptr, :ptr
    UpdateRecognitionResults proc :ptr
    GetStrokes		proc :ptr
    GetRecognitionResults proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkRecognizer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkRecognizer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkRecognizer <L"Windows.UI.Input.Inking.IInkRecognizer">
DEFINE_IIDX(IInkRecognizer, "077CCEA3-904D-442A-B151-AACA3631C43B")

.comdef IInkRecognizer : public IInspectable

    get_Name		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkRecognizerContainer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkRecognizerContainer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkRecognizerContainer <L"Windows.UI.Input.Inking.IInkRecognizerContainer">
DEFINE_IIDX(IInkRecognizerContainer, "A74D9A31-8047-4698-A912-F82A5085012F")

.comdef IInkRecognizerContainer : public IInspectable

    SetDefaultRecognizer proc :ptr
    RecognizeAsync	proc :ptr, :Windows::UI::Input::Inking::InkRecognitionTarget, :ptr
    GetRecognizers	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CInking_CIInkManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CInking_CIInkManager_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_Inking_IInkManager <L"Windows.UI.Input.Inking.IInkManager">
DEFINE_IIDX(IInkManager, "4744737D-671B-4163-9C95-4E8D7A035FE1")

.comdef IInkManager : public IInspectable

    get_Mode		proc :ptr
    put_Mode		proc :Windows::UI::Input::Inking::InkManipulationMode
    ProcessPointerDown	proc :ptr
    ProcessPointerUpdate proc :ptr, :ptr
    ProcessPointerUp	proc :ptr, :ptr
    SetDefaultDrawingAttributes proc :ptr
    RecognizeAsync2	proc :Windows::UI::Input::Inking::InkRecognitionTarget, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkDrawingAttributes_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkDrawingAttributes_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkDrawingAttributes <L"Windows.UI.Input.Inking.InkDrawingAttributes">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkStrokeRenderingSegment_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkStrokeRenderingSegment_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkStrokeRenderingSegment <L"Windows.UI.Input.Inking.InkStrokeRenderingSegment">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkStroke_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkStroke_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkStroke <L"Windows.UI.Input.Inking.InkStroke">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkStrokeBuilder_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkStrokeBuilder_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkStrokeBuilder <L"Windows.UI.Input.Inking.InkStrokeBuilder">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkRecognitionResult_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkRecognitionResult_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkRecognitionResult <L"Windows.UI.Input.Inking.InkRecognitionResult">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkStrokeContainer_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkStrokeContainer_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkStrokeContainer <L"Windows.UI.Input.Inking.InkStrokeContainer">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkRecognizer_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkRecognizer_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkRecognizer <L"Windows.UI.Input.Inking.InkRecognizer">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkRecognizerContainer_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkRecognizerContainer_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkRecognizerContainer <L"Windows.UI.Input.Inking.InkRecognizerContainer">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_Inking_InkManager_DEFINED
define RUNTIMECLASS_Windows_UI_Input_Inking_InkManager_DEFINED
define RuntimeClass_Windows_UI_Input_Inking_InkManager <L"Windows.UI.Input.Inking.InkManager">
endif

endif
