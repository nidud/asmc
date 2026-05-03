ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __windows2Eui2Ecomposition_h__
define __windows2Eui2Ecomposition_h__

ifndef __windows2Eui2Ecomposition_p_h__
define __windows2Eui2Ecomposition_p_h__

ifndef SPECIFIC_API_CONTRACT_DEFINITIONS
ifndef WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION
define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
endif
ifndef WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION
define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x130000
endif
ifndef WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION
define WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION 0x70000
endif
ifndef WINDOWS_UI_CORE_COREWINDOWDIALOGSCONTRACT_VERSION
define WINDOWS_UI_CORE_COREWINDOWDIALOGSCONTRACT_VERSION 0x10000
endif
endif

ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include windowscontracts.inc
include Windows.Foundation.Numerics.inc
include Windows.Graphics.inc
include Windows.Graphics.DirectX.inc
include Windows.Graphics.Effects.inc
include Windows.System.inc
include Windows.UI.inc
include Windows.UI.Core.inc

.namespace Windows
.namespace UI
.namespace Composition

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
.enum AnimationControllerProgressBehavior {
    AnimationControllerProgressBehavior_Default = 0,
    AnimationControllerProgressBehavior_IncludesDelayTime = 1,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
.enum AnimationDelayBehavior {
    AnimationDelayBehavior_SetInitialValueAfterDelay = 0,
    AnimationDelayBehavior_SetInitialValueBeforeDelay = 1,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
.enum AnimationDirection {
    AnimationDirection_Normal = 0,
    AnimationDirection_Reverse = 1,
    AnimationDirection_Alternate = 2,
    AnimationDirection_AlternateReverse = 3,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum AnimationIterationBehavior {
    AnimationIterationBehavior_Count = 0,
    AnimationIterationBehavior_Forever = 1,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
.enum AnimationPropertyAccessMode {
    AnimationPropertyAccessMode_None = 0,
    AnimationPropertyAccessMode_ReadOnly = 1,
    AnimationPropertyAccessMode_WriteOnly = 2,
    AnimationPropertyAccessMode_ReadWrite = 3,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum AnimationStopBehavior {
    AnimationStopBehavior_LeaveCurrentValue = 0,
    AnimationStopBehavior_SetToInitialValue = 1,
    AnimationStopBehavior_SetToFinalValue = 2,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionBackfaceVisibility {
    CompositionBackfaceVisibility_Inherit = 0,
    CompositionBackfaceVisibility_Visible = 1,
    CompositionBackfaceVisibility_Hidden = 2,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionBatchTypes : uint_t {
    CompositionBatchTypes_None = 0,
    CompositionBatchTypes_Animation = 0x1,
    CompositionBatchTypes_Effect = 0x2,
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
    CompositionBatchTypes_InfiniteAnimation = 0x4,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
    CompositionBatchTypes_AllAnimations = 0x5,
endif
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionBitmapInterpolationMode {
    CompositionBitmapInterpolationMode_NearestNeighbor = 0,
    CompositionBitmapInterpolationMode_Linear = 1,
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
    CompositionBitmapInterpolationMode_MagLinearMinLinearMipLinear = 2,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
    CompositionBitmapInterpolationMode_MagLinearMinLinearMipNearest = 3,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
    CompositionBitmapInterpolationMode_MagLinearMinNearestMipLinear = 4,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
    CompositionBitmapInterpolationMode_MagLinearMinNearestMipNearest = 5,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
    CompositionBitmapInterpolationMode_MagNearestMinLinearMipLinear = 6,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
    CompositionBitmapInterpolationMode_MagNearestMinLinearMipNearest = 7,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
    CompositionBitmapInterpolationMode_MagNearestMinNearestMipLinear = 8,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
    CompositionBitmapInterpolationMode_MagNearestMinNearestMipNearest = 9,
endif
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionBorderMode {
    CompositionBorderMode_Inherit = 0,
    CompositionBorderMode_Soft = 1,
    CompositionBorderMode_Hard = 2,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionColorSpace {
    CompositionColorSpace_Auto = 0,
    CompositionColorSpace_Hsl = 1,
    CompositionColorSpace_Rgb = 2,
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
    CompositionColorSpace_HslLinear = 3,
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
    CompositionColorSpace_RgbLinear = 4,
endif
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionCompositeMode {
    CompositionCompositeMode_Inherit = 0,
    CompositionCompositeMode_SourceOver = 1,
    CompositionCompositeMode_DestinationInvert = 2,
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
    CompositionCompositeMode_MinBlend = 3,
endif
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
.enum CompositionDropShadowSourcePolicy {
    CompositionDropShadowSourcePolicy_Default = 0,
    CompositionDropShadowSourcePolicy_InheritFromVisualContent = 1,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
.enum CompositionEasingFunctionMode {
    CompositionEasingFunctionMode_In = 0,
    CompositionEasingFunctionMode_Out = 1,
    CompositionEasingFunctionMode_InOut = 2,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionEffectFactoryLoadStatus {
    CompositionEffectFactoryLoadStatus_Success = 0,
    CompositionEffectFactoryLoadStatus_EffectTooComplex = 1,
    CompositionEffectFactoryLoadStatus_Pending = 2,
    CompositionEffectFactoryLoadStatus_Other = -1,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionGetValueStatus {
    CompositionGetValueStatus_Succeeded = 0,
    CompositionGetValueStatus_TypeMismatch = 1,
    CompositionGetValueStatus_NotFound = 2,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
.enum CompositionGradientExtendMode {
    CompositionGradientExtendMode_Clamp = 0,
    CompositionGradientExtendMode_Wrap = 1,
    CompositionGradientExtendMode_Mirror = 2,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
.enum CompositionMappingMode {
    CompositionMappingMode_Absolute = 0,
    CompositionMappingMode_Relative = 1,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
.enum CompositionStretch {
    CompositionStretch_None = 0,
    CompositionStretch_Fill = 1,
    CompositionStretch_Uniform = 2,
    CompositionStretch_UniformToFill = 3,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
.enum CompositionStrokeCap {
    CompositionStrokeCap_Flat = 0,
    CompositionStrokeCap_Square = 1,
    CompositionStrokeCap_Round = 2,
    CompositionStrokeCap_Triangle = 3,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
.enum CompositionStrokeLineJoin {
    CompositionStrokeLineJoin_Miter = 0,
    CompositionStrokeLineJoin_Bevel = 1,
    CompositionStrokeLineJoin_Round = 2,
    CompositionStrokeLineJoin_MiterOrBevel = 3,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
InkTrailPoint           struct
Foundation              Windows::Foundation::Point <>
Radius                  real4 ?
InkTrailPoint           ends
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIAmbientLight_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIAmbientLight_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IAmbientLight <"Windows.UI.Composition.IAmbientLight">
DEFINE_IIDX(IAmbientLight, "a48130a1-b7c4-46f7-b9bf-daf43a44e6ee")

.comdef IAmbientLight : public IInspectable
    get_Color           proc :ptr
    put_Color           proc :Windows::UI::Color
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIAmbientLight2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIAmbientLight2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IAmbientLight2 <"Windows.UI.Composition.IAmbientLight2">
DEFINE_IIDX(IAmbientLight2, "3b64a6bf-5f97-4c94-86e5-042dd386b27d")

.comdef IAmbientLight2 : public IInspectable
    get_Intensity       proc :ptr
    put_Intensity       proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIAnimationController_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIAnimationController_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IAnimationController <"Windows.UI.Composition.IAnimationController">
DEFINE_IIDX(IAnimationController, "c934efd2-0722-4f5f-a4e2-9510f3d43bf7")

.comdef IAnimationController : public IInspectable
    get_PlaybackRate    proc :ptr
    put_PlaybackRate    proc :FLOAT
    get_Progress        proc :ptr
    put_Progress        proc :FLOAT
    get_ProgressBehavior proc :ptr
    put_ProgressBehavior proc :Windows::UI::Composition::AnimationControllerProgressBehavior
    _Pause              proc
    Resume              proc
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIAnimationControllerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIAnimationControllerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IAnimationControllerStatics <"Windows.UI.Composition.IAnimationControllerStatics">
DEFINE_IIDX(IAnimationControllerStatics, "e71164df-651b-4800-b9e5-6a3bcfed3365")

.comdef IAnimationControllerStatics : public IInspectable
    get_MaxPlaybackRate proc :ptr
    get_MinPlaybackRate proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIAnimationObject_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIAnimationObject_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IAnimationObject <"Windows.UI.Composition.IAnimationObject">
DEFINE_IIDX(IAnimationObject, "e7141e0a-04b8-4fc5-a4dc-195392e57807")

.comdef IAnimationObject : public IInspectable
    PopulatePropertyInfo proc :HSTRING, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIAnimationPropertyInfo_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIAnimationPropertyInfo_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IAnimationPropertyInfo <"Windows.UI.Composition.IAnimationPropertyInfo">
DEFINE_IIDX(IAnimationPropertyInfo, "f4716f05-ed77-4e3c-b328-5c3985b3738f")

.comdef IAnimationPropertyInfo : public IInspectable
    get_AccessMode      proc :ptr
    put_AccessMode      proc :Windows::UI::Composition::AnimationPropertyAccessMode
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIAnimationPropertyInfo2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIAnimationPropertyInfo2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IAnimationPropertyInfo2 <"Windows.UI.Composition.IAnimationPropertyInfo2">
DEFINE_IIDX(IAnimationPropertyInfo2, "591720b4-7472-5218-8b39-dffe615ae6da")

.comdef IAnimationPropertyInfo2 : public IInspectable
    GetResolvedCompositionObject proc :ptr ptr
    GetResolvedCompositionObjectProperty proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIBackEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIBackEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IBackEasingFunction <"Windows.UI.Composition.IBackEasingFunction">
DEFINE_IIDX(IBackEasingFunction, "b8560da4-5e3c-545d-b263-7987a2bd27cb")

.comdef IBackEasingFunction : public IInspectable
    get_Mode            proc :ptr
    get_Amplitude       proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIBooleanKeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIBooleanKeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IBooleanKeyFrameAnimation <"Windows.UI.Composition.IBooleanKeyFrameAnimation">
DEFINE_IIDX(IBooleanKeyFrameAnimation, "95e23a08-d1f4-4972-9770-3efe68d82e14")

.comdef IBooleanKeyFrameAnimation : public IInspectable
    InsertKeyFrame      proc :FLOAT, :boolean
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIBounceEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIBounceEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IBounceEasingFunction <"Windows.UI.Composition.IBounceEasingFunction">
DEFINE_IIDX(IBounceEasingFunction, "e7fdb44b-aad5-5174-9421-eef8b75a6a43")

.comdef IBounceEasingFunction : public IInspectable
    get_Mode            proc :ptr
    get_Bounces         proc :ptr
    get_Bounciness      proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIBounceScalarNaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIBounceScalarNaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IBounceScalarNaturalMotionAnimation <"Windows.UI.Composition.IBounceScalarNaturalMotionAnimation">
DEFINE_IIDX(IBounceScalarNaturalMotionAnimation, "baa30dcc-a633-4618-9b06-7f7c72c87cff")

.comdef IBounceScalarNaturalMotionAnimation : public IInspectable
    get_Acceleration    proc :ptr
    put_Acceleration    proc :FLOAT
    get_Restitution     proc :ptr
    put_Restitution     proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIBounceVector2NaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIBounceVector2NaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IBounceVector2NaturalMotionAnimation <"Windows.UI.Composition.IBounceVector2NaturalMotionAnimation">
DEFINE_IIDX(IBounceVector2NaturalMotionAnimation, "da344196-2154-4b3c-88aa-47361204eccd")

.comdef IBounceVector2NaturalMotionAnimation : public IInspectable
    get_Acceleration    proc :ptr
    put_Acceleration    proc :FLOAT
    get_Restitution     proc :ptr
    put_Restitution     proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIBounceVector3NaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIBounceVector3NaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IBounceVector3NaturalMotionAnimation <"Windows.UI.Composition.IBounceVector3NaturalMotionAnimation">
DEFINE_IIDX(IBounceVector3NaturalMotionAnimation, "47dabc31-10d3-4518-86f1-09caf742d113")

.comdef IBounceVector3NaturalMotionAnimation : public IInspectable
    get_Acceleration    proc :ptr
    put_Acceleration    proc :FLOAT
    get_Restitution     proc :ptr
    put_Restitution     proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICircleEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICircleEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICircleEasingFunction <"Windows.UI.Composition.ICircleEasingFunction">
DEFINE_IIDX(ICircleEasingFunction, "1e07222a-6f82-5a28-8748-2e92fc46ee2b")

.comdef ICircleEasingFunction : public IInspectable
    get_Mode            proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIColorKeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIColorKeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IColorKeyFrameAnimation <"Windows.UI.Composition.IColorKeyFrameAnimation">
DEFINE_IIDX(IColorKeyFrameAnimation, "93adb5e9-8e05-4593-84a3-dca152781e56")

.comdef IColorKeyFrameAnimation : public IInspectable
    get_InterpolationColorSpace proc :ptr
    put_InterpolationColorSpace proc :Windows::UI::Composition::CompositionColorSpace
    InsertKeyFrame      proc :FLOAT, :Windows::UI::Color
    InsertKeyFrameWithEasingFunction proc :FLOAT, :Windows::UI::Color, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionAnimation <"Windows.UI.Composition.ICompositionAnimation">
DEFINE_IIDX(ICompositionAnimation, "464c4c2c-1caa-4061-9b40-e13fde1503ca")

.comdef ICompositionAnimation : public IInspectable
    ClearAllParameters  proc
    ClearParameter      proc :HSTRING
    SetColorParameter   proc :HSTRING, :Windows::UI::Color
    SetMatrix3x2Parameter proc :HSTRING, :Windows::Foundation::Numerics::Matrix3x2
    SetMatrix4x4Parameter proc :HSTRING, :Windows::Foundation::Numerics::Matrix4x4
    SetQuaternionParameter proc :HSTRING, :Windows::Foundation::Numerics::Quaternion
    SetReferenceParameter proc :HSTRING, :ptr
    SetScalarParameter  proc :HSTRING, :FLOAT
    SetVector2Parameter proc :HSTRING, :Windows::Foundation::Numerics::Vector2
    SetVector3Parameter proc :HSTRING, :Windows::Foundation::Numerics::Vector3
    SetVector4Parameter proc :HSTRING, :Windows::Foundation::Numerics::Vector4
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimation2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimation2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionAnimation2 <"Windows.UI.Composition.ICompositionAnimation2">
DEFINE_IIDX(ICompositionAnimation2, "369b603e-a80f-4948-93e3-ed23fb38c6cb")

.comdef ICompositionAnimation2 : public IInspectable
    SetBooleanParameter proc :HSTRING, :boolean
    get_Target          proc :ptr
    put_Target          proc :HSTRING
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimation3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimation3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionAnimation3 <"Windows.UI.Composition.ICompositionAnimation3">
DEFINE_IIDX(ICompositionAnimation3, "d51e030d-7da4-4bd7-bc2d-f4517529f43a")

.comdef ICompositionAnimation3 : public IInspectable
    get_InitialValueExpressions proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimation4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimation4_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionAnimation4 <"Windows.UI.Composition.ICompositionAnimation4">
DEFINE_IIDX(ICompositionAnimation4, "770137be-76bc-4e23-bfed-fe9cc20f6ec9")

.comdef ICompositionAnimation4 : public IInspectable
    SetExpressionReferenceParameter proc :HSTRING, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimationBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimationBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionAnimationBase <"Windows.UI.Composition.ICompositionAnimationBase">
DEFINE_IIDX(ICompositionAnimationBase, "1c2c2999-e818-48d3-a6dd-d78c82f8ace9")

.comdef ICompositionAnimationBase : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionAnimationFactory <"Windows.UI.Composition.ICompositionAnimationFactory">
DEFINE_IIDX(ICompositionAnimationFactory, "10f6c4fb-6e51-4c25-bbd3-586a9bec3ef4")

.comdef ICompositionAnimationFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimationGroup_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionAnimationGroup_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionAnimationGroup <"Windows.UI.Composition.ICompositionAnimationGroup">
DEFINE_IIDX(ICompositionAnimationGroup, "5e7cc90c-cd14-4e07-8a55-c72527aabdac")

.comdef ICompositionAnimationGroup : public IInspectable
    get_Count           proc :ptr
    _Add                proc :ptr
    Remove              proc :ptr
    RemoveAll           proc
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionBackdropBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionBackdropBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionBackdropBrush <"Windows.UI.Composition.ICompositionBackdropBrush">
DEFINE_IIDX(ICompositionBackdropBrush, "c5acae58-3898-499e-8d7f-224e91286a5d")

.comdef ICompositionBackdropBrush : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionBatchCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionBatchCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionBatchCompletedEventArgs <"Windows.UI.Composition.ICompositionBatchCompletedEventArgs">
DEFINE_IIDX(ICompositionBatchCompletedEventArgs, "0d00dad0-9464-450a-a562-2e2698b0a812")

.comdef ICompositionBatchCompletedEventArgs : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionBrush <"Windows.UI.Composition.ICompositionBrush">
DEFINE_IIDX(ICompositionBrush, "ab0d7608-30c0-40e9-b568-b60a6bd1fb46")

.comdef ICompositionBrush : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionBrushFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionBrushFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionBrushFactory <"Windows.UI.Composition.ICompositionBrushFactory">
DEFINE_IIDX(ICompositionBrushFactory, "da53fb4c-4650-47c4-ad76-765379607ed6")

.comdef ICompositionBrushFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionCapabilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionCapabilities_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionCapabilities <"Windows.UI.Composition.ICompositionCapabilities">
DEFINE_IIDX(ICompositionCapabilities, "8253353e-b517-48bc-b1e8-4b3561a2e181")

.comdef ICompositionCapabilities : public IInspectable
    AreEffectsSupported proc :ptr
    AreEffectsFast      proc :ptr
    add_Changed         proc :ptr, :ptr
    remove_Changed      proc :EventRegistrationToken
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionCapabilitiesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionCapabilitiesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionCapabilitiesStatics <"Windows.UI.Composition.ICompositionCapabilitiesStatics">
DEFINE_IIDX(ICompositionCapabilitiesStatics, "f7b7a86e-6416-49e5-8ddf-afe949e20562")

.comdef ICompositionCapabilitiesStatics : public IInspectable
    GetForCurrentView   proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionClip_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionClip_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionClip <"Windows.UI.Composition.ICompositionClip">
DEFINE_IIDX(ICompositionClip, "1ccd2a52-cfc7-4ace-9983-146bb8eb6a3c")

.comdef ICompositionClip : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionClip2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionClip2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionClip2 <"Windows.UI.Composition.ICompositionClip2">
DEFINE_IIDX(ICompositionClip2, "5893e069-3516-40e1-89e0-5ba924927235")

.comdef ICompositionClip2 : public IInspectable
    get_AnchorPoint     proc :ptr
    put_AnchorPoint     proc :Windows::Foundation::Numerics::Vector2
    get_CenterPoint     proc :ptr
    put_CenterPoint     proc :Windows::Foundation::Numerics::Vector2
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector2
    get_RotationAngle   proc :ptr
    put_RotationAngle   proc :FLOAT
    get_RotationAngleInDegrees proc :ptr
    put_RotationAngleInDegrees proc :FLOAT
    get_Scale           proc :ptr
    put_Scale           proc :Windows::Foundation::Numerics::Vector2
    get_TransformMatrix proc :ptr
    put_TransformMatrix proc :Windows::Foundation::Numerics::Matrix3x2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionClipFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionClipFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionClipFactory <"Windows.UI.Composition.ICompositionClipFactory">
DEFINE_IIDX(ICompositionClipFactory, "b9484caf-20c7-4aed-ac4a-9c78ba1302cf")

.comdef ICompositionClipFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionColorBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionColorBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionColorBrush <"Windows.UI.Composition.ICompositionColorBrush">
DEFINE_IIDX(ICompositionColorBrush, "2b264c5e-bf35-4831-8642-cf70c20fff2f")

.comdef ICompositionColorBrush : public IInspectable
    get_Color           proc :ptr
    put_Color           proc :Windows::UI::Color
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionColorGradientStop_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionColorGradientStop_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionColorGradientStop <"Windows.UI.Composition.ICompositionColorGradientStop">
DEFINE_IIDX(ICompositionColorGradientStop, "6f00ca92-c801-4e41-9a8f-a53e20f57778")

.comdef ICompositionColorGradientStop : public IInspectable
    get_Color           proc :ptr
    put_Color           proc :Windows::UI::Color
    get_Offset          proc :ptr
    put_Offset          proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionColorGradientStopCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionColorGradientStopCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionColorGradientStopCollection <"Windows.UI.Composition.ICompositionColorGradientStopCollection">
DEFINE_IIDX(ICompositionColorGradientStopCollection, "9f1d20ec-7b04-4b1d-90bc-9fa32c0cfd26")

.comdef ICompositionColorGradientStopCollection : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionCommitBatch_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionCommitBatch_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionCommitBatch <"Windows.UI.Composition.ICompositionCommitBatch">
DEFINE_IIDX(ICompositionCommitBatch, "0d00dad0-ca07-4400-8c8e-cb5db08559cc")

.comdef ICompositionCommitBatch : public IInspectable
    get_IsActive        proc :ptr
    get_IsEnded         proc :ptr
    add_Completed       proc :ptr, :ptr
    remove_Completed    proc :EventRegistrationToken
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionContainerShape_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionContainerShape_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionContainerShape <"Windows.UI.Composition.ICompositionContainerShape">
DEFINE_IIDX(ICompositionContainerShape, "4f5e859b-2e5b-44a8-982c-aa0f69c16059")

.comdef ICompositionContainerShape : public IInspectable
    get_Shapes          proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionDrawingSurface_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionDrawingSurface_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionDrawingSurface <"Windows.UI.Composition.ICompositionDrawingSurface">
DEFINE_IIDX(ICompositionDrawingSurface, "a166c300-fad0-4d11-9e67-e433162ff49e")

.comdef ICompositionDrawingSurface : public IInspectable
    get_AlphaMode       proc :ptr
    get_PixelFormat     proc :ptr
    get_Size            proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionDrawingSurface2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionDrawingSurface2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionDrawingSurface2 <"Windows.UI.Composition.ICompositionDrawingSurface2">
DEFINE_IIDX(ICompositionDrawingSurface2, "fad0e88b-e354-44e8-8e3d-c4880d5a213f")

.comdef ICompositionDrawingSurface2 : public IInspectable
    get_SizeInt32       proc :ptr
    Resize              proc :Windows::Graphics::SizeInt32
    Scroll              proc :Windows::Graphics::PointInt32
    ScrollRect          proc :Windows::Graphics::PointInt32, :Windows::Graphics::RectInt32
    ScrollWithClip      proc :Windows::Graphics::PointInt32, :Windows::Graphics::RectInt32
    ScrollRectWithClip  proc :Windows::Graphics::PointInt32, :Windows::Graphics::RectInt32, :Windows::Graphics::RectInt32
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionDrawingSurfaceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionDrawingSurfaceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionDrawingSurfaceFactory <"Windows.UI.Composition.ICompositionDrawingSurfaceFactory">
DEFINE_IIDX(ICompositionDrawingSurfaceFactory, "9497b00a-312d-46b9-9db3-412fd79464c8")

.comdef ICompositionDrawingSurfaceFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionEasingFunction <"Windows.UI.Composition.ICompositionEasingFunction">
DEFINE_IIDX(ICompositionEasingFunction, "5145e356-bf79-4ea8-8cc2-6b5b472e6c9a")

.comdef ICompositionEasingFunction : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionEasingFunctionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionEasingFunctionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionEasingFunctionFactory <"Windows.UI.Composition.ICompositionEasingFunctionFactory">
DEFINE_IIDX(ICompositionEasingFunctionFactory, "60840774-3da0-4949-8200-7206c00190a0")

.comdef ICompositionEasingFunctionFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionEasingFunctionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionEasingFunctionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionEasingFunctionStatics <"Windows.UI.Composition.ICompositionEasingFunctionStatics">
DEFINE_IIDX(ICompositionEasingFunctionStatics, "17a766b6-2936-53ea-b5af-c642f4a61083")

.comdef ICompositionEasingFunctionStatics : public IInspectable
    CreateCubicBezierEasingFunction proc :ptr, :Windows::Foundation::Numerics::Vector2, :Windows::Foundation::Numerics::Vector2, :ptr ptr
    CreateLinearEasingFunction proc :ptr, :ptr ptr
    CreateStepEasingFunction proc :ptr, :ptr ptr
    CreateStepEasingFunctionWithStepCount proc :ptr, :INT32, :ptr ptr
    CreateBackEasingFunction proc :ptr, :Windows::UI::Composition::CompositionEasingFunctionMode, :FLOAT, :ptr ptr
    CreateBounceEasingFunction proc :ptr, :Windows::UI::Composition::CompositionEasingFunctionMode, :INT32, :FLOAT, :ptr ptr
    CreateCircleEasingFunction proc :ptr, :Windows::UI::Composition::CompositionEasingFunctionMode, :ptr ptr
    CreateElasticEasingFunction proc :ptr, :Windows::UI::Composition::CompositionEasingFunctionMode, :INT32, :FLOAT, :ptr ptr
    CreateExponentialEasingFunction proc :ptr, :Windows::UI::Composition::CompositionEasingFunctionMode, :FLOAT, :ptr ptr
    CreatePowerEasingFunction proc :ptr, :Windows::UI::Composition::CompositionEasingFunctionMode, :FLOAT, :ptr ptr
    CreateSineEasingFunction proc :ptr, :Windows::UI::Composition::CompositionEasingFunctionMode, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionEffectBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionEffectBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionEffectBrush <"Windows.UI.Composition.ICompositionEffectBrush">
DEFINE_IIDX(ICompositionEffectBrush, "bf7f795e-83cc-44bf-a447-3e3c071789ec")

.comdef ICompositionEffectBrush : public IInspectable
    GetSourceParameter  proc :HSTRING, :ptr ptr
    SetSourceParameter  proc :HSTRING, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionEffectFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionEffectFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionEffectFactory <"Windows.UI.Composition.ICompositionEffectFactory">
DEFINE_IIDX(ICompositionEffectFactory, "be5624af-ba7e-4510-9850-41c0b4ff74df")

.comdef ICompositionEffectFactory : public IInspectable
    CreateBrush         proc :ptr ptr
    get_ExtendedError   proc :ptr
    get_LoadStatus      proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionEffectSourceParameter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionEffectSourceParameter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionEffectSourceParameter <"Windows.UI.Composition.ICompositionEffectSourceParameter">
DEFINE_IIDX(ICompositionEffectSourceParameter, "858ab13a-3292-4e4e-b3bb-2b6c6544a6ee")

.comdef ICompositionEffectSourceParameter : public IInspectable
    get_Name            proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionEffectSourceParameterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionEffectSourceParameterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionEffectSourceParameterFactory <"Windows.UI.Composition.ICompositionEffectSourceParameterFactory">
DEFINE_IIDX(ICompositionEffectSourceParameterFactory, "b3d9f276-aba3-4724-acf3-d0397464db1c")

.comdef ICompositionEffectSourceParameterFactory : public IInspectable
    Create              proc :HSTRING, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionEllipseGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionEllipseGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionEllipseGeometry <"Windows.UI.Composition.ICompositionEllipseGeometry">
DEFINE_IIDX(ICompositionEllipseGeometry, "4801f884-f6ad-4b93-afa9-897b64e57b1f")

.comdef ICompositionEllipseGeometry : public IInspectable
    get_Center          proc :ptr
    put_Center          proc :Windows::Foundation::Numerics::Vector2
    get_Radius          proc :ptr
    put_Radius          proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGeometricClip_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGeometricClip_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGeometricClip <"Windows.UI.Composition.ICompositionGeometricClip">
DEFINE_IIDX(ICompositionGeometricClip, "c840b581-81c9-4444-a2c1-ccaece3a50e5")

.comdef ICompositionGeometricClip : public IInspectable
    get_Geometry        proc :ptr ptr
    put_Geometry        proc :ptr
    get_ViewBox         proc :ptr ptr
    put_ViewBox         proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGeometry <"Windows.UI.Composition.ICompositionGeometry">
DEFINE_IIDX(ICompositionGeometry, "e985217c-6a17-4207-abd8-5fd3dd612a9d")

.comdef ICompositionGeometry : public IInspectable
    get_TrimEnd         proc :ptr
    put_TrimEnd         proc :FLOAT
    get_TrimOffset      proc :ptr
    put_TrimOffset      proc :FLOAT
    get_TrimStart       proc :ptr
    put_TrimStart       proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGeometryFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGeometryFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGeometryFactory <"Windows.UI.Composition.ICompositionGeometryFactory">
DEFINE_IIDX(ICompositionGeometryFactory, "bffebfe1-8c25-480b-9f56-fed6b288055d")

.comdef ICompositionGeometryFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGradientBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGradientBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGradientBrush <"Windows.UI.Composition.ICompositionGradientBrush">
DEFINE_IIDX(ICompositionGradientBrush, "1d9709e0-ffc6-4c0e-a9ab-34144d4c9098")

.comdef ICompositionGradientBrush : public IInspectable
    get_AnchorPoint     proc :ptr
    put_AnchorPoint     proc :Windows::Foundation::Numerics::Vector2
    get_CenterPoint     proc :ptr
    put_CenterPoint     proc :Windows::Foundation::Numerics::Vector2
    get_ColorStops      proc :ptr ptr
    get_ExtendMode      proc :ptr
    put_ExtendMode      proc :Windows::UI::Composition::CompositionGradientExtendMode
    get_InterpolationSpace proc :ptr
    put_InterpolationSpace proc :Windows::UI::Composition::CompositionColorSpace
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector2
    get_RotationAngle   proc :ptr
    put_RotationAngle   proc :FLOAT
    get_RotationAngleInDegrees proc :ptr
    put_RotationAngleInDegrees proc :FLOAT
    get_Scale           proc :ptr
    put_Scale           proc :Windows::Foundation::Numerics::Vector2
    get_TransformMatrix proc :ptr
    put_TransformMatrix proc :Windows::Foundation::Numerics::Matrix3x2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGradientBrush2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGradientBrush2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGradientBrush2 <"Windows.UI.Composition.ICompositionGradientBrush2">
DEFINE_IIDX(ICompositionGradientBrush2, "899dd5a1-b4c7-4b33-a1b6-264addc26d10")

.comdef ICompositionGradientBrush2 : public IInspectable
    get_MappingMode     proc :ptr
    put_MappingMode     proc :Windows::UI::Composition::CompositionMappingMode
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGradientBrushFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGradientBrushFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGradientBrushFactory <"Windows.UI.Composition.ICompositionGradientBrushFactory">
DEFINE_IIDX(ICompositionGradientBrushFactory, "56d765d7-f189-48c9-9c8d-94daf1bec010")

.comdef ICompositionGradientBrushFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGraphicsDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGraphicsDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGraphicsDevice <"Windows.UI.Composition.ICompositionGraphicsDevice">
DEFINE_IIDX(ICompositionGraphicsDevice, "fb22c6e1-80a2-4667-9936-dbeaf6eefe95")

.comdef ICompositionGraphicsDevice : public IInspectable
    CreateDrawingSurface proc :Windows::Foundation::Size, :Windows::Graphics::DirectX::DirectXPixelFormat, :Windows::Graphics::DirectX::DirectXAlphaMode, :ptr ptr
    add_RenderingDeviceReplaced proc :ptr, :ptr
    remove_RenderingDeviceReplaced proc :EventRegistrationToken
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGraphicsDevice2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGraphicsDevice2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGraphicsDevice2 <"Windows.UI.Composition.ICompositionGraphicsDevice2">
DEFINE_IIDX(ICompositionGraphicsDevice2, "0fb8bdf6-c0f0-4bcc-9fb8-084982490d7d")

.comdef ICompositionGraphicsDevice2 : public IInspectable
    CreateDrawingSurface2 proc :Windows::Graphics::SizeInt32, :Windows::Graphics::DirectX::DirectXPixelFormat, :Windows::Graphics::DirectX::DirectXAlphaMode, :ptr ptr
    CreateVirtualDrawingSurface proc :Windows::Graphics::SizeInt32, :Windows::Graphics::DirectX::DirectXPixelFormat, :Windows::Graphics::DirectX::DirectXAlphaMode, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGraphicsDevice3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGraphicsDevice3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGraphicsDevice3 <"Windows.UI.Composition.ICompositionGraphicsDevice3">
DEFINE_IIDX(ICompositionGraphicsDevice3, "37f67514-d3ef-49d1-b69d-0d8eabeb3626")

.comdef ICompositionGraphicsDevice3 : public IInspectable
    CreateMipmapSurface proc :Windows::Graphics::SizeInt32, :Windows::Graphics::DirectX::DirectXPixelFormat, :Windows::Graphics::DirectX::DirectXAlphaMode, :ptr ptr
    Trim                proc
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionGraphicsDevice4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionGraphicsDevice4_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionGraphicsDevice4 <"Windows.UI.Composition.ICompositionGraphicsDevice4">
DEFINE_IIDX(ICompositionGraphicsDevice4, "5a73bff9-a97f-4cf5-ba46-98ef358e71b1")

.comdef ICompositionGraphicsDevice4 : public IInspectable
    CaptureAsync        proc :ptr, :Windows::Graphics::SizeInt32, :Windows::Graphics::DirectX::DirectXPixelFormat, :Windows::Graphics::DirectX::DirectXAlphaMode, :FLOAT, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionLight_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionLight_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionLight <"Windows.UI.Composition.ICompositionLight">
DEFINE_IIDX(ICompositionLight, "41a6d7c2-2e5d-4bc1-b09e-8f0a03e3d8d3")

.comdef ICompositionLight : public IInspectable
    get_Targets         proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionLight2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionLight2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionLight2 <"Windows.UI.Composition.ICompositionLight2">
DEFINE_IIDX(ICompositionLight2, "a7bcda72-f35d-425d-9b98-23f4205f6669")

.comdef ICompositionLight2 : public IInspectable
    get_ExclusionsFromTargets proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionLight3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionLight3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionLight3 <"Windows.UI.Composition.ICompositionLight3">
DEFINE_IIDX(ICompositionLight3, "4b0b00e4-df07-4959-b7a4-4f7e4233f838")

.comdef ICompositionLight3 : public IInspectable
    get_IsEnabled       proc :ptr
    put_IsEnabled       proc :boolean
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionLightFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionLightFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionLightFactory <"Windows.UI.Composition.ICompositionLightFactory">
DEFINE_IIDX(ICompositionLightFactory, "069cf306-da3c-4b44-838a-5e03d51ace55")

.comdef ICompositionLightFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionLineGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionLineGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionLineGeometry <"Windows.UI.Composition.ICompositionLineGeometry">
DEFINE_IIDX(ICompositionLineGeometry, "dd7615a4-0c9a-4b67-8dce-440a5bf9cdec")

.comdef ICompositionLineGeometry : public IInspectable
    get_Start           proc :ptr
    put_Start           proc :Windows::Foundation::Numerics::Vector2
    get_End             proc :ptr
    put_End             proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionLinearGradientBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionLinearGradientBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionLinearGradientBrush <"Windows.UI.Composition.ICompositionLinearGradientBrush">
DEFINE_IIDX(ICompositionLinearGradientBrush, "983bc519-a9db-413c-a2d8-2a9056fc525e")

.comdef ICompositionLinearGradientBrush : public IInspectable
    get_EndPoint        proc :ptr
    put_EndPoint        proc :Windows::Foundation::Numerics::Vector2
    get_StartPoint      proc :ptr
    put_StartPoint      proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionMaskBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionMaskBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionMaskBrush <"Windows.UI.Composition.ICompositionMaskBrush">
DEFINE_IIDX(ICompositionMaskBrush, "522cf09e-be6b-4f41-be49-f9226d471b4a")

.comdef ICompositionMaskBrush : public IInspectable
    get_Mask            proc :ptr ptr
    put_Mask            proc :ptr
    get_Source          proc :ptr ptr
    put_Source          proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionMipmapSurface_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionMipmapSurface_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionMipmapSurface <"Windows.UI.Composition.ICompositionMipmapSurface">
DEFINE_IIDX(ICompositionMipmapSurface, "4863675c-cf4a-4b1c-9ece-c5ec0c2b2fe6")

.comdef ICompositionMipmapSurface : public IInspectable
    get_LevelCount      proc :ptr
    get_AlphaMode       proc :ptr
    get_PixelFormat     proc :ptr
    get_SizeInt32       proc :ptr
    GetDrawingSurfaceForLevel proc :UINT32, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionNineGridBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionNineGridBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionNineGridBrush <"Windows.UI.Composition.ICompositionNineGridBrush">
DEFINE_IIDX(ICompositionNineGridBrush, "f25154e4-bc8c-4be7-b80f-8685b83c0186")

.comdef ICompositionNineGridBrush : public IInspectable
    get_BottomInset     proc :ptr
    put_BottomInset     proc :FLOAT
    get_BottomInsetScale proc :ptr
    put_BottomInsetScale proc :FLOAT
    get_IsCenterHollow  proc :ptr
    put_IsCenterHollow  proc :boolean
    get_LeftInset       proc :ptr
    put_LeftInset       proc :FLOAT
    get_LeftInsetScale  proc :ptr
    put_LeftInsetScale  proc :FLOAT
    get_RightInset      proc :ptr
    put_RightInset      proc :FLOAT
    get_RightInsetScale proc :ptr
    put_RightInsetScale proc :FLOAT
    get_Source          proc :ptr ptr
    put_Source          proc :ptr
    get_TopInset        proc :ptr
    put_TopInset        proc :FLOAT
    get_TopInsetScale   proc :ptr
    put_TopInsetScale   proc :FLOAT
    SetInsets           proc :FLOAT
    SetInsetsWithValues proc :FLOAT, :FLOAT, :FLOAT, :FLOAT
    SetInsetScales      proc :FLOAT
    SetInsetScalesWithValues proc :FLOAT, :FLOAT, :FLOAT, :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionObject_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionObject_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionObject <"Windows.UI.Composition.ICompositionObject">
DEFINE_IIDX(ICompositionObject, "bcb4ad45-7609-4550-934f-16002a68fded")

.comdef ICompositionObject : public IInspectable
    get_Compositor      proc :ptr ptr
    get_Dispatcher      proc :ptr ptr
    get_Properties      proc :ptr ptr
    StartAnimation      proc :HSTRING, :ptr
    StopAnimation       proc :HSTRING
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionObject2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionObject2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionObject2 <"Windows.UI.Composition.ICompositionObject2">
DEFINE_IIDX(ICompositionObject2, "ef874ea1-5cff-4b68-9e30-a1519d08ba03")

.comdef ICompositionObject2 : public IInspectable
    get_Comment         proc :ptr
    put_Comment         proc :HSTRING
    get_ImplicitAnimations proc :ptr ptr
    put_ImplicitAnimations proc :ptr
    StartAnimationGroup proc :ptr
    StopAnimationGroup  proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionObject3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionObject3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionObject3 <"Windows.UI.Composition.ICompositionObject3">
DEFINE_IIDX(ICompositionObject3, "4bc27925-dacd-4cf2-98b1-986b76e7ebe6")

.comdef ICompositionObject3 : public IInspectable
    get_DispatcherQueue proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionObject4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionObject4_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionObject4 <"Windows.UI.Composition.ICompositionObject4">
DEFINE_IIDX(ICompositionObject4, "0bb3784c-346b-4a7c-966b-7310966553d5")

.comdef ICompositionObject4 : public IInspectable
    TryGetAnimationController proc :HSTRING, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xf0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionObject5_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionObject5_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionObject5 <"Windows.UI.Composition.ICompositionObject5">
DEFINE_IIDX(ICompositionObject5, "1d7f391b-a130-5265-a62b-60b8e668965a")

.comdef ICompositionObject5 : public IInspectable
    StartAnimationWithController proc :HSTRING, :ptr, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionObjectFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionObjectFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionObjectFactory <"Windows.UI.Composition.ICompositionObjectFactory">
DEFINE_IIDX(ICompositionObjectFactory, "51205c5e-558a-4f2a-8d39-37bfe1e20ddd")

.comdef ICompositionObjectFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionObjectStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionObjectStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionObjectStatics <"Windows.UI.Composition.ICompositionObjectStatics">
DEFINE_IIDX(ICompositionObjectStatics, "c1ed052f-1ba2-44ba-a904-6a882a0a5adb")

.comdef ICompositionObjectStatics : public IInspectable
    StartAnimationWithIAnimationObject proc :ptr, :HSTRING, :ptr
    StartAnimationGroupWithIAnimationObject proc :ptr, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionPath_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionPath_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionPath <"Windows.UI.Composition.ICompositionPath">
DEFINE_IIDX(ICompositionPath, "66da1d5f-2e10-4f22-8a06-0a8151919e60")

.comdef ICompositionPath : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionPathFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionPathFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionPathFactory <"Windows.UI.Composition.ICompositionPathFactory">
DEFINE_IIDX(ICompositionPathFactory, "9c1e8c6a-0f33-4751-9437-eb3fb9d3ab07")

.comdef ICompositionPathFactory : public IInspectable
    Create              proc :ptr, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionPathGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionPathGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionPathGeometry <"Windows.UI.Composition.ICompositionPathGeometry">
DEFINE_IIDX(ICompositionPathGeometry, "0b6a417e-2c77-4c23-af5e-6304c147bb61")

.comdef ICompositionPathGeometry : public IInspectable
    get_Path            proc :ptr ptr
    put_Path            proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadow_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadow_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionProjectedShadow <"Windows.UI.Composition.ICompositionProjectedShadow">
DEFINE_IIDX(ICompositionProjectedShadow, "285b8e72-4328-523f-bcf2-5557c52c3b25")

.comdef ICompositionProjectedShadow : public IInspectable
    get_BlurRadiusMultiplier proc :ptr
    put_BlurRadiusMultiplier proc :FLOAT
    get_Casters         proc :ptr ptr
    get_LightSource     proc :ptr ptr
    put_LightSource     proc :ptr
    get_MaxBlurRadius   proc :ptr
    put_MaxBlurRadius   proc :FLOAT
    get_MinBlurRadius   proc :ptr
    put_MinBlurRadius   proc :FLOAT
    get_Receivers       proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowCaster_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowCaster_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionProjectedShadowCaster <"Windows.UI.Composition.ICompositionProjectedShadowCaster">
DEFINE_IIDX(ICompositionProjectedShadowCaster, "b1d7d426-1e36-5a62-be56-a16112fdd148")

.comdef ICompositionProjectedShadowCaster : public IInspectable
    get_Brush           proc :ptr ptr
    put_Brush           proc :ptr
    get_CastingVisual   proc :ptr ptr
    put_CastingVisual   proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowCasterCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowCasterCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionProjectedShadowCasterCollection <"Windows.UI.Composition.ICompositionProjectedShadowCasterCollection">
DEFINE_IIDX(ICompositionProjectedShadowCasterCollection, "d2525c0c-e07f-58a3-ac91-37f73ee91740")

.comdef ICompositionProjectedShadowCasterCollection : public IInspectable
    get_Count           proc :ptr
    InsertAbove         proc :ptr, :ptr
    InsertAtBottom      proc :ptr
    InsertAtTop         proc :ptr
    InsertBelow         proc :ptr, :ptr
    Remove              proc :ptr
    RemoveAll           proc
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowCasterCollectionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowCasterCollectionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionProjectedShadowCasterCollectionStatics <"Windows.UI.Composition.ICompositionProjectedShadowCasterCollectionStatics">
DEFINE_IIDX(ICompositionProjectedShadowCasterCollectionStatics, "56fbb136-e94f-5299-ab5b-6e15e38bd899")

.comdef ICompositionProjectedShadowCasterCollectionStatics : public IInspectable
    get_MaxRespectedCasters proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowReceiver_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowReceiver_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionProjectedShadowReceiver <"Windows.UI.Composition.ICompositionProjectedShadowReceiver">
DEFINE_IIDX(ICompositionProjectedShadowReceiver, "1377985a-6a49-536a-9be4-a96a8e5298a9")

.comdef ICompositionProjectedShadowReceiver : public IInspectable
    get_ReceivingVisual proc :ptr ptr
    put_ReceivingVisual proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowReceiverUnorderedCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionProjectedShadowReceiverUnorderedCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionProjectedShadowReceiverUnorderedCollection <"Windows.UI.Composition.ICompositionProjectedShadowReceiverUnorderedCollection">
DEFINE_IIDX(ICompositionProjectedShadowReceiverUnorderedCollection, "02b3e3b7-27d2-599f-ac4b-ab787cdde6fd")

.comdef ICompositionProjectedShadowReceiverUnorderedCollection : public IInspectable
    _Add                proc :ptr
    get_Count           proc :ptr
    Remove              proc :ptr
    RemoveAll           proc
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionPropertySet_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionPropertySet_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionPropertySet <"Windows.UI.Composition.ICompositionPropertySet">
DEFINE_IIDX(ICompositionPropertySet, "c9d6d202-5f67-4453-9117-9eadd430d3c2")

.comdef ICompositionPropertySet : public IInspectable
    InsertColor         proc :HSTRING, :Windows::UI::Color
    InsertMatrix3x2     proc :HSTRING, :Windows::Foundation::Numerics::Matrix3x2
    InsertMatrix4x4     proc :HSTRING, :Windows::Foundation::Numerics::Matrix4x4
    InsertQuaternion    proc :HSTRING, :Windows::Foundation::Numerics::Quaternion
    InsertScalar        proc :HSTRING, :FLOAT
    InsertVector2       proc :HSTRING, :Windows::Foundation::Numerics::Vector2
    InsertVector3       proc :HSTRING, :Windows::Foundation::Numerics::Vector3
    InsertVector4       proc :HSTRING, :Windows::Foundation::Numerics::Vector4
    TryGetColor         proc :HSTRING, :ptr, :ptr
    TryGetMatrix3x2     proc :HSTRING, :ptr, :ptr
    TryGetMatrix4x4     proc :HSTRING, :ptr, :ptr
    TryGetQuaternion    proc :HSTRING, :ptr, :ptr
    TryGetScalar        proc :HSTRING, :ptr, :ptr
    TryGetVector2       proc :HSTRING, :ptr, :ptr
    TryGetVector3       proc :HSTRING, :ptr, :ptr
    TryGetVector4       proc :HSTRING, :ptr, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionPropertySet2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionPropertySet2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionPropertySet2 <"Windows.UI.Composition.ICompositionPropertySet2">
DEFINE_IIDX(ICompositionPropertySet2, "de80731e-a211-4455-8880-7d0f3f6a44fd")

.comdef ICompositionPropertySet2 : public IInspectable
    InsertBoolean       proc :HSTRING, :boolean
    TryGetBoolean       proc :HSTRING, :ptr, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionRadialGradientBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionRadialGradientBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionRadialGradientBrush <"Windows.UI.Composition.ICompositionRadialGradientBrush">
DEFINE_IIDX(ICompositionRadialGradientBrush, "3d3b50c5-e3fa-4ce2-b9fc-3ee12561788f")

.comdef ICompositionRadialGradientBrush : public IInspectable
    get_EllipseCenter   proc :ptr
    put_EllipseCenter   proc :Windows::Foundation::Numerics::Vector2
    get_EllipseRadius   proc :ptr
    put_EllipseRadius   proc :Windows::Foundation::Numerics::Vector2
    get_GradientOriginOffset proc :ptr
    put_GradientOriginOffset proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionRectangleGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionRectangleGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionRectangleGeometry <"Windows.UI.Composition.ICompositionRectangleGeometry">
DEFINE_IIDX(ICompositionRectangleGeometry, "0cd51428-5356-4246-aecf-7a0b76975400")

.comdef ICompositionRectangleGeometry : public IInspectable
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector2
    get_Size            proc :ptr
    put_Size            proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionRoundedRectangleGeometry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionRoundedRectangleGeometry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionRoundedRectangleGeometry <"Windows.UI.Composition.ICompositionRoundedRectangleGeometry">
DEFINE_IIDX(ICompositionRoundedRectangleGeometry, "8770c822-1d50-4b8b-b013-7c9a0e46935f")

.comdef ICompositionRoundedRectangleGeometry : public IInspectable
    get_CornerRadius    proc :ptr
    put_CornerRadius    proc :Windows::Foundation::Numerics::Vector2
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector2
    get_Size            proc :ptr
    put_Size            proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionScopedBatch_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionScopedBatch_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionScopedBatch <"Windows.UI.Composition.ICompositionScopedBatch">
DEFINE_IIDX(ICompositionScopedBatch, "0d00dad0-fb07-46fd-8c72-6280d1a3d1dd")

.comdef ICompositionScopedBatch : public IInspectable
    get_IsActive        proc :ptr
    get_IsEnded         proc :ptr
    _End                proc
    Resume              proc
    Suspend             proc
    add_Completed       proc :ptr, :ptr
    remove_Completed    proc :EventRegistrationToken
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionShadow_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionShadow_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionShadow <"Windows.UI.Composition.ICompositionShadow">
DEFINE_IIDX(ICompositionShadow, "329e52e2-4335-49cc-b14a-37782d10f0c4")

.comdef ICompositionShadow : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionShadowFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionShadowFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionShadowFactory <"Windows.UI.Composition.ICompositionShadowFactory">
DEFINE_IIDX(ICompositionShadowFactory, "221f492f-dcba-4b91-999e-1dc217a01530")

.comdef ICompositionShadowFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionShape_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionShape_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionShape <"Windows.UI.Composition.ICompositionShape">
DEFINE_IIDX(ICompositionShape, "b47ce2f7-9a88-42c4-9e87-2e500ca8688c")

.comdef ICompositionShape : public IInspectable
    get_CenterPoint     proc :ptr
    put_CenterPoint     proc :Windows::Foundation::Numerics::Vector2
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector2
    get_RotationAngle   proc :ptr
    put_RotationAngle   proc :FLOAT
    get_RotationAngleInDegrees proc :ptr
    put_RotationAngleInDegrees proc :FLOAT
    get_Scale           proc :ptr
    put_Scale           proc :Windows::Foundation::Numerics::Vector2
    get_TransformMatrix proc :ptr
    put_TransformMatrix proc :Windows::Foundation::Numerics::Matrix3x2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionShapeFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionShapeFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionShapeFactory <"Windows.UI.Composition.ICompositionShapeFactory">
DEFINE_IIDX(ICompositionShapeFactory, "1dfc36d0-b05a-44ef-82b0-12118bcd4cd0")

.comdef ICompositionShapeFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionSpriteShape_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionSpriteShape_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionSpriteShape <"Windows.UI.Composition.ICompositionSpriteShape">
DEFINE_IIDX(ICompositionSpriteShape, "401b61bb-0007-4363-b1f3-6bcc003fb83e")

.comdef ICompositionSpriteShape : public IInspectable
    get_FillBrush       proc :ptr ptr
    put_FillBrush       proc :ptr
    get_Geometry        proc :ptr ptr
    put_Geometry        proc :ptr
    get_IsStrokeNonScaling proc :ptr
    put_IsStrokeNonScaling proc :boolean
    get_StrokeBrush     proc :ptr ptr
    put_StrokeBrush     proc :ptr
    get_StrokeDashArray proc :ptr ptr
    get_StrokeDashCap   proc :ptr
    put_StrokeDashCap   proc :Windows::UI::Composition::CompositionStrokeCap
    get_StrokeDashOffset proc :ptr
    put_StrokeDashOffset proc :FLOAT
    get_StrokeEndCap    proc :ptr
    put_StrokeEndCap    proc :Windows::UI::Composition::CompositionStrokeCap
    get_StrokeLineJoin  proc :ptr
    put_StrokeLineJoin  proc :Windows::UI::Composition::CompositionStrokeLineJoin
    get_StrokeMiterLimit proc :ptr
    put_StrokeMiterLimit proc :FLOAT
    get_StrokeStartCap  proc :ptr
    put_StrokeStartCap  proc :Windows::UI::Composition::CompositionStrokeCap
    get_StrokeThickness proc :ptr
    put_StrokeThickness proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xd0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionSupportsSystemBackdrop_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionSupportsSystemBackdrop_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionSupportsSystemBackdrop <"Windows.UI.Composition.ICompositionSupportsSystemBackdrop">
DEFINE_IIDX(ICompositionSupportsSystemBackdrop, "397dafe4-b6c2-5bb9-951d-f5707de8b7bc")

.comdef ICompositionSupportsSystemBackdrop : public IInspectable
    get_SystemBackdrop  proc :ptr ptr
    put_SystemBackdrop  proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionSurface_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionSurface_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionSurface <"Windows.UI.Composition.ICompositionSurface">
DEFINE_IIDX(ICompositionSurface, "1527540d-42c7-47a6-a408-668f79a90dfb")

.comdef ICompositionSurface : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionSurfaceBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionSurfaceBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionSurfaceBrush <"Windows.UI.Composition.ICompositionSurfaceBrush">
DEFINE_IIDX(ICompositionSurfaceBrush, "ad016d79-1e4c-4c0d-9c29-83338c87c162")

.comdef ICompositionSurfaceBrush : public IInspectable
    get_BitmapInterpolationMode proc :ptr
    put_BitmapInterpolationMode proc :Windows::UI::Composition::CompositionBitmapInterpolationMode
    get_HorizontalAlignmentRatio proc :ptr
    put_HorizontalAlignmentRatio proc :FLOAT
    get_Stretch         proc :ptr
    put_Stretch         proc :Windows::UI::Composition::CompositionStretch
    get_Surface         proc :ptr ptr
    put_Surface         proc :ptr
    get_VerticalAlignmentRatio proc :ptr
    put_VerticalAlignmentRatio proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionSurfaceBrush2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionSurfaceBrush2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionSurfaceBrush2 <"Windows.UI.Composition.ICompositionSurfaceBrush2">
DEFINE_IIDX(ICompositionSurfaceBrush2, "d27174d5-64f5-4692-9dc7-71b61d7e5880")

.comdef ICompositionSurfaceBrush2 : public IInspectable
    get_AnchorPoint     proc :ptr
    put_AnchorPoint     proc :Windows::Foundation::Numerics::Vector2
    get_CenterPoint     proc :ptr
    put_CenterPoint     proc :Windows::Foundation::Numerics::Vector2
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector2
    get_RotationAngle   proc :ptr
    put_RotationAngle   proc :FLOAT
    get_RotationAngleInDegrees proc :ptr
    put_RotationAngleInDegrees proc :FLOAT
    get_Scale           proc :ptr
    put_Scale           proc :Windows::Foundation::Numerics::Vector2
    get_TransformMatrix proc :ptr
    put_TransformMatrix proc :Windows::Foundation::Numerics::Matrix3x2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionSurfaceBrush3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionSurfaceBrush3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionSurfaceBrush3 <"Windows.UI.Composition.ICompositionSurfaceBrush3">
DEFINE_IIDX(ICompositionSurfaceBrush3, "550bb289-1fe0-42e5-8195-1eefa87ff08e")

.comdef ICompositionSurfaceBrush3 : public IInspectable
    get_SnapToPixels    proc :ptr
    put_SnapToPixels    proc :boolean
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionSurfaceFacade_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionSurfaceFacade_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionSurfaceFacade <"Windows.UI.Composition.ICompositionSurfaceFacade">
DEFINE_IIDX(ICompositionSurfaceFacade, "e01622c8-2332-55c7-8868-a7312c5c229d")

.comdef ICompositionSurfaceFacade : public IInspectable
    GetRealSurface      proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionTarget_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionTarget_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionTarget <"Windows.UI.Composition.ICompositionTarget">
DEFINE_IIDX(ICompositionTarget, "a1bea8ba-d726-4663-8129-6b5e7927ffa6")

.comdef ICompositionTarget : public IInspectable
    get_Root            proc :ptr ptr
    put_Root            proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionTargetFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionTargetFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionTargetFactory <"Windows.UI.Composition.ICompositionTargetFactory">
DEFINE_IIDX(ICompositionTargetFactory, "93cd9d2b-8516-4b14-a8ce-f49e2119ec42")

.comdef ICompositionTargetFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xf0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionTexture_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionTexture_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionTexture <"Windows.UI.Composition.ICompositionTexture">
DEFINE_IIDX(ICompositionTexture, "347d03a0-1c0a-4c0b-b232-8570b2b1a4ea")

.comdef ICompositionTexture : public IInspectable
    get_SourceRect      proc :ptr
    put_SourceRect      proc :Windows::Graphics::RectInt32
    get_AlphaMode       proc :ptr
    put_AlphaMode       proc :Windows::Graphics::DirectX::DirectXAlphaMode
    get_ColorSpace      proc :ptr
    put_ColorSpace      proc :Windows::Graphics::DirectX::DirectXColorSpace
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xf0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionTextureFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionTextureFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionTextureFactory <"Windows.UI.Composition.ICompositionTextureFactory">
DEFINE_IIDX(ICompositionTextureFactory, "09d9523d-471c-5ab5-b053-b568ee46ebfb")

.comdef ICompositionTextureFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionTransform <"Windows.UI.Composition.ICompositionTransform">
DEFINE_IIDX(ICompositionTransform, "7cd54529-fbed-4112-abc5-185906dd927c")

.comdef ICompositionTransform : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionTransformFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionTransformFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionTransformFactory <"Windows.UI.Composition.ICompositionTransformFactory">
DEFINE_IIDX(ICompositionTransformFactory, "aaaeca26-c149-517a-8f72-6bff7a65ce08")

.comdef ICompositionTransformFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionViewBox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionViewBox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionViewBox <"Windows.UI.Composition.ICompositionViewBox">
DEFINE_IIDX(ICompositionViewBox, "b440bf07-068f-4537-84c6-4ecbe019e1f4")

.comdef ICompositionViewBox : public IInspectable
    get_HorizontalAlignmentRatio proc :ptr
    put_HorizontalAlignmentRatio proc :FLOAT
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector2
    get_Size            proc :ptr
    put_Size            proc :Windows::Foundation::Numerics::Vector2
    get_Stretch         proc :ptr
    put_Stretch         proc :Windows::UI::Composition::CompositionStretch
    get_VerticalAlignmentRatio proc :ptr
    put_VerticalAlignmentRatio proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionVirtualDrawingSurface_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionVirtualDrawingSurface_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionVirtualDrawingSurface <"Windows.UI.Composition.ICompositionVirtualDrawingSurface">
DEFINE_IIDX(ICompositionVirtualDrawingSurface, "a9c384db-8740-4f94-8b9d-b68521e7863d")

.comdef ICompositionVirtualDrawingSurface : public IInspectable
    Trim                proc :UINT32, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionVirtualDrawingSurfaceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionVirtualDrawingSurfaceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionVirtualDrawingSurfaceFactory <"Windows.UI.Composition.ICompositionVirtualDrawingSurfaceFactory">
DEFINE_IIDX(ICompositionVirtualDrawingSurfaceFactory, "6766106c-d56b-4a49-b1df-5076a0620768")

.comdef ICompositionVirtualDrawingSurfaceFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionVisualSurface_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositionVisualSurface_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositionVisualSurface <"Windows.UI.Composition.ICompositionVisualSurface">
DEFINE_IIDX(ICompositionVisualSurface, "b224d803-4f6e-4a3f-8cae-3dc1cda74fc6")

.comdef ICompositionVisualSurface : public IInspectable
    get_SourceVisual    proc :ptr ptr
    put_SourceVisual    proc :ptr
    get_SourceOffset    proc :ptr
    put_SourceOffset    proc :Windows::Foundation::Numerics::Vector2
    get_SourceSize      proc :ptr
    put_SourceSize      proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositor_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositor <"Windows.UI.Composition.ICompositor">
DEFINE_IIDX(ICompositor, "b403ca50-7f8c-4e83-985f-cc45060036d8")

.comdef ICompositor : public IInspectable
    CreateColorKeyFrameAnimation proc :ptr ptr
    CreateColorBrush    proc :ptr ptr
    CreateColorBrushWithColor proc :Windows::UI::Color, :ptr ptr
    CreateContainerVisual proc :ptr ptr
    CreateCubicBezierEasingFunction proc :Windows::Foundation::Numerics::Vector2, :Windows::Foundation::Numerics::Vector2, :ptr ptr
    CreateEffectFactory proc :ptr, :ptr ptr
    CreateEffectFactoryWithProperties proc :ptr, :ptr, :ptr ptr
    CreateExpressionAnimation proc :ptr ptr
    CreateExpressionAnimationWithExpression proc :HSTRING, :ptr ptr
    CreateInsetClip     proc :ptr ptr
    CreateInsetClipWithInsets proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr ptr
    CreateLinearEasingFunction proc :ptr ptr
    CreatePropertySet   proc :ptr ptr
    CreateQuaternionKeyFrameAnimation proc :ptr ptr
    CreateScalarKeyFrameAnimation proc :ptr ptr
    CreateScopedBatch   proc :Windows::UI::Composition::CompositionBatchTypes, :ptr ptr
    CreateSpriteVisual  proc :ptr ptr
    CreateSurfaceBrush  proc :ptr ptr
    CreateSurfaceBrushWithSurface proc :ptr, :ptr ptr
    CreateTargetForCurrentView proc :ptr ptr
    CreateVector2KeyFrameAnimation proc :ptr ptr
    CreateVector3KeyFrameAnimation proc :ptr ptr
    CreateVector4KeyFrameAnimation proc :ptr ptr
    GetCommitBatch      proc :Windows::UI::Composition::CompositionBatchTypes, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositor2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositor2 <"Windows.UI.Composition.ICompositor2">
DEFINE_IIDX(ICompositor2, "735081dc-5e24-45da-a38f-e32cc349a9a0")

.comdef ICompositor2 : public IInspectable
    CreateAmbientLight  proc :ptr ptr
    CreateAnimationGroup proc :ptr ptr
    CreateBackdropBrush proc :ptr ptr
    CreateDistantLight  proc :ptr ptr
    CreateDropShadow    proc :ptr ptr
    CreateImplicitAnimationCollection proc :ptr ptr
    CreateLayerVisual   proc :ptr ptr
    CreateMaskBrush     proc :ptr ptr
    CreateNineGridBrush proc :ptr ptr
    CreatePointLight    proc :ptr ptr
    CreateSpotLight     proc :ptr ptr
    CreateStepEasingFunction proc :ptr ptr
    CreateStepEasingFunctionWithStepCount proc :INT32, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositor3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositor3 <"Windows.UI.Composition.ICompositor3">
DEFINE_IIDX(ICompositor3, "c9dd8ef0-6eb1-4e3c-a658-675d9c64d4ab")

.comdef ICompositor3 : public IInspectable
    CreateHostBackdropBrush proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositor4_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositor4 <"Windows.UI.Composition.ICompositor4">
DEFINE_IIDX(ICompositor4, "ae47e78a-7910-4425-a482-a05b758adce9")

.comdef ICompositor4 : public IInspectable
    CreateColorGradientStop proc :ptr ptr
    CreateColorGradientStopWithOffsetAndColor proc :FLOAT, :Windows::UI::Color, :ptr ptr
    CreateLinearGradientBrush proc :ptr ptr
    CreateSpringScalarAnimation proc :ptr ptr
    CreateSpringVector2Animation proc :ptr ptr
    CreateSpringVector3Animation proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor5_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositor5_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositor5 <"Windows.UI.Composition.ICompositor5">
DEFINE_IIDX(ICompositor5, "48ea31ad-7fcd-4076-a79c-90cc4b852c9b")

.comdef ICompositor5 : public IInspectable
    get_Comment         proc :ptr
    put_Comment         proc :HSTRING
    get_GlobalPlaybackRate proc :ptr
    put_GlobalPlaybackRate proc :FLOAT
    CreateBounceScalarAnimation proc :ptr ptr
    CreateBounceVector2Animation proc :ptr ptr
    CreateBounceVector3Animation proc :ptr ptr
    CreateContainerShape proc :ptr ptr
    CreateEllipseGeometry proc :ptr ptr
    CreateLineGeometry  proc :ptr ptr
    CreatePathGeometry  proc :ptr ptr
    CreatePathGeometryWithPath proc :ptr, :ptr ptr
    CreatePathKeyFrameAnimation proc :ptr ptr
    CreateRectangleGeometry proc :ptr ptr
    CreateRoundedRectangleGeometry proc :ptr ptr
    CreateShapeVisual   proc :ptr ptr
    CreateSpriteShape   proc :ptr ptr
    CreateSpriteShapeWithGeometry proc :ptr, :ptr ptr
    CreateViewBox       proc :ptr ptr
    RequestCommitAsync  proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor6_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositor6_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositor6 <"Windows.UI.Composition.ICompositor6">
DEFINE_IIDX(ICompositor6, "7a38b2bd-cec8-4eeb-830f-d8d07aedebc3")

.comdef ICompositor6 : public IInspectable
    CreateGeometricClip proc :ptr ptr
    CreateGeometricClipWithGeometry proc :ptr, :ptr ptr
    CreateRedirectVisual proc :ptr ptr
    CreateRedirectVisualWithSourceVisual proc :ptr, :ptr ptr
    CreateBooleanKeyFrameAnimation proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor7_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositor7_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositor7 <"Windows.UI.Composition.ICompositor7">
DEFINE_IIDX(ICompositor7, "d3483fad-9a12-53ba-bfc8-88b7ff7977c6")

.comdef ICompositor7 : public IInspectable
    get_DispatcherQueue proc :ptr ptr
    CreateAnimationPropertyInfo proc :ptr ptr
    CreateRectangleClip proc :ptr ptr
    CreateRectangleClipWithSides proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr ptr
    CreateRectangleClipWithSidesAndRadius proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :Windows::Foundation::Numerics::Vector2, :Windows::Foundation::Numerics::Vector2, :Windows::Foundation::Numerics::Vector2, :Windows::Foundation::Numerics::Vector2, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xf0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor8_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositor8_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositor8 <"Windows.UI.Composition.ICompositor8">
DEFINE_IIDX(ICompositor8, "9a0bdee2-fe7b-5f62-a366-9cf8effe2112")

.comdef ICompositor8 : public IInspectable
    CreateAnimationController proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositorStatics <"Windows.UI.Composition.ICompositorStatics">
DEFINE_IIDX(ICompositorStatics, "080db93e-121e-4d97-8b74-1dfcf91987ea")

.comdef ICompositorStatics : public IInspectable
    get_MaxGlobalPlaybackRate proc :ptr
    get_MinGlobalPlaybackRate proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xd0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositorWithBlurredWallpaperBackdropBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositorWithBlurredWallpaperBackdropBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositorWithBlurredWallpaperBackdropBrush <"Windows.UI.Composition.ICompositorWithBlurredWallpaperBackdropBrush">
DEFINE_IIDX(ICompositorWithBlurredWallpaperBackdropBrush, "0d8fb190-f122-5b8d-9fdd-543b0d8eb7f3")

.comdef ICompositorWithBlurredWallpaperBackdropBrush : public IInspectable
    TryCreateBlurredWallpaperBackdropBrush proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositorWithProjectedShadow_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositorWithProjectedShadow_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositorWithProjectedShadow <"Windows.UI.Composition.ICompositorWithProjectedShadow">
DEFINE_IIDX(ICompositorWithProjectedShadow, "a2e6330e-8a60-5a38-bb85-b44ea901677c")

.comdef ICompositorWithProjectedShadow : public IInspectable
    CreateProjectedShadowCaster proc :ptr ptr
    CreateProjectedShadow proc :ptr ptr
    CreateProjectedShadowReceiver proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositorWithRadialGradient_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositorWithRadialGradient_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositorWithRadialGradient <"Windows.UI.Composition.ICompositorWithRadialGradient">
DEFINE_IIDX(ICompositorWithRadialGradient, "98b9c1a7-8e71-4b53-b4a8-69ba5d19dc5b")

.comdef ICompositorWithRadialGradient : public IInspectable
    CreateRadialGradientBrush proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositorWithVisualSurface_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICompositorWithVisualSurface_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICompositorWithVisualSurface <"Windows.UI.Composition.ICompositorWithVisualSurface">
DEFINE_IIDX(ICompositorWithVisualSurface, "cfa1658b-0123-4551-8891-89bdcc40322b")

.comdef ICompositorWithVisualSurface : public IInspectable
    CreateVisualSurface proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIContainerVisual_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIContainerVisual_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IContainerVisual <"Windows.UI.Composition.IContainerVisual">
DEFINE_IIDX(IContainerVisual, "02f6bc74-ed20-4773-afe6-d49b4a93db32")

.comdef IContainerVisual : public IInspectable
    get_Children        proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIContainerVisualFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIContainerVisualFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IContainerVisualFactory <"Windows.UI.Composition.IContainerVisualFactory">
DEFINE_IIDX(IContainerVisualFactory, "0363a65b-c7da-4d9a-95f4-69b5c8df670b")

.comdef IContainerVisualFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CICubicBezierEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CICubicBezierEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ICubicBezierEasingFunction <"Windows.UI.Composition.ICubicBezierEasingFunction">
DEFINE_IIDX(ICubicBezierEasingFunction, "32350666-c1e8-44f9-96b8-c98acf0ae698")

.comdef ICubicBezierEasingFunction : public IInspectable
    get_ControlPoint1   proc :ptr
    get_ControlPoint2   proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIDelegatedInkTrailVisual_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIDelegatedInkTrailVisual_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IDelegatedInkTrailVisual <"Windows.UI.Composition.IDelegatedInkTrailVisual">
DEFINE_IIDX(IDelegatedInkTrailVisual, "856e60b1-e1ab-5b23-8e3d-d513f221c998")

.comdef IDelegatedInkTrailVisual : public IInspectable
    AddTrailPoints      proc :UINT32, :ptr, :ptr
    AddTrailPointsWithPrediction proc :UINT32, :ptr, :UINT32, :ptr, :ptr
    RemoveTrailPoints   proc :UINT32
    StartNewTrail       proc :Windows::UI::Color
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIDelegatedInkTrailVisualStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIDelegatedInkTrailVisualStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IDelegatedInkTrailVisualStatics <"Windows.UI.Composition.IDelegatedInkTrailVisualStatics">
DEFINE_IIDX(IDelegatedInkTrailVisualStatics, "0daf6bd5-42c6-555c-9267-e0ac663af836")

.comdef IDelegatedInkTrailVisualStatics : public IInspectable
    Create              proc :ptr, :ptr ptr
    CreateForSwapChain  proc :ptr, :ptr, :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIDistantLight_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIDistantLight_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IDistantLight <"Windows.UI.Composition.IDistantLight">
DEFINE_IIDX(IDistantLight, "318cfafc-5ce3-4b55-ab5d-07a00353ac99")

.comdef IDistantLight : public IInspectable
    get_Color           proc :ptr
    put_Color           proc :Windows::UI::Color
    get_CoordinateSpace proc :ptr ptr
    put_CoordinateSpace proc :ptr
    get_Direction       proc :ptr
    put_Direction       proc :Windows::Foundation::Numerics::Vector3
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIDistantLight2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIDistantLight2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IDistantLight2 <"Windows.UI.Composition.IDistantLight2">
DEFINE_IIDX(IDistantLight2, "dbcdaa1c-294b-48d7-b60e-76df64aa392b")

.comdef IDistantLight2 : public IInspectable
    get_Intensity       proc :ptr
    put_Intensity       proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIDropShadow_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIDropShadow_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IDropShadow <"Windows.UI.Composition.IDropShadow">
DEFINE_IIDX(IDropShadow, "cb977c07-a154-4851-85e7-a8924c84fad8")

.comdef IDropShadow : public IInspectable
    get_BlurRadius      proc :ptr
    put_BlurRadius      proc :FLOAT
    get_Color           proc :ptr
    put_Color           proc :Windows::UI::Color
    get_Mask            proc :ptr ptr
    put_Mask            proc :ptr
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector3
    get_Opacity         proc :ptr
    put_Opacity         proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIDropShadow2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIDropShadow2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IDropShadow2 <"Windows.UI.Composition.IDropShadow2">
DEFINE_IIDX(IDropShadow2, "6c4218bc-15b9-4c2d-8d4a-0767df11977a")

.comdef IDropShadow2 : public IInspectable
    get_SourcePolicy    proc :ptr
    put_SourcePolicy    proc :Windows::UI::Composition::CompositionDropShadowSourcePolicy
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIElasticEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIElasticEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IElasticEasingFunction <"Windows.UI.Composition.IElasticEasingFunction">
DEFINE_IIDX(IElasticEasingFunction, "66de6285-054e-5594-8475-c22cb51f1bd5")

.comdef IElasticEasingFunction : public IInspectable
    get_Mode            proc :ptr
    get_Oscillations    proc :ptr
    get_Springiness     proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIExponentialEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIExponentialEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IExponentialEasingFunction <"Windows.UI.Composition.IExponentialEasingFunction">
DEFINE_IIDX(IExponentialEasingFunction, "6f7d1a51-98d2-5638-a34a-00486554c750")

.comdef IExponentialEasingFunction : public IInspectable
    get_Mode            proc :ptr
    get_Exponent        proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIExpressionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIExpressionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IExpressionAnimation <"Windows.UI.Composition.IExpressionAnimation">
DEFINE_IIDX(IExpressionAnimation, "6acc5431-7d3d-4bf3-abb6-f44bdc4888c1")

.comdef IExpressionAnimation : public IInspectable
    get_Expression      proc :ptr
    put_Expression      proc :HSTRING
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIImplicitAnimationCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIImplicitAnimationCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IImplicitAnimationCollection <"Windows.UI.Composition.IImplicitAnimationCollection">
DEFINE_IIDX(IImplicitAnimationCollection, "0598a3ff-0a92-4c9d-a427-b25519250dbf")

.comdef IImplicitAnimationCollection : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIInsetClip_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIInsetClip_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IInsetClip <"Windows.UI.Composition.IInsetClip">
DEFINE_IIDX(IInsetClip, "1e73e647-84c7-477a-b474-5880e0442e15")

.comdef IInsetClip : public IInspectable
    get_BottomInset     proc :ptr
    put_BottomInset     proc :FLOAT
    get_LeftInset       proc :ptr
    put_LeftInset       proc :FLOAT
    get_RightInset      proc :ptr
    put_RightInset      proc :FLOAT
    get_TopInset        proc :ptr
    put_TopInset        proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIKeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIKeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IKeyFrameAnimation <"Windows.UI.Composition.IKeyFrameAnimation">
DEFINE_IIDX(IKeyFrameAnimation, "126e7f22-3ae9-4540-9a8a-deae8a4a4a84")

.comdef IKeyFrameAnimation : public IInspectable
    get_DelayTime       proc :ptr
    put_DelayTime       proc :Windows::Foundation::TimeSpan
    get_Duration        proc :ptr
    put_Duration        proc :Windows::Foundation::TimeSpan
    get_IterationBehavior proc :ptr
    put_IterationBehavior proc :Windows::UI::Composition::AnimationIterationBehavior
    get_IterationCount  proc :ptr
    put_IterationCount  proc :INT32
    get_KeyFrameCount   proc :ptr
    get_StopBehavior    proc :ptr
    put_StopBehavior    proc :Windows::UI::Composition::AnimationStopBehavior
    InsertExpressionKeyFrame proc :FLOAT, :HSTRING
    InsertExpressionKeyFrameWithEasingFunction proc :FLOAT, :HSTRING, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIKeyFrameAnimation2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIKeyFrameAnimation2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IKeyFrameAnimation2 <"Windows.UI.Composition.IKeyFrameAnimation2">
DEFINE_IIDX(IKeyFrameAnimation2, "f4b488bb-2940-4ec0-a41a-eb6d801a2f18")

.comdef IKeyFrameAnimation2 : public IInspectable
    get_Direction       proc :ptr
    put_Direction       proc :Windows::UI::Composition::AnimationDirection
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIKeyFrameAnimation3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIKeyFrameAnimation3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IKeyFrameAnimation3 <"Windows.UI.Composition.IKeyFrameAnimation3">
DEFINE_IIDX(IKeyFrameAnimation3, "845bf0b4-d8de-462f-8753-c80d43c6ff5a")

.comdef IKeyFrameAnimation3 : public IInspectable
    get_DelayBehavior   proc :ptr
    put_DelayBehavior   proc :Windows::UI::Composition::AnimationDelayBehavior
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIKeyFrameAnimationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIKeyFrameAnimationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IKeyFrameAnimationFactory <"Windows.UI.Composition.IKeyFrameAnimationFactory">
DEFINE_IIDX(IKeyFrameAnimationFactory, "bf0803f8-712a-4fc1-8c87-970859ed8d2e")

.comdef IKeyFrameAnimationFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CILayerVisual_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CILayerVisual_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ILayerVisual <"Windows.UI.Composition.ILayerVisual">
DEFINE_IIDX(ILayerVisual, "af843985-0444-4887-8e83-b40b253f822c")

.comdef ILayerVisual : public IInspectable
    get_Effect          proc :ptr ptr
    put_Effect          proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CILayerVisual2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CILayerVisual2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ILayerVisual2 <"Windows.UI.Composition.ILayerVisual2">
DEFINE_IIDX(ILayerVisual2, "98f9aeeb-6f23-49f1-90b1-1f59a14fbce3")

.comdef ILayerVisual2 : public IInspectable
    get_Shadow          proc :ptr ptr
    put_Shadow          proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CILinearEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CILinearEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ILinearEasingFunction <"Windows.UI.Composition.ILinearEasingFunction">
DEFINE_IIDX(ILinearEasingFunction, "9400975a-c7a6-46b3-acf7-1a268a0a117d")

.comdef ILinearEasingFunction : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CINaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CINaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_INaturalMotionAnimation <"Windows.UI.Composition.INaturalMotionAnimation">
DEFINE_IIDX(INaturalMotionAnimation, "438de12d-769b-4821-a949-284a6547e873")

.comdef INaturalMotionAnimation : public IInspectable
    get_DelayBehavior   proc :ptr
    put_DelayBehavior   proc :Windows::UI::Composition::AnimationDelayBehavior
    get_DelayTime       proc :ptr
    put_DelayTime       proc :Windows::Foundation::TimeSpan
    get_StopBehavior    proc :ptr
    put_StopBehavior    proc :Windows::UI::Composition::AnimationStopBehavior
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CINaturalMotionAnimationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CINaturalMotionAnimationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_INaturalMotionAnimationFactory <"Windows.UI.Composition.INaturalMotionAnimationFactory">
DEFINE_IIDX(INaturalMotionAnimationFactory, "f53acb06-cf6a-4387-a3fe-5221f3e7e0e0")

.comdef INaturalMotionAnimationFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIPathKeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIPathKeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IPathKeyFrameAnimation <"Windows.UI.Composition.IPathKeyFrameAnimation">
DEFINE_IIDX(IPathKeyFrameAnimation, "9d0d18c9-1576-4b3f-be60-1d5031f5e71b")

.comdef IPathKeyFrameAnimation : public IInspectable
    InsertKeyFrame      proc :FLOAT, :ptr
    InsertKeyFrameWithEasingFunction proc :FLOAT, :ptr, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIPointLight_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIPointLight_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IPointLight <"Windows.UI.Composition.IPointLight">
DEFINE_IIDX(IPointLight, "b18545b3-0c5a-4ab0-bedc-4f3546948272")

.comdef IPointLight : public IInspectable
    get_Color           proc :ptr
    put_Color           proc :Windows::UI::Color
    get_ConstantAttenuation proc :ptr
    put_ConstantAttenuation proc :FLOAT
    get_CoordinateSpace proc :ptr ptr
    put_CoordinateSpace proc :ptr
    get_LinearAttenuation proc :ptr
    put_LinearAttenuation proc :FLOAT
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector3
    get_QuadraticAttenuation proc :ptr
    put_QuadraticAttenuation proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIPointLight2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIPointLight2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IPointLight2 <"Windows.UI.Composition.IPointLight2">
DEFINE_IIDX(IPointLight2, "efe98f2c-0678-4f69-b164-a810d995bcb7")

.comdef IPointLight2 : public IInspectable
    get_Intensity       proc :ptr
    put_Intensity       proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIPointLight3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIPointLight3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IPointLight3 <"Windows.UI.Composition.IPointLight3">
DEFINE_IIDX(IPointLight3, "4c0a8367-d4e9-468a-87ae-7ba43ab29485")

.comdef IPointLight3 : public IInspectable
    get_MinAttenuationCutoff proc :ptr
    put_MinAttenuationCutoff proc :FLOAT
    get_MaxAttenuationCutoff proc :ptr
    put_MaxAttenuationCutoff proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIPowerEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIPowerEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IPowerEasingFunction <"Windows.UI.Composition.IPowerEasingFunction">
DEFINE_IIDX(IPowerEasingFunction, "c3ff53d6-138b-5815-891a-b7f615ccc563")

.comdef IPowerEasingFunction : public IInspectable
    get_Mode            proc :ptr
    get_Power           proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIQuaternionKeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIQuaternionKeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IQuaternionKeyFrameAnimation <"Windows.UI.Composition.IQuaternionKeyFrameAnimation">
DEFINE_IIDX(IQuaternionKeyFrameAnimation, "404e5835-ecf6-4240-8520-671279cf36bc")

.comdef IQuaternionKeyFrameAnimation : public IInspectable
    InsertKeyFrame      proc :FLOAT, :Windows::Foundation::Numerics::Quaternion
    InsertKeyFrameWithEasingFunction proc :FLOAT, :Windows::Foundation::Numerics::Quaternion, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIRectangleClip_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIRectangleClip_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IRectangleClip <"Windows.UI.Composition.IRectangleClip">
DEFINE_IIDX(IRectangleClip, "b3e7549e-00b4-5b53-8be8-353f6c433101")

.comdef IRectangleClip : public IInspectable
    get_Bottom          proc :ptr
    put_Bottom          proc :FLOAT
    get_BottomLeftRadius proc :ptr
    put_BottomLeftRadius proc :Windows::Foundation::Numerics::Vector2
    get_BottomRightRadius proc :ptr
    put_BottomRightRadius proc :Windows::Foundation::Numerics::Vector2
    get_Left            proc :ptr
    put_Left            proc :FLOAT
    get_Right           proc :ptr
    put_Right           proc :FLOAT
    get_Top             proc :ptr
    put_Top             proc :FLOAT
    get_TopLeftRadius   proc :ptr
    put_TopLeftRadius   proc :Windows::Foundation::Numerics::Vector2
    get_TopRightRadius  proc :ptr
    put_TopRightRadius  proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIRedirectVisual_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIRedirectVisual_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IRedirectVisual <"Windows.UI.Composition.IRedirectVisual">
DEFINE_IIDX(IRedirectVisual, "8cc6e340-8b75-5422-b06f-09ffe9f8617e")

.comdef IRedirectVisual : public IInspectable
    get_Source          proc :ptr ptr
    put_Source          proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIRenderingDeviceReplacedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIRenderingDeviceReplacedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IRenderingDeviceReplacedEventArgs <"Windows.UI.Composition.IRenderingDeviceReplacedEventArgs">
DEFINE_IIDX(IRenderingDeviceReplacedEventArgs, "3a31ac7d-28bf-4e7a-8524-71679d480f38")

.comdef IRenderingDeviceReplacedEventArgs : public IInspectable
    get_GraphicsDevice  proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIScalarKeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIScalarKeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IScalarKeyFrameAnimation <"Windows.UI.Composition.IScalarKeyFrameAnimation">
DEFINE_IIDX(IScalarKeyFrameAnimation, "ae288fa9-252c-4b95-a725-bf85e38000a1")

.comdef IScalarKeyFrameAnimation : public IInspectable
    InsertKeyFrame      proc :FLOAT, :FLOAT
    InsertKeyFrameWithEasingFunction proc :FLOAT, :FLOAT, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIScalarNaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIScalarNaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IScalarNaturalMotionAnimation <"Windows.UI.Composition.IScalarNaturalMotionAnimation">
DEFINE_IIDX(IScalarNaturalMotionAnimation, "94a94581-bf92-495b-b5bd-d2c659430737")

.comdef IScalarNaturalMotionAnimation : public IInspectable
    get_FinalValue      proc :ptr ptr
    put_FinalValue      proc :ptr
    get_InitialValue    proc :ptr ptr
    put_InitialValue    proc :ptr
    get_InitialVelocity proc :ptr
    put_InitialVelocity proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIScalarNaturalMotionAnimationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIScalarNaturalMotionAnimationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IScalarNaturalMotionAnimationFactory <"Windows.UI.Composition.IScalarNaturalMotionAnimationFactory">
DEFINE_IIDX(IScalarNaturalMotionAnimationFactory, "835aa4fc-671c-41dd-af48-ae8def8b1529")

.comdef IScalarNaturalMotionAnimationFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIShapeVisual_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIShapeVisual_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IShapeVisual <"Windows.UI.Composition.IShapeVisual">
DEFINE_IIDX(IShapeVisual, "f2bd13c3-ba7e-4b0f-9126-ffb7536b8176")

.comdef IShapeVisual : public IInspectable
    get_Shapes          proc :ptr ptr
    get_ViewBox         proc :ptr ptr
    put_ViewBox         proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISineEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISineEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISineEasingFunction <"Windows.UI.Composition.ISineEasingFunction">
DEFINE_IIDX(ISineEasingFunction, "f1b518bf-9563-5474-bd13-44b2df4b1d58")

.comdef ISineEasingFunction : public IInspectable
    get_Mode            proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISpotLight_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISpotLight_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISpotLight <"Windows.UI.Composition.ISpotLight">
DEFINE_IIDX(ISpotLight, "5a9fe273-44a1-4f95-a422-8fa5116bdb44")

.comdef ISpotLight : public IInspectable
    get_ConstantAttenuation proc :ptr
    put_ConstantAttenuation proc :FLOAT
    get_CoordinateSpace proc :ptr ptr
    put_CoordinateSpace proc :ptr
    get_Direction       proc :ptr
    put_Direction       proc :Windows::Foundation::Numerics::Vector3
    get_InnerConeAngle  proc :ptr
    put_InnerConeAngle  proc :FLOAT
    get_InnerConeAngleInDegrees proc :ptr
    put_InnerConeAngleInDegrees proc :FLOAT
    get_InnerConeColor  proc :ptr
    put_InnerConeColor  proc :Windows::UI::Color
    get_LinearAttenuation proc :ptr
    put_LinearAttenuation proc :FLOAT
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector3
    get_OuterConeAngle  proc :ptr
    put_OuterConeAngle  proc :FLOAT
    get_OuterConeAngleInDegrees proc :ptr
    put_OuterConeAngleInDegrees proc :FLOAT
    get_OuterConeColor  proc :ptr
    put_OuterConeColor  proc :Windows::UI::Color
    get_QuadraticAttenuation proc :ptr
    put_QuadraticAttenuation proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISpotLight2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISpotLight2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISpotLight2 <"Windows.UI.Composition.ISpotLight2">
DEFINE_IIDX(ISpotLight2, "64ee615e-0686-4dea-a9e8-bc3a8c701459")

.comdef ISpotLight2 : public IInspectable
    get_InnerConeIntensity proc :ptr
    put_InnerConeIntensity proc :FLOAT
    get_OuterConeIntensity proc :ptr
    put_OuterConeIntensity proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISpotLight3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISpotLight3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISpotLight3 <"Windows.UI.Composition.ISpotLight3">
DEFINE_IIDX(ISpotLight3, "e4d03eea-131f-480e-859e-b82705b74360")

.comdef ISpotLight3 : public IInspectable
    get_MinAttenuationCutoff proc :ptr
    put_MinAttenuationCutoff proc :FLOAT
    get_MaxAttenuationCutoff proc :ptr
    put_MaxAttenuationCutoff proc :FLOAT
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISpringScalarNaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISpringScalarNaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISpringScalarNaturalMotionAnimation <"Windows.UI.Composition.ISpringScalarNaturalMotionAnimation">
DEFINE_IIDX(ISpringScalarNaturalMotionAnimation, "0572a95f-37f9-4fbe-b87b-5cd03a89501c")

.comdef ISpringScalarNaturalMotionAnimation : public IInspectable
    get_DampingRatio    proc :ptr
    put_DampingRatio    proc :FLOAT
    get_Period          proc :ptr
    put_Period          proc :Windows::Foundation::TimeSpan
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISpringVector2NaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISpringVector2NaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISpringVector2NaturalMotionAnimation <"Windows.UI.Composition.ISpringVector2NaturalMotionAnimation">
DEFINE_IIDX(ISpringVector2NaturalMotionAnimation, "23f494b5-ee73-4f0f-a423-402b946df4b3")

.comdef ISpringVector2NaturalMotionAnimation : public IInspectable
    get_DampingRatio    proc :ptr
    put_DampingRatio    proc :FLOAT
    get_Period          proc :ptr
    put_Period          proc :Windows::Foundation::TimeSpan
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISpringVector3NaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISpringVector3NaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISpringVector3NaturalMotionAnimation <"Windows.UI.Composition.ISpringVector3NaturalMotionAnimation">
DEFINE_IIDX(ISpringVector3NaturalMotionAnimation, "6c8749df-d57b-4794-8e2d-cecb11e194e5")

.comdef ISpringVector3NaturalMotionAnimation : public IInspectable
    get_DampingRatio    proc :ptr
    put_DampingRatio    proc :FLOAT
    get_Period          proc :ptr
    put_Period          proc :Windows::Foundation::TimeSpan
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISpriteVisual_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISpriteVisual_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISpriteVisual <"Windows.UI.Composition.ISpriteVisual">
DEFINE_IIDX(ISpriteVisual, "08e05581-1ad1-4f97-9757-402d76e4233b")

.comdef ISpriteVisual : public IInspectable
    get_Brush           proc :ptr ptr
    put_Brush           proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CISpriteVisual2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CISpriteVisual2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_ISpriteVisual2 <"Windows.UI.Composition.ISpriteVisual2">
DEFINE_IIDX(ISpriteVisual2, "588c9664-997a-4850-91fe-53cb58f81ce9")

.comdef ISpriteVisual2 : public IInspectable
    get_Shadow          proc :ptr ptr
    put_Shadow          proc :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIStepEasingFunction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIStepEasingFunction_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IStepEasingFunction <"Windows.UI.Composition.IStepEasingFunction">
DEFINE_IIDX(IStepEasingFunction, "d0caa74b-560c-4a0b-a5f6-206ca8c3ecd6")

.comdef IStepEasingFunction : public IInspectable
    get_FinalStep       proc :ptr
    put_FinalStep       proc :INT32
    get_InitialStep     proc :ptr
    put_InitialStep     proc :INT32
    get_IsFinalStepSingleFrame proc :ptr
    put_IsFinalStepSingleFrame proc :boolean
    get_IsInitialStepSingleFrame proc :ptr
    put_IsInitialStepSingleFrame proc :boolean
    get_StepCount       proc :ptr
    put_StepCount       proc :INT32
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVector2KeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVector2KeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVector2KeyFrameAnimation <"Windows.UI.Composition.IVector2KeyFrameAnimation">
DEFINE_IIDX(IVector2KeyFrameAnimation, "df414515-4e29-4f11-b55e-bf2a6eb36294")

.comdef IVector2KeyFrameAnimation : public IInspectable
    InsertKeyFrame      proc :FLOAT, :Windows::Foundation::Numerics::Vector2
    InsertKeyFrameWithEasingFunction proc :FLOAT, :Windows::Foundation::Numerics::Vector2, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVector2NaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVector2NaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVector2NaturalMotionAnimation <"Windows.UI.Composition.IVector2NaturalMotionAnimation">
DEFINE_IIDX(IVector2NaturalMotionAnimation, "0f3e0b7d-e512-479d-a00c-77c93a30a395")

.comdef IVector2NaturalMotionAnimation : public IInspectable
    get_FinalValue      proc :ptr ptr
    put_FinalValue      proc :ptr
    get_InitialValue    proc :ptr ptr
    put_InitialValue    proc :ptr
    get_InitialVelocity proc :ptr
    put_InitialVelocity proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVector2NaturalMotionAnimationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVector2NaturalMotionAnimationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVector2NaturalMotionAnimationFactory <"Windows.UI.Composition.IVector2NaturalMotionAnimationFactory">
DEFINE_IIDX(IVector2NaturalMotionAnimationFactory, "8c74ff61-0761-48a2-bddb-6afcc52b89d8")

.comdef IVector2NaturalMotionAnimationFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVector3KeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVector3KeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVector3KeyFrameAnimation <"Windows.UI.Composition.IVector3KeyFrameAnimation">
DEFINE_IIDX(IVector3KeyFrameAnimation, "c8039daa-a281-43c2-a73d-b68e3c533c40")

.comdef IVector3KeyFrameAnimation : public IInspectable
    InsertKeyFrame      proc :FLOAT, :Windows::Foundation::Numerics::Vector3
    InsertKeyFrameWithEasingFunction proc :FLOAT, :Windows::Foundation::Numerics::Vector3, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVector3NaturalMotionAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVector3NaturalMotionAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVector3NaturalMotionAnimation <"Windows.UI.Composition.IVector3NaturalMotionAnimation">
DEFINE_IIDX(IVector3NaturalMotionAnimation, "9c17042c-e2ca-45ad-969e-4e78b7b9ad41")

.comdef IVector3NaturalMotionAnimation : public IInspectable
    get_FinalValue      proc :ptr ptr
    put_FinalValue      proc :ptr
    get_InitialValue    proc :ptr ptr
    put_InitialValue    proc :ptr
    get_InitialVelocity proc :ptr
    put_InitialVelocity proc :Windows::Foundation::Numerics::Vector3
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVector3NaturalMotionAnimationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVector3NaturalMotionAnimationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVector3NaturalMotionAnimationFactory <"Windows.UI.Composition.IVector3NaturalMotionAnimationFactory">
DEFINE_IIDX(IVector3NaturalMotionAnimationFactory, "21a81d2f-0880-457b-ac87-b609018c876d")

.comdef IVector3NaturalMotionAnimationFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVector4KeyFrameAnimation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVector4KeyFrameAnimation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVector4KeyFrameAnimation <"Windows.UI.Composition.IVector4KeyFrameAnimation">
DEFINE_IIDX(IVector4KeyFrameAnimation, "2457945b-addd-4385-9606-b6a3d5e4e1b9")

.comdef IVector4KeyFrameAnimation : public IInspectable
    InsertKeyFrame      proc :FLOAT, :Windows::Foundation::Numerics::Vector4
    InsertKeyFrameWithEasingFunction proc :FLOAT, :Windows::Foundation::Numerics::Vector4, :ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisual_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisual_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisual <"Windows.UI.Composition.IVisual">
DEFINE_IIDX(IVisual, "117e202d-a859-4c89-873b-c2aa566788e3")

.comdef IVisual : public IInspectable
    get_AnchorPoint     proc :ptr
    put_AnchorPoint     proc :Windows::Foundation::Numerics::Vector2
    get_BackfaceVisibility proc :ptr
    put_BackfaceVisibility proc :Windows::UI::Composition::CompositionBackfaceVisibility
    get_BorderMode      proc :ptr
    put_BorderMode      proc :Windows::UI::Composition::CompositionBorderMode
    get_CenterPoint     proc :ptr
    put_CenterPoint     proc :Windows::Foundation::Numerics::Vector3
    get_Clip            proc :ptr ptr
    put_Clip            proc :ptr
    get_CompositeMode   proc :ptr
    put_CompositeMode   proc :Windows::UI::Composition::CompositionCompositeMode
    get_IsVisible       proc :ptr
    put_IsVisible       proc :boolean
    get_Offset          proc :ptr
    put_Offset          proc :Windows::Foundation::Numerics::Vector3
    get_Opacity         proc :ptr
    put_Opacity         proc :FLOAT
    get_Orientation     proc :ptr
    put_Orientation     proc :Windows::Foundation::Numerics::Quaternion
    get_Parent          proc :ptr ptr
    get_RotationAngle   proc :ptr
    put_RotationAngle   proc :FLOAT
    get_RotationAngleInDegrees proc :ptr
    put_RotationAngleInDegrees proc :FLOAT
    get_RotationAxis    proc :ptr
    put_RotationAxis    proc :Windows::Foundation::Numerics::Vector3
    get_Scale           proc :ptr
    put_Scale           proc :Windows::Foundation::Numerics::Vector3
    get_Size            proc :ptr
    put_Size            proc :Windows::Foundation::Numerics::Vector2
    get_TransformMatrix proc :ptr
    put_TransformMatrix proc :Windows::Foundation::Numerics::Matrix4x4
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisual2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisual2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisual2 <"Windows.UI.Composition.IVisual2">
DEFINE_IIDX(IVisual2, "3052b611-56c3-4c3e-8bf3-f6e1ad473f06")

.comdef IVisual2 : public IInspectable
    get_ParentForTransform proc :ptr ptr
    put_ParentForTransform proc :ptr
    get_RelativeOffsetAdjustment proc :ptr
    put_RelativeOffsetAdjustment proc :Windows::Foundation::Numerics::Vector3
    get_RelativeSizeAdjustment proc :ptr
    put_RelativeSizeAdjustment proc :Windows::Foundation::Numerics::Vector2
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xb0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisual3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisual3_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisual3 <"Windows.UI.Composition.IVisual3">
DEFINE_IIDX(IVisual3, "30be580d-f4b6-4ab7-80dd-3738cbac9f2c")

.comdef IVisual3 : public IInspectable
    get_IsHitTestVisible proc :ptr
    put_IsHitTestVisible proc :boolean
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisual4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisual4_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisual4 <"Windows.UI.Composition.IVisual4">
DEFINE_IIDX(IVisual4, "9476bf11-e24b-5bf9-9ebe-6274109b2711")

.comdef IVisual4 : public IInspectable
    get_IsPixelSnappingEnabled proc :ptr
    put_IsPixelSnappingEnabled proc :boolean
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisualCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisualCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisualCollection <"Windows.UI.Composition.IVisualCollection">
DEFINE_IIDX(IVisualCollection, "8b745505-fd3e-4a98-84a8-e949468c6bcb")

.comdef IVisualCollection : public IInspectable
    get_Count           proc :ptr
    InsertAbove         proc :ptr, :ptr
    InsertAtBottom      proc :ptr
    InsertAtTop         proc :ptr
    InsertBelow         proc :ptr, :ptr
    Remove              proc :ptr
    RemoveAll           proc
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisualElement_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisualElement_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisualElement <"Windows.UI.Composition.IVisualElement">
DEFINE_IIDX(IVisualElement, "01e64612-1d82-42f4-8e3f-a722ded33fc7")

.comdef IVisualElement : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisualElement2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisualElement2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisualElement2 <"Windows.UI.Composition.IVisualElement2">
DEFINE_IIDX(IVisualElement2, "993ae8a0-6057-5e40-918c-e06e0b7e7c64")

.comdef IVisualElement2 : public IInspectable
    GetVisualInternal   proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisualFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisualFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisualFactory <"Windows.UI.Composition.IVisualFactory">
DEFINE_IIDX(IVisualFactory, "ad0ff93e-b502-4eb5-87b4-9a38a71d0137")

.comdef IVisualFactory : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisualUnorderedCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CComposition_CIVisualUnorderedCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Composition_IVisualUnorderedCollection <"Windows.UI.Composition.IVisualUnorderedCollection">
DEFINE_IIDX(IVisualUnorderedCollection, "338faa70-54c8-40a7-8029-c9ceeb0aa250")

.comdef IVisualUnorderedCollection : public IInspectable
    get_Count           proc :ptr
    _Add                proc :ptr
    Remove              proc :ptr
    RemoveAll           proc
   .ends
endif
endif

.endn
.endn
.endn

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_AmbientLight_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_AmbientLight_DEFINED
define RuntimeClass_Windows_UI_Composition_AmbientLight <"Windows.UI.Composition.AmbientLight">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_AnimationController_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_AnimationController_DEFINED
define RuntimeClass_Windows_UI_Composition_AnimationController <"Windows.UI.Composition.AnimationController">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef RUNTIMECLASS_Windows_UI_Composition_AnimationPropertyInfo_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_AnimationPropertyInfo_DEFINED
define RuntimeClass_Windows_UI_Composition_AnimationPropertyInfo <"Windows.UI.Composition.AnimationPropertyInfo">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_BackEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_BackEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_BackEasingFunction <"Windows.UI.Composition.BackEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef RUNTIMECLASS_Windows_UI_Composition_BooleanKeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_BooleanKeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_BooleanKeyFrameAnimation <"Windows.UI.Composition.BooleanKeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_BounceEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_BounceEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_BounceEasingFunction <"Windows.UI.Composition.BounceEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_BounceScalarNaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_BounceScalarNaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_BounceScalarNaturalMotionAnimation <"Windows.UI.Composition.BounceScalarNaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_BounceVector2NaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_BounceVector2NaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_BounceVector2NaturalMotionAnimation <"Windows.UI.Composition.BounceVector2NaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_BounceVector3NaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_BounceVector3NaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_BounceVector3NaturalMotionAnimation <"Windows.UI.Composition.BounceVector3NaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_CircleEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CircleEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_CircleEasingFunction <"Windows.UI.Composition.CircleEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_ColorKeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ColorKeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_ColorKeyFrameAnimation <"Windows.UI.Composition.ColorKeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionAnimation <"Windows.UI.Composition.CompositionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionAnimationGroup_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionAnimationGroup_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionAnimationGroup <"Windows.UI.Composition.CompositionAnimationGroup">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionBackdropBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionBackdropBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionBackdropBrush <"Windows.UI.Composition.CompositionBackdropBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionBatchCompletedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionBatchCompletedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionBatchCompletedEventArgs <"Windows.UI.Composition.CompositionBatchCompletedEventArgs">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionBrush <"Windows.UI.Composition.CompositionBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionCapabilities_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionCapabilities_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionCapabilities <"Windows.UI.Composition.CompositionCapabilities">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionClip_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionClip_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionClip <"Windows.UI.Composition.CompositionClip">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionColorBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionColorBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionColorBrush <"Windows.UI.Composition.CompositionColorBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionColorGradientStop_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionColorGradientStop_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionColorGradientStop <"Windows.UI.Composition.CompositionColorGradientStop">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionColorGradientStopCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionColorGradientStopCollection_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionColorGradientStopCollection <"Windows.UI.Composition.CompositionColorGradientStopCollection">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionCommitBatch_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionCommitBatch_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionCommitBatch <"Windows.UI.Composition.CompositionCommitBatch">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionContainerShape_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionContainerShape_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionContainerShape <"Windows.UI.Composition.CompositionContainerShape">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionDrawingSurface_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionDrawingSurface_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionDrawingSurface <"Windows.UI.Composition.CompositionDrawingSurface">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionEasingFunction <"Windows.UI.Composition.CompositionEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionEffectBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionEffectBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionEffectBrush <"Windows.UI.Composition.CompositionEffectBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionEffectFactory_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionEffectFactory_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionEffectFactory <"Windows.UI.Composition.CompositionEffectFactory">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionEffectSourceParameter_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionEffectSourceParameter_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionEffectSourceParameter <"Windows.UI.Composition.CompositionEffectSourceParameter">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionEllipseGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionEllipseGeometry_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionEllipseGeometry <"Windows.UI.Composition.CompositionEllipseGeometry">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionGeometricClip_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionGeometricClip_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionGeometricClip <"Windows.UI.Composition.CompositionGeometricClip">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionGeometry_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionGeometry <"Windows.UI.Composition.CompositionGeometry">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionGradientBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionGradientBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionGradientBrush <"Windows.UI.Composition.CompositionGradientBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionGraphicsDevice_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionGraphicsDevice_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionGraphicsDevice <"Windows.UI.Composition.CompositionGraphicsDevice">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionLight_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionLight_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionLight <"Windows.UI.Composition.CompositionLight">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionLineGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionLineGeometry_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionLineGeometry <"Windows.UI.Composition.CompositionLineGeometry">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionLinearGradientBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionLinearGradientBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionLinearGradientBrush <"Windows.UI.Composition.CompositionLinearGradientBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionMaskBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionMaskBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionMaskBrush <"Windows.UI.Composition.CompositionMaskBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionMipmapSurface_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionMipmapSurface_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionMipmapSurface <"Windows.UI.Composition.CompositionMipmapSurface">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionNineGridBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionNineGridBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionNineGridBrush <"Windows.UI.Composition.CompositionNineGridBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionObject_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionObject_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionObject <"Windows.UI.Composition.CompositionObject">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionPath_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionPath_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionPath <"Windows.UI.Composition.CompositionPath">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionPathGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionPathGeometry_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionPathGeometry <"Windows.UI.Composition.CompositionPathGeometry">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadow_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadow_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionProjectedShadow <"Windows.UI.Composition.CompositionProjectedShadow">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadowCaster_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadowCaster_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionProjectedShadowCaster <"Windows.UI.Composition.CompositionProjectedShadowCaster">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadowCasterCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadowCasterCollection_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionProjectedShadowCasterCollection <"Windows.UI.Composition.CompositionProjectedShadowCasterCollection">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadowReceiver_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadowReceiver_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionProjectedShadowReceiver <"Windows.UI.Composition.CompositionProjectedShadowReceiver">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadowReceiverUnorderedCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionProjectedShadowReceiverUnorderedCollection_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionProjectedShadowReceiverUnorderedCollection <"Windows.UI.Composition.CompositionProjectedShadowReceiverUnorderedCollection">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionPropertySet_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionPropertySet_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionPropertySet <"Windows.UI.Composition.CompositionPropertySet">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionRadialGradientBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionRadialGradientBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionRadialGradientBrush <"Windows.UI.Composition.CompositionRadialGradientBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionRectangleGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionRectangleGeometry_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionRectangleGeometry <"Windows.UI.Composition.CompositionRectangleGeometry">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionRoundedRectangleGeometry_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionRoundedRectangleGeometry_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionRoundedRectangleGeometry <"Windows.UI.Composition.CompositionRoundedRectangleGeometry">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionScopedBatch_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionScopedBatch_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionScopedBatch <"Windows.UI.Composition.CompositionScopedBatch">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionShadow_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionShadow_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionShadow <"Windows.UI.Composition.CompositionShadow">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionShape_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionShape_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionShape <"Windows.UI.Composition.CompositionShape">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionShapeCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionShapeCollection_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionShapeCollection <"Windows.UI.Composition.CompositionShapeCollection">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionSpriteShape_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionSpriteShape_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionSpriteShape <"Windows.UI.Composition.CompositionSpriteShape">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionStrokeDashArray_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionStrokeDashArray_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionStrokeDashArray <"Windows.UI.Composition.CompositionStrokeDashArray">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionSurfaceBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionSurfaceBrush_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionSurfaceBrush <"Windows.UI.Composition.CompositionSurfaceBrush">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionTarget_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionTarget_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionTarget <"Windows.UI.Composition.CompositionTarget">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xf0000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionTexture_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionTexture_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionTexture <"Windows.UI.Composition.CompositionTexture">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionTransform_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionTransform_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionTransform <"Windows.UI.Composition.CompositionTransform">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionViewBox_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionViewBox_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionViewBox <"Windows.UI.Composition.CompositionViewBox">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionVirtualDrawingSurface_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionVirtualDrawingSurface_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionVirtualDrawingSurface <"Windows.UI.Composition.CompositionVirtualDrawingSurface">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_UI_Composition_CompositionVisualSurface_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CompositionVisualSurface_DEFINED
define RuntimeClass_Windows_UI_Composition_CompositionVisualSurface <"Windows.UI.Composition.CompositionVisualSurface">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_Compositor_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_Compositor_DEFINED
define RuntimeClass_Windows_UI_Composition_Compositor <"Windows.UI.Composition.Compositor">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_ContainerVisual_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ContainerVisual_DEFINED
define RuntimeClass_Windows_UI_Composition_ContainerVisual <"Windows.UI.Composition.ContainerVisual">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_CubicBezierEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_CubicBezierEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_CubicBezierEasingFunction <"Windows.UI.Composition.CubicBezierEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_DelegatedInkTrailVisual_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_DelegatedInkTrailVisual_DEFINED
define RuntimeClass_Windows_UI_Composition_DelegatedInkTrailVisual <"Windows.UI.Composition.DelegatedInkTrailVisual">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_DistantLight_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_DistantLight_DEFINED
define RuntimeClass_Windows_UI_Composition_DistantLight <"Windows.UI.Composition.DistantLight">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_DropShadow_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_DropShadow_DEFINED
define RuntimeClass_Windows_UI_Composition_DropShadow <"Windows.UI.Composition.DropShadow">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_ElasticEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ElasticEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_ElasticEasingFunction <"Windows.UI.Composition.ElasticEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_ExponentialEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ExponentialEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_ExponentialEasingFunction <"Windows.UI.Composition.ExponentialEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_ExpressionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ExpressionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_ExpressionAnimation <"Windows.UI.Composition.ExpressionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_ImplicitAnimationCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ImplicitAnimationCollection_DEFINED
define RuntimeClass_Windows_UI_Composition_ImplicitAnimationCollection <"Windows.UI.Composition.ImplicitAnimationCollection">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_InitialValueExpressionCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_InitialValueExpressionCollection_DEFINED
define RuntimeClass_Windows_UI_Composition_InitialValueExpressionCollection <"Windows.UI.Composition.InitialValueExpressionCollection">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_InsetClip_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_InsetClip_DEFINED
define RuntimeClass_Windows_UI_Composition_InsetClip <"Windows.UI.Composition.InsetClip">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_KeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_KeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_KeyFrameAnimation <"Windows.UI.Composition.KeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_LayerVisual_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_LayerVisual_DEFINED
define RuntimeClass_Windows_UI_Composition_LayerVisual <"Windows.UI.Composition.LayerVisual">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_LinearEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_LinearEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_LinearEasingFunction <"Windows.UI.Composition.LinearEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_NaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_NaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_NaturalMotionAnimation <"Windows.UI.Composition.NaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_PathKeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_PathKeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_PathKeyFrameAnimation <"Windows.UI.Composition.PathKeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_PointLight_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_PointLight_DEFINED
define RuntimeClass_Windows_UI_Composition_PointLight <"Windows.UI.Composition.PointLight">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_PowerEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_PowerEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_PowerEasingFunction <"Windows.UI.Composition.PowerEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_QuaternionKeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_QuaternionKeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_QuaternionKeyFrameAnimation <"Windows.UI.Composition.QuaternionKeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_RectangleClip_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_RectangleClip_DEFINED
define RuntimeClass_Windows_UI_Composition_RectangleClip <"Windows.UI.Composition.RectangleClip">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef RUNTIMECLASS_Windows_UI_Composition_RedirectVisual_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_RedirectVisual_DEFINED
define RuntimeClass_Windows_UI_Composition_RedirectVisual <"Windows.UI.Composition.RedirectVisual">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_RenderingDeviceReplacedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_RenderingDeviceReplacedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Composition_RenderingDeviceReplacedEventArgs <"Windows.UI.Composition.RenderingDeviceReplacedEventArgs">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_ScalarKeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ScalarKeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_ScalarKeyFrameAnimation <"Windows.UI.Composition.ScalarKeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_ScalarNaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ScalarNaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_ScalarNaturalMotionAnimation <"Windows.UI.Composition.ScalarNaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef RUNTIMECLASS_Windows_UI_Composition_ShapeVisual_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_ShapeVisual_DEFINED
define RuntimeClass_Windows_UI_Composition_ShapeVisual <"Windows.UI.Composition.ShapeVisual">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xc0000
ifndef RUNTIMECLASS_Windows_UI_Composition_SineEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_SineEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_SineEasingFunction <"Windows.UI.Composition.SineEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_SpotLight_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_SpotLight_DEFINED
define RuntimeClass_Windows_UI_Composition_SpotLight <"Windows.UI.Composition.SpotLight">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_SpringScalarNaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_SpringScalarNaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_SpringScalarNaturalMotionAnimation <"Windows.UI.Composition.SpringScalarNaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_SpringVector2NaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_SpringVector2NaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_SpringVector2NaturalMotionAnimation <"Windows.UI.Composition.SpringVector2NaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_SpringVector3NaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_SpringVector3NaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_SpringVector3NaturalMotionAnimation <"Windows.UI.Composition.SpringVector3NaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_SpriteVisual_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_SpriteVisual_DEFINED
define RuntimeClass_Windows_UI_Composition_SpriteVisual <"Windows.UI.Composition.SpriteVisual">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_StepEasingFunction_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_StepEasingFunction_DEFINED
define RuntimeClass_Windows_UI_Composition_StepEasingFunction <"Windows.UI.Composition.StepEasingFunction">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_Vector2KeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_Vector2KeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_Vector2KeyFrameAnimation <"Windows.UI.Composition.Vector2KeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_Vector2NaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_Vector2NaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_Vector2NaturalMotionAnimation <"Windows.UI.Composition.Vector2NaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_Vector3KeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_Vector3KeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_Vector3KeyFrameAnimation <"Windows.UI.Composition.Vector3KeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef RUNTIMECLASS_Windows_UI_Composition_Vector3NaturalMotionAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_Vector3NaturalMotionAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_Vector3NaturalMotionAnimation <"Windows.UI.Composition.Vector3NaturalMotionAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_Vector4KeyFrameAnimation_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_Vector4KeyFrameAnimation_DEFINED
define RuntimeClass_Windows_UI_Composition_Vector4KeyFrameAnimation <"Windows.UI.Composition.Vector4KeyFrameAnimation">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_Visual_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_Visual_DEFINED
define RuntimeClass_Windows_UI_Composition_Visual <"Windows.UI.Composition.Visual">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef RUNTIMECLASS_Windows_UI_Composition_VisualCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_VisualCollection_DEFINED
define RuntimeClass_Windows_UI_Composition_VisualCollection <"Windows.UI.Composition.VisualCollection">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef RUNTIMECLASS_Windows_UI_Composition_VisualUnorderedCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Composition_VisualUnorderedCollection_DEFINED
define RuntimeClass_Windows_UI_Composition_VisualUnorderedCollection <"Windows.UI.Composition.VisualUnorderedCollection">
endif
endif

endif

endif

