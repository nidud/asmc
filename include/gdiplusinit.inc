ifndef _GDIPLUSINIT_H
_GDIPLUSINIT_H equ <>

DebugEventLevel		typedef SDWORD
DebugEventLevelFatal	equ 0
DebugEventLevelWarning	equ 1

CALLBACK(DebugEventProc, :DebugEventLevel, :ptr)
CALLBACK(NotificationHookProc, :ptr)
CALLBACK(NotificationUnhookProc, :ULONG_PTR)

GdiplusStartupInput	STRUC
GdiplusVersion		UINT ?
DebugEventCallback	DebugEventProc ?
SuppressBackgroundThread BOOL ?
SuppressExternalCodecs	BOOL ?
GdiplusStartupInput	ENDS

if (GDIPVER GE 0x0110)
GdiplusStartupInputEx	STRUC
StartupParameters	SINT ?
GdiplusStartupInputEx	ENDS

GdiplusStartupParams	typedef SDWORD
GdiplusStartupDefault	equ 0
GdiplusStartupNoSetRound equ 1
GdiplusStartupSetPSValue equ 2
GdiplusStartupTransparencyMask equ 0xFF000000
endif

GdiplusStartupOutput	STRUC
NotificationHook	NotificationHookProc ?
NotificationUnhook	NotificationUnhookProc ?
GdiplusStartupOutput	ENDS

GdiplusStartup proto WINAPI \
		 token: ptr ULONG_PTR,
		 input: ptr GdiplusStartupInput,
		output: ptr GdiplusStartupOutput

GdiplusShutdown proto WINAPI \
		 token: ULONG_PTR

endif
