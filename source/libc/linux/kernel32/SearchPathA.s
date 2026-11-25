; SEARCHPATHA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include malloc.inc
include winbase.inc
include sys/stat.inc

.code

 SearchPathA proc WINAPI uses rbx lpPath:LPCSTR, lpFileName:LPCSTR,
        lpExtension:LPCSTR, nBufferLength:DWORD, lpBuffer:LPSTR, lpFilePart:ptr

   .new pathalloc:LPSTR = NULL
   .new nextdir:LPSTR
   .new candir:LPSTR
   .new pathlen:uint_t
   .new dirlen:size_t
   .new fnlen:size_t
   .new extlen:size_t = 0
   .new needext:byte = 0
   .new cand[4096]:char_t

    ldr rbx,lpFileName
    .if ( !rbx || byte ptr [rbx] == 0 )
        .return( SetLastError( ERROR_INVALID_PARAMETER ) )
    .endif
    mov fnlen,strlen(rbx)
    mov rdx,lpExtension
    .if ( rdx && byte ptr [rdx] != 0 )
        mov rdx,rbx
        mov rcx,rbx
        .while ( byte ptr [rdx] )
            .if ( byte ptr [rdx] == '/' )
                lea rcx,[rdx+1]
            .endif
            inc rdx
        .endw
        .if ( !strchr(rcx, '.') )
            mov needext,1
            mov extlen,strlen(lpExtension)
        .endif
    .endif
    mov rbx,lpPath
    .if ( !rbx )
        .ifd !GetEnvironmentVariableA("PATH", NULL, 0)
            .return( SetLastError( ERROR_FILE_NOT_FOUND ) )
        .endif
        mov pathlen,eax
        .if !malloc(rax)
            .return( SetLastError( ERROR_NOT_ENOUGH_MEMORY ) )
        .endif
        mov pathalloc,rax
        mov rbx,rax
        GetEnvironmentVariableA("PATH", rbx, pathlen)
    .endif

    .while ( byte ptr [rbx] )

        .if strchr(rbx, ':')
            mov rcx,rax
            sub rcx,rbx
            lea rdx,[rax+1]
        .else
            strlen(rbx)
            mov rcx,rax
            lea rdx,[rbx+rax]
        .endif
        mov nextdir,rdx
        mov dirlen,rcx
        mov rax,rcx
        add rax,fnlen
        add rax,extlen
        add rax,2
        .ifs ( rcx > 0 && rax < 4096 )
            memcpy(&cand, rbx, rcx)
            lea rcx,cand
            add rcx,dirlen
            .if ( byte ptr [rcx-1] != '/' )
                mov byte ptr [rcx],'/'
                inc rcx
            .endif
            mov candir,rcx
            memcpy(rcx, lpFileName, fnlen)
            mov rcx,candir
            add rcx,fnlen
            .if ( needext )
                mov candir,rcx
                memcpy(rcx, lpExtension, extlen)
                mov rcx,candir
                add rcx,extlen
            .endif
            mov byte ptr [rcx],0
            GetFileAttributesA(&cand)
            .if !( eax & S_IFDIR )
                .if ( pathalloc )
                    free(pathalloc)
                .endif
                strlen(&cand)
                mov ebx,eax
                mov edx,nBufferLength
                mov rcx,lpBuffer
                .if ( !rcx || edx <= ebx )
                    inc ebx
                   .return( ebx )
                .endif
                inc eax
                memcpy(rcx, &cand, eax)
                .if ( lpFilePart )
                    mov rcx,lpBuffer
                    mov rdx,rcx
                    .while ( byte ptr [rcx] )
                        .if ( byte ptr [rcx] == '/' )
                            lea rdx,[rcx+1]
                        .endif
                        inc rcx
                    .endw
                    mov rax,lpFilePart
                    mov [rax],rdx
                .endif
                .return( ebx )
            .endif
        .endif
        mov rbx,nextdir
    .endw
    .if ( pathalloc )
        free(pathalloc)
    .endif
    .return( SetLastError( ERROR_FILE_NOT_FOUND ) )
    endp

    end
