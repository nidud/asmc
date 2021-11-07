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

ifndef __windows2Eui2Ecore2Eanimationmetrics_h__
define __windows2Eui2Ecore2Eanimationmetrics_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation, "bb6799d3-9f1a-5a4e-a940-945f1ab8c4fe")

.comdef __FIIterator_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation, "c75f1bd1-a3c1-5881-9da0-1ecdb8e51bc3")

.comdef __FIIterable_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation, "3a6ed95d-6a50-5ead-a4c6-09f8babc632c")

.comdef __FIVectorView_1_Windows__CUI__CCore__CAnimationMetrics__CIPropertyAnimation : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Core
.namespace AnimationMetrics

.enum PropertyAnimationType {
    PropertyAnimationType_Scale = 0,
    PropertyAnimationType_Translation	= 1,
    PropertyAnimationType_Opacity	= 2
    }

.enum AnimationEffect {
    AnimationEffect_Expand	= 0,
    AnimationEffect_Collapse	= 1,
    AnimationEffect_Reposition	= 2,
    AnimationEffect_FadeIn	= 3,
    AnimationEffect_FadeOut	= 4,
    AnimationEffect_AddToList	= 5,
    AnimationEffect_DeleteFromList	= 6,
    AnimationEffect_AddToGrid	= 7,
    AnimationEffect_DeleteFromGrid	= 8,
    AnimationEffect_AddToSearchGrid	= 9,
    AnimationEffect_DeleteFromSearchGrid	= 10,
    AnimationEffect_AddToSearchList	= 11,
    AnimationEffect_DeleteFromSearchList	= 12,
    AnimationEffect_ShowEdgeUI	= 13,
    AnimationEffect_ShowPanel	= 14,
    AnimationEffect_HideEdgeUI	= 15,
    AnimationEffect_HidePanel	= 16,
    AnimationEffect_ShowPopup	= 17,
    AnimationEffect_HidePopup	= 18,
    AnimationEffect_PointerDown = 19,
    AnimationEffect_PointerUp	= 20,
    AnimationEffect_DragSourceStart	= 21,
    AnimationEffect_DragSourceEnd	= 22,
    AnimationEffect_TransitionContent	= 23,
    AnimationEffect_Reveal	= 24,
    AnimationEffect_Hide	= 25,
    AnimationEffect_DragBetweenEnter	= 26,
    AnimationEffect_DragBetweenLeave	= 27,
    AnimationEffect_SwipeSelect = 28,
    AnimationEffect_SwipeDeselect	= 29,
    AnimationEffect_SwipeReveal = 30,
    AnimationEffect_EnterPage	= 31,
    AnimationEffect_TransitionPage	= 32,
    AnimationEffect_CrossFade	= 33,
    AnimationEffect_Peek	= 34,
    AnimationEffect_UpdateBadge = 35
    }

.enum AnimationEffectTarget {
    AnimationEffectTarget_Primary	= 0,
    AnimationEffectTarget_Added = 1,
    AnimationEffectTarget_Affected	= 2,
    AnimationEffectTarget_Background	= 3,
    AnimationEffectTarget_Content	= 4,
    AnimationEffectTarget_Deleted	= 5,
    AnimationEffectTarget_Deselected	= 6,
    AnimationEffectTarget_DragSource	= 7,
    AnimationEffectTarget_Hidden	= 8,
    AnimationEffectTarget_Incoming	= 9,
    AnimationEffectTarget_Outgoing	= 10,
    AnimationEffectTarget_Outline	= 11,
    AnimationEffectTarget_Remaining	= 12,
    AnimationEffectTarget_Revealed	= 13,
    AnimationEffectTarget_RowIn = 14,
    AnimationEffectTarget_RowOut	= 15,
    AnimationEffectTarget_Selected	= 16,
    AnimationEffectTarget_Selection	= 17,
    AnimationEffectTarget_Shown = 18,
    AnimationEffectTarget_Tapped	= 19
    }

ifndef ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIPropertyAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIPropertyAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_AnimationMetrics_IPropertyAnimation <L"Windows.UI.Core.AnimationMetrics.IPropertyAnimation">
DEFINE_IIDX(IPropertyAnimation, "3A01B4DA-4D8C-411E-B615-1ADE683A9903")

.comdef IPropertyAnimation : public IInspectable

    get_Type		proc :ptr
    get_Delay		proc :ptr
    get_Duration	proc :ptr
    get_Control1	proc :ptr
    get_Control2	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIScaleAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIScaleAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_AnimationMetrics_IScaleAnimation <L"Windows.UI.Core.AnimationMetrics.IScaleAnimation">
DEFINE_IIDX(IScaleAnimation, "023552C7-71AB-428C-9C9F-D31780964995")

.comdef IScaleAnimation : public IInspectable

    get_InitialScaleX	proc :ptr
    get_InitialScaleY	proc :ptr
    get_FinalScaleX	proc :ptr
    get_FinalScaleY	proc :ptr
    get_NormalizedOrigin proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIOpacityAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIOpacityAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_AnimationMetrics_IOpacityAnimation <L"Windows.UI.Core.AnimationMetrics.IOpacityAnimation">
DEFINE_IIDX(IOpacityAnimation, "803AABE5-EE7E-455F-84E9-2506AFB8D2B4")

.comdef IOpacityAnimation : public IInspectable

    get_InitialOpacity	proc :ptr
    get_FinalOpacity	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIAnimationDescription_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIAnimationDescription_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_AnimationMetrics_IAnimationDescription <L"Windows.UI.Core.AnimationMetrics.IAnimationDescription">
DEFINE_IIDX(IAnimationDescription, "7D11A549-BE3D-41DE-B081-05C149962F9B")

.comdef IAnimationDescription : public IInspectable

    get_Animations	proc :ptr
    get_StaggerDelay	proc :ptr
    get_StaggerDelayFactor proc :ptr
    get_DelayLimit	proc :ptr
    get_ZOrder		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIAnimationDescriptionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CAnimationMetrics_CIAnimationDescriptionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_AnimationMetrics_IAnimationDescriptionFactory <L"Windows.UI.Core.AnimationMetrics.IAnimationDescriptionFactory">
DEFINE_IIDX(IAnimationDescriptionFactory, "C6E27ABE-C1FB-48B5-9271-ECC70AC86EF0")

.comdef IAnimationDescriptionFactory : public IInspectable

    CreateInstance	proc :Windows::UI::Core::AnimationMetrics::AnimationEffect, :Windows::UI::Core::AnimationMetrics::AnimationEffectTarget, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_AnimationDescription_DEFINED
define RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_AnimationDescription_DEFINED
define RuntimeClass_Windows_UI_Core_AnimationMetrics_AnimationDescription <L"Windows.UI.Core.AnimationMetrics.AnimationDescription">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_PropertyAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_PropertyAnimation_DEFINED
define RuntimeClass_Windows_UI_Core_AnimationMetrics_PropertyAnimation <L"Windows.UI.Core.AnimationMetrics.PropertyAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_ScaleAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_ScaleAnimation_DEFINED
define RuntimeClass_Windows_UI_Core_AnimationMetrics_ScaleAnimation <L"Windows.UI.Core.AnimationMetrics.ScaleAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_TranslationAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_TranslationAnimation_DEFINED
define RuntimeClass_Windows_UI_Core_AnimationMetrics_TranslationAnimation <L"Windows.UI.Core.AnimationMetrics.TranslationAnimation">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_OpacityAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Core_AnimationMetrics_OpacityAnimation_DEFINED
define RuntimeClass_Windows_UI_Core_AnimationMetrics_OpacityAnimation <L"Windows.UI.Core.AnimationMetrics.OpacityAnimation">
endif

endif

