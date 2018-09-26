ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err<this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __austream_h__
__austream_h__ equ <>

ifndef __IAudioMediaStream_FWD_DEFINED__
__IAudioMediaStream_FWD_DEFINED__ equ 1
endif
ifndef __IAudioStreamSample_FWD_DEFINED__
__IAudioStreamSample_FWD_DEFINED__ equ 1
endif
ifndef __IMemoryData_FWD_DEFINED__
__IMemoryData_FWD_DEFINED__ equ 1
endif
ifndef __IAudioData_FWD_DEFINED__
__IAudioData_FWD_DEFINED__ equ 1
endif

include unknwn.inc
include mmstream.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

externdef		__MIDL_itf_austream_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_austream_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAudioMediaStream_INTERFACE_DEFINED__
__IAudioMediaStream_INTERFACE_DEFINED__ equ 1

externdef		IID_IAudioMediaStream:IID

.comdef IAudioMediaStream

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMultiMediaStream proc :ptr
    GetInformation	proc :ptr, :ptr
    SetSameFormat	proc :ptr, :DWORD
    AllocateSample	proc :DWORD, :ptr
    CreateSharedSample	proc :ptr, :DWORD, :ptr
    SendEndOfStream	proc :DWORD
    GetFormat		proc :ptr
    SetFormat		proc :ptr
    CreateSample	proc :ptr, :DWORD, :ptr
    .ends

endif

ifndef __IAudioStreamSample_INTERFACE_DEFINED__
__IAudioStreamSample_INTERFACE_DEFINED__ equ 1

externdef		IID_IAudioStreamSample:IID

.comdef IAudioStreamSample

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMediaStream	proc :ptr
    GetSampleTimes	proc :ptr, :ptr, :ptr
    SetSampleTimes	proc :ptr, :ptr
    Update		proc :DWORD, :HANDLE, :PAPCFUNC, :DWORD_PTR
    CompletionStatus	proc :DWORD, :DWORD
    GetAudioData	proc :ptr
    .ends

endif

ifndef __IMemoryData_INTERFACE_DEFINED__
__IMemoryData_INTERFACE_DEFINED__ equ 1

externdef		IID_IMemoryData:IID

.comdef IMemoryData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetBuffer		proc :DWORD, :ptr, :DWORD
    GetInfo		proc :ptr, :ptr, :ptr
    SetActual		proc :DWORD
    .ends

endif

ifndef __IAudioData_INTERFACE_DEFINED__
__IAudioData_INTERFACE_DEFINED__ equ 1

externdef		IID_IAudioData:IID

.comdef IAudioData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetBuffer		proc :DWORD, :ptr, :DWORD
    GetInfo		proc :ptr, :ptr, :ptr
    SetActual		proc :DWORD
    GetFormat		proc :ptr
    SetFormat		proc :ptr
    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

externdef		__MIDL_itf_austream_0000_0004_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_austream_0000_0004_v0_0_s_ifspec:RPC_IF_HANDLE

endif
