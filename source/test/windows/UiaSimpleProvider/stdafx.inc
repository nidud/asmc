;
; include file for standard system include files, or project specific include
; files that are used frequently, but are changed infrequently
;
; Modify the following defines if you have to target a platform prior to the
; ones specified below. Refer to MSDN for the latest info on corresponding
; values for different platforms.
;
if 0
;
; Allow use of features specific to Windows 95 and Windows NT 4 or later.
; Change this to the appropriate value to target Windows 98 and Windows 2000 or
; later.
;
ifndef WINVER
define WINVER 0x0400
endif
;
; Allow use of features specific to Windows NT 4 or later. Change this to the
; appropriate value to target Windows 98 and Windows 2000 or later.
;
ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0400
endif
;
; Allow use of features specific to Windows 98 or later. Change this to the
; appropriate value to target Windows Me or later.
;
ifndef _WIN32_WINDOWS
define _WIN32_WINDOWS 0x0410
endif
;
; Allow use of features specific to IE 4.0 or later. Change this to the
; appropriate value to target IE 5.0 or later.
;
ifndef _WIN32_IE
define _WIN32_IE 0x0400
endif
endif

ifndef WIN32_LEAN_AND_MEAN
define WIN32_LEAN_AND_MEAN ; Exclude rarely-used stuff from Windows headers
endif
;
; Windows Header Files:
;
include windows.inc
;
; C RunTime Header Files
;
include stdlib.inc
include malloc.inc
include memory.inc
include tchar.inc


; TODO: reference additional headers your program requires here
