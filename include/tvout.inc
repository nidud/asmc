ifndef __TVOUT__
__TVOUT__ equ 1

ifndef GUID_DEFINED
include guiddef.inc
endif

VIDEOPARAMETERS		STRUC
Guid			GUID <> ;; GUID for this structure
dwOffset		dd ?	;; leave it 0 for now.
dwCommand		dd ?	;; VP_COMMAND_*		   SET or GET
dwFlags			dd ?	;; bitfield, defined below SET or GET
dwMode			dd ?	;; bitfield, defined below SET or GET
dwTVStandard		dd ?	;; bitfield, defined below SET or GET
dwAvailableModes	dd ?	;; bitfield, defined below GET
dwAvailableTVStandard	dd ?	;; bitfield, defined below GET
dwFlickerFilter		dd ?	;; value		   SET or GET
dwOverScanX		dd ?	;; value		   SET or GET
dwOverScanY		dd ?	;;			   SET or GET
dwMaxUnscaledX		dd ?	;; value		   SET or GET
dwMaxUnscaledY		dd ?	;;			   SET or GET
dwPositionX		dd ?	;; value		   SET or GET
dwPositionY		dd ?	;;			   SET or GET
dwBrightness		dd ?	;; value		   SET or GET
dwContrast		dd ?	;; value		   SET or GET
dwCPType		dd ?	;; copy protection type	   SET or GET
dwCPCommand		dd ?	;; VP_CP_CMD_
dwCPStandard		dd ?	;; what TV standards CP is available on. GET
dwCPKey			dd ?
bCP_APSTriggerBits	dd ?	;; (a dword for alignment) SET(bits 0 and 1 valid).
bOEMCopyProtection	db 256 dup(?) ;; oem specific copy protection data SET or GET
VIDEOPARAMETERS		ENDS
PVIDEOPARAMETERS	typedef ptr VIDEOPARAMETERS
LPVIDEOPARAMETERS	typedef ptr VIDEOPARAMETERS

VP_COMMAND_GET		equ 0x0001  ;; size set, return caps.
					;; returned Flags = 0 if not supported.
VP_COMMAND_SET		equ 0x0002  ;; size and params set.

VP_FLAGS_TV_MODE	equ 0x0001
VP_FLAGS_TV_STANDARD	equ 0x0002
VP_FLAGS_FLICKER	equ 0x0004
VP_FLAGS_OVERSCAN	equ 0x0008
VP_FLAGS_MAX_UNSCALED	equ 0x0010  ;; do not use on SET
VP_FLAGS_POSITION	equ 0x0020
VP_FLAGS_BRIGHTNESS	equ 0x0040
VP_FLAGS_CONTRAST	equ 0x0080
VP_FLAGS_COPYPROTECT	equ 0x0100

VP_MODE_WIN_GRAPHICS	equ 0x0001
VP_MODE_TV_PLAYBACK	equ 0x0002  ;; optimize for TV video playback

VP_TV_STANDARD_NTSC_M	equ 0x0001  ;;	      75 IRE Setup
VP_TV_STANDARD_NTSC_M_J equ 0x0002  ;; Japan,  0 IRE Setup
VP_TV_STANDARD_PAL_B	equ 0x0004
VP_TV_STANDARD_PAL_D	equ 0x0008
VP_TV_STANDARD_PAL_H	equ 0x0010
VP_TV_STANDARD_PAL_I	equ 0x0020
VP_TV_STANDARD_PAL_M	equ 0x0040
VP_TV_STANDARD_PAL_N	equ 0x0080
VP_TV_STANDARD_SECAM_B	equ 0x0100
VP_TV_STANDARD_SECAM_D	equ 0x0200
VP_TV_STANDARD_SECAM_G	equ 0x0400
VP_TV_STANDARD_SECAM_H	equ 0x0800
VP_TV_STANDARD_SECAM_K	equ 0x1000
VP_TV_STANDARD_SECAM_K1 equ 0x2000
VP_TV_STANDARD_SECAM_L	equ 0x4000
VP_TV_STANDARD_WIN_VGA	equ 0x8000
;; and the rest
VP_TV_STANDARD_NTSC_433 equ 0x00010000
VP_TV_STANDARD_PAL_G	equ 0x00020000
VP_TV_STANDARD_PAL_60	equ 0x00040000
VP_TV_STANDARD_SECAM_L1 equ 0x00080000

VP_CP_TYPE_APS_TRIGGER	equ 0x0001  ;; DVD trigger bits only
VP_CP_TYPE_MACROVISION	equ 0x0002  ;; full macrovision data available

VP_CP_CMD_ACTIVATE	equ 0x0001  ;; CP command type
VP_CP_CMD_DEACTIVATE	equ 0x0002
VP_CP_CMD_CHANGE	equ 0x0004

endif

