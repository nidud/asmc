; _TSEARCHENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; errno_t _searchenv(const char *, const char *, char *);
; errno_t _searchenv_s(const char *, const char *, char *, size_t);
; errno_t _wsearchenv(const wchar_t *, const wchar_t *, wchar_t *);
; errno_t _wsearchenv_s(const wchar_t *, const wchar_t *, wchar_t *, size_t);
;
include stdlib.inc
include io.inc
include errno.inc
include string.inc
include malloc.inc
include tchar.inc

.code

_tsearchenv_s proc uses rbx fname:tstring_t, env_var:tstring_t, path:tstring_t, size:size_t

   .new p:tstring_t
   .new envbuf:tstring_t = NULL
   .new env_p:tstring_t
   .new save_env_p:tstring_t
   .new len:size_t
   .new pathbuf[_MAX_PATH + 4]:tchar_t
   .new pbuf:tstring_t = NULL
   .new fnamelen:size_t
   .new buflen:size_t
   .new save_errno:errno_t
   .new acc:int_t
   .new retvalue:errno_t = 0

    ldr rbx,path
    ldr rax,size
    .if ( !rax || !rbx )

        _set_errno(EINVAL)
        .return( EINVAL )
    .endif

    ldr rcx,fname
    .if ( !rcx )

        mov tchar_t ptr [rbx],0
        _set_errno(EINVAL)
        .return( EINVAL )
    .endif

    .if ( tchar_t ptr [rcx] == 0 )

        mov tchar_t ptr [rbx],0
        _set_errno(ENOENT)
        .return( ENOENT )
    .endif

    _get_errno(&save_errno)
    mov acc,_taccess(fname, 0)
    _set_errno(save_errno)

    .if ( acc == 0 )

        .if ( _tfullpath(rbx, fname, size) == NULL )

            mov tchar_t ptr [rbx],0
            .return( _get_errno(0) )
        .endif
        .return( 0 )
    .endif

    .if ( _tdupenv_s(&envbuf, NULL, env_var) || envbuf == NULL )

        mov tchar_t ptr [rbx],0
        _set_errno(ENOENT)
        .return( ENOENT )
    .endif

    mov env_p,envbuf
    mov fnamelen,_tcslen(fname)
    mov pbuf,&pathbuf
    mov buflen,_countof(pathbuf)

    .if ( fnamelen >= buflen )

        _tcslen(env_p)
        add rax,fnamelen
        add rax,2
        mov buflen,rax
        mov pbuf,calloc( buflen, sizeof(tchar_t) )

        .if ( rax == NULL )

            mov tchar_t ptr [rbx],0
            mov retvalue,ENOMEM
            jmp cleanup
        .endif
    .endif
    _get_errno(&save_errno)

    .while ( env_p )

        mov save_env_p,env_p
        mov rcx,buflen
        sub rcx,fnamelen
        dec rcx
        mov env_p,_tgetpath(env_p, pbuf, rcx)
        mov ecx,errno
        lea rax,pathbuf
        .if ( env_p == NULL && rax == pbuf && ecx == ERANGE )

            _tcslen(save_env_p)
            add rax,fnamelen
            add rax,2
            mov buflen,rax
            mov pbuf,calloc( buflen, sizeof(tchar_t) )

            .if ( rax == NULL )

                mov tchar_t ptr [rbx],0
                mov retvalue,ENOMEM
                jmp cleanup
            .endif
            mov rcx,buflen
            sub rcx,fnamelen
            mov env_p,_tgetpath(save_env_p, pbuf, rcx)
        .endif

        mov rcx,pbuf
        .if ( env_p == NULL || tchar_t ptr [rcx] == 0 )
            .break
        .endif

        mov rcx,_tcslen(pbuf)
ifdef _UNICODE
        add rax,rax
endif
        add rax,pbuf
        mov _tdl,[rax-tchar_t]
ifdef __UNIX__
        .if ( _tdl != '/' )
            mov _tdl,'/'
else
        .if ( _tdl != '/' && _tdl != '\' && _tdl != ':' )
            mov _tdl,'\'
endif
            mov [rax],_tdl
            add rax,tchar_t
            inc rcx
        .endif
        mov len,rcx
        mov p,rax
        sub rax,pbuf
        mov rcx,buflen
        sub rcx,rax

        .break .ifd _tcscpy_s(p, rcx, fname)

        .ifd ( _taccess(pbuf, 0) == 0 )

            mov rax,len
            add rax,fnamelen
            .if ( rax >= size )

                mov tchar_t ptr [rbx],0
                _set_errno(ERANGE)
                mov retvalue,ERANGE
                jmp cleanup
            .endif
            _set_errno(save_errno)
            .break .ifd _tcscpy_s(path, size, pbuf)
            mov retvalue,0
            jmp cleanup
        .endif
    .endw

    mov tchar_t ptr [rbx],0
    _set_errno(ENOENT)
    mov retvalue,ENOENT

cleanup:
    lea rax,pathbuf
    .if ( rax != pbuf )
        free(pbuf)
    .endif
    free(envbuf)
    mov eax,retvalue
    ret

_tsearchenv_s endp


_tsearchenv proc fname:tstring_t, env_var:tstring_t, path:tstring_t

    _tsearchenv_s(ldr(fname), ldr(env_var), ldr(path), _MAX_PATH)
    ret

_tsearchenv endp

    end
