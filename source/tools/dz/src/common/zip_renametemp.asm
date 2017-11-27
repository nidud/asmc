include io.inc
include iost.inc
include wsub.inc

    .code

zip_renametemp proc
    ioclose(&STDI)
    ioclose(&STDO)
    filexist(edi)           ; 1 file, 2 subdir
    dec eax
    .ifz
        remove(esi)
        rename(edi, esi)   ; 0 or -1
    .else
        mov eax,-1
    .endif
    ret
zip_renametemp endp

    end
