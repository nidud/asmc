; CMEDIT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include io.inc
include time.inc

editzip proto
topensession proto
wedit proto :dword, :dword
TVGetCurrentFile proto :dword
loadiniproc proto :dword, :dword, :dword
ifdef __HEDIT__
hedit proto :LPSTR, :dword
endif
    .code

load_tedit proc uses esi ebx file, etype

  local path[_MAX_PATH*2]:byte

    lea esi,path
    .if !strchr(strcpy(esi, file), '.')

        strcat(esi, &cp_dotdot[1])
    .endif

    .if !loadiniproc("Edit", esi, etype)

        clrcmdl()

        .if panel_findnext(cpanel)

            mov ebx,cpanel
            mov ebx,[ebx].S_PANEL.pn_wsub
            wedit([ebx].S_WSUB.ws_fcb, [ebx].S_WSUB.ws_count)
        .else
            .if byte ptr [esi] == '"'

                inc esi
                .if strrchr(esi,'"')

                    mov byte ptr [eax],0
                .endif
            .endif
ifdef __HEDIT__
            mov eax,keyshift
            mov eax,[eax]
            .if al & KEY_CTRL   ; 2 (Ctrl)
                hedit(esi, 0)
            .else
endif
                tedit(esi, 0)
ifdef __HEDIT__
            .endif
endif
        .endif
        xor eax,eax
    .endif
    ret
load_tedit endp

cmedit proc uses ebx

  local fname[_MAX_PATH*2]:byte

    lea ebx,fname

    .switch TVGetCurrentFile(ebx)
      .case 1
        .if ecx == eax
            mov ecx,4
        .endif
        load_tedit(ebx, ecx)
        .endc
      .case 2
        editzip()
    .endsw
    ret
cmedit endp

unzip_to_temp proto :dword, :dword

zipadd proc private uses esi edi archive, path, file

    strpath(strcpy(__srcpath, strcpy(__srcfile, file)))
    strcpy(__outpath, path)
    strcpy(__outfile, archive)

    .if osopen(file, _A_NORMAL, M_RDONLY, A_OPEN) != -1
        mov esi,eax
        .if _filelength(eax)
            mov edi,eax
            _close(esi)
            clock()
            push    eax
            getfattr(file)
            pop edx
            xor ecx,ecx
            wzipadd(ecx::edi, edx, eax)
        .else
            _close(esi)
            dec eax
        .endif
    .endif
    ret
zipadd endp

editzip proc uses esi edi

    mov edi,ecx
    .if unzip_to_temp(edx, ebx)
        mov esi,_diskflag
        setfattr(eax, 0)
        mov byte ptr _diskflag,0
        tedit(ebx, 0)
        mov eax,_diskflag
        .if eax
            mov eax,cpanel
            mov eax,[eax].S_PANEL.pn_wsub
            mov edx,[eax].S_WSUB.ws_arch
            mov eax,[eax].S_WSUB.ws_file
            zipadd(eax, edx, ebx)
        .else
            mov _diskflag,esi
        .endif
        remove(ebx)
    .endif
    ret
editzip endp

cmwindowlist proc
    .if tdlgopen() > 2
        mov tinfo,eax
        jmp cmtmodal
    .elseif eax == 1
        mov tinfo,edx
        tclose()
    .elseif eax == 2
        tiflush(edx)
    .endif
    ret
cmwindowlist endp

cmtmodal proc

    .if tistate(tinfo)

        tmodal()
    .else

        topensession()
    .endif
    ret

cmtmodal endp

    END
