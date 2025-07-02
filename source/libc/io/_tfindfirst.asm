; _TFINDFIRST.ASM--
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
ifdef _WIN64
define _xstat <_stat64>
define _sstat <_stati64>
else
define _xstat <_stat>
define _sstat <_stat32>
endif

.template FFDATA
    dirp LPDIR ?
    mask string_t ?
    path char_t 3 dup(?)
   .ends

   .code

    assume rbx:ptr FFDATA

_tfindnext proc uses rbx handle:ptr, ff:ptr _tfinddata_t

   .new file:string_t
   .new q:_sstat
   .new path[1024]:char_t

    ldr rbx,handle

    .while 1

        .if ( !readdir( [rbx].dirp ) )

            dec rax
           .return
        .endif

        mov file,&[rax].dirent.d_name

        .ifd ( _tcswild([rbx].mask, file) )

            strcat( strcat( strcpy(&path, &[rbx].path), "/" ), file )

            mov rcx,rax
            .ifd ( _xstat(rcx, &q) == 0 )

                assume rbx:ptr _tfinddata_t
                mov rbx,ff
                strcpy(&[rbx].name, file)
                mov [rbx].attrib,q.st_mode
                mov [rbx].time_create,q.st_ctime
                mov [rbx].time_access,q.st_atime
                mov [rbx].time_write,q.st_mtime
                mov [rbx].size,q.st_size
                assume rbx:ptr FFDATA
               .return( 0 )
            .endif
        .endif
    .endw
    ret

_tfindnext endp


_tfindfirst proc uses rbx lpFileName:tstring_t, ff:ptr _tfinddata_t

   .new dir:ptr DIR

    ldr rbx,lpFileName

    .if ( malloc( &[strlen(rbx)+FFDATA] ) == NULL )

        dec rax
       .return
    .endif
    mov dir,rax

    .if ( _tcsfn(rbx) == rbx )

        mov rcx,dir
        strcpy(&[rcx].FFDATA.path, "./")
        strcat(rax, rbx)
    .else
        mov rcx,dir
        strcpy(&[rcx].FFDATA.path, rbx)
    .endif
    mov rbx,dir
    mov [rbx].mask,_tcsfn(rax)
    mov byte ptr [rax-1],0
    mov [rbx].dirp,opendir(&[rbx].path)

    .if ( rax == NULL )

        free(rbx)
       .return( -1 )
    .endif

    .ifd ( _tfindnext(rbx, ff) == -1 )

        _findclose( rbx )
        .return( -1 )
    .endif
    mov rax,rbx
    ret

_tfindfirst endp


else

   .code

    ASSUME  rsi:ptr WIN32_FIND_DATA
    ASSUME  rdi:ptr _tfinddata_t

copyblock proc private

    mov eax,[rsi].dwFileAttributes
    .if ( eax == FILE_ATTRIBUTE_NORMAL )
        xor eax,eax
    .endif
    mov [rdi].attrib,eax
    mov [rdi].size,[rsi].nFileSizeLow

    __timet_from_ft( addr [rsi].ftCreationTime )
    mov [rdi].time_create,rax
    __timet_from_ft( addr [rsi].ftLastAccessTime )
    mov [rdi].time_access,rax
    __timet_from_ft( addr [rsi].ftLastWriteTime )
    mov [rdi].time_write,rax

    lea rsi,[rsi].cFileName
    lea rdi,[rdi].name
    mov ecx,(260/4)*tchar_t
    rep movsd
    xor eax,eax
    ret

copyblock endp


_tfindnext proc uses rsi rdi handle:ptr, ff:ptr _tfinddata_t

  local wf:WIN32_FIND_DATA

    ldr rdi,ff
    lea rsi,wf

    .if FindNextFile( ldr(handle), rsi )
        copyblock()
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret

_tfindnext endp


_tfindfirst proc uses rsi rdi rbx lpFileName:tstring_t, ff:ptr _tfinddata_t

  local FindFileData:WIN32_FIND_DATA

    ldr rdi,ff
    lea rsi,FindFileData

    .ifd ( FindFirstFile( ldr(lpFileName), rsi ) != -1 )

        mov rbx,rax
        copyblock()
        mov rax,rbx
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret

_tfindfirst endp

endif ; __UNIX__

    end
