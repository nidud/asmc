;; https://msdn.microsoft.com/en-us/library/a3140177.aspx
;; crt_byteswap.c
include stdio.inc
include intrin.inc
include tchar.inc
.code
main proc

  local u64:qword
  local ul:dword

    mov rax,0x0102030405060708
    mov u64,rax
    mov ul,0x01020304

    printf("byteswap of %I64x = %I64x\n", u64, _byteswap_uint64(u64))
    printf("byteswap of %Ix = %Ix\n", ul, _byteswap_ulong(ul))
    ret
main endp

    end _tstart
