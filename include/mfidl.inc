ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __mfidl_h__
__mfidl_h__ equ <>

ifndef __IMFMediaSession_FWD_DEFINED__
__IMFMediaSession_FWD_DEFINED__ equ 1
endif
ifndef __IMFSourceResolver_FWD_DEFINED__
__IMFSourceResolver_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaSource_FWD_DEFINED__
__IMFMediaSource_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaSourceEx_FWD_DEFINED__
__IMFMediaSourceEx_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaStream_FWD_DEFINED__
__IMFMediaStream_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaSink_FWD_DEFINED__
__IMFMediaSink_FWD_DEFINED__ equ 1
endif
ifndef __IMFStreamSink_FWD_DEFINED__
__IMFStreamSink_FWD_DEFINED__ equ 1
endif
ifndef __IMFVideoSampleAllocator_FWD_DEFINED__
__IMFVideoSampleAllocator_FWD_DEFINED__ equ 1
endif
ifndef __IMFVideoSampleAllocatorNotify_FWD_DEFINED__
__IMFVideoSampleAllocatorNotify_FWD_DEFINED__ equ 1
endif
ifndef __IMFVideoSampleAllocatorCallback_FWD_DEFINED__
__IMFVideoSampleAllocatorCallback_FWD_DEFINED__ equ 1
endif
ifndef __IMFVideoSampleAllocatorEx_FWD_DEFINED__
__IMFVideoSampleAllocatorEx_FWD_DEFINED__ equ 1
endif
ifndef __IMFDXGIDeviceManagerSource_FWD_DEFINED__
__IMFDXGIDeviceManagerSource_FWD_DEFINED__ equ 1
endif
ifndef __IMFVideoProcessorControl_FWD_DEFINED__
__IMFVideoProcessorControl_FWD_DEFINED__ equ 1
endif
ifndef __IMFTopology_FWD_DEFINED__
__IMFTopology_FWD_DEFINED__ equ 1
endif
ifndef __IMFTopologyNode_FWD_DEFINED__
__IMFTopologyNode_FWD_DEFINED__ equ 1
endif
ifndef __IMFGetService_FWD_DEFINED__
__IMFGetService_FWD_DEFINED__ equ 1
endif
ifndef __IMFClock_FWD_DEFINED__
__IMFClock_FWD_DEFINED__ equ 1
endif
ifndef __IMFPresentationClock_FWD_DEFINED__
__IMFPresentationClock_FWD_DEFINED__ equ 1
endif
ifndef __IMFPresentationTimeSource_FWD_DEFINED__
__IMFPresentationTimeSource_FWD_DEFINED__ equ 1
endif
ifndef __IMFClockStateSink_FWD_DEFINED__
__IMFClockStateSink_FWD_DEFINED__ equ 1
endif
ifndef __IMFPresentationDescriptor_FWD_DEFINED__
__IMFPresentationDescriptor_FWD_DEFINED__ equ 1
endif
ifndef __IMFStreamDescriptor_FWD_DEFINED__
__IMFStreamDescriptor_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaTypeHandler_FWD_DEFINED__
__IMFMediaTypeHandler_FWD_DEFINED__ equ 1
endif
ifndef __IMFTimer_FWD_DEFINED__
__IMFTimer_FWD_DEFINED__ equ 1
endif
ifndef __IMFShutdown_FWD_DEFINED__
__IMFShutdown_FWD_DEFINED__ equ 1
endif
ifndef __IMFTopoLoader_FWD_DEFINED__
__IMFTopoLoader_FWD_DEFINED__ equ 1
endif
ifndef __IMFContentProtectionManager_FWD_DEFINED__
__IMFContentProtectionManager_FWD_DEFINED__ equ 1
endif
ifndef __IMFContentEnabler_FWD_DEFINED__
__IMFContentEnabler_FWD_DEFINED__ equ 1
endif
ifndef __IMFMetadata_FWD_DEFINED__
__IMFMetadata_FWD_DEFINED__ equ 1
endif
ifndef __IMFMetadataProvider_FWD_DEFINED__
__IMFMetadataProvider_FWD_DEFINED__ equ 1
endif
ifndef __IMFRateSupport_FWD_DEFINED__
__IMFRateSupport_FWD_DEFINED__ equ 1
endif
ifndef __IMFRateControl_FWD_DEFINED__
__IMFRateControl_FWD_DEFINED__ equ 1
endif
ifndef __IMFTimecodeTranslate_FWD_DEFINED__
__IMFTimecodeTranslate_FWD_DEFINED__ equ 1
endif
ifndef __IMFSeekInfo_FWD_DEFINED__
__IMFSeekInfo_FWD_DEFINED__ equ 1
endif
ifndef __IMFSimpleAudioVolume_FWD_DEFINED__
__IMFSimpleAudioVolume_FWD_DEFINED__ equ 1
endif
ifndef __IMFAudioStreamVolume_FWD_DEFINED__
__IMFAudioStreamVolume_FWD_DEFINED__ equ 1
endif
ifndef __IMFAudioPolicy_FWD_DEFINED__
__IMFAudioPolicy_FWD_DEFINED__ equ 1
endif
ifndef __IMFSampleGrabberSinkCallback_FWD_DEFINED__
__IMFSampleGrabberSinkCallback_FWD_DEFINED__ equ 1
endif
ifndef __IMFSampleGrabberSinkCallback2_FWD_DEFINED__
__IMFSampleGrabberSinkCallback2_FWD_DEFINED__ equ 1
endif
ifndef __IMFWorkQueueServices_FWD_DEFINED__
__IMFWorkQueueServices_FWD_DEFINED__ equ 1
endif
ifndef __IMFWorkQueueServicesEx_FWD_DEFINED__
__IMFWorkQueueServicesEx_FWD_DEFINED__ equ 1
endif
ifndef __IMFQualityManager_FWD_DEFINED__
__IMFQualityManager_FWD_DEFINED__ equ 1
endif
ifndef __IMFQualityAdvise_FWD_DEFINED__
__IMFQualityAdvise_FWD_DEFINED__ equ 1
endif
ifndef __IMFQualityAdvise2_FWD_DEFINED__
__IMFQualityAdvise2_FWD_DEFINED__ equ 1
endif
ifndef __IMFQualityAdviseLimits_FWD_DEFINED__
__IMFQualityAdviseLimits_FWD_DEFINED__ equ 1
endif
ifndef __IMFRealTimeClient_FWD_DEFINED__
__IMFRealTimeClient_FWD_DEFINED__ equ 1
endif
ifndef __IMFRealTimeClientEx_FWD_DEFINED__
__IMFRealTimeClientEx_FWD_DEFINED__ equ 1
endif
ifndef __IMFSequencerSource_FWD_DEFINED__
__IMFSequencerSource_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaSourceTopologyProvider_FWD_DEFINED__
__IMFMediaSourceTopologyProvider_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaSourcePresentationProvider_FWD_DEFINED__
__IMFMediaSourcePresentationProvider_FWD_DEFINED__ equ 1
endif
ifndef __IMFTopologyNodeAttributeEditor_FWD_DEFINED__
__IMFTopologyNodeAttributeEditor_FWD_DEFINED__ equ 1
endif
ifndef __IMFByteStreamBuffering_FWD_DEFINED__
__IMFByteStreamBuffering_FWD_DEFINED__ equ 1
endif
ifndef __IMFByteStreamCacheControl_FWD_DEFINED__
__IMFByteStreamCacheControl_FWD_DEFINED__ equ 1
endif
ifndef __IMFByteStreamTimeSeek_FWD_DEFINED__
__IMFByteStreamTimeSeek_FWD_DEFINED__ equ 1
endif
ifndef __IMFByteStreamCacheControl2_FWD_DEFINED__
__IMFByteStreamCacheControl2_FWD_DEFINED__ equ 1
endif
ifndef __IMFNetCredential_FWD_DEFINED__
__IMFNetCredential_FWD_DEFINED__ equ 1
endif
ifndef __IMFNetCredentialManager_FWD_DEFINED__
__IMFNetCredentialManager_FWD_DEFINED__ equ 1
endif
ifndef __IMFNetCredentialCache_FWD_DEFINED__
__IMFNetCredentialCache_FWD_DEFINED__ equ 1
endif
ifndef __IMFSSLCertificateManager_FWD_DEFINED__
__IMFSSLCertificateManager_FWD_DEFINED__ equ 1
endif
ifndef __IMFNetResourceFilter_FWD_DEFINED__
__IMFNetResourceFilter_FWD_DEFINED__ equ 1
endif
ifndef __IMFSourceOpenMonitor_FWD_DEFINED__
__IMFSourceOpenMonitor_FWD_DEFINED__ equ 1
endif
ifndef __IMFNetProxyLocator_FWD_DEFINED__
__IMFNetProxyLocator_FWD_DEFINED__ equ 1
endif
ifndef __IMFNetProxyLocatorFactory_FWD_DEFINED__
__IMFNetProxyLocatorFactory_FWD_DEFINED__ equ 1
endif
ifndef __IMFSaveJob_FWD_DEFINED__
__IMFSaveJob_FWD_DEFINED__ equ 1
endif
ifndef __IMFNetSchemeHandlerConfig_FWD_DEFINED__
__IMFNetSchemeHandlerConfig_FWD_DEFINED__ equ 1
endif
ifndef __IMFSchemeHandler_FWD_DEFINED__
__IMFSchemeHandler_FWD_DEFINED__ equ 1
endif
ifndef __IMFByteStreamHandler_FWD_DEFINED__
__IMFByteStreamHandler_FWD_DEFINED__ equ 1
endif
ifndef __IMFTrustedInput_FWD_DEFINED__
__IMFTrustedInput_FWD_DEFINED__ equ 1
endif
ifndef __IMFInputTrustAuthority_FWD_DEFINED__
__IMFInputTrustAuthority_FWD_DEFINED__ equ 1
endif
ifndef __IMFTrustedOutput_FWD_DEFINED__
__IMFTrustedOutput_FWD_DEFINED__ equ 1
endif
ifndef __IMFOutputTrustAuthority_FWD_DEFINED__
__IMFOutputTrustAuthority_FWD_DEFINED__ equ 1
endif
ifndef __IMFOutputPolicy_FWD_DEFINED__
__IMFOutputPolicy_FWD_DEFINED__ equ 1
endif
ifndef __IMFOutputSchema_FWD_DEFINED__
__IMFOutputSchema_FWD_DEFINED__ equ 1
endif
ifndef __IMFSecureChannel_FWD_DEFINED__
__IMFSecureChannel_FWD_DEFINED__ equ 1
endif
ifndef __IMFSampleProtection_FWD_DEFINED__
__IMFSampleProtection_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaSinkPreroll_FWD_DEFINED__
__IMFMediaSinkPreroll_FWD_DEFINED__ equ 1
endif
ifndef __IMFFinalizableMediaSink_FWD_DEFINED__
__IMFFinalizableMediaSink_FWD_DEFINED__ equ 1
endif
ifndef __IMFStreamingSinkConfig_FWD_DEFINED__
__IMFStreamingSinkConfig_FWD_DEFINED__ equ 1
endif
ifndef __IMFRemoteProxy_FWD_DEFINED__
__IMFRemoteProxy_FWD_DEFINED__ equ 1
endif
ifndef __IMFObjectReferenceStream_FWD_DEFINED__
__IMFObjectReferenceStream_FWD_DEFINED__ equ 1
endif
ifndef __IMFPMPHost_FWD_DEFINED__
__IMFPMPHost_FWD_DEFINED__ equ 1
endif
ifndef __IMFPMPClient_FWD_DEFINED__
__IMFPMPClient_FWD_DEFINED__ equ 1
endif
ifndef __IMFPMPServer_FWD_DEFINED__
__IMFPMPServer_FWD_DEFINED__ equ 1
endif
ifndef __IMFRemoteDesktopPlugin_FWD_DEFINED__
__IMFRemoteDesktopPlugin_FWD_DEFINED__ equ 1
endif
ifndef __IMFSAMIStyle_FWD_DEFINED__
__IMFSAMIStyle_FWD_DEFINED__ equ 1
endif
ifndef __IMFTranscodeProfile_FWD_DEFINED__
__IMFTranscodeProfile_FWD_DEFINED__ equ 1
endif
ifndef __IMFTranscodeSinkInfoProvider_FWD_DEFINED__
__IMFTranscodeSinkInfoProvider_FWD_DEFINED__ equ 1
endif
ifndef __IMFFieldOfUseMFTUnlock_FWD_DEFINED__
__IMFFieldOfUseMFTUnlock_FWD_DEFINED__ equ 1
endif
ifndef __IMFLocalMFTRegistration_FWD_DEFINED__
__IMFLocalMFTRegistration_FWD_DEFINED__ equ 1
endif
ifndef __IMFPMPHostApp_FWD_DEFINED__
__IMFPMPHostApp_FWD_DEFINED__ equ 1
endif
ifndef __IMFPMPClientApp_FWD_DEFINED__
__IMFPMPClientApp_FWD_DEFINED__ equ 1
endif
ifndef __IMFMediaStreamSourceSampleRequest_FWD_DEFINED__
__IMFMediaStreamSourceSampleRequest_FWD_DEFINED__ equ 1
endif
ifndef __IMFTrackedSample_FWD_DEFINED__
__IMFTrackedSample_FWD_DEFINED__ equ 1
endif
ifndef __IMFProtectedEnvironmentAccess_FWD_DEFINED__
__IMFProtectedEnvironmentAccess_FWD_DEFINED__ equ 1
endif
ifndef __IMFSignedLibrary_FWD_DEFINED__
__IMFSignedLibrary_FWD_DEFINED__ equ 1
endif
ifndef __IMFSystemId_FWD_DEFINED__
__IMFSystemId_FWD_DEFINED__ equ 1
endif

include mfobjects.inc
include mftransform.inc

include winapifamily.inc
include windef.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MFSESSION_SETTOPOLOGY_FLAGS {
    MFSESSION_SETTOPOLOGY_IMMEDIATE = 0x1,
    MFSESSION_SETTOPOLOGY_NORESOLUTION	= 0x2,
    MFSESSION_SETTOPOLOGY_CLEAR_CURRENT = 0x4
    }

.enum MFSESSION_GETFULLTOPOLOGY_FLAGS {
    MFSESSION_GETFULLTOPOLOGY_CURRENT	= 0x1
    }

.enum MFPMPSESSION_CREATION_FLAGS {
    MFPMPSESSION_UNPROTECTED_PROCESS	= 0x1
    }

TOPOID typedef qword

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
DEFINE_GUID( MF_WVC1_PROG_SINGLE_SLICE_CONTENT, 0x67EC2559, 0x0F2F, 0x4420, 0xA4, 0xDD, 0x2F, 0x8E, 0xE7, 0xA5, 0x73, 0x8B);
DEFINE_GUID( MF_PROGRESSIVE_CODING_CONTENT, 0x8F020EEA, 0x1508, 0x471F, 0x9D, 0xA6, 0x50, 0x7D, 0x7C, 0xFA, 0x40, 0xDB);
DEFINE_GUID( MF_NALU_LENGTH_SET, 0xA7911D53, 0x12A4, 0x4965, 0xAE, 0x70, 0x6E, 0xAD, 0xD6, 0xFF, 0x05, 0x51);
DEFINE_GUID( MF_NALU_LENGTH_INFORMATION, 0x19124E7C, 0xAD4B, 0x465F, 0xBB, 0x18, 0x20, 0x18, 0x62, 0x87, 0xB6, 0xAF);
DEFINE_GUID( MF_USER_DATA_PAYLOAD, 0xd1d4985d, 0xdc92, 0x457a, 0xb3, 0xa0, 0x65, 0x1a, 0x33, 0xa3, 0x10, 0x47);
DEFINE_GUID( MF_MPEG4SINK_SPSPPS_PASSTHROUGH, 0x5601a134, 0x2005, 0x4ad2, 0xb3, 0x7d, 0x22, 0xa6, 0xc5, 0x54, 0xde, 0xb2);
DEFINE_GUID( MF_MPEG4SINK_MOOV_BEFORE_MDAT, 0xf672e3ac, 0xe1e6, 0x4f10, 0xb5, 0xec, 0x5f, 0x3b, 0x30, 0x82, 0x88, 0x16);
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFMediaSession_INTERFACE_DEFINED__
__IMFMediaSession_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaSession, "90377834-21D0-4dee-8214-BA2E3E6C1127")

.comdef IMFMediaSession : public IMFMediaEventGenerator

    SetTopology		proc :DWORD, :ptr
    ClearTopologies	proc
    Start		proc :ptr, :ptr
    _Pause		proc
    Stop		proc
    Close		proc
    Shutdown		proc
    GetClock		proc :ptr
    GetSessionCapabilities proc :ptr
    GetFullTopology	proc :DWORD, :TOPOID, :ptr
    .ends

endif

DEFINE_GUID( MF_SESSION_TOPOLOADER, 0x1e83d482, 0x1f1c, 0x4571, 0x84, 0x5, 0x88, 0xf4, 0xb2, 0x18, 0x1f, 0x71);
DEFINE_GUID( MF_SESSION_GLOBAL_TIME, 0x1e83d482, 0x1f1c, 0x4571, 0x84, 0x5, 0x88, 0xf4, 0xb2, 0x18, 0x1f, 0x72);
DEFINE_GUID( MF_SESSION_QUALITY_MANAGER, 0x1e83d482, 0x1f1c, 0x4571, 0x84, 0x5, 0x88, 0xf4, 0xb2, 0x18, 0x1f, 0x73);
DEFINE_GUID( MF_SESSION_CONTENT_PROTECTION_MANAGER, 0x1e83d482, 0x1f1c, 0x4571, 0x84, 0x5, 0x88, 0xf4, 0xb2, 0x18, 0x1f, 0x74);
DEFINE_GUID( MF_SESSION_SERVER_CONTEXT, 0xafe5b291, 0x50fa, 0x46e8, 0xb9, 0xbe, 0xc, 0xc, 0x3c, 0xe4, 0xb3, 0xa5);
DEFINE_GUID( MF_SESSION_REMOTE_SOURCE_MODE, 0xf4033ef4, 0x9bb3, 0x4378, 0x94, 0x1f, 0x85, 0xa0, 0x85, 0x6b, 0xc2, 0x44);
DEFINE_GUID( MF_SESSION_APPROX_EVENT_OCCURRENCE_TIME, 0x190e852f, 0x6238, 0x42d1, 0xb5, 0xaf, 0x69, 0xea, 0x33, 0x8e, 0xf8, 0x50);
DEFINE_GUID( MF_PMP_SERVER_CONTEXT, 0x2f00c910, 0xd2cf, 0x4278, 0x8b, 0x6a, 0xd0, 0x77, 0xfa, 0xc3, 0xa2, 0x5f);
;STDAPI
MFCreateMediaSession proto __cdecl \
	pConfiguration: ptr IMFAttributes,
	ppMediaSession: ptr ptr IMFMediaSession

;STDAPI
MFCreatePMPMediaSession proto __cdecl \
       dwCreationFlags: DWORD,
	pConfiguration: ptr IMFAttributes,
	ppMediaSession: ptr ptr IMFMediaSession,
     ppEnablerActivate: ptr IMFActivate

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MF_OBJECT_TYPE {
    MF_OBJECT_MEDIASOURCE	= 0,
    MF_OBJECT_BYTESTREAM	= ( MF_OBJECT_MEDIASOURCE + 1 ) ,
    MF_OBJECT_INVALID	= ( MF_OBJECT_BYTESTREAM + 1 )
    }


.enum _MIDL___MIDL_itf_mfidl_0000_0001_0001 {
    MF_RESOLUTION_MEDIASOURCE	= 0x1,
    MF_RESOLUTION_BYTESTREAM	= 0x2,
    MF_RESOLUTION_CONTENT_DOES_NOT_HAVE_TO_MATCH_EXTENSION_OR_MIME_TYPE = 0x10,
    MF_RESOLUTION_KEEP_BYTE_STREAM_ALIVE_ON_FAIL	= 0x20,
    MF_RESOLUTION_DISABLE_LOCAL_PLUGINS = 0x40,
    MF_RESOLUTION_PLUGIN_CONTROL_POLICY_APPROVED_ONLY	= 0x80,
    MF_RESOLUTION_PLUGIN_CONTROL_POLICY_WEB_ONLY	= 0x100,
    MF_RESOLUTION_READ	= 0x10000,
    MF_RESOLUTION_WRITE = 0x20000
    }
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MF_CONNECT_METHOD {
    MF_CONNECT_DIRECT	= 0,
    MF_CONNECT_ALLOW_CONVERTER	= 0x1,
    MF_CONNECT_ALLOW_DECODER	= 0x3,
    MF_CONNECT_RESOLVE_INDEPENDENT_OUTPUTTYPES	= 0x4,
    MF_CONNECT_AS_OPTIONAL	= 0x10000,
    MF_CONNECT_AS_OPTIONAL_BRANCH	= 0x20000
    }

.enum MF_TOPOLOGY_RESOLUTION_STATUS_FLAGS {
    MF_TOPOLOGY_RESOLUTION_SUCCEEDED	= 0,
    MF_OPTIONAL_NODE_REJECTED_MEDIA_TYPE	= 0x1,
    MF_OPTIONAL_NODE_REJECTED_PROTECTED_PROCESS = 0x2
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __IMFSourceResolver_INTERFACE_DEFINED__
__IMFSourceResolver_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSourceResolver, "FBE5A32D-A497-4b61-BB85-97B1A848A6E3")

.comdef IMFSourceResolver : public IUnknown

    CreateObjectFromURL proc :LPCWSTR, :DWORD, :ptr, :ptr, :ptr
    CreateObjectFromByteStream proc :ptr, :LPCWSTR, :DWORD, :ptr, :ptr, :ptr
    BeginCreateObjectFromURL proc :LPCWSTR, :DWORD, :ptr, :ptr, :ptr, :ptr
    EndCreateObjectFromURL proc :ptr, :ptr, :ptr
    BeginCreateObjectFromByteStream proc :ptr, :LPCWSTR, :DWORD, :ptr, :ptr, :ptr, :ptr
    EndCreateObjectFromByteStream proc :ptr, :ptr, :ptr
    CancelObjectCreation proc :ptr
    .ends


IMFSourceResolver_RemoteBeginCreateObjectFromURL_Proxy proto __cdecl :ptr, :DWORD, :ptr, :ptr

IMFSourceResolver_RemoteBeginCreateObjectFromURL_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFSourceResolver_RemoteEndCreateObjectFromURL_Proxy proto __cdecl :ptr, :ptr, :ptr, :ptr

IMFSourceResolver_RemoteEndCreateObjectFromURL_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFSourceResolver_RemoteBeginCreateObjectFromByteStream_Proxy proto __cdecl :ptr, :ptr, :ptr, :DWORD, :ptr, :ptr

IMFSourceResolver_RemoteBeginCreateObjectFromByteStream_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFSourceResolver_RemoteEndCreateObjectFromByteStream_Proxy proto __cdecl :ptr, :ptr, :ptr, :ptr

IMFSourceResolver_RemoteEndCreateObjectFromByteStream_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

;STDAPI
MFCreateSourceResolver proto __cdecl \
     ppISourceResolver: ptr IMFSourceResolver

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
;STDAPI
CreatePropertyStore proto __cdecl \
	       ppStore: ptr IPropertyStore

;STDAPI
MFGetSupportedSchemes proto __cdecl \
   pPropVarSchemeArray: ptr PROPVARIANT

;STDAPI
MFGetSupportedMimeTypes proto __cdecl \
 pPropVarMimeTypeArray: ptr PROPVARIANT

MFPKEY_SourceOpenMonitor equ <{ { 0x074d4637, 0xb5ae, 0x465d, 0xaf, 0x17, 0x1a, 0x53, 0x8d, 0x28, 0x59, 0xdd}, 0x02 }>
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MFPKEY_ASFMediaSource_ApproxSeek equ <{ { 0xb4cd270f, 0x244d, 0x4969, 0xbb, 0x92, 0x3f, 0x0f, 0xb8, 0x31, 0x6f, 0x10}, 0x01 }>
endif

if (WINVER GE _WIN32_WINNT_WIN7)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MFPKEY_ASFMediaSource_IterativeSeekIfNoIndex			equ <{ { 0x170b65dc, 0x4a4e, 0x407a, 0xac, 0x22, 0x57, 0x7f, 0x50, 0xe4, 0xa3, 0x7c }, 0x01 }>
MFPKEY_ASFMediaSource_IterativeSeek_Max_Count			equ <{ { 0x170b65dc, 0x4a4e, 0x407a, 0xac, 0x22, 0x57, 0x7f, 0x50, 0xe4, 0xa3, 0x7c }, 0x02 }>
MFPKEY_ASFMediaSource_IterativeSeek_Tolerance_In_MilliSecond	equ <{ { 0x170b65dc, 0x4a4e, 0x407a, 0xac, 0x22, 0x57, 0x7f, 0x50, 0xe4, 0xa3, 0x7c }, 0x03 }>
MFPKEY_Content_DLNA_Profile_ID					equ <{ { 0xcfa31b45, 0x525d, 0x4998, 0xbb, 0x44, 0x3f, 0x7d, 0x81, 0x54, 0x2f, 0xa4 }, 0x01 }>
MFPKEY_MediaSource_DisableReadAhead				equ <{ { 0x26366c14, 0xc5bf, 0x4c76, 0x88, 0x7b, 0x9f, 0x17, 0x54, 0xdb, 0x5f, 0x09 }, 0x01 }>
MFPKEY_SBESourceMode						equ <{ { 0x3fae10bb, 0xf859, 0x4192, 0xb5, 0x62, 0x18, 0x68, 0xd3, 0xda, 0x3a, 0x02 }, 0x01 }>
endif
endif

if (WINVER GE _WIN32_WINNT_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MFPKEY_PMP_Creation_Callback				equ <{ { 0x28bb4de2, 0x26a2, 0x4870, 0xb7, 0x20, 0xd2, 0x6b, 0xbe, 0xb1, 0x49, 0x42 }, 0x01 }>
MFPKEY_HTTP_ByteStream_Enable_Urlmon			equ <{ { 0xeda8afdf, 0xc171, 0x417f, 0x8d, 0x17, 0x2e, 0x09, 0x18, 0x30, 0x32, 0x92 }, 0x01 }>
MFPKEY_HTTP_ByteStream_Urlmon_Bind_Flags		equ <{ { 0xeda8afdf, 0xc171, 0x417f, 0x8d, 0x17, 0x2e, 0x09, 0x18, 0x30, 0x32, 0x92 }, 0x02 }>
MFPKEY_HTTP_ByteStream_Urlmon_Security_Id		equ <{ { 0xeda8afdf, 0xc171, 0x417f, 0x8d, 0x17, 0x2e, 0x09, 0x18, 0x30, 0x32, 0x92 }, 0x03 }>
MFPKEY_HTTP_ByteStream_Urlmon_Window			equ <{ { 0xeda8afdf, 0xc171, 0x417f, 0x8d, 0x17, 0x2e, 0x09, 0x18, 0x30, 0x32, 0x92 }, 0x04 }>
MFPKEY_HTTP_ByteStream_Urlmon_Callback_QueryService	equ <{ { 0xeda8afdf, 0xc171, 0x417f, 0x8d, 0x17, 0x2e, 0x09, 0x18, 0x30, 0x32, 0x92 }, 0x05 }>
MFPKEY_MediaProtectionSystemId				equ <{ { 0x636b271d, 0xddc7, 0x49e9, 0xa6, 0xc6, 0x47, 0x38, 0x59, 0x62, 0xe5, 0xbd }, 0x01 }>
MFPKEY_MediaProtectionSystemContext			equ <{ { 0x636b271d, 0xddc7, 0x49e9, 0xa6, 0xc6, 0x47, 0x38, 0x59, 0x62, 0xe5, 0xbd }, 0x02 }>
MFPKEY_MediaProtectionSystemIdMapping			equ <{ { 0x636b271d, 0xddc7, 0x49e9, 0xa6, 0xc6, 0x47, 0x38, 0x59, 0x62, 0xe5, 0xbd }, 0x03 }>
MFPKEY_MediaProtectionContainerGuid			equ <{ { 0x42af3d7c, 0x00cf, 0x4a0f, 0x81, 0xf0, 0xad, 0xf5, 0x24, 0xa5, 0xa5, 0xb5 }, 0x01 }>
MFPKEY_MediaProtectionSystemContextsPerTrack		equ <{ { 0x4454b092, 0xd3da, 0x49b0, 0x84, 0x52, 0x68, 0x50, 0xc7, 0xdb, 0x76, 0x4d }, 0x03 }>
endif

MFPKEY_HTTP_ByteStream_Download_Mode equ <{ { 0x817f11b7, 0xa982, 0x46ec, 0xa4, 0x49, 0xef, 0x58, 0xae, 0xd5, 0x3c, 0xa8 }, 0x01 }>
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MFMEDIASOURCE_CHARACTERISTICS {
    MFMEDIASOURCE_IS_LIVE	= 0x1,
    MFMEDIASOURCE_CAN_SEEK	= 0x2,
    MFMEDIASOURCE_CAN_PAUSE = 0x4,
    MFMEDIASOURCE_HAS_SLOW_SEEK = 0x8,
    MFMEDIASOURCE_HAS_MULTIPLE_PRESENTATIONS	= 0x10,
    MFMEDIASOURCE_CAN_SKIPFORWARD	= 0x20,
    MFMEDIASOURCE_CAN_SKIPBACKWARD	= 0x40,
    MFMEDIASOURCE_DOES_NOT_USE_NETWORK	= 0x80
    }

if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID( MF_TIME_FORMAT_ENTRY_RELATIVE, 0x4399f178, 0x46d3, 0x4504, 0xaf, 0xda, 0x20, 0xd3, 0x2e, 0x9b, 0xa3, 0x60 );
endif

ifndef __IMFMediaSource_INTERFACE_DEFINED__
__IMFMediaSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaSource, "279a808d-aec7-40c8-9c6b-a6b492c78a66")

.comdef IMFMediaSource : public IMFMediaEventGenerator

    GetCharacteristics	proc :ptr
    CreatePresentationDescriptor proc :ptr
    Start		proc :ptr, :ptr, :ptr
    Stop		proc
    _Pause		proc
    Shutdown		proc
    .ends

IMFMediaSource_RemoteCreatePresentationDescriptor_Proxy proto __cdecl :ptr, :ptr, :ptr, :ptr

IMFMediaSource_RemoteCreatePresentationDescriptor_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif
endif

if (WINVER GE _WIN32_WINNT_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFMediaSourceEx_INTERFACE_DEFINED__
__IMFMediaSourceEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaSourceEx, "3C9B2EB9-86D5-4514-A394-F56664F9F0D8")

.comdef IMFMediaSourceEx : public IMFMediaSource

    GetSourceAttributes proc :ptr
    GetStreamAttributes proc :DWORD, :ptr
    SetD3DManager	proc :ptr
    .ends

endif

DEFINE_GUID( MF_SOURCE_STREAM_SUPPORTS_HW_CONNECTION, 0xa38253aa, 0x6314, 0x42fd, 0xa3, 0xce, 0xbb, 0x27, 0xb6, 0x85, 0x99, 0x46);
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFMediaStream_INTERFACE_DEFINED__
__IMFMediaStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaStream, "D182108F-4EC6-443f-AA42-A71106EC825F")

.comdef IMFMediaStream : public IMFMediaEventGenerator

    GetMediaSource	proc :ptr
    GetStreamDescriptor proc :ptr
    RequestSample	proc :ptr
    .ends

IMFMediaStream_RemoteRequestSample_Proxy proto __cdecl :ptr

IMFMediaStream_RemoteRequestSample_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_GUID( MF_STREAM_SINK_SUPPORTS_HW_CONNECTION, 0x9b465cbf, 0x597, 0x4f9e, 0x9f, 0x3c, 0xb9, 0x7e, 0xee, 0xf9, 0x3, 0x59);
DEFINE_GUID( MF_STREAM_SINK_SUPPORTS_ROTATION, 0xb3e96280, 0xbd05, 0x41a5, 0x97, 0xad, 0x8a, 0x7f, 0xee, 0x24, 0xb9, 0x12);
endif
MEDIASINK_FIXED_STREAMS equ 0x00000001
MEDIASINK_CANNOT_MATCH_CLOCK equ 0x00000002
MEDIASINK_RATELESS	equ 0x00000004
MEDIASINK_CLOCK_REQUIRED equ 0x00000008
MEDIASINK_CAN_PREROLL	equ 0x00000010
MEDIASINK_REQUIRE_REFERENCE_MEDIATYPE equ 0x00000020

ifndef __IMFMediaSink_INTERFACE_DEFINED__
__IMFMediaSink_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaSink, "6ef2a660-47c0-4666-b13d-cbb717f2fa2c")

.comdef IMFMediaSink : public IUnknown

    GetCharacteristics	proc :ptr
    AddStreamSink	proc :DWORD, :ptr, :ptr
    RemoveStreamSink	proc :DWORD
    GetStreamSinkCount	proc :ptr
    GetStreamSinkByIndex proc :DWORD, :ptr
    GetStreamSinkById	proc :DWORD, :ptr
    SetPresentationClock proc :ptr
    GetPresentationClock proc :ptr
    Shutdown		proc
    .ends

endif

.enum MFSTREAMSINK_MARKER_TYPE {
    MFSTREAMSINK_MARKER_DEFAULT = 0,
    MFSTREAMSINK_MARKER_ENDOFSEGMENT	= ( MFSTREAMSINK_MARKER_DEFAULT + 1 ) ,
    MFSTREAMSINK_MARKER_TICK	= ( MFSTREAMSINK_MARKER_ENDOFSEGMENT + 1 ) ,
    MFSTREAMSINK_MARKER_EVENT	= ( MFSTREAMSINK_MARKER_TICK + 1 )
    }

ifndef __IMFStreamSink_INTERFACE_DEFINED__
__IMFStreamSink_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFStreamSink, "0A97B3CF-8E7C-4a3d-8F8C-0C843DC247FB")

.comdef IMFStreamSink : public IMFMediaEventGenerator

    GetMediaSink	proc :ptr
    GetIdentifier	proc :ptr
    GetMediaTypeHandler proc :ptr
    ProcessSample	proc :ptr
    PlaceMarker		proc :MFSTREAMSINK_MARKER_TYPE, :ptr, :ptr
    Flush		proc
    .ends

endif

ifndef __IMFVideoSampleAllocator_INTERFACE_DEFINED__
__IMFVideoSampleAllocator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFVideoSampleAllocator, "86cbc910-e533-4751-8e3b-f19b5b806a03")

.comdef IMFVideoSampleAllocator : public IUnknown

    SetDirectXManager	proc :ptr
    UninitializeSampleAllocator proc
    InitializeSampleAllocator proc :DWORD, :ptr
    AllocateSample	proc :ptr
    .ends

endif

if (WINVER GE _WIN32_WINNT_WIN7)

ifndef __IMFVideoSampleAllocatorNotify_INTERFACE_DEFINED__
__IMFVideoSampleAllocatorNotify_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFVideoSampleAllocatorNotify, "A792CDBE-C374-4e89-8335-278E7B9956A4")

.comdef IMFVideoSampleAllocatorNotify : public IUnknown

    NotifyRelease	proc
    .ends

endif

ifndef __IMFVideoSampleAllocatorCallback_INTERFACE_DEFINED__
__IMFVideoSampleAllocatorCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFVideoSampleAllocatorCallback, "992388B4-3372-4f67-8B6F-C84C071F4751")

.comdef IMFVideoSampleAllocatorCallback : public IUnknown

    SetCallback		proc :ptr
    GetFreeSampleCount	proc :ptr
    .ends

endif

ifndef __IMFVideoSampleAllocatorEx_INTERFACE_DEFINED__
__IMFVideoSampleAllocatorEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFVideoSampleAllocatorEx, "545b3a48-3283-4f62-866f-a62d8f598f9f")

.comdef IMFVideoSampleAllocatorEx : public IMFVideoSampleAllocator

    InitializeSampleAllocatorEx proc :DWORD, :DWORD, :ptr, :ptr
    .ends

endif
endif

if (WINVER GE _WIN32_WINNT_WINBLUE)

ifndef __IMFDXGIDeviceManagerSource_INTERFACE_DEFINED__
__IMFDXGIDeviceManagerSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFDXGIDeviceManagerSource, "20bc074b-7a8d-4609-8c3b-64a0a3b5d7ce")

.comdef IMFDXGIDeviceManagerSource : public IUnknown

    GetManager		proc :ptr
    .ends

endif
endif
endif

if (WINVER GE _WIN32_WINNT_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MF_VIDEO_PROCESSOR_ROTATION {
    ROTATION_NONE	= 0,
    ROTATION_NORMAL = 1
    }

.enum MF_VIDEO_PROCESSOR_MIRROR {
    MIRROR_NONE = 0,
    MIRROR_HORIZONTAL	= 1,
    MIRROR_VERTICAL = 2
    }

ifndef __IMFVideoProcessorControl_INTERFACE_DEFINED__
__IMFVideoProcessorControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFVideoProcessorControl, "A3F675D5-6119-4f7f-A100-1D8B280F0EFB")

.comdef IMFVideoProcessorControl : public IUnknown

    SetBorderColor	proc :ptr
    SetSourceRectangle	proc :ptr
    SetDestinationRectangle proc :ptr
    SetMirror		proc :MF_VIDEO_PROCESSOR_MIRROR
    SetRotation		proc :MF_VIDEO_PROCESSOR_ROTATION
    SetConstrictionSize proc :ptr
    .ends

endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFTopology_INTERFACE_DEFINED__
__IMFTopology_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTopology, "83CF873A-F6DA-4bc8-823F-BACFD55DC433")

.comdef IMFTopology : public IMFAttributes

    GetTopologyID	proc :ptr
    AddNode		proc :ptr
    RemoveNode		proc :ptr
    GetNodeCount	proc :ptr
    GetNode		proc :WORD, :ptr
    Clear		proc
    CloneFrom		proc :ptr
    GetNodeByID		proc :TOPOID, :ptr
    GetSourceNodeCollection proc :ptr
    GetOutputNodeCollection proc :ptr
    .ends

endif
endif

DEFINE_GUID( MF_TOPOLOGY_PROJECTSTART, 0x7ed3f802, 0x86bb, 0x4b3f, 0xb7, 0xe4, 0x7c, 0xb4, 0x3a, 0xfd, 0x4b, 0x80);
DEFINE_GUID( MF_TOPOLOGY_PROJECTSTOP, 0x7ed3f803, 0x86bb, 0x4b3f, 0xb7, 0xe4, 0x7c, 0xb4, 0x3a, 0xfd, 0x4b, 0x80);
DEFINE_GUID( MF_TOPOLOGY_NO_MARKIN_MARKOUT, 0x7ed3f804, 0x86bb, 0x4b3f, 0xb7, 0xe4, 0x7c, 0xb4, 0x3a, 0xfd, 0x4b, 0x80);

if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
.enum MFTOPOLOGY_DXVA_MODE {
    MFTOPOLOGY_DXVA_DEFAULT = 0,
    MFTOPOLOGY_DXVA_NONE	= 1,
    MFTOPOLOGY_DXVA_FULL	= 2
    }

endif

DEFINE_GUID(MF_TOPOLOGY_DXVA_MODE, 0x1e8d34f6, 0xf5ab, 0x4e23, 0xbb, 0x88, 0x87, 0x4a, 0xa3, 0xa1, 0xa7, 0x4d);
DEFINE_GUID(MF_TOPOLOGY_ENABLE_XVP_FOR_PLAYBACK, 0x1967731f, 0xcd78, 0x42fc, 0xb0, 0x26, 0x9, 0x92, 0xa5, 0x6e, 0x56, 0x93);
DEFINE_GUID(MF_TOPOLOGY_STATIC_PLAYBACK_OPTIMIZATIONS, 0xb86cac42, 0x41a6, 0x4b79, 0x89, 0x7a, 0x1a, 0xb0, 0xe5, 0x2b, 0x4a, 0x1b);
DEFINE_GUID(MF_TOPOLOGY_PLAYBACK_MAX_DIMS, 0x5715cf19, 0x5768, 0x44aa, 0xad, 0x6e, 0x87, 0x21, 0xf1, 0xb0, 0xf9, 0xbb);

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MFTOPOLOGY_HARDWARE_MODE {
    MFTOPOLOGY_HWMODE_SOFTWARE_ONLY = 0,
    MFTOPOLOGY_HWMODE_USE_HARDWARE	= 1,
    MFTOPOLOGY_HWMODE_USE_ONLY_HARDWARE = 2
    }

DEFINE_GUID(MF_TOPOLOGY_HARDWARE_MODE, 0xd2d362fd, 0x4e4f, 0x4191, 0xa5, 0x79, 0xc6, 0x18, 0xb6, 0x67, 0x6, 0xaf);
DEFINE_GUID(MF_TOPOLOGY_PLAYBACK_FRAMERATE, 0xc164737a, 0xc2b1, 0x4553, 0x83, 0xbb, 0x5a, 0x52, 0x60, 0x72, 0x44, 0x8f);
DEFINE_GUID(MF_TOPOLOGY_DYNAMIC_CHANGE_NOT_ALLOWED, 0xd529950b, 0xd484, 0x4527, 0xa9, 0xcd, 0xb1, 0x90, 0x95, 0x32, 0xb5, 0xb0);
DEFINE_GUID(MF_TOPOLOGY_ENUMERATE_SOURCE_TYPES, 0x6248c36d, 0x5d0b, 0x4f40, 0xa0, 0xbb, 0xb0, 0xb3, 0x05, 0xf7, 0x76, 0x98);
DEFINE_GUID( MF_TOPOLOGY_START_TIME_ON_PRESENTATION_SWITCH, 0xc8cc113f, 0x7951, 0x4548, 0xaa, 0xd6, 0x9e, 0xd6, 0x20, 0x2e, 0x62, 0xb3);
endif

endif
if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_GUID( MF_DISABLE_LOCALLY_REGISTERED_PLUGINS, 0x66b16da9, 0xadd4, 0x47e0, 0xa1, 0x6b, 0x5a, 0xf1, 0xfb, 0x48, 0x36, 0x34);
DEFINE_GUID( MF_LOCAL_PLUGIN_CONTROL_POLICY, 0xd91b0085, 0xc86d, 0x4f81, 0x88, 0x22, 0x8c, 0x68, 0xe1, 0xd7, 0xfa, 0x04);
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateTopology proto __cdecl \
		ppTopo: ptr ptr

.enum MF_TOPOLOGY_TYPE {
    MF_TOPOLOGY_OUTPUT_NODE = 0,
    MF_TOPOLOGY_SOURCESTREAM_NODE	= ( MF_TOPOLOGY_OUTPUT_NODE + 1 ) ,
    MF_TOPOLOGY_TRANSFORM_NODE	= ( MF_TOPOLOGY_SOURCESTREAM_NODE + 1 ) ,
    MF_TOPOLOGY_TEE_NODE	= ( MF_TOPOLOGY_TRANSFORM_NODE + 1 ) ,
    MF_TOPOLOGY_MAX = 0xffffffff
    }

ifndef __IMFTopologyNode_INTERFACE_DEFINED__
__IMFTopologyNode_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTopologyNode, "83CF873A-F6DA-4bc8-823F-BACFD55DC430")

.comdef IMFTopologyNode : public IMFAttributes

    SetObject		proc :ptr
    GetObject		proc :ptr
    GetNodeType		proc :ptr
    GetTopoNodeID	proc :ptr
    SetTopoNodeID	proc :TOPOID
    GetInputCount	proc :ptr
    GetOutputCount	proc :ptr
    ConnectOutput	proc :DWORD, :ptr, :DWORD
    DisconnectOutput	proc :DWORD
    GetInput		proc :DWORD, :ptr, :ptr
    GetOutput		proc :DWORD, :ptr, :ptr
    SetOutputPrefType	proc :DWORD, :ptr
    GetOutputPrefType	proc :DWORD, :ptr
    SetInputPrefType	proc :DWORD, :ptr
    GetInputPrefType	proc :DWORD, :ptr
    CloneFrom		proc :ptr
    .ends

IMFTopologyNode_RemoteGetOutputPrefType_Proxy proto __cdecl :ptr, :dword, :ptr, :ptr

IMFTopologyNode_RemoteGetOutputPrefType_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFTopologyNode_RemoteGetInputPrefType_Proxy proto __cdecl :ptr, :dword, :ptr, :ptr

IMFTopologyNode_RemoteGetInputPrefType_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

.enum MF_TOPONODE_FLUSH_MODE {
    MF_TOPONODE_FLUSH_ALWAYS	= 0,
    MF_TOPONODE_FLUSH_SEEK	= ( MF_TOPONODE_FLUSH_ALWAYS + 1 ) ,
    MF_TOPONODE_FLUSH_NEVER = ( MF_TOPONODE_FLUSH_SEEK + 1 )
    }

DEFINE_GUID( MF_TOPONODE_FLUSH, 0x494bbce8, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);

.enum MF_TOPONODE_DRAIN_MODE {
    MF_TOPONODE_DRAIN_DEFAULT	= 0,
    MF_TOPONODE_DRAIN_ALWAYS	= ( MF_TOPONODE_DRAIN_DEFAULT + 1 ) ,
    MF_TOPONODE_DRAIN_NEVER = ( MF_TOPONODE_DRAIN_ALWAYS + 1 )
    }

DEFINE_GUID( MF_TOPONODE_DRAIN, 0x494bbce9, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_D3DAWARE, 0x494bbced, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPOLOGY_RESOLUTION_STATUS, 0x494bbcde, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_ERRORCODE, 0x494bbcee, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_CONNECT_METHOD, 0x494bbcf1, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_LOCKED, 0x494bbcf7, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_WORKQUEUE_ID, 0x494bbcf8, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_WORKQUEUE_MMCSS_CLASS, 0x494bbcf9, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_DECRYPTOR, 0x494bbcfa, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_DISCARDABLE, 0x494bbcfb, 0xb031,	 0x4e38,  0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_ERROR_MAJORTYPE, 0x494bbcfd, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_ERROR_SUBTYPE, 0x494bbcfe, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_WORKQUEUE_MMCSS_TASKID, 0x494bbcff, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_WORKQUEUE_MMCSS_PRIORITY, 0x5001f840, 0x2816, 0x48f4, 0x93, 0x64, 0xad, 0x1e, 0xf6, 0x61, 0xa1, 0x23);
DEFINE_GUID( MF_TOPONODE_WORKQUEUE_ITEM_PRIORITY, 0xa1ff99be, 0x5e97, 0x4a53, 0xb4, 0x94, 0x56, 0x8c, 0x64, 0x2c, 0x0f, 0xf3);
DEFINE_GUID( MF_TOPONODE_MARKIN_HERE, 0x494bbd00, 0xb031,	 0x4e38,  0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_MARKOUT_HERE, 0x494bbd01, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_DECODER, 0x494bbd02, 0xb031, 0x4e38, 0x97, 0xc4, 0xd5, 0x42, 0x2d, 0xd6, 0x18, 0xdc);
DEFINE_GUID( MF_TOPONODE_MEDIASTART, 0x835c58ea, 0xe075, 0x4bc7, 0xbc, 0xba, 0x4d, 0xe0, 0x00, 0xdf, 0x9a, 0xe6);
DEFINE_GUID( MF_TOPONODE_MEDIASTOP, 0x835c58eb, 0xe075, 0x4bc7, 0xbc, 0xba, 0x4d, 0xe0, 0x00, 0xdf, 0x9a, 0xe6);
DEFINE_GUID( MF_TOPONODE_SOURCE, 0x835c58ec, 0xe075, 0x4bc7, 0xbc, 0xba, 0x4d, 0xe0, 0x00, 0xdf, 0x9a, 0xe6);
DEFINE_GUID( MF_TOPONODE_PRESENTATION_DESCRIPTOR, 0x835c58ed, 0xe075, 0x4bc7, 0xbc, 0xba, 0x4d, 0xe0, 0x00, 0xdf, 0x9a, 0xe6);
DEFINE_GUID( MF_TOPONODE_STREAM_DESCRIPTOR, 0x835c58ee, 0xe075, 0x4bc7, 0xbc, 0xba, 0x4d, 0xe0, 0x00, 0xdf, 0x9a, 0xe6);
DEFINE_GUID( MF_TOPONODE_SEQUENCE_ELEMENTID, 0x835c58ef, 0xe075, 0x4bc7, 0xbc, 0xba, 0x4d, 0xe0, 0x00, 0xdf, 0x9a, 0xe6);
DEFINE_GUID( MF_TOPONODE_TRANSFORM_OBJECTID, 0x88dcc0c9, 0x293e, 0x4e8b, 0x9a, 0xeb, 0xa, 0xd6, 0x4c, 0xc0, 0x16, 0xb0);
DEFINE_GUID( MF_TOPONODE_STREAMID, 0x14932f9b, 0x9087, 0x4bb4, 0x84, 0x12, 0x51, 0x67, 0x14, 0x5c, 0xbe, 0x04);
DEFINE_GUID( MF_TOPONODE_NOSHUTDOWN_ON_REMOVE, 0x14932f9c, 0x9087, 0x4bb4, 0x84, 0x12, 0x51, 0x67, 0x14, 0x5c, 0xbe, 0x04);
DEFINE_GUID( MF_TOPONODE_RATELESS, 0x14932f9d, 0x9087, 0x4bb4, 0x84, 0x12, 0x51, 0x67, 0x14, 0x5c, 0xbe, 0x04);
DEFINE_GUID( MF_TOPONODE_DISABLE_PREROLL, 0x14932f9e, 0x9087, 0x4bb4, 0x84, 0x12, 0x51, 0x67, 0x14, 0x5c, 0xbe, 0x04);
DEFINE_GUID( MF_TOPONODE_PRIMARYOUTPUT, 0x6304ef99, 0x16b2, 0x4ebe, 0x9d, 0x67, 0xe4, 0xc5, 0x39, 0xb3, 0xa2, 0x59);

MFCreateTopologyNode proto __cdecl \
	      NodeType: MF_TOPOLOGY_TYPE,
		ppNode: ptr ptr

if (WINVER GE _WIN32_WINNT_WIN7)

MFGetTopoNodeCurrentType proto __cdecl \
		 pNode: ptr IMFTopologyNode,
	 dwStreamIndex: DWORD,
	       fOutput: BOOL,
		ppType: ptr ptr IMFMediaType

endif
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFGetService_INTERFACE_DEFINED__
__IMFGetService_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFGetService, "fa993888-4383-415a-a930-dd472a8cf6f7")

.comdef IMFGetService : public IUnknown

    GetService		proc :REFGUID, :REFIID, :ptr
    .ends

endif

MFGetService proto __cdecl \
	    punkObject: ptr IUnknown,
	   guidService: REFGUID,
		  riid: REFIID,
	     ppvObject: ptr ptr

MFTIME	typedef LONGLONG

.enum MFCLOCK_CHARACTERISTICS_FLAGS {
    MFCLOCK_CHARACTERISTICS_FLAG_FREQUENCY_10MHZ	= 0x2,
    MFCLOCK_CHARACTERISTICS_FLAG_ALWAYS_RUNNING = 0x4,
    MFCLOCK_CHARACTERISTICS_FLAG_IS_SYSTEM_CLOCK	= 0x8
    }

.enum MFCLOCK_STATE {
    MFCLOCK_STATE_INVALID	= 0,
    MFCLOCK_STATE_RUNNING	= ( MFCLOCK_STATE_INVALID + 1 ) ,
    MFCLOCK_STATE_STOPPED	= ( MFCLOCK_STATE_RUNNING + 1 ) ,
    MFCLOCK_STATE_PAUSED	= ( MFCLOCK_STATE_STOPPED + 1 )
    }

.enum MFCLOCK_RELATIONAL_FLAGS {
    MFCLOCK_RELATIONAL_FLAG_JITTER_NEVER_AHEAD	= 0x1
    }

MFCLOCK_PROPERTIES	STRUC
qwCorrelationRate	int64_t ?
guidClockId		GUID <>
dwClockFlags		dd ?
qwClockFrequency	int64_t ?
dwClockTolerance	dd ?
dwClockJitter		dd ?
MFCLOCK_PROPERTIES	ENDS

MFCLOCK_FREQUENCY_HNS	equ 10000000
MFCLOCK_TOLERANCE_UNKNOWN equ 50000
MFCLOCK_JITTER_ISR	equ 1000
MFCLOCK_JITTER_DPC	equ 4000
MFCLOCK_JITTER_PASSIVE	equ 10000

ifndef __IMFClock_INTERFACE_DEFINED__
__IMFClock_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFClock, "2eb1e945-18b8-4139-9b1a-d5d584818530")

.comdef IMFClock : public IUnknown

    GetClockCharacteristics proc :ptr
    GetCorrelatedTime	proc :DWORD, :ptr, :ptr
    GetContinuityKey	proc :ptr
    GetState		proc :DWORD, :ptr
    GetProperties	proc :ptr
    .ends

endif

MFGetSystemTime proto __cdecl
PRESENTATION_CURRENT_POSITION equ 0x7fffffffffffffff

ifndef __IMFPresentationClock_INTERFACE_DEFINED__
__IMFPresentationClock_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFPresentationClock, "868CE85C-8EA9-4f55-AB82-B009A910A805")

.comdef IMFPresentationClock : public IMFClock

    SetTimeSource	proc :ptr
    GetTimeSource	proc :ptr
    GetTime		proc :ptr
    AddClockStateSink	proc :ptr
    RemoveClockStateSink proc :ptr
    Start		proc :LONGLONG
    Stop		proc
    _Pause		proc
    .ends

endif
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreatePresentationClock proto __cdecl \
   ppPresentationClock: ptr ptr IMFPresentationClock

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __IMFPresentationTimeSource_INTERFACE_DEFINED__
__IMFPresentationTimeSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFPresentationTimeSource, "7FF12CCE-F76F-41c2-863B-1666C8E5E139")

.comdef IMFPresentationTimeSource : public IMFClock

    GetUnderlyingClock	proc :ptr
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateSystemTimeSource proto __cdecl \
    ppSystemTimeSource: ptr ptr IMFPresentationTimeSource

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFClockStateSink_INTERFACE_DEFINED__
__IMFClockStateSink_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFClockStateSink, "F6696E82-74F7-4f3d-A178-8A5E09C3659F")

.comdef IMFClockStateSink : public IUnknown

    OnClockStart	proc :MFTIME, :LONGLONG
    OnClockStop		proc :MFTIME
    OnClockPause	proc :MFTIME
    OnClockRestart	proc :MFTIME
    OnClockSetRate	proc :MFTIME, :real4
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
DEFINE_GUID( MF_PD_PMPHOST_CONTEXT, 0x6c990d31, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID( MF_PD_APP_CONTEXT, 0x6c990d32, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
DEFINE_GUID( MF_PD_DURATION, 0x6c990d33, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID( MF_PD_TOTAL_FILE_SIZE, 0x6c990d34, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID( MF_PD_AUDIO_ENCODING_BITRATE, 0x6c990d35, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID( MF_PD_VIDEO_ENCODING_BITRATE, 0x6c990d36, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID( MF_PD_MIME_TYPE, 0x6c990d37, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID(MF_PD_LAST_MODIFIED_TIME, 0x6c990d38, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID(MF_PD_PLAYBACK_ELEMENT_ID, 0x6c990d39, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID( MF_PD_PREFERRED_LANGUAGE, 0x6c990d3A, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID(MF_PD_PLAYBACK_BOUNDARY_TIME, 0x6c990d3b, 0xbb8e, 0x477a, 0x85, 0x98, 0xd, 0x5d, 0x96, 0xfc, 0xd8, 0x8a );
DEFINE_GUID( MF_PD_AUDIO_ISVARIABLEBITRATE, 0x33026ee0, 0xe387, 0x4582, 0xae, 0x0a, 0x34, 0xa2, 0xad, 0x3b, 0xaa, 0x18 );
endif

ifndef __IMFPresentationDescriptor_INTERFACE_DEFINED__
__IMFPresentationDescriptor_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFPresentationDescriptor, "03cb2711-24d7-4db6-a17f-f3a7a479a536")

.comdef IMFPresentationDescriptor : public IMFAttributes

    GetStreamDescriptorCount proc :ptr
    GetStreamDescriptorByIndex proc :DWORD, :ptr, :ptr
    SelectStream	proc :DWORD
    DeselectStream	proc :DWORD
    Clone		proc :ptr
    .ends

endif

MFCreatePresentationDescriptor proto __cdecl \
    cStreamDescriptors: DWORD,
   apStreamDescriptors: ptr ptr IMFStreamDescriptor,
ppPresentationDescriptor: ptr ptr IMFPresentationDescriptor


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFRequireProtectedEnvironment proto __cdecl \
pPresentationDescriptor: ptr IMFPresentationDescriptor


MFSerializePresentationDescriptor proto __cdecl \
		   pPD: ptr,
	       pcbData: ptr,
	       ppbData: ptr ptr


MFDeserializePresentationDescriptor proto __cdecl \
		cbData: DWORD,
		pbData: ptr,
		  ppPD: ptr ptr


endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DEFINE_GUID(MF_SD_LANGUAGE, 0xaf2180, 0xbdc2, 0x423c, 0xab, 0xca, 0xf5, 0x3, 0x59, 0x3b, 0xc1, 0x21);
DEFINE_GUID(MF_SD_PROTECTED, 0xaf2181, 0xbdc2, 0x423c, 0xab, 0xca, 0xf5, 0x3, 0x59, 0x3b, 0xc1, 0x21);
DEFINE_GUID(MF_SD_STREAM_NAME, 0x4f1b099d, 0xd314, 0x41e5, 0xa7, 0x81, 0x7f, 0xef, 0xaa, 0x4c, 0x50, 0x1f);
DEFINE_GUID(MF_SD_MUTUALLY_EXCLUSIVE, 0x23ef79c, 0x388d, 0x487f, 0xac, 0x17, 0x69, 0x6c, 0xd6, 0xe3, 0xc6, 0xf5);

ifndef __IMFStreamDescriptor_INTERFACE_DEFINED__
__IMFStreamDescriptor_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFStreamDescriptor, "56c03d9c-9dbb-45f5-ab4b-d80f47c05938")

.comdef IMFStreamDescriptor : public IMFAttributes

    GetStreamIdentifier proc :ptr
    GetMediaTypeHandler proc :ptr
    .ends

endif

MFCreateStreamDescriptor proto __cdecl \
    dwStreamIdentifier: DWORD,
	   cMediaTypes: DWORD,
	  apMediaTypes: ptr ptr IMFMediaType,
	  ppDescriptor: ptr ptr IMFStreamDescriptor

ifndef __IMFMediaTypeHandler_INTERFACE_DEFINED__
__IMFMediaTypeHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaTypeHandler, "e93dcf6c-4b07-4e1e-8123-aa16ed6eadf5")

.comdef IMFMediaTypeHandler : public IUnknown

    IsMediaTypeSupported proc :ptr, :ptr
    GetMediaTypeCount	proc :ptr
    GetMediaTypeByIndex proc :DWORD, :ptr
    SetCurrentMediaType proc :ptr
    GetCurrentMediaType proc :ptr
    GetMajorType	proc :ptr
    .ends

IMFMediaTypeHandler_RemoteIsMediaTypeSupported_Proxy proto __cdecl :ptr, :ptr, :dword, :ptr, :ptr

IMFMediaTypeHandler_RemoteIsMediaTypeSupported_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFMediaTypeHandler_RemoteGetMediaTypeByIndex_Proxy proto __cdecl :ptr, :dword, :ptr, :ptr

IMFMediaTypeHandler_RemoteGetMediaTypeByIndex_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFMediaTypeHandler_RemoteSetCurrentMediaType_Proxy proto __cdecl :ptr, :ptr, :dword

IMFMediaTypeHandler_RemoteSetCurrentMediaType_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFMediaTypeHandler_RemoteGetCurrentMediaType_Proxy proto __cdecl :ptr, :ptr, :ptr

IMFMediaTypeHandler_RemoteGetCurrentMediaType_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateSimpleTypeHandler proto __cdecl \
	     ppHandler: ptr ptr

.enum MFTIMER_FLAGS {
    MFTIMER_RELATIVE	= 0x1
    }

ifndef __IMFTimer_INTERFACE_DEFINED__
__IMFTimer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTimer, "e56e4cbd-8f70-49d8-a0f8-edb3d6ab9bf2")

.comdef IMFTimer : public IUnknown

    SetTimer		proc :DWORD, :LONGLONG, :ptr, :ptr, :ptr
    CancelTimer		proc :ptr
    .ends

endif

DEFINE_GUID( MF_ACTIVATE_CUSTOM_VIDEO_MIXER_CLSID,	  0xba491360, 0xbe50, 0x451e, 0x95, 0xab, 0x6d, 0x4a, 0xcc, 0xc7, 0xda, 0xd8 );
DEFINE_GUID( MF_ACTIVATE_CUSTOM_VIDEO_MIXER_ACTIVATE,	  0xba491361, 0xbe50, 0x451e, 0x95, 0xab, 0x6d, 0x4a, 0xcc, 0xc7, 0xda, 0xd8 );
DEFINE_GUID( MF_ACTIVATE_CUSTOM_VIDEO_MIXER_FLAGS,	  0xba491362, 0xbe50, 0x451e, 0x95, 0xab, 0x6d, 0x4a, 0xcc, 0xc7, 0xda, 0xd8 );
DEFINE_GUID( MF_ACTIVATE_CUSTOM_VIDEO_PRESENTER_CLSID,	  0xba491364, 0xbe50, 0x451e, 0x95, 0xab, 0x6d, 0x4a, 0xcc, 0xc7, 0xda, 0xd8 );
DEFINE_GUID( MF_ACTIVATE_CUSTOM_VIDEO_PRESENTER_ACTIVATE,	  0xba491365, 0xbe50, 0x451e, 0x95, 0xab, 0x6d, 0x4a, 0xcc, 0xc7, 0xda, 0xd8 );
DEFINE_GUID( MF_ACTIVATE_CUSTOM_VIDEO_PRESENTER_FLAGS,	  0xba491366, 0xbe50, 0x451e, 0x95, 0xab, 0x6d, 0x4a, 0xcc, 0xc7, 0xda, 0xd8 );

.enum _MIDL___MIDL_itf_mfidl_0000_0024_0001 {
    MF_ACTIVATE_CUSTOM_MIXER_ALLOWFAIL	= 0x1
    }

.enum _MIDL___MIDL_itf_mfidl_0000_0024_0002 {
    MF_ACTIVATE_CUSTOM_PRESENTER_ALLOWFAIL	= 0x1
    }
DEFINE_GUID( MF_ACTIVATE_MFT_LOCKED, 0xc1f6093c, 0x7f65, 0x4fbd, 0x9e, 0x39, 0x5f, 0xae, 0xc3, 0xc4, 0xfb, 0xd7 );
DEFINE_GUID( MF_ACTIVATE_VIDEO_WINDOW, 0x9a2dbbdd, 0xf57e, 0x4162, 0x82, 0xb9, 0x68, 0x31, 0x37, 0x76, 0x82, 0xd3 );
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MFSHUTDOWN_STATUS {
    MFSHUTDOWN_INITIATED	= 0,
    MFSHUTDOWN_COMPLETED	= ( MFSHUTDOWN_INITIATED + 1 )
    }

ifndef __IMFShutdown_INTERFACE_DEFINED__
__IMFShutdown_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFShutdown, "97ec2ea4-0e42-4937-97ac-9d6d328824e1")

.comdef IMFShutdown : public IUnknown

    Shutdown		proc
    GetShutdownStatus	proc :ptr
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFShutdownObject proto __cdecl \
		  pUnk: ptr

MFCreateAudioRenderer proto __cdecl \
      pAudioAttributes: ptr IMFAttributes,
		ppSink: ptr ptr IMFMediaSink

;STDAPI
MFCreateAudioRendererActivate proto __cdecl \
	    ppActivate: ptr ptr

DEFINE_GUID( MF_AUDIO_RENDERER_ATTRIBUTE_FLAGS, 0xede4b5e0, 0xf805, 0x4d6c, 0x99, 0xb3, 0xdb, 0x01, 0xbf, 0x95, 0xdf, 0xab);
MF_AUDIO_RENDERER_ATTRIBUTE_FLAGS_CROSSPROCESS equ 0x00000001
MF_AUDIO_RENDERER_ATTRIBUTE_FLAGS_NOPERSIST equ 0x00000002
if (WINVER GE _WIN32_WINNT_WIN7)
MF_AUDIO_RENDERER_ATTRIBUTE_FLAGS_DONT_ALLOW_FORMAT_CHANGES equ 0x00000004
endif
DEFINE_GUID( MF_AUDIO_RENDERER_ATTRIBUTE_SESSION_ID, 0xede4b5e3, 0xf805, 0x4d6c, 0x99, 0xb3, 0xdb, 0x01, 0xbf, 0x95, 0xdf, 0xab);
DEFINE_GUID( MF_AUDIO_RENDERER_ATTRIBUTE_ENDPOINT_ID, 0xb10aaec3, 0xef71, 0x4cc3, 0xb8, 0x73, 0x5, 0xa9, 0xa0, 0x8b, 0x9f, 0x8e);
DEFINE_GUID( MF_AUDIO_RENDERER_ATTRIBUTE_ENDPOINT_ROLE, 0x6ba644ff, 0x27c5, 0x4d02, 0x98, 0x87, 0xc2, 0x86, 0x19, 0xfd, 0xb9, 0x1b);
DEFINE_GUID( MF_AUDIO_RENDERER_ATTRIBUTE_STREAM_CATEGORY, 0xa9770471, 0x92ec, 0x4df4, 0x94, 0xfe, 0x81, 0xc3, 0x6f, 0xc, 0x3a, 0x7a);

MFCreateVideoRendererActivate proto __cdecl \
	     hwndVideo: HWND,
	    ppActivate: ptr ptr

if (WINVER GE _WIN32_WINNT_WIN7)
;STDAPI
MFCreateMPEG4MediaSink proto __cdecl \
	  pIByteStream: ptr IMFByteStream,
       pVideoMediaType: ptr IMFMediaType,
       pAudioMediaType: ptr IMFMediaType,
	  ppIMediaSink: ptr ptr IMFMediaSink

;STDAPI
MFCreate3GPMediaSink proto __cdecl \
	  pIByteStream: ptr IMFByteStream,
       pVideoMediaType: ptr IMFMediaType,
       pAudioMediaType: ptr IMFMediaType,
	  ppIMediaSink: ptr ptr IMFMediaSink

;STDAPI
MFCreateMP3MediaSink proto __cdecl \
     pTargetByteStream: ptr IMFByteStream,
	   ppMediaSink: ptr ptr IMFMediaSink

endif ;; (WINVER GE _WIN32_WINNT_WIN7)
if (WINVER GE _WIN32_WINNT_WIN8)
;STDAPI
MFCreateAC3MediaSink proto __cdecl \
     pTargetByteStream: ptr IMFByteStream,
       pAudioMediaType: ptr IMFMediaType,
	   ppMediaSink: ptr ptr IMFMediaSink

;STDAPI
MFCreateADTSMediaSink proto __cdecl \
     pTargetByteStream: ptr IMFByteStream,
       pAudioMediaType: ptr IMFMediaType,
	   ppMediaSink: ptr ptr IMFMediaSink

;STDAPI
MFCreateMuxSink proto __cdecl \
     guidOutputSubType: ptr GUID,
     pOutputAttributes: ptr IMFAttributes,
     pOutputByteStream: ptr IMFByteStream,
	     ppMuxSink: ptr ptr IMFMediaSink

;STDAPI
MFCreateFMPEG4MediaSink proto __cdecl \
	  pIByteStream: ptr IMFByteStream,
       pVideoMediaType: ptr IMFMediaType,
       pAudioMediaType: ptr IMFMediaType,
	  ppIMediaSink: ptr ptr IMFMediaSink

endif
if (WINVER GE _WIN32_WINNT_WINBLUE)

MFCreateAVIMediaSink proto __cdecl \
	  pIByteStream: ptr IMFByteStream,
       pVideoMediaType: ptr IMFMediaType,
       pAudioMediaType: ptr IMFMediaType,
	  ppIMediaSink: ptr ptr IMFMediaSink

endif
if (WINVER GE _WIN32_WINNT_WINBLUE)

MFCreateWAVEMediaSink proto __cdecl \
     pTargetByteStream: ptr IMFByteStream,
       pAudioMediaType: ptr IMFMediaType,
	   ppMediaSink: ptr ptr IMFMediaSink

endif

ifndef __IMFTopoLoader_INTERFACE_DEFINED__
__IMFTopoLoader_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTopoLoader, "DE9A6157-F660-4643-B56A-DF9F7998C7CD")

.comdef IMFTopoLoader : public IUnknown

    Load		proc :ptr, :ptr, :ptr
    .ends

endif

MFCreateTopoLoader proto __cdecl \
		 ppObj: ptr  ptr

ifndef __IMFContentProtectionManager_INTERFACE_DEFINED__
__IMFContentProtectionManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFContentProtectionManager, "ACF92459-6A61-42bd-B57C-B43E51203CB0")

.comdef IMFContentProtectionManager : public IUnknown

    BeginEnableContent	proc :ptr, :ptr, :ptr, :ptr
    EndEnableContent	proc :ptr
    .ends

IMFContentProtectionManager_RemoteBeginEnableContent_Proxy proto __cdecl :ptr, :REFCLSID, :ptr, :dword, :ptr

IMFContentProtectionManager_RemoteBeginEnableContent_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFContentProtectionManager_RemoteEndEnableContent_Proxy proto __cdecl :ptr, :ptr

IMFContentProtectionManager_RemoteEndEnableContent_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

.enum _MIDL___MIDL_itf_mfidl_0000_0027_0001 {
    MF_LICENSE_URL_UNTRUSTED	= 0,
    MF_LICENSE_URL_TRUSTED	= ( MF_LICENSE_URL_UNTRUSTED + 1 ) ,
    MF_LICENSE_URL_TAMPERED = ( MF_LICENSE_URL_TRUSTED + 1 )
    }

ifndef __IMFContentEnabler_INTERFACE_DEFINED__
__IMFContentEnabler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFContentEnabler, "D3C4EF59-49CE-4381-9071-D5BCD044C770")

.comdef IMFContentEnabler : public IUnknown

    GetEnableType	proc :ptr
    GetEnableURL	proc :ptr, :ptr, :ptr
    GetEnableData	proc :ptr, :ptr
    IsAutomaticSupported proc :ptr
    AutomaticEnable	proc
    MonitorEnable	proc
    Cancel		proc
    .ends

endif

DEFINE_GUID( MFENABLETYPE_WMDRMV1_LicenseAcquisition, 0x4ff6eeaf, 0xb43, 0x4797, 0x9b, 0x85, 0xab, 0xf3, 0x18, 0x15, 0xe7, 0xb0);
DEFINE_GUID( MFENABLETYPE_WMDRMV7_LicenseAcquisition, 0x3306df, 0x4a06, 0x4884,0xa0, 0x97, 0xef, 0x6d, 0x22, 0xec, 0x84, 0xa3);
DEFINE_GUID( MFENABLETYPE_WMDRMV7_Individualization, 0xacd2c84a, 0xb303, 0x4f65, 0xbc, 0x2c, 0x2c, 0x84, 0x8d, 0x1, 0xa9, 0x89);
DEFINE_GUID( MFENABLETYPE_MF_UpdateRevocationInformation, 0xe558b0b5, 0xb3c4, 0x44a0, 0x92, 0x4c, 0x50, 0xd1, 0x78, 0x93, 0x23, 0x85);
DEFINE_GUID( MFENABLETYPE_MF_UpdateUntrustedComponent, 0x9879f3d6, 0xcee2, 0x48e6, 0xb5, 0x73, 0x97, 0x67, 0xab, 0x17, 0x2f, 0x16);
DEFINE_GUID( MFENABLETYPE_MF_RebootRequired, 0x6d4d3d4b, 0x0ece, 0x4652, 0x8b, 0x3a, 0xf2, 0xd2, 0x42, 0x60, 0xd8, 0x87);
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef MFRR_INFO_VERSION
MFRR_INFO_VERSION	equ 0
endif

MF_USER_MODE_COMPONENT_LOAD equ 0x00000001
MF_KERNEL_MODE_COMPONENT_LOAD equ 0x00000002
MF_GRL_LOAD_FAILED	equ 0x00000010
MF_INVALID_GRL_SIGNATURE equ 0x00000020
MF_GRL_ABSENT		equ 0x00001000
MF_COMPONENT_REVOKED	equ 0x00002000
MF_COMPONENT_INVALID_EKU equ 0x00004000
MF_COMPONENT_CERT_REVOKED equ 0x00008000
MF_COMPONENT_INVALID_ROOT equ 0x00010000
MF_COMPONENT_HS_CERT_REVOKED equ 0x00020000
MF_COMPONENT_LS_CERT_REVOKED equ 0x00040000
MF_BOOT_DRIVER_VERIFICATION_FAILED equ 0x00100000
MF_TEST_SIGNED_COMPONENT_LOADING equ 0x01000000
MF_MINCRYPT_FAILURE	equ 0x10000000
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

SHA_HASH_LEN		equ 20
STR_HASH_LEN		equ (SHA_HASH_LEN*2 + 3)
MFRR_COMPONENT_HASH_INFO STRUC
ulReason		dd ?
rgHeaderHash		WCHAR STR_HASH_LEN dup(?)
rgPublicKeyHash		WCHAR STR_HASH_LEN dup(?)
wszName			WCHAR MAX_PATH dup(?)
MFRR_COMPONENT_HASH_INFO ENDS
PMFRR_COMPONENT_HASH_INFO typedef ptr MFRR_COMPONENT_HASH_INFO

MFRR_COMPONENTS		STRUC
dwRRInfoVersion		dd ?
dwRRComponents		dd ?
pRRComponents		PMFRR_COMPONENT_HASH_INFO ?
MFRR_COMPONENTS		ENDS
PMFRR_COMPONENTS	typedef ptr MFRR_COMPONENTS

.pragma pack(push, 1)

ASF_FLAT_PICTURE	STRUC
bPictureType		db ?
dwDataLen		dd ?
ASF_FLAT_PICTURE	ENDS

ASF_FLAT_SYNCHRONISED_LYRICS STRUC
bTimeStampFormat	db ?
bContentType		db ?
dwLyricsLen		dd ?
ASF_FLAT_SYNCHRONISED_LYRICS ENDS
.pragma pack(pop)
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFMetadata_INTERFACE_DEFINED__
__IMFMetadata_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMetadata, "F88CFB8C-EF16-4991-B450-CB8C69E51704")

.comdef IMFMetadata : public IUnknown

    SetLanguage		proc :LPCWSTR
    GetLanguage		proc :ptr
    GetAllLanguages	proc :ptr
    SetProperty		proc :LPCWSTR, :ptr
    GetProperty		proc :LPCWSTR, :ptr
    DeleteProperty	proc :LPCWSTR
    GetAllPropertyNames proc :ptr
    .ends

endif

ifndef __IMFMetadataProvider_INTERFACE_DEFINED__
__IMFMetadataProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMetadataProvider, "56181D2D-E221-4adb-B1C8-3CEE6A53F76F")

.comdef IMFMetadataProvider : public IUnknown

    GetMFMetadata	proc :ptr, :DWORD, :DWORD, :ptr
    .ends

endif

DEFINE_GUID( MF_METADATA_PROVIDER_SERVICE, 0xdb214084, 0x58a4, 0x4d2e, 0xb8, 0x4f, 0x6f, 0x75, 0x5b, 0x2f, 0x7a, 0xd);
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID( MF_PROPERTY_HANDLER_SERVICE, 0xa3face02, 0x32b8, 0x41dd, 0x90, 0xe7, 0x5f, 0xef, 0x7c, 0x89, 0x91, 0xb5);
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MFRATE_DIRECTION {
    MFRATE_FORWARD	= 0,
    MFRATE_REVERSE	= ( MFRATE_FORWARD + 1 )
    }

ifndef __IMFRateSupport_INTERFACE_DEFINED__
__IMFRateSupport_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFRateSupport, "0a9ccdbc-d797-4563-9667-94ec5d79292d")

.comdef IMFRateSupport : public IUnknown

    GetSlowestRate	proc :MFRATE_DIRECTION, :BOOL, :ptr
    GetFastestRate	proc :MFRATE_DIRECTION, :BOOL, :ptr
    IsRateSupported	proc :BOOL, :real4, :ptr
    .ends

endif

DEFINE_GUID( MF_RATE_CONTROL_SERVICE, 0x866fa297, 0xb802, 0x4bf8, 0x9d, 0xc9, 0x5e, 0x3b, 0x6a, 0x9f, 0x53, 0xc9);

ifndef __IMFRateControl_INTERFACE_DEFINED__
__IMFRateControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFRateControl, "88ddcd21-03c3-4275-91ed-55ee3929328f")

.comdef IMFRateControl : public IUnknown

    SetRate		proc :BOOL, :real4
    GetRate		proc :ptr, :ptr
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if (WINVER GE _WIN32_WINNT_WIN7)
ifndef __IMFTimecodeTranslate_INTERFACE_DEFINED__
__IMFTimecodeTranslate_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTimecodeTranslate, "ab9d8661-f7e8-4ef4-9861-89f334f94e74")

.comdef IMFTimecodeTranslate : public IUnknown

    BeginConvertTimecodeToHNS proc :ptr, :ptr, :ptr
    EndConvertTimecodeToHNS proc :ptr, :ptr
    BeginConvertHNSToTimecode proc :MFTIME, :ptr, :ptr
    EndConvertHNSToTimecode proc :ptr, :ptr
    .ends

endif
DEFINE_GUID( MF_TIMECODE_SERVICE, 0xa0d502a7, 0x0eb3, 0x4885, 0xb1, 0xb9, 0x9f, 0xeb, 0x0d, 0x08, 0x34, 0x54 );
endif

if (WINVER GE _WIN32_WINNT_WIN8)
ifndef __IMFSeekInfo_INTERFACE_DEFINED__
__IMFSeekInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSeekInfo, "26AFEA53-D9ED-42B5-AB80-E64F9EE34779")

.comdef IMFSeekInfo : public IUnknown

    GetNearestKeyFrames proc :ptr, :ptr, :ptr, :ptr
    .ends

endif

externdef		MF_SCRUBBING_SERVICE:GUID
endif

ifndef __IMFSimpleAudioVolume_INTERFACE_DEFINED__
__IMFSimpleAudioVolume_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSimpleAudioVolume, "089EDF13-CF71-4338-8D13-9E569DBDC319")

.comdef IMFSimpleAudioVolume : public IUnknown

    SetMasterVolume	proc :real4
    GetMasterVolume	proc :ptr
    SetMute		proc :BOOL
    GetMute		proc :ptr
    .ends

endif

DEFINE_GUID( MR_POLICY_VOLUME_SERVICE, 0x1abaa2ac, 0x9d3b, 0x47c6, 0xab, 0x48, 0xc5, 0x95, 0x6, 0xde, 0x78, 0x4d);
if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_GUID( MR_CAPTURE_POLICY_VOLUME_SERVICE, 0x24030acd, 0x107a, 0x4265, 0x97, 0x5c, 0x41, 0x4e, 0x33, 0xe6, 0x5f, 0x2a);
endif

ifndef __IMFAudioStreamVolume_INTERFACE_DEFINED__
__IMFAudioStreamVolume_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFAudioStreamVolume, "76B1BBDB-4EC8-4f36-B106-70A9316DF593")

.comdef IMFAudioStreamVolume : public IUnknown

    GetChannelCount	proc :ptr
    SetChannelVolume	proc :UINT32, :real4
    GetChannelVolume	proc :UINT32, :ptr
    SetAllVolumes	proc :UINT32, :ptr
    GetAllVolumes	proc :UINT32, :ptr
    .ends

endif

DEFINE_GUID( MR_STREAM_VOLUME_SERVICE, 0xf8b5fa2f, 0x32ef, 0x46f5, 0xb1, 0x72, 0x13, 0x21, 0x21, 0x2f, 0xb2, 0xc4);

ifndef __IMFAudioPolicy_INTERFACE_DEFINED__
__IMFAudioPolicy_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFAudioPolicy, "a0638c2b-6465-4395-9ae7-a321a9fd2856")

.comdef IMFAudioPolicy : public IUnknown

    SetGroupingParam	proc :REFGUID
    GetGroupingParam	proc :ptr
    SetDisplayName	proc :LPCWSTR
    GetDisplayName	proc :ptr
    SetIconPath		proc :LPCWSTR
    GetIconPath		proc :ptr
    .ends

endif

DEFINE_GUID( MR_AUDIO_POLICY_SERVICE, 0x911fd737, 0x6775, 0x4ab0, 0xa6, 0x14, 0x29, 0x78, 0x62, 0xfd, 0xac, 0x88);

ifndef __IMFSampleGrabberSinkCallback_INTERFACE_DEFINED__
__IMFSampleGrabberSinkCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSampleGrabberSinkCallback, "8C7B80BF-EE42-4b59-B1DF-55668E1BDCA8")

.comdef IMFSampleGrabberSinkCallback : public IMFClockStateSink

    OnSetPresentationClock proc :ptr
    OnProcessSample	proc :REFGUID, :DWORD, :LONGLONG, :LONGLONG
    OnShutdown		proc
    .ends

endif

MFCreateSampleGrabberSinkActivate proto __cdecl \
	 pIMFMediaType: ptr IMFMediaType,
pIMFSampleGrabberSinkCallback: ptr IMFSampleGrabberSinkCallback,
	   ppIActivate: ptr ptr IMFActivate

DEFINE_GUID( MF_SAMPLEGRABBERSINK_SAMPLE_TIME_OFFSET, 0x62e3d776, 0x8100, 0x4e03, 0xa6, 0xe8, 0xbd, 0x38, 0x57, 0xac, 0x9c, 0x47);
if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID( MF_SAMPLEGRABBERSINK_IGNORE_CLOCK, 0x0efda2c0, 0x2b69, 0x4e2e, 0xab, 0x8d, 0x46, 0xdc, 0xbf, 0xf7, 0xd2, 0x5d);

ifndef __IMFSampleGrabberSinkCallback2_INTERFACE_DEFINED__
__IMFSampleGrabberSinkCallback2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSampleGrabberSinkCallback2, "ca86aa50-c46e-429e-ab27-16d6ac6844cb")

.comdef IMFSampleGrabberSinkCallback2 : public IMFSampleGrabberSinkCallback

    OnProcessSampleEx	proc :REFGUID, :DWORD, :LONGLONG, :LONGLONG
    .ends

endif
endif
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
DEFINE_GUID( MF_QUALITY_SERVICES, 0xb7e2be11, 0x2f96, 0x4640, 0xb5, 0x2c, 0x28, 0x23, 0x65, 0xbd, 0xf1, 0x6c);
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
ifndef __IMFWorkQueueServices_INTERFACE_DEFINED__
__IMFWorkQueueServices_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFWorkQueueServices, "35FE1BB8-A3A9-40fe-BBEC-EB569C9CCCA3")

.comdef IMFWorkQueueServices : public IUnknown

    BeginRegisterTopologyWorkQueuesWithMMCSS proc :ptr, :ptr
    EndRegisterTopologyWorkQueuesWithMMCSS proc :ptr
    BeginUnregisterTopologyWorkQueuesWithMMCSS proc :ptr, :ptr
    EndUnregisterTopologyWorkQueuesWithMMCSS proc :ptr
    GetTopologyWorkQueueMMCSSClass proc :DWORD, :LPWSTR, :ptr
    GetTopologyWorkQueueMMCSSTaskId proc :DWORD, :ptr
    BeginRegisterPlatformWorkQueueWithMMCSS proc :DWORD, :LPCWSTR, :DWORD, :ptr, :ptr
    EndRegisterPlatformWorkQueueWithMMCSS proc :ptr, :ptr
    BeginUnregisterPlatformWorkQueueWithMMCSS proc :DWORD, :ptr, :ptr
    EndUnregisterPlatformWorkQueueWithMMCSS proc :ptr
    GetPlaftormWorkQueueMMCSSClass proc :DWORD, :LPWSTR, :ptr
    GetPlatformWorkQueueMMCSSTaskId proc :DWORD, :ptr
    .ends


IMFWorkQueueServices_RemoteBeginRegisterTopologyWorkQueuesWithMMCSS_Proxy proto __cdecl :ptr, :ptr

IMFWorkQueueServices_RemoteBeginRegisterTopologyWorkQueuesWithMMCSS_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFWorkQueueServices_RemoteEndRegisterTopologyWorkQueuesWithMMCSS_Proxy proto __cdecl :ptr, :ptr

IMFWorkQueueServices_RemoteEndRegisterTopologyWorkQueuesWithMMCSS_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFWorkQueueServices_RemoteBeginUnregisterTopologyWorkQueuesWithMMCSS_Proxy proto __cdecl :ptr, :ptr

IMFWorkQueueServices_RemoteBeginUnregisterTopologyWorkQueuesWithMMCSS_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFWorkQueueServices_RemoteEndUnregisterTopologyWorkQueuesWithMMCSS_Proxy proto __cdecl :ptr, :ptr

IMFWorkQueueServices_RemoteEndUnregisterTopologyWorkQueuesWithMMCSS_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFWorkQueueServices_RemoteBeginRegisterPlatformWorkQueueWithMMCSS_Proxy proto __cdecl :ptr, :dword, :ptr, :dword, :ptr

IMFWorkQueueServices_RemoteBeginRegisterPlatformWorkQueueWithMMCSS_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFWorkQueueServices_RemoteEndRegisterPlatformWorkQueueWithMMCSS_Proxy proto __cdecl :ptr, :ptr, :ptr

IMFWorkQueueServices_RemoteEndRegisterPlatformWorkQueueWithMMCSS_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFWorkQueueServices_RemoteBeginUnregisterPlatformWorkQueueWithMMCSS_Proxy proto __cdecl :ptr, :dword, :ptr

IMFWorkQueueServices_RemoteBeginUnregisterPlatformWorkQueueWithMMCSS_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

IMFWorkQueueServices_RemoteEndUnregisterPlatformWorkQueueWithMMCSS_Proxy proto __cdecl :ptr, :ptr

IMFWorkQueueServices_RemoteEndUnregisterPlatformWorkQueueWithMMCSS_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

DEFINE_GUID( MF_WORKQUEUE_SERVICES, 0x8e37d489, 0x41e0, 0x413a, 0x90, 0x68, 0x28, 0x7c, 0x88, 0x6d, 0x8d, 0xda);

ifndef __IMFWorkQueueServicesEx_INTERFACE_DEFINED__
__IMFWorkQueueServicesEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFWorkQueueServicesEx, "96bf961b-40fe-42f1-ba9d-320238b49700")

.comdef IMFWorkQueueServicesEx : public IMFWorkQueueServices

    GetTopologyWorkQueueMMCSSPriority proc :DWORD, :ptr
    BeginRegisterPlatformWorkQueueWithMMCSSEx proc :DWORD, :LPCWSTR, :DWORD, :LONG, :ptr, :ptr
    GetPlatformWorkQueueMMCSSPriority proc :DWORD, :ptr
    .ends

IMFWorkQueueServicesEx_RemoteBeginRegisterPlatformWorkQueueWithMMCSSEx_Proxy proto __cdecl :ptr, :dword, :ptr, :dword, :ptr, :ptr

IMFWorkQueueServicesEx_RemoteBeginRegisterPlatformWorkQueueWithMMCSSEx_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MF_QUALITY_DROP_MODE {
    MF_DROP_MODE_NONE	= 0,
    MF_DROP_MODE_1	= 0x1,
    MF_DROP_MODE_2	= 0x2,
    MF_DROP_MODE_3	= 0x3,
    MF_DROP_MODE_4	= 0x4,
    MF_DROP_MODE_5	= 0x5,
    MF_NUM_DROP_MODES	= 0x6
    }

.enum MF_QUALITY_LEVEL {
    MF_QUALITY_NORMAL	= 0,
    MF_QUALITY_NORMAL_MINUS_1	= 0x1,
    MF_QUALITY_NORMAL_MINUS_2	= 0x2,
    MF_QUALITY_NORMAL_MINUS_3	= 0x3,
    MF_QUALITY_NORMAL_MINUS_4	= 0x4,
    MF_QUALITY_NORMAL_MINUS_5	= 0x5,
    MF_NUM_QUALITY_LEVELS	= 0x6
    }

endif

if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MF_QUALITY_ADVISE_FLAGS {
    MF_QUALITY_CANNOT_KEEP_UP	= 0x1
    }

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFQualityManager_INTERFACE_DEFINED__
__IMFQualityManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFQualityManager, "8D009D86-5B9F-4115-B1FC-9F80D52AB8AB")

.comdef IMFQualityManager : public IUnknown

    NotifyTopology	proc :ptr
    NotifyPresentationClock proc :ptr
    NotifyProcessInput	proc :ptr, :LONG, :ptr
    NotifyProcessOutput proc :ptr, :LONG, :ptr
    NotifyQualityEvent	proc :ptr, :ptr
    Shutdown		proc
    .ends

endif

MFCreateStandardQualityManager proto __cdecl \
      ppQualityManager: ptr IMFQualityManager

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
DEFINE_GUID( MF_QUALITY_NOTIFY_PROCESSING_LATENCY, 0xf6b44af8, 0x604d, 0x46fe, 0xa9, 0x5d, 0x45, 0x47, 0x9b, 0x10, 0xc9, 0xbc );
DEFINE_GUID( MF_QUALITY_NOTIFY_SAMPLE_LAG, 0x30d15206, 0xed2a, 0x4760, 0xbe, 0x17, 0xeb, 0x4a, 0x9f, 0x12, 0x29, 0x5c );

ifndef __IMFQualityAdvise_INTERFACE_DEFINED__
__IMFQualityAdvise_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFQualityAdvise, "EC15E2E9-E36B-4f7c-8758-77D452EF4CE7")

.comdef IMFQualityAdvise : public IUnknown

    SetDropMode		proc :MF_QUALITY_DROP_MODE
    SetQualityLevel	proc :MF_QUALITY_LEVEL
    GetDropMode		proc :ptr
    GetQualityLevel	proc :ptr
    DropTime		proc :LONGLONG
    .ends

endif
endif

if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFQualityAdvise2_INTERFACE_DEFINED__
__IMFQualityAdvise2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFQualityAdvise2, "F3706F0D-8EA2-4886-8000-7155E9EC2EAE")

.comdef IMFQualityAdvise2 : public IMFQualityAdvise

    NotifyQualityEvent	proc :ptr, :ptr
    .ends

endif

ifndef __IMFQualityAdviseLimits_INTERFACE_DEFINED__
__IMFQualityAdviseLimits_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFQualityAdviseLimits, "dfcd8e4d-30b5-4567-acaa-8eb5b7853dc9")

.comdef IMFQualityAdviseLimits : public IUnknown

    GetMaximumDropMode	proc :ptr
    GetMinimumQualityLevel proc :ptr
    .ends

endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFRealTimeClient_INTERFACE_DEFINED__
__IMFRealTimeClient_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFRealTimeClient, "2347D60B-3FB5-480c-8803-8DF3ADCD3EF0")

.comdef IMFRealTimeClient : public IUnknown

    RegisterThreads	proc :DWORD, :LPCWSTR
    UnregisterThreads	proc
    SetWorkQueue	proc :DWORD
    .ends

endif
endif

if (WINVER GE _WIN32_WINNT_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __IMFRealTimeClientEx_INTERFACE_DEFINED__
__IMFRealTimeClientEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFRealTimeClientEx, "03910848-AB16-4611-B100-17B88AE2F248")

.comdef IMFRealTimeClientEx : public IUnknown

    RegisterThreadsEx	proc :ptr, :LPCWSTR, :LONG
    UnregisterThreads	proc
    SetWorkQueueEx	proc :DWORD, :LONG
    .ends

endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
MFSequencerElementId	typedef DWORD

MFSEQUENCER_INVALID_ELEMENT_ID equ ( 0xffffffff )

.enum MFSequencerTopologyFlags {
    SequencerTopologyFlags_Last = 0x1
    }

ifndef __IMFSequencerSource_INTERFACE_DEFINED__
__IMFSequencerSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSequencerSource, "197CD219-19CB-4de1-A64C-ACF2EDCBE59E")

.comdef IMFSequencerSource : public IUnknown

    AppendTopology	proc :ptr, :DWORD, :ptr
    DeleteTopology	proc :MFSequencerElementId
    GetPresentationContext proc :ptr, :ptr, :ptr
    UpdateTopology	proc :MFSequencerElementId, :ptr
    UpdateTopologyFlags proc :MFSequencerElementId, :DWORD
    .ends

endif

DEFINE_GUID( MF_TIME_FORMAT_SEGMENT_OFFSET, 0xc8b8be77, 0x869c, 0x431d, 0x81, 0x2e, 0x16, 0x96, 0x93, 0xf6, 0x5a, 0x39 );

MFCreateSequencerSource proto __cdecl \
	     pReserved: ptr IUnknown,
     ppSequencerSource: ptr IMFSequencerSource

MFCreateSequencerSegmentOffset proto __cdecl \
		  dwId: MFSequencerElementId,
	     hnsOffset: MFTIME,
     pvarSegmentOffset: ptr PROPVARIANT

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
if (WINVER GE _WIN32_WINNT_WIN7)

MFCreateAggregateSource proto __cdecl \
     pSourceCollection: ptr IMFCollection,
	   ppAggSource: ptr IMFMediaSource

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFMediaSourceTopologyProvider_INTERFACE_DEFINED__
__IMFMediaSourceTopologyProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaSourceTopologyProvider, "0E1D6009-C9F3-442d-8C51-A42D2D49452F")

.comdef IMFMediaSourceTopologyProvider : public IUnknown

    GetMediaSourceTopology proc :ptr, :ptr
    .ends

endif

ifndef __IMFMediaSourcePresentationProvider_INTERFACE_DEFINED__
__IMFMediaSourcePresentationProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaSourcePresentationProvider, "0E1D600a-C9F3-442d-8C51-A42D2D49452F")

.comdef IMFMediaSourcePresentationProvider : public IUnknown

    ForceEndOfPresentation proc :ptr
    .ends

endif

DEFINE_GUID( MF_SOURCE_PRESENTATION_PROVIDER_SERVICE, 0xe002aadc, 0xf4af, 0x4ee5, 0x98, 0x47, 0x05, 0x3e, 0xdf, 0x84, 0x04, 0x26 );

MFTOPONODE_ATTRIBUTE_UPDATE STRUC
NodeId			TOPOID ?
guidAttributeKey	GUID <>
attrType		MF_ATTRIBUTE_TYPE ?
UNION
 u32			UINT32 ?
 u64			UINT64 ?
 d			real8 ?
ENDS
MFTOPONODE_ATTRIBUTE_UPDATE ENDS

ifndef __IMFTopologyNodeAttributeEditor_INTERFACE_DEFINED__
__IMFTopologyNodeAttributeEditor_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTopologyNodeAttributeEditor, "676aa6dd-238a-410d-bb99-65668d01605a")

.comdef IMFTopologyNodeAttributeEditor : public IUnknown

    UpdateNodeAttributes proc :TOPOID, :DWORD, :ptr
    .ends

endif

DEFINE_GUID( MF_TOPONODE_ATTRIBUTE_EDITOR_SERVICE, 0x65656e1a, 0x077f, 0x4472, 0x83, 0xef, 0x31, 0x6f, 0x11, 0xd5, 0x08, 0x7a );
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MF_LEAKY_BUCKET_PAIR	STRUC
dwBitrate		dd ?
msBufferWindow		dd ?
MF_LEAKY_BUCKET_PAIR	ENDS
LPMF_LEAKY_BUCKET_PAIR	typedef ptr MF_LEAKY_BUCKET_PAIR
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MFBYTESTREAM_BUFFERING_PARAMS STRUC
cbTotalFileSize		dq ?
cbPlayableDataSize	dq ?
prgBuckets		LPMF_LEAKY_BUCKET_PAIR ?
cBuckets		dd ?
qwNetBufferingTime	dq ?
qwExtraBufferingTimeDuringSeek QWORD ?
qwPlayDuration		dq ?
dRate			real4 ?
MFBYTESTREAM_BUFFERING_PARAMS ENDS

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __IMFByteStreamBuffering_INTERFACE_DEFINED__
__IMFByteStreamBuffering_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFByteStreamBuffering, "6d66d782-1d4f-4db7-8c63-cb8c77f1ef5e")

.comdef IMFByteStreamBuffering : public IUnknown

    SetBufferingParams	proc :ptr
    EnableBuffering	proc :BOOL
    StopBuffering	proc
    .ends

endif

ifndef __IMFByteStreamCacheControl_INTERFACE_DEFINED__
__IMFByteStreamCacheControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFByteStreamCacheControl, "F5042EA4-7A96-4a75-AA7B-2BE1EF7F88D5")

.comdef IMFByteStreamCacheControl : public IUnknown

    StopBackgroundTransfer proc
    .ends

endif

ifndef __IMFByteStreamTimeSeek_INTERFACE_DEFINED__
__IMFByteStreamTimeSeek_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFByteStreamTimeSeek, "64976BFA-FB61-4041-9069-8C9A5F659BEB")

.comdef IMFByteStreamTimeSeek : public IUnknown

    IsTimeSeekSupported proc :ptr
    TimeSeek		proc :QWORD
    GetTimeSeekResult	proc :ptr, :ptr, :ptr
    .ends

endif

if (WINVER GE _WIN32_WINNT_WIN8)
qwStartOffset		typedef	 struct __MIDL___MIDL_itf_mfidl_0000_0054_0001 { QWORD
qwEndOffset		QWORD ?
MF_BYTE_STREAM_CACHE_RANGE ENDS

ifndef __IMFByteStreamCacheControl2_INTERFACE_DEFINED__
__IMFByteStreamCacheControl2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFByteStreamCacheControl2, "71CE469C-F34B-49EA-A56B-2D2A10E51149")

.comdef IMFByteStreamCacheControl2 : public IMFByteStreamCacheControl

    GetByteRanges	proc :ptr, :ptr
    SetCacheLimit	proc :QWORD
    IsBackgroundTransferActive proc :ptr
    .ends

endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFNetCredential_INTERFACE_DEFINED__
__IMFNetCredential_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFNetCredential, "5b87ef6a-7ed8-434f-ba0e-184fac1628d1")

.comdef IMFNetCredential : public IUnknown

    SetUser		proc
    SetPassword		proc
    GetUser		proc :ptr, :ptr, :BOOL
    GetPassword		proc :ptr, :ptr, :BOOL
    LoggedOnUser	proc :ptr
    .ends

endif

ifndef __IMFNetCredentialManager_INTERFACE_DEFINED__
__IMFNetCredentialManager_INTERFACE_DEFINED__ equ 1

MFNetCredentialManagerGetParam STRUC
hrOp			HRESULT ?
fAllowLoggedOnUser	BOOL ?
fClearTextPackage	BOOL ?
pszUrl			LPCWSTR ?
pszSite			LPCWSTR ?
pszRealm		LPCWSTR ?
pszPackage		LPCWSTR ?
nRetries		LONG ?
MFNetCredentialManagerGetParam ENDS

DEFINE_IIDX(IMFNetCredentialManager, "5b87ef6b-7ed8-434f-ba0e-184fac1628d1")

.comdef IMFNetCredentialManager : public IUnknown

    BeginGetCredentials proc :ptr, :ptr, :ptr
    EndGetCredentials	proc :ptr, :ptr
    SetGood		proc :ptr, :BOOL
    .ends

endif

ifndef __IMFNetCredentialCache_INTERFACE_DEFINED__
__IMFNetCredentialCache_INTERFACE_DEFINED__ equ 1

.enum MFNetCredentialRequirements {
    REQUIRE_PROMPT	= 0x1,
    REQUIRE_SAVE_SELECTED	= 0x2
    }

.enum MFNetCredentialOptions {
    MFNET_CREDENTIAL_SAVE	= 0x1,
    MFNET_CREDENTIAL_DONT_CACHE = 0x2,
    MFNET_CREDENTIAL_ALLOW_CLEAR_TEXT	= 0x4
    }

.enum MFNetAuthenticationFlags {
    MFNET_AUTHENTICATION_PROXY	= 0x1,
    MFNET_AUTHENTICATION_CLEAR_TEXT = 0x2,
    MFNET_AUTHENTICATION_LOGGED_ON_USER = 0x4
    }

DEFINE_IIDX(IMFNetCredentialCache, "5b87ef6c-7ed8-434f-ba0e-184fac1628d1")

.comdef IMFNetCredentialCache : public IUnknown

    GetCredential	proc :LPCWSTR, :LPCWSTR, :DWORD, :ptr, :ptr
    SetGood		proc :ptr, :BOOL
    SetUserOptions	proc :ptr, :DWORD
    .ends

endif

MFCreateCredentialCache proto __cdecl \
	       ppCache: ptr ptr

endif

if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFSSLCertificateManager_INTERFACE_DEFINED__
__IMFSSLCertificateManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSSLCertificateManager, "61f7d887-1230-4a8b-aeba-8ad434d1a64d")

.comdef IMFSSLCertificateManager : public IUnknown

    GetClientCertificate proc :LPCWSTR, :ptr, :ptr
    BeginGetClientCertificate proc :LPCWSTR, :ptr, :ptr
    EndGetClientCertificate proc :ptr, :ptr, :ptr
    GetCertificatePolicy proc :LPCWSTR, :ptr, :ptr
    OnServerCertificate proc :LPCWSTR
    .ends

endif

DEFINE_GUID( MFNETSOURCE_SSLCERTIFICATE_MANAGER, 0x55e6cb27, 0xe69b, 0x4267, 0x94, 0x0c, 0x2d, 0x7e, 0xc5, 0xbb, 0x8a, 0x0f );

ifndef __IMFNetResourceFilter_INTERFACE_DEFINED__
__IMFNetResourceFilter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFNetResourceFilter, "091878a3-bf11-4a5c-bc9f-33995b06ef2d")

.comdef IMFNetResourceFilter : public IUnknown

    OnRedirect		proc :LPCWSTR, :ptr
    OnSendingRequest	proc :LPCWSTR
    .ends

endif

DEFINE_GUID( MFNETSOURCE_RESOURCE_FILTER, 0x815d0ff6, 0x265a, 0x4477, 0x9e, 0x46, 0x7b, 0x80, 0xad, 0x80, 0xb5, 0xfb);
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFSourceOpenMonitor_INTERFACE_DEFINED__
__IMFSourceOpenMonitor_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSourceOpenMonitor, "059054B3-027C-494C-A27D-9113291CF87F")

.comdef IMFSourceOpenMonitor : public IUnknown

    OnSourceEvent	proc :ptr
    .ends

endif

ifndef __IMFNetProxyLocator_INTERFACE_DEFINED__
__IMFNetProxyLocator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFNetProxyLocator, "e9cd0383-a268-4bb4-82de-658d53574d41")

.comdef IMFNetProxyLocator : public IUnknown

    FindFirstProxy	proc :LPCWSTR, :LPCWSTR, :BOOL
    FindNextProxy	proc
    RegisterProxyResult proc :HRESULT
    GetCurrentProxy	proc
    Clone		proc :ptr
    .ends

endif

MFCreateProxyLocator proto __cdecl \
	   pszProtocol: LPCWSTR,
	  pProxyConfig: ptr IPropertyStore,
	ppProxyLocator: ptr ptr IMFNetProxyLocator

ifndef __IMFNetProxyLocatorFactory_INTERFACE_DEFINED__
__IMFNetProxyLocatorFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFNetProxyLocatorFactory, "e9cd0384-a268-4bb4-82de-658d53574d41")

.comdef IMFNetProxyLocatorFactory : public IUnknown

    CreateProxyLocator	proc :LPCWSTR, :ptr
    .ends

endif

ifndef __IMFSaveJob_INTERFACE_DEFINED__
__IMFSaveJob_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSaveJob, "e9931663-80bf-4c6e-98af-5dcf58747d1f")

.comdef IMFSaveJob : public IUnknown

    BeginSave		proc :ptr, :ptr, :ptr
    EndSave		proc :ptr
    CancelSave		proc
    GetProgress		proc :ptr
    .ends

endif

DEFINE_GUID( MFNET_SAVEJOB_SERVICE, 0xb85a587f, 0x3d02, 0x4e52, 0x95, 0x65, 0x55, 0xd3, 0xec, 0x1e, 0x7f, 0xf7 );

.enum MFNETSOURCE_PROTOCOL_TYPE {
    MFNETSOURCE_UNDEFINED	= 0,
    MFNETSOURCE_HTTP	= 0x1,
    MFNETSOURCE_RTSP	= 0x2,
    MFNETSOURCE_FILE	= 0x3,
    MFNETSOURCE_MULTICAST	= 0x4
    }

ifndef __IMFNetSchemeHandlerConfig_INTERFACE_DEFINED__
__IMFNetSchemeHandlerConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFNetSchemeHandlerConfig, "7BE19E73-C9BF-468a-AC5A-A5E8653BEC87")

.comdef IMFNetSchemeHandlerConfig : public IUnknown

    GetNumberOfSupportedProtocols proc :ptr
    GetSupportedProtocolType proc :ULONG, :ptr
    ResetProtocolRolloverSettings proc
    .ends

endif

MFCreateNetSchemePlugin proto __cdecl \
		  riid: REFIID,
	    ppvHandler: ptr LPVOID

.enum MFNETSOURCE_TRANSPORT_TYPE {
    MFNETSOURCE_UDP = 0,
    MFNETSOURCE_TCP = ( MFNETSOURCE_UDP + 1 )
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MFNETSOURCE_CACHE_STATE {
    MFNETSOURCE_CACHE_UNAVAILABLE	= 0,
    MFNETSOURCE_CACHE_ACTIVE_WRITING	= ( MFNETSOURCE_CACHE_UNAVAILABLE + 1 ) ,
    MFNETSOURCE_CACHE_ACTIVE_COMPLETE	= ( MFNETSOURCE_CACHE_ACTIVE_WRITING + 1 )
    }

.enum MFNETSOURCE_STATISTICS_IDS {
    MFNETSOURCE_RECVPACKETS_ID	= 0,
    MFNETSOURCE_LOSTPACKETS_ID	= ( MFNETSOURCE_RECVPACKETS_ID + 1 ) ,
    MFNETSOURCE_RESENDSREQUESTED_ID = ( MFNETSOURCE_LOSTPACKETS_ID + 1 ) ,
    MFNETSOURCE_RESENDSRECEIVED_ID	= ( MFNETSOURCE_RESENDSREQUESTED_ID + 1 ) ,
    MFNETSOURCE_RECOVEREDBYECCPACKETS_ID	= ( MFNETSOURCE_RESENDSRECEIVED_ID + 1 ) ,
    MFNETSOURCE_RECOVEREDBYRTXPACKETS_ID	= ( MFNETSOURCE_RECOVEREDBYECCPACKETS_ID + 1 ) ,
    MFNETSOURCE_OUTPACKETS_ID	= ( MFNETSOURCE_RECOVEREDBYRTXPACKETS_ID + 1 ) ,
    MFNETSOURCE_RECVRATE_ID = ( MFNETSOURCE_OUTPACKETS_ID + 1 ) ,
    MFNETSOURCE_AVGBANDWIDTHBPS_ID	= ( MFNETSOURCE_RECVRATE_ID + 1 ) ,
    MFNETSOURCE_BYTESRECEIVED_ID	= ( MFNETSOURCE_AVGBANDWIDTHBPS_ID + 1 ) ,
    MFNETSOURCE_PROTOCOL_ID = ( MFNETSOURCE_BYTESRECEIVED_ID + 1 ) ,
    MFNETSOURCE_TRANSPORT_ID	= ( MFNETSOURCE_PROTOCOL_ID + 1 ) ,
    MFNETSOURCE_CACHE_STATE_ID	= ( MFNETSOURCE_TRANSPORT_ID + 1 ) ,
    MFNETSOURCE_LINKBANDWIDTH_ID	= ( MFNETSOURCE_CACHE_STATE_ID + 1 ) ,
    MFNETSOURCE_CONTENTBITRATE_ID	= ( MFNETSOURCE_LINKBANDWIDTH_ID + 1 ) ,
    MFNETSOURCE_SPEEDFACTOR_ID	= ( MFNETSOURCE_CONTENTBITRATE_ID + 1 ) ,
    MFNETSOURCE_BUFFERSIZE_ID	= ( MFNETSOURCE_SPEEDFACTOR_ID + 1 ) ,
    MFNETSOURCE_BUFFERPROGRESS_ID	= ( MFNETSOURCE_BUFFERSIZE_ID + 1 ) ,
    MFNETSOURCE_LASTBWSWITCHTS_ID	= ( MFNETSOURCE_BUFFERPROGRESS_ID + 1 ) ,
    MFNETSOURCE_SEEKRANGESTART_ID	= ( MFNETSOURCE_LASTBWSWITCHTS_ID + 1 ) ,
    MFNETSOURCE_SEEKRANGEEND_ID = ( MFNETSOURCE_SEEKRANGESTART_ID + 1 ) ,
    MFNETSOURCE_BUFFERINGCOUNT_ID	= ( MFNETSOURCE_SEEKRANGEEND_ID + 1 ) ,
    MFNETSOURCE_INCORRECTLYSIGNEDPACKETS_ID = ( MFNETSOURCE_BUFFERINGCOUNT_ID + 1 ) ,
    MFNETSOURCE_SIGNEDSESSION_ID	= ( MFNETSOURCE_INCORRECTLYSIGNEDPACKETS_ID + 1 ) ,
    MFNETSOURCE_MAXBITRATE_ID	= ( MFNETSOURCE_SIGNEDSESSION_ID + 1 ) ,
    MFNETSOURCE_RECEPTION_QUALITY_ID	= ( MFNETSOURCE_MAXBITRATE_ID + 1 ) ,
    MFNETSOURCE_RECOVEREDPACKETS_ID = ( MFNETSOURCE_RECEPTION_QUALITY_ID + 1 ) ,
    MFNETSOURCE_VBR_ID	= ( MFNETSOURCE_RECOVEREDPACKETS_ID + 1 ) ,
    MFNETSOURCE_DOWNLOADPROGRESS_ID = ( MFNETSOURCE_VBR_ID + 1 ) ,
    MFNETSOURCE_UNPREDEFINEDPROTOCOLNAME_ID = ( MFNETSOURCE_DOWNLOADPROGRESS_ID + 1 )
    }

DEFINE_GUID( MFNETSOURCE_STATISTICS_SERVICE, 0x3cb1f275, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_STATISTICS, 0x3cb1f274, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
DEFINE_GUID( MFNETSOURCE_BUFFERINGTIME, 0x3cb1f276, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ACCELERATEDSTREAMINGDURATION, 0x3cb1f277, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_MAXUDPACCELERATEDSTREAMINGDURATION, 0x4aab2879, 0xbbe1, 0x4994, 0x9f, 0xf0, 0x54, 0x95, 0xbd, 0x25, 0x1, 0x29 );
DEFINE_GUID( MFNETSOURCE_MAXBUFFERTIMEMS, 0x408b24e6, 0x4038, 0x4401, 0xb5, 0xb2, 0xfe, 0x70, 0x1a, 0x9e, 0xbf, 0x10 );
DEFINE_GUID( MFNETSOURCE_CONNECTIONBANDWIDTH, 0x3cb1f278, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_CACHEENABLED, 0x3cb1f279, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_AUTORECONNECTLIMIT, 0x3cb1f27a, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_RESENDSENABLED, 0x3cb1f27b, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_THINNINGENABLED, 0x3cb1f27c, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PROTOCOL, 0x3cb1f27d, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_TRANSPORT, 0x3cb1f27e, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID( MFNETSOURCE_PREVIEWMODEENABLED, 0x3cb1f27f, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
endif
DEFINE_GUID( MFNETSOURCE_CREDENTIAL_MANAGER, 0x3cb1f280, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PPBANDWIDTH, 0x3cb1f281, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_AUTORECONNECTPROGRESS, 0x3cb1f282, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PROXYLOCATORFACTORY, 0x3cb1f283, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_BROWSERUSERAGENT, 0x3cb1f28b, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_BROWSERWEBPAGE, 0x3cb1f28c, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PLAYERVERSION, 0x3cb1f28d, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PLAYERID, 0x3cb1f28e, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_HOSTEXE, 0x3cb1f28f, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_HOSTVERSION, 0x3cb1f291, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PLAYERUSERAGENT, 0x3cb1f292, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID( MFNETSOURCE_CLIENTGUID, 0x60a2c4a6, 0xf197, 0x4c14, 0xa5, 0xbf, 0x88, 0x83, 0xd, 0x24, 0x58, 0xaf );
endif
DEFINE_GUID( MFNETSOURCE_LOGURL, 0x3cb1f293, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ENABLE_UDP, 0x3cb1f294, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ENABLE_TCP, 0x3cb1f295, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ENABLE_MSB, 0x3cb1f296, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ENABLE_RTSP, 0x3cb1f298, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ENABLE_HTTP, 0x3cb1f299, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ENABLE_STREAMING, 0x3cb1f29c, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ENABLE_DOWNLOAD, 0x3cb1f29d, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_ENABLE_PRIVATEMODE, 0x824779d8, 0xf18b, 0x4405, 0x8c, 0xf1, 0x46, 0x4f, 0xb5, 0xaa, 0x8f, 0x71 );
DEFINE_GUID( MFNETSOURCE_UDP_PORT_RANGE, 0x3cb1f29a, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PROXYINFO, 0x3cb1f29b, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_DRMNET_LICENSE_REPRESENTATION, 0x47eae1bd, 0xbdfe, 0x42e2, 0x82, 0xf3, 0x54, 0xa4, 0x8c, 0x17, 0x96, 0x2d );
DEFINE_GUID( MFNETSOURCE_PROXYSETTINGS, 0x3cb1f287, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PROXYHOSTNAME, 0x3cb1f284, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PROXYPORT, 0x3cb1f288, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PROXYEXCEPTIONLIST, 0x3cb1f285, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PROXYBYPASSFORLOCAL, 0x3cb1f286, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
DEFINE_GUID( MFNETSOURCE_PROXYRERUNAUTODETECTION, 0x3cb1f289, 0x0505, 0x4c5d, 0xae, 0x71, 0x0a, 0x55, 0x63, 0x44, 0xef, 0xa1 );
if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID( MFNETSOURCE_STREAM_LANGUAGE, 0x9ab44318, 0xf7cd, 0x4f2d, 0x8d, 0x6d, 0xfa, 0x35, 0xb4, 0x92, 0xce, 0xcb );
DEFINE_GUID( MFNETSOURCE_LOGPARAMS, 0x64936ae8, 0x9418, 0x453a, 0x8c, 0xda, 0x3e, 0xa, 0x66, 0x8b, 0x35, 0x3b );
endif
if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_GUID( MFNETSOURCE_PEERMANAGER, 0x48b29adb, 0xfebf, 0x45ee, 0xa9, 0xbf, 0xef, 0xb8, 0x1c, 0x49, 0x2e, 0xfc );
DEFINE_GUID( MFNETSOURCE_FRIENDLYNAME, 0x5b2a7757, 0xbc6b, 0x447e, 0xaa, 0x06, 0x0d, 0xda, 0x1c, 0x64, 0x6e, 0x2f );
endif

.enum MFNET_PROXYSETTINGS {
    MFNET_PROXYSETTING_NONE = 0,
    MFNET_PROXYSETTING_MANUAL	= 1,
    MFNET_PROXYSETTING_AUTO = 2,
    MFNET_PROXYSETTING_BROWSER	= 3
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFSchemeHandler_INTERFACE_DEFINED__
__IMFSchemeHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSchemeHandler, "6D4C7B74-52A0-4bb7-B0DB-55F29F47A668")

.comdef IMFSchemeHandler : public IUnknown

    BeginCreateObject	proc :LPCWSTR, :DWORD, :ptr, :ptr, :ptr, :ptr
    EndCreateObject	proc :ptr, :ptr, :ptr
    CancelObjectCreation proc :ptr
    .ends

endif

if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID(MF_BYTESTREAMHANDLER_ACCEPTS_SHARE_WRITE, 0xa6e1f733, 0x3001, 0x4915, 0x81, 0x50, 0x15, 0x58, 0xa2, 0x18, 0xe, 0xc8);
endif

ifndef __IMFByteStreamHandler_INTERFACE_DEFINED__
__IMFByteStreamHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFByteStreamHandler, "BB420AA4-765B-4a1f-91FE-D6A8A143924C")

.comdef IMFByteStreamHandler : public IUnknown

    BeginCreateObject	proc :ptr, :LPCWSTR, :DWORD, :ptr, :ptr, :ptr, :ptr
    EndCreateObject	proc :ptr, :ptr, :ptr
    CancelObjectCreation proc :ptr
    GetMaxNumberOfBytesRequiredForResolution proc :ptr
    .ends

endif

DEFINE_GUID( MF_BYTESTREAM_SERVICE, 0xab025e2b, 0x16d9, 0x4180, 0xa1, 0x27, 0xba, 0x6c, 0x70, 0x15, 0x61, 0x61 );

ifndef __IMFTrustedInput_INTERFACE_DEFINED__
__IMFTrustedInput_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTrustedInput, "542612C4-A1B8-4632-B521-DE11EA64A0B0")

.comdef IMFTrustedInput : public IUnknown

    GetInputTrustAuthority proc :DWORD, :REFIID, :ptr
    .ends

endif

.enum MFPOLICYMANAGER_ACTION {
    PEACTION_NO = 0,
    PEACTION_PLAY	= 1,
    PEACTION_COPY	= 2,
    PEACTION_EXPORT = 3,
    PEACTION_EXTRACT	= 4,
    PEACTION_RESERVED1	= 5,
    PEACTION_RESERVED2	= 6,
    PEACTION_RESERVED3	= 7,
    PEACTION_LAST	= 7
    }

MFINPUTTRUSTAUTHORITY_ACCESS_ACTION STRUC
Action			MFPOLICYMANAGER_ACTION ?
pbTicket		LPBYTE ?
cbTicket		dd ?
MFINPUTTRUSTAUTHORITY_ACCESS_ACTION ENDS

MFINPUTTRUSTAUTHORITY_ACCESS_PARAMS STRUC
dwSize			dd ?
dwVer			dd ?
cbSignatureOffset	dd ?
cbSignatureSize		dd ?
cbExtensionOffset	dd ?
cbExtensionSize		dd ?
cActions		dd ?
rgOutputActions		MFINPUTTRUSTAUTHORITY_ACCESS_ACTION  1	dup(<>)
MFINPUTTRUSTAUTHORITY_ACCESS_PARAMS ENDS

ifndef __IMFInputTrustAuthority_INTERFACE_DEFINED__
__IMFInputTrustAuthority_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFInputTrustAuthority, "D19F8E98-B126-4446-890C-5DCB7AD71453")

.comdef IMFInputTrustAuthority : public IUnknown

    GetDecrypter	proc :REFIID, :ptr
    RequestAccess	proc :MFPOLICYMANAGER_ACTION, :ptr
    GetPolicy		proc :MFPOLICYMANAGER_ACTION, :ptr
    BindAccess		proc :ptr
    UpdateAccess	proc :ptr
    Reset		proc
    .ends

endif

ifndef __IMFTrustedOutput_INTERFACE_DEFINED__
__IMFTrustedOutput_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTrustedOutput, "D19F8E95-B126-4446-890C-5DCB7AD71453")

.comdef IMFTrustedOutput : public IUnknown

    GetOutputTrustAuthorityCount proc :ptr
    GetOutputTrustAuthorityByIndex proc :DWORD, :ptr
    IsFinal		proc :ptr
    .ends

endif

ifndef __IMFOutputTrustAuthority_INTERFACE_DEFINED__
__IMFOutputTrustAuthority_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFOutputTrustAuthority, "D19F8E94-B126-4446-890C-5DCB7AD71453")

.comdef IMFOutputTrustAuthority : public IUnknown

    GetAction		proc :ptr
    SetPolicy		proc
    .ends

endif

ifndef __IMFOutputPolicy_INTERFACE_DEFINED__
__IMFOutputPolicy_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFOutputPolicy, "7F00F10A-DAED-41AF-AB26-5FDFA4DFBA3C")

.comdef IMFOutputPolicy : public IMFAttributes

    GenerateRequiredSchemas proc :DWORD, :GUID, :ptr, :DWORD, :ptr
    GetOriginatorID	proc :ptr
    GetMinimumGRLVersion proc :ptr
    .ends

endif

MFOUTPUTATTRIBUTE_DIGITAL equ ( 0x00000001)
MFOUTPUTATTRIBUTE_NONSTANDARDIMPLEMENTATION equ ( 0x00000002)
MFOUTPUTATTRIBUTE_VIDEO equ ( 0x00000004)
MFOUTPUTATTRIBUTE_COMPRESSED equ ( 0x00000008)
MFOUTPUTATTRIBUTE_SOFTWARE equ ( 0x00000010)
MFOUTPUTATTRIBUTE_BUS	equ ( 0x00000020)
MFOUTPUTATTRIBUTE_BUSIMPLEMENTATION equ ( 0x0000FF00)
DEFINE_GUID( MFCONNECTOR_SPDIF, 0xb94a712, 0xad3e, 0x4cee, 0x83, 0xce, 0xce, 0x32, 0xe3, 0xdb, 0x65, 0x22);

DEFINE_GUID( MFCONNECTOR_UNKNOWN, 0xac3aef5c, 0xce43, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_PCI, 0xac3aef5d, 0xce43, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_PCIX, 0xac3aef5e, 0xce43, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_PCI_Express, 0xac3aef5f, 0xce43, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_AGP, 0xac3aef60, 0xce43, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);


DEFINE_GUID( MFCONNECTOR_VGA, 0x57cd5968, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_SVIDEO, 0x57cd5969, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_COMPOSITE, 0x57cd596a, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_COMPONENT, 0x57cd596b, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_DVI, 0x57cd596c, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_HDMI, 0x57cd596d, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_LVDS, 0x57cd596e, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_D_JPN, 0x57cd5970, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_SDI, 0x57cd5971, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_DISPLAYPORT_EXTERNAL, 0x57cd5972, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_DISPLAYPORT_EMBEDDED, 0x57cd5973, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_UDI_EXTERNAL, 0x57cd5974, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_UDI_EMBEDDED, 0x57cd5975, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);
DEFINE_GUID( MFCONNECTOR_MIRACAST, 0x57cd5977, 0xce47, 0x11d9, 0x92, 0xdb, 0x00, 0x0b, 0xdb, 0x28, 0xff, 0x98);

ifndef __IMFOutputSchema_INTERFACE_DEFINED__
__IMFOutputSchema_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFOutputSchema, "7BE0FC5B-ABD9-44FB-A5C8-F50136E71599")

.comdef IMFOutputSchema : public IMFAttributes

    GetSchemaType	proc :ptr
    GetConfigurationData proc :ptr
    GetOriginatorID	proc :ptr
    .ends

endif

DEFINE_GUID( MFPROTECTION_DISABLE, 0x8cc6d81b, 0xfec6, 0x4d8f, 0x96, 0x4b, 0xcf, 0xba, 0x0b, 0x0d, 0xad, 0x0d);
DEFINE_GUID( MFPROTECTION_CONSTRICTVIDEO, 0x193370ce, 0xc5e4, 0x4c3a, 0x8a, 0x66, 0x69, 0x59, 0xb4, 0xda, 0x44, 0x42);
DEFINE_GUID( MFPROTECTION_CONSTRICTVIDEO_NOOPM, 0xa580e8cd, 0xc247, 0x4957, 0xb9, 0x83, 0x3c, 0x2e, 0xeb, 0xd1, 0xff, 0x59);
DEFINE_GUID( MFPROTECTION_CONSTRICTAUDIO, 0xffc99b44, 0xdf48, 0x4e16, 0x8e, 0x66, 0x09, 0x68, 0x92, 0xc1, 0x57, 0x8a);
DEFINE_GUID( MFPROTECTION_TRUSTEDAUDIODRIVERS, 0x65bdf3d2, 0x0168, 0x4816, 0xa5, 0x33, 0x55, 0xd4, 0x7b, 0x02, 0x71, 0x01);
DEFINE_GUID( MFPROTECTION_HDCP, 0xAE7CC03D, 0xC828, 0x4021, 0xac, 0xb7, 0xd5, 0x78, 0xd2, 0x7a, 0xaf, 0x13);
DEFINE_GUID( MFPROTECTION_CGMSA, 0xE57E69E9, 0x226B, 0x4d31, 0xB4, 0xE3, 0xD3, 0xDB, 0x00, 0x87, 0x36, 0xDD);
DEFINE_GUID( MFPROTECTION_ACP, 0xc3fd11c6, 0xf8b7, 0x4d20, 0xb0, 0x08, 0x1d, 0xb1, 0x7d, 0x61, 0xf2, 0xda);
DEFINE_GUID( MFPROTECTION_WMDRMOTA, 0xa267a6a1, 0x362e, 0x47d0, 0x88, 0x05, 0x46, 0x28, 0x59, 0x8a, 0x23, 0xe4);
DEFINE_GUID( MFPROTECTION_FFT, 0x462a56b2, 0x2866, 0x4bb6, 0x98, 0x0d, 0x6d, 0x8d, 0x9e, 0xdb, 0x1a, 0x8c);
DEFINE_GUID( MFPROTECTION_PROTECTED_SURFACE, 0x4f5d9566, 0xe742, 0x4a25, 0x8d, 0x1f, 0xd2, 0x87, 0xb5, 0xfa, 0x0a, 0xde);
DEFINE_GUID( MFPROTECTION_DISABLE_SCREEN_SCRAPE, 0xa21179a4, 0xb7cd, 0x40d8, 0x96, 0x14, 0x8e, 0xf2, 0x37, 0x1b, 0xa7, 0x8d);

.enum MF_OPM_CGMSA_PROTECTION_LEVEL {
    MF_OPM_CGMSA_OFF	= 0,
    MF_OPM_CGMSA_COPY_FREELY	= 0x1,
    MF_OPM_CGMSA_COPY_NO_MORE	= 0x2,
    MF_OPM_CGMSA_COPY_ONE_GENERATION	= 0x3,
    MF_OPM_CGMSA_COPY_NEVER = 0x4,
    MF_OPM_CGMSA_REDISTRIBUTION_CONTROL_REQUIRED	= 0x8
    }

.enum MF_OPM_ACP_PROTECTION_LEVEL {
    MF_OPM_ACP_OFF	= 0,
    MF_OPM_ACP_LEVEL_ONE	= 1,
    MF_OPM_ACP_LEVEL_TWO	= 2,
    MF_OPM_ACP_LEVEL_THREE	= 3,
    MF_OPM_ACP_FORCE_ULONG	= 0x7fffffff
    }

DEFINE_GUID( MFPROTECTION_VIDEO_FRAMES, 0x36a59cbc, 0x7401, 0x4a8c, 0xbc, 0x20, 0x46, 0xa7, 0xc9, 0xe5, 0x97, 0xf0);
DEFINE_GUID( MFPROTECTIONATTRIBUTE_BEST_EFFORT, 0xc8e06331, 0x75f0, 0x4ec1, 0x8e, 0x77, 0x17, 0x57, 0x8f, 0x77, 0x3b, 0x46);

DEFINE_GUID( MFPROTECTIONATTRIBUTE_FAIL_OVER, 0x8536abc5, 0x38f1, 0x4151, 0x9c, 0xce, 0xf5, 0x5d, 0x94, 0x12, 0x29, 0xac);

endif

if (WINVER GE _WIN32_WINNT_WIN8)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
DEFINE_GUID(MFPROTECTION_GRAPHICS_TRANSFER_AES_ENCRYPTION, 0xc873de64, 0xd8a5, 0x49e6, 0x88, 0xbb, 0xfb, 0x96, 0x3f, 0xd3, 0xd4, 0xce);
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DEFINE_GUID( MFPROTECTIONATTRIBUTE_CONSTRICTVIDEO_IMAGESIZE, 0x8476fc, 0x4b58, 0x4d80, 0xa7, 0x90, 0xe7, 0x29, 0x76, 0x73, 0x16, 0x1d);
DEFINE_GUID( MFPROTECTIONATTRIBUTE_HDCP_SRM, 0x6f302107, 0x3477, 0x4468, 0x8a, 0x8, 0xee, 0xf9, 0xdb, 0x10, 0xe2, 0xf);

.enum MFAudioConstriction {
    MFaudioConstrictionOff   = 0,
    MFaudioConstriction48_16 = ( MFaudioConstrictionOff + 1 ) ,
    MFaudioConstriction44_16 = ( MFaudioConstriction48_16 + 1 ) ,
    MFaudioConstriction14_14 = ( MFaudioConstriction44_16 + 1 ) ,
    MFaudioConstrictionMute  = ( MFaudioConstriction14_14 + 1 )
    }

if (WINVER GE _WIN32_WINNT_WIN7)
endif

if (WINVER GE _WIN32_WINNT_WIN7)
else
endif
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFSecureChannel_INTERFACE_DEFINED__
__IMFSecureChannel_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSecureChannel, "d0ae555d-3b12-4d97-b060-0990bc5aeb67")

.comdef IMFSecureChannel : public IUnknown

    GetCertificate	proc :ptr, :ptr
    SetupSession	proc
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum SAMPLE_PROTECTION_VERSION {
    SAMPLE_PROTECTION_VERSION_NO	= 0,
    SAMPLE_PROTECTION_VERSION_BASIC_LOKI	= 1,
    SAMPLE_PROTECTION_VERSION_SCATTER	= 2,
    SAMPLE_PROTECTION_VERSION_RC4	= 3
    }

DEFINE_GUID( MF_SampleProtectionSalt, 0x5403deee, 0xb9ee, 0x438f, 0xaa, 0x83, 0x38, 0x4, 0x99, 0x7e, 0x56, 0x9d);

ifndef __IMFSampleProtection_INTERFACE_DEFINED__
__IMFSampleProtection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSampleProtection, "8e36395f-c7b9-43c4-a54d-512b4af63c95")

.comdef IMFSampleProtection : public IUnknown

    GetInputProtectionVersion proc :ptr
    GetOutputProtectionVersion proc :ptr
    GetProtectionCertificate proc :DWORD, :ptr, :ptr
    InitOutputProtection proc :DWORD, :DWORD, :ptr, :DWORD, :ptr, :ptr
    InitInputProtection proc :DWORD, :DWORD, :ptr, :DWORD
    .ends

endif

ifndef __IMFMediaSinkPreroll_INTERFACE_DEFINED__
__IMFMediaSinkPreroll_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaSinkPreroll, "5dfd4b2a-7674-4110-a4e6-8a68fd5f3688")

.comdef IMFMediaSinkPreroll : public IUnknown

    NotifyPreroll	proc :MFTIME
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFFinalizableMediaSink_INTERFACE_DEFINED__
__IMFFinalizableMediaSink_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFFinalizableMediaSink, "EAECB74A-9A50-42ce-9541-6A7F57AA4AD7")

.comdef IMFFinalizableMediaSink : public IMFMediaSink

    BeginFinalize	proc :ptr, :ptr
    EndFinalize		proc :ptr
    .ends

endif
endif

if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __IMFStreamingSinkConfig_INTERFACE_DEFINED__
__IMFStreamingSinkConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFStreamingSinkConfig, "9db7aa41-3cc5-40d4-8509-555804ad34cc")

.comdef IMFStreamingSinkConfig : public IUnknown

    StartStreaming	proc :BOOL, :QWORD
    .ends

endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFRemoteProxy_INTERFACE_DEFINED__
__IMFRemoteProxy_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFRemoteProxy, "994e23ad-1cc2-493c-b9fa-46f1cb040fa4")

.comdef IMFRemoteProxy : public IUnknown

    GetRemoteObject	proc :REFIID, :ptr
    GetRemoteHost	proc :REFIID, :ptr
    .ends

endif

DEFINE_GUID( MF_REMOTE_PROXY, 0x2f00c90e, 0xd2cf, 0x4278, 0x8b, 0x6a, 0xd0, 0x77, 0xfa, 0xc3, 0xa2, 0x5f);

ifndef __IMFObjectReferenceStream_INTERFACE_DEFINED__
__IMFObjectReferenceStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFObjectReferenceStream, "09EF5BE3-C8A7-469e-8B70-73BF25BB193F")

.comdef IMFObjectReferenceStream : public IUnknown

    SaveReference	proc :REFIID, :ptr
    LoadReference	proc :REFIID, :ptr
    .ends

endif

DEFINE_GUID( CLSID_CreateMediaExtensionObject, 0xef65a54d, 0x0788, 0x45b8, 0x8b, 0x14, 0xbc, 0x0f, 0x6a, 0x6b, 0x51, 0x37);

ifndef __IMFPMPHost_INTERFACE_DEFINED__
__IMFPMPHost_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFPMPHost, "F70CA1A9-FDC7-4782-B994-ADFFB1C98606")

.comdef IMFPMPHost : public IUnknown

    LockProcess		proc
    UnlockProcess	proc
    CreateObjectByCLSID proc :REFCLSID, :ptr, :REFIID, :ptr
    .ends


IMFPMPHost_RemoteCreateObjectByCLSID_Proxy proto __cdecl :ptr, :REFCLSID, :ptr, :dword, :REFIID, :ptr

IMFPMPHost_RemoteCreateObjectByCLSID_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

if (WINVER GE _WIN32_WINNT_WIN7)
externdef		MF_PMP_SERVICE:GUID
endif

ifndef __IMFPMPClient_INTERFACE_DEFINED__
__IMFPMPClient_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFPMPClient, "6C4E655D-EAD8-4421-B6B9-54DCDBBDF820")

.comdef IMFPMPClient : public IUnknown

    SetPMPHost		proc :ptr
    .ends

endif

ifndef __IMFPMPServer_INTERFACE_DEFINED__
__IMFPMPServer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFPMPServer, "994e23af-1cc2-493c-b9fa-46f1cb040fa4")

.comdef IMFPMPServer : public IUnknown

    LockProcess		proc
    UnlockProcess	proc
    CreateObjectByCLSID proc :REFCLSID, :REFIID, :ptr
    .ends

endif

MFCreatePMPServer proto __cdecl \
       dwCreationFlags: DWORD,
	   ppPMPServer: ptr ptr IMFPMPServer

ifndef __IMFRemoteDesktopPlugin_INTERFACE_DEFINED__
__IMFRemoteDesktopPlugin_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFRemoteDesktopPlugin, "1cde6309-cae0-4940-907e-c1ec9c3d1d4a")

.comdef IMFRemoteDesktopPlugin : public IUnknown

    UpdateTopology	proc :ptr
    .ends

endif

MFCreateRemoteDesktopPlugin proto __cdecl \
	      ppPlugin: ptr ptr IMFRemoteDesktopPlugin

CreateNamedPropertyStore proto __cdecl :ptr


ifndef __IMFSAMIStyle_INTERFACE_DEFINED__
__IMFSAMIStyle_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSAMIStyle, "A7E025DD-5303-4a62-89D6-E747E1EFAC73")

.comdef IMFSAMIStyle : public IUnknown

    GetStyleCount	proc :ptr
    GetStyles		proc :ptr
    SetSelectedStyle	proc :LPCWSTR
    GetSelectedStyle	proc :ptr
    .ends

endif

DEFINE_GUID( MF_SAMI_SERVICE, 0x49a89ae7, 0xb4d9, 0x4ef2, 0xaa, 0x5c, 0xf6, 0x5a, 0x3e, 0x5, 0xae, 0x4e );
DEFINE_GUID( MF_PD_SAMI_STYLELIST, 0xe0b73c7f, 0x486d, 0x484e, 0x98, 0x72, 0x4d, 0xe5, 0x19, 0x2a, 0x7b, 0xf8 );
DEFINE_GUID( MF_SD_SAMI_LANGUAGE, 0x36fcb98a, 0x6cd0, 0x44cb, 0xac, 0xb9, 0xa8, 0xf5, 0x60, 0xd, 0xd0, 0xbb );
endif

if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateSampleCopierMFT proto __cdecl \
	   ppCopierMFT: ptr ptr IMFTransform


ifndef __IMFTranscodeProfile_INTERFACE_DEFINED__
__IMFTranscodeProfile_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTranscodeProfile, "4ADFDBA3-7AB0-4953-A62B-461E7FF3DA1E")

.comdef IMFTranscodeProfile : public IUnknown

    SetAudioAttributes	proc :ptr
    GetAudioAttributes	proc :ptr
    SetVideoAttributes	proc :ptr
    GetVideoAttributes	proc :ptr
    SetContainerAttributes proc :ptr
    GetContainerAttributes proc :ptr
    .ends

endif

DEFINE_GUID( MF_TRANSCODE_CONTAINERTYPE, 0x150ff23f, 0x4abc, 0x478b, 0xac, 0x4f, 0xe1, 0x91, 0x6f, 0xba, 0x1c, 0xca );
DEFINE_GUID( MFTranscodeContainerType_ASF, 0x430f6f6e, 0xb6bf, 0x4fc1, 0xa0, 0xbd, 0x9e, 0xe4, 0x6e, 0xee, 0x2a, 0xfb );
DEFINE_GUID( MFTranscodeContainerType_MPEG4, 0xdc6cd05d, 0xb9d0, 0x40ef, 0xbd, 0x35, 0xfa, 0x62, 0x2c, 0x1a, 0xb2, 0x8a );
DEFINE_GUID( MFTranscodeContainerType_MP3, 0xe438b912, 0x83f1, 0x4de6, 0x9e, 0x3a, 0x9f, 0xfb, 0xc6, 0xdd, 0x24, 0xd1 );
DEFINE_GUID( MFTranscodeContainerType_3GP, 0x34c50167, 0x4472, 0x4f34, 0x9e, 0xa0, 0xc4, 0x9f, 0xba, 0xcf, 0x03, 0x7d );
DEFINE_GUID( MFTranscodeContainerType_AC3, 0x6d8d91c3, 0x8c91, 0x4ed1, 0x87, 0x42, 0x8c, 0x34, 0x7d, 0x5b, 0x44, 0xd0 );
DEFINE_GUID( MFTranscodeContainerType_ADTS, 0x132fd27d, 0x0f02, 0x43de, 0xa3, 0x01, 0x38, 0xfb, 0xbb, 0xb3, 0x83, 0x4e );
DEFINE_GUID( MFTranscodeContainerType_MPEG2, 0xbfc2dbf9, 0x7bb4, 0x4f8f, 0xaf, 0xde, 0xe1, 0x12, 0xc4, 0x4b, 0xa8, 0x82 );
DEFINE_GUID( MFTranscodeContainerType_WAVE, 0x64c3453c, 0x0f26, 0x4741, 0xbe, 0x63, 0x87, 0xbd, 0xf8, 0xbb, 0x93, 0x5b );
DEFINE_GUID( MFTranscodeContainerType_AVI, 0x7edfe8af, 0x402f, 0x4d76, 0xa3, 0x3c, 0x61, 0x9f, 0xd1, 0x57, 0xd0, 0xf1 );
if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_GUID( MFTranscodeContainerType_FMPEG4, 0x9ba876f1, 0x419f, 0x4b77, 0xa1, 0xe0, 0x35, 0x95, 0x9d, 0x9d, 0x40, 0x4 );
endif
DEFINE_GUID( MF_TRANSCODE_SKIP_METADATA_TRANSFER, 0x4e4469ef, 0xb571, 0x4959, 0x8f, 0x83, 0x3d, 0xcf, 0xba, 0x33, 0xa3, 0x93 );
DEFINE_GUID( MF_TRANSCODE_TOPOLOGYMODE, 0x3e3df610, 0x394a, 0x40b2, 0x9d, 0xea, 0x3b, 0xab, 0x65, 0xb, 0xeb, 0xf2 );
.enum MF_TRANSCODE_TOPOLOGYMODE_FLAGS {
    MF_TRANSCODE_TOPOLOGYMODE_SOFTWARE_ONLY = 0,
    MF_TRANSCODE_TOPOLOGYMODE_HARDWARE_ALLOWED	= 1
    }

DEFINE_GUID( MF_TRANSCODE_ADJUST_PROFILE, 0x9c37c21b, 0x60f, 0x487c, 0xa6, 0x90, 0x80, 0xd7, 0xf5, 0xd, 0x1c, 0x72 );
.enum MF_TRANSCODE_ADJUST_PROFILE_FLAGS {
    MF_TRANSCODE_ADJUST_PROFILE_DEFAULT = 0,
    MF_TRANSCODE_ADJUST_PROFILE_USE_SOURCE_ATTRIBUTES	= 1
    }

DEFINE_GUID( MF_TRANSCODE_ENCODINGPROFILE, 0x6947787c, 0xf508, 0x4ea9, 0xb1, 0xe9, 0xa1, 0xfe, 0x3a, 0x49, 0xfb, 0xc9 );
DEFINE_GUID( MF_TRANSCODE_QUALITYVSSPEED, 0x98332df8, 0x03cd, 0x476b, 0x89, 0xfa, 0x3f, 0x9e, 0x44, 0x2d, 0xec, 0x9f );
DEFINE_GUID( MF_TRANSCODE_DONOT_INSERT_ENCODER, 0xf45aa7ce, 0xab24, 0x4012, 0xa1, 0x1b, 0xdc, 0x82, 0x20, 0x20, 0x14, 0x10 );
.enum MF_VIDEO_PROCESSOR_ALGORITHM_TYPE {
    MF_VIDEO_PROCESSOR_ALGORITHM_DEFAULT	= 0,
    MF_VIDEO_PROCESSOR_ALGORITHM_MRF_CRF_444	= 1
    }

DEFINE_GUID( MF_VIDEO_PROCESSOR_ALGORITHM, 0x4a0a1e1f, 0x272c, 0x4fb6, 0x9e, 0xb1, 0xdb, 0x33, 0xc, 0xbc, 0x97, 0xca);
DEFINE_GUID( MF_XVP_DISABLE_FRC, 0x2c0afa19, 0x7a97, 0x4d5a, 0x9e, 0xe8, 0x16, 0xd4, 0xfc, 0x51, 0x8d, 0x8c );
;STDAPI
MFCreateTranscodeProfile proto __cdecl \
    ppTranscodeProfile: ptr ptr IMFTranscodeProfile

;STDAPI
MFCreateTranscodeTopology proto __cdecl \
		  pSrc: ptr IMFMediaSource,
    pwszOutputFilePath: LPCWSTR,
	      pProfile: ptr IMFTranscodeProfile,
       ppTranscodeTopo: ptr ptr IMFTopology

endif

if (WINVER GE _WIN32_WINNT_WIN8)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateTranscodeTopologyFromByteStream proto __cdecl \
		  pSrc: ptr IMFMediaSource,
	 pOutputStream: ptr IMFByteStream,
	      pProfile: ptr IMFTranscodeProfile,
       ppTranscodeTopo: ptr ptr IMFTopology

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFTranscodeGetAudioOutputAvailableTypes proto __cdecl \
	   guidSubType: REFGUID,
	    dwMFTFlags: DWORD,
	  pCodecConfig: ptr IMFAttributes,
      ppAvailableTypes: ptr ptr IMFCollection

MF_TRANSCODE_SINK_INFO	STRUC
dwVideoStreamID		dd ?
pVideoMediaType		ptr_t ?
dwAudioStreamID		dd ?
pAudioMediaType		ptr_t ?
MF_TRANSCODE_SINK_INFO	ENDS

ifndef __IMFTranscodeSinkInfoProvider_INTERFACE_DEFINED__
__IMFTranscodeSinkInfoProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTranscodeSinkInfoProvider, "8CFFCD2E-5A03-4a3a-AFF7-EDCD107C620E")

.comdef IMFTranscodeSinkInfoProvider : public IUnknown

    SetOutputFile	proc :LPCWSTR
    SetOutputByteStream proc :ptr
    SetProfile		proc :ptr
    GetSinkInfo		proc :ptr
    .ends

endif

MFCreateTranscodeSinkActivate proto __cdecl :ptr ptr

ifndef __IMFFieldOfUseMFTUnlock_INTERFACE_DEFINED__
__IMFFieldOfUseMFTUnlock_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFFieldOfUseMFTUnlock, "508E71D3-EC66-4fc3-8775-B4B9ED6BA847")

.comdef IMFFieldOfUseMFTUnlock : public IUnknown

    Unlock		proc :ptr
    .ends

endif

MFT_REGISTRATION_INFO	STRUC
clsid			CLSID <>
guidCategory		GUID <>
uiFlags			UINT32 ?
pszName			LPCWSTR ?
cInTypes		dd ?
pInTypes		ptr_t ?
cOutTypes		dd ?
pOutTypes		ptr_t ?
MFT_REGISTRATION_INFO	ENDS

DEFINE_GUID(MF_LOCAL_MFT_REGISTRATION_SERVICE, 0xddf5cf9c, 0x4506, 0x45aa, 0xab, 0xf0, 0x6d, 0x5d, 0x94, 0xdd, 0x1b, 0x4a);

ifndef __IMFLocalMFTRegistration_INTERFACE_DEFINED__
__IMFLocalMFTRegistration_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFLocalMFTRegistration, "149c4d73-b4be-4f8d-8b87-079e926b6add")

.comdef IMFLocalMFTRegistration : public IUnknown

    RegisterMFTs	proc :ptr, :DWORD
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
if (WINVER GE _WIN32_WINNT_WIN8)

ifndef __IMFPMPHostApp_INTERFACE_DEFINED__
__IMFPMPHostApp_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFPMPHostApp, "84d2054a-3aa1-4728-a3b0-440a418cf49c")

.comdef IMFPMPHostApp : public IUnknown

    LockProcess		proc
    UnlockProcess	proc
    ActivateClassById	proc :LPCWSTR, :ptr, :REFIID, :ptr
    .ends

endif

ifndef __IMFPMPClientApp_INTERFACE_DEFINED__
__IMFPMPClientApp_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFPMPClientApp, "c004f646-be2c-48f3-93a2-a0983eba1108")

.comdef IMFPMPClientApp : public IUnknown

    SetPMPHost		proc :ptr
    .ends

endif
endif

if (WINVER GE _WIN32_WINNT_WINBLUE)

ifndef __IMFMediaStreamSourceSampleRequest_INTERFACE_DEFINED__
__IMFMediaStreamSourceSampleRequest_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFMediaStreamSourceSampleRequest, "380b9af9-a85b-4e78-a2af-ea5ce645c6b4")

.comdef IMFMediaStreamSourceSampleRequest : public IUnknown

    SetSample		proc :ptr
    .ends

endif
endif

ifndef __IMFTrackedSample_INTERFACE_DEFINED__
__IMFTrackedSample_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTrackedSample, "245BF8E9-0755-40f7-88A5-AE0F18D55E17")

.comdef IMFTrackedSample : public IUnknown

    SetAllocator	proc :ptr, :ptr
    .ends

endif

MFCreateTrackedSample proto __cdecl \
	    ppMFSample: ptr ptr IMFTrackedSample

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateMFByteStreamOnStream proto __cdecl \
	       pStream: ptr IStream,
	  ppByteStream: ptr ptr IMFByteStream

MFCreateStreamOnMFByteStream proto __cdecl \
	   pByteStream: ptr IMFByteStream,
	      ppStream: ptr ptr IStream

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateMFByteStreamOnStreamEx proto __cdecl \
	    punkStream: ptr IUnknown,
	  ppByteStream: ptr ptr IMFByteStream

MFCreateStreamOnMFByteStreamEx proto __cdecl \
	   pByteStream: ptr IMFByteStream,
		  riid: REFIID,
		      : ptr ptr

MFCreateMediaTypeFromProperties proto __cdecl \
	    punkStream: ptr IUnknown,
	   ppMediaType: ptr ptr IMFMediaType

MFCreatePropertiesFromMediaType proto __cdecl \
	    pMediaType: ptr IMFMediaType,
		  riid: REFIID,
		      : ptr ptr

if (WINVER GE _WIN32_WINNT_WINBLUE)
DEFINE_GUID(MF_WRAPPED_BUFFER_SERVICE, 0xab544072, 0xc269, 0x4ebc, 0xa5, 0x52, 0x1c, 0x3b, 0x32, 0xbe, 0xd5, 0xca);
DEFINE_GUID(MF_WRAPPED_SAMPLE_SERVICE, 0x31f52bf2, 0xd03e, 0x4048, 0x80, 0xd0, 0x9c, 0x10, 0x46, 0xd8, 0x7c, 0x61);
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
DEFINE_GUID( MF_WRAPPED_OBJECT, 0x2b182c4c, 0xd6ac, 0x49f4, 0x89, 0x15, 0xf7, 0x18, 0x87, 0xdb, 0x70, 0xcd);
DEFINE_GUID(CLSID_HttpSchemePlugin, 0x44cb442b, 0x9da9, 0x49df, 0xb3, 0xfd, 0x2, 0x37, 0x77, 0xb1, 0x6e, 0x50);
DEFINE_GUID(CLSID_UrlmonSchemePlugin, 0x9ec4b4f9, 0x3029, 0x45ad, 0x94, 0x7b, 0x34, 0x4d, 0xe2, 0xa2, 0x49, 0xe2);
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
DEFINE_GUID(CLSID_NetSchemePlugin, 0xe9f4ebab, 0xd97b, 0x463e, 0xa2, 0xb1, 0xc5, 0x4e, 0xe3, 0xf9, 0x41, 0x4d);
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFEnumDeviceSources proto __cdecl \
	   pAttributes: ptr IMFAttributes,
     pppSourceActivate: ptr ptr ptr IMFActivate,
      pcSourceActivate: ptr UINT32

MFCreateDeviceSource proto __cdecl \
	   pAttributes: ptr IMFAttributes,
	      ppSource: ptr ptr IMFMediaSource

MFCreateDeviceSourceActivate proto __cdecl \
	   pAttributes: ptr IMFAttributes,
	    ppActivate: ptr ptr IMFActivate

DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, 0xc60ac5fe, 0x252a, 0x478f, 0xa0, 0xef, 0xbc, 0x8f, 0xa5, 0xf7, 0xca, 0xd3);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_HW_SOURCE, 0xde7046ba, 0x54d6, 0x4487, 0xa2, 0xa4, 0xec, 0x7c, 0xd, 0x1b, 0xd1, 0x63);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, 0x60d0e559, 0x52f8, 0x4fa2, 0xbb, 0xce, 0xac, 0xdb, 0x34, 0xa8, 0xec, 0x1);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_MEDIA_TYPE, 0x56a819ca, 0xc78, 0x4de4, 0xa0, 0xa7, 0x3d, 0xda, 0xba, 0xf, 0x24, 0xd4);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_CATEGORY, 0x77f0ae69, 0xc3bd, 0x4509, 0x94, 0x1d, 0x46, 0x7e, 0x4d, 0x24, 0x89, 0x9e);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK, 0x58f0aad8, 0x22bf, 0x4f8a, 0xbb, 0x3d, 0xd2, 0xc4, 0x97, 0x8c, 0x6e, 0x2f);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_SYMBOLIC_LINK, 0x98d24b5e, 0x5930, 0x4614, 0xb5, 0xa1, 0xf6, 0x0, 0xf9, 0x35, 0x5a, 0x78);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_MAX_BUFFERS, 0x7dd9b730, 0x4f2d, 0x41d5, 0x8f, 0x95, 0xc, 0xc9, 0xa9, 0x12, 0xba, 0x26);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_ENDPOINT_ID, 0x30da9258, 0xfeb9, 0x47a7, 0xa4, 0x53, 0x76, 0x3a, 0x7a, 0x8e, 0x1c, 0x5f);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_ROLE, 0xbc9d118e, 0x8c67, 0x4a18, 0x85, 0xd4, 0x12, 0xd3, 0x0, 0x40, 0x5, 0x52);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_GUID, 0x14dd9a1c, 0x7cff, 0x41be, 0xb1, 0xb9, 0xba, 0x1a, 0xc6, 0xec, 0xb5, 0x71);
DEFINE_GUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID, 0x8ac3587a, 0x4ae7, 0x42d8, 0x99, 0xe0, 0x0a, 0x60, 0x13, 0xee, 0xf9, 0x0f);
DEFINE_GUID( MF_DEVICESTREAM_IMAGE_STREAM, 0xa7ffb865, 0xe7b2, 0x43b0, 0x9f, 0x6f, 0x9a, 0xf2, 0xa0, 0xe5, 0xf, 0xc0);
DEFINE_GUID( MF_DEVICESTREAM_INDEPENDENT_IMAGE_STREAM, 0x3eeec7e, 0xd605, 0x4576, 0x8b, 0x29, 0x65, 0x80, 0xb4, 0x90, 0xd7, 0xd3);
DEFINE_GUID( MF_DEVICESTREAM_STREAM_ID, 0x11bd5120, 0xd124, 0x446b, 0x88, 0xe6, 0x17, 0x6, 0x2, 0x57, 0xff, 0xf9);
DEFINE_GUID( MF_DEVICESTREAM_STREAM_CATEGORY, 0x2939e7b8, 0xa62e, 0x4579, 0xb6, 0x74, 0xd4, 0x7, 0x3d, 0xfa, 0xbb, 0xba);
DEFINE_GUID( MF_DEVICESTREAM_TRANSFORM_STREAM_ID,	 0xe63937b7, 0xdaaf, 0x4d49, 0x81, 0x5f, 0xd8, 0x26, 0xf8, 0xad, 0x31, 0xe7);
DEFINE_GUID( MF_DEVICESTREAM_EXTENSION_PLUGIN_CLSID, 0x048e6558, 0x60c4, 0x4173, 0xbd, 0x5b, 0x6a, 0x3c, 0xa2, 0x89, 0x6a, 0xee);
DEFINE_GUID( MF_DEVICESTREAM_EXTENSION_PLUGIN_CONNECTION_POINT, 0x37f9375c, 0xe664, 0x4ea4, 0xaa, 0xe4, 0xcb, 0x6d, 0x1d, 0xac, 0xa1, 0xf4);
DEFINE_GUID( MF_DEVICESTREAM_TAKEPHOTO_TRIGGER, 0x1d180e34, 0x538c, 0x4fbb, 0xa7, 0x5a, 0x85, 0x9a, 0xf7, 0xd2, 0x61, 0xa6 );
DEFINE_GUID( MF_DEVICESTREAM_MAX_FRAME_BUFFERS, 0x1684cebe, 0x3175, 0x4985, 0x88, 0x2c, 0x0e, 0xfd, 0x3e, 0x8a, 0xc1, 0x1e );
DEFINE_GUID(MFSampleExtension_DeviceTimestamp, 0x8f3e35e7, 0x2dcd, 0x4887, 0x86, 0x22, 0x2a, 0x58, 0xba, 0xa6, 0x52, 0xb0);
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFProtectedEnvironmentAccess_INTERFACE_DEFINED__
__IMFProtectedEnvironmentAccess_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFProtectedEnvironmentAccess, "ef5dc845-f0d9-4ec9-b00c-cb5183d38434")

.comdef IMFProtectedEnvironmentAccess : public IUnknown

    _Call		proc :UINT32, :ptr, :UINT32, :ptr
    ReadGRL		proc :ptr, :ptr
    .ends

endif

ifndef __IMFSignedLibrary_INTERFACE_DEFINED__
__IMFSignedLibrary_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSignedLibrary, "4a724bca-ff6a-4c07-8e0d-7a358421cf06")

.comdef IMFSignedLibrary : public IUnknown

    GetProcedureAddress proc :LPCSTR, :ptr
    .ends

endif

ifndef __IMFSystemId_INTERFACE_DEFINED__
__IMFSystemId_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSystemId, "fff4af3a-1fc1-4ef9-a29b-d26c49e2f31a")

.comdef IMFSystemId : public IUnknown

    GetData		proc :ptr, :ptr
    Setup		proc :UINT32, :UINT32, :ptr, :ptr, :ptr
    .ends

endif

MFCreateProtectedEnvironmentAccess proto __cdecl \
	      ppAccess: ptr ptr IMFProtectedEnvironmentAccess

MFLoadSignedLibrary proto __cdecl \
	       pszName: LPCWSTR,
		 ppLib: ptr ptr IMFSignedLibrary

MFGetSystemId proto __cdecl \
		  ppId: ptr ptr IMFSystemId

MFGetLocalId proto __cdecl \
	      verifier: ptr BYTE,
		  size: UINT32,
		    id: ptr LPWSTR

;; {40871C59-AB40-471F-8DC3-1F259D862479}
DEFINE_GUID(CLSID_MPEG2ByteStreamPlugin,0x40871c59, 0xab40, 0x471f, 0x8d, 0xc3, 0x1f, 0x25, 0x9d, 0x86, 0x24, 0x79);
;; {f09992f7-9fba-4c4a-a37f-8c47b4e1dfe7}
DEFINE_GUID( MF_MEDIASOURCE_SERVICE, 0xf09992f7, 0x9fba, 0x4c4a, 0xa3, 0x7f, 0x8c, 0x47, 0xb4, 0xe1, 0xdf, 0xe7 );
endif

;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPBYTE
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr BSTR

;LPBYTE
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
LPSAFEARRAY_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY

;LPBYTE
LPSAFEARRAY_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr LPSAFEARRAY

;LPBYTE
LPSAFEARRAY_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr LPSAFEARRAY

;void
LPSAFEARRAY_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY


;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPBYTE
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr BSTR

;LPBYTE
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
LPSAFEARRAY_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY

;LPBYTE
LPSAFEARRAY_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr LPSAFEARRAY

;LPBYTE
LPSAFEARRAY_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr LPSAFEARRAY

;void
LPSAFEARRAY_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY


IMFSourceResolver_BeginCreateObjectFromURL_Proxy proto __cdecl :ptr, :ptr, :dword, :ptr
IMFSourceResolver_BeginCreateObjectFromURL_Stub proto __cdecl :ptr, :ptr, :dword, :ptr, :ptr
IMFSourceResolver_EndCreateObjectFromURL_Proxy proto __cdecl :ptr, :ptr, :ptr, :ptr
IMFSourceResolver_EndCreateObjectFromURL_Stub proto __cdecl :ptr, :ptr, :ptr, :ptr
IMFSourceResolver_BeginCreateObjectFromByteStream_Proxy proto __cdecl :ptr, :ptr, :ptr, :dword, :ptr, :ptr, :ptr, :ptr
IMFSourceResolver_BeginCreateObjectFromByteStream_Stub proto __cdecl :ptr, :ptr, :ptr, :dword, :ptr, :ptr
IMFSourceResolver_EndCreateObjectFromByteStream_Proxy proto __cdecl :ptr, :ptr, :ptr, :ptr
IMFSourceResolver_EndCreateObjectFromByteStream_Stub proto __cdecl :ptr, :ptr, :ptr, :ptr
IMFMediaSource_CreatePresentationDescriptor_Proxy proto __cdecl :ptr, :ptr
IMFMediaSource_CreatePresentationDescriptor_Stub proto __cdecl :ptr, :ptr, :ptr, :ptr
IMFMediaStream_RequestSample_Proxy proto __cdecl :ptr, :ptr
IMFMediaStream_RequestSample_Stub proto __cdecl :ptr
IMFTopologyNode_GetOutputPrefType_Proxy proto __cdecl :ptr, :dword, :ptr
IMFTopologyNode_GetOutputPrefType_Stub proto __cdecl :ptr, :dword, :ptr, :ptr
IMFTopologyNode_GetInputPrefType_Proxy proto __cdecl :ptr, :dword, :ptr
IMFTopologyNode_GetInputPrefType_Stub proto __cdecl :ptr, :dword, :ptr, :ptr
IMFMediaTypeHandler_IsMediaTypeSupported_Proxy proto __cdecl :ptr, :ptr, :ptr
IMFMediaTypeHandler_IsMediaTypeSupported_Stub proto __cdecl :ptr, :ptr, :dword, :ptr, :ptr
IMFMediaTypeHandler_GetMediaTypeByIndex_Proxy proto __cdecl :ptr, :dword, :ptr
IMFMediaTypeHandler_GetMediaTypeByIndex_Stub proto __cdecl :ptr, :dword, :ptr, :ptr
IMFMediaTypeHandler_SetCurrentMediaType_Proxy proto __cdecl :ptr, :ptr
IMFMediaTypeHandler_SetCurrentMediaType_Stub proto __cdecl :ptr, :ptr, :dword
IMFMediaTypeHandler_GetCurrentMediaType_Proxy proto __cdecl :ptr, :ptr
IMFMediaTypeHandler_GetCurrentMediaType_Stub proto __cdecl :ptr, :ptr, :ptr
IMFContentProtectionManager_BeginEnableContent_Proxy proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
IMFContentProtectionManager_BeginEnableContent_Stub proto __cdecl :ptr, :REFCLSID, :ptr, :dword, :ptr
IMFContentProtectionManager_EndEnableContent_Proxy proto __cdecl :ptr, :ptr
IMFContentProtectionManager_EndEnableContent_Stub proto __cdecl :ptr, :ptr
IMFWorkQueueServices_BeginRegisterTopologyWorkQueuesWithMMCSS_Proxy proto __cdecl :ptr, :ptr, :ptr
IMFWorkQueueServices_BeginRegisterTopologyWorkQueuesWithMMCSS_Stub proto __cdecl :ptr, :ptr
IMFWorkQueueServices_EndRegisterTopologyWorkQueuesWithMMCSS_Proxy proto __cdecl :ptr, :ptr
IMFWorkQueueServices_EndRegisterTopologyWorkQueuesWithMMCSS_Stub proto __cdecl :ptr, :ptr
IMFWorkQueueServices_BeginUnregisterTopologyWorkQueuesWithMMCSS_Proxy proto __cdecl :ptr, :ptr, :ptr
IMFWorkQueueServices_BeginUnregisterTopologyWorkQueuesWithMMCSS_Stub proto __cdecl :ptr, :ptr
IMFWorkQueueServices_EndUnregisterTopologyWorkQueuesWithMMCSS_Proxy proto __cdecl :ptr, :ptr
IMFWorkQueueServices_EndUnregisterTopologyWorkQueuesWithMMCSS_Stub proto __cdecl :ptr, :ptr
IMFWorkQueueServices_BeginRegisterPlatformWorkQueueWithMMCSS_Proxy proto __cdecl :ptr, :dword, :ptr, :dword, :ptr, :ptr
IMFWorkQueueServices_BeginRegisterPlatformWorkQueueWithMMCSS_Stub proto __cdecl :ptr, :dword, :ptr, :dword, :ptr
IMFWorkQueueServices_EndRegisterPlatformWorkQueueWithMMCSS_Proxy proto __cdecl :ptr, :ptr, :ptr
IMFWorkQueueServices_EndRegisterPlatformWorkQueueWithMMCSS_Stub proto __cdecl :ptr, :ptr, :ptr
IMFWorkQueueServices_BeginUnregisterPlatformWorkQueueWithMMCSS_Proxy proto __cdecl :ptr, :dword, :ptr, :ptr
IMFWorkQueueServices_BeginUnregisterPlatformWorkQueueWithMMCSS_Stub proto __cdecl :ptr, :dword, :ptr
IMFWorkQueueServices_EndUnregisterPlatformWorkQueueWithMMCSS_Proxy proto __cdecl :ptr, :ptr
IMFWorkQueueServices_EndUnregisterPlatformWorkQueueWithMMCSS_Stub proto __cdecl :ptr, :ptr
IMFWorkQueueServicesEx_BeginRegisterPlatformWorkQueueWithMMCSSEx_Proxy proto __cdecl :ptr, :dword, :ptr, :dword, :ptr, :ptr, :ptr
IMFWorkQueueServicesEx_BeginRegisterPlatformWorkQueueWithMMCSSEx_Stub proto __cdecl :ptr, :dword, :ptr, :dword, :LONG, :ptr
IMFPMPHost_CreateObjectByCLSID_Proxy proto __cdecl :ptr, :REFCLSID, :ptr, :REFCLSID, :ptr
IMFPMPHost_CreateObjectByCLSID_Stub proto __cdecl :ptr, :REFCLSID, :ptr, :dword, :REFIID, :ptr

endif
