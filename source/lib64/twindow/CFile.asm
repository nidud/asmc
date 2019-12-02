; CFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include CFile.inc
include strlib.inc
include malloc.inc
include crtl.inc

    .code

    assume rcx:cfile_t
    option win64:rsp noauto

CFile::Select proc

    xor eax,eax

    .if !( [rcx].flag & _A_UPDIR )

        or  [rcx].flag,_A_SELECTED
        inc eax
    .endif
    ret

CFile::Select endp


CFile::Invert proc

    xor eax,eax

    .if !( [rcx].flag & _A_UPDIR )

        xor [rcx].flag,_A_SELECTED
        inc eax
    .endif
    ret

CFile::Invert endp


    assume rsi:cfile_t
    option win64:rbp

CFile::Color proc uses rsi rdi rbx hwnd:window_t, config:config_t

    mov rsi,rcx
    mov rbx,[rdx].TWindow.Color

    .repeat

        .if !( [rsi].flag & _A_SUBDIR )

            mov rdi,[rsi].name

            .if strext(rdi)

                lea rdi,[rax+1]
            .endif

            .if config.GetEntry("FileColor", rdi)

                .if strtolx(rax) <= 15

                    shl eax,4
                    .if al != [rbx+BG_PANEL]

                        shr eax,4
                        .break
                    .endif
                .endif
            .endif
        .endif

        mov eax,[rsi].flag

        .switch
          .case eax & _A_SELECTED
            mov al,[rbx+FG_PANEL]
            .break
          .case eax & _A_UPDIR
            mov al,7
            .break
          .case eax & _A_ROOTDIR
          .case eax & _A_SYSTEM
            mov al,[rbx+FG_SYSTEM]
            .break
          .case eax & _A_HIDDEN
            mov al,[rbx+FG_HIDDEN]
            .break
          .case eax & _A_SUBDIR
            mov al,[rbx+FG_SUBDIR]
            .break
          .default
            mov al,[rbx+FG_FILES]
            .break
        .endsw

    .until 1

    or al,[rbx+BG_PANEL]
    movzx eax,al
    ret

CFile::Color endp


CFile::Release proc

    free([rcx].name)
    free(this)
    ret

CFile::Release endp

    .data
    CFileVTable CFileVtbl { CFile_Release, CFile_Invert, CFile_Select, CFile_Color }
    .code

CFile::CFile proc

    .return .if !malloc(CFile)

    lea rcx,CFileVTable
    mov [rax].CFile.lpVtbl,rcx

    xor ecx,ecx
    mov [rax].CFile.flag,ecx
    mov [rax].CFile.time,ecx
    mov [rax].CFile.size,rcx
    mov [rax].CFile.name,rcx
    ret

CFile::CFile endp

    end
