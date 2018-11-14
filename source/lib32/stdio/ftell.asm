; FTELL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include errno.inc
include winbase.inc

    .code

    assume ebx:ptr _iobuf

ftell proc uses esi edi ebx fp:LPFILE

  local rdcnt:SIZE_T, filepos:SIZE_T

    mov ebx,fp
    xor eax,eax
    .ifs [ebx]._cnt < eax

        mov [ebx]._cnt,eax
    .endif

    mov eax,[ebx]._file
    mov eax,_osfhnd[eax*4]

    .repeat

        .if SetFilePointer( eax, 0, 0, SEEK_CUR ) == -1

            osmaperr()
            .break
        .endif
        mov filepos,eax

        .ifs eax < 0

            mov eax,-1
            .break
        .endif

        mov ecx,[ebx]._flag
        .if !(ecx & ( _IOMYBUF or _IOYOURBUF ) )

            sub eax,[ebx]._cnt
            .break
        .endif

        mov edi,[ebx]._ptr
        sub edi,[ebx]._base

        .if ecx & _IOWRT or _IOREAD

            mov eax,[ebx]._file
            .if _osfile[eax] & FH_TEXT

                mov eax,[ebx]._base
                .while eax < [ebx]._ptr

                    .if byte ptr [eax] == 10

                        inc edi
                    .endif
                    inc eax
                .endw
            .endif

        .elseif !(ecx & _IORW)

            mov errno,EINVAL
            mov eax,-1
            .break
        .endif

        mov eax,edi
        .break .if !filepos

        .if ecx & _IOREAD

            mov eax,[ebx]._cnt
            .if !eax

                mov edi,eax
            .else
                add eax,[ebx]._ptr
                sub eax,[ebx]._base
                mov rdcnt,eax
                mov eax,[ebx]._file

                .if _osfile[eax] & FH_TEXT

                    mov ecx,_osfhnd[eax*4]
                    .if SetFilePointer( ecx, 0, 0, SEEK_END ) == filepos

                        .for eax=[ebx]._base, ecx=eax, eax+=rdcnt:,
                             ecx < eax: ecx++

                            .if byte ptr [ecx] == 10

                                inc rdcnt
                            .endif
                        .endf

                        .if [ebx]._flag & _IOCTRLZ

                            inc rdcnt
                        .endif
                    .else
                        mov eax,[ebx]._file
                        mov ecx,_osfhnd[eax*4]
                        SetFilePointer(ecx, filepos, 0, SEEK_SET)
                        mov eax,[ebx]._flag

                        .if rdcnt <= 512 && ( eax & _IOMYBUF ) \
                            && !( eax & _IOSETVBUF )

                            mov rdcnt,512
                        .else
                            mov eax,[ebx]._bufsiz
                            mov rdcnt,eax
                        .endif
                        mov eax,[ebx]._file

                        .if _osfile[eax] & FH_CRLF

                            inc rdcnt
                        .endif
                    .endif
                .endif
                mov eax,rdcnt
                sub filepos,eax
            .endif
        .endif
        add edi,filepos
        mov eax,edi
    .until 1
    ret

ftell endp

    END
