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

ifndef __windows2Emedia2Espeechsynthesis_h__
define __windows2Emedia2Espeechsynthesis_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Media.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation, "12d40a27-ae8d-5fb0-8fed-00165d59c6ab")

.comdef __FIIterator_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation, "3c33bb52-bd98-5c8c-adee-ee8da0628efc")

.comdef __FIIterable_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation, "ee8d63ce-51ac-5984-891b-d232fa7f6453")

.comdef __FIVectorView_1_Windows__CMedia__CSpeechSynthesis__CVoiceInformation : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CSpeechSynthesis__CSpeechSynthesisStream_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CSpeechSynthesis__CSpeechSynthesisStream_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CSpeechSynthesis__CSpeechSynthesisStream, "c972b996-6165-50d4-af60-a8c3df51d092")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CSpeechSynthesis__CSpeechSynthesisStream : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CSpeechSynthesis__CSpeechSynthesisStream_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CSpeechSynthesis__CSpeechSynthesisStream_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CSpeechSynthesis__CSpeechSynthesisStream, "df9d48ad-9cea-560c-9edc-cb8852cb55e3")

.comdef __FIAsyncOperation_1_Windows__CMedia__CSpeechSynthesis__CSpeechSynthesisStream : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace SpeechSynthesis

.enum VoiceGender {
    VoiceGender_Male	= 0,
    VoiceGender_Female	= 1
    }

ifndef ____x_ABI_CWindows_CMedia_CSpeechSynthesis_CIVoiceInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CSpeechSynthesis_CIVoiceInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_SpeechSynthesis_IVoiceInformation <L"Windows.Media.SpeechSynthesis.IVoiceInformation">
DEFINE_IIDX(IVoiceInformation, "B127D6A4-1291-4604-AA9C-83134083352C")

.comdef IVoiceInformation : public IInspectable

    get_DisplayName	proc :ptr
    get_Id		proc :ptr
    get_Language	proc :ptr
    get_Description	proc :ptr
    get_Gender		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CSpeechSynthesis_CIInstalledVoicesStatic_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CSpeechSynthesis_CIInstalledVoicesStatic_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_SpeechSynthesis_IInstalledVoicesStatic <L"Windows.Media.SpeechSynthesis.IInstalledVoicesStatic">
DEFINE_IIDX(IInstalledVoicesStatic, "7D526ECC-7533-4C3F-85BE-888C2BAEEBDC")

.comdef IInstalledVoicesStatic : public IInspectable

    get_AllVoices	proc :ptr
    get_DefaultVoice	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CSpeechSynthesis_CISpeechSynthesisStream_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CSpeechSynthesis_CISpeechSynthesisStream_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_SpeechSynthesis_ISpeechSynthesisStream <L"Windows.Media.SpeechSynthesis.ISpeechSynthesisStream">
DEFINE_IIDX(ISpeechSynthesisStream, "83E46E93-244C-4622-BA0B-6229C4D0D65D")

.comdef ISpeechSynthesisStream : public IInspectable

    get_Markers		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CSpeechSynthesis_CISpeechSynthesizer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CSpeechSynthesis_CISpeechSynthesizer_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_SpeechSynthesis_ISpeechSynthesizer <L"Windows.Media.SpeechSynthesis.ISpeechSynthesizer">
DEFINE_IIDX(ISpeechSynthesizer, "CE9F7C76-97F4-4CED-AD68-D51C458E45C6")

.comdef ISpeechSynthesizer : public IInspectable

    SynthesizeTextToStreamAsync proc :HSTRING, :ptr
    SynthesizeSsmlToStreamAsync proc :HSTRING, :ptr
    put_Voice		proc :ptr
    get_Voice		proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_SpeechSynthesis_VoiceInformation_DEFINED
define RUNTIMECLASS_Windows_Media_SpeechSynthesis_VoiceInformation_DEFINED
define RuntimeClass_Windows_Media_SpeechSynthesis_VoiceInformation <L"Windows.Media.SpeechSynthesis.VoiceInformation">
endif
ifndef RUNTIMECLASS_Windows_Media_SpeechSynthesis_SpeechSynthesisStream_DEFINED
define RUNTIMECLASS_Windows_Media_SpeechSynthesis_SpeechSynthesisStream_DEFINED
define RuntimeClass_Windows_Media_SpeechSynthesis_SpeechSynthesisStream <L"Windows.Media.SpeechSynthesis.SpeechSynthesisStream">
endif
ifndef RUNTIMECLASS_Windows_Media_SpeechSynthesis_SpeechSynthesizer_DEFINED
define RUNTIMECLASS_Windows_Media_SpeechSynthesis_SpeechSynthesizer_DEFINED
define RuntimeClass_Windows_Media_SpeechSynthesis_SpeechSynthesizer <L"Windows.Media.SpeechSynthesis.SpeechSynthesizer">
endif

endif
