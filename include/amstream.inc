.pragma list(push, 0)

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
ifndef __amstream_h__
__amstream_h__ equ <>

ifndef __IAMMultiMediaStream_FWD_DEFINED__
__IAMMultiMediaStream_FWD_DEFINED__ equ 1
endif
ifndef __IAMMediaStream_FWD_DEFINED__
__IAMMediaStream_FWD_DEFINED__ equ 1
endif
ifndef __IMediaStreamFilter_FWD_DEFINED__
__IMediaStreamFilter_FWD_DEFINED__ equ 1
endif
ifndef __IDirectDrawMediaSampleAllocator_FWD_DEFINED__
__IDirectDrawMediaSampleAllocator_FWD_DEFINED__ equ 1
endif
ifndef __IDirectDrawMediaSample_FWD_DEFINED__
__IDirectDrawMediaSample_FWD_DEFINED__ equ 1
endif
ifndef __IAMMediaTypeStream_FWD_DEFINED__
__IAMMediaTypeStream_FWD_DEFINED__ equ 1
endif
ifndef __IAMMediaTypeSample_FWD_DEFINED__
__IAMMediaTypeSample_FWD_DEFINED__ equ 1
endif
include unknwn.inc
include mmstream.inc
include strmif.inc
include ddraw.inc
;include mmsystem.inc
;include mmstream.inc
;include ddstream.inc
;include austream.inc

AMMSF_NOGRAPHTHREAD	equ 0x1

AMMSF_ADDDEFAULTRENDERER equ 0x1
AMMSF_CREATEPEER	equ 0x2
AMMSF_STOPIFNOSAMPLES	equ 0x4
AMMSF_NOSTALL		equ 0x8

AMMSF_RENDERTYPEMASK	equ 0x3
AMMSF_RENDERTOEXISTING	equ 0
AMMSF_RENDERALLSTREAMS	equ 0x1
AMMSF_NORENDER		equ 0x2
AMMSF_NOCLOCK		equ 0x4
AMMSF_RUN		equ 0x8

OUTPUT_STATE		typedef SDWORD
Disabled		equ 0
ReadData		equ 1
RenderData		equ 2

ifndef __IAMMultiMediaStream_INTERFACE_DEFINED__
__IAMMultiMediaStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAMMultiMediaStream, "BEBE595C-9A6F-11d0-8FDE-00C04FD9189D")

.comdef IAMMultiMediaStream

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetInformation	proc :ptr, :ptr
    GetMediaStream	proc :REFMSPID, :ptr
    EnumMediaStreams	proc :LONG, :ptr
    GetState		proc :ptr
    SetState		proc :STREAM_STATE
    GetTime		proc :ptr
    GetDuration		proc :ptr
    Seek		proc :STREAM_TIME
    GetEndOfStreamEventHandle proc :ptr
    Initialize		proc :STREAM_TYPE, :DWORD, :ptr
    GetFilterGraph	proc :ptr
    GetFilter		proc :ptr
    AddMediaStream	proc :ptr, :ptr, :DWORD, :ptr
    OpenFile		proc :LPCWSTR, :DWORD
    OpenMoniker		proc :ptr, :ptr, :DWORD
    Render		proc :DWORD
    .ends

endif

ifndef __IAMMediaStream_INTERFACE_DEFINED__
__IAMMediaStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAMMediaStream, "BEBE595D-9A6F-11d0-8FDE-00C04FD9189D")

.comdef IAMMediaStream

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMultiMediaStream proc :ptr
    GetInformation	proc :ptr, :ptr
    SetSameFormat	proc :ptr, :DWORD
    AllocateSample	proc :DWORD, :ptr
    CreateSharedSample	proc :ptr, :DWORD, :ptr
    SendEndOfStream	proc :DWORD
    Initialize		proc :ptr, :DWORD, :REFMSPID, :STREAM_TYPE
    SetState		proc :FILTER_STATE
    JoinAMMultiMediaStream proc :ptr
    JoinFilter		proc :ptr
    JoinFilterGraph	proc :ptr
    .ends

endif

ifndef __IMediaStreamFilter_INTERFACE_DEFINED__
__IMediaStreamFilter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMediaStreamFilter, "BEBE595E-9A6F-11d0-8FDE-00C04FD9189D")

.comdef IMediaStreamFilter

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
    AddMediaStream	proc :ptr
    GetMediaStream	proc :REFMSPID, :ptr
    EnumMediaStreams	proc :LONG, :ptr
    SupportSeeking	proc :BOOL
    ReferenceTimeToStreamTime proc :ptr
    GetCurrentStreamTime proc :ptr
    WaitUntil		proc :REFERENCE_TIME
    Flush		proc :BOOL
    EndOfStream		proc
    .ends

endif

ifndef __IDirectDrawMediaSampleAllocator_INTERFACE_DEFINED__
__IDirectDrawMediaSampleAllocator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectDrawMediaSampleAllocator, "AB6B4AFC-F6E4-11d0-900D-00C04FD9189D")

.comdef IDirectDrawMediaSampleAllocator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDirectDraw	proc :ptr
    .ends

endif

ifndef __IDirectDrawMediaSample_INTERFACE_DEFINED__
__IDirectDrawMediaSample_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectDrawMediaSample, "AB6B4AFE-F6E4-11d0-900D-00C04FD9189D")

.comdef IDirectDrawMediaSample

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetSurfaceAndReleaseLock proc :ptr, :ptr
    LockMediaSamplePointer proc
    .ends

endif

ifndef __IAMMediaTypeStream_INTERFACE_DEFINED__
__IAMMediaTypeStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAMMediaTypeStream, "AB6B4AFA-F6E4-11d0-900D-00C04FD9189D")

.comdef IAMMediaTypeStream

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMultiMediaStream proc :ptr
    GetInformation	proc :ptr, :ptr
    SetSameFormat	proc :ptr, :DWORD
    AllocateSample	proc :DWORD, :ptr
    CreateSharedSample	proc :ptr, :DWORD, :ptr
    SendEndOfStream	proc :DWORD
    GetFormat		proc :ptr, :DWORD
    SetFormat		proc :ptr, :DWORD
    CreateSample	proc :LONG, :ptr, :DWORD, :ptr, :ptr
    GetStreamAllocatorRequirements proc :ptr
    SetStreamAllocatorRequirements proc :ptr
    .ends

endif

ifndef __IAMMediaTypeSample_INTERFACE_DEFINED__
__IAMMediaTypeSample_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAMMediaTypeSample, "AB6B4AFB-F6E4-11d0-900D-00C04FD9189D")

.comdef IAMMediaTypeSample

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMediaStream	proc :ptr
    GetSampleTimes	proc :ptr, :ptr, :ptr
    SetSampleTimes	proc :ptr, :ptr
    Update		proc :DWORD, :HANDLE, :PAPCFUNC, :DWORD_PTR
    CompletionStatus	proc :DWORD, :DWORD
    SetPointer		proc :ptr, :LONG
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

DEFINE_GUID(CLSID_AMMultiMediaStream, 0x49c47ce5, 0x9ba4, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45)
DEFINE_GUID(CLSID_AMDirectDrawStream, 0x49c47ce4, 0x9ba4, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45)
DEFINE_GUID(CLSID_AMAudioStream, 0x8496e040, 0xaf4c, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45)
DEFINE_GUID(CLSID_AMAudioData, 0xf2468580, 0xaf8a, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45)
DEFINE_GUID(CLSID_AMMediaTypeStream, 0xcf0f2f7c, 0xf7bf, 0x11d0, 0x90, 0xd, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d)

endif

.pragma list(pop)
