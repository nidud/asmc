;; stdafx.inc : include file for standard system include files,
;; or project specific include files that are used frequently, but
;; are changed infrequently
;;

;; Modify the following defines if you have to target a platform prior to the ones specified below.
;; Refer to MSDN for the latest info on corresponding values for different platforms.
ifndef WINVER               ;; Allow use of features specific to Windows XP or later.
WINVER equ 0x0602           ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINNT         ;; Allow use of features specific to Windows XP or later.
_WIN32_WINNT equ 0x0602     ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINDOWS       ;; Allow use of features specific to Windows 98 or later.
_WIN32_WINDOWS equ 0x0410   ;; Change this to the appropriate value to target Windows Me or later.
endif

ifndef _WIN32_IE            ;; Allow use of features specific to IE 6.0 or later.
_WIN32_IE equ 0x0600        ;; Change this to the appropriate value to target other versions of IE.
endif

;; Windows Header Files:

include windows.inc
include comdef.inc

;; C RunTime Header Files

include stdlib.inc
include math.inc
include malloc.inc
include memory.inc
include tchar.inc

ifdef __CV__
.pragma comment(linker,"/DEFAULTLIB:libcmtd.lib")
endif
