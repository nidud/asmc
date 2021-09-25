.pragma list(push, 0)
ifndef _INC_INTERNAL_SECURECRT
define _INC_INTERNAL_SECURECRT

include internal.inc

;; string resetting
_FILL_STRING    equ _SECURECRT__FILL_STRING
_FILL_BYTE      equ _SECURECRT__FILL_BYTE

_RESET_STRING macro _String, _Size
    mov _CHAR ptr [_String],0
    _FILL_STRING(_String, _Size, 1)
    exitm<>
    endm

;; validations
_VALIDATE_STRING_ERROR macro _String, _Size, _Ret
    exitm<_VALIDATE_RETURN((_String && _Size), EINVAL, _Ret)>
    endm

_VALIDATE_STRING macro _String, _Size
    exitm<_VALIDATE_STRING_ERROR(_String, _Size, EINVAL)>
    endm

_VALIDATE_POINTER_ERROR_RETURN macro _Pointer, _ErrorCode, _Ret
    exitm<_VALIDATE_RETURN(_Pointer, _ErrorCode, _Ret)>
    endm

_VALIDATE_POINTER_ERROR macro _Pointer, _Ret
    exitm<_VALIDATE_POINTER_ERROR_RETURN(_Pointer, EINVAL, _Ret)>
    endm

_VALIDATE_POINTER macro _Pointer
    exitm<_VALIDATE_POINTER_ERROR(_Pointer, EINVAL)>
    endm

_VALIDATE_CONDITION_ERROR_RETURN macro _Condition, _ErrorCode, _Ret
    exitm<_VALIDATE_RETURN(_Condition, _ErrorCode, _Ret)>
    endm

_VALIDATE_CONDITION_ERROR macro _Condition, _Ret
    exitm<_VALIDATE_CONDITION_ERROR_RETURN(_Condition, EINVAL, _Ret)>
    endm

_VALIDATE_POINTER_RESET_STRING_ERROR macro _Pointer, _String, _Size, _Ret
    .if (_Pointer == NULL)
        _RESET_STRING(_String, _Size)
        _VALIDATE_POINTER_ERROR_RETURN(_Pointer, EINVAL, _Ret)
    .endif
    exitm<>
    endm

_VALIDATE_POINTER_RESET_STRING macro _Pointer, _String, _Size
    exitm<_VALIDATE_POINTER_RESET_STRING_ERROR(_Pointer, _String, _Size, EINVAL)>
    endm

_RETURN_BUFFER_TOO_SMALL_ERROR macro _String, _Size, _Ret
    exitm<_VALIDATE_RETURN(0, ERANGE, _Ret)> ; L"Buffer is too small" && 0
    endm

_RETURN_BUFFER_TOO_SMALL macro _String, _Size
    exitm<_RETURN_BUFFER_TOO_SMALL_ERROR(_String, _Size, ERANGE)>
    endm

_RETURN_DEST_NOT_NULL_TERMINATED macro _String, _Size
    exitm<_VALIDATE_RETURN((0), EINVAL, EINVAL)> ; L"String is not null terminated" && 0
    endm

_RETURN_EINVAL macro
    exitm<_VALIDATE_RETURN((0), EINVAL, EINVAL)> ; L"Invalid parameter", 0
    endm

_RETURN_ERROR macro _Msg, _Ret
    exitm<_VALIDATE_RETURN(((_Msg), 0), EINVAL, _Ret)>
    endm

;; returns without calling _invalid_parameter
_RETURN_NO_ERROR macro
    xor eax,eax
    exitm<.break>
    endm

;; Note that _RETURN_TRUNCATE does not set errno
_RETURN_TRUNCATE macro
    mov eax,STRUNCATE
    exitm<.break>
    endm

_SET_MBCS_ERROR macro
    exitm<mov errno,EILSEQ>
    endm

_RETURN_MBCS_ERROR macro
    mov eax,_SET_MBCS_ERROR
    exitm<.break>
    endm

;; locale dependent
_LOCALE_ARG         equ <_LocInfo>
_LOCALE_ARG_DECL    equ <local _LOCALE_ARG:_locale_t>

_LOCALE_UPDATE macro
    exitm<_LocaleUpdate _LocUpdate(_LOCALE_ARG)>
    endm

_ISMBBLEAD macro _Character
    exitm<_ismbblead_l(_Character, _LocUpdate.GetLocaleT())>
    endm

_MBSDEC macro _String, _Current
    exitm<_mbsdec(_String, _Current)>
    endm

_ISMBBLEADPREFIX macro _Result, _StringStart, _BytePtr

    ; unsigned char *_Tmp_VAR, *_StringStart_VAR, *_BytePtr_VAR;
    ;
    ;     _StringStart_VAR = (_StringStart);
    ;     _BytePtr_VAR = (_BytePtr);
    ;     _Tmp_VAR = _BytePtr_VAR;
    ;     while ((_Tmp_VAR >= _StringStart_VAR) && _ISMBBLEAD(*_Tmp_VAR))
    ;     {
    ;         _Tmp_VAR--;
    ;     }
    ;     (_Result) = ((_BytePtr_VAR - _Tmp_VAR) & 1) != 0;
    exitm<.err>
    endm

_LOCALE_SHORTCUT_TEST macro
    exitm<_LocUpdate.GetLocaleT()->mbcinfo->ismbcodepage == 0>
    endm

_USE_LOCALE_ARG equ 1

;; misc
_ASSIGN_IF_NOT_NULL macro _Pointer, _Value
    .if (_Pointer != NULL)
        mov [_Pointer],_Value
    .endif
    exitm<>
    endm

endif ;; _INC_INTERNAL_SECURECRT
.pragma list(pop)
