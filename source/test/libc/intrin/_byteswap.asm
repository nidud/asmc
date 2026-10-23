;; https://msdn.microsoft.com/en-us/library/a3140177.aspx
include stdio.inc
include intrin.inc
include tchar.inc

.code
 main proc
   .new u64:qword = 0x0102030405060708
   .new ul:dword  = 0x01020304
    printf("byteswap of %I64x = %I64x\n", u64, _byteswap_uint64(u64))
    printf("byteswap of %Ix = %Ix\n", ul, _byteswap_ulong(ul))
    xor eax,eax
    ret
    endp
    end _tstart
