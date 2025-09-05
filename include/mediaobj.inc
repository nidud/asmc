ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __mediaobj_h__
define __mediaobj_h__

ifndef __unknwn_h__
include unknwn.inc
endif
include objidl.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

ifdef __strmif_h__
DMO_MEDIA_TYPE		typedef AM_MEDIA_TYPE
else
DMO_MEDIA_TYPE		STRUC
majortype		GUID <>
subtype			GUID <>
bFixedSizeSamples	BOOL ?
bTemporalCompression	BOOL ?
lSampleSize		ULONG ?
formattype		GUID <>
pUnk			LPUNKNOWN ?
cbFormat		ULONG ?
pbFormat		LPBYTE ?
DMO_MEDIA_TYPE		ENDS
REFERENCE_TIME		typedef LONGLONG

endif

.enum DMO_INPUT_DATA_BUFFER_FLAGS {
    DMO_INPUT_DATA_BUFFERF_SYNCPOINT	= 0x1,
    DMO_INPUT_DATA_BUFFERF_TIME		= 0x2,
    DMO_INPUT_DATA_BUFFERF_TIMELENGTH	= 0x4,
    DMO_INPUT_DATA_BUFFERF_DISCONTINUITY= 0x8
    }

.enum DMO_OUTPUT_DATA_BUFFER_FLAGS {
    DMO_OUTPUT_DATA_BUFFERF_SYNCPOINT	= 0x1,
    DMO_OUTPUT_DATA_BUFFERF_TIME	= 0x2,
    DMO_OUTPUT_DATA_BUFFERF_TIMELENGTH	= 0x4,
    DMO_OUTPUT_DATA_BUFFERF_DISCONTINUITY= 0x8,
    DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE	= 0x1000000
    }

.enum DMO_INPUT_STATUS_FLAGS {
    DMO_INPUT_STATUSF_ACCEPT_DATA	= 0x1
    }

.enum DMO_INPUT_STREAM_INFO_FLAGS {
    DMO_INPUT_STREAMF_WHOLE_SAMPLES	= 0x1,
    DMO_INPUT_STREAMF_SINGLE_SAMPLE_PER_BUFFER	= 0x2,
    DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE = 0x4,
    DMO_INPUT_STREAMF_HOLDS_BUFFERS	= 0x8
    }

.enum DMO_OUTPUT_STREAM_INFO_FLAGS {
    DMO_OUTPUT_STREAMF_WHOLE_SAMPLES	= 0x1,
    DMO_OUTPUT_STREAMF_SINGLE_SAMPLE_PER_BUFFER = 0x2,
    DMO_OUTPUT_STREAMF_FIXED_SAMPLE_SIZE	= 0x4,
    DMO_OUTPUT_STREAMF_DISCARDABLE	= 0x8,
    DMO_OUTPUT_STREAMF_OPTIONAL = 0x10
    }

.enum DMO_SET_TYPE_FLAGS {
    DMO_SET_TYPEF_TEST_ONLY	= 0x1,
    DMO_SET_TYPEF_CLEAR = 0x2
    }

.enum DMO_PROCESS_OUTPUT_FLAGS {
    DMO_PROCESS_OUTPUT_DISCARD_WHEN_NO_BUFFER	= 0x1
    }

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMediaBuffer_INTERFACE_DEFINED__
define __IMediaBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaBuffer, "59eff8b9-938c-4a26-82f2-95cb84cdc837")

.comdef IMediaBuffer : public IUnknown

    SetLength		proc :DWORD
    GetMaxLength	proc :ptr
    GetBufferAndLength	proc
   .ends
    LPIMediaBuffer	typedef ptr IMediaBuffer

endif

DMO_OUTPUT_DATA_BUFFER	STRUC
pBuffer			LPIMediaBuffer ?
dwStatus		dd ?
rtTimestamp		REFERENCE_TIME ?
rtTimelength		REFERENCE_TIME ?
DMO_OUTPUT_DATA_BUFFER	ENDS

PDMO_OUTPUT_DATA_BUFFER typedef ptr DMO_OUTPUT_DATA_BUFFER

ifndef __IMediaObject_INTERFACE_DEFINED__
define __IMediaObject_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaObject, "d8ad0f58-5494-4102-97c5-ec798e59bcf4")

.comdef IMediaObject : public IUnknown

    GetStreamCount	proc :ptr, :ptr
    GetInputStreamInfo	proc :DWORD, :ptr
    GetOutputStreamInfo proc :DWORD, :ptr
    GetInputType	proc :DWORD, :DWORD, :ptr
    GetOutputType	proc :DWORD, :DWORD, :ptr
    SetInputType	proc :DWORD, :ptr, :DWORD
    SetOutputType	proc :DWORD, :ptr, :DWORD
    GetInputCurrentType proc :DWORD, :ptr
    GetOutputCurrentType proc :DWORD, :ptr
    GetInputSizeInfo	proc :DWORD, :ptr, :ptr, :ptr
    GetOutputSizeInfo	proc :DWORD, :ptr, :ptr
    GetInputMaxLatency	proc :DWORD, :ptr
    SetInputMaxLatency	proc :DWORD, :REFERENCE_TIME
    Flush		proc
    Discontinuity	proc :DWORD
    AllocateStreamingResources proc
    FreeStreamingResources proc
    GetInputStatus	proc :DWORD, :ptr
    ProcessInput	proc :DWORD, :ptr, :DWORD, :REFERENCE_TIME, :REFERENCE_TIME
    ProcessOutput	proc :DWORD, :DWORD
    _Lock		proc :LONG
   .ends

endif

ifndef __IEnumDMO_INTERFACE_DEFINED__
define __IEnumDMO_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumDMO, "2c3cd98a-2bfa-4a53-9c27-5249ba64ba0f")

.comdef IEnumDMO : public IUnknown

    Next		proc :DWORD, :ptr, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr
   .ends

endif

.enum DMO_INPLACE_PROCESS_FLAGS {
    DMO_INPLACE_NORMAL	= 0,
    DMO_INPLACE_ZERO	= 0x1
    }

ifndef __IMediaObjectInPlace_INTERFACE_DEFINED__
define __IMediaObjectInPlace_INTERFACE_DEFINED__

DEFINE_IIDX(IMediaObjectInPlace, "651b9ad0-0fc7-4aa9-9538-d89931010741")

.comdef IMediaObjectInPlace : public IUnknown

    Process		proc :ULONG
    Clone		proc :ptr
    GetLatency		proc :ptr
   .ends

endif

.enum DMO_QUALITY_STATUS_FLAGS {
    DMO_QUALITY_STATUS_ENABLED	= 0x1
    }

ifndef __IDMOQualityControl_INTERFACE_DEFINED__
define __IDMOQualityControl_INTERFACE_DEFINED__

DEFINE_IIDX(IDMOQualityControl, "65abea96-cf36-453f-af8a-705e98f16260")

.comdef IDMOQualityControl : public IUnknown

    SetNow		proc :REFERENCE_TIME
    SetStatus		proc :DWORD
    GetStatus		proc :ptr
   .ends

endif

.enum DMO_VIDEO_OUTPUT_STREAM_FLAGS {
    DMO_VOSF_NEEDS_PREVIOUS_SAMPLE	= 0x1
    }

ifndef __IDMOVideoOutputOptimizations_INTERFACE_DEFINED__
define __IDMOVideoOutputOptimizations_INTERFACE_DEFINED__

DEFINE_IIDX(IDMOVideoOutputOptimizations, "be8f4f4e-5b16-4d29-b350-7f6b5d9298ac")

.comdef IDMOVideoOutputOptimizations : public IUnknown

    QueryOperationModePreferences proc :ULONG, :ptr
    SetOperationMode	proc :ULONG, :DWORD
    GetCurrentOperationMode proc :ULONG, :ptr
    GetCurrentSampleRequirements proc :ULONG, :ptr
   .ends

endif
endif
endif
