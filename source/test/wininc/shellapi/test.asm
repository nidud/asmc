include windows.inc
include shellapi.inc
include tchar.inc

.code

_tmain proc argc:SINT, argv:ptr

    local sei:SHELLEXECUTEINFO

    .if ecx == 3
        mov sei.cbSize,sizeof(sei)
        mov sei.fMask,SEE_MASK_FLAG_DDEWAIT
        mov sei.nShow,SW_SHOWNORMAL
        mov rax,[rdx+8]
        mov sei.lpVerb,rax
        mov rax,[rdx+16]
        mov sei.lpFile,rax
        ShellExecuteEx(&sei)
    .endif
    xor eax,eax
    ret

_tmain endp

    end _tstart