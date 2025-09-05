ifndef __TVOUT__
define __TVOUT__

ifndef GUID_DEFINED
include guiddef.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

VIDEOPARAMETERS		struct
Guid			GUID <>
dwOffset		dd ?
dwCommand		dd ?
dwFlags			dd ?
dwMode			dd ?
dwTVStandard		dd ?
dwAvailableModes	dd ?
dwAvailableTVStandard	dd ?
dwFlickerFilter		dd ?
dwOverScanX		dd ?
dwOverScanY		dd ?
dwMaxUnscaledX		dd ?
dwMaxUnscaledY		dd ?
dwPositionX		dd ?
dwPositionY		dd ?
dwBrightness		dd ?
dwContrast		dd ?
dwCPType		dd ?
dwCPCommand		dd ?
dwCPStandard		dd ?
dwCPKey			dd ?
bCP_APSTriggerBits	dd ?
bOEMCopyProtection	dw 256 dup(?)
VIDEOPARAMETERS		ends
PVIDEOPARAMETERS	typedef ptr VIDEOPARAMETERS
LPVIDEOPARAMETERS	typedef ptr VIDEOPARAMETERS

define VP_COMMAND_GET	       0x0001
define VP_COMMAND_SET	       0x0002

define VP_FLAGS_TV_MODE	       0x0001
define VP_FLAGS_TV_STANDARD    0x0002
define VP_FLAGS_FLICKER	       0x0004
define VP_FLAGS_OVERSCAN       0x0008
define VP_FLAGS_MAX_UNSCALED   0x0010
define VP_FLAGS_POSITION       0x0020
define VP_FLAGS_BRIGHTNESS     0x0040
define VP_FLAGS_CONTRAST       0x0080
define VP_FLAGS_COPYPROTECT    0x0100

define VP_MODE_WIN_GRAPHICS    0x0001
define VP_MODE_TV_PLAYBACK     0x0002

define VP_TV_STANDARD_NTSC_M   0x0001
define VP_TV_STANDARD_NTSC_M_J 0x0002
define VP_TV_STANDARD_PAL_B    0x0004
define VP_TV_STANDARD_PAL_D    0x0008
define VP_TV_STANDARD_PAL_H    0x0010
define VP_TV_STANDARD_PAL_I    0x0020
define VP_TV_STANDARD_PAL_M    0x0040
define VP_TV_STANDARD_PAL_N    0x0080
define VP_TV_STANDARD_SECAM_B  0x0100
define VP_TV_STANDARD_SECAM_D  0x0200
define VP_TV_STANDARD_SECAM_G  0x0400
define VP_TV_STANDARD_SECAM_H  0x0800
define VP_TV_STANDARD_SECAM_K  0x1000
define VP_TV_STANDARD_SECAM_K1 0x2000
define VP_TV_STANDARD_SECAM_L  0x4000
define VP_TV_STANDARD_WIN_VGA  0x8000
define VP_TV_STANDARD_NTSC_433 0x00010000
define VP_TV_STANDARD_PAL_G    0x00020000
define VP_TV_STANDARD_PAL_60   0x00040000
define VP_TV_STANDARD_SECAM_L1 0x00080000

define VP_CP_TYPE_APS_TRIGGER  0x0001
define VP_CP_TYPE_MACROVISION  0x0002

define VP_CP_CMD_ACTIVATE      0x0001
define VP_CP_CMD_DEACTIVATE    0x0002
define VP_CP_CMD_CHANGE	       0x0004

endif

endif
