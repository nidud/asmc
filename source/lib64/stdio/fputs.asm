include stdio.inc
include string.inc

    .code

fputs proc string:LPSTR, fp:LPFILE

  local buffing:SINT, ndone:UINT, lengt:UINT

    _stbuf(rdx)
    mov buffing,eax
    strlen(string)
    mov lengt,eax
    fwrite(string, 1, eax, fp)
    mov ndone,eax
    _ftbuf(buffing, fp)
    mov ecx,lengt
    xor eax,eax
    .if eax != ndone
	dec rax
    .endif
    ret

fputs endp

    END
