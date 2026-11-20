include conio.inc
include intrin.inc
include tchar.inc

.code

_tmain proc
  local dwMask:dword
  local index:dword
  local isNonzero:byte
    mov dwMask,0x1000
    _cputts( "Enter a positive integer as the mask: " )
    xor edi,edi
    .while 1
        _gettch()
        .break .if al < '0'
        .break .if al > '9'
        movzx ebx,al
        _puttch( eax )
        lea rcx,[rdi*8]
        lea rdi,[rcx+rdi*2]
        sub bl,'0'
        add rdi,rbx
    .endw
    mov dwMask,edi
    mov isNonzero,_BitScanForward(&index, dwMask)
    .if (isNonzero)
      _tcprintf( "\r\nMask: %d Index: %d\r\n", dwMask, index )
    .else
      _tcprintf( "\r\nNo set bits found.  Mask is zero.\r\n" )
    .endif
    ret
    endp

    end
