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

PNODE typedef ptr DNODE
.template DNODE
    next PNODE ?
    file char_t 1 dup(?)
   .ends

   .code

copyblock proc private uses rbx path:string_t, ff:ptr _tfinddatai64_t

ifdef _WIN64

   .new q:_tstati64
    mov rbx,rsi

    .if _tstat64(rdi, &q)

       .return
    .endif
    strcpy(&[rbx]._tfinddatai64_t.name, _tstrfn(path))
    mov [rbx]._tfinddatai64_t.attrib,q.st_mode
    mov [rbx]._tfinddatai64_t.time_create,q.st_ctime
    mov [rbx]._tfinddatai64_t.time_access,q.st_atime
    mov [rbx]._tfinddatai64_t.time_write,q.st_mtime
    mov [rbx]._tfinddatai64_t.size,q.st_size
    xor eax,eax

else
    mov eax,-1
endif
    ret

copyblock endp


_tfindnexti64 proc uses rbx handle:ptr, ff:ptr _tfinddatai64_t

ifdef _WIN64

    mov rax,[rdi].DNODE.next
    .if ( rax )

        mov rbx,rax
        mov rcx,[rax].DNODE.next
        mov [rdi].DNODE.next,rcx
        copyblock(&[rax].DNODE.file, rsi)

        mov rdi,rbx
        mov rbx,rax
        free(rdi)
        mov rax,rbx

    .elseif ( [rdi].DNODE.file )

        mov rbx,rdi
        copyblock(&[rax].DNODE.file, rsi)
        mov [rbx].DNODE.file,0
    .else
        dec rax
    .endif
else
    mov eax,-1
endif
    ret

_tfindnexti64 endp


_tfindfirsti64 proc uses rbx lpFileName:LPTSTR, ff:ptr _tfinddatai64_t

   .new dir:ptr DIR
   .new directory[512]:char_t
   .new mask:string_t
   .new file:string_t
   .new base:PNODE = NULL
   .new next:PNODE

    mov directory[0],'.'
    mov directory[1],0

    ldr rbx,lpFileName
    mov mask,_tstrfn(rbx)

    .if ( rax > rbx )

        mov byte ptr [rax-1],0
        strcpy(&directory, rbx)
        mov rax,mask
        mov byte ptr [rax-1],'/'
    .endif

    lea rbx,directory
    mov file,&[rbx+strlen(rbx)]

    .if ( opendir( rbx ) != NULL )

        mov dir,rax

        .while ( readdir( dir ) )

            mov rbx,rax
            .if ( _twildcard( mask, &[rbx].dirent.d_name ) )

                mov rcx,file
                mov eax,'/'
                mov [rcx],ax
                strcat( rcx, &[rbx].dirent.d_name )
                add strlen( &directory ),DNODE

                .if malloc( eax )

                    .if ( base )
                        mov rcx,next
                        mov [rcx].DNODE.next,rax
                    .else
                        mov base,rax
                    .endif
                    mov next,rax
                    mov [rax].DNODE.next,NULL
                    strcpy( &[rax].DNODE.file, &directory )
                .endif
                mov rcx,file
                mov byte ptr [rcx],0
            .endif
        .endw
        closedir( dir )
    .endif

    mov rax,base
    .if ( rax == NULL )

        dec rax
       .return
    .endif

    .ifd ( _tfindnext(rax, ff) == -1 )

        _findclose( base )
        .return( -1 )
    .endif
    mov rax,base
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
