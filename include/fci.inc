ifndef _WINDEF_
 include windef.inc
endif
ifndef INCLUDED_TYPES_FCI_FDI
INCLUDED_TYPES_FCI_FDI	equ <>
.pragma list(push, 0)

ifndef DIAMONDAPI
DIAMONDAPI equ <__cdecl>
endif

ifndef _WIN64
;include pshpack4.inc
endif

ifndef _INC_WINDOWS
ifndef _WINDOWS_
BOOL			typedef SDWORD
;BYTE			typedef BYTE
UINT			typedef DWORD
USHORT			typedef WORD
ULONG			typedef DWORD
endif
endif

CHECKSUM		typedef DWORD
UOFF			typedef DWORD
COFF			typedef DWORD

ifndef TRUE
TRUE			equ 1
endif
ifndef FALSE
FALSE			equ 0
endif
ifndef NULL
NULL			equ 0
endif

ERF			STRUC
erfOper			SINT ?
erfType			SINT ?
fError			BOOL ?
ERF			ENDS
PERF			typedef ptr ERF

CB_MAX_CHUNK		equ 32768
CB_MAX_DISK		equ 0x7fffffff
CB_MAX_FILENAME		equ 256
CB_MAX_CABINET_NAME	equ 256
CB_MAX_CAB_PATH		equ 256
CB_MAX_DISK_NAME	equ 256

TCOMP			typedef WORD

tcompMASK_TYPE		equ 0x000F
tcompTYPE_NONE		equ 0x0000
tcompTYPE_MSZIP		equ 0x0001
tcompTYPE_QUANTUM	equ 0x0002
tcompTYPE_LZX		equ 0x0003
tcompBAD		equ 0x000F

tcompMASK_LZX_WINDOW	equ 0x1F00
tcompLZX_WINDOW_LO	equ 0x0F00
tcompLZX_WINDOW_HI	equ 0x1500
tcompSHIFT_LZX_WINDOW	equ 8

tcompMASK_QUANTUM_LEVEL equ 0x00F0
tcompQUANTUM_LEVEL_LO	equ 0x0010
tcompQUANTUM_LEVEL_HI	equ 0x0070
tcompSHIFT_QUANTUM_LEVEL equ 4

tcompMASK_QUANTUM_MEM	equ 0x1F00
tcompQUANTUM_MEM_LO	equ 0x0A00
tcompQUANTUM_MEM_HI	equ 0x1500
tcompSHIFT_QUANTUM_MEM	equ 8

tcompMASK_RESERVED	equ 0xE000

CompressionTypeFromTCOMP macro tc
	exitm<((tc) AND tcompMASK_TYPE)>
	endm

CompressionLevelFromTCOMP macro tc
	exitm<(((tc) AND tcompMASK_QUANTUM_LEVEL) SHR tcompSHIFT_QUANTUM_LEVEL)>
	endm

CompressionMemoryFromTCOMP macro tc
	exitm<(((tc) AND tcompMASK_QUANTUM_MEM) SHR tcompSHIFT_QUANTUM_MEM)>
	endm

TCOMPfromTypeLevelMemory macro t,l,m
	exitm<(((m) SHL tcompSHIFT_QUANTUM_MEM	) OR ((l) SHL tcompSHIFT_QUANTUM_LEVEL) OR (t))>
	endm

LZXCompressionWindowFromTCOMP macro tc
	exitm<(((tc) OR tcompMASK_LZX_WINDOW) SHR tcompSHIFT_LZX_WINDOW)>
	endm

TCOMPfromLZXWindow macro w
	exitm<(((w) SHL tcompSHIFT_LZX_WINDOW ) OR (tcompTYPE_LZX ))>
	endm

ifndef _WIN64
;include poppack.inc
endif

endif ;; NOT INCLUDED_TYPES_FCI_FDI

ifndef INCLUDED_FCI
INCLUDED_FCI equ <>

include specstrings.inc
include basetsd.inc

ifndef _WIN64
;include pshpack4.inc
endif

FCIERR_NONE		equ 0
FCIERR_OPEN_SRC		equ 1
FCIERR_READ_SRC		equ 2
FCIERR_ALLOC_FAIL	equ 3
FCIERR_TEMP_FILE	equ 4
FCIERR_BAD_COMPR_TYPE	equ 5
FCIERR_CAB_FILE		equ 6
FCIERR_USER_ABORT	equ 7
FCIERR_MCI_FAIL		equ 8
FCIERR_CAB_FORMAT_LIMIT equ 9

ifndef _A_NAME_IS_UTF
_A_NAME_IS_UTF		equ 0x80
endif
ifndef _A_EXEC
_A_EXEC			equ 0x40
endif

HFCI			typedef ptr
CCAB			STRUC
cb			ULONG ?
cbFolderThresh		ULONG ?
cbReserveCFHeader	UINT ?
cbReserveCFFolder	UINT ?
cbReserveCFData		UINT ?
iCab			SINT ?
iDisk			SINT ?
ifndef REMOVE_CHICAGO_M6_HACK
fFailOnIncompressible	SINT ?
endif
setID			USHORT ?
szDisk			db CB_MAX_DISK_NAME dup(?)
szCab			db CB_MAX_CABINET_NAME dup(?)
szCabPath		db CB_MAX_CAB_PATH dup(?)
CCAB			ENDS
PCCAB			typedef ptr CCAB


CALLBACK(PFNFCIALLOC, :ULONG)
FNFCIALLOC macro fn
	exitm<CALLBACK(fn, :ULONG)>
	endm

CALLBACK(PFNFCIFREE, :ptr)
FNFCIFREE macro fn
	exitm<CALLBACK(fn, :ptr)>
	endm


;;** File I/O functions for FCI
CALLBACK(PFNFCIOPEN, :LPSTR, :SINT, :SINT, :ptr, :ptr)
CALLBACK(PFNFCIREAD, :INT_PTR, :ptr, :UINT, :ptr, :ptr)
CALLBACK(PFNFCIWRITE, :INT_PTR, :ptr, :UINT, :ptr, :ptr)
CALLBACK(PFNFCICLOSE, :INT_PTR, :ptr, :ptr)
CALLBACK(PFNFCISEEK, :INT_PTR, :LONG, :SINT, :ptr, :ptr)
CALLBACK(PFNFCIDELETE, :LPSTR, :ptr, :ptr)

FNFCIOPEN macro fn
	exitm<CALLBACK(fn, :LPSTR, :SINT, :SINT, :ptr, :ptr)>
	endm
FNFCIREAD macro fn
	exitm<CALLBACK(fn, :INT_PTR, :ptr, :UINT, :ptr, :ptr)>
	endm
FNFCIWRITE macro fn
	exitm<CALLBACK(fn, :INT_PTR, :ptr, :UINT, :ptr, :ptr)>
	endm
FNFCICLOSE macro fn
	exitm<CALLBACK(fn, :INT_PTR, :ptr, :ptr)>
	endm
FNFCISEEK macro fn
	exitm<CALLBACK(fn, :INT_PTR, :LONG, :SINT, :ptr, :ptr)>
	endm
FNFCIDELETE macro fn
	exitm<CALLBACK(fn, :LPSTR, :ptr, :ptr)>
	endm


CALLBACK(PFNFCIGETNEXTCABINET, :PCCAB, :ULONG, :ptr)
FNFCIGETNEXTCABINET macro fn
	exitm<CALLBACK(fn, :PCCAB, :ULONG, :ptr)>
	endm

CALLBACK(PFNFCIFILEPLACED, :PCCAB, :LPSTR, :LONG, :BOOL, :ptr)
FNFCIFILEPLACED macro fn
	exitm<CALLBACK(fn, :PCCAB, :LPSTR, :LONG, :BOOL, :ptr)>
	endm

ifndef LPUSHORT
LPUSHORT typedef ptr WORD
endif

CALLBACK(PFNFCIGETOPENINFO, :LPSTR, :LPUSHORT, :LPUSHORT, :LPUSHORT, :ptr, :ptr)
FNFCIGETOPENINFO macro fn
	exitm<CALLBACK(fn, :LPSTR, :LPUSHORT, :LPUSHORT, :LPUSHORT, :ptr, :ptr)>
	endm

statusFile		equ 0	;; Add File to Folder callback
statusFolder		equ 1	;; Add Folder to Cabinet callback
statusCabinet		equ 2	;; Write out a completed cabinet callback

CALLBACK(PFNFCISTATUS, :UINT, :ULONG, :ULONG, :ptr)
FNFCISTATUS macro fn
	exitm<CALLBACK(fn, :UINT, :ULONG, :ULONG, :ptr)>
	endm

CALLBACK(PFNFCIGETTEMPFILE, :LPSTR, :SINT, :ptr)
FNFCIGETTEMPFILE macro fn
	exitm<CALLBACK(fn, :LPSTR, :SINT, :ptr)>
	endm

;HFCI DIAMONDAPI
FCICreate proto WINAPI \
			perf: PERF,
		    pfnfcifp: PFNFCIFILEPLACED,
			pfna: PFNFCIALLOC,
			pfnf: PFNFCIFREE,
		     pfnopen: PFNFCIOPEN,
		     pfnread: PFNFCIREAD,
		    pfnwrite: PFNFCIWRITE,
		    pfnclose: PFNFCICLOSE,
		     pfnseek: PFNFCISEEK,
		   pfndelete: PFNFCIDELETE,
		   pfnfcigtf: PFNFCIGETTEMPFILE,
		       pccab: PCCAB,
			  pv: ptr


;BOOL
FCIAddFile proto WINAPI \
			hfci: HFCI,
	       pszSourceFile: LPSTR,
		 pszFileName: LPSTR,
		    fExecute: BOOL,
		   pfnfcignc: PFNFCIGETNEXTCABINET,
		     pfnfcis: PFNFCISTATUS,
		   pfnfcigoi: PFNFCIGETOPENINFO,
		typeCompress: TCOMP

;BOOL
FCIFlushCabinet proto WINAPI \
			hfci: HFCI,
		 fGetNextCab: BOOL,
		   pfnfcignc: PFNFCIGETNEXTCABINET,
		     pfnfcis: PFNFCISTATUS

;BOOL
FCIFlushFolder proto WINAPI \
			hfci: HFCI,
		   pfnfcignc: PFNFCIGETNEXTCABINET,
		     pfnfcis: PFNFCISTATUS

;BOOL
FCIDestroy proto WINAPI hfci:HFCI

.pragma list(pop)
endif
