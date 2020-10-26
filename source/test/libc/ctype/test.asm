;
; v2.31.08
;
; - Stack allocation within a macro -- NEW directive
; - PROTO and MACRO combination -- ctype.inc
; - RETURN directive and ENDP
;
include ctype.inc
include stdio.inc
include stdlib.inc
include winbase.inc

return equ <.return>

SystemDirectory macro

    .new buffer[_MAX_PATH]:char_t

    GetSystemDirectory(&buffer, _MAX_PATH)
    lea rax,buffer
    retm<rax>
    endm

WindowsDirectory macro

    .new buffer[_MAX_PATH]:char_t

    GetWindowsDirectory(&buffer, _MAX_PATH)
    lea rax,buffer
    retm<rax>
    endm

    .code

main proc

   printf( "WindowsDirectory: %s\n", WindowsDirectory() )
   printf( "SystemDirectory:  %s\n", SystemDirectory() )

   printf( "isupper('A'): %d\n", isupper('A') )
   printf( "isupper('a'): %d\n", isupper('a') )
   printf( "isalnum('0'): %d\n", isalnum('0') )
   printf( "isascii('9'): %d\n", isascii('9') )

   return( 0 )

main endp

    end
