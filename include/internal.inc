ifndef _INC_INTERNAL
define _INC_INTERNAL

include crtdefs.inc
include errno.inc
include limits.inc
include windows.inc
include mtdll.inc

externdef _exitflag:char_t

__crtExitProcess proto WINAPI :SINT
__crtCorExitProcess proto WINAPI :SINT
_get_errno_from_oserr proto __cdecl :DWORD

_UNKNOWN_APP        equ 0
_CONSOLE_APP        equ 1
_GUI_APP            equ 2

externdef           __app_type:int_t

ifndef _SECURECRT_FILL_BUFFER
ifdef _DEBUG
define _SECURECRT_FILL_BUFFER 1
else
define _SECURECRT_FILL_BUFFER 0
endif
endif

if _SECURECRT_FILL_BUFFER
_SECURECRT__FILL_STRING macro _String, _Size, _Offset
ifnb _SECURECRT_FILL_BUFFER_THRESHOLD
    .ifs (_Size != -1 && _Size != INT_MAX && _Size >= _Offset)
        mov r10,rdi
        mov r11,rcx
        mov rdi,_String
        add rdi,_Offset
        mov rax,_Size
        sub rax,_Offset
        mov rcx,_SECURECRT_FILL_BUFFER_THRESHOLD
        .if ( rcx >= rax )
            mov rcx,rax
        .endif
        mov eax,_SECURECRT_FILL_BUFFER_PATTERN
        rep stosb
        mov rdi,r10
        mov rcx,r11
    .endif
endif
    exitm<>
    endm
else  ;; _SECURECRT_FILL_BUFFER
_SECURECRT__FILL_STRING macro _String, _Size, _Offset
    exitm<>
    endm
endif

ifdef _DEBUG
_CALL_INVALID_PARAMETER macro expr
    exitm<_invalid_parameter(expr, "", __FILEW__, @Line, 0)>
    endm
else
_CALL_INVALID_PARAMETER macro expr
    exitm<_invalid_parameter_noinfo()>
    endm
endif

_INVALID_PARAMETER macro expr
    exitm<_CALL_INVALID_PARAMETER(expr)>
    endm

_VALIDATE_RETURN macro expr, errorcode, retexpr

    .ASSERT( expr )

    .if !( expr )

        mov errno,errorcode
        _INVALID_PARAMETER(_CRT_WIDE(expr))
        mov eax,retexpr
        .break
    .endif
    exitm<>
    endm

_VALIDATE_RETURN_NOEXC macro expr, errorcode, retexpr
    .if ( !(expr) )
        mov errno,errorcode
        mov eax,retexpr
        .break
    .endif
    exitm<>
    endm

endif
