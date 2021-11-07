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

ifndef __windows2Emedia2Eeffects_h__
define __windows2Emedia2Eeffects_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Media.inc
include Windows.Media.Capture.inc
include Windows.Media.Render.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CMedia__CEffects__CAudioEffect_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CEffects__CAudioEffect_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CEffects__CAudioEffect, "673ce717-a3cf-5d68-a80b-5ed3e7b93fed")

.comdef __FIIterator_1_Windows__CMedia__CEffects__CAudioEffect : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CEffects__CAudioEffect_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CEffects__CAudioEffect_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CEffects__CAudioEffect, "07af9afd-25b8-579d-be7e-8acc03418d0b")

.comdef __FIIterable_1_Windows__CMedia__CEffects__CAudioEffect : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CEffects__CAudioEffect_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CEffects__CAudioEffect_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CEffects__CAudioEffect, "cdcbc9e7-53d8-5e66-9e45-31d5a23fd01d")

.comdef __FIVectorView_1_Windows__CMedia__CEffects__CAudioEffect : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CEffects__CAudioCaptureEffectsManager_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CEffects__CAudioCaptureEffectsManager_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CEffects__CAudioCaptureEffectsManager_IInspectable, "a1c5e803-a275-5bb1-9d44-2ac8ae9ffb89")

.comdef __FITypedEventHandler_2_Windows__CMedia__CEffects__CAudioCaptureEffectsManager_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CEffects__CAudioRenderEffectsManager_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CEffects__CAudioRenderEffectsManager_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CEffects__CAudioRenderEffectsManager_IInspectable, "4be29c7e-449c-576e-a7b8-3a40f2f01dc8")

.comdef __FITypedEventHandler_2_Windows__CMedia__CEffects__CAudioRenderEffectsManager_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Effects

.enum AudioEffectType {
    AudioEffectType_Other	= 0,
    AudioEffectType_AcousticEchoCancellation	= 1,
    AudioEffectType_NoiseSuppression	= 2,
    AudioEffectType_AutomaticGainControl	= 3,
    AudioEffectType_BeamForming = 4,
    AudioEffectType_ConstantToneRemoval = 5,
    AudioEffectType_Equalizer	= 6,
    AudioEffectType_LoudnessEqualizer	= 7,
    AudioEffectType_BassBoost	= 8,
    AudioEffectType_VirtualSurround	= 9,
    AudioEffectType_VirtualHeadphones	= 10,
    AudioEffectType_SpeakerFill = 11,
    AudioEffectType_RoomCorrection	= 12,
    AudioEffectType_BassManagement	= 13,
    AudioEffectType_EnvironmentalEffects	= 14,
    AudioEffectType_SpeakerProtection	= 15,
    AudioEffectType_SpeakerCompensation = 16,
    AudioEffectType_DynamicRangeCompression	= 17
    }

ifndef ____x_ABI_CWindows_CMedia_CEffects_CIAudioEffect_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CEffects_CIAudioEffect_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Effects_IAudioEffect <L"Windows.Media.Effects.IAudioEffect">
DEFINE_IIDX(IAudioEffect, "34AAFA51-9207-4055-BE93-6E5734A86AE4")

.comdef IAudioEffect : public IInspectable

    get_AudioEffectType proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CEffects_CIAudioEffectsManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CEffects_CIAudioEffectsManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Effects_IAudioEffectsManagerStatics <L"Windows.Media.Effects.IAudioEffectsManagerStatics">
DEFINE_IIDX(IAudioEffectsManagerStatics, "66406C04-86FA-47CC-A315-F489D8C3FE10")

.comdef IAudioEffectsManagerStatics : public IInspectable

    CreateAudioRenderEffectsManager proc :HSTRING, :Windows::Media::Render::AudioRenderCategory, :ptr
    CreateAudioRenderEffectsManagerWithMode proc :HSTRING, :Windows::Media::Render::AudioRenderCategory, :Windows::Media::AudioProcessing, :ptr
    CreateAudioCaptureEffectsManager proc :HSTRING, :Windows::Media::Capture::MediaCategory, :ptr
    CreateAudioCaptureEffectsManagerWithMode proc :HSTRING, :Windows::Media::Capture::MediaCategory, :Windows::Media::AudioProcessing, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CEffects_CIAudioRenderEffectsManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CEffects_CIAudioRenderEffectsManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Effects_IAudioRenderEffectsManager <L"Windows.Media.Effects.IAudioRenderEffectsManager">
DEFINE_IIDX(IAudioRenderEffectsManager, "4DC98966-8751-42B2-BFCB-39CA7864BD47")

.comdef IAudioRenderEffectsManager : public IInspectable

    add_AudioRenderEffectsChanged proc :ptr, :ptr
    remove_AudioRenderEffectsChanged proc :EventRegistrationToken
    GetAudioRenderEffects proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CEffects_CIAudioCaptureEffectsManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CEffects_CIAudioCaptureEffectsManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Effects_IAudioCaptureEffectsManager <L"Windows.Media.Effects.IAudioCaptureEffectsManager">
DEFINE_IIDX(IAudioCaptureEffectsManager, "8F85C271-038D-4393-8298-540110608EEF")

.comdef IAudioCaptureEffectsManager : public IInspectable

    add_AudioCaptureEffectsChanged proc :ptr, :ptr
    remove_AudioCaptureEffectsChanged proc :EventRegistrationToken
    GetAudioCaptureEffects proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Effects_AudioEffect_DEFINED
define RUNTIMECLASS_Windows_Media_Effects_AudioEffect_DEFINED
define RuntimeClass_Windows_Media_Effects_AudioEffect <L"Windows.Media.Effects.AudioEffect">
endif
ifndef RUNTIMECLASS_Windows_Media_Effects_AudioRenderEffectsManager_DEFINED
define RUNTIMECLASS_Windows_Media_Effects_AudioRenderEffectsManager_DEFINED
define RuntimeClass_Windows_Media_Effects_AudioRenderEffectsManager <L"Windows.Media.Effects.AudioRenderEffectsManager">
endif
ifndef RUNTIMECLASS_Windows_Media_Effects_AudioCaptureEffectsManager_DEFINED
define RUNTIMECLASS_Windows_Media_Effects_AudioCaptureEffectsManager_DEFINED
define RuntimeClass_Windows_Media_Effects_AudioCaptureEffectsManager <L"Windows.Media.Effects.AudioCaptureEffectsManager">
endif
ifndef RUNTIMECLASS_Windows_Media_Effects_AudioEffectsManager_DEFINED
define RUNTIMECLASS_Windows_Media_Effects_AudioEffectsManager_DEFINED
define RuntimeClass_Windows_Media_Effects_AudioEffectsManager <L"Windows.Media.Effects.AudioEffectsManager">
endif

endif
