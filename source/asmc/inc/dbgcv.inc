; DBGCV.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2021-04-29 - created from dbgcv.h
;
; Description:	MS codeview debug info header. Values and structures
;		in this header are derived from document:
;		"Microsoft Symbol and Type Information"
;		Format Specifications for Windows Version 1.0
;		Tool Interface Standards (TIS)
;
;		CV 5 format is described in
;		"Visual C++ 5.0 Symbolic Debug Information Specification";
;		the doc is available in MSDN libraries ( 199?-2001 ).
;
;		CV 8 is not "officially" described.
;		It's an extended CV5 format - 'names' are no longer
;		prefixed by a 1-byte length, instead they are terminated
;		by a x'00 (asciiz).
;		Additionally, the $$SYMBOLS segment has now sub-sections
;		for filenames, files, linenumbers and symbols.
;
; Update v2.32: The header file is rewritten from Microsoft's cvinfo.h
;
;		https://github.com/Microsoft/microsoft-pdb/
;
ifndef __CVDBG_INC
define __CVDBG_INC

.pragma pack(push, 1)

CV_uoff32_t		typedef DWORD
CV_off32_t		typedef SDWORD
CV_uoff16_t		typedef WORD
CV_off16_t		typedef SWORD
CV_typ16_t		typedef WORD
CV_typ_t		typedef DWORD
CV_pubsymflag_t		typedef DWORD
_2BYTEPAD		typedef WORD
CV_tkn_t		typedef DWORD

ifndef CV_ZEROLEN
define CV_ZEROLEN
endif

define CV_SIGNATURE_C6		0  ; Actual signature is GT 64K
define CV_SIGNATURE_C7		1  ; First explicit signature
define CV_SIGNATURE_C11		2  ; C11 (vc5.x) 32-bit types
define CV_SIGNATURE_C13		4  ; C13 (vc7.x) zero terminated names
define CV_SIGNATURE_RESERVED	5  ; All signatures from 5 to 64K are reserved

define CV_MAXOFFSET   0xffffffff

ifndef GUID_DEFINED
define GUID_DEFINED
GUID			STRUC
Data1			dd ?
Data2			dw ?
Data3			dw ?
Data4			db 8 dup(?)
GUID			ENDS
endif

SIG70			typedef GUID
PSIG70			typedef ptr SIG70
PCSIG70			typedef ptr SIG70

;
; CodeView Symbol and Type OMF type information is broken up into two
; ranges.  Type indices less than 0x1000 describe type information
; that is frequently used.  Type indices above 0x1000 are used to
; describe more complex features such as functions, arrays and
; structures.
;

;
;  Primitive types have predefined meaning that is encoded in the
;  values of the various bit fields in the value.
;
; A CodeView primitive type is defined as:
;
;	1 1
;	1 089  7654  3	210
;	r mode type  r	sub
;
;	Where
;	    mode is the pointer mode
;	    type is a type indicator
;	    sub	 is a subtype enumeration
;	    r	 is a reserved field
;
; See Microsoft Symbol and Type OMF (Version 4.0) for more
; information.
;

define CV_MMASK		0x700 ; mode mask
define CV_TMASK		0x0f0 ; type mask
define CV_SMASK		0x00f ; subtype mask

define CV_MSHIFT	8     ; primitive mode right shift count
define CV_TSHIFT	4     ; primitive type right shift count
define CV_SSHIFT	0     ; primitive subtype right shift count

CV_PRIMITIVE		typedef WORD

CV_MODE proto watcall type:CV_PRIMITIVE {
	and eax,CV_MMASK
	shr eax,CV_MSHIFT
	}
CV_TYPE proto watcall type:CV_PRIMITIVE {
	and eax,CV_TMASK
	shr eax,CV_TSHIFT
	}
CV_SUBT proto watcall type:CV_PRIMITIVE {
	and eax,CV_SMASK
	}

CV_NEWMODE proto watcall type:CV_PRIMITIVE, nm:CV_PRIMITIVE {
	and eax,NOT CV_MMASK
	shl edx,CV_MSHIFT
	or  ax,dx
	}
CV_NEWTYPE proto watcall type:CV_PRIMITIVE, nt:CV_PRIMITIVE {
	and eax,not CV_TMASK
	shl edx,CV_TSHIFT
	or  ax,dx
	}
CV_NEWSUBT proto watcall type:CV_PRIMITIVE, ns:CV_PRIMITIVE {
	and eax,not CV_SMASK
	shl edx,CV_SSHIFT
	or  ax,dx
	}


.enum CV_prmode_e {
    CV_TM_DIRECT    = 0,
    CV_TM_NPTR	    = 1,
    CV_TM_FPTR	    = 2,
    CV_TM_HPTR	    = 3,
    CV_TM_NPTR32    = 4,
    CV_TM_FPTR32    = 5,
    CV_TM_NPTR64    = 6,
    CV_TM_NPTR128   = 7,
    }

.enum CV_type_e {
    CV_SPECIAL	    = 0x00,
    CV_SIGNED	    = 0x01,
    CV_UNSIGNED	    = 0x02,
    CV_BOOLEAN	    = 0x03,
    CV_REAL	    = 0x04,
    CV_COMPLEX	    = 0x05,
    CV_SPECIAL2	    = 0x06,
    CV_INT	    = 0x07,
    CV_CVRESERVED   = 0x0f,
    }

.enum CV_special_e {
    CV_SP_NOTYPE    = 0x00,
    CV_SP_ABS	    = 0x01,
    CV_SP_SEGMENT   = 0x02,
    CV_SP_VOID	    = 0x03,
    CV_SP_CURRENCY  = 0x04,
    CV_SP_NBASICSTR = 0x05,
    CV_SP_FBASICSTR = 0x06,
    CV_SP_NOTTRANS  = 0x07,
    CV_SP_HRESULT   = 0x08,
    }

.enum CV_special2_e {
    CV_S2_BIT	    = 0x00,
    CV_S2_PASCHAR   = 0x01,
    CV_S2_BOOL32FF  = 0x02,
    }

.enum CV_integral_e {
    CV_IN_1BYTE	    = 0x00,
    CV_IN_2BYTE	    = 0x01,
    CV_IN_4BYTE	    = 0x02,
    CV_IN_8BYTE	    = 0x03,
    CV_IN_16BYTE    = 0x04
    }

.enum CV_real_e {
    CV_RC_REAL32    = 0x00,
    CV_RC_REAL64    = 0x01,
    CV_RC_REAL80    = 0x02,
    CV_RC_REAL128   = 0x03,
    CV_RC_REAL48    = 0x04,
    CV_RC_REAL32PP  = 0x05,
    CV_RC_REAL16    = 0x06,
    }

.enum CV_int_e {
    CV_RI_CHAR	    = 0x00,
    CV_RI_INT1	    = 0x00,
    CV_RI_WCHAR	    = 0x01,
    CV_RI_UINT1	    = 0x01,
    CV_RI_INT2	    = 0x02,
    CV_RI_UINT2	    = 0x03,
    CV_RI_INT4	    = 0x04,
    CV_RI_UINT4	    = 0x05,
    CV_RI_INT8	    = 0x06,
    CV_RI_UINT8	    = 0x07,
    CV_RI_INT16	    = 0x08,
    CV_RI_UINT16    = 0x09,
    CV_RI_CHAR16    = 0x0a,
    CV_RI_CHAR32    = 0x0b,
    }

CV_TYP_IS_DIRECT macro typ
	exitm<(CV_MODE(typ) == CV_TM_DIRECT)>
	endm
CV_TYP_IS_PTR macro typ
	exitm<(CV_MODE(typ) !!= CV_TM_DIRECT)>
	endm
CV_TYP_IS_NPTR macro typ
	exitm<(CV_MODE(typ) == CV_TM_NPTR)>
	endm
CV_TYP_IS_FPTR macro typ
	exitm<(CV_MODE(typ) == CV_TM_FPTR)>
	endm
CV_TYP_IS_HPTR macro typ
	exitm<(CV_MODE(typ) == CV_TM_HPTR)>
	endm
CV_TYP_IS_NPTR32 macro typ
	exitm<(CV_MODE(typ) == CV_TM_NPTR32)>
	endm
CV_TYP_IS_FPTR32 macro typ
	exitm<(CV_MODE(typ) == CV_TM_FPTR32)>
	endm

CV_TYP_IS_SIGNED proto watcall type:CV_PRIMITIVE {
	mov ecx,eax
	mov edx,eax
	and ecx,CV_MMASK
	shr ecx,CV_MSHIFT
	and edx,CV_TMASK
	shr edx,CV_TSHIFT
	.if (((edx == CV_SIGNED) && (ecx == CV_TM_DIRECT)) || \
	    (eax == T_INT1)	|| \
	    (eax == T_INT2)	|| \
	    (eax == T_INT4)	|| \
	    (eax == T_INT8)	|| \
	    (eax == T_INT16)	|| \
	    (eax == T_RCHAR))
	    mov eax,1
	.else
	    xor eax,eax
	.endif
	}

CV_TYP_IS_UNSIGNED proto watcall type:CV_PRIMITIVE {
	mov ecx,eax
	mov edx,eax
	and ecx,CV_MMASK
	shr ecx,CV_MSHIFT
	and edx,CV_TMASK
	shr edx,CV_TSHIFT
	.if (((edx == CV_UNSIGNED) && (ecx == CV_TM_DIRECT)) || \
	    (eax == T_UINT1)	|| \
	    (eax == T_UINT2)	|| \
	    (eax == T_UINT4)	|| \
	    (eax == T_UINT8)	|| \
	    (eax == T_UINT16))
	    mov eax,1
	.else
	    xor eax,eax
	.endif
	}

CV_TYP_IS_REAL proto watcall type:CV_PRIMITIVE {
	mov ecx,eax
	and ecx,CV_MMASK
	shr ecx,CV_MSHIFT
	and eax,CV_TMASK
	shr eax,CV_TSHIFT
	.if ((eax == CV_REAL) && (ecx == CV_TM_DIRECT))
	    mov eax,1
	.else
	    xor eax,eax
	.endif
	}

define CV_FIRST_NONPRIM 0x1000

CV_IS_PRIMITIVE macro typ
	exitm<((typ) !< CV_FIRST_NONPRIM)>
	endm

CV_TYP_IS_COMPLEX proto watcall type:CV_PRIMITIVE {
	mov ecx,eax
	and ecx,CV_MMASK
	shr ecx,CV_MSHIFT
	and eax,CV_TMASK
	shr eax,CV_TSHIFT
	.if ((eax == CV_COMPLEX) && (ecx == CV_TM_DIRECT))
	    mov eax,1
	.else
	    xor eax,eax
	.endif
	}

CV_IS_INTERNAL_PTR proto watcall type:CV_PRIMITIVE {
	mov ecx,eax
	and eax,CV_TMASK
	shr eax,CV_TSHIFT
	.if ((eax == CV_CVRESERVED) && (ecx < CV_FIRST_NONPRIM))
	    mov eax,1
	.else
	    xor eax,eax
	.endif
	}

; Special Types

.enum TYPE_ENUM_e {

    ST_NOTYPE		= 0x0000,
    ST_ABS		= 0x0001,
    ST_SEGMENT		= 0x0002,
    ST_VOID		= 0x0003,
    ST_HRESULT		= 0x0008,
    ST_32PHRESULT	= 0x0408,
    ST_64PHRESULT	= 0x0608,

    ST_PVOID		= 0x0103,
    ST_PFVOID		= 0x0203,
    ST_PHVOID		= 0x0303,
    ST_32PVOID		= 0x0403,
    ST_32PFVOID		= 0x0503,
    ST_64PVOID		= 0x0603,
    ST_CURRENCY		= 0x0004,
    ST_NBASICSTR	= 0x0005,
    ST_FBASICSTR	= 0x0006,
    ST_NOTTRANS		= 0x0007,
    ST_BIT		= 0x0060,
    ST_PASCHAR		= 0x0061,
    ST_BOOL32FF		= 0x0062,

    ST_CHAR		= 0x0010,
    ST_PCHAR		= 0x0110,
    ST_PFCHAR		= 0x0210,
    ST_PHCHAR		= 0x0310,
    ST_32PCHAR		= 0x0410,
    ST_32PFCHAR		= 0x0510,
    ST_64PCHAR		= 0x0610,

    ST_UCHAR		= 0x0020,
    ST_PUCHAR		= 0x0120,
    ST_PFUCHAR		= 0x0220,
    ST_PHUCHAR		= 0x0320,
    ST_32PUCHAR		= 0x0420,
    ST_32PFUCHAR	= 0x0520,
    ST_64PUCHAR		= 0x0620,

    ST_RCHAR		= 0x0070,
    ST_PRCHAR		= 0x0170,
    ST_PFRCHAR		= 0x0270,
    ST_PHRCHAR		= 0x0370,
    ST_32PRCHAR		= 0x0470,
    ST_32PFRCHAR	= 0x0570,
    ST_64PRCHAR		= 0x0670,

    ST_WCHAR		= 0x0071,
    ST_PWCHAR		= 0x0171,
    ST_PFWCHAR		= 0x0271,
    ST_PHWCHAR		= 0x0371,
    ST_32PWCHAR		= 0x0471,
    ST_32PFWCHAR	= 0x0571,
    ST_64PWCHAR		= 0x0671,

    ST_CHAR16		= 0x007a,
    ST_PCHAR16		= 0x017a,
    ST_PFCHAR16		= 0x027a,
    ST_PHCHAR16		= 0x037a,
    ST_32PCHAR16	= 0x047a,
    ST_32PFCHAR16	= 0x057a,
    ST_64PCHAR16	= 0x067a,

    ST_CHAR32		= 0x007b,
    ST_PCHAR32		= 0x017b,
    ST_PFCHAR32		= 0x027b,
    ST_PHCHAR32		= 0x037b,
    ST_32PCHAR32	= 0x047b,
    ST_32PFCHAR32	= 0x057b,
    ST_64PCHAR32	= 0x067b,

    ST_INT1		= 0x0068,
    ST_PINT1		= 0x0168,
    ST_PFINT1		= 0x0268,
    ST_PHINT1		= 0x0368,
    ST_32PINT1		= 0x0468,
    ST_32PFINT1		= 0x0568,
    ST_64PINT1		= 0x0668,

    ST_UINT1		= 0x0069,
    ST_PUINT1		= 0x0169,
    ST_PFUINT1		= 0x0269,
    ST_PHUINT1		= 0x0369,
    ST_32PUINT1		= 0x0469,
    ST_32PFUINT1	= 0x0569,
    ST_64PUINT1		= 0x0669,

    ST_SHORT		= 0x0011,
    ST_PSHORT		= 0x0111,
    ST_PFSHORT		= 0x0211,
    ST_PHSHORT		= 0x0311,
    ST_32PSHORT		= 0x0411,
    ST_32PFSHORT	= 0x0511,
    ST_64PSHORT		= 0x0611,

    ST_USHORT		= 0x0021,
    ST_PUSHORT		= 0x0121,
    ST_PFUSHORT		= 0x0221,
    ST_PHUSHORT		= 0x0321,
    ST_32PUSHORT	= 0x0421,
    ST_32PFUSHORT	= 0x0521,
    ST_64PUSHORT	= 0x0621,

    ST_INT2		= 0x0072,
    ST_PINT2		= 0x0172,
    ST_PFINT2		= 0x0272,
    ST_PHINT2		= 0x0372,
    ST_32PINT2		= 0x0472,
    ST_32PFINT2		= 0x0572,
    ST_64PINT2		= 0x0672,

    ST_UINT2		= 0x0073,
    ST_PUINT2		= 0x0173,
    ST_PFUINT2		= 0x0273,
    ST_PHUINT2		= 0x0373,
    ST_32PUINT2		= 0x0473,
    ST_32PFUINT2	= 0x0573,
    ST_64PUINT2		= 0x0673,

    ST_LONG		= 0x0012,
    ST_ULONG		= 0x0022,
    ST_PLONG		= 0x0112,
    ST_PULONG		= 0x0122,
    ST_PFLONG		= 0x0212,
    ST_PFULONG		= 0x0222,
    ST_PHLONG		= 0x0312,
    ST_PHULONG		= 0x0322,

    ST_32PLONG		= 0x0412,
    ST_32PULONG		= 0x0422,
    ST_32PFLONG		= 0x0512,
    ST_32PFULONG	= 0x0522,
    ST_64PLONG		= 0x0612,
    ST_64PULONG		= 0x0622,

    ST_INT4		= 0x0074,
    ST_PINT4		= 0x0174,
    ST_PFINT4		= 0x0274,
    ST_PHINT4		= 0x0374,
    ST_32PINT4		= 0x0474,
    ST_32PFINT4		= 0x0574,
    ST_64PINT4		= 0x0674,

    ST_UINT4		= 0x0075,
    ST_PUINT4		= 0x0175,
    ST_PFUINT4		= 0x0275,
    ST_PHUINT4		= 0x0375,
    ST_32PUINT4		= 0x0475,
    ST_32PFUINT4	= 0x0575,
    ST_64PUINT4		= 0x0675,

    ST_QUAD		= 0x0013,
    ST_PQUAD		= 0x0113,
    ST_PFQUAD		= 0x0213,
    ST_PHQUAD		= 0x0313,
    ST_32PQUAD		= 0x0413,
    ST_32PFQUAD		= 0x0513,
    ST_64PQUAD		= 0x0613,

    ST_UQUAD		= 0x0023,
    ST_PUQUAD		= 0x0123,
    ST_PFUQUAD		= 0x0223,
    ST_PHUQUAD		= 0x0323,
    ST_32PUQUAD		= 0x0423,
    ST_32PFUQUAD	= 0x0523,
    ST_64PUQUAD		= 0x0623,

    ST_INT8		= 0x0076,
    ST_PINT8		= 0x0176,
    ST_PFINT8		= 0x0276,
    ST_PHINT8		= 0x0376,
    ST_32PINT8		= 0x0476,
    ST_32PFINT8		= 0x0576,
    ST_64PINT8		= 0x0676,

    ST_UINT8		= 0x0077,
    ST_PUINT8		= 0x0177,
    ST_PFUINT8		= 0x0277,
    ST_PHUINT8		= 0x0377,
    ST_32PUINT8		= 0x0477,
    ST_32PFUINT8	= 0x0577,
    ST_64PUINT8		= 0x0677,

    ST_OCT		= 0x0014,
    ST_POCT		= 0x0114,
    ST_PFOCT		= 0x0214,
    ST_PHOCT		= 0x0314,
    ST_32POCT		= 0x0414,
    ST_32PFOCT		= 0x0514,
    ST_64POCT		= 0x0614,

    ST_UOCT		= 0x0024,
    ST_PUOCT		= 0x0124,
    ST_PFUOCT		= 0x0224,
    ST_PHUOCT		= 0x0324,
    ST_32PUOCT		= 0x0424,
    ST_32PFUOCT		= 0x0524,
    ST_64PUOCT		= 0x0624,

    ST_INT16		= 0x0078,
    ST_PINT16		= 0x0178,
    ST_PFINT16		= 0x0278,
    ST_PHINT16		= 0x0378,
    ST_32PINT16		= 0x0478,
    ST_32PFINT16	= 0x0578,
    ST_64PINT16		= 0x0678,

    ST_UINT16		= 0x0079,
    ST_PUINT16		= 0x0179,
    ST_PFUINT16		= 0x0279,
    ST_PHUINT16		= 0x0379,
    ST_32PUINT16	= 0x0479,
    ST_32PFUINT16	= 0x0579,
    ST_64PUINT16	= 0x0679,

    ST_REAL16		= 0x0046,
    ST_PREAL16		= 0x0146,
    ST_PFREAL16		= 0x0246,
    ST_PHREAL16		= 0x0346,
    ST_32PREAL16	= 0x0446,
    ST_32PFREAL16	= 0x0546,
    ST_64PREAL16	= 0x0646,

    ST_REAL32		= 0x0040,
    ST_PREAL32		= 0x0140,
    ST_PFREAL32		= 0x0240,
    ST_PHREAL32		= 0x0340,
    ST_32PREAL32	= 0x0440,
    ST_32PFREAL32	= 0x0540,
    ST_64PREAL32	= 0x0640,

    ST_REAL32PP		= 0x0045,
    ST_PREAL32PP	= 0x0145,
    ST_PFREAL32PP	= 0x0245,
    ST_PHREAL32PP	= 0x0345,
    ST_32PREAL32PP	= 0x0445,
    ST_32PFREAL32PP	= 0x0545,
    ST_64PREAL32PP	= 0x0645,

    ST_REAL48		= 0x0044,
    ST_PREAL48		= 0x0144,
    ST_PFREAL48		= 0x0244,
    ST_PHREAL48		= 0x0344,
    ST_32PREAL48	= 0x0444,
    ST_32PFREAL48	= 0x0544,
    ST_64PREAL48	= 0x0644,

    ST_REAL64		= 0x0041,
    ST_PREAL64		= 0x0141,
    ST_PFREAL64		= 0x0241,
    ST_PHREAL64		= 0x0341,
    ST_32PREAL64	= 0x0441,
    ST_32PFREAL64	= 0x0541,
    ST_64PREAL64	= 0x0641,

    ST_REAL80		= 0x0042,
    ST_PREAL80		= 0x0142,
    ST_PFREAL80		= 0x0242,
    ST_PHREAL80		= 0x0342,
    ST_32PREAL80	= 0x0442,
    ST_32PFREAL80	= 0x0542,
    ST_64PREAL80	= 0x0642,

    ST_REAL128		= 0x0043,
    ST_PREAL128		= 0x0143,
    ST_PFREAL128	= 0x0243,
    ST_PHREAL128	= 0x0343,
    ST_32PREAL128	= 0x0443,
    ST_32PFREAL128	= 0x0543,
    ST_64PREAL128	= 0x0643,

    ST_CPLX32		= 0x0050,
    ST_PCPLX32		= 0x0150,
    ST_PFCPLX32		= 0x0250,
    ST_PHCPLX32		= 0x0350,
    ST_32PCPLX32	= 0x0450,
    ST_32PFCPLX32	= 0x0550,
    ST_64PCPLX32	= 0x0650,

    ST_CPLX64		= 0x0051,
    ST_PCPLX64		= 0x0151,
    ST_PFCPLX64		= 0x0251,
    ST_PHCPLX64		= 0x0351,
    ST_32PCPLX64	= 0x0451,
    ST_32PFCPLX64	= 0x0551,
    ST_64PCPLX64	= 0x0651,

    ST_CPLX80		= 0x0052,
    ST_PCPLX80		= 0x0152,
    ST_PFCPLX80		= 0x0252,
    ST_PHCPLX80		= 0x0352,
    ST_32PCPLX80	= 0x0452,
    ST_32PFCPLX80	= 0x0552,
    ST_64PCPLX80	= 0x0652,

    ST_CPLX128		= 0x0053,
    ST_PCPLX128		= 0x0153,
    ST_PFCPLX128	= 0x0253,
    ST_PHCPLX128	= 0x0353,
    ST_32PCPLX128	= 0x0453,
    ST_32PFCPLX128	= 0x0553,
    ST_64PCPLX128	= 0x0653,

    ST_BOOL08		= 0x0030,
    ST_PBOOL08		= 0x0130,
    ST_PFBOOL08		= 0x0230,
    ST_PHBOOL08		= 0x0330,
    ST_32PBOOL08	= 0x0430,
    ST_32PFBOOL08	= 0x0530,
    ST_64PBOOL08	= 0x0630,

    ST_BOOL16		= 0x0031,
    ST_PBOOL16		= 0x0131,
    ST_PFBOOL16		= 0x0231,
    ST_PHBOOL16		= 0x0331,
    ST_32PBOOL16	= 0x0431,
    ST_32PFBOOL16	= 0x0531,
    ST_64PBOOL16	= 0x0631,

    ST_BOOL32		= 0x0032,
    ST_PBOOL32		= 0x0132,
    ST_PFBOOL32		= 0x0232,
    ST_PHBOOL32		= 0x0332,
    ST_32PBOOL32	= 0x0432,
    ST_32PFBOOL32	= 0x0532,
    ST_64PBOOL32	= 0x0632,

    ST_BOOL64		= 0x0033,
    ST_PBOOL64		= 0x0133,
    ST_PFBOOL64		= 0x0233,
    ST_PHBOOL64		= 0x0333,
    ST_32PBOOL64	= 0x0433,
    ST_32PFBOOL64	= 0x0533,
    ST_64PBOOL64	= 0x0633,

    ST_NCVPTR		= 0x01f0,
    ST_FCVPTR		= 0x02f0,
    ST_HCVPTR		= 0x03f0,
    ST_32NCVPTR		= 0x04f0,
    ST_32FCVPTR		= 0x05f0,
    ST_64NCVPTR		= 0x06f0,
    }


.enum LEAF_ENUM_e {

    ; leaf indices starting records but referenced from symbol records

    LF_MODIFIER_16t	= 0x0001,
    LF_POINTER_16t	= 0x0002,
    LF_ARRAY_16t	= 0x0003,
    LF_CLASS_16t	= 0x0004,
    LF_STRUCTURE_16t	= 0x0005,
    LF_UNION_16t	= 0x0006,
    LF_ENUM_16t		= 0x0007,
    LF_PROCEDURE_16t	= 0x0008,
    LF_MFUNCTION_16t	= 0x0009,
    LF_VTSHAPE		= 0x000a,
    LF_COBOL0_16t	= 0x000b,
    LF_COBOL1		= 0x000c,
    LF_BARRAY_16t	= 0x000d,
    LF_LABEL		= 0x000e,
    LF_NULL		= 0x000f,
    LF_NOTTRAN		= 0x0010,
    LF_DIMARRAY_16t	= 0x0011,
    LF_VFTPATH_16t	= 0x0012,
    LF_PRECOMP_16t	= 0x0013,
    LF_ENDPRECOMP	= 0x0014,
    LF_OEM_16t		= 0x0015,
    LF_TYPESERVER_ST	= 0x0016,

    ; leaf indices starting records but referenced only from type records

    LF_SKIP_16t		= 0x0200,
    LF_ARGLIST_16t	= 0x0201,
    LF_DEFARG_16t	= 0x0202,
    LF_LIST		= 0x0203,
    LF_FIELDLIST_16t	= 0x0204,
    LF_DERIVED_16t	= 0x0205,
    LF_BITFIELD_16t	= 0x0206,
    LF_METHODLIST_16t	= 0x0207,
    LF_DIMCONU_16t	= 0x0208,
    LF_DIMCONLU_16t	= 0x0209,
    LF_DIMVARU_16t	= 0x020a,
    LF_DIMVARLU_16t	= 0x020b,
    LF_REFSYM		= 0x020c,

    LF_BCLASS_16t	= 0x0400,
    LF_VBCLASS_16t	= 0x0401,
    LF_IVBCLASS_16t	= 0x0402,
    LF_ENUMERATE_ST	= 0x0403,
    LF_FRIENDFCN_16t	= 0x0404,
    LF_INDEX_16t	= 0x0405,
    LF_MEMBER_16t	= 0x0406,
    LF_STMEMBER_16t	= 0x0407,
    LF_METHOD_16t	= 0x0408,
    LF_NESTTYPE_16t	= 0x0409,
    LF_VFUNCTAB_16t	= 0x040a,
    LF_FRIENDCLS_16t	= 0x040b,
    LF_ONEMETHOD_16t	= 0x040c,
    LF_VFUNCOFF_16t	= 0x040d,

; 32-bit type index versions of leaves, all have the 0x1000 bit set

    LF_TI16_MAX		= 0x1000,
    LF_MODIFIER		= 0x1001,
    LF_POINTER		= 0x1002,
    LF_ARRAY_ST		= 0x1003,
    LF_CLASS_ST		= 0x1004,
    LF_STRUCTURE_ST	= 0x1005,
    LF_UNION_ST		= 0x1006,
    LF_ENUM_ST		= 0x1007,
    LF_PROCEDURE	= 0x1008,
    LF_MFUNCTION	= 0x1009,
    LF_COBOL0		= 0x100a,
    LF_BARRAY		= 0x100b,
    LF_DIMARRAY_ST	= 0x100c,
    LF_VFTPATH		= 0x100d,
    LF_PRECOMP_ST	= 0x100e,
    LF_OEM		= 0x100f,
    LF_ALIAS_ST		= 0x1010,
    LF_OEM2		= 0x1011,

    ; leaf indices starting records but referenced only from type records

    LF_SKIP		= 0x1200,
    LF_ARGLIST		= 0x1201,
    LF_DEFARG_ST	= 0x1202,
    LF_FIELDLIST	= 0x1203,
    LF_DERIVED		= 0x1204,
    LF_BITFIELD		= 0x1205,
    LF_METHODLIST	= 0x1206,
    LF_DIMCONU		= 0x1207,
    LF_DIMCONLU		= 0x1208,
    LF_DIMVARU		= 0x1209,
    LF_DIMVARLU		= 0x120a,

    LF_BCLASS		= 0x1400,
    LF_VBCLASS		= 0x1401,
    LF_IVBCLASS		= 0x1402,
    LF_FRIENDFCN_ST	= 0x1403,
    LF_INDEX		= 0x1404,
    LF_MEMBER_ST	= 0x1405,
    LF_STMEMBER_ST	= 0x1406,
    LF_METHOD_ST	= 0x1407,
    LF_NESTTYPE_ST	= 0x1408,
    LF_VFUNCTAB		= 0x1409,
    LF_FRIENDCLS	= 0x140a,
    LF_ONEMETHOD_ST	= 0x140b,
    LF_VFUNCOFF		= 0x140c,
    LF_NESTTYPEEX_ST	= 0x140d,
    LF_MEMBERMODIFY_ST	= 0x140e,
    LF_MANAGED_ST	= 0x140f,

    ; Types w/ SZ names

    LF_ST_MAX		= 0x1500,

    LF_TYPESERVER	= 0x1501,
    LF_ENUMERATE	= 0x1502,
    LF_ARRAY		= 0x1503,
    LF_CLASS		= 0x1504,
    LF_STRUCTURE	= 0x1505,
    LF_UNION		= 0x1506,
    LF_ENUM		= 0x1507,
    LF_DIMARRAY		= 0x1508,
    LF_PRECOMP		= 0x1509,
    LF_ALIAS		= 0x150a,
    LF_DEFARG		= 0x150b,
    LF_FRIENDFCN	= 0x150c,
    LF_MEMBER		= 0x150d,
    LF_STMEMBER		= 0x150e,
    LF_METHOD		= 0x150f,
    LF_NESTTYPE		= 0x1510,
    LF_ONEMETHOD	= 0x1511,
    LF_NESTTYPEEX	= 0x1512,
    LF_MEMBERMODIFY	= 0x1513,
    LF_MANAGED		= 0x1514,
    LF_TYPESERVER2	= 0x1515,

    LF_STRIDED_ARRAY	= 0x1516,
    LF_HLSL		= 0x1517,
    LF_MODIFIER_EX	= 0x1518,
    LF_INTERFACE	= 0x1519,
    LF_BINTERFACE	= 0x151a,
    LF_VECTOR		= 0x151b,
    LF_MATRIX		= 0x151c,

    LF_VFTABLE		= 0x151d,
    LF_ENDOFLEAFRECORD	= LF_VFTABLE,

    LF_TYPE_LAST,	; one greater than the last type record
    LF_TYPE_MAX		= LF_TYPE_LAST - 1,

    LF_FUNC_ID		= 0x1601,
    LF_MFUNC_ID		= 0x1602,
    LF_BUILDINFO	= 0x1603,
    LF_SUBSTR_LIST	= 0x1604,
    LF_STRING_ID	= 0x1605,

    LF_UDT_SRC_LINE	= 0x1606,
    LF_UDT_MOD_SRC_LINE = 0x1607,

    LF_ID_LAST,
    LF_ID_MAX		= LF_ID_LAST - 1,

    LF_NUMERIC		= 0x8000,
    LF_CHAR		= 0x8000,
    LF_SHORT		= 0x8001,
    LF_USHORT		= 0x8002,
    LF_LONG		= 0x8003,
    LF_ULONG		= 0x8004,
    LF_REAL32		= 0x8005,
    LF_REAL64		= 0x8006,
    LF_REAL80		= 0x8007,
    LF_REAL128		= 0x8008,
    LF_QUADWORD		= 0x8009,
    LF_UQUADWORD	= 0x800a,
    LF_REAL48		= 0x800b,
    LF_COMPLEX32	= 0x800c,
    LF_COMPLEX64	= 0x800d,
    LF_COMPLEX80	= 0x800e,
    LF_COMPLEX128	= 0x800f,
    LF_VARSTRING	= 0x8010,

    LF_OCTWORD		= 0x8017,
    LF_UOCTWORD		= 0x8018,

    LF_DECIMAL		= 0x8019,
    LF_DATE		= 0x801a,
    LF_UTF8STRING	= 0x801b,

    LF_REAL16		= 0x801c,

    LF_PAD0		= 0xf0,
    LF_PAD1		= 0xf1,
    LF_PAD2		= 0xf2,
    LF_PAD3		= 0xf3,
    LF_PAD4		= 0xf4,
    LF_PAD5		= 0xf5,
    LF_PAD6		= 0xf6,
    LF_PAD7		= 0xf7,
    LF_PAD8		= 0xf8,
    LF_PAD9		= 0xf9,
    LF_PAD10		= 0xfa,
    LF_PAD11		= 0xfb,
    LF_PAD12		= 0xfc,
    LF_PAD13		= 0xfd,
    LF_PAD14		= 0xfe,
    LF_PAD15		= 0xff,
    }


; Type enum for pointer records
; Pointers can be one of the following types

.enum CV_ptrtype_e {
    CV_PTR_NEAR		= 0x00,
    CV_PTR_FAR		= 0x01,
    CV_PTR_HUGE		= 0x02,
    CV_PTR_BASE_SEG	= 0x03,
    CV_PTR_BASE_VAL	= 0x04,
    CV_PTR_BASE_SEGVAL	= 0x05,
    CV_PTR_BASE_ADDR	= 0x06,
    CV_PTR_BASE_SEGADDR = 0x07,
    CV_PTR_BASE_TYPE	= 0x08,
    CV_PTR_BASE_SELF	= 0x09,
    CV_PTR_NEAR32	= 0x0a,
    CV_PTR_FAR32	= 0x0b,
    CV_PTR_64		= 0x0c,
    CV_PTR_UNUSEDPTR	= 0x0d
    }


;
; Mode enum for pointers
; Pointers can have one of the following modes
;
;  To support for l-value and r-value reference, we added CV_PTR_MODE_LVREF
;  and CV_PTR_MODE_RVREF.  CV_PTR_MODE_REF should be removed at some point.
;  We keep it now so that old code that uses it won't be broken.
;

.enum CV_ptrmode_e {
    CV_PTR_MODE_PTR	= 0x00,
    CV_PTR_MODE_REF	= 0x01,
    CV_PTR_MODE_LVREF	= 0x01,
    CV_PTR_MODE_PMEM	= 0x02,
    CV_PTR_MODE_PMFUNC	= 0x03,
    CV_PTR_MODE_RVREF	= 0x04,
    CV_PTR_MODE_RESERVED= 0x05
    }


; enumeration for pointer-to-member types

.enum CV_pmtype_e {
    CV_PMTYPE_Undef	= 0x00,
    CV_PMTYPE_D_Single	= 0x01,
    CV_PMTYPE_D_Multiple= 0x02,
    CV_PMTYPE_D_Virtual = 0x03,
    CV_PMTYPE_D_General = 0x04,
    CV_PMTYPE_F_Single	= 0x05,
    CV_PMTYPE_F_Multiple= 0x06,
    CV_PMTYPE_F_Virtual = 0x07,
    CV_PMTYPE_F_General = 0x08,
    }


; enumeration for method properties

.enum CV_methodprop_e {
    CV_MTvanilla	= 0x00,
    CV_MTvirtual	= 0x01,
    CV_MTstatic		= 0x02,
    CV_MTfriend		= 0x03,
    CV_MTintro		= 0x04,
    CV_MTpurevirt	= 0x05,
    CV_MTpureintro	= 0x06
    }


; enumeration for virtual shape table entries

.enum CV_VTS_desc_e {
    CV_VTS_near		= 0x00,
    CV_VTS_far		= 0x01,
    CV_VTS_thin		= 0x02,
    CV_VTS_outer	= 0x03,
    CV_VTS_meta		= 0x04,
    CV_VTS_near32	= 0x05,
    CV_VTS_far32	= 0x06,
    CV_VTS_unused	= 0x07
    }


; enumeration for LF_LABEL address modes

.enum CV_LABEL_TYPE_e {
    CV_LABEL_NEAR	= 0,
    CV_LABEL_FAR	= 4
    }


; enumeration for LF_MODIFIER values

.enum CV_modifier_t : WORD {
    MOD_const		= 0x0001,
    MOD_volatile	= 0x0002,
    MOD_unaligned	= 0x0004,
    }


; enumeration for HFA kinds

.enum CV_HFA_e {
    CV_HFA_none		= 0,
    CV_HFA_float	= 1,
    CV_HFA_double	= 2,
    CV_HFA_other	= 3
    }


;  enumeration for MoCOM UDT kinds

.enum CV_MOCOM_UDT_e {
    CV_MOCOM_UDT_none	   = 0,
    CV_MOCOM_UDT_ref	   = 1,
    CV_MOCOM_UDT_value	   = 2,
    CV_MOCOM_UDT_interface = 3
    }


; bit field structure describing class/struct/union/enum properties

.enum CV_prop_t : WORD {
    CV_prop_packed	  = 0x0001 ; true if structure is packed
    CV_prop_ctor	  = 0x0002 ; true if constructors or destructors present
    CV_prop_ovlops	  = 0x0004 ; true if overloaded operators present
    CV_prop_isnested	  = 0x0008 ; true if this is a nested class
    CV_prop_cnested	  = 0x0010 ; true if this class contains nested types
    CV_prop_opassign	  = 0x0020 ; true if overloaded assignment (=)
    CV_prop_opcast	  = 0x0040 ; true if casting methods
    CV_prop_fwdref	  = 0x0080 ; true if forward reference (incomplete defn)
    CV_prop_scoped	  = 0x0100 ; scoped definition
    CV_prop_hasuniquename = 0x0200 ; true if there is a decorated name following the regular name
    CV_prop_sealed	  = 0x0400 ; true if class cannot be used as a base class
    CV_prop_hfa		  = 0x1800 ; CV_HFA_e
    CV_prop_intrinsic	  = 0x2000 ; true if class is an intrinsic type (e.g. __m128d)
    CV_prop_mocom	  = 0xC000 ; CV_MOCOM_UDT_e
    }


; class field attribute

.enum CV_fldattr_t : WORD {

    CV_fldattr_access	   = 0x0003 ; access protection CV_access_t
    CV_fldattr_mprop	   = 0x001C ; method properties CV_methodprop_t
    CV_fldattr_pseudo	   = 0x0020 ; compiler generated fcn and does not exist
    CV_fldattr_noinherit   = 0x0040 ; true if class cannot be inherited
    CV_fldattr_noconstruct = 0x0080 ; true if class cannot be constructed
    CV_fldattr_compgenx	   = 0x0100 ; compiler generated fcn and does exist
    CV_fldattr_sealed	   = 0x0200 ; true if method cannot be overridden
    }


; function flags

.enum CV_funcattr_t : BYTE {
    CV_funcattr_cxxreturnudt = 0x01 ; true if C++ style ReturnUDT
    CV_funcattr_ctor	     = 0x02 ; true if func is an instance constructor
    CV_funcattr_ctorvbase    = 0x04 ; true if func is an instance constructor
    }				    ; of a class with virtual bases


; matrix flags

.enum CV_matrixattr_t : BYTE {
    CV_matrixattr_row_major = 0x01 ; true if matrix has row-major layout
    }				   ; (column-major is default)


;  Structures to access to the type records

.template TYPTYPE fastcall
    len	  dw ?
    leaf  dw ?
    data  db CV_ZEROLEN dup(?)

    .inline NextType {
	movzx eax,[rcx].TYPTYPE.len
	lea rax,[rcx+rax+sizeof(WORD)]
	}
    .ends


.enum CV_PMEMBER {
    CV_PDM16_NONVIRT	= 0x00,
    CV_PDM16_VFCN	= 0x01,
    CV_PDM16_VBASE	= 0x02,
    CV_PDM32_NVVFCN	= 0x03,
    CV_PDM32_VBASE	= 0x04,
    CV_PMF16_NEARNVSA	= 0x05,
    CV_PMF16_NEARNVMA	= 0x06,
    CV_PMF16_NEARVBASE	= 0x07,
    CV_PMF16_FARNVSA	= 0x08,
    CV_PMF16_FARNVMA	= 0x09,
    CV_PMF16_FARVBASE	= 0x0a,
    CV_PMF32_NVSA	= 0x0b,
    CV_PMF32_NVMA	= 0x0c,
    CV_PMF32_VBASE	= 0x0d
    }


; memory representation of pointer to member. These representations are
; indexed by the enumeration above in the LF_POINTER record
;
; representation of a 16:16 pointer to data for a class with no
; virtual functions or virtual bases

.template CV_PDMR16_NONVIRT
    mdisp CV_off16_t ?	; displacement to data (NULL = -1)
    .ends


; representation of a 16:16 pointer to data for a class with virtual
; functions

.template CV_PMDR16_VFCN
    mdisp CV_off16_t ?	; displacement to data ( NULL = 0)
    .ends


; representation of a 16:16 pointer to data for a class with
; virtual bases

.template CV_PDMR16_VBASE
    mdisp CV_off16_t ?	; displacement to data
    pdisp CV_off16_t ?	; this pointer displacement to vbptr
    vdisp CV_off16_t ?	; displacement within vbase table
    .ends		; NULL = (,,0xffff)


; representation of a 32 bit pointer to data for a class with
; or without virtual functions and no virtual bases

.template CV_PDMR32_NVVFCN
    mdisp CV_off32_t ?	; displacement to data (NULL = 0x80000000)
    .ends


; representation of a 32 bit pointer to data for a class
; with virtual bases

.template CV_PDMR32_VBASE
    mdisp CV_off32_t ?	; displacement to data
    pdisp CV_off32_t ?	; this pointer displacement
    vdisp CV_off32_t ?	; vbase table displacement
   .ends		; NULL = (,,0xffffffff)


; representation of a 16:16 pointer to near member function for a
; class with no virtual functions or bases and a single address point */

.template CV_PMFR16_NEARNVSA
    off	  CV_uoff16_t ? ; near address of function (NULL = 0)
    .ends


; representation of a 16 bit pointer to member functions of a
; class with no virtual bases and multiple address points

.template CV_PMFR16_NEARNVMA
    off	  CV_uoff16_t ? ; offset of function (NULL = 0,x)
    disp  SWORD ?
    .ends


; representation of a 16 bit pointer to member function of a
; class with virtual bases

.template CV_PMFR16_NEARVBASE
    off	  CV_uoff16_t ? ; offset of function (NULL = 0,x,x,x)
    mdisp CV_off16_t ?	; displacement to data
    pdisp CV_off16_t ?	; this pointer displacement
    vdisp CV_off16_t ?	; vbase table displacement
    .ends


; representation of a 16:16 pointer to far member function for a
; class with no virtual bases and a single address point

.template CV_PMFR16_FARNVSA
    off	  CV_uoff16_t ? ; offset of function (NULL = 0:0)
    _seg  dw ?		; segment of function
    .ends


; representation of a 16:16 far pointer to member functions of a
; class with no virtual bases and multiple address points

.template CV_PMFR16_FARNVMA
    off	  CV_uoff16_t ? ; offset of function (NULL = 0:0,x)
    _seg  dw ?
    disp  SWORD ?
    .ends


; representation of a 16:16 far pointer to member function of a
; class with virtual bases

.template CV_PMFR16_FARVBASE
    off	  CV_uoff16_t ? ; offset of function (NULL = 0:0,x,x,x)
    _seg  dw ?
    mdisp CV_off16_t ?	; displacement to data
    pdisp CV_off16_t ?	; this pointer displacement
    vdisp CV_off16_t ?	; vbase table displacement
    .ends


; representation of a 32 bit pointer to member function for a
; class with no virtual bases and a single address point

.template CV_PMFR32_NVSA
    off	  CV_uoff32_t ? ; near address of function (NULL = 0L)
    .ends


; representation of a 32 bit pointer to member function for a
; class with no virtual bases and multiple address points

.template CV_PMFR32_NVMA
    off	  CV_uoff32_t ? ; near address of function (NULL = 0L,x)
    disp  CV_off32_t ?
    .ends


; representation of a 32 bit pointer to member function for a
; class with virtual bases

.template CV_PMFR32_VBASE
    off	  CV_uoff32_t ? ; near address of function (NULL = 0L,x,x,x)
    mdisp CV_off32_t ?	; displacement to data
    pdisp CV_off32_t ?	; this pointer displacement
    vdisp CV_off32_t ?	; vbase table displacement
    .ends


; Easy leaf - used for generic casting to reference leaf field
; of a subfield of a complex list

.template lfEasy
    leaf  dw ?	; LF_...
    .ends


; Type record for LF_MODIFIER

.template CV_MODIFIER_16t
    size  dw ?
    leaf  dw ?			; LF_MODIFIER_16t
    attr  CV_modifier_t ?	; modifier attribute modifier_t
    type  CV_typ16_t ?		; modified type
    .ends

.template CV_MODIFIER
    size  dw ?
    leaf  dw ?			; LF_MODIFIER
    type  CV_typ_t ?		; modified type
    attr  CV_modifier_t ?	; modifier attribute modifier_t
    .ends


; type record for LF_POINTER

.enum CV_ptr16_t : WORD {
    CV_ptr16_type		= 0x001F ; ordinal specifying pointer type (CV_ptrtype_e)
    CV_ptr16_mode		= 0x00E0 ; ordinal specifying pointer mode (CV_ptrmode_e)
    CV_ptr16_isflat32		= 0x0100 ; true if 0:32 pointer
    CV_ptr16_isvolatile		= 0x0200 ; TRUE if volatile pointer
    CV_ptr16_isconst		= 0x0400 ; TRUE if pointer
    CV_ptr16_isunaligned	= 0x0800 ; TRUE if unaligned pointer
    }

.enum CV_ptr_t : DWORD {
    CV_ptr_ptrtype		= 0x0000001F ; ordinal specifying pointer type (CV_ptrtype_e)
    CV_ptr_ptrmode		= 0x000000E0 ; ordinal specifying pointer mode (CV_ptrmode_e)
    CV_ptr_isflat32		= 0x00000100 ; true if 0:32 pointer
    CV_ptr_isvolatile		= 0x00000200 ; TRUE if volatile pointer
    CV_ptr_is			= 0x00000400 ; TRUE if pointer
    CV_ptr_isunaligned		= 0x00000800 ; TRUE if unaligned pointer
    CV_ptr_isrestrict		= 0x00001000 ; TRUE if restricted pointer (allow agressive opts)
    CV_ptr_size			= 0x0007E000 ; size of pointer (in bytes)
    CV_ptr_ismocom		= 0x00080000 ; TRUE if it is a MoCOM pointer (^ or %)
    CV_ptr_islref		= 0x00100000 ; TRUE if it is this pointer of member function with & ref-qualifier
    CV_ptr_isrref		= 0x00200000 ; TRUE if it is this pointer of member function with && ref-qualifier
    }

.template CV_POINTER_16t
    size	dw ?
    leaf	dw ?		; LF_POINTER_16t
    attr	CV_ptr16_t ?
    utype	CV_typ16_t ?	; type index of the underlying type
    union
     struct
      pmclass	 CV_typ16_t ?	; index of containing class for pointer to member
      pmenum	 dw ?		; enumeration specifying pm format (CV_pmtype_e)
     ends
     bseg	 dw ?		; base segment if PTR_BASE_SEG
     Sym	 db 1 dup(?)	; copy of base symbol record (including length)
     struct
      index	 CV_typ16_t ?	; type index if CV_PTR_BASE_TYPE
      name	 db 1 dup(?)	; name of base type
     ends
    ends
   .ends

.template CV_POINTER
    len		dw ?
    leaf	dw ?		; LF_POINTER
    utype	CV_typ_t ?	; type index of the underlying type
    attr	CV_ptr_t ?
    union
     struct
      pmclass	 CV_typ_t ?	; index of containing class for pointer to member
      pmenum	 CV_typ_t ?	; enumeration specifying pm format (CV_pmtype_e)
     ends
     bseg	 dw ?		; base segment if PTR_BASE_SEG
     Sym	 db 1 dup(?)	; copy of base symbol record (including length)
     struct
      index	 CV_typ_t ?	; type index if CV_PTR_BASE_TYPE
      name	 db 1 dup(?)	; name of base type
     ends
    ends
   .ends


; type record for LF_ARRAY

.template CV_ARRAY_16t
    size	dw ?
    leaf	dw ?		; LF_ARRAY_16t
    elemtype	CV_typ16_t ?	; type index of element type
    idxtype	CV_typ16_t ?	; type index of indexing type
    data	db CV_ZEROLEN dup(?)
   .ends

.template CV_ARRAY
    size	dw ?
    leaf	dw ?		; LF_ARRAY
    elemtype	CV_typ_t ?
    idxtype	CV_typ_t ?
    data	db CV_ZEROLEN dup(?)
   .ends


.template CV_STRIDED_ARRAY
    size	dw ?
    leaf	dw ?		; LF_STRIDED_ARRAY
    elemtype	CV_typ_t ?
    idxtype	CV_typ_t ?
    stride	dd ?
    data	db CV_ZEROLEN dup(?)
   .ends


; type record for LF_VECTOR

.template CV_VECTOR
    size	dw ?
    leaf	dw ?		; LF_VECTOR
    elemtype	CV_typ_t ?	; type index of element type
    count	dd ?		; number of elements in the vector
    data	db CV_ZEROLEN dup(?)
   .ends


; type record for LF_MATRIX

.template CV_MATRIX
    size	dw ?
    leaf	dw ?		; LF_MATRIX
    elemtype	CV_typ_t ?	; type index of element type
    rows	dd ?		; number of rows
    cols	dd ?		; number of columns
    majorStride dd ?
    matattr	CV_matrixattr_t ?
    data	db CV_ZEROLEN dup(?)
   .ends


; type record for LF_CLASS, LF_STRUCTURE

.template CV_CLASS_16t
    size	dw ?
    leaf	dw ?		; LF_CLASS_16t, LF_STRUCT_16t
    count	dw ?		; count of number of elements in class
    field	CV_typ16_t ?	; type index of LF_FIELD descriptor list
    property	CV_prop_t ?	; property attribute field (prop_t)
    derived	CV_typ16_t ?	; type index of derived from list if not zero
    vshape	CV_typ16_t ?	; type index of vshape table for this class
    data	db CV_ZEROLEN dup(?)
   .ends

CV_STRUCT_16t	typedef CV_CLASS_16t

.template CV_CLASS
    size	dw ?
    leaf	dw ?		; LF_CLASS, LF_STRUCT, LF_INTERFACE
    count	dw ?
    property	CV_prop_t ?
    field	CV_typ_t ?
    derived	CV_typ_t ?
    vshape	CV_typ_t ?
    data	db CV_ZEROLEN dup(?)
   .ends

CV_STRUCT	typedef CV_CLASS
CV_INTERFACE	typedef CV_CLASS


; type record for LF_UNION

.template CV_UNION_16t
    size	dw ?
    leaf	dw ?		; LF_UNION_16t
    count	dw ?		; count of number of elements in class
    field	CV_typ16_t ?	; type index of LF_FIELD descriptor list
    property	CV_prop_t ?	; property attribute field
    data	db CV_ZEROLEN dup(?)
   .ends

.template CV_UNION
    size	dw ?
    leaf	dw ?		; LF_UNION
    count	dw ?
    property	CV_prop_t ?
    field	CV_typ_t ?
    data	db CV_ZEROLEN dup(?)
   .ends


; type record for LF_ALIAS

.template CV_ALIAS
    size	dw ?
    leaf	dw ?		; LF_ALIAS
    utype	CV_typ_t ?	; underlying type
    Name	db 1 dup(?)	; alias name
   .ends

CV_ItemId	typedef CV_typ_t

.template CV_FUNC_ID
    size	dw ?
    leaf	dw ?		; LF_FUNC_ID
    scopeId	CV_ItemId ?	; parent scope of the ID, 0 if global
    type	CV_typ_t ?	; function type
    name	db CV_ZEROLEN dup(?)
   .ends

.template CV_MFUNC_ID
    size	dw ?
    leaf	dw ?		; LF_MFUNC_ID
    parentType	CV_typ_t ?	; type index of parent
    type	CV_typ_t ?	; function type
    name	db CV_ZEROLEN dup(?)
   .ends

.template CV_STRING_ID
    size	dw ?
    leaf	db ?		; LF_STRING_ID
    id		CV_ItemId ?	; ID to list of sub string IDs
    name	db CV_ZEROLEN dup(?)
   .ends

.template CV_UDT_SRC_LINE
    size	dw ?
    leaf	dw ?		; LF_UDT_SRC_LINE
    type	CV_typ_t ?	; UDT's type index
    src		CV_ItemId ?	; index to LF_STRING_ID record where source file name is saved
    line	dd ?		; line number
   .ends

.template CV_UDT_MOD_SRC_LINE
    size	dw ?
    leaf	dw ?		; LF_UDT_MOD_SRC_LINE
    type	CV_typ_t ?	; UDT's type index
    src		CV_ItemId ?	; index into string table where source file name is saved
    line	dd ?		; line number
    imod	dw ?		; module that contributes this UDT definition
   .ends


.enum CV_BuildInfo_e {
    CV_BuildInfo_CurrentDirectory	= 0,
    CV_BuildInfo_BuildTool		= 1,
    CV_BuildInfo_SourceFile		= 2,
    CV_BuildInfo_ProgramDatabaseFile	= 3,
    CV_BuildInfo_CommandArguments	= 4,
    CV_BUILDINFO_KNOWN
    }


; type record for build information

.template CV_BUILDINFO
    size	dw ?
    leaf	dw ?		; LF_BUILDINFO
    count	dw ?		; number of arguments
    arg		CV_ItemId CV_BUILDINFO_KNOWN dup(?)	; arguments as CodeItemId
   .ends


; type record for LF_MANAGED

.template CV_MANAGED
    leaf	dw ?		; LF_MANAGED
    Name	db 1 dup(?)	; utf8, zero terminated managed type name
   .ends

; type record for LF_ENUM

.template CV_ENUM_16t
    leaf	dw ?		; LF_ENUM_16t
    count	dw ?		; count of number of elements in class
    utype	CV_typ16_t ?	; underlying type of the enum
    field	CV_typ16_t ?	; type index of LF_FIELD descriptor list
    property	CV_prop_t ?	; property attribute field
    Name	db 1 dup(?)	; length prefixed name of enum
   .ends

.template CV_ENUM
    leaf	dw ?		; LF_ENUM
    count	dw ?		; count of number of elements in class
    property	CV_prop_t ?	; property attribute field
    utype	CV_typ_t ?	; underlying type of the enum
    field	CV_typ_t ?	; type index of LF_FIELD descriptor list
    Name	db 1 dup(?)	; length prefixed name of enum
   .ends


; Type record for LF_PROCEDURE

.template CV_PROCEDURE_16t
    size	dw ?
    leaf	dw ?		; LF_PROCEDURE_16t
    rvtype	CV_typ16_t ?	; type index of return value
    calltype	db ?		; calling convention (CV_call_t)
    funcattr	CV_funcattr_t ? ; attributes
    parmcount	dw ?		; number of parameters
    arglist	CV_typ16_t ?	; type index of argument list
   .ends

.template CV_PROCEDURE
    size	dw ?
    leaf	dw ?		; LF_PROCEDURE
    rvtype	CV_typ_t ?	; type index of return value
    calltype	db ?		; calling convention (CV_call_t)
    funcattr	CV_funcattr_t ? ; attributes
    parmcount	dw ?		; number of parameters
    arglist	CV_typ_t ?	; type index of argument list
   .ends


; Type record for member function

.template CV_MFUNCTION_16t
    size	dw ?
    leaf	dw ?		; LF_MFUNCTION_16t
    rvtype	CV_typ16_t ?	; type index of return value
    classtype	CV_typ16_t ?	; type index of containing class
    thistype	CV_typ16_t ?	; type index of this pointer (model specific)
    calltype	db ?		; calling convention (call_t)
    funcattr	CV_funcattr_t ? ; attributes
    parmcount	dw ?		; number of parameters
    arglist	CV_typ16_t ?	; type index of argument list
    thisadjust	sdword ?	; this adjuster (long because pad required anyway)
   .ends

.template CV_MFUNCTION
    size	dw ?
    leaf	dw ?		; LF_MFUNCTION
    rvtype	CV_typ_t ?	; type index of return value
    classtype	CV_typ_t ?	; type index of containing class
    thistype	CV_typ_t ?	; type index of this pointer (model specific)
    calltype	db ?		; calling convention (call_t)
    funcattr	CV_funcattr_t ? ; attributes
    parmcount	dw ?		; number of parameters
    arglist	CV_typ_t ?	; type index of argument list
    thisadjust	sdword ?	; this adjuster (long because pad required anyway)
   .ends


; type record for basic array

.template CV_BARRAY_16t
    size	dw ?
    leaf	dw ?		; LF_BARRAY_16t
    utype	CV_typ16_t ?	; type index of underlying type
   .ends

.template CV_BARRAY
    size	dw ?
    leaf	dw ?		; LF_BARRAY
    utype	CV_typ_t ?	; type index of underlying type
   .ends


; type record for assembler labels

.template CV_LABEL
    size	dw ?
    leaf	dw ?		; LF_LABEL
    mode	dw ?		; addressing mode of label
   .ends


; argument list leaf

.template CV_ARGLIST_16t
    size	dw ?
    leaf	dw ?		; LF_ARGLIST_16t
    count	dw ?		; number of arguments
    arg		CV_typ16_t CV_ZEROLEN dup(?) ; number of arguments
   .ends

.template CV_ARGLIST
    size	dw ?
    leaf	dw ?		; LF_ARGLIST, LF_SUBSTR_LIST
    count	dd ?		; number of arguments
    arg		CV_typ_t CV_ZEROLEN dup(?) ; number of arguments
   .ends

.template CV_FIELDLIST
    size	dw ?
    leaf	dw ?		; LF_FIELDLIST, LF_FIELDLIST_16t
    data	db CV_ZEROLEN dup(?) ; field list sub lists
   .ends


; type record for LF_BITFIELD

.template CV_BITFIELD_16t
    size	dw ?
    leaf	dw ?		; LF_BITFIELD_16t
    length	db ?
    position	db ?
    type	CV_typ16_t ?	; type of bitfield
   .ends

.template CV_BITFIELD
    size	dw ?
    leaf	dw ?		; LF_BITFIELD
    type	CV_typ_t ?	; type of bitfield
    length	db ?
    position	db ?
    reserved	dw ?		; align 4...
   .ends


; Symbol definitions

.enum SYM_ENUM_e {

    S_COMPILE	    =  0x0001,
    S_REGISTER_16t  =  0x0002,
    S_CONSTANT_16t  =  0x0003,
    S_UDT_16t	    =  0x0004,
    S_SSEARCH	    =  0x0005,
    S_END	    =  0x0006,
    S_SKIP	    =  0x0007,
    S_CVRESERVE	    =  0x0008,
    S_OBJNAME_ST    =  0x0009,
    S_ENDARG	    =  0x000a,
    S_COBOLUDT_16t  =  0x000b,
    S_MANYREG_16t   =  0x000c,
    S_RETURN	    =  0x000d,
    S_ENTRYTHIS	    =  0x000e,

    S_BPREL16	    =  0x0100,
    S_LDATA16	    =  0x0101,
    S_GDATA16	    =  0x0102,
    S_PUB16	    =  0x0103,
    S_LPROC16	    =  0x0104,
    S_GPROC16	    =  0x0105,
    S_THUNK16	    =  0x0106,
    S_BLOCK16	    =  0x0107,
    S_WITH16	    =  0x0108,
    S_LABEL16	    =  0x0109,
    S_CEXMODEL16    =  0x010a,
    S_VFTABLE16	    =  0x010b,
    S_REGREL16	    =  0x010c,

    S_BPREL32_16t   =  0x0200,
    S_LDATA32_16t   =  0x0201,
    S_GDATA32_16t   =  0x0202,
    S_PUB32_16t	    =  0x0203,
    S_LPROC32_16t   =  0x0204,
    S_GPROC32_16t   =  0x0205,
    S_THUNK32_ST    =  0x0206,
    S_BLOCK32_ST    =  0x0207,
    S_WITH32_ST	    =  0x0208,
    S_LABEL32_ST    =  0x0209,
    S_CEXMODEL32    =  0x020a,
    S_VFTABLE32_16t =  0x020b,
    S_REGREL32_16t  =  0x020c,
    S_LTHREAD32_16t =  0x020d,
    S_GTHREAD32_16t =  0x020e,
    S_SLINK32	    =  0x020f,

    S_LPROCMIPS_16t =  0x0300,
    S_GPROCMIPS_16t =  0x0301,

    ; if these ref symbols have names following then the names are in ST format

    S_PROCREF_ST    =  0x0400,
    S_DATAREF_ST    =  0x0401,
    S_ALIGN	    =  0x0402,

    S_LPROCREF_ST   =  0x0403,
    S_OEM	    =  0x0404,

    ; sym records with 32-bit types embedded instead of 16-bit
    ;	 all have 0x1000 bit set for easy identification
    ;	 only do the 32-bit target versions since we don't really
    ;	 care about 16-bit ones anymore.

    S_TI16_MAX	    =  0x1000,

    S_REGISTER_ST   =  0x1001,
    S_CONSTANT_ST   =  0x1002,
    S_UDT_ST	    =  0x1003,
    S_COBOLUDT_ST   =  0x1004,
    S_MANYREG_ST    =  0x1005,
    S_BPREL32_ST    =  0x1006,
    S_LDATA32_ST    =  0x1007,
    S_GDATA32_ST    =  0x1008,
    S_PUB32_ST	    =  0x1009,
    S_LPROC32_ST    =  0x100a,
    S_GPROC32_ST    =  0x100b,
    S_VFTABLE32	    =  0x100c,
    S_REGREL32_ST   =  0x100d,
    S_LTHREAD32_ST  =  0x100e,
    S_GTHREAD32_ST  =  0x100f,

    S_LPROCMIPS_ST  =  0x1010,
    S_GPROCMIPS_ST  =  0x1011,

    S_FRAMEPROC	    =  0x1012,
    S_COMPILE2_ST   =  0x1013,

    ; new symbols necessary for 16-bit enumerates of IA64 registers
    ; and IA64 specific symbols

    S_MANYREG2_ST   =  0x1014,
    S_LPROCIA64_ST  =  0x1015,
    S_GPROCIA64_ST  =  0x1016,

    ; Local symbols for IL

    S_LOCALSLOT_ST  =  0x1017,
    S_PARAMSLOT_ST  =  0x1018,

    S_ANNOTATION    =  0x1019,

    ; symbols to support managed code debugging

    S_GMANPROC_ST   =  0x101a,
    S_LMANPROC_ST   =  0x101b,
    S_RESERVED1	    =  0x101c,
    S_RESERVED2	    =  0x101d,
    S_RESERVED3	    =  0x101e,
    S_RESERVED4	    =  0x101f,
    S_LMANDATA_ST   =  0x1020,
    S_GMANDATA_ST   =  0x1021,
    S_MANFRAMEREL_ST=  0x1022,
    S_MANREGISTER_ST=  0x1023,
    S_MANSLOT_ST    =  0x1024,
    S_MANMANYREG_ST =  0x1025,
    S_MANREGREL_ST  =  0x1026,
    S_MANMANYREG2_ST=  0x1027,
    S_MANTYPREF	    =  0x1028,
    S_UNAMESPACE_ST =  0x1029,

    ; Symbols w/ SZ name fields. All name fields contain utf8 encoded strings.

    S_ST_MAX	    =  0x1100,

    S_OBJNAME	    =  0x1101,
    S_THUNK32	    =  0x1102,
    S_BLOCK32	    =  0x1103,
    S_WITH32	    =  0x1104,
    S_LABEL32	    =  0x1105,
    S_REGISTER	    =  0x1106,
    S_CONSTANT	    =  0x1107,
    S_UDT	    =  0x1108,
    S_COBOLUDT	    =  0x1109,
    S_MANYREG	    =  0x110a,
    S_BPREL32	    =  0x110b,
    S_LDATA32	    =  0x110c,
    S_GDATA32	    =  0x110d,
    S_PUB32	    =  0x110e,
    S_LPROC32	    =  0x110f,
    S_GPROC32	    =  0x1110,
    S_REGREL32	    =  0x1111,
    S_LTHREAD32	    =  0x1112,
    S_GTHREAD32	    =  0x1113,

    S_LPROCMIPS	    =  0x1114,
    S_GPROCMIPS	    =  0x1115,
    S_COMPILE2	    =  0x1116,
    S_MANYREG2	    =  0x1117,
    S_LPROCIA64	    =  0x1118,
    S_GPROCIA64	    =  0x1119,
    S_LOCALSLOT	    =  0x111a,
    S_SLOT	    = S_LOCALSLOT,
    S_PARAMSLOT	    =  0x111b,

    ; symbols to support managed code debugging

    S_LMANDATA	    =  0x111c,
    S_GMANDATA	    =  0x111d,
    S_MANFRAMEREL   =  0x111e,
    S_MANREGISTER   =  0x111f,
    S_MANSLOT	    =  0x1120,
    S_MANMANYREG    =  0x1121,
    S_MANREGREL	    =  0x1122,
    S_MANMANYREG2   =  0x1123,
    S_UNAMESPACE    =  0x1124,

    ; ref symbols with name fields

    S_PROCREF	    =  0x1125,
    S_DATAREF	    =  0x1126,
    S_LPROCREF	    =  0x1127,
    S_ANNOTATIONREF =  0x1128,
    S_TOKENREF	    =  0x1129,

    ; continuation of managed symbols

    S_GMANPROC	    =  0x112a,
    S_LMANPROC	    =  0x112b,

    ; short, light-weight thunks

    S_TRAMPOLINE    =  0x112c,
    S_MANCONSTANT   =  0x112d,

    ; native attributed local/parms

    S_ATTR_FRAMEREL =  0x112e,
    S_ATTR_REGISTER =  0x112f,
    S_ATTR_REGREL   =  0x1130,
    S_ATTR_MANYREG  =  0x1131,

    ; Separated code (from the compiler) support

    S_SEPCODE	    =  0x1132,

    S_LOCAL_2005    =  0x1133,
    S_DEFRANGE_2005 =  0x1134,
    S_DEFRANGE2_2005 = 0x1135,

    S_SECTION	    =  0x1136,
    S_COFFGROUP	    =  0x1137,
    S_EXPORT	    =  0x1138,

    S_CALLSITEINFO  =  0x1139,
    S_FRAMECOOKIE   =  0x113a,

    S_DISCARDED	    =  0x113b,

    S_COMPILE3	    =  0x113c,
    S_ENVBLOCK	    =  0x113d,

    S_LOCAL	    =  0x113e,
    S_DEFRANGE	    =  0x113f,
    S_DEFRANGE_SUBFIELD =  0x1140,

    S_DEFRANGE_REGISTER =  0x1141,
    S_DEFRANGE_FRAMEPOINTER_REL =  0x1142,
    S_DEFRANGE_SUBFIELD_REGISTER =  0x1143,
    S_DEFRANGE_FRAMEPOINTER_REL_FULL_SCOPE =  0x1144,
    S_DEFRANGE_REGISTER_REL =  0x1145,

    ; S_PROC symbols that reference ID instead of type

    S_LPROC32_ID     =	0x1146,
    S_GPROC32_ID     =	0x1147,
    S_LPROCMIPS_ID   =	0x1148,
    S_GPROCMIPS_ID   =	0x1149,
    S_LPROCIA64_ID   =	0x114a,
    S_GPROCIA64_ID   =	0x114b,

    S_BUILDINFO	     = 0x114c,
    S_INLINESITE     = 0x114d,
    S_INLINESITE_END = 0x114e,
    S_PROC_ID_END    = 0x114f,

    S_DEFRANGE_HLSL  = 0x1150,
    S_GDATA_HLSL     = 0x1151,
    S_LDATA_HLSL     = 0x1152,

    S_FILESTATIC     = 0x1153,

if defined(CC_DP_CXX) AND CC_DP_CXX
    S_LOCAL_DPC_GROUPSHARED = 0x1154,
    S_LPROC32_DPC = 0x1155,
    S_LPROC32_DPC_ID =	0x1156,
    S_DEFRANGE_DPC_PTR_TAG =  0x1157,
    S_DPC_SYM_TAG_MAP = 0x1158,
endif
    S_ARMSWITCHTABLE  = 0x1159,
    S_CALLEES = 0x115a,
    S_CALLERS = 0x115b,
    S_POGODATA = 0x115c,
    S_INLINESITE2 = 0x115d,

    S_HEAPALLOCSITE = 0x115e,

    S_MOD_TYPEREF = 0x115f,

    S_REF_MINIPDB = 0x1160,
    S_PDBMAP	  = 0x1161,

    S_GDATA_HLSL32 = 0x1162,
    S_LDATA_HLSL32 = 0x1163,

    S_GDATA_HLSL32_EX = 0x1164,
    S_LDATA_HLSL32_EX = 0x1165,

    S_RECTYPE_MAX,
    S_RECTYPE_LAST  = S_RECTYPE_MAX - 1,
    S_RECTYPE_PAD   = S_RECTYPE_MAX + 0x100
    }


; enum describing the compile flag source language

.enum CV_CFL_LANG {
    CV_CFL_C	    = 0x00,
    CV_CFL_CXX	    = 0x01,
    CV_CFL_FORTRAN  = 0x02,
    CV_CFL_MASM	    = 0x03,
    CV_CFL_PASCAL   = 0x04,
    CV_CFL_BASIC    = 0x05,
    CV_CFL_COBOL    = 0x06,
    CV_CFL_LINK	    = 0x07,
    CV_CFL_CVTRES   = 0x08,
    CV_CFL_CVTPGD   = 0x09,
    CV_CFL_CSHARP   = 0x0A,
    CV_CFL_VB	    = 0x0B,
    CV_CFL_ILASM    = 0x0C,
    CV_CFL_JAVA	    = 0x0D,
    CV_CFL_JSCRIPT  = 0x0E,
    CV_CFL_MSIL	    = 0x0F,
    CV_CFL_HLSL	    = 0x10,
    CV_CFL_OBJC	    = 0x11,
    CV_CFL_OBJCXX   = 0x12,
    }


; enum describing target processor

.enum CV_CPU_TYPE_e {
    CV_CFL_8080		= 0x00,
    CV_CFL_8086		= 0x01,
    CV_CFL_80286	= 0x02,
    CV_CFL_80386	= 0x03,
    CV_CFL_80486	= 0x04,
    CV_CFL_PENTIUM	= 0x05,
    CV_CFL_PENTIUMII	= 0x06,
    CV_CFL_PENTIUMPRO	= CV_CFL_PENTIUMII,
    CV_CFL_PENTIUMIII	= 0x07,
    CV_CFL_MIPS		= 0x10,
    CV_CFL_MIPSR4000	= CV_CFL_MIPS,
    CV_CFL_MIPS16	= 0x11,
    CV_CFL_MIPS32	= 0x12,
    CV_CFL_MIPS64	= 0x13,
    CV_CFL_MIPSI	= 0x14,
    CV_CFL_MIPSII	= 0x15,
    CV_CFL_MIPSIII	= 0x16,
    CV_CFL_MIPSIV	= 0x17,
    CV_CFL_MIPSV	= 0x18,
    CV_CFL_M68000	= 0x20,
    CV_CFL_M68010	= 0x21,
    CV_CFL_M68020	= 0x22,
    CV_CFL_M68030	= 0x23,
    CV_CFL_M68040	= 0x24,
    CV_CFL_ALPHA	= 0x30,
    CV_CFL_ALPHA_21064	= 0x30,
    CV_CFL_ALPHA_21164	= 0x31,
    CV_CFL_ALPHA_21164A = 0x32,
    CV_CFL_ALPHA_21264	= 0x33,
    CV_CFL_ALPHA_21364	= 0x34,
    CV_CFL_PPC601	= 0x40,
    CV_CFL_PPC603	= 0x41,
    CV_CFL_PPC604	= 0x42,
    CV_CFL_PPC620	= 0x43,
    CV_CFL_PPCFP	= 0x44,
    CV_CFL_PPCBE	= 0x45,
    CV_CFL_SH3		= 0x50,
    CV_CFL_SH3E		= 0x51,
    CV_CFL_SH3DSP	= 0x52,
    CV_CFL_SH4		= 0x53,
    CV_CFL_SHMEDIA	= 0x54,
    CV_CFL_ARM3		= 0x60,
    CV_CFL_ARM4		= 0x61,
    CV_CFL_ARM4T	= 0x62,
    CV_CFL_ARM5		= 0x63,
    CV_CFL_ARM5T	= 0x64,
    CV_CFL_ARM6		= 0x65,
    CV_CFL_ARM_XMAC	= 0x66,
    CV_CFL_ARM_WMMX	= 0x67,
    CV_CFL_ARM7		= 0x68,
    CV_CFL_OMNI		= 0x70,
    CV_CFL_IA64		= 0x80,
    CV_CFL_IA64_1	= 0x80,
    CV_CFL_IA64_2	= 0x81,
    CV_CFL_CEE		= 0x90,
    CV_CFL_AM33		= 0xA0,
    CV_CFL_M32R		= 0xB0,
    CV_CFL_TRICORE	= 0xC0,
    CV_CFL_X64		= 0xD0,
    CV_CFL_AMD64	= CV_CFL_X64,
    CV_CFL_EBC		= 0xE0,
    CV_CFL_THUMB	= 0xF0,
    CV_CFL_ARMNT	= 0xF4,
    CV_CFL_ARM64	= 0xF6,
    CV_CFL_D3D11_SHADER = 0x100,
    }

.enum CV_HREG_e {
    CV_ALLREG_ERR	= 30000,
    CV_ALLREG_TEB	= 30001,
    CV_ALLREG_TIMER	= 30002,
    CV_ALLREG_EFAD1	= 30003,
    CV_ALLREG_EFAD2	= 30004,
    CV_ALLREG_EFAD3	= 30005,
    CV_ALLREG_VFRAME	= 30006,
    CV_ALLREG_HANDLE	= 30007,
    CV_ALLREG_PARAMS	= 30008,
    CV_ALLREG_LOCALS	= 30009,
    CV_ALLREG_TID	= 30010,
    CV_ALLREG_ENV	= 30011,
    CV_ALLREG_CMDLN	= 30012,
    CV_REG_NONE		= 0,
    CV_REG_AL		= 1,
    CV_REG_CL		= 2,
    CV_REG_DL		= 3,
    CV_REG_BL		= 4,
    CV_REG_AH		= 5,
    CV_REG_CH		= 6,
    CV_REG_DH		= 7,
    CV_REG_BH		= 8,
    CV_REG_AX		= 9,
    CV_REG_CX		= 10,
    CV_REG_DX		= 11,
    CV_REG_BX		= 12,
    CV_REG_SP		= 13,
    CV_REG_BP		= 14,
    CV_REG_SI		= 15,
    CV_REG_DI		= 16,
    CV_REG_EAX		= 17,
    CV_REG_ECX		= 18,
    CV_REG_EDX		= 19,
    CV_REG_EBX		= 20,
    CV_REG_ESP		= 21,
    CV_REG_EBP		= 22,
    CV_REG_ESI		= 23,
    CV_REG_EDI		= 24,
    CV_REG_ES		= 25,
    CV_REG_CS		= 26,
    CV_REG_SS		= 27,
    CV_REG_DS		= 28,
    CV_REG_FS		= 29,
    CV_REG_GS		= 30,
    CV_REG_IP		= 31,
    CV_REG_FLAGS	= 32,
    CV_REG_EIP		= 33,
    CV_REG_EFLAGS	= 34,
    CV_REG_TEMP		= 40,
    CV_REG_TEMPH	= 41,
    CV_REG_QUOTE	= 42,
    CV_REG_PCDR3	= 43,
    CV_REG_PCDR4	= 44,
    CV_REG_PCDR5	= 45,
    CV_REG_PCDR6	= 46,
    CV_REG_PCDR7	= 47,
    CV_REG_CR0		= 80,
    CV_REG_CR1		= 81,
    CV_REG_CR2		= 82,
    CV_REG_CR3		= 83,
    CV_REG_CR4		= 84,
    CV_REG_DR0		= 90,
    CV_REG_DR1		= 91,
    CV_REG_DR2		= 92,
    CV_REG_DR3		= 93,
    CV_REG_DR4		= 94,
    CV_REG_DR5		= 95,
    CV_REG_DR6		= 96,
    CV_REG_DR7		= 97,
    CV_REG_GDTR		= 110,
    CV_REG_GDTL		= 111,
    CV_REG_IDTR		= 112,
    CV_REG_IDTL		= 113,
    CV_REG_LDTR		= 114,
    CV_REG_TR		= 115,
    CV_REG_PSEUDO1	= 116,
    CV_REG_PSEUDO2	= 117,
    CV_REG_PSEUDO3	= 118,
    CV_REG_PSEUDO4	= 119,
    CV_REG_PSEUDO5	= 120,
    CV_REG_PSEUDO6	= 121,
    CV_REG_PSEUDO7	= 122,
    CV_REG_PSEUDO8	= 123,
    CV_REG_PSEUDO9	= 124,
    CV_REG_ST0		= 128,
    CV_REG_ST1		= 129,
    CV_REG_ST2		= 130,
    CV_REG_ST3		= 131,
    CV_REG_ST4		= 132,
    CV_REG_ST5		= 133,
    CV_REG_ST6		= 134,
    CV_REG_ST7		= 135,
    CV_REG_CTRL		= 136,
    CV_REG_STAT		= 137,
    CV_REG_TAG		= 138,
    CV_REG_FPIP		= 139,
    CV_REG_FPCS		= 140,
    CV_REG_FPDO		= 141,
    CV_REG_FPDS		= 142,
    CV_REG_ISEM		= 143,
    CV_REG_FPEIP	= 144,
    CV_REG_FPEDO	= 145,
    CV_REG_MM0		= 146,
    CV_REG_MM1		= 147,
    CV_REG_MM2		= 148,
    CV_REG_MM3		= 149,
    CV_REG_MM4		= 150,
    CV_REG_MM5		= 151,
    CV_REG_MM6		= 152,
    CV_REG_MM7		= 153,
    CV_REG_XMM0		= 154,
    CV_REG_XMM1		= 155,
    CV_REG_XMM2		= 156,
    CV_REG_XMM3		= 157,
    CV_REG_XMM4		= 158,
    CV_REG_XMM5		= 159,
    CV_REG_XMM6		= 160,
    CV_REG_XMM7		= 161,
    CV_REG_XMM00	= 162,
    CV_REG_XMM01	= 163,
    CV_REG_XMM02	= 164,
    CV_REG_XMM03	= 165,
    CV_REG_XMM10	= 166,
    CV_REG_XMM11	= 167,
    CV_REG_XMM12	= 168,
    CV_REG_XMM13	= 169,
    CV_REG_XMM20	= 170,
    CV_REG_XMM21	= 171,
    CV_REG_XMM22	= 172,
    CV_REG_XMM23	= 173,
    CV_REG_XMM30	= 174,
    CV_REG_XMM31	= 175,
    CV_REG_XMM32	= 176,
    CV_REG_XMM33	= 177,
    CV_REG_XMM40	= 178,
    CV_REG_XMM41	= 179,
    CV_REG_XMM42	= 180,
    CV_REG_XMM43	= 181,
    CV_REG_XMM50	= 182,
    CV_REG_XMM51	= 183,
    CV_REG_XMM52	= 184,
    CV_REG_XMM53	= 185,
    CV_REG_XMM60	= 186,
    CV_REG_XMM61	= 187,
    CV_REG_XMM62	= 188,
    CV_REG_XMM63	= 189,
    CV_REG_XMM70	= 190,
    CV_REG_XMM71	= 191,
    CV_REG_XMM72	= 192,
    CV_REG_XMM73	= 193,
    CV_REG_XMM0L	= 194,
    CV_REG_XMM1L	= 195,
    CV_REG_XMM2L	= 196,
    CV_REG_XMM3L	= 197,
    CV_REG_XMM4L	= 198,
    CV_REG_XMM5L	= 199,
    CV_REG_XMM6L	= 200,
    CV_REG_XMM7L	= 201,
    CV_REG_XMM0H	= 202,
    CV_REG_XMM1H	= 203,
    CV_REG_XMM2H	= 204,
    CV_REG_XMM3H	= 205,
    CV_REG_XMM4H	= 206,
    CV_REG_XMM5H	= 207,
    CV_REG_XMM6H	= 208,
    CV_REG_XMM7H	= 209,
    CV_REG_MXCSR	= 211,
    CV_REG_EDXEAX	= 212,
    CV_REG_EMM0L	= 220,
    CV_REG_EMM1L	= 221,
    CV_REG_EMM2L	= 222,
    CV_REG_EMM3L	= 223,
    CV_REG_EMM4L	= 224,
    CV_REG_EMM5L	= 225,
    CV_REG_EMM6L	= 226,
    CV_REG_EMM7L	= 227,
    CV_REG_EMM0H	= 228,
    CV_REG_EMM1H	= 229,
    CV_REG_EMM2H	= 230,
    CV_REG_EMM3H	= 231,
    CV_REG_EMM4H	= 232,
    CV_REG_EMM5H	= 233,
    CV_REG_EMM6H	= 234,
    CV_REG_EMM7H	= 235,
    CV_REG_MM00		= 236,
    CV_REG_MM01		= 237,
    CV_REG_MM10		= 238,
    CV_REG_MM11		= 239,
    CV_REG_MM20		= 240,
    CV_REG_MM21		= 241,
    CV_REG_MM30		= 242,
    CV_REG_MM31		= 243,
    CV_REG_MM40		= 244,
    CV_REG_MM41		= 245,
    CV_REG_MM50		= 246,
    CV_REG_MM51		= 247,
    CV_REG_MM60		= 248,
    CV_REG_MM61		= 249,
    CV_REG_MM70		= 250,
    CV_REG_MM71		= 251,
    CV_REG_YMM0		= 252,
    CV_REG_YMM1		= 253,
    CV_REG_YMM2		= 254,
    CV_REG_YMM3		= 255,
    CV_REG_YMM4		= 256,
    CV_REG_YMM5		= 257,
    CV_REG_YMM6		= 258,
    CV_REG_YMM7		= 259,
    CV_REG_YMM0H	= 260,
    CV_REG_YMM1H	= 261,
    CV_REG_YMM2H	= 262,
    CV_REG_YMM3H	= 263,
    CV_REG_YMM4H	= 264,
    CV_REG_YMM5H	= 265,
    CV_REG_YMM6H	= 266,
    CV_REG_YMM7H	= 267,
    CV_REG_YMM0I0	= 268,
    CV_REG_YMM0I1	= 269,
    CV_REG_YMM0I2	= 270,
    CV_REG_YMM0I3	= 271,
    CV_REG_YMM1I0	= 272,
    CV_REG_YMM1I1	= 273,
    CV_REG_YMM1I2	= 274,
    CV_REG_YMM1I3	= 275,
    CV_REG_YMM2I0	= 276,
    CV_REG_YMM2I1	= 277,
    CV_REG_YMM2I2	= 278,
    CV_REG_YMM2I3	= 279,
    CV_REG_YMM3I0	= 280,
    CV_REG_YMM3I1	= 281,
    CV_REG_YMM3I2	= 282,
    CV_REG_YMM3I3	= 283,
    CV_REG_YMM4I0	= 284,
    CV_REG_YMM4I1	= 285,
    CV_REG_YMM4I2	= 286,
    CV_REG_YMM4I3	= 287,
    CV_REG_YMM5I0	= 288,
    CV_REG_YMM5I1	= 289,
    CV_REG_YMM5I2	= 290,
    CV_REG_YMM5I3	= 291,
    CV_REG_YMM6I0	= 292,
    CV_REG_YMM6I1	= 293,
    CV_REG_YMM6I2	= 294,
    CV_REG_YMM6I3	= 295,
    CV_REG_YMM7I0	= 296,
    CV_REG_YMM7I1	= 297,
    CV_REG_YMM7I2	= 298,
    CV_REG_YMM7I3	= 299,
    CV_REG_YMM0F0	= 300,
    CV_REG_YMM0F1	= 301,
    CV_REG_YMM0F2	= 302,
    CV_REG_YMM0F3	= 303,
    CV_REG_YMM0F4	= 304,
    CV_REG_YMM0F5	= 305,
    CV_REG_YMM0F6	= 306,
    CV_REG_YMM0F7	= 307,
    CV_REG_YMM1F0	= 308,
    CV_REG_YMM1F1	= 309,
    CV_REG_YMM1F2	= 310,
    CV_REG_YMM1F3	= 311,
    CV_REG_YMM1F4	= 312,
    CV_REG_YMM1F5	= 313,
    CV_REG_YMM1F6	= 314,
    CV_REG_YMM1F7	= 315,
    CV_REG_YMM2F0	= 316,
    CV_REG_YMM2F1	= 317,
    CV_REG_YMM2F2	= 318,
    CV_REG_YMM2F3	= 319,
    CV_REG_YMM2F4	= 320,
    CV_REG_YMM2F5	= 321,
    CV_REG_YMM2F6	= 322,
    CV_REG_YMM2F7	= 323,
    CV_REG_YMM3F0	= 324,
    CV_REG_YMM3F1	= 325,
    CV_REG_YMM3F2	= 326,
    CV_REG_YMM3F3	= 327,
    CV_REG_YMM3F4	= 328,
    CV_REG_YMM3F5	= 329,
    CV_REG_YMM3F6	= 330,
    CV_REG_YMM3F7	= 331,
    CV_REG_YMM4F0	= 332,
    CV_REG_YMM4F1	= 333,
    CV_REG_YMM4F2	= 334,
    CV_REG_YMM4F3	= 335,
    CV_REG_YMM4F4	= 336,
    CV_REG_YMM4F5	= 337,
    CV_REG_YMM4F6	= 338,
    CV_REG_YMM4F7	= 339,
    CV_REG_YMM5F0	= 340,
    CV_REG_YMM5F1	= 341,
    CV_REG_YMM5F2	= 342,
    CV_REG_YMM5F3	= 343,
    CV_REG_YMM5F4	= 344,
    CV_REG_YMM5F5	= 345,
    CV_REG_YMM5F6	= 346,
    CV_REG_YMM5F7	= 347,
    CV_REG_YMM6F0	= 348,
    CV_REG_YMM6F1	= 349,
    CV_REG_YMM6F2	= 350,
    CV_REG_YMM6F3	= 351,
    CV_REG_YMM6F4	= 352,
    CV_REG_YMM6F5	= 353,
    CV_REG_YMM6F6	= 354,
    CV_REG_YMM6F7	= 355,
    CV_REG_YMM7F0	= 356,
    CV_REG_YMM7F1	= 357,
    CV_REG_YMM7F2	= 358,
    CV_REG_YMM7F3	= 359,
    CV_REG_YMM7F4	= 360,
    CV_REG_YMM7F5	= 361,
    CV_REG_YMM7F6	= 362,
    CV_REG_YMM7F7	= 363,
    CV_REG_YMM0D0	= 364,
    CV_REG_YMM0D1	= 365,
    CV_REG_YMM0D2	= 366,
    CV_REG_YMM0D3	= 367,
    CV_REG_YMM1D0	= 368,
    CV_REG_YMM1D1	= 369,
    CV_REG_YMM1D2	= 370,
    CV_REG_YMM1D3	= 371,
    CV_REG_YMM2D0	= 372,
    CV_REG_YMM2D1	= 373,
    CV_REG_YMM2D2	= 374,
    CV_REG_YMM2D3	= 375,
    CV_REG_YMM3D0	= 376,
    CV_REG_YMM3D1	= 377,
    CV_REG_YMM3D2	= 378,
    CV_REG_YMM3D3	= 379,
    CV_REG_YMM4D0	= 380,
    CV_REG_YMM4D1	= 381,
    CV_REG_YMM4D2	= 382,
    CV_REG_YMM4D3	= 383,
    CV_REG_YMM5D0	= 384,
    CV_REG_YMM5D1	= 385,
    CV_REG_YMM5D2	= 386,
    CV_REG_YMM5D3	= 387,
    CV_REG_YMM6D0	= 388,
    CV_REG_YMM6D1	= 389,
    CV_REG_YMM6D2	= 390,
    CV_REG_YMM6D3	= 391,
    CV_REG_YMM7D0	= 392,
    CV_REG_YMM7D1	= 393,
    CV_REG_YMM7D2	= 394,
    CV_REG_YMM7D3	= 395,
    CV_REG_BND0		= 396,
    CV_REG_BND1		= 397,
    CV_REG_BND2		= 398,
    CV_REG_BND3		= 399,
    CV_REG_BNDCFGU	= 400,
    CV_REG_BNDSTATUS	= 401,

    CV_AMD64_AL		= 1,
    CV_AMD64_CL		= 2,
    CV_AMD64_DL		= 3,
    CV_AMD64_BL		= 4,
    CV_AMD64_AH		= 5,
    CV_AMD64_CH		= 6,
    CV_AMD64_DH		= 7,
    CV_AMD64_BH		= 8,
    CV_AMD64_AX		= 9,
    CV_AMD64_CX		= 10,
    CV_AMD64_DX		= 11,
    CV_AMD64_BX		= 12,
    CV_AMD64_SP		= 13,
    CV_AMD64_BP		= 14,
    CV_AMD64_SI		= 15,
    CV_AMD64_DI		= 16,
    CV_AMD64_EAX	= 17,
    CV_AMD64_ECX	= 18,
    CV_AMD64_EDX	= 19,
    CV_AMD64_EBX	= 20,
    CV_AMD64_ESP	= 21,
    CV_AMD64_EBP	= 22,
    CV_AMD64_ESI	= 23,
    CV_AMD64_EDI	= 24,
    CV_AMD64_ES		= 25,
    CV_AMD64_CS		= 26,
    CV_AMD64_SS		= 27,
    CV_AMD64_DS		= 28,
    CV_AMD64_FS		= 29,
    CV_AMD64_GS		= 30,
    CV_AMD64_FLAGS	= 32,
    CV_AMD64_RIP	= 33,
    CV_AMD64_EFLAGS	= 34,
    CV_AMD64_CR0	= 80,
    CV_AMD64_CR1	= 81,
    CV_AMD64_CR2	= 82,
    CV_AMD64_CR3	= 83,
    CV_AMD64_CR4	= 84,
    CV_AMD64_CR8	= 88,
    CV_AMD64_DR0	= 90,
    CV_AMD64_DR1	= 91,
    CV_AMD64_DR2	= 92,
    CV_AMD64_DR3	= 93,
    CV_AMD64_DR4	= 94,
    CV_AMD64_DR5	= 95,
    CV_AMD64_DR6	= 96,
    CV_AMD64_DR7	= 97,
    CV_AMD64_DR8	= 98,
    CV_AMD64_DR9	= 99,
    CV_AMD64_DR10	= 100,
    CV_AMD64_DR11	= 101,
    CV_AMD64_DR12	= 102,
    CV_AMD64_DR13	= 103,
    CV_AMD64_DR14	= 104,
    CV_AMD64_DR15	= 105,
    CV_AMD64_GDTR	= 110,
    CV_AMD64_GDTL	= 111,
    CV_AMD64_IDTR	= 112,
    CV_AMD64_IDTL	= 113,
    CV_AMD64_LDTR	= 114,
    CV_AMD64_TR		= 115,
    CV_AMD64_ST0	= 128,
    CV_AMD64_ST1	= 129,
    CV_AMD64_ST2	= 130,
    CV_AMD64_ST3	= 131,
    CV_AMD64_ST4	= 132,
    CV_AMD64_ST5	= 133,
    CV_AMD64_ST6	= 134,
    CV_AMD64_ST7	= 135,
    CV_AMD64_CTRL	= 136,
    CV_AMD64_STAT	= 137,
    CV_AMD64_TAG	= 138,
    CV_AMD64_FPIP	= 139,
    CV_AMD64_FPCS	= 140,
    CV_AMD64_FPDO	= 141,
    CV_AMD64_FPDS	= 142,
    CV_AMD64_ISEM	= 143,
    CV_AMD64_FPEIP	= 144,
    CV_AMD64_FPEDO	= 145,
    CV_AMD64_MM0	= 146,
    CV_AMD64_MM1	= 147,
    CV_AMD64_MM2	= 148,
    CV_AMD64_MM3	= 149,
    CV_AMD64_MM4	= 150,
    CV_AMD64_MM5	= 151,
    CV_AMD64_MM6	= 152,
    CV_AMD64_MM7	= 153,
    CV_AMD64_XMM0	= 154,
    CV_AMD64_XMM1	= 155,
    CV_AMD64_XMM2	= 156,
    CV_AMD64_XMM3	= 157,
    CV_AMD64_XMM4	= 158,
    CV_AMD64_XMM5	= 159,
    CV_AMD64_XMM6	= 160,
    CV_AMD64_XMM7	= 161,
    CV_AMD64_XMM0_0	= 162,
    CV_AMD64_XMM0_1	= 163,
    CV_AMD64_XMM0_2	= 164,
    CV_AMD64_XMM0_3	= 165,
    CV_AMD64_XMM1_0	= 166,
    CV_AMD64_XMM1_1	= 167,
    CV_AMD64_XMM1_2	= 168,
    CV_AMD64_XMM1_3	= 169,
    CV_AMD64_XMM2_0	= 170,
    CV_AMD64_XMM2_1	= 171,
    CV_AMD64_XMM2_2	= 172,
    CV_AMD64_XMM2_3	= 173,
    CV_AMD64_XMM3_0	= 174,
    CV_AMD64_XMM3_1	= 175,
    CV_AMD64_XMM3_2	= 176,
    CV_AMD64_XMM3_3	= 177,
    CV_AMD64_XMM4_0	= 178,
    CV_AMD64_XMM4_1	= 179,
    CV_AMD64_XMM4_2	= 180,
    CV_AMD64_XMM4_3	= 181,
    CV_AMD64_XMM5_0	= 182,
    CV_AMD64_XMM5_1	= 183,
    CV_AMD64_XMM5_2	= 184,
    CV_AMD64_XMM5_3	= 185,
    CV_AMD64_XMM6_0	= 186,
    CV_AMD64_XMM6_1	= 187,
    CV_AMD64_XMM6_2	= 188,
    CV_AMD64_XMM6_3	= 189,
    CV_AMD64_XMM7_0	= 190,
    CV_AMD64_XMM7_1	= 191,
    CV_AMD64_XMM7_2	= 192,
    CV_AMD64_XMM7_3	= 193,
    CV_AMD64_XMM0L	= 194,
    CV_AMD64_XMM1L	= 195,
    CV_AMD64_XMM2L	= 196,
    CV_AMD64_XMM3L	= 197,
    CV_AMD64_XMM4L	= 198,
    CV_AMD64_XMM5L	= 199,
    CV_AMD64_XMM6L	= 200,
    CV_AMD64_XMM7L	= 201,
    CV_AMD64_XMM0H	= 202,
    CV_AMD64_XMM1H	= 203,
    CV_AMD64_XMM2H	= 204,
    CV_AMD64_XMM3H	= 205,
    CV_AMD64_XMM4H	= 206,
    CV_AMD64_XMM5H	= 207,
    CV_AMD64_XMM6H	= 208,
    CV_AMD64_XMM7H	= 209,
    CV_AMD64_MXCSR	= 211,
    CV_AMD64_EMM0L	= 220,
    CV_AMD64_EMM1L	= 221,
    CV_AMD64_EMM2L	= 222,
    CV_AMD64_EMM3L	= 223,
    CV_AMD64_EMM4L	= 224,
    CV_AMD64_EMM5L	= 225,
    CV_AMD64_EMM6L	= 226,
    CV_AMD64_EMM7L	= 227,
    CV_AMD64_EMM0H	= 228,
    CV_AMD64_EMM1H	= 229,
    CV_AMD64_EMM2H	= 230,
    CV_AMD64_EMM3H	= 231,
    CV_AMD64_EMM4H	= 232,
    CV_AMD64_EMM5H	= 233,
    CV_AMD64_EMM6H	= 234,
    CV_AMD64_EMM7H	= 235,
    CV_AMD64_MM00	= 236,
    CV_AMD64_MM01	= 237,
    CV_AMD64_MM10	= 238,
    CV_AMD64_MM11	= 239,
    CV_AMD64_MM20	= 240,
    CV_AMD64_MM21	= 241,
    CV_AMD64_MM30	= 242,
    CV_AMD64_MM31	= 243,
    CV_AMD64_MM40	= 244,
    CV_AMD64_MM41	= 245,
    CV_AMD64_MM50	= 246,
    CV_AMD64_MM51	= 247,
    CV_AMD64_MM60	= 248,
    CV_AMD64_MM61	= 249,
    CV_AMD64_MM70	= 250,
    CV_AMD64_MM71	= 251,
    CV_AMD64_XMM8	= 252,
    CV_AMD64_XMM9	= 253,
    CV_AMD64_XMM10	= 254,
    CV_AMD64_XMM11	= 255,
    CV_AMD64_XMM12	= 256,
    CV_AMD64_XMM13	= 257,
    CV_AMD64_XMM14	= 258,
    CV_AMD64_XMM15	= 259,
    CV_AMD64_XMM8_0	= 260,
    CV_AMD64_XMM8_1	= 261,
    CV_AMD64_XMM8_2	= 262,
    CV_AMD64_XMM8_3	= 263,
    CV_AMD64_XMM9_0	= 264,
    CV_AMD64_XMM9_1	= 265,
    CV_AMD64_XMM9_2	= 266,
    CV_AMD64_XMM9_3	= 267,
    CV_AMD64_XMM10_0	= 268,
    CV_AMD64_XMM10_1	= 269,
    CV_AMD64_XMM10_2	= 270,
    CV_AMD64_XMM10_3	= 271,
    CV_AMD64_XMM11_0	= 272,
    CV_AMD64_XMM11_1	= 273,
    CV_AMD64_XMM11_2	= 274,
    CV_AMD64_XMM11_3	= 275,
    CV_AMD64_XMM12_0	= 276,
    CV_AMD64_XMM12_1	= 277,
    CV_AMD64_XMM12_2	= 278,
    CV_AMD64_XMM12_3	= 279,
    CV_AMD64_XMM13_0	= 280,
    CV_AMD64_XMM13_1	= 281,
    CV_AMD64_XMM13_2	= 282,
    CV_AMD64_XMM13_3	= 283,
    CV_AMD64_XMM14_0	= 284,
    CV_AMD64_XMM14_1	= 285,
    CV_AMD64_XMM14_2	= 286,
    CV_AMD64_XMM14_3	= 287,
    CV_AMD64_XMM15_0	= 288,
    CV_AMD64_XMM15_1	= 289,
    CV_AMD64_XMM15_2	= 290,
    CV_AMD64_XMM15_3	= 291,
    CV_AMD64_XMM8L	= 292,
    CV_AMD64_XMM9L	= 293,
    CV_AMD64_XMM10L	= 294,
    CV_AMD64_XMM11L	= 295,
    CV_AMD64_XMM12L	= 296,
    CV_AMD64_XMM13L	= 297,
    CV_AMD64_XMM14L	= 298,
    CV_AMD64_XMM15L	= 299,
    CV_AMD64_XMM8H	= 300,
    CV_AMD64_XMM9H	= 301,
    CV_AMD64_XMM10H	= 302,
    CV_AMD64_XMM11H	= 303,
    CV_AMD64_XMM12H	= 304,
    CV_AMD64_XMM13H	= 305,
    CV_AMD64_XMM14H	= 306,
    CV_AMD64_XMM15H	= 307,
    CV_AMD64_EMM8L	= 308,
    CV_AMD64_EMM9L	= 309,
    CV_AMD64_EMM10L	= 310,
    CV_AMD64_EMM11L	= 311,
    CV_AMD64_EMM12L	= 312,
    CV_AMD64_EMM13L	= 313,
    CV_AMD64_EMM14L	= 314,
    CV_AMD64_EMM15L	= 315,
    CV_AMD64_EMM8H	= 316,
    CV_AMD64_EMM9H	= 317,
    CV_AMD64_EMM10H	= 318,
    CV_AMD64_EMM11H	= 319,
    CV_AMD64_EMM12H	= 320,
    CV_AMD64_EMM13H	= 321,
    CV_AMD64_EMM14H	= 322,
    CV_AMD64_EMM15H	= 323,
    CV_AMD64_SIL	= 324,
    CV_AMD64_DIL	= 325,
    CV_AMD64_BPL	= 326,
    CV_AMD64_SPL	= 327,
    CV_AMD64_RAX	= 328,
    CV_AMD64_RBX	= 329,
    CV_AMD64_RCX	= 330,
    CV_AMD64_RDX	= 331,
    CV_AMD64_RSI	= 332,
    CV_AMD64_RDI	= 333,
    CV_AMD64_RBP	= 334,
    CV_AMD64_RSP	= 335,
    CV_AMD64_R8		= 336,
    CV_AMD64_R9		= 337,
    CV_AMD64_R10	= 338,
    CV_AMD64_R11	= 339,
    CV_AMD64_R12	= 340,
    CV_AMD64_R13	= 341,
    CV_AMD64_R14	= 342,
    CV_AMD64_R15	= 343,
    CV_AMD64_R8B	= 344,
    CV_AMD64_R9B	= 345,
    CV_AMD64_R10B	= 346,
    CV_AMD64_R11B	= 347,
    CV_AMD64_R12B	= 348,
    CV_AMD64_R13B	= 349,
    CV_AMD64_R14B	= 350,
    CV_AMD64_R15B	= 351,
    CV_AMD64_R8W	= 352,
    CV_AMD64_R9W	= 353,
    CV_AMD64_R10W	= 354,
    CV_AMD64_R11W	= 355,
    CV_AMD64_R12W	= 356,
    CV_AMD64_R13W	= 357,
    CV_AMD64_R14W	= 358,
    CV_AMD64_R15W	= 359,
    CV_AMD64_R8D	= 360,
    CV_AMD64_R9D	= 361,
    CV_AMD64_R10D	= 362,
    CV_AMD64_R11D	= 363,
    CV_AMD64_R12D	= 364,
    CV_AMD64_R13D	= 365,
    CV_AMD64_R14D	= 366,
    CV_AMD64_R15D	= 367,
    CV_AMD64_YMM0	= 368,
    CV_AMD64_YMM1	= 369,
    CV_AMD64_YMM2	= 370,
    CV_AMD64_YMM3	= 371,
    CV_AMD64_YMM4	= 372,
    CV_AMD64_YMM5	= 373,
    CV_AMD64_YMM6	= 374,
    CV_AMD64_YMM7	= 375,
    CV_AMD64_YMM8	= 376,
    CV_AMD64_YMM9	= 377,
    CV_AMD64_YMM10	= 378,
    CV_AMD64_YMM11	= 379,
    CV_AMD64_YMM12	= 380,
    CV_AMD64_YMM13	= 381,
    CV_AMD64_YMM14	= 382,
    CV_AMD64_YMM15	= 383,
    CV_AMD64_YMM0H	= 384,
    CV_AMD64_YMM1H	= 385,
    CV_AMD64_YMM2H	= 386,
    CV_AMD64_YMM3H	= 387,
    CV_AMD64_YMM4H	= 388,
    CV_AMD64_YMM5H	= 389,
    CV_AMD64_YMM6H	= 390,
    CV_AMD64_YMM7H	= 391,
    CV_AMD64_YMM8H	= 392,
    CV_AMD64_YMM9H	= 393,
    CV_AMD64_YMM10H	= 394,
    CV_AMD64_YMM11H	= 395,
    CV_AMD64_YMM12H	= 396,
    CV_AMD64_YMM13H	= 397,
    CV_AMD64_YMM14H	= 398,
    CV_AMD64_YMM15H	= 399,
    CV_AMD64_XMM0IL	= 400,
    CV_AMD64_XMM1IL	= 401,
    CV_AMD64_XMM2IL	= 402,
    CV_AMD64_XMM3IL	= 403,
    CV_AMD64_XMM4IL	= 404,
    CV_AMD64_XMM5IL	= 405,
    CV_AMD64_XMM6IL	= 406,
    CV_AMD64_XMM7IL	= 407,
    CV_AMD64_XMM8IL	= 408,
    CV_AMD64_XMM9IL	= 409,
    CV_AMD64_XMM10IL	= 410,
    CV_AMD64_XMM11IL	= 411,
    CV_AMD64_XMM12IL	= 412,
    CV_AMD64_XMM13IL	= 413,
    CV_AMD64_XMM14IL	= 414,
    CV_AMD64_XMM15IL	= 415,
    CV_AMD64_XMM0IH	= 416,
    CV_AMD64_XMM1IH	= 417,
    CV_AMD64_XMM2IH	= 418,
    CV_AMD64_XMM3IH	= 419,
    CV_AMD64_XMM4IH	= 420,
    CV_AMD64_XMM5IH	= 421,
    CV_AMD64_XMM6IH	= 422,
    CV_AMD64_XMM7IH	= 423,
    CV_AMD64_XMM8IH	= 424,
    CV_AMD64_XMM9IH	= 425,
    CV_AMD64_XMM10IH	= 426,
    CV_AMD64_XMM11IH	= 427,
    CV_AMD64_XMM12IH	= 428,
    CV_AMD64_XMM13IH	= 429,
    CV_AMD64_XMM14IH	= 430,
    CV_AMD64_XMM15IH	= 431,
    CV_AMD64_YMM0I0	= 432,
    CV_AMD64_YMM0I1	= 433,
    CV_AMD64_YMM0I2	= 434,
    CV_AMD64_YMM0I3	= 435,
    CV_AMD64_YMM1I0	= 436,
    CV_AMD64_YMM1I1	= 437,
    CV_AMD64_YMM1I2	= 438,
    CV_AMD64_YMM1I3	= 439,
    CV_AMD64_YMM2I0	= 440,
    CV_AMD64_YMM2I1	= 441,
    CV_AMD64_YMM2I2	= 442,
    CV_AMD64_YMM2I3	= 443,
    CV_AMD64_YMM3I0	= 444,
    CV_AMD64_YMM3I1	= 445,
    CV_AMD64_YMM3I2	= 446,
    CV_AMD64_YMM3I3	= 447,
    CV_AMD64_YMM4I0	= 448,
    CV_AMD64_YMM4I1	= 449,
    CV_AMD64_YMM4I2	= 450,
    CV_AMD64_YMM4I3	= 451,
    CV_AMD64_YMM5I0	= 452,
    CV_AMD64_YMM5I1	= 453,
    CV_AMD64_YMM5I2	= 454,
    CV_AMD64_YMM5I3	= 455,
    CV_AMD64_YMM6I0	= 456,
    CV_AMD64_YMM6I1	= 457,
    CV_AMD64_YMM6I2	= 458,
    CV_AMD64_YMM6I3	= 459,
    CV_AMD64_YMM7I0	= 460,
    CV_AMD64_YMM7I1	= 461,
    CV_AMD64_YMM7I2	= 462,
    CV_AMD64_YMM7I3	= 463,
    CV_AMD64_YMM8I0	= 464,
    CV_AMD64_YMM8I1	= 465,
    CV_AMD64_YMM8I2	= 466,
    CV_AMD64_YMM8I3	= 467,
    CV_AMD64_YMM9I0	= 468,
    CV_AMD64_YMM9I1	= 469,
    CV_AMD64_YMM9I2	= 470,
    CV_AMD64_YMM9I3	= 471,
    CV_AMD64_YMM10I0	= 472,
    CV_AMD64_YMM10I1	= 473,
    CV_AMD64_YMM10I2	= 474,
    CV_AMD64_YMM10I3	= 475,
    CV_AMD64_YMM11I0	= 476,
    CV_AMD64_YMM11I1	= 477,
    CV_AMD64_YMM11I2	= 478,
    CV_AMD64_YMM11I3	= 479,
    CV_AMD64_YMM12I0	= 480,
    CV_AMD64_YMM12I1	= 481,
    CV_AMD64_YMM12I2	= 482,
    CV_AMD64_YMM12I3	= 483,
    CV_AMD64_YMM13I0	= 484,
    CV_AMD64_YMM13I1	= 485,
    CV_AMD64_YMM13I2	= 486,
    CV_AMD64_YMM13I3	= 487,
    CV_AMD64_YMM14I0	= 488,
    CV_AMD64_YMM14I1	= 489,
    CV_AMD64_YMM14I2	= 490,
    CV_AMD64_YMM14I3	= 491,
    CV_AMD64_YMM15I0	= 492,
    CV_AMD64_YMM15I1	= 493,
    CV_AMD64_YMM15I2	= 494,
    CV_AMD64_YMM15I3	= 495,
    CV_AMD64_YMM0F0	= 496,
    CV_AMD64_YMM0F1	= 497,
    CV_AMD64_YMM0F2	= 498,
    CV_AMD64_YMM0F3	= 499,
    CV_AMD64_YMM0F4	= 500,
    CV_AMD64_YMM0F5	= 501,
    CV_AMD64_YMM0F6	= 502,
    CV_AMD64_YMM0F7	= 503,
    CV_AMD64_YMM1F0	= 504,
    CV_AMD64_YMM1F1	= 505,
    CV_AMD64_YMM1F2	= 506,
    CV_AMD64_YMM1F3	= 507,
    CV_AMD64_YMM1F4	= 508,
    CV_AMD64_YMM1F5	= 509,
    CV_AMD64_YMM1F6	= 510,
    CV_AMD64_YMM1F7	= 511,
    CV_AMD64_YMM2F0	= 512,
    CV_AMD64_YMM2F1	= 513,
    CV_AMD64_YMM2F2	= 514,
    CV_AMD64_YMM2F3	= 515,
    CV_AMD64_YMM2F4	= 516,
    CV_AMD64_YMM2F5	= 517,
    CV_AMD64_YMM2F6	= 518,
    CV_AMD64_YMM2F7	= 519,
    CV_AMD64_YMM3F0	= 520,
    CV_AMD64_YMM3F1	= 521,
    CV_AMD64_YMM3F2	= 522,
    CV_AMD64_YMM3F3	= 523,
    CV_AMD64_YMM3F4	= 524,
    CV_AMD64_YMM3F5	= 525,
    CV_AMD64_YMM3F6	= 526,
    CV_AMD64_YMM3F7	= 527,
    CV_AMD64_YMM4F0	= 528,
    CV_AMD64_YMM4F1	= 529,
    CV_AMD64_YMM4F2	= 530,
    CV_AMD64_YMM4F3	= 531,
    CV_AMD64_YMM4F4	= 532,
    CV_AMD64_YMM4F5	= 533,
    CV_AMD64_YMM4F6	= 534,
    CV_AMD64_YMM4F7	= 535,
    CV_AMD64_YMM5F0	= 536,
    CV_AMD64_YMM5F1	= 537,
    CV_AMD64_YMM5F2	= 538,
    CV_AMD64_YMM5F3	= 539,
    CV_AMD64_YMM5F4	= 540,
    CV_AMD64_YMM5F5	= 541,
    CV_AMD64_YMM5F6	= 542,
    CV_AMD64_YMM5F7	= 543,
    CV_AMD64_YMM6F0	= 544,
    CV_AMD64_YMM6F1	= 545,
    CV_AMD64_YMM6F2	= 546,
    CV_AMD64_YMM6F3	= 547,
    CV_AMD64_YMM6F4	= 548,
    CV_AMD64_YMM6F5	= 549,
    CV_AMD64_YMM6F6	= 550,
    CV_AMD64_YMM6F7	= 551,
    CV_AMD64_YMM7F0	= 552,
    CV_AMD64_YMM7F1	= 553,
    CV_AMD64_YMM7F2	= 554,
    CV_AMD64_YMM7F3	= 555,
    CV_AMD64_YMM7F4	= 556,
    CV_AMD64_YMM7F5	= 557,
    CV_AMD64_YMM7F6	= 558,
    CV_AMD64_YMM7F7	= 559,
    CV_AMD64_YMM8F0	= 560,
    CV_AMD64_YMM8F1	= 561,
    CV_AMD64_YMM8F2	= 562,
    CV_AMD64_YMM8F3	= 563,
    CV_AMD64_YMM8F4	= 564,
    CV_AMD64_YMM8F5	= 565,
    CV_AMD64_YMM8F6	= 566,
    CV_AMD64_YMM8F7	= 567,
    CV_AMD64_YMM9F0	= 568,
    CV_AMD64_YMM9F1	= 569,
    CV_AMD64_YMM9F2	= 570,
    CV_AMD64_YMM9F3	= 571,
    CV_AMD64_YMM9F4	= 572,
    CV_AMD64_YMM9F5	= 573,
    CV_AMD64_YMM9F6	= 574,
    CV_AMD64_YMM9F7	= 575,
    CV_AMD64_YMM10F0	= 576,
    CV_AMD64_YMM10F1	= 577,
    CV_AMD64_YMM10F2	= 578,
    CV_AMD64_YMM10F3	= 579,
    CV_AMD64_YMM10F4	= 580,
    CV_AMD64_YMM10F5	= 581,
    CV_AMD64_YMM10F6	= 582,
    CV_AMD64_YMM10F7	= 583,
    CV_AMD64_YMM11F0	= 584,
    CV_AMD64_YMM11F1	= 585,
    CV_AMD64_YMM11F2	= 586,
    CV_AMD64_YMM11F3	= 587,
    CV_AMD64_YMM11F4	= 588,
    CV_AMD64_YMM11F5	= 589,
    CV_AMD64_YMM11F6	= 590,
    CV_AMD64_YMM11F7	= 591,
    CV_AMD64_YMM12F0	= 592,
    CV_AMD64_YMM12F1	= 593,
    CV_AMD64_YMM12F2	= 594,
    CV_AMD64_YMM12F3	= 595,
    CV_AMD64_YMM12F4	= 596,
    CV_AMD64_YMM12F5	= 597,
    CV_AMD64_YMM12F6	= 598,
    CV_AMD64_YMM12F7	= 599,
    CV_AMD64_YMM13F0	= 600,
    CV_AMD64_YMM13F1	= 601,
    CV_AMD64_YMM13F2	= 602,
    CV_AMD64_YMM13F3	= 603,
    CV_AMD64_YMM13F4	= 604,
    CV_AMD64_YMM13F5	= 605,
    CV_AMD64_YMM13F6	= 606,
    CV_AMD64_YMM13F7	= 607,
    CV_AMD64_YMM14F0	= 608,
    CV_AMD64_YMM14F1	= 609,
    CV_AMD64_YMM14F2	= 610,
    CV_AMD64_YMM14F3	= 611,
    CV_AMD64_YMM14F4	= 612,
    CV_AMD64_YMM14F5	= 613,
    CV_AMD64_YMM14F6	= 614,
    CV_AMD64_YMM14F7	= 615,
    CV_AMD64_YMM15F0	= 616,
    CV_AMD64_YMM15F1	= 617,
    CV_AMD64_YMM15F2	= 618,
    CV_AMD64_YMM15F3	= 619,
    CV_AMD64_YMM15F4	= 620,
    CV_AMD64_YMM15F5	= 621,
    CV_AMD64_YMM15F6	= 622,
    CV_AMD64_YMM15F7	= 623,
    CV_AMD64_YMM0D0	= 624,
    CV_AMD64_YMM0D1	= 625,
    CV_AMD64_YMM0D2	= 626,
    CV_AMD64_YMM0D3	= 627,
    CV_AMD64_YMM1D0	= 628,
    CV_AMD64_YMM1D1	= 629,
    CV_AMD64_YMM1D2	= 630,
    CV_AMD64_YMM1D3	= 631,
    CV_AMD64_YMM2D0	= 632,
    CV_AMD64_YMM2D1	= 633,
    CV_AMD64_YMM2D2	= 634,
    CV_AMD64_YMM2D3	= 635,
    CV_AMD64_YMM3D0	= 636,
    CV_AMD64_YMM3D1	= 637,
    CV_AMD64_YMM3D2	= 638,
    CV_AMD64_YMM3D3	= 639,
    CV_AMD64_YMM4D0	= 640,
    CV_AMD64_YMM4D1	= 641,
    CV_AMD64_YMM4D2	= 642,
    CV_AMD64_YMM4D3	= 643,
    CV_AMD64_YMM5D0	= 644,
    CV_AMD64_YMM5D1	= 645,
    CV_AMD64_YMM5D2	= 646,
    CV_AMD64_YMM5D3	= 647,
    CV_AMD64_YMM6D0	= 648,
    CV_AMD64_YMM6D1	= 649,
    CV_AMD64_YMM6D2	= 650,
    CV_AMD64_YMM6D3	= 651,
    CV_AMD64_YMM7D0	= 652,
    CV_AMD64_YMM7D1	= 653,
    CV_AMD64_YMM7D2	= 654,
    CV_AMD64_YMM7D3	= 655,
    CV_AMD64_YMM8D0	= 656,
    CV_AMD64_YMM8D1	= 657,
    CV_AMD64_YMM8D2	= 658,
    CV_AMD64_YMM8D3	= 659,
    CV_AMD64_YMM9D0	= 660,
    CV_AMD64_YMM9D1	= 661,
    CV_AMD64_YMM9D2	= 662,
    CV_AMD64_YMM9D3	= 663,
    CV_AMD64_YMM10D0	= 664,
    CV_AMD64_YMM10D1	= 665,
    CV_AMD64_YMM10D2	= 666,
    CV_AMD64_YMM10D3	= 667,
    CV_AMD64_YMM11D0	= 668,
    CV_AMD64_YMM11D1	= 669,
    CV_AMD64_YMM11D2	= 670,
    CV_AMD64_YMM11D3	= 671,
    CV_AMD64_YMM12D0	= 672,
    CV_AMD64_YMM12D1	= 673,
    CV_AMD64_YMM12D2	= 674,
    CV_AMD64_YMM12D3	= 675,
    CV_AMD64_YMM13D0	= 676,
    CV_AMD64_YMM13D1	= 677,
    CV_AMD64_YMM13D2	= 678,
    CV_AMD64_YMM13D3	= 679,
    CV_AMD64_YMM14D0	= 680,
    CV_AMD64_YMM14D1	= 681,
    CV_AMD64_YMM14D2	= 682,
    CV_AMD64_YMM14D3	= 683,
    CV_AMD64_YMM15D0	= 684,
    CV_AMD64_YMM15D1	= 685,
    CV_AMD64_YMM15D2	= 686,
    CV_AMD64_YMM15D3	= 687,
    CV_AMD64_BND0	= 688,
    CV_AMD64_BND1	= 689,
    CV_AMD64_BND2	= 690,
    CV_AMD64_BND3	= 691,
    CV_AMD64_BNDCFGU	= 692,
    CV_AMD64_BNDSTATUS	= 693
    }


.enum CV_access_e {
    CV_private		= 1,
    CV_protected	= 2,
    CV_public		= 3
    }


; subfield record for non-static data members

.template CV_MEMBER_16t
    leaf	dw ?		; LF_MEMBER_16t
    index	CV_typ16_t ?	; index of type record for field
    attr	CV_fldattr_t ?	; attribute mask
    offs	db CV_ZEROLEN dup(?)
   .ends

.template CV_MEMBER
    leaf	dw ?		; LF_MEMBER
    attr	CV_fldattr_t ?
    index	CV_typ_t ?
    offs	db CV_ZEROLEN dup(?)
   .ends

.template DATASYM32_16t
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_LDATA32_16t, S_GDATA32_16t or S_PUB32_16t
    off		CV_uoff32_t ?
    _seg	dw ?
    typind	CV_typ16_t ?	; Type index
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template DATASYM32
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_LDATA32, S_GDATA32, S_LMANDATA, S_GMANDATA
    typind	CV_typ_t ?	; Type index, or Metadata token if a managed symbol
    off		CV_uoff32_t ?
    _seg	dw ?
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template REGREL32_16t
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_REGREL32_16t
    off		CV_uoff32_t ?	; offset of symbol
    reg		dw ?		; register index for symbol
    typind	CV_typ16_t ?	; Type index
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template REGREL32
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_REGREL32
    off		CV_uoff32_t ?	; offset of symbol
    typind	CV_typ_t ?	; Type index or metadata token
    reg		dw ?		; register index for symbol
    name	db 1 dup(?)	; Length-prefixed name
   .ends


.template REGSYM_16t
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_REGISTER_16t
    typind	CV_typ16_t ?	; Type index
    reg		dw ?		; register enumerate
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template REGSYM
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_REGISTER
    typind	CV_typ_t ?	; Type index or Metadata token
    reg		dw ?		; register enumerate
    name	db 1 dup(?)	; Length-prefixed name
   .ends


.template BPRELSYM32_16t
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_BPREL32_16t
    off		CV_off32_t ?	; BP-relative offset
    typind	CV_typ16_t ?	; Type index
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template BPRELSYM32
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_BPREL32
    off		CV_off32_t ?	; BP-relative offset
    typind	CV_typ_t ?	; Type index or Metadata token
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template BPRELSYM16
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_BPREL16
    off		CV_off16_t ?	; BP-relative offset
    typind	CV_typ16_t ?	; Type index
    name	db 1 dup(?)	; Length-prefixed name
   .ends


; enum describing function return method

.enum cv_proc_flags {
    CV_PROCF_FPO	= 0x01,
    CV_PROCF_INTERRUPT	= 0x02,
    CV_PROCF_FAR	= 0x04,
    CV_PROCF_NEVER	= 0x08,
    }

.enum CV_PROCFLAGS : BYTE {
    CV_PFLAG_bAll	= 0xFF,
    CV_PFLAG_grfAll	= 0xFF,
    CV_PFLAG_NOFPO	= 0x01, ; frame pointer present
    CV_PFLAG_INT	= 0x02, ; interrupt return
    CV_PFLAG_FAR	= 0x04, ; far return
    CV_PFLAG_NEVER	= 0x08, ; function does not return
    CV_PFLAG_NOTREACHED = 0x10, ; label isn't fallen into
    CV_PFLAG_CUST_CALL	= 0x20, ; custom calling convention
    CV_PFLAG_NOINLINE	= 0x40, ; function marked as noinline
    CV_PFLAG_OPTDBGINFO = 0x80	; function has debug information for optimized code
    }


.template LABELSYM16
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_LABEL16
    off		CV_uoff16_t ?	; offset of symbol
    _seg	dw ?		; segment of symbol
    flags	CV_PROCFLAGS ?	; flags
    name	db 1 dup(?)	; Length-prefixed name
   .ends


.template PROCSYM
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_GPROC16 or S_LPROC16
    pParent	dd ?		; pointer to the parent
    pEnd	dd ?		; pointer to this blocks end
    pNext	dd ?		; pointer to next symbol
   .ends

.template PROCSYM16
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_GPROC16 or S_LPROC16
    pParent	dd ?		; pointer to the parent
    pEnd	dd ?		; pointer to this blocks end
    pNext	dd ?		; pointer to next symbol
    len		dw ?		; Proc length
    DbgStart	dw ?		; Debug start offset
    DbgEnd	dw ?		; Debug end offset
    off		CV_uoff16_t ?	; offset of symbol
    _seg	dw ?		; segment of symbol
    typind	CV_typ16_t ?	; Type index
    flags	CV_PROCFLAGS ?	; Proc flags
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template PROCSYM32_16t
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_GPROC32_16t or S_LPROC32_16t
    pParent	dd ?		; pointer to the parent
    pEnd	dd ?		; pointer to this blocks end
    pNext	dd ?		; pointer to next symbol
    len		dd ?		; Proc length
    DbgStart	dd ?		; Debug start offset
    DbgEnd	dd ?		; Debug end offset
    off		CV_uoff32_t ?
    _seg	dw ?
    typind	CV_typ16_t ?	; Type index
    flags	CV_PROCFLAGS ?	; Proc flags
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template PROCSYM32
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_GPROC32, S_LPROC32, S_GPROC32_ID, S_LPROC32_ID, S_LPROC32_DPC or S_LPROC32_DPC_ID
    pParent	dd ?		; pointer to the parent
    pEnd	dd ?		; pointer to this blocks end
    pNext	dd ?		; pointer to next symbol
    len		dd ?		; Proc length
    DbgStart	dd ?		; Debug start offset
    DbgEnd	dd ?		; Debug end offset
    typind	CV_typ_t ?	; Type index or ID
    off		CV_uoff32_t ?
    _seg	dw ?
    flags	CV_PROCFLAGS ?	; Proc flags
    name	db 1 dup(?)	; Length-prefixed name
   .ends


.template LABELSYM32
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_LABEL32
    off		CV_uoff32_t ?
    _seg	dw ?
    flags	CV_PROCFLAGS ?	; flags
    name	db 1 dup(?)	; Length-prefixed name
   .ends


.template UDTSYM_16t
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_UDT_16t | S_COBOLUDT_16t
    typind	CV_typ16_t ?	; Type index
    name	db 1 dup(?)	; Length-prefixed name
   .ends


.template UDTSYM
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_UDT | S_COBOLUDT
    typind	CV_typ_t ?	; Type index
    name	db 1 dup(?)	; Length-prefixed name
   .ends

.template CONSTSYM_16t
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_CONSTANT_16t
    typind	CV_typ16_t ?	; Type index (containing enum if enumerate)
    value	dw ?		; numeric leaf containing value
    name	db CV_ZEROLEN dup(?)
   .ends

.template CONSTSYM
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_CONSTANT or S_MANCONSTANT
    typind	CV_typ_t ?	; Type index (containing enum if enumerate) or metadata token
    value	dw ?		; numeric leaf containing value
    name	db CV_ZEROLEN dup(?)
   .ends


.enum cv_ambient_model {
    CV_AMB_NEAR		= 0,
    CV_AMB_FAR		= 1,
    CV_AMB_HUGE		= 2,
    }

.template CFLAGSYM
    reclen		dw ?		; Record length
    rectyp		dw ?		; S_COMPILE
    machine		db ?		; target processor
    language		db ?		; language index
    record flags
     pcode		dw : 1 ?	; true if pcode present
     floatprec		dw : 2 ?	; floating precision
     floatpkg		dw : 2 ?	; float package
     ambdata		dw : 3 ?	; ambient data model
     ambcode		dw : 3 ?	; ambient code model
     mode32		dw : 1 ?	; true if compiled 32 bit mode
     pad		dw : 4 ?	; reserved
    ends
    ver			db 1 dup(?)	; Length-prefixed compiler version string
   .ends


.template COMPILESYM
    reclen		dw ?		; Record length
    rectyp		dw ?		; S_COMPILE2
    record flags
     iLanguage		dd :  8 ?	; language index
     fEC		dd :  1 ?	; compiled for E/C
     fNoDbgInfo		dd :  1 ?	; not compiled with debug info
     fLTCG		dd :  1 ?	; compiled with LTCG
     fNoDataAlign	dd :  1 ?	; compiled with -Bzalign
     fManagedPresent	dd :  1 ?	; managed code/data present
     fSecurityChecks	dd :  1 ?	; compiled with /GS
     fHotPatch		dd :  1 ?	; compiled with /hotpatch
     fCVTCIL		dd :  1 ?	; converted with CVTCIL
     fMSILModule	dd :  1 ?	; MSIL netmodule
     pad		dd : 15 ?	; reserved, must be 0
    ends
    machine		dw ?		; target processor
    verFEMajor		dw ?		; front end major version #
    verFEMinor		dw ?		; front end minor version #
    verFEBuild		dw ?		; front end build version #
    verMajor		dw ?		; back end major version #
    verMinor		dw ?		; back end minor version #
    verBuild		dw ?		; back end build version #
    verSt		db 1 dup(?)
   .ends


.template COMPILESYM3
    reclen		dw ?		; Record length
    rectyp		dw ?		; S_COMPILE2
    record flags
     iLanguage		dd :  8 ?	; language index
     fEC		dd :  1 ?	; compiled for E/C
     fNoDbgInfo		dd :  1 ?	; not compiled with debug info
     fLTCG		dd :  1 ?	; compiled with LTCG
     fNoDataAlign	dd :  1 ?	; compiled with -Bzalign
     fManagedPresent	dd :  1 ?	; managed code/data present
     fSecurityChecks	dd :  1 ?	; compiled with /GS
     fHotPatch		dd :  1 ?	; compiled with /hotpatch
     fCVTCIL		dd :  1 ?	; converted with CVTCIL
     fMSILModule	dd :  1 ?	; MSIL netmodule
     fSdl		dd :  1 ?	; compiled with /sdl
     fPGO		dd :  1 ?	; compiled with /ltcg:pgo or pgu
     fExp		dd :  1 ?	; .exp module
     pad		dd : 12 ?	; reserved, must be 0
    ends
    machine		dw ?		; target processor
    verFEMajor		dw ?		; front end major version
    verFEMinor		dw ?		; front end minor version
    verFEBuild		dw ?		; front end build version
    verFEQFE		dw ?		; front end QFE version
    verMajor		dw ?		; back end major version
    verMinor		dw ?		; back end minor version
    verBuild		dw ?		; back end build version
    verQFE		dw ?		; back end QFE version
    verSz		db 1 dup(?)	; Zero terminated compiler version string
   .ends


.template ENVBLOCKSYM
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_ENVBLOCK
    flags	db ?
    rgsz	db 1 dup(?)	; Sequence of zero-terminated strings
   .ends


.template OBJNAMESYM
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_OBJNAME
    signature	dd ?		; signature
    name	db 1 dup(?)	; Length-prefixed name
   .ends


.template ENDARGSYM
    reclen	dw ?		; Record length
    rectyp	dw ?		; S_ENDARG
   .ends



.enum DEBUG_S_SUBSECTION_TYPE {
    DEBUG_S_IGNORE	= 0x80000000,
    DEBUG_S_SYMBOLS	= 0xf1,
    DEBUG_S_LINES,
    DEBUG_S_STRINGTABLE,
    DEBUG_S_FILECHKSMS,
    DEBUG_S_FRAMEDATA,
    DEBUG_S_INLINEELINES,
    DEBUG_S_CROSSSCOPEIMPORTS,
    DEBUG_S_CROSSSCOPEEXPORTS,
    DEBUG_S_IL_LINES,
    DEBUG_S_FUNC_MDTOKEN_MAP,
    DEBUG_S_TYPE_MDTOKEN_MAP,
    DEBUG_S_MERGED_ASSEMBLYINPUT,
    DEBUG_S_COFF_SYMBOL_RVA,
    }

.template CV_DebugSSubsectionHeader_t
    type	DEBUG_S_SUBSECTION_TYPE ?
    cbLen	CV_off32_t ?
   .ends

.template CV_DebugSLinesHeader_t
    offCon	CV_off32_t ?
    segCon	dw ?
    flags	dw ?
    cbCon	CV_off32_t ?
   .ends

.template CV_DebugSLinesFileBlockHeader_t
    offFile	CV_off32_t ?
    nLines	CV_off32_t ?
    cbBlock	CV_off32_t ?
   .ends


define CV_LINES_HAVE_COLUMNS 0x0001

.template CV_Line_t
    offs		dd ?		; Offset to start of code bytes for line number
    record flags
     linenumStart	dd :24 ?	; line where statement/expression starts
     deltaLineEnd	dd : 7 ?	; delta to line where statement ends (optional)
     fStatement		dd : 1 ?	; true if a statement linenumber, else an expression line num
    ends
   .ends

CV_columnpos_t		typedef WORD

.template CV_Column_t
    offColumnStart	CV_columnpos_t ?
    offColumnEnd	CV_columnpos_t ?
   .ends

.template FRAMEPROCSYM
    reclen		dw ?		; Record length
    rectyp		dw ?		; S_FRAMEPROC
    cbFrame		dd ?		; count of bytes of total frame of procedure
    cbPad		dd ?		; count of bytes of padding in the frame
    offPad		dd ?		; offset (relative to frame poniter) to where padding starts
    cbSaveRegs		dd ?		; count of bytes of callee save registers
    offExHdlr		dd ?		; offset of exception handler
    sectExHdlr		dw ?		; section id of exception handler
    record flags
     fHasAlloca		dd : 1 ?	; function uses _alloca()
     fHasSetJmp		dd : 1 ?	; function uses setjmp()
     fHasLongJmp	dd : 1 ?	; function uses longjmp()
     fHasInlAsm		dd : 1 ?	; function uses inline asm
     fHasEH		dd : 1 ?	; function has EH states
     fInlSpec		dd : 1 ?	; function was speced as inline
     fHasSEH		dd : 1 ?	; function has SEH
     fNaked		dd : 1 ?	; function is __declspec(naked)
     fSecurityChecks	dd : 1 ?	; function has buffer security check introduced by /GS.
     fAsyncEH		dd : 1 ?	; function compiled with /EHa
     fGSNoStackOrdering dd : 1 ?	; function has /GS buffer checks, but stack ordering couldn't be done
     fWasInlined	dd : 1 ?	; function was inlined within another function
     fGSCheck		dd : 1 ?	; function is __declspec(strict_gs_check)
     fSafeBuffers	dd : 1 ?	; function is __declspec(safebuffers)
     encodedLocalBasePointer dd : 2 ?	; record function's local pointer explicitly.
     encodedParamBasePointer dd : 2 ?	; record function's parameter pointer explicitly.
     fPogoOn		dd : 1 ?	; function was compiled with PGO/PGU
     fValidCounts	dd : 1 ?	; Do we have valid Pogo counts?
     fOptSpeed		dd : 1 ?	; Did we optimize for speed?
     fGuardCF		dd : 1 ?	; function contains CFG checks (and no write checks)
     fGuardCFW		dd : 1 ?	; function contains CFW checks and/or instrumentation
     pad		dd : 9 ?	; must be zero
    ends
   .ends

.pragma pack(pop)

endif
