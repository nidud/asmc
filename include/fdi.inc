ifndef _WINDEF_
 include windef.inc
endif
ifndef INCLUDED_TYPES_FCI_FDI
INCLUDED_TYPES_FCI_FDI	equ <>
.xlist

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

include basetsd.inc

ifndef INCLUDED_FDI
INCLUDED_FDI equ <>

include specstrings.inc

ifndef _WIN64
;include pshpack4.inc
endif

FDIERROR		typedef SDWORD
FDIERROR_NONE		equ 0
FDIERROR_CABINET_NOT_FOUND equ 1
FDIERROR_NOT_A_CABINET	equ 2
FDIERROR_UNKNOWN_CABINET_VERSION equ 3
FDIERROR_CORRUPT_CABINET equ 4
FDIERROR_ALLOC_FAIL	equ 5
FDIERROR_BAD_COMPR_TYPE equ 6
FDIERROR_MDI_FAIL	equ 7
FDIERROR_TARGET_FILE	equ 8
FDIERROR_RESERVE_MISMATCH equ 9
FDIERROR_WRONG_CABINET	equ 10
FDIERROR_USER_ABORT	equ 11

ifndef _A_NAME_IS_UTF
_A_NAME_IS_UTF		equ 0x80
endif
ifndef _A_EXEC
_A_EXEC			equ 0x40
endif

HFDI			typedef ptr

FDICABINETINFO		STRUC
cbCabinet		LONG ? ;; Total length of cabinet file
cFolders		USHORT ?	;; Count of folders in cabinet
cFiles			USHORT ?	;; Count of files in cabinet
setID			USHORT ?	;; Cabinet set ID
iCabinet		USHORT ?	;; Cabinet number in set (0 based)
fReserve		BOOL ?	;; TRUE => RESERVE present in cabinet
hasprev			BOOL ?	;; TRUE => Cabinet is chained prev
hasnext			BOOL ?	;; TRUE => Cabinet is chained next
FDICABINETINFO		ENDS
PFDICABINETINFO		typedef ptr FDICABINETINFO

FDIDECRYPTTYPE		typedef SDWORD
fdidtNEW_CABINET	equ 0
fdidtNEW_FOLDER		equ 1
fdidtDECRYPT		equ 2


FDIDECRYPT		STRUC
fdidt			FDIDECRYPTTYPE ?
pvUser			PVOID ?
UNION
 STRUC cabinet
  pHeaderReserve	PVOID ?
  cbHeaderReserve	USHORT ?
  setID			USHORT ?
  iCabinet		SINT ?
 ENDS
 STRUC folder
  pFolderReserve	 PVOID ?
  cbFolderReserve	 USHORT ?
  iFolder		 USHORT ?
 ENDS
 STRUC decrypt
  pDataReserve		PVOID ?
  cbDataReserve		USHORT ?
  pbData		PVOID ?
  cbData		USHORT ?
  fSplit		BOOL ?
  cbPartial		USHORT ?
 ENDS
ENDS
FDIDECRYPT		ENDS
PFDIDECRYPT		typedef ptr FDIDECRYPT


CALLBACK(PFNALLOC, :ULONG)
FNALLOC macro fn
	exitm<CALLBACK(fn, :ULONG)>
	endm

CALLBACK(PFNFREE, :ptr)
FNFREE macro fn
	exitm<CALLBACK(fn, :ptr)>
	endm


;;** File I/O functions for FDI
CALLBACK(PFNOPEN,  :LPSTR, :SINT, :SINT)
CALLBACK(PFNREAD,  :INT_PTR, :ptr, :UINT)
CALLBACK(PFNWRITE, :INT_PTR, :ptr, :UINT)
CALLBACK(PFNCLOSE, :INT_PTR)
CALLBACK(PFNSEEK,  :INT_PTR, :LONG, :SINT)

FNOPEN macro fn
	exitm<CALLBACK(fn, :LPSTR, :SINT, :SINT)>
	endm
FNREAD macro fn
	exitm<CALLBACK(fn, :INT_PTR, :ptr, :UINT)>
	endm
FNWRITE macro fn
	exitm<CALLBACK(fn, :INT_PTR, :ptr, :UINT)>
	endm
FNCLOSE macro fn
	exitm<CALLBACK(fn, :INT_PTR)>
	endm
FNSEEK macro fn
	exitm<CALLBACK(fn, :INT_PTR, :LONG, :SINT)>
	endm

CALLBACK(PFNFDIDECRYPT, :PFDIDECRYPT)
FNFDIDECRYPT macro fn
	exitm<CALLBACK(fn, :PFDIDECRYPT)>
	endm


FDINOTIFICATION		STRUC
cb			LONG ?
psz1			LPSTR ?
psz2			LPSTR ?
psz3			LPSTR ?
pv			PVOID ?
hf			INT_PTR ?
date			USHORT ?
time			USHORT ?
attribs			USHORT ?
setID			USHORT ?
iCabinet		USHORT ?
iFolder			USHORT ?
fdie			FDIERROR ?
FDINOTIFICATION		ENDS
PFDINOTIFICATION	typedef ptr FDINOTIFICATION

FDINOTIFICATIONTYPE	typedef SDWORD
fdintCABINET_INFO	equ 0
fdintPARTIAL_FILE	equ 1
fdintCOPY_FILE		equ 2
fdintCLOSE_FILE_INFO	equ 3
fdintNEXT_CABINET	equ 4
fdintENUMERATE		equ 5

CALLBACK(PFNFDINOTIFY, :FDINOTIFICATIONTYPE, :PFDINOTIFICATION)
FNFDINOTIFY macro fn
	exitm<CALLBACK(fn, :FDINOTIFICATIONTYPE, :PFDINOTIFICATION)>
	endm

ifdef _WIN64
FDISPILLFILE_ALIGN equ <>
else
FDISPILLFILE_ALIGN equ <BYTE>
endif

FDISPILLFILE		STRUC FDISPILLFILE_ALIGN
ach			db 2 dup(?)
cbFile			LONG ?
FDISPILLFILE		ENDS
PFDISPILLFILE		typedef ptr FDISPILLFILE

cpuUNKNOWN		equ (-1)    ;; FDI does detection
cpu80286		equ (0)	    ;; '286 opcodes only
cpu80386		equ (1)	    ;; '386 opcodes used

;HFDI DIAMONDAPI
FDICreate proto WINAPI \
	      pfnalloc: PFNALLOC,
	       pfnfree: PFNFREE,
	       pfnopen: PFNOPEN,
	       pfnread: PFNREAD,
	      pfnwrite: PFNWRITE,
	      pfnclose: PFNCLOSE,
	       pfnseek: PFNSEEK,
	       cpuType: SINT,
		  perf: PERF

FDIIsCabinet proto WINAPI \
		  hfdi: HFDI,
		    hf: INT_PTR,
		pfdici: PFDICABINETINFO

;BOOL
FDICopy proto WINAPI \
		  hfdi: HFDI,
	    pszCabinet: LPSTR,
	    pszCabPath: LPSTR,
		 flags: SINT,
	       pfnfdin: PFNFDINOTIFY,
	       pfnfdid: PFNFDIDECRYPT,
		pvUser: ptr
;BOOL
FDIDestroy proto WINAPI \
		  hfdi: HFDI

;BOOL
FDITruncateCabinet proto WINAPI \
		  hfdi: HFDI,
	pszCabinetName: LPSTR,
       iFolderToDelete: USHORT

ifndef _WIN64
;include poppack.inc
endif

.list
endif ;; NOT INCLUDED_FDI

