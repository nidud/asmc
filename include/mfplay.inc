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

ifndef __mfplay_h__
define __mfplay_h__

include unknwn.inc
include propsys.inc
include mfidl.inc
include evr.inc
include winapifamily.inc

.pragma comment(lib, mfplay)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (WINVER GE _WIN32_WINNT_WIN7)

.enum MFP_CREATION_OPTIONS {
    MFP_OPTION_NONE	= 0,
    MFP_OPTION_FREE_THREADED_CALLBACK	= 0x1,
    MFP_OPTION_NO_MMCSS = 0x2,
    MFP_OPTION_NO_REMOTE_DESKTOP_OPTIMIZATION	= 0x4
    }

.enum MFP_MEDIAPLAYER_STATE {
    MFP_MEDIAPLAYER_STATE_EMPTY = 0,
    MFP_MEDIAPLAYER_STATE_STOPPED	= 0x1,
    MFP_MEDIAPLAYER_STATE_PLAYING	= 0x2,
    MFP_MEDIAPLAYER_STATE_PAUSED	= 0x3,
    MFP_MEDIAPLAYER_STATE_SHUTDOWN	= 0x4
    }

.enum MFP_MEDIAITEM_CHARACTERISTICS : UINT32 {
    MFP_MEDIAITEM_IS_LIVE	= 0x1,
    MFP_MEDIAITEM_CAN_SEEK	= 0x2,
    MFP_MEDIAITEM_CAN_PAUSE	= 0x4,
    MFP_MEDIAITEM_HAS_SLOW_SEEK = 0x8
    }

.enum MFP_CREDENTIAL_FLAGS : UINT32 {
    MFP_CREDENTIAL_PROMPT	= 0x1,
    MFP_CREDENTIAL_SAVE = 0x2,
    MFP_CREDENTIAL_DO_NOT_CACHE = 0x4,
    MFP_CREDENTIAL_CLEAR_TEXT	= 0x8,
    MFP_CREDENTIAL_PROXY	= 0x10,
    MFP_CREDENTIAL_LOGGED_ON_USER	= 0x20
    }

MFPCreateMediaPlayer proto WINAPI \
	       pwszURL: LPCWSTR,
	fStartPlayback: BOOL,
       creationOptions: MFP_CREATION_OPTIONS,
	     pCallback: ptr IMFPMediaPlayerCallback,
		  hWnd: HWND,
	 ppMediaPlayer: ptr IMFPMediaPlayer

ifndef __IMFPMediaPlayer_INTERFACE_DEFINED__
define __IMFPMediaPlayer_INTERFACE_DEFINED__

DEFINE_IIDX(IMFPMediaPlayer, "A714590A-58AF-430a-85BF-44F5EC838D85")

.comdef IMFPMediaPlayer : public IUnknown

    Play		proc
    _Pause		proc
    Stop		proc
    FrameStep		proc
    SetPosition		proc :REFGUID, :ptr PROPVARIANT
    GetPosition		proc :REFGUID, :ptr
    GetDuration		proc :REFGUID, :ptr
    SetRate		proc :real4
    GetRate		proc :ptr
    GetSupportedRates	proc :BOOL, :ptr, :ptr
    GetState		proc :ptr
    CreateMediaItemFromURL proc :LPCWSTR, :BOOL, :DWORD_PTR, :ptr
    CreateMediaItemFromObject proc :ptr, :BOOL, :DWORD_PTR, :ptr
    SetMediaItem	proc :ptr
    ClearMediaItem	proc
    GetMediaItem	proc :ptr
    GetVolume		proc :ptr
    SetVolume		proc :real4
    GetBalance		proc :ptr
    SetBalance		proc :real4
    GetMute		proc :ptr
    SetMute		proc :BOOL
    GetNativeVideoSize	proc :ptr, :ptr
    GetIdealVideoSize	proc :ptr, :ptr
    SetVideoSourceRect	proc :ptr MFVideoNormalizedRect
    GetVideoSourceRect	proc :ptr
    SetAspectRatioMode	proc :DWORD
    GetAspectRatioMode	proc :ptr
    GetVideoWindow	proc :ptr
    UpdateVideo		proc
    SetBorderColor	proc :COLORREF
    GetBorderColor	proc :ptr
    InsertEffect	proc :ptr, :BOOL
    RemoveEffect	proc :ptr
    RemoveAllEffects	proc
    Shutdown		proc
   .ends
    LPIMFPMediaPlayer	typedef ptr IMFPMediaPlayer

endif


DEFINE_GUID( MFP_POSITIONTYPE_100NS, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 )

ifndef __IMFPMediaItem_INTERFACE_DEFINED__
define __IMFPMediaItem_INTERFACE_DEFINED__

DEFINE_IIDX(IMFPMediaItem, "90EB3E6B-ECBF-45cc-B1DA-C6FE3EA70D57")

.comdef IMFPMediaItem : public IUnknown

    GetMediaPlayer	proc :ptr
    GetURL		proc :ptr
    GetObject		proc :ptr
    GetUserData		proc :ptr
    SetUserData		proc :DWORD_PTR
    GetStartStopPosition proc :ptr, :ptr, :ptr, :ptr
    SetStartStopPosition proc :ptr GUID, :ptr PROPVARIANT, :ptr GUID, :ptr PROPVARIANT
    HasVideo		proc :ptr, :ptr
    HasAudio		proc :ptr, :ptr
    IsProtected		proc :ptr
    GetDuration		proc :REFGUID, :ptr
    GetNumberOfStreams	proc :ptr
    GetStreamSelection	proc :DWORD, :ptr
    SetStreamSelection	proc :DWORD, :BOOL
    GetStreamAttribute	proc :DWORD, :REFGUID, :ptr
    GetPresentationAttribute proc :REFGUID, :ptr
    GetCharacteristics	proc :ptr
    SetStreamSink	proc :DWORD, :ptr
    GetMetadata		proc :ptr
   .ends
    LPIMFPMediaItem	typedef ptr IMFPMediaItem

endif

.enum MFP_EVENT_TYPE {
    MFP_EVENT_TYPE_PLAY = 0,
    MFP_EVENT_TYPE_PAUSE	= 1,
    MFP_EVENT_TYPE_STOP = 2,
    MFP_EVENT_TYPE_POSITION_SET = 3,
    MFP_EVENT_TYPE_RATE_SET	= 4,
    MFP_EVENT_TYPE_MEDIAITEM_CREATED	= 5,
    MFP_EVENT_TYPE_MEDIAITEM_SET	= 6,
    MFP_EVENT_TYPE_FRAME_STEP	= 7,
    MFP_EVENT_TYPE_MEDIAITEM_CLEARED	= 8,
    MFP_EVENT_TYPE_MF	= 9,
    MFP_EVENT_TYPE_ERROR	= 10,
    MFP_EVENT_TYPE_PLAYBACK_ENDED	= 11,
    MFP_EVENT_TYPE_ACQUIRE_USER_CREDENTIAL	= 12
    }

LPIPropertyStore	typedef ptr IPropertyStore
MFP_EVENT_HEADER	STRUC
eEventType		MFP_EVENT_TYPE ?
hrEvent			HRESULT ?
pMediaPlayer		LPIMFPMediaPlayer ?
eState			MFP_MEDIAPLAYER_STATE ?
pPropertyStore		LPIPropertyStore ?
MFP_EVENT_HEADER	ENDS

MFP_PLAY_EVENT		STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
MFP_PLAY_EVENT		ENDS

MFP_PAUSE_EVENT		STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
MFP_PAUSE_EVENT		ENDS

MFP_STOP_EVENT		STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
MFP_STOP_EVENT		ENDS

MFP_POSITION_SET_EVENT	STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
MFP_POSITION_SET_EVENT	ENDS

MFP_RATE_SET_EVENT	STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
flRate			real4 ?
MFP_RATE_SET_EVENT	ENDS

MFP_MEDIAITEM_CREATED_EVENT STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
dwUserData		dd ?
MFP_MEDIAITEM_CREATED_EVENT ENDS

MFP_MEDIAITEM_SET_EVENT STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
MFP_MEDIAITEM_SET_EVENT ENDS

MFP_FRAME_STEP_EVENT	STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
MFP_FRAME_STEP_EVENT	ENDS

MFP_MEDIAITEM_CLEARED_EVENT STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
MFP_MEDIAITEM_CLEARED_EVENT ENDS

MFP_MF_EVENT		STRUC
header			MFP_EVENT_HEADER <>
MFEventType		MediaEventType ?
pMFMediaEvent		LPIMFMediaEvent ?
pMediaItem		LPIMFPMediaItem ?
MFP_MF_EVENT		ENDS

MFP_ERROR_EVENT		STRUC
header			MFP_EVENT_HEADER <>
MFP_ERROR_EVENT		ENDS

MFP_PLAYBACK_ENDED_EVENT STRUC
header			MFP_EVENT_HEADER <>
pMediaItem		LPIMFPMediaItem ?
MFP_PLAYBACK_ENDED_EVENT ENDS

MFP_ACQUIRE_USER_CREDENTIAL_EVENT STRUC
header			MFP_EVENT_HEADER <>
dwUserData		dd ?
fProceedWithAuthentication BOOL ?
hrAuthenticationStatus	HRESULT ?
pwszURL			LPCWSTR ?
pwszSite		LPCWSTR ?
pwszRealm		LPCWSTR ?
pwszPackage		LPCWSTR ?
nRetries		LONG ?
flags			MFP_CREDENTIAL_FLAGS ?
pCredential		LPIMFNetCredential ?
MFP_ACQUIRE_USER_CREDENTIAL_EVENT ENDS

MFP_PKEY_StreamIndex equ <{ { 0xa7cf9740, 0xe8d9, 0x4a87, { 0xbd, 0x8e, 0x29, 0x67, 0x0, 0x1f, 0xd3, 0xad } }, 0x00 }>
MFP_PKEY_StreamRenderingResults equ <{ { 0xa7cf9740, 0xe8d9, 0x4a87, { 0xbd, 0x8e, 0x29, 0x67, 0x0, 0x1f, 0xd3, 0xad } }, 0x01 }>

__MFP_CAST_EVENT proto fastcall :ptr, :abs {
	xor eax,eax
	cmp [rcx].MFP_EVENT_HEADER.eEventType,MFP_EVENT_TYPE_&_2
	cmove rax,rcx
	}
MFP_GET_PLAY_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, PLAY )>
	endm
MFP_GET_PAUSE_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, PAUSE )>
	endm
MFP_GET_STOP_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, STOP )>
	endm
MFP_GET_POSITION_SET_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, POSITION_SET )>
	endm
MFP_GET_RATE_SET_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, RATE_SET )>
	endm
MFP_GET_MEDIAITEM_CREATED_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, MEDIAITEM_CREATED )>
	endm
MFP_GET_MEDIAITEM_SET_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, MEDIAITEM_SET )>
	endm
MFP_GET_FRAME_STEP_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, FRAME_STEP )>
	endm
MFP_GET_MEDIAITEM_CLEARED_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, MEDIAITEM_CLEARED )>
	endm
MFP_GET_MF_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, MF )>
	endm
MFP_GET_ERROR_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, ERROR )>
	endm
MFP_GET_PLAYBACK_ENDED_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, PLAYBACK_ENDED )>
	endm
MFP_GET_ACQUIRE_USER_CREDENTIAL_EVENT macro pHdr
	exitm<__MFP_CAST_EVENT( pHdr, ACQUIRE_USER_CREDENTIAL )>
	endm

ifndef __IMFPMediaPlayerCallback_INTERFACE_DEFINED__
define __IMFPMediaPlayerCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IMFPMediaPlayerCallback, "766C8FFB-5FDB-4fea-A28D-B912996F51BD")

.comdef IMFPMediaPlayerCallback : public IUnknown

    OnMediaPlayerEvent	proc :ptr
   .ends

endif

endif ;; (WINVER GE _WIN32_WINNT_WIN7)
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
