ifndef _INC_DCIMAN
_INC_DCIMAN equ <>
include dciddi.inc
.xlist

DECLARE_HANDLE(HWINWATCH)

DCIOpenProvider proto WINAPI

;void
DCICloseProvider proto WINAPI \
		   hdc: HDC

;int
DCICreatePrimary proto WINAPI \
		   hdc: HDC,
	   lplpSurface: LPDCISURFACEINFO

;int
DCICreateOffscreen proto WINAPI \
		   hdc: HDC,
	 dwCompression: DWORD,
	     dwRedMask: DWORD,
	   dwGreenMask: DWORD,
	    dwBlueMask: DWORD,
	       dwWidth: DWORD,
	      dwHeight: DWORD,
	     dwDCICaps: DWORD,
	    dwBitCount: DWORD,
	   lplpSurface: LPDCIOFFSCREEN

;int
DCICreateOverlay proto WINAPI \
		   hdc: HDC,
       lpOffscreenSurf: LPVOID,
	   lplpSurface: LPDCIOVERLAY

;int
DCIEnum proto WINAPI \
		   hdc: HDC,
		lprDst: LPRECT,
		lprSrc: LPRECT,
	  lpFnCallback: LPVOID,
	     lpContext: LPVOID

DCISetSrcDestClip proto WINAPI \
		  pdci: LPDCIOFFSCREEN,
		 srcrc: LPRECT,
		destrc: LPRECT,
		   prd: LPRGNDATA

WinWatchOpen proto WINAPI \
		  hwnd: HWND

;void
WinWatchClose proto WINAPI \
		   hWW: HWINWATCH


;UINT
WinWatchGetClipList proto WINAPI \
		   hWW: HWINWATCH,
		   prc: LPRECT,
		 _size: UINT,
		   prd: LPRGNDATA

;BOOL
WinWatchDidStatusChange proto WINAPI \
		   hWW: HWINWATCH


;DWORD
GetWindowRegionData proto WINAPI \
		  hwnd: HWND,
		 _size: DWORD,
		   prd: LPRGNDATA

;DWORD
GetDCRegionData proto WINAPI \
		   hdc: HDC,
		 _size: DWORD,
		   prd: LPRGNDATA

WINWATCHNOTIFY_START	equ 0
WINWATCHNOTIFY_STOP	equ 1
WINWATCHNOTIFY_DESTROY	equ 2
WINWATCHNOTIFY_CHANGING equ 3
WINWATCHNOTIFY_CHANGED	equ 4

CALLBACK(WINWATCHNOTIFYPROC, hww:HWINWATCH, hwnd:HWND, code:DWORD, lParam:LPARAM)

;BOOL
WinWatchNotify proto WINAPI \
		   hWW: HWINWATCH,
	NotifyCallback: WINWATCHNOTIFYPROC,
	   NotifyParam: LPARAM

ifdef _WIN32

;void
DCIEndAccess proto WINAPI \
		  pdci: LPDCISURFACEINFO

DCIBeginAccess proto WINAPI \
		  pdci: LPDCISURFACEINFO,
		     x: SINT,
		     y: SINT,
		   _dx: SINT,
		   _dy: SINT

;void
DCIDestroy proto WINAPI \
		  pdci: LPDCISURFACEINFO

DCIDraw proto WINAPI \
		  pdci: LPDCIOFFSCREEN

DCISetClipList proto WINAPI \
		  pdci: LPDCIOFFSCREEN,
		   prd: LPRGNDATA

DCISetDestination proto WINAPI \
		  pdci: LPDCIOFFSCREEN,
		   dst: LPRECT,
		   src: LPRECT
else

;int
DCISendCommand proto WINAPI \
		   hdc: HDC,
		  pcmd: PVOID,
		 nSize: SINT
endif

.list
endif
