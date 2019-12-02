; COMMAND.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include tview.inc
include process.inc
include string.inc
include malloc.inc
include stdio.inc
include stdlib.inc
include io.inc
include crtl.inc
include cfini.inc
include winbase.inc

    .data

com_wsub  dd path_a
com_base  db WMAXPATH dup(0)
com_info  TEDIT <com_base,_TE_OVERWRITE,0,24,80,WMAXPATH,0720h,0,0,0,0,0>

    .code

comhndlevent proc private
    .if cflag & _C_COMMANDLINE

        CursorOn() ; preserve EAX
        dledite(addr com_info, eax)
        ret
    .endif
    xor eax,eax
    ret
comhndlevent endp

cominit proc wsub
    mov eax,wsub
    mov com_wsub,eax
    wsinit(eax)
    cominitline()
    mov eax,1
    ret
cominit endp

cominitline proc private uses ebx

    mov ebx,DLG_Commandline
    .if ebx && [ebx].S_DOBJ.dl_flag & _D_DOPEN

        movzx eax,[ebx].S_DOBJ.dl_rect.rc_x
        movzx edx,[ebx].S_DOBJ.dl_rect.rc_y
        mov com_info.ti_ypos,edx
        mov com_info.ti_xpos,eax
        mov eax,com_wsub
        strlen([eax].S_WSUB.ws_path)
        inc eax
        .if eax > 51
            mov eax,51
        .endif
        mov com_info.ti_xpos,eax
        mov edx,_scrcol
        sub edx,eax
        mov com_info.ti_cols,edx
        _gotoxy(eax, com_info.ti_ypos)

        .if [ebx].S_DOBJ.dl_flag & _D_ONSCR

            mov edx,com_info.ti_ypos
            scputw(0, edx, _scrcol, ' ')
            mov eax,com_wsub
            scpath(0, edx, 50, [eax].S_WSUB.ws_path)
            mov al,byte ptr com_info.ti_xpos
            dec al
            scputw(eax, edx, 1, 62) ; '>'
            mov eax,KEY_PGUP
            comhndlevent()
        .else
            mov eax,[ebx].S_DOBJ.dl_wp
            wcputw(eax, _scrcol, ' ')
            add eax,com_info.ti_xpos
            add eax,com_info.ti_xpos
            sub eax,2
            wcputw(eax, 1, 62)
            mov eax,com_wsub
            wcpath([ebx].S_DOBJ.dl_wp, 50, [eax].S_WSUB.ws_path)
        .endif
    .endif
    ret

cominitline endp

comshow proc

    mov eax,com_info.ti_ypos
    lea ecx,prect_b
    .if !(byte ptr [ecx] & _D_ONSCR)

        lea ecx,prect_a
    .endif

    .if (byte ptr [ecx] & _D_ONSCR)

        mov dl,[ecx].S_DOBJ.dl_rect.rc_y
        add dl,[ecx].S_DOBJ.dl_rect.rc_row
        .if dl > al

            mov al,dl
        .endif
    .endif

    .if !eax && cflag & _C_MENUSLINE

        inc eax
    .endif

    .if eax >= _scrrow && cflag & _C_STATUSLINE

        dec eax
    .endif

    .if eax > _scrrow

        mov eax,_scrrow
    .endif

    mov byte ptr com_info.ti_ypos,al
    mov edx,DLG_Commandline
    mov [edx+5],al

    .if cflag & _C_COMMANDLINE

        _gotoxy(0, eax)
        CursorOn()
        dlshow(DLG_Commandline)
        cominitline()
    .endif
    ret

comshow endp

comhide proc
    dlhide(DLG_Commandline)
    CursorOff()
    ret
comhide endp

comevent proc event

    mov eax,event
    .switch eax
      .case KEY_UP
        .if cpanel_state()

            xor eax,eax
        .else
            cmdoskeyup()
            mov eax,1
        .endif
        .endc
      .case KEY_DOWN
        .if cpanel_state()

            xor eax,eax
        .else
            cmdoskeydown()
            mov eax,1
        .endif
        .endc
      .case KEY_ALTRIGHT
        cmpathright()
        mov eax,1
        .endc
      .case KEY_ALTLEFT
        cmpathleft()
        mov eax,1
        .endc
      .case 0
      .case KEY_CTRLX
        xor eax,eax
        .endc
      .default
        .if comhndlevent()

            xor eax,eax
        .else
            mov eax,1
        .endif
    .endsw
    ret
comevent endp

clrcmdl proc
    .if cflag & _C_COMMANDLINE

        mov com_base,0
        comevent(KEY_HOME)
        cominitline()
    .endif
    ret
clrcmdl endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; command
;
command proc uses esi edi ebx cmd ; BOOL

  local cursor:S_CURSOR, batch, path, temp
  local UpdateEnviron, CallBatch

    mov eax,console
    and eax,CON_NTCMD
    CFGetComspec(eax)


    mov edi,alloca(8000h + _MAX_PATH*2 + 32)
    add eax,8000h
    mov batch,eax
    mov byte ptr [eax],0
    add eax,_MAX_PATH
    mov path,eax
    add eax,_MAX_PATH
    mov temp,eax

    mov edx,cmd
    .while byte ptr [edx] == ' '

        add edx,1
    .endw

    .return .if !strtrim(strnzcpy(edi, edx, 8000h-1))

    expenviron(edi)

    .if byte ptr [edi] == '%'

        ; %view% <filename>
        ; %edit% <filename>
        ; %find% [<directory>] [<file_mask(s)>] [<text_to_find_in_files>]

        .switch

          .case !_strnicmp(edi, "%view%", 6)

            load_tview(addr [edi+7], 0)
            .return 1

          .case !_strnicmp(edi, "%edit%", 6)

            load_tedit(addr [edi+7], 4)
            .return 1

          .case !_strnicmp(edi, "%find%", 6)

            .if byte ptr [edi+6] == ' '

                add edi,7
                strchr(edi, ' ')
                mov ecx,edi
                mov edi,eax
                .if strrchr(ecx, ' ')

                    mov byte ptr [edi],0    ; end of first arg
                    mov byte ptr [eax],0    ; start of last arg - 1
                    .if byte ptr [eax+1] != '?' && eax != edi

                        inc eax
                        strcpy(addr searchstring, eax)
                    .endif

                    .if byte ptr [edi+1] != '?'

                        strcpy(addr findfilemask, addr [edi+1])
                    .endif
                .endif
                .return FindFile(&[edi+7])
            .endif
            cmsearch()
            .return 1
          .default
            .return 0
        .endsw
    .endif

    clrcmdl()

    xor eax,eax
    mov CallBatch,eax
    mov UpdateEnviron,eax

    ; use batch for old .EXE files, \r\n, > and <

    .switch
      .case strchr(edi, '>')
      .case strchr(edi, '<')
      .case strchr(edi, 10)
        jmp create_batch
    .endsw

    ; case exit

    mov eax,[edi]
    or  eax,0x20202020

    .if eax == 'tixe' && byte ptr [edi+4] <= ' '

        .return cmquit()
    .endif

    ; Inline CD and C: commands

    mov edx,edi
    mov ecx,1

    .if word ptr [edi+1] != ':'

        mov eax,[edi]
        or  ax,0x2020

        .if ax != 'dc'

            xor ecx,ecx

        .else

            add edx,2

            mov al,[edx]

            .if al != ' ' && al != '.' && al != '\'

                xor ecx,ecx
            .endif
        .endif
    .endif

    .if ecx

        mov esi,edx
        .while byte ptr [esi] == ' '

            add esi,1
        .endw

        .if SetCurrentDirectory(esi)

            .if GetCurrentDirectory(_MAX_PATH, esi)

                cpanel_setpath(esi)
                mov _diskflag,3
            .endif
        .endif
        .return
    .endif


    ; Parse the first token

    strnzcpy(path, edi, _MAX_PATH-1)
    mov ebx,eax
    strtrim(eax)
    jz  execute_command

    .if byte ptr [ebx] == '"'

        .if strchr(strcpy(ebx, addr [ebx+1]), '"')

            mov byte ptr [eax],0
        .elseif strchr(ebx, ' ')
            mov byte ptr [eax],0
        .endif
    .elseif strchr(ebx, ' ')
        mov byte ptr [eax],0
    .endif

    .if !searchp(ebx)
        ;
        ; Not an executable file
        ;
        ; SET and FOR may change the environment
        ;
        __isexec(ebx)
        test eax,eax
        jnz execute_command
        mov eax,[ebx]
        and eax,00FFFFFFh
        or  eax,00202020h
        .switch eax
          ;
          ; Change or set environment variable
          ;
          .case 'tes'   ; SET
          .case 'rof'   ; FOR
            mov al,[edi+3]
            .switch al
              .case ' '
              .case 9
                inc UpdateEnviron
                jmp create_batch
            .endsw
        .endsw
        jmp execute_command
    .endif

    .switch __isexec(strcpy(ebx, eax))
      .case _EXEC_EXE
        .if comspec_type == 0

            .if osopen(ebx, 0, M_RDONLY, A_OPEN) != -1

                mov esi,eax
                push osread(esi, temp, 32)
                _close(esi)
                pop eax
                .if eax == 32

                    mov esi,temp
                    mov ax,[esi+24]
                    .if ax == 0040h

                        xor eax,eax
                        .if eax != [esi+20]

                            jmp create_batch
                        .endif
                    .endif
                .endif
            .endif
        .endif
        jmp execute_command
      .case _EXEC_CMD
      .case _EXEC_BAT
        mov CallBatch,eax
        mov UpdateEnviron,eax
      .case _EXEC_COM
        jmp create_batch
    .endsw

create_batch:

    mov eax,console
    and eax,CON_CMDENV
    .if !eax

        mov CallBatch,eax
        mov UpdateEnviron,eax
    .endif

    .if CreateBatch(edi, CallBatch, UpdateEnviron) != -1

        strcpy(batch, eax)
    .endif


execute_command:

    doszip_hide()
    _gotoxy(0, com_info.ti_ypos)
    CursorOn()
    system(edi)
    push eax

    .if UpdateEnviron

        strfcat(edi, envtemp, "dzcmd.env")
        ReadEnvironment(edi)
        removefile(edi)
        GetEnvironmentTEMP()
        GetEnvironmentPATH()
        .if !GetCurrentDirectory(WMAXPATH, edi)

            xor edi,edi
        .endif
    .endif

    doszip_show()
    SetKeyState()

    mov eax,batch
    .if byte ptr [eax]

        removefile(eax)
    .endif

    .if UpdateEnviron && edi

        cpanel_setpath(edi)
    .endif
    pop eax
    ret

command endp

    END

