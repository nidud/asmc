; GS_COOKIE.ASM--
;
; defines buffer overrun security cookie
;
include windef.inc

public __security_cookie
public __security_cookie_complement

DEFAULT_SECURITY_COOKIE equ 0x00002B992DDFA232

    .data
     __security_cookie            UINT_PTR DEFAULT_SECURITY_COOKIE
     __security_cookie_complement UINT_PTR not DEFAULT_SECURITY_COOKIE

    end
