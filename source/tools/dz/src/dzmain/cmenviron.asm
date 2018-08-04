; CMENVIRON.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include malloc.inc
include io.inc
include string.inc
include stdio.inc
include errno.inc
include stdlib.inc
include syserrls.inc
include winbase.inc

MAXHIT      equ 128
CELLCOUNT   equ 18

    .data

externdef   IDD_DZEnviron:dword

DLG_Environ dd 0
FCB_Environ dd 0
event_keys  dd KEY_F2,  event_add
            dd KEY_F3,  event_load
            dd KEY_F4,  event_edit
            dd KEY_F5,  event_save
            dd KEY_F8,  event_delete
            dd 0

    .code

    option  proc:private

getcurobj proc
    xor eax,eax
    mov edx,FCB_Environ
    .if [edx].S_LOBJ.ll_count != eax
    mov eax,[edx].S_LOBJ.ll_index
    add eax,[edx].S_LOBJ.ll_celoff
    mov edx,[edx].S_LOBJ.ll_list
    lea edx,[edx+eax*4]
    mov eax,[edx]
    test    eax,eax
    .endif
    ret
getcurobj endp

putcelid proc uses ebx
    mov ebx,DLG_Environ
    movzx   eax,[ebx].S_DOBJ.dl_index
    .if eax >= CELLCOUNT
    xor eax,eax
    .endif
    inc eax
    mov edx,FCB_Environ
    add eax,[edx].S_LOBJ.ll_index
    mov ecx,[edx].S_LOBJ.ll_count
    mov bx,[ebx+4]
    add bx,1403h
    mov dl,bh
    scputf(ebx, edx, 0, 0, "<%02d:%02d>", eax, ecx)
    ret
putcelid endp

read_environ proc uses esi edi ebx

    mov ebx,FCB_Environ
    mov eax,[ebx].S_LOBJ.ll_list
    .if eax
    xor edx,edx
    mov edi,eax
    .while  edx < [ebx].S_LOBJ.ll_count
        free  ([edi+edx*4])
        inc edx
    .endw
    xor eax,eax
    mov [ebx].S_LOBJ.ll_count,eax
    mov [ebx].S_LOBJ.ll_numcel,eax
    .if GetEnvironmentStrings()
        push    eax
        mov esi,eax
        .repeat
        mov al,[esi]
        .break .if !al
        .if al != '='
            _strdup(esi)
            stosd
            inc [ebx].S_LOBJ.ll_count
            mov eax,[ebx].S_LOBJ.ll_count
            .if eax <= CELLCOUNT
            inc [ebx].S_LOBJ.ll_numcel
            .endif
        .endif
        .break .if !strlen(esi)
        lea esi,[esi+eax+1]
        .until  0
        call    FreeEnvironmentStrings
        mov eax,[ebx].S_LOBJ.ll_count
    .endif
    .endif
    ret
read_environ endp

event_list proc uses esi edi ebx
    dlinit(DLG_Environ)
    mov ebx,DLG_Environ
    movzx   esi,[ebx].S_DOBJ.dl_rect.rc_x
    add esi,3
    movzx   edi,[ebx].S_DOBJ.dl_rect.rc_y
    add edi,2
    xor ebx,ebx
    .repeat
    mov edx,FCB_Environ
    .break .if ebx >= [edx].S_LOBJ.ll_numcel
    mov eax,ebx
    add eax,[edx].S_LOBJ.ll_index
    shl eax,2
    mov edx,[edx].S_LOBJ.ll_list
    add edx,eax
    mov ecx,[edx]
    strchr(ecx,'=')
    mov ecx,[edx]
    mov edx,eax
    .if !ZERO?
        mov byte ptr [eax],0
    .endif
    scputs(esi, edi, 0, 25, ecx)
    .if edx
        mov byte ptr [edx],'='
        inc edx
        mov eax,esi
        add eax,25
        scputs(eax, edi, 0, 45, edx)
    .endif
    inc edi
    inc ebx
    .until  0
    mov eax,1
    ret
event_list endp

update_cellid proc uses edi ebx
    call    putcelid
    call    event_list
    mov ebx,DLG_Environ
    mov edi,FCB_Environ
    mov ecx,CELLCOUNT
    mov eax,_O_STATE
    .repeat
    add ebx,16
    or  [ebx],ax
    .untilcxz
    mov ebx,DLG_Environ
    not eax
    mov ecx,[edi].S_LOBJ.ll_numcel
    .while  ecx
    add ebx,16
    and [ebx],ax
    dec ecx
    .endw
    mov eax,_C_NORMAL
    ret
update_cellid endp

event_xcell proc
    call    putcelid
    mov edx,DLG_Environ
    movzx   eax,[edx].S_DOBJ.dl_index
    mov edx,FCB_Environ
    mov [edx].S_LOBJ.ll_celoff,eax
    call    dlxcellevent
    ret
event_xcell endp

     ;--------------------------------------

event_edit proc uses esi edi ebx

local   variable[256]:byte
local   value[2048]:byte

    .if getcurobj()

    mov esi,eax
    lea ebx,value
    lea edi,variable
    xor edx,edx
    mov [ebx],dl

    .if strchr(esi, '=')

        mov byte ptr [eax],0
        mov edx,eax
        inc eax
        strcpy(ebx, eax)
    .endif
    strcpy(edi, esi)

    .if edx

        mov byte ptr [edx],'='
    .endif
    mov esi,edx

    .if tgetline(edi, ebx, 60, 2048)

        .if byte ptr [ebx]

        .if esi

            inc esi
            strcmp(esi, ebx)
            jz  toend
        .endif

        .if SetEnvironmentVariable(edi, ebx)

            call    read_environ
            call    update_cellid
        .endif
        .endif
    .endif
    .endif
toend:
    mov eax,_C_NORMAL
    ret
event_edit endp

event_add proc uses esi edi ebx

local   environ[2048]:byte

    lea ebx,environ
    mov byte ptr [ebx],0

    .if tgetline("Format: <variable>=<value>", ebx, 60, 2048)

    .if byte ptr [ebx]

        .if strchr(ebx, '=')

        mov byte ptr [eax],0
        inc eax
        .if SetEnvironmentVariable(ebx, eax)

            read_environ()
            update_cellid()
        .endif
        .endif
    .endif
    .endif
    mov eax,_C_NORMAL
    ret

event_add endp

event_delete proc uses esi ebx

    .if getcurobj()

    mov esi,eax
    .if strchr(eax, '=')

        mov byte ptr [eax],0
        mov ebx,eax
        SetEnvironmentVariable(esi, 0)
        mov byte ptr [ebx],'='

        .if eax

        mov ebx,FCB_Environ
        .if !read_environ()

            mov [ebx].S_LOBJ.ll_index,eax
            mov [ebx].S_LOBJ.ll_celoff,eax
        .else
            mov edx,[ebx].S_LOBJ.ll_index
            mov ecx,[ebx].S_LOBJ.ll_celoff

            .if edx

            mov esi,eax
            sub esi,edx

            .if esi < CELLCOUNT

                dec edx
                inc ecx
            .endif
            .endif

            sub eax,edx
            .if eax >= CELLCOUNT

            mov eax,CELLCOUNT
            .endif
            .if ecx >= eax

            dec ecx
            .endif

            mov [ebx].S_LOBJ.ll_index,edx
            mov [ebx].S_LOBJ.ll_celoff,ecx
            mov [ebx].S_LOBJ.ll_numcel,eax
            mov ebx,DLG_Environ
            test    eax,eax
            mov al,cl
            .ifz
            mov al,CELLCOUNT-1
            .endif
            mov [ebx].S_DOBJ.dl_index,al
            call    update_cellid
        .endif
        .endif
    .endif
    .endif
    mov eax,_C_NORMAL
    ret

event_delete endp

event_load proc

local   path[_MAX_PATH]:sbyte

    .if wgetfile(addr path, "*.env", _WOPEN)

    _close(eax)
    ReadEnvironment(addr path)
    read_environ()
    update_cellid()
    .endif
    mov eax,_C_NORMAL
    ret

event_load endp

event_save proc

local   path[_MAX_PATH]:sbyte

    .if wgetfile(addr path, "*.env", _WSAVE)

    _close(eax)
    SaveEnvironment(addr path)
    .endif
    mov eax,_C_NORMAL
    ret

event_save endp

    option  proc: PUBLIC

cmenviron proc uses esi edi ebx

local   cursor:S_CURSOR
local   ll:S_LOBJ

    lea edx,ll
    mov FCB_Environ,edx
    mov edi,edx
    xor eax,eax
    mov ecx,SIZE S_LOBJ
    rep stosb

    mov [edx].S_LOBJ.ll_dcount,CELLCOUNT
    mov [edx].S_LOBJ.ll_proc,event_list

    .if malloc((MAXHIT * 4) + 4)

    lea edx,ll
    mov [edx].S_LOBJ.ll_list,eax
    call    clrcmdl
    CursorGet(addr cursor)

    .if rsopen(IDD_DZEnviron)

        mov DLG_Environ,eax
        mov ebx,eax
        mov edi,[ebx].S_DOBJ.dl_object
        mov [edi].S_TOBJ.to_data[24*16],offset event_keys
        lea edx,[edi].S_TOBJ.to_proc
        mov ecx,CELLCOUNT
        mov eax,event_xcell
        .repeat
        mov [edx],eax
        add edx,SIZE S_TOBJ
        .untilcxz

        dlshow(ebx)
        mov eax,FCB_Environ
        mov tdllist,eax
        call    read_environ
        call    update_cellid

        .while  rsevent(IDD_DZEnviron, ebx)

        .switch eax
          .case 1..19
            .break .if event_edit() != _C_NORMAL
            .endc
          .case 20
            call    event_add
            .endc
          .case 21
            call    event_delete
            .endc
          .case 22
            call    event_load
            .endc
          .case 23
            call    event_save
            .endc
        .endsw
        .endw
        dlclose(ebx)
    .endif

    mov ebx,FCB_Environ
    mov eax,[ebx].S_LOBJ.ll_list
    .if eax

        xor edx,edx
        mov eax,[ebx].S_LOBJ.ll_list
        .while  edx < [ebx].S_LOBJ.ll_count
        free([eax+edx*4])

        inc edx
        .endw
        free([ebx].S_LOBJ.ll_list)
    .endif
    .else
    ermsg(0, addr CP_ENOMEM)
    .endif

    GetEnvironmentTEMP()
    GetEnvironmentPATH()
    CursorSet(addr cursor)
    xor eax,eax
    ret

cmenviron endp

    END
