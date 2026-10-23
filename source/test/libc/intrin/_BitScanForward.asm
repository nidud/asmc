;; https://msdn.microsoft.com/en-us/library/wfd9z0bb.aspx
include conio.inc
include intrin.inc
include tchar.inc

.code
 main proc
   local dwMask:dword, index:dword, isNonzero:byte, char:sbyte
    mov dwMask,0x1000
    _cputs( "Enter a positive integer as the mask: " )
    xor ebx,ebx
    .while 1
        _getch()
        .break .if al < '0'
        .break .if al > '9'
        mov char,al
        _putch( eax )
        lea rcx,[rbx*8]
        lea rbx,[rcx+rbx*2]
        movzx eax,char
        sub al,'0'
        add rbx,rax
    .endw
    mov dwMask,ebx
    mov isNonzero,_BitScanForward(&index, dwMask)
    .if (isNonzero)
        _cprintf( "\r\nMask: %d Index: %d\r\n", dwMask, index )
    .else
        _cprintf( "\r\nNo set bits found.  Mask is zero.\r\n" )
    .endif
    xor eax,eax
    ret
    endp
    end _tstart
