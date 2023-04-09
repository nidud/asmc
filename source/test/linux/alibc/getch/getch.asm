; GETCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include intrin.inc

    .code

main proc

  .new dwMask:dword = 0x1000
  .new index:dword
  .new isNonzero:byte
  .new c:int_t, i:int_t = 0

   _cputs( "Enter a positive integer as the mask: " )

   .while 1

        mov c,_getch()

        .break .if c < '0'
        .break .if c > '9'

        _putch( c )

        imul eax,i,10
        sub c,'0'
        add eax,c
        mov i,eax
   .endw

   mov dwMask,i
   mov isNonzero,_BitScanForward(&index, dwMask)
   .if (isNonzero)
      _cprintf( "\nMask: %d Index: %d\n", dwMask, index )
   .else
      _cprintf( "\nNo set bits found.  Mask is zero.\n" )
   .endif
   _getch()
   .return( 0 )

main endp

    end
