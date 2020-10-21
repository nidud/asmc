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

ifndef __mfreadwrite_h__
__mfreadwrite_h__ equ <>

ifndef __IMFReadWriteClassFactory_FWD_DEFINED__
__IMFReadWriteClassFactory_FWD_DEFINED__ equ 1
endif
ifndef __IMFSourceReader_FWD_DEFINED__
__IMFSourceReader_FWD_DEFINED__ equ 1
endif
ifndef __IMFSourceReaderEx_FWD_DEFINED__
__IMFSourceReaderEx_FWD_DEFINED__ equ 1
endif
ifndef __IMFSourceReaderCallback_FWD_DEFINED__
__IMFSourceReaderCallback_FWD_DEFINED__ equ 1
endif
ifndef __IMFSinkWriter_FWD_DEFINED__
__IMFSinkWriter_FWD_DEFINED__ equ 1
endif
ifndef __IMFSinkWriterEx_FWD_DEFINED__
__IMFSinkWriterEx_FWD_DEFINED__ equ 1
endif
ifndef __IMFSinkWriterEncoderConfig_FWD_DEFINED__
__IMFSinkWriterEncoderConfig_FWD_DEFINED__ equ 1
endif
ifndef __IMFSinkWriterCallback_FWD_DEFINED__
__IMFSinkWriterCallback_FWD_DEFINED__ equ 1
endif

include mfobjects.inc
include MFTransform.inc

.pragma comment(lib, mfreadwrite)

include winapifamily.inc
if (WINVER GE _WIN32_WINNT_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DEFINE_GUID(CLSID_MFReadWriteClassFactory, 0x48e2ed0f, 0x98c2, 0x4a37, 0xbe, 0xd5, 0x16, 0x63, 0x12, 0xdd, 0xd8, 0x3f)

ifndef __IMFReadWriteClassFactory_INTERFACE_DEFINED__
__IMFReadWriteClassFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFReadWriteClassFactory, "E7FE2E12-661C-40DA-92F9-4F002AB67627")

.comdef IMFReadWriteClassFactory : public IUnknown

    CreateInstanceFromURL proc :REFCLSID, :LPCWSTR, :ptr, :REFIID, :ptr
    CreateInstanceFromObject proc :REFCLSID, :ptr, :ptr, :REFIID, :ptr
    .ends

endif

DEFINE_GUID(CLSID_MFSourceReader, 0x1777133c, 0x0881, 0x411b, 0xa5, 0x77, 0xad, 0x54, 0x5f, 0x07, 0x14, 0xc4);

MFCreateSourceReaderFromURL proto WINAPI \
	       pwszURL: LPCWSTR,
	   pAttributes: ptr IMFAttributes,
	ppSourceReader: ptr IMFSourceReader

MFCreateSourceReaderFromByteStream proto WINAPI \
	   pByteStream: ptr IMFByteStream,
	   pAttributes: ptr IMFAttributes,
	ppSourceReader: ptr IMFSourceReader

MFCreateSourceReaderFromMediaSource proto WINAPI \
	  pMediaSource: ptr IMFMediaSource,
	   pAttributes: ptr IMFAttributes,
	ppSourceReader: ptr IMFSourceReader

DEFINE_GUID( MF_SOURCE_READER_ASYNC_CALLBACK, 0x1e3dbeac, 0xbb43, 0x4c35, 0xb5, 0x07, 0xcd, 0x64, 0x44, 0x64, 0xc9, 0x65);
DEFINE_GUID( MF_SOURCE_READER_D3D_MANAGER, 0xec822da2, 0xe1e9, 0x4b29, 0xa0, 0xd8, 0x56, 0x3c, 0x71, 0x9f, 0x52, 0x69);
DEFINE_GUID( MF_SOURCE_READER_DISABLE_DXVA, 0xaa456cfd, 0x3943, 0x4a1e, 0xa7, 0x7d, 0x18, 0x38, 0xc0, 0xea, 0x2e, 0x35);
DEFINE_GUID( MF_SOURCE_READER_MEDIASOURCE_CONFIG, 0x9085abeb, 0x0354, 0x48f9, 0xab, 0xb5, 0x20, 0x0d, 0xf8, 0x38, 0xc6, 0x8e);
DEFINE_GUID( MF_SOURCE_READER_MEDIASOURCE_CHARACTERISTICS, 0x6d23f5c8, 0xc5d7, 0x4a9b, 0x99, 0x71, 0x5d, 0x11, 0xf8, 0xbc, 0xa8, 0x80);
DEFINE_GUID( MF_SOURCE_READER_ENABLE_VIDEO_PROCESSING, 0xfb394f3d, 0xccf1, 0x42ee, 0xbb, 0xb3, 0xf9, 0xb8, 0x45, 0xd5, 0x68, 0x1d);
if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_GUID( MF_SOURCE_READER_ENABLE_ADVANCED_VIDEO_PROCESSING, 0xf81da2c, 0xb537, 0x4672, 0xa8, 0xb2, 0xa6, 0x81, 0xb1, 0x73, 0x7, 0xa3);
DEFINE_GUID( MF_SOURCE_READER_DISABLE_CAMERA_PLUGINS, 0x9d3365dd, 0x58f, 0x4cfb, 0x9f, 0x97, 0xb3, 0x14, 0xcc, 0x99, 0xc8, 0xad );
endif
DEFINE_GUID( MF_SOURCE_READER_DISCONNECT_MEDIASOURCE_ON_SHUTDOWN, 0x56b67165, 0x219e, 0x456d, 0xa2, 0x2e, 0x2d, 0x30, 0x04, 0xc7, 0xfe, 0x56);
DEFINE_GUID( MF_SOURCE_READER_ENABLE_TRANSCODE_ONLY_TRANSFORMS, 0xdfd4f008, 0xb5fd, 0x4e78, 0xae, 0x44, 0x62, 0xa1, 0xe6, 0x7b, 0xbe, 0x27);

.enum MF_SOURCE_READER_FLAG {
    MF_SOURCE_READERF_ERROR	= 0x1,
    MF_SOURCE_READERF_ENDOFSTREAM	= 0x2,
    MF_SOURCE_READERF_NEWSTREAM = 0x4,
    MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED	= 0x10,
    MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED	= 0x20,
    MF_SOURCE_READERF_STREAMTICK	= 0x100,
    MF_SOURCE_READERF_ALLEFFECTSREMOVED = 0x200
    }

.enum MF_SOURCE_READER_CONTROL_FLAG {
    MF_SOURCE_READER_CONTROLF_DRAIN	= 0x1
    }

.enum _MIDL___MIDL_itf_mfreadwrite_0000_0001_0001 {
    MF_SOURCE_READER_INVALID_STREAM_INDEX	= 0xffffffff,
    MF_SOURCE_READER_ALL_STREAMS	= 0xfffffffe,
    MF_SOURCE_READER_ANY_STREAM = 0xfffffffe,
    MF_SOURCE_READER_FIRST_AUDIO_STREAM = 0xfffffffd,
    MF_SOURCE_READER_FIRST_VIDEO_STREAM = 0xfffffffc,
    MF_SOURCE_READER_MEDIASOURCE	= 0xffffffff
    }

if (WINVER GE _WIN32_WINNT_WIN8)
.enum _MIDL___MIDL_itf_mfreadwrite_0000_0001_0002 {
    MF_SOURCE_READER_CURRENT_TYPE_INDEX = 0xffffffff
    }
endif

ifndef __IMFSourceReader_INTERFACE_DEFINED__
__IMFSourceReader_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSourceReader, "70ae66f2-c809-4e4f-8915-bdcb406b7993")

.comdef IMFSourceReader : public IUnknown

    GetStreamSelection	proc :DWORD, :ptr
    SetStreamSelection	proc :DWORD, :BOOL
    GetNativeMediaType	proc :DWORD, :DWORD, :ptr
    GetCurrentMediaType proc :DWORD, :ptr
    SetCurrentMediaType proc :DWORD, :ptr, :ptr
    SetCurrentPosition	proc :REFGUID, :REFPROPVARIANT
    ReadSample		proc :DWORD, :DWORD, :ptr, :ptr, :ptr, :ptr
    Flush		proc :DWORD
    GetServiceForStream proc :DWORD, :REFGUID, :REFIID, :ptr
    GetPresentationAttribute proc :DWORD, :REFGUID, :ptr
    .ends

endif

endif

if (WINVER GE _WIN32_WINNT_WIN8)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __IMFSourceReaderEx_INTERFACE_DEFINED__
__IMFSourceReaderEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSourceReaderEx, "7b981cf0-560e-4116-9875-b099895f23d7")

.comdef IMFSourceReaderEx : public IMFSourceReader

    SetNativeMediaType	proc :DWORD, :ptr, :ptr
    AddTransformForStream proc :DWORD, :ptr
    RemoveAllTransformsForStream proc :DWORD
    GetTransformForStream proc :DWORD, :DWORD, :ptr, :ptr
    .ends

endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __IMFSourceReaderCallback_INTERFACE_DEFINED__
__IMFSourceReaderCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSourceReaderCallback, "deec8d99-fa1d-4d82-84c2-2c8969944867")

.comdef IMFSourceReaderCallback : public IUnknown

    OnReadSample	proc :HRESULT, :DWORD, :DWORD, :LONGLONG, :ptr
    OnFlush		proc :DWORD
    OnEvent		proc :DWORD, :ptr
    .ends

endif

DEFINE_GUID(CLSID_MFSinkWriter, 0xa3bbfb17, 0x8273, 0x4e52, 0x9e, 0x0e, 0x97, 0x39, 0xdc, 0x88, 0x79, 0x90);

MFCreateSinkWriterFromURL proto WINAPI \
	 pwszOutputURL: LPCWSTR,
	   pByteStream: ptr IMFByteStream,
	   pAttributes: ptr IMFAttributes,
	  ppSinkWriter: ptr IMFSinkWriter

MFCreateSinkWriterFromMediaSink proto WINAPI \
	    pMediaSink: ptr IMFMediaSink,
	   pAttributes: ptr IMFAttributes,
	  ppSinkWriter: ptr IMFSinkWriter

DEFINE_GUID( MF_SINK_WRITER_ASYNC_CALLBACK, 0x48cb183e, 0x7b0b, 0x46f4, 0x82, 0x2e, 0x5e, 0x1d, 0x2d, 0xda, 0x43, 0x54);
DEFINE_GUID( MF_SINK_WRITER_DISABLE_THROTTLING, 0x08b845d8, 0x2b74, 0x4afe, 0x9d, 0x53, 0xbe, 0x16, 0xd2, 0xd5, 0xae, 0x4f);
if (WINVER GE _WIN32_WINNT_WIN8)
DEFINE_GUID( MF_SINK_WRITER_D3D_MANAGER, 0xec822da2, 0xe1e9, 0x4b29, 0xa0, 0xd8, 0x56, 0x3c, 0x71, 0x9f, 0x52, 0x69);
DEFINE_GUID( MF_SINK_WRITER_ENCODER_CONFIG, 0xad91cd04, 0xa7cc, 0x4ac7, 0x99, 0xb6, 0xa5, 0x7b, 0x9a, 0x4a, 0x7c, 0x70);
endif

.enum _MIDL___MIDL_itf_mfreadwrite_0000_0004_0001 {
    MF_SINK_WRITER_INVALID_STREAM_INDEX = 0xffffffff,
    MF_SINK_WRITER_ALL_STREAMS	= 0xfffffffe,
    MF_SINK_WRITER_MEDIASINK	= 0xffffffff
    }

MF_SINK_WRITER_STATISTICS STRUC
cb			dd ?
llLastTimestampReceived LONGLONG ?
llLastTimestampEncoded	LONGLONG ?
llLastTimestampProcessed LONGLONG ?
llLastStreamTickReceived LONGLONG ?
llLastSinkSampleRequest LONGLONG ?
qwNumSamplesReceived	QWORD ?
qwNumSamplesEncoded	QWORD ?
qwNumSamplesProcessed	QWORD ?
qwNumStreamTicksReceived QWORD ?
dwByteCountQueued	dd ?
qwByteCountProcessed	QWORD ?
dwNumOutstandingSinkSampleRequests dd ?
dwAverageSampleRateReceived dd ?
dwAverageSampleRateEncoded dd ?
dwAverageSampleRateProcessed dd ?
MF_SINK_WRITER_STATISTICS ENDS

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __IMFSinkWriter_INTERFACE_DEFINED__
__IMFSinkWriter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSinkWriter, "3137f1cd-fe5e-4805-a5d8-fb477448cb3d")

.comdef IMFSinkWriter : public IUnknown

    AddStream		proc :ptr, :ptr
    SetInputMediaType	proc :DWORD, :ptr, :ptr
    BeginWriting	proc
    WriteSample		proc :DWORD, :ptr
    SendStreamTick	proc :DWORD, :LONGLONG
    PlaceMarker		proc :DWORD, :LPVOID
    NotifyEndOfSegment	proc :DWORD
    Flush		proc :DWORD
    Finalize		proc
    GetServiceForStream proc :DWORD, :REFGUID, :REFIID, :ptr
    GetStatistics	proc :DWORD, :ptr
    .ends

endif

if (WINVER GE _WIN32_WINNT_WIN8)

ifndef __IMFSinkWriterEx_INTERFACE_DEFINED__
__IMFSinkWriterEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSinkWriterEx, "588d72ab-5Bc1-496a-8714-b70617141b25")

.comdef IMFSinkWriterEx : public IMFSinkWriter

    GetTransformForStream proc :DWORD, :DWORD, :ptr, :ptr
    .ends

endif

ifndef __IMFSinkWriterEncoderConfig_INTERFACE_DEFINED__
__IMFSinkWriterEncoderConfig_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSinkWriterEncoderConfig, "17C3779E-3CDE-4EDE-8C60-3899F5F53AD6")

.comdef IMFSinkWriterEncoderConfig : public IUnknown

    SetTargetMediaType	proc :DWORD, :ptr, :ptr
    PlaceEncodingParameters proc :DWORD, :ptr
    .ends

endif

endif

ifndef __IMFSinkWriterCallback_INTERFACE_DEFINED__
__IMFSinkWriterCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFSinkWriterCallback, "666f76de-33d2-41b9-a458-29ed0a972c58")

.comdef IMFSinkWriterCallback : public IUnknown

    OnFinalize		proc :HRESULT
    OnMarker		proc :DWORD, :LPVOID
    .ends

endif


DEFINE_GUID( MF_READWRITE_DISABLE_CONVERTERS, 0x98d5b065, 0x1374, 0x4847, 0x8d, 0x5d, 0x31, 0x52, 0x0f, 0xee, 0x71, 0x56);
DEFINE_GUID( MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, 0xa634a91c, 0x822b, 0x41b9, 0xa4, 0x94, 0x4d, 0xe4, 0x64, 0x36, 0x12, 0xb0);
endif

endif
if (WINVER GE _WIN32_WINNT_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
DEFINE_GUID( MF_READWRITE_MMCSS_CLASS, 0x39384300, 0xd0eb, 0x40b1, 0x87, 0xa0, 0x33, 0x18, 0x87, 0x1b, 0x5a, 0x53);
DEFINE_GUID( MF_READWRITE_MMCSS_PRIORITY, 0x43ad19ce, 0xf33f, 0x4ba9, 0xa5, 0x80, 0xe4, 0xcd, 0x12, 0xf2, 0xd1, 0x44);
DEFINE_GUID( MF_READWRITE_MMCSS_CLASS_AUDIO, 0x430847da, 0x0890, 0x4b0e, 0x93, 0x8c, 0x05, 0x43, 0x32, 0xc5, 0x47, 0xe1);
DEFINE_GUID( MF_READWRITE_MMCSS_PRIORITY_AUDIO, 0x273db885, 0x2de2, 0x4db2, 0xa6, 0xa7, 0xfd, 0xb6, 0x6f, 0xb4, 0x0b, 0x61);
DEFINE_GUID( MF_READWRITE_D3D_OPTIONAL, 0x216479d9, 0x3071, 0x42ca, 0xbb, 0x6c, 0x4c, 0x22, 0x10, 0x2e, 0x1d, 0x18);
endif

endif

endif


