ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
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
define __austream_h__

include unknwn.inc
include mmstream.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IAudioMediaStream_INTERFACE_DEFINED__
define __IAudioMediaStream_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioMediaStream, "f7537560-a3be-11d0-8212-00c04fc32c45")

.comdef IAudioMediaStream : public IUnknown

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
define __IAudioStreamSample_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioStreamSample, "345fee00-aba5-11d0-8212-00c04fc32c45")

.comdef IAudioStreamSample : public IUnknown

    GetMediaStream	proc :ptr
    GetSampleTimes	proc :ptr, :ptr, :ptr
    SetSampleTimes	proc :ptr, :ptr
    Update		proc :DWORD, :HANDLE, :PAPCFUNC, :DWORD_PTR
    CompletionStatus	proc :DWORD, :DWORD
    GetAudioData	proc :ptr
   .ends

endif

ifndef __IMemoryData_INTERFACE_DEFINED__
define __IMemoryData_INTERFACE_DEFINED__

DEFINE_IIDX(IMemoryData, "327fc560-af60-11d0-8212-00c04fc32c45")

.comdef IMemoryData : public IUnknown

    SetBuffer		proc :DWORD, :ptr, :DWORD
    GetInfo		proc :ptr, :ptr, :ptr
    SetActual		proc :DWORD
   .ends

endif

ifndef __IAudioData_INTERFACE_DEFINED__
define __IAudioData_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioData, "54c719c0-af60-11d0-8212-00c04fc32c45")

.comdef IAudioData : public IUnknown

    SetBuffer		proc :DWORD, :ptr, :DWORD
    GetInfo		proc :ptr, :ptr, :ptr
    SetActual		proc :DWORD
    GetFormat		proc :ptr
    SetFormat		proc :ptr
   .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
