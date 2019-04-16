;; https://msdn.microsoft.com/en-us/library/wfd9z0bb.aspx
;; _BitScanForward.asm
include conio.inc
include intrin.inc
include tchar.inc

    .code

main proc

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

main endp

    end _tstart
