ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __strmif_h__
define __strmif_h__
ifndef __unknwn_h__
include unknwn.inc
endif
include objidl.inc
ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif

define CDEF_CLASS_DEFAULT		0x0001
define CDEF_BYPASS_CLASS_MANAGER	0x0002
define CDEF_MERIT_ABOVE_DO_NOT_USE	0x0008
define CDEF_DEVMON_CMGR_DEVICE		0x0010
define CDEF_DEVMON_DMO			0x0020
define CDEF_DEVMON_PNP_DEVICE		0x0040
define CDEF_DEVMON_FILTER		0x0080
define CDEF_DEVMON_SELECTIVE_MASK	0x00f0

ifndef __ICreateDevEnum_INTERFACE_DEFINED__
define __ICreateDevEnum_INTERFACE_DEFINED__

DEFINE_IIDX(ICreateDevEnum,"29840822-5B84-11D0-BD3B-00A0C911CE86")

.comdef ICreateDevEnum : public IUnknown

    CreateClassEnumerator proc :REFCLSID, :ptr, :DWORD
   .ends

endif

define CHARS_IN_GUID	39

AM_MEDIA_TYPE		STRUC
majortype		GUID <>
subtype			GUID <>
bFixedSizeSamples	BOOL ?
bTemporalCompression	BOOL ?
lSampleSize		ULONG ?
formattype		GUID <>
pUnk			LPUNKNOWN ?
cbFormat		ULONG ?
pbFormat		LPBYTE ?
AM_MEDIA_TYPE		ENDS
PAM_MEDIA_TYPE		typedef ptr AM_MEDIA_TYPE

.enum PIN_DIRECTION {
    PINDIR_INPUT,
    PINDIR_OUTPUT
    }

define MAX_PIN_NAME	128
define MAX_FILTER_NAME	128

REFERENCE_TIME		typedef LONGLONG
REFTIME			typedef REAL8
HSEMAPHORE		typedef DWORD_PTR
HEVENT			typedef DWORD_PTR

ALLOCATOR_PROPERTIES	STRUC
cBuffers		LONG ?
cbBuffer		LONG ?
cbAlign			LONG ?
cbPrefix		LONG ?
ALLOCATOR_PROPERTIES	ENDS

ifndef __IPin_INTERFACE_DEFINED__
define __IPin_INTERFACE_DEFINED__

PIN_INFO		STRUC
pFilter			PVOID ?
dir			PIN_DIRECTION ?
achName			WCHAR  128  dup(?)
PIN_INFO		ENDS

DEFINE_IIDX(IPin, "56a86891-0ad4-11ce-b03a-0020af0ba770")

.comdef IPin : public IUnknown

    Connect		proc :ptr, :ptr
    ReceiveConnection	proc :ptr, :ptr
    Disconnect		proc
    ConnectedTo		proc :ptr
    ConnectionMediaType proc :ptr
    QueryPinInfo	proc :ptr
    QueryDirection	proc :ptr
    QueryId		proc :ptr
    QueryAccept		proc :ptr
    EnumMediaTypes	proc :ptr
    QueryInternalConnections proc :ptr, :ptr
    EndOfStream		proc
    BeginFlush		proc
    EndFlush		proc
    NewSegment		proc :REFERENCE_TIME, :REFERENCE_TIME, :REAL8
   .ends

endif

PPIN			typedef ptr IPin

ifndef __IEnumPins_INTERFACE_DEFINED__
define __IEnumPins_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumPins, "56a86892-0ad4-11ce-b03a-0020af0ba770")

.comdef IEnumPins : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

PENUMPINS		typedef ptr IEnumPins

ifndef __IEnumMediaTypes_INTERFACE_DEFINED__
define __IEnumMediaTypes_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumMediaTypes, "89c31040-846b-11ce-97d3-00aa0055595a")

.comdef IEnumMediaTypes : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

PENUMMEDIATYPES		typedef ptr IEnumMediaTypes

ifndef __IFilterGraph_INTERFACE_DEFINED__
define __IFilterGraph_INTERFACE_DEFINED__

DEFINE_IIDX(IFilterGraph, "56a8689f-0ad4-11ce-b03a-0020af0ba770")

.comdef IFilterGraph : public IUnknown

    AddFilter		proc :ptr, :LPCWSTR
    RemoveFilter	proc :ptr
    EnumFilters		proc :ptr
    FindFilterByName	proc :LPCWSTR, :ptr
    ConnectDirect	proc :ptr, :ptr, :ptr
    Reconnect		proc :ptr
    Disconnect		proc :ptr
    SetDefaultSyncSource proc
   .ends

PFILTERGRAPH		typedef ptr IFilterGraph

endif

ifndef __IEnumFilters_INTERFACE_DEFINED__
define __IEnumFilters_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumFilters, "56a86893-0ad4-11ce-b03a-0020af0ba770")

.comdef IEnumFilters : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

PENUMFILTERS		typedef ptr IEnumFilters

endif

ifndef __IMediaFilter_INTERFACE_DEFINED__
define __IMediaFilter_INTERFACE_DEFINED__

.enum FILTER_STATE {
    State_Stopped = 0,
    State_Paused  = ( State_Stopped + 1 ),
    State_Running = ( State_Paused + 1 )
    }

DEFINE_IIDX(IMediaFilter, "56a86899-0ad4-11ce-b03a-0020af0ba770")

.comdef IMediaFilter : public IPersist

    Stop		proc
    _Pause		proc
    Run			proc :REFERENCE_TIME
    GetState		proc :DWORD, :ptr
    SetSyncSource	proc :ptr
    GetSyncSource	proc :ptr
   .ends

PMEDIAFILTER		typedef ptr IMediaFilter

endif

ifndef __IBaseFilter_INTERFACE_DEFINED__
define __IBaseFilter_INTERFACE_DEFINED__

FILTER_INFO		STRUC
achName			dw 128 dup(?)
pGraph			PFILTERGRAPH ?
FILTER_INFO		ENDS

DEFINE_IIDX(IBaseFilter, "56a86895-0ad4-11ce-b03a-0020af0ba770")

.comdef IBaseFilter : public IMediaFilter

    EnumPins		proc :ptr
    FindPin		proc :LPCWSTR, :ptr
    QueryFilterInfo	proc :ptr
    JoinFilterGraph	proc :ptr, :LPCWSTR
    QueryVendorInfo	proc :ptr
   .ends

PFILTER			typedef ptr IBaseFilter

endif

ifndef __IReferenceClock_INTERFACE_DEFINED__
define __IReferenceClock_INTERFACE_DEFINED__

DEFINE_IIDX(IReferenceClock, "56a86897-0ad4-11ce-b03a-0020af0ba770")

.comdef IReferenceClock : public IUnknown

    GetTime		proc :ptr
    AdviseTime		proc :REFERENCE_TIME, :REFERENCE_TIME, :HEVENT, :ptr
    AdvisePeriodic	proc :REFERENCE_TIME, :REFERENCE_TIME, :HSEMAPHORE, :ptr
    Unadvise		proc :DWORD_PTR
   .ends

PREFERENCECLOCK		typedef ptr IReferenceClock

endif

ifndef __IReferenceClockTimerControl_INTERFACE_DEFINED__
define __IReferenceClockTimerControl_INTERFACE_DEFINED__

DEFINE_IIDX(IReferenceClockTimerControl, "ebec459c-2eca-4d42-a8af-30df557614b8")

.comdef IReferenceClockTimerControl : public IUnknown

    SetDefaultTimerResolution proc :REFERENCE_TIME
    GetDefaultTimerResolution proc :ptr
   .ends

endif

ifndef __IReferenceClock2_INTERFACE_DEFINED__
define __IReferenceClock2_INTERFACE_DEFINED__

DEFINE_IIDX(IReferenceClock2, "36b73885-c2c8-11cf-8b46-00805f6cef60")

.comdef IReferenceClock2 : public IReferenceClock
   .ends

PREFERENCECLOCK2	typedef ptr IReferenceClock2

endif

ifndef __IMediaSample_INTERFACE_DEFINED__
define __IMediaSample_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaSample, "56a8689a-0ad4-11ce-b03a-0020af0ba770")

.comdef IMediaSample : public IUnknown

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

PMEDIASAMPLE		typedef ptr IMediaSample

endif

.enum AM_SAMPLE_PROPERTY_FLAGS {
	AM_SAMPLE_SPLICEPOINT	= 0x1,
	AM_SAMPLE_PREROLL	= 0x2,
	AM_SAMPLE_DATADISCONTINUITY	= 0x4,
	AM_SAMPLE_TYPECHANGED	= 0x8,
	AM_SAMPLE_TIMEVALID	= 0x10,
	AM_SAMPLE_TIMEDISCONTINUITY	= 0x40,
	AM_SAMPLE_FLUSH_ON_PAUSE	= 0x80,
	AM_SAMPLE_STOPVALID	= 0x100,
	AM_SAMPLE_ENDOFSTREAM	= 0x200,
	AM_STREAM_MEDIA = 0,
	AM_STREAM_CONTROL	= 1
	}

AM_SAMPLE2_PROPERTIES	STRUC
cbData			dd ?
dwTypeSpecificFlags	dd ?
dwSampleFlags		dd ?
lActual			LONG ?
tStart			REFERENCE_TIME ?
tStop			REFERENCE_TIME ?
dwStreamId		dd ?
pMediaType		PAM_MEDIA_TYPE ?
pbBuffer		LPBYTE ?
cbBuffer		LONG ?
AM_SAMPLE2_PROPERTIES	ENDS

ifndef __IMediaSample2_INTERFACE_DEFINED__
define __IMediaSample2_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaSample2, "36b73884-c2c8-11cf-8b46-00805f6cef60")

.comdef IMediaSample2 : public IMediaSample

    GetProperties	proc :DWORD, :ptr
    SetProperties	proc :DWORD, :ptr
   .ends

PMEDIASAMPLE2		typedef ptr IMediaSample2

endif

ifndef __IMediaSample2Config_INTERFACE_DEFINED__
define __IMediaSample2Config_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaSample2Config, "68961E68-832B-41ea-BC91-63593F3E70E3")

.comdef IMediaSample2Config : public IUnknown

    GetSurface		proc :ptr
   .ends

endif

define AM_GBF_PREVFRAMESKIPPED	1
define AM_GBF_NOTASYNCPOINT	2
define AM_GBF_NOWAIT		4
define AM_GBF_NODDSURFACELOCK	8

ifndef __IMemAllocator_INTERFACE_DEFINED__
define __IMemAllocator_INTERFACE_DEFINED__

DEFINE_IIDX(IMemAllocator, "56a8689c-0ad4-11ce-b03a-0020af0ba770")

.comdef IMemAllocator : public IUnknown

    SetProperties	proc :ptr, :ptr
    GetProperties	proc :ptr
    Commit		proc
    Decommit		proc
    GetBuffer		proc :ptr, :ptr, :ptr, :DWORD
    ReleaseBuffer	proc :ptr
   .ends

PMEMALLOCATOR		typedef ptr IMemAllocator

endif

ifndef __IMemAllocatorCallbackTemp_INTERFACE_DEFINED__
define __IMemAllocatorCallbackTemp_INTERFACE_DEFINED__

DEFINE_IIDX(IMemAllocatorCallbackTemp, "379a0cf0-c1de-11d2-abf5-00a0c905f375")

.comdef IMemAllocatorCallbackTemp : public IMemAllocator

    SetNotify		proc :ptr
    GetFreeCount	proc :ptr
   .ends

endif

ifndef __IMemAllocatorNotifyCallbackTemp_INTERFACE_DEFINED__
define __IMemAllocatorNotifyCallbackTemp_INTERFACE_DEFINED__

DEFINE_IIDX(IMemAllocatorNotifyCallbackTemp, "92980b30-c1de-11d2-abf5-00a0c905f375")

.comdef IMemAllocatorNotifyCallbackTemp : public IUnknown

    NotifyRelease	proc
   .ends

endif

ifndef __IMemInputPin_INTERFACE_DEFINED__
define __IMemInputPin_INTERFACE_DEFINED__

DEFINE_IIDX(IMemInputPin, "56a8689d-0ad4-11ce-b03a-0020af0ba770")

.comdef IMemInputPin : public IUnknown

    GetAllocator	proc :ptr
    NotifyAllocator	proc :ptr, :BOOL
    GetAllocatorRequirements proc :ptr
    Receive		proc :ptr
    ReceiveMultiple	proc
    ReceiveCanBlock	proc
   .ends

PMEMINPUTPIN		typedef ptr IMemInputPin

endif

ifndef __IAMovieSetup_INTERFACE_DEFINED__
define __IAMovieSetup_INTERFACE_DEFINED__

DEFINE_IIDX(IAMovieSetup, "a3d8cec0-7e5a-11cf-bbc5-00805f6cef20")

.comdef IAMovieSetup : public IUnknown

    Register		proc
    Unregister		proc
   .ends

PAMOVIESETUP		typedef ptr IAMovieSetup

endif

.enum AM_SEEKING_SEEKING_FLAGS {
	AM_SEEKING_NoPositioning	= 0,
	AM_SEEKING_AbsolutePositioning	= 0x1,
	AM_SEEKING_RelativePositioning	= 0x2,
	AM_SEEKING_IncrementalPositioning = 0x3,
	AM_SEEKING_PositioningBitsMask	= 0x3,
	AM_SEEKING_SeekToKeyFrame	= 0x4,
	AM_SEEKING_ReturnTime		= 0x8,
	AM_SEEKING_Segment		= 0x10,
	AM_SEEKING_NoFlush		= 0x20
	}

.enum AM_SEEKING_SEEKING_CAPABILITIES {
	AM_SEEKING_CanSeekAbsolute	= 0x1,
	AM_SEEKING_CanSeekForwards	= 0x2,
	AM_SEEKING_CanSeekBackwards	= 0x4,
	AM_SEEKING_CanGetCurrentPos	= 0x8,
	AM_SEEKING_CanGetStopPos	= 0x10,
	AM_SEEKING_CanGetDuration	= 0x20,
	AM_SEEKING_CanPlayBackwards	= 0x40,
	AM_SEEKING_CanDoSegments	= 0x80,
	AM_SEEKING_Source		= 0x100
	}

ifndef __IMediaSeeking_INTERFACE_DEFINED__
define __IMediaSeeking_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaSeeking, "36b73880-c2c8-11cf-8b46-00805f6cef60")

.comdef IMediaSeeking : public IUnknown

    GetCapabilities	proc :ptr
    CheckCapabilities	proc :ptr
    IsFormatSupported	proc :ptr
    QueryPreferredFormat proc :ptr
    GetTimeFormat	proc :ptr
    IsUsingTimeFormat	proc :ptr
    SetTimeFormat	proc :ptr
    GetDuration		proc :ptr
    GetStopPosition	proc :ptr
    GetCurrentPosition	proc :ptr
    ConvertTimeFormat	proc :ptr, :ptr, :LONGLONG, :ptr
    SetPositions	proc :ptr, :DWORD, :ptr, :DWORD
    GetPositions	proc :ptr, :ptr
    GetAvailable	proc :ptr, :ptr
    SetRate		proc :REAL8
    GetRate		proc :ptr
    GetPreroll		proc :ptr
   .ends

PMEDIASEEKING		typedef ptr IMediaSeeking

endif

.enum AM_MEDIAEVENT_FLAGS {
	AM_MEDIAEVENT_NONOTIFY	= 0x01
	}

REGFILTER		STRUC
Clsid			CLSID <>
Name			LPWSTR ?
REGFILTER		ENDS

ifndef __IEnumRegFilters_INTERFACE_DEFINED__
define __IEnumRegFilters_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumRegFilters, "901db4c7-31ce-41a2-85dc-8fa0bf41b8da")

.comdef IEnumRegFilters : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

PENUMREGFILTERS		typedef ptr IEnumRegFilters

endif

ifndef __IFilterMapper_INTERFACE_DEFINED__
define __IFilterMapper_INTERFACE_DEFINED__

.enum __MIDL_IFilterMapper_0001 {
	MERIT_PREFERRED		= 0x800000,
	MERIT_NORMAL		= 0x600000,
	MERIT_UNLIKELY		= 0x400000,
	MERIT_DO_NOT_USE	= 0x200000,
	MERIT_SW_COMPRESSOR	= 0x100000,
	MERIT_HW_COMPRESSOR	= 0x100050
	}

DEFINE_IIDX(IFilterMapper, "56a868a4-0ad4-11ce-b03a-0020af0ba770")

.comdef IFilterMapper : public IUnknown

    RegisterFilter	proc :CLSID, :LPCWSTR, :DWORD
    RegisterFilterInstance proc :CLSID, :LPCWSTR, :ptr
    RegisterPin		proc :CLSID, :LPCWSTR, :BOOL, :BOOL, :BOOL, :BOOL, :CLSID, :LPCWSTR
    RegisterPinType	proc :CLSID, :LPCWSTR, :CLSID, :CLSID
    UnregisterFilter	proc :CLSID
    UnregisterFilterInstance proc :CLSID
    UnregisterPin	proc :CLSID, :LPCWSTR
    EnumMatchingFilters proc :ptr, :DWORD, :BOOL, :CLSID, :CLSID, :BOOL, :BOOL, :CLSID, :CLSID
   .ends

endif

REGPINTYPES		STRUC
clsMajorType		LPCLSID ?
clsMinorType		LPCLSID ?
REGPINTYPES		ENDS
PREGPINTYPES		typedef ptr REGPINTYPES

REGFILTERPINS		STRUC
strName			LPWSTR ?
bRendered		BOOL ?
bOutput			BOOL ?
bZero			BOOL ?
bMany			BOOL ?
clsConnectsToFilter	LPCLSID ?
strConnectsToPin	LPWSTR ?
nMediaTypes		UINT ?
lpMediaType		PREGPINTYPES ?
REGFILTERPINS		ENDS
PREGFILTERPINS		typedef ptr REGFILTERPINS

REGPINMEDIUM		STRUC
clsMedium		CLSID <>
dw1			dd ?
dw2			dd ?
REGPINMEDIUM		ENDS
PREGPINMEDIUM		typedef ptr REGPINMEDIUM

.enum __MIDL___MIDL_itf_strmif_0000_0023_0001 {
	REG_PINFLAG_B_ZERO	= 0x1,
	REG_PINFLAG_B_RENDERER	= 0x2,
	REG_PINFLAG_B_MANY	= 0x4,
	REG_PINFLAG_B_OUTPUT	= 0x8
	}

REGFILTERPINS2		STRUC
dwFlags			dd ?
cInstances		UINT ?
nMediaTypes		UINT ?
lpMediaType		PREGPINTYPES ?
nMediums		UINT ?
lpMedium		PREGPINMEDIUM ?
clsPinCategory		LPCLSID ?
REGFILTERPINS2		ENDS
PREGFILTERPINS2		typedef ptr REGFILTERPINS2

REGFILTER2		STRUC
dwVersion		dd ?
dwMerit			dd ?
UNION
 STRUC
  cPins			ULONG ?
  rgPins		PREGFILTERPINS ?
 ENDS
 STRUC
  cPins2		ULONG ?
  rgPins2		PREGFILTERPINS2 ?
 ENDS
ENDS
REGFILTER2		ENDS

ifndef __IFilterMapper2_INTERFACE_DEFINED__
define __IFilterMapper2_INTERFACE_DEFINED__

DEFINE_IIDX(IFilterMapper2, "56a868a3-0ad4-11ce-b03a-0020af0ba770")

.comdef IFilterMapper2 : public IUnknown

    CreateCategory	proc :REFCLSID, :DWORD, :LPCWSTR
    UnregisterFilter	proc :ptr, :LPCOLESTR, :REFCLSID
    RegisterFilter	proc :REFCLSID, :LPCWSTR, :ptr, :ptr, :LPCOLESTR, :ptr
    EnumMatchingFilters proc :ptr, :DWORD, :BOOL, :DWORD, :BOOL, :DWORD, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IFilterMapper3_INTERFACE_DEFINED__
define __IFilterMapper3_INTERFACE_DEFINED__

DEFINE_IIDX(IFilterMapper3, "b79bb0b0-33c1-11d1-abe1-00a0c905f375")

.comdef IFilterMapper3 : public IFilterMapper2

    GetICreateDevEnum	proc :ptr
   .ends

endif

.enum QualityMessageType {
	Famine,
	Flood
	}

Quality			STRUC
Type			QualityMessageType ?
Proportion		LONG ?
Late			REFERENCE_TIME ?
TimeStamp		REFERENCE_TIME ?
Quality			ENDS

ifndef __IQualityControl_INTERFACE_DEFINED__
define __IQualityControl_INTERFACE_DEFINED__

DEFINE_IIDX(IQualityControl, "56a868a5-0ad4-11ce-b03a-0020af0ba770")

.comdef IQualityControl : public IUnknown

    Notify		proc :ptr, :Quality
    SetSink		proc :ptr
   .ends

PQUALITYCONTROL		typedef ptr IQualityControl

endif

.enum __MIDL___MIDL_itf_strmif_0000_0026_0001 {
	CK_NOCOLORKEY	= 0,
	CK_INDEX	= 0x1,
	CK_RGB		= 0x2
	}

COLORKEY		STRUC
KeyType			dd ?
PaletteIndex		dd ?
LowColorValue		COLORREF ?
HighColorValue		COLORREF ?
COLORKEY		ENDS

.enum _MIDL___MIDL_itf_strmif_0000_0025_0002 {
	ADVISE_NONE		= 0,
	ADVISE_CLIPPING		= 0x1,
	ADVISE_PALETTE		= 0x2,
	ADVISE_COLORKEY		= 0x4,
	ADVISE_POSITION		= 0x8,
	ADVISE_DISPLAY_CHANGE	= 0x10,
	ADVISE_ALL		= ADVISE_CLIPPING OR ADVISE_PALETTE OR ADVISE_COLORKEY OR ADVISE_POSITION,
	ADVISE_ALL2		= ADVISE_ALL OR ADVISE_DISPLAY_CHANGE
	}

ifndef _WINGDI_
RGNDATAHEADER		STRUC
dwSize			dd ?
iType			dd ?
nCount			dd ?
nRgnSize		dd ?
rcBound			RECT <>
RGNDATAHEADER		ENDS

RGNDATA			STRUC
rdh			RGNDATAHEADER <>
Buffer			sbyte 1 dup(?)
RGNDATA			ENDS

endif

ifndef __IOverlayNotify_INTERFACE_DEFINED__
define __IOverlayNotify_INTERFACE_DEFINED__

DEFINE_IIDX(IOverlayNotify, "56a868a0-0ad4-11ce-b03a-0020af0ba770")

.comdef IOverlayNotify : public IUnknown

    OnPaletteChange	proc :DWORD, :ptr
    OnClipChange	proc :ptr, :ptr, :ptr
    OnColorKeyChange	proc :ptr
    OnPositionChange	proc :ptr, :ptr
   .ends
    POVERLAYNOTIFY	typedef ptr IOverlayNotify
endif

if NOT defined(HMONITOR_DECLARED) AND NOT defined(HMONITOR) AND (WINVER LT 0x0500)
HMONITOR_DECLARED equ 1
if 0
HMONITOR typedef HANDLE
endif
DECLARE_HANDLE(HMONITOR)
endif

ifndef __IOverlayNotify2_INTERFACE_DEFINED__
define __IOverlayNotify2_INTERFACE_DEFINED__

DEFINE_IIDX(IOverlayNotify2, "680EFA10-D535-11D1-87C8-00A0C9223196")

.comdef IOverlayNotify2 : public IOverlayNotify

    OnDisplayChange	proc :HMONITOR
   .ends
    POVERLAYNOTIFY2	typedef ptr IOverlayNotify2
endif

ifndef __IOverlay_INTERFACE_DEFINED__
define __IOverlay_INTERFACE_DEFINED__

DEFINE_IIDX(IOverlay, "56a868a1-0ad4-11ce-b03a-0020af0ba770")

.comdef IOverlay : public IUnknown

    GetPalette		proc :ptr, :ptr
    SetPalette		proc :DWORD, :ptr
    GetDefaultColorKey	proc :ptr
    GetColorKey		proc :ptr
    SetColorKey		proc :ptr
    GetWindowHandle	proc :ptr
    GetClipList		proc :ptr, :ptr, :ptr
    GetVideoPosition	proc :ptr, :ptr
    Advise		proc :ptr, :DWORD
    Unadvise		proc
   .ends
    POVERLAY		typedef ptr IOverlay
endif

ifndef __IMediaEventSink_INTERFACE_DEFINED__
define __IMediaEventSink_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaEventSink, "56a868a2-0ad4-11ce-b03a-0020af0ba770")

.comdef IMediaEventSink : public IUnknown

    Notify		proc :LONG, :LONG_PTR, :LONG_PTR
   .ends

PMEDIAEVENTSINK		typedef ptr IMediaEventSink

endif

ifndef __IFileSourceFilter_INTERFACE_DEFINED__
define __IFileSourceFilter_INTERFACE_DEFINED__

DEFINE_IIDX(IFileSourceFilter, "56a868a6-0ad4-11ce-b03a-0020af0ba770")

.comdef IFileSourceFilter : public IUnknown

    Load		proc :LPCOLESTR, :ptr
    GetCurFile		proc :ptr, :ptr
   .ends
    PFILTERFILESOURCE	typedef ptr IFileSourceFilter
endif

ifndef __IFileSinkFilter_INTERFACE_DEFINED__
define __IFileSinkFilter_INTERFACE_DEFINED__

DEFINE_IIDX(IFileSinkFilter, "a2104830-7c70-11cf-8bce-00aa00a3f1a6")

.comdef IFileSinkFilter : public IUnknown

    SetFileName		proc :LPCOLESTR, :ptr
    GetCurFile		proc :ptr, :ptr
   .ends
    PFILTERFILESINK	typedef ptr IFileSinkFilter
endif

ifndef __IFileSinkFilter2_INTERFACE_DEFINED__
define __IFileSinkFilter2_INTERFACE_DEFINED__

DEFINE_IIDX(IFileSinkFilter2, "00855B90-CE1B-11d0-BD4F-00A0C911CE86")

.comdef IFileSinkFilter2 : public IFileSinkFilter

    SetMode		proc :DWORD
    GetMode		proc :ptr
   .ends
    PFILESINKFILTER2	typedef ptr IFileSinkFilter2
endif

.enum AM_FILESINK_FLAGS {
	AM_FILE_OVERWRITE	= 0x1
	}

ifndef __IGraphBuilder_INTERFACE_DEFINED__
define __IGraphBuilder_INTERFACE_DEFINED__

DEFINE_IIDX(IGraphBuilder, "56a868a9-0ad4-11ce-b03a-0020af0ba770")

.comdef IGraphBuilder : public IFilterGraph

    Connect		proc :ptr, :ptr
    Render		proc :ptr
    RenderFile		proc :LPCWSTR, :LPCWSTR
    AddSourceFilter	proc :LPCWSTR, :LPCWSTR, :ptr
    SetLogFile		proc :DWORD_PTR
    Abort		proc
    ShouldOperationContinue proc
   .ends
endif

ifndef __ICaptureGraphBuilder_INTERFACE_DEFINED__
define __ICaptureGraphBuilder_INTERFACE_DEFINED__

DEFINE_IIDX(ICaptureGraphBuilder, "bf87b6e0-8c27-11d0-b3f0-00aa003761c5")

.comdef ICaptureGraphBuilder : public IUnknown

    SetFiltergraph	proc :ptr
    GetFiltergraph	proc :ptr
    SetOutputFileName	proc :ptr, :LPCOLESTR, :ptr, :ptr
    FindInterface	proc :ptr, :ptr, :REFIID, :ptr
    RenderStream	proc :ptr, :ptr, :ptr, :ptr
    ControlStream	proc :ptr, :ptr, :ptr, :ptr, :WORD, :WORD
    AllocCapFile	proc :LPCOLESTR, :DWORDLONG
    CopyCaptureFile	proc :LPOLESTR, :LPOLESTR, :SINT, :ptr
   .ends

endif

ifndef __IAMCopyCaptureFileProgress_INTERFACE_DEFINED__
define __IAMCopyCaptureFileProgress_INTERFACE_DEFINED__

DEFINE_IIDX(IAMCopyCaptureFileProgress, "670d1d20-a068-11d0-b3f0-00aa003761c5")

.comdef IAMCopyCaptureFileProgress : public IUnknown

    Progress		proc :SINT
   .ends

endif

ifndef __ICaptureGraphBuilder2_INTERFACE_DEFINED__
define __ICaptureGraphBuilder2_INTERFACE_DEFINED__

DEFINE_IIDX(ICaptureGraphBuilder2, "93E5A4E0-2D50-11d2-ABFA-00A0C9C6E38D")

.comdef ICaptureGraphBuilder2 : public IUnknown

    SetFiltergraph	proc :ptr
    GetFiltergraph	proc :ptr
    SetOutputFileName	proc :ptr, :LPCOLESTR, :ptr, :ptr
    FindInterface	proc :ptr, :ptr, :ptr, :REFIID, :ptr
    RenderStream	proc :ptr, :ptr, :ptr, :ptr, :ptr
    ControlStream	proc :ptr, :ptr, :ptr, :ptr, :ptr, :WORD, :WORD
    AllocCapFile	proc :LPCOLESTR, :DWORDLONG
    CopyCaptureFile	proc :LPOLESTR, :LPOLESTR, :SINT, :ptr
    FindPin		proc :ptr, :PIN_DIRECTION, :ptr, :ptr, :BOOL, :SINT, :ptr
   .ends

endif

.enum AM_RENSDEREXFLAGS {
	AM_RENDEREX_RENDERTOEXISTINGRENDERERS = 0x1
	}

ifndef __IFilterGraph2_INTERFACE_DEFINED__
define __IFilterGraph2_INTERFACE_DEFINED__

DEFINE_IIDX(IFilterGraph2, "36b73882-c2c8-11cf-8b46-00805f6cef60")

.comdef IFilterGraph2 : public IGraphBuilder

    AddSourceFilterForMoniker proc :ptr, :ptr, :LPCWSTR, :ptr
    ReconnectEx		proc :ptr, :ptr
    RenderEx		proc :ptr, :DWORD, :ptr
   .ends

endif

ifndef __IFilterGraph3_INTERFACE_DEFINED__
define __IFilterGraph3_INTERFACE_DEFINED__

DEFINE_IIDX(IFilterGraph3, "aaf38154-b80b-422f-91e6-b66467509a07")

.comdef IFilterGraph3 : public IFilterGraph2

    SetSyncSourceEx	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef __IStreamBuilder_INTERFACE_DEFINED__
define __IStreamBuilder_INTERFACE_DEFINED__

DEFINE_IIDX(IStreamBuilder, "56a868bf-0ad4-11ce-b03a-0020af0ba770")

.comdef IStreamBuilder : public IUnknown

    Render		proc :ptr, :ptr
    Backout		proc :ptr, :ptr
   .ends

endif

ifndef __IAsyncReader_INTERFACE_DEFINED__
define __IAsyncReader_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncReader, "56a868aa-0ad4-11ce-b03a-0020af0ba770")

.comdef IAsyncReader : public IUnknown

    RequestAllocator	proc :ptr, :ptr, :ptr
    Request		proc :ptr, :DWORD_PTR
    WaitForNext		proc :DWORD, :ptr, :ptr
    SyncReadAligned	proc :ptr
    SyncRead		proc :LONGLONG, :LONG, :ptr
    Length		proc :ptr, :ptr
    BeginFlush		proc
    EndFlush		proc
   .ends

endif

ifndef __IGraphVersion_INTERFACE_DEFINED__
define __IGraphVersion_INTERFACE_DEFINED__

DEFINE_IIDX(IGraphVersion, "56a868ab-0ad4-11ce-b03a-0020af0ba770")

.comdef IGraphVersion : public IUnknown

    QueryVersion	proc :ptr
   .ends

endif

ifndef __IResourceConsumer_INTERFACE_DEFINED__
define __IResourceConsumer_INTERFACE_DEFINED__

DEFINE_IIDX(IResourceConsumer, "56a868ad-0ad4-11ce-b03a-0020af0ba770")

.comdef IResourceConsumer : public IUnknown

    AcquireResource	proc :LONG
    ReleaseResource	proc :LONG
   .ends

endif

ifndef __IResourceManager_INTERFACE_DEFINED__
define __IResourceManager_INTERFACE_DEFINED__

DEFINE_IIDX(IResourceManager, "56a868ac-0ad4-11ce-b03a-0020af0ba770")

.comdef IResourceManager : public IUnknown

    Register		proc :LPCWSTR, :LONG, :ptr
    RegisterGroup	proc :LPCWSTR, :LONG
    RequestResource	proc :LONG, :ptr, :ptr
    NotifyAcquire	proc :LONG, :ptr, :HRESULT
    NotifyRelease	proc :LONG, :ptr, :BOOL
    CancelRequest	proc :LONG, :ptr
    SetFocus		proc :ptr
    ReleaseFocus	proc :ptr
   .ends

endif

ifndef __IDistributorNotify_INTERFACE_DEFINED__
define __IDistributorNotify_INTERFACE_DEFINED__

DEFINE_IIDX(IDistributorNotify, "56a868af-0ad4-11ce-b03a-0020af0ba770")

.comdef IDistributorNotify : public IUnknown

    Stop		proc
    _Pause		proc
    Run			proc :REFERENCE_TIME
    SetSyncSource	proc :ptr
    NotifyGraphChange	proc
   .ends

endif

.enum AM_STREAM_INFO_FLAGS {
	AM_STREAM_INFO_START_DEFINED	= 0x1,
	AM_STREAM_INFO_STOP_DEFINED	= 0x2,
	AM_STREAM_INFO_DISCARDING	= 0x4,
	AM_STREAM_INFO_STOP_SEND_EXTRA	= 0x10
	}

AM_STREAM_INFO		STRUC
tStart			REFERENCE_TIME ?
tStop			REFERENCE_TIME ?
dwStartCookie		dd ?
dwStopCookie		dd ?
dwFlags			dd ?
AM_STREAM_INFO		ENDS

ifndef __IAMStreamControl_INTERFACE_DEFINED__
define __IAMStreamControl_INTERFACE_DEFINED__

DEFINE_IIDX(IAMStreamControl, "36b73881-c2c8-11cf-8b46-00805f6cef60")

.comdef IAMStreamControl : public IUnknown

    StartAt		proc :ptr, :DWORD
    StopAt		proc :ptr, :BOOL, :DWORD
    GetInfo		proc :ptr
   .ends

endif

ifndef __ISeekingPassThru_INTERFACE_DEFINED__
define __ISeekingPassThru_INTERFACE_DEFINED__

DEFINE_IIDX(ISeekingPassThru, "36b73883-c2c8-11cf-8b46-00805f6cef60")

.comdef ISeekingPassThru : public IUnknown

    Init		proc :BOOL, :ptr
   .ends

endif

ifndef __IAMStreamConfig_INTERFACE_DEFINED__
define __IAMStreamConfig_INTERFACE_DEFINED__

VIDEO_STREAM_CONFIG_CAPS STRUC
guid			GUID <>
VideoStandard		ULONG ?
InputSize		SIZEL <>
MinCroppingSize		SIZEL <>
MaxCroppingSize		SIZEL <>
CropGranularityX	SINT ?
CropGranularityY	SINT ?
CropAlignX		SINT ?
CropAlignY		SINT ?
MinOutputSize		SIZEL <>
MaxOutputSize		SIZEL <>
OutputGranularityX	SINT ?
OutputGranularityY	SINT ?
StretchTapsX		SINT ?
StretchTapsY		SINT ?
ShrinkTapsX		SINT ?
ShrinkTapsY		SINT ?
MinFrameInterval	LONGLONG ?
MaxFrameInterval	LONGLONG ?
MinBitsPerSecond	LONG ?
MaxBitsPerSecond	LONG ?
VIDEO_STREAM_CONFIG_CAPS ENDS

AUDIO_STREAM_CONFIG_CAPS STRUC
guid			GUID <>
MinimumChannels		ULONG ?
MaximumChannels		ULONG ?
ChannelsGranularity	ULONG ?
MinimumBitsPerSample	ULONG ?
MaximumBitsPerSample	ULONG ?
BitsPerSampleGranularity ULONG ?
MinimumSampleFrequency	ULONG ?
MaximumSampleFrequency	ULONG ?
SampleFrequencyGranularity ULONG ?
AUDIO_STREAM_CONFIG_CAPS ENDS

DEFINE_IIDX(IAMStreamConfig, "C6E13340-30AC-11d0-A18C-00A0C9118956")

.comdef IAMStreamConfig : public IUnknown

    SetFormat		proc :ptr
    GetFormat		proc :ptr
    GetNumberOfCapabilities proc :ptr, :ptr
    GetStreamCaps	proc :SINT, :ptr, :ptr
   .ends

endif

ifndef __IConfigInterleaving_INTERFACE_DEFINED__
define __IConfigInterleaving_INTERFACE_DEFINED__

.enum InterleavingMode {
	INTERLEAVE_NONE,
	INTERLEAVE_CAPTURE,
	INTERLEAVE_FULL,
	INTERLEAVE_NONE_BUFFERED
	}

DEFINE_IIDX(IConfigInterleaving, "BEE3D220-157B-11d0-BD23-00A0C911CE86")

.comdef IConfigInterleaving : public IUnknown

    put_Mode		proc :InterleavingMode
    get_Mode		proc :ptr
    put_Interleaving	proc :ptr, :ptr
    get_Interleaving	proc :ptr, :ptr
   .ends

endif

ifndef __IConfigAviMux_INTERFACE_DEFINED__
define __IConfigAviMux_INTERFACE_DEFINED__

DEFINE_IIDX(IConfigAviMux, "5ACD6AA0-F482-11ce-8B67-00AA00A3F1A6")

.comdef IConfigAviMux : public IUnknown

    SetMasterStream	proc :LONG
    GetMasterStream	proc :ptr
    SetOutputCompatibilityIndex proc :BOOL
    GetOutputCompatibilityIndex proc :ptr
   .ends

endif

.enum CompressionCaps {
	CompressionCaps_CanQuality	= 0x1,
	CompressionCaps_CanCrunch	= 0x2,
	CompressionCaps_CanKeyFrame	= 0x4,
	CompressionCaps_CanBFrame	= 0x8,
	CompressionCaps_CanWindow	= 0x10
	}

ifndef __IAMVideoCompression_INTERFACE_DEFINED__
define __IAMVideoCompression_INTERFACE_DEFINED__

DEFINE_IIDX(IAMVideoCompression, "C6E13343-30AC-11d0-A18C-00A0C9118956")

.comdef IAMVideoCompression : public IUnknown

    put_KeyFrameRate	proc :LONG
    get_KeyFrameRate	proc :ptr
    put_PFramesPerKeyFrame proc :LONG
    get_PFramesPerKeyFrame proc :ptr
    put_Quality		proc :REAL8
    get_Quality		proc :ptr
    put_WindowSize	proc :DWORDLONG
    get_WindowSize	proc :ptr
    GetInfo		proc :LPWSTR, :ptr, :ptr, :ptr, :ptr, :ptr
    OverrideKeyFrame	proc :LONG
    OverrideFrameSize	proc :LONG, :LONG
   .ends

endif

.enum VfwCaptureDialogs {
	VfwCaptureDialog_Source	 = 0x1,
	VfwCaptureDialog_Format	 = 0x2,
	VfwCaptureDialog_Display = 0x4
	}

.enum VfwCompressDialogs {
	VfwCompressDialog_Config	= 0x1,
	VfwCompressDialog_About		= 0x2,
	VfwCompressDialog_QueryConfig	= 0x4,
	VfwCompressDialog_QueryAbout	= 0x8
	}

ifndef __IAMVfwCaptureDialogs_INTERFACE_DEFINED__
define __IAMVfwCaptureDialogs_INTERFACE_DEFINED__

DEFINE_IIDX(IAMVfwCaptureDialogs, "D8D715A0-6E5E-11D0-B3F0-00AA003761C5")

.comdef IAMVfwCaptureDialogs : public IUnknown

    HasDialog		proc :SINT
    ShowDialog		proc :SINT, :HWND
    SendDriverMessage	proc :SINT, :SINT, :LONG, :LONG
   .ends

endif

ifndef __IAMVfwCompressDialogs_INTERFACE_DEFINED__
define __IAMVfwCompressDialogs_INTERFACE_DEFINED__

DEFINE_IIDX(IAMVfwCompressDialogs, "D8D715A3-6E5E-11D0-B3F0-00AA003761C5")

.comdef IAMVfwCompressDialogs : public IUnknown

    ShowDialog		proc :SINT, :HWND
    GetState		proc :LPVOID, :ptr
    SetState		proc
    SendDriverMessage	proc :SINT, :LONG, :LONG
   .ends

endif

ifndef __IAMDroppedFrames_INTERFACE_DEFINED__
define __IAMDroppedFrames_INTERFACE_DEFINED__

DEFINE_IIDX(IAMDroppedFrames, "C6E13344-30AC-11d0-A18C-00A0C9118956")

.comdef IAMDroppedFrames : public IUnknown

    GetNumDropped	proc :ptr
    GetNumNotDropped	proc :ptr
    GetDroppedInfo	proc :LONG, :ptr, :ptr
    GetAverageFrameSize proc :ptr
   .ends

endif

AMF_AUTOMATICGAIN	equ -1.0

ifndef __IAMAudioInputMixer_INTERFACE_DEFINED__
define __IAMAudioInputMixer_INTERFACE_DEFINED__

DEFINE_IIDX(IAMAudioInputMixer, "54C39221-8380-11d0-B3F0-00AA003761C5")

.comdef IAMAudioInputMixer : public IUnknown

    put_Enable		proc :BOOL
    get_Enable		proc :ptr
    put_Mono		proc :BOOL
    get_Mono		proc :ptr
    put_MixLevel	proc :REAL8
    get_MixLevel	proc :ptr
    put_Pan		proc :REAL8
    get_Pan		proc :ptr
    put_Loudness	proc :BOOL
    get_Loudness	proc :ptr
    put_Treble		proc :REAL8
    get_Treble		proc :ptr
    get_TrebleRange	proc :ptr
    put_Bass		proc :REAL8
    get_Bass		proc :ptr
    get_BassRange	proc :ptr
   .ends

endif

ifndef __IAMBufferNegotiation_INTERFACE_DEFINED__
define __IAMBufferNegotiation_INTERFACE_DEFINED__

DEFINE_IIDX(IAMBufferNegotiation, "56ED71A0-AF5F-11D0-B3F0-00AA003761C5")

.comdef IAMBufferNegotiation : public IUnknown

    SuggestAllocatorProperties proc :ptr
    GetAllocatorProperties proc :ptr
   .ends

endif

.enum AnalogVideoStandard {
	AnalogVideo_None	= 0,
	AnalogVideo_NTSC_M	= 0x1,
	AnalogVideo_NTSC_M_J	= 0x2,
	AnalogVideo_NTSC_433	= 0x4,
	AnalogVideo_PAL_B	= 0x10,
	AnalogVideo_PAL_D	= 0x20,
	AnalogVideo_PAL_G	= 0x40,
	AnalogVideo_PAL_H	= 0x80,
	AnalogVideo_PAL_I	= 0x100,
	AnalogVideo_PAL_M	= 0x200,
	AnalogVideo_PAL_N	= 0x400,
	AnalogVideo_PAL_60	= 0x800,
	AnalogVideo_SECAM_B	= 0x1000,
	AnalogVideo_SECAM_D	= 0x2000,
	AnalogVideo_SECAM_G	= 0x4000,
	AnalogVideo_SECAM_H	= 0x8000,
	AnalogVideo_SECAM_K	= 0x10000,
	AnalogVideo_SECAM_K1	= 0x20000,
	AnalogVideo_SECAM_L	= 0x40000,
	AnalogVideo_SECAM_L1	= 0x80000,
	AnalogVideo_PAL_N_COMBO = 0x100000,
	AnalogVideoMask_MCE_NTSC = ( ( ( ( ( ( AnalogVideo_NTSC_M or AnalogVideo_NTSC_M_J )  or AnalogVideo_NTSC_433 ) or AnalogVideo_PAL_M ) or AnalogVideo_PAL_N ) or AnalogVideo_PAL_60 ) or AnalogVideo_PAL_N_COMBO ) ,
	AnalogVideoMask_MCE_PAL = ( ( ( ( AnalogVideo_PAL_B or AnalogVideo_PAL_D ) or AnalogVideo_PAL_G ) or AnalogVideo_PAL_H ) or AnalogVideo_PAL_I ) ,
	AnalogVideoMask_MCE_SECAM = ( ( ( ( ( ( ( AnalogVideo_SECAM_B or AnalogVideo_SECAM_D ) or AnalogVideo_SECAM_G ) or AnalogVideo_SECAM_H ) or AnalogVideo_SECAM_K ) or AnalogVideo_SECAM_K1 ) or AnalogVideo_SECAM_L ) or AnalogVideo_SECAM_L1 )
	}

.enum TunerInputType {
	TunerInputCable,
	TunerInputAntenna
	}

AnalogVideo_NTSC_Mask	equ 0x00000007
AnalogVideo_PAL_Mask	equ 0x00100FF0
AnalogVideo_SECAM_Mask	equ 0x000FF000

.enum VideoCopyProtectionType {
	VideoCopyProtectionMacrovisionBasic,
	VideoCopyProtectionMacrovisionCBI
	}

.enum PhysicalConnectorType {
	PhysConn_Video_Tuner = 1,
	PhysConn_Video_Composite,
	PhysConn_Video_SVideo,
	PhysConn_Video_RGB,
	PhysConn_Video_YRYBY,
	PhysConn_Video_SerialDigital,
	PhysConn_Video_ParallelDigital,
	PhysConn_Video_SCSI,
	PhysConn_Video_AUX,
	PhysConn_Video_1394,
	PhysConn_Video_USB,
	PhysConn_Video_VideoDecoder,
	PhysConn_Video_VideoEncoder,
	PhysConn_Video_SCART,
	PhysConn_Video_Black,
	PhysConn_Audio_Tuner,
	PhysConn_Audio_Line,
	PhysConn_Audio_Mic,
	PhysConn_Audio_AESDigital,
	PhysConn_Audio_SPDIFDigital,
	PhysConn_Audio_SCSI,
	PhysConn_Audio_AUX,
	PhysConn_Audio_1394,
	PhysConn_Audio_USB,
	PhysConn_Audio_AudioDecoder
	}


ifndef __IAMAnalogVideoDecoder_INTERFACE_DEFINED__
define __IAMAnalogVideoDecoder_INTERFACE_DEFINED__

DEFINE_IIDX(IAMAnalogVideoDecoder, "C6E13350-30AC-11d0-A18C-00A0C9118956")

.comdef IAMAnalogVideoDecoder : public IUnknown

    get_AvailableTVFormats proc :ptr
    put_TVFormat	proc :LONG
    get_TVFormat	proc :ptr
    get_HorizontalLocked proc :ptr
    put_VCRHorizontalLocking proc :LONG
    get_VCRHorizontalLocking proc :ptr
    get_NumberOfLines	proc :ptr
    put_OutputEnable	proc :LONG
    get_OutputEnable	proc :ptr
   .ends

endif

.enum VideoProcAmpProperty {
	VideoProcAmp_Brightness,
	VideoProcAmp_Contrast,
	VideoProcAmp_Hue,
	VideoProcAmp_Saturation,
	VideoProcAmp_Sharpness,
	VideoProcAmp_Gamma,
	VideoProcAmp_ColorEnable,
	VideoProcAmp_WhiteBalance,
	VideoProcAmp_BacklightCompensation,
	VideoProcAmp_Gain
	}

.enum VideoProcAmpFlags	 {
	VideoProcAmp_Flags_Auto = 0x1,
	VideoProcAmp_Flags_Manual = 0x2
	}

ifndef __IAMVideoProcAmp_INTERFACE_DEFINED__
define __IAMVideoProcAmp_INTERFACE_DEFINED__

DEFINE_IIDX(IAMVideoProcAmp, "C6E13360-30AC-11d0-A18C-00A0C9118956")

.comdef IAMVideoProcAmp : public IUnknown

    GetRange		proc :LONG, :ptr, :ptr, :ptr, :ptr, :ptr
    Set			proc :LONG, :LONG, :LONG
    Get			proc :LONG, :ptr, :ptr
   .ends

endif

.enum CameraControlProperty {
	CameraControl_Pan,
	CameraControl_Tilt,
	CameraControl_Roll,
	CameraControl_Zoom,
	CameraControl_Exposure,
	CameraControl_Iris,
	CameraControl_Focus
	}

.enum CameraControlFlags {
	CameraControl_Flags_Auto = 0x1,
	CameraControl_Flags_Manual = 0x2
	}

ifndef __IAMCameraControl_INTERFACE_DEFINED__
define __IAMCameraControl_INTERFACE_DEFINED__

DEFINE_IIDX(IAMCameraControl, "C6E13370-30AC-11d0-A18C-00A0C9118956")

.comdef IAMCameraControl : public IUnknown

    GetRange		proc :LONG, :ptr, :ptr, :ptr, :ptr, :ptr
    Set			proc :LONG, :LONG, :LONG
    Get			proc :LONG, :ptr, :ptr
   .ends

endif

.enum VideoControlFlags {
	VideoControlFlag_FlipHorizontal = 0x1,
	VideoControlFlag_FlipVertical	= 0x2,
	VideoControlFlag_ExternalTriggerEnable	= 0x4,
	VideoControlFlag_Trigger	= 0x8
	}

ifndef __IAMVideoControl_INTERFACE_DEFINED__
define __IAMVideoControl_INTERFACE_DEFINED__

DEFINE_IIDX(IAMVideoControl, "6a2e0670-28e4-11d0-a18c-00a0c9118956")

.comdef IAMVideoControl : public IUnknown

    GetCaps		proc :ptr, :ptr
    SetMode		proc :ptr, :LONG
    GetMode		proc :ptr, :ptr
    GetCurrentActualFrameRate proc :ptr, :ptr
    GetMaxAvailableFrameRate proc :ptr, :LONG, :SIZEL, :ptr
    GetFrameRateList	proc :ptr, :LONG, :SIZEL, :ptr, :ptr
   .ends

endif

ifndef __IAMCrossbar_INTERFACE_DEFINED__
define __IAMCrossbar_INTERFACE_DEFINED__

DEFINE_IIDX(IAMCrossbar, "C6E13380-30AC-11d0-A18C-00A0C9118956")

.comdef IAMCrossbar : public IUnknown

    get_PinCounts	proc :ptr, :ptr
    CanRoute		proc :LONG, :LONG
    Route		proc :LONG, :LONG
    get_IsRoutedTo	proc :LONG, :ptr
    get_CrossbarPinInfo proc :BOOL, :LONG, :ptr, :ptr
   .ends

endif

.enum AMTunerSubChannel {
	AMTUNER_SUBCHAN_NO_TUNE = -2,
	AMTUNER_SUBCHAN_DEFAULT = -1
	}

.enum AMTunerSignalStrength {
	AMTUNER_HASNOSIGNALSTRENGTH = -1,
	AMTUNER_NOSIGNAL	= 0,
	AMTUNER_SIGNALPRESENT	= 1
	}

.enum AMTunerModeType {
	AMTUNER_MODE_DEFAULT	= 0,
	AMTUNER_MODE_TV		= 0x1,
	AMTUNER_MODE_FM_RADIO	= 0x2,
	AMTUNER_MODE_AM_RADIO	= 0x4,
	AMTUNER_MODE_DSS	= 0x8
	}

.enum AMTunerEventType {
	AMTUNER_EVENT_CHANGED	= 0x1
	}

ifndef __IAMTuner_INTERFACE_DEFINED__
define __IAMTuner_INTERFACE_DEFINED__

DEFINE_IIDX(IAMTuner, "211A8761-03AC-11d1-8D13-00AA00BD8339")

.comdef IAMTuner : public IUnknown

    put_Channel		proc :LONG, :LONG, :LONG
    get_Channel		proc :ptr, :ptr, :ptr
    ChannelMinMax	proc :ptr, :ptr
    put_CountryCode	proc :LONG
    get_CountryCode	proc :ptr
    put_TuningSpace	proc :LONG
    get_TuningSpace	proc :ptr
    Logon		proc :HANDLE
    Logout		proc
    SignalPresent	proc :ptr
    put_Mode		proc :AMTunerModeType
    get_Mode		proc :ptr
    GetAvailableModes	proc :ptr
    RegisterNotificationCallBack proc :ptr, :LONG
    UnRegisterNotificationCallBack proc :ptr
   .ends

endif

ifndef __IAMTunerNotification_INTERFACE_DEFINED__
define __IAMTunerNotification_INTERFACE_DEFINED__

DEFINE_IIDX(IAMTunerNotification, "211A8760-03AC-11d1-8D13-00AA00BD8339")

.comdef IAMTunerNotification : public IUnknown

    OnEvent		proc :AMTunerEventType
   .ends

endif

ifndef __IAMTVTuner_INTERFACE_DEFINED__
define __IAMTVTuner_INTERFACE_DEFINED__

DEFINE_IIDX(IAMTVTuner, "211A8766-03AC-11d1-8D13-00AA00BD8339")

.comdef IAMTVTuner : public IAMTuner

    get_AvailableTVFormats proc :ptr
    get_TVFormat	proc :ptr
    AutoTune		proc :LONG, :ptr
    StoreAutoTune	proc
    get_NumInputConnections proc :ptr
    put_InputType	proc :LONG, :TunerInputType
    get_InputType	proc :LONG, :ptr
    put_ConnectInput	proc :LONG
    get_ConnectInput	proc :ptr
    get_VideoFrequency	proc :ptr
    get_AudioFrequency	proc :ptr
   .ends

endif

ifndef __IBPCSatelliteTuner_INTERFACE_DEFINED__
define __IBPCSatelliteTuner_INTERFACE_DEFINED__

DEFINE_IIDX(IBPCSatelliteTuner, "211A8765-03AC-11d1-8D13-00AA00BD8339")

.comdef IBPCSatelliteTuner : public IAMTuner

    get_DefaultSubChannelTypes proc :ptr, :ptr
    put_DefaultSubChannelTypes proc :LONG, :LONG
    IsTapingPermitted	proc
   .ends

endif

.enum TVAudioMode {
	AMTVAUDIO_MODE_MONO	= 0x1,
	AMTVAUDIO_MODE_STEREO	= 0x2,
	AMTVAUDIO_MODE_LANG_A	= 0x10,
	AMTVAUDIO_MODE_LANG_B	= 0x20,
	AMTVAUDIO_MODE_LANG_C	= 0x40,
	AMTVAUDIO_PRESET_STEREO = 0x200,
	AMTVAUDIO_PRESET_LANG_A = 0x1000,
	AMTVAUDIO_PRESET_LANG_B = 0x2000,
	AMTVAUDIO_PRESET_LANG_C = 0x4000
	}

.enum AMTVAudioEventType {
	AMTVAUDIO_EVENT_CHANGED = 0x1
	}

ifndef __IAMTVAudio_INTERFACE_DEFINED__
define __IAMTVAudio_INTERFACE_DEFINED__

DEFINE_IIDX(IAMTVAudio, "83EC1C30-23D1-11d1-99E6-00A0C9560266")

.comdef IAMTVAudio : public IUnknown

    GetHardwareSupportedTVAudioModes proc :ptr
    GetAvailableTVAudioModes proc :ptr
    get_TVAudioMode	proc :ptr
    put_TVAudioMode	proc :LONG
    RegisterNotificationCallBack proc :ptr, :LONG
    UnRegisterNotificationCallBack proc :ptr
   .ends

endif

ifndef __IAMTVAudioNotification_INTERFACE_DEFINED__
define __IAMTVAudioNotification_INTERFACE_DEFINED__

DEFINE_IIDX(IAMTVAudioNotification, "83EC1C33-23D1-11d1-99E6-00A0C9560266")

.comdef IAMTVAudioNotification : public IUnknown

    OnEvent		proc :AMTVAudioEventType
   .ends

endif

ifndef __IAMAnalogVideoEncoder_INTERFACE_DEFINED__
define __IAMAnalogVideoEncoder_INTERFACE_DEFINED__

DEFINE_IIDX(IAMAnalogVideoEncoder, "C6E133B0-30AC-11d0-A18C-00A0C9118956")

.comdef IAMAnalogVideoEncoder : public IUnknown

    get_AvailableTVFormats proc :ptr
    put_TVFormat	proc :LONG
    get_TVFormat	proc :ptr
    put_CopyProtection	proc :LONG
    get_CopyProtection	proc :ptr
    put_CCEnable	proc :LONG
    get_CCEnable	proc :ptr
   .ends
endif

.enum AMPROPERTY_PIN {
	AMPROPERTY_PIN_CATEGORY,
	AMPROPERTY_PIN_MEDIUM
	}

ifndef _IKsPropertySet_
define _IKsPropertySet_
define KSPROPERTY_SUPPORT_GET 1
define KSPROPERTY_SUPPORT_SET 2

ifndef __IKsPropertySet_INTERFACE_DEFINED__
define __IKsPropertySet_INTERFACE_DEFINED__

DEFINE_IIDX(IKsPropertySet, "31EFAC30-515C-11d0-A9AA-00AA0061BE93")

.comdef IKsPropertySet : public IUnknown

    Set			proc :REFGUID, :DWORD, :LPVOID, :DWORD
    Get			proc :REFGUID, :DWORD, :LPVOID, :DWORD, :ptr
    QuerySupported	proc :REFGUID, :DWORD, :ptr
   .ends
endif

endif

ifndef __IMediaPropertyBag_INTERFACE_DEFINED__
define __IMediaPropertyBag_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaPropertyBag, "6025A880-C0D5-11d0-BD4E-00A0C911CE86")

.comdef IMediaPropertyBag : public IPropertyBag

    EnumProperty	proc :ULONG, :ptr, :ptr
   .ends
    LPMEDIAPROPERTYBAG	typedef ptr IMediaPropertyBag
endif

ifndef __IPersistMediaPropertyBag_INTERFACE_DEFINED__
define __IPersistMediaPropertyBag_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistMediaPropertyBag, "5738E040-B67F-11d0-BD4D-00A0C911CE86")

.comdef IPersistMediaPropertyBag : public IPersist

    InitNew		proc
    Load		proc :ptr, :ptr
    Save		proc :ptr, :BOOL, :BOOL
   .ends
    LPPERSISTMEDIAPROPERTYBAG typedef ptr IPersistMediaPropertyBag
endif

ifndef __IAMPhysicalPinInfo_INTERFACE_DEFINED__
define __IAMPhysicalPinInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IAMPhysicalPinInfo, "F938C991-3029-11cf-8C44-00AA006B6814")

.comdef IAMPhysicalPinInfo : public IUnknown

    GetPhysicalType	proc :ptr, :ptr
   .ends
endif

PAMPHYSICALPININFO	typedef ptr IAMPhysicalPinInfo

ifndef __IAMExtDevice_INTERFACE_DEFINED__
define __IAMExtDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IAMExtDevice, "B5730A90-1A2C-11cf-8C23-00AA006B6814")

.comdef IAMExtDevice : public IUnknown

    GetCapability	proc :LONG, :ptr, :ptr
    get_ExternalDeviceID proc :ptr
    get_ExternalDeviceVersion proc :ptr
    put_DevicePower	proc :LONG
    get_DevicePower	proc :ptr
    Calibrate		proc :HEVENT, :LONG, :ptr
    put_DevicePort	proc :LONG
    get_DevicePort	proc :ptr
   .ends

PEXTDEVICE		typedef ptr IAMExtDevice

endif

ifndef __IAMExtTransport_INTERFACE_DEFINED__
define __IAMExtTransport_INTERFACE_DEFINED__

DEFINE_IIDX(IAMExtTransport, "A03CD5F0-3045-11cf-8C44-00AA006B6814")

.comdef IAMExtTransport : public IUnknown

    GetCapability	proc :LONG, :ptr, :ptr
    put_MediaState	proc :LONG
    get_MediaState	proc :ptr
    put_LocalControl	proc :LONG
    get_LocalControl	proc :ptr
    GetStatus		proc :LONG, :ptr
    GetTransportBasicParameters proc :LONG, :ptr, :ptr
    SetTransportBasicParameters proc :LONG, :LONG, :LPCOLESTR
    GetTransportVideoParameters proc :LONG, :ptr
    SetTransportVideoParameters proc :LONG, :LONG
    GetTransportAudioParameters proc :LONG, :ptr
    SetTransportAudioParameters proc :LONG, :LONG
    put_Mode		proc :LONG
    get_Mode		proc :ptr
    put_Rate		proc :REAL8
    get_Rate		proc :ptr
    GetChase		proc :ptr, :ptr, :ptr
    SetChase		proc :LONG, :LONG, :HEVENT
    GetBump		proc :ptr, :ptr
    SetBump		proc :LONG, :LONG
    get_AntiClogControl proc :ptr
    put_AntiClogControl proc :LONG
    GetEditPropertySet	proc :LONG, :ptr
    SetEditPropertySet	proc :ptr, :LONG
    GetEditProperty	proc :LONG, :LONG, :ptr
    SetEditProperty	proc :LONG, :LONG, :LONG
    get_EditStart	proc :ptr
    put_EditStart	proc :LONG
   .ends

endif

PIAMEXTTRANSPORT	typedef ptr IAMExtTransport

ifndef TIMECODE_DEFINED
TIMECODE_DEFINED equ 1
TIMECODE		UNION
STRUC
 wFrameRate		dw ?
 wFrameFract		dw ?
 dwFrames		dd ?
ENDS
qw			dd ?
TIMECODE		ENDS
PTIMECODE		typedef ptr TIMECODE
endif

TIMECODE_SAMPLE		STRUC
qwTick			LONGLONG ?
timecode		TIMECODE <>
dwUser			dd ?
dwFlags			dd ?
TIMECODE_SAMPLE		ENDS
PTIMECODE_SAMPLE	typedef ptr TIMECODE_SAMPLE

ifndef __IAMTimecodeReader_INTERFACE_DEFINED__
define __IAMTimecodeReader_INTERFACE_DEFINED__

DEFINE_IIDX(IAMTimecodeReader, "9B496CE1-811B-11cf-8C77-00AA006B6814")

.comdef IAMTimecodeReader : public IUnknown

    GetTCRMode		proc :LONG, :ptr
    SetTCRMode		proc :LONG, :LONG
    put_VITCLine	proc :LONG
    get_VITCLine	proc :ptr
    GetTimecode		proc :PTIMECODE_SAMPLE
   .ends

PIAMTIMECODEREADER	typedef ptr IAMTimecodeReader

endif

ifndef __IAMTimecodeGenerator_INTERFACE_DEFINED__
define __IAMTimecodeGenerator_INTERFACE_DEFINED__

DEFINE_IIDX(IAMTimecodeGenerator, "9B496CE0-811B-11cf-8C77-00AA006B6814")

.comdef IAMTimecodeGenerator : public IUnknown

    GetTCGMode		proc :LONG, :ptr
    SetTCGMode		proc :LONG, :LONG
    put_VITCLine	proc :LONG
    get_VITCLine	proc :ptr
    SetTimecode		proc :PTIMECODE_SAMPLE
    GetTimecode		proc :PTIMECODE_SAMPLE
   .ends

PIAMTIMECODEGENERATOR	typedef ptr IAMTimecodeGenerator

endif

ifndef __IAMTimecodeDisplay_INTERFACE_DEFINED__
define __IAMTimecodeDisplay_INTERFACE_DEFINED__

DEFINE_IIDX(IAMTimecodeDisplay, "9B496CE2-811B-11cf-8C77-00AA006B6814")

.comdef IAMTimecodeDisplay : public IUnknown

    GetTCDisplayEnable	proc :ptr
    SetTCDisplayEnable	proc :LONG
    GetTCDisplay	proc :LONG, :ptr
    SetTCDisplay	proc :LONG, :LONG
   .ends

PIAMTIMECODEDISPLAY	typedef ptr IAMTimecodeDisplay

endif

ifndef __IAMDevMemoryAllocator_INTERFACE_DEFINED__
define __IAMDevMemoryAllocator_INTERFACE_DEFINED__

DEFINE_IIDX(IAMDevMemoryAllocator, "c6545bf0-e76b-11d0-bd52-00a0c911ce86")

.comdef IAMDevMemoryAllocator : public IUnknown

    GetInfo		proc :ptr, :ptr, :ptr, :ptr
    CheckMemory		proc :ptr
    Alloc		proc
    Free		proc :ptr
    GetDevMemoryObject	proc :ptr, :ptr
   .ends

PAMDEVMEMORYALLOCATOR	typedef ptr IAMDevMemoryAllocator

endif

ifndef __IAMDevMemoryControl_INTERFACE_DEFINED__
define __IAMDevMemoryControl_INTERFACE_DEFINED__

DEFINE_IIDX(IAMDevMemoryControl, "c6545bf1-e76b-11d0-bd52-00a0c911ce86")

.comdef IAMDevMemoryControl : public IUnknown

    QueryWriteSync	proc
    WriteSync		proc
    GetDevId		proc :ptr
   .ends

PAMDEVMEMORYCONTROL	typedef ptr IAMDevMemoryControl

endif

.enum AMSTREAMSELECTINFOFLAGS {
	AMSTREAMSELECTINFO_ENABLED	= 0x1,
	AMSTREAMSELECTINFO_EXCLUSIVE	= 0x2
	}

.enum AMSTREAMSELECTENABLEFLAGS {
	AMSTREAMSELECTENABLE_ENABLE	= 0x1,
	AMSTREAMSELECTENABLE_ENABLEALL	= 0x2
	}

ifndef __IAMStreamSelect_INTERFACE_DEFINED__
define __IAMStreamSelect_INTERFACE_DEFINED__

DEFINE_IIDX(IAMStreamSelect, "c1960960-17f5-11d1-abe1-00a0c905f375")

.comdef IAMStreamSelect : public IUnknown

    Count		proc :ptr
    Info		proc :LONG, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    Enable		proc :LONG, :DWORD
   .ends

PAMSTREAMSELECT		typedef ptr IAMStreamSelect

endif

.enum AMRESCTL_RESERVEFLAGS {
	AMRESCTL_RESERVEFLAGS_RESERVE	= 0,
	AMRESCTL_RESERVEFLAGS_UNRESERVE = 0x1
	}

ifndef __IAMResourceControl_INTERFACE_DEFINED__
define __IAMResourceControl_INTERFACE_DEFINED__

DEFINE_IIDX(IAMResourceControl, "8389d2d0-77d7-11d1-abe6-00a0c905f375")

.comdef IAMResourceControl : public IUnknown

    Reserve		proc :DWORD, :PVOID
   .ends

endif

ifndef __IAMClockAdjust_INTERFACE_DEFINED__
define __IAMClockAdjust_INTERFACE_DEFINED__

DEFINE_IIDX(IAMClockAdjust, "4d5466b0-a49c-11d1-abe8-00a0c905f375")

.comdef IAMClockAdjust : public IUnknown

    SetClockDelta	proc :REFERENCE_TIME
   .ends

endif

.enum AM_FILTER_MISC_FLAGS {
	AM_FILTER_MISC_FLAGS_IS_RENDERER = 0x1,
	AM_FILTER_MISC_FLAGS_IS_SOURCE	= 0x2
	}

ifndef __IAMFilterMiscFlags_INTERFACE_DEFINED__
define __IAMFilterMiscFlags_INTERFACE_DEFINED__

DEFINE_IIDX(IAMFilterMiscFlags, "2dd74950-a890-11d1-abe8-00a0c905f375")

.comdef IAMFilterMiscFlags : public IUnknown

    GetMiscFlags	proc
   .ends

endif

ifndef __IDrawVideoImage_INTERFACE_DEFINED__
define __IDrawVideoImage_INTERFACE_DEFINED__

DEFINE_IIDX(IDrawVideoImage, "48efb120-ab49-11d2-aed2-00a0c995e8d5")

.comdef IDrawVideoImage : public IUnknown

    DrawVideoImageBegin proc
    DrawVideoImageEnd	proc
    DrawVideoImageDraw	proc :HDC, :LPRECT, :LPRECT
   .ends

endif

ifndef __IDecimateVideoImage_INTERFACE_DEFINED__
define __IDecimateVideoImage_INTERFACE_DEFINED__

DEFINE_IIDX(IDecimateVideoImage, "2e5ea3e0-e924-11d2-b6da-00a0c995e8df")

.comdef IDecimateVideoImage : public IUnknown

    SetDecimationImageSize proc :LONG, :LONG
    ResetDecimationImageSize proc
   .ends

endif

.enum DECIMATION_USAGE {
	DECIMATION_LEGACY,
	DECIMATION_USE_DECODER_ONLY,
	DECIMATION_USE_VIDEOPORT_ONLY,
	DECIMATION_USE_OVERLAY_ONLY,
	DECIMATION_DEFAULT
	}

ifndef __IAMVideoDecimationProperties_INTERFACE_DEFINED__
define __IAMVideoDecimationProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IAMVideoDecimationProperties, "60d32930-13da-11d3-9ec6-c4fcaef5c7be")

.comdef IAMVideoDecimationProperties : public IUnknown

    QueryDecimationUsage proc :ptr

    SetDecimationUsage	proc :DECIMATION_USAGE
   .ends

endif

ifndef __IVideoFrameStep_INTERFACE_DEFINED__
define __IVideoFrameStep_INTERFACE_DEFINED__

DEFINE_IIDX(IVideoFrameStep, "e46a9787-2b71-444d-a4b5-1fab7b708d6a")

.comdef IVideoFrameStep : public IUnknown

    Step		proc :DWORD, :ptr
    CanStep		proc :LONG, :ptr
    CancelStep		proc
   .ends

endif

.enum AM_PUSHSOURCE_FLAGS {
	AM_PUSHSOURCECAPS_INTERNAL_RM	= 0x1,
	AM_PUSHSOURCECAPS_NOT_LIVE	= 0x2,
	AM_PUSHSOURCECAPS_PRIVATE_CLOCK = 0x4,
	AM_PUSHSOURCEREQS_USE_STREAM_CLOCK = 0x10000,
	AM_PUSHSOURCEREQS_USE_CLOCK_CHAIN  = 0x20000
	}

ifndef __IAMLatency_INTERFACE_DEFINED__
define __IAMLatency_INTERFACE_DEFINED__

DEFINE_IIDX(IAMLatency, "62EA93BA-EC62-11d2-B770-00C04FB6BD3D")

.comdef IAMLatency : public IUnknown

    GetLatency		proc :ptr
   .ends

endif

ifndef __IAMPushSource_INTERFACE_DEFINED__
define __IAMPushSource_INTERFACE_DEFINED__

DEFINE_IIDX(IAMPushSource, "F185FE76-E64E-11d2-B76E-00C04FB6BD3D")

.comdef IAMPushSource : public IAMLatency

    GetPushSourceFlags	proc :ptr
    SetPushSourceFlags	proc :ULONG
    SetStreamOffset	proc :REFERENCE_TIME
    GetStreamOffset	proc :ptr
    GetMaxStreamOffset	proc :ptr
    SetMaxStreamOffset	proc :REFERENCE_TIME
   .ends

endif

ifndef __IAMDeviceRemoval_INTERFACE_DEFINED__
define __IAMDeviceRemoval_INTERFACE_DEFINED__

DEFINE_IIDX(IAMDeviceRemoval, "f90a6130-b658-11d2-ae49-0000f8754b99")

.comdef IAMDeviceRemoval : public IUnknown

    DeviceInfo		proc :ptr, :ptr
    Reassociate		proc
    Disassociate	proc
   .ends

endif

DVINFO			STRUC
dwDVAAuxSrc		dd ?
dwDVAAuxCtl		dd ?
dwDVAAuxSrc1		dd ?
dwDVAAuxCtl1		dd ?
dwDVVAuxSrc		dd ?
dwDVVAuxCtl		dd ?
dwDVReserved		dd  2  dup(?)
DVINFO			ENDS

PDVINFO			typedef ptr DVINFO

.enum DVENCODERRESOLUTION {
	DVENCODERRESOLUTION_720x480	= 2012,
	DVENCODERRESOLUTION_360x240	= 2013,
	DVENCODERRESOLUTION_180x120	= 2014,
	DVENCODERRESOLUTION_88x60	= 2015
	}

.enum DVENCODERVIDEOFORMAT {
	DVENCODERVIDEOFORMAT_NTSC	= 2000,
	DVENCODERVIDEOFORMAT_PAL	= 2001
	}

.enum DVENCODERFORMAT {
	DVENCODERFORMAT_DVSD	= 2007,
	DVENCODERFORMAT_DVHD	= 2008,
	DVENCODERFORMAT_DVSL	= 2009
	}

ifndef __IDVEnc_INTERFACE_DEFINED__
define __IDVEnc_INTERFACE_DEFINED__

DEFINE_IIDX(IDVEnc, "d18e17a0-aacb-11d0-afb0-00aa00b67a42")

.comdef IDVEnc : public IUnknown

    get_IFormatResolution proc :ptr, :ptr, :ptr, :BYTE, :ptr
    put_IFormatResolution proc :SINT, :SINT, :SINT, :BYTE, :ptr
   .ends

endif

.enum DVDECODERRESOLUTION {
	DVDECODERRESOLUTION_720x480	= 1000,
	DVDECODERRESOLUTION_360x240	= 1001,
	DVDECODERRESOLUTION_180x120	= 1002,
	DVDECODERRESOLUTION_88x60	= 1003
	}

.enum DVRESOLUTION {
	DVRESOLUTION_FULL	= 1000,
	DVRESOLUTION_HALF	= 1001,
	DVRESOLUTION_QUARTER	= 1002,
	DVRESOLUTION_DC = 1003
	}

ifndef __IIPDVDec_INTERFACE_DEFINED__
define __IIPDVDec_INTERFACE_DEFINED__

DEFINE_IIDX(IIPDVDec, "b8e8bd60-0bfe-11d0-af91-00aa00b67a42")

.comdef IIPDVDec : public IUnknown

    get_IPDisplay	proc :ptr
    put_IPDisplay	proc :SINT
   .ends

endif

ifndef __IDVRGB219_INTERFACE_DEFINED__
define __IDVRGB219_INTERFACE_DEFINED__

DEFINE_IIDX(IDVRGB219, "58473A19-2BC8-4663-8012-25F81BABDDD1")

.comdef IDVRGB219 : public IUnknown

    SetRGB219		proc :BOOL
   .ends

endif

ifndef __IDVSplitter_INTERFACE_DEFINED__
define __IDVSplitter_INTERFACE_DEFINED__

DEFINE_IIDX(IDVSplitter, "92a3a302-da7c-4a1f-ba7e-1802bb5d2d02")

.comdef IDVSplitter : public IUnknown

    DiscardAlternateVideoFrames proc :SINT
   .ends

endif

.enum AM_AUDIO_RENDERER_STAT_PARAM {
	AM_AUDREND_STAT_PARAM_BREAK_COUNT = 1,
	AM_AUDREND_STAT_PARAM_SLAVE_MODE,
	AM_AUDREND_STAT_PARAM_SILENCE_DUR,
	AM_AUDREND_STAT_PARAM_LAST_BUFFER_DUR,
	AM_AUDREND_STAT_PARAM_DISCONTINUITIES,
	AM_AUDREND_STAT_PARAM_SLAVE_RATE,
	AM_AUDREND_STAT_PARAM_SLAVE_DROPWRITE_DUR,
	AM_AUDREND_STAT_PARAM_SLAVE_HIGHLOWERROR,
	AM_AUDREND_STAT_PARAM_SLAVE_LASTHIGHLOWERROR,
	AM_AUDREND_STAT_PARAM_SLAVE_ACCUMERROR,
	AM_AUDREND_STAT_PARAM_BUFFERFULLNESS,
	AM_AUDREND_STAT_PARAM_JITTER
	}

ifndef __IAMAudioRendererStats_INTERFACE_DEFINED__
define __IAMAudioRendererStats_INTERFACE_DEFINED__

DEFINE_IIDX(IAMAudioRendererStats, "22320CB2-D41A-11d2-BF7C-D7CB9DF0BF93")

.comdef IAMAudioRendererStats : public IUnknown

    GetStatParam	proc :DWORD, :ptr, :ptr
   .ends

endif

.enum AM_INTF_SEARCH_FLAGS {
	AM_INTF_SEARCH_INPUT_PIN	= 0x1,
	AM_INTF_SEARCH_OUTPUT_PIN	= 0x2,
	AM_INTF_SEARCH_FILTER	= 0x4
	}

ifndef __IAMGraphStreams_INTERFACE_DEFINED__
define __IAMGraphStreams_INTERFACE_DEFINED__

DEFINE_IIDX(IAMGraphStreams, "632105FA-072E-11d3-8AF9-00C04FB6BD3D")

.comdef IAMGraphStreams : public IUnknown

    FindUpstreamInterface proc :ptr, :REFIID, :ptr, :DWORD
    SyncUsingStreamOffset proc :BOOL
    SetMaxGraphLatency	proc :REFERENCE_TIME
   .ends

endif

.enum AMOVERLAYFX {
	AMOVERFX_NOFX	= 0,
	AMOVERFX_MIRRORLEFTRIGHT	= 0x2,
	AMOVERFX_MIRRORUPDOWN	= 0x4,
	AMOVERFX_DEINTERLACE	= 0x8
	}

ifndef __IAMOverlayFX_INTERFACE_DEFINED__
define __IAMOverlayFX_INTERFACE_DEFINED__

DEFINE_IIDX(IAMOverlayFX, "62fae250-7e65-4460-bfc9-6398b322073c")

.comdef IAMOverlayFX : public IUnknown

    QueryOverlayFXCaps	proc :ptr
    SetOverlayFX	proc :DWORD
    GetOverlayFX	proc :ptr
   .ends

endif

ifndef __IAMOpenProgress_INTERFACE_DEFINED__
define __IAMOpenProgress_INTERFACE_DEFINED__

DEFINE_IIDX(IAMOpenProgress, "8E1C39A1-DE53-11cf-AA63-0080C744528D")

.comdef IAMOpenProgress : public IUnknown

    QueryProgress	proc :ptr, :ptr
    AbortOperation	proc
   .ends

endif

ifndef __IMpeg2Demultiplexer_INTERFACE_DEFINED__
define __IMpeg2Demultiplexer_INTERFACE_DEFINED__

DEFINE_IIDX(IMpeg2Demultiplexer, "436eee9c-264f-4242-90e1-4e330c107512")

.comdef IMpeg2Demultiplexer : public IUnknown

    CreateOutputPin	proc :ptr, :LPWSTR, :ptr
    SetOutputPinMediaType proc :LPWSTR, :ptr
    DeleteOutputPin	proc :LPWSTR
   .ends

endif

MPEG2_PROGRAM_STREAM_MAP equ 0x00000000
MPEG2_PROGRAM_ELEMENTARY_STREAM equ 0x00000001
MPEG2_PROGRAM_DIRECTORY_PES_PACKET equ 0x00000002
MPEG2_PROGRAM_PACK_HEADER equ 0x00000003
MPEG2_PROGRAM_PES_STREAM equ 0x00000004
MPEG2_PROGRAM_SYSTEM_HEADER equ 0x00000005
SUBSTREAM_FILTER_VAL_NONE equ 0x10000000

STREAM_ID_MAP		STRUC
stream_id		ULONG ?
dwMediaSampleContent	dd ?
ulSubstreamFilterValue	ULONG ?
iDataOffset		SINT ?
STREAM_ID_MAP		ENDS

ifndef __IEnumStreamIdMap_INTERFACE_DEFINED__
define __IEnumStreamIdMap_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumStreamIdMap, "945C1566-6202-46fc-96C7-D87F289C6534")

.comdef IEnumStreamIdMap : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IMPEG2StreamIdMap_INTERFACE_DEFINED__
define __IMPEG2StreamIdMap_INTERFACE_DEFINED__

DEFINE_IIDX(IMPEG2StreamIdMap, "D0E04C47-25B8-4369-925A-362A01D95444")

.comdef IMPEG2StreamIdMap : public IUnknown

    MapStreamId		proc :ULONG, :DWORD, :ULONG, :SINT
    UnmapStreamId	proc :ULONG, :ptr
    EnumStreamIdMap	proc :ptr
   .ends

endif

ifndef __IRegisterServiceProvider_INTERFACE_DEFINED__
define __IRegisterServiceProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IRegisterServiceProvider, "7B3A2F01-0751-48DD-B556-004785171C54")

.comdef IRegisterServiceProvider : public IUnknown

    RegisterService	proc :REFGUID, :ptr
   .ends

endif

ifndef __IAMClockSlave_INTERFACE_DEFINED__
define __IAMClockSlave_INTERFACE_DEFINED__

DEFINE_IIDX(IAMClockSlave, "9FD52741-176D-4b36-8F51-CA8F933223BE")

.comdef IAMClockSlave : public IUnknown

    SetErrorTolerance	proc :DWORD
    GetErrorTolerance	proc :ptr
   .ends

endif

ifndef __IAMGraphBuilderCallback_INTERFACE_DEFINED__
define __IAMGraphBuilderCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IAMGraphBuilderCallback, "4995f511-9ddb-4f12-bd3b-f04611807b79")

.comdef IAMGraphBuilderCallback : public IUnknown

    SelectedFilter	proc :ptr
    CreatedFilter	proc :ptr
   .ends

endif

AMCOPPSignature		STRUC
Signature		db 256 dup(?)
AMCOPPSignature		ENDS

AMCOPPCommand		STRUC
macKDI			GUID <>
guidCommandID		GUID <>
dwSequence		dd ?
cbSizeData		dd ?
CommandData		db 4056 dup(?)
AMCOPPCommand		ENDS

LPAMCOPPCommand		typedef ptr AMCOPPCommand

AMCOPPStatusInput	STRUC
rApp			GUID <>
guidStatusRequestID	GUID <>
dwSequence		dd ?
cbSizeData		dd ?
StatusData		db 4056 dup(?)
AMCOPPStatusInput	ENDS

LPAMCOPPStatusInput	typedef ptr AMCOPPStatusInput

AMCOPPStatusOutput	STRUC
macKDI			GUID <>
cbSizeData		dd ?
COPPStatus		db 4076 dup(?)
AMCOPPStatusOutput	ENDS

LPAMCOPPStatusOutput	typedef ptr AMCOPPStatusOutput

ifndef __IAMCertifiedOutputProtection_INTERFACE_DEFINED__
define __IAMCertifiedOutputProtection_INTERFACE_DEFINED__

DEFINE_IIDX(IAMCertifiedOutputProtection, "6feded3e-0ff1-4901-a2f1-43f7012c8515")

.comdef IAMCertifiedOutputProtection : public IUnknown

    KeyExchange		proc :ptr
    SessionSequenceStart proc :ptr
    ProtectionCommand	proc :ptr
    ProtectionStatus	proc :ptr, :ptr
   .ends

endif

ifndef __IAMAsyncReaderTimestampScaling_INTERFACE_DEFINED__
define __IAMAsyncReaderTimestampScaling_INTERFACE_DEFINED__

DEFINE_IIDX(IAMAsyncReaderTimestampScaling, "cf7b26fc-9a00-485b-8147-3e789d5e8f67")

.comdef IAMAsyncReaderTimestampScaling : public IUnknown

    GetTimestampMode	proc :ptr
    SetTimestampMode	proc :BOOL
   .ends

endif

ifndef __IAMPluginControl_INTERFACE_DEFINED__
define __IAMPluginControl_INTERFACE_DEFINED__

DEFINE_IIDX(IAMPluginControl, "0e26a181-f40c-4635-8786-976284b52981")

.comdef IAMPluginControl : public IUnknown

    GetPreferredClsid	proc :REFGUID, :ptr
    GetPreferredClsidByIndex proc :DWORD, :ptr, :ptr
    SetPreferredClsid	proc :REFGUID, :ptr
    IsDisabled		proc :REFCLSID
    GetDisabledByIndex	proc :DWORD, :ptr
    SetDisabled		proc :REFCLSID, :BOOL
    IsLegacyDisabled	proc :LPCWSTR
   .ends

endif

include ddraw.inc

.enum DVD_DOMAIN {
	DVD_DOMAIN_FirstPlay	= 1,
	DVD_DOMAIN_VideoManagerMenu,
	DVD_DOMAIN_VideoTitleSetMenu,
	DVD_DOMAIN_Title,
	DVD_DOMAIN_Stop
	}

.enum DVD_MENU_ID {
	DVD_MENU_Title	= 2,
	DVD_MENU_Root	= 3,
	DVD_MENU_Subpicture	= 4,
	DVD_MENU_Audio	= 5,
	DVD_MENU_Angle	= 6,
	DVD_MENU_Chapter	= 7
	}

.enum DVD_DISC_SIDE {
	DVD_SIDE_A	= 1,
	DVD_SIDE_B	= 2
	}

.enum DVD_PREFERRED_DISPLAY_MODE {
	DISPLAY_CONTENT_DEFAULT = 0,
	DISPLAY_16x9	= 1,
	DISPLAY_4x3_PANSCAN_PREFERRED	= 2,
	DISPLAY_4x3_LETTERBOX_PREFERRED = 3
	}

DVD_REGISTER		typedef WORD

DVD_ATR			STRUC
ulCAT			ULONG ?
pbATRI			db  768	 dup(?)
DVD_ATR			ENDS

.enum DVD_FRAMERATE {
	DVD_FPS_25	= 1,
	DVD_FPS_30NonDrop	= 3
	}

DVD_TIMECODE		STRUC
record
 Hours1			dd : 4 ?
 Hours10		dd : 4 ?
 Minutes1		dd : 4 ?
 Minutes10		dd : 4 ?
 Seconds1		dd : 4 ?
 Seconds10		dd : 4 ?
 Frames1		dd : 4 ?
 Frames10		dd : 2 ?
 FrameRateCode		dd : 2 ?
ends
DVD_TIMECODE		ENDS

.enum DVD_NavCmdType {
	DVD_NavCmdType_Pre	= 1,
	DVD_NavCmdType_Post	= 2,
	DVD_NavCmdType_Cell	= 3,
	DVD_NavCmdType_Button	= 4
	}

.enum DVD_TIMECODE_FLAGS {
	DVD_TC_FLAG_25fps	= 0x1,
	DVD_TC_FLAG_30fps	= 0x2,
	DVD_TC_FLAG_DropFrame	= 0x4,
	DVD_TC_FLAG_Interpolated = 0x8
	}

DVD_HMSF_TIMECODE	STRUC
bHours			db ?
bMinutes		db ?
bSeconds		db ?
bFrames			db ?
DVD_HMSF_TIMECODE	ENDS

DVD_PLAYBACK_LOCATION2	STRUC
TitleNum		ULONG ?
ChapterNum		ULONG ?
TimeCode		DVD_HMSF_TIMECODE <>
TimeCodeFlags		ULONG ?
DVD_PLAYBACK_LOCATION2	ENDS

DVD_PLAYBACK_LOCATION	STRUC
TitleNum		ULONG ?
ChapterNum		ULONG ?
TimeCode		ULONG ?
DVD_PLAYBACK_LOCATION	ENDS

VALID_UOP_SOMTHING_OR_OTHER typedef DWORD

.enum VALID_UOP_FLAG {
	UOP_FLAG_Play_Title_Or_AtTime	= 0x1,
	UOP_FLAG_Play_Chapter	= 0x2,
	UOP_FLAG_Play_Title	= 0x4,
	UOP_FLAG_Stop	= 0x8,
	UOP_FLAG_ReturnFromSubMenu	= 0x10,
	UOP_FLAG_Play_Chapter_Or_AtTime = 0x20,
	UOP_FLAG_PlayPrev_Or_Replay_Chapter	= 0x40,
	UOP_FLAG_PlayNext_Chapter	= 0x80,
	UOP_FLAG_Play_Forwards	= 0x100,
	UOP_FLAG_Play_Backwards = 0x200,
	UOP_FLAG_ShowMenu_Title = 0x400,
	UOP_FLAG_ShowMenu_Root	= 0x800,
	UOP_FLAG_ShowMenu_SubPic	= 0x1000,
	UOP_FLAG_ShowMenu_Audio = 0x2000,
	UOP_FLAG_ShowMenu_Angle = 0x4000,
	UOP_FLAG_ShowMenu_Chapter	= 0x8000,
	UOP_FLAG_Resume = 0x10000,
	UOP_FLAG_Select_Or_Activate_Button	= 0x20000,
	UOP_FLAG_Still_Off	= 0x40000,
	UOP_FLAG_Pause_On	= 0x80000,
	UOP_FLAG_Select_Audio_Stream	= 0x100000,
	UOP_FLAG_Select_SubPic_Stream	= 0x200000,
	UOP_FLAG_Select_Angle	= 0x400000,
	UOP_FLAG_Select_Karaoke_Audio_Presentation_Mode = 0x800000,
	UOP_FLAG_Select_Video_Mode_Preference	= 0x1000000
	}

.enum DVD_CMD_FLAGS {
	DVD_CMD_FLAG_None	= 0,
	DVD_CMD_FLAG_Flush	= 0x1,
	DVD_CMD_FLAG_SendEvents = 0x2,
	DVD_CMD_FLAG_Block	= 0x4,
	DVD_CMD_FLAG_StartWhenRendered	= 0x8,
	DVD_CMD_FLAG_EndAfterRendered	= 0x10
	}

.enum DVD_OPTION_FLAG {
	DVD_ResetOnStop = 1,
	DVD_NotifyParentalLevelChange	= 2,
	DVD_HMSF_TimeCodeEvents = 3,
	DVD_AudioDuringFFwdRew	= 4,
	DVD_EnableNonblockingAPIs	= 5,
	DVD_CacheSizeInMB	= 6,
	DVD_EnablePortableBookmarks	= 7,
	DVD_EnableExtendedCopyProtectErrors	= 8,
	DVD_NotifyPositionChange	= 9,
	DVD_IncreaseOutputControl	= 10,
	DVD_EnableStreaming	= 11,
	DVD_EnableESOutput	= 12,
	DVD_EnableTitleLength	= 13,
	DVD_DisableStillThrottle	= 14,
	DVD_EnableLoggingEvents = 15,
	DVD_MaxReadBurstInKB	= 16,
	DVD_ReadBurstPeriodInMS = 17
	}

.enum DVD_RELATIVE_BUTTON {
	DVD_Relative_Upper	= 1,
	DVD_Relative_Lower	= 2,
	DVD_Relative_Left	= 3,
	DVD_Relative_Right	= 4
	}

.enum DVD_PARENTAL_LEVEL {
	DVD_PARENTAL_LEVEL_8	= 0x8000,
	DVD_PARENTAL_LEVEL_7	= 0x4000,
	DVD_PARENTAL_LEVEL_6	= 0x2000,
	DVD_PARENTAL_LEVEL_5	= 0x1000,
	DVD_PARENTAL_LEVEL_4	= 0x800,
	DVD_PARENTAL_LEVEL_3	= 0x400,
	DVD_PARENTAL_LEVEL_2	= 0x200,
	DVD_PARENTAL_LEVEL_1	= 0x100
	}

.enum DVD_AUDIO_LANG_EXT {
	DVD_AUD_EXT_NotSpecified	= 0,
	DVD_AUD_EXT_Captions	= 1,
	DVD_AUD_EXT_VisuallyImpaired	= 2,
	DVD_AUD_EXT_DirectorComments1	= 3,
	DVD_AUD_EXT_DirectorComments2	= 4
	}

.enum DVD_SUBPICTURE_LANG_EXT {
	DVD_SP_EXT_NotSpecified = 0,
	DVD_SP_EXT_Caption_Normal	= 1,
	DVD_SP_EXT_Caption_Big	= 2,
	DVD_SP_EXT_Caption_Children	= 3,
	DVD_SP_EXT_CC_Normal	= 5,
	DVD_SP_EXT_CC_Big	= 6,
	DVD_SP_EXT_CC_Children	= 7,
	DVD_SP_EXT_Forced	= 9,
	DVD_SP_EXT_DirectorComments_Normal	= 13,
	DVD_SP_EXT_DirectorComments_Big = 14,
	DVD_SP_EXT_DirectorComments_Children	= 15
	}

.enum DVD_AUDIO_APPMODE {
	DVD_AudioMode_None	= 0,
	DVD_AudioMode_Karaoke	= 1,
	DVD_AudioMode_Surround	= 2,
	DVD_AudioMode_Other	= 3
	}

.enum DVD_AUDIO_FORMAT {
	DVD_AudioFormat_AC3	= 0,
	DVD_AudioFormat_MPEG1	= 1,
	DVD_AudioFormat_MPEG1_DRC	= 2,
	DVD_AudioFormat_MPEG2	= 3,
	DVD_AudioFormat_MPEG2_DRC	= 4,
	DVD_AudioFormat_LPCM	= 5,
	DVD_AudioFormat_DTS	= 6,
	DVD_AudioFormat_SDDS	= 7,
	DVD_AudioFormat_Other	= 8
	}

.enum DVD_KARAOKE_DOWNMIX {
	DVD_Mix_0to0	= 0x1,
	DVD_Mix_1to0	= 0x2,
	DVD_Mix_2to0	= 0x4,
	DVD_Mix_3to0	= 0x8,
	DVD_Mix_4to0	= 0x10,
	DVD_Mix_Lto0	= 0x20,
	DVD_Mix_Rto0	= 0x40,
	DVD_Mix_0to1	= 0x100,
	DVD_Mix_1to1	= 0x200,
	DVD_Mix_2to1	= 0x400,
	DVD_Mix_3to1	= 0x800,
	DVD_Mix_4to1	= 0x1000,
	DVD_Mix_Lto1	= 0x2000,
	DVD_Mix_Rto1	= 0x4000
	}

DVD_AudioAttributes	STRUC
AppMode			DVD_AUDIO_APPMODE ?
AppModeData		db ?
AudioFormat		DVD_AUDIO_FORMAT ?
Language		LCID ?
LanguageExtension	DVD_AUDIO_LANG_EXT ?
fHasMultichannelInfo	BOOL ?
dwFrequency		dd ?
bQuantization		db ?
bNumberOfChannels	db ?
dwReserved		dd 2 dup(?)
DVD_AudioAttributes	ENDS

DVD_MUA_MixingInfo	STRUC
fMixTo0			BOOL ?
fMixTo1			BOOL ?
fMix0InPhase		BOOL ?
fMix1InPhase		BOOL ?
dwSpeakerPosition	dd ?
DVD_MUA_MixingInfo	ENDS

DVD_MUA_Coeff		STRUC
log2_alpha		REAL8 ?
log2_beta		REAL8 ?
DVD_MUA_Coeff		ENDS

DVD_MultichannelAudioAttributes STRUC
Info			DVD_MUA_MixingInfo 8 dup(<>)
Coeff			DVD_MUA_Coeff 8 dup(<>)
DVD_MultichannelAudioAttributes ENDS

.enum DVD_KARAOKE_CONTENTS {
	DVD_Karaoke_GuideVocal1 = 0x1,
	DVD_Karaoke_GuideVocal2 = 0x2,
	DVD_Karaoke_GuideMelody1 = 0x4,
	DVD_Karaoke_GuideMelody2 = 0x8,
	DVD_Karaoke_GuideMelodyA = 0x10,
	DVD_Karaoke_GuideMelodyB = 0x20,
	DVD_Karaoke_SoundEffectA = 0x40,
	DVD_Karaoke_SoundEffectB = 0x80
	}

.enum DVD_KARAOKE_ASSIGNMENT {
	DVD_Assignment_reserved0 = 0,
	DVD_Assignment_reserved1 = 1,
	DVD_Assignment_LR	= 2,
	DVD_Assignment_LRM	= 3,
	DVD_Assignment_LR1	= 4,
	DVD_Assignment_LRM1	= 5,
	DVD_Assignment_LR12	= 6,
	DVD_Assignment_LRM12	= 7
	}

DVD_KaraokeAttributes	STRUC
bVersion		db ?
fMasterOfCeremoniesInGuideVocal1 BOOL ?
fDuet			BOOL ?
ChannelAssignment	DVD_KARAOKE_ASSIGNMENT ?
wChannelContents	dw  8  dup(?)
DVD_KaraokeAttributes	ENDS

.enum DVD_VIDEO_COMPRESSION {
	DVD_VideoCompression_Other	= 0,
	DVD_VideoCompression_MPEG1	= 1,
	DVD_VideoCompression_MPEG2	= 2
	}

DVD_VideoAttributes	STRUC
fPanscanPermitted	BOOL ?
fLetterboxPermitted	BOOL ?
ulAspectX		ULONG ?
ulAspectY		ULONG ?
ulFrameRate		ULONG ?
ulFrameHeight		ULONG ?
Compression		DVD_VIDEO_COMPRESSION ?
fLine21Field1InGOP	BOOL ?
fLine21Field2InGOP	BOOL ?
ulSourceResolutionX	ULONG ?
ulSourceResolutionY	ULONG ?
fIsSourceLetterboxed	BOOL ?
fIsFilmMode		BOOL ?
DVD_VideoAttributes	ENDS

.enum DVD_SUBPICTURE_TYPE {
	DVD_SPType_NotSpecified = 0,
	DVD_SPType_Language	= 1,
	DVD_SPType_Other	= 2
	}

.enum DVD_SUBPICTURE_CODING {
	DVD_SPCoding_RunLength	= 0,
	DVD_SPCoding_Extended	= 1,
	DVD_SPCoding_Other	= 2
	}

DVD_SubpictureAttributes STRUC
Type			DVD_SUBPICTURE_TYPE ?
CodingMode		DVD_SUBPICTURE_CODING ?
Language		LCID ?
LanguageExtension	DVD_SUBPICTURE_LANG_EXT ?
DVD_SubpictureAttributes ENDS

.enum DVD_TITLE_APPMODE {
	DVD_AppMode_Not_Specified = 0,
	DVD_AppMode_Karaoke	= 1,
	DVD_AppMode_Other	= 3
	}

DVD_TitleAttributes	STRUC
UNION
 AppMode		DVD_TITLE_APPMODE ?
 TitleLength		DVD_HMSF_TIMECODE <>
ENDS
VideoAttributes		DVD_VideoAttributes <>
ulNumberOfAudioStreams	ULONG ?
AudioAttributes		DVD_AudioAttributes 8 dup(<>)
MultichannelAudioAttributes DVD_MultichannelAudioAttributes 8 dup(<>)
ulNumberOfSubpictureStreams ULONG ?
SubpictureAttributes	DVD_SubpictureAttributes 32 dup(<>)
DVD_TitleAttributes	ENDS

DVD_MenuAttributes	STRUC
fCompatibleRegion	BOOL 8 dup(?)
VideoAttributes		DVD_VideoAttributes <>
fAudioPresent		BOOL ?
AudioAttributes		DVD_AudioAttributes <>
fSubpicturePresent	BOOL ?
SubpictureAttributes	DVD_SubpictureAttributes <>
DVD_MenuAttributes	ENDS

ifndef __IDvdControl_INTERFACE_DEFINED__
define __IDvdControl_INTERFACE_DEFINED__

DEFINE_IIDX(IDvdControl, "A70EFE61-E2A3-11d0-A9BE-00AA0061BE93")

.comdef IDvdControl : public IUnknown

    TitlePlay		proc :ULONG
    ChapterPlay		proc :ULONG, :ULONG
    TimePlay		proc :ULONG, :ULONG
    StopForResume	proc
    GoUp		proc
    TimeSearch		proc :ULONG
    ChapterSearch	proc :ULONG
    PrevPGSearch	proc
    TopPGSearch		proc
    NextPGSearch	proc
    ForwardScan		proc :REAL8
    BackwardScan	proc :REAL8
    MenuCall		proc :DVD_MENU_ID
    Resume		proc
    UpperButtonSelect	proc
    LowerButtonSelect	proc
    LeftButtonSelect	proc
    RightButtonSelect	proc
    ButtonActivate	proc
    ButtonSelectAndActivate proc :ULONG
    StillOff		proc
    PauseOn		proc
    PauseOff		proc
    MenuLanguageSelect	proc :LCID
    AudioStreamChange	proc :ULONG
    SubpictureStreamChange proc :ULONG, :BOOL
    AngleChange		proc :ULONG
    ParentalLevelSelect proc :ULONG
    ParentalCountrySelect proc :WORD
    KaraokeAudioPresentationModeChange proc :ULONG
    VideoModePreferrence proc :ULONG
    SetRoot		proc :LPCWSTR
    MouseActivate	proc :POINT
    MouseSelect		proc :POINT
    ChapterPlayAutoStop proc :ULONG, :ULONG, :ULONG
   .ends

endif

ifndef __IDvdInfo_INTERFACE_DEFINED__
define __IDvdInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IDvdInfo, "A70EFE60-E2A3-11d0-A9BE-00AA0061BE93")

.comdef IDvdInfo : public IUnknown

    GetCurrentDomain	proc :ptr
    GetCurrentLocation	proc :ptr
    GetTotalTitleTime	proc :ptr
    GetCurrentButton	proc :ptr, :ptr
    GetCurrentAngle	proc :ptr, :ptr
    GetCurrentAudio	proc :ptr, :ptr
    GetCurrentSubpicture proc :ptr, :ptr, :ptr
    GetCurrentUOPS	proc :ptr
    GetAllSPRMs		proc :ptr
    GetAllGPRMs		proc :ptr
    GetAudioLanguage	proc :ULONG, :ptr
    GetSubpictureLanguage proc :ULONG, :ptr
    GetTitleAttributes	proc :ULONG, :ptr
    GetVMGAttributes	proc :ptr
    GetCurrentVideoAttributes proc :ptr
    GetCurrentAudioAttributes proc :ptr
    GetCurrentSubpictureAttributes proc :ptr
    GetCurrentVolumeInfo proc :ptr, :ptr
    GetDVDTextInfo	proc :ptr, :ULONG, :ptr
    GetPlayerParentalLevel proc :ptr, :ptr
    GetNumberOfChapters proc :ULONG, :ptr
    GetTitleParentalLevels proc :ULONG, :ptr
    GetRoot		proc :LPSTR, :ULONG, :ptr
   .ends

endif

ifndef __IDvdCmd_INTERFACE_DEFINED__
define __IDvdCmd_INTERFACE_DEFINED__

DEFINE_IIDX(IDvdCmd, "5a4a97e4-94ee-4a55-9751-74b5643aa27d")

.comdef IDvdCmd : public IUnknown

    WaitForStart	proc
    WaitForEnd		proc
   .ends

endif

ifndef __IDvdState_INTERFACE_DEFINED__
define __IDvdState_INTERFACE_DEFINED__

DEFINE_IIDX(IDvdState, "86303d6d-1c4a-4087-ab42-f711167048ef")

.comdef IDvdState : public IUnknown

    GetDiscID		proc :ptr
    GetParentalLevel	proc :ptr
   .ends

endif

ifndef __IDvdControl2_INTERFACE_DEFINED__
define __IDvdControl2_INTERFACE_DEFINED__

DEFINE_IIDX(IDvdControl2, "33BC7430-EEC0-11D2-8201-00A0C9D74842")

.comdef IDvdControl2 : public IUnknown

    PlayTitle		proc :ULONG, :DWORD, :ptr
    PlayChapterInTitle	proc :ULONG, :ULONG, :DWORD, :ptr
    PlayAtTimeInTitle	proc :ULONG, :ptr, :DWORD, :ptr
    Stop		proc
    ReturnFromSubmenu	proc :DWORD, :ptr
    PlayAtTime		proc :ptr, :DWORD, :ptr
    PlayChapter		proc :ULONG, :DWORD, :ptr
    PlayPrevChapter	proc :DWORD, :ptr
    ReplayChapter	proc :DWORD, :ptr
    PlayNextChapter	proc :DWORD, :ptr
    PlayForwards	proc :REAL8, :DWORD, :ptr
    PlayBackwards	proc :REAL8, :DWORD, :ptr
    ShowMenu		proc :DVD_MENU_ID, :DWORD, :ptr
    Resume		proc :DWORD, :ptr
    SelectRelativeButton proc :DVD_RELATIVE_BUTTON
    ActivateButton	proc
    SelectButton	proc :ULONG
    SelectAndActivateButton proc :ULONG
    StillOff		proc
    _Pause		proc :BOOL
    SelectAudioStream	proc :ULONG, :DWORD, :ptr
    SelectSubpictureStream proc :ULONG, :DWORD, :ptr
    SetSubpictureState	proc :BOOL, :DWORD, :ptr
    SelectAngle		proc :ULONG, :DWORD, :ptr
    SelectParentalLevel proc :ULONG
    SelectParentalCountry proc :ptr
    SelectKaraokeAudioPresentationMode proc :ULONG
    SelectVideoModePreference proc :ULONG
    SetDVDDirectory	proc :LPCWSTR
    ActivateAtPosition	proc :POINT
    SelectAtPosition	proc :POINT
    PlayChaptersAutoStop proc :ULONG, :ULONG, :ULONG, :DWORD, :ptr
    AcceptParentalLevelChange proc :BOOL
    SetOption		proc :DVD_OPTION_FLAG, :BOOL
    SetState		proc :ptr, :DWORD, :ptr
    PlayPeriodInTitleAutoStop proc :ULONG, :ptr, :ptr, :DWORD, :ptr
    SetGPRM		proc :ULONG, :WORD, :DWORD, :ptr
    SelectDefaultMenuLanguage proc :LCID
    SelectDefaultAudioLanguage proc :LCID, :DVD_AUDIO_LANG_EXT
    SelectDefaultSubpictureLanguage proc :LCID, :DVD_SUBPICTURE_LANG_EXT
   .ends

endif

.enum DVD_TextStringType {
	DVD_Struct_Volume	= 0x1,
	DVD_Struct_Title	= 0x2,
	DVD_Struct_ParentalID	= 0x3,
	DVD_Struct_PartOfTitle	= 0x4,
	DVD_Struct_Cell		= 0x5,
	DVD_Stream_Audio	= 0x10,
	DVD_Stream_Subpicture	= 0x11,
	DVD_Stream_Angle	= 0x12,
	DVD_Channel_Audio	= 0x20,
	DVD_General_Name	= 0x30,
	DVD_General_Comments	= 0x31,
	DVD_Title_Series	= 0x38,
	DVD_Title_Movie		= 0x39,
	DVD_Title_Video		= 0x3a,
	DVD_Title_Album		= 0x3b,
	DVD_Title_Song		= 0x3c,
	DVD_Title_Other		= 0x3f,
	DVD_Title_Sub_Series	= 0x40,
	DVD_Title_Sub_Movie	= 0x41,
	DVD_Title_Sub_Video	= 0x42,
	DVD_Title_Sub_Album	= 0x43,
	DVD_Title_Sub_Song	= 0x44,
	DVD_Title_Sub_Other	= 0x47,
	DVD_Title_Orig_Series	= 0x48,
	DVD_Title_Orig_Movie	= 0x49,
	DVD_Title_Orig_Video	= 0x4a,
	DVD_Title_Orig_Album	= 0x4b,
	DVD_Title_Orig_Song	= 0x4c,
	DVD_Title_Orig_Other	= 0x4f,
	DVD_Other_Scene		= 0x50,
	DVD_Other_Cut		= 0x51,
	DVD_Other_Take		= 0x52
	}

.enum DVD_TextCharSet {
	DVD_CharSet_Unicode	= 0,
	DVD_CharSet_ISO646	= 1,
	DVD_CharSet_JIS_Roman_Kanji = 2,
	DVD_CharSet_ISO8859_1	= 3,
	DVD_CharSet_ShiftJIS_Kanji_Roman_Katakana = 4
	}

DVD_TITLE_MENU		equ 0x000
DVD_STREAM_DATA_CURRENT equ 0x800
DVD_STREAM_DATA_VMGM	equ 0x400
DVD_STREAM_DATA_VTSM	equ 0x401
DVD_DEFAULT_AUDIO_STREAM equ 0x0f

DVD_DECODER_CAPS	STRUC
dwSize			dd ?
dwAudioCaps		dd ?
dFwdMaxRateVideo	REAL8 ?
dFwdMaxRateAudio	REAL8 ?
dFwdMaxRateSP		REAL8 ?
dBwdMaxRateVideo	REAL8 ?
dBwdMaxRateAudio	REAL8 ?
dBwdMaxRateSP		REAL8 ?
dwRes1			dd ?
dwRes2			dd ?
dwRes3			dd ?
dwRes4			dd ?
DVD_DECODER_CAPS	ENDS

DVD_AUDIO_CAPS_AC3	equ 0x00000001
DVD_AUDIO_CAPS_MPEG2	equ 0x00000002
DVD_AUDIO_CAPS_LPCM	equ 0x00000004
DVD_AUDIO_CAPS_DTS	equ 0x00000008
DVD_AUDIO_CAPS_SDDS	equ 0x00000010

ifndef __IDvdInfo2_INTERFACE_DEFINED__
define __IDvdInfo2_INTERFACE_DEFINED__

DEFINE_IIDX(IDvdInfo2, "34151510-EEC0-11D2-8201-00A0C9D74842")

.comdef IDvdInfo2 : public IUnknown

    GetCurrentDomain	proc :ptr
    GetCurrentLocation	proc :ptr
    GetTotalTitleTime	proc :ptr, :ptr
    GetCurrentButton	proc :ptr, :ptr
    GetCurrentAngle	proc :ptr, :ptr
    GetCurrentAudio	proc :ptr, :ptr
    GetCurrentSubpicture proc :ptr, :ptr, :ptr
    GetCurrentUOPS	proc :ptr
    GetAllSPRMs		proc :ptr
    GetAllGPRMs		proc :ptr
    GetAudioLanguage	proc :ULONG, :ptr
    GetSubpictureLanguage proc :ULONG, :ptr
    GetTitleAttributes	proc :ULONG, :ptr, :ptr
    GetVMGAttributes	proc :ptr
    GetCurrentVideoAttributes proc :ptr
    GetAudioAttributes	proc :ULONG, :ptr
    GetKaraokeAttributes proc :ULONG, :ptr
    GetSubpictureAttributes proc :ULONG, :ptr
    GetDVDVolumeInfo	proc :ptr, :ptr, :ptr, :ptr
    GetDVDTextNumberOfLanguages proc :ptr
    GetDVDTextLanguageInfo proc :ULONG, :ptr, :ptr, :ptr
    GetDVDTextStringAsNative proc :ULONG, :ULONG, :ptr, :ULONG, :ptr, :ptr
    GetDVDTextStringAsUnicode proc :ULONG, :ULONG, :ptr, :ULONG, :ptr, :ptr
    GetPlayerParentalLevel proc :ptr, :BYTE
    GetNumberOfChapters proc :ULONG, :ptr
    GetTitleParentalLevels proc :ULONG, :ptr
    GetDVDDirectory	proc :LPWSTR, :ULONG, :ptr
    IsAudioStreamEnabled proc :ULONG, :ptr
    GetDiscID		proc :LPCWSTR, :ptr
    GetState		proc :ptr
    GetMenuLanguages	proc :ptr, :ULONG, :ptr
    GetButtonAtPosition proc :POINT, :ptr
    GetCmdFromEvent	proc :LONG_PTR, :ptr
    GetDefaultMenuLanguage proc :ptr
    GetDefaultAudioLanguage proc :ptr, :ptr
    GetDefaultSubpictureLanguage proc :ptr, :ptr
    GetDecoderCaps	proc :ptr
    GetButtonRect	proc :ULONG, :ptr
    IsSubpictureStreamEnabled proc :ULONG, :ptr
   .ends

endif

.enum AM_DVD_GRAPH_FLAGS {
	AM_DVD_HWDEC_PREFER	= 0x1,
	AM_DVD_HWDEC_ONLY	= 0x2,
	AM_DVD_SWDEC_PREFER	= 0x4,
	AM_DVD_SWDEC_ONLY	= 0x8,
	AM_DVD_NOVPE	= 0x100,
	AM_DVD_DO_NOT_CLEAR	= 0x200,
	AM_DVD_VMR9_ONLY	= 0x800,
	AM_DVD_EVR_ONLY = 0x1000,
	AM_DVD_EVR_QOS	= 0x2000,
	AM_DVD_ADAPT_GRAPH	= 0x4000,
	AM_DVD_MASK	= 0xffff
	}

.enum AM_DVD_STREAM_FLAGS {
	AM_DVD_STREAM_VIDEO	= 0x1,
	AM_DVD_STREAM_AUDIO	= 0x2,
	AM_DVD_STREAM_SUBPIC	= 0x4
	}

AM_DVD_RENDERSTATUS	STRUC
hrVPEStatus		HRESULT ?
bDvdVolInvalid		BOOL ?
bDvdVolUnknown		BOOL ?
bNoLine21In		BOOL ?
bNoLine21Out		BOOL ?
iNumStreams		SINT ?
iNumStreamsFailed	SINT ?
dwFailedStreamsFlag	dd ?
AM_DVD_RENDERSTATUS	ENDS

ifndef __IDvdGraphBuilder_INTERFACE_DEFINED__
define __IDvdGraphBuilder_INTERFACE_DEFINED__

DEFINE_IIDX(IDvdGraphBuilder, "FCC152B6-F372-11d0-8E00-00C04FD7C08B")

.comdef IDvdGraphBuilder : public IUnknown

    GetFiltergraph	proc :ptr
    GetDvdInterface	proc :REFIID, :ptr
    RenderDvdVideoVolume proc :LPCWSTR, :DWORD, :ptr
   .ends

endif

ifndef __IDDrawExclModeVideo_INTERFACE_DEFINED__
define __IDDrawExclModeVideo_INTERFACE_DEFINED__

DEFINE_IIDX(IDDrawExclModeVideo, "153ACC21-D83B-11d1-82BF-00A0C9696C8F")

.comdef IDDrawExclModeVideo : public IUnknown

    SetDDrawObject	proc :ptr
    GetDDrawObject	proc :ptr, :ptr
    SetDDrawSurface	proc :ptr
    GetDDrawSurface	proc :ptr, :ptr
    SetDrawParameters	proc :ptr, :ptr
    GetNativeVideoProps proc :ptr, :ptr, :ptr, :ptr
    SetCallbackInterface proc :ptr, :DWORD
   .ends

endif

.enum AM_OVERLAY_NOTIFY_FLAGS {
	AM_OVERLAY_NOTIFY_VISIBLE_CHANGE = 0x1,
	AM_OVERLAY_NOTIFY_SOURCE_CHANGE = 0x2,
	AM_OVERLAY_NOTIFY_DEST_CHANGE	= 0x4
	}

ifndef __IDDrawExclModeVideoCallback_INTERFACE_DEFINED__
define __IDDrawExclModeVideoCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IDDrawExclModeVideoCallback, "913c24a0-20ab-11d2-9038-00a0c9697298")

.comdef IDDrawExclModeVideoCallback : public IUnknown

    OnUpdateOverlay	proc :BOOL, :DWORD, :BOOL, :ptr, :ptr, :BOOL, :ptr, :ptr
    OnUpdateColorKey	proc :ptr, :DWORD
    OnUpdateSize	proc :DWORD, :DWORD, :DWORD, :DWORD
   .ends

endif

ifndef __IPinConnection_INTERFACE_DEFINED__
define __IPinConnection_INTERFACE_DEFINED__

DEFINE_IIDX(IPinConnection, "4a9a62d3-27d4-403d-91e9-89f540e55534")

.comdef IPinConnection : public IUnknown

    DynamicQueryAccept	proc :ptr
    NotifyEndOfStream	proc :HANDLE
    IsEndPin		proc
    DynamicDisconnect	proc
   .ends

endif

ifndef __IPinFlowControl_INTERFACE_DEFINED__
define __IPinFlowControl_INTERFACE_DEFINED__

DEFINE_IIDX(IPinFlowControl, "c56e9858-dbf3-4f6b-8119-384af2060deb")

.comdef IPinFlowControl : public IUnknown

    Block		proc :DWORD, :HANDLE
   .ends

endif

.enum AM_PIN_FLOW_CONTROL_BLOCK_FLAGS {
	AM_PIN_FLOW_CONTROL_BLOCK = 0x1
	}
.enum AM_GRAPH_CONFIG_RECONNECT_FLAGS {
	AM_GRAPH_CONFIG_RECONNECT_DIRECTCONNECT = 0x1,
	AM_GRAPH_CONFIG_RECONNECT_CACHE_REMOVED_FILTERS = 0x2,
	AM_GRAPH_CONFIG_RECONNECT_USE_ONLY_CACHED_FILTERS = 0x4
	}
.enum REM_FILTER_FLAGS {
	REMFILTERF_LEAVECONNECTED = 0x1
	}
.enum AM_FILTER_FLAGS {
	AM_FILTER_FLAGS_REMOVABLE = 0x1
	}

ifndef __IGraphConfig_INTERFACE_DEFINED__
define __IGraphConfig_INTERFACE_DEFINED__

DEFINE_IIDX(IGraphConfig, "03A1EB8E-32BF-4245-8502-114D08A9CB88")

.comdef IGraphConfig : public IUnknown

    Reconnect		proc :ptr, :ptr, :ptr, :ptr, :HANDLE, :DWORD
    Reconfigure		proc :ptr, :PVOID, :DWORD, :HANDLE
    AddFilterToCache	proc :ptr
    EnumCacheFilter	proc :ptr
    RemoveFilterFromCache proc :ptr
    GetStartTime	proc :ptr
    PushThroughData	proc :ptr, :ptr, :HANDLE
    SetFilterFlags	proc :ptr, :DWORD
    GetFilterFlags	proc :ptr, :ptr
    RemoveFilterEx	proc :ptr, :DWORD
   .ends

endif

ifndef __IGraphConfigCallback_INTERFACE_DEFINED__
define __IGraphConfigCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IGraphConfigCallback, "ade0fd60-d19d-11d2-abf6-00a0c905f375")

.comdef IGraphConfigCallback : public IUnknown

    Reconfigure		proc :PVOID, :DWORD
   .ends

endif

ifndef __IFilterChain_INTERFACE_DEFINED__
define __IFilterChain_INTERFACE_DEFINED__

DEFINE_IIDX(IFilterChain, "DCFBDCF6-0DC2-45f5-9AB2-7C330EA09C29")

.comdef IFilterChain : public IUnknown

    StartChain		proc :ptr, :ptr
    PauseChain		proc :ptr, :ptr
    StopChain		proc :ptr, :ptr
    RemoveChain		proc :ptr, :ptr
   .ends

endif

include ddraw.inc

.enum VMRPresentationFlags {
	VMRSample_SyncPoint	= 0x1,
	VMRSample_Preroll	= 0x2,
	VMRSample_Discontinuity = 0x4,
	VMRSample_TimeValid	= 0x8,
	VMRSample_SrcDstRectsValid	= 0x10
	}

VMRPRESENTATIONINFO	STRUC
dwFlags			dd ?
lpSurf			LPDIRECTDRAWSURFACE7 ?
rtStart			REFERENCE_TIME ?
rtEnd			REFERENCE_TIME ?
szAspectRatio		SIZEL <>
rcSrc			RECT <>
rcDst			RECT <>
dwTypeSpecificFlags	dd ?
dwInterlaceFlags	dd ?
VMRPRESENTATIONINFO	ENDS

ifndef __IVMRImagePresenter_INTERFACE_DEFINED__
define __IVMRImagePresenter_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRImagePresenter, "CE704FE7-E71E-41fb-BAA2-C4403E1182F5")

.comdef IVMRImagePresenter : public IUnknown

    StartPresenting	proc :DWORD_PTR
    StopPresenting	proc :DWORD_PTR
    PresentImage	proc :DWORD_PTR, :ptr
   .ends

endif

.enum VMRSurfaceAllocationFlags {
	AMAP_PIXELFORMAT_VALID	= 0x1,
	AMAP_3D_TARGET	= 0x2,
	AMAP_ALLOW_SYSMEM	= 0x4,
	AMAP_FORCE_SYSMEM	= 0x8,
	AMAP_DIRECTED_FLIP	= 0x10,
	AMAP_DXVA_TARGET	= 0x20
	}

VMRALLOCATIONINFO	STRUC
dwFlags			dd ?
lpHdr			LPBITMAPINFOHEADER ?
lpPixFmt		LPDDPIXELFORMAT ?
szAspectRatio		SIZEL <>
dwMinBuffers		dd ?
dwMaxBuffers		dd ?
dwInterlaceFlags	dd ?
szNativeSize		SIZEL <>
VMRALLOCATIONINFO	ENDS

ifndef __IVMRSurfaceAllocator_INTERFACE_DEFINED__
define __IVMRSurfaceAllocator_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRSurfaceAllocator, "31ce832e-4484-458b-8cca-f4d7e3db0b52")

.comdef IVMRSurfaceAllocator : public IUnknown

    AllocateSurface	proc :DWORD_PTR, :ptr, :ptr, :ptr
    FreeSurface		proc :DWORD_PTR
    PrepareSurface	proc :DWORD_PTR, :LPDIRECTDRAWSURFACE7, :DWORD
    AdviseNotify	proc :ptr
   .ends

endif


ifndef __IVMRSurfaceAllocatorNotify_INTERFACE_DEFINED__
define __IVMRSurfaceAllocatorNotify_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRSurfaceAllocatorNotify, "aada05a8-5a4e-4729-af0b-cea27aed51e2")

.comdef IVMRSurfaceAllocatorNotify : public IUnknown

    AdviseSurfaceAllocator proc :DWORD_PTR, :ptr
    SetDDrawDevice	proc :LPDIRECTDRAW7, :HMONITOR
    ChangeDDrawDevice	proc :LPDIRECTDRAW7, :HMONITOR
    RestoreDDrawSurfaces proc
    NotifyEvent		proc :LONG, :LONG_PTR, :LONG_PTR
    SetBorderColor	proc :COLORREF
   .ends

endif

VMR_ASPECT_RATIO_MODE	typedef SDWORD
VMR_ARMODE_NONE		equ 0
VMR_ARMODE_LETTER_BOX	equ ( VMR_ARMODE_NONE + 1 )

ifndef __IVMRWindowlessControl_INTERFACE_DEFINED__
define __IVMRWindowlessControl_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRWindowlessControl, "0eb1088c-4dcd-46f0-878f-39dae86a51b7")

.comdef IVMRWindowlessControl : public IUnknown

    GetNativeVideoSize	proc :ptr, :ptr, :ptr, :ptr
    GetMinIdealVideoSize proc :ptr, :ptr
    GetMaxIdealVideoSize proc :ptr, :ptr
    SetVideoPosition	proc :LPRECT, :LPRECT
    GetVideoPosition	proc :LPRECT, :LPRECT
    GetAspectRatioMode	proc :ptr
    SetAspectRatioMode	proc :DWORD
    SetVideoClippingWindow proc :HWND
    RepaintVideo	proc :HWND, :HDC
    DisplayModeChanged	proc
    GetCurrentImage	proc :ptr
    SetBorderColor	proc :COLORREF
    GetBorderColor	proc :ptr
    SetColorKey		proc :COLORREF
    GetColorKey		proc :ptr
   .ends

endif

.enum VMRMixerPrefs {
	MixerPref_NoDecimation		= 0x1,
	MixerPref_DecimateOutput	= 0x2,
	MixerPref_ARAdjustXorY		= 0x4,
	MixerPref_DecimationReserved	= 0x8,
	MixerPref_DecimateMask		= 0xf,
	MixerPref_BiLinearFiltering	= 0x10,
	MixerPref_PointFiltering	= 0x20,
	MixerPref_FilteringMask		= 0xf0,
	MixerPref_RenderTargetRGB	= 0x100,
	MixerPref_RenderTargetYUV	= 0x1000,
	MixerPref_RenderTargetYUV420	= 0x200,
	MixerPref_RenderTargetYUV422	= 0x400,
	MixerPref_RenderTargetYUV444	= 0x800,
	MixerPref_RenderTargetReserved	= 0xe000,
	MixerPref_RenderTargetMask	= 0xff00,
	MixerPref_DynamicSwitchToBOB	= 0x10000,
	MixerPref_DynamicDecimateBy2	= 0x20000,
	MixerPref_DynamicReserved	= 0xc0000,
	MixerPref_DynamicMask		= 0xf0000
	}

NORMALIZEDRECT		STRUC
left			REAL4 ?
top			REAL4 ?
right			REAL4 ?
bottom			REAL4 ?
NORMALIZEDRECT		ENDS

PNORMALIZEDRECT		typedef ptr NORMALIZEDRECT

ifndef __IVMRMixerControl_INTERFACE_DEFINED__
define __IVMRMixerControl_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRMixerControl, "1c1a17b0-bed0-415d-974b-dc6696131599")

.comdef IVMRMixerControl : public IUnknown

    SetAlpha		proc :DWORD, :REAL4
    GetAlpha		proc :DWORD, :ptr
    SetZOrder		proc :DWORD, :DWORD
    GetZOrder		proc :DWORD, :ptr
    SetOutputRect	proc :DWORD, :ptr
    GetOutputRect	proc :DWORD, :ptr
    SetBackgroundClr	proc :COLORREF
    GetBackgroundClr	proc :ptr
    SetMixingPrefs	proc :DWORD
    GetMixingPrefs	proc :ptr
   .ends

endif

VMRGUID			STRUC
pGUID			LPGUID ?
GUID			GUID <>
VMRGUID			ENDS

VMRMONITORINFO		STRUC
guid			VMRGUID <>
rcMonitor		RECT <>
hMon			HMONITOR ?
dwFlags			dd ?
szDevice		wchar_t	 32  dup(?)
szDescription		wchar_t	 256  dup(?)
liDriverVersion		LARGE_INTEGER <>
dwVendorId		dd ?
dwDeviceId		dd ?
dwSubSysId		dd ?
dwRevision		dd ?
VMRMONITORINFO		ENDS

ifndef __IVMRMonitorConfig_INTERFACE_DEFINED__
define __IVMRMonitorConfig_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRMonitorConfig, "9cf0b1b6-fbaa-4b7f-88cf-cf1f130a0dce")

.comdef IVMRMonitorConfig : public IUnknown

    SetMonitor		proc :ptr
    GetMonitor		proc :ptr
    SetDefaultMonitor	proc :ptr
    GetDefaultMonitor	proc :ptr
    GetAvailableMonitors proc :ptr, :DWORD, :ptr
   .ends

endif

.enum VMRRenderPrefs {
	RenderPrefs_RestrictToInitialMonitor = 0,
	RenderPrefs_ForceOffscreen	= 0x1,
	RenderPrefs_ForceOverlays	= 0x2,
	RenderPrefs_AllowOverlays	= 0,
	RenderPrefs_AllowOffscreen	= 0,
	RenderPrefs_DoNotRenderColorKeyAndBorder = 0x8,
	RenderPrefs_Reserved	= 0x10,
	RenderPrefs_PreferAGPMemWhenMixing = 0x20,
	RenderPrefs_Mask	= 0x3f
	}

.enum VMRMode {
	VMRMode_Windowed	= 0x1,
	VMRMode_Windowless	= 0x2,
	VMRMode_Renderless	= 0x4,
	VMRMode_Mask		= 0x7
	}

.enum __MIDL___MIDL_itf_strmif_0000_0131_0001 {
	MAX_NUMBER_OF_STREAMS	= 16
	}

ifndef __IVMRFilterConfig_INTERFACE_DEFINED__
define __IVMRFilterConfig_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRFilterConfig, "9e5530c5-7034-48b4-bb46-0b8a6efc8e36")

.comdef IVMRFilterConfig : public IUnknown

    SetImageCompositor	proc :ptr
    SetNumberOfStreams	proc :DWORD
    GetNumberOfStreams	proc :ptr
    SetRenderingPrefs	proc :DWORD
    GetRenderingPrefs	proc :ptr
    SetRenderingMode	proc :DWORD
    GetRenderingMode	proc :ptr
   .ends

endif

ifndef __IVMRAspectRatioControl_INTERFACE_DEFINED__
define __IVMRAspectRatioControl_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRAspectRatioControl, "ede80b5c-bad6-4623-b537-65586c9f8dfd")

.comdef IVMRAspectRatioControl : public IUnknown

    GetAspectRatioMode	proc :LPDWORD
    SetAspectRatioMode	proc :DWORD
   .ends

endif

.enum VMRDeinterlacePrefs {
	DeinterlacePref_NextBest = 0x1,
	DeinterlacePref_BOB	= 0x2,
	DeinterlacePref_Weave	= 0x4,
	DeinterlacePref_Mask	= 0x7
	}

.enum VMRDeinterlaceTech {
	DeinterlaceTech_Unknown = 0,
	DeinterlaceTech_BOBLineReplicate	= 0x1,
	DeinterlaceTech_BOBVerticalStretch	= 0x2,
	DeinterlaceTech_MedianFiltering = 0x4,
	DeinterlaceTech_EdgeFiltering	= 0x10,
	DeinterlaceTech_FieldAdaptive	= 0x20,
	DeinterlaceTech_PixelAdaptive	= 0x40,
	DeinterlaceTech_MotionVectorSteered	= 0x80
	}

VMRFrequency		STRUC
dwNumerator		dd ?
dwDenominator		dd ?
VMRFrequency		ENDS

VMRVideoDesc		STRUC
dwSize			dd ?
dwSampleWidth		dd ?
dwSampleHeight		dd ?
SingleFieldPerSample	BOOL ?
dwFourCC		dd ?
InputSampleFreq		VMRFrequency <>
OutputFrameFreq		VMRFrequency <>
VMRVideoDesc		ENDS

VMRDeinterlaceCaps	STRUC
dwSize			dd ?
dwNumPreviousOutputFrames dd ?
dwNumForwardRefSamples	dd ?
dwNumBackwardRefSamples dd ?
DeinterlaceTechnology	VMRDeinterlaceTech ?
VMRDeinterlaceCaps	ENDS

ifndef __IVMRDeinterlaceControl_INTERFACE_DEFINED__
define __IVMRDeinterlaceControl_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRDeinterlaceControl, "bb057577-0db8-4e6a-87a7-1a8c9a505a0f")

.comdef IVMRDeinterlaceControl : public IUnknown

    GetNumberOfDeinterlaceModes proc :ptr, :LPDWORD, :LPGUID
    GetDeinterlaceModeCaps proc :LPGUID, :ptr, :ptr
    GetDeinterlaceMode	proc :DWORD, :LPGUID
    SetDeinterlaceMode	proc :DWORD, :LPGUID
    GetDeinterlacePrefs proc :LPDWORD
    SetDeinterlacePrefs proc :DWORD
    GetActualDeinterlaceMode proc :DWORD, :LPGUID
   .ends

endif

VMRALPHABITMAP		STRUC
dwFlags			dd ?
hdc			HDC ?
pDDS			LPDIRECTDRAWSURFACE7 ?
rSrc			RECT <>
rDest			NORMALIZEDRECT <>
fAlpha			FLOAT ?
clrSrcKey		COLORREF ?
VMRALPHABITMAP		ENDS

PVMRALPHABITMAP		typedef ptr VMRALPHABITMAP

VMRBITMAP_DISABLE	equ 0x00000001
VMRBITMAP_HDC		equ 0x00000002
VMRBITMAP_ENTIREDDS	equ 0x00000004
VMRBITMAP_SRCCOLORKEY	equ 0x00000008
VMRBITMAP_SRCRECT	equ 0x00000010

ifndef __IVMRMixerBitmap_INTERFACE_DEFINED__
define __IVMRMixerBitmap_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRMixerBitmap, "1E673275-0257-40aa-AF20-7C608D4A0428")

.comdef IVMRMixerBitmap : public IUnknown

    SetAlphaBitmap	proc :ptr
    UpdateAlphaBitmapParameters proc :PVMRALPHABITMAP
    GetAlphaBitmapParameters proc :PVMRALPHABITMAP
   .ends

endif

VMRVIDEOSTREAMINFO	STRUC
pddsVideoSurface	LPDIRECTDRAWSURFACE7 ?
dwWidth			dd ?
dwHeight		dd ?
dwStrmID		dd ?
fAlpha			FLOAT ?
ddClrKey		DDCOLORKEY <>
rNormal			NORMALIZEDRECT <>
VMRVIDEOSTREAMINFO	ENDS

ifndef __IVMRImageCompositor_INTERFACE_DEFINED__
define __IVMRImageCompositor_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRImageCompositor, "7a4fb5af-479f-4074-bb40-ce6722e43c82")

.comdef IVMRImageCompositor : public IUnknown

    InitCompositionTarget proc :ptr, :LPDIRECTDRAWSURFACE7
    TermCompositionTarget proc :ptr, :LPDIRECTDRAWSURFACE7
    SetStreamMediaType	proc :DWORD, :ptr, :BOOL
    CompositeImage	proc :ptr, :LPDIRECTDRAWSURFACE7, :ptr, :REFERENCE_TIME, :REFERENCE_TIME, :DWORD, :ptr, :UINT
   .ends

endif

ifndef __IVMRVideoStreamControl_INTERFACE_DEFINED__
define __IVMRVideoStreamControl_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRVideoStreamControl, "058d1f11-2a54-4bef-bd54-df706626b727")

.comdef IVMRVideoStreamControl : public IUnknown

    SetColorKey		proc :LPDDCOLORKEY
    GetColorKey		proc :LPDDCOLORKEY
    SetStreamActiveState proc :BOOL
    GetStreamActiveState proc :ptr
   .ends

endif


ifndef __IVMRSurface_INTERFACE_DEFINED__
define __IVMRSurface_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRSurface, "a9849bbe-9ec8-4263-b764-62730f0d15d0")

.comdef IVMRSurface : public IUnknown

    IsSurfaceLocked	proc
    LockSurface		proc :ptr
    UnlockSurface	proc
    GetSurface		proc :ptr
   .ends

endif

ifndef __IVMRImagePresenterConfig_INTERFACE_DEFINED__
define __IVMRImagePresenterConfig_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRImagePresenterConfig, "9f3a1c85-8555-49ba-935f-be5b5b29d178")

.comdef IVMRImagePresenterConfig : public IUnknown

    SetRenderingPrefs	proc :DWORD
    GetRenderingPrefs	proc :ptr
   .ends

endif

ifndef __IVMRImagePresenterExclModeConfig_INTERFACE_DEFINED__
define __IVMRImagePresenterExclModeConfig_INTERFACE_DEFINED__

DEFINE_IIDX(IVMRImagePresenterExclModeConfig, "e6f7ce40-4673-44f1-8f77-5499d68cb4ea")

.comdef IVMRImagePresenterExclModeConfig : public IVMRImagePresenterConfig

    SetXlcModeDDObjAndPrimarySurface proc :LPDIRECTDRAW7, :LPDIRECTDRAWSURFACE7
    GetXlcModeDDObjAndPrimarySurface proc :ptr, :ptr
   .ends

endif


ifndef __IVPManager_INTERFACE_DEFINED__
define __IVPManager_INTERFACE_DEFINED__

DEFINE_IIDX(IVPManager, "aac18c18-e186-46d2-825d-a1f8dc8e395a")

.comdef IVPManager : public IUnknown

    SetVideoPortIndex	proc :DWORD
    GetVideoPortIndex	proc :ptr
   .ends

endif

endif
