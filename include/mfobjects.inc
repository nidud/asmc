ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __mfobjects_h__
define __mfobjects_h__

ifndef __unknwn_h__
include unknwn.inc
endif
include propsys.inc
include mediaobj.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif
include mmreg.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
.enum MF_ATTRIBUTE_TYPE {
    MF_ATTRIBUTE_UINT32 = VT_UI4,
    MF_ATTRIBUTE_UINT64 = VT_UI8,
    MF_ATTRIBUTE_DOUBLE = VT_R8,
    MF_ATTRIBUTE_GUID	= VT_CLSID,
    MF_ATTRIBUTE_STRING = VT_LPWSTR,
    MF_ATTRIBUTE_BLOB	= ( VT_VECTOR or VT_UI1 ) ,
    MF_ATTRIBUTE_IUNKNOWN = VT_UNKNOWN
    }

.enum MF_ATTRIBUTES_MATCH_TYPE {
    MF_ATTRIBUTES_MATCH_OUR_ITEMS,
    MF_ATTRIBUTES_MATCH_THEIR_ITEMS,
    MF_ATTRIBUTES_MATCH_ALL_ITEMS,
    MF_ATTRIBUTES_MATCH_INTERSECTION,
    MF_ATTRIBUTES_MATCH_SMALLER
    }

ifndef __IMFAttributes_INTERFACE_DEFINED__
define __IMFAttributes_INTERFACE_DEFINED__

DEFINE_IIDX(IMFAttributes, "2cd2d921-c447-44a7-a13c-4adabfc247e3")

.comdef IMFAttributes : public IUnknown

    GetItem		proc :REFGUID, :ptr
    GetItemType		proc :REFGUID, :ptr
    CompareItem		proc :REFGUID, :REFPROPVARIANT, :ptr
    Compare		proc :ptr, :MF_ATTRIBUTES_MATCH_TYPE, :ptr
    GetUINT32		proc :REFGUID, :ptr
    GetUINT64		proc :REFGUID, :ptr
    GetDouble		proc :REFGUID, :ptr
    GetGUID		proc :REFGUID, :ptr
    GetStringLength	proc :REFGUID, :ptr
    GetString		proc :REFGUID, :LPWSTR, :UINT32, :ptr
    GetAllocatedString	proc :REFGUID, :ptr, :ptr
    GetBlobSize		proc :REFGUID, :ptr
    GetBlob		proc :REFGUID, :ptr, :UINT32, :ptr
    GetAllocatedBlob	proc :REFGUID, :ptr, :ptr
    GetUnknown		proc :REFGUID, :REFIID, :ptr
    SetItem		proc :REFGUID, :REFPROPVARIANT
    DeleteItem		proc :REFGUID
    DeleteAllItems	proc
    SetUINT32		proc :REFGUID, :UINT32
    SetUINT64		proc :REFGUID, :UINT64
    SetDouble		proc :REFGUID, :real8
    SetGUID		proc :REFGUID, :REFGUID
    SetString		proc :REFGUID, :LPCWSTR
    SetBlob		proc :REFGUID, :ptr, :UINT32
    SetUnknown		proc :REFGUID, :ptr
    LockStore		proc
    UnlockStore		proc
    GetCount		proc :ptr
    GetItemByIndex	proc :UINT32, :ptr, :ptr
    CopyAllItems	proc :ptr
   .ends

endif

.enum MF_ATTRIBUTE_SERIALIZE_OPTIONS {
    MF_ATTRIBUTE_SERIALIZE_UNKNOWN_BYREF = 0x1
    }

MFSerializeAttributesToStream proto __cdecl :ptr, :DWORD, :ptr
MFDeserializeAttributesFromStream proto __cdecl :ptr, :DWORD, :ptr

ifndef __IMFMediaBuffer_INTERFACE_DEFINED__
define __IMFMediaBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IMFMediaBuffer, "045FA593-8799-42b8-BC8D-8968C6453507")

.comdef IMFMediaBuffer : public IUnknown

    _Lock		proc :ptr, :ptr, :ptr
    Unlock		proc
    GetCurrentLength	proc :ptr
    SetCurrentLength	proc :DWORD
    GetMaxLength	proc :ptr
   .ends

endif

ifndef __IMFSample_INTERFACE_DEFINED__
define __IMFSample_INTERFACE_DEFINED__

DEFINE_IIDX(IMFSample, "c40a00f2-b93a-4d80-ae8c-5a1c634f58e4")

.comdef IMFSample : public IMFAttributes

    GetSampleFlags	proc :ptr
    SetSampleFlags	proc :DWORD
    GetSampleTime	proc :ptr
    SetSampleTime	proc :LONGLONG
    GetSampleDuration	proc :ptr
    SetSampleDuration	proc :LONGLONG
    GetBufferCount	proc :ptr
    GetBufferByIndex	proc :DWORD, :ptr
    ConvertToContiguousBuffer proc :ptr
    AddBuffer		proc :ptr
    RemoveBufferByIndex proc :DWORD
    RemoveAllBuffers	proc
    GetTotalLength	proc :ptr
    CopyToBuffer	proc :ptr
   .ends

endif

ifndef __IMF2DBuffer_INTERFACE_DEFINED__
define __IMF2DBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IMF2DBuffer, "7DC9D5F9-9ED9-44ec-9BBF-0600BB589FBB")

.comdef IMF2DBuffer : public IUnknown

    Lock2D		proc
    Unlock2D		proc
    GetScanline0AndPitch proc :ptr, :ptr
    IsContiguousFormat	proc :ptr
    GetContiguousLength proc :ptr
    ContiguousCopyTo	proc :ptr, :DWORD
    ContiguousCopyFrom	proc :ptr, :DWORD
   .ends

endif

.enum MF2DBuffer_LockFlags {
    MF2DBuffer_LockFlags_LockTypeMask	= ( ( 0x1 or 0x2 ) or 0x3 ),
    MF2DBuffer_LockFlags_Read		= 0x1,
    MF2DBuffer_LockFlags_Write		= 0x2,
    MF2DBuffer_LockFlags_ReadWrite	= 0x3,
    MF2DBuffer_LockFlags_ForceDWORD	= 0x7fffffff
    }

ifndef __IMF2DBuffer2_INTERFACE_DEFINED__
define __IMF2DBuffer2_INTERFACE_DEFINED__

DEFINE_IIDX(IMF2DBuffer2, "33ae5ea6-4316-436f-8ddd-d73d22f829ec")

.comdef IMF2DBuffer2 : public IMF2DBuffer

    Lock2DSize		proc :MF2DBuffer_LockFlags, :ptr, :ptr
    Copy2DTo		proc :ptr
   .ends

endif

ifndef __IMFDXGIBuffer_INTERFACE_DEFINED__
define __IMFDXGIBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IMFDXGIBuffer, "e7174cfa-1c9e-48b1-8866-626226bfc258")

.comdef IMFDXGIBuffer : public IUnknown

    GetResource		proc :REFIID, :ptr
    GetSubresourceIndex proc :ptr
    GetUnknown		proc :REFIID, :REFIID, :ptr
    SetUnknown		proc :REFIID, :ptr
   .ends

endif

ifndef __IMFMediaType_INTERFACE_DEFINED__
define __IMFMediaType_INTERFACE_DEFINED__

DEFINE_IIDX(IMFMediaType, "44ae0fa8-ea31-4109-8d2e-4cae4997c555")

.comdef IMFMediaType : public IMFAttributes

    GetMajorType	proc :ptr
    IsCompressedFormat	proc :ptr
    IsEqual		proc :ptr, :ptr
    GetRepresentation	proc :ptr, :ptr
    FreeRepresentation	proc :ptr, :ptr
   .ends

endif

MF_MEDIATYPE_EQUAL_MAJOR_TYPES equ 0x00000001
MF_MEDIATYPE_EQUAL_FORMAT_TYPES equ 0x00000002
MF_MEDIATYPE_EQUAL_FORMAT_DATA equ 0x00000004
MF_MEDIATYPE_EQUAL_FORMAT_USER_DATA equ 0x00000008

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFAudioMediaType_INTERFACE_DEFINED__
define __IMFAudioMediaType_INTERFACE_DEFINED__

DEFINE_IIDX(IMFAudioMediaType, "26a0adc3-ce26-4672-9304-69552edd3faf")

.comdef IMFAudioMediaType : public IMFMediaType

    GetAudioFormat	proc
   .ends

endif

ifndef _WINGDI_
RGBQUAD			typedef DWORD

BITMAPINFOHEADER	STRUC
biSize			DWORD ?
biWidth			LONG ?
biHeight		LONG ?
biPlanes		dw ?
biBitCount		dw ?
biCompression		dd ?
biSizeImage		dd ?
biXPelsPerMeter		LONG ?
biYPelsPerMeter		LONG ?
biClrUsed		dd ?
biClrImportant		dd ?
BITMAPINFOHEADER	ENDS

BITMAPINFO		STRUC
bmiHeader		BITMAPINFOHEADER <>
bmiColors		RGBQUAD	 1  dup(?)
BITMAPINFO		ENDS

endif

MFT_REGISTER_TYPE_INFO	STRUC
guidMajorType		GUID <>
guidSubtype		GUID <>
MFT_REGISTER_TYPE_INFO	ENDS

endif

if NOT defined( _MFVIDEOFORMAT_ )

_MFVIDEOFORMAT_ equ 1

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MFVideoInterlaceMode {
    MFVideoInterlace_Unknown,
    MFVideoInterlace_Progressive,
    MFVideoInterlace_FieldInterleavedUpperFirst,
    MFVideoInterlace_FieldInterleavedLowerFirst,
    MFVideoInterlace_FieldSingleUpper,
    MFVideoInterlace_FieldSingleLower,
    MFVideoInterlace_MixedInterlaceOrProgressive,
    MFVideoInterlace_Last,
    MFVideoInterlace_ForceDWORD = 0x7fffffff
    }

MFVideoInterlace_FieldSingleUpperFirst equ MFVideoInterlace_FieldSingleUpper
MFVideoInterlace_FieldSingleLowerFirst equ MFVideoInterlace_FieldSingleLower

.enum MFVideoTransferFunction {
    MFVideoTransFunc_Unknown,
    MFVideoTransFunc_10,
    MFVideoTransFunc_18,
    MFVideoTransFunc_20,
    MFVideoTransFunc_22,
    MFVideoTransFunc_709,
    MFVideoTransFunc_240M,
    MFVideoTransFunc_sRGB,
    MFVideoTransFunc_28,
    MFVideoTransFunc_Log_100,
    MFVideoTransFunc_Log_316,
    MFVideoTransFunc_709_sym,
    MFVideoTransFunc_Last,
    MFVideoTransFunc_ForceDWORD = 0x7fffffff
    }

.enum MFVideoPrimaries {
    MFVideoPrimaries_Unknown,
    MFVideoPrimaries_reserved,
    MFVideoPrimaries_BT709,
    MFVideoPrimaries_BT470_2_SysM,
    MFVideoPrimaries_BT470_2_SysBG,
    MFVideoPrimaries_SMPTE170M,
    MFVideoPrimaries_SMPTE240M,
    MFVideoPrimaries_EBU3213,
    MFVideoPrimaries_SMPTE_C,
    MFVideoPrimaries_Last,
    MFVideoPrimaries_ForceDWORD = 0x7fffffff
    }

.enum MFVideoLighting {
    MFVideoLighting_Unknown,
    MFVideoLighting_bright,
    MFVideoLighting_office,
    MFVideoLighting_dim,
    MFVideoLighting_dark,
    MFVideoLighting_Last,
    MFVideoLighting_ForceDWORD	= 0x7fffffff
    }

.enum MFVideoTransferMatrix {
    MFVideoTransferMatrix_Unknown,
    MFVideoTransferMatrix_BT709,
    MFVideoTransferMatrix_BT601,
    MFVideoTransferMatrix_SMPTE240M,
    MFVideoTransferMatrix_Last,
    MFVideoTransferMatrix_ForceDWORD = 0x7fffffff
    }

.enum MFVideoChromaSubsampling {
    MFVideoChromaSubsampling_Unknown,
    MFVideoChromaSubsampling_ProgressiveChroma	= 0x8,
    MFVideoChromaSubsampling_Horizontally_Cosited = 0x4,
    MFVideoChromaSubsampling_Vertically_Cosited = 0x2,
    MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes = 0x1,
    MFVideoChromaSubsampling_MPEG2	= ( MFVideoChromaSubsampling_Horizontally_Cosited or MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes ) ,
    MFVideoChromaSubsampling_MPEG1	= MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes,
    MFVideoChromaSubsampling_DV_PAL	= ( MFVideoChromaSubsampling_Horizontally_Cosited or MFVideoChromaSubsampling_Vertically_Cosited ) ,
    MFVideoChromaSubsampling_Cosited	= ( ( MFVideoChromaSubsampling_Horizontally_Cosited or MFVideoChromaSubsampling_Vertically_Cosited ) or MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes ) ,
    MFVideoChromaSubsampling_Last	= ( MFVideoChromaSubsampling_Cosited + 1 ) ,
    MFVideoChromaSubsampling_ForceDWORD = 0x7fffffff
    }

.enum MFNominalRange {
    MFNominalRange_Unknown,
    MFNominalRange_Normal,
    MFNominalRange_Wide,
    MFNominalRange_0_255,
    MFNominalRange_16_235,
    MFNominalRange_48_208,
    MFNominalRange_64_127,
    MFNominalRange_Last,
    MFNominalRange_ForceDWORD	= 0x7fffffff
    }

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MFVideoFlags {
    MFVideoFlag_PAD_TO_Mask		= ( 0x1 or 0x2 ) ,
    MFVideoFlag_PAD_TO_None		= ( 0 * 0x1 ) ,
    MFVideoFlag_PAD_TO_4x3		= ( 1 * 0x1 ) ,
    MFVideoFlag_PAD_TO_16x9		= ( 2 * 0x1 ) ,
    MFVideoFlag_SrcContentHintMask	= ( ( 0x4 or 0x8 ) or 0x10 ) ,
    MFVideoFlag_SrcContentHintNone	= ( 0 * 0x4 ) ,
    MFVideoFlag_SrcContentHint16x9	= ( 1 * 0x4 ) ,
    MFVideoFlag_SrcContentHint235_1	= ( 2 * 0x4 ) ,
    MFVideoFlag_AnalogProtected		= 0x20,
    MFVideoFlag_DigitallyProtected	= 0x40,
    MFVideoFlag_ProgressiveContent	= 0x80,
    MFVideoFlag_FieldRepeatCountMask	= ( ( 0x100 or 0x200 ) or 0x400 ) ,
    MFVideoFlag_FieldRepeatCountShift	= 8,
    MFVideoFlag_ProgressiveSeqReset	= 0x800,
    MFVideoFlag_PanScanEnabled		= 0x20000,
    MFVideoFlag_LowerFieldFirst		= 0x40000,
    MFVideoFlag_BottomUpLinearRep	= 0x80000,
    MFVideoFlags_DXVASurface		= 0x100000,
    MFVideoFlags_RenderTargetSurface	= 0x400000,
    MFVideoFlags_ForceQWORD		= 0x7fffffff
    }

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFRatio			STRUC
Numerator		dd ?
Denominator		dd ?
MFRatio			ENDS

MFOffset		STRUC
fract			dw ?
value			sword ?
MFOffset		ENDS

MFVideoArea		STRUC
OffsetX			MFOffset <>
OffsetY			MFOffset <>
Area			tagSIZE <>
MFVideoArea		ENDS

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFVideoInfo		STRUC
dwWidth			dd ?
dwHeight		dd ?
PixelAspectRatio	MFRatio <>
SourceChromaSubsampling MFVideoChromaSubsampling ?
InterlaceMode		MFVideoInterlaceMode ?
TransferFunction	MFVideoTransferFunction ?
ColorPrimaries		MFVideoPrimaries ?
TransferMatrix		MFVideoTransferMatrix ?
SourceLighting		MFVideoLighting ?
FramesPerSecond		MFRatio <>
NominalRange		MFNominalRange ?
GeometricAperture	MFVideoArea <>
MinimumDisplayAperture	MFVideoArea <>
PanScanAperture		MFVideoArea <>
VideoFlags		int64_t ?
MFVideoInfo		ENDS

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MFAYUVSample		STRUC
bCrValue		db ?
bCbValue		db ?
bYValue			db ?
bSampleAlpha8		db ?
MFAYUVSample		ENDS

MFARGB			STRUC
rgbBlue			db ?
rgbGreen		db ?
rgbRed			db ?
rgbAlpha		db ?
MFARGB			ENDS

MFPaletteEntry		UNION
ARGB			MFARGB <>
AYCbCr			MFAYUVSample <>
MFPaletteEntry		ENDS

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MFVideoSurfaceInfo	STRUC
Format			dd ?
PaletteEntries		dd ?
Palette			MFPaletteEntry 1 dup(<>)
MFVideoSurfaceInfo	ENDS

MFVideoCompressedInfo	STRUC
AvgBitrate		LONGLONG ?
AvgBitErrorRate		LONGLONG ?
MaxKeyFrameSpacing	dd ?
MFVideoCompressedInfo	ENDS

MFVIDEOFORMAT		STRUC
dwSize			dd ?
videoInfo		MFVideoInfo <>
guidFormat		GUID <>
compressedInfo		MFVideoCompressedInfo <>
surfaceInfo		MFVideoSurfaceInfo <>
MFVIDEOFORMAT		ENDS

.enum MFStandardVideoFormat {
    MFStdVideoFormat_reserved,
    MFStdVideoFormat_NTSC,
    MFStdVideoFormat_PAL,
    MFStdVideoFormat_DVD_NTSC,
    MFStdVideoFormat_DVD_PAL,
    MFStdVideoFormat_DV_PAL,
    MFStdVideoFormat_DV_NTSC,
    MFStdVideoFormat_ATSC_SD480i,
    MFStdVideoFormat_ATSC_HD1080i,
    MFStdVideoFormat_ATSC_HD720p
    }

endif

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFVideoMediaType_INTERFACE_DEFINED__
define __IMFVideoMediaType_INTERFACE_DEFINED__

DEFINE_IIDX(IMFVideoMediaType, "b99f381f-a8f9-47a2-a5af-ca3a225a3890")

.comdef IMFVideoMediaType : public IMFMediaType

    GetVideoFormat	proc
    GetVideoRepresentation proc :GUID, :ptr, :LONG
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFAsyncResult_INTERFACE_DEFINED__
define __IMFAsyncResult_INTERFACE_DEFINED__

DEFINE_IIDX(IMFAsyncResult, "ac6b7889-0740-4d51-8619-905994a55cc6")

.comdef IMFAsyncResult : public IUnknown

    GetState		proc :ptr
    GetStatus		proc
    SetStatus		proc :HRESULT
    GetObject		proc :ptr
    GetStateNoAddRef	proc
   .ends

endif

ifndef __IMFAsyncCallback_INTERFACE_DEFINED__
define __IMFAsyncCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IMFAsyncCallback, "a27003cf-2354-4f2a-8d6a-ab7cff15437e")

.comdef IMFAsyncCallback : public IUnknown

    GetParameters	proc :ptr, :ptr
    _Invoke		proc :ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFAsyncCallbackLogging_INTERFACE_DEFINED__
define __IMFAsyncCallbackLogging_INTERFACE_DEFINED__

DEFINE_IIDX(IMFAsyncCallbackLogging, "c7a4dca1-f5f0-47b6-b92b-bf0106d25791")

.comdef IMFAsyncCallbackLogging : public IMFAsyncCallback

    GetObjectPointer	proc
    GetObjectTag	proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MFASYNC_FAST_IO_PROCESSING_CALLBACK equ 0x00000001
MFASYNC_SIGNAL_CALLBACK equ 0x00000002
MFASYNC_BLOCKING_CALLBACK equ 0x00000004
MFASYNC_REPLY_CALLBACK	equ 0x00000008
MFASYNC_LOCALIZE_REMOTE_CALLBACK equ 0x00000010
MFASYNC_CALLBACK_QUEUE_UNDEFINED equ 0x00000000
MFASYNC_CALLBACK_QUEUE_STANDARD equ 0x00000001
MFASYNC_CALLBACK_QUEUE_RT equ 0x00000002
MFASYNC_CALLBACK_QUEUE_IO equ 0x00000003
MFASYNC_CALLBACK_QUEUE_TIMER equ 0x00000004
MFASYNC_CALLBACK_QUEUE_MULTITHREADED equ 0x00000005
MFASYNC_CALLBACK_QUEUE_LONG_FUNCTION equ 0x00000007
MFASYNC_CALLBACK_QUEUE_PRIVATE_MASK equ 0xFFFF0000
MFASYNC_CALLBACK_QUEUE_ALL equ 0xFFFFFFFF

.enum _MIDL___MIDL_itf_mfobjects_0000_0012_0001 {
    MEUnknown	= 0,
    MEError = 1,
    MEExtendedType	= 2,
    MENonFatalError = 3,
    MEGenericV1Anchor	= MENonFatalError,
    MESessionUnknown	= 100,
    MESessionTopologySet	= 101,
    MESessionTopologiesCleared	= 102,
    MESessionStarted	= 103,
    MESessionPaused = 104,
    MESessionStopped	= 105,
    MESessionClosed = 106,
    MESessionEnded	= 107,
    MESessionRateChanged	= 108,
    MESessionScrubSampleComplete	= 109,
    MESessionCapabilitiesChanged	= 110,
    MESessionTopologyStatus = 111,
    MESessionNotifyPresentationTime = 112,
    MENewPresentation	= 113,
    MELicenseAcquisitionStart	= 114,
    MELicenseAcquisitionCompleted	= 115,
    MEIndividualizationStart	= 116,
    MEIndividualizationCompleted	= 117,
    MEEnablerProgress	= 118,
    MEEnablerCompleted	= 119,
    MEPolicyError	= 120,
    MEPolicyReport	= 121,
    MEBufferingStarted	= 122,
    MEBufferingStopped	= 123,
    MEConnectStart	= 124,
    MEConnectEnd	= 125,
    MEReconnectStart	= 126,
    MEReconnectEnd	= 127,
    MERendererEvent = 128,
    MESessionStreamSinkFormatChanged	= 129,
    MESessionV1Anchor	= MESessionStreamSinkFormatChanged,
    MESourceUnknown = 200,
    MESourceStarted = 201,
    MEStreamStarted = 202,
    MESourceSeeked	= 203,
    MEStreamSeeked	= 204,
    MENewStream = 205,
    MEUpdatedStream = 206,
    MESourceStopped = 207,
    MEStreamStopped = 208,
    MESourcePaused	= 209,
    MEStreamPaused	= 210,
    MEEndOfPresentation = 211,
    MEEndOfStream	= 212,
    MEMediaSample	= 213,
    MEStreamTick	= 214,
    MEStreamThinMode	= 215,
    MEStreamFormatChanged	= 216,
    MESourceRateChanged = 217,
    MEEndOfPresentationSegment	= 218,
    MESourceCharacteristicsChanged	= 219,
    MESourceRateChangeRequested = 220,
    MESourceMetadataChanged = 221,
    MESequencerSourceTopologyUpdated	= 222,
    MESourceV1Anchor	= MESequencerSourceTopologyUpdated,
    MESinkUnknown	= 300,
    MEStreamSinkStarted = 301,
    MEStreamSinkStopped = 302,
    MEStreamSinkPaused	= 303,
    MEStreamSinkRateChanged = 304,
    MEStreamSinkRequestSample	= 305,
    MEStreamSinkMarker	= 306,
    MEStreamSinkPrerolled	= 307,
    MEStreamSinkScrubSampleComplete = 308,
    MEStreamSinkFormatChanged	= 309,
    MEStreamSinkDeviceChanged	= 310,
    MEQualityNotify = 311,
    MESinkInvalidated	= 312,
    MEAudioSessionNameChanged	= 313,
    MEAudioSessionVolumeChanged = 314,
    MEAudioSessionDeviceRemoved = 315,
    MEAudioSessionServerShutdown	= 316,
    MEAudioSessionGroupingParamChanged	= 317,
    MEAudioSessionIconChanged	= 318,
    MEAudioSessionFormatChanged = 319,
    MEAudioSessionDisconnected	= 320,
    MEAudioSessionExclusiveModeOverride = 321,
    MESinkV1Anchor	= MEAudioSessionExclusiveModeOverride,
    MECaptureAudioSessionVolumeChanged	= 322,
    MECaptureAudioSessionDeviceRemoved	= 323,
    MECaptureAudioSessionFormatChanged	= 324,
    MECaptureAudioSessionDisconnected	= 325,
    MECaptureAudioSessionExclusiveModeOverride	= 326,
    MECaptureAudioSessionServerShutdown = 327,
    MESinkV2Anchor	= MECaptureAudioSessionServerShutdown,
    METrustUnknown	= 400,
    MEPolicyChanged = 401,
    MEContentProtectionMessage	= 402,
    MEPolicySet = 403,
    METrustV1Anchor = MEPolicySet,
    MEWMDRMLicenseBackupCompleted	= 500,
    MEWMDRMLicenseBackupProgress	= 501,
    MEWMDRMLicenseRestoreCompleted	= 502,
    MEWMDRMLicenseRestoreProgress	= 503,
    MEWMDRMLicenseAcquisitionCompleted	= 506,
    MEWMDRMIndividualizationCompleted	= 508,
    MEWMDRMIndividualizationProgress	= 513,
    MEWMDRMProximityCompleted	= 514,
    MEWMDRMLicenseStoreCleaned	= 515,
    MEWMDRMRevocationDownloadCompleted	= 516,
    MEWMDRMV1Anchor = MEWMDRMRevocationDownloadCompleted,
    METransformUnknown	= 600,
    METransformNeedInput,
    METransformHaveOutput,
    METransformDrainComplete,
    METransformMarker,
    MEByteStreamCharacteristicsChanged	= 700,
    MEVideoCaptureDeviceRemoved = 800,
    MEVideoCaptureDevicePreempted	= 801,
    MEStreamSinkFormatInvalidated	= 802,
    MEEncodingParameters	= 803,
    MEContentProtectionMetadata = 900,
    MEReservedMax	= 10000
    }
MediaEventType		typedef DWORD

ifndef __IMFMediaEvent_INTERFACE_DEFINED__
define __IMFMediaEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMFMediaEvent, "DF598932-F10C-4E39-BBA2-C308F101DAA3")

.comdef IMFMediaEvent : public IMFAttributes

    GetType		proc :ptr
    GetExtendedType	proc :ptr
    GetStatus		proc :ptr
    GetValue		proc :ptr
   .ends
    LPIMFMediaEvent	typedef ptr IMFMediaEvent

endif

MF_EVENT_FLAG_NO_WAIT	equ 0x00000001

ifndef __IMFMediaEventGenerator_INTERFACE_DEFINED__
define __IMFMediaEventGenerator_INTERFACE_DEFINED__

DEFINE_IIDX(IMFMediaEventGenerator, "2CD0BD52-BCD5-4B89-B62C-EADC0C031E7D")

.comdef IMFMediaEventGenerator : public IUnknown

    GetEvent		proc :DWORD, :ptr
    BeginGetEvent	proc :ptr, :ptr
    EndGetEvent		proc :ptr, :ptr
    QueueEvent		proc :MediaEventType, :REFGUID, :HRESULT, :ptr
   .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMFRemoteAsyncCallback_INTERFACE_DEFINED__
define __IMFRemoteAsyncCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IMFRemoteAsyncCallback, "a27003d0-2354-4f2a-8d6a-ab7cff15437e")

.comdef IMFRemoteAsyncCallback : public IUnknown

    _Invoke		proc :HRESULT, :ptr
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MFBYTESTREAM_SEEK_ORIGIN {
    msoBegin,
    msoCurrent
    }

ifndef __IMFByteStream_INTERFACE_DEFINED__
define __IMFByteStream_INTERFACE_DEFINED__

DEFINE_IIDX(IMFByteStream, "ad4c1b00-4bf7-422f-9175-756693d9130d")

.comdef IMFByteStream : public IUnknown

    GetCapabilities	proc :ptr
    GetLength		proc :ptr
    SetLength		proc :QWORD
    GetCurrentPosition	proc :ptr
    SetCurrentPosition	proc :QWORD
    IsEndOfStream	proc :ptr
    Read		proc :ptr, :ULONG, :ptr
    BeginRead		proc :ptr, :ULONG, :ptr, :ptr
    EndRead		proc :ptr, :ptr
    Write		proc :ptr, :ULONG, :ptr
    BeginWrite		proc :ptr, :ULONG, :ptr, :ptr
    EndWrite		proc :ptr, :ptr
    Seek		proc :MFBYTESTREAM_SEEK_ORIGIN, :LONGLONG, :DWORD, :ptr
    Flush		proc
    Close		proc
   .ends

endif

MFBYTESTREAM_IS_READABLE equ 0x00000001
MFBYTESTREAM_IS_WRITABLE equ 0x00000002
MFBYTESTREAM_IS_SEEKABLE equ 0x00000004
MFBYTESTREAM_IS_REMOTE	equ 0x00000008
MFBYTESTREAM_IS_DIRECTORY equ 0x00000080
MFBYTESTREAM_HAS_SLOW_SEEK equ 0x00000100
MFBYTESTREAM_IS_PARTIALLY_DOWNLOADED equ 0x00000200
if (WINVER GE _WIN32_WINNT_WIN7)
MFBYTESTREAM_SHARE_WRITE equ 0x00000400
endif
if (WINVER GE _WIN32_WINNT_WIN8)
MFBYTESTREAM_DOES_NOT_USE_NETWORK equ 0x00000800
endif
MFBYTESTREAM_SEEK_FLAG_CANCEL_PENDING_IO equ 0x00000001
DEFINE_GUID( MF_BYTESTREAM_ORIGIN_NAME, 0xfc358288, 0x3cb6, 0x460c, 0xa4, 0x24, 0xb6, 0x68, 0x12, 0x60, 0x37, 0x5a)
DEFINE_GUID( MF_BYTESTREAM_CONTENT_TYPE, 0xfc358289, 0x3cb6, 0x460c, 0xa4, 0x24, 0xb6, 0x68, 0x12, 0x60, 0x37, 0x5a)
DEFINE_GUID( MF_BYTESTREAM_DURATION, 0xfc35828a, 0x3cb6, 0x460c, 0xa4, 0x24, 0xb6, 0x68, 0x12, 0x60, 0x37, 0x5a)
DEFINE_GUID( MF_BYTESTREAM_LAST_MODIFIED_TIME, 0xfc35828b, 0x3cb6, 0x460c, 0xa4, 0x24, 0xb6, 0x68, 0x12, 0x60, 0x37, 0x5a)
if (WINVER GE _WIN32_WINNT_WIN7)
DEFINE_GUID( MF_BYTESTREAM_IFO_FILE_URI, 0xfc35828c, 0x3cb6, 0x460c, 0xa4, 0x24, 0xb6, 0x68, 0x12, 0x60, 0x37, 0x5a)
DEFINE_GUID( MF_BYTESTREAM_DLNA_PROFILE_ID, 0xfc35828d, 0x3cb6, 0x460c, 0xa4, 0x24, 0xb6, 0x68, 0x12, 0x60, 0x37, 0x5a)
DEFINE_GUID( MF_BYTESTREAM_EFFECTIVE_URL, 0x9afa0209, 0x89d1, 0x42af, 0x84, 0x56, 0x1d, 0xe6, 0xb5, 0x62, 0xd6, 0x91)
DEFINE_GUID( MF_BYTESTREAM_TRANSCODED, 0xb6c5c282, 0x4dc9, 0x4db9, 0xab, 0x48, 0xcf, 0x3b, 0x6d, 0x8b, 0xc5, 0xe0 )
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
DEFINE_GUID(CLSID_MFByteStreamProxyClassFactory, 0x770e8e77, 0x4916, 0x441c, 0xa9, 0xa7, 0xb3, 0x42, 0xd0, 0xee, 0xbc, 0x71 );

ifndef __IMFByteStreamProxyClassFactory_INTERFACE_DEFINED__
define __IMFByteStreamProxyClassFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IMFByteStreamProxyClassFactory, "a6b43f84-5c0a-42e8-a44d-b1857a76992f")

.comdef IMFByteStreamProxyClassFactory : public IUnknown

    CreateByteStreamProxy proc :ptr, :ptr, :REFIID, :ptr
   .ends

endif

.enum MF_FILE_ACCESSMODE {
    MF_ACCESSMODE_READ	= 1,
    MF_ACCESSMODE_WRITE = 2,
    MF_ACCESSMODE_READWRITE = 3
    }

.enum MF_FILE_OPENMODE {
    MF_OPENMODE_FAIL_IF_NOT_EXIST	= 0,
    MF_OPENMODE_FAIL_IF_EXIST	= 1,
    MF_OPENMODE_RESET_IF_EXIST	= 2,
    MF_OPENMODE_APPEND_IF_EXIST = 3,
    MF_OPENMODE_DELETE_IF_EXIST = 4
    }

.enum MF_FILE_FLAGS {
    MF_FILEFLAGS_NONE	= 0,
    MF_FILEFLAGS_NOBUFFERING	= 0x1,
    MF_FILEFLAGS_ALLOW_WRITE_SHARING	= 0x2
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFSampleOutputStream_INTERFACE_DEFINED__
define __IMFSampleOutputStream_INTERFACE_DEFINED__

DEFINE_IIDX(IMFSampleOutputStream, "8feed468-6f7e-440d-869a-49bdd283ad0d")

.comdef IMFSampleOutputStream : public IUnknown

    BeginWriteSample	proc :ptr, :ptr, :ptr
    EndWriteSample	proc :ptr
    Close		proc
   .ends

endif

ifndef __IMFCollection_INTERFACE_DEFINED__
define __IMFCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IMFCollection, "5BC8A76B-869A-46a3-9B03-FA218A66AEBE")

.comdef IMFCollection : public IUnknown

    GetElementCount	proc :ptr
    GetElement		proc :DWORD, :ptr
    AddElement		proc :ptr
    RemoveElement	proc :DWORD, :ptr
    InsertElementAt	proc :DWORD, :ptr
    RemoveAllElements	proc
   .ends

endif

ifndef __IMFMediaEventQueue_INTERFACE_DEFINED__
define __IMFMediaEventQueue_INTERFACE_DEFINED__

DEFINE_IIDX(IMFMediaEventQueue, "36f846fc-2256-48b6-b58e-e2b638316581")

.comdef IMFMediaEventQueue : public IUnknown

    GetEvent		proc :DWORD, :ptr
    BeginGetEvent	proc :ptr, :ptr
    EndGetEvent		proc :ptr, :ptr
    QueueEvent		proc :ptr
    QueueEventParamVar	proc :MediaEventType, :REFGUID, :HRESULT, :ptr
    QueueEventParamUnk	proc :MediaEventType, :REFGUID, :HRESULT, :ptr
    Shutdown		proc
   .ends

endif

ifndef __IMFActivate_INTERFACE_DEFINED__
define __IMFActivate_INTERFACE_DEFINED__

DEFINE_IIDX(IMFActivate, "7FEE9E9A-4A89-47a6-899C-B6A53A70FB67")

.comdef IMFActivate : public IMFAttributes

    ActivateObject	proc :REFIID, :ptr
    ShutdownObject	proc
    DetachObject	proc
   .ends

endif

endif

if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MF_Plugin_Type {
    MF_Plugin_Type_MFT	= 0,
    MF_Plugin_Type_MediaSource	= 1,
    MF_Plugin_Type_MFT_MatchOutputType	= 2,
    MF_Plugin_Type_Other	= ( DWORD  )-1
    }

ifndef __IMFPluginControl_INTERFACE_DEFINED__
define __IMFPluginControl_INTERFACE_DEFINED__

DEFINE_IIDX(IMFPluginControl, "5c6c44bf-1db6-435b-9249-e8cd10fdec96")

.comdef IMFPluginControl : public IUnknown

    GetPreferredClsid	proc :DWORD, :LPCWSTR, :ptr
    GetPreferredClsidByIndex proc :DWORD, :DWORD, :ptr, :ptr
    SetPreferredClsid	proc :DWORD, :LPCWSTR, :ptr
    IsDisabled		proc :DWORD, :REFCLSID
    GetDisabledByIndex	proc :DWORD, :DWORD, :ptr
    SetDisabled		proc :DWORD, :REFCLSID, :BOOL
   .ends

endif

.enum MF_PLUGIN_CONTROL_POLICY {
    MF_PLUGIN_CONTROL_POLICY_USE_ALL_PLUGINS	= 0,
    MF_PLUGIN_CONTROL_POLICY_USE_APPROVED_PLUGINS	= 1,
    MF_PLUGIN_CONTROL_POLICY_USE_WEB_PLUGINS	= 2
    }

ifndef __IMFPluginControl2_INTERFACE_DEFINED__
define __IMFPluginControl2_INTERFACE_DEFINED__

DEFINE_IIDX(IMFPluginControl2, "C6982083-3DDC-45CB-AF5E-0F7A8CE4DE77")

.comdef IMFPluginControl2 : public IMFPluginControl

    SetPolicy		proc :MF_PLUGIN_CONTROL_POLICY
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IMFDXGIDeviceManager_INTERFACE_DEFINED__
define __IMFDXGIDeviceManager_INTERFACE_DEFINED__

DEFINE_IIDX(IMFDXGIDeviceManager, "eb533d5d-2db6-40f8-97a9-494692014f07")

.comdef IMFDXGIDeviceManager : public IUnknown

    CloseDeviceHandle	proc :HANDLE
    GetVideoService	proc :HANDLE, :REFIID, :ptr
    LockDevice		proc :HANDLE, :REFIID, :ptr, :BOOL
    OpenDeviceHandle	proc :ptr
    ResetDevice		proc :ptr, :UINT
    TestDevice		proc :HANDLE
    UnlockDevice	proc :HANDLE, :BOOL
   .ends

endif
endif
endif

endif
