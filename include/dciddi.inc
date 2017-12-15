ifndef _WINDEF_
 include windef.inc
endif
ifndef _WINNT_
 include winnt.inc
endif
ifndef _INC_DCIDDI
_INC_DCIDDI equ <>
.xlist

;; DCI Command Escapes
DCICOMMAND		equ 3075
DCI_VERSION		equ 0x0100

DCICREATEPRIMARYSURFACE equ 1
DCICREATEOFFSCREENSURFACE equ 2
DCICREATEOVERLAYSURFACE equ 3
DCIENUMSURFACE		equ 4
DCIESCAPE		equ 5

;; DCI-Defined error codes
DCI_OK			equ 0 ;; success

;; Hard errors -- DCI will be unavailable
DCI_FAIL_GENERIC	equ -1
DCI_FAIL_UNSUPPORTEDVERSION equ -2
DCI_FAIL_INVALIDSURFACE equ -3
DCI_FAIL_UNSUPPORTED	equ -4

;; Soft errors -- DCI may be available later
DCI_ERR_CURRENTLYNOTAVAIL equ -5
DCI_ERR_INVALIDRECT	equ -6
DCI_ERR_UNSUPPORTEDFORMAT equ -7
DCI_ERR_UNSUPPORTEDMASK equ -8
DCI_ERR_TOOBIGHEIGHT	equ -9
DCI_ERR_TOOBIGWIDTH	equ -10
DCI_ERR_TOOBIGSIZE	equ -11
DCI_ERR_OUTOFMEMORY	equ -12
DCI_ERR_INVALIDPOSITION equ -13
DCI_ERR_INVALIDSTRETCH	equ -14
DCI_ERR_INVALIDCLIPLIST equ -15
DCI_ERR_SURFACEISOBSCURED equ -16
DCI_ERR_XALIGN		equ -17
DCI_ERR_YALIGN		equ -18
DCI_ERR_XYALIGN		equ -19
DCI_ERR_WIDTHALIGN	equ -20
DCI_ERR_HEIGHTALIGN	equ -21

;; success messages -- DCI call succeeded, but specified item changed
DCI_STATUS_POINTERCHANGED equ 1
DCI_STATUS_STRIDECHANGED equ 2
DCI_STATUS_FORMATCHANGED equ 4
DCI_STATUS_SURFACEINFOCHANGED equ 8
DCI_STATUS_CHROMAKEYCHANGED equ 16
DCI_STATUS_WASSTILLDRAWING equ 32

DCI_SUCCESS macro error
	exitm<error !>= 0>
	endm

;; DCI Capability Flags
DCI_SURFACE_TYPE	equ 0x0000000F
DCI_PRIMARY		equ 0x00000000
DCI_OFFSCREEN		equ 0x00000001
DCI_OVERLAY		equ 0x00000002

DCI_VISIBLE		equ 0x00000010
DCI_CHROMAKEY		equ 0x00000020
DCI_1632_ACCESS		equ 0x00000040
DCI_DWORDSIZE		equ 0x00000080
DCI_DWORDALIGN		equ 0x00000100
DCI_WRITEONLY		equ 0x00000200
DCI_ASYNC		equ 0x00000400

DCI_CAN_STRETCHX	equ 0x00001000
DCI_CAN_STRETCHY	equ 0x00002000
DCI_CAN_STRETCHXY	equ (DCI_CAN_STRETCHX OR DCI_CAN_STRETCHY)

DCI_CAN_STRETCHXN	equ 0x00004000
DCI_CAN_STRETCHYN	equ 0x00008000
DCI_CAN_STRETCHXYN	equ (DCI_CAN_STRETCHXN OR DCI_CAN_STRETCHYN)


DCI_CANOVERLAY		equ 0x00010000

;;
;; Win32 RGNDATA structure.  This will be used for  cliplist info. passing.
;;
if (WINVER LT 0x0400)

ifndef RDH_RECTANGLES

RECTL			STRUC
left			sdword ?
top			sdword ?
right			sdword ?
bottom			sdword ?
RECTL			ENDS
PRECTL			typedef ptr RECTL
NPRECTL			typedef ptr RECTL
LPRECTL			typedef ptr RECTL
LPCRECTL		typedef ptr RECTL

RDH_RECTANGLES		equ 0

RGNDATAHEADER		STRUC
dwSize			dd ?	;; size of structure
iType			dd ?	;; Will be RDH_RECTANGLES
nCount			dd ?	;; # of clipping rectangles
nRgnSize		dd ?	;; size of buffer -- can be zero
rcBound			RECTL <> ;; bounding  rectangle for region
RGNDATAHEADER		ENDS
PRGNDATAHEADER		typedef ptr RGNDATAHEADER
NPRGNDATAHEADER		typedef ptr RGNDATAHEADER
LPRGNDATAHEADER		typedef ptr RGNDATAHEADER
LPCRGNDATAHEADER	typedef ptr RGNDATAHEADER

RGNDATA			STRUC
rdh			RGNDATAHEADER <>
Buffer			sbyte 1 dup(?)
RGNDATA			ENDS
PRGNDATA		typedef ptr RGNDATA
NPRGNDATA		typedef ptr RGNDATA
LPRGNDATA		typedef ptr RGNDATA
LPCRGNDATA		typedef ptr RGNDATA

endif
endif

DCIRVAL			typedef SINT		  ;; return for callbacks

;;*************************************************************************
;;	input structures
;;************************************************************************

;;
;; Used by a DCI client to provide input parameters for the
;; DCICREATEPRIMARYSURFACE escape.
;;
DCICMD			STRUC
dwCommand		dd ?
dwParam1		dd ?
dwParam2		dd ?
dwVersion		dd ?
dwReserved		dd ?
DCICMD			ENDS

;;
;; This structure is used by a DCI client to provide input parameters for
;; the DCICREATE... calls.  The fields that are actually relevant differ for
;; each of the three calls.  Details are in the DCI Spec chapter providing
;; the function specifications.
;;
DCICREATEINPUT		STRUC
cmd			DCICMD <>	;; common header structure
dwCompression		dd ?	;; format of surface to be created
dwMask			dd 3 dup(?)	;; for	nonstandard RGB (e.g. 5-6-5, RGB32)
dwWidth			dd ?	;; height of the surface to be created
dwHeight		dd ?	;; width of input surfaces
dwDCICaps		dd ?	;; capabilities of surface wanted
dwBitCount		dd ?	;; bit depth of format to be created
lpSurface		PVOID ? ;; pointer to an associated surface
DCICREATEINPUT		ENDS
LPDCICREATEINPUT	typedef ptr DCICREATEINPUT


;;*************************************************************************
;;	surface info. structures
;;************************************************************************

;;
;; This structure is used to return information about available support
;; during a DCIEnumSurface call.  It is also used to create a primary
;; surface, and as a member of the larger structures returned by the
;; offscreen and overlay calls.
;;
DCISURFACEINFO		STRUC
dwSize			dd ?	;; size of structure
dwDCICaps		dd ?	;; capability flags (stretch, etc.)
dwCompression		dd ?	;; format of surface to be created
dwMask			dd 3 dup(?)	;; for BI_BITMASK surfaces
dwWidth			dd ?	;; width of surface
dwHeight		dd ?	;; height of surface
lStride			dd ?	;; distance in bytes betw. one pixel
;; and the pixel directly below it
dwBitCount		dd ?	;; Bits per pixel for this dwCompression
dwOffSurface		ULONG_PTR ?	;; offset of surface pointer
wSelSurface		dw ?	;; selector of surface pointer
wReserved		dw ?
dwReserved1		dd ?	;; reserved for provider
dwReserved2		dd ?	;; reserved for DCIMAN
dwReserved3		dd ?	;; reserved for future
BeginAccess		PVOID ? ;; (LPVOID, LPRECT) ;; BeginAccess callback
EndAccess		PVOID ? ;; (LPVOID) ;; EndAcess callback
DestroySurface		PVOID ? ;; (LPVOID) ;; Destroy surface callback
DCISURFACEINFO		ENDS
LPDCISURFACEINFO	typedef ptr DCISURFACEINFO


;;
;; This structure is used by a DCI client to provide input parameters for the
;; DCIEnumSurface call.
;;

CALLBACK(ENUM_CALLBACK, lpSurfaceInfo:LPDCISURFACEINFO, lpContext:PVOID)


DCIENUMINPUT		STRUC
cmd			DCICMD <>	;; common header structure
rSrc			RECT <>		;; source rect. for stretch
rDst			RECT <>		;; dest. rect. for stretch
EnumCallback		ENUM_CALLBACK ? ;; callback for supported formats
lpContext		PVOID ?
DCIENUMINPUT		ENDS
LPDCIENUMINPUT		typedef ptr DCIENUMINPUT


;;
;; This structure must be allocated and returned by the DCI provider in
;; response to a DCICREATEPRIMARYSURFACE call.
;;
DCIPRIMARY		typedef DCISURFACEINFO
LPDCIPRIMARY		typedef ptr DCISURFACEINFO

;;
;; This structure must be allocated and returned by the DCI provider in
;; response to a DCICREATEOFFSCREENSURFACE call.
;;
DCIOFFSCREEN		STRUC
dciInfo			DCISURFACEINFO <>	;; surface info
Draw			PVOID ? ;; copy to onscreen buffer
SetClipList		PVOID ? ;; SetCliplist callback
SetDestination		PVOID ? ;; SetDestination callback
DCIOFFSCREEN		ENDS
LPDCIOFFSCREEN		typedef ptr DCIOFFSCREEN


;;
;; This structure must be allocated and returned by the DCI provider in response
;; to a DCICREATEOVERLAYSURFACE call.
;;
DCIOVERLAY		STRUC
dciInfo			DCISURFACEINFO <>	;; surface info
dwChromakeyValue	dd ?	;; chromakey color value
dwChromakeyMask		dd ?	;; specifies valid bits of value
DCIOVERLAY		ENDS
LPDCIOVERLAY		typedef ptr DCIOVERLAY


;; DCI FOURCC def.s for extended DIB formats

ifndef YVU9
YVU9			equ mmioFOURCC('Y','V','U','9')
endif
ifndef Y411
Y411			equ mmioFOURCC('Y','4','1','1')
endif
ifndef YUY2
YUY2			equ mmioFOURCC('Y','U','Y','2')
endif
ifndef YVYU
YVYU			equ mmioFOURCC('Y','V','Y','U')
endif
ifndef UYVY
UYVY			equ mmioFOURCC('U','Y','V','Y')
endif
ifndef Y211
Y211			equ mmioFOURCC('Y','2','1','1')
endif

.list
endif ;; _INC_DCIDDI

