; FINDFIRSTFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include string.inc
include malloc.inc
include sys/stat.inc
include fileapi.inc
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

 FindFirstFileA proc WINAPI uses rbx lpFileName:LPCSTR, lpFindFileData:LPWIN32_FIND_DATAA
   .new dir:LPDIR
    ldr rbx,lpFileName
    .if ( malloc( &[strlen(rbx)+FFDATA] ) == NULL )
        dec rax
       .return
    .endif
    mov dir,rax
    .if ( strfn(rbx) == rbx )
        mov rcx,dir
        strcpy(&[rcx].FFDATA.path, "./")
        strcat(rax, rbx)
    .else
        mov rcx,dir
        strcpy(&[rcx].FFDATA.path, rbx)
    .endif
    mov rbx,dir
    mov [rbx].mask,strfn(rax)
    mov byte ptr [rax-1],0
    mov [rbx].dirp,opendir(&[rbx].path)
    .if ( rax == NULL )
        free(rbx)
       .return( -1 )
    .endif
    .ifd !FindNextFileA(rbx, lpFindFileData)
        FindClose( rbx )
       .return( -1 )
    .endif
    mov rax,rbx
    ret
    endp


 FindNextFileA proc WINAPI uses rbx hFindFile:HANDLE, lpFindFileData:LPWIN32_FIND_DATAA
   .new file:string_t
   .new q:_sstat
   .new path[2048]:char_t
    ldr rbx,hFindFile
    .while readdir( [rbx].dirp )
        mov file,&[rax].dirent.d_name
        .ifd ( strwild([rbx].mask, file) )
            strcat( strcat( strcpy(&path, &[rbx].path), "/" ), file )
            mov rcx,rax
            .ifd ( _xstat(rcx, &q) == 0 )
                assume rbx:LPWIN32_FIND_DATAA
                mov rbx,lpFindFileData
                strncpy(&[rbx].cFileName, file, lengthof(WIN32_FIND_DATA.cFileName))
                mov [rbx].dwFileAttributes,q.st_mode
                __timespec_to_ft(&q.st_ctime, &[rbx].ftCreationTime)
                __timespec_to_ft(&q.st_atime, &[rbx].ftLastAccessTime)
                __timespec_to_ft(&q.st_mtime, &[rbx].ftLastWriteTime)
                mov [rbx].nFileSizeLow,dword ptr q.st_size
ifdef _WIN64
                mov [rbx].nFileSizeHigh,dword ptr q.st_size[4]
else
                mov [rbx].nFileSizeHigh,0
endif
                assume rbx:ptr FFDATA
               .return( 1 )
            .endif
        .endif
    .endw
    ret
    endp


 FindClose proc WINAPI uses rbx hFindFile:HANDLE
    ldr rbx,hFindFile
    closedir( [rbx] )
    free(rbx)
    .return( 1 )
    endp

    end
