ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;
; This module defines the 32-Bit Windows MCX APIs
;
ifndef _MCX_H_
_MCX_H_ equ 1

MODEMDEVCAPS		STRUC
dwActualSize		dd ?
dwRequiredSize		dd ?
dwDevSpecificOffset	dd ?
dwDevSpecificSize	dd ?

;; product and version identification
dwModemProviderVersion	dd ?
dwModemManufacturerOffset dd ?
dwModemManufacturerSize dd ?
dwModemModelOffset	dd ?
dwModemModelSize	dd ?
dwModemVersionOffset	dd ?
dwModemVersionSize	dd ?

;; local option capabilities
dwDialOptions		dd ?	;; bitmap of supported values
dwCallSetupFailTimer	dd ?	;; maximum in seconds
dwInactivityTimeout	dd ?	;; maximum in seconds
dwSpeakerVolume		dd ?	;; bitmap of supported values
dwSpeakerMode		dd ?	;; bitmap of supported values
dwModemOptions		dd ?	;; bitmap of supported values
dwMaxDTERate		dd ?	;; maximum value in bit/s
dwMaxDCERate		dd ?	;; maximum value in bit/s

;; Variable portion for proprietary expansion
abVariablePortion	db ?
MODEMDEVCAPS		ENDS
PMODEMDEVCAPS		typedef ptr MODEMDEVCAPS
LPMODEMDEVCAPS		typedef ptr MODEMDEVCAPS

MODEMSETTINGS		STRUC
dwActualSize		dd ?
dwRequiredSize		dd ?
dwDevSpecificOffset	dd ?
dwDevSpecificSize	dd ?

;; static local options (read/write)
dwCallSetupFailTimer	dd ?	;; seconds
dwInactivityTimeout	dd ?	;; seconds
dwSpeakerVolume		dd ?	;; level
dwSpeakerMode		dd ?	;; mode
dwPreferredModemOptions dd ?	;; bitmap

;; negotiated options (read only) for current or last call ;; ?
dwNegotiatedModemOptions dd ?	;; bitmap
dwNegotiatedDCERate	dd ?	;; bit/s

;; Variable portion for proprietary expansion ;; ?
abVariablePortion	db ?
MODEMSETTINGS		ENDS
PMODEMSETTINGS		typedef ptr MODEMSETTINGS
LPMODEMSETTINGS		typedef ptr MODEMSETTINGS

;; Dial Options
DIALOPTION_BILLING	equ 0x00000040	;; Supports wait for bong "$"
DIALOPTION_QUIET	equ 0x00000080	;; Supports wait for quiet "@"
DIALOPTION_DIALTONE	equ 0x00000100	;; Supports wait for dial tone "W"

;; SpeakerVolume for MODEMDEVCAPS
MDMVOLFLAG_LOW		equ 0x00000001
MDMVOLFLAG_MEDIUM	equ 0x00000002
MDMVOLFLAG_HIGH		equ 0x00000004

;; SpeakerVolume for MODEMSETTINGS
MDMVOL_LOW		equ 0x00000000
MDMVOL_MEDIUM		equ 0x00000001
MDMVOL_HIGH		equ 0x00000002

;; SpeakerMode for MODEMDEVCAPS
MDMSPKRFLAG_OFF		equ 0x00000001
MDMSPKRFLAG_DIAL	equ 0x00000002
MDMSPKRFLAG_ON		equ 0x00000004
MDMSPKRFLAG_CALLSETUP	equ 0x00000008

;; SpeakerMode for MODEMSETTINGS
MDMSPKR_OFF		equ 0x00000000
MDMSPKR_DIAL		equ 0x00000001
MDMSPKR_ON		equ 0x00000002
MDMSPKR_CALLSETUP	equ 0x00000003

;; Modem Options
MDM_COMPRESSION		equ 0x00000001
MDM_ERROR_CONTROL	equ 0x00000002
MDM_FORCED_EC		equ 0x00000004
MDM_CELLULAR		equ 0x00000008
MDM_FLOWCONTROL_HARD	equ 0x00000010
MDM_FLOWCONTROL_SOFT	equ 0x00000020
MDM_CCITT_OVERRIDE	equ 0x00000040
MDM_SPEED_ADJUST	equ 0x00000080
MDM_TONE_DIAL		equ 0x00000100
MDM_BLIND_DIAL		equ 0x00000200
MDM_V23_OVERRIDE	equ 0x00000400

endif ;; _MCX_H_

.list
