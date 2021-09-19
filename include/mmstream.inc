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
ifndef __mmstream_h__
define __mmstream_h__

include unknwn.inc

MS_ERROR_CODE macro x
	exitm<MAKE_HRESULT(1, FACILITY_ITF, (x) + 0x400)>
	endm
MS_SUCCESS_CODE macro x
	exitm<MAKE_HRESULT(0, FACILITY_ITF, x)>
	endm
MS_S_PENDING		equ MS_SUCCESS_CODE(1)
MS_S_NOUPDATE		equ MS_SUCCESS_CODE(2)
MS_S_ENDOFSTREAM	equ MS_SUCCESS_CODE(3)
MS_E_SAMPLEALLOC	equ MS_ERROR_CODE(1)
MS_E_PURPOSEID		equ MS_ERROR_CODE(2)
MS_E_NOSTREAM		equ MS_ERROR_CODE(3)
MS_E_NOSEEKING		equ MS_ERROR_CODE(4)
MS_E_INCOMPATIBLE	equ MS_ERROR_CODE(5)
MS_E_BUSY		equ MS_ERROR_CODE(6)
MS_E_NOTINIT		equ MS_ERROR_CODE(7)
MS_E_SOURCEALREADYDEFINED equ MS_ERROR_CODE(8)
MS_E_INVALIDSTREAMTYPE	equ MS_ERROR_CODE(9)
MS_E_NOTRUNNING		equ MS_ERROR_CODE(10)

DEFINE_GUID(MSPID_PrimaryVideo, 0xa35ff56a, 0x9fda, 0x11d0, 0x8f, 0xdf, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d)
DEFINE_GUID(MSPID_PrimaryAudio, 0xa35ff56b, 0x9fda, 0x11d0, 0x8f, 0xdf, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d)
if(_WIN32_WINNT LT 0x0400)
CALLBACK(PAPCFUNC, :DWORD_PTR)
endif
STREAM_TIME		typedef LONGLONG
MSPID			typedef GUID
REFMSPID		typedef REFGUID

STREAM_TYPE typedef SDWORD
STREAMTYPE_READ		equ 0
STREAMTYPE_WRITE	equ 1
STREAMTYPE_TRANSFORM	equ 2

STREAM_STATE typedef SDWORD
STREAMSTATE_STOP	equ 0
STREAMSTATE_RUN		equ 1

COMPLETION_STATUS_FLAGS typedef SDWORD
COMPSTAT_NOUPDATEOK	equ 0x1
COMPSTAT_WAIT		equ 0x2
COMPSTAT_ABORT		equ 0x4

MMSSF_HASCLOCK		equ 0x1
MMSSF_SUPPORTSEEK	equ 0x2
MMSSF_ASYNCHRONOUS	equ 0x4

SSUPDATE_ASYNC		equ 0x1
SSUPDATE_CONTINUOUS	equ 0x2

ifndef __IMultiMediaStream_INTERFACE_DEFINED__
define __IMultiMediaStream_INTERFACE_DEFINED__

DEFINE_IIDX(IMultiMediaStream, "B502D1BC-9A57-11d0-8FDE-00C04FD9189D")

.comdef IMultiMediaStream : public IUnknown

    GetInformation	proc :ptr, :ptr
    GetMediaStream	proc :REFMSPID, :ptr
    EnumMediaStreams	proc :LONG, :ptr
    GetState		proc :ptr
    SetState		proc :STREAM_STATE
    GetTime		proc :ptr
    GetDuration		proc :ptr
    Seek		proc :STREAM_TIME
    GetEndOfStreamEventHandle proc :ptr
   .ends

endif

ifndef __IMediaStream_INTERFACE_DEFINED__
define __IMediaStream_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaStream, "B502D1BD-9A57-11d0-8FDE-00C04FD9189D")

.comdef IMediaStream : public IUnknown

    GetMultiMediaStream proc :ptr
    GetInformation	proc :ptr, :ptr
    SetSameFormat	proc :ptr, :DWORD
    AllocateSample	proc :DWORD, :ptr
    CreateSharedSample	proc :ptr, :DWORD, :ptr
    SendEndOfStream	proc :DWORD
   .ends

endif

ifndef __IStreamSample_INTERFACE_DEFINED__
define __IStreamSample_INTERFACE_DEFINED__

DEFINE_IIDX(IStreamSample, "B502D1BE-9A57-11d0-8FDE-00C04FD9189D")

.comdef IStreamSample : public IUnknown

    GetMediaStream	proc :ptr
    GetSampleTimes	proc :ptr, :ptr, :ptr
    SetSampleTimes	proc :ptr, :ptr
    Update		proc :DWORD, :HANDLE, :PAPCFUNC, :DWORD_PTR
    CompletionStatus	proc :DWORD, :DWORD
   .ends

endif

endif
