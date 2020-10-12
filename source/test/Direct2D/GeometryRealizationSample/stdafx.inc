
;; Modify the following defines if you have to target a platform prior to the ones specified below.
;; Refer to MSDN for the latest info on corresponding values for different platforms.
ifndef WINVER               ;; Allow use of features specific to Windows XP or later.
WINVER equ 0x0501           ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINNT         ;; Allow use of features specific to Windows XP or later.
_WIN32_WINNT equ 0x0501     ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINDOWS       ;; Allow use of features specific to Windows 98 or later.
_WIN32_WINDOWS equ 0x0410   ;; Change this to the appropriate value to target Windows Me or later.
endif

ifndef _WIN32_IE            ;; Allow use of features specific to IE 6.0 or later.
_WIN32_IE equ 0x0600        ;; Change this to the appropriate value to target other versions of IE.
endif

ifndef _UNICODE
_UNICODE equ 1
endif

;; Windows Header Files:
include windows.inc

;; C RunTime Header Files
include stdlib.inc
include malloc.inc
include memory.inc
include wchar.inc

_USE_MATH_DEFINES equ 1

include math.inc

include strsafe.inc

include d2d1.inc
include d2d1helper.inc
include dwrite.inc
include wincodec.inc
include tchar.inc

option dllimport:none

;/******************************************************************
;*                                                                 *
;*  Macros                                                         *
;*                                                                 *
;******************************************************************/

SafeRelease proto :ptr, :abs {

    mov rax,[this]
    .if rax
        mov qword ptr [this],NULL
        [rax]._1.Release()
    .endif
    }

SafeReplace proto :ptr ptr, :ptr {

   .new p:ptr

    mov rax,[rcx]
    mov [rcx],rdx
    mov p,rcx
    .if rax
        [rax].IUnknown.Release()
        mov rcx,p
    .endif
    mov rax,[rcx]
    .if rax
        [rax].IUnknown.AddRef()
    .endif
    }


ifndef HINST_THISCOMPONENT
ifndef _MSVCRT
extern __ImageBase:byte
endif
HINST_THISCOMPONENT equ <&__ImageBase>
endif

include geometryrealization.inc
include ringbuffer.inc
include GeometryRealizationSample.inc
