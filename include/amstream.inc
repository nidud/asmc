.pragma list(push, 0)
ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __amstream_h__
define __amstream_h__

ifndef __unknwn_h__
include unknwn.inc
endif
include mmstream.inc
include strmif.inc
include ddraw.inc
;include mmsystem.inc
;include mmstream.inc
;include ddstream.inc
;include austream.inc

.enum {
    AMMSF_NOGRAPHTHREAD = 0x1
}

.enum {
    AMMSF_ADDDEFAULTRENDERER = 0x1,
    AMMSF_CREATEPEER	= 0x2,
    AMMSF_STOPIFNOSAMPLES = 0x4,
    AMMSF_NOSTALL	= 0x8
}

.enum {
    AMMSF_RENDERTYPEMASK = 0x3,
    AMMSF_RENDERTOEXISTING = 0,
    AMMSF_RENDERALLSTREAMS = 0x1,
    AMMSF_NORENDER	= 0x2,
    AMMSF_NOCLOCK	= 0x4,
    AMMSF_RUN		= 0x8
}

.enum OUTPUT_STATE {
    Disabled		= 0,
    ReadData		= 1,
    RenderData		= 2
}

ifndef __IAMMultiMediaStream_INTERFACE_DEFINED__
define __IAMMultiMediaStream_INTERFACE_DEFINED__

DEFINE_IIDX(IAMMultiMediaStream, "BEBE595C-9A6F-11d0-8FDE-00C04FD9189D")

.comdef IAMMultiMediaStream : public IMultiMediaStream

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
define __IAMMediaStream_INTERFACE_DEFINED__

DEFINE_IIDX(IAMMediaStream, "BEBE595D-9A6F-11d0-8FDE-00C04FD9189D")

.comdef IAMMediaStream : public IMediaStream

    Initialize		proc :ptr, :DWORD, :REFMSPID, :STREAM_TYPE
    SetState		proc :FILTER_STATE
    JoinAMMultiMediaStream proc :ptr
    JoinFilter		proc :ptr
    JoinFilterGraph	proc :ptr
   .ends

endif

ifndef __IMediaStreamFilter_INTERFACE_DEFINED__
define __IMediaStreamFilter_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaStreamFilter, "BEBE595E-9A6F-11d0-8FDE-00C04FD9189D")

.comdef IMediaStreamFilter : public IBaseFilter

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
define __IDirectDrawMediaSampleAllocator_INTERFACE_DEFINED__

DEFINE_IIDX(IDirectDrawMediaSampleAllocator, "AB6B4AFC-F6E4-11d0-900D-00C04FD9189D")

.comdef IDirectDrawMediaSampleAllocator : public IUnknown

    GetDirectDraw	proc :ptr
   .ends

endif

ifndef __IDirectDrawMediaSample_INTERFACE_DEFINED__
define __IDirectDrawMediaSample_INTERFACE_DEFINED__

DEFINE_IIDX(IDirectDrawMediaSample, "AB6B4AFE-F6E4-11d0-900D-00C04FD9189D")

.comdef IDirectDrawMediaSample : public IUnknown

    GetSurfaceAndReleaseLock proc :ptr, :ptr
    LockMediaSamplePointer proc
   .ends

endif

ifndef __IAMMediaTypeStream_INTERFACE_DEFINED__
define __IAMMediaTypeStream_INTERFACE_DEFINED__

DEFINE_IIDX(IAMMediaTypeStream, "AB6B4AFA-F6E4-11d0-900D-00C04FD9189D")

.comdef IAMMediaTypeStream : public IMediaStream

    GetFormat		proc :ptr, :DWORD
    SetFormat		proc :ptr, :DWORD
    CreateSample	proc :LONG, :ptr, :DWORD, :ptr, :ptr
    GetStreamAllocatorRequirements proc :ptr
    SetStreamAllocatorRequirements proc :ptr
   .ends

endif

ifndef __IAMMediaTypeSample_INTERFACE_DEFINED__
define __IAMMediaTypeSample_INTERFACE_DEFINED__

DEFINE_IIDX(IAMMediaTypeSample, "AB6B4AFB-F6E4-11d0-900D-00C04FD9189D")

.comdef IAMMediaTypeSample : public IStreamSample

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
