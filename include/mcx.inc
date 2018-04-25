ifndef __LIBC_INC
 include libc.inc
endif
ifndef _MCX_H_
_MCX_H_ equ <>

MODEMDEVCAPS		STRUC
dwActualSize		dd ?
dwRequiredSize		dd ?
dwDevSpecificOffset	dd ?
dwDevSpecificSize	dd ?

dwModemProviderVersion	dd ?
dwModemManufacturerOffset dd ?
dwModemManufacturerSize dd ?
dwModemModelOffset	dd ?
dwModemModelSize	dd ?
dwModemVersionOffset	dd ?
dwModemVersionSize	dd ?

dwDialOptions		dd ?
dwCallSetupFailTimer	dd ?
dwInactivityTimeout	dd ?
dwSpeakerVolume		dd ?
dwSpeakerMode		dd ?
dwModemOptions		dd ?
dwMaxDTERate		dd ?
dwMaxDCERate		dd ?

abVariablePortion	db ?
MODEMDEVCAPS		ENDS
PMODEMDEVCAPS		typedef ptr MODEMDEVCAPS
LPMODEMDEVCAPS		typedef ptr MODEMDEVCAPS

MODEMSETTINGS		STRUC
dwActualSize		dd ?
dwRequiredSize		dd ?
dwDevSpecificOffset	dd ?
dwDevSpecificSize	dd ?

dwCallSetupFailTimer	dd ?
dwInactivityTimeout	dd ?
dwSpeakerVolume		dd ?
dwSpeakerMode		dd ?
dwPreferredModemOptions dd ?

dwNegotiatedModemOptions dd ?
dwNegotiatedDCERate	dd ?

abVariablePortion	db ?
MODEMSETTINGS		ENDS
PMODEMSETTINGS		typedef ptr MODEMSETTINGS
LPMODEMSETTINGS		typedef ptr MODEMSETTINGS

DIALOPTION_BILLING	equ 0x00000040
DIALOPTION_QUIET	equ 0x00000080
DIALOPTION_DIALTONE	equ 0x00000100

MDMVOLFLAG_LOW		equ 0x00000001
MDMVOLFLAG_MEDIUM	equ 0x00000002
MDMVOLFLAG_HIGH		equ 0x00000004

MDMVOL_LOW		equ 0x00000000
MDMVOL_MEDIUM		equ 0x00000001
MDMVOL_HIGH		equ 0x00000002

MDMSPKRFLAG_OFF		equ 0x00000001
MDMSPKRFLAG_DIAL	equ 0x00000002
MDMSPKRFLAG_ON		equ 0x00000004
MDMSPKRFLAG_CALLSETUP	equ 0x00000008

MDMSPKR_OFF		equ 0x00000000
MDMSPKR_DIAL		equ 0x00000001
MDMSPKR_ON		equ 0x00000002
MDMSPKR_CALLSETUP	equ 0x00000003

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

endif
