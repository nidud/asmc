ifndef _LIBC_
include libc.inc
endif
ifndef _MCX_H_
define _MCX_H_

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

define DIALOPTION_BILLING	0x00000040
define DIALOPTION_QUIET		0x00000080
define DIALOPTION_DIALTONE	0x00000100

define MDMVOLFLAG_LOW		0x00000001
define MDMVOLFLAG_MEDIUM	0x00000002
define MDMVOLFLAG_HIGH		0x00000004

define MDMVOL_LOW		0x00000000
define MDMVOL_MEDIUM		0x00000001
define MDMVOL_HIGH		0x00000002

define MDMSPKRFLAG_OFF		0x00000001
define MDMSPKRFLAG_DIAL		0x00000002
define MDMSPKRFLAG_ON		0x00000004
define MDMSPKRFLAG_CALLSETUP	0x00000008

define MDMSPKR_OFF		0x00000000
define MDMSPKR_DIAL		0x00000001
define MDMSPKR_ON		0x00000002
define MDMSPKR_CALLSETUP	0x00000003

define MDM_COMPRESSION		0x00000001
define MDM_ERROR_CONTROL	0x00000002
define MDM_FORCED_EC		0x00000004
define MDM_CELLULAR		0x00000008
define MDM_FLOWCONTROL_HARD	0x00000010
define MDM_FLOWCONTROL_SOFT	0x00000020
define MDM_CCITT_OVERRIDE	0x00000040
define MDM_SPEED_ADJUST		0x00000080
define MDM_TONE_DIAL		0x00000100
define MDM_BLIND_DIAL		0x00000200
define MDM_V23_OVERRIDE		0x00000400

endif
