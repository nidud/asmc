
include shtypes.inc

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

.pragma comment(lib, shcore)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef SCALING_ENUMS_DECLARED

.enum DISPLAY_DEVICE_TYPE {
    DEVICE_PRIMARY = 0,
    DEVICE_IMMERSIVE = 1,
    }

.enum SCALE_CHANGE_FLAGS {
    SCF_VALUE_NONE = 0x00,
    SCF_SCALE = 0x01,
    SCF_PHYSICAL = 0x02,
    }

define SCALING_ENUMS_DECLARED
endif

if (NTDDI_VERSION GE NTDDI_WIN8)

GetScaleFactorForDevice proto WINAPI :DISPLAY_DEVICE_TYPE

RegisterScaleChangeNotifications proto WINAPI :DISPLAY_DEVICE_TYPE, :HWND, :UINT, :ptr DWORD
RevokeScaleChangeNotifications proto WINAPI :DISPLAY_DEVICE_TYPE, :DWORD

endif

if (NTDDI_VERSION GE NTDDI_WINBLUE)

GetScaleFactorForMonitor proto WINAPI :HMONITOR, :ptr DEVICE_SCALE_FACTOR
RegisterScaleChangeEvent proto WINAPI :HANDLE, :ptr DWORD_PTR
UnregisterScaleChangeEvent proto WINAPI :DWORD_PTR

endif

ifndef DPI_ENUMS_DECLARED
define DPI_ENUMS_DECLARED

.enum PROCESS_DPI_AWARENESS {
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_PER_MONITOR_DPI_AWARE = 2
    }

.enum MONITOR_DPI_TYPE {
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
    }

endif

if (NTDDI_VERSION GE NTDDI_WINBLUE)

SetProcessDpiAwareness proto WINAPI :PROCESS_DPI_AWARENESS
GetProcessDpiAwareness proto WINAPI :HANDLE, :ptr PROCESS_DPI_AWARENESS
GetDpiForMonitor proto WINAPI :HMONITOR, :MONITOR_DPI_TYPE, :ptr UINT, :ptr UINT

endif

endif
