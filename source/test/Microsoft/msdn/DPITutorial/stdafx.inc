; stdafx.inc: include file for standard system include files,
; or project specific include files that are used frequently, but
; are changed infrequently
;
define NTDDI_VERSION NTDDI_WINBLUE

; Windows Header Files:
include windows.inc
include windowsx.inc
include winnls.inc

; C RunTime Header Files
include stdlib.inc
include malloc.inc
include memory.inc
include tchar.inc

; Specific header required by the program
include shellscalingapi.inc
include libloaderapi.inc
