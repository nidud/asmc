;
; https://msdn.microsoft.com/en-us/library/3w2s47z0.aspx
;
; errno definition added for -pe: _get_errno()
;

;; compile with: Asmc64 -pe _cputs.asm
;; This program first displays a string to the console.

include conio.inc
include errno.inc

.code

print_to_console proc buffer:LPSTR

   local retval:SINT

   mov retval,_cputs( buffer )

   .if (retval)

       .if (errno == EINVAL)

         _cputs( "Invalid buffer in print_to_console.\r\n");

       .else
         _cputs( "Unexpected error in print_to_console.\r\n");
       .endif
   .endif
   ret

print_to_console endp


wprint_to_console proc wbuffer:ptr wchar_t

   local retval:SINT

   mov retval,_cputws( wbuffer )

   .if (retval)

       .if (errno == EINVAL)

         _cputws( L"Invalid buffer in print_to_console.\r\n")

       .else
         _cputws( L"Unexpected error in print_to_console.\r\n")
       .endif
   .endif
   ret

wprint_to_console endp

main proc

    ;; String to print at console.
    ;; Notice the \r (return) character.

    print_to_console( "Hello world (courtesy of _cputs)!\r\n" )
    wprint_to_console( L"Hello world (courtesy of _cputws)!\r\n" )
    ret

main endp

    end main
