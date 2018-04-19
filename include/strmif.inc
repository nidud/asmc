ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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
ifndef __strmif_h__
__strmif_h__ equ <>
.xlist

ifndef __ICreateDevEnum_FWD_DEFINED__
__ICreateDevEnum_FWD_DEFINED__ equ 1
endif
ifndef __IPin_FWD_DEFINED__
__IPin_FWD_DEFINED__ equ 1
endif
ifndef __IEnumPins_FWD_DEFINED__
__IEnumPins_FWD_DEFINED__ equ 1
endif
ifndef __IEnumMediaTypes_FWD_DEFINED__
__IEnumMediaTypes_FWD_DEFINED__ equ 1
endif
ifndef __IFilterGraph_FWD_DEFINED__
__IFilterGraph_FWD_DEFINED__ equ 1
endif
ifndef __IEnumFilters_FWD_DEFINED__
__IEnumFilters_FWD_DEFINED__ equ 1
endif
ifndef __IMediaFilter_FWD_DEFINED__
__IMediaFilter_FWD_DEFINED__ equ 1
endif
ifndef __IBaseFilter_FWD_DEFINED__
__IBaseFilter_FWD_DEFINED__ equ 1
endif
ifndef __IReferenceClock_FWD_DEFINED__
__IReferenceClock_FWD_DEFINED__ equ 1
endif
ifndef __IReferenceClockTimerControl_FWD_DEFINED__
__IReferenceClockTimerControl_FWD_DEFINED__ equ 1
endif
ifndef __IReferenceClock2_FWD_DEFINED__
__IReferenceClock2_FWD_DEFINED__ equ 1
endif
ifndef __IMediaSample_FWD_DEFINED__
__IMediaSample_FWD_DEFINED__ equ 1
endif
ifndef __IMediaSample2_FWD_DEFINED__
__IMediaSample2_FWD_DEFINED__ equ 1
endif
ifndef __IMediaSample2Config_FWD_DEFINED__
__IMediaSample2Config_FWD_DEFINED__ equ 1
endif
ifndef __IMemAllocator_FWD_DEFINED__
__IMemAllocator_FWD_DEFINED__ equ 1
endif
ifndef __IMemAllocatorCallbackTemp_FWD_DEFINED__
__IMemAllocatorCallbackTemp_FWD_DEFINED__ equ 1
endif
ifndef __IMemAllocatorNotifyCallbackTemp_FWD_DEFINED__
__IMemAllocatorNotifyCallbackTemp_FWD_DEFINED__ equ 1
endif
ifndef __IMemInputPin_FWD_DEFINED__
__IMemInputPin_FWD_DEFINED__ equ 1
endif
ifndef __IAMovieSetup_FWD_DEFINED__
__IAMovieSetup_FWD_DEFINED__ equ 1
endif
ifndef __IMediaSeeking_FWD_DEFINED__
__IMediaSeeking_FWD_DEFINED__ equ 1
endif
ifndef __IEnumRegFilters_FWD_DEFINED__
__IEnumRegFilters_FWD_DEFINED__ equ 1
endif
ifndef __IFilterMapper_FWD_DEFINED__
__IFilterMapper_FWD_DEFINED__ equ 1
endif
ifndef __IFilterMapper2_FWD_DEFINED__
__IFilterMapper2_FWD_DEFINED__ equ 1
endif
ifndef __IFilterMapper3_FWD_DEFINED__
__IFilterMapper3_FWD_DEFINED__ equ 1
endif
ifndef __IQualityControl_FWD_DEFINED__
__IQualityControl_FWD_DEFINED__ equ 1
endif
ifndef __IOverlayNotify_FWD_DEFINED__
__IOverlayNotify_FWD_DEFINED__ equ 1
endif
ifndef __IOverlayNotify2_FWD_DEFINED__
__IOverlayNotify2_FWD_DEFINED__ equ 1
endif
ifndef __IOverlay_FWD_DEFINED__
__IOverlay_FWD_DEFINED__ equ 1
endif
ifndef __IMediaEventSink_FWD_DEFINED__
__IMediaEventSink_FWD_DEFINED__ equ 1
endif
ifndef __IFileSourceFilter_FWD_DEFINED__
__IFileSourceFilter_FWD_DEFINED__ equ 1
endif
ifndef __IFileSinkFilter_FWD_DEFINED__
__IFileSinkFilter_FWD_DEFINED__ equ 1
endif
ifndef __IFileSinkFilter2_FWD_DEFINED__
__IFileSinkFilter2_FWD_DEFINED__ equ 1
endif
ifndef __IGraphBuilder_FWD_DEFINED__
__IGraphBuilder_FWD_DEFINED__ equ 1
endif
ifndef __ICaptureGraphBuilder_FWD_DEFINED__
__ICaptureGraphBuilder_FWD_DEFINED__ equ 1
endif
ifndef __IAMCopyCaptureFileProgress_FWD_DEFINED__
__IAMCopyCaptureFileProgress_FWD_DEFINED__ equ 1
endif
ifndef __ICaptureGraphBuilder2_FWD_DEFINED__
__ICaptureGraphBuilder2_FWD_DEFINED__ equ 1
endif
ifndef __IFilterGraph2_FWD_DEFINED__
__IFilterGraph2_FWD_DEFINED__ equ 1
endif
ifndef __IFilterGraph3_FWD_DEFINED__
__IFilterGraph3_FWD_DEFINED__ equ 1
endif
ifndef __IStreamBuilder_FWD_DEFINED__
__IStreamBuilder_FWD_DEFINED__ equ 1
endif
ifndef __IAsyncReader_FWD_DEFINED__
__IAsyncReader_FWD_DEFINED__ equ 1
endif
ifndef __IGraphVersion_FWD_DEFINED__
__IGraphVersion_FWD_DEFINED__ equ 1
endif
ifndef __IResourceConsumer_FWD_DEFINED__
__IResourceConsumer_FWD_DEFINED__ equ 1
endif
ifndef __IResourceManager_FWD_DEFINED__
__IResourceManager_FWD_DEFINED__ equ 1
endif
ifndef __IDistributorNotify_FWD_DEFINED__
__IDistributorNotify_FWD_DEFINED__ equ 1
endif
ifndef __IAMStreamControl_FWD_DEFINED__
__IAMStreamControl_FWD_DEFINED__ equ 1
endif
ifndef __ISeekingPassThru_FWD_DEFINED__
__ISeekingPassThru_FWD_DEFINED__ equ 1
endif
ifndef __IAMStreamConfig_FWD_DEFINED__
__IAMStreamConfig_FWD_DEFINED__ equ 1
endif
ifndef __IConfigInterleaving_FWD_DEFINED__
__IConfigInterleaving_FWD_DEFINED__ equ 1
endif
ifndef __IConfigAviMux_FWD_DEFINED__
__IConfigAviMux_FWD_DEFINED__ equ 1
endif
ifndef __IAMVideoCompression_FWD_DEFINED__
__IAMVideoCompression_FWD_DEFINED__ equ 1
endif
ifndef __IAMVfwCaptureDialogs_FWD_DEFINED__
__IAMVfwCaptureDialogs_FWD_DEFINED__ equ 1
endif
ifndef __IAMVfwCompressDialogs_FWD_DEFINED__
__IAMVfwCompressDialogs_FWD_DEFINED__ equ 1
endif
ifndef __IAMDroppedFrames_FWD_DEFINED__
__IAMDroppedFrames_FWD_DEFINED__ equ 1
endif
ifndef __IAMAudioInputMixer_FWD_DEFINED__
__IAMAudioInputMixer_FWD_DEFINED__ equ 1
endif
ifndef __IAMBufferNegotiation_FWD_DEFINED__
__IAMBufferNegotiation_FWD_DEFINED__ equ 1
endif
ifndef __IAMAnalogVideoDecoder_FWD_DEFINED__
__IAMAnalogVideoDecoder_FWD_DEFINED__ equ 1
endif
ifndef __IAMVideoProcAmp_FWD_DEFINED__
__IAMVideoProcAmp_FWD_DEFINED__ equ 1
endif
ifndef __IAMCameraControl_FWD_DEFINED__
__IAMCameraControl_FWD_DEFINED__ equ 1
endif
ifndef __IAMVideoControl_FWD_DEFINED__
__IAMVideoControl_FWD_DEFINED__ equ 1
endif
ifndef __IAMCrossbar_FWD_DEFINED__
__IAMCrossbar_FWD_DEFINED__ equ 1
endif
ifndef __IAMTuner_FWD_DEFINED__
__IAMTuner_FWD_DEFINED__ equ 1
endif
ifndef __IAMTunerNotification_FWD_DEFINED__
__IAMTunerNotification_FWD_DEFINED__ equ 1
endif
ifndef __IAMTVTuner_FWD_DEFINED__
__IAMTVTuner_FWD_DEFINED__ equ 1
endif
ifndef __IBPCSatelliteTuner_FWD_DEFINED__
__IBPCSatelliteTuner_FWD_DEFINED__ equ 1
endif
ifndef __IAMTVAudio_FWD_DEFINED__
__IAMTVAudio_FWD_DEFINED__ equ 1
endif
ifndef __IAMTVAudioNotification_FWD_DEFINED__
__IAMTVAudioNotification_FWD_DEFINED__ equ 1
endif
ifndef __IAMAnalogVideoEncoder_FWD_DEFINED__
__IAMAnalogVideoEncoder_FWD_DEFINED__ equ 1
endif
ifndef __IKsPropertySet_FWD_DEFINED__
__IKsPropertySet_FWD_DEFINED__ equ 1
endif
ifndef __IMediaPropertyBag_FWD_DEFINED__
__IMediaPropertyBag_FWD_DEFINED__ equ 1
endif
ifndef __IPersistMediaPropertyBag_FWD_DEFINED__
__IPersistMediaPropertyBag_FWD_DEFINED__ equ 1
endif
ifndef __IAMPhysicalPinInfo_FWD_DEFINED__
__IAMPhysicalPinInfo_FWD_DEFINED__ equ 1
endif
ifndef __IAMExtDevice_FWD_DEFINED__
__IAMExtDevice_FWD_DEFINED__ equ 1
endif
ifndef __IAMExtTransport_FWD_DEFINED__
__IAMExtTransport_FWD_DEFINED__ equ 1
endif
ifndef __IAMTimecodeReader_FWD_DEFINED__
__IAMTimecodeReader_FWD_DEFINED__ equ 1
endif
ifndef __IAMTimecodeGenerator_FWD_DEFINED__
__IAMTimecodeGenerator_FWD_DEFINED__ equ 1
endif
ifndef __IAMTimecodeDisplay_FWD_DEFINED__
__IAMTimecodeDisplay_FWD_DEFINED__ equ 1
endif
ifndef __IAMDevMemoryAllocator_FWD_DEFINED__
__IAMDevMemoryAllocator_FWD_DEFINED__ equ 1
endif
ifndef __IAMDevMemoryControl_FWD_DEFINED__
__IAMDevMemoryControl_FWD_DEFINED__ equ 1
endif
ifndef __IAMStreamSelect_FWD_DEFINED__
__IAMStreamSelect_FWD_DEFINED__ equ 1
endif
ifndef __IAMResourceControl_FWD_DEFINED__
__IAMResourceControl_FWD_DEFINED__ equ 1
endif
ifndef __IAMClockAdjust_FWD_DEFINED__
__IAMClockAdjust_FWD_DEFINED__ equ 1
endif
ifndef __IAMFilterMiscFlags_FWD_DEFINED__
__IAMFilterMiscFlags_FWD_DEFINED__ equ 1
endif
ifndef __IDrawVideoImage_FWD_DEFINED__
__IDrawVideoImage_FWD_DEFINED__ equ 1
endif
ifndef __IDecimateVideoImage_FWD_DEFINED__
__IDecimateVideoImage_FWD_DEFINED__ equ 1
endif
ifndef __IAMVideoDecimationProperties_FWD_DEFINED__
__IAMVideoDecimationProperties_FWD_DEFINED__ equ 1
endif
ifndef __IVideoFrameStep_FWD_DEFINED__
__IVideoFrameStep_FWD_DEFINED__ equ 1
endif
ifndef __IAMLatency_FWD_DEFINED__
__IAMLatency_FWD_DEFINED__ equ 1
endif
ifndef __IAMPushSource_FWD_DEFINED__
__IAMPushSource_FWD_DEFINED__ equ 1
endif
ifndef __IAMDeviceRemoval_FWD_DEFINED__
__IAMDeviceRemoval_FWD_DEFINED__ equ 1
endif
ifndef __IDVEnc_FWD_DEFINED__
__IDVEnc_FWD_DEFINED__ equ 1
endif
ifndef __IIPDVDec_FWD_DEFINED__
__IIPDVDec_FWD_DEFINED__ equ 1
endif
ifndef __IDVRGB219_FWD_DEFINED__
__IDVRGB219_FWD_DEFINED__ equ 1
endif
ifndef __IDVSplitter_FWD_DEFINED__
__IDVSplitter_FWD_DEFINED__ equ 1
endif
ifndef __IAMAudioRendererStats_FWD_DEFINED__
__IAMAudioRendererStats_FWD_DEFINED__ equ 1
endif
ifndef __IAMGraphStreams_FWD_DEFINED__
__IAMGraphStreams_FWD_DEFINED__ equ 1
endif
ifndef __IAMOverlayFX_FWD_DEFINED__
__IAMOverlayFX_FWD_DEFINED__ equ 1
endif
ifndef __IAMOpenProgress_FWD_DEFINED__
__IAMOpenProgress_FWD_DEFINED__ equ 1
endif
ifndef __IMpeg2Demultiplexer_FWD_DEFINED__
__IMpeg2Demultiplexer_FWD_DEFINED__ equ 1
endif
ifndef __IEnumStreamIdMap_FWD_DEFINED__
__IEnumStreamIdMap_FWD_DEFINED__ equ 1
endif
ifndef __IMPEG2StreamIdMap_FWD_DEFINED__
__IMPEG2StreamIdMap_FWD_DEFINED__ equ 1
endif
ifndef __IRegisterServiceProvider_FWD_DEFINED__
__IRegisterServiceProvider_FWD_DEFINED__ equ 1
endif
ifndef __IAMClockSlave_FWD_DEFINED__
__IAMClockSlave_FWD_DEFINED__ equ 1
endif
ifndef __IAMGraphBuilderCallback_FWD_DEFINED__
__IAMGraphBuilderCallback_FWD_DEFINED__ equ 1
endif
ifndef __ICodecAPI_FWD_DEFINED__
__ICodecAPI_FWD_DEFINED__ equ 1
endif
ifndef __IGetCapabilitiesKey_FWD_DEFINED__
__IGetCapabilitiesKey_FWD_DEFINED__ equ 1
endif
ifndef __IEncoderAPI_FWD_DEFINED__
__IEncoderAPI_FWD_DEFINED__ equ 1
endif
ifndef __IVideoEncoder_FWD_DEFINED__
__IVideoEncoder_FWD_DEFINED__ equ 1
endif
ifndef __IAMDecoderCaps_FWD_DEFINED__
__IAMDecoderCaps_FWD_DEFINED__ equ 1
endif
ifndef __IAMCertifiedOutputProtection_FWD_DEFINED__
__IAMCertifiedOutputProtection_FWD_DEFINED__ equ 1
endif
ifndef __IAMAsyncReaderTimestampScaling_FWD_DEFINED__
__IAMAsyncReaderTimestampScaling_FWD_DEFINED__ equ 1
endif
ifndef __IAMPluginControl_FWD_DEFINED__
__IAMPluginControl_FWD_DEFINED__ equ 1
endif
ifndef __IDvdControl_FWD_DEFINED__
__IDvdControl_FWD_DEFINED__ equ 1
endif
ifndef __IDvdInfo_FWD_DEFINED__
__IDvdInfo_FWD_DEFINED__ equ 1
endif
ifndef __IDvdCmd_FWD_DEFINED__
__IDvdCmd_FWD_DEFINED__ equ 1
endif
ifndef __IDvdState_FWD_DEFINED__
__IDvdState_FWD_DEFINED__ equ 1
endif
ifndef __IDvdControl2_FWD_DEFINED__
__IDvdControl2_FWD_DEFINED__ equ 1
endif
ifndef __IDvdInfo2_FWD_DEFINED__
__IDvdInfo2_FWD_DEFINED__ equ 1
endif
ifndef __IDvdGraphBuilder_FWD_DEFINED__
__IDvdGraphBuilder_FWD_DEFINED__ equ 1
endif
ifndef __IDDrawExclModeVideo_FWD_DEFINED__
__IDDrawExclModeVideo_FWD_DEFINED__ equ 1
endif
ifndef __IDDrawExclModeVideoCallback_FWD_DEFINED__
__IDDrawExclModeVideoCallback_FWD_DEFINED__ equ 1
endif
ifndef __IPinConnection_FWD_DEFINED__
__IPinConnection_FWD_DEFINED__ equ 1
endif
ifndef __IPinFlowControl_FWD_DEFINED__
__IPinFlowControl_FWD_DEFINED__ equ 1
endif
ifndef __IGraphConfig_FWD_DEFINED__
__IGraphConfig_FWD_DEFINED__ equ 1
endif
ifndef __IGraphConfigCallback_FWD_DEFINED__
__IGraphConfigCallback_FWD_DEFINED__ equ 1
endif
ifndef __IFilterChain_FWD_DEFINED__
__IFilterChain_FWD_DEFINED__ equ 1
endif
ifndef __IVMRImagePresenter_FWD_DEFINED__
__IVMRImagePresenter_FWD_DEFINED__ equ 1
endif
ifndef __IVMRSurfaceAllocator_FWD_DEFINED__
__IVMRSurfaceAllocator_FWD_DEFINED__ equ 1
endif
ifndef __IVMRSurfaceAllocatorNotify_FWD_DEFINED__
__IVMRSurfaceAllocatorNotify_FWD_DEFINED__ equ 1
endif
ifndef __IVMRWindowlessControl_FWD_DEFINED__
__IVMRWindowlessControl_FWD_DEFINED__ equ 1
endif
ifndef __IVMRMixerControl_FWD_DEFINED__
__IVMRMixerControl_FWD_DEFINED__ equ 1
endif
ifndef __IVMRMonitorConfig_FWD_DEFINED__
__IVMRMonitorConfig_FWD_DEFINED__ equ 1
endif
ifndef __IVMRFilterConfig_FWD_DEFINED__
__IVMRFilterConfig_FWD_DEFINED__ equ 1
endif
ifndef __IVMRAspectRatioControl_FWD_DEFINED__
__IVMRAspectRatioControl_FWD_DEFINED__ equ 1
endif
ifndef __IVMRDeinterlaceControl_FWD_DEFINED__
__IVMRDeinterlaceControl_FWD_DEFINED__ equ 1
endif
ifndef __IVMRMixerBitmap_FWD_DEFINED__
__IVMRMixerBitmap_FWD_DEFINED__ equ 1
endif
ifndef __IVMRImageCompositor_FWD_DEFINED__
__IVMRImageCompositor_FWD_DEFINED__ equ 1
endif
ifndef __IVMRVideoStreamControl_FWD_DEFINED__
__IVMRVideoStreamControl_FWD_DEFINED__ equ 1
endif
ifndef __IVMRSurface_FWD_DEFINED__
__IVMRSurface_FWD_DEFINED__ equ 1
endif
ifndef __IVMRImagePresenterConfig_FWD_DEFINED__
__IVMRImagePresenterConfig_FWD_DEFINED__ equ 1
endif
ifndef __IVMRImagePresenterExclModeConfig_FWD_DEFINED__
__IVMRImagePresenterExclModeConfig_FWD_DEFINED__ equ 1
endif
ifndef __IVPManager_FWD_DEFINED__
__IVPManager_FWD_DEFINED__ equ 1
endif
include unknwn.inc
include objidl.inc
include oaidl.inc
include ocidl.inc
.xlist

CDEF_CLASS_DEFAULT	equ 0x0001
CDEF_BYPASS_CLASS_MANAGER equ 0x0002
CDEF_MERIT_ABOVE_DO_NOT_USE equ 0x0008
CDEF_DEVMON_CMGR_DEVICE equ 0x0010
CDEF_DEVMON_DMO		equ 0x0020
CDEF_DEVMON_PNP_DEVICE	equ 0x0040
CDEF_DEVMON_FILTER	equ 0x0080
CDEF_DEVMON_SELECTIVE_MASK equ 0x00f0


externdef		__MIDL_itf_strmif_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICreateDevEnum_INTERFACE_DEFINED__
__ICreateDevEnum_INTERFACE_DEFINED__ equ 1

externdef		IID_ICreateDevEnum:IID

.comdef ICreateDevEnum

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateClassEnumerator proc :REFCLSID, :ptr, :DWORD
    .ends

endif

CHARS_IN_GUID		equ 39
AM_MEDIA_TYPE		STRUC
majortype		GUID <>
subtype			GUID <>
bFixedSizeSamples	BOOL ?
bTemporalCompression	BOOL ?
lSampleSize		ULONG ?
formattype		GUID <>
pUnk			LPIUnknown ?
cbFormat		ULONG ?
pbFormat		LPBYTE ?
AM_MEDIA_TYPE		ENDS
PAM_MEDIA_TYPE		typedef ptr AM_MEDIA_TYPE

PIN_DIRECTION		typedef SDWORD
PINDIR_INPUT		equ 0
PINDIR_OUTPUT		equ ( PINDIR_INPUT + 1 )

MAX_PIN_NAME		equ 128
MAX_FILTER_NAME		equ 128
REFERENCE_TIME		typedef LONGLONG

REFTIME			typedef REAL8
HSEMAPHORE		typedef DWORD_PTR
HEVENT			typedef DWORD_PTR

ALLOCATOR_PROPERTIES	STRUC
cBuffers		LONG ?
cbBuffer		LONG ?
cbAlign			LONG ?
cbPrefix		LONG ?
ALLOCATOR_PROPERTIES	ENDS

externdef		__MIDL_itf_strmif_0000_0001_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0001_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPin_INTERFACE_DEFINED__
__IPin_INTERFACE_DEFINED__ equ 1

PIN_INFO		STRUC
pFilter			PVOID ?
dir			PIN_DIRECTION ?
achName			WCHAR  128  dup(?)
PIN_INFO		ENDS

externdef		IID_IPin:IID

.comdef IPin

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Connect		proc :ptr, :ptr
    ReceiveConnection	proc :ptr, :ptr
    Disconnect		proc
    ConnectedTo		proc :ptr
    ConnectionMediaType proc :ptr
    QueryPinInfo	proc :ptr
    QueryDirection	proc :ptr
    QueryId		proc :ptr
    QueryAccept		proc :ptr
    EnumMediaTypes	proc :ptr
    QueryInternalConnections proc :ptr, :ptr
    EndOfStream		proc
    BeginFlush		proc
    EndFlush		proc
    NewSegment		proc :REFERENCE_TIME, :REFERENCE_TIME, :REAL8
    .ends

endif

PPIN			typedef ptr IPin

externdef		__MIDL_itf_strmif_0000_0002_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0002_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumPins_INTERFACE_DEFINED__
__IEnumPins_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumPins:IID

.comdef IEnumPins

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

PENUMPINS		typedef ptr IEnumPins

externdef		__MIDL_itf_strmif_0000_0003_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0003_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumMediaTypes_INTERFACE_DEFINED__
__IEnumMediaTypes_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumMediaTypes:IID

.comdef IEnumMediaTypes

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

PENUMMEDIATYPES		typedef ptr IEnumMediaTypes

externdef		__MIDL_itf_strmif_0000_0004_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0004_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFilterGraph_INTERFACE_DEFINED__
__IFilterGraph_INTERFACE_DEFINED__ equ 1

externdef		IID_IFilterGraph:IID

.comdef IFilterGraph

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddFilter		proc :ptr, :LPCWSTR
    RemoveFilter	proc :ptr
    EnumFilters		proc :ptr
    FindFilterByName	proc :LPCWSTR, :ptr
    ConnectDirect	proc :ptr, :ptr, :ptr
    Reconnect		proc :ptr
    Disconnect		proc :ptr
    SetDefaultSyncSource proc
    .ends

endif

PFILTERGRAPH		typedef ptr IFilterGraph

externdef		__MIDL_itf_strmif_0000_0005_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0005_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumFilters_INTERFACE_DEFINED__
__IEnumFilters_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumFilters:IID

.comdef IEnumFilters

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

PENUMFILTERS		typedef ptr IEnumFilters

externdef		__MIDL_itf_strmif_0000_0006_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0006_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMediaFilter_INTERFACE_DEFINED__
__IMediaFilter_INTERFACE_DEFINED__ equ 1

FILTER_STATE		typedef SDWORD
State_Stopped		equ 0
State_Paused		equ ( State_Stopped + 1 )
State_Running		equ ( State_Paused + 1 )

externdef		IID_IMediaFilter:IID


.comdef IMediaFilter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetClassID		proc :ptr
    Stop		proc
    _Pause		proc
    Run			proc :REFERENCE_TIME
    GetState		proc :DWORD, :ptr
    SetSyncSource	proc :ptr
    GetSyncSource	proc :ptr
    .ends

endif

PMEDIAFILTER		typedef ptr IMediaFilter

externdef		__MIDL_itf_strmif_0000_0007_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0007_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBaseFilter_INTERFACE_DEFINED__
__IBaseFilter_INTERFACE_DEFINED__ equ 1

FILTER_INFO		STRUC
achName			WCHAR  128  dup(?)
pGraph			PFILTERGRAPH ?
FILTER_INFO		ENDS

externdef		IID_IBaseFilter:IID

.comdef IBaseFilter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetClassID		proc :ptr
    Stop		proc
    _Pause		proc
    Run			proc :REFERENCE_TIME
    GetState		proc :DWORD, :ptr
    SetSyncSource	proc :ptr
    GetSyncSource	proc :ptr
    EnumPins		proc :ptr
    FindPin		proc :LPCWSTR, :ptr
    QueryFilterInfo	proc :ptr
    JoinFilterGraph	proc :ptr, :LPCWSTR
    QueryVendorInfo	proc :ptr
    .ends

endif

PFILTER			typedef ptr IBaseFilter

externdef		__MIDL_itf_strmif_0000_0008_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0008_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IReferenceClock_INTERFACE_DEFINED__
__IReferenceClock_INTERFACE_DEFINED__ equ 1

externdef		IID_IReferenceClock:IID

.comdef IReferenceClock

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTime		proc :ptr
    AdviseTime		proc :REFERENCE_TIME, :REFERENCE_TIME, :HEVENT, :ptr
    AdvisePeriodic	proc :REFERENCE_TIME, :REFERENCE_TIME, :HSEMAPHORE, :ptr
    Unadvise		proc :DWORD_PTR
    .ends

endif

PREFERENCECLOCK		typedef ptr IReferenceClock

externdef		__MIDL_itf_strmif_0000_0009_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0009_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IReferenceClockTimerControl_INTERFACE_DEFINED__
__IReferenceClockTimerControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IReferenceClockTimerControl:IID

.comdef IReferenceClockTimerControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetDefaultTimerResolution proc :REFERENCE_TIME
    GetDefaultTimerResolution proc :ptr
    .ends

endif

ifndef __IReferenceClock2_INTERFACE_DEFINED__
__IReferenceClock2_INTERFACE_DEFINED__ equ 1

externdef		IID_IReferenceClock2:IID

.comdef IReferenceClock2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTime		proc :ptr
    AdviseTime		proc :REFERENCE_TIME, :REFERENCE_TIME, :HEVENT, :ptr
    AdvisePeriodic	proc :REFERENCE_TIME, :REFERENCE_TIME, :HSEMAPHORE, :ptr
    Unadvise		proc :DWORD_PTR
    .ends

endif

PREFERENCECLOCK2	typedef ptr IReferenceClock2

externdef		__MIDL_itf_strmif_0000_0011_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0011_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMediaSample_INTERFACE_DEFINED__
__IMediaSample_INTERFACE_DEFINED__ equ 1

externdef		IID_IMediaSample:IID

.comdef IMediaSample

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPointer		proc :ptr
    GetSize		proc
    GetTime		proc :ptr, :ptr
    SetTime		proc :ptr, :ptr
    IsSyncPoint		proc
    SetSyncPoint	proc :BOOL
    IsPreroll		proc
    SetPreroll		proc :BOOL
    GetActualDataLength proc
    SetActualDataLength proc :LONG
    GetMediaType	proc :ptr
    SetMediaType	proc :ptr
    IsDiscontinuity	proc
    SetDiscontinuity	proc :BOOL
    GetMediaTime	proc :ptr, :ptr
    SetMediaTime	proc :ptr, :ptr
    .ends

endif

PMEDIASAMPLE		typedef ptr IMediaSample

AM_SAMPLE_PROPERTY_FLAGS typedef SDWORD
AM_SAMPLE_SPLICEPOINT	equ 0x1
AM_SAMPLE_PREROLL	equ 0x2
AM_SAMPLE_DATADISCONTINUITY equ 0x4
AM_SAMPLE_TYPECHANGED	equ 0x8
AM_SAMPLE_TIMEVALID	equ 0x10
AM_SAMPLE_TIMEDISCONTINUITY equ 0x40
AM_SAMPLE_FLUSH_ON_PAUSE equ 0x80
AM_SAMPLE_STOPVALID	equ 0x100
AM_SAMPLE_ENDOFSTREAM	equ 0x200
AM_STREAM_MEDIA		equ 0
AM_STREAM_CONTROL	equ 1
AM_SAMPLE2_PROPERTIES	STRUC
cbData			dd ?
dwTypeSpecificFlags	dd ?
dwSampleFlags		dd ?
lActual			LONG ?
tStart			REFERENCE_TIME ?
tStop			REFERENCE_TIME ?
dwStreamId		dd ?
pMediaType		PAM_MEDIA_TYPE ?
pbBuffer		LPBYTE ?
cbBuffer		LONG ?
AM_SAMPLE2_PROPERTIES	ENDS

externdef		__MIDL_itf_strmif_0000_0012_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0012_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMediaSample2_INTERFACE_DEFINED__
__IMediaSample2_INTERFACE_DEFINED__ equ 1

externdef		IID_IMediaSample2:IID

.comdef IMediaSample2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPointer		proc :ptr
    GetSize		proc
    GetTime		proc :ptr, :ptr
    SetTime		proc :ptr, :ptr
    IsSyncPoint		proc
    SetSyncPoint	proc :BOOL
    IsPreroll		proc
    SetPreroll		proc :BOOL
    GetActualDataLength proc
    SetActualDataLength proc :LONG
    GetMediaType	proc :ptr
    SetMediaType	proc :ptr
    IsDiscontinuity	proc
    SetDiscontinuity	proc :BOOL
    GetMediaTime	proc :ptr, :ptr
    SetMediaTime	proc :ptr, :ptr
    GetProperties	proc :DWORD, :ptr
    SetProperties	proc :DWORD, :ptr
    .ends

endif

PMEDIASAMPLE2		typedef ptr IMediaSample2

externdef		__MIDL_itf_strmif_0000_0013_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0013_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMediaSample2Config_INTERFACE_DEFINED__
__IMediaSample2Config_INTERFACE_DEFINED__ equ 1

externdef		IID_IMediaSample2Config:IID

.comdef IMediaSample2Config

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetSurface		proc :ptr
    .ends

endif

AM_GBF_PREVFRAMESKIPPED equ 1
AM_GBF_NOTASYNCPOINT	equ 2
AM_GBF_NOWAIT		equ 4
AM_GBF_NODDSURFACELOCK	equ 8

externdef		__MIDL_itf_strmif_0000_0014_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0014_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMemAllocator_INTERFACE_DEFINED__
__IMemAllocator_INTERFACE_DEFINED__ equ 1

externdef		IID_IMemAllocator:IID

.comdef IMemAllocator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetProperties	proc :ptr, :ptr
    GetProperties	proc :ptr
    Commit		proc
    Decommit		proc
    GetBuffer		proc :ptr, :ptr, :ptr, :DWORD
    ReleaseBuffer	proc :ptr
    .ends

endif

PMEMALLOCATOR		typedef ptr IMemAllocator

externdef		__MIDL_itf_strmif_0000_0015_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0015_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMemAllocatorCallbackTemp_INTERFACE_DEFINED__
__IMemAllocatorCallbackTemp_INTERFACE_DEFINED__ equ 1

externdef		IID_IMemAllocatorCallbackTemp:IID

.comdef IMemAllocatorCallbackTemp

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetProperties	proc :ptr, :ptr
    GetProperties	proc :ptr
    Commit		proc
    Decommit		proc
    GetBuffer		proc :ptr, :ptr, :ptr, :DWORD
    ReleaseBuffer	proc :ptr
    SetNotify		proc :ptr
    GetFreeCount	proc :ptr
    .ends

endif

ifndef __IMemAllocatorNotifyCallbackTemp_INTERFACE_DEFINED__
__IMemAllocatorNotifyCallbackTemp_INTERFACE_DEFINED__ equ 1

externdef		IID_IMemAllocatorNotifyCallbackTemp:IID

.comdef IMemAllocatorNotifyCallbackTemp

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    NotifyRelease	proc
    .ends

endif

ifndef __IMemInputPin_INTERFACE_DEFINED__
__IMemInputPin_INTERFACE_DEFINED__ equ 1

externdef		IID_IMemInputPin:IID

.comdef IMemInputPin

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetAllocator	proc :ptr
    NotifyAllocator	proc :ptr, :BOOL
    GetAllocatorRequirements proc :ptr
    Receive		proc :ptr
    ReceiveMultiple	proc
    ReceiveCanBlock	proc
    .ends

endif

PMEMINPUTPIN		typedef ptr IMemInputPin

externdef		__MIDL_itf_strmif_0000_0018_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0018_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMovieSetup_INTERFACE_DEFINED__
__IAMovieSetup_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMovieSetup:IID

.comdef IAMovieSetup

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Register		proc
    Unregister		proc
    .ends

endif

PAMOVIESETUP		typedef ptr IAMovieSetup

AM_SEEKING_SeekingFlags typedef SDWORD
AM_SEEKING_NoPositioning equ 0
AM_SEEKING_AbsolutePositioning equ 0x1
AM_SEEKING_RelativePositioning equ 0x2
AM_SEEKING_IncrementalPositioning equ 0x3
AM_SEEKING_PositioningBitsMask equ 0x3
AM_SEEKING_SeekToKeyFrame equ 0x4
AM_SEEKING_ReturnTime	equ 0x8
AM_SEEKING_Segment	equ 0x10
AM_SEEKING_NoFlush	equ 0x20

AM_SEEKING_SeekingCapabilities typedef SDWORD
AM_SEEKING_CanSeekAbsolute equ 0x1
AM_SEEKING_CanSeekForwards equ 0x2
AM_SEEKING_CanSeekBackwards equ 0x4
AM_SEEKING_CanGetCurrentPos equ 0x8
AM_SEEKING_CanGetStopPos equ 0x10
AM_SEEKING_CanGetDuration equ 0x20
AM_SEEKING_CanPlayBackwards equ 0x40
AM_SEEKING_CanDoSegments equ 0x80
AM_SEEKING_Source	equ 0x100

externdef		__MIDL_itf_strmif_0000_0019_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0019_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMediaSeeking_INTERFACE_DEFINED__
__IMediaSeeking_INTERFACE_DEFINED__ equ 1

externdef		IID_IMediaSeeking:IID

.comdef IMediaSeeking

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCapabilities	proc :ptr
    CheckCapabilities	proc :ptr
    IsFormatSupported	proc :ptr
    QueryPreferredFormat proc :ptr
    GetTimeFormat	proc :ptr
    IsUsingTimeFormat	proc :ptr
    SetTimeFormat	proc :ptr
    GetDuration		proc :ptr
    GetStopPosition	proc :ptr
    GetCurrentPosition	proc :ptr
    ConvertTimeFormat	proc :ptr, :ptr, :LONGLONG, :ptr
    SetPositions	proc :ptr, :DWORD, :ptr, :DWORD
    GetPositions	proc :ptr, :ptr
    GetAvailable	proc :ptr, :ptr
    SetRate		proc :REAL8
    GetRate		proc :ptr
    GetPreroll		proc :ptr
    .ends

endif

PMEDIASEEKING		typedef ptr IMediaSeeking

AM_MEDIAEVENT_FLAGS	typedef SDWORD
AM_MEDIAEVENT_NONOTIFY	equ 0x01

REGFILTER		STRUC
Clsid			CLSID <>
_Name			LPWSTR ?
REGFILTER		ENDS

externdef		__MIDL_itf_strmif_0000_0020_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0020_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumRegFilters_INTERFACE_DEFINED__
__IEnumRegFilters_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumRegFilters:IID

.comdef IEnumRegFilters

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

PENUMREGFILTERS		typedef ptr IEnumRegFilters

externdef		__MIDL_itf_strmif_0000_0021_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0021_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFilterMapper_INTERFACE_DEFINED__
__IFilterMapper_INTERFACE_DEFINED__ equ 1

_MIDL_IFilterMapper_0001 typedef SDWORD
MERIT_PREFERRED		equ 0x800000
MERIT_NORMAL		equ 0x600000
MERIT_UNLIKELY		equ 0x400000
MERIT_DO_NOT_USE	equ 0x200000
MERIT_SW_COMPRESSOR	equ 0x100000
MERIT_HW_COMPRESSOR	equ 0x100050

externdef		IID_IFilterMapper:IID

.comdef IFilterMapper

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    RegisterFilter	proc :CLSID, :LPCWSTR, :DWORD
    RegisterFilterInstance proc :CLSID, :LPCWSTR, :ptr
    RegisterPin		proc :CLSID, :LPCWSTR, :BOOL, :BOOL, :BOOL, :BOOL, :CLSID, :LPCWSTR
    RegisterPinType	proc :CLSID, :LPCWSTR, :CLSID, :CLSID
    UnregisterFilter	proc :CLSID
    UnregisterFilterInstance proc :CLSID
    UnregisterPin	proc :CLSID, :LPCWSTR
    EnumMatchingFilters proc :ptr, :DWORD, :BOOL, :CLSID, :CLSID, :BOOL, :BOOL, :CLSID, :CLSID
    .ends

endif

REGPINTYPES		STRUC
clsMajorType		LPCLSID ?
clsMinorType		LPCLSID ?
REGPINTYPES		ENDS
PREGPINTYPES		typedef ptr REGPINTYPES

REGFILTERPINS		STRUC
strName			LPWSTR ?
bRendered		BOOL ?
bOutput			BOOL ?
bZero			BOOL ?
bMany			BOOL ?
clsConnectsToFilter	LPCLSID ?
strConnectsToPin	LPWSTR ?
nMediaTypes		UINT ?
lpMediaType		PREGPINTYPES ?
REGFILTERPINS		ENDS
PREGFILTERPINS		typedef ptr REGFILTERPINS

REGPINMEDIUM		STRUC
clsMedium		CLSID <>
dw1			dd ?
dw2			dd ?
REGPINMEDIUM		ENDS
PREGPINMEDIUM		typedef ptr REGPINMEDIUM

_MIDL___MIDL_itf_strmif_0000_0022_0001 typedef SDWORD
REG_PINFLAG_B_ZERO	equ 0x1
REG_PINFLAG_B_RENDERER	equ 0x2
REG_PINFLAG_B_MANY	equ 0x4
REG_PINFLAG_B_OUTPUT	equ 0x8

REGFILTERPINS2		STRUC
dwFlags			dd ?
cInstances		UINT ?
nMediaTypes		UINT ?
lpMediaType		PREGPINTYPES ?
nMediums		UINT ?
lpMedium		PREGPINMEDIUM ?
clsPinCategory		LPCLSID ?
REGFILTERPINS2		ENDS
PREGFILTERPINS2		typedef ptr REGFILTERPINS2

REGFILTER2		STRUC
dwVersion		dd ?
dwMerit			dd ?
UNION
 STRUC
  cPins			ULONG ?
  rgPins		PREGFILTERPINS ?
 ENDS
 STRUC
  cPins2		ULONG ?
  rgPins2		PREGFILTERPINS2 ?
 ENDS
ENDS
REGFILTER2		ENDS

externdef		__MIDL_itf_strmif_0000_0022_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0022_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFilterMapper2_INTERFACE_DEFINED__
__IFilterMapper2_INTERFACE_DEFINED__ equ 1

externdef		IID_IFilterMapper2:IID

.comdef IFilterMapper2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateCategory	proc :REFCLSID, :DWORD, :LPCWSTR
    UnregisterFilter	proc :ptr, :LPCOLESTR, :REFCLSID
    RegisterFilter	proc :REFCLSID, :LPCWSTR, :ptr, :ptr, :LPCOLESTR, :ptr
    EnumMatchingFilters proc :ptr, :DWORD, :BOOL, :DWORD, :BOOL, :DWORD, :ptr, :ptr, :ptr
    .ends

endif

ifndef __IFilterMapper3_INTERFACE_DEFINED__
__IFilterMapper3_INTERFACE_DEFINED__ equ 1

externdef		IID_IFilterMapper3:IID

.comdef IFilterMapper3

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateCategory	proc :REFCLSID, :DWORD, :LPCWSTR
    UnregisterFilter	proc :ptr, :LPCOLESTR, :REFCLSID
    RegisterFilter	proc :REFCLSID, :LPCWSTR, :ptr, :ptr, :LPCOLESTR, :ptr
    EnumMatchingFilters proc :ptr, :DWORD, :BOOL, :DWORD, :BOOL, :DWORD, :ptr, :ptr, :ptr
    GetICreateDevEnum	proc :ptr
    .ends

endif

QualityMessageType	typedef SDWORD
Famine			equ 0
Flood			equ ( Famine + 1 )

Quality			STRUC
_Type			QualityMessageType ?
Proportion		LONG ?
Late			REFERENCE_TIME ?
TimeStamp		REFERENCE_TIME ?
Quality			ENDS

PQUALITYCONTROL		typedef ptr IQualityControl

externdef		__MIDL_itf_strmif_0000_0024_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0024_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IQualityControl_INTERFACE_DEFINED__
__IQualityControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IQualityControl:IID

.comdef IQualityControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Notify		proc :ptr, :Quality
    SetSink		proc :ptr
    .ends

endif

_MIDL___MIDL_itf_strmif_0000_0025_0001 typedef SDWORD
CK_NOCOLORKEY		equ 0
CK_INDEX		equ 0x1
CK_RGB			equ 0x2
COLORKEY		STRUC
KeyType			dd ?
PaletteIndex		dd ?
LowColorValue		COLORREF ?
HighColorValue		COLORREF ?
COLORKEY		ENDS

_MIDL___MIDL_itf_strmif_0000_0025_0002 typedef SDWORD
ADVISE_NONE		equ 0
ADVISE_CLIPPING		equ 0x1
ADVISE_PALETTE		equ 0x2
ADVISE_COLORKEY		equ 0x4
ADVISE_POSITION		equ 0x8
ADVISE_DISPLAY_CHANGE	equ 0x10
ADVISE_ALL		equ ADVISE_CLIPPING OR ADVISE_PALETTE OR ADVISE_COLORKEY OR ADVISE_POSITION
ADVISE_ALL2		equ ADVISE_ALL OR ADVISE_DISPLAY_CHANGE

ifndef _WINGDI_
RGNDATAHEADER		STRUC
dwSize			dd ?
iType			dd ?
nCount			dd ?
nRgnSize		dd ?
rcBound			RECT ?
RGNDATAHEADER		ENDS

RGNDATA			STRUC
rdh			RGNDATAHEADER ?
Buffer			char  1	 dup(?)
RGNDATA			ENDS

endif

externdef		__MIDL_itf_strmif_0000_0025_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0025_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOverlayNotify_INTERFACE_DEFINED__
__IOverlayNotify_INTERFACE_DEFINED__ equ 1

externdef		IID_IOverlayNotify:IID

.comdef IOverlayNotify

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnPaletteChange	proc :DWORD, :ptr
    OnClipChange	proc :ptr, :ptr, :ptr
    OnColorKeyChange	proc :ptr
    OnPositionChange	proc :ptr, :ptr
    .ends

endif

POVERLAYNOTIFY		typedef ptr IOverlayNotify

if NOT defined(HMONITOR_DECLARED) AND NOT defined(HMONITOR) AND (WINVER LT 0x0500)
HMONITOR_DECLARED equ 1
if 0
HMONITOR		typedef HANDLE
endif
DECLARE_HANDLE(HMONITOR);
endif

externdef		__MIDL_itf_strmif_0000_0026_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0026_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOverlayNotify2_INTERFACE_DEFINED__
__IOverlayNotify2_INTERFACE_DEFINED__ equ 1

externdef		IID_IOverlayNotify2:IID

.comdef IOverlayNotify2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnPaletteChange	proc :DWORD, :ptr
    OnClipChange	proc :ptr, :ptr, :ptr
    OnColorKeyChange	proc :ptr
    OnPositionChange	proc :ptr, :ptr
    OnDisplayChange	proc :HMONITOR
    .ends

endif

POVERLAYNOTIFY2		typedef ptr IOverlayNotify2

externdef		__MIDL_itf_strmif_0000_0027_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0027_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOverlay_INTERFACE_DEFINED__
__IOverlay_INTERFACE_DEFINED__ equ 1

externdef		IID_IOverlay:IID

.comdef IOverlay

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPalette		proc :ptr, :ptr
    SetPalette		proc :DWORD, :ptr
    GetDefaultColorKey	proc :ptr
    GetColorKey		proc :ptr
    SetColorKey		proc :ptr
    GetWindowHandle	proc :ptr
    GetClipList		proc :ptr, :ptr, :ptr
    GetVideoPosition	proc :ptr, :ptr
    Advise		proc :ptr, :DWORD
    Unadvise		proc
    .ends

endif

POVERLAY		typedef ptr IOverlay

externdef		__MIDL_itf_strmif_0000_0028_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0028_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMediaEventSink_INTERFACE_DEFINED__
__IMediaEventSink_INTERFACE_DEFINED__ equ 1

externdef		IID_IMediaEventSink:IID

.comdef IMediaEventSink

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Notify		proc :LONG, :LONG_PTR, :LONG_PTR
    .ends

endif

PMEDIAEVENTSINK		typedef ptr IMediaEventSink

externdef		__MIDL_itf_strmif_0000_0029_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0029_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileSourceFilter_INTERFACE_DEFINED__
__IFileSourceFilter_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileSourceFilter:IID

.comdef IFileSourceFilter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Load		proc :LPCOLESTR, :ptr
    GetCurFile		proc :ptr, :ptr
    .ends

endif

PFILTERFILESOURCE	typedef ptr IFileSourceFilter

externdef		__MIDL_itf_strmif_0000_0030_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0030_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileSinkFilter_INTERFACE_DEFINED__
__IFileSinkFilter_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileSinkFilter:IID

.comdef IFileSinkFilter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetFileName		proc :LPCOLESTR, :ptr
    GetCurFile		proc :ptr, :ptr
    .ends

endif

PFILTERFILESINK		typedef ptr IFileSinkFilter

externdef		__MIDL_itf_strmif_0000_0031_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0031_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileSinkFilter2_INTERFACE_DEFINED__
__IFileSinkFilter2_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileSinkFilter2:IID

.comdef IFileSinkFilter2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetFileName		proc :LPCOLESTR, :ptr
    GetCurFile		proc :ptr, :ptr
    SetMode		proc :DWORD
    GetMode		proc :ptr
    .ends

endif

PFILESINKFILTER2	typedef ptr IFileSinkFilter2

AM_FILESINK_FLAGS	typedef SDWORD
AM_FILE_OVERWRITE	equ 0x1

externdef		__MIDL_itf_strmif_0000_0032_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0032_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IGraphBuilder_INTERFACE_DEFINED__
__IGraphBuilder_INTERFACE_DEFINED__ equ 1

externdef		IID_IGraphBuilder:IID

.comdef IGraphBuilder

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddFilter		proc :ptr, :LPCWSTR
    RemoveFilter	proc :ptr
    EnumFilters		proc :ptr
    FindFilterByName	proc :LPCWSTR, :ptr
    ConnectDirect	proc :ptr, :ptr, :ptr
    Reconnect		proc :ptr
    Disconnect		proc :ptr
    SetDefaultSyncSource proc
    Connect		proc :ptr, :ptr
    Render		proc :ptr
    RenderFile		proc :LPCWSTR, :LPCWSTR
    AddSourceFilter	proc :LPCWSTR, :LPCWSTR, :ptr
    SetLogFile		proc :DWORD_PTR
    Abort		proc
    ShouldOperationContinue proc
    .ends

endif

ifndef __ICaptureGraphBuilder_INTERFACE_DEFINED__
__ICaptureGraphBuilder_INTERFACE_DEFINED__ equ 1

externdef		IID_ICaptureGraphBuilder:IID

.comdef ICaptureGraphBuilder

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetFiltergraph	proc :ptr
    GetFiltergraph	proc :ptr
    SetOutputFileName	proc :ptr, :LPCOLESTR, :ptr, :ptr
    FindInterface	proc :ptr, :ptr, :REFIID, :ptr
    RenderStream	proc :ptr, :ptr, :ptr, :ptr
    ControlStream	proc :ptr, :ptr, :ptr, :ptr, :WORD, :WORD
    AllocCapFile	proc :LPCOLESTR, :DWORDLONG
    CopyCaptureFile	proc :LPOLESTR, :LPOLESTR, :SINT, :ptr
    .ends

;void
ICaptureGraphBuilder_RemoteFindInterface_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


endif

ifndef __IAMCopyCaptureFileProgress_INTERFACE_DEFINED__
__IAMCopyCaptureFileProgress_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMCopyCaptureFileProgress:IID

.comdef IAMCopyCaptureFileProgress

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Progress		proc :SINT
    .ends

endif

ifndef __ICaptureGraphBuilder2_INTERFACE_DEFINED__
__ICaptureGraphBuilder2_INTERFACE_DEFINED__ equ 1

externdef		IID_ICaptureGraphBuilder2:IID

.comdef ICaptureGraphBuilder2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetFiltergraph	proc :ptr
    GetFiltergraph	proc :ptr
    SetOutputFileName	proc :ptr, :LPCOLESTR, :ptr, :ptr
    FindInterface	proc :ptr, :ptr, :ptr, :REFIID, :ptr
    RenderStream	proc :ptr, :ptr, :ptr, :ptr, :ptr
    ControlStream	proc :ptr, :ptr, :ptr, :ptr, :ptr, :WORD, :WORD
    AllocCapFile	proc :LPCOLESTR, :DWORDLONG
    CopyCaptureFile	proc :LPOLESTR, :LPOLESTR, :SINT, :ptr
    FindPin		proc :ptr, :PIN_DIRECTION, :ptr, :ptr, :BOOL, :SINT, :ptr
    .ends

;void
ICaptureGraphBuilder2_RemoteFindInterface_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

AM_RENSDEREXFLAGS	typedef SDWORD
AM_RENDEREX_RENDERTOEXISTINGRENDERERS equ 0x1

externdef		__MIDL_itf_strmif_0000_0036_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0036_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFilterGraph2_INTERFACE_DEFINED__
__IFilterGraph2_INTERFACE_DEFINED__ equ 1

externdef		IID_IFilterGraph2:IID

.comdef IFilterGraph2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddFilter		proc :ptr, :LPCWSTR
    RemoveFilter	proc :ptr
    EnumFilters		proc :ptr
    FindFilterByName	proc :LPCWSTR, :ptr
    ConnectDirect	proc :ptr, :ptr, :ptr
    Reconnect		proc :ptr
    Disconnect		proc :ptr
    SetDefaultSyncSource proc
    Connect		proc :ptr, :ptr
    Render		proc :ptr
    RenderFile		proc :LPCWSTR, :LPCWSTR
    AddSourceFilter	proc :LPCWSTR, :LPCWSTR, :ptr
    SetLogFile		proc :DWORD_PTR
    Abort		proc
    ShouldOperationContinue proc
    AddSourceFilterForMoniker proc :ptr, :ptr, :LPCWSTR, :ptr
    ReconnectEx		proc :ptr, :ptr
    RenderEx		proc :ptr, :DWORD, :ptr
    .ends

endif

ifndef __IFilterGraph3_INTERFACE_DEFINED__
__IFilterGraph3_INTERFACE_DEFINED__ equ 1

externdef		IID_IFilterGraph3:IID

.comdef IFilterGraph3

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddFilter		proc :ptr, :LPCWSTR
    RemoveFilter	proc :ptr
    EnumFilters		proc :ptr
    FindFilterByName	proc :LPCWSTR, :ptr
    ConnectDirect	proc :ptr, :ptr, :ptr
    Reconnect		proc :ptr
    Disconnect		proc :ptr
    SetDefaultSyncSource proc
    Connect		proc :ptr, :ptr
    Render		proc :ptr
    RenderFile		proc :LPCWSTR, :LPCWSTR
    AddSourceFilter	proc :LPCWSTR, :LPCWSTR, :ptr
    SetLogFile		proc :DWORD_PTR
    Abort		proc
    ShouldOperationContinue proc
    AddSourceFilterForMoniker proc :ptr, :ptr, :LPCWSTR, :ptr
    ReconnectEx		proc :ptr, :ptr
    RenderEx		proc :ptr, :DWORD, :ptr
    SetSyncSourceEx	proc :ptr, :ptr, :ptr
    .ends

endif

ifndef __IStreamBuilder_INTERFACE_DEFINED__
__IStreamBuilder_INTERFACE_DEFINED__ equ 1

externdef		IID_IStreamBuilder:IID

.comdef IStreamBuilder

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Render		proc :ptr, :ptr
    Backout		proc :ptr, :ptr
    .ends

endif

ifndef __IAsyncReader_INTERFACE_DEFINED__
__IAsyncReader_INTERFACE_DEFINED__ equ 1

externdef		IID_IAsyncReader:IID

.comdef IAsyncReader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    RequestAllocator	proc :ptr, :ptr, :ptr
    Request		proc :ptr, :DWORD_PTR
    WaitForNext		proc :DWORD, :ptr, :ptr
    SyncReadAligned	proc :ptr
    SyncRead		proc :LONGLONG, :LONG, :ptr
    _Length		proc :ptr, :ptr
    BeginFlush		proc
    EndFlush		proc
    .ends

endif

ifndef __IGraphVersion_INTERFACE_DEFINED__
__IGraphVersion_INTERFACE_DEFINED__ equ 1

externdef		IID_IGraphVersion:IID

.comdef IGraphVersion

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryVersion	proc :ptr
    .ends

endif

ifndef __IResourceConsumer_INTERFACE_DEFINED__
__IResourceConsumer_INTERFACE_DEFINED__ equ 1

externdef		IID_IResourceConsumer:IID

.comdef IResourceConsumer

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AcquireResource	proc :LONG
    ReleaseResource	proc :LONG
    .ends

endif

ifndef __IResourceManager_INTERFACE_DEFINED__
__IResourceManager_INTERFACE_DEFINED__ equ 1

externdef		IID_IResourceManager:IID

.comdef IResourceManager

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Register		proc :LPCWSTR, :LONG, :ptr
    RegisterGroup	proc :LPCWSTR, :LONG
    RequestResource	proc :LONG, :ptr, :ptr
    NotifyAcquire	proc :LONG, :ptr, :HRESULT
    NotifyRelease	proc :LONG, :ptr, :BOOL
    CancelRequest	proc :LONG, :ptr
    SetFocus		proc :ptr
    ReleaseFocus	proc :ptr
    .ends

endif

ifndef __IDistributorNotify_INTERFACE_DEFINED__
__IDistributorNotify_INTERFACE_DEFINED__ equ 1

externdef		IID_IDistributorNotify:IID

.comdef IDistributorNotify

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Stop		proc
    _Pause		proc
    Run			proc :REFERENCE_TIME
    SetSyncSource	proc :ptr
    NotifyGraphChange	proc
    .ends

endif

AM_STREAM_INFO_FLAGS	typedef SDWORD
AM_STREAM_INFO_START_DEFINED equ 0x1
AM_STREAM_INFO_STOP_DEFINED equ 0x2
AM_STREAM_INFO_DISCARDING equ 0x4
AM_STREAM_INFO_STOP_SEND_EXTRA equ 0x10

AM_STREAM_INFO		STRUC
tStart			REFERENCE_TIME ?
tStop			REFERENCE_TIME ?
dwStartCookie		dd ?
dwStopCookie		dd ?
dwFlags			dd ?
AM_STREAM_INFO		ENDS

externdef		__MIDL_itf_strmif_0000_0044_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0044_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMStreamControl_INTERFACE_DEFINED__
__IAMStreamControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMStreamControl:IID

.comdef IAMStreamControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    StartAt		proc :ptr, :DWORD
    StopAt		proc :ptr, :BOOL, :DWORD
    GetInfo		proc :ptr
    .ends

endif

ifndef __ISeekingPassThru_INTERFACE_DEFINED__
__ISeekingPassThru_INTERFACE_DEFINED__ equ 1

externdef		IID_ISeekingPassThru:IID

.comdef ISeekingPassThru

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Init		proc :BOOL, :ptr
    .ends

endif

ifndef __IAMStreamConfig_INTERFACE_DEFINED__
__IAMStreamConfig_INTERFACE_DEFINED__ equ 1

VIDEO_STREAM_CONFIG_CAPS STRUC
guid			GUID <>
VideoStandard		ULONG ?
InputSize		SIZEL <>
MinCroppingSize		SIZEL <>
MaxCroppingSize		SIZEL <>
CropGranularityX	SINT ?
CropGranularityY	SINT ?
CropAlignX		SINT ?
CropAlignY		SINT ?
MinOutputSize		SIZEL <>
MaxOutputSize		SIZEL <>
OutputGranularityX	SINT ?
OutputGranularityY	SINT ?
StretchTapsX		SINT ?
StretchTapsY		SINT ?
ShrinkTapsX		SINT ?
ShrinkTapsY		SINT ?
MinFrameInterval	LONGLONG ?
MaxFrameInterval	LONGLONG ?
MinBitsPerSecond	LONG ?
MaxBitsPerSecond	LONG ?
VIDEO_STREAM_CONFIG_CAPS ENDS

AUDIO_STREAM_CONFIG_CAPS STRUC
guid			GUID <>
MinimumChannels		ULONG ?
MaximumChannels		ULONG ?
ChannelsGranularity	ULONG ?
MinimumBitsPerSample	ULONG ?
MaximumBitsPerSample	ULONG ?
BitsPerSampleGranularity ULONG ?
MinimumSampleFrequency	ULONG ?
MaximumSampleFrequency	ULONG ?
SampleFrequencyGranularity ULONG ?
AUDIO_STREAM_CONFIG_CAPS ENDS

externdef		IID_IAMStreamConfig:IID

.comdef IAMStreamConfig

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetFormat		proc :ptr
    GetFormat		proc :ptr
    GetNumberOfCapabilities proc :ptr, :ptr
    GetStreamCaps	proc :SINT, :ptr, :ptr
    .ends

endif

ifndef __IConfigInterleaving_INTERFACE_DEFINED__
__IConfigInterleaving_INTERFACE_DEFINED__ equ 1

InterleavingMode	typedef SDWORD
INTERLEAVE_NONE		equ 0
INTERLEAVE_CAPTURE	equ ( INTERLEAVE_NONE + 1 )
INTERLEAVE_FULL		equ ( INTERLEAVE_CAPTURE + 1 )
INTERLEAVE_NONE_BUFFERED equ ( INTERLEAVE_FULL + 1 )

externdef		IID_IConfigInterleaving:IID

.comdef IConfigInterleaving

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    put_Mode		proc :InterleavingMode
    get_Mode		proc :ptr
    put_Interleaving	proc :ptr, :ptr
    get_Interleaving	proc :ptr, :ptr
    .ends

endif

ifndef __IConfigAviMux_INTERFACE_DEFINED__
__IConfigAviMux_INTERFACE_DEFINED__ equ 1

externdef		IID_IConfigAviMux:IID

.comdef IConfigAviMux

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetMasterStream	proc :LONG
    GetMasterStream	proc :ptr
    SetOutputCompatibilityIndex proc :BOOL
    GetOutputCompatibilityIndex proc :ptr
    .ends

endif

CompressionCaps		typedef SDWORD
CompressionCaps_CanQuality equ 0x1
CompressionCaps_CanCrunch equ 0x2
CompressionCaps_CanKeyFrame equ 0x4
CompressionCaps_CanBFrame equ 0x8
CompressionCaps_CanWindow equ 0x10

externdef		__MIDL_itf_strmif_0000_0049_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0049_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMVideoCompression_INTERFACE_DEFINED__
__IAMVideoCompression_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMVideoCompression:IID

.comdef IAMVideoCompression

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    put_KeyFrameRate	proc :LONG
    get_KeyFrameRate	proc :ptr
    put_PFramesPerKeyFrame proc :LONG
    get_PFramesPerKeyFrame proc :ptr
    put_Quality		proc :REAL8
    get_Quality		proc :ptr
    put_WindowSize	proc :DWORDLONG
    get_WindowSize	proc :ptr
    GetInfo		proc :LPWSTR, :ptr, :ptr, :ptr, :ptr, :ptr
    OverrideKeyFrame	proc :LONG
    OverrideFrameSize	proc :LONG, :LONG
    .ends

endif

VfwCaptureDialogs	typedef SDWORD
VfwCaptureDialog_Source equ 0x1
VfwCaptureDialog_Format equ 0x2
VfwCaptureDialog_Display equ 0x4

VfwCompressDialogs	typedef SDWORD
VfwCompressDialog_Config equ 0x1
VfwCompressDialog_About equ 0x2
VfwCompressDialog_QueryConfig equ 0x4
VfwCompressDialog_QueryAbout equ 0x8

externdef		__MIDL_itf_strmif_0000_0050_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0050_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMVfwCaptureDialogs_INTERFACE_DEFINED__
__IAMVfwCaptureDialogs_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMVfwCaptureDialogs:IID

.comdef IAMVfwCaptureDialogs

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    HasDialog		proc :SINT
    ShowDialog		proc :SINT, :HWND
    SendDriverMessage	proc :SINT, :SINT, :LONG, :LONG
    .ends

endif

ifndef __IAMVfwCompressDialogs_INTERFACE_DEFINED__
__IAMVfwCompressDialogs_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMVfwCompressDialogs:IID

.comdef IAMVfwCompressDialogs

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ShowDialog		proc :SINT, :HWND
    GetState		proc :LPVOID, :ptr
    SetState		proc
    SendDriverMessage	proc :SINT, :LONG, :LONG
    .ends

endif

ifndef __IAMDroppedFrames_INTERFACE_DEFINED__
__IAMDroppedFrames_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMDroppedFrames:IID

.comdef IAMDroppedFrames

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetNumDropped	proc :ptr
    GetNumNotDropped	proc :ptr
    GetDroppedInfo	proc :LONG, :ptr, :ptr
    GetAverageFrameSize proc :ptr
    .ends

endif

AMF_AUTOMATICGAIN	equ -1.0

externdef		__MIDL_itf_strmif_0000_0053_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0053_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMAudioInputMixer_INTERFACE_DEFINED__
__IAMAudioInputMixer_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMAudioInputMixer:IID

.comdef IAMAudioInputMixer

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    put_Enable		proc :BOOL
    get_Enable		proc :ptr
    put_Mono		proc :BOOL
    get_Mono		proc :ptr
    put_MixLevel	proc :REAL8
    get_MixLevel	proc :ptr
    put_Pan		proc :REAL8
    get_Pan		proc :ptr
    put_Loudness	proc :BOOL
    get_Loudness	proc :ptr
    put_Treble		proc :REAL8
    get_Treble		proc :ptr
    get_TrebleRange	proc :ptr
    put_Bass		proc :REAL8
    get_Bass		proc :ptr
    get_BassRange	proc :ptr
    .ends

endif

ifndef __IAMBufferNegotiation_INTERFACE_DEFINED__
__IAMBufferNegotiation_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMBufferNegotiation:IID

.comdef IAMBufferNegotiation

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SuggestAllocatorProperties proc :ptr
    GetAllocatorProperties proc :ptr
    .ends

endif

AnalogVideoStandard	typedef SDWORD
AnalogVideo_None	equ 0
AnalogVideo_NTSC_M	equ 0x1
AnalogVideo_NTSC_M_J	equ 0x2
AnalogVideo_NTSC_433	equ 0x4
AnalogVideo_PAL_B	equ 0x10
AnalogVideo_PAL_D	equ 0x20
AnalogVideo_PAL_G	equ 0x40
AnalogVideo_PAL_H	equ 0x80
AnalogVideo_PAL_I	equ 0x100
AnalogVideo_PAL_M	equ 0x200
AnalogVideo_PAL_N	equ 0x400
AnalogVideo_PAL_60	equ 0x800
AnalogVideo_SECAM_B	equ 0x1000
AnalogVideo_SECAM_D	equ 0x2000
AnalogVideo_SECAM_G	equ 0x4000
AnalogVideo_SECAM_H	equ 0x8000
AnalogVideo_SECAM_K	equ 0x10000
AnalogVideo_SECAM_K1	equ 0x20000
AnalogVideo_SECAM_L	equ 0x40000
AnalogVideo_SECAM_L1	equ 0x80000
AnalogVideo_PAL_N_COMBO equ 0x100000
AnalogVideoMask_MCE_NTSC equ ((((((AnalogVideo_NTSC_M OR AnalogVideo_NTSC_M_J) OR AnalogVideo_NTSC_433) OR AnalogVideo_PAL_M) OR AnalogVideo_PAL_N) OR AnalogVideo_PAL_60) OR AnalogVideo_PAL_N_COMBO)
AnalogVideoMask_MCE_PAL equ ((((AnalogVideo_PAL_B OR AnalogVideo_PAL_D) OR AnalogVideo_PAL_G) OR AnalogVideo_PAL_H) OR AnalogVideo_PAL_I)
AnalogVideoMask_MCE_SECAM equ (((((((AnalogVideo_SECAM_B OR AnalogVideo_SECAM_D) OR AnalogVideo_SECAM_G) OR AnalogVideo_SECAM_H) OR AnalogVideo_SECAM_K) OR AnalogVideo_SECAM_K1) OR AnalogVideo_SECAM_L) OR AnalogVideo_SECAM_L1)

TunerInputType		typedef SDWORD
TunerInputCable		equ 0
TunerInputAntenna	equ ( TunerInputCable + 1 )

AnalogVideo_NTSC_Mask	equ 0x00000007
AnalogVideo_PAL_Mask	equ 0x00100FF0
AnalogVideo_SECAM_Mask	equ 0x000FF000
VideoCopyProtectionType typedef SDWORD
VideoCopyProtectionMacrovisionBasic equ 0
VideoCopyProtectionMacrovisionCBI equ ( VideoCopyProtectionMacrovisionBasic + 1 )

tagPhysicalConnectorType typedef SDWORD
PhysConn_Video_Tuner	equ 1
PhysConn_Video_Composite equ ( PhysConn_Video_Tuner + 1 )
PhysConn_Video_SVideo	equ ( PhysConn_Video_Composite + 1 )
PhysConn_Video_RGB	equ ( PhysConn_Video_SVideo + 1 )
PhysConn_Video_YRYBY	equ ( PhysConn_Video_RGB + 1 )
PhysConn_Video_SerialDigital equ ( PhysConn_Video_YRYBY + 1 )
PhysConn_Video_ParallelDigital equ ( PhysConn_Video_SerialDigital + 1 )
PhysConn_Video_SCSI	equ ( PhysConn_Video_ParallelDigital + 1 )
PhysConn_Video_AUX	equ ( PhysConn_Video_SCSI + 1 )
PhysConn_Video_1394	equ ( PhysConn_Video_AUX + 1 )
PhysConn_Video_USB	equ ( PhysConn_Video_1394 + 1 )
PhysConn_Video_VideoDecoder equ ( PhysConn_Video_USB + 1 )
PhysConn_Video_VideoEncoder equ ( PhysConn_Video_VideoDecoder + 1 )
PhysConn_Video_SCART	equ ( PhysConn_Video_VideoEncoder + 1 )
PhysConn_Video_Black	equ ( PhysConn_Video_SCART + 1 )
PhysConn_Audio_Tuner	equ 0x1000
PhysConn_Audio_Line	equ ( PhysConn_Audio_Tuner + 1 )
PhysConn_Audio_Mic	equ ( PhysConn_Audio_Line + 1 )
PhysConn_Audio_AESDigital equ ( PhysConn_Audio_Mic + 1 )
PhysConn_Audio_SPDIFDigital equ ( PhysConn_Audio_AESDigital + 1 )
PhysConn_Audio_SCSI	equ ( PhysConn_Audio_SPDIFDigital + 1 )
PhysConn_Audio_AUX	equ ( PhysConn_Audio_SCSI + 1 )
PhysConn_Audio_1394	equ ( PhysConn_Audio_AUX + 1 )
PhysConn_Audio_USB	equ ( PhysConn_Audio_1394 + 1 )
PhysConn_Audio_AudioDecoder equ ( PhysConn_Audio_USB + 1 )

externdef		__MIDL_itf_strmif_0000_0055_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0055_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMAnalogVideoDecoder_INTERFACE_DEFINED__
__IAMAnalogVideoDecoder_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMAnalogVideoDecoder:IID

.comdef IAMAnalogVideoDecoder

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_AvailableTVFormats proc :ptr
    put_TVFormat	proc :LONG
    get_TVFormat	proc :ptr
    get_HorizontalLocked proc :ptr
    put_VCRHorizontalLocking proc :LONG
    get_VCRHorizontalLocking proc :ptr
    get_NumberOfLines	proc :ptr
    put_OutputEnable	proc :LONG
    get_OutputEnable	proc :ptr
    .ends

endif

VideoProcAmpProperty typedef SDWORD
VideoProcAmp_Brightness equ 0
VideoProcAmp_Contrast	equ ( VideoProcAmp_Brightness + 1 )
VideoProcAmp_Hue	equ ( VideoProcAmp_Contrast + 1 )
VideoProcAmp_Saturation equ ( VideoProcAmp_Hue + 1 )
VideoProcAmp_Sharpness	equ ( VideoProcAmp_Saturation + 1 )
VideoProcAmp_Gamma	equ ( VideoProcAmp_Sharpness + 1 )
VideoProcAmp_ColorEnable equ ( VideoProcAmp_Gamma + 1 )
VideoProcAmp_WhiteBalance equ ( VideoProcAmp_ColorEnable + 1 )
VideoProcAmp_BacklightCompensation equ ( VideoProcAmp_WhiteBalance + 1 )
VideoProcAmp_Gain	equ ( VideoProcAmp_BacklightCompensation + 1 )

tagVideoProcAmpFlags	typedef SDWORD
VideoProcAmp_Flags_Auto equ 0x1
VideoProcAmp_Flags_Manual equ 0x2

externdef		__MIDL_itf_strmif_0000_0056_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0056_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMVideoProcAmp_INTERFACE_DEFINED__
__IAMVideoProcAmp_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMVideoProcAmp:IID

.comdef IAMVideoProcAmp

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetRange		proc :LONG, :ptr, :ptr, :ptr, :ptr, :ptr
    Set			proc :LONG, :LONG, :LONG
    Get			proc :LONG, :ptr, :ptr
    .ends

endif

CameraControlProperty typedef SDWORD
CameraControl_Pan	equ 0
CameraControl_Tilt	equ ( CameraControl_Pan + 1 )
CameraControl_Roll	equ ( CameraControl_Tilt + 1 )
CameraControl_Zoom	equ ( CameraControl_Roll + 1 )
CameraControl_Exposure	equ ( CameraControl_Zoom + 1 )
CameraControl_Iris	equ ( CameraControl_Exposure + 1 )
CameraControl_Focus	equ ( CameraControl_Iris + 1 )

tagCameraControlFlags	typedef SDWORD
CameraControl_Flags_Auto equ 0x1
CameraControl_Flags_Manual equ 0x2

externdef		__MIDL_itf_strmif_0000_0057_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0057_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMCameraControl_INTERFACE_DEFINED__
__IAMCameraControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMCameraControl:IID

.comdef IAMCameraControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetRange		proc :LONG, :ptr, :ptr, :ptr, :ptr, :ptr
    Set			proc :LONG, :LONG, :LONG
    Get			proc :LONG, :ptr, :ptr
    .ends

endif

VideoControlFlags	typedef SDWORD
VideoControlFlag_FlipHorizontal equ 0x1
VideoControlFlag_FlipVertical equ 0x2
VideoControlFlag_ExternalTriggerEnable equ 0x4
VideoControlFlag_Trigger equ 0x8

externdef		__MIDL_itf_strmif_0000_0058_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0058_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMVideoControl_INTERFACE_DEFINED__
__IAMVideoControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMVideoControl:IID

.comdef IAMVideoControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCaps		proc :ptr, :ptr
    SetMode		proc :ptr, :LONG
    GetMode		proc :ptr, :ptr
    GetCurrentActualFrameRate proc :ptr, :ptr
    GetMaxAvailableFrameRate proc :ptr, :LONG, :SIZEL, :ptr
    GetFrameRateList	proc :ptr, :LONG, :SIZEL, :ptr, :ptr
    .ends

endif

ifndef __IAMCrossbar_INTERFACE_DEFINED__
__IAMCrossbar_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMCrossbar:IID

.comdef IAMCrossbar

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_PinCounts	proc :ptr, :ptr
    CanRoute		proc :LONG, :LONG
    Route		proc :LONG, :LONG
    get_IsRoutedTo	proc :LONG, :ptr
    get_CrossbarPinInfo proc :BOOL, :LONG, :ptr, :ptr
    .ends

endif

AMTunerSubChannel	typedef SDWORD
AMTUNER_SUBCHAN_NO_TUNE equ -2
AMTUNER_SUBCHAN_DEFAULT equ -1

AMTunerSignalStrength typedef SDWORD
AMTUNER_HASNOSIGNALSTRENGTH equ -1
AMTUNER_NOSIGNAL	equ 0
AMTUNER_SIGNALPRESENT	equ 1

AMTunerModeType		typedef SDWORD
AMTUNER_MODE_DEFAULT	equ 0
AMTUNER_MODE_TV		equ 0x1
AMTUNER_MODE_FM_RADIO	equ 0x2
AMTUNER_MODE_AM_RADIO	equ 0x4
AMTUNER_MODE_DSS	equ 0x8

AMTunerEventType	typedef SDWORD
AMTUNER_EVENT_CHANGED	equ 0x1

externdef		__MIDL_itf_strmif_0000_0060_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0060_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMTuner_INTERFACE_DEFINED__
__IAMTuner_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMTuner:IID

.comdef IAMTuner

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    put_Channel		proc :LONG, :LONG, :LONG
    get_Channel		proc :ptr, :ptr, :ptr
    ChannelMinMax	proc :ptr, :ptr
    put_CountryCode	proc :LONG
    get_CountryCode	proc :ptr
    put_TuningSpace	proc :LONG
    get_TuningSpace	proc :ptr
    Logon		proc :HANDLE
    Logout		proc
    SignalPresent	proc :ptr
    put_Mode		proc :AMTunerModeType
    get_Mode		proc :ptr
    GetAvailableModes	proc :ptr
    RegisterNotificationCallBack proc :ptr, :LONG
    UnRegisterNotificationCallBack proc :ptr
    .ends

endif

ifndef __IAMTunerNotification_INTERFACE_DEFINED__
__IAMTunerNotification_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMTunerNotification:IID

.comdef IAMTunerNotification

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnEvent		proc :AMTunerEventType
    .ends

endif

ifndef __IAMTVTuner_INTERFACE_DEFINED__
__IAMTVTuner_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMTVTuner:IID

.comdef IAMTVTuner

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    put_Channel		proc :LONG, :LONG, :LONG
    get_Channel		proc :ptr, :ptr, :ptr
    ChannelMinMax	proc :ptr, :ptr
    put_CountryCode	proc :LONG
    get_CountryCode	proc :ptr
    put_TuningSpace	proc :LONG
    get_TuningSpace	proc :ptr
    Logon		proc :HANDLE
    Logout		proc
    SignalPresent	proc :ptr
    put_Mode		proc :AMTunerModeType
    get_Mode		proc :ptr
    GetAvailableModes	proc :ptr
    RegisterNotificationCallBack proc :ptr, :LONG
    UnRegisterNotificationCallBack proc :ptr
    get_AvailableTVFormats proc :ptr
    get_TVFormat	proc :ptr
    AutoTune		proc :LONG, :ptr
    StoreAutoTune	proc
    get_NumInputConnections proc :ptr
    put_InputType	proc :LONG, :TunerInputType
    get_InputType	proc :LONG, :ptr
    put_ConnectInput	proc :LONG
    get_ConnectInput	proc :ptr
    get_VideoFrequency	proc :ptr
    get_AudioFrequency	proc :ptr
    .ends

endif

ifndef __IBPCSatelliteTuner_INTERFACE_DEFINED__
__IBPCSatelliteTuner_INTERFACE_DEFINED__ equ 1

externdef		IID_IBPCSatelliteTuner:IID

.comdef IBPCSatelliteTuner

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    put_Channel		proc :LONG, :LONG, :LONG
    get_Channel		proc :ptr, :ptr, :ptr
    ChannelMinMax	proc :ptr, :ptr
    put_CountryCode	proc :LONG
    get_CountryCode	proc :ptr
    put_TuningSpace	proc :LONG
    get_TuningSpace	proc :ptr
    Logon		proc :HANDLE
    Logout		proc
    SignalPresent	proc :ptr
    put_Mode		proc :AMTunerModeType
    get_Mode		proc :ptr
    GetAvailableModes	proc :ptr
    RegisterNotificationCallBack proc :ptr, :LONG
    UnRegisterNotificationCallBack proc :ptr
    get_DefaultSubChannelTypes proc :ptr, :ptr
    put_DefaultSubChannelTypes proc :LONG, :LONG
    IsTapingPermitted	proc
    .ends

endif

TVAudioMode		typedef SDWORD
AMTVAUDIO_MODE_MONO	equ 0x1
AMTVAUDIO_MODE_STEREO	equ 0x2
AMTVAUDIO_MODE_LANG_A	equ 0x10
AMTVAUDIO_MODE_LANG_B	equ 0x20
AMTVAUDIO_MODE_LANG_C	equ 0x40
AMTVAUDIO_PRESET_STEREO equ 0x200
AMTVAUDIO_PRESET_LANG_A equ 0x1000
AMTVAUDIO_PRESET_LANG_B equ 0x2000
AMTVAUDIO_PRESET_LANG_C equ 0x4000

AMTVAudioEventType	typedef SDWORD
AMTVAUDIO_EVENT_CHANGED equ 0x1

externdef		__MIDL_itf_strmif_0000_0064_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0064_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMTVAudio_INTERFACE_DEFINED__
__IAMTVAudio_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMTVAudio:IID

.comdef IAMTVAudio

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetHardwareSupportedTVAudioModes proc :ptr
    GetAvailableTVAudioModes proc :ptr
    get_TVAudioMode	proc :ptr
    put_TVAudioMode	proc :LONG
    RegisterNotificationCallBack proc :ptr, :LONG
    UnRegisterNotificationCallBack proc :ptr
    .ends

endif

ifndef __IAMTVAudioNotification_INTERFACE_DEFINED__
__IAMTVAudioNotification_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMTVAudioNotification:IID

.comdef IAMTVAudioNotification

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnEvent		proc :AMTVAudioEventType
    .ends

endif

ifndef __IAMAnalogVideoEncoder_INTERFACE_DEFINED__
__IAMAnalogVideoEncoder_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMAnalogVideoEncoder:IID

.comdef IAMAnalogVideoEncoder

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_AvailableTVFormats proc :ptr
    put_TVFormat	proc :LONG
    get_TVFormat	proc :ptr
    put_CopyProtection	proc :LONG
    get_CopyProtection	proc :ptr
    put_CCEnable	proc :LONG
    get_CCEnable	proc :ptr
    .ends

endif

AMPROPERTY_PIN		typedef SDWORD
AMPROPERTY_PIN_CATEGORY equ 0
AMPROPERTY_PIN_MEDIUM	equ ( AMPROPERTY_PIN_CATEGORY + 1 )

ifndef _IKsPropertySet_
_IKsPropertySet_ equ 1
KSPROPERTY_SUPPORT_GET	equ 1
KSPROPERTY_SUPPORT_SET	equ 2

externdef		__MIDL_itf_strmif_0000_0067_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0067_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IKsPropertySet_INTERFACE_DEFINED__
__IKsPropertySet_INTERFACE_DEFINED__ equ 1

externdef		IID_IKsPropertySet:IID

.comdef IKsPropertySet

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Set			proc :REFGUID, :DWORD, :LPVOID, :DWORD
    Get			proc :REFGUID, :DWORD, :LPVOID, :DWORD, :ptr
    QuerySupported	proc :REFGUID, :DWORD, :ptr
    .ends

endif

;void
IKsPropertySet_RemoteSet_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


;void
IKsPropertySet_RemoteGet_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

externdef		__MIDL_itf_strmif_0000_0068_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0068_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMediaPropertyBag_INTERFACE_DEFINED__
__IMediaPropertyBag_INTERFACE_DEFINED__ equ 1

LPMEDIAPROPERTYBAG	typedef ptr IMediaPropertyBag
externdef		IID_IMediaPropertyBag:IID

.comdef IMediaPropertyBag

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Read		proc :LPCOLESTR, :ptr, :ptr
    Write		proc :LPCOLESTR, :ptr
    EnumProperty	proc :ULONG, :ptr, :ptr
    .ends

endif

ifndef __IPersistMediaPropertyBag_INTERFACE_DEFINED__
__IPersistMediaPropertyBag_INTERFACE_DEFINED__ equ 1

LPPERSISTMEDIAPROPERTYBAG typedef ptr IPersistMediaPropertyBag

externdef		IID_IPersistMediaPropertyBag:IID

.comdef IPersistMediaPropertyBag

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetClassID		proc :ptr
    InitNew		proc
    Load		proc :ptr, :ptr
    Save		proc :ptr, :BOOL, :BOOL
    .ends

endif

ifndef __IAMPhysicalPinInfo_INTERFACE_DEFINED__
__IAMPhysicalPinInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMPhysicalPinInfo:IID

.comdef IAMPhysicalPinInfo

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPhysicalType	proc :ptr, :ptr
    .ends

endif

PAMPHYSICALPININFO	typedef ptr IAMPhysicalPinInfo

externdef		__MIDL_itf_strmif_0000_0071_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0071_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMExtDevice_INTERFACE_DEFINED__
__IAMExtDevice_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMExtDevice:IID

.comdef IAMExtDevice

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCapability	proc :LONG, :ptr, :ptr
    get_ExternalDeviceID proc :ptr
    get_ExternalDeviceVersion proc :ptr
    put_DevicePower	proc :LONG
    get_DevicePower	proc :ptr
    Calibrate		proc :HEVENT, :LONG, :ptr
    put_DevicePort	proc :LONG
    get_DevicePort	proc :ptr
    .ends

endif

PEXTDEVICE		typedef ptr IAMExtDevice

externdef		__MIDL_itf_strmif_0000_0072_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0072_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMExtTransport_INTERFACE_DEFINED__
__IAMExtTransport_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMExtTransport:IID

.comdef IAMExtTransport

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCapability	proc :LONG, :ptr, :ptr
    put_MediaState	proc :LONG
    get_MediaState	proc :ptr
    put_LocalControl	proc :LONG
    get_LocalControl	proc :ptr
    GetStatus		proc :LONG, :ptr
    GetTransportBasicParameters proc :LONG, :ptr, :ptr
    SetTransportBasicParameters proc :LONG, :LONG, :LPCOLESTR
    GetTransportVideoParameters proc :LONG, :ptr
    SetTransportVideoParameters proc :LONG, :LONG
    GetTransportAudioParameters proc :LONG, :ptr
    SetTransportAudioParameters proc :LONG, :LONG
    put_Mode		proc :LONG
    get_Mode		proc :ptr
    put_Rate		proc :REAL8
    get_Rate		proc :ptr
    GetChase		proc :ptr, :ptr, :ptr
    SetChase		proc :LONG, :LONG, :HEVENT
    GetBump		proc :ptr, :ptr
    SetBump		proc :LONG, :LONG
    get_AntiClogControl proc :ptr
    put_AntiClogControl proc :LONG
    GetEditPropertySet	proc :LONG, :ptr
    SetEditPropertySet	proc :ptr, :LONG
    GetEditProperty	proc :LONG, :LONG, :ptr
    SetEditProperty	proc :LONG, :LONG, :LONG
    get_EditStart	proc :ptr
    put_EditStart	proc :LONG
    .ends

endif

PIAMEXTTRANSPORT	typedef ptr IAMExtTransport

if 0
TIMECODE		STRUC
wFrameRate		dw ?
wFrameFract		dw ?
dwFrames		dd ?
TIMECODE		ENDS
else
ifndef TIMECODE_DEFINED
TIMECODE_DEFINED equ 1
TIMECODE		UNION
STRUC
 wFrameRate		dw ?
 wFrameFract		dw ?
 dwFrames		dd ?
ENDS
qw			dd ?
TIMECODE		ENDS
endif
endif
PTIMECODE		typedef ptr TIMECODE

TIMECODE_SAMPLE		STRUC
qwTick			LONGLONG ?
timecode		TIMECODE <>
dwUser			dd ?
dwFlags			dd ?
TIMECODE_SAMPLE		ENDS

PTIMECODE_SAMPLE	typedef ptr TIMECODE_SAMPLE

externdef		__MIDL_itf_strmif_0000_0073_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0073_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMTimecodeReader_INTERFACE_DEFINED__
__IAMTimecodeReader_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMTimecodeReader:IID

.comdef IAMTimecodeReader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTCRMode		proc :LONG, :ptr
    SetTCRMode		proc :LONG, :LONG
    put_VITCLine	proc :LONG
    get_VITCLine	proc :ptr
    GetTimecode		proc :PTIMECODE_SAMPLE
    .ends

endif

PIAMTIMECODEREADER	typedef ptr IAMTimecodeReader

externdef		__MIDL_itf_strmif_0000_0074_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0074_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMTimecodeGenerator_INTERFACE_DEFINED__
__IAMTimecodeGenerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMTimecodeGenerator:IID

.comdef IAMTimecodeGenerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTCGMode		proc :LONG, :ptr
    SetTCGMode		proc :LONG, :LONG
    put_VITCLine	proc :LONG
    get_VITCLine	proc :ptr
    SetTimecode		proc :PTIMECODE_SAMPLE
    GetTimecode		proc :PTIMECODE_SAMPLE
    .ends

endif

PIAMTIMECODEGENERATOR	typedef ptr IAMTimecodeGenerator

externdef		__MIDL_itf_strmif_0000_0075_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0075_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMTimecodeDisplay_INTERFACE_DEFINED__
__IAMTimecodeDisplay_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMTimecodeDisplay:IID

.comdef IAMTimecodeDisplay

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTCDisplayEnable	proc :ptr
    SetTCDisplayEnable	proc :LONG
    GetTCDisplay	proc :LONG, :ptr
    SetTCDisplay	proc :LONG, :LONG
    .ends

endif

PIAMTIMECODEDISPLAY	typedef ptr IAMTimecodeDisplay

externdef		__MIDL_itf_strmif_0000_0076_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0076_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMDevMemoryAllocator_INTERFACE_DEFINED__
__IAMDevMemoryAllocator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMDevMemoryAllocator:IID

.comdef IAMDevMemoryAllocator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetInfo		proc :ptr, :ptr, :ptr, :ptr
    CheckMemory		proc :ptr
    Alloc		proc
    Free		proc :ptr
    GetDevMemoryObject	proc :ptr, :ptr
    .ends

endif

PAMDEVMEMORYALLOCATOR	typedef ptr IAMDevMemoryAllocator

externdef		__MIDL_itf_strmif_0000_0077_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0077_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMDevMemoryControl_INTERFACE_DEFINED__
__IAMDevMemoryControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMDevMemoryControl:IID

.comdef IAMDevMemoryControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryWriteSync	proc
    WriteSync		proc
    GetDevId		proc :ptr
    .ends

endif

PAMDEVMEMORYCONTROL	typedef ptr IAMDevMemoryControl

AMSTREAMSELECTINFOFLAGS typedef SDWORD
AMSTREAMSELECTINFO_ENABLED equ 0x1
AMSTREAMSELECTINFO_EXCLUSIVE equ 0x2

AMSTREAMSELECTENABLEFLAGS typedef SDWORD
AMSTREAMSELECTENABLE_ENABLE equ 0x1
AMSTREAMSELECTENABLE_ENABLEALL equ 0x2

externdef		__MIDL_itf_strmif_0000_0078_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0078_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMStreamSelect_INTERFACE_DEFINED__
__IAMStreamSelect_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMStreamSelect:IID

.comdef IAMStreamSelect

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Count		proc :ptr
    Info		proc :LONG, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    Enable		proc :LONG, :DWORD
    .ends

endif

PAMSTREAMSELECT		typedef ptr IAMStreamSelect

AMRESCTL_RESERVEFLAGS	typedef SDWORD
AMRESCTL_RESERVEFLAGS_RESERVE equ 0
AMRESCTL_RESERVEFLAGS_UNRESERVE equ 0x1

externdef		__MIDL_itf_strmif_0000_0079_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0079_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMResourceControl_INTERFACE_DEFINED__
__IAMResourceControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMResourceControl:IID

.comdef IAMResourceControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Reserve		proc :DWORD, :PVOID
    .ends

endif

ifndef __IAMClockAdjust_INTERFACE_DEFINED__
__IAMClockAdjust_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMClockAdjust:IID

.comdef IAMClockAdjust

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetClockDelta	proc :REFERENCE_TIME
    .ends

endif

AM_FILTER_MISC_FLAGS	typedef SDWORD
AM_FILTER_MISC_FLAGS_IS_RENDERER equ 0x1
AM_FILTER_MISC_FLAGS_IS_SOURCE equ 0x2

externdef		__MIDL_itf_strmif_0000_0081_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0081_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMFilterMiscFlags_INTERFACE_DEFINED__
__IAMFilterMiscFlags_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMFilterMiscFlags:IID

.comdef IAMFilterMiscFlags

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMiscFlags	proc
    .ends

endif

ifndef __IDrawVideoImage_INTERFACE_DEFINED__
__IDrawVideoImage_INTERFACE_DEFINED__ equ 1

externdef		IID_IDrawVideoImage:IID

.comdef IDrawVideoImage

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    DrawVideoImageBegin proc
    DrawVideoImageEnd	proc
    DrawVideoImageDraw	proc :HDC, :LPRECT, :LPRECT
    .ends

endif

ifndef __IDecimateVideoImage_INTERFACE_DEFINED__
__IDecimateVideoImage_INTERFACE_DEFINED__ equ 1

externdef		IID_IDecimateVideoImage:IID

.comdef IDecimateVideoImage

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetDecimationImageSize proc :LONG, :LONG
    ResetDecimationImageSize proc
    .ends

endif

DECIMATION_USAGE	typedef SDWORD
DECIMATION_LEGACY	equ 0
DECIMATION_USE_DECODER_ONLY equ ( DECIMATION_LEGACY + 1 )
DECIMATION_USE_VIDEOPORT_ONLY equ ( DECIMATION_USE_DECODER_ONLY + 1 )
DECIMATION_USE_OVERLAY_ONLY equ ( DECIMATION_USE_VIDEOPORT_ONLY + 1 )
DECIMATION_DEFAULT	equ ( DECIMATION_USE_OVERLAY_ONLY + 1 )

externdef		__MIDL_itf_strmif_0000_0084_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0084_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMVideoDecimationProperties_INTERFACE_DEFINED__
__IAMVideoDecimationProperties_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMVideoDecimationProperties:IID

.comdef IAMVideoDecimationProperties

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryDecimationUsage proc :ptr
    SetDecimationUsage	proc :DECIMATION_USAGE
    .ends

endif

ifndef __IVideoFrameStep_INTERFACE_DEFINED__
__IVideoFrameStep_INTERFACE_DEFINED__ equ 1

externdef		IID_IVideoFrameStep:IID

.comdef IVideoFrameStep

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Step		proc :DWORD, :ptr
    CanStep		proc :LONG, :ptr
    CancelStep		proc
    .ends

endif

AM_PUSHSOURCE_FLAGS	typedef SDWORD
AM_PUSHSOURCECAPS_INTERNAL_RM equ 0x1
AM_PUSHSOURCECAPS_NOT_LIVE equ 0x2
AM_PUSHSOURCECAPS_PRIVATE_CLOCK equ 0x4
AM_PUSHSOURCEREQS_USE_STREAM_CLOCK equ 0x10000
AM_PUSHSOURCEREQS_USE_CLOCK_CHAIN equ 0x20000

externdef		__MIDL_itf_strmif_0000_0086_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0086_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMLatency_INTERFACE_DEFINED__
__IAMLatency_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMLatency:IID

.comdef IAMLatency

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetLatency		proc :ptr
    .ends

endif

ifndef __IAMPushSource_INTERFACE_DEFINED__
__IAMPushSource_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMPushSource:IID

.comdef IAMPushSource

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetLatency		proc :ptr
    GetPushSourceFlags	proc :ptr
    SetPushSourceFlags	proc :ULONG
    SetStreamOffset	proc :REFERENCE_TIME
    GetStreamOffset	proc :ptr
    GetMaxStreamOffset	proc :ptr
    SetMaxStreamOffset	proc :REFERENCE_TIME
    .ends

endif

ifndef __IAMDeviceRemoval_INTERFACE_DEFINED__
__IAMDeviceRemoval_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMDeviceRemoval:IID

.comdef IAMDeviceRemoval

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    DeviceInfo		proc :ptr, :ptr
    Reassociate		proc
    Disassociate	proc
    .ends

endif

DVINFO			STRUC
dwDVAAuxSrc		dd ?
dwDVAAuxCtl		dd ?
dwDVAAuxSrc1		dd ?
dwDVAAuxCtl1		dd ?
dwDVVAuxSrc		dd ?
dwDVVAuxCtl		dd ?
dwDVReserved		dd  2  dup(?)
DVINFO			ENDS

PDVINFO			typedef ptr DVINFO

DVENCODERRESOLUTION	typedef SDWORD
DVENCODERRESOLUTION_720x480 equ 2012
DVENCODERRESOLUTION_360x240 equ 2013
DVENCODERRESOLUTION_180x120 equ 2014
DVENCODERRESOLUTION_88x60 equ 2015

DVENCODERVIDEOFORMAT	typedef SDWORD
DVENCODERVIDEOFORMAT_NTSC equ 2000
DVENCODERVIDEOFORMAT_PAL equ 2001

DVENCODERFORMAT		typedef SDWORD
DVENCODERFORMAT_DVSD	equ 2007
DVENCODERFORMAT_DVHD	equ 2008
DVENCODERFORMAT_DVSL	equ 2009

externdef		__MIDL_itf_strmif_0000_0088_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0088_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDVEnc_INTERFACE_DEFINED__
__IDVEnc_INTERFACE_DEFINED__ equ 1

externdef		IID_IDVEnc:IID

.comdef IDVEnc

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_IFormatResolution proc :ptr, :ptr, :ptr, :BYTE, :ptr
    put_IFormatResolution proc :SINT, :SINT, :SINT, :BYTE, :ptr
    .ends

endif

DVDECODERRESOLUTION	typedef SDWORD
DVDECODERRESOLUTION_720x480 equ 1000
DVDECODERRESOLUTION_360x240 equ 1001
DVDECODERRESOLUTION_180x120 equ 1002
DVDECODERRESOLUTION_88x60 equ 1003

DVRESOLUTION		typedef SDWORD
DVRESOLUTION_FULL	equ 1000
DVRESOLUTION_HALF	equ 1001
DVRESOLUTION_QUARTER	equ 1002
DVRESOLUTION_DC		equ 1003

externdef		__MIDL_itf_strmif_0000_0089_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0089_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IIPDVDec_INTERFACE_DEFINED__
__IIPDVDec_INTERFACE_DEFINED__ equ 1

externdef		IID_IIPDVDec:IID

.comdef IIPDVDec

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_IPDisplay	proc :ptr
    put_IPDisplay	proc :SINT
    .ends

endif

ifndef __IDVRGB219_INTERFACE_DEFINED__
__IDVRGB219_INTERFACE_DEFINED__ equ 1

externdef		IID_IDVRGB219:IID

.comdef IDVRGB219

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetRGB219		proc :BOOL
    .ends

endif

ifndef __IDVSplitter_INTERFACE_DEFINED__
__IDVSplitter_INTERFACE_DEFINED__ equ 1

externdef		IID_IDVSplitter:IID

.comdef IDVSplitter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    DiscardAlternateVideoFrames proc :SINT
    .ends

endif

AM_AUDIO_RENDERER_STAT_PARAM typedef SDWORD
AM_AUDREND_STAT_PARAM_BREAK_COUNT equ 1
AM_AUDREND_STAT_PARAM_SLAVE_MODE equ ( AM_AUDREND_STAT_PARAM_BREAK_COUNT + 1 )
AM_AUDREND_STAT_PARAM_SILENCE_DUR equ ( AM_AUDREND_STAT_PARAM_SLAVE_MODE + 1 )
AM_AUDREND_STAT_PARAM_LAST_BUFFER_DUR equ ( AM_AUDREND_STAT_PARAM_SILENCE_DUR + 1 )
AM_AUDREND_STAT_PARAM_DISCONTINUITIES equ ( AM_AUDREND_STAT_PARAM_LAST_BUFFER_DUR + 1 )
AM_AUDREND_STAT_PARAM_SLAVE_RATE equ ( AM_AUDREND_STAT_PARAM_DISCONTINUITIES + 1 )
AM_AUDREND_STAT_PARAM_SLAVE_DROPWRITE_DUR equ ( AM_AUDREND_STAT_PARAM_SLAVE_RATE + 1 )
AM_AUDREND_STAT_PARAM_SLAVE_HIGHLOWERROR equ ( AM_AUDREND_STAT_PARAM_SLAVE_DROPWRITE_DUR + 1 )
AM_AUDREND_STAT_PARAM_SLAVE_LASTHIGHLOWERROR equ ( AM_AUDREND_STAT_PARAM_SLAVE_HIGHLOWERROR + 1 )
AM_AUDREND_STAT_PARAM_SLAVE_ACCUMERROR equ ( AM_AUDREND_STAT_PARAM_SLAVE_LASTHIGHLOWERROR + 1 )
AM_AUDREND_STAT_PARAM_BUFFERFULLNESS equ ( AM_AUDREND_STAT_PARAM_SLAVE_ACCUMERROR + 1 )
AM_AUDREND_STAT_PARAM_JITTER equ ( AM_AUDREND_STAT_PARAM_BUFFERFULLNESS + 1 )

externdef		__MIDL_itf_strmif_0000_0092_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0092_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMAudioRendererStats_INTERFACE_DEFINED__
__IAMAudioRendererStats_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMAudioRendererStats:IID

.comdef IAMAudioRendererStats

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetStatParam	proc :DWORD, :ptr, :ptr
    .ends

endif

AM_INTF_SEARCH_FLAGS	typedef SDWORD
AM_INTF_SEARCH_INPUT_PIN equ 0x1
AM_INTF_SEARCH_OUTPUT_PIN equ 0x2
AM_INTF_SEARCH_FILTER	equ 0x4

externdef		__MIDL_itf_strmif_0000_0094_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0094_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMGraphStreams_INTERFACE_DEFINED__
__IAMGraphStreams_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMGraphStreams:IID

.comdef IAMGraphStreams

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    FindUpstreamInterface proc :ptr, :REFIID, :ptr, :DWORD
    SyncUsingStreamOffset proc :BOOL
    SetMaxGraphLatency	proc :REFERENCE_TIME
    .ends

endif

AMOVERLAYFX		typedef SDWORD
AMOVERFX_NOFX		equ 0
AMOVERFX_MIRRORLEFTRIGHT equ 0x2
AMOVERFX_MIRRORUPDOWN	equ 0x4
AMOVERFX_DEINTERLACE	equ 0x8

externdef		__MIDL_itf_strmif_0000_0095_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0095_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMOverlayFX_INTERFACE_DEFINED__
__IAMOverlayFX_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMOverlayFX:IID

.comdef IAMOverlayFX

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryOverlayFXCaps	proc :ptr
    SetOverlayFX	proc :DWORD
    GetOverlayFX	proc :ptr
    .ends

endif

ifndef __IAMOpenProgress_INTERFACE_DEFINED__
__IAMOpenProgress_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMOpenProgress:IID

.comdef IAMOpenProgress

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryProgress	proc :ptr, :ptr
    AbortOperation	proc
    .ends

endif

ifndef __IMpeg2Demultiplexer_INTERFACE_DEFINED__
__IMpeg2Demultiplexer_INTERFACE_DEFINED__ equ 1

externdef		IID_IMpeg2Demultiplexer:IID

.comdef IMpeg2Demultiplexer

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateOutputPin	proc :ptr, :LPWSTR, :ptr
    SetOutputPinMediaType proc :LPWSTR, :ptr
    DeleteOutputPin	proc :LPWSTR
    .ends

endif

MPEG2_PROGRAM_STREAM_MAP equ 0x00000000
MPEG2_PROGRAM_ELEMENTARY_STREAM equ 0x00000001
MPEG2_PROGRAM_DIRECTORY_PES_PACKET equ 0x00000002
MPEG2_PROGRAM_PACK_HEADER equ 0x00000003
MPEG2_PROGRAM_PES_STREAM equ 0x00000004
MPEG2_PROGRAM_SYSTEM_HEADER equ 0x00000005
SUBSTREAM_FILTER_VAL_NONE equ 0x10000000
STREAM_ID_MAP		STRUC
stream_id		ULONG ?
dwMediaSampleContent	dd ?
ulSubstreamFilterValue	ULONG ?
iDataOffset		SINT ?
STREAM_ID_MAP		ENDS

externdef		__MIDL_itf_strmif_0000_0098_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0098_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumStreamIdMap_INTERFACE_DEFINED__
__IEnumStreamIdMap_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumStreamIdMap:IID

.comdef IEnumStreamIdMap

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IMPEG2StreamIdMap_INTERFACE_DEFINED__
__IMPEG2StreamIdMap_INTERFACE_DEFINED__ equ 1

externdef		IID_IMPEG2StreamIdMap:IID

.comdef IMPEG2StreamIdMap

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    MapStreamId		proc :ULONG, :DWORD, :ULONG, :SINT
    UnmapStreamId	proc :ULONG, :ptr
    EnumStreamIdMap	proc :ptr
    .ends

endif

ifndef __IRegisterServiceProvider_INTERFACE_DEFINED__
__IRegisterServiceProvider_INTERFACE_DEFINED__ equ 1

externdef		IID_IRegisterServiceProvider:IID

.comdef IRegisterServiceProvider

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    RegisterService	proc :REFGUID, :ptr
    .ends

endif

ifndef __IAMClockSlave_INTERFACE_DEFINED__
__IAMClockSlave_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMClockSlave:IID

.comdef IAMClockSlave

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetErrorTolerance	proc :DWORD
    GetErrorTolerance	proc :ptr
    .ends

endif

ifndef __IAMGraphBuilderCallback_INTERFACE_DEFINED__
__IAMGraphBuilderCallback_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMGraphBuilderCallback:IID

.comdef IAMGraphBuilderCallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SelectedFilter	proc :ptr
    CreatedFilter	proc :ptr
    .ends

endif

AMCOPPSignature		STRUC
Signature		db  256	 dup(?)
AMCOPPSignature		ENDS

AMCOPPCommand		STRUC
macKDI			GUID <>
guidCommandID		GUID <>
dwSequence		dd ?
cbSizeData		dd ?
CommandData		db  4056  dup(?)
AMCOPPCommand		ENDS

LPAMCOPPCommand		typedef ptr AMCOPPCommand

AMCOPPStatusInput	STRUC
rApp			GUID <>
guidStatusRequestID	GUID <>
dwSequence		dd ?
cbSizeData		dd ?
StatusData		db  4056  dup(?)
AMCOPPStatusInput	ENDS

LPAMCOPPStatusInput	typedef ptr AMCOPPStatusInput

AMCOPPStatusOutput	STRUC
macKDI			GUID <>
cbSizeData		dd ?
COPPStatus		db  4076  dup(?)
AMCOPPStatusOutput	ENDS

LPAMCOPPStatusOutput	typedef ptr AMCOPPStatusOutput

externdef		__MIDL_itf_strmif_0000_0108_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0108_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAMCertifiedOutputProtection_INTERFACE_DEFINED__
__IAMCertifiedOutputProtection_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMCertifiedOutputProtection:IID

.comdef IAMCertifiedOutputProtection

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    KeyExchange		proc :ptr
    SessionSequenceStart proc :ptr
    ProtectionCommand	proc :ptr
    ProtectionStatus	proc :ptr, :ptr
    .ends

endif

ifndef __IAMAsyncReaderTimestampScaling_INTERFACE_DEFINED__
__IAMAsyncReaderTimestampScaling_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMAsyncReaderTimestampScaling:IID

.comdef IAMAsyncReaderTimestampScaling

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTimestampMode	proc :ptr
    SetTimestampMode	proc :BOOL
    .ends

endif

ifndef __IAMPluginControl_INTERFACE_DEFINED__
__IAMPluginControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IAMPluginControl:IID

.comdef IAMPluginControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPreferredClsid	proc :REFGUID, :ptr
    GetPreferredClsidByIndex proc :DWORD, :ptr, :ptr
    SetPreferredClsid	proc :REFGUID, :ptr
    IsDisabled		proc :REFCLSID
    GetDisabledByIndex	proc :DWORD, :ptr
    SetDisabled		proc :REFCLSID, :BOOL
    IsLegacyDisabled	proc :LPCWSTR
    .ends

endif

include ddraw.inc
.xlist

DVD_DOMAIN		typedef SDWORD
DVD_DOMAIN_FirstPlay	equ 1
DVD_DOMAIN_VideoManagerMenu equ ( DVD_DOMAIN_FirstPlay + 1 )
DVD_DOMAIN_VideoTitleSetMenu equ ( DVD_DOMAIN_VideoManagerMenu + 1 )
DVD_DOMAIN_Title	equ ( DVD_DOMAIN_VideoTitleSetMenu + 1 )
DVD_DOMAIN_Stop		equ ( DVD_DOMAIN_Title + 1 )

DVD_MENU_ID		typedef SDWORD
DVD_MENU_Title		equ 2
DVD_MENU_Root		equ 3
DVD_MENU_Subpicture	equ 4
DVD_MENU_Audio		equ 5
DVD_MENU_Angle		equ 6
DVD_MENU_Chapter	equ 7

DVD_DISC_SIDE		typedef SDWORD
DVD_SIDE_A		equ 1
DVD_SIDE_B		equ 2

DVD_PREFERRED_DISPLAY_MODE typedef SDWORD
DISPLAY_CONTENT_DEFAULT equ 0
DISPLAY_16x9		equ 1
DISPLAY_4x3_PANSCAN_PREFERRED equ 2
DISPLAY_4x3_LETTERBOX_PREFERRED equ 3

DVD_REGISTER		typedef WORD

DVD_ATR			STRUC
ulCAT			ULONG ?
pbATRI			db  768	 dup(?)
DVD_ATR			ENDS

DVD_FRAMERATE		typedef SDWORD
DVD_FPS_25		equ 1
DVD_FPS_30NonDrop	equ 3

DVD_TIMECODE		STRUC
if 1
flags			ULONG ?
else
Hours1	  :4		ULONG ?
Hours10	  :4		ULONG ?
Minutes1  :4		ULONG ?
Minutes10 :4		ULONG ?
Seconds1  :4		ULONG ?
Seconds10 :4		ULONG ?
Frames1	  :4		ULONG ?
Frames10  :2		ULONG ?
FrameRateCode: 2	ULONG ?
endif
DVD_TIMECODE		ENDS
DVD_NavCmdType		typedef SDWORD
DVD_NavCmdType_Pre	equ 1
DVD_NavCmdType_Post	equ 2
DVD_NavCmdType_Cell	equ 3
DVD_NavCmdType_Button	equ 4

DVD_TIMECODE_FLAGS	typedef SDWORD
DVD_TC_FLAG_25fps	equ 0x1
DVD_TC_FLAG_30fps	equ 0x2
DVD_TC_FLAG_DropFrame	equ 0x4
DVD_TC_FLAG_Interpolated equ 0x8

DVD_HMSF_TIMECODE	STRUC
bHours			db ?
bMinutes		db ?
bSeconds		db ?
bFrames			db ?
DVD_HMSF_TIMECODE	ENDS

DVD_PLAYBACK_LOCATION2	STRUC
TitleNum		ULONG ?
ChapterNum		ULONG ?
TimeCode		DVD_HMSF_TIMECODE <>
TimeCodeFlags		ULONG ?
DVD_PLAYBACK_LOCATION2	ENDS

DVD_PLAYBACK_LOCATION	STRUC
TitleNum		ULONG ?
ChapterNum		ULONG ?
TimeCode		ULONG ?
DVD_PLAYBACK_LOCATION	ENDS

VALID_UOP_SOMTHING_OR_OTHER typedef DWORD
VALID_UOP_FLAG		typedef SDWORD

UOP_FLAG_Play_Title_Or_AtTime equ 0x1
UOP_FLAG_Play_Chapter	equ 0x2
UOP_FLAG_Play_Title	equ 0x4
UOP_FLAG_Stop		equ 0x8
UOP_FLAG_ReturnFromSubMenu equ 0x10
UOP_FLAG_Play_Chapter_Or_AtTime equ 0x20
UOP_FLAG_PlayPrev_Or_Replay_Chapter equ 0x40
UOP_FLAG_PlayNext_Chapter equ 0x80
UOP_FLAG_Play_Forwards	equ 0x100
UOP_FLAG_Play_Backwards equ 0x200
UOP_FLAG_ShowMenu_Title equ 0x400
UOP_FLAG_ShowMenu_Root	equ 0x800
UOP_FLAG_ShowMenu_SubPic equ 0x1000
UOP_FLAG_ShowMenu_Audio equ 0x2000
UOP_FLAG_ShowMenu_Angle equ 0x4000
UOP_FLAG_ShowMenu_Chapter equ 0x8000
UOP_FLAG_Resume		equ 0x10000
UOP_FLAG_Select_Or_Activate_Button equ 0x20000
UOP_FLAG_Still_Off	equ 0x40000
UOP_FLAG_Pause_On	equ 0x80000
UOP_FLAG_Select_Audio_Stream equ 0x100000
UOP_FLAG_Select_SubPic_Stream equ 0x200000
UOP_FLAG_Select_Angle	equ 0x400000
UOP_FLAG_Select_Karaoke_Audio_Presentation_Mode equ 0x800000
UOP_FLAG_Select_Video_Mode_Preference equ 0x1000000

DVD_CMD_FLAGS		typedef SDWORD
DVD_CMD_FLAG_None	equ 0
DVD_CMD_FLAG_Flush	equ 0x1
DVD_CMD_FLAG_SendEvents equ 0x2
DVD_CMD_FLAG_Block	equ 0x4
DVD_CMD_FLAG_StartWhenRendered equ 0x8
DVD_CMD_FLAG_EndAfterRendered equ 0x10

DVD_OPTION_FLAG		typedef SDWORD
DVD_ResetOnStop		equ 1
DVD_NotifyParentalLevelChange equ 2
DVD_HMSF_TimeCodeEvents equ 3
DVD_AudioDuringFFwdRew	equ 4
DVD_EnableNonblockingAPIs equ 5
DVD_CacheSizeInMB	equ 6
DVD_EnablePortableBookmarks equ 7
DVD_EnableExtendedCopyProtectErrors equ 8
DVD_NotifyPositionChange equ 9
DVD_IncreaseOutputControl equ 10
DVD_EnableStreaming	equ 11
DVD_EnableESOutput	equ 12
DVD_EnableTitleLength	equ 13
DVD_DisableStillThrottle equ 14
DVD_EnableLoggingEvents equ 15
DVD_MaxReadBurstInKB	equ 16
DVD_ReadBurstPeriodInMS equ 17

DVD_RELATIVE_BUTTON	typedef SDWORD
DVD_Relative_Upper	equ 1
DVD_Relative_Lower	equ 2
DVD_Relative_Left	equ 3
DVD_Relative_Right	equ 4

DVD_PARENTAL_LEVEL	typedef SDWORD
DVD_PARENTAL_LEVEL_8	equ 0x8000
DVD_PARENTAL_LEVEL_7	equ 0x4000
DVD_PARENTAL_LEVEL_6	equ 0x2000
DVD_PARENTAL_LEVEL_5	equ 0x1000
DVD_PARENTAL_LEVEL_4	equ 0x800
DVD_PARENTAL_LEVEL_3	equ 0x400
DVD_PARENTAL_LEVEL_2	equ 0x200
DVD_PARENTAL_LEVEL_1	equ 0x100

DVD_AUDIO_LANG_EXT	typedef SDWORD
DVD_AUD_EXT_NotSpecified equ 0
DVD_AUD_EXT_Captions	equ 1
DVD_AUD_EXT_VisuallyImpaired equ 2
DVD_AUD_EXT_DirectorComments1 equ 3
DVD_AUD_EXT_DirectorComments2 equ 4

DVD_SUBPICTURE_LANG_EXT typedef SDWORD
DVD_SP_EXT_NotSpecified equ 0
DVD_SP_EXT_Caption_Normal equ 1
DVD_SP_EXT_Caption_Big	equ 2
DVD_SP_EXT_Caption_Children equ 3
DVD_SP_EXT_CC_Normal	equ 5
DVD_SP_EXT_CC_Big	equ 6
DVD_SP_EXT_CC_Children	equ 7
DVD_SP_EXT_Forced	equ 9
DVD_SP_EXT_DirectorComments_Normal equ 13
DVD_SP_EXT_DirectorComments_Big equ 14
DVD_SP_EXT_DirectorComments_Children equ 15

DVD_AUDIO_APPMODE	typedef SDWORD
DVD_AudioMode_None	equ 0
DVD_AudioMode_Karaoke	equ 1
DVD_AudioMode_Surround	equ 2
DVD_AudioMode_Other	equ 3

DVD_AUDIO_FORMAT	typedef SDWORD
DVD_AudioFormat_AC3	equ 0
DVD_AudioFormat_MPEG1	equ 1
DVD_AudioFormat_MPEG1_DRC equ 2
DVD_AudioFormat_MPEG2	equ 3
DVD_AudioFormat_MPEG2_DRC equ 4
DVD_AudioFormat_LPCM	equ 5
DVD_AudioFormat_DTS	equ 6
DVD_AudioFormat_SDDS	equ 7
DVD_AudioFormat_Other	equ 8

DVD_KARAOKE_DOWNMIX	typedef SDWORD
DVD_Mix_0to0		equ 0x1
DVD_Mix_1to0		equ 0x2
DVD_Mix_2to0		equ 0x4
DVD_Mix_3to0		equ 0x8
DVD_Mix_4to0		equ 0x10
DVD_Mix_Lto0		equ 0x20
DVD_Mix_Rto0		equ 0x40
DVD_Mix_0to1		equ 0x100
DVD_Mix_1to1		equ 0x200
DVD_Mix_2to1		equ 0x400
DVD_Mix_3to1		equ 0x800
DVD_Mix_4to1		equ 0x1000
DVD_Mix_Lto1		equ 0x2000
DVD_Mix_Rto1		equ 0x4000

DVD_AudioAttributes	STRUC
AppMode			DVD_AUDIO_APPMODE ?
AppModeData		db ?
AudioFormat		DVD_AUDIO_FORMAT ?
Language		LCID ?
LanguageExtension	DVD_AUDIO_LANG_EXT ?
fHasMultichannelInfo	BOOL ?
dwFrequency		dd ?
bQuantization		db ?
bNumberOfChannels	db ?
dwReserved		dd  2  dup(?)
DVD_AudioAttributes	ENDS

DVD_MUA_MixingInfo	STRUC
fMixTo0			BOOL ?
fMixTo1			BOOL ?
fMix0InPhase		BOOL ?
fMix1InPhase		BOOL ?
dwSpeakerPosition	dd ?
DVD_MUA_MixingInfo	ENDS

DVD_MUA_Coeff		STRUC
log2_alpha		REAL8 ?
log2_beta		REAL8 ?
DVD_MUA_Coeff		ENDS

DVD_MultichannelAudioAttributes STRUC
Info			DVD_MUA_MixingInfo  8  dup(<>)
Coeff			DVD_MUA_Coeff  8  dup(<>)
DVD_MultichannelAudioAttributes ENDS

DVD_KARAOKE_CONTENTS typedef SDWORD
DVD_Karaoke_GuideVocal1 equ 0x1
DVD_Karaoke_GuideVocal2 equ 0x2
DVD_Karaoke_GuideMelody1 equ 0x4
DVD_Karaoke_GuideMelody2 equ 0x8
DVD_Karaoke_GuideMelodyA equ 0x10
DVD_Karaoke_GuideMelodyB equ 0x20
DVD_Karaoke_SoundEffectA equ 0x40
DVD_Karaoke_SoundEffectB equ 0x80

DVD_KARAOKE_ASSIGNMENT typedef SDWORD
DVD_Assignment_reserved0 equ 0
DVD_Assignment_reserved1 equ 1
DVD_Assignment_LR	equ 2
DVD_Assignment_LRM	equ 3
DVD_Assignment_LR1	equ 4
DVD_Assignment_LRM1	equ 5
DVD_Assignment_LR12	equ 6
DVD_Assignment_LRM12	equ 7

DVD_KaraokeAttributes	STRUC
bVersion		db ?
fMasterOfCeremoniesInGuideVocal1 BOOL ?
fDuet			BOOL ?
ChannelAssignment	DVD_KARAOKE_ASSIGNMENT ?
wChannelContents	dw  8  dup(?)
DVD_KaraokeAttributes	ENDS

DVD_VIDEO_COMPRESSION typedef SDWORD
DVD_VideoCompression_Other equ 0
DVD_VideoCompression_MPEG1 equ 1
DVD_VideoCompression_MPEG2 equ 2

DVD_VideoAttributes	STRUC
fPanscanPermitted	BOOL ?
fLetterboxPermitted	BOOL ?
ulAspectX		ULONG ?
ulAspectY		ULONG ?
ulFrameRate		ULONG ?
ulFrameHeight		ULONG ?
Compression		DVD_VIDEO_COMPRESSION ?
fLine21Field1InGOP	BOOL ?
fLine21Field2InGOP	BOOL ?
ulSourceResolutionX	ULONG ?
ulSourceResolutionY	ULONG ?
fIsSourceLetterboxed	BOOL ?
fIsFilmMode		BOOL ?
DVD_VideoAttributes	ENDS

DVD_SUBPICTURE_TYPE	typedef SDWORD
DVD_SPType_NotSpecified equ 0
DVD_SPType_Language	equ 1
DVD_SPType_Other	equ 2

DVD_SUBPICTURE_CODING typedef SDWORD
DVD_SPCoding_RunLength	equ 0
DVD_SPCoding_Extended	equ 1
DVD_SPCoding_Other	equ 2

DVD_SubpictureAttributes STRUC
_Type			DVD_SUBPICTURE_TYPE ?
CodingMode		DVD_SUBPICTURE_CODING ?
Language		LCID ?
LanguageExtension	DVD_SUBPICTURE_LANG_EXT ?
DVD_SubpictureAttributes ENDS

DVD_TITLE_APPMODE	typedef SDWORD
DVD_AppMode_Not_Specified equ 0
DVD_AppMode_Karaoke	equ 1
DVD_AppMode_Other	equ 3

DVD_TitleAttributes	STRUC
UNION
 AppMode		DVD_TITLE_APPMODE ?
 TitleLength		DVD_HMSF_TIMECODE <>
ENDS
VideoAttributes		DVD_VideoAttributes <>
ulNumberOfAudioStreams	ULONG ?
AudioAttributes		DVD_AudioAttributes 8 dup(<>)
MultichannelAudioAttributes DVD_MultichannelAudioAttributes 8 dup(<>)
ulNumberOfSubpictureStreams ULONG ?
SubpictureAttributes	DVD_SubpictureAttributes 32 dup(<>)
DVD_TitleAttributes	ENDS

DVD_MenuAttributes	STRUC
fCompatibleRegion	BOOL 8 dup(?)
VideoAttributes		DVD_VideoAttributes <>
fAudioPresent		BOOL ?
AudioAttributes		DVD_AudioAttributes <>
fSubpicturePresent	BOOL ?
SubpictureAttributes	DVD_SubpictureAttributes <>
DVD_MenuAttributes	ENDS

externdef		__MIDL_itf_strmif_0000_0111_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0111_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDvdControl_INTERFACE_DEFINED__
__IDvdControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IDvdControl:IID

.comdef IDvdControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    TitlePlay		proc :ULONG
    ChapterPlay		proc :ULONG, :ULONG
    TimePlay		proc :ULONG, :ULONG
    StopForResume	proc
    GoUp		proc
    TimeSearch		proc :ULONG
    ChapterSearch	proc :ULONG
    PrevPGSearch	proc
    TopPGSearch		proc
    NextPGSearch	proc
    ForwardScan		proc :REAL8
    BackwardScan	proc :REAL8
    MenuCall		proc :DVD_MENU_ID
    Resume		proc
    UpperButtonSelect	proc
    LowerButtonSelect	proc
    LeftButtonSelect	proc
    RightButtonSelect	proc
    ButtonActivate	proc
    ButtonSelectAndActivate proc :ULONG
    StillOff		proc
    PauseOn		proc
    PauseOff		proc
    MenuLanguageSelect	proc :LCID
    AudioStreamChange	proc :ULONG
    SubpictureStreamChange proc :ULONG, :BOOL
    AngleChange		proc :ULONG
    ParentalLevelSelect proc :ULONG
    ParentalCountrySelect proc :WORD
    KaraokeAudioPresentationModeChange proc :ULONG
    VideoModePreferrence proc :ULONG
    SetRoot		proc :LPCWSTR
    MouseActivate	proc :POINT
    MouseSelect		proc :POINT
    ChapterPlayAutoStop proc :ULONG, :ULONG, :ULONG
    .ends

endif

ifndef __IDvdInfo_INTERFACE_DEFINED__
__IDvdInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IDvdInfo:IID

.comdef IDvdInfo

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrentDomain	proc :ptr
    GetCurrentLocation	proc :ptr
    GetTotalTitleTime	proc :ptr
    GetCurrentButton	proc :ptr, :ptr
    GetCurrentAngle	proc :ptr, :ptr
    GetCurrentAudio	proc :ptr, :ptr
    GetCurrentSubpicture proc :ptr, :ptr, :ptr
    GetCurrentUOPS	proc :ptr
    GetAllSPRMs		proc :ptr
    GetAllGPRMs		proc :ptr
    GetAudioLanguage	proc :ULONG, :ptr
    GetSubpictureLanguage proc :ULONG, :ptr
    GetTitleAttributes	proc :ULONG, :ptr
    GetVMGAttributes	proc :ptr
    GetCurrentVideoAttributes proc :ptr
    GetCurrentAudioAttributes proc :ptr
    GetCurrentSubpictureAttributes proc :ptr
    GetCurrentVolumeInfo proc :ptr, :ptr
    GetDVDTextInfo	proc :ptr, :ULONG, :ptr
    GetPlayerParentalLevel proc :ptr, :ptr
    GetNumberOfChapters proc :ULONG, :ptr
    GetTitleParentalLevels proc :ULONG, :ptr
    GetRoot		proc :LPSTR, :ULONG, :ptr
    .ends

endif

ifndef __IDvdCmd_INTERFACE_DEFINED__
__IDvdCmd_INTERFACE_DEFINED__ equ 1

externdef		IID_IDvdCmd:IID

.comdef IDvdCmd

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    WaitForStart	proc
    WaitForEnd		proc
    .ends

endif

ifndef __IDvdState_INTERFACE_DEFINED__
__IDvdState_INTERFACE_DEFINED__ equ 1

externdef		IID_IDvdState:IID

.comdef IDvdState

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDiscID		proc :ptr
    GetParentalLevel	proc :ptr
    .ends

endif

ifndef __IDvdControl2_INTERFACE_DEFINED__
__IDvdControl2_INTERFACE_DEFINED__ equ 1

externdef		IID_IDvdControl2:IID

.comdef IDvdControl2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    PlayTitle		proc :ULONG, :DWORD, :ptr
    PlayChapterInTitle	proc :ULONG, :ULONG, :DWORD, :ptr
    PlayAtTimeInTitle	proc :ULONG, :ptr, :DWORD, :ptr
    Stop		proc
    ReturnFromSubmenu	proc :DWORD, :ptr
    PlayAtTime		proc :ptr, :DWORD, :ptr
    PlayChapter		proc :ULONG, :DWORD, :ptr
    PlayPrevChapter	proc :DWORD, :ptr
    ReplayChapter	proc :DWORD, :ptr
    PlayNextChapter	proc :DWORD, :ptr
    PlayForwards	proc :REAL8, :DWORD, :ptr
    PlayBackwards	proc :REAL8, :DWORD, :ptr
    ShowMenu		proc :DVD_MENU_ID, :DWORD, :ptr
    Resume		proc :DWORD, :ptr
    SelectRelativeButton proc :DVD_RELATIVE_BUTTON
    ActivateButton	proc
    SelectButton	proc :ULONG
    SelectAndActivateButton proc :ULONG
    StillOff		proc
    _Pause		proc :BOOL
    SelectAudioStream	proc :ULONG, :DWORD, :ptr
    SelectSubpictureStream proc :ULONG, :DWORD, :ptr
    SetSubpictureState	proc :BOOL, :DWORD, :ptr
    SelectAngle		proc :ULONG, :DWORD, :ptr
    SelectParentalLevel proc :ULONG
    SelectParentalCountry proc :ptr
    SelectKaraokeAudioPresentationMode proc :ULONG
    SelectVideoModePreference proc :ULONG
    SetDVDDirectory	proc :LPCWSTR
    ActivateAtPosition	proc :POINT
    SelectAtPosition	proc :POINT
    PlayChaptersAutoStop proc :ULONG, :ULONG, :ULONG, :DWORD, :ptr
    AcceptParentalLevelChange proc :BOOL
    SetOption		proc :DVD_OPTION_FLAG, :BOOL
    SetState		proc :ptr, :DWORD, :ptr
    PlayPeriodInTitleAutoStop proc :ULONG, :ptr, :ptr, :DWORD, :ptr
    SetGPRM		proc :ULONG, :WORD, :DWORD, :ptr
    SelectDefaultMenuLanguage proc :LCID
    SelectDefaultAudioLanguage proc :LCID, :DVD_AUDIO_LANG_EXT
    SelectDefaultSubpictureLanguage proc :LCID, :DVD_SUBPICTURE_LANG_EXT
    .ends

endif

DVD_TextStringType	typedef SDWORD
DVD_Struct_Volume	equ 0x1
DVD_Struct_Title	equ 0x2
DVD_Struct_ParentalID	equ 0x3
DVD_Struct_PartOfTitle	equ 0x4
DVD_Struct_Cell		equ 0x5
DVD_Stream_Audio	equ 0x10
DVD_Stream_Subpicture	equ 0x11
DVD_Stream_Angle	equ 0x12
DVD_Channel_Audio	equ 0x20
DVD_General_Name	equ 0x30
DVD_General_Comments	equ 0x31
DVD_Title_Series	equ 0x38
DVD_Title_Movie		equ 0x39
DVD_Title_Video		equ 0x3a
DVD_Title_Album		equ 0x3b
DVD_Title_Song		equ 0x3c
DVD_Title_Other		equ 0x3f
DVD_Title_Sub_Series	equ 0x40
DVD_Title_Sub_Movie	equ 0x41
DVD_Title_Sub_Video	equ 0x42
DVD_Title_Sub_Album	equ 0x43
DVD_Title_Sub_Song	equ 0x44
DVD_Title_Sub_Other	equ 0x47
DVD_Title_Orig_Series	equ 0x48
DVD_Title_Orig_Movie	equ 0x49
DVD_Title_Orig_Video	equ 0x4a
DVD_Title_Orig_Album	equ 0x4b
DVD_Title_Orig_Song	equ 0x4c
DVD_Title_Orig_Other	equ 0x4f
DVD_Other_Scene		equ 0x50
DVD_Other_Cut		equ 0x51
DVD_Other_Take		equ 0x52

DVD_TextCharSet		typedef SDWORD
DVD_CharSet_Unicode	equ 0
DVD_CharSet_ISO646	equ 1
DVD_CharSet_JIS_Roman_Kanji equ 2
DVD_CharSet_ISO8859_1	equ 3
DVD_CharSet_ShiftJIS_Kanji_Roman_Katakana equ 4
DVD_TITLE_MENU		equ 0x000
DVD_STREAM_DATA_CURRENT equ 0x800
DVD_STREAM_DATA_VMGM	equ 0x400
DVD_STREAM_DATA_VTSM	equ 0x401
DVD_DEFAULT_AUDIO_STREAM equ 0x0f
DVD_DECODER_CAPS	STRUC
dwSize			dd ?
dwAudioCaps		dd ?
dFwdMaxRateVideo	REAL8 ?
dFwdMaxRateAudio	REAL8 ?
dFwdMaxRateSP		REAL8 ?
dBwdMaxRateVideo	REAL8 ?
dBwdMaxRateAudio	REAL8 ?
dBwdMaxRateSP		REAL8 ?
dwRes1			dd ?
dwRes2			dd ?
dwRes3			dd ?
dwRes4			dd ?
DVD_DECODER_CAPS	ENDS

DVD_AUDIO_CAPS_AC3	equ 0x00000001
DVD_AUDIO_CAPS_MPEG2	equ 0x00000002
DVD_AUDIO_CAPS_LPCM	equ 0x00000004
DVD_AUDIO_CAPS_DTS	equ 0x00000008
DVD_AUDIO_CAPS_SDDS	equ 0x00000010

externdef		__MIDL_itf_strmif_0000_0116_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0116_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDvdInfo2_INTERFACE_DEFINED__
__IDvdInfo2_INTERFACE_DEFINED__ equ 1

externdef		IID_IDvdInfo2:IID

.comdef IDvdInfo2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrentDomain	proc :ptr
    GetCurrentLocation	proc :ptr
    GetTotalTitleTime	proc :ptr, :ptr
    GetCurrentButton	proc :ptr, :ptr
    GetCurrentAngle	proc :ptr, :ptr
    GetCurrentAudio	proc :ptr, :ptr
    GetCurrentSubpicture proc :ptr, :ptr, :ptr
    GetCurrentUOPS	proc :ptr
    GetAllSPRMs		proc :ptr
    GetAllGPRMs		proc :ptr
    GetAudioLanguage	proc :ULONG, :ptr
    GetSubpictureLanguage proc :ULONG, :ptr
    GetTitleAttributes	proc :ULONG, :ptr, :ptr
    GetVMGAttributes	proc :ptr
    GetCurrentVideoAttributes proc :ptr
    GetAudioAttributes	proc :ULONG, :ptr
    GetKaraokeAttributes proc :ULONG, :ptr
    GetSubpictureAttributes proc :ULONG, :ptr
    GetDVDVolumeInfo	proc :ptr, :ptr, :ptr, :ptr
    GetDVDTextNumberOfLanguages proc :ptr
    GetDVDTextLanguageInfo proc :ULONG, :ptr, :ptr, :ptr
    GetDVDTextStringAsNative proc :ULONG, :ULONG, :ptr, :ULONG, :ptr, :ptr
    GetDVDTextStringAsUnicode proc :ULONG, :ULONG, :ptr, :ULONG, :ptr, :ptr
    GetPlayerParentalLevel proc :ptr, :BYTE
    GetNumberOfChapters proc :ULONG, :ptr
    GetTitleParentalLevels proc :ULONG, :ptr
    GetDVDDirectory	proc :LPWSTR, :ULONG, :ptr
    IsAudioStreamEnabled proc :ULONG, :ptr
    GetDiscID		proc :LPCWSTR, :ptr
    GetState		proc :ptr
    GetMenuLanguages	proc :ptr, :ULONG, :ptr
    GetButtonAtPosition proc :POINT, :ptr
    GetCmdFromEvent	proc :LONG_PTR, :ptr
    GetDefaultMenuLanguage proc :ptr
    GetDefaultAudioLanguage proc :ptr, :ptr
    GetDefaultSubpictureLanguage proc :ptr, :ptr
    GetDecoderCaps	proc :ptr
    GetButtonRect	proc :ULONG, :ptr
    IsSubpictureStreamEnabled proc :ULONG, :ptr
    .ends

endif

AM_DVD_GRAPH_FLAGS	typedef SDWORD
AM_DVD_HWDEC_PREFER	equ 0x1
AM_DVD_HWDEC_ONLY	equ 0x2
AM_DVD_SWDEC_PREFER	equ 0x4
AM_DVD_SWDEC_ONLY	equ 0x8
AM_DVD_NOVPE		equ 0x100
AM_DVD_DO_NOT_CLEAR	equ 0x200
AM_DVD_VMR9_ONLY	equ 0x800
AM_DVD_EVR_ONLY		equ 0x1000
AM_DVD_EVR_QOS		equ 0x2000
AM_DVD_ADAPT_GRAPH	equ 0x4000
AM_DVD_MASK		equ 0xffff

AM_DVD_STREAM_FLAGS	typedef SDWORD
AM_DVD_STREAM_VIDEO	equ 0x1
AM_DVD_STREAM_AUDIO	equ 0x2
AM_DVD_STREAM_SUBPIC	equ 0x4

AM_DVD_RENDERSTATUS	STRUC
hrVPEStatus		HRESULT ?
bDvdVolInvalid		BOOL ?
bDvdVolUnknown		BOOL ?
bNoLine21In		BOOL ?
bNoLine21Out		BOOL ?
iNumStreams		SINT ?
iNumStreamsFailed	SINT ?
dwFailedStreamsFlag	dd ?
AM_DVD_RENDERSTATUS	ENDS

externdef		__MIDL_itf_strmif_0000_0117_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0117_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDvdGraphBuilder_INTERFACE_DEFINED__
__IDvdGraphBuilder_INTERFACE_DEFINED__ equ 1

externdef		IID_IDvdGraphBuilder:IID

.comdef IDvdGraphBuilder

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFiltergraph	proc :ptr
    GetDvdInterface	proc :REFIID, :ptr
    RenderDvdVideoVolume proc :LPCWSTR, :DWORD, :ptr
    .ends

endif

ifndef __IDDrawExclModeVideo_INTERFACE_DEFINED__
__IDDrawExclModeVideo_INTERFACE_DEFINED__ equ 1

externdef		IID_IDDrawExclModeVideo:IID

.comdef IDDrawExclModeVideo

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetDDrawObject	proc :ptr
    GetDDrawObject	proc :ptr, :ptr
    SetDDrawSurface	proc :ptr
    GetDDrawSurface	proc :ptr, :ptr
    SetDrawParameters	proc :ptr, :ptr
    GetNativeVideoProps proc :ptr, :ptr, :ptr, :ptr
    SetCallbackInterface proc :ptr, :DWORD
    .ends

endif

AM_OVERLAY_NOTIFY_FLAGS typedef SDWORD
AM_OVERLAY_NOTIFY_VISIBLE_CHANGE equ 0x1
AM_OVERLAY_NOTIFY_SOURCE_CHANGE equ 0x2
AM_OVERLAY_NOTIFY_DEST_CHANGE equ 0x4

externdef		__MIDL_itf_strmif_0000_0119_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0119_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDDrawExclModeVideoCallback_INTERFACE_DEFINED__
__IDDrawExclModeVideoCallback_INTERFACE_DEFINED__ equ 1

externdef		IID_IDDrawExclModeVideoCallback:IID

.comdef IDDrawExclModeVideoCallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnUpdateOverlay	proc :BOOL, :DWORD, :BOOL, :ptr, :ptr, :BOOL, :ptr, :ptr
    OnUpdateColorKey	proc :ptr, :DWORD
    OnUpdateSize	proc :DWORD, :DWORD, :DWORD, :DWORD
    .ends

endif

externdef		__MIDL_itf_strmif_0000_0120_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0120_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPinConnection_INTERFACE_DEFINED__
__IPinConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IPinConnection:IID

.comdef IPinConnection

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    DynamicQueryAccept	proc :ptr
    NotifyEndOfStream	proc :HANDLE
    IsEndPin		proc
    DynamicDisconnect	proc
    .ends

endif

ifndef __IPinFlowControl_INTERFACE_DEFINED__
__IPinFlowControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IPinFlowControl:IID

.comdef IPinFlowControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Block		proc :DWORD, :HANDLE
    .ends

endif

AM_PIN_FLOW_CONTROL_BLOCK_FLAGS typedef SDWORD
AM_PIN_FLOW_CONTROL_BLOCK equ 0x1
AM_GRAPH_CONFIG_RECONNECT_FLAGS typedef SDWORD
AM_GRAPH_CONFIG_RECONNECT_DIRECTCONNECT equ 0x1
AM_GRAPH_CONFIG_RECONNECT_CACHE_REMOVED_FILTERS equ 0x2
AM_GRAPH_CONFIG_RECONNECT_USE_ONLY_CACHED_FILTERS equ 0x4

REM_FILTER_FLAGS	typedef SDWORD
REMFILTERF_LEAVECONNECTED equ 0x1
AM_FILTER_FLAGS		typedef SDWORD
AM_FILTER_FLAGS_REMOVABLE equ 0x1

externdef		__MIDL_itf_strmif_0000_0122_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0122_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IGraphConfig_INTERFACE_DEFINED__
__IGraphConfig_INTERFACE_DEFINED__ equ 1

externdef		IID_IGraphConfig:IID

.comdef IGraphConfig

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Reconnect		proc :ptr, :ptr, :ptr, :ptr, :HANDLE, :DWORD
    Reconfigure		proc :ptr, :PVOID, :DWORD, :HANDLE
    AddFilterToCache	proc :ptr
    EnumCacheFilter	proc :ptr
    RemoveFilterFromCache proc :ptr
    GetStartTime	proc :ptr
    PushThroughData	proc :ptr, :ptr, :HANDLE
    SetFilterFlags	proc :ptr, :DWORD
    GetFilterFlags	proc :ptr, :ptr
    RemoveFilterEx	proc :ptr, :DWORD
    .ends

endif

ifndef __IGraphConfigCallback_INTERFACE_DEFINED__
__IGraphConfigCallback_INTERFACE_DEFINED__ equ 1

externdef		IID_IGraphConfigCallback:IID

.comdef IGraphConfigCallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Reconfigure		proc :PVOID, :DWORD
    .ends

endif

ifndef __IFilterChain_INTERFACE_DEFINED__
__IFilterChain_INTERFACE_DEFINED__ equ 1

externdef		IID_IFilterChain:IID

.comdef IFilterChain

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    StartChain		proc :ptr, :ptr
    PauseChain		proc :ptr, :ptr
    StopChain		proc :ptr, :ptr
    RemoveChain		proc :ptr, :ptr
    .ends

endif

if 0
LPDIRECTDRAW7		typedef ptr DWORD
LPDIRECTDRAWSURFACE7	typedef ptr DWORD
LPDDPIXELFORMAT		typedef ptr DWORD
LPBITMAPINFOHEADER	typedef ptr DWORD

DDCOLORKEY		STRUC
dw1			dd ?
dw2			dd ?
DDCOLORKEY		ENDS
LPDDCOLORKEY		typedef ptr DDCOLORKEY
endif

include ddraw.inc
.xlist

VMRPresentationFlags	typedef SDWORD
VMRSample_SyncPoint	equ 0x1
VMRSample_Preroll	equ 0x2
VMRSample_Discontinuity equ 0x4
VMRSample_TimeValid	equ 0x8
VMRSample_SrcDstRectsValid equ 0x10

VMRPRESENTATIONINFO	STRUC
dwFlags			dd ?
lpSurf			LPDIRECTDRAWSURFACE7 ?
rtStart			REFERENCE_TIME ?
rtEnd			REFERENCE_TIME ?
szAspectRatio		SIZEL <>
rcSrc			RECT <>
rcDst			RECT <>
dwTypeSpecificFlags	dd ?
dwInterlaceFlags	dd ?
VMRPRESENTATIONINFO	ENDS

externdef		__MIDL_itf_strmif_0000_0125_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0125_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRImagePresenter_INTERFACE_DEFINED__
__IVMRImagePresenter_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRImagePresenter:IID

.comdef IVMRImagePresenter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    StartPresenting	proc :DWORD_PTR
    StopPresenting	proc :DWORD_PTR
    PresentImage	proc :DWORD_PTR, :ptr
    .ends

endif

VMRSurfaceAllocationFlags typedef SDWORD
AMAP_PIXELFORMAT_VALID	equ 0x1
AMAP_3D_TARGET		equ 0x2
AMAP_ALLOW_SYSMEM	equ 0x4
AMAP_FORCE_SYSMEM	equ 0x8
AMAP_DIRECTED_FLIP	equ 0x10
AMAP_DXVA_TARGET	equ 0x20

VMRALLOCATIONINFO	STRUC
dwFlags			dd ?
lpHdr			LPBITMAPINFOHEADER ?
lpPixFmt		LPDDPIXELFORMAT ?
szAspectRatio		SIZEL <>
dwMinBuffers		dd ?
dwMaxBuffers		dd ?
dwInterlaceFlags	dd ?
szNativeSize		SIZEL <>
VMRALLOCATIONINFO	ENDS

externdef		__MIDL_itf_strmif_0000_0126_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0126_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRSurfaceAllocator_INTERFACE_DEFINED__
__IVMRSurfaceAllocator_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRSurfaceAllocator:IID

.comdef IVMRSurfaceAllocator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AllocateSurface	proc :DWORD_PTR, :ptr, :ptr, :ptr
    FreeSurface		proc :DWORD_PTR
    PrepareSurface	proc :DWORD_PTR, :LPDIRECTDRAWSURFACE7, :DWORD
    AdviseNotify	proc :ptr
    .ends

endif


ifndef __IVMRSurfaceAllocatorNotify_INTERFACE_DEFINED__
__IVMRSurfaceAllocatorNotify_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRSurfaceAllocatorNotify:IID

.comdef IVMRSurfaceAllocatorNotify

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AdviseSurfaceAllocator proc :DWORD_PTR, :ptr
    SetDDrawDevice	proc :LPDIRECTDRAW7, :HMONITOR
    ChangeDDrawDevice	proc :LPDIRECTDRAW7, :HMONITOR
    RestoreDDrawSurfaces proc
    NotifyEvent		proc :LONG, :LONG_PTR, :LONG_PTR
    SetBorderColor	proc :COLORREF
    .ends

endif

VMR_ASPECT_RATIO_MODE	typedef SDWORD
VMR_ARMODE_NONE		equ 0
VMR_ARMODE_LETTER_BOX	equ ( VMR_ARMODE_NONE + 1 )

externdef		__MIDL_itf_strmif_0000_0128_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0128_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRWindowlessControl_INTERFACE_DEFINED__
__IVMRWindowlessControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRWindowlessControl:IID

.comdef IVMRWindowlessControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetNativeVideoSize	proc :ptr, :ptr, :ptr, :ptr
    GetMinIdealVideoSize proc :ptr, :ptr
    GetMaxIdealVideoSize proc :ptr, :ptr
    SetVideoPosition	proc :LPRECT, :LPRECT
    GetVideoPosition	proc :LPRECT, :LPRECT
    GetAspectRatioMode	proc :ptr
    SetAspectRatioMode	proc :DWORD
    SetVideoClippingWindow proc :HWND
    RepaintVideo	proc :HWND, :HDC
    DisplayModeChanged	proc
    GetCurrentImage	proc :ptr
    SetBorderColor	proc :COLORREF
    GetBorderColor	proc :ptr
    SetColorKey		proc :COLORREF
    GetColorKey		proc :ptr
    .ends

endif

VMRMixerPrefs		typedef SDWORD
MixerPref_NoDecimation	equ 0x1
MixerPref_DecimateOutput equ 0x2
MixerPref_ARAdjustXorY	equ 0x4
MixerPref_DecimationReserved equ 0x8
MixerPref_DecimateMask	equ 0xf
MixerPref_BiLinearFiltering equ 0x10
MixerPref_PointFiltering equ 0x20
MixerPref_FilteringMask equ 0xf0
MixerPref_RenderTargetRGB equ 0x100
MixerPref_RenderTargetYUV equ 0x1000
MixerPref_RenderTargetYUV420 equ 0x200
MixerPref_RenderTargetYUV422 equ 0x400
MixerPref_RenderTargetYUV444 equ 0x800
MixerPref_RenderTargetReserved equ 0xe000
MixerPref_RenderTargetMask equ 0xff00
MixerPref_DynamicSwitchToBOB equ 0x10000
MixerPref_DynamicDecimateBy2 equ 0x20000
MixerPref_DynamicReserved equ 0xc0000
MixerPref_DynamicMask	equ 0xf0000

NORMALIZEDRECT		STRUC
left			REAL4 ?
top			REAL4 ?
right			REAL4 ?
bottom			REAL4 ?
NORMALIZEDRECT		ENDS

PNORMALIZEDRECT		typedef ptr NORMALIZEDRECT

externdef		__MIDL_itf_strmif_0000_0129_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0129_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRMixerControl_INTERFACE_DEFINED__
__IVMRMixerControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRMixerControl:IID

.comdef IVMRMixerControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetAlpha		proc :DWORD, :REAL4
    GetAlpha		proc :DWORD, :ptr
    SetZOrder		proc :DWORD, :DWORD
    GetZOrder		proc :DWORD, :ptr
    SetOutputRect	proc :DWORD, :ptr
    GetOutputRect	proc :DWORD, :ptr
    SetBackgroundClr	proc :COLORREF
    GetBackgroundClr	proc :ptr
    SetMixingPrefs	proc :DWORD
    GetMixingPrefs	proc :ptr
    .ends

endif

VMRGUID			STRUC
pGUID			LPGUID ?
GUID			GUID <>
VMRGUID			ENDS

VMRMONITORINFO		STRUC
guid			VMRGUID <>
rcMonitor		RECT <>
hMon			HMONITOR ?
dwFlags			dd ?
szDevice		wchar_t	 32  dup(?)
szDescription		wchar_t	 256  dup(?)
liDriverVersion		LARGE_INTEGER <>
dwVendorId		dd ?
dwDeviceId		dd ?
dwSubSysId		dd ?
dwRevision		dd ?
VMRMONITORINFO		ENDS

externdef		__MIDL_itf_strmif_0000_0130_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0130_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRMonitorConfig_INTERFACE_DEFINED__
__IVMRMonitorConfig_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRMonitorConfig:IID

.comdef IVMRMonitorConfig

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetMonitor		proc :ptr
    GetMonitor		proc :ptr
    SetDefaultMonitor	proc :ptr
    GetDefaultMonitor	proc :ptr
    GetAvailableMonitors proc :ptr, :DWORD, :ptr
    .ends

endif

VMRRenderPrefs		typedef SDWORD
RenderPrefs_RestrictToInitialMonitor equ 0
RenderPrefs_ForceOffscreen equ 0x1
RenderPrefs_ForceOverlays equ 0x2
RenderPrefs_AllowOverlays equ 0
RenderPrefs_AllowOffscreen equ 0
RenderPrefs_DoNotRenderColorKeyAndBorder equ 0x8
RenderPrefs_Reserved	equ 0x10
RenderPrefs_PreferAGPMemWhenMixing equ 0x20
RenderPrefs_Mask	equ 0x3f

VMRMode			typedef SDWORD
VMRMode_Windowed	equ 0x1
VMRMode_Windowless	equ 0x2
VMRMode_Renderless	equ 0x4
VMRMode_Mask		equ 0x7

_MIDL___MIDL_itf_strmif_0000_0131_0001 typedef SDWORD
MAX_NUMBER_OF_STREAMS	equ 16

externdef		__MIDL_itf_strmif_0000_0131_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0131_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRFilterConfig_INTERFACE_DEFINED__
__IVMRFilterConfig_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRFilterConfig:IID

.comdef IVMRFilterConfig

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetImageCompositor	proc :ptr
    SetNumberOfStreams	proc :DWORD
    GetNumberOfStreams	proc :ptr
    SetRenderingPrefs	proc :DWORD
    GetRenderingPrefs	proc :ptr
    SetRenderingMode	proc :DWORD
    GetRenderingMode	proc :ptr
    .ends

endif

ifndef __IVMRAspectRatioControl_INTERFACE_DEFINED__
__IVMRAspectRatioControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRAspectRatioControl:IID

.comdef IVMRAspectRatioControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetAspectRatioMode	proc :LPDWORD
    SetAspectRatioMode	proc :DWORD
    .ends

endif

VMRDeinterlacePrefs	typedef SDWORD
DeinterlacePref_NextBest equ 0x1
DeinterlacePref_BOB	equ 0x2
DeinterlacePref_Weave	equ 0x4
DeinterlacePref_Mask	equ 0x7

VMRDeinterlaceTech	typedef SDWORD
DeinterlaceTech_Unknown equ 0
DeinterlaceTech_BOBLineReplicate equ 0x1
DeinterlaceTech_BOBVerticalStretch equ 0x2
DeinterlaceTech_MedianFiltering equ 0x4
DeinterlaceTech_EdgeFiltering equ 0x10
DeinterlaceTech_FieldAdaptive equ 0x20
DeinterlaceTech_PixelAdaptive equ 0x40
DeinterlaceTech_MotionVectorSteered equ 0x80

VMRFrequency		STRUC
dwNumerator		dd ?
dwDenominator		dd ?
VMRFrequency		ENDS

VMRVideoDesc		STRUC
dwSize			dd ?
dwSampleWidth		dd ?
dwSampleHeight		dd ?
SingleFieldPerSample	BOOL ?
dwFourCC		dd ?
InputSampleFreq		VMRFrequency <>
OutputFrameFreq		VMRFrequency <>
VMRVideoDesc		ENDS

VMRDeinterlaceCaps	STRUC
dwSize			dd ?
dwNumPreviousOutputFrames dd ?
dwNumForwardRefSamples	dd ?
dwNumBackwardRefSamples dd ?
DeinterlaceTechnology	VMRDeinterlaceTech ?
VMRDeinterlaceCaps	ENDS

externdef		__MIDL_itf_strmif_0000_0133_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0133_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRDeinterlaceControl_INTERFACE_DEFINED__
__IVMRDeinterlaceControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRDeinterlaceControl:IID

.comdef IVMRDeinterlaceControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetNumberOfDeinterlaceModes proc :ptr, :LPDWORD, :LPGUID
    GetDeinterlaceModeCaps proc :LPGUID, :ptr, :ptr
    GetDeinterlaceMode	proc :DWORD, :LPGUID
    SetDeinterlaceMode	proc :DWORD, :LPGUID
    GetDeinterlacePrefs proc :LPDWORD
    SetDeinterlacePrefs proc :DWORD
    GetActualDeinterlaceMode proc :DWORD, :LPGUID
    .ends

endif

VMRALPHABITMAP		STRUC
dwFlags			dd ?
hdc			HDC ?
pDDS			LPDIRECTDRAWSURFACE7 ?
rSrc			RECT <>
rDest			NORMALIZEDRECT <>
fAlpha			FLOAT ?
clrSrcKey		COLORREF ?
VMRALPHABITMAP		ENDS

PVMRALPHABITMAP		typedef ptr VMRALPHABITMAP

VMRBITMAP_DISABLE	equ 0x00000001
VMRBITMAP_HDC		equ 0x00000002
VMRBITMAP_ENTIREDDS	equ 0x00000004
VMRBITMAP_SRCCOLORKEY	equ 0x00000008
VMRBITMAP_SRCRECT	equ 0x00000010

externdef		__MIDL_itf_strmif_0000_0134_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0134_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRMixerBitmap_INTERFACE_DEFINED__
__IVMRMixerBitmap_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRMixerBitmap:IID

.comdef IVMRMixerBitmap

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetAlphaBitmap	proc :ptr
    UpdateAlphaBitmapParameters proc :PVMRALPHABITMAP
    GetAlphaBitmapParameters proc :PVMRALPHABITMAP
    .ends

endif

VMRVIDEOSTREAMINFO	STRUC
pddsVideoSurface	LPDIRECTDRAWSURFACE7 ?
dwWidth			dd ?
dwHeight		dd ?
dwStrmID		dd ?
fAlpha			FLOAT ?
ddClrKey		DDCOLORKEY <>
rNormal			NORMALIZEDRECT <>
VMRVIDEOSTREAMINFO	ENDS

externdef		__MIDL_itf_strmif_0000_0135_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0135_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVMRImageCompositor_INTERFACE_DEFINED__
__IVMRImageCompositor_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRImageCompositor:IID

.comdef IVMRImageCompositor

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InitCompositionTarget proc :ptr, :LPDIRECTDRAWSURFACE7
    TermCompositionTarget proc :ptr, :LPDIRECTDRAWSURFACE7
    SetStreamMediaType	proc :DWORD, :ptr, :BOOL
    CompositeImage	proc :ptr, :LPDIRECTDRAWSURFACE7, :ptr, :REFERENCE_TIME, :REFERENCE_TIME, :DWORD, :ptr, :UINT
    .ends

endif

ifndef __IVMRVideoStreamControl_INTERFACE_DEFINED__
__IVMRVideoStreamControl_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRVideoStreamControl:IID

.comdef IVMRVideoStreamControl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetColorKey		proc :LPDDCOLORKEY
    GetColorKey		proc :LPDDCOLORKEY
    SetStreamActiveState proc :BOOL
    GetStreamActiveState proc :ptr
    .ends

endif


ifndef __IVMRSurface_INTERFACE_DEFINED__
__IVMRSurface_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRSurface:IID

.comdef IVMRSurface

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    IsSurfaceLocked	proc
    LockSurface		proc :ptr
    UnlockSurface	proc
    GetSurface		proc :ptr
    .ends

endif

ifndef __IVMRImagePresenterConfig_INTERFACE_DEFINED__
__IVMRImagePresenterConfig_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRImagePresenterConfig:IID

.comdef IVMRImagePresenterConfig

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetRenderingPrefs	proc :DWORD
    GetRenderingPrefs	proc :ptr
    .ends

endif

ifndef __IVMRImagePresenterExclModeConfig_INTERFACE_DEFINED__
__IVMRImagePresenterExclModeConfig_INTERFACE_DEFINED__ equ 1

externdef		IID_IVMRImagePresenterExclModeConfig:IID

.comdef IVMRImagePresenterExclModeConfig

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetRenderingPrefs	proc :DWORD
    GetRenderingPrefs	proc :ptr
    SetXlcModeDDObjAndPrimarySurface proc :LPDIRECTDRAW7, :LPDIRECTDRAWSURFACE7
    GetXlcModeDDObjAndPrimarySurface proc :ptr, :ptr
    .ends

endif


ifndef __IVPManager_INTERFACE_DEFINED__
__IVPManager_INTERFACE_DEFINED__ equ 1

externdef		IID_IVPManager:IID

.comdef IVPManager

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetVideoPortIndex	proc :DWORD
    GetVideoPortIndex	proc :ptr
    .ends

endif

externdef		__MIDL_itf_strmif_0000_0141_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_strmif_0000_0141_v0_0_s_ifspec:RPC_IF_HANDLE

.list
endif
