; _TFINDFIRSTI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include time.inc
ifdef __UNIX__
include direct.inc
include string.inc
include malloc.inc
include sys/stat.inc
else
include winbase.inc
endif
include tchar.inc

ifdef __UNIX__

.template FFDATA
    dirp LPDIR ?
    mask string_t ?
    path char_t 3 dup(?)
   .ends

   .code

    assume rbx:ptr FFDATA

_tfindnexti64 proc uses rbx handle:ptr, ff:ptr _tfinddatai64_t

   .new file:string_t
   .new q:_tstati64
   .new path[1024]:char_t

    ldr rbx,handle

    .while 1

        .if ( !readdir( [rbx].dirp ) )

            dec rax
           .return
        .endif

        mov file,&[rax].dirent.d_name

        .ifd ( _twildcard([rbx].mask, file) )

            mov rcx,strcat( strcat( strcpy(&path, &[rbx].path), "/" ), file )

            .ifd ( _tstat64(rcx, &q) == 0 )

                assume rbx:ptr _tfinddatai64_t
                mov rbx,ff
                strcpy(&[rbx].name, file)
                mov [rbx].attrib,q.st_mode
ifdef _WIN64
                mov [rbx].time_create,q.st_ctime
                mov [rbx].time_access,q.st_atime
                mov [rbx].time_write,q.st_mtime
else
                mov eax,dword ptr q.st_ctime
                mov [rbx].time_create,eax
                mov eax,dword ptr q.st_atime
                mov [rbx].time_access,eax
                mov eax,dword ptr q.st_mtime
                mov [rbx].time_write,eax
endif
                mov [rbx].size,q.st_size
                assume rbx:ptr FFDATA
               .return( 0 )
            .endif
        .endif
    .endw
    ret

_tfindnexti64 endp


_tfindfirsti64 proc uses rbx lpFileName:LPTSTR, ff:ptr _tfinddatai64_t

   .new dir:ptr DIR

    ldr rbx,lpFileName

    .if ( malloc( &[strlen(rbx)+FFDATA] ) == NULL )

        dec rax
       .return
    .endif
    mov dir,rax

    .if ( _tstrfn(rbx) == rbx )

        mov rcx,dir
        strcpy(&[rcx].FFDATA.path, "./")
        strcat(rax, rbx)
    .else
        mov rcx,dir
        strcpy(&[rcx].FFDATA.path, rbx)
    .endif
    mov rbx,dir
    mov [rbx].mask,_tstrfn(rax)
    mov byte ptr [rax-1],0
    mov [rbx].dirp,opendir(&[rbx].path)

    .if ( rax == NULL )

        free(rbx)
       .return( -1 )
    .endif

    .ifd ( _tfindnexi64(rbx, ff) == -1 )

        _findclose( rbx )
        .return( -1 )
    .endif
    mov rax,rbx
    ret

_tfindfirsti64 endp


else

   .code

    ASSUME  rsi:ptr WIN32_FIND_DATA
    ASSUME  rdi:ptr _tfinddatai64_t

copyblock proc private

    mov eax,[rsi].dwFileAttributes
    .if ( eax == FILE_ATTRIBUTE_NORMAL )
        xor eax,eax
    .endif
    mov [rdi].attrib,eax
    mov eax,[rsi].nFileSizeLow
    mov dword ptr [rdi].size,eax
    mov eax,[rsi].nFileSizeHigh
    mov dword ptr [rdi].size[4],eax

    __timet_from_ft( addr [rsi].ftCreationTime )
    mov [rdi].time_create,rax
    __timet_from_ft( addr [rsi].ftLastAccessTime )
    mov [rdi].time_access,rax
    __timet_from_ft( addr [rsi].ftLastWriteTime )
    mov [rdi].time_write,rax

    lea rsi,[rsi].cFileName
    lea rdi,[rdi].name
    mov rcx,(260/4)*TCHAR
    rep movsd
    xor eax,eax
    ret

copyblock endp


_tfindnexti64 proc uses rsi rdi handle:ptr, ff:ptr _tfinddatai64_t

  local wf:WIN32_FIND_DATA

    ldr rcx,handle
    ldr rdi,ff
    lea rsi,wf

    .if FindNextFile( rcx, rsi )
        copyblock()
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret

_tfindnexti64 endp


_tfindfirsti64 proc uses rsi rdi rbx lpFileName:LPTSTR, ff:ptr _tfinddatai64_t

  local FindFileData:WIN32_FIND_DATA

    ldr rcx,lpFileName
    ldr rdi,ff
    lea rsi,FindFileData

    .ifd ( FindFirstFile( rcx, rsi ) != -1 )

        mov rbx,rax
        copyblock()
        mov rax,rbx
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret

_tfindfirsti64 endp

endif ; __UNIX__

    end
