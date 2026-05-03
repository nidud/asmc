ifndef __DIRECTX_VA__
define __DIRECTX_VA__
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifdef __DIRECTX_VA_COPP_ONLY
define __DIRECTX_VA_DECODER__
define __DIRECTX_VA_PROCAMPCONTROL__
define __DIRECTX_VA_DEINTERLACE__
endif

ifndef DXVABit
DXVABit macro __x
	exitm<(1 SHL __x)>
	endm
endif

ifndef __DIRECTX_VA_DECODER__
define __DIRECTX_VA_DECODER__

DEFINE_GUID(DXVA_ModeNone,    0x1b81be00, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH261_A,  0x1b81be01, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH261_B,  0x1b81be02, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)

DEFINE_GUID(DXVA_ModeH263_A,  0x1b81be03, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH263_B,  0x1b81be04, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH263_C,  0x1b81be05, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH263_D,  0x1b81be06, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH263_E,  0x1b81be07, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH263_F,  0x1b81be08, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)

DEFINE_GUID(DXVA_ModeMPEG1_A, 0x1b81be09, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeMPEG1_VLD, 0x6f3ec719, 0x3735,0x42cc,0x80,0x63,0x65,0xcc,0x3c,0xb3,0x66,0x16)

DEFINE_GUID(DXVA_ModeMPEG2_A, 0x1b81be0A, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeMPEG2_B, 0x1b81be0B, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeMPEG2_C, 0x1b81be0C, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeMPEG2_D, 0x1b81be0D, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeMPEG2and1_VLD, 0x86695f12, 0x340e,0x4f04,0x9f,0xd3,0x92,0x53,0xdd,0x32,0x74,0x60)

DEFINE_GUID(DXVA_ModeH264_A,  0x1b81be64, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH264_B,  0x1b81be65, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH264_C,  0x1b81be66, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH264_D,  0x1b81be67, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH264_E,  0x1b81be68, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH264_F,  0x1b81be69, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeH264_VLD_WithFMOASO_NoFGT, 0xd5f04ff9, 0x3418,0x45d8,0x95,0x61,0x32,0xa7,0x6a,0xae,0x2d,0xdd)

DEFINE_GUID(DXVA_ModeH264_VLD_Stereo_Progressive_NoFGT,	    0xd79be8da, 0x0cf1,0x4c81,0xb8,0x2a,0x69,0xa4,0xe2,0x36,0xf4,0x3d)
DEFINE_GUID(DXVA_ModeH264_VLD_Stereo_NoFGT,		    0xf9aaccbb, 0xc2b6,0x4cfc,0x87,0x79,0x57,0x07,0xb1,0x76,0x05,0x52)
DEFINE_GUID(DXVA_ModeH264_VLD_Multiview_NoFGT,		    0x705b9d82, 0x76cf,0x49d6,0xb7,0xe6,0xac,0x88,0x72,0xdb,0x01,0x3c)

DEFINE_GUID(DXVA_ModeWMV8_A,  0x1b81be80, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeWMV8_B,  0x1b81be81, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)

DEFINE_GUID(DXVA_ModeWMV9_A,  0x1b81be90, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeWMV9_B,  0x1b81be91, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeWMV9_C,  0x1b81be94, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)

DEFINE_GUID(DXVA_ModeVC1_A,   0x1b81beA0, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeVC1_B,   0x1b81beA1, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeVC1_C,   0x1b81beA2, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeVC1_D,   0x1b81beA3, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)
DEFINE_GUID(DXVA_ModeVC1_D2010,0x1b81beA4, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)

DEFINE_GUID(DXVA_ModeMPEG4pt2_VLD_Simple,	    0xefd64d74, 0xc9e8,0x41d7,0xa5,0xe9,0xe9,0xb0,0xe3,0x9f,0xa3,0x19)
DEFINE_GUID(DXVA_ModeMPEG4pt2_VLD_AdvSimple_NoGMC,  0xed418a9f, 0x010d,0x4eda,0x9a,0xe3,0x9a,0x65,0x35,0x8d,0x8d,0x2e)
DEFINE_GUID(DXVA_ModeMPEG4pt2_VLD_AdvSimple_GMC,    0xab998b5b, 0x4258,0x44a9,0x9f,0xeb,0x94,0xe5,0x97,0xa6,0xba,0xae)

DEFINE_GUID(DXVA_ModeHEVC_VLD_Main,    0x5b11d51b, 0x2f4c,0x4452,0xbc,0xc3,0x09,0xf2,0xa1,0x16,0x0c,0xc0)
DEFINE_GUID(DXVA_ModeHEVC_VLD_Main10,  0x107af0e0, 0xef1a,0x4d19,0xab,0xa8,0x67,0xa1,0x63,0x07,0x3d,0x13)

DEFINE_GUID(DXVA_NoEncrypt,   0x1b81beD0, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5)

define DXVA_ModeWMV8_PostProc		       <DXVA_ModeWMV8_A>
define DXVA_ModeWMV8_MoComp		       <DXVA_ModeWMV8_B>

define DXVA_ModeWMV9_PostProc		       <DXVA_ModeWMV9_A>
define DXVA_ModeWMV9_MoComp		       <DXVA_ModeWMV9_B>
define DXVA_ModeWMV9_IDCT		       <DXVA_ModeWMV9_C>

define DXVA_ModeVC1_PostProc		       <DXVA_ModeVC1_A>
define DXVA_ModeVC1_MoComp		       <DXVA_ModeVC1_B>
define DXVA_ModeVC1_IDCT		       <DXVA_ModeVC1_C>
define DXVA_ModeVC1_VLD			       <DXVA_ModeVC1_D>

define DXVA_ModeH264_MoComp_NoFGT	       <DXVA_ModeH264_A>
define DXVA_ModeH264_MoComp_FGT		       <DXVA_ModeH264_B>
define DXVA_ModeH264_IDCT_NoFGT		       <DXVA_ModeH264_C>
define DXVA_ModeH264_IDCT_FGT		       <DXVA_ModeH264_D>
define DXVA_ModeH264_VLD_NoFGT		       <DXVA_ModeH264_E>
define DXVA_ModeH264_VLD_FGT		       <DXVA_ModeH264_F>

define DXVA_RESTRICTED_MODE_UNRESTRICTED       0xFFFF
define DXVA_RESTRICTED_MODE_H261_A	       1
define DXVA_RESTRICTED_MODE_H261_B	       2

define DXVA_RESTRICTED_MODE_H263_A	       3
define DXVA_RESTRICTED_MODE_H263_B	       4
define DXVA_RESTRICTED_MODE_H263_C	       5
define DXVA_RESTRICTED_MODE_H263_D	       6
define DXVA_RESTRICTED_MODE_H263_E	       7
define DXVA_RESTRICTED_MODE_H263_F	       8

define DXVA_RESTRICTED_MODE_MPEG1_A	       9

define DXVA_RESTRICTED_MODE_MPEG2_A	       0xA
define DXVA_RESTRICTED_MODE_MPEG2_B	       0xB
define DXVA_RESTRICTED_MODE_MPEG2_C	       0xC
define DXVA_RESTRICTED_MODE_MPEG2_D	       0xD
define DXVA_RESTRICTED_MODE_MPEG1_VLD	       0x10
define DXVA_RESTRICTED_MODE_MPEG2and1_VLD      0x11

define DXVA_RESTRICTED_MODE_H264_A	       0x64
define DXVA_RESTRICTED_MODE_H264_B	       0x65
define DXVA_RESTRICTED_MODE_H264_C	       0x66
define DXVA_RESTRICTED_MODE_H264_D	       0x67
define DXVA_RESTRICTED_MODE_H264_E	       0x68
define DXVA_RESTRICTED_MODE_H264_F	       0x69

define DXVA_RESTRICTED_MODE_H264_VLD_WITHFMOASO_NOFGT 0x70

define DXVA_RESTRICTED_MODE_H264_VLD_STEREO_PROGRESSIVE_NOFGT  0x71
define DXVA_RESTRICTED_MODE_H264_VLD_STEREO_NOFGT	       0x72
define DXVA_RESTRICTED_MODE_H264_VLD_MULTIVIEW_NOFGT	       0x73

define DXVA_RESTRICTED_MODE_WMV8_A	       0x80
define DXVA_RESTRICTED_MODE_WMV8_B	       0x81

define DXVA_RESTRICTED_MODE_WMV9_A	       0x90
define DXVA_RESTRICTED_MODE_WMV9_B	       0x91
define DXVA_RESTRICTED_MODE_WMV9_C	       0x94

define DXVA_RESTRICTED_MODE_VC1_A	       0xA0
define DXVA_RESTRICTED_MODE_VC1_B	       0xA1
define DXVA_RESTRICTED_MODE_VC1_C	       0xA2
define DXVA_RESTRICTED_MODE_VC1_D	       0xA3

define DXVA_RESTRICTED_MODE_VC1_D2010	       0xA4

define DXVA_RESTRICTED_MODE_MPEG4PT2_VLD_SIMPLE		   0xB0
define DXVA_RESTRICTED_MODE_MPEG4PT2_VLD_ADV_SIMPLE_NOGMC  0xB1
define DXVA_RESTRICTED_MODE_MPEG4PT2_VLD_ADV_SIMPLE_GMC	   0xB2

define DXVA_RESTRICTED_MODE_WMV8_POSTPROC      DXVA_RESTRICTED_MODE_WMV8_A
define DXVA_RESTRICTED_MODE_WMV8_MOCOMP	       DXVA_RESTRICTED_MODE_WMV8_B

define DXVA_RESTRICTED_MODE_WMV9_POSTPROC      DXVA_RESTRICTED_MODE_WMV9_A
define DXVA_RESTRICTED_MODE_WMV9_MOCOMP	       DXVA_RESTRICTED_MODE_WMV9_B
define DXVA_RESTRICTED_MODE_WMV9_IDCT	       DXVA_RESTRICTED_MODE_WMV9_C

define DXVA_RESTRICTED_MODE_VC1_POSTPROC       DXVA_RESTRICTED_MODE_VC1_A
define DXVA_RESTRICTED_MODE_VC1_MOCOMP	       DXVA_RESTRICTED_MODE_VC1_B
define DXVA_RESTRICTED_MODE_VC1_IDCT	       DXVA_RESTRICTED_MODE_VC1_C
define DXVA_RESTRICTED_MODE_VC1_VLD	       DXVA_RESTRICTED_MODE_VC1_D

define DXVA_RESTRICTED_MODE_H264_MOCOMP_NOFGT  DXVA_RESTRICTED_MODE_H264_A
define DXVA_RESTRICTED_MODE_H264_MOCOMP_FGT    DXVA_RESTRICTED_MODE_H264_B
define DXVA_RESTRICTED_MODE_H264_IDCT_NOFGT    DXVA_RESTRICTED_MODE_H264_C
define DXVA_RESTRICTED_MODE_H264_IDCT_FGT      DXVA_RESTRICTED_MODE_H264_D
define DXVA_RESTRICTED_MODE_H264_VLD_NOFGT     DXVA_RESTRICTED_MODE_H264_E
define DXVA_RESTRICTED_MODE_H264_VLD_FGT       DXVA_RESTRICTED_MODE_H264_F

define DXVA_COMPBUFFER_TYPE_THAT_IS_NOT_USED	0
define DXVA_PICTURE_DECODE_BUFFER		1
define DXVA_MACROBLOCK_CONTROL_BUFFER		2
define DXVA_RESIDUAL_DIFFERENCE_BUFFER		3
define DXVA_DEBLOCKING_CONTROL_BUFFER		4
define DXVA_INVERSE_QUANTIZATION_MATRIX_BUFFER	5
define DXVA_SLICE_CONTROL_BUFFER		6
define DXVA_BITSTREAM_DATA_BUFFER		7
define DXVA_AYUV_BUFFER				8
define DXVA_IA44_SURFACE_BUFFER			9
define DXVA_DPXD_SURFACE_BUFFER		       10
define DXVA_HIGHLIGHT_BUFFER		       11
define DXVA_DCCMD_SURFACE_BUFFER	       12
define DXVA_ALPHA_BLEND_COMBINATION_BUFFER     13
define DXVA_PICTURE_RESAMPLE_BUFFER	       14
define DXVA_READ_BACK_BUFFER		       15


define DXVA_MOTION_VECTOR_BUFFER	       16
define DXVA_FILM_GRAIN_BUFFER		       17

define DXVA_NUM_TYPES_COMP_BUFFERS	       18


define DXVA_PICTURE_DECODING_FUNCTION	     1
define DXVA_ALPHA_BLEND_DATA_LOAD_FUNCTION   2
define DXVA_ALPHA_BLEND_COMBINATION_FUNCTION 3
define DXVA_PICTURE_RESAMPLE_FUNCTION	     4
define DXVA_DEBLOCKING_FILTER_FUNCTION	     5
define DXVA_FILM_GRAIN_SYNTHESIS_FUNCTION    6
define DXVA_STATUS_REPORTING_FUNCTION	     7


define DXVA_EXECUTE_RETURN_OK		       0
define DXVA_EXECUTE_RETURN_DATA_ERROR_MINOR    1
define DXVA_EXECUTE_RETURN_DATA_ERROR_SIGNIF   2
define DXVA_EXECUTE_RETURN_DATA_ERROR_SEVERE   3
define DXVA_EXECUTE_RETURN_OTHER_ERROR_SEVERE  4


.pragma pack(push, 1)

DXVA_ConnectMode	STRUC
guidMode		GUID <>
wRestrictedMode		dw ?
DXVA_ConnectMode	ENDS
LPDXVA_ConnectMode	typedef ptr DXVA_ConnectMode

DXVA_ConfigQueryOrReplyFunc   typedef DWORD
LPDXVA_ConfigQueryOrReplyFunc typedef ptr DWORD

define DXVA_QUERYORREPLYFUNCFLAG_DECODER_PROBE_QUERY	 0xFFFFF1
define DXVA_QUERYORREPLYFUNCFLAG_DECODER_LOCK_QUERY	 0xFFFFF5
define DXVA_QUERYORREPLYFUNCFLAG_ACCEL_PROBE_OK_COPY	 0xFFFFF8
define DXVA_QUERYORREPLYFUNCFLAG_ACCEL_PROBE_OK_PLUS	 0xFFFFF9
define DXVA_QUERYORREPLYFUNCFLAG_ACCEL_LOCK_OK_COPY	 0xFFFFFC
define DXVA_QUERYORREPLYFUNCFLAG_ACCEL_PROBE_FALSE_PLUS	 0xFFFFFB
define DXVA_QUERYORREPLYFUNCFLAG_ACCEL_LOCK_FALSE_PLUS	 0xFFFFFF

.inline readDXVA_QueryOrReplyFuncFlag fastcall :ptr {
	mov eax,[_1]
	shr eax,8
	}

.inline readDXVA_QueryOrReplyFuncFlag_ACCEL fastcall :ptr {
	mov eax,[_1]
	shr eax,11
	and eax,1
	}

.inline readDXVA_QueryOrReplyFuncFlag_LOCK fastcall :ptr {
	mov eax,[_1]
	shr eax,10
	and eax,1
	}
.inline readDXVA_QueryOrReplyFuncFlag_BAD fastcall :ptr {
	mov eax,[_1]
	shr eax,9
	and eax,1
	}
.inline readDXVA_QueryOrReplyFuncFlag_PLUS fastcall :ptr {
	mov eax,[_1]
	shr eax,8
	and eax,1
	}

.inline readDXVA_QueryOrReplyFuncFunc fastcall :ptr {
	mov eax,[_1]
	and eax,0xFF
	}

DXVA_EncryptProtocolFunc typedef DWORD
LPDXVA_EncryptProtocolFunc typedef ptr DWORD

define DXVA_ENCRYPTPROTOCOLFUNCFLAG_HOST    0xFFFF00
define DXVA_ENCRYPTPROTOCOLFUNCFLAG_ACCEL   0xFFFF08

DXVA_EncryptProtocolHeader STRUC
dwFunction		DXVA_EncryptProtocolFunc ?
ReservedBits		dd 3 dup(?)
guidEncryptProtocol	GUID <>
DXVA_EncryptProtocolHeader ENDS
LPDXVA_EncryptProtocolHeader typedef ptr DXVA_EncryptProtocolHeader

DXVA_ConfigPictureDecode  STRUC
dwFunction		DXVA_ConfigQueryOrReplyFunc ?
dwReservedBits		dd 3 dup(?)
guidConfigBitstreamEncryption GUID <>
guidConfigMBcontrolEncryption GUID <>
guidConfigResidDiffEncryption GUID <>
bConfigBitstreamRaw	db ?
bConfigMBcontrolRasterOrder db ?
bConfigResidDiffHost	db ?
bConfigSpatialResid8	db ?
bConfigResid8Subtraction db ?
bConfigSpatialHost8or9Clipping db ?
bConfigSpatialResidInterleaved db ?
bConfigIntraResidUnsigned db ?
bConfigResidDiffAccelerator db ?
bConfigHostInverseScan	db ?
bConfigSpecificIDCT	db ?
bConfig4GroupedCoefs	db ?
DXVA_ConfigPictureDecode ENDS
LPDXVA_ConfigPictureDecode typedef ptr DXVA_ConfigPictureDecode


DXVA_PictureParameters	STRUC
wDecodedPictureIndex	dw ?
wDeblockedPictureIndex	dw ?
wForwardRefPictureIndex dw ?
wBackwardRefPictureIndex dw ?
wPicWidthInMBminus1	dw ?
wPicHeightInMBminus1	dw ?
bMacroblockWidthMinus1	db ?
bMacroblockHeightMinus1 db ?
bBlockWidthMinus1	db ?
bBlockHeightMinus1	db ?
bBPPminus1		db ?
bPicStructure		db ?
bSecondField		db ?
bPicIntra		db ?
bPicBackwardPrediction	db ?
bBidirectionalAveragingMode db ?
bMVprecisionAndChromaRelation db ?
bChromaFormat		db ?
bPicScanFixed		db ?
bPicScanMethod		db ?
bPicReadbackRequests	db ?
bRcontrol		db ?
bPicSpatialResid8	db ?
bPicOverflowBlocks	db ?
bPicExtrapolation	db ?
bPicDeblocked		db ?
bPicDeblockConfined	db ?
bPic4MVallowed		db ?
bPicOBMC		db ?
bPicBinPB		db ?
bMV_RPS			db ?
bReservedBits		db ?
wBitstreamFcodes	dw ?
wBitstreamPCEelements	dw ?
bBitstreamConcealmentNeed db ?
bBitstreamConcealmentMethod db ?
DXVA_PictureParameters	ENDS
LPDXVA_PictureParameters typedef ptr DXVA_PictureParameters

DXVA_PicResample	STRUC
wPicResampleSourcePicIndex dw ?
wPicResampleDestPicIndex dw ?
wPicResampleRcontrol	dw ?
bPicResampleExtrapWidth db ?
bPicResampleExtrapHeight db ?
dwPicResampleSourceWidth dd ?
dwPicResampleSourceHeight dd ?
dwPicResampleDestWidth	dd ?
dwPicResampleDestHeight dd ?
dwPicResampleFullDestWidth dd ?
dwPicResampleFullDestHeight dd ?
DXVA_PicResample	ENDS
LPDXVA_PicResample	typedef ptr DXVA_PicResample


define DXVA_CHROMA_FORMAT_420 1
define DXVA_CHROMA_FORMAT_422 2
define DXVA_CHROMA_FORMAT_444 3

define DXVA_PICTURE_STRUCTURE_TOP_FIELD	   1
define DXVA_PICTURE_STRUCTURE_BOTTOM_FIELD 2
define DXVA_PICTURE_STRUCTURE_FRAME	   3

define DXVA_BIDIRECTIONAL_AVERAGING_MPEG2_ROUND 0
define DXVA_BIDIRECTIONAL_AVERAGING_H263_TRUNC	1

define DXVA_MV_PRECISION_AND_CHROMA_RELATION_MPEG2  0
define DXVA_MV_PRECISION_AND_CHROMA_RELATION_H263   1
define DXVA_MV_PRECISION_AND_CHROMA_RELATION_H261   2

define DXVA_SCAN_METHOD_ZIG_ZAG		     0
define DXVA_SCAN_METHOD_ALTERNATE_VERTICAL   1
define DXVA_SCAN_METHOD_ALTERNATE_HORIZONTAL 2
define DXVA_SCAN_METHOD_ARBITRARY	     3

define DXVA_BITSTREAM_CONCEALMENT_NEED_UNLIKELY 0
define DXVA_BITSTREAM_CONCEALMENT_NEED_MILD	1
define DXVA_BITSTREAM_CONCEALMENT_NEED_LIKELY	2
define DXVA_BITSTREAM_CONCEALMENT_NEED_SEVERE	3

define DXVA_BITSTREAM_CONCEALMENT_METHOD_UNSPECIFIED 0
define DXVA_BITSTREAM_CONCEALMENT_METHOD_INTRA	     1
define DXVA_BITSTREAM_CONCEALMENT_METHOD_FORWARD     2
define DXVA_BITSTREAM_CONCEALMENT_METHOD_BACKWARD    3

DXVA_BufferDescription	STRUC
dwTypeIndex		dd ?
dwBufferIndex		dd ?
dwDataOffset		dd ?
dwDataSize		dd ?
dwFirstMBaddress	dd ?
dwNumMBsInBuffer	dd ?
dwWidth			dd ?
dwHeight		dd ?
dwStride		dd ?
dwReservedBits		dd ?
DXVA_BufferDescription	ENDS
LPDXVA_BufferDescription typedef ptr DXVA_BufferDescription

DXVA_TCoef4Group	STRUC
TCoefIDX		db 4 dup(?)
TCoefValue		SWORD 4 dup(?)
DXVA_TCoef4Group	ENDS
LPDXVA_TCoef4Group	typedef ptr DXVA_TCoef4Group

DXVA_TCoefSingle	STRUC
wIndexWithEOB		dw ?
TCoefValue		SWORD ?
DXVA_TCoefSingle	ENDS
LPDXVA_TCoefSingle	typedef ptr DXVA_TCoefSingle


define DXVA_USUAL_BLOCK_WIDTH	8
define DXVA_USUAL_BLOCK_HEIGHT	8
DXVA_USUAL_BLOCK_SIZE	equ (DXVA_USUAL_BLOCK_WIDTH * DXVA_USUAL_BLOCK_HEIGHT)

DXVA_DeblockingEdgeControl typedef BYTE
LPDXVA_DeblockingEdgeControl typedef ptr DXVA_DeblockingEdgeControl

DXVA_MVvalue		STRUC
horz			SWORD ?
vert			SWORD ?
DXVA_MVvalue		ENDS
LPDXVA_MVvalue		typedef ptr DXVA_MVvalue

DXVA_QmatrixData	STRUC
bNewQmatrix		db 4 dup(?)
Qmatrix			dw 4 * DXVA_USUAL_BLOCK_WIDTH * DXVA_USUAL_BLOCK_HEIGHT dup(?)
DXVA_QmatrixData	ENDS
LPDXVA_QmatrixData	typedef ptr DXVA_QmatrixData

DXVA_SliceInfo		STRUC
wHorizontalPosition	dw ?
wVerticalPosition	dw ?
dwSliceBitsInBuffer	dd ?
dwSliceDataLocation	dd ?
bStartCodeBitOffset	db ?
bReservedBits		db ?
wMBbitOffset		dw ?
wNumberMBsInSlice	dw ?
wQuantizerScaleCode	dw ?
wBadSliceChopping	dw ?
DXVA_SliceInfo		ENDS
LPDXVA_SliceInfo	typedef ptr DXVA_SliceInfo


define DXVA_NumMV_OBMC_off_BinPBwith4MV_off    4

DXVA_NumMV_OBMC_off_BinPBwith4MV_on equ (4+1)
DXVA_NumMV_OBMC_on__BinPB_off equ (10)
DXVA_NumMV_OBMC_on__BinPB_on equ (11)

DXVA_NumBlocksPerMB_420 equ (4+2+0)
DXVA_NumBlocksPerMB_422 equ (4+2+2)
DXVA_NumBlocksPerMB_444 equ (4+4+4)

DXVA_MBctrl_I_HostResidDiff_1 STRUC
wMBaddress		dw ?
wMBtype			dw ?
dwMB_SNL		dd ?
wPatternCode		dw ?
wPC_Overflow		dw ?
dwReservedBits2		dd ?
DXVA_MBctrl_I_HostResidDiff_1 ENDS

DXVA_MBctrl_I_OffHostIDCT_1 STRUC
wMBaddress		dw ?
wMBtype			dw ?
dwMB_SNL		dd ?
wPatternCode		dw ?
bNumCoef		db DXVA_NumBlocksPerMB_420 dup(?)
DXVA_MBctrl_I_OffHostIDCT_1 ENDS

DXVA_MBctrl_P_HostResidDiff_1 STRUC
wMBaddress		dw ?
wMBtype			dw ?
dwMB_SNL		dd ?
wPatternCode		dw ?
wPC_Overflow		dw ?
dwReservedBits2		dd ?
MVector			DXVA_MVvalue DXVA_NumMV_OBMC_off_BinPBwith4MV_off dup(<>)
DXVA_MBctrl_P_HostResidDiff_1 ENDS

DXVA_MBctrl_P_OffHostIDCT_1  STRUC
wMBaddress		dw ?
wMBtype			dw ?
dwMB_SNL		dd ?
wPatternCode		dw ?
bNumCoef		db DXVA_NumBlocksPerMB_420 dup(?)
MVector			DXVA_MVvalue DXVA_NumMV_OBMC_off_BinPBwith4MV_off dup(<>)
DXVA_MBctrl_P_OffHostIDCT_1 ENDS

DXVA_ConfigAlphaLoad	STRUC
dwFunction		DXVA_ConfigQueryOrReplyFunc ?
dwReservedBits		dd 3 dup(?)
bConfigDataType		db ?
DXVA_ConfigAlphaLoad	ENDS
LPDXVA_ConfigAlphaLoad	typedef ptr DXVA_ConfigAlphaLoad

define DXVA_CONFIG_DATA_TYPE_IA44  0
define DXVA_CONFIG_DATA_TYPE_AI44  1
define DXVA_CONFIG_DATA_TYPE_DPXD  2
define DXVA_CONFIG_DATA_TYPE_AYUV  3


DXVA_ConfigAlphaCombine	 STRUC
dwFunction		DXVA_ConfigQueryOrReplyFunc ?
dwReservedBits		dd 3 dup(?)
bConfigBlendType	db ?
bConfigPictureResizing	db ?
bConfigOnlyUsePicDestRectArea db ?
bConfigGraphicResizing	db ?
bConfigWholePlaneAlpha	db ?
DXVA_ConfigAlphaCombine ENDS
LPDXVA_ConfigAlphaCombine typedef ptr DXVA_ConfigAlphaCombine

define DXVA_CONFIG_BLEND_TYPE_FRONT_BUFFER   0
define DXVA_CONFIG_BLEND_TYPE_BACK_HARDWARE  1

DXVA_AYUVsample2	STRUC
bCrValue		db ?
bCbValue		db ?
bY_Value		db ?
bSampleAlpha8		db ?
DXVA_AYUVsample2	ENDS
LPDXVA_AYUVsample2	typedef ptr DXVA_AYUVsample2

DXVA_IA44sample		typedef BYTE
LPDXVA_IA44sample	typedef ptr BYTE
DXVA_AI44sample		typedef BYTE
LPDXVA_AI44sample	typedef ptr BYTE

DXVA_Highlight		STRUC
wHighlightActive	dw ?
wHighlightIndices	dw ?
wHighlightAlphas	dw ?
HighlightRect		RECT <>
DXVA_Highlight		ENDS
LPDXVA_Highlight	typedef ptr DXVA_Highlight
DXVA_DPXD		typedef BYTE
LPDXVA_DPXD		typedef ptr BYTE
DXVA_DCCMD		typedef WORD
LPDXVA_DCCMD		typedef ptr WORD

DXVA_BlendCombination	STRUC
wPictureSourceIndex	dw ?
wBlendedDestinationIndex dw ?
PictureSourceRect16thPel RECT <>
PictureDestinationRect	RECT <>
GraphicSourceRect	RECT <>
GraphicDestinationRect	RECT <>
wBlendDelay		dw ?
bBlendOn		db ?
bWholePlaneAlpha	db ?
OutsideYUVcolor		DXVA_AYUVsample2 <>
DXVA_BlendCombination	ENDS
LPDXVA_BlendCombination typedef ptr DXVA_BlendCombination

DXVA_PicEntry_H264	STRUC
bPicEntry		db ?
DXVA_PicEntry_H264	ENDS
LPDXVA_PicEntry_H264	typedef ptr DXVA_PicEntry_H264

DXVA_PicParams_H264	STRUC
wFrameWidthInMbsMinus1	dw ?
wFrameHeightInMbsMinus1 dw ?
CurrPic			DXVA_PicEntry_H264 <>
num_ref_frames		db ?
wBitFields		dw ?
bit_depth_luma_minus8	db ?
bit_depth_chroma_minus8 db ?
Reserved16Bits		dw ?
StatusReportFeedbackNumber dd ?
RefFrameList		DXVA_PicEntry_H264 16 dup(<>)
CurrFieldOrderCnt	SINT 2 dup(?)
FieldOrderCntList	SINT 16*2 dup(?)
pic_init_qs_minus26	SBYTE ?
chroma_qp_index_offset	SBYTE ?
second_chroma_qp_index_offset SBYTE ?
ContinuationFlag	db ?
pic_init_qp_minus26	SBYTE ?
num_ref_idx_l0_active_minus1 db ?
num_ref_idx_l1_active_minus1 db ?
Reserved8BitsA		db ?
FrameNumList		dw 16 dup(?)
UsedForReferenceFlags	dd ?
NonExistingFrameFlags	dw ?
frame_num		dw ?
log2_max_frame_num_minus4 db ?
pic_order_cnt_type	db ?
log2_max_pic_order_cnt_lsb_minus4 db ?
delta_pic_order_always_zero_flag db ?
direct_8x8_inference_flag db ?
entropy_coding_mode_flag db ?
pic_order_present_flag	db ?
num_slice_groups_minus1 db ?
slice_group_map_type	db ?
deblocking_filter_control_present_flag db ?
redundant_pic_cnt_present_flag db ?
Reserved8BitsB		db ?
slice_group_change_rate_minus1 dw ?
SliceGroupMap		db 810 dup(?)
DXVA_PicParams_H264	ENDS
LPDXVA_PicParams_H264	typedef ptr DXVA_PicParams_H264

DXVA_Qmatrix_H264	STRUC
bScalingLists4x4	db 6*16 dup(?)
bScalingLists8x8	db 2*64 dup(?)
DXVA_Qmatrix_H264	ENDS
LPDXVA_Qmatrix_H264	typedef ptr DXVA_Qmatrix_H264

DXVA_Slice_H264_Short	STRUC
BSNALunitDataLocation	dd ?
SliceBytesInBuffer	dd ?
wBadSliceChopping	dw ?
DXVA_Slice_H264_Short	ENDS
LPDXVA_Slice_H264_Short typedef ptr DXVA_Slice_H264_Short

DXVA_Slice_H264_Long	STRUC
BSNALunitDataLocation	dd ?
SliceBytesInBuffer	dd ?
wBadSliceChopping	dw ?
first_mb_in_slice	dw ?
NumMbsForSlice		dw ?
BitOffsetToSliceData	dw ?
slice_type		db ?
luma_log2_weight_denom	db ?
chroma_log2_weight_denom db ?
num_ref_idx_l0_active_minus1 db ?
num_ref_idx_l1_active_minus1 db ?
slice_alpha_c0_offset_div2 SBYTE ?
slice_beta_offset_div2	SBYTE ?
Reserved8Bits		db ?
RefPicList		DXVA_PicEntry_H264 2*32 dup(<>)
Weights			SWORD 2*32*3*2 dup(?)
slice_qs_delta		SBYTE ?
slice_qp_delta		SBYTE ?
redundant_pic_cnt	db ?
direct_spatial_mv_pred_flag db ?
cabac_init_idc		db ?
disable_deblocking_filter_idc db ?
slice_id		dw ?
DXVA_Slice_H264_Long	ENDS
LPDXVA_Slice_H264_Long	typedef ptr DXVA_Slice_H264_Long

DXVA_MBctrl_H264	STRUC
dwMBtype		dd ?
CurrMbAddr		dw ?
wPatternCode		dw 3 dup(?)
bQpPrime		db 3 dup(?)
bMBresidDataQuantity	db ?
dwMBdataLocation	dd ?
UNION ; {
 STRUC
  LumaIntraPredModes	dw 4 dup(?)
  bMbIntraStruct	db ?
  ReservedIntra24Bits	db 3 dup(?)
 ENDS
 STRUC
  bSubMbShapes		db ?
  bSubMbPredModes	db ?
  wMvBuffOffset		dw ?
  bRefPicSelect		db 2*4 dup(?)
 ENDS
ENDS
DXVA_MBctrl_H264	ENDS
LPDXVA_MBctrl_H264	typedef ptr DXVA_MBctrl_H264


DXVA_DeblockIndexAB_H264  STRUC
bIndexAinternal		db ?
bIndexBinternal		db ?
bIndexAleft0		db ?
bIndexBleft0		db ?
bIndexAleft1		db ?
bIndexBleft1		db ?
bIndexAtop0		db ?
bIndexBtop0		db ?
bIndexAtop1		db ?
bIndexBtop1		db ?
DXVA_DeblockIndexAB_H264 ENDS
LPDXVA_DeblockIndexAB_H264 typedef ptr DXVA_DeblockIndexAB_H264


DXVA_Deblock_H264	STRUC
CurrMbAddr		dw ?
FirstByte		db ?
Reserved8Bits		db ?
bbSinternalLeftVert	db ?
bbSinternalMidVert	db ?
bbSinternalRightVert	db ?
bbSinternalTopHorz	db ?
bbSinternalMidHorz	db ?
bbSinternalBotHorz	db ?
wbSLeft0		dw ?
wbSLeft1		dw ?
wbSTop0			dw ?
wbSTop1			dw ?
IndexAB			DXVA_DeblockIndexAB_H264 3 dup(<>)
DXVA_Deblock_H264	ENDS
LPDXVA_Deblock_H264	typedef ptr DXVA_Deblock_H264


DXVA_FilmGrainChar_H264 STRUC
wFrameWidthInMbsMinus1	dw ?
wFrameHeightInMbsMinus1 dw ?
InPic			DXVA_PicEntry_H264 <>
OutPic			DXVA_PicEntry_H264 <>
PicOrderCnt_offset	dw ?
CurrPicOrderCnt		SINT ?
StatusReportFeedbackNumber dd ?
model_id		db ?
separate_colour_description_present_flag db ?
film_grain_bit_depth_luma_minus8 db ?
film_grain_bit_depth_chroma_minus8 db ?
film_grain_full_range_flag db ?
film_grain_colour_primaries db ?
film_grain_transfer_characteristics db ?
film_grain_matrix_coefficients db ?
blending_mode_id	db ?
log2_scale_factor	db ?
comp_model_present_flag db 4 dup(?)
num_intensity_intervals_minus1 db 4 dup(?)
num_model_values_minus1 db 4 dup(?)
intensity_interval_lower_bound db 3*16 dup(?)
intensity_interval_upper_bound db 3*16 dup(?)
comp_model_value	SWORD 3*16*8 dup(?)
DXVA_FilmGrainChar_H264 ENDS
LPDXVA_FilmGrainChar_H264 typedef ptr DXVA_FilmGrainChar_H264

DXVA_Status_H264	STRUC
StatusReportFeedbackNumber dd ?
CurrPic			DXVA_PicEntry_H264 <>
field_pic_flag		db ?
bDXVA_Func		db ?
bBufType		db ?
bStatus			db ?
bReserved8Bits		db ?
wNumMbsAffected		dw ?
DXVA_Status_H264	ENDS
LPDXVA_Status_H264	typedef ptr DXVA_Status_H264

DXVA_PicParams_H264_MVC	 STRUC
wFrameWidthInMbsMinus1	dw ?
wFrameHeightInMbsMinus1 dw ?
CurrPic			DXVA_PicEntry_H264 <>
num_ref_frames		db ?
wBitFields		dw ?
bit_depth_luma_minus8	db ?
bit_depth_chroma_minus8 db ?
Reserved16Bits		dw ?
StatusReportFeedbackNumber dd ?
RefFrameList		DXVA_PicEntry_H264 16 dup(<>)
CurrFieldOrderCnt	SINT 2 dup(?)
FieldOrderCntList	SINT 16*2 dup(?)
pic_init_qs_minus26	SBYTE ?
chroma_qp_index_offset	SBYTE ?
second_chroma_qp_index_offset SBYTE ?
ContinuationFlag	db ?
pic_init_qp_minus26	SBYTE ?
num_ref_idx_l0_active_minus1 db ?
num_ref_idx_l1_active_minus1 db ?
Reserved8BitsA		db ?
FrameNumList		dw 16 dup(?)
UsedForReferenceFlags	dd ?
NonExistingFrameFlags	dw ?
frame_num		dw ?
log2_max_frame_num_minus4 db ?
pic_order_cnt_type	db ?
log2_max_pic_order_cnt_lsb_minus4 db ?
delta_pic_order_always_zero_flag db ?
direct_8x8_inference_flag db ?
entropy_coding_mode_flag db ?
pic_order_present_flag	db ?
num_slice_groups_minus1 db ?
slice_group_map_type	db ?
deblocking_filter_control_present_flag db ?
redundant_pic_cnt_present_flag db ?
Reserved8BitsB		db ?
slice_group_change_rate_minus1 dw ?
num_views_minus1	db ?
view_id			dw 16 dup(?)
num_anchor_refs_l0	db 16 dup(?)
anchor_ref_l0		dw 16*16 dup(?)
num_anchor_refs_l1	db 16 dup(?)
anchor_ref_l1		dw 16*16 dup(?)
num_non_anchor_refs_l0	db 16 dup(?)
non_anchor_ref_l0	dw 16*16 dup(?)
num_non_anchor_refs_l1	db 16 dup(?)
non_anchor_ref_l1	dw 16*16 dup(?)
curr_view_id		dw ?
anchor_pic_flag		db ?
inter_view_flag		db ?
ViewIDList		dw 16 dup(?)
DXVA_PicParams_H264_MVC ENDS
LPDXVA_PicParams_H264_MVC typedef ptr DXVA_PicParams_H264_MVC


DXVA_Status_VC1		STRUC
StatusReportFeedbackNumber dw ?
wDecodedPictureIndex	dw ?
wDeblockedPictureIndex	dw ?
bPicStructure		db ?
bBufType		db ?
bStatus			db ?
bReserved8Bits		db ?
wNumMbsAffected		dw ?
DXVA_Status_VC1		ENDS
LPDXVA_Status_VC1	typedef ptr DXVA_Status_VC1

DXVA_PicParams_MPEG4_PART2 STRUC
short_video_header	db ?
vop_coding_type		db ?
vop_quant		db ?
wDecodedPictureIndex	dw ?
wDeblockedPictureIndex	dw ?
wForwardRefPictureIndex dw ?
wBackwardRefPictureIndex dw ?
vop_time_increment_resolution dw ?
TRB			dd 2 dup(?)
TRD			dd 2 dup(?)
wPicFlagBitFields	dw ?
profile_and_level_indication db ?
video_object_layer_verid db ?
vop_width		dw ?
vop_height		dw ?
wSpriteBitFields	dw ?
warping_mv		SWORD 4*2 dup(?)
wFcodeBitFields		db ?
StatusReportFeedbackNumber dw ?
Reserved16BitsA		dw ?
Reserved16BitsB		dw ?
DXVA_PicParams_MPEG4_PART2 ENDS
LPDXVA_PicParams_MPEG4_PART2 typedef ptr DXVA_PicParams_MPEG4_PART2

DXVA_PicEntry_HEVC	STRUC
bPicEntry		db ?
DXVA_PicEntry_HEVC	ENDS
LPDXVA_PicEntry_HEVC	typedef ptr DXVA_PicEntry_HEVC

DXVA_PicParams_HEVC	STRUC
PicWidthInMinCbsY	dw ?
PicHeightInMinCbsY	dw ?
wFormatAndSequenceInfoFlags dw ?
CurrPic			DXVA_PicEntry_HEVC <>
sps_max_dec_pic_buffering_minus1 db ?
log2_min_luma_coding_block_size_minus3 db ?
log2_diff_max_min_luma_coding_block_size db ?
log2_min_transform_block_size_minus2 db ?
log2_diff_max_min_transform_block_size db ?
max_transform_hierarchy_depth_inter db ?
max_transform_hierarchy_depth_intra db ?
num_short_term_ref_pic_sets db ?
num_long_term_ref_pics_sps db ?
num_ref_idx_l0_default_active_minus1 db ?
num_ref_idx_l1_default_active_minus1 db ?
init_qp_minus26		SBYTE ?
ucNumDeltaPocsOfRefRpsIdx db ?
wNumBitsForShortTermRPSInSlice dw ?
ReservedBits2		dw ?
dwCodingParamToolFlags	dd ?
dwCodingSettingPicturePropertyFlags dd ?
pps_cb_qp_offset	SBYTE ?
pps_cr_qp_offset	SBYTE ?
num_tile_columns_minus1 db ?
num_tile_rows_minus1	db ?
column_width_minus1	dw 19 dup(?)
row_height_minus1	dw 21 dup(?)
diff_cu_qp_delta_depth	db ?
pps_beta_offset_div2	SBYTE ?
pps_tc_offset_div2	SBYTE ?
log2_parallel_merge_level_minus2 db ?
CurrPicOrderCntVal	SINT ?
RefPicList		DXVA_PicEntry_HEVC 15 dup(<>)
ReservedBits5		db ?
PicOrderCntValList	SINT 15 dup(?)
RefPicSetStCurrBefore	db 8 dup(?)
RefPicSetStCurrAfter	db 8 dup(?)
RefPicSetLtCurr		db 8 dup(?)
ReservedBits6		dw ?
ReservedBits7		dw ?
StatusReportFeedbackNumber dd ?
DXVA_PicParams_HEVC	ENDS
LPDXVA_PicParams_HEVC	typedef ptr DXVA_PicParams_HEVC

DXVA_Qmatrix_HEVC	STRUC
ucScalingLists0		db 6*16 dup(?)
ucScalingLists1		db 6*64 dup(?)
ucScalingLists2		db 6*64 dup(?)
ucScalingLists3		db 2*64 dup(?)
ucScalingListDCCoefSizeID2 db 6 dup(?)
ucScalingListDCCoefSizeID3 db 2 dup(?)
DXVA_Qmatrix_HEVC	ENDS
LPDXVA_Qmatrix_HEVC	typedef ptr DXVA_Qmatrix_HEVC

DXVA_Slice_HEVC_Short	STRUC
BSNALunitDataLocation	dd ?
SliceBytesInBuffer	dd ?
wBadSliceChopping	dw ?
DXVA_Slice_HEVC_Short	ENDS
LPDXVA_Slice_HEVC_Short typedef ptr DXVA_Slice_HEVC_Short

.pragma pack(push, 16)


LPDXVA_MBctrl_I_HostResidDiff_1 typedef ptr DXVA_MBctrl_I_HostResidDiff_1
LPDXVA_MBctrl_I_OffHostIDCT_1	typedef ptr DXVA_MBctrl_I_OffHostIDCT_1
LPDXVA_MBctrl_P_HostResidDiff_1 typedef ptr DXVA_MBctrl_P_HostResidDiff_1
LPDXVA_MBctrl_P_OffHostIDCT_1	typedef ptr DXVA_MBctrl_P_OffHostIDCT_1


.pragma pack(pop)
.pragma pack(pop)

endif

ifndef __DIRECTX_VA_SAMPLEFORMAT__
define __DIRECTX_VA_SAMPLEFORMAT__

.enum DXVA_SampleFormat {
    DXVA_SampleFormatMask = 0xFF,
    DXVA_SampleUnknown = 0,
    DXVA_SamplePreviousFrame = 1,
    DXVA_SampleProgressiveFrame = 2,
    DXVA_SampleFieldInterleavedEvenFirst = 3,
    DXVA_SampleFieldInterleavedOddFirst = 4,
    DXVA_SampleFieldSingleEven = 5,
    DXVA_SampleFieldSingleOdd = 6,
    DXVA_SampleSubStream = 7
    }

DXVABitMask macro __n
	exitm<(not ((not 0) shl __n))>
	endm

define DXVA_ExtColorData_ShiftBase 8
DXVAColorMask macro __bits, __base
	exitm<(DXVABitMask(__bits) shl (__base))>
	endm


.enum DXVA_VideoTransferFunction {
    DXVA_VideoTransFuncShift = (DXVA_ExtColorData_ShiftBase + 19),
    DXVA_VideoTransFuncMask = DXVAColorMask(5, DXVA_VideoTransFuncShift),
    DXVA_VideoTransFunc_Unknown = 0,
    DXVA_VideoTransFunc_10 = 1,
    DXVA_VideoTransFunc_18 = 2,
    DXVA_VideoTransFunc_20 = 3,
    DXVA_VideoTransFunc_22 = 4,
    DXVA_VideoTransFunc_22_709	= 5,
    DXVA_VideoTransFunc_22_240M = 6,
    DXVA_VideoTransFunc_22_8bit_sRGB = 7,
    DXVA_VideoTransFunc_28 = 8
    }

.enum DXVA_VideoPrimaries {
    DXVA_VideoPrimariesShift = (DXVA_ExtColorData_ShiftBase + 14),
    DXVA_VideoPrimariesMask = DXVAColorMask(5, DXVA_VideoPrimariesShift),
    DXVA_VideoPrimaries_Unknown = 0,
    DXVA_VideoPrimaries_reserved = 1,
    DXVA_VideoPrimaries_BT709 = 2,
    DXVA_VideoPrimaries_BT470_2_SysM = 3,
    DXVA_VideoPrimaries_BT470_2_SysBG = 4,
    DXVA_VideoPrimaries_SMPTE170M = 5,
    DXVA_VideoPrimaries_SMPTE240M = 6,
    DXVA_VideoPrimaries_EBU3213 = 7,
    DXVA_VideoPrimaries_SMPTE_C = 8
    }

.enum DXVA_VideoLighting {
    DXVA_VideoLightingShift = (DXVA_ExtColorData_ShiftBase + 10),
    DXVA_VideoLightingMask = DXVAColorMask(4, DXVA_VideoLightingShift),
    DXVA_VideoLighting_Unknown = 0,
    DXVA_VideoLighting_bright = 1,
    DXVA_VideoLighting_office = 2,
    DXVA_VideoLighting_dim = 3,
    DXVA_VideoLighting_dark = 4
    }

.enum DXVA_VideoTransferMatrix {
    DXVA_VideoTransferMatrixShift = (DXVA_ExtColorData_ShiftBase + 7),
    DXVA_VideoTransferMatrixMask = DXVAColorMask(3, DXVA_VideoTransferMatrixShift),
    DXVA_VideoTransferMatrix_Unknown = 0,
    DXVA_VideoTransferMatrix_BT709 = 1,
    DXVA_VideoTransferMatrix_BT601 = 2,
    DXVA_VideoTransferMatrix_SMPTE240M = 3
    }

.enum DXVA_NominalRange {
    DXVA_NominalRangeShift = (DXVA_ExtColorData_ShiftBase + 4),
    DXVA_NominalRangeMask = DXVAColorMask(3, DXVA_NominalRangeShift),
    DXVA_NominalRange_Unknown = 0,
    DXVA_NominalRange_Normal = 1,
    DXVA_NominalRange_Wide = 2,
    DXVA_NominalRange_0_255 = 1,
    DXVA_NominalRange_16_235 = 2,
    DXVA_NominalRange_48_208 = 3
    }


.enum DXVA_VideoChromaSubsampling {
    DXVA_VideoChromaSubsamplingShift = (DXVA_ExtColorData_ShiftBase + 0),
    DXVA_VideoChromaSubsamplingMask = DXVAColorMask(4, DXVA_VideoChromaSubsamplingShift),
    DXVA_VideoChromaSubsampling_Unknown = 0,
    DXVA_VideoChromaSubsampling_ProgressiveChroma = 0x8,
    DXVA_VideoChromaSubsampling_Horizontally_Cosited = 0x4,
    DXVA_VideoChromaSubsampling_Vertically_Cosited = 0x2,
    DXVA_VideoChromaSubsampling_Vertically_AlignedChromaPlanes = 0x1,
    DXVA_VideoChromaSubsampling_MPEG2  =   DXVA_VideoChromaSubsampling_Horizontally_Cosited or DXVA_VideoChromaSubsampling_Vertically_AlignedChromaPlanes,
    DXVA_VideoChromaSubsampling_MPEG1  =   DXVA_VideoChromaSubsampling_Vertically_AlignedChromaPlanes,
    DXVA_VideoChromaSubsampling_DV_PAL	=  DXVA_VideoChromaSubsampling_Horizontally_Cosited or DXVA_VideoChromaSubsampling_Vertically_Cosited,
    DXVA_VideoChromaSubsampling_Cosited =  DXVA_VideoChromaSubsampling_Horizontally_Cosited or DXVA_VideoChromaSubsampling_Vertically_Cosited or DXVA_VideoChromaSubsampling_Vertically_AlignedChromaPlanes,
    }

DXVA_ExtendedFormat	STRUC
RECORD
 SampleFormat		dd : 8 ?
 VideoChromaSubsampling dd : 4 ?
 NominalRange		dd : 3 ?
 VideoTransferMatrix	dd : 3 ?
 VideoLighting		dd : 4 ?
 VideoPrimaries		dd : 5 ?
 VideoTransferFunction	dd : 5 ?
ENDS
DXVA_ExtendedFormat	ENDS

endif



ifndef __DIRECTX_VA_DEINTERLACE__
define __DIRECTX_VA_DEINTERLACE__

REFERENCE_TIME typedef LONGLONG

DEFINE_GUID(DXVA_DeinterlaceBobDevice, 0x335aa36e,0x7884,0x43a4,0x9c,0x91,0x7f,0x87,0xfa,0xf3,0xe3,0x7e)
DEFINE_GUID(DXVA_DeinterlaceContainerDevice, 0x0e85cb93,0x3046,0x4ff0,0xae,0xcc,0xd5,0x8c,0xb5,0xf0,0x35,0xfd)

if not defined(DIRECT3D_VERSION) ;OR (DIRECT3D_VERSION LT 0x0800)

D3DFORMAT typedef DWORD

.enum {
    D3DPOOL_DEFAULT		    = 0,
    D3DPOOL_MANAGED		    = 1,
    D3DPOOL_SYSTEMMEM		    = 2,
    D3DPOOL_SCRATCH		    = 3,
    D3DPOOL_LOCALVIDMEM		    = 4,
    D3DPOOL_NONLOCALVIDMEM	    = 5,
    D3DPOOL_FORCE_DWORD		    = 0x7fffffff
    }

endif

DXVA_Frequency		STRUC
Numerator		dd ?
Denominator		dd ?
DXVA_Frequency		ENDS

DXVA_VideoDesc		STRUC
Size			dd ?
SampleWidth		dd ?
SampleHeight		dd ?
SampleFormat		dd ?
d3dFormat		D3DFORMAT ?
InputSampleFreq		DXVA_Frequency <>
OutputFrameFreq		DXVA_Frequency <>
DXVA_VideoDesc		ENDS
LPDXVA_VideoDesc	typedef ptr DXVA_VideoDesc

.enum DXVA_VideoProcessCaps {
    DXVA_VideoProcess_None		    = 0x0000,
    DXVA_VideoProcess_YUV2RGB		    = 0x0001,
    DXVA_VideoProcess_StretchX		    = 0x0002,
    DXVA_VideoProcess_StretchY		    = 0x0004,
    DXVA_VideoProcess_AlphaBlend	    = 0x0008,
    DXVA_VideoProcess_SubRects		    = 0x0010,
    DXVA_VideoProcess_SubStreams	    = 0x0020,
    DXVA_VideoProcess_SubStreamsExtended    = 0x0040,
    DXVA_VideoProcess_YUV2RGBExtended	    = 0x0080,
    DXVA_VideoProcess_AlphaBlendExtended    = 0x0100
    }

.enum DXVA_DeinterlaceTech {
    DXVA_DeinterlaceTech_Unknown		= 0x0000,
    DXVA_DeinterlaceTech_BOBLineReplicate	= 0x0001,
    DXVA_DeinterlaceTech_BOBVerticalStretch	= 0x0002,
    DXVA_DeinterlaceTech_BOBVerticalStretch4Tap = 0x0100,
    DXVA_DeinterlaceTech_MedianFiltering	= 0x0004,
    DXVA_DeinterlaceTech_EdgeFiltering		= 0x0010,
    DXVA_DeinterlaceTech_FieldAdaptive		= 0x0020,
    DXVA_DeinterlaceTech_PixelAdaptive		= 0x0040,
    DXVA_DeinterlaceTech_MotionVectorSteered	= 0x0080
    }


DXVA_VideoSample	STRUC
rtStart			REFERENCE_TIME ?
rtEnd			REFERENCE_TIME ?
SampleFormat		DXVA_SampleFormat ?
lpDDSSrcSurface		PVOID ?
DXVA_VideoSample	ENDS
LPDXVA_VideoSample	typedef ptr DXVA_VideoSample


.enum DXVA_SampleFlags {
    DXVA_SampleFlagsMask = ( DXVABit(3) or  DXVABit(2) or DXVABit(1) or DXVABit(0) ),
    DXVA_SampleFlag_Palette_Changed	    = 0x0001,
    DXVA_SampleFlag_SrcRect_Changed	    = 0x0002,
    DXVA_SampleFlag_DstRect_Changed	    = 0x0004,
    DXVA_SampleFlag_ColorData_Changed	    = 0x0008,
    }

.enum DXVA_DestinationFlags {
    DXVA_DestinationFlagMask = ( DXVABit(3) or DXVABit(2) or DXVABit(1) or DXVABit(0) ),
    DXVA_DestinationFlag_Background_Changed = 0x0001,
    DXVA_DestinationFlag_TargetRect_Changed = 0x0002,
    DXVA_DestinationFlag_ColorData_Changed  = 0x0004,
    DXVA_DestinationFlag_Alpha_Changed	    = 0x0008
    }


DXVA_VideoSample2	STRUC
ifdef _WIN64
Size			dd ?
Reserved		dd ?
endif
rtStart			REFERENCE_TIME ?
rtEnd			REFERENCE_TIME ?
SampleFormat		dd ?
SampleFlags		dd ?
lpDDSSrcSurface		PVOID ?
rcSrc			RECT <>
rcDst			RECT <>
Palette			DXVA_AYUVsample2 16 dup(<>)
DXVA_VideoSample2	ENDS
LPDXVA_VideoSample2	typedef ptr DXVA_VideoSample2

DXVA_DeinterlaceCaps	STRUC
Size			dd ?
NumPreviousOutputFrames dd ?
InputPool		dd ?
NumForwardRefSamples	dd ?
NumBackwardRefSamples	dd ?
d3dOutputFormat		D3DFORMAT ?
VideoProcessingCaps	DXVA_VideoProcessCaps ?
DeinterlaceTechnology	DXVA_DeinterlaceTech ?
DXVA_DeinterlaceCaps	ENDS
LPDXVA_DeinterlaceCaps	typedef ptr DXVA_DeinterlaceCaps

define MAX_DEINTERLACE_SURFACES 32

ifdef _WIN64
DXVA_VideoSample32	STRUC
rtStart			REFERENCE_TIME ?
rtEnd			REFERENCE_TIME ?
SampleFormat		dd ?
SampleFlags		dd ?
lpDDSSrcSurface		dd ?
rcSrc			RECT <>
rcDst			RECT <>
Palette			DXVA_AYUVsample2 16 dup(<>)
Pad			dd ?
DXVA_VideoSample32	ENDS

DXVA_DeinterlaceBltEx32 STRUC
Size			dd ?
BackgroundColor		DXVA_AYUVsample2 <>
rcTarget		RECT <>
rtTarget		REFERENCE_TIME ?
NumSourceSurfaces	dd ?
Alpha			real4 ?
Source			DXVA_VideoSample32 MAX_DEINTERLACE_SURFACES dup(<>)
DestinationFormat	dd ?
DestinationFlags	dd ?
DXVA_DeinterlaceBltEx32 ENDS
endif


DXVA_DeinterlaceBlt	STRUC
Size			dd ?
Reserved		dd ?
rtTarget		REFERENCE_TIME ?
DstRect			RECT <>
SrcRect			RECT <>
NumSourceSurfaces	dd ?
Alpha			FLOAT ?
Source			DXVA_VideoSample MAX_DEINTERLACE_SURFACES dup(<>)
DXVA_DeinterlaceBlt	ENDS

define DXVA_DeinterlaceBltFnCode 0x01


DXVA_DeinterlaceBltEx	STRUC
Size			dd ?
BackgroundColor		DXVA_AYUVsample2 <>
rcTarget		RECT <>
rtTarget		REFERENCE_TIME ?
NumSourceSurfaces	dd ?
Alpha			real4 ?
Source			DXVA_VideoSample2 MAX_DEINTERLACE_SURFACES dup(<>)
DestinationFormat	dd ?
DestinationFlags	dd ?
DXVA_DeinterlaceBltEx	ENDS

define DXVA_DeinterlaceBltExFnCode 0x02


define MAX_DEINTERLACE_DEVICE_GUIDS 32
DXVA_DeinterlaceQueryAvailableModes STRUC
Size			dd ?
NumGuids		dd ?
Guids			GUID MAX_DEINTERLACE_DEVICE_GUIDS dup(<>)
DXVA_DeinterlaceQueryAvailableModes ENDS

define DXVA_DeinterlaceQueryAvailableModesFnCode 0x01


DXVA_DeinterlaceQueryModeCaps STRUC
Size			dd ?
Guid			GUID <>
VideoDesc		DXVA_VideoDesc <>
DXVA_DeinterlaceQueryModeCaps ENDS

define DXVA_DeinterlaceQueryModeCapsFnCode 0x02

endif


ifndef __DIRECTX_VA_PROCAMPCONTROL__
define __DIRECTX_VA_PROCAMPCONTROL__

DEFINE_GUID(DXVA_ProcAmpControlDevice, 0x9f200913,0x2ffd,0x4056,0x9f,0x1e,0xe1,0xb5,0x08,0xf2,0x2d,0xcf)

.enum DXVA_ProcAmpControlProp {
    DXVA_ProcAmp_None	    = 0x0000,
    DXVA_ProcAmp_Brightness = 0x0001,
    DXVA_ProcAmp_Contrast   = 0x0002,
    DXVA_ProcAmp_Hue	    = 0x0004,
    DXVA_ProcAmp_Saturation = 0x0008
    }


DXVA_ProcAmpControlCaps STRUC
Size			dd ?
InputPool		dd ?
d3dOutputFormat		D3DFORMAT ?
ProcAmpControlProps	dd ?
VideoProcessingCaps	dd ?
DXVA_ProcAmpControlCaps ENDS
LPDXVA_ProcAmpControlCaps typedef ptr DXVA_ProcAmpControlCaps

define DXVA_ProcAmpControlQueryCapsFnCode 0x03

DXVA_ProcAmpControlQueryRange STRUC
Size			dd ?
ProcAmpControlProp	DXVA_ProcAmpControlProp ?
VideoDesc		DXVA_VideoDesc <>
DXVA_ProcAmpControlQueryRange ENDS
LPDXVA_ProcAmpControlQueryRange typedef ptr DXVA_ProcAmpControlQueryRange

DXVA_VideoPropertyRange STRUC
MinValue		real4 ?
MaxValue		real4 ?
DefaultValue		real4 ?
StepSize		real4 ?
DXVA_VideoPropertyRange ENDS
LPDXVA_VideoPropertyRange typedef ptr DXVA_VideoPropertyRange

define DXVA_ProcAmpControlQueryRangeFnCode 0x04


DXVA_ProcAmpControlBlt	STRUC
Size			dd ?
DstRect			RECT <>
SrcRect			RECT <>
Alpha			real4 ?
Brightness		real4 ?
Contrast		real4 ?
Hue			real4 ?
Saturation		real4 ?
DXVA_ProcAmpControlBlt	ENDS

define DXVA_ProcAmpControlBltFnCode 0x01

endif

ifndef __DIRECTX_VA_CERTOUTPUTPROTECT__
define __DIRECTX_VA_CERTOUTPUTPROTECT__


DEFINE_GUID(DXVA_COPPDevice, 0xd2457add,0x8999,0x45ed,0x8a,0x8a,0xd1,0xaa,0x04,0x7b,0xa4,0xd5)


define DXVA_COPPGetCertificateLengthFnCode 0x01


define DXVA_COPPKeyExchangeFnCode 0x02


DXVA_COPPSignature	STRUC
Signature		db 256 dup(?)
DXVA_COPPSignature	ENDS
LPDXVA_COPPSignature	typedef ptr DXVA_COPPSignature

define DXVA_COPPSequenceStartFnCode 0x03

DXVA_COPPCommand	STRUC
macKDI			GUID <>
guidCommandID		GUID <>
dwSequence		dd ?
cbSizeData		dd ?
CommandData		db 4056 dup(?)
DXVA_COPPCommand	ENDS
LPDXVA_COPPCommand	typedef ptr DXVA_COPPCommand

define DXVA_COPPCommandFnCode 0x04


DEFINE_GUID(DXVA_COPPSetProtectionLevel, 0x9bb9327c,0x4eb5,0x4727,0x9f,0x00,0xb4,0x2b,0x09,0x19,0xc0,0xda)

DXVA_COPPSetProtectionLevelCmdData STRUC
ProtType		dd ?
ProtLevel		dd ?
ExtendedInfoChangeMask	dd ?
ExtendedInfoData	dd ?
DXVA_COPPSetProtectionLevelCmdData ENDS

.enum COPP_DPCP_Protection_Level {
    COPP_DPCP_Level0	    = 0,
    COPP_DPCP_LevelMin	    = COPP_DPCP_Level0,
    COPP_DPCP_Level1	    = 1,
    COPP_DPCP_LevelMax	    = COPP_DPCP_Level1,
    COPP_DPCP_ForceDWORD    = 0x7fffffff
    }


.enum COPP_HDCP_Protection_Level {
    COPP_HDCP_Level0	= 0,
    COPP_HDCP_LevelMin	= COPP_HDCP_Level0,
    COPP_HDCP_Level1	= 1,
    COPP_HDCP_LevelMax	= COPP_HDCP_Level1,
    COPP_HDCP_ForceDWORD = 0x7fffffff
    }

.enum COPP_CGMSA_Protection_Level {
    COPP_CGMSA_Disabled = 0,
    COPP_CGMSA_LevelMin = COPP_CGMSA_Disabled,
    COPP_CGMSA_CopyFreely = 1,
    COPP_CGMSA_CopyNoMore = 2,
    COPP_CGMSA_CopyOneGeneration   = 3,
    COPP_CGMSA_CopyNever = 4,
    COPP_CGMSA_RedistributionControlRequired = 0x08,
    COPP_CGMSA_LevelMax = (COPP_CGMSA_RedistributionControlRequired + COPP_CGMSA_CopyNever),
    COPP_CGMSA_ForceDWORD = 0x7fffffff
    }

.enum COPP_ACP_Protection_Level {
    COPP_ACP_Level0	= 0,
    COPP_ACP_LevelMin	= COPP_ACP_Level0,
    COPP_ACP_Level1	= 1,
    COPP_ACP_Level2	= 2,
    COPP_ACP_Level3	= 3,
    COPP_ACP_LevelMax	= COPP_ACP_Level3,
    COPP_ACP_ForceDWORD = 0x7fffffff
    }

define COPP_NoProtectionLevelAvailable	-1
define COPP_DefaultProtectionLevel 0


.enum {
    COPP_ProtectionType_Unknown	     = 0x80000000,
    COPP_ProtectionType_None	     = 0x00000000,
    COPP_ProtectionType_HDCP	     = 0x00000001,
    COPP_ProtectionType_ACP	     = 0x00000002,
    COPP_ProtectionType_CGMSA	     = 0x00000004,
    COPP_ProtectionType_DPCP	     = 0x00000010,
    COPP_ProtectionType_Mask	     = 0x80000017,
    COPP_ProtectionType_Reserved     = 0x7FFFFFF8
    }

DEFINE_GUID(DXVA_COPPSetSignaling, 0x9a631a5, 0xd684, 0x4c60, 0x8e, 0x4d, 0xd3, 0xbb, 0xf, 0xb, 0xe3, 0xee)

DXVA_COPPSetSignalingCmdData STRUC
ActiveTVProtectionStandard dd ?
AspectRatioChangeMask1	dd ?
AspectRatioData1	dd ?
AspectRatioChangeMask2	dd ?
AspectRatioData2	dd ?
AspectRatioChangeMask3	dd ?
AspectRatioData3	dd ?
ExtendedInfoChangeMask	dd 4 dup(?)
ExtendedInfoData	dd 4 dup(?)
Reserved		dd ?
DXVA_COPPSetSignalingCmdData ENDS

.enum COPP_TVProtectionStandard {
    COPP_ProtectionStandard_Unknown			    = 0x80000000,
    COPP_ProtectionStandard_None			    = 0x00000000,
    COPP_ProtectionStandard_IEC61880_525i		    = 0x00000001,
    COPP_ProtectionStandard_IEC61880_2_525i		    = 0x00000002,
    COPP_ProtectionStandard_IEC62375_625p		    = 0x00000004,
    COPP_ProtectionStandard_EIA608B_525			    = 0x00000008,
    COPP_ProtectionStandard_EN300294_625i		    = 0x00000010,
    COPP_ProtectionStandard_CEA805A_TypeA_525p		    = 0x00000020,
    COPP_ProtectionStandard_CEA805A_TypeA_750p		    = 0x00000040,
    COPP_ProtectionStandard_CEA805A_TypeA_1125i		    = 0x00000080,
    COPP_ProtectionStandard_CEA805A_TypeB_525p		    = 0x00000100,
    COPP_ProtectionStandard_CEA805A_TypeB_750p		    = 0x00000200,
    COPP_ProtectionStandard_CEA805A_TypeB_1125i		    = 0x00000400,
    COPP_ProtectionStandard_ARIBTRB15_525i		    = 0x00000800,
    COPP_ProtectionStandard_ARIBTRB15_525p		    = 0x00001000,
    COPP_ProtectionStandard_ARIBTRB15_750p		    = 0x00002000,
    COPP_ProtectionStandard_ARIBTRB15_1125i		    = 0x00004000,
    COPP_ProtectionStandard_Mask			    = 0x80007FFF,
    COPP_ProtectionStandard_Reserved			    = 0x7FFF8000
    }

define COPP_ImageAspectRatio_EN300294_Mask		   0x00000007

.enum COPP_ImageAspectRatio_EN300294 {
    COPP_AspectRatio_EN300294_FullFormat4by3		    = 0,
    COPP_AspectRatio_EN300294_Box14by9Center		    = 1,
    COPP_AspectRatio_EN300294_Box14by9Top		    = 2,
    COPP_AspectRatio_EN300294_Box16by9Center		    = 3,
    COPP_AspectRatio_EN300294_Box16by9Top		    = 4,
    COPP_AspectRatio_EN300294_BoxGT16by9Center		    = 5,
    COPP_AspectRatio_EN300294_FullFormat4by3ProtectedCenter = 6,
    COPP_AspectRatio_EN300294_FullFormat16by9Anamorphic	    = 7,
    COPP_AspectRatio_ForceDWORD				    = 0x7fffffff
    }


DXVA_COPPStatusInput	STRUC
rApp			GUID <>
guidStatusRequestID	GUID <>
dwSequence		dd ?
cbSizeData		dd ?
StatusData		db 4056 dup(?)
DXVA_COPPStatusInput	ENDS
LPDXVA_COPPStatusInput	typedef ptr DXVA_COPPStatusInput

DXVA_COPPStatusOutput	STRUC
macKDI			GUID <>
cbSizeData		dd ?
COPPStatus		db 4076 dup(?)
DXVA_COPPStatusOutput	ENDS
LPDXVA_COPPStatusOutput typedef ptr DXVA_COPPStatusOutput

.enum COPP_StatusFlags {
    COPP_StatusNormal		= 0x00,
    COPP_LinkLost		= 0x01,
    COPP_RenegotiationRequired	= 0x02,
    COPP_StatusFlagsReserved	= 0xFFFFFFFC
    }

DXVA_COPPStatusData	STRUC
rApp			GUID <>
dwFlags			dd ?
dwData			dd ?
ExtendedInfoValidMask	dd ?
ExtendedInfoData	dd ?
DXVA_COPPStatusData	ENDS

DXVA_COPPStatusDisplayData STRUC
rApp			GUID <>
dwFlags			dd ?
DisplayWidth		dd ?
DisplayHeight		dd ?
Format			dd ?
d3dFormat		dd ?
FreqNumerator		dd ?
FreqDenominator		dd ?
DXVA_COPPStatusDisplayData ENDS

.enum COPP_StatusHDCPFlags {
    COPP_HDCPRepeater	    = 0x01,
    COPP_HDCPFlagsReserved  = 0xFFFFFFFE
    }

DXVA_COPPStatusHDCPKeyData STRUC
rApp			GUID <>
dwFlags			dd ?
dwHDCPFlags		dd ?
BKey			GUID <>
Reserved1		GUID <>
Reserved2		GUID <>
DXVA_COPPStatusHDCPKeyData ENDS


define DXVA_COPPQueryStatusFnCode 0x05


DEFINE_GUID(DXVA_COPPQueryConnectorType, 0x81d0bfd5,0x6afe,0x48c2,0x99,0xc0,0x95,0xa0,0x8f,0x97,0xc5,0xda)

.enum COPP_ConnectorType {
    COPP_ConnectorType_Unknown = -1,
    COPP_ConnectorType_VGA = 0,
    COPP_ConnectorType_SVideo = 1,
    COPP_ConnectorType_CompositeVideo = 2,
    COPP_ConnectorType_ComponentVideo = 3,
    COPP_ConnectorType_DVI = 4,
    COPP_ConnectorType_HDMI = 5,
    COPP_ConnectorType_LVDS = 6,
    COPP_ConnectorType_TMDS = 7,
    COPP_ConnectorType_D_JPN = 8,
    COPP_ConnectorType_SDI = 9,
    COPP_ConnectorType_DisplayPortExternal = 10,
    COPP_ConnectorType_DisplayPortEmbedded = 11,
    COPP_ConnectorType_UDIExternal = 12,
    COPP_ConnectorType_UDIEmbedded = 13,
    COPP_ConnectorType_Internal = 0x80000000,
    COPP_ConnectorType_ForceDWORD = 0x7fffffff
    }

DEFINE_GUID(DXVA_COPPQueryProtectionType, 0x38f2a801,0x9a6c,0x48bb,0x91,0x07,0xb6,0x69,0x6e,0x6f,0x17,0x97)
DEFINE_GUID(DXVA_COPPQueryLocalProtectionLevel, 0xb2075857,0x3eda,0x4d5d,0x88,0xdb,0x74,0x8f,0x8c,0x1a,0x05,0x49)
DEFINE_GUID(DXVA_COPPQueryGlobalProtectionLevel, 0x1957210a,0x7766,0x452a,0xb9,0x9a,0xd2,0x7a,0xed,0x54,0xf0,0x3a)
DEFINE_GUID(DXVA_COPPQueryDisplayData, 0xd7bf1ba3,0xad13,0x4f8e,0xaf,0x98,0x0d,0xcb,0x3c,0xa2,0x04,0xcc)
DEFINE_GUID(DXVA_COPPQueryHDCPKeyData, 0xdb59d74, 0xa992, 0x492e, 0xa0, 0xbd, 0xc2, 0x3f, 0xda, 0x56, 0x4e, 0x0)
DEFINE_GUID(DXVA_COPPQueryBusData, 0xc6f4d673, 0x6174, 0x4184, 0x8e, 0x35, 0xf6, 0xdb, 0x52, 0x0, 0xbc, 0xba)

.enum COPP_BusType {
    COPP_BusType_Unknown    = 0,
    COPP_BusType_PCI	    = 1,
    COPP_BusType_PCIX	    = 2,
    COPP_BusType_PCIExpress = 3,
    COPP_BusType_AGP	    = 4,
    COPP_BusType_Integrated = 0x80000000,
    COPP_BusType_ForceDWORD = 0x7fffffff
    }

DEFINE_GUID(DXVA_COPPQuerySignaling, 0x6629a591, 0x3b79, 0x4cf3, 0x92, 0x4a, 0x11, 0xe8, 0xe7, 0x81, 0x16, 0x71)

DXVA_COPPStatusSignalingCmdData STRUC
rApp			GUID <>
dwFlags			dd ?
AvailableTVProtectionStandards dd ?
ActiveTVProtectionStandard dd ?
TVType			dd ?
AspectRatioValidMask1	dd ?
AspectRatioData1	dd ?
AspectRatioValidMask2	dd ?
AspectRatioData2	dd ?
AspectRatioValidMask3	dd ?
AspectRatioData3	dd ?
ExtendedInfoValidMask	dd 4 dup(?)
ExtendedInfoData	dd 4 dup(?)
DXVA_COPPStatusSignalingCmdData ENDS


endif

ifdef __DXVA1_DEPRECATED_INTERFACES__

DEFINE_GUID(IID_IDirect3DVideoDevice9, 0x694036ac, 0x542a, 0x4a3a, 0x9a, 0x32, 0x53, 0xbc, 0x20, 0x0, 0x2c, 0x1b)
DEFINE_GUID(IID_IDirect3DDXVADevice9, 0x9f00c3d3, 0x5ab6, 0x465f, 0xb9, 0x55, 0x9f, 0xe, 0xbb, 0x2c, 0x56, 0x6)

DXVAUncompDataInfo	STRUC
UncompWidth		dd ?
UncompHeight		dd ?
UncompFormat		D3DFORMAT ?
DXVAUncompDataInfo	ENDS

DXVACompBufferInfo	STRUC
NumCompBuffers		dd ?
WidthToCreate		dd ?
HeightToCreate		dd ?
BytesToAllocate		dd ?
Usage			dd ?
Pool			D3DPOOL ?
Format			D3DFORMAT ?
DXVACompBufferInfo	ENDS

DXVABufferInfo		STRUC
pCompSurface		PVOID ?
DataOffset		dd ?
DataSize		dd ?
DXVABufferInfo		ENDS


.comdef IDirect3DVideoDevice9 : public IUnknown

    CreateSurface	proc :UINT, :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :DWORD, :ptr, :ptr
    GetDXVACompressedBufferInfo proc :ptr, :ptr, :ptr, :ptr
    GetDXVAGuids	proc :ptr, :ptr
    GetDXVAInternalInfo proc :ptr, :ptr, :ptr
    GetUncompressedDXVAFormats proc :ptr, :ptr, :ptr
    CreateDXVADevice	proc :ptr, :ptr, :LPVOID, :DWORD, :ptr
    .ends

.comdef IDirect3DDXVADevice9 : public IUnknown

    BeginFrame		proc :ptr, :DWORD, :ptr, :ptr, :ptr
    EndFrame		proc :DWORD, :ptr
    Execute		proc :DWORD, :ptr, :DWORD, :ptr, :DWORD, :DWORD, :ptr
    QueryStatus		proc :ptr, :DWORD
    .ends

endif

endif

endif

