; _GETCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include intrin.inc
include tchar.inc

    .code

_tmain proc argc:int_t, argv:array_t

   local dwMask:dword
   local index:dword
   local isNonzero:byte

   mov dwMask,0x1000
   _cputs( "Enter a positive integer as the mask: " )

   xor edi,edi
   .while 1

        _getch()

        .break .if al < '0'
        .break .if al > '9'

        movzx ebx,al
        _putch( eax )

        lea rcx,[rdi*8]
        lea rdi,[rcx+rdi*2]
        sub bl,'0'
        add rdi,rbx
   .endw

   mov dwMask,edi
   mov isNonzero,_BitScanForward(&index, dwMask)
   .if (isNonzero)
      _cprintf( "\r\nMask: %d Index: %d\r\n", dwMask, index )
   .else
      _cprintf( "\r\nNo set bits found.  Mask is zero.\r\n" )
   .endif
   ret

_tmain endp

    end _tstart
