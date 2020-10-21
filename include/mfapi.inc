include winapifamily.inc

ifndef __MFAPI_H__
__MFAPI_H__ equ <>

.pragma pack(push, 1)
include mfobjects.inc
.pragma pack(pop)

include mmreg.inc

include avrt.inc

ifndef AVRT_DATA
AVRT_DATA equ 1
endif
ifndef AVRT_BSS
AVRT_BSS equ 1
endif

ifndef MF_VERSION

if (WINVER GE _WIN32_WINNT_WIN7)
MF_SDK_VERSION		equ 0x0002
else
MF_SDK_VERSION		equ 0x0001
endif

MF_API_VERSION		equ 0x0070
MF_VERSION		equ (MF_SDK_VERSION SHL 16 OR MF_API_VERSION)

endif


MFSTARTUP_NOSOCKET	equ 0x1
MFSTARTUP_LITE		equ (MFSTARTUP_NOSOCKET)
MFSTARTUP_FULL		equ 0

.pragma comment(lib, mfplat)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MFStartup proto WINAPI \
	       Version: ULONG,
	       dwFlags: DWORD
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFShutdown proto WINAPI


MFLockPlatform proto WINAPI
MFUnlockPlatform proto WINAPI

MFWORKITEM_KEY		typedef qword

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFPutWorkItem proto WINAPI \
	       dwQueue: DWORD,
	     pCallback: ptr,
		pState: ptr


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFPutWorkItem2 proto WINAPI \
	       dwQueue: DWORD,
	      Priority: LONG,
	     pCallback: ptr IMFAsyncCallback,
		pState: ptr IUnknown


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFPutWorkItemEx proto WINAPI \
	       dwQueue: DWORD,
	       pResult: ptr


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFPutWorkItemEx2 proto WINAPI \
	       dwQueue: DWORD,
	      Priority: LONG,
	       pResult: ptr IMFAsyncResult

MFPutWaitingWorkItem proto WINAPI \
		hEvent: HANDLE,
	      Priority: LONG,
	       pResult: ptr IMFAsyncResult,
		  pKey: ptr MFWORKITEM_KEY

MFAllocateSerialWorkQueue proto WINAPI \
	   dwWorkQueue: DWORD,
	  pdwWorkQueue: ptr DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFScheduleWorkItem proto WINAPI \
	     pCallback: ptr,
		pState: ptr,
	       Timeout: INT64,
		  pKey: ptr MFWORKITEM_KEY

MFScheduleWorkItemEx proto WINAPI \
	       pResult: ptr,
	       Timeout: INT64,
		  pKey: ptr MFWORKITEM_KEY


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCancelWorkItem proto WINAPI \
		   Key: MFWORKITEM_KEY


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFGetTimerPeriodicity proto WINAPI \
	   Periodicity: ptr DWORD


CALLBACK(MFPERIODICCALLBACK, pContext:ptr IUnknown)

MFAddPeriodicCallback proto WINAPI \
	      Callback: MFPERIODICCALLBACK,
	      pContext: ptr,
		pdwKey: ptr DWORD

MFRemovePeriodicCallback proto WINAPI \
		 dwKey: DWORD


if (WINVER GE _WIN32_WINNT_WIN7)

.enum MFASYNC_WORKQUEUE_TYPE {
    MF_STANDARD_WORKQUEUE = 0,
    MF_WINDOW_WORKQUEUE = 1,
    MF_MULTITHREADED_WORKQUEUE = 2,
    }

MFAllocateWorkQueueEx proto WINAPI \
	 WorkQueueType: MFASYNC_WORKQUEUE_TYPE,
	  pdwWorkQueue: ptr DWORD

endif

MFAllocateWorkQueue proto WINAPI \
	  pdwWorkQueue: ptr DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFLockWorkQueue proto WINAPI \
	   dwWorkQueue: DWORD


MFUnlockWorkQueue proto WINAPI \
	   dwWorkQueue: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFBeginRegisterWorkQueueWithMMCSS proto WINAPI \
	 dwWorkQueueId: DWORD,
	      wszClass: LPCWSTR,
	      dwTaskId: DWORD,
	 pDoneCallback: ptr IMFAsyncCallback,
	    pDoneState: ptr IUnknown

MFBeginRegisterWorkQueueWithMMCSSEx proto WINAPI \
	 dwWorkQueueId: DWORD,
	      wszClass: LPCWSTR,
	      dwTaskId: DWORD,
	     lPriority: LONG,
	 pDoneCallback: ptr IMFAsyncCallback,
	    pDoneState: ptr IUnknown

MFEndRegisterWorkQueueWithMMCSS proto WINAPI \
	       pResult: ptr IMFAsyncResult,
	     pdwTaskId: ptr DWORD

MFBeginUnregisterWorkQueueWithMMCSS proto WINAPI \
	 dwWorkQueueId: DWORD,
	 pDoneCallback: ptr IMFAsyncCallback,
	    pDoneState: ptr IUnknown

MFEndUnregisterWorkQueueWithMMCSS proto WINAPI \
	       pResult: ptr IMFAsyncResult

MFGetWorkQueueMMCSSClass proto WINAPI \
	 dwWorkQueueId: DWORD,
	     pwszClass: LPWSTR,
	     pcchClass: ptr DWORD

MFGetWorkQueueMMCSSTaskId proto WINAPI \
	 dwWorkQueueId: DWORD,
	     pdwTaskId: LPDWORD

MFRegisterPlatformWithMMCSS proto WINAPI \
	      wszClass: PCWSTR,
	     pdwTaskId: ptr DWORD,
	     lPriority: LONG

MFUnregisterPlatformFromMMCSS proto WINAPI

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFLockSharedWorkQueue proto WINAPI \
	      wszClass: PCWSTR,
	  BasePriority: LONG,
	     pdwTaskId: ptr DWORD,
		   pID: ptr DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFGetWorkQueueMMCSSPriority proto WINAPI \
	 dwWorkQueueId: DWORD,
	     lPriority: ptr LONG

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateAsyncResult proto WINAPI \
	    punkObject: ptr,
	     pCallback: ptr,
	     punkState: ptr,
	 ppAsyncResult: ptr IMFAsyncResult


MFInvokeCallback proto WINAPI \
	  pAsyncResult: ptr

if defined(__cplusplus) and not defined(CINTERFACE)
.template MFASYNCRESULT : public IMFAsyncResult

    overlapped		OVERLAPPED ?
    pCallback		LPIMFAsyncCallback ?
    hrStatusResult	HRESULT ?
    dwBytesTransferred	dd ?
    hEvent		HANDLE ?

    .ends
else
LPIMFAsyncCallback	typedef ptr IMFAsyncCallback
MFASYNCRESULT		STRUC
AsyncResult		IMFAsyncResult <>
overlapped		OVERLAPPED <>
pCallback		LPIMFAsyncCallback ?
hrStatusResult		HRESULT ?
dwBytesTransferred	dd ?
hEvent			HANDLE ?
MFASYNCRESULT		ENDS
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateFile proto WINAPI \
	    AccessMode: MF_FILE_ACCESSMODE,
	      OpenMode: MF_FILE_OPENMODE,
		fFlags: MF_FILE_FLAGS,
	   pwszFileURL: LPCWSTR,
	 ppIByteStream: ptr IMFByteStream


MFCreateTempFile proto WINAPI \
	    AccessMode: MF_FILE_ACCESSMODE,
	      OpenMode: MF_FILE_OPENMODE,
		fFlags: MF_FILE_FLAGS,
	 ppIByteStream: ptr IMFByteStream


MFBeginCreateFile proto WINAPI \
	    AccessMode: MF_FILE_ACCESSMODE,
	      OpenMode: MF_FILE_OPENMODE,
		fFlags: MF_FILE_FLAGS,
	  pwszFilePath: LPCWSTR,
	     pCallback: ptr,
		pState: ptr,
	ppCancelCookie: ptr IUnknown


MFEndCreateFile proto WINAPI \
	       pResult: ptr,
		ppFile: ptr IMFByteStream


MFCancelCreateFile proto WINAPI \
	 pCancelCookie: ptr



endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateMemoryBuffer proto WINAPI \
	   cbMaxLength: DWORD,
	      ppBuffer: ptr IMFMediaBuffer


MFCreateMediaBufferWrapper proto WINAPI \
	       pBuffer: ptr IMFMediaBuffer,
	      cbOffset: DWORD,
	      dwLength: DWORD,
	      ppBuffer: ptr IMFMediaBuffer


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateLegacyMediaBufferOnMFMediaBuffer proto WINAPI \
	       pSample: ptr IMFSample,
	   pMFMediaBuffer: ptr IMFMediaBuffer,
	      cbOffset: DWORD,
	 ppMediaBuffer: ptr IMediaBuffer


include dxgiformat.inc

MFMapDX9FormatToDXGIFormat proto WINAPI \
		   dx9: DWORD


MFMapDXGIFormatToDX9Format proto WINAPI \
		  dx11: DXGI_FORMAT


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFLockDXGIDeviceManager proto WINAPI \
	   pResetToken: ptr UINT,
	     ppManager: ptr ptr IMFDXGIDeviceManager


MFUnlockDXGIDeviceManager proto WINAPI
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateDXSurfaceBuffer proto WINAPI \
		  riid: REFIID,
		 punkSurface: ptr IUnknown,
   fBottomUpWhenLinear: BOOL,
	      ppBuffer: ptr IMFMediaBuffer


MFCreateWICBitmapBuffer proto WINAPI \
		  riid: REFIID,
		 punkSurface: ptr IUnknown,
	      ppBuffer: ptr IMFMediaBuffer


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateDXGISurfaceBuffer proto WINAPI \
		  riid: REFIID,
	   punkSurface: ptr IUnknown,
     uSubresourceIndex: UINT,
   fBottomUpWhenLinear: BOOL,
	      ppBuffer: ptr ptr IMFMediaBuffer


MFCreateVideoSampleAllocatorEx proto WINAPI \
		  riid: REFIID,
     ppSampleAllocator: ptr ptr

MFCreateDXGIDeviceManager proto WINAPI \
	    resetToken: ptr UINT,
       ppDeviceManager: ptr ptr IMFDXGIDeviceManager


MF_E_DXGI_DEVICE_NOT_INITIALIZED equ (0x80041000)
MF_E_DXGI_NEW_VIDEO_DEVICE equ (0x80041001)
MF_E_DXGI_VIDEO_DEVICE_LOCKED equ (0x80041002)

MF_1_BYTE_ALIGNMENT	equ 0x00000000
MF_2_BYTE_ALIGNMENT	equ 0x00000001
MF_4_BYTE_ALIGNMENT	equ 0x00000003
MF_8_BYTE_ALIGNMENT	equ 0x00000007
MF_16_BYTE_ALIGNMENT	equ 0x0000000f
MF_32_BYTE_ALIGNMENT	equ 0x0000001f
MF_64_BYTE_ALIGNMENT	equ 0x0000003f
MF_128_BYTE_ALIGNMENT	equ 0x0000007f
MF_256_BYTE_ALIGNMENT	equ 0x000000ff
MF_512_BYTE_ALIGNMENT	equ 0x000001ff

MFCreateAlignedMemoryBuffer proto WINAPI \
	   cbMaxLength: DWORD,
	    cbAligment: DWORD,
	      ppBuffer: ptr IMFMediaBuffer


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

externdef		MR_BUFFER_SERVICE:GUID

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateMediaEvent proto WINAPI \
		   met: MediaEventType,
      guidExtendedType: REFGUID,
	      hrStatus: HRESULT,
	       pvValue: ptr PROPVARIANT,
	       ppEvent: ptr IMFMediaEvent


MFCreateEventQueue proto WINAPI \
     ppMediaEventQueue: ptr IMFMediaEventQueue


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


DEFINE_GUID(MF_EVENT_SESSIONCAPS, 0x7e5ebcd0, 0x11b8, 0x4abe, 0xaf, 0xad, 0x10, 0xf6, 0x59, 0x9a, 0x7f, 0x42)
DEFINE_GUID(MF_EVENT_SESSIONCAPS_DELTA, 0x7e5ebcd1, 0x11b8, 0x4abe, 0xaf, 0xad, 0x10, 0xf6, 0x59, 0x9a, 0x7f, 0x42)

MFSESSIONCAP_START	equ 0x00000001
MFSESSIONCAP_SEEK	equ 0x00000002
MFSESSIONCAP_PAUSE	equ 0x00000004
MFSESSIONCAP_RATE_FORWARD equ 0x00000010
MFSESSIONCAP_RATE_REVERSE equ 0x00000020
MFSESSIONCAP_DOES_NOT_USE_NETWORK equ 0x00000040

.enum {
    MF_TOPOSTATUS_INVALID = 0,
    MF_TOPOSTATUS_READY	    = 100,
    MF_TOPOSTATUS_STARTED_SOURCE = 200,
if (WINVER GE _WIN32_WINNT_WIN7)
    MF_TOPOSTATUS_DYNAMIC_CHANGED = 210,
endif
    MF_TOPOSTATUS_SINK_SWITCHED = 300,
    MF_TOPOSTATUS_ENDED = 400,
    }

DEFINE_GUID(MF_EVENT_TOPOLOGY_STATUS, 0x30c5018d, 0x9a53, 0x454b, 0xad, 0x9e, 0x6d, 0x5f, 0x8f, 0xa7, 0xc4, 0x3b);
DEFINE_GUID(MF_EVENT_START_PRESENTATION_TIME, 0x5ad914d0, 0x9b45, 0x4a8d, 0xa2, 0xc0, 0x81, 0xd1, 0xe5, 0xb, 0xfb, 0x7);
DEFINE_GUID(MF_EVENT_PRESENTATION_TIME_OFFSET, 0x5ad914d1, 0x9b45, 0x4a8d, 0xa2, 0xc0, 0x81, 0xd1, 0xe5, 0xb, 0xfb, 0x7);
DEFINE_GUID(MF_EVENT_START_PRESENTATION_TIME_AT_OUTPUT, 0x5ad914d2, 0x9b45, 0x4a8d, 0xa2, 0xc0, 0x81, 0xd1, 0xe5, 0xb, 0xfb, 0x7);
DEFINE_GUID(MF_EVENT_SOURCE_FAKE_START, 0xa8cc55a7, 0x6b31, 0x419f, 0x84, 0x5d, 0xff, 0xb3, 0x51, 0xa2, 0x43, 0x4b);
DEFINE_GUID(MF_EVENT_SOURCE_PROJECTSTART, 0xa8cc55a8, 0x6b31, 0x419f, 0x84, 0x5d, 0xff, 0xb3, 0x51, 0xa2, 0x43, 0x4b);
DEFINE_GUID(MF_EVENT_SOURCE_ACTUAL_START, 0xa8cc55a9, 0x6b31, 0x419f, 0x84, 0x5d, 0xff, 0xb3, 0x51, 0xa2, 0x43, 0x4b);
DEFINE_GUID(MF_EVENT_SOURCE_TOPOLOGY_CANCELED, 0xdb62f650, 0x9a5e, 0x4704, 0xac, 0xf3, 0x56, 0x3b, 0xc6, 0xa7, 0x33, 0x64);
DEFINE_GUID(MF_EVENT_SOURCE_CHARACTERISTICS, 0x47db8490, 0x8b22, 0x4f52, 0xaf, 0xda, 0x9c, 0xe1, 0xb2, 0xd3, 0xcf, 0xa8);
DEFINE_GUID(MF_EVENT_SOURCE_CHARACTERISTICS_OLD, 0x47db8491, 0x8b22, 0x4f52, 0xaf, 0xda, 0x9c, 0xe1, 0xb2, 0xd3, 0xcf, 0xa8);
DEFINE_GUID(MF_EVENT_DO_THINNING, 0x321ea6fb, 0xdad9, 0x46e4, 0xb3, 0x1d, 0xd2, 0xea, 0xe7, 0x9, 0xe, 0x30);
DEFINE_GUID(MF_EVENT_SCRUBSAMPLE_TIME, 0x9ac712b3, 0xdcb8, 0x44d5, 0x8d, 0xc, 0x37, 0x45, 0x5a, 0x27, 0x82, 0xe3);
DEFINE_GUID(MF_EVENT_OUTPUT_NODE, 0x830f1a8b, 0xc060, 0x46dd, 0xa8, 0x01, 0x1c, 0x95, 0xde, 0xc9, 0xb1, 0x07);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID(MF_EVENT_MFT_INPUT_STREAM_ID, 0xf29c2cca, 0x7ae6, 0x42d2, 0xb2, 0x84, 0xbf, 0x83, 0x7c, 0xc8, 0x74, 0xe2);
DEFINE_GUID(MF_EVENT_MFT_CONTEXT, 0xb7cd31f1, 0x899e, 0x4b41, 0x80, 0xc9, 0x26, 0xa8, 0x96, 0xd3, 0x29, 0x77);

endif

if (WINVER GE _WIN32_WINNT_WINBLUE)
DEFINE_GUID(MF_EVENT_STREAM_METADATA_KEYDATA, 0xcd59a4a1, 0x4a3b, 0x4bbd, 0x86, 0x65, 0x72, 0xa4, 0xf, 0xbe, 0xa7, 0x76);
DEFINE_GUID(MF_EVENT_STREAM_METADATA_CONTENT_KEYIDS, 0x5063449d, 0xcc29, 0x4fc6, 0xa7, 0x5a, 0xd2, 0x47, 0xb3, 0x5a, 0xf8, 0x5c);
DEFINE_GUID(MF_EVENT_STREAM_METADATA_SYSTEMID, 0x1ea2ef64, 0xba16, 0x4a36, 0x87, 0x19, 0xfe, 0x75, 0x60, 0xba, 0x32, 0xad);

endif

MFCreateSample proto WINAPI \
	   ppIMFSample: ptr IMFSample

DEFINE_GUID(MFSampleExtension_CleanPoint, 0x9cdf01d8, 0xa0f0, 0x43ba, 0xb0, 0x77, 0xea, 0xa0, 0x6c, 0xbd, 0x72, 0x8a);
DEFINE_GUID(MFSampleExtension_Discontinuity, 0x9cdf01d9, 0xa0f0, 0x43ba, 0xb0, 0x77, 0xea, 0xa0, 0x6c, 0xbd, 0x72, 0x8a);
DEFINE_GUID(MFSampleExtension_Token, 0x8294da66, 0xf328, 0x4805, 0xb5, 0x51, 0x00, 0xde, 0xb4, 0xc5, 0x7a, 0x61);
DEFINE_GUID(MFSampleExtension_DecodeTimestamp, 0x73a954d4, 0x9e2, 0x4861, 0xbe, 0xfc, 0x94, 0xbd, 0x97, 0xc0, 0x8e, 0x6e);
DEFINE_GUID(MFSampleExtension_VideoEncodeQP, 0xb2efe478, 0xf979, 0x4c66, 0xb9, 0x5e, 0xee, 0x2b, 0x82, 0xc8, 0x2f, 0x36);
DEFINE_GUID(MFSampleExtension_VideoEncodePictureType, 0x973704e6, 0xcd14, 0x483c, 0x8f, 0x20, 0xc9, 0xfc, 0x9, 0x28, 0xba, 0xd5);
DEFINE_GUID(MFSampleExtension_FrameCorruption, 0xb4dd4a8c, 0xbeb, 0x44c4, 0x8b, 0x75, 0xb0, 0x2b, 0x91, 0x3b, 0x4, 0xf0);
DEFINE_GUID(MFSampleExtension_DescrambleData, 0x43483be6, 0x4903, 0x4314, 0xb0, 0x32, 0x29, 0x51, 0x36, 0x59, 0x36, 0xfc);
DEFINE_GUID(MFSampleExtension_SampleKeyID, 0x9ed713c8, 0x9b87, 0x4b26, 0x82, 0x97, 0xa9, 0x3b, 0x0c, 0x5a, 0x8a, 0xcc);
DEFINE_GUID(MFSampleExtension_GenKeyFunc, 0x441ca1ee, 0x6b1f, 0x4501, 0x90, 0x3a, 0xde, 0x87, 0xdf, 0x42, 0xf6, 0xed);
DEFINE_GUID(MFSampleExtension_GenKeyCtx, 0x188120cb, 0xd7da, 0x4b59, 0x9b, 0x3e, 0x92, 0x52, 0xfd, 0x37, 0x30, 0x1c);
DEFINE_GUID(MFSampleExtension_PacketCrossOffsets, 0x2789671d, 0x389f, 0x40bb, 0x90, 0xd9, 0xc2, 0x82, 0xf7, 0x7f, 0x9a, 0xbd);
DEFINE_GUID(MFSampleExtension_Encryption_SampleID, 0x6698b84e, 0x0afa, 0x4330, 0xae, 0xb2, 0x1c, 0x0a, 0x98, 0xd7, 0xa4, 0x4d);
DEFINE_GUID(MFSampleExtension_Encryption_KeyID, 0x76376591, 0x795f, 0x4da1, 0x86, 0xed, 0x9d, 0x46, 0xec, 0xa1, 0x09, 0xa9);
DEFINE_GUID(MFSampleExtension_Content_KeyID, 0xc6c7f5b0, 0xacca, 0x415b, 0x87, 0xd9, 0x10, 0x44, 0x14, 0x69, 0xef, 0xc6);
DEFINE_GUID(MFSampleExtension_Encryption_SubSampleMappingSplit, 0xfe0254b9, 0x2aa5, 0x4edc, 0x99, 0xf7, 0x17, 0xe8, 0x9d, 0xbf, 0x91, 0x74);
DEFINE_GUID(MFSampleExtension_Interlaced, 0xb1d5830a, 0xdeb8, 0x40e3, 0x90, 0xfa, 0x38, 0x99, 0x43, 0x71, 0x64, 0x61);
DEFINE_GUID(MFSampleExtension_BottomFieldFirst, 0x941ce0a3, 0x6ae3, 0x4dda, 0x9a, 0x08, 0xa6, 0x42, 0x98, 0x34, 0x06, 0x17);
DEFINE_GUID(MFSampleExtension_RepeatFirstField, 0x304d257c, 0x7493, 0x4fbd, 0xb1, 0x49, 0x92, 0x28, 0xde, 0x8d, 0x9a, 0x99);
DEFINE_GUID(MFSampleExtension_SingleField, 0x9d85f816, 0x658b, 0x455a, 0xbd, 0xe0, 0x9f, 0xa7, 0xe1, 0x5a, 0xb8, 0xf9);
DEFINE_GUID(MFSampleExtension_DerivedFromTopField, 0x6852465a, 0xae1c, 0x4553, 0x8e, 0x9b, 0xc3, 0x42, 0x0f, 0xcb, 0x16, 0x37);
DEFINE_GUID(MFSampleExtension_MeanAbsoluteDifference, 0x1cdbde11, 0x08b4, 0x4311, 0xa6, 0xdd, 0x0f, 0x9f, 0x37, 0x19, 0x07, 0xaa);
DEFINE_GUID(MFSampleExtension_LongTermReferenceFrameInfo, 0x9154733f, 0xe1bd, 0x41bf, 0x81, 0xd3, 0xfc, 0xd9, 0x18, 0xf7, 0x13, 0x32);
DEFINE_GUID(MFSampleExtension_ROIRectangle, 0x3414a438, 0x4998, 0x4d2c, 0xbe, 0x82, 0xbe, 0x3c, 0xa0, 0xb2, 0x4d, 0x43);

ROI_AREA		STRUC
rect			RECT <>
QPDelta			INT32 ?
ROI_AREA		ENDS
PROI_AREA		typedef ptr ROI_AREA

DEFINE_GUID(MFSampleExtension_PhotoThumbnail, 0x74BBC85C, 0xC8BB, 0x42DC, 0xB5, 0x86, 0xDA, 0x17, 0xFF, 0xD3, 0x5D, 0xCC);
DEFINE_GUID(MFSampleExtension_PhotoThumbnailMediaType, 0x61AD5420, 0xEBF8, 0x4143, 0x89, 0xAF, 0x6B, 0xF2, 0x5F, 0x67, 0x2D, 0xEF);
DEFINE_GUID(MFSampleExtension_CaptureMetadata, 0x2EBE23A8, 0xFAF5, 0x444A, 0xA6, 0xA2, 0xEB, 0x81, 0x08, 0x80, 0xAB, 0x5D);
DEFINE_GUID(MF_CAPTURE_METADATA_PHOTO_FRAME_FLASH, 0x0F9DD6C6, 0x6003, 0x45D8, 0xBD, 0x59, 0xF1, 0xF5, 0x3E, 0x3D, 0x04, 0xE8);

MFCreateAttributes proto WINAPI \
	ppMFAttributes: ptr ptr IMFAttributes,
	  cInitialSize: UINT32

MFInitAttributesFromBlob proto WINAPI \
	   pAttributes: ptr IMFAttributes,
	    pBuf: ptr UINT8,
	     cbBufSize: UINT

MFGetAttributesAsBlobSize proto WINAPI \
	   pAttributes: ptr IMFAttributes,
	    pcbBufSize: ptr UINT32

MFGetAttributesAsBlob proto WINAPI \
	   pAttributes: ptr IMFAttributes,
		  pBuf: ptr UINT8,
	     cbBufSize: UINT


ifdef MF_INIT_GUIDS
include initguid.inc
endif

DEFINE_GUID(MFT_CATEGORY_VIDEO_DECODER, 0xd6c02d4b, 0x6833, 0x45b4, 0x97, 0x1a, 0x05, 0xa4, 0xb0, 0x4b, 0xab, 0x91);
DEFINE_GUID(MFT_CATEGORY_VIDEO_ENCODER, 0xf79eac7d, 0xe545, 0x4387, 0xbd, 0xee, 0xd6, 0x47, 0xd7, 0xbd, 0xe4, 0x2a);
DEFINE_GUID(MFT_CATEGORY_VIDEO_EFFECT, 0x12e17c21, 0x532c, 0x4a6e, 0x8a, 0x1c, 0x40, 0x82, 0x5a, 0x73, 0x63, 0x97);
DEFINE_GUID(MFT_CATEGORY_MULTIPLEXER, 0x059c561e, 0x05ae, 0x4b61, 0xb6, 0x9d, 0x55, 0xb6, 0x1e, 0xe5, 0x4a, 0x7b);
DEFINE_GUID(MFT_CATEGORY_DEMULTIPLEXER, 0xa8700a7a, 0x939b, 0x44c5, 0x99, 0xd7, 0x76, 0x22, 0x6b, 0x23, 0xb3, 0xf1);
DEFINE_GUID(MFT_CATEGORY_AUDIO_DECODER, 0x9ea73fb4, 0xef7a, 0x4559, 0x8d, 0x5d, 0x71, 0x9d, 0x8f, 0x04, 0x26, 0xc7);
DEFINE_GUID(MFT_CATEGORY_AUDIO_ENCODER, 0x91c64bd0, 0xf91e, 0x4d8c, 0x92, 0x76, 0xdb, 0x24, 0x82, 0x79, 0xd9, 0x75);
DEFINE_GUID(MFT_CATEGORY_AUDIO_EFFECT, 0x11064c48, 0x3648, 0x4ed0, 0x93, 0x2e, 0x05, 0xce, 0x8a, 0xc8, 0x11, 0xb7);

if (WINVER GE _WIN32_WINNT_WIN7)

DEFINE_GUID(MFT_CATEGORY_VIDEO_PROCESSOR, 0x302ea3fc, 0xaa5f, 0x47f9, 0x9f, 0x7a, 0xc2, 0x18, 0x8b, 0xb1, 0x63, 0x2);
endif
DEFINE_GUID(MFT_CATEGORY_OTHER, 0x90175d57, 0xb7ea, 0x4901, 0xae, 0xb3, 0x93, 0x3a, 0x87, 0x47, 0x75, 0x6f);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFTRegister proto WINAPI \
	      clsidMFT: CLSID,
	  guidCategory: GUID,
	       pszName: LPWSTR,
		 Flags: UINT32,
	   cInputTypes: UINT32,
	   pInputTypes: ptr MFT_REGISTER_TYPE_INFO,
	  cOutputTypes: UINT32,


MFTUnregister proto WINAPI \
	      clsidMFT: CLSID


if (WINVER GE _WIN32_WINNT_WIN7)

MFTRegisterLocal proto WINAPI \
	 pClassFactory: ptr IClassFactory,
	  guidCategory: REFGUID,
	       pszName: LPCWSTR,
		 Flags: UINT32,
	   cInputTypes: UINT32,
	   pInputTypes: ptr MFT_REGISTER_TYPE_INFO,
	  cOutputTypes: UINT32,
		      : ptr MFT_REGISTER_TYPE_INFO


MFTUnregisterLocal proto WINAPI \
	 pClassFactory: ptr IClassFactory


MFTRegisterLocalByCLSID proto WINAPI \
	      clisdMFT: REFCLSID,
	  guidCategory: REFGUID,
	       pszName: LPCWSTR,
		 Flags: UINT32,
	   cInputTypes: UINT32,
	   pInputTypes: ptr MFT_REGISTER_TYPE_INFO,
	  cOutputTypes: UINT32,
		      : ptr MFT_REGISTER_TYPE_INFO

MFTUnregisterLocalByCLSID proto WINAPI \
	      clsidMFT: CLSID

endif

MFTEnum proto WINAPI \
	  guidCategory: GUID,
		 Flags: UINT32,
	    pInputType: ptr MFT_REGISTER_TYPE_INFO,
	   pOutputType: ptr MFT_REGISTER_TYPE_INFO,
	   pAttributes: ptr IMFAttributes,
	    ppclsidMFT: ptr ptr CLSID,
		pcMFTs: ptr UINT32


if (WINVER GE _WIN32_WINNT_WIN7)

.enum MFT_ENUM_FLAG {
    MFT_ENUM_FLAG_SYNCMFT			= 0x00000001,
    MFT_ENUM_FLAG_ASYNCMFT			= 0x00000002,
    MFT_ENUM_FLAG_HARDWARE			= 0x00000004,
    MFT_ENUM_FLAG_FIELDOFUSE			= 0x00000008,
    MFT_ENUM_FLAG_LOCALMFT			= 0x00000010,
    MFT_ENUM_FLAG_TRANSCODE_ONLY		= 0x00000020,
    MFT_ENUM_FLAG_SORTANDFILTER			= 0x00000040,
    MFT_ENUM_FLAG_SORTANDFILTER_APPROVED_ONLY	= 0x000000C0,
    MFT_ENUM_FLAG_SORTANDFILTER_WEB_ONLY	= 0x00000140,
    MFT_ENUM_FLAG_ALL				= 0x0000003F
    }

MFTEnumEx proto WINAPI \
	  guidCategory: ptr GUID,
		 Flags: UINT32,
	    pInputType: ptr MFT_REGISTER_TYPE_INFO,
	   pOutputType: ptr MFT_REGISTER_TYPE_INFO,
	pppMFTActivate: ptr ptr ptr IMFActivate,
       pnumMFTActivate: ptr UINT32

endif

MFTGetInfo proto WINAPI \
	      clsidMFT: ptr CLSID,
	       pszName: ptr LPWSTR,
	  ppInputTypes: ptr ptr MFT_REGISTER_TYPE_INFO,
	  pcInputTypes: ptr UINT32,
	 ppOutputTypes: ptr ptr MFT_REGISTER_TYPE_INFO,
	 pcOutputTypes: ptr UINT32,



if (WINVER GE _WIN32_WINNT_WIN7)

MFGetPluginControl proto WINAPI \
       ppPluginControl: ptr IMFPluginControl


MFGetMFTMerit proto WINAPI \
		  pMFT: ptr IUnknown,
	    cbVerifier: UINT32,
	      verifier: ptr BYTE,
		 merit: ptr DWORD

endif

endif

if (WINVER GE _WIN32_WINNT_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFRegisterLocalSchemeHandler proto WINAPI \
	      szScheme: PCWSTR,
	     pActivate: ptr IMFActivate


MFRegisterLocalByteStreamHandler proto WINAPI \
       szFileExtension: PCWSTR,
	    szMimeType: PCWSTR,
	     pActivate: ptr IMFActivate


MFCreateMFByteStreamWrapper proto WINAPI \
	       pStream: IMFByteStream*,
       ppStreamWrapper: IMFByteStream**


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateMediaExtensionActivate proto WINAPI \
  szActivatableClassId: PCWSTR,
	pConfiguration: ptr IUnknown,
		  riid: REFIID,
	     ppvObject: ptr LPVOID


endif

endif ;; (WINVER GE _WIN32_WINNT_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)


DEFINE_GUID(MFT_SUPPORT_DYNAMIC_FORMAT_CHANGE, 0x53476a11, 0x3f13, 0x49fb, 0xac, 0x42, 0xee, 0x27, 0x33, 0xc9, 0x67, 0x41);
ifndef FCC
FCC macro ch4
	exitm<( (((ch4) AND 0xFF)	SHL 24) OR \
		(((ch4) AND 0xFF00)	SHL 8) OR \
		(((ch4) AND 0xFF0000)	SHR 8) OR \
		(((ch4) AND 0xFF000000) SHR 24) )>
	endm
endif


ifndef DEFINE_MEDIATYPE_GUID
DEFINE_MEDIATYPE_GUID macro name, format
	exitm<DEFINE_GUID(name, %format, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71)>
	endm

endif

ifndef DIRECT3D_VERSION
D3DFMT_R8G8B8		equ 20
D3DFMT_A8R8G8B8		equ 21
D3DFMT_X8R8G8B8		equ 22
D3DFMT_R5G6B5		equ 23
D3DFMT_X1R5G5B5		equ 24
D3DFMT_P8		equ 41
LOCAL_D3DFMT_DEFINES	equ 1
endif

DEFINE_MEDIATYPE_GUID( MFVideoFormat_Base,	0x00000000 );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_RGB32,	D3DFMT_X8R8G8B8 );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_ARGB32,	D3DFMT_A8R8G8B8 );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_RGB24,	D3DFMT_R8G8B8 );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_RGB555,	D3DFMT_X1R5G5B5 );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_RGB565,	D3DFMT_R5G6B5 );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_RGB8,	D3DFMT_P8 );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_AI44,	FCC('AI44') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_AYUV,	FCC('AYUV') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_YUY2,	FCC('YUY2') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_YVYU,	FCC('YVYU') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_YVU9,	FCC('YVU9') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_UYVY,	FCC('UYVY') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_NV11,	FCC('NV11') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_NV12,	FCC('NV12') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_YV12,	FCC('YV12') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_I420,	FCC('I420') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_IYUV,	FCC('IYUV') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_Y210,	FCC('Y210') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_Y216,	FCC('Y216') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_Y410,	FCC('Y410') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_Y416,	FCC('Y416') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_Y41P,	FCC('Y41P') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_Y41T,	FCC('Y41T') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_Y42T,	FCC('Y42T') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_P210,	FCC('P210') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_P216,	FCC('P216') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_P010,	FCC('P010') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_P016,	FCC('P016') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_v210,	FCC('v210') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_v216,	FCC('v216') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_v410,	FCC('v410') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_MP43,	FCC('MP43') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_MP4S,	FCC('MP4S') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_M4S2,	FCC('M4S2') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_MP4V,	FCC('MP4V') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_WMV1,	FCC('WMV1') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_WMV2,	FCC('WMV2') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_WMV3,	FCC('WMV3') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_WVC1,	FCC('WVC1') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_MSS1,	FCC('MSS1') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_MSS2,	FCC('MSS2') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_MPG1,	FCC('MPG1') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_DVSL,	FCC('dvsl') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_DVSD,	FCC('dvsd') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_DVHD,	FCC('dvhd') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_DV25,	FCC('dv25') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_DV50,	FCC('dv50') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_DVH1,	FCC('dvh1') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_DVC,	FCC('dvc ') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_H264,	FCC('H264') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_MJPG,	FCC('MJPG') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_420O,	FCC('420O') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_HEVC,	FCC('HEVC') );
DEFINE_MEDIATYPE_GUID( MFVideoFormat_HEVC_ES,	FCC('HEVS') );

if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_MEDIATYPE_GUID( MFVideoFormat_H263,	FCC('H263') );
endif

ifdef LOCAL_D3DFMT_DEFINES
undef D3DFMT_R8G8B8
undef D3DFMT_A8R8G8B8
undef D3DFMT_X8R8G8B8
undef D3DFMT_R5G6B5
undef D3DFMT_X1R5G5B5
undef D3DFMT_P8
undef LOCAL_D3DFMT_DEFINES
endif


DEFINE_GUID(MFVideoFormat_H264_ES, 0x3f40f4f0, 0x5622, 0x4ff8, 0xb6, 0xd8, 0xa1, 0x7a, 0x58, 0x4b, 0xee, 0x5e);
DEFINE_GUID(MFVideoFormat_MPEG2, 0xe06d8026, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x5f, 0x6c, 0xbb, 0xea);

MFVideoFormat_MPG2	equ <MFVideoFormat_MPEG2>

DEFINE_MEDIATYPE_GUID( MFAudioFormat_Base,		0x00000000 );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_PCM,		WAVE_FORMAT_PCM );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_Float,		WAVE_FORMAT_IEEE_FLOAT );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_DTS,		WAVE_FORMAT_DTS );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_Dolby_AC3_SPDIF,	WAVE_FORMAT_DOLBY_AC3_SPDIF );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_DRM,		WAVE_FORMAT_DRM );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_WMAudioV8,		WAVE_FORMAT_WMAUDIO2 );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_WMAudioV9,		WAVE_FORMAT_WMAUDIO3 );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_WMAudio_Lossless,	WAVE_FORMAT_WMAUDIO_LOSSLESS );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_WMASPDIF,		WAVE_FORMAT_WMASPDIF );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_MSP1,		WAVE_FORMAT_WMAVOICE9 );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_MP3,		WAVE_FORMAT_MPEGLAYER3 );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_MPEG,		WAVE_FORMAT_MPEG );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_AAC,		WAVE_FORMAT_MPEG_HEAAC );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_ADTS,		WAVE_FORMAT_MPEG_ADTS_AAC );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_AMR_NB,		WAVE_FORMAT_AMR_NB );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_AMR_WB,		WAVE_FORMAT_AMR_WB );
DEFINE_MEDIATYPE_GUID( MFAudioFormat_AMR_WP,		WAVE_FORMAT_AMR_WP );

DEFINE_GUID(MFAudioFormat_Dolby_AC3, 0xe06d802c, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea);
DEFINE_GUID(MFAudioFormat_Dolby_DDPlus, 0xa7fb87af, 0x2d02, 0x42fb, 0xa4, 0xd4, 0x5, 0xcd, 0x93, 0x84, 0x3b, 0xdd);
DEFINE_GUID(MFMPEG4Format_Base, 0x00000000, 0x767a, 0x494d, 0xb4, 0x78, 0xf2, 0x9d, 0x25, 0xdc, 0x90, 0x37);
DEFINE_GUID(MF_MT_MAJOR_TYPE, 0x48eba18e, 0xf8c9, 0x4687, 0xbf, 0x11, 0x0a, 0x74, 0xc9, 0xf9, 0x6a, 0x8f);
DEFINE_GUID(MF_MT_SUBTYPE, 0xf7e34c9a, 0x42e8, 0x4714, 0xb7, 0x4b, 0xcb, 0x29, 0xd7, 0x2c, 0x35, 0xe5);
DEFINE_GUID(MF_MT_ALL_SAMPLES_INDEPENDENT, 0xc9173739, 0x5e56, 0x461c, 0xb7, 0x13, 0x46, 0xfb, 0x99, 0x5c, 0xb9, 0x5f);
DEFINE_GUID(MF_MT_FIXED_SIZE_SAMPLES, 0xb8ebefaf, 0xb718, 0x4e04, 0xb0, 0xa9, 0x11, 0x67, 0x75, 0xe3, 0x32, 0x1b);
DEFINE_GUID(MF_MT_COMPRESSED, 0x3afd0cee, 0x18f2, 0x4ba5, 0xa1, 0x10, 0x8b, 0xea, 0x50, 0x2e, 0x1f, 0x92);
DEFINE_GUID(MF_MT_SAMPLE_SIZE, 0xdad3ab78, 0x1990, 0x408b, 0xbc, 0xe2, 0xeb, 0xa6, 0x73, 0xda, 0xcc, 0x10);
DEFINE_GUID(MF_MT_WRAPPED_TYPE, 0x4d3f7b23, 0xd02f, 0x4e6c, 0x9b, 0xee, 0xe4, 0xbf, 0x2c, 0x6c, 0x69, 0x5d);

if (WINVER GE _WIN32_WINNT_WIN8)

DEFINE_GUID( MF_MT_VIDEO_3D, 0xcb5e88cf, 0x7b5b, 0x476b, 0x85, 0xaa, 0x1c, 0xa5, 0xae, 0x18, 0x75, 0x55);

.enum MFVideo3DFormat {
    MFVideo3DSampleFormat_BaseView		= 0,
    MFVideo3DSampleFormat_MultiView		= 1,
    MFVideo3DSampleFormat_Packed_LeftRight	= 2,
    MFVideo3DSampleFormat_Packed_TopBottom	= 3,
    }

DEFINE_GUID(MF_MT_VIDEO_3D_FORMAT, 0x5315d8a0, 0x87c5, 0x4697, 0xb7, 0x93, 0x66, 0x6, 0xc6, 0x7c, 0x4, 0x9b);
DEFINE_GUID( MF_MT_VIDEO_3D_NUM_VIEWS, 0xbb077e8a, 0xdcbf, 0x42eb, 0xaf, 0x60, 0x41, 0x8d, 0xf9, 0x8a, 0xa4, 0x95);
DEFINE_GUID( MF_MT_VIDEO_3D_LEFT_IS_BASE, 0x6d4b7bff, 0x5629, 0x4404, 0x94, 0x8c, 0xc6, 0x34, 0xf4, 0xce, 0x26, 0xd4);
DEFINE_GUID( MF_MT_VIDEO_3D_FIRST_IS_LEFT, 0xec298493, 0xada, 0x4ea1, 0xa4, 0xfe, 0xcb, 0xbd, 0x36, 0xce, 0x93, 0x31);
DEFINE_GUID( MFSampleExtension_3DVideo, 0xf86f97a4, 0xdd54, 0x4e2e, 0x9a, 0x5e, 0x55, 0xfc, 0x2d, 0x74, 0xa0, 0x05);

.enum MFVideo3DSampleFormat {
    MFSampleExtension_3DVideo_MultiView		= 1,
    MFSampleExtension_3DVideo_Packed		= 0,
    }

DEFINE_GUID( MFSampleExtension_3DVideo_SampleFormat, 0x8671772, 0xe36f, 0x4cff, 0x97, 0xb3, 0xd7, 0x2e, 0x20, 0x98, 0x7a, 0x48);

.enum MFVideoRotationFormat {
    MFVideoRotationFormat_0	   = 0,
    MFVideoRotationFormat_90	   = 90,
    MFVideoRotationFormat_180	   = 180,
    MFVideoRotationFormat_270	   = 270,
    }

DEFINE_GUID(MF_MT_VIDEO_ROTATION, 0xc380465d, 0x2271, 0x428c, 0x9b, 0x83, 0xec, 0xea, 0x3b, 0x4a, 0x85, 0xc1);

endif ;; (WINVER GE _WIN32_WINNT_WIN8)

DEFINE_GUID(MF_MT_AUDIO_NUM_CHANNELS, 0x37e48bf5, 0x645e, 0x4c5b, 0x89, 0xde, 0xad, 0xa9, 0xe2, 0x9b, 0x69, 0x6a);
DEFINE_GUID(MF_MT_AUDIO_SAMPLES_PER_SECOND, 0x5faeeae7, 0x0290, 0x4c31, 0x9e, 0x8a, 0xc5, 0x34, 0xf6, 0x8d, 0x9d, 0xba);
DEFINE_GUID(MF_MT_AUDIO_FLOAT_SAMPLES_PER_SECOND, 0xfb3b724a, 0xcfb5, 0x4319, 0xae, 0xfe, 0x6e, 0x42, 0xb2, 0x40, 0x61, 0x32);
DEFINE_GUID(MF_MT_AUDIO_AVG_BYTES_PER_SECOND, 0x1aab75c8, 0xcfef, 0x451c, 0xab, 0x95, 0xac, 0x03, 0x4b, 0x8e, 0x17, 0x31);
DEFINE_GUID(MF_MT_AUDIO_BLOCK_ALIGNMENT, 0x322de230, 0x9eeb, 0x43bd, 0xab, 0x7a, 0xff, 0x41, 0x22, 0x51, 0x54, 0x1d);
DEFINE_GUID(MF_MT_AUDIO_BITS_PER_SAMPLE, 0xf2deb57f, 0x40fa, 0x4764, 0xaa, 0x33, 0xed, 0x4f, 0x2d, 0x1f, 0xf6, 0x69);
DEFINE_GUID(MF_MT_AUDIO_VALID_BITS_PER_SAMPLE, 0xd9bf8d6a, 0x9530, 0x4b7c, 0x9d, 0xdf, 0xff, 0x6f, 0xd5, 0x8b, 0xbd, 0x06);
DEFINE_GUID(MF_MT_AUDIO_SAMPLES_PER_BLOCK, 0xaab15aac, 0xe13a, 0x4995, 0x92, 0x22, 0x50, 0x1e, 0xa1, 0x5c, 0x68, 0x77);
DEFINE_GUID(MF_MT_AUDIO_CHANNEL_MASK, 0x55fb5765, 0x644a, 0x4caf, 0x84, 0x79, 0x93, 0x89, 0x83, 0xbb, 0x15, 0x88);

MFFOLDDOWN_MATRIX	STRUC
cbSize			UINT32 ?
cSrcChannels		UINT32 ?
cDstChannels		UINT32 ?
dwChannelMask		UINT32 ?
Coeff			LONG 64 dup(?)
MFFOLDDOWN_MATRIX	ENDS

DEFINE_GUID(MF_MT_AUDIO_FOLDDOWN_MATRIX, 0x9d62927c, 0x36be, 0x4cf2, 0xb5, 0xc4, 0xa3, 0x92, 0x6e, 0x3e, 0x87, 0x11);
DEFINE_GUID(MF_MT_AUDIO_WMADRC_PEAKREF, 0x9d62927d, 0x36be, 0x4cf2, 0xb5, 0xc4, 0xa3, 0x92, 0x6e, 0x3e, 0x87, 0x11);
DEFINE_GUID(MF_MT_AUDIO_WMADRC_PEAKTARGET, 0x9d62927e, 0x36be, 0x4cf2, 0xb5, 0xc4, 0xa3, 0x92, 0x6e, 0x3e, 0x87, 0x11);

DEFINE_GUID(MF_MT_AUDIO_WMADRC_AVGREF, 0x9d62927f, 0x36be, 0x4cf2, 0xb5, 0xc4, 0xa3, 0x92, 0x6e, 0x3e, 0x87, 0x11);
DEFINE_GUID(MF_MT_AUDIO_WMADRC_AVGTARGET, 0x9d629280, 0x36be, 0x4cf2, 0xb5, 0xc4, 0xa3, 0x92, 0x6e, 0x3e, 0x87, 0x11);

DEFINE_GUID(MF_MT_AUDIO_PREFER_WAVEFORMATEX, 0xa901aaba, 0xe037, 0x458a, 0xbd, 0xf6, 0x54, 0x5b, 0xe2, 0x07, 0x40, 0x42);

if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID(MF_MT_AAC_PAYLOAD_TYPE, 0xbfbabe79, 0x7434, 0x4d1c, 0x94, 0xf0, 0x72, 0xa3, 0xb9, 0xe1, 0x71, 0x88);
DEFINE_GUID(MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION, 0x7632f0e6, 0x9538, 0x4d61, 0xac, 0xda, 0xea, 0x29, 0xc8, 0xc1, 0x44, 0x56);
endif

DEFINE_GUID(MF_MT_FRAME_SIZE, 0x1652c33d, 0xd6b2, 0x4012, 0xb8, 0x34, 0x72, 0x03, 0x08, 0x49, 0xa3, 0x7d);
DEFINE_GUID(MF_MT_FRAME_RATE, 0xc459a2e8, 0x3d2c, 0x4e44, 0xb1, 0x32, 0xfe, 0xe5, 0x15, 0x6c, 0x7b, 0xb0);
DEFINE_GUID(MF_MT_PIXEL_ASPECT_RATIO, 0xc6376a1e, 0x8d0a, 0x4027, 0xbe, 0x45, 0x6d, 0x9a, 0x0a, 0xd3, 0x9b, 0xb6);
DEFINE_GUID(MF_MT_DRM_FLAGS, 0x8772f323, 0x355a, 0x4cc7, 0xbb, 0x78, 0x6d, 0x61, 0xa0, 0x48, 0xae, 0x82);

if (WINVER GE _WIN32_WINNT_WIN8)

DEFINE_GUID(MF_MT_TIMESTAMP_CAN_BE_DTS, 0x24974215, 0x1b7b, 0x41e4, 0x86, 0x25, 0xac, 0x46, 0x9f, 0x2d, 0xed, 0xaa);

endif

.enum MFVideoDRMFlags {
    MFVideoDRMFlag_None			= 0,
    MFVideoDRMFlag_AnalogProtected	= 1,
    MFVideoDRMFlag_DigitallyProtected	= 2,
    }


DEFINE_GUID(MF_MT_PAD_CONTROL_FLAGS, 0x4d0e73e5, 0x80ea, 0x4354, 0xa9, 0xd0, 0x11, 0x76, 0xce, 0xb0, 0x28, 0xea);

.enum MFVideoPadFlags {
    MFVideoPadFlag_PAD_TO_None	= 0,
    MFVideoPadFlag_PAD_TO_4x3	= 1,
    MFVideoPadFlag_PAD_TO_16x9	= 2
    }

DEFINE_GUID(MF_MT_SOURCE_CONTENT_HINT, 0x68aca3cc, 0x22d0, 0x44e6, 0x85, 0xf8, 0x28, 0x16, 0x71, 0x97, 0xfa, 0x38);

.enum MFVideoSrcContentHintFlags {
    MFVideoSrcContentHintFlag_None  = 0,
    MFVideoSrcContentHintFlag_16x9  = 1,
    MFVideoSrcContentHintFlag_235_1 = 2
    }

DEFINE_GUID(MF_MT_VIDEO_CHROMA_SITING, 0x65df2370, 0xc773, 0x4c33, 0xaa, 0x64, 0x84, 0x3e, 0x06, 0x8e, 0xfb, 0x0c);
DEFINE_GUID(MF_MT_INTERLACE_MODE, 0xe2724bb8, 0xe676, 0x4806, 0xb4, 0xb2, 0xa8, 0xd6, 0xef, 0xb4, 0x4c, 0xcd);
DEFINE_GUID(MF_MT_TRANSFER_FUNCTION, 0x5fb0fce9, 0xbe5c, 0x4935, 0xa8, 0x11, 0xec, 0x83, 0x8f, 0x8e, 0xed, 0x93);
DEFINE_GUID(MF_MT_VIDEO_PRIMARIES, 0xdbfbe4d7, 0x0740, 0x4ee0, 0x81, 0x92, 0x85, 0x0a, 0xb0, 0xe2, 0x19, 0x35);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

DEFINE_GUID(MF_MT_CUSTOM_VIDEO_PRIMARIES, 0x47537213, 0x8cfb, 0x4722, 0xaa, 0x34, 0xfb, 0xc9, 0xe2, 0x4d, 0x77, 0xb8);

MT_CUSTOM_VIDEO_PRIMARIES  STRUC
fRx			real4 ?
fRy			real4 ?
fGx			real4 ?
fGy			real4 ?
fBx			real4 ?
fBy			real4 ?
fWx			real4 ?
fWy			real4 ?
MT_CUSTOM_VIDEO_PRIMARIES ENDS

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DEFINE_GUID(MF_MT_YUV_MATRIX, 0x3e23d450, 0x2c75, 0x4d25, 0xa0, 0x0e, 0xb9, 0x16, 0x70, 0xd1, 0x23, 0x27);
DEFINE_GUID(MF_MT_VIDEO_LIGHTING, 0x53a0529c, 0x890b, 0x4216, 0x8b, 0xf9, 0x59, 0x93, 0x67, 0xad, 0x6d, 0x20);
DEFINE_GUID(MF_MT_VIDEO_NOMINAL_RANGE, 0xc21b8ee5, 0xb956, 0x4071, 0x8d, 0xaf, 0x32, 0x5e, 0xdf, 0x5c, 0xab, 0x11);
DEFINE_GUID(MF_MT_GEOMETRIC_APERTURE, 0x66758743, 0x7e5f, 0x400d, 0x98, 0x0a, 0xaa, 0x85, 0x96, 0xc8, 0x56, 0x96);
DEFINE_GUID(MF_MT_MINIMUM_DISPLAY_APERTURE, 0xd7388766, 0x18fe, 0x48c6, 0xa1, 0x77, 0xee, 0x89, 0x48, 0x67, 0xc8, 0xc4);
DEFINE_GUID(MF_MT_PAN_SCAN_APERTURE, 0x79614dde, 0x9187, 0x48fb, 0xb8, 0xc7, 0x4d, 0x52, 0x68, 0x9d, 0xe6, 0x49);
DEFINE_GUID(MF_MT_PAN_SCAN_ENABLED, 0x4b7f6bc3, 0x8b13, 0x40b2, 0xa9, 0x93, 0xab, 0xf6, 0x30, 0xb8, 0x20, 0x4e);
DEFINE_GUID(MF_MT_AVG_BITRATE, 0x20332624, 0xfb0d, 0x4d9e, 0xbd, 0x0d, 0xcb, 0xf6, 0x78, 0x6c, 0x10, 0x2e);
DEFINE_GUID(MF_MT_AVG_BIT_ERROR_RATE, 0x799cabd6, 0x3508, 0x4db4, 0xa3, 0xc7, 0x56, 0x9c, 0xd5, 0x33, 0xde, 0xb1);
DEFINE_GUID(MF_MT_MAX_KEYFRAME_SPACING, 0xc16eb52b, 0x73a1, 0x476f, 0x8d, 0x62, 0x83, 0x9d, 0x6a, 0x02, 0x06, 0x52);
DEFINE_GUID(MF_MT_USER_DATA, 0xb6bc765f, 0x4c3b, 0x40a4, 0xbd, 0x51, 0x25, 0x35, 0xb6, 0x6f, 0xe0, 0x9d);

DEFINE_GUID(MF_MT_DEFAULT_STRIDE, 0x644b4e48, 0x1e02, 0x4516, 0xb0, 0xeb, 0xc0, 0x1c, 0xa9, 0xd4, 0x9a, 0xc6);
DEFINE_GUID(MF_MT_PALETTE, 0x6d283f42, 0x9846, 0x4410, 0xaf, 0xd9, 0x65, 0x4d, 0x50, 0x3b, 0x1a, 0x54);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

DEFINE_GUID(MF_MT_AM_FORMAT_TYPE, 0x73d1072d, 0x1870, 0x4174, 0xa0, 0x63, 0x29, 0xff, 0x4f, 0xf6, 0xc1, 0x1e);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DEFINE_GUID(MF_MT_VIDEO_PROFILE, 0xad76a80b, 0x2d5c, 0x4e0b, 0xb3, 0x75, 0x64, 0xe5, 0x20, 0x13, 0x70, 0x36);
DEFINE_GUID(MF_MT_VIDEO_LEVEL, 0x96f66574, 0x11c5, 0x4015, 0x86, 0x66, 0xbf, 0xf5, 0x16, 0x43, 0x6d, 0xa7);

DEFINE_GUID(MF_MT_MPEG_START_TIME_CODE, 0x91f67885, 0x4333, 0x4280, 0x97, 0xcd, 0xbd, 0x5a, 0x6c, 0x03, 0xa0, 0x6e);
DEFINE_GUID(MF_MT_MPEG2_PROFILE, 0xad76a80b, 0x2d5c, 0x4e0b, 0xb3, 0x75, 0x64, 0xe5, 0x20, 0x13, 0x70, 0x36);
DEFINE_GUID(MF_MT_MPEG2_LEVEL, 0x96f66574, 0x11c5, 0x4015, 0x86, 0x66, 0xbf, 0xf5, 0x16, 0x43, 0x6d, 0xa7);
DEFINE_GUID(MF_MT_MPEG2_FLAGS, 0x31e3991d, 0xf701, 0x4b2f, 0xb4, 0x26, 0x8a, 0xe3, 0xbd, 0xa9, 0xe0, 0x4b);
DEFINE_GUID(MF_MT_MPEG_SEQUENCE_HEADER, 0x3c036de7, 0x3ad0, 0x4c9e, 0x92, 0x16, 0xee, 0x6d, 0x6a, 0xc2, 0x1c, 0xb3);
DEFINE_GUID(MF_MT_MPEG2_STANDARD, 0xa20af9e8, 0x928a, 0x4b26, 0xaa, 0xa9, 0xf0, 0x5c, 0x74, 0xca, 0xc4, 0x7c);
DEFINE_GUID(MF_MT_MPEG2_TIMECODE, 0x5229ba10, 0xe29d, 0x4f80, 0xa5, 0x9c, 0xdf, 0x4f, 0x18, 0x2, 0x7, 0xd2);
DEFINE_GUID(MF_MT_MPEG2_CONTENT_PACKET, 0x825d55e4, 0x4f12, 0x4197, 0x9e, 0xb3, 0x59, 0xb6, 0xe4, 0x71, 0xf, 0x6);

DEFINE_GUID(MF_MT_H264_MAX_CODEC_CONFIG_DELAY, 0xf5929986, 0x4c45, 0x4fbb, 0xbb, 0x49, 0x6c, 0xc5, 0x34, 0xd0, 0x5b, 0x9b);
DEFINE_GUID(MF_MT_H264_SUPPORTED_SLICE_MODES, 0xc8be1937, 0x4d64, 0x4549, 0x83, 0x43, 0xa8, 0x8, 0x6c, 0xb, 0xfd, 0xa5);
DEFINE_GUID(MF_MT_H264_SUPPORTED_SYNC_FRAME_TYPES, 0x89a52c01, 0xf282, 0x48d2, 0xb5, 0x22, 0x22, 0xe6, 0xae, 0x63, 0x31, 0x99);
DEFINE_GUID(MF_MT_H264_RESOLUTION_SCALING, 0xe3854272, 0xf715, 0x4757, 0xba, 0x90, 0x1b, 0x69, 0x6c, 0x77, 0x34, 0x57);
DEFINE_GUID(MF_MT_H264_SIMULCAST_SUPPORT, 0x9ea2d63d, 0x53f0, 0x4a34, 0xb9, 0x4e, 0x9d, 0xe4, 0x9a, 0x7, 0x8c, 0xb3);
DEFINE_GUID(MF_MT_H264_SUPPORTED_RATE_CONTROL_MODES, 0x6a8ac47e, 0x519c, 0x4f18, 0x9b, 0xb3, 0x7e, 0xea, 0xae, 0xa5, 0x59, 0x4d);
DEFINE_GUID(MF_MT_H264_MAX_MB_PER_SEC, 0x45256d30, 0x7215, 0x4576, 0x93, 0x36, 0xb0, 0xf1, 0xbc, 0xd5, 0x9b, 0xb2);
DEFINE_GUID(MF_MT_H264_SUPPORTED_USAGES, 0x60b1a998, 0xdc01, 0x40ce, 0x97, 0x36, 0xab, 0xa8, 0x45, 0xa2, 0xdb, 0xdc);
DEFINE_GUID(MF_MT_H264_CAPABILITIES, 0xbb3bd508, 0x490a, 0x11e0, 0x99, 0xe4, 0x13, 0x16, 0xdf, 0xd7, 0x20, 0x85);
DEFINE_GUID(MF_MT_H264_SVC_CAPABILITIES, 0xf8993abe, 0xd937, 0x4a8f, 0xbb, 0xca, 0x69, 0x66, 0xfe, 0x9e, 0x11, 0x52);
DEFINE_GUID(MF_MT_H264_USAGE, 0x359ce3a5, 0xaf00, 0x49ca, 0xa2, 0xf4, 0x2a, 0xc9, 0x4c, 0xa8, 0x2b, 0x61);
DEFINE_GUID(MF_MT_H264_RATE_CONTROL_MODES, 0x705177d8, 0x45cb, 0x11e0, 0xac, 0x7d, 0xb9, 0x1c, 0xe0, 0xd7, 0x20, 0x85);
DEFINE_GUID(MF_MT_H264_LAYOUT_PER_STREAM, 0x85e299b2, 0x90e3, 0x4fe8, 0xb2, 0xf5, 0xc0, 0x67, 0xe0, 0xbf, 0xe5, 0x7a);

DEFINE_GUID(MF_MT_DV_AAUX_SRC_PACK_0, 0x84bd5d88, 0x0fb8, 0x4ac8, 0xbe, 0x4b, 0xa8, 0x84, 0x8b, 0xef, 0x98, 0xf3);
DEFINE_GUID(MF_MT_DV_AAUX_CTRL_PACK_0, 0xf731004e, 0x1dd1, 0x4515, 0xaa, 0xbe, 0xf0, 0xc0, 0x6a, 0xa5, 0x36, 0xac);
DEFINE_GUID(MF_MT_DV_AAUX_SRC_PACK_1, 0x720e6544, 0x0225, 0x4003, 0xa6, 0x51, 0x01, 0x96, 0x56, 0x3a, 0x95, 0x8e);
DEFINE_GUID(MF_MT_DV_AAUX_CTRL_PACK_1, 0xcd1f470d, 0x1f04, 0x4fe0, 0xbf, 0xb9, 0xd0, 0x7a, 0xe0, 0x38, 0x6a, 0xd8);
DEFINE_GUID(MF_MT_DV_VAUX_SRC_PACK, 0x41402d9d, 0x7b57, 0x43c6, 0xb1, 0x29, 0x2c, 0xb9, 0x97, 0xf1, 0x50, 0x09);
DEFINE_GUID(MF_MT_DV_VAUX_CTRL_PACK, 0x2f84e1c4, 0x0da1, 0x4788, 0x93, 0x8e, 0x0d, 0xfb, 0xfb, 0xb3, 0x4b, 0x48);

endif

if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MT_ARBITRARY_HEADER	STRUC
majortype		GUID <>
subtype			GUID <>
bFixedSizeSamples	BOOL ?
bTemporalCompression	BOOL ?
lSampleSize		ULONG ?
formattype		GUID <>
MT_ARBITRARY_HEADER	ENDS

DEFINE_GUID(MF_MT_ARBITRARY_HEADER, 0x9e6bd6f5, 0x109, 0x4f95, 0x84, 0xac, 0x93, 0x9, 0x15, 0x3a, 0x19, 0xfc );
DEFINE_GUID(MF_MT_ARBITRARY_FORMAT, 0x5a75b249, 0xd7d, 0x49a1, 0xa1, 0xc3, 0xe0, 0xd8, 0x7f, 0xc, 0xad, 0xe5);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DEFINE_GUID(MF_MT_IMAGE_LOSS_TOLERANT, 0xed062cf4, 0xe34e, 0x4922, 0xbe, 0x99, 0x93, 0x40, 0x32, 0x13, 0x3d, 0x7c);

DEFINE_GUID(MF_MT_MPEG4_SAMPLE_DESCRIPTION, 0x261e9d83, 0x9529, 0x4b8f, 0xa1, 0x11, 0x8b, 0x9c, 0x95, 0x0a, 0x81, 0xa9);
DEFINE_GUID(MF_MT_MPEG4_CURRENT_SAMPLE_ENTRY, 0x9aa7e155, 0xb64a, 0x4c1d, 0xa5, 0x00, 0x45, 0x5d, 0x60, 0x0b, 0x65, 0x60);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

DEFINE_GUID(MF_MT_ORIGINAL_4CC, 0xd7be3fe0, 0x2bc7, 0x492d, 0xb8, 0x43, 0x61, 0xa1, 0x91, 0x9b, 0x70, 0xc3);
DEFINE_GUID(MF_MT_ORIGINAL_WAVE_FORMAT_TAG, 0x8cbbc843, 0x9fd9, 0x49c2, 0x88, 0x2f, 0xa7, 0x25, 0x86, 0xc4, 0x08, 0xad);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DEFINE_GUID(MF_MT_FRAME_RATE_RANGE_MIN, 0xd2e7558c, 0xdc1f, 0x403f, 0x9a, 0x72, 0xd2, 0x8b, 0xb1, 0xeb, 0x3b, 0x5e);
DEFINE_GUID(MF_MT_FRAME_RATE_RANGE_MAX, 0xe3371d41, 0xb4cf, 0x4a05, 0xbd, 0x4e, 0x20, 0xb8, 0x8b, 0xb2, 0xc4, 0xd6);

endif

endif ;; (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_GUID(MF_LOW_LATENCY, 0x9c27891a, 0xed7a, 0x40e1, 0x88, 0xe8, 0xb2, 0x27, 0x27, 0xa0, 0x24, 0xee);
DEFINE_GUID(MF_VIDEO_MAX_MB_PER_SEC, 0xe3f2e203, 0xd445, 0x4b8c, 0x92, 0x11, 0xae, 0x39, 0xd, 0x3b, 0xa0, 0x17);
endif

DEFINE_GUID(MFMediaType_Default, 0x81A412E6, 0x8103, 0x4B06, 0x85, 0x7F, 0x18, 0x62, 0x78, 0x10, 0x24, 0xAC);
DEFINE_GUID(MFMediaType_Audio, 0x73647561, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
DEFINE_GUID(MFMediaType_Video, 0x73646976, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
DEFINE_GUID(MFMediaType_Protected, 0x7b4b6fe6, 0x9d04, 0x4494, 0xbe, 0x14, 0x7e, 0x0b, 0xd0, 0x76, 0xc8, 0xe4);
DEFINE_GUID(MFMediaType_SAMI, 0xe69669a0, 0x3dcd, 0x40cb, 0x9e, 0x2e, 0x37, 0x08, 0x38, 0x7c, 0x06, 0x16);
DEFINE_GUID(MFMediaType_Script, 0x72178C22, 0xE45B, 0x11D5, 0xBC, 0x2A, 0x00, 0xB0, 0xD0, 0xF3, 0xF4, 0xAB);
DEFINE_GUID(MFMediaType_Image, 0x72178C23, 0xE45B, 0x11D5, 0xBC, 0x2A, 0x00, 0xB0, 0xD0, 0xF3, 0xF4, 0xAB);
DEFINE_GUID(MFMediaType_HTML, 0x72178C24, 0xE45B, 0x11D5, 0xBC, 0x2A, 0x00, 0xB0, 0xD0, 0xF3, 0xF4, 0xAB);
DEFINE_GUID(MFMediaType_Binary, 0x72178C25, 0xE45B, 0x11D5, 0xBC, 0x2A, 0x00, 0xB0, 0xD0, 0xF3, 0xF4, 0xAB);
DEFINE_GUID(MFMediaType_FileTransfer, 0x72178C26, 0xE45B, 0x11D5, 0xBC, 0x2A, 0x00, 0xB0, 0xD0, 0xF3, 0xF4, 0xAB);
DEFINE_GUID(MFMediaType_Stream, 0xe436eb83, 0x524f, 0x11ce, 0x9f, 0x53, 0x00, 0x20, 0xaf, 0x0b, 0xa7, 0x70);

DEFINE_GUID(MFImageFormat_JPEG, 0x19e4a5aa, 0x5662, 0x4fc5, 0xa0, 0xc0, 0x17, 0x58, 0x02, 0x8e, 0x10, 0x57);
DEFINE_GUID(MFImageFormat_RGB32, 0x00000016, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

DEFINE_GUID(MFStreamFormat_MPEG2Transport, 0xe06d8023, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x5f, 0x6c, 0xbb, 0xea);
DEFINE_GUID(MFStreamFormat_MPEG2Program, 0x263067d1, 0xd330, 0x45dc, 0xb6, 0x69, 0x34, 0xd9, 0x86, 0xe4, 0xe3, 0xe1);

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
DEFINE_GUID(AM_MEDIA_TYPE_REPRESENTATION, 0xe2e42ad2, 0x132c, 0x491e, 0xa2, 0x68, 0x3c, 0x7c, 0x2d, 0xca, 0x18, 0x1f);
DEFINE_GUID(FORMAT_MFVideoFormat, 0xaed4ab2d, 0x7326, 0x43cb, 0x94, 0x64, 0xc8, 0x79, 0xca, 0xb9, 0xc4, 0x3d);


MFValidateMediaTypeSize proto WINAPI \
	    FormatType: ptr GUID,
		pBlock: ptr UINT8,
		cbSize: UINT32


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateMediaType proto WINAPI \
	      ppMFType: ptr ptr IMFMediaType


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCreateMFVideoFormatFromMFMediaType proto WINAPI \
	       pMFType: ptr IMFMediaType,
		ppMFVF: ptr ptr MFVIDEOFORMAT,
	       pcbSize: ptr UINT32


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MFWaveFormatExConvertFlags {
    MFWaveFormatExConvertFlag_Normal		= 0,
    MFWaveFormatExConvertFlag_ForceExtensible	= 1
    }
endif

ifdef __cplusplus

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateWaveFormatExFromMFMediaType proto WINAPI \
	       pMFType: ptr IMFMediaType,
		  ppWF: ptr ptr WAVEFORMATEX,
	       pcbSize: ptr UINT32,
		      : UINT32

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFInitMediaTypeFromVideoInfoHeader proto WINAPI \
	       pMFType: ptr IMFMediaType,
		  pVIH: ptr VIDEOINFOHEADER,
	     cbBufSize: UINT32,
	      pSubtype: ptr GUID

MFInitMediaTypeFromVideoInfoHeader2 proto WINAPI \
	       pMFType: ptr IMFMediaType,
		 pVIH2: ptr VIDEOINFOHEADER2,
	     cbBufSize: UINT32,
	     pSubtypeL: ptr GUID

MFInitMediaTypeFromMPEG1VideoInfo proto WINAPI \
	       pMFType: ptr IMFMediaType,
		pMP1VI: ptr MPEG1VIDEOINFO,
	     cbBufSize: UINT32,
	      pSubtype: ptr GUID


MFInitMediaTypeFromMPEG2VideoInfo proto WINAPI \
	       pMFType: ptr IMFMediaType,
		pMP1VI: ptr MPEG1VIDEOINFO,
	     cbBufSize: UINT32,
	      pSubtype: ptr GUID


MFCalculateBitmapImageSize proto WINAPI \
		 pBMIH: ptr BITMAPINFOHEADER,
	     cbBufSize: UINT32,
	  pcbImageSize: ptr UINT32,
	       pbKnown: ptr BOOL

endif


else ;; cplusplus

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreateWaveFormatExFromMFMediaType proto WINAPI \
	       pMFType: ptr IMFMediaType,
		  ppWF: ptr ptr WAVEFORMATEX,
	       pcbSize: ptr UINT32,
		 Flags: UINT32

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFInitMediaTypeFromVideoInfoHeader proto WINAPI \
	       pMFType: ptr IMFMediaType,
		  pVIH: ptr VIDEOINFOHEADER,
	     cbBufSize: UINT32,
	      pSubtype: ptr GUID

MFInitMediaTypeFromVideoInfoHeader2 proto WINAPI \
	       pMFType: ptr IMFMediaType,
		 pVIH2: ptr VIDEOINFOHEADER2,
	     cbBufSize: UINT32,
	     pSubtypeL: ptr GUID

MFInitMediaTypeFromMPEG1VideoInfo proto WINAPI \
	       pMFType: ptr IMFMediaType,
		pMP1VI: ptr MPEG1VIDEOINFO,
	     cbBufSize: UINT32,
	      pSubtype: ptr GUID


MFInitMediaTypeFromMPEG2VideoInfo proto WINAPI \
	       pMFType: ptr IMFMediaType,
		pMP1VI: ptr MPEG1VIDEOINFO,
	     cbBufSize: UINT32,
	      pSubtype: ptr GUID


MFCalculateBitmapImageSize proto WINAPI \
		 pBMIH: ptr BITMAPINFOHEADER,
	     cbBufSize: UINT32,
	  pcbImageSize: ptr UINT32,
	       pbKnown: ptr BOOL

endif


endif ;; cplusplus

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFCalculateImageSize proto WINAPI \
	   guidSubtype: REFGUID,
	       unWidth: UINT32,
	      unHeight: UINT32,
	  pcbImageSize: ptr UINT32

MFFrameRateToAverageTimePerFrame proto WINAPI \
	   unNumerator: UINT32,
	 unDenominator: UINT32,
punAverageTimePerFrame: ptr UINT64

MFAverageTimePerFrameToFrameRate proto WINAPI \
 unAverageTimePerFrame: UINT64,
	  punNumerator: ptr UINT32,
	punDenominator: ptr UINT32


MFInitMediaTypeFromMFVideoFormat proto WINAPI \
	       pMFType: ptr IMFMediaType,
		 pMFVF: ptr MFVIDEOFORMAT,
	     cbBufSize: UINT32

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFInitMediaTypeFromWaveFormatEx proto WINAPI \
	       pMFType: ptr IMFMediaType,
	   pWaveFormat: ptr WAVEFORMATEX,
	     cbBufSize: UINT32

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFInitMediaTypeFromAMMediaType proto WINAPI \
	       pMFType: ptr IMFMediaType,
	       pAMType: ptr AM_MEDIA_TYPE

MFInitAMMediaTypeFromMFMediaType proto WINAPI \
	       pMFType: ptr IMFMediaType,
   guidFormatBlockType: ptr GUID,
	       pAMType: ptr AM_MEDIA_TYPE

MFCreateAMMediaTypeFromMFMediaType proto WINAPI \
	       pMFType: ptr IMFMediaType,
   guidFormatBlockType: ptr GUID,
	      ppAMType: ptr ptr AM_MEDIA_TYPE

MFCompareFullToPartialMediaType proto WINAPI \
	   pMFTypeFull: ptr IMFMediaType,
	pMFTypePartial: ptr IMFMediaType

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFWrapMediaType proto WINAPI \
		 pOrig: ptr IMFMediaType,
	     MajorType: REFGUID,
	       SubType: REFGUID,
		ppWrap: ptr IMFMediaType

MFUnwrapMediaType proto WINAPI \
		 pWrap: ptr IMFMediaType,
		ppOrig: ptr IMFMediaType


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifdef _KSMEDIA_

MFCreateVideoMediaTypeFromVideoInfoHeader proto WINAPI \
      pVideoInfoHeader: ptr KS_VIDEOINFOHEADER,
     cbVideoInfoHeader: DWORD,
   dwPixelAspectRatioX: DWORD,
   dwPixelAspectRatioY: DWORD,
	 InterlaceMode: MFVideoInterlaceMode,
	    VideoFlags: QWORD,
	      pSubtype: ptr GUID,
     ppIVideoMediaType: ptr ptr IMFVideoMediaType


;STDAPI
MFCreateVideoMediaTypeFromVideoInfoHeader2 proto WINAPI \
      pVideoInfoHeader: ptr KS_VIDEOINFOHEADER2,
     cbVideoInfoHeader: DWORD,
  AdditionalVideoFlags: QWORD,
	      pSubtype: ptr GUID,
     ppIVideoMediaType: ptr ptr IMFVideoMediaType


endif


MFCreateVideoMediaType proto WINAPI \
	  pVideoFormat: ptr MFVIDEOFORMAT,
     ppIVideoMediaType: ptr ptr IMFVideoMediaType

MFCreateVideoMediaTypeFromSubtype proto WINAPI \
	    pAMSubtype: ptr GUID,
     ppIVideoMediaType: ptr IMFVideoMediaType

MFIsFormatYUV proto WINAPI \
		Format: DWORD


MFCreateVideoMediaTypeFromBitMapInfoHeader proto WINAPI \
 pbmihBitMapInfoHeader: ptr BITMAPINFOHEADER,
   dwPixelAspectRatioX: DWORD,
   dwPixelAspectRatioY: DWORD,
	 InterlaceMode: MFVideoInterlaceMode,
	    VideoFlags: QWORD,
qwFramesPerSecondNumerator: QWORD,
qwFramesPerSecondDenominator: QWORD,
	  dwMaxBitRate: DWORD,
     ppIVideoMediaType: ptr ptr IMFVideoMediaType

MFGetStrideForBitmapInfoHeader proto WINAPI \
		format: DWORD,
	       dwWidth: DWORD,
	       pStride: ptr LONG

MFGetPlaneSize proto WINAPI \
		format: DWORD,
	       dwWidth: DWORD,
	      dwHeight: DWORD,
	  pdwPlaneSize: ptr DWORD


if (WINVER GE _WIN32_WINNT_WIN7)

MFCreateVideoMediaTypeFromBitMapInfoHeaderEx proto WINAPI \
 pbmihBitMapInfoHeader: ptr BITMAPINFOHEADER,
    cbBitMapInfoHeader: UINT32,
   dwPixelAspectRatioX: DWORD,
   dwPixelAspectRatioY: DWORD,
	 InterlaceMode: MFVideoInterlaceMode,
	    VideoFlags: QWORD,
dwFramesPerSecondNumerator: DWORD,
dwFramesPerSecondDenominator: DWORD,
	  dwMaxBitRate: DWORD,
     ppIVideoMediaType: ptr ptr IMFVideoMediaType

endif

MFCreateMediaTypeFromRepresentation proto WINAPI \
    guidRepresentation: ptr GUID,
      pvRepresentation: LPVOID,
	  ppIMediaType: ptr ptr IMFMediaType

MFCreateAudioMediaType proto WINAPI \
	  pAudioFormat: ptr WAVEFORMATEX,
     ppIAudioMediaType: ptr ptr IMFAudioMediaType


MFGetUncompressedVideoFormat proto WINAPI \
	  pVideoFormat: ptr MFVIDEOFORMAT

MFInitVideoFormat proto WINAPI \
	  pVideoFormat: ptr MFVIDEOFORMAT,
		  type: MFStandardVideoFormat

MFInitVideoFormat_RGB proto WINAPI \
	  pVideoFormat: ptr MFVIDEOFORMAT,
	       dwWidth: DWORD,
	      dwHeight: DWORD,
		D3Dfmt: DWORD

MFConvertColorInfoToDXVA proto WINAPI \
	     pdwToDXVA: ptr DWORD,
	   pFromFormat: ptr MFVIDEOFORMAT

MFConvertColorInfoFromDXVA proto WINAPI \
	     pToFormat: ptr MFVIDEOFORMAT,
	    dwFromDXVA: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCopyImage proto WINAPI \
		 pDest: ptr BYTE,
	   lDestStride: LONG,
		  pSrc: ptr BYTE,
	    lSrcStride: LONG,
	dwWidthInBytes: DWORD,
	       dwLines: DWORD

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFConvertFromFP16Array proto WINAPI \
		 pDest: ptr real4,
		  pSrc: ptr WORD,
	       dwCount: DWORD

MFConvertToFP16Array proto WINAPI \
		 pDest: ptr WORD,
		  pSrc: ptr real4,
	       dwCount: DWORD


endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFCreate2DMediaBuffer proto WINAPI \
	       dwWidth: DWORD,
	      dwHeight: DWORD,
	      dwFourCC: DWORD,
	     fBottomUp: BOOL,
	      ppBuffer: ptr ptr IMFMediaBuffer

MFCreateMediaBufferFromMediaType proto WINAPI \
	    pMediaType: ptr IMFMediaType,
	    llDuration: LONGLONG,
	   dwMinLength: DWORD,
	dwMinAlignment: DWORD,
	      ppBuffer: ptr ptr IMFMediaBuffer


endif

ifdef _WIN64;__cplusplus

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

HI32 proto fastcall :UINT64 {
    mov rax,rcx
    shr rax,32
    }
LO32 proto fastcall :UINT64 {
    mov eax,ecx
    }
Pack2UINT32AsUINT64 proto fastcall :UINT32, unLow:UINT32 {
    mov eax,ecx
    shl rax,32
    or	rax,rdx
    }
Unpack2UINT32AsUINT64 proto fastcall unPacked:UINT64,
	punHigh:ptr UINT32, punLow:ptr UINT32 {
    HI32(rcx)
    mov [rdx],eax
    mov [r8],ecx
    }
PackSize proto fastcall unWidth:UINT32, unHeight:UINT32 {
    Pack2UINT32AsUINT64(ecx, edx)
    }
UnpackSize proto fastcall unPacked:UINT64,
	punWidth:ptr UINT32, punHeight:ptr UINT32 {
    Unpack2UINT32AsUINT64(rcx, rdx, r8)
    }
PackRatio proto fastcall nNumerator:INT32, unDenominator:INT32 {
    Pack2UINT32AsUINT64(ecx, edx)
    }
UnpackRatio proto fastcall unPacked:UINT64,
	pnNumerator:ptr INT32, punDenominator:ptr INT32 {
    Unpack2UINT32AsUINT64(rcx, rdx, r8)
    }

MFGetAttributeUINT32 proto fastcall pAttributes:ptr IMFAttributes,
	guidKey:REFGUID, unDefault:UINT32 {

   .new unRet:UINT32
   .new unDefault:UINT32

    mov unDefault,r8d
    [rcx].IMFAttributes.GetUINT32(rdx, &unRet)
    .if (FAILED(eax))
	mov eax,unDefault
    .else
	mov eax,unRet
    .endif
    }


MFGetAttributeUINT64 proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
	     unDefault: UINT64 {

   .new unRet:UINT64
   .new unDefault:UINT64

    mov unDefault,r8
    [rcx].IMFAttributes.GetUINT64(rdx, &unRet)
    .if (FAILED(eax))
	mov rax,unDefault
    .else
	mov rax,unRet
    .endif
    }

MFGetAttributeDouble proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
	      fDefault: real8 {

   .new fRet:real8
   .new fDefault:real8

    movsd unDefault,xmm2
    [rcx].IMFAttributes.GetDouble(rdx, &fRet)
    movsd xmm0,fRet
    .if (FAILED(eax))
	movsd xmm0,fDefault
    .endif
    }


MFGetAttribute2UINT32asUINT64 proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
	     punHigh32: ptr UINT32,
	      punLow32: ptr UINT32 {

   .new unPacked:UINT64
   .new punLow32:ptr UINT32
   .new punHigh32:ptr UINT32

    mov punHigh32,r8
    mov punLow32,r9

    [rcx].IMFAttributes.GetUINT64(rdx, &unPacked)
    .if !(FAILED(eax))
	Unpack2UINT32AsUINT64(unPacked, punHigh32, punLow32)
    .endif
    }

MFSetAttribute2UINT32asUINT64 proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
	      unHigh32: UINT32,
	       unLow32: UINT32 {

    shl r8,32 ; Pack2UINT32AsUINT64(r8, r9)
    or	r8,r9
    [rcx].IMFAttributes.SetUINT64(rdx, r8)
    }


MFGetAttributeRatio proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
	  punNumerator: ptr UINT32,
	punDenominator: ptr UINT32 {
    MFGetAttribute2UINT32asUINT64(rcx, rdx, r8, r9)
    }


MFGetAttributeSize proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
	      punWidth: ptr UINT32,
	     punHeight: ptr UINT32 {
    MFGetAttribute2UINT32asUINT64(rcx, rdx, r8, r9)
    }

MFSetAttributeRatio proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
	   unNumerator: UINT32,
	 unDenominator: UINT32 {
    MFSetAttribute2UINT32asUINT64(rcx, rdx, r8, r9)
    }

MFSetAttributeSize proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
	       unWidth: UINT32,
	      unHeight: UINT32 {
    MFSetAttribute2UINT32asUINT64(rcx, rdx, r8, r9)
    }

ifdef _INTSAFE_H_INCLUDED_

MFGetAttributeString proto fastcall \
	   pAttributes: ptr IMFAttributes,
	       guidKey: REFGUID,
		  ppsz: ptr PWSTR {

   .new length:UINT32
   .new psz:PWSTR
   .new guidKey:REFGUID
   .new ppsz:ptr PWSTR
   .new pAttributes:ptr IMFAttributes

    mov pAttributes,rcx
    mov guidKey,rdx
    mov ppsz,r8
    xor eax,eax
    mov psz,rax
    mov [r8],rax

   .new hr:HRESULT
    mov hr,[rcx].pAttributes.GetStringLength(rdx, &length)
    ;; add NULL to length

    .if (SUCCEEDED(hr)) {
	mov hr,UIntAdd(length, 1, &length)
    .endif
    .if (SUCCEEDED(hr))
       .new cb:size_t
	mov hr,SizeTMult(length, sizeof(WCHAR), &cb)
	.if( SUCCEEDED( hr ) )

	    mov psz,PWSTR( CoTaskMemAlloc( cb ) )
	    .if( !psz )

		mov hr,E_OUTOFMEMORY
	    .endif
	.endif
    .endif
    .if (SUCCEEDED(hr))
	mov hr,pAttributes.GetString(guidKey, psz, length, &length)
    .endif
    .if (SUCCEEDED(hr)) {
	mov rcx,ppsz
	mov rax,psz
	mov [rcx],rax
    .else
	CoTaskMemFree(psz)
    .endif
    mov eax,hr
    }

endif ;; _INTSAFE_H_INCLUDED_

MFCreateCollection proto WINAPI \
       ppIMFCollection: ptr IMFCollection

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum EAllocationType {
    eAllocationTypeDynamic,
    eAllocationTypeRT,
    eAllocationTypePageable,
    eAllocationTypeIgnore
    }

MFHeapAlloc proto WINAPI \
		 nSize: size_t,
	       dwFlags: ULONG,
	       pszFile: string_t,
		  line: int_t,
		   eat: EAllocationType

MFHeapFree proto WINAPI pv:ptr

DEFINE_GUID(CLSID_MFSourceResolver, 0x90eab60f, 0xe43a, 0x4188, 0xbc, 0xc4, 0xe4, 0x7f, 0xdf, 0x04, 0x86, 0x8c)

endif

if (WINVER GE _WIN32_WINNT_WIN7)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFllMulDiv proto WINAPI \
		     a: LONGLONG,
		     b: LONGLONG,
		     c: LONGLONG,
		     d: LONGLONG


endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFGetContentProtectionSystemCLSID proto WINAPI \
guidProtectionSystemID: REFGUID,
		pclsid: ptr CLSID


endif

