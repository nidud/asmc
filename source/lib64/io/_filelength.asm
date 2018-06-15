include io.inc
include winbase.inc

    .code

filelength PROC handle:SINT

  local FileSize:QWORD

    lea rax,_osfhnd
    mov rcx,[rax+rcx*8]
    .if GetFileSizeEx(rcx, &FileSize)

        mov rax,FileSize
    .else
        osmaperr()
        xor eax,eax
    .endif
    ret
filelength ENDP

    END
