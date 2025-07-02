; FREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include stdio.inc

reg macro inst:vararg
if defined(_WIN64) and defined(__UNIX__)
    mov inst
endif
endm

    .code

    assume rbx:ptr _iobuf

if defined(_WIN64) and defined(__UNIX__)
fread proc uses rbx r12 buffer:string_t, size:int_t, num:int_t, fp:LPFILE
else
fread proc uses rsi rdi rbx buffer:string_t, size:int_t, num:int_t, fp:LPFILE
endif

  local total:uint_t   ; total bytes to read
  local count:uint_t   ; num bytes left to read
  local bufsize:uint_t ; size of stream buffer

    ldr rdi,buffer
    ldr rbx,fp
    ldr eax,size

    mul ldr(num)
    .if ( eax == 0 )
        .return
    .endif

    mov count,eax
    mov total,eax

    mov eax,_MAXIOBUF
    .if ( [rbx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF )

        mov eax,[rbx]._bufsiz ; already has buffer, use its size
    .endif
    mov bufsize,eax

    .repeat ; here is the main loop -- we go through here until we're done

        mov eax,count
        mov ecx,[rbx]._cnt

        .if ( [rbx]._flag & _IOMYBUF or _IOYOURBUF && ecx )

            .if ( eax < ecx )
                mov ecx,eax
            .endif

            mov rsi,[rbx]._ptr
            sub count,ecx
            sub [rbx]._cnt,ecx
            add [rbx]._ptr,rcx
            rep movsb
            reg r12,rdi

        .elseif ( eax >= bufsize )

            ; If we have more than bufsize chars to read, get data
            ; by calling read with an integral number of bufsiz
            ; blocks.  Note that if the stream is text mode, read
            ; will return less chars than we ordered.

            ; calc chars to read -- (count/bufsize) * bufsize

            mov ecx,bufsize
            .if ecx
                xor edx,edx
                div ecx
                mov eax,count
                sub eax,edx
            .endif

            reg r12,rdi
            .ifsd ( _read( [rbx]._file, rdi, rax ) <= 0 )

                or [rbx]._flag,_IOEOF
                mov eax,total
                sub eax,count
                xor edx,edx
                div size
               .return
            .endif
            sub count,eax
            reg rdi,r12
            mov rcx,rdi
            add rdi,rax
ifdef STDZIP
            .if ( [rbx]._flag & _IOCRC32 )

                _crc32( [rbx]._crc32, rcx, eax )
                mov [rbx]._crc32,eax
            .endif
endif
        .else

            reg r12,rdi
            .ifd ( _filbuf( rbx ) == -1 )

                mov eax,total
                sub eax,count
                xor edx,edx
                div size
               .return
            .endif
            reg rdi,r12
            stosb
            dec count
            mov eax,[rbx]._bufsiz
            mov bufsize,eax
        .endif
    .until !count
    .return( num )

fread endp

    end
