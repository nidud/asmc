include crtl.inc
include io.inc
include time.inc
include winbase.inc

    .code

    option win64:rsp nosave

_findnext PROC USES rsi rdi handle: HANDLE, ff: ptr _finddata_t

    local wf:WIN32_FIND_DATA

    mov rdi,rdx
    lea rsi,wf
    .if FindNextFileA(rcx, rsi)
        copyblock()
    .else
        osmaperr()
    .endif
    ret

_findnext ENDP

_findfirst PROC USES rsi rdi rbx lpFileName:LPSTR, ff:PTR _finddata_t

    local FindFileData:WIN32_FIND_DATAA

    mov rdi,rdx
    lea rsi,FindFileData
    .ifd FindFirstFileA(rcx, rsi) != -1
        mov rbx,rax
        copyblock()
        mov rax,rbx
    .else
        osmaperr()
    .endif
    ret

_findfirst ENDP

_findclose PROC h:HANDLE

    .if !FindClose(rcx)
        osmaperr()
    .else
        xor eax,eax
    .endif
    ret

_findclose ENDP

    ASSUME  rsi:ptr WIN32_FIND_DATAA
    ASSUME  rdi:ptr _finddata_t

copyblock proc private
    mov eax,[rsi].dwFileAttributes
    mov [rdi].attrib,eax
    mov eax,[rsi].nFileSizeLow
    mov dword ptr [rdi]._size,eax
    mov eax,[rsi].nFileSizeHigh
    mov dword ptr [rdi]._size[4],eax
    __FTToTime( addr [rsi].ftCreationTime )
    mov [rdi].time_create,eax
    __FTToTime( addr [rsi].ftLastAccessTime )
    mov [rdi].time_access,eax
    __FTToTime( addr [rsi].ftLastWriteTime )
    mov [rdi].time_write,eax
    lea rsi,[rsi].cFileName
    lea rdi,[rdi]._name
    mov rcx,260/4
    rep movsd
    xor eax,eax
    ret
copyblock endp

    END
