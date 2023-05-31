; FREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include stdio.inc

    .code

    assume rbx:ptr _iobuf

fread proc uses rsi rdi rbx buffer:LPSTR, size:SINT, num:SINT, fp:LPFILE

  local total:UINT   ; total bytes to read
  local count:UINT   ; num bytes left to read
  local bufsize:UINT ; size of stream buffer
  local p:LPSTR

    ldr rdi,buffer
    ldr rbx,fp

    ldr eax,size
    mul num
    .return .if !eax

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
            mov p,rdi

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
            mov p,rdi
            .ifsd ( _read( [rbx]._file, rdi, rax ) <= 0 )

                or [rbx]._flag,_IOEOF
                mov eax,total
                sub eax,count
                xor edx,edx
                div size
               .return
            .endif

            mov rdi,p
            sub count,eax
            add rdi,rax

        .else

            mov p,rdi
            .ifd ( _filbuf( rbx ) == -1 )

                mov eax,total
                sub eax,count
                xor edx,edx
                div size
               .return
            .endif
            mov rdi,p
            stosb
            dec count
            mov eax,[rbx]._bufsiz
            mov bufsize,eax
        .endif
    .until !count
    .return( num )

fread endp

    end
