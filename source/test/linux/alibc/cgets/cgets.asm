;
; https://docs.microsoft.com/en-us/cpp/c-runtime-library/cgets-cgetws?view=vs-2019
;
; This program creates a buffer and initializes
; the first byte to the size of the buffer. Next, the
; program accepts an input string using _cgets and displays
; the size and text of that string.

include conio.inc
include stdio.inc
include errno.inc

.code

main proc

   local buffer[83]:char_t
   local result:string_t

   mov buffer,80 ; Maximum characters in 1st byte

   printf( "Input line of text, followed by carriage return:\n")

   ; Input a line of text:

   mov result,_cgets( &buffer ) ;; C4996

   ; Note: _cgets is deprecated; consider using _cgets_s

   .if (!result)

      printf( "An error occurred reading from the console:"
              " error code %d\n", _get_errno(NULL))
   .else
      printf( "\nLine length = %d\nText = %s\n", buffer[1], result )
   .endif
   _getch()
   .return( 0 )

main endp

    end
