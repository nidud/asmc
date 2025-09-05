ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Egraphics2Eprinting_h__
define __windows2Egraphics2Eprinting_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.ApplicationModel.DataTransfer.inc

ifndef ____FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintManager_Windows__CGraphics__CPrinting__CPrintTaskRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintManager_Windows__CGraphics__CPrinting__CPrintTaskRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintManager_Windows__CGraphics__CPrinting__CPrintTaskRequestedEventArgs, "8a8cb877-70c5-54ce-8b42-d790e2914859")

.comdef __FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintManager_Windows__CGraphics__CPrinting__CPrintTaskRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_IInspectable, "4cc141d4-c0d9-5220-b1ce-80fff3bd2d44")

.comdef __FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_Windows__CGraphics__CPrinting__CPrintTaskCompletedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_Windows__CGraphics__CPrinting__CPrintTaskCompletedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_Windows__CGraphics__CPrinting__CPrintTaskCompletedEventArgs, "b0b02549-b9ad-5226-898a-7b563b46640c")

.comdef __FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_Windows__CGraphics__CPrinting__CPrintTaskCompletedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_Windows__CGraphics__CPrinting__CPrintTaskProgressingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_Windows__CGraphics__CPrinting__CPrintTaskProgressingEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_Windows__CGraphics__CPrinting__CPrintTaskProgressingEventArgs, "c08d0524-5899-536c-8f46-55fdaa4cf78b")

.comdef __FITypedEventHandler_2_Windows__CGraphics__CPrinting__CPrintTask_Windows__CGraphics__CPrinting__CPrintTaskProgressingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Graphics
.namespace Printing

.enum PrintMediaSize {
    PrintMediaSize_Default	= 0,
    PrintMediaSize_NotAvailable = 1,
    PrintMediaSize_PrinterCustom	= 2,
    PrintMediaSize_BusinessCard = 3,
    PrintMediaSize_CreditCard	= 4,
    PrintMediaSize_IsoA0	= 5,
    PrintMediaSize_IsoA1	= 6,
    PrintMediaSize_IsoA10	= 7,
    PrintMediaSize_IsoA2	= 8,
    PrintMediaSize_IsoA3	= 9,
    PrintMediaSize_IsoA3Extra	= 10,
    PrintMediaSize_IsoA3Rotated = 11,
    PrintMediaSize_IsoA4	= 12,
    PrintMediaSize_IsoA4Extra	= 13,
    PrintMediaSize_IsoA4Rotated = 14,
    PrintMediaSize_IsoA5	= 15,
    PrintMediaSize_IsoA5Extra	= 16,
    PrintMediaSize_IsoA5Rotated = 17,
    PrintMediaSize_IsoA6	= 18,
    PrintMediaSize_IsoA6Rotated = 19,
    PrintMediaSize_IsoA7	= 20,
    PrintMediaSize_IsoA8	= 21,
    PrintMediaSize_IsoA9	= 22,
    PrintMediaSize_IsoB0	= 23,
    PrintMediaSize_IsoB1	= 24,
    PrintMediaSize_IsoB10	= 25,
    PrintMediaSize_IsoB2	= 26,
    PrintMediaSize_IsoB3	= 27,
    PrintMediaSize_IsoB4	= 28,
    PrintMediaSize_IsoB4Envelope	= 29,
    PrintMediaSize_IsoB5Envelope	= 30,
    PrintMediaSize_IsoB5Extra	= 31,
    PrintMediaSize_IsoB7	= 32,
    PrintMediaSize_IsoB8	= 33,
    PrintMediaSize_IsoB9	= 34,
    PrintMediaSize_IsoC0	= 35,
    PrintMediaSize_IsoC1	= 36,
    PrintMediaSize_IsoC10	= 37,
    PrintMediaSize_IsoC2	= 38,
    PrintMediaSize_IsoC3	= 39,
    PrintMediaSize_IsoC3Envelope	= 40,
    PrintMediaSize_IsoC4	= 41,
    PrintMediaSize_IsoC4Envelope	= 42,
    PrintMediaSize_IsoC5	= 43,
    PrintMediaSize_IsoC5Envelope	= 44,
    PrintMediaSize_IsoC6	= 45,
    PrintMediaSize_IsoC6C5Envelope	= 46,
    PrintMediaSize_IsoC6Envelope	= 47,
    PrintMediaSize_IsoC7	= 48,
    PrintMediaSize_IsoC8	= 49,
    PrintMediaSize_IsoC9	= 50,
    PrintMediaSize_IsoDLEnvelope	= 51,
    PrintMediaSize_IsoDLEnvelopeRotated = 52,
    PrintMediaSize_IsoSRA3	= 53,
    PrintMediaSize_Japan2LPhoto = 54,
    PrintMediaSize_JapanChou3Envelope	= 55,
    PrintMediaSize_JapanChou3EnvelopeRotated	= 56,
    PrintMediaSize_JapanChou4Envelope	= 57,
    PrintMediaSize_JapanChou4EnvelopeRotated	= 58,
    PrintMediaSize_JapanDoubleHagakiPostcard	= 59,
    PrintMediaSize_JapanDoubleHagakiPostcardRotated	= 60,
    PrintMediaSize_JapanHagakiPostcard	= 61,
    PrintMediaSize_JapanHagakiPostcardRotated	= 62,
    PrintMediaSize_JapanKaku2Envelope	= 63,
    PrintMediaSize_JapanKaku2EnvelopeRotated	= 64,
    PrintMediaSize_JapanKaku3Envelope	= 65,
    PrintMediaSize_JapanKaku3EnvelopeRotated	= 66,
    PrintMediaSize_JapanLPhoto	= 67,
    PrintMediaSize_JapanQuadrupleHagakiPostcard = 68,
    PrintMediaSize_JapanYou1Envelope	= 69,
    PrintMediaSize_JapanYou2Envelope	= 70,
    PrintMediaSize_JapanYou3Envelope	= 71,
    PrintMediaSize_JapanYou4Envelope	= 72,
    PrintMediaSize_JapanYou4EnvelopeRotated	= 73,
    PrintMediaSize_JapanYou6Envelope	= 74,
    PrintMediaSize_JapanYou6EnvelopeRotated	= 75,
    PrintMediaSize_JisB0	= 76,
    PrintMediaSize_JisB1	= 77,
    PrintMediaSize_JisB10	= 78,
    PrintMediaSize_JisB2	= 79,
    PrintMediaSize_JisB3	= 80,
    PrintMediaSize_JisB4	= 81,
    PrintMediaSize_JisB4Rotated = 82,
    PrintMediaSize_JisB5	= 83,
    PrintMediaSize_JisB5Rotated = 84,
    PrintMediaSize_JisB6	= 85,
    PrintMediaSize_JisB6Rotated = 86,
    PrintMediaSize_JisB7	= 87,
    PrintMediaSize_JisB8	= 88,
    PrintMediaSize_JisB9	= 89,
    PrintMediaSize_NorthAmerica10x11	= 90,
    PrintMediaSize_NorthAmerica10x12	= 91,
    PrintMediaSize_NorthAmerica10x14	= 92,
    PrintMediaSize_NorthAmerica11x17	= 93,
    PrintMediaSize_NorthAmerica14x17	= 94,
    PrintMediaSize_NorthAmerica4x6	= 95,
    PrintMediaSize_NorthAmerica4x8	= 96,
    PrintMediaSize_NorthAmerica5x7	= 97,
    PrintMediaSize_NorthAmerica8x10	= 98,
    PrintMediaSize_NorthAmerica9x11	= 99,
    PrintMediaSize_NorthAmericaArchitectureASheet	= 100,
    PrintMediaSize_NorthAmericaArchitectureBSheet	= 101,
    PrintMediaSize_NorthAmericaArchitectureCSheet	= 102,
    PrintMediaSize_NorthAmericaArchitectureDSheet	= 103,
    PrintMediaSize_NorthAmericaArchitectureESheet	= 104,
    PrintMediaSize_NorthAmericaCSheet	= 105,
    PrintMediaSize_NorthAmericaDSheet	= 106,
    PrintMediaSize_NorthAmericaESheet	= 107,
    PrintMediaSize_NorthAmericaExecutive	= 108,
    PrintMediaSize_NorthAmericaGermanLegalFanfold	= 109,
    PrintMediaSize_NorthAmericaGermanStandardFanfold	= 110,
    PrintMediaSize_NorthAmericaLegal	= 111,
    PrintMediaSize_NorthAmericaLegalExtra	= 112,
    PrintMediaSize_NorthAmericaLetter	= 113,
    PrintMediaSize_NorthAmericaLetterExtra	= 114,
    PrintMediaSize_NorthAmericaLetterPlus	= 115,
    PrintMediaSize_NorthAmericaLetterRotated	= 116,
    PrintMediaSize_NorthAmericaMonarchEnvelope	= 117,
    PrintMediaSize_NorthAmericaNote	= 118,
    PrintMediaSize_NorthAmericaNumber10Envelope = 119,
    PrintMediaSize_NorthAmericaNumber10EnvelopeRotated	= 120,
    PrintMediaSize_NorthAmericaNumber11Envelope = 121,
    PrintMediaSize_NorthAmericaNumber12Envelope = 122,
    PrintMediaSize_NorthAmericaNumber14Envelope = 123,
    PrintMediaSize_NorthAmericaNumber9Envelope	= 124,
    PrintMediaSize_NorthAmericaPersonalEnvelope = 125,
    PrintMediaSize_NorthAmericaQuarto	= 126,
    PrintMediaSize_NorthAmericaStatement	= 127,
    PrintMediaSize_NorthAmericaSuperA	= 128,
    PrintMediaSize_NorthAmericaSuperB	= 129,
    PrintMediaSize_NorthAmericaTabloid	= 130,
    PrintMediaSize_NorthAmericaTabloidExtra	= 131,
    PrintMediaSize_OtherMetricA3Plus	= 132,
    PrintMediaSize_OtherMetricA4Plus	= 133,
    PrintMediaSize_OtherMetricFolio	= 134,
    PrintMediaSize_OtherMetricInviteEnvelope	= 135,
    PrintMediaSize_OtherMetricItalianEnvelope	= 136,
    PrintMediaSize_Prc10Envelope	= 137,
    PrintMediaSize_Prc10EnvelopeRotated = 138,
    PrintMediaSize_Prc16K	= 139,
    PrintMediaSize_Prc16KRotated	= 140,
    PrintMediaSize_Prc1Envelope = 141,
    PrintMediaSize_Prc1EnvelopeRotated	= 142,
    PrintMediaSize_Prc2Envelope = 143,
    PrintMediaSize_Prc2EnvelopeRotated	= 144,
    PrintMediaSize_Prc32K	= 145,
    PrintMediaSize_Prc32KBig	= 146,
    PrintMediaSize_Prc32KRotated	= 147,
    PrintMediaSize_Prc3Envelope = 148,
    PrintMediaSize_Prc3EnvelopeRotated	= 149,
    PrintMediaSize_Prc4Envelope = 150,
    PrintMediaSize_Prc4EnvelopeRotated	= 151,
    PrintMediaSize_Prc5Envelope = 152,
    PrintMediaSize_Prc5EnvelopeRotated	= 153,
    PrintMediaSize_Prc6Envelope = 154,
    PrintMediaSize_Prc6EnvelopeRotated	= 155,
    PrintMediaSize_Prc7Envelope = 156,
    PrintMediaSize_Prc7EnvelopeRotated	= 157,
    PrintMediaSize_Prc8Envelope = 158,
    PrintMediaSize_Prc8EnvelopeRotated	= 159,
    PrintMediaSize_Prc9Envelope = 160,
    PrintMediaSize_Prc9EnvelopeRotated	= 161,
    PrintMediaSize_Roll04Inch	= 162,
    PrintMediaSize_Roll06Inch	= 163,
    PrintMediaSize_Roll08Inch	= 164,
    PrintMediaSize_Roll12Inch	= 165,
    PrintMediaSize_Roll15Inch	= 166,
    PrintMediaSize_Roll18Inch	= 167,
    PrintMediaSize_Roll22Inch	= 168,
    PrintMediaSize_Roll24Inch	= 169,
    PrintMediaSize_Roll30Inch	= 170,
    PrintMediaSize_Roll36Inch	= 171,
    PrintMediaSize_Roll54Inch	= 172
    }

.enum PrintMediaType {
    PrintMediaType_Default	= 0,
    PrintMediaType_NotAvailable = 1,
    PrintMediaType_PrinterCustom	= 2,
    PrintMediaType_AutoSelect	= 3,
    PrintMediaType_Archival	= 4,
    PrintMediaType_BackPrintFilm	= 5,
    PrintMediaType_Bond = 6,
    PrintMediaType_CardStock	= 7,
    PrintMediaType_Continuous	= 8,
    PrintMediaType_EnvelopePlain	= 9,
    PrintMediaType_EnvelopeWindow	= 10,
    PrintMediaType_Fabric	= 11,
    PrintMediaType_HighResolution	= 12,
    PrintMediaType_Label	= 13,
    PrintMediaType_MultiLayerForm	= 14,
    PrintMediaType_MultiPartForm	= 15,
    PrintMediaType_Photographic = 16,
    PrintMediaType_PhotographicFilm	= 17,
    PrintMediaType_PhotographicGlossy	= 18,
    PrintMediaType_PhotographicHighGloss	= 19,
    PrintMediaType_PhotographicMatte	= 20,
    PrintMediaType_PhotographicSatin	= 21,
    PrintMediaType_PhotographicSemiGloss	= 22,
    PrintMediaType_Plain	= 23,
    PrintMediaType_Screen	= 24,
    PrintMediaType_ScreenPaged	= 25,
    PrintMediaType_Stationery	= 26,
    PrintMediaType_TabStockFull = 27,
    PrintMediaType_TabStockPreCut	= 28,
    PrintMediaType_Transparency = 29,
    PrintMediaType_TShirtTransfer	= 30,
    PrintMediaType_None = 31
    }

.enum PrintOrientation {
    PrintOrientation_Default	= 0,
    PrintOrientation_NotAvailable	= 1,
    PrintOrientation_PrinterCustom	= 2,
    PrintOrientation_Portrait	= 3,
    PrintOrientation_PortraitFlipped	= 4,
    PrintOrientation_Landscape	= 5,
    PrintOrientation_LandscapeFlipped	= 6
    }

.enum PrintQuality {
    PrintQuality_Default	= 0,
    PrintQuality_NotAvailable	= 1,
    PrintQuality_PrinterCustom	= 2,
    PrintQuality_Automatic	= 3,
    PrintQuality_Draft	= 4,
    PrintQuality_Fax	= 5,
    PrintQuality_High	= 6,
    PrintQuality_Normal = 7,
    PrintQuality_Photographic	= 8,
    PrintQuality_Text	= 9
    }

.enum PrintColorMode {
    PrintColorMode_Default	= 0,
    PrintColorMode_NotAvailable = 1,
    PrintColorMode_PrinterCustom	= 2,
    PrintColorMode_Color	= 3,
    PrintColorMode_Grayscale	= 4,
    PrintColorMode_Monochrome	= 5
    }

.enum PrintDuplex {
    PrintDuplex_Default = 0,
    PrintDuplex_NotAvailable	= 1,
    PrintDuplex_PrinterCustom	= 2,
    PrintDuplex_OneSided	= 3,
    PrintDuplex_TwoSidedShortEdge	= 4,
    PrintDuplex_TwoSidedLongEdge	= 5
    }

.enum PrintCollation {
    PrintCollation_Default	= 0,
    PrintCollation_NotAvailable = 1,
    PrintCollation_PrinterCustom	= 2,
    PrintCollation_Collated	= 3,
    PrintCollation_Uncollated	= 4
    }

.enum PrintStaple {
    PrintStaple_Default = 0,
    PrintStaple_NotAvailable	= 1,
    PrintStaple_PrinterCustom	= 2,
    PrintStaple_None	= 3,
    PrintStaple_StapleTopLeft	= 4,
    PrintStaple_StapleTopRight	= 5,
    PrintStaple_StapleBottomLeft	= 6,
    PrintStaple_StapleBottomRight	= 7,
    PrintStaple_StapleDualLeft	= 8,
    PrintStaple_StapleDualRight = 9,
    PrintStaple_StapleDualTop	= 10,
    PrintStaple_StapleDualBottom	= 11,
    PrintStaple_SaddleStitch	= 12
    }

.enum PrintHolePunch {
    PrintHolePunch_Default	= 0,
    PrintHolePunch_NotAvailable = 1,
    PrintHolePunch_PrinterCustom	= 2,
    PrintHolePunch_None = 3,
    PrintHolePunch_LeftEdge	= 4,
    PrintHolePunch_RightEdge	= 5,
    PrintHolePunch_TopEdge	= 6,
    PrintHolePunch_BottomEdge	= 7
    }

.enum PrintBinding {
    PrintBinding_Default	= 0,
    PrintBinding_NotAvailable	= 1,
    PrintBinding_PrinterCustom	= 2,
    PrintBinding_None	= 3,
    PrintBinding_Bale	= 4,
    PrintBinding_BindBottom	= 5,
    PrintBinding_BindLeft	= 6,
    PrintBinding_BindRight	= 7,
    PrintBinding_BindTop	= 8,
    PrintBinding_Booklet	= 9,
    PrintBinding_EdgeStitchBottom	= 10,
    PrintBinding_EdgeStitchLeft = 11,
    PrintBinding_EdgeStitchRight	= 12,
    PrintBinding_EdgeStitchTop	= 13,
    PrintBinding_Fold	= 14,
    PrintBinding_JogOffset	= 15,
    PrintBinding_Trim	= 16
    }

.enum PrintTaskCompletion {
    PrintTaskCompletion_Abandoned	= 0,
    PrintTaskCompletion_Canceled	= 1,
    PrintTaskCompletion_Failed	= 2,
    PrintTaskCompletion_Submitted	= 3
    }

.template PrintPageDescription
    PageSize		Windows::Foundation::Size <>
    ImageableRect	Windows::Foundation::Rect <>
    DpiX		UINT32 ?
    DpiY		UINT32 ?
   .ends

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskSourceRequestedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskSourceRequestedHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IPrintTaskSourceRequestedHandler, "6C109FA8-5CB6-4B3A-8663-F39CB02DC9B4")

.comdef IPrintTaskSourceRequestedHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskOptionsCoreProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskOptionsCoreProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskOptionsCoreProperties <L"Windows.Graphics.Printing.IPrintTaskOptionsCoreProperties">
DEFINE_IIDX(IPrintTaskOptionsCoreProperties, "C1B71832-9E93-4E55-814B-3326A59EFCE1")

.comdef IPrintTaskOptionsCoreProperties : public IInspectable

    put_MediaSize	proc :Windows::Graphics::Printing::PrintMediaSize
    get_MediaSize	proc :ptr
    put_MediaType	proc :Windows::Graphics::Printing::PrintMediaType
    get_MediaType	proc :ptr
    put_Orientation	proc :Windows::Graphics::Printing::PrintOrientation
    get_Orientation	proc :ptr
    put_PrintQuality	proc :Windows::Graphics::Printing::PrintQuality
    get_PrintQuality	proc :ptr
    put_ColorMode	proc :Windows::Graphics::Printing::PrintColorMode
    get_ColorMode	proc :ptr
    put_Duplex		proc :Windows::Graphics::Printing::PrintDuplex
    get_Duplex		proc :ptr
    put_Collation	proc :Windows::Graphics::Printing::PrintCollation
    get_Collation	proc :ptr
    put_Staple		proc :Windows::Graphics::Printing::PrintStaple
    get_Staple		proc :ptr
    put_HolePunch	proc :Windows::Graphics::Printing::PrintHolePunch
    get_HolePunch	proc :ptr
    put_Binding		proc :Windows::Graphics::Printing::PrintBinding
    get_Binding		proc :ptr
    get_MinCopies	proc :ptr
    get_MaxCopies	proc :ptr
    put_NumberOfCopies	proc :UINT32
    get_NumberOfCopies	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskOptionsCoreUIConfiguration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskOptionsCoreUIConfiguration_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskOptionsCoreUIConfiguration <L"Windows.Graphics.Printing.IPrintTaskOptionsCoreUIConfiguration">
DEFINE_IIDX(IPrintTaskOptionsCoreUIConfiguration, "62E69E23-9A1E-4336-B74F-3CC7F4CFF709")

.comdef IPrintTaskOptionsCoreUIConfiguration : public IInspectable

    get_DisplayedOptions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskOptionsCore_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskOptionsCore_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskOptionsCore <L"Windows.Graphics.Printing.IPrintTaskOptionsCore">
DEFINE_IIDX(IPrintTaskOptionsCore, "1BDBB474-4ED1-41EB-BE3C-72D18ED67337")

.comdef IPrintTaskOptionsCore : public IInspectable

    GetPageDescription	proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIStandardPrintTaskOptionsStatic_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIStandardPrintTaskOptionsStatic_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IStandardPrintTaskOptionsStatic <L"Windows.Graphics.Printing.IStandardPrintTaskOptionsStatic">
DEFINE_IIDX(IStandardPrintTaskOptionsStatic, "B4483D26-0DD0-4CD4-BAFF-930FC7D6A574")

.comdef IStandardPrintTaskOptionsStatic : public IInspectable

    get_MediaSize	proc :ptr
    get_MediaType	proc :ptr
    get_Orientation	proc :ptr
    get_PrintQuality	proc :ptr
    get_ColorMode	proc :ptr
    get_Duplex		proc :ptr
    get_Collation	proc :ptr
    get_Staple		proc :ptr
    get_HolePunch	proc :ptr
    get_Binding		proc :ptr
    get_Copies		proc :ptr
    get_NUp		proc :ptr
    get_InputBin	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintDocumentSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintDocumentSource_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintDocumentSource <L"Windows.Graphics.Printing.IPrintDocumentSource">
DEFINE_IIDX(IPrintDocumentSource, "DEDC0C30-F1EB-47DF-AAE6-ED5427511F01")

.comdef IPrintDocumentSource : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskProgressingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskProgressingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskProgressingEventArgs <L"Windows.Graphics.Printing.IPrintTaskProgressingEventArgs">
DEFINE_IIDX(IPrintTaskProgressingEventArgs, "810CD3CB-B410-4282-A073-5AC378234174")

.comdef IPrintTaskProgressingEventArgs : public IInspectable

    get_DocumentPageCount proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskCompletedEventArgs <L"Windows.Graphics.Printing.IPrintTaskCompletedEventArgs">
DEFINE_IIDX(IPrintTaskCompletedEventArgs, "5BCD34AF-24E9-4C10-8D07-14C346BA3FCE")

.comdef IPrintTaskCompletedEventArgs : public IInspectable

    get_Completion	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTask_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTask_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTask <L"Windows.Graphics.Printing.IPrintTask">
DEFINE_IIDX(IPrintTask, "61D80247-6CF6-4FAD-84E2-A5E82E2D4CEB")

.comdef IPrintTask : public IInspectable

    get_Properties	proc :ptr
    get_Source		proc :ptr
    get_Options		proc :ptr
    add_Previewing	proc :ptr, :ptr
    remove_Previewing	proc :EventRegistrationToken
    add_Submitting	proc :ptr, :ptr
    remove_Submitting	proc :EventRegistrationToken
    add_Progressing	proc :ptr, :ptr
    remove_Progressing	proc :EventRegistrationToken
    add_Completed	proc :ptr, :ptr
    remove_Completed	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskTargetDeviceSupport_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskTargetDeviceSupport_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskTargetDeviceSupport <L"Windows.Graphics.Printing.IPrintTaskTargetDeviceSupport">
DEFINE_IIDX(IPrintTaskTargetDeviceSupport, "295D70C0-C2CB-4B7D-B0EA-93095091A220")

.comdef IPrintTaskTargetDeviceSupport : public IInspectable

    put_IsPrinterTargetEnabled proc :boolean
    get_IsPrinterTargetEnabled proc :ptr
    put_Is3DManufacturingTargetEnabled proc :boolean
    get_Is3DManufacturingTargetEnabled proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskSourceRequestedDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskSourceRequestedDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskSourceRequestedDeferral <L"Windows.Graphics.Printing.IPrintTaskSourceRequestedDeferral">
DEFINE_IIDX(IPrintTaskSourceRequestedDeferral, "4A1560D1-6992-4D9D-8555-4CA4563FB166")

.comdef IPrintTaskSourceRequestedDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskSourceRequestedArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskSourceRequestedArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskSourceRequestedArgs <L"Windows.Graphics.Printing.IPrintTaskSourceRequestedArgs">
DEFINE_IIDX(IPrintTaskSourceRequestedArgs, "F9F067BE-F456-41F0-9C98-5CE73E851410")

.comdef IPrintTaskSourceRequestedArgs : public IInspectable

    get_Deadline	proc :ptr
    SetSource		proc :ptr
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskRequestedDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskRequestedDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskRequestedDeferral <L"Windows.Graphics.Printing.IPrintTaskRequestedDeferral">
DEFINE_IIDX(IPrintTaskRequestedDeferral, "CFEFB3F0-CE3E-42C7-9496-64800C622C44")

.comdef IPrintTaskRequestedDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskRequest <L"Windows.Graphics.Printing.IPrintTaskRequest">
DEFINE_IIDX(IPrintTaskRequest, "6FF61E2E-2722-4240-A67C-F364849A17F3")

.comdef IPrintTaskRequest : public IInspectable

    get_Deadline	proc :ptr
    CreatePrintTask	proc :HSTRING, :ptr, :ptr
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintTaskRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintTaskRequestedEventArgs <L"Windows.Graphics.Printing.IPrintTaskRequestedEventArgs">
DEFINE_IIDX(IPrintTaskRequestedEventArgs, "D0AFF924-A31B-454C-A7B6-5D0CC522FC16")

.comdef IPrintTaskRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintManagerStatic_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintManagerStatic_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintManagerStatic <L"Windows.Graphics.Printing.IPrintManagerStatic">
DEFINE_IIDX(IPrintManagerStatic, "58185DCD-E634-4654-84F0-E0152A8217AC")

.comdef IPrintManagerStatic : public IInspectable

    GetForCurrentView	proc :ptr
    ShowPrintUIAsync	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CPrinting_CIPrintManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Printing_IPrintManager <L"Windows.Graphics.Printing.IPrintManager">
DEFINE_IIDX(IPrintManager, "FF2A9694-8C99-44FD-AE4A-19D9AA9A0F0A")

.comdef IPrintManager : public IInspectable

    add_PrintTaskRequested proc :ptr, :ptr
    remove_PrintTaskRequested proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskOptions_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskOptions_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTaskOptions <L"Windows.Graphics.Printing.PrintTaskOptions">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_StandardPrintTaskOptions_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_StandardPrintTaskOptions_DEFINED
define RuntimeClass_Windows_Graphics_Printing_StandardPrintTaskOptions <L"Windows.Graphics.Printing.StandardPrintTaskOptions">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskProgressingEventArgs_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskProgressingEventArgs_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTaskProgressingEventArgs <L"Windows.Graphics.Printing.PrintTaskProgressingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskCompletedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskCompletedEventArgs_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTaskCompletedEventArgs <L"Windows.Graphics.Printing.PrintTaskCompletedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTask_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTask_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTask <L"Windows.Graphics.Printing.PrintTask">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskSourceRequestedDeferral_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskSourceRequestedDeferral_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTaskSourceRequestedDeferral <L"Windows.Graphics.Printing.PrintTaskSourceRequestedDeferral">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskSourceRequestedArgs_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskSourceRequestedArgs_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTaskSourceRequestedArgs <L"Windows.Graphics.Printing.PrintTaskSourceRequestedArgs">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskRequestedDeferral_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskRequestedDeferral_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTaskRequestedDeferral <L"Windows.Graphics.Printing.PrintTaskRequestedDeferral">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskRequest_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskRequest_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTaskRequest <L"Windows.Graphics.Printing.PrintTaskRequest">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintTaskRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintTaskRequestedEventArgs <L"Windows.Graphics.Printing.PrintTaskRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Printing_PrintManager_DEFINED
define RUNTIMECLASS_Windows_Graphics_Printing_PrintManager_DEFINED
define RuntimeClass_Windows_Graphics_Printing_PrintManager <L"Windows.Graphics.Printing.PrintManager">
endif

endif
