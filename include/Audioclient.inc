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
ifndef __audioclient_h__
__audioclient_h__ equ <>
.xlist

ifndef __IAudioClient_FWD_DEFINED__
__IAudioClient_FWD_DEFINED__ equ 1
endif
ifndef __IAudioRenderClient_FWD_DEFINED__
__IAudioRenderClient_FWD_DEFINED__ equ 1
endif
ifndef __IAudioCaptureClient_FWD_DEFINED__
__IAudioCaptureClient_FWD_DEFINED__ equ 1
endif
ifndef __IAudioClock_FWD_DEFINED__
__IAudioClock_FWD_DEFINED__ equ 1
endif
ifndef __IAudioClock2_FWD_DEFINED__
__IAudioClock2_FWD_DEFINED__ equ 1
endif
ifndef __IAudioClockAdjustment_FWD_DEFINED__
__IAudioClockAdjustment_FWD_DEFINED__ equ 1
endif
ifndef __ISimpleAudioVolume_FWD_DEFINED__
__ISimpleAudioVolume_FWD_DEFINED__ equ 1
endif
ifndef __IAudioStreamVolume_FWD_DEFINED__
__IAudioStreamVolume_FWD_DEFINED__ equ 1
endif
ifndef __IChannelAudioVolume_FWD_DEFINED__
__IChannelAudioVolume_FWD_DEFINED__ equ 1
endif
include wtypes.inc
include unknwn.inc
include AudioSessionTypes.inc
.xlist

if 0
wFormatTag		typedef	 struct WAVEFORMATEX { WORD
nChannels		dw ?
nSamplesPerSec		dd ?
nAvgBytesPerSec		dd ?
nBlockAlign		dw ?
wBitsPerSample		dw ?
cbSize			dw ?
WAVEFORMATEX		ENDS
else
include mmreg.inc
endif

if 0
REFERENCE_TIME		typedef	 LONGLONG
else
_IKsControl_ equ 1
include ks.inc
include ksmedia.inc
.xlist
endif

AUDCLNT_BUFFERFLAGS	typedef SDWORD
AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY equ 0x1
AUDCLNT_BUFFERFLAGS_SILENT equ 0x2
AUDCLNT_BUFFERFLAGS_TIMESTAMP_ERROR equ 0x4


externdef		__MIDL_itf_audioclient_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_audioclient_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAudioClient_INTERFACE_DEFINED__
__IAudioClient_INTERFACE_DEFINED__ equ 1
externdef		IID_IAudioClient:IID

.comdef IAudioClient

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc :AUDCLNT_SHAREMODE, :DWORD, :REFERENCE_TIME, :REFERENCE_TIME, :ptr, :LPCGUID
    GetBufferSize	proc :ptr
    GetStreamLatency	proc :ptr
    GetCurrentPadding	proc :ptr
    IsFormatSupported	proc :AUDCLNT_SHAREMODE, :ptr, :ptr
    GetMixFormat	proc :ptr
    GetDevicePeriod	proc :ptr, :ptr
    Start		proc
    Stop		proc
    Reset		proc
    SetEventHandle	proc :HANDLE
    GetService		proc :REFIID, :ptr
    .ends
endif

ifndef __IAudioRenderClient_INTERFACE_DEFINED__
__IAudioRenderClient_INTERFACE_DEFINED__ equ 1
externdef		IID_IAudioRenderClient:IID

.comdef IAudioRenderClient

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetBuffer		proc :UINT32, :ptr
    ReleaseBuffer	proc :UINT32, :DWORD
    .ends
endif	;; __IAudioRenderClient_INTERFACE_DEFINED__

ifndef __IAudioCaptureClient_INTERFACE_DEFINED__
__IAudioCaptureClient_INTERFACE_DEFINED__ equ 1
externdef		IID_IAudioCaptureClient:IID

.comdef IAudioCaptureClient

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetBuffer		proc :ptr, :ptr, :ptr, :ptr, :ptr
    ReleaseBuffer	proc :UINT32
    GetNextPacketSize	proc :ptr
    .ends
endif

AUDIOCLOCK_CHARACTERISTIC_FIXED_FREQ equ 0x00000001

externdef		__MIDL_itf_audioclient_0000_0003_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_audioclient_0000_0003_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAudioClock_INTERFACE_DEFINED__
__IAudioClock_INTERFACE_DEFINED__ equ 1
externdef		IID_IAudioClock:IID

.comdef IAudioClock

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFrequency	proc :ptr
    GetPosition		proc :ptr, :ptr
    GetCharacteristics	proc :ptr
    .ends
endif

ifndef __IAudioClock2_INTERFACE_DEFINED__
__IAudioClock2_INTERFACE_DEFINED__ equ 1
externdef		IID_IAudioClock2:IID

.comdef IAudioClock2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevicePosition	proc :ptr, :ptr
    .ends
endif

ifndef __IAudioClockAdjustment_INTERFACE_DEFINED__
__IAudioClockAdjustment_INTERFACE_DEFINED__ equ 1
externdef		IID_IAudioClockAdjustment:IID

.comdef IAudioClockAdjustment

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetSampleRate	proc :FLOAT
    .ends
endif

ifndef __ISimpleAudioVolume_INTERFACE_DEFINED__
__ISimpleAudioVolume_INTERFACE_DEFINED__ equ 1
externdef		IID_ISimpleAudioVolume:IID

.comdef ISimpleAudioVolume

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetMasterVolume	proc :FLOAT, :LPCGUID
    GetMasterVolume	proc :ptr
    SetMute		proc :ptr, :LPCGUID
    GetMute		proc :ptr
    .ends
endif

ifndef __IAudioStreamVolume_INTERFACE_DEFINED__
__IAudioStreamVolume_INTERFACE_DEFINED__ equ 1
externdef		IID_IAudioStreamVolume:IID

.comdef IAudioStreamVolume

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetChannelCount	proc :ptr
    SetChannelVolume	proc :UINT32, :ptr
    GetChannelVolume	proc :UINT32, :ptr
    SetAllVolumes	proc :UINT32, :ptr
    GetAllVolumes	proc :UINT32, :ptr
    .ends
endif

ifndef __IChannelAudioVolume_INTERFACE_DEFINED__
__IChannelAudioVolume_INTERFACE_DEFINED__ equ 1
externdef		IID_IChannelAudioVolume:IID

.comdef IChannelAudioVolume

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetChannelCount	proc :ptr
    SetChannelVolume	proc :UINT32, :ptr, :LPCGUID
    GetChannelVolume	proc :UINT32, :ptr
    SetAllVolumes	proc :UINT32
    GetAllVolumes	proc :UINT32, :ptr
    .ends
endif

FACILITY_AUDCLNT	equ 0x889
AUDCLNT_ERR macro n
	exitm<MAKE_HRESULT(SEVERITY_ERROR, FACILITY_AUDCLNT, n)>
	endm
AUDCLNT_SUCCESS macro n
	exitm<MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_AUDCLNT, n)>
	endm
AUDCLNT_E_NOT_INITIALIZED equ AUDCLNT_ERR(0x001)
AUDCLNT_E_ALREADY_INITIALIZED equ AUDCLNT_ERR(0x002)
AUDCLNT_E_WRONG_ENDPOINT_TYPE equ AUDCLNT_ERR(0x003)
AUDCLNT_E_DEVICE_INVALIDATED equ AUDCLNT_ERR(0x004)
AUDCLNT_E_NOT_STOPPED	equ AUDCLNT_ERR(0x005)
AUDCLNT_E_BUFFER_TOO_LARGE equ AUDCLNT_ERR(0x006)
AUDCLNT_E_OUT_OF_ORDER	equ AUDCLNT_ERR(0x007)
AUDCLNT_E_UNSUPPORTED_FORMAT equ AUDCLNT_ERR(0x008)
AUDCLNT_E_INVALID_SIZE	equ AUDCLNT_ERR(0x009)
AUDCLNT_E_DEVICE_IN_USE equ AUDCLNT_ERR(0x00a)
AUDCLNT_E_BUFFER_OPERATION_PENDING equ AUDCLNT_ERR(0x00b)
AUDCLNT_E_THREAD_NOT_REGISTERED equ AUDCLNT_ERR(0x00c)
AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED equ AUDCLNT_ERR(0x00e)
AUDCLNT_E_ENDPOINT_CREATE_FAILED equ AUDCLNT_ERR(0x00f)
AUDCLNT_E_SERVICE_NOT_RUNNING equ AUDCLNT_ERR(0x010)
AUDCLNT_E_EVENTHANDLE_NOT_EXPECTED equ AUDCLNT_ERR(0x011)
AUDCLNT_E_EXCLUSIVE_MODE_ONLY equ AUDCLNT_ERR(0x012)
AUDCLNT_E_BUFDURATION_PERIOD_NOT_EQUAL equ AUDCLNT_ERR(0x013)
AUDCLNT_E_EVENTHANDLE_NOT_SET equ AUDCLNT_ERR(0x014)
AUDCLNT_E_INCORRECT_BUFFER_SIZE equ AUDCLNT_ERR(0x015)
AUDCLNT_E_BUFFER_SIZE_ERROR equ AUDCLNT_ERR(0x016)
AUDCLNT_E_CPUUSAGE_EXCEEDED equ AUDCLNT_ERR(0x017)
AUDCLNT_E_BUFFER_ERROR	equ AUDCLNT_ERR(0x018)
AUDCLNT_E_BUFFER_SIZE_NOT_ALIGNED equ AUDCLNT_ERR(0x019)
AUDCLNT_E_INVALID_DEVICE_PERIOD equ AUDCLNT_ERR(0x020)
AUDCLNT_S_BUFFER_EMPTY	equ AUDCLNT_SUCCESS(0x001)
AUDCLNT_S_THREAD_ALREADY_REGISTERED equ AUDCLNT_SUCCESS(0x002)
AUDCLNT_S_POSITION_STALLED equ AUDCLNT_SUCCESS(0x003)

externdef __MIDL_itf_audioclient_0000_0009_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_audioclient_0000_0009_v0_0_s_ifspec:RPC_IF_HANDLE

.list
endif
