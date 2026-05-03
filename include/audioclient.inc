ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __audioclient_h__
define __audioclient_h__

include wtypes.inc
ifndef __unknwn_h__
include unknwn.inc
endif
include audiosessiontypes.inc

include mmreg.inc
define _IKsControl_
include ks.inc
include ksmedia.inc

AUDCLNT_BUFFERFLAGS typedef SDWORD
AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY equ 0x1
AUDCLNT_BUFFERFLAGS_SILENT equ 0x2
AUDCLNT_BUFFERFLAGS_TIMESTAMP_ERROR equ 0x4

ifndef __IAudioClient_INTERFACE_DEFINED__
define __IAudioClient_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioClient, "1CB9AD4C-DBFA-4c32-B178-C2F568A703B2")

.comdef IAudioClient : public IUnknown

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
define __IAudioRenderClient_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioRenderClient, "F294ACFC-3146-4483-A7BF-ADDCA7C260E2")

.comdef IAudioRenderClient : public IUnknown

    GetBuffer		proc :UINT32, :ptr
    ReleaseBuffer	proc :UINT32, :DWORD
   .ends

endif

ifndef __IAudioCaptureClient_INTERFACE_DEFINED__
define __IAudioCaptureClient_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioCaptureClient, "C8ADBD64-E71E-48a0-A4DE-185C395CD317")

.comdef IAudioCaptureClient : public IUnknown

    GetBuffer		proc :ptr, :ptr, :ptr, :ptr, :ptr
    ReleaseBuffer	proc :UINT32
    GetNextPacketSize	proc :ptr
   .ends

endif

AUDIOCLOCK_CHARACTERISTIC_FIXED_FREQ equ 0x00000001

ifndef __IAudioClock_INTERFACE_DEFINED__
define __IAudioClock_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioClock, "CD63314F-3FBA-4a1b-812C-EF96358728E7")

.comdef IAudioClock : public IUnknown

    GetFrequency	proc :ptr
    GetPosition		proc :ptr, :ptr
    GetCharacteristics	proc :ptr
   .ends

endif

ifndef __IAudioClock2_INTERFACE_DEFINED__
define __IAudioClock2_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioClock2, "6f49ff73-6727-49ac-a008-d98cf5e70048")

.comdef IAudioClock2 : public IUnknown

    GetDevicePosition	proc :ptr, :ptr
   .ends

endif

ifndef __IAudioClockAdjustment_INTERFACE_DEFINED__
define __IAudioClockAdjustment_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioClockAdjustment, "f6e4c0a0-46d9-4fb8-be21-57a3ef2b626c")

.comdef IAudioClockAdjustment : public IUnknown

    SetSampleRate	proc :FLOAT
   .ends

endif

ifndef __ISimpleAudioVolume_INTERFACE_DEFINED__
define __ISimpleAudioVolume_INTERFACE_DEFINED__

DEFINE_IIDX(ISimpleAudioVolume, "87CE5498-68D6-44E5-9215-6DA47EF883D8")

.comdef ISimpleAudioVolume : public IUnknown

    SetMasterVolume	proc :FLOAT, :LPCGUID
    GetMasterVolume	proc :ptr
    SetMute		proc :ptr, :LPCGUID
    GetMute		proc :ptr
   .ends

endif

ifndef __IAudioStreamVolume_INTERFACE_DEFINED__
define __IAudioStreamVolume_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioStreamVolume, "93014887-242D-4068-8A15-CF5E93B90FE3")

.comdef IAudioStreamVolume : public IUnknown

    GetChannelCount	proc :ptr
    SetChannelVolume	proc :UINT32, :ptr
    GetChannelVolume	proc :UINT32, :ptr
    SetAllVolumes	proc :UINT32, :ptr
    GetAllVolumes	proc :UINT32, :ptr
   .ends

endif

ifndef __IChannelAudioVolume_INTERFACE_DEFINED__
define __IChannelAudioVolume_INTERFACE_DEFINED__

DEFINE_IIDX(IChannelAudioVolume, "1C158861-B533-4B30-B1CF-E853E51C59B8")

.comdef IChannelAudioVolume : public IUnknown

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

endif
