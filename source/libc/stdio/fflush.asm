include stdio.inc
include io.inc

    .code

    assume ebx: LPFILE

fflush proc uses ebx edi esi fp:LPFILE

    mov ebx,fp
    xor esi,esi
    mov eax,[ebx]._flag
    mov edi,eax
    and eax,_IOREAD or _IOWRT

    .repeat

        .break .if eax != _IOWRT
        .break .if !(edi & _IOMYBUF or _IOYOURBUF)

        mov eax,[ebx]._ptr
        sub eax,[ebx]._base
        .break .ifng

        push eax
        _write( [ebx]._file, [ebx]._base, eax )
        pop edx

        .if eax != edx
            or  edi,_IOERR
            mov [ebx]._flag,edi
            or  esi,-1
            .break
        .endif

        mov eax,[ebx]._flag
        .break .if !(eax & _IORW)

        and eax,not _IOWRT
        mov [ebx]._flag,eax
    .until 1
    mov eax,[ebx]._base
    mov [ebx]._ptr,eax
    mov [ebx]._cnt,0
    mov eax,esi
    ret

fflush endp

    END
