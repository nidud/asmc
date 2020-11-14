;; stdafx.h : include file for standard system include files,
;; or project specific include files that are used frequently, but
;; are changed infrequently
;;

;; Modify the following defines if you have to target a platform prior to the ones specified below.
;; Refer to MSDN for the latest info on corresponding values for different platforms.
ifndef WINVER           ;; Allow use of features specific to Windows 95 and Windows NT 4 or later.
WINVER equ 0x0400       ;; Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
endif

ifndef _WIN32_WINNT     ;; Allow use of features specific to Windows NT 4 or later.
_WIN32_WINNT equ 0x0400 ;; Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
endif

ifndef _WIN32_WINDOWS   ;; Allow use of features specific to Windows 98 or later.
_WIN32_WINDOWS equ 0x0410 ;; Change this to the appropriate value to target Windows Me or later.
endif

ifndef _WIN32_IE        ;; Allow use of features specific to IE 4.0 or later.
_WIN32_IE equ 0x0400    ;; Change this to the appropriate value to target IE 5.0 or later.
endif

WIN32_LEAN_AND_MEAN equ 1 ;; Exclude rarely-used stuff from Windows headers

;; Windows Header Files:

include windows.inc

;; C RunTime Header Files

include stdlib.inc
include malloc.inc
include memory.inc
include tchar.inc

;; TODO: reference additional headers your program requires here
