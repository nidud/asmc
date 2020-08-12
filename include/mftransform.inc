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

ifndef __mftransform_h__
__mftransform_h__ equ <>

ifndef __IMFTransform_FWD_DEFINED__
__IMFTransform_FWD_DEFINED__ equ 1
endif

include mfobjects.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum MFT_INPUT_DATA_BUFFER_FLAGS {
    MFT_INPUT_DATA_BUFFER_PLACEHOLDER	= 0xffffffff
    }

.enum MFT_OUTPUT_DATA_BUFFER_FLAGS {
    MFT_OUTPUT_DATA_BUFFER_INCOMPLETE	= 0x1000000,
    MFT_OUTPUT_DATA_BUFFER_FORMAT_CHANGE	= 0x100,
    MFT_OUTPUT_DATA_BUFFER_STREAM_END	= 0x200,
    MFT_OUTPUT_DATA_BUFFER_NO_SAMPLE	= 0x300
    }

.enum MFT_INPUT_STATUS_FLAGS {
    MFT_INPUT_STATUS_ACCEPT_DATA	= 0x1
    }

.enum MFT_OUTPUT_STATUS_FLAGS {
    MFT_OUTPUT_STATUS_SAMPLE_READY	= 0x1
    }

.enum MFT_INPUT_STREAM_INFO_FLAGS {
    MFT_INPUT_STREAM_WHOLE_SAMPLES	= 0x1,
    MFT_INPUT_STREAM_SINGLE_SAMPLE_PER_BUFFER	= 0x2,
    MFT_INPUT_STREAM_FIXED_SAMPLE_SIZE	= 0x4,
    MFT_INPUT_STREAM_HOLDS_BUFFERS	= 0x8,
    MFT_INPUT_STREAM_DOES_NOT_ADDREF	= 0x100,
    MFT_INPUT_STREAM_REMOVABLE	= 0x200,
    MFT_INPUT_STREAM_OPTIONAL	= 0x400,
    MFT_INPUT_STREAM_PROCESSES_IN_PLACE = 0x800
    }

.enum MFT_OUTPUT_STREAM_INFO_FLAGS {
    MFT_OUTPUT_STREAM_WHOLE_SAMPLES	= 0x1,
    MFT_OUTPUT_STREAM_SINGLE_SAMPLE_PER_BUFFER	= 0x2,
    MFT_OUTPUT_STREAM_FIXED_SAMPLE_SIZE = 0x4,
    MFT_OUTPUT_STREAM_DISCARDABLE	= 0x8,
    MFT_OUTPUT_STREAM_OPTIONAL	= 0x10,
    MFT_OUTPUT_STREAM_PROVIDES_SAMPLES	= 0x100,
    MFT_OUTPUT_STREAM_CAN_PROVIDE_SAMPLES	= 0x200,
    MFT_OUTPUT_STREAM_LAZY_READ = 0x400,
    MFT_OUTPUT_STREAM_REMOVABLE = 0x800
    }

.enum MFT_SET_TYPE_FLAGS {
    MFT_SET_TYPE_TEST_ONLY	= 0x1
    }

.enum MFT_PROCESS_OUTPUT_FLAGS {
    MFT_PROCESS_OUTPUT_DISCARD_WHEN_NO_BUFFER	= 0x1,
    MFT_PROCESS_OUTPUT_REGENERATE_LAST_OUTPUT	= 0x2
    }

.enum MFT_PROCESS_OUTPUT_STATUS {
    MFT_PROCESS_OUTPUT_STATUS_NEW_STREAMS	= 0x100
    }

.enum MFT_DRAIN_TYPE {
    MFT_DRAIN_PRODUCE_TAILS	= 0,
    MFT_DRAIN_NO_TAILS	= 0x1
    }

MFT_STREAMS_UNLIMITED	equ 0xFFFFFFFF
MFT_OUTPUT_BOUND_LOWER_UNBOUNDED equ MINLONGLONG
MFT_OUTPUT_BOUND_UPPER_UNBOUNDED equ MAXLONGLONG

.enum MFT_MESSAGE_TYPE {
    MFT_MESSAGE_COMMAND_FLUSH	= 0,
    MFT_MESSAGE_COMMAND_DRAIN	= 0x1,
    MFT_MESSAGE_SET_D3D_MANAGER = 0x2,
    MFT_MESSAGE_DROP_SAMPLES	= 0x3,
    MFT_MESSAGE_COMMAND_TICK	= 0x4,
    MFT_MESSAGE_NOTIFY_BEGIN_STREAMING	= 0x10000000,
    MFT_MESSAGE_NOTIFY_END_STREAMING	= 0x10000001,
    MFT_MESSAGE_NOTIFY_END_OF_STREAM	= 0x10000002,
    MFT_MESSAGE_NOTIFY_START_OF_STREAM	= 0x10000003,
    MFT_MESSAGE_COMMAND_MARKER	= 0x20000000
    }

MFT_INPUT_STREAM_INFO	STRUC
hnsMaxLatency		LONGLONG ?
dwFlags			dd ?
cbSize			dd ?
cbMaxLookahead		dd ?
cbAlignment		dd ?
MFT_INPUT_STREAM_INFO	ENDS

MFT_OUTPUT_STREAM_INFO	STRUC
dwFlags			dd ?
cbSize			dd ?
cbAlignment		dd ?
MFT_OUTPUT_STREAM_INFO	ENDS

MFT_OUTPUT_DATA_BUFFER	STRUC
dwStreamID		dd ?
pSample			ptr_t ?
dwStatus		dd ?
pEvents			ptr_t ?
MFT_OUTPUT_DATA_BUFFER	ENDS
PMFT_OUTPUT_DATA_BUFFER typedef ptr MFT_OUTPUT_DATA_BUFFER

ifdef MFT_UNIQUE_METHOD_NAMES
GetStreamLimits		equ <MFTGetStreamLimits>
GetStreamCount		equ <MFTGetStreamCount>
GetStreamIDs		equ <MFTGetStreamIDs>
GetInputStreamInfo	equ <MFTGetInputStreamInfo>
GetOutputStreamInfo	equ <MFTGetOutputStreamInfo>
DeleteInputStream	equ <MFTDeleteInputStream>
AddInputStreams		equ <MFTAddInputStreams>
GetInputAvailableType	equ <MFTGetInputAvailableType>
GetOutputAvailableType	equ <MFTGetOutputAvailableType>
SetInputType		equ <MFTSetInputType>
SetOutputType		equ <MFTSetOutputType>
GetInputCurrentType	equ <MFTGetInputCurrentType>
GetOutputCurrentType	equ <MFTGetOutputCurrentType>
GetInputStatus		equ <MFTGetInputStatus>
GetOutputStatus		equ <MFTGetOutputStatus>
SetOutputBounds		equ <MFTSetOutputBounds>
ProcessEvent		equ <MFTProcessEvent>
ProcessMessage		equ <MFTProcessMessage>
ProcessInput		equ <MFTProcessInput>
ProcessOutput		equ <MFTProcessOutput>
endif

ifndef __IMFTransform_INTERFACE_DEFINED__
__IMFTransform_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMFTransform, "bf94c121-5b05-4e6f-8000-ba598961414d")

.comdef IMFTransform : public IUnknown

    GetStreamLimits	proc :ptr, :ptr, :ptr, :ptr
    GetStreamCount	proc :ptr, :ptr
    GetStreamIDs	proc :DWORD, :ptr
    GetInputStreamInfo	proc :DWORD, :ptr
    GetOutputStreamInfo proc :DWORD, :ptr
    GetAttributes	proc :ptr
    GetInputStreamAttributes proc :DWORD, :ptr
    GetOutputStreamAttributes proc :DWORD, :ptr
    DeleteInputStream	proc :DWORD
    AddInputStreams	proc :DWORD, :ptr
    GetInputAvailableType proc :DWORD, :DWORD, :ptr
    GetOutputAvailableType proc :DWORD, :DWORD, :ptr
    SetInputType	proc :DWORD, :ptr, :DWORD
    SetOutputType	proc :DWORD, :ptr, :DWORD
    GetInputCurrentType proc :DWORD, :ptr
    GetOutputCurrentType proc :DWORD, :ptr
    GetInputStatus	proc :DWORD, :ptr
    GetOutputStatus	proc :ptr
    SetOutputBounds	proc :LONGLONG, :LONGLONG
    ProcessEvent	proc :DWORD, :ptr
    ProcessMessage	proc :MFT_MESSAGE_TYPE, :ULONG_PTR
    ProcessInput	proc :DWORD, :ptr IMFSample, :DWORD
    ProcessOutput	proc :DWORD, :DWORD, :ptr MFT_OUTPUT_DATA_BUFFER, :ptr DWORD
    .ends

endif
endif

if (WINVER GE _WIN32_WINNT_WIN7)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
STREAM_MEDIUM		STRUC
gidMedium		GUID <>
unMediumInstance	UINT32 ?
STREAM_MEDIUM		ENDS
PSTREAM_MEDIUM		typedef ptr STREAM_MEDIUM
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifdef MFT_UNIQUE_METHOD_NAMES
undef GetStreamLimits
undef GetStreamCount
undef GetStreamIDs
undef GetInputStreamInfo
undef GetOutputStreamInfo
undef DeleteInputStream
undef AddInputStreams
undef GetInputAvailableType
undef GetOutputAvailableType
undef SetInputType
undef SetOutputType
undef GetInputCurrentType
undef GetOutputCurrentType
undef GetInputStatus
undef GetOutputStatus
undef SetOutputBounds
undef ProcessMessage
undef ProcessInput
undef ProcessOutput
endif
MFPKEY_CLSID			 equ <{ { 0xc57a84c0, 0x1a80, 0x40a3, {0x97, 0xb5, 0x92, 0x72, 0xa4, 0x3, 0xc8, 0xae} }, 0x01 }>
MFPKEY_CATEGORY			 equ <{ { 0xc57a84c0, 0x1a80, 0x40a3, {0x97, 0xb5, 0x92, 0x72, 0xa4, 0x3, 0xc8, 0xae} }, 0x02 }>
MFPKEY_EXATTRIBUTE_SUPPORTED	 equ <{ { 0x456fe843, 0x3c87, 0x40c0, {0x94, 0x9d, 0x14, 0x9, 0xc9, 0x7d, 0xab, 0x2c} }, 0x01 }>
MFPKEY_MULTICHANNEL_CHANNEL_MASK equ <{ { 0x58bdaf8c, 0x3224, 0x4692, { 0x86, 0xd0, 0x44, 0xd6, 0x5c, 0x5b, 0xf8, 0x2b } }, 0x01 }>
MF_SA_D3D_AWARE			 equ <{ 0xeaa35c29,	 0x775e, 0x488e, { 0x9b, 0x61, 0xb3, 0x28, 0x3e, 0x49, 0x58, 0x3b } }>
MF_SA_REQUIRED_SAMPLE_COUNT	 equ <{ 0x18802c61, 0x324b, 0x4952, { 0xab, 0xd0, 0x17, 0x6f, 0xf5, 0xc6, 0x96, 0xff } }>
endif

if (WINVER GE _WIN32_WINNT_WIN8)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MF_SA_REQUIRED_SAMPLE_COUNT_PROGRESSIVE		equ <{ 0xb172d58e, 0xfa77, 0x4e48, { 0x8d, 0x2a, 0x1d, 0xf2, 0xd8, 0x50, 0xea, 0xc2 } }>
MF_SA_MINIMUM_OUTPUT_SAMPLE_COUNT		equ <{ 0x851745d5, 0xc3d6, 0x476d, { 0x95, 0x27, 0x49, 0x8e, 0xf2, 0xd1, 0x0d, 0x18 } }>
MF_SA_MINIMUM_OUTPUT_SAMPLE_COUNT_PROGRESSIVE	equ <{ 0x0f5523a5, 0x1cb2, 0x47c5, { 0xa5, 0x50, 0x2e, 0xeb, 0x84, 0xb4, 0xd1, 0x4a } }>
MFT_SUPPORT_3DVIDEO				equ <{ 0x093f81b1, 0x4f2e, 0x4631, { 0x81, 0x68, 0x79, 0x34, 0x03, 0x2a, 0x01, 0xd3 } }>

.enum MF3DVideoOutputType {
    MF3DVideoOutputType_BaseView = 0,
    MF3DVideoOutputType_Stereo	 = 1
    }

MF_ENABLE_3DVIDEO_OUTPUT			equ <{ 0xbdad7bca, 0x0e5f, 0x4b10, { 0xab, 0x16, 0x26, 0xde, 0x38, 0x1b, 0x62, 0x93 } }>
MF_SA_D3D11_BINDFLAGS				equ <{ 0xeacf97ad, 0x065c, 0x4408, { 0xbe, 0xe3, 0xfd, 0xcb, 0xfd, 0x12, 0x8b, 0xe2 } }>
MF_SA_D3D11_USAGE				equ <{ 0xe85fe442, 0x2ca3, 0x486e, { 0xa9, 0xc7, 0x10, 0x9d, 0xda, 0x60, 0x98, 0x80 } }>
MF_SA_D3D11_AWARE				equ <{ 0x206b4fc8, 0xfcf9, 0x4c51, { 0xaf, 0xe3, 0x97, 0x64, 0x36, 0x9e, 0x33, 0xa0 } }>
MF_SA_D3D11_SHARED				equ <{ 0x7b8f32c3, 0x6d96, 0x4b89, { 0x92, 0x03, 0xdd, 0x38, 0xb6, 0x14, 0x14, 0xf3 } }>
MF_SA_D3D11_SHARED_WITHOUT_MUTEX		equ <{ 0x39dbd44d, 0x2e44, 0x4931, { 0xa4, 0xc8, 0x35, 0x2d, 0x3d, 0xc4, 0x21, 0x15 } }>
MF_SA_BUFFERS_PER_SAMPLE			equ <{ 0x873c5171, 0x1e3d, 0x4e25, { 0x98, 0x8d, 0xb4, 0x33, 0xce, 0x04, 0x19, 0x83 } }>
MFT_DECODER_EXPOSE_OUTPUT_TYPES_IN_NATIVE_ORDER equ <{ 0xef80833f, 0xf8fa, 0x44d9, { 0x80, 0xd8, 0x41, 0xed, 0x62, 0x32, 0x67, 0x0c } }>
MFT_REMUX_MARK_I_PICTURE_AS_CLEAN_POINT		equ <{ 0x364e8f85, 0x3f2e, 0x436c, { 0xb2, 0xa2, 0x44, 0x40, 0xa0, 0x12, 0xa9, 0xe8 } }>
MFT_DECODER_FINAL_VIDEO_RESOLUTION_HINT		equ <{ 0xdc2f8496, 0x15c4, 0x407a, { 0xb6, 0xf0, 0x1b, 0x66, 0xab, 0x5f, 0xbf, 0x53 } }>
MFT_ENCODER_SUPPORTS_CONFIG_EVENT		equ <{ 0x86a355ae, 0x3a77, 0x4ec4, { 0x9f, 0x31, 0x01, 0x14, 0x9a, 0x4e, 0x92, 0xde } }>
MFT_ENUM_HARDWARE_VENDOR_ID_Attribute		equ <{ 0x3aecb0cc, 0x035b, 0x4bcc, { 0x81, 0x85, 0x2b, 0x8d, 0x55, 0x1e, 0xf3, 0xaf } }>
endif
endif

if (WINVER GE _WIN32_WINNT_WIN7)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
MF_TRANSFORM_ASYNC			equ <{ 0xf81a699a, 0x649a, 0x497d, { 0x8c, 0x73, 0x29, 0xf8, 0xfe, 0xd6, 0xad, 0x7a } }>
MF_TRANSFORM_ASYNC_UNLOCK		equ <{ 0xe5666d6b, 0x3422, 0x4eb6, { 0xa4, 0x21, 0xda, 0x7d, 0xb1, 0xf8, 0xe2, 0x07 } }>
MF_TRANSFORM_FLAGS_Attribute		equ <{ 0x9359bb7e, 0x6275, 0x46c4, { 0xa0, 0x25, 0x1c, 0x01, 0xe4, 0x5f, 0x1a, 0x86 } }>
MF_TRANSFORM_CATEGORY_Attribute		equ <{ 0xceabba49, 0x506d, 0x4757, { 0xa6, 0xff, 0x66, 0xc1, 0x84, 0x98, 0x7e, 0x4e } }>
MFT_TRANSFORM_CLSID_Attribute		equ <{ 0x6821c42b, 0x65a4, 0x4e82, { 0x99, 0xbc, 0x9a, 0x88, 0x20, 0x5e, 0xcd, 0x0c } }>
MFT_INPUT_TYPES_Attributes		equ <{ 0x4276c9b1, 0x759d, 0x4bf3, { 0x9c, 0xd0, 0x0d, 0x72, 0x3d, 0x13, 0x8f, 0x96 } }>
MFT_OUTPUT_TYPES_Attributes		equ <{ 0x8eae8cf3, 0xa44f, 0x4306, { 0xba, 0x5c, 0xbf, 0x5d, 0xda, 0x24, 0x28, 0x18 } }>
MFT_ENUM_HARDWARE_URL_Attribute		equ <{ 0x2fb866ac, 0xb078, 0x4942, { 0xab, 0x6c, 0x00, 0x3d, 0x05, 0xcd, 0xa6, 0x74 } }>
MFT_FRIENDLY_NAME_Attribute		equ <{ 0x314ffbae, 0x5b41, 0x4c95, { 0x9c, 0x19, 0x4e, 0x7d, 0x58, 0x6f, 0xac, 0xe3 } }>
MFT_CONNECTED_STREAM_ATTRIBUTE		equ <{ 0x71eeb820, 0xa59f, 0x4de2, { 0xbc, 0xec, 0x38, 0xdb, 0x1d, 0xd6, 0x11, 0xa4 } }>
MFT_CONNECTED_TO_HW_STREAM		equ <{ 0x34e6e728, 0x06d6, 0x4491, { 0xa5, 0x53, 0x47, 0x95, 0x65, 0x0d, 0xb9, 0x12 } }>
MFT_PREFERRED_OUTPUTTYPE_Attribute	equ <{ 0x7e700499, 0x396a, 0x49ee, { 0xb1, 0xb4, 0xf6, 0x28, 0x02, 0x1e, 0x8c, 0x9d } }>
MFT_PROCESS_LOCAL_Attribute		equ <{ 0x543186e4, 0x4649, 0x4e65, { 0xb5, 0x88, 0x4a, 0xa3, 0x52, 0xaf, 0xf3, 0x79 } }>
MFT_PREFERRED_ENCODER_PROFILE		equ <{ 0x53004909, 0x1ef5, 0x46d7, { 0xa1, 0x8e, 0x5a, 0x75, 0xf8, 0xb5, 0x90, 0x5f } }>
MFT_HW_TIMESTAMP_WITH_QPC_Attribute	equ <{ 0x8d030fb8, 0xcc43, 0x4258, { 0xa2, 0x2e, 0x92, 0x10, 0xbe, 0xf8, 0x9b, 0xe4 } }>
MFT_FIELDOFUSE_UNLOCK_Attribute		equ <{ 0x8ec2e9fd, 0x9148, 0x410d, { 0x83, 0x1e, 0x70, 0x24, 0x39, 0x46, 0x1a, 0x8e } }>
MFT_CODEC_MERIT_Attribute		equ <{ 0x88a7cb15, 0x7b07, 0x4a34, { 0x91, 0x28, 0xe6, 0x4c, 0x67, 0x03, 0xc4, 0xd3 } }>
MFT_ENUM_TRANSCODE_ONLY_ATTRIBUTE	equ <{ 0x111ea8cd, 0xb62a, 0x4bdb, { 0x89, 0xf6, 0x67, 0xff, 0xcd, 0xc2, 0x45, 0x8b } }>
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
MFCreateTransformActivate proto __cdecl : ptr ptr IMFActivate
endif
endif
endif
