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

ifndef __windows2Eui2Examl_h__
define __windows2Eui2Examl_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.ApplicationModel.inc
include Windows.ApplicationModel.Activation.inc

.namespace Windows
.namespace UI
.namespace Xaml

.enum ApplicationTheme {
    ApplicationTheme_Light	= 0,
    ApplicationTheme_Dark	= 1
    }

.enum DurationType {
    DurationType_Automatic	= 0,
    DurationType_TimeSpan	= 1,
    DurationType_Forever	= 2
    }

.enum ElementTheme {
    ElementTheme_Default	= 0,
    ElementTheme_Light	= 1,
    ElementTheme_Dark	= 2
    }

.enum FlowDirection {
    FlowDirection_LeftToRight	= 0,
    FlowDirection_RightToLeft	= 1
    }

.enum FocusState {
    FocusState_Unfocused	= 0,
    FocusState_Pointer	= 1,
    FocusState_Keyboard = 2,
    FocusState_Programmatic	= 3
    }

.enum FontCapitals {
    FontCapitals_Normal = 0,
    FontCapitals_AllSmallCaps	= 1,
    FontCapitals_SmallCaps	= 2,
    FontCapitals_AllPetiteCaps	= 3,
    FontCapitals_PetiteCaps	= 4,
    FontCapitals_Unicase	= 5,
    FontCapitals_Titling	= 6
    }

.enum FontEastAsianLanguage {
    FontEastAsianLanguage_Normal	= 0,
    FontEastAsianLanguage_HojoKanji	= 1,
    FontEastAsianLanguage_Jis04 = 2,
    FontEastAsianLanguage_Jis78 = 3,
    FontEastAsianLanguage_Jis83 = 4,
    FontEastAsianLanguage_Jis90 = 5,
    FontEastAsianLanguage_NlcKanji	= 6,
    FontEastAsianLanguage_Simplified	= 7,
    FontEastAsianLanguage_Traditional	= 8,
    FontEastAsianLanguage_TraditionalNames	= 9
    }

.enum FontEastAsianWidths {
    FontEastAsianWidths_Normal	= 0,
    FontEastAsianWidths_Full	= 1,
    FontEastAsianWidths_Half	= 2,
    FontEastAsianWidths_Proportional	= 3,
    FontEastAsianWidths_Quarter = 4,
    FontEastAsianWidths_Third	= 5
    }

.enum FontFraction {
    FontFraction_Normal = 0,
    FontFraction_Stacked	= 1,
    FontFraction_Slashed	= 2
    }

.enum FontNumeralAlignment {
    FontNumeralAlignment_Normal = 0,
    FontNumeralAlignment_Proportional	= 1,
    FontNumeralAlignment_Tabular	= 2
    }

.enum FontNumeralStyle {
    FontNumeralStyle_Normal	= 0,
    FontNumeralStyle_Lining	= 1,
    FontNumeralStyle_OldStyle	= 2
    }

.enum FontVariants {
    FontVariants_Normal = 0,
    FontVariants_Superscript	= 1,
    FontVariants_Subscript	= 2,
    FontVariants_Ordinal	= 3,
    FontVariants_Inferior	= 4,
    FontVariants_Ruby	= 5
    }

.enum GridUnitType {
    GridUnitType_Auto	= 0,
    GridUnitType_Pixel	= 1,
    GridUnitType_Star	= 2
    }

.enum HorizontalAlignment {
    HorizontalAlignment_Left	= 0,
    HorizontalAlignment_Center	= 1,
    HorizontalAlignment_Right	= 2,
    HorizontalAlignment_Stretch = 3
    }

.enum LineStackingStrategy {
    LineStackingStrategy_MaxHeight	= 0,
    LineStackingStrategy_BlockLineHeight	= 1,
    LineStackingStrategy_BaselineToBaseline	= 2
    }

.enum OpticalMarginAlignment {
    OpticalMarginAlignment_None = 0,
    OpticalMarginAlignment_TrimSideBearings	= 1
    }

.enum TextAlignment {
    TextAlignment_Center	= 0,
    TextAlignment_Left	= 1,
    TextAlignment_Right = 2,
    TextAlignment_Justify	= 3
    }

.enum TextLineBounds {
    TextLineBounds_Full = 0,
    TextLineBounds_TrimToCapHeight	= 1,
    TextLineBounds_TrimToBaseline	= 2,
    TextLineBounds_Tight	= 3
    }

.enum TextReadingOrder {
    TextReadingOrder_Default	= 0,
    TextReadingOrder_DetectFromContent	= 1
    }

.enum TextTrimming {
    TextTrimming_None		= 0,
    TextTrimming_CharacterEllipsis = 1,
    TextTrimming_WordEllipsis	= 2,
    TextTrimming_Clip		= 3
    }

.enum TextWrapping {
    TextWrapping_NoWrap		= 1,
    TextWrapping_Wrap		= 2,
    TextWrapping_WrapWholeWords = 3
    }

.enum VerticalAlignment {
    VerticalAlignment_Top	= 0,
    VerticalAlignment_Center	= 1,
    VerticalAlignment_Bottom	= 2,
    VerticalAlignment_Stretch	= 3
    }

.enum Visibility {
    Visibility_Visible		= 0,
    Visibility_Collapsed	= 1
    }

.template CornerRadius
    TopLeft		DOUBLE ?
    TopRight		DOUBLE ?
    BottomRight		DOUBLE ?
    BottomLeft		DOUBLE ?
   .ends

.template Duration
    TimeSpan		Windows::Foundation::TimeSpan <>
    Type		Windows::UI::Xaml::DurationType ?
   .ends

.template GridLength
    Value		DOUBLE ?
    GridUnitType	Windows::UI::Xaml::GridUnitType ?
   .ends

.template Thickness
    Left		DOUBLE ?
    Top			DOUBLE ?
    Right		DOUBLE ?
    Bottom		DOUBLE ?
   .ends

.endn
.endn
.endn

include Windows.UI.Xaml.Automation.Peers.inc
include windows.foundation.collections.inc

ifndef __windows2Eui2Examl2Einterop_h__
 include windows.ui.xaml.interop.inc
endif
ifndef __windows2Eui2Examl2Econtrols2Eprimitives_h__
 include windows.ui.xaml.controls.primitives.inc
endif
ifndef __windows2Eui2Examl2Einput_h__
 include windows.ui.xaml.input.inc
endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CDependencyObject, "29f8d454-905d-587e-b9d8-bfd418805a65")

.comdef __FIIterator_1_Windows__CUI__CXaml__CDependencyObject : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CDependencyObject, "f66c6bd3-55b4-5bbb-b82a-6d9ce383091a")

.comdef __FIIterable_1_Windows__CUI__CXaml__CDependencyObject : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CResourceDictionary_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CResourceDictionary_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CResourceDictionary, "849a2f3a-2e5e-58a8-b76e-73450ea680c0")

.comdef __FIIterator_1_Windows__CUI__CXaml__CResourceDictionary : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CResourceDictionary_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CResourceDictionary_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CResourceDictionary, "eaf20635-a462-5397-bee1-f7a09504653b")

.comdef __FIIterable_1_Windows__CUI__CXaml__CResourceDictionary : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CSetterBase_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CSetterBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CSetterBase, "3198322e-2527-58d1-8d92-9d22b977d255")

.comdef __FIIterator_1_Windows__CUI__CXaml__CSetterBase : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CSetterBase_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CSetterBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CSetterBase, "aafe70cb-90a8-5719-bd3e-f0b066ed1626")

.comdef __FIIterable_1_Windows__CUI__CXaml__CSetterBase : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CTriggerAction_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CTriggerAction_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CTriggerAction, "fa0c6c2e-f81a-543c-b8b6-5c18d36711b0")

.comdef __FIIterator_1_Windows__CUI__CXaml__CTriggerAction : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CTriggerAction_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CTriggerAction_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CTriggerAction, "a9d34579-8a6a-58bf-85fd-0f37324e2397")

.comdef __FIIterable_1_Windows__CUI__CXaml__CTriggerAction : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CTriggerBase_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CTriggerBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CTriggerBase, "d317c81a-5dda-59f6-8ce9-44f2877bfae8")

.comdef __FIIterator_1_Windows__CUI__CXaml__CTriggerBase : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CTriggerBase_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CTriggerBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CTriggerBase, "d697764f-4e15-5888-a2a5-7b4cf0eb07a5")

.comdef __FIIterable_1_Windows__CUI__CXaml__CTriggerBase : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CUIElement, "1d1f9d60-d53b-57f7-b144-8f7c487846e8")

.comdef __FIIterator_1_Windows__CUI__CXaml__CUIElement : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CUIElement, "42e26ae1-d357-57e8-bb48-f75c9ff69d91")

.comdef __FIIterable_1_Windows__CUI__CXaml__CUIElement : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CVisualState_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CVisualState_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CVisualState, "f20bd8bc-6dda-5c71-bd39-c57137c5a4ed")

.comdef __FIIterator_1_Windows__CUI__CXaml__CVisualState : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CVisualState_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CVisualState_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CVisualState, "1fb071a3-a064-5619-a94e-23c01a4cbf3a")

.comdef __FIIterable_1_Windows__CUI__CXaml__CVisualState : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CVisualStateGroup_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CVisualStateGroup_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CVisualStateGroup, "09e95afc-3096-50c1-b05a-acae1a8cb92e")

.comdef __FIIterator_1_Windows__CUI__CXaml__CVisualStateGroup : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CVisualStateGroup_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CVisualStateGroup_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CVisualStateGroup, "5d9ab411-e991-55b0-b16c-a400a50a93df")

.comdef __FIIterable_1_Windows__CUI__CXaml__CVisualStateGroup : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CVisualTransition_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CVisualTransition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CVisualTransition, "5ae4cb71-a8b8-506b-b31b-62db11f66257")

.comdef __FIIterator_1_Windows__CUI__CXaml__CVisualTransition : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CVisualTransition_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CVisualTransition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CVisualTransition, "017a8eb0-e942-5f25-a945-205a9470b9fc")

.comdef __FIIterable_1_Windows__CUI__CXaml__CVisualTransition : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CDependencyObject, "fe750d77-1307-5df2-a021-1c7a8d6b80ad")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CDependencyObject : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CDependencyObject, "771b857e-ab5c-5db8-a021-397c92cdc44c")

.comdef __FIVector_1_Windows__CUI__CXaml__CDependencyObject : public IInspectable

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

ifndef ____FVectorChangedEventHandler_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
define ____FVectorChangedEventHandler_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FVectorChangedEventHandler_1_Windows__CUI__CXaml__CDependencyObject, "b62dec93-a7a5-5ff5-b2d2-6bd20ca0bd4d")

.comdef __FVectorChangedEventHandler_1_Windows__CUI__CXaml__CDependencyObject : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIObservableVector_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
define ____FIObservableVector_1_Windows__CUI__CXaml__CDependencyObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIObservableVector_1_Windows__CUI__CXaml__CDependencyObject, "fac6f4d2-96fd-5ceb-80bf-46ac6529fc65")

.comdef __FIObservableVector_1_Windows__CUI__CXaml__CDependencyObject : public IInspectable

    add_VectorChanged	proc :ptr, :ptr
    remove_VectorChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CResourceDictionary_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CResourceDictionary_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CResourceDictionary, "36ce8ed8-c1a9-55b7-86dc-b41b8ed8edf4")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CResourceDictionary : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CSetterBase_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CSetterBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CSetterBase, "88eef29a-842b-55c2-a936-2b9d75e923e5")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CSetterBase : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CTriggerAction_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CTriggerAction_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CTriggerAction, "b6c7ce15-6a2f-5bbb-9efb-49be20b928a1")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CTriggerAction : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CTriggerBase_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CTriggerBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CTriggerBase, "6c97f246-4010-5c09-9722-39fcc3d0647d")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CTriggerBase : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CUIElement, "f3864c10-14a4-5516-b1d9-63b6579429b1")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CUIElement : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CVisualState_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CVisualState_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CVisualState, "eb031bb8-8028-5164-9699-1eb288383fa8")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CVisualState : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CVisualStateGroup_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CVisualStateGroup_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CVisualStateGroup, "adf1746e-8936-546a-9733-8626880c4ce1")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CVisualStateGroup : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CVisualTransition_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CVisualTransition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CVisualTransition, "bb3d4d2f-3406-5f29-812a-bb1e437863da")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CVisualTransition : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CResourceDictionary_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CResourceDictionary_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CResourceDictionary, "fe820a0c-694d-518b-8ec5-372993f6ceaf")

.comdef __FIVector_1_Windows__CUI__CXaml__CResourceDictionary : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CSetterBase_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CSetterBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CSetterBase, "bd55a7fd-7501-5519-9ffb-d0074240db61")

.comdef __FIVector_1_Windows__CUI__CXaml__CSetterBase : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CTriggerAction_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CTriggerAction_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CTriggerAction, "a488f35d-9ffc-5250-ac19-9416777b175a")

.comdef __FIVector_1_Windows__CUI__CXaml__CTriggerAction : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CTriggerBase_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CTriggerBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CTriggerBase, "9149863b-b78b-5fb6-a0a1-9ebf6bbc3407")

.comdef __FIVector_1_Windows__CUI__CXaml__CTriggerBase : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CUIElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CUIElement, "b4c1e3ac-8768-5b9d-a661-f63330b8507b")

.comdef __FIVector_1_Windows__CUI__CXaml__CUIElement : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CVisualState_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CVisualState_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CVisualState, "5b6d19b8-bc0c-5a77-a406-c01c12fd46c3")

.comdef __FIVector_1_Windows__CUI__CXaml__CVisualState : public IInspectable

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

ifndef ____FIVector_1_Windows__CUI__CXaml__CVisualStateGroup_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CVisualStateGroup_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CVisualStateGroup, "729a0392-675e-58e4-b6a3-0457bb9ea968")

.comdef __FIVector_1_Windows__CUI__CXaml__CVisualStateGroup : public IInspectable

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
ifndef ____FIVector_1_Windows__CUI__CXaml__CVisualTransition_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CVisualTransition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CVisualTransition, "5aebeb8c-7ef7-5975-ba0a-6c19a529bb72")

.comdef __FIVector_1_Windows__CUI__CXaml__CVisualTransition : public IInspectable

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

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CRoutedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CRoutedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CRoutedEventArgs, "a16eff3c-cc37-554c-8f10-0f7e6e2bcaad")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CRoutedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CFrameworkElement_Windows__CUI__CXaml__CDataContextChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CFrameworkElement_Windows__CUI__CXaml__CDataContextChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CFrameworkElement_Windows__CUI__CXaml__CDataContextChangedEventArgs, "b01c8a21-de6f-5edd-8796-300e3fe66382")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CFrameworkElement_Windows__CUI__CXaml__CDataContextChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Xaml

ifndef ____x_ABI_CWindows_CUI_CXaml_CICreateDefaultValueCallback_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CICreateDefaultValueCallback_INTERFACE_DEFINED__
DEFINE_IIDX(ICreateDefaultValueCallback, "D6ECB12C-15B5-4EC8-B95C-CDD208F08153")

.comdef ICreateDefaultValueCallback : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIPropertyChangedCallback_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIPropertyChangedCallback_INTERFACE_DEFINED__
DEFINE_IIDX(IPropertyChangedCallback, "5A9F8A25-D142-44A4-8231-FD676724F29B")

.comdef IPropertyChangedCallback : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIApplicationInitializationCallback_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIApplicationInitializationCallback_INTERFACE_DEFINED__
DEFINE_IIDX(IApplicationInitializationCallback, "B6351C55-C284-46E4-8310-FB0967FAB76F")

.comdef IApplicationInitializationCallback : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIBindingFailedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIBindingFailedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IBindingFailedEventHandler, "136B1782-54BA-420D-A1AA-82828721CDE6")

.comdef IBindingFailedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDependencyPropertyChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDependencyPropertyChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDependencyPropertyChangedEventHandler, "09223E5A-75BE-4499-8180-1DDC005421C0")

.comdef IDependencyPropertyChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDragEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDragEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDragEventHandler, "2AB1A205-1E73-4BCF-AABC-57B97E21961D")

.comdef IDragEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIExceptionRoutedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIExceptionRoutedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IExceptionRoutedEventHandler, "68E0E810-F6EA-42BC-855B-5D9B67E6A262")

.comdef IExceptionRoutedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIRoutedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIRoutedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IRoutedEventHandler, "A856E674-B0B6-4BC3-BBA8-1BA06E40D4B5")

.comdef IRoutedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISizeChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISizeChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISizeChangedEventHandler, "1115B13C-25D2-480B-89DC-EB3DCBD6B7FA")

.comdef ISizeChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISuspendingEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISuspendingEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISuspendingEventHandler, "23429465-E36A-40E2-B139-A4704602A6E1")

.comdef ISuspendingEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIUnhandledExceptionEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIUnhandledExceptionEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IUnhandledExceptionEventHandler, "9274E6BD-49A1-4958-BEEE-D0E19587B6E3")

.comdef IUnhandledExceptionEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualStateChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualStateChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IVisualStateChangedEventHandler, "E6D5BBD5-E029-43A6-B36D-84A81042D774")

.comdef IVisualStateChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIWindowActivatedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIWindowActivatedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IWindowActivatedEventHandler, "18026348-8619-4C7B-B534-CED45D9DE219")

.comdef IWindowActivatedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIWindowClosedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIWindowClosedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IWindowClosedEventHandler, "0DB89161-20D7-45DF-9122-BA89576703BA")

.comdef IWindowClosedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIWindowSizeChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIWindowSizeChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IWindowSizeChangedEventHandler, "5C21C742-2CED-4FD9-BA38-7118D40E966B")

.comdef IWindowSizeChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIWindowVisibilityChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIWindowVisibilityChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IWindowVisibilityChangedEventHandler, "10406AD6-B090-4A4A-B2AD-D682DF27130F")

.comdef IWindowVisibilityChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CICornerRadiusHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CICornerRadiusHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ICornerRadiusHelper <L"Windows.UI.Xaml.ICornerRadiusHelper">
DEFINE_IIDX(ICornerRadiusHelper, "FD7BE182-1CDB-4288-B8C8-85EE79297BFC")

.comdef ICornerRadiusHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CICornerRadiusHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CICornerRadiusHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ICornerRadiusHelperStatics <L"Windows.UI.Xaml.ICornerRadiusHelperStatics">
DEFINE_IIDX(ICornerRadiusHelperStatics, "F4A1F659-D4D4-451F-A387-D6BF4B2451D4")

.comdef ICornerRadiusHelperStatics : public IInspectable

    FromRadii		proc :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :ptr
    FromUniformRadius	proc :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDurationHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDurationHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDurationHelper <L"Windows.UI.Xaml.IDurationHelper">
DEFINE_IIDX(IDurationHelper, "25C1659F-4497-4135-940F-EE96F4D6E934")

.comdef IDurationHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDurationHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDurationHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDurationHelperStatics <L"Windows.UI.Xaml.IDurationHelperStatics">
DEFINE_IIDX(IDurationHelperStatics, "BC88093E-3547-4EC0-B519-FFA8F9C4838C")

.comdef IDurationHelperStatics : public IInspectable

    get_Automatic	proc :ptr
    get_Forever		proc :ptr
    Compare		proc :Windows::UI::Xaml::Duration, :Windows::UI::Xaml::Duration, :ptr
    FromTimeSpan	proc :Windows::Foundation::TimeSpan, :ptr
    GetHasTimeSpan	proc :Windows::UI::Xaml::Duration, :ptr
    _Add		proc :Windows::UI::Xaml::Duration, :Windows::UI::Xaml::Duration, :ptr
    Equals		proc :Windows::UI::Xaml::Duration, :Windows::UI::Xaml::Duration, :ptr
    Subtract		proc :Windows::UI::Xaml::Duration, :Windows::UI::Xaml::Duration, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIGridLengthHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIGridLengthHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IGridLengthHelper <L"Windows.UI.Xaml.IGridLengthHelper">
DEFINE_IIDX(IGridLengthHelper, "7A826CE1-07A0-4083-B6D1-B1D917B976AC")

.comdef IGridLengthHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIGridLengthHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIGridLengthHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IGridLengthHelperStatics <L"Windows.UI.Xaml.IGridLengthHelperStatics">
DEFINE_IIDX(IGridLengthHelperStatics, "9D457B9B-019F-4266-8872-215F198F6A9D")

.comdef IGridLengthHelperStatics : public IInspectable

    get_Auto		proc :ptr
    FromPixels		proc :DOUBLE, :ptr
    FromValueAndType	proc :DOUBLE, :Windows::UI::Xaml::GridUnitType, :ptr
    GetIsAbsolute	proc :Windows::UI::Xaml::GridLength, :ptr
    GetIsAuto		proc :Windows::UI::Xaml::GridLength, :ptr
    GetIsStar		proc :Windows::UI::Xaml::GridLength, :ptr
    Equals		proc :Windows::UI::Xaml::GridLength, :Windows::UI::Xaml::GridLength, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIPointHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIPointHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IPointHelper <L"Windows.UI.Xaml.IPointHelper">
DEFINE_IIDX(IPointHelper, "727BDD92-64B0-49CF-A321-A9793E73E2E7")

.comdef IPointHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIPointHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIPointHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IPointHelperStatics <L"Windows.UI.Xaml.IPointHelperStatics">
DEFINE_IIDX(IPointHelperStatics, "015ACA75-76D8-4B7E-8A33-7D79204691EE")

.comdef IPointHelperStatics : public IInspectable

    FromCoordinates	proc :FLOAT, :FLOAT, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIRectHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIRectHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IRectHelper <L"Windows.UI.Xaml.IRectHelper">
DEFINE_IIDX(IRectHelper, "A38781E2-4BFB-4EE2-AFE5-89F31B37478D")

.comdef IRectHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIRectHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIRectHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IRectHelperStatics <L"Windows.UI.Xaml.IRectHelperStatics">
DEFINE_IIDX(IRectHelperStatics, "5EE163E4-C17E-494F-B580-2F0574FC3A15")

.comdef IRectHelperStatics : public IInspectable

    get_Empty		proc :ptr
    FromCoordinatesAndDimensions proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    FromPoints		proc :Windows::Foundation::Point, :Windows::Foundation::Point, :ptr
    FromLocationAndSize proc :Windows::Foundation::Point, :Windows::Foundation::Size, :ptr
    GetIsEmpty		proc :Windows::Foundation::Rect, :ptr
    GetBottom		proc :Windows::Foundation::Rect, :ptr
    GetLeft		proc :Windows::Foundation::Rect, :ptr
    GetRight		proc :Windows::Foundation::Rect, :ptr
    GetTop		proc :Windows::Foundation::Rect, :ptr
    Contains		proc :Windows::Foundation::Rect, :Windows::Foundation::Point, :ptr
    Equals		proc :Windows::Foundation::Rect, :Windows::Foundation::Rect, :ptr
    Intersect		proc :Windows::Foundation::Rect, :Windows::Foundation::Rect, :ptr
    UnionWithPoint	proc :Windows::Foundation::Rect, :Windows::Foundation::Point, :ptr
    UnionWithRect	proc :Windows::Foundation::Rect, :Windows::Foundation::Rect, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISizeHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISizeHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ISizeHelper <L"Windows.UI.Xaml.ISizeHelper">
DEFINE_IIDX(ISizeHelper, "E7225A94-5D03-4A03-BA94-967FC68FCEFE")

.comdef ISizeHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISizeHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISizeHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ISizeHelperStatics <L"Windows.UI.Xaml.ISizeHelperStatics">
DEFINE_IIDX(ISizeHelperStatics, "6286C5B2-CF78-4915-AA40-76004A165F5E")

.comdef ISizeHelperStatics : public IInspectable

    get_Empty		proc :ptr
    FromDimensions	proc :FLOAT, :FLOAT, :ptr
    GetIsEmpty		proc :Windows::Foundation::Size, :ptr
    Equals		proc :Windows::Foundation::Size, :Windows::Foundation::Size, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIThicknessHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIThicknessHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IThicknessHelper <L"Windows.UI.Xaml.IThicknessHelper">
DEFINE_IIDX(IThicknessHelper, "A86BAE4B-1E8F-4EEB-9013-0B2838A97B34")

.comdef IThicknessHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIThicknessHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIThicknessHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IThicknessHelperStatics <L"Windows.UI.Xaml.IThicknessHelperStatics">
DEFINE_IIDX(IThicknessHelperStatics, "C0991A7C-070C-4DA6-8784-01CA800EB73A")

.comdef IThicknessHelperStatics : public IInspectable

    FromLengths		proc :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :ptr
    FromUniformLength	proc :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIApplicationInitializationCallbackParams_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIApplicationInitializationCallbackParams_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IApplicationInitializationCallbackParams <L"Windows.UI.Xaml.IApplicationInitializationCallbackParams">
DEFINE_IIDX(IApplicationInitializationCallbackParams, "751B792E-5772-4488-8B87-F547FAA64474")

.comdef IApplicationInitializationCallbackParams : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIBindingFailedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIBindingFailedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IBindingFailedEventArgs <L"Windows.UI.Xaml.IBindingFailedEventArgs">
DEFINE_IIDX(IBindingFailedEventArgs, "32C1D013-4DBD-446D-BBB8-0DE35048A449")

.comdef IBindingFailedEventArgs : public IInspectable

    get_Message		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDataContextChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDataContextChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDataContextChangedEventArgs <L"Windows.UI.Xaml.IDataContextChangedEventArgs">
DEFINE_IIDX(IDataContextChangedEventArgs, "7DA68E21-0B8F-4F9F-A143-F8E7780136A2")

.comdef IDataContextChangedEventArgs : public IInspectable

    get_NewValue	proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDataTemplate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDataTemplate_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDataTemplate <L"Windows.UI.Xaml.IDataTemplate">
DEFINE_IIDX(IDataTemplate, "9910AEC7-8AB5-4118-9BC6-09F45A35073D")

.comdef IDataTemplate : public IInspectable

    LoadContent		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDataTemplateFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDataTemplateFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDataTemplateFactory <L"Windows.UI.Xaml.IDataTemplateFactory">
DEFINE_IIDX(IDataTemplateFactory, "51ED9D7E-2B53-475B-9C88-0C1832C8351A")

.comdef IDataTemplateFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDataTemplateKey_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDataTemplateKey_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDataTemplateKey <L"Windows.UI.Xaml.IDataTemplateKey">
DEFINE_IIDX(IDataTemplateKey, "873B6C28-CCEB-4B61-86FA-B2CEC39CC2FA")

.comdef IDataTemplateKey : public IInspectable

    get_DataType	proc :ptr
    put_DataType	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDataTemplateKeyFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDataTemplateKeyFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDataTemplateKeyFactory <L"Windows.UI.Xaml.IDataTemplateKeyFactory">
DEFINE_IIDX(IDataTemplateKeyFactory, "E96B2959-D982-4152-91CB-DE0E4DFD7693")

.comdef IDataTemplateKeyFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
    CreateInstanceWithType proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDebugSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDebugSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDebugSettings <L"Windows.UI.Xaml.IDebugSettings">
DEFINE_IIDX(IDebugSettings, "3D451F98-C6A7-4D17-8398-D83A067183D8")

.comdef IDebugSettings : public IInspectable

    get_EnableFrameRateCounter proc :ptr
    put_EnableFrameRateCounter proc :boolean
    get_IsBindingTracingEnabled proc :ptr
    put_IsBindingTracingEnabled proc :boolean
    get_IsOverdrawHeatMapEnabled proc :ptr
    put_IsOverdrawHeatMapEnabled proc :boolean
    add_BindingFailed	proc :ptr, :ptr
    remove_BindingFailed proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDebugSettings2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDebugSettings2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDebugSettings2 <L"Windows.UI.Xaml.IDebugSettings2">
DEFINE_IIDX(IDebugSettings2, "48D37585-E1A6-469B-83C8-30825037119E")

.comdef IDebugSettings2 : public IInspectable

    get_EnableRedrawRegions proc :ptr
    put_EnableRedrawRegions proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDependencyObject_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDependencyObject_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDependencyObject <L"Windows.UI.Xaml.IDependencyObject">
DEFINE_IIDX(IDependencyObject, "5C526665-F60E-4912-AF59-5FE0680F089D")

.comdef IDependencyObject : public IInspectable

    GetValue		proc :ptr, :ptr
    SetValue		proc :ptr, :ptr
    ClearValue		proc :ptr
    ReadLocalValue	proc :ptr, :ptr
    GetAnimationBaseValue proc :ptr, :ptr
    get_Dispatcher	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDependencyObjectFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDependencyObjectFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDependencyObjectFactory <L"Windows.UI.Xaml.IDependencyObjectFactory">
DEFINE_IIDX(IDependencyObjectFactory, "9A03AF92-7D8A-4937-884F-ECF34FE02ACB")

.comdef IDependencyObjectFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDependencyObjectCollectionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDependencyObjectCollectionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDependencyObjectCollectionFactory <L"Windows.UI.Xaml.IDependencyObjectCollectionFactory">
DEFINE_IIDX(IDependencyObjectCollectionFactory, "051E79FF-B3A8-49EE-B5AF-AC8F68B649E4")

.comdef IDependencyObjectCollectionFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDependencyProperty_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDependencyProperty_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDependencyProperty <L"Windows.UI.Xaml.IDependencyProperty">
DEFINE_IIDX(IDependencyProperty, "85B13970-9BC4-4E96-ACF1-30C8FD3D55C8")

.comdef IDependencyProperty : public IInspectable

    GetMetadata		proc :Windows::UI::Xaml::Interop::TypeName, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDependencyPropertyStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDependencyPropertyStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDependencyPropertyStatics <L"Windows.UI.Xaml.IDependencyPropertyStatics">
DEFINE_IIDX(IDependencyPropertyStatics, "49E5F28F-8259-4D5C-AAE0-83D56DBB68D9")

.comdef IDependencyPropertyStatics : public IInspectable

    get_UnsetValue	proc :ptr
    Register		proc :HSTRING, :Windows::UI::Xaml::Interop::TypeName, :Windows::UI::Xaml::Interop::TypeName, :ptr, :ptr
    RegisterAttached	proc :HSTRING, :Windows::UI::Xaml::Interop::TypeName, :Windows::UI::Xaml::Interop::TypeName, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDependencyPropertyChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDependencyPropertyChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDependencyPropertyChangedEventArgs <L"Windows.UI.Xaml.IDependencyPropertyChangedEventArgs">
DEFINE_IIDX(IDependencyPropertyChangedEventArgs, "81212C2B-24D0-4957-ABC3-224470A93A4E")

.comdef IDependencyPropertyChangedEventArgs : public IInspectable

    get_Property	proc :ptr
    get_OldValue	proc :ptr
    get_NewValue	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDispatcherTimer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDispatcherTimer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDispatcherTimer <L"Windows.UI.Xaml.IDispatcherTimer">
DEFINE_IIDX(IDispatcherTimer, "D160CE46-CD22-4F5F-8C97-40E61DA3E2DC")

.comdef IDispatcherTimer : public IInspectable

    get_Interval	proc :ptr
    put_Interval	proc :Windows::Foundation::TimeSpan
    get_IsEnabled	proc :ptr
    add_Tick		proc :ptr, :ptr
    remove_Tick		proc :EventRegistrationToken
    Start		proc
    Stop		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDispatcherTimerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDispatcherTimerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDispatcherTimerFactory <L"Windows.UI.Xaml.IDispatcherTimerFactory">
DEFINE_IIDX(IDispatcherTimerFactory, "E9961E6E-3626-403A-AFE0-040D58165632")

.comdef IDispatcherTimerFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIDragEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIDragEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IDragEventArgs <L"Windows.UI.Xaml.IDragEventArgs">
DEFINE_IIDX(IDragEventArgs, "B440C7C3-02B4-4980-9342-25DAE1C0F188")

.comdef IDragEventArgs : public IInspectable

    get_Handled		proc :ptr
    put_Handled		proc :boolean
    get_Data		proc :ptr
    put_Data		proc :ptr
    GetPosition		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIEventTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIEventTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IEventTrigger <L"Windows.UI.Xaml.IEventTrigger">
DEFINE_IIDX(IEventTrigger, "DEF8F855-0B49-4087-B1A9-B8B38488F786")

.comdef IEventTrigger : public IInspectable

    get_RoutedEvent	proc :ptr
    put_RoutedEvent	proc :ptr
    get_Actions		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIExceptionRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIExceptionRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IExceptionRoutedEventArgs <L"Windows.UI.Xaml.IExceptionRoutedEventArgs">
DEFINE_IIDX(IExceptionRoutedEventArgs, "DD9FF16A-4B62-4A6C-A49D-0671EF6136BE")

.comdef IExceptionRoutedEventArgs : public IInspectable

    get_ErrorMessage	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIExceptionRoutedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIExceptionRoutedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IExceptionRoutedEventArgsFactory <L"Windows.UI.Xaml.IExceptionRoutedEventArgsFactory">
DEFINE_IIDX(IExceptionRoutedEventArgsFactory, "BBA9826D-5D7A-44E7-B893-B2AE0DD24273")

.comdef IExceptionRoutedEventArgsFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIApplication_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIApplication_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IApplication <L"Windows.UI.Xaml.IApplication">
DEFINE_IIDX(IApplication, "74B861A1-7487-46A9-9A6E-C78B512726C5")

.comdef IApplication : public IInspectable

    get_Resources	proc :ptr
    put_Resources	proc :ptr
    get_DebugSettings	proc :ptr
    get_RequestedTheme	proc :ptr
    put_RequestedTheme	proc :Windows::UI::Xaml::ApplicationTheme
    add_UnhandledException proc :ptr, :ptr
    remove_UnhandledException proc :EventRegistrationToken
    add_Suspending	proc :ptr, :ptr
    remove_Suspending	proc :EventRegistrationToken
    add_Resuming	proc :ptr, :ptr
    remove_Resuming	proc :EventRegistrationToken
    Exit		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIApplicationOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIApplicationOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IApplicationOverrides <L"Windows.UI.Xaml.IApplicationOverrides">
DEFINE_IIDX(IApplicationOverrides, "25F99FF7-9347-459A-9FAC-B2D0E11C1A0F")

.comdef IApplicationOverrides : public IInspectable

    OnActivated		proc :ptr
    OnLaunched		proc :ptr
    OnFileActivated	proc :ptr
    OnSearchActivated	proc :ptr
    OnShareTargetActivated proc :ptr
    OnFileOpenPickerActivated proc :ptr
    OnFileSavePickerActivated proc :ptr
    OnCachedFileUpdaterActivated proc :ptr
    OnWindowCreated	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIApplicationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIApplicationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IApplicationStatics <L"Windows.UI.Xaml.IApplicationStatics">
DEFINE_IIDX(IApplicationStatics, "06499997-F7B4-45FE-B763-7577D1D3CB4A")

.comdef IApplicationStatics : public IInspectable

    get_Current		proc :ptr
    Start		proc :ptr
    LoadComponent	proc :ptr, :ptr
    LoadComponentWithResourceLocation proc :ptr, :ptr, :Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIApplicationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIApplicationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IApplicationFactory <L"Windows.UI.Xaml.IApplicationFactory">
DEFINE_IIDX(IApplicationFactory, "93BBE361-BE5A-4EE3-B4A3-95118DC97A89")

.comdef IApplicationFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElement_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElement_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkElement <L"Windows.UI.Xaml.IFrameworkElement">
DEFINE_IIDX(IFrameworkElement, "A391D09B-4A99-4B7C-9D8D-6FA5D01F6FBF")

.comdef IFrameworkElement : public IInspectable

    get_Triggers	proc :ptr
    get_Resources	proc :ptr
    put_Resources	proc :ptr
    get_Tag		proc :ptr
    put_Tag		proc :ptr
    get_Language	proc :ptr
    put_Language	proc :HSTRING
    get_ActualWidth	proc :ptr
    get_ActualHeight	proc :ptr
    get_Width		proc :ptr
    put_Width		proc :DOUBLE
    get_Height		proc :ptr
    put_Height		proc :DOUBLE
    get_MinWidth	proc :ptr
    put_MinWidth	proc :DOUBLE
    get_MaxWidth	proc :ptr
    put_MaxWidth	proc :DOUBLE
    get_MinHeight	proc :ptr
    put_MinHeight	proc :DOUBLE
    get_MaxHeight	proc :ptr
    put_MaxHeight	proc :DOUBLE
    get_HorizontalAlignment proc :ptr
    put_HorizontalAlignment proc :Windows::UI::Xaml::HorizontalAlignment
    get_VerticalAlignment proc :ptr
    put_VerticalAlignment proc :Windows::UI::Xaml::VerticalAlignment
    get_Margin		proc :ptr
    put_Margin		proc :Windows::UI::Xaml::Thickness
    get_Name		proc :ptr
    put_Name		proc :HSTRING
    get_BaseUri		proc :ptr
    get_DataContext	proc :ptr
    put_DataContext	proc :ptr
    get_Style		proc :ptr
    put_Style		proc :ptr
    get_Parent		proc :ptr
    get_FlowDirection	proc :ptr
    put_FlowDirection	proc :Windows::UI::Xaml::FlowDirection
    add_Loaded		proc :ptr, :ptr
    remove_Loaded	proc :EventRegistrationToken
    add_Unloaded	proc :ptr, :ptr
    remove_Unloaded	proc :EventRegistrationToken
    add_SizeChanged	proc :ptr, :ptr
    remove_SizeChanged	proc :EventRegistrationToken
    add_LayoutUpdated	proc :ptr, :ptr
    remove_LayoutUpdated proc :EventRegistrationToken
    FindName		proc :HSTRING, :ptr
    SetBinding		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkElementOverrides <L"Windows.UI.Xaml.IFrameworkElementOverrides">
DEFINE_IIDX(IFrameworkElementOverrides, "DA007E54-B3C2-4B9A-AA8E-D3F071262B97")

.comdef IFrameworkElementOverrides : public IInspectable

    MeasureOverride	proc :Windows::Foundation::Size, :ptr
    ArrangeOverride	proc :Windows::Foundation::Size, :ptr
    OnApplyTemplate	proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkElementStatics <L"Windows.UI.Xaml.IFrameworkElementStatics">
DEFINE_IIDX(IFrameworkElementStatics, "48383032-FBEB-4F8A-AED2-EE21FB27A57B")

.comdef IFrameworkElementStatics : public IInspectable

    get_TagProperty	proc :ptr
    get_LanguageProperty proc :ptr
    get_ActualWidthProperty proc :ptr
    get_ActualHeightProperty proc :ptr
    get_WidthProperty	proc :ptr
    get_HeightProperty	proc :ptr
    get_MinWidthProperty proc :ptr
    get_MaxWidthProperty proc :ptr
    get_MinHeightProperty proc :ptr
    get_MaxHeightProperty proc :ptr
    get_HorizontalAlignmentProperty proc :ptr
    get_VerticalAlignmentProperty proc :ptr
    get_MarginProperty	proc :ptr
    get_NameProperty	proc :ptr
    get_DataContextProperty proc :ptr
    get_StyleProperty	proc :ptr
    get_FlowDirectionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkElementFactory <L"Windows.UI.Xaml.IFrameworkElementFactory">
DEFINE_IIDX(IFrameworkElementFactory, "DEAEE126-03CA-4966-B576-604CCE93B5E8")

.comdef IFrameworkElementFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElement2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElement2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkElement2 <L"Windows.UI.Xaml.IFrameworkElement2">
DEFINE_IIDX(IFrameworkElement2, "F19104BE-422A-4904-A52F-EE72010429E5")

.comdef IFrameworkElement2 : public IInspectable

    get_RequestedTheme	proc :ptr
    put_RequestedTheme	proc :Windows::UI::Xaml::ElementTheme
    add_DataContextChanged proc :ptr, :ptr
    remove_DataContextChanged proc :EventRegistrationToken
    GetBindingExpression proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementOverrides2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementOverrides2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkElementOverrides2 <L"Windows.UI.Xaml.IFrameworkElementOverrides2">
DEFINE_IIDX(IFrameworkElementOverrides2, "CB5CD2B9-E3B4-458C-B64E-1434FD1BD88A")

.comdef IFrameworkElementOverrides2 : public IInspectable

    GoToElementStateCore proc :HSTRING, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkElementStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkElementStatics2 <L"Windows.UI.Xaml.IFrameworkElementStatics2">
DEFINE_IIDX(IFrameworkElementStatics2, "9695DB02-C0D8-4FA2-B100-3FA2DF8B9538")

.comdef IFrameworkElementStatics2 : public IInspectable

    get_RequestedThemeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkTemplate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkTemplate_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkTemplate <L"Windows.UI.Xaml.IFrameworkTemplate">
DEFINE_IIDX(IFrameworkTemplate, "A1E254D8-A446-4A27-9A9D-A0F59E1258A5")

.comdef IFrameworkTemplate : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkTemplateFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkTemplateFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkTemplateFactory <L"Windows.UI.Xaml.IFrameworkTemplateFactory">
DEFINE_IIDX(IFrameworkTemplateFactory, "1A78A0A5-937D-46D4-832B-94FF14DAB061")

.comdef IFrameworkTemplateFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkView <L"Windows.UI.Xaml.IFrameworkView">
DEFINE_IIDX(IFrameworkView, "DDBA664B-B603-47AA-942D-3833174F0D80")

.comdef IFrameworkView : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIFrameworkViewSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIFrameworkViewSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IFrameworkViewSource <L"Windows.UI.Xaml.IFrameworkViewSource">
DEFINE_IIDX(IFrameworkViewSource, "E3B077DA-35AD-4B09-B5B2-27420041BA9F")

.comdef IFrameworkViewSource : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIMediaFailedRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIMediaFailedRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IMediaFailedRoutedEventArgs <L"Windows.UI.Xaml.IMediaFailedRoutedEventArgs">
DEFINE_IIDX(IMediaFailedRoutedEventArgs, "46D1FA8D-5149-4153-BA3C-B03E64EE531E")

.comdef IMediaFailedRoutedEventArgs : public IInspectable

    get_ErrorTrace	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIPropertyMetadata_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIPropertyMetadata_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IPropertyMetadata <L"Windows.UI.Xaml.IPropertyMetadata">
DEFINE_IIDX(IPropertyMetadata, "814EF30D-8D18-448A-8644-F2CB51E70380")

.comdef IPropertyMetadata : public IInspectable

    get_DefaultValue	proc :ptr
    get_CreateDefaultValueCallback proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIPropertyMetadataStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIPropertyMetadataStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IPropertyMetadataStatics <L"Windows.UI.Xaml.IPropertyMetadataStatics">
DEFINE_IIDX(IPropertyMetadataStatics, "3B01077A-6E06-45E9-8B5C-AF243458C062")

.comdef IPropertyMetadataStatics : public IInspectable

    CreateWithDefaultValue proc :ptr, :ptr
    CreateWithDefaultValueAndCallback proc :ptr, :ptr, :ptr
    CreateWithFactory	proc :ptr, :ptr
    CreateWithFactoryAndCallback proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIPropertyMetadataFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIPropertyMetadataFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IPropertyMetadataFactory <L"Windows.UI.Xaml.IPropertyMetadataFactory">
DEFINE_IIDX(IPropertyMetadataFactory, "C1B81CC0-57CD-4F2F-B0A9-E1801B28F76B")

.comdef IPropertyMetadataFactory : public IInspectable

    CreateInstanceWithDefaultValue proc :ptr, :ptr, :ptr, :ptr
    CreateInstanceWithDefaultValueAndCallback proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIPropertyPath_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIPropertyPath_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IPropertyPath <L"Windows.UI.Xaml.IPropertyPath">
DEFINE_IIDX(IPropertyPath, "300E5D8A-1FF3-4D2C-95EC-27F81DEBACB8")

.comdef IPropertyPath : public IInspectable

    get_Path		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIPropertyPathFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIPropertyPathFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IPropertyPathFactory <L"Windows.UI.Xaml.IPropertyPathFactory">
DEFINE_IIDX(IPropertyPathFactory, "4E4CDF99-9826-4E56-847C-CA055F162905")

.comdef IPropertyPathFactory : public IInspectable

    CreateInstance	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIResourceDictionary_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIResourceDictionary_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IResourceDictionary <L"Windows.UI.Xaml.IResourceDictionary">
DEFINE_IIDX(IResourceDictionary, "C1EA4F24-D6DE-4191-8E3A-F48601F7489C")

.comdef IResourceDictionary : public IInspectable

    get_Source		proc :ptr
    put_Source		proc :ptr
    get_MergedDictionaries proc :ptr
    get_ThemeDictionaries proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIResourceDictionaryFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIResourceDictionaryFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IResourceDictionaryFactory <L"Windows.UI.Xaml.IResourceDictionaryFactory">
DEFINE_IIDX(IResourceDictionaryFactory, "EA3639B5-31B7-4271-92C9-7C9584A91C22")

.comdef IResourceDictionaryFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIRoutedEvent_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIRoutedEvent_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IRoutedEvent <L"Windows.UI.Xaml.IRoutedEvent">
DEFINE_IIDX(IRoutedEvent, "A6B25818-43C1-4C70-865C-7BDD5A32E327")

.comdef IRoutedEvent : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IRoutedEventArgs <L"Windows.UI.Xaml.IRoutedEventArgs">
DEFINE_IIDX(IRoutedEventArgs, "5C985AC6-D802-4B38-A223-BF070C43FEDF")

.comdef IRoutedEventArgs : public IInspectable

    get_OriginalSource	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIRoutedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIRoutedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IRoutedEventArgsFactory <L"Windows.UI.Xaml.IRoutedEventArgsFactory">
DEFINE_IIDX(IRoutedEventArgsFactory, "B61C4D87-70E5-412E-B520-1A41EE76BBF4")

.comdef IRoutedEventArgsFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISetter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISetter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ISetter <L"Windows.UI.Xaml.ISetter">
DEFINE_IIDX(ISetter, "A73DED29-B4AE-4A81-BE85-E690BA0D3B6E")

.comdef ISetter : public IInspectable

    get_Property	proc :ptr
    put_Property	proc :ptr
    get_Value		proc :ptr
    put_Value		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISetterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISetterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ISetterFactory <L"Windows.UI.Xaml.ISetterFactory">
DEFINE_IIDX(ISetterFactory, "D3CA3D42-09B1-49D5-8891-E7B5648E02A2")

.comdef ISetterFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISetterBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISetterBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ISetterBase <L"Windows.UI.Xaml.ISetterBase">
DEFINE_IIDX(ISetterBase, "418BE27C-2AC4-4F22-8097-DEA3AEEB2FB3")

.comdef ISetterBase : public IInspectable

    get_IsSealed	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISetterBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISetterBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ISetterBaseFactory <L"Windows.UI.Xaml.ISetterBaseFactory">
DEFINE_IIDX(ISetterBaseFactory, "81F8AD60-1CE8-469D-A667-16E37CEF8BA9")

.comdef ISetterBaseFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISetterBaseCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISetterBaseCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ISetterBaseCollection <L"Windows.UI.Xaml.ISetterBaseCollection">
DEFINE_IIDX(ISetterBaseCollection, "03C40CA8-909E-4117-811C-A4529496BDF1")

.comdef ISetterBaseCollection : public IInspectable

    get_IsSealed	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CISizeChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CISizeChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ISizeChangedEventArgs <L"Windows.UI.Xaml.ISizeChangedEventArgs">
DEFINE_IIDX(ISizeChangedEventArgs, "D5312E60-5CC1-42A1-920C-1AF46BE2F986")

.comdef ISizeChangedEventArgs : public IInspectable

    get_PreviousSize	proc :ptr
    get_NewSize		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIStyle_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIStyle_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IStyle <L"Windows.UI.Xaml.IStyle">
DEFINE_IIDX(IStyle, "C4A9F225-9DB7-4A7D-B6D1-F74EDB9293C2")

.comdef IStyle : public IInspectable

    get_IsSealed	proc :ptr
    get_Setters		proc :ptr
    get_TargetType	proc :ptr
    put_TargetType	proc :Windows::UI::Xaml::Interop::TypeName
    get_BasedOn		proc :ptr
    put_BasedOn		proc :ptr
    Seal		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIStyleFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIStyleFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IStyleFactory <L"Windows.UI.Xaml.IStyleFactory">
DEFINE_IIDX(IStyleFactory, "A36824E3-3D81-4CE5-AA51-8B410F602FCD")

.comdef IStyleFactory : public IInspectable

    CreateInstance	proc :Windows::UI::Xaml::Interop::TypeName, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CITriggerAction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CITriggerAction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ITriggerAction <L"Windows.UI.Xaml.ITriggerAction">
DEFINE_IIDX(ITriggerAction, "A2C0DF02-63D5-4B46-9B83-0868D3079621")

.comdef ITriggerAction : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CITriggerActionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CITriggerActionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ITriggerActionFactory <L"Windows.UI.Xaml.ITriggerActionFactory">
DEFINE_IIDX(ITriggerActionFactory, "68D2C0B9-3289-414F-8F6E-C6B97AEDDA03")

.comdef ITriggerActionFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CITriggerBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CITriggerBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ITriggerBase <L"Windows.UI.Xaml.ITriggerBase">
DEFINE_IIDX(ITriggerBase, "E7EA222F-DEE6-4393-A8B2-8923D641F395")

.comdef ITriggerBase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CITriggerBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CITriggerBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_ITriggerBaseFactory <L"Windows.UI.Xaml.ITriggerBaseFactory">
DEFINE_IIDX(ITriggerBaseFactory, "6A3B9E57-FC5D-42D0-8CB9-CA50667AF746")

.comdef ITriggerBaseFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIUIElement_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIUIElement_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IUIElement <L"Windows.UI.Xaml.IUIElement">
DEFINE_IIDX(IUIElement, "676D0BE9-B65C-41C6-BA40-58CF87F201C1")

.comdef IUIElement : public IInspectable

    get_DesiredSize	proc :ptr
    get_AllowDrop	proc :ptr
    put_AllowDrop	proc :boolean
    get_Opacity		proc :ptr
    put_Opacity		proc :DOUBLE
    get_Clip		proc :ptr
    put_Clip		proc :ptr
    get_RenderTransform proc :ptr
    put_RenderTransform proc :ptr
    get_Projection	proc :ptr
    put_Projection	proc :ptr
    get_RenderTransformOrigin proc :ptr
    put_RenderTransformOrigin proc :Windows::Foundation::Point
    get_IsHitTestVisible proc :ptr
    put_IsHitTestVisible proc :boolean
    get_Visibility	proc :ptr
    put_Visibility	proc :Windows::UI::Xaml::Visibility
    get_RenderSize	proc :ptr
    get_UseLayoutRounding proc :ptr
    put_UseLayoutRounding proc :boolean
    get_Transitions	proc :ptr
    put_Transitions	proc :ptr
    get_CacheMode	proc :ptr
    put_CacheMode	proc :ptr
    get_IsTapEnabled	proc :ptr
    put_IsTapEnabled	proc :boolean
    get_IsDoubleTapEnabled proc :ptr
    put_IsDoubleTapEnabled proc :boolean
    get_IsRightTapEnabled proc :ptr
    put_IsRightTapEnabled proc :boolean
    get_IsHoldingEnabled proc :ptr
    put_IsHoldingEnabled proc :boolean
    get_ManipulationMode proc :ptr
    put_ManipulationMode proc :Windows::UI::Xaml::Input::ManipulationModes
    get_PointerCaptures proc :ptr
    add_KeyUp		proc :ptr, :ptr
    remove_KeyUp	proc :EventRegistrationToken
    add_KeyDown		proc :ptr, :ptr
    remove_KeyDown	proc :EventRegistrationToken
    add_GotFocus	proc :ptr, :ptr
    remove_GotFocus	proc :EventRegistrationToken
    add_LostFocus	proc :ptr, :ptr
    remove_LostFocus	proc :EventRegistrationToken
    add_DragEnter	proc :ptr, :ptr
    remove_DragEnter	proc :EventRegistrationToken
    add_DragLeave	proc :ptr, :ptr
    remove_DragLeave	proc :EventRegistrationToken
    add_DragOver	proc :ptr, :ptr
    remove_DragOver	proc :EventRegistrationToken
    add_Drop		proc :ptr, :ptr
    remove_Drop		proc :EventRegistrationToken
    add_PointerPressed	proc :ptr, :ptr
    remove_PointerPressed proc :EventRegistrationToken
    add_PointerMoved	proc :ptr, :ptr
    remove_PointerMoved proc :EventRegistrationToken
    add_PointerReleased proc :ptr, :ptr
    remove_PointerReleased proc :EventRegistrationToken
    add_PointerEntered	proc :ptr, :ptr
    remove_PointerEntered proc :EventRegistrationToken
    add_PointerExited	proc :ptr, :ptr
    remove_PointerExited proc :EventRegistrationToken
    add_PointerCaptureLost proc :ptr, :ptr
    remove_PointerCaptureLost proc :EventRegistrationToken
    add_PointerCanceled proc :ptr, :ptr
    remove_PointerCanceled proc :EventRegistrationToken
    add_PointerWheelChanged proc :ptr, :ptr
    remove_PointerWheelChanged proc :EventRegistrationToken
    add_Tapped		proc :ptr, :ptr
    remove_Tapped	proc :EventRegistrationToken
    add_DoubleTapped	proc :ptr, :ptr
    remove_DoubleTapped proc :EventRegistrationToken
    add_Holding		proc :ptr, :ptr
    remove_Holding	proc :EventRegistrationToken
    add_RightTapped	proc :ptr, :ptr
    remove_RightTapped	proc :EventRegistrationToken
    add_ManipulationStarting proc :ptr, :ptr
    remove_ManipulationStarting proc :EventRegistrationToken
    add_ManipulationInertiaStarting proc :ptr, :ptr
    remove_ManipulationInertiaStarting proc :EventRegistrationToken
    add_ManipulationStarted proc :ptr, :ptr
    remove_ManipulationStarted proc :EventRegistrationToken
    add_ManipulationDelta proc :ptr, :ptr
    remove_ManipulationDelta proc :EventRegistrationToken
    add_ManipulationCompleted proc :ptr, :ptr
    remove_ManipulationCompleted proc :EventRegistrationToken
    Measure		proc :Windows::Foundation::Size
    Arrange		proc :Windows::Foundation::Rect
    CapturePointer	proc :ptr, :ptr
    ReleasePointerCapture proc :ptr
    ReleasePointerCaptures proc
    AddHandler		proc :ptr, :ptr, :boolean
    RemoveHandler	proc :ptr, :ptr
    TransformToVisual	proc :ptr, :ptr
    InvalidateMeasure	proc
    InvalidateArrange	proc
    UpdateLayout	proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIUIElementOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIUIElementOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IUIElementOverrides <L"Windows.UI.Xaml.IUIElementOverrides">
DEFINE_IIDX(IUIElementOverrides, "608D2F1D-7858-4AEB-89E4-B54E2C7ED3D3")

.comdef IUIElementOverrides : public IInspectable

    OnCreateAutomationPeer proc :ptr
    OnDisconnectVisualChildren proc
    FindSubElementsForTouchTargeting proc :Windows::Foundation::Point, :Windows::Foundation::Rect, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIUIElementStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIUIElementStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IUIElementStatics <L"Windows.UI.Xaml.IUIElementStatics">
DEFINE_IIDX(IUIElementStatics, "58D3573B-F52C-45BE-988B-A5869564873C")

.comdef IUIElementStatics : public IInspectable

    get_KeyDownEvent	proc :ptr
    get_KeyUpEvent	proc :ptr
    get_PointerEnteredEvent proc :ptr
    get_PointerPressedEvent proc :ptr
    get_PointerMovedEvent proc :ptr
    get_PointerReleasedEvent proc :ptr
    get_PointerExitedEvent proc :ptr
    get_PointerCaptureLostEvent proc :ptr
    get_PointerCanceledEvent proc :ptr
    get_PointerWheelChangedEvent proc :ptr
    get_TappedEvent	proc :ptr
    get_DoubleTappedEvent proc :ptr
    get_HoldingEvent	proc :ptr
    get_RightTappedEvent proc :ptr
    get_ManipulationStartingEvent proc :ptr
    get_ManipulationInertiaStartingEvent proc :ptr
    get_ManipulationStartedEvent proc :ptr
    get_ManipulationDeltaEvent proc :ptr
    get_ManipulationCompletedEvent proc :ptr
    get_DragEnterEvent	proc :ptr
    get_DragLeaveEvent	proc :ptr
    get_DragOverEvent	proc :ptr
    get_DropEvent	proc :ptr
    get_AllowDropProperty proc :ptr
    get_OpacityProperty proc :ptr
    get_ClipProperty	proc :ptr
    get_RenderTransformProperty proc :ptr
    get_ProjectionProperty proc :ptr
    get_RenderTransformOriginProperty proc :ptr
    get_IsHitTestVisibleProperty proc :ptr
    get_VisibilityProperty proc :ptr
    get_UseLayoutRoundingProperty proc :ptr
    get_TransitionsProperty proc :ptr
    get_CacheModeProperty proc :ptr
    get_IsTapEnabledProperty proc :ptr
    get_IsDoubleTapEnabledProperty proc :ptr
    get_IsRightTapEnabledProperty proc :ptr
    get_IsHoldingEnabledProperty proc :ptr
    get_ManipulationModeProperty proc :ptr
    get_PointerCapturesProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIUIElementFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIUIElementFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IUIElementFactory <L"Windows.UI.Xaml.IUIElementFactory">
DEFINE_IIDX(IUIElementFactory, "B9EE93FE-A338-419F-AC32-91DCAADF5D08")

.comdef IUIElementFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIUIElement2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIUIElement2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IUIElement2 <L"Windows.UI.Xaml.IUIElement2">
DEFINE_IIDX(IUIElement2, "676D0BF9-B66C-41D6-BA50-58CF87F201D1")

.comdef IUIElement2 : public IInspectable

    get_CompositeMode	proc :ptr
    put_CompositeMode	proc :Windows::UI::Xaml::Media::ElementCompositeMode
    CancelDirectManipulations proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIUIElementStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIUIElementStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IUIElementStatics2 <L"Windows.UI.Xaml.IUIElementStatics2">
DEFINE_IIDX(IUIElementStatics2, "58D3574B-F53C-45BE-989B-A5869564874C")

.comdef IUIElementStatics2 : public IInspectable

    get_CompositeModeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIUnhandledExceptionEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIUnhandledExceptionEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IUnhandledExceptionEventArgs <L"Windows.UI.Xaml.IUnhandledExceptionEventArgs">
DEFINE_IIDX(IUnhandledExceptionEventArgs, "7230269C-054E-4CF3-86C5-BE90EB6863D5")

.comdef IUnhandledExceptionEventArgs : public IInspectable

    get_Exception	proc :ptr
    get_Message		proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualState_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualState_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualState <L"Windows.UI.Xaml.IVisualState">
DEFINE_IIDX(IVisualState, "6320AFFC-C31A-4450-AFDE-F6EA7BD1F586")

.comdef IVisualState : public IInspectable

    get_Name		proc :ptr
    get_Storyboard	proc :ptr
    put_Storyboard	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualStateChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualStateChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualStateChangedEventArgs <L"Windows.UI.Xaml.IVisualStateChangedEventArgs">
DEFINE_IIDX(IVisualStateChangedEventArgs, "FE216AB1-F31F-4791-8989-C70E1D9B59FF")

.comdef IVisualStateChangedEventArgs : public IInspectable

    get_OldState	proc :ptr
    put_OldState	proc :ptr
    get_NewState	proc :ptr
    put_NewState	proc :ptr
    get_Control		proc :ptr
    put_Control		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualStateGroup_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualStateGroup_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualStateGroup <L"Windows.UI.Xaml.IVisualStateGroup">
DEFINE_IIDX(IVisualStateGroup, "E4F9D9A4-E028-44DE-9B15-4929AE0A26C2")

.comdef IVisualStateGroup : public IInspectable

    get_Name		proc :ptr
    get_Transitions	proc :ptr
    get_States		proc :ptr
    get_CurrentState	proc :ptr
    add_CurrentStateChanged proc :ptr, :ptr
    remove_CurrentStateChanged proc :EventRegistrationToken
    add_CurrentStateChanging proc :ptr, :ptr
    remove_CurrentStateChanging proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManager_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualStateManager <L"Windows.UI.Xaml.IVisualStateManager">
DEFINE_IIDX(IVisualStateManager, "6FDA9F9A-6FAB-4112-9258-1006A3C3476E")

.comdef IVisualStateManager : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManagerOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManagerOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualStateManagerOverrides <L"Windows.UI.Xaml.IVisualStateManagerOverrides">
DEFINE_IIDX(IVisualStateManagerOverrides, "4A66910E-7979-43C8-8FF4-EC6122750006")

.comdef IVisualStateManagerOverrides : public IInspectable

    GoToStateCore	proc :ptr, :ptr, :HSTRING, :ptr, :ptr, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManagerProtected_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManagerProtected_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualStateManagerProtected <L"Windows.UI.Xaml.IVisualStateManagerProtected">
DEFINE_IIDX(IVisualStateManagerProtected, "4B3B8640-B0B7-404C-9EF4-D949640E245D")

.comdef IVisualStateManagerProtected : public IInspectable

    RaiseCurrentStateChanging proc :ptr, :ptr, :ptr, :ptr
    RaiseCurrentStateChanged proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualStateManagerStatics <L"Windows.UI.Xaml.IVisualStateManagerStatics">
DEFINE_IIDX(IVisualStateManagerStatics, "01D0E9E0-D713-414E-A74E-E63EC7AC8C3D")

.comdef IVisualStateManagerStatics : public IInspectable

    GetVisualStateGroups proc :ptr, :ptr
    get_CustomVisualStateManagerProperty proc :ptr
    GetCustomVisualStateManager proc :ptr, :ptr
    SetCustomVisualStateManager proc :ptr, :ptr
    GoToState		proc :ptr, :HSTRING, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManagerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualStateManagerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualStateManagerFactory <L"Windows.UI.Xaml.IVisualStateManagerFactory">
DEFINE_IIDX(IVisualStateManagerFactory, "85E598FD-A575-47B6-9E30-383CD08585F2")

.comdef IVisualStateManagerFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualTransition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualTransition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualTransition <L"Windows.UI.Xaml.IVisualTransition">
DEFINE_IIDX(IVisualTransition, "55C5905E-2BC7-400D-AAA4-1A2981491EE0")

.comdef IVisualTransition : public IInspectable

    get_GeneratedDuration proc :ptr
    put_GeneratedDuration proc :Windows::UI::Xaml::Duration
    get_GeneratedEasingFunction proc :ptr
    put_GeneratedEasingFunction proc :ptr
    get_To		proc :ptr
    put_To		proc :HSTRING
    get_From		proc :ptr
    put_From		proc :HSTRING
    get_Storyboard	proc :ptr
    put_Storyboard	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIVisualTransitionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIVisualTransitionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IVisualTransitionFactory <L"Windows.UI.Xaml.IVisualTransitionFactory">
DEFINE_IIDX(IVisualTransitionFactory, "EA75864F-D1E0-4DAE-B429-89FC322724F4")

.comdef IVisualTransitionFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIWindow_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIWindow_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IWindow <L"Windows.UI.Xaml.IWindow">
DEFINE_IIDX(IWindow, "3276167D-C9F6-462D-9DE2-AE4C1FD8C2E5")

.comdef IWindow : public IInspectable

    get_Bounds		proc :ptr
    get_Visible		proc :ptr
    get_Content		proc :ptr
    put_Content		proc :ptr
    get_CoreWindow	proc :ptr
    get_Dispatcher	proc :ptr
    add_Activated	proc :ptr, :ptr
    remove_Activated	proc :EventRegistrationToken
    add_Closed		proc :ptr, :ptr
    remove_Closed	proc :EventRegistrationToken
    add_SizeChanged	proc :ptr, :ptr
    remove_SizeChanged	proc :EventRegistrationToken
    add_VisibilityChanged proc :ptr, :ptr
    remove_VisibilityChanged proc :EventRegistrationToken
    Activate		proc
    Close		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIWindowStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIWindowStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IWindowStatics <L"Windows.UI.Xaml.IWindowStatics">
DEFINE_IIDX(IWindowStatics, "93328409-4EA1-4AFA-83DC-0C4E73E88BB1")

.comdef IWindowStatics : public IInspectable

    get_Current		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CIWindowCreatedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CIWindowCreatedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_IWindowCreatedEventArgs <L"Windows.UI.Xaml.IWindowCreatedEventArgs">
DEFINE_IIDX(IWindowCreatedEventArgs, "31B71470-FEFF-4654-AF48-9B398AB5772B")

.comdef IWindowCreatedEventArgs : public IInspectable

    get_Window		proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_DependencyObject_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DependencyObject_DEFINED
define RuntimeClass_Windows_UI_Xaml_DependencyObject <L"Windows.UI.Xaml.DependencyObject">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DependencyPropertyChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DependencyPropertyChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_DependencyPropertyChangedEventArgs <L"Windows.UI.Xaml.DependencyPropertyChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_ApplicationInitializationCallbackParams_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_ApplicationInitializationCallbackParams_DEFINED
define RuntimeClass_Windows_UI_Xaml_ApplicationInitializationCallbackParams <L"Windows.UI.Xaml.ApplicationInitializationCallbackParams">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_CornerRadiusHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_CornerRadiusHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_CornerRadiusHelper <L"Windows.UI.Xaml.CornerRadiusHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DurationHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DurationHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_DurationHelper <L"Windows.UI.Xaml.DurationHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_GridLengthHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_GridLengthHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_GridLengthHelper <L"Windows.UI.Xaml.GridLengthHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_PointHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_PointHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_PointHelper <L"Windows.UI.Xaml.PointHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_RectHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_RectHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_RectHelper <L"Windows.UI.Xaml.RectHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_SizeHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_SizeHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_SizeHelper <L"Windows.UI.Xaml.SizeHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_ThicknessHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_ThicknessHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_ThicknessHelper <L"Windows.UI.Xaml.ThicknessHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_BindingFailedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_BindingFailedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_BindingFailedEventArgs <L"Windows.UI.Xaml.BindingFailedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_RoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_RoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_RoutedEventArgs <L"Windows.UI.Xaml.RoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_UnhandledExceptionEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_UnhandledExceptionEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_UnhandledExceptionEventArgs <L"Windows.UI.Xaml.UnhandledExceptionEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_VisualStateChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_VisualStateChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_VisualStateChangedEventArgs <L"Windows.UI.Xaml.VisualStateChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DataContextChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DataContextChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_DataContextChangedEventArgs <L"Windows.UI.Xaml.DataContextChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DataTemplateKey_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DataTemplateKey_DEFINED
define RuntimeClass_Windows_UI_Xaml_DataTemplateKey <L"Windows.UI.Xaml.DataTemplateKey">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DebugSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DebugSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_DebugSettings <L"Windows.UI.Xaml.DebugSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DependencyProperty_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DependencyProperty_DEFINED
define RuntimeClass_Windows_UI_Xaml_DependencyProperty <L"Windows.UI.Xaml.DependencyProperty">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DependencyObjectCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DependencyObjectCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_DependencyObjectCollection <L"Windows.UI.Xaml.DependencyObjectCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_PropertyMetadata_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_PropertyMetadata_DEFINED
define RuntimeClass_Windows_UI_Xaml_PropertyMetadata <L"Windows.UI.Xaml.PropertyMetadata">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DispatcherTimer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DispatcherTimer_DEFINED
define RuntimeClass_Windows_UI_Xaml_DispatcherTimer <L"Windows.UI.Xaml.DispatcherTimer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DragEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DragEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_DragEventArgs <L"Windows.UI.Xaml.DragEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_RoutedEvent_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_RoutedEvent_DEFINED
define RuntimeClass_Windows_UI_Xaml_RoutedEvent <L"Windows.UI.Xaml.RoutedEvent">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_TriggerActionCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_TriggerActionCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_TriggerActionCollection <L"Windows.UI.Xaml.TriggerActionCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_ExceptionRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_ExceptionRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_ExceptionRoutedEventArgs <L"Windows.UI.Xaml.ExceptionRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_WindowCreatedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_WindowCreatedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_WindowCreatedEventArgs <L"Windows.UI.Xaml.WindowCreatedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Application_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Application_DEFINED
define RuntimeClass_Windows_UI_Xaml_Application <L"Windows.UI.Xaml.Application">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_TriggerCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_TriggerCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_TriggerCollection <L"Windows.UI.Xaml.TriggerCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_FrameworkTemplate_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_FrameworkTemplate_DEFINED
define RuntimeClass_Windows_UI_Xaml_FrameworkTemplate <L"Windows.UI.Xaml.FrameworkTemplate">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_DataTemplate_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_DataTemplate_DEFINED
define RuntimeClass_Windows_UI_Xaml_DataTemplate <L"Windows.UI.Xaml.DataTemplate">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_FrameworkView_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_FrameworkView_DEFINED
define RuntimeClass_Windows_UI_Xaml_FrameworkView <L"Windows.UI.Xaml.FrameworkView">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_FrameworkViewSource_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_FrameworkViewSource_DEFINED
define RuntimeClass_Windows_UI_Xaml_FrameworkViewSource <L"Windows.UI.Xaml.FrameworkViewSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_MediaFailedRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_MediaFailedRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_MediaFailedRoutedEventArgs <L"Windows.UI.Xaml.MediaFailedRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_PropertyPath_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_PropertyPath_DEFINED
define RuntimeClass_Windows_UI_Xaml_PropertyPath <L"Windows.UI.Xaml.PropertyPath">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_ResourceDictionary_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_ResourceDictionary_DEFINED
define RuntimeClass_Windows_UI_Xaml_ResourceDictionary <L"Windows.UI.Xaml.ResourceDictionary">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_SetterBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_SetterBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_SetterBase <L"Windows.UI.Xaml.SetterBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Setter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Setter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Setter <L"Windows.UI.Xaml.Setter">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_SetterBaseCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_SetterBaseCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_SetterBaseCollection <L"Windows.UI.Xaml.SetterBaseCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_SizeChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_SizeChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_SizeChangedEventArgs <L"Windows.UI.Xaml.SizeChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Style_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Style_DEFINED
define RuntimeClass_Windows_UI_Xaml_Style <L"Windows.UI.Xaml.Style">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_TriggerAction_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_TriggerAction_DEFINED
define RuntimeClass_Windows_UI_Xaml_TriggerAction <L"Windows.UI.Xaml.TriggerAction">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_TriggerBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_TriggerBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_TriggerBase <L"Windows.UI.Xaml.TriggerBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_EventTrigger_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_EventTrigger_DEFINED
define RuntimeClass_Windows_UI_Xaml_EventTrigger <L"Windows.UI.Xaml.EventTrigger">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_UIElement_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_UIElement_DEFINED
define RuntimeClass_Windows_UI_Xaml_UIElement <L"Windows.UI.Xaml.UIElement">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_FrameworkElement_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_FrameworkElement_DEFINED
define RuntimeClass_Windows_UI_Xaml_FrameworkElement <L"Windows.UI.Xaml.FrameworkElement">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_VisualState_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_VisualState_DEFINED
define RuntimeClass_Windows_UI_Xaml_VisualState <L"Windows.UI.Xaml.VisualState">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_VisualStateGroup_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_VisualStateGroup_DEFINED
define RuntimeClass_Windows_UI_Xaml_VisualStateGroup <L"Windows.UI.Xaml.VisualStateGroup">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_VisualStateManager_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_VisualStateManager_DEFINED
define RuntimeClass_Windows_UI_Xaml_VisualStateManager <L"Windows.UI.Xaml.VisualStateManager">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_VisualTransition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_VisualTransition_DEFINED
define RuntimeClass_Windows_UI_Xaml_VisualTransition <L"Windows.UI.Xaml.VisualTransition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Window_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Window_DEFINED
define RuntimeClass_Windows_UI_Xaml_Window <L"Windows.UI.Xaml.Window">
endif

endif
