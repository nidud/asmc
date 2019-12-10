; FILESEARCH.ASM--
; Copyright (C) 2019 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include tview.inc
include malloc.inc
include io.inc
include string.inc
include stdio.inc
include errno.inc
include FileSearch.inc

FF_CASE         equ 0x01 ; IO_SEARCHCASE
FF_HEX          equ 0x02 ; IO_SEARCHHEX
FF_OUTBINARY    equ 0x00 ; Binary dump (default)
FF_OUTTEXT      equ 0x04 ; Convert tabs, CR/LF
FF_OUTLINE      equ 0x08 ; Convert tabs, break on LF
FF_ONEHIT       equ 0x10 ; files only...
FF_SUBDIR       equ 0x20 ; IO_SEARCHSUB

externdef IDD_DZFFOptions:ptr_t

GetPathFromHistory proto :ptr

.enum { ID_SUBDIR,
        ID_CASE,
        ID_HEX,
        ID_ONEHIT,
        ID_SAVE }

.enum { ID_FILE = 12,
        ID_MASK,
        ID_LOCATION,
        ID_STRING,
        ID_START,
        ID_OPTIONS,
        ID_GOTO,
        ID_QUIT,
        ID_MOUSEUP,
        ID_MOUSEDN }

        TOFFSET equ <16+16>

ID_GCMD equ ID_MOUSEUP

    .data

    ff LPFILESEARCH 0

    GLCMD   struct
    key     uint_t ?
    cmdptr  ptr_t ?
    GLCMD   ends

    GlobalKeys GLCMD \
        { KEY_F2,     EventProc },
        { KEY_F3,     EventProc },
        { KEY_F4,     EventProc },
        { KEY_F5,     EventProc },
        { KEY_F6,     EventProc },
        { KEY_F7,     EventProc },
        { KEY_F8,     EventProc },
        { KEY_F9,     EventProc },
        { KEY_F10,    EventProc },
        { KEY_F11,    EventProc },
        { KEY_DEL,    EventProc },
        { KEY_ALTX,   EventProc },
        { 0,          0         }

    .code

    option proc: private

    assume esi:ptr S_DOBJ
    assume ebx:ptr FileSearch

FileSearch::PutCellId proc uses esi ebx

    mov ebx,this
    mov esi,[ebx].dialog

    movzx eax,[esi].dl_index
    .if al > ID_FILE
        xor eax,eax
    .endif

    inc eax
    add eax,[ebx].ll.ll_index
    mov ecx,[ebx].ll.ll_count
    mov bx,[esi+4]
    inc bl
    mov dl,bh
    scputf(ebx, edx, 0, 0, "%4d:%-4d", eax, ecx)
    ret

FileSearch::PutCellId endp


FileSearch::UpdateCell proc uses ebx

    mov ebx,this

    [ebx].PutCellId()
    [ebx].List()

    .for edx = [ebx].dialog,
         eax = _O_STATE,
         ecx = 0 : ecx <= ID_FILE : ecx++, edx += 16
        or [edx+16],ax
    .endf

    .for edx = [ebx].dialog,
         eax = not _O_STATE,
         ecx = [ebx].ll.ll_numcel : ecx : ecx--, edx += 16
        and [edx+16],ax
    .endf
    mov eax,_C_NORMAL
    ret

FileSearch::UpdateCell endp


FileSearch::CurItem proc uses ebx

    mov ebx,this
    xor eax,eax

    .if [ebx].ll.ll_count != eax

        mov eax,[ebx].ll.ll_index
        add eax,[ebx].ll.ll_celoff
        shl eax,2
        mov edx,[ebx].ll.ll_list
        add edx,eax
        mov eax,[edx]
    .endif
    ret

FileSearch::CurItem endp


FileSearch::CurFile proc

    .if this.CurItem()

        add eax,S_SBLK.sb_file
    .endif
    ret

FileSearch::CurFile endp


CallbackFile proc private uses esi edi ebx directory:string_t, wfblk:ptr

  local path[_MAX_PATH*2]:byte
  local fblk, offs, line, fbsize, ioflag, result

    mov edi,wfblk
    mov result,FFMAXHIT

    xor eax,eax
    mov offs,eax
    mov line,eax
    mov STDI.ios_line,eax

    mov ebx,ff
    xor esi,esi

    .if [ebx].ll.ll_count < FFMAXHIT

        mov result,eax
        .if filter_wblk(edi)

            add edi,WIN32_FIND_DATA.cFileName
            strfcat(&path, directory, edi)
            mov result,test_userabort()

            .ifz
                .if directory
                    .if cmpwarg(edi, fp_maskp)
                        inc esi
                    .endif
                .else
                    mov result,-1
                .endif
            .endif
        .endif
    .endif

    .if esi

        xor esi,esi

        cmp searchstring,0
        je  found

        mov edx,wfblk
        mov esi,osopen(&path, [edx].WIN32_FIND_DATA.dwFileAttributes, M_RDONLY, A_OPEN)
        mov STDI.ios_file,eax

        inc eax
        .ifnz ; @v2.33 -- continue seacrh if open fails..

            mov ecx,wfblk
            mov eax,[ecx].WIN32_FIND_DATA.nFileSizeLow
            mov edx,[ecx].WIN32_FIND_DATA.nFileSizeHigh
            mov STDI.fsize_l,eax
            mov STDI.fsize_h,edx

            xor eax,eax
            .if edx == eax  ; No search above 4G...

                mov STDI.offset_l,eax
                mov STDI.offset_h,eax
                mov STDI.ios_flag,IO_RETURNLF
                mov STDI.ios_i,eax
                mov STDI.ios_c,eax

                ioread(&STDI)
                mov eax,STDI.ios_c
                .if STDI.fsize_l <= eax
                    or STDI.ios_flag,IO_MEMBUF
                .endif

                xor eax,eax
                .if [ebx].flags & FF_CASE
                    or STDI.ios_flag,IO_SEARCHCASE
                .endif
                .if [ebx].flags & FF_HEX
                    or STDI.ios_flag,IO_SEARCHHEX
                .endif

                .repeat

                    oseek(eax, SEEK_SET)
                    .break .ifz

                    mov STDI.offset_l,eax
                    mov STDI.offset_h,edx
                    or  STDI.ios_flag,IO_SEARCHCUR
                    .break .if !searchstring

                    osearch()
                    .break .ifz

                    mov offs,eax
                    mov line,ecx

found:
                    lea edi,[strlen(&path)+BLOCKSIZE]

                    .if !malloc(edi)

                        dec eax
                        mov result,eax
                        .break
                    .endif

                    mov fblk,memset(eax, 0, edi)
                    add eax,S_SBLK.sb_file
                    lea ecx,path
                    strcpy(eax, ecx)

                    xor edx,edx
                    mov eax,[ebx].ll.ll_count
                    progress_update(edx::eax)

                    push eax
                    mov eax,[ebx].ll.ll_count
                    inc [ebx].ll.ll_count
                    mov edx,[ebx].ll.ll_count
                    .if edx > ID_FILE+1
                        mov edx,ID_FILE+1
                    .endif
                    mov [ebx].ll.ll_numcel,edx
                    mov edx,[ebx].ll.ll_list
                    mov ecx,fblk
                    mov [edx+eax*4],ecx
                    mov [ecx].S_SBLK.sb_size,edi
                    mov eax,line
                    mov [ecx].S_SBLK.sb_line,eax
                    mov eax,offs
                    mov [ecx].S_SBLK.sb_offs,eax
                    pop eax

                    .if eax ; user abort

                        mov result,eax
                        .break
                    .endif

                    push ecx
                    strlen([ebx].basedir)
                    pop ecx
                    inc eax
                    mov [ecx],ax

                    .break .if !esi

                    oseek(offs, SEEK_SET)

                    mov eax,fblk
                    lea eax,[eax+edi-INFOSIZE]
                    oreadb(eax, INFOSIZE-1)

                    mov eax,offs
                    inc eax
                    .if eax >= STDI.fsize_l
                        mov eax,STDI.fsize_l
                    .endif
                    oseek(eax, SEEK_SET)
                    .break .if result

                .until [ebx].ll.ll_count >= FFMAXHIT

            .endif

            .if esi

                _close(esi)
            .endif
        .endif
    .endif

    mov eax,result
    ret

CallbackFile endp


CallbackDirectory proc private directory:string_t

    .if !progress_set(0, directory, 0)

        scan_files(directory)
    .endif
    ret

CallbackDirectory endp


InitPath proc directory:string_t

    mov ecx,directory ; *.asm *.inc C: D:
    mov edx,' '       ; seperator assumed space
    .if [ecx] == dl
        add ecx,1     ; next item
    .endif
    .if byte ptr [ecx] == '"'
        inc ecx
        mov dl,'"'    ; seperator is quote
    .endif
    mov eax,ecx       ; start of item
    .repeat
        mov dh,[ecx]
        inc ecx
        .return .if !dh
    .until dh == dl
    mov byte ptr [ecx-1],0
    ret

InitPath endp


FileSearch::SearchPath proc uses esi edi ebx directory:string_t

  local path[_MAX_PATH]:byte, retval:int_t, length:int_t

    mov ebx,this
    mov [ebx].basedir,strcpy(&path, directory)
    xor ecx,ecx
    mov retval,ecx

    .if path == cl

        mov path,'"'
        inc eax
        mov edx,com_wsub
        strcpy(eax, [edx].S_WSUB.ws_path)
    .endif

    .repeat

        ; Multi search using quotes:
        ; Find Files: ["Long Name.type" *.c *.asm.......]
        ; Location:   ["D:\My Documents" c: f:\doc......]

        mov [ebx].basedir,InitPath([ebx].basedir)
        mov edi,ecx

        .if strlen(eax)

            mov length,eax

            add eax,[ebx].basedir
            .if byte ptr [eax-1] == '\'
                mov byte ptr [eax-1],0
            .endif

            mov ecx,[ebx].dialog
            mov fp_maskp,[ecx].S_TOBJ.to_data[ID_MASK*TOFFSET]

            .repeat

                mov fp_maskp,InitPath(fp_maskp)
                mov esi,ecx
                mov retval,edx

                .if [ebx].flags & FF_SUBDIR
                    scan_directory(1, [ebx].basedir)
                .else
                    push [ebx].basedir
                    call fp_directory
                .endif

                mov edx,retval
                mov retval,eax
                mov fp_maskp,esi

                .if dl == '"'
                    mov [esi-1],dl
                .endif
                .break .if byte ptr [esi] == 0
                mov [esi-1],dl

            .until eax

            mov eax,length
        .endif

        mov [ebx].basedir,edi

        .break .if retval
        .break .if byte ptr [edi] == 0

    .until !eax

    mov eax,retval
    ret

FileSearch::SearchPath endp


FileSearch::Find proc uses esi edi ebx

  local cursor:S_CURSOR

    mov fp_directory,CallbackDirectory
    mov fp_fileblock,CallbackFile

    mov STDI.ios_size,4096 ; default to _bufin
    mov STDI.ios_bp,offset _bufin

    .if malloc(0x800000)

        mov STDI.ios_bp,eax
        mov STDI.ios_size,0x800000
    .endif

    mov ebx,this
    mov edx,[ebx].dialog

    .if !( [edx].S_TOBJ.to_flag[ID_GOTO*TOFFSET] & _O_STATE )

        CursorGet(&cursor)
        CursorOff()
        [ebx].ClearList()
        dlinit( [ebx].dialog )
        mov edx,[ebx].dialog
        mov ax,[edx+4]
        add ax,0x0F03
        mov dl,ah
        scputw(eax, edx, 11, 0x00C4)
        progress_open(&cp_search, 0)

        mov edx,[ebx].dialog
        mov edi,[edx].S_TOBJ.to_data[ID_LOCATION*TOFFSET]

        progress_set(edi, 0, FFMAXHIT+2)
        [ebx].SearchPath(edi)
        progress_close()

        CursorSet(&cursor)

        mov eax,[ebx].ll.ll_count
        .if eax > ID_FILE+1
            mov eax,ID_FILE+1
        .endif
        mov [ebx].ll.ll_numcel,eax
        [ebx].UpdateCell()
    .endif

    .if STDI.ios_size != 4096

        free(STDI.ios_bp)
    .endif

    memset(&STDI, 0, S_IOST)
    ret

FileSearch::Find endp


FileSearch::Options proc uses esi edi ebx

    .if rsopen(IDD_DZFFOptions)

        mov esi,eax
        mov ebx,this

        .if [ebx].flags & FF_CASE
            or [esi+ID_CASE*TOFFSET].dl_flag,_O_FLAGB
        .endif
        .if [ebx].flags & FF_HEX
            or [esi+ID_HEX*TOFFSET].dl_flag,_O_FLAGB
        .endif
        .if [ebx].flags & FF_SUBDIR
            or [esi+ID_SUBDIR*TOFFSET].dl_flag,_O_FLAGB
        .endif
        .if [ebx].flags & FF_ONEHIT
            or [esi+ID_ONEHIT*TOFFSET].dl_flag,_O_FLAGB
        .endif

        dlshow(esi)
        dlinit(esi)

        .if rsevent(IDD_DZFFOptions, esi)
            mov eax,[ebx].flags
            and eax,not (FF_CASE or FF_HEX or FF_SUBDIR or FF_ONEHIT)
            .if [esi+ID_CASE*TOFFSET].dl_flag & _O_FLAGB
                or eax,FF_CASE
            .endif
            .if [esi+ID_HEX*TOFFSET].dl_flag & _O_FLAGB
                or eax,FF_HEX
            .endif
            .if [esi+ID_SUBDIR*TOFFSET].dl_flag & _O_FLAGB
                or eax,FF_SUBDIR
            .endif
            .if [esi+ID_ONEHIT*TOFFSET].dl_flag & _O_FLAGB
                or eax,FF_ONEHIT
            .endif
            mov [ebx].flags,eax
        .endif
        dlclose(esi)
    .endif
    mov eax,_C_NORMAL
    ret

FileSearch::Options endp


FileSearch::Modal proc uses esi edi ebx

    mov ebx,this
    mov filter,0

    .while rsevent(IDD_DZFindFile, [ebx].dialog)

        mov esi,eax
        mov edi,ecx
        mov edx,[ebx].dialog

        mov al,[edx].S_DOBJ.dl_index
        .if al <= ID_FILE

            .break .if [ebx].WndProc(KEY_F3) != _C_NORMAL
        .else
            .break .if al == ID_GOTO

            [ebx].Find()
        .endif
    .endw
    ret

FileSearch::Modal endp


FileSearch::List proc uses esi edi ebx

  local x,count

    mov ebx,this

    dlinit([ebx].dialog)

    mov     eax,[ebx].dialog
    movzx   esi,[eax].S_DOBJ.dl_rect.rc_x
    add     esi,4
    movzx   edi,[eax].S_DOBJ.dl_rect.rc_y
    add     edi,2

    .for edx = [ebx].ll.ll_index,
         edx <<= 2,
         edx += [ebx].ll.ll_list,
         ecx = [ebx].ll.ll_numcel : ecx : edi++, ecx--, edx += 4

        mov eax,[edx]
        add eax,[eax]
        add eax,S_FBLK.fb_name
        scpath(esi, edi, 25, eax)

        add eax,esi
        mov x,esi
        mov esi,edx

        mov edx,[edx]
        mov edx,[edx].S_SBLK.sb_line

        .if edx

            inc edx ; append (<line>) to filename
            scputf(eax, edi, 0, 7, "(%u)", edx)
        .endif

        mov count,ecx
        mov edx,esi

        lea ebx,[esi+33]
        mov ecx,[esi]
        add ecx,[ecx].S_SBLK.sb_size
        lea esi,[ecx-INFOSIZE]
        mov ecx,36

        .repeat

            lodsb

            .if ffflag & FF_OUTLINE

                .break .if al == 10
                .break .if al == 13
            .endif

            .if ( ffflag & ( FF_OUTLINE or FF_OUTTEXT ) ) && (al == 9 || al == 10 || al == 13)

                mov ah,al
                mov al,'\'
                scputc(ebx, edi, 1, eax)
                inc ebx
                mov al,'t'
                .if ah == 13

                    mov al,'n'
                .endif
                .if ah == 10

                    mov al,'r'
                .endif
                dec ecx
                .break .ifz
            .endif

            .if al
                scputc(ebx, edi, 1, eax)
            .endif

            inc ebx
        .untilcxz

        mov ecx,count
        mov esi,x
    .endf
    mov eax,1
    ret

FileSearch::List endp


FileSearch::ClearList proc uses esi edi ebx

    .for ebx = this,
         esi = [ebx].ll.ll_list,
         edi = [ebx].ll.ll_count : edi : edi--
        lodsd
        free(eax)
    .endf
    xor eax,eax
    mov [ebx].ll.ll_celoff,eax
    mov [ebx].ll.ll_index,eax
    mov [ebx].ll.ll_numcel,eax
    mov [ebx].ll.ll_count,eax
    ret

FileSearch::ClearList endp


FileSearch::Release proc uses edi ebx

    mov ebx,this

    mov thelp, [ebx].oldhelp
    mov ff,    [ebx].oldff
    CursorSet(&[ebx].cursor)

    mov eax,fsflag
    and eax,not (IO_SEARCHCASE or IO_SEARCHHEX or IO_SEARCHSUB)
    mov ecx,[ebx].flags
    and ecx,IO_SEARCHCASE or IO_SEARCHHEX or IO_SEARCHSUB
    or  eax,ecx
    mov fsflag,eax

    mov edx,[ebx].dialog
    .if edx
        movzx edi,[edx].S_DOBJ.dl_index
        dlclose(edx)
        .if edi == ID_GOTO
            .if [ebx].ll.ll_count
                .if panel_state(cpanel)
                    mov eax,[ebx].ll.ll_index
                    add eax,[ebx].ll.ll_celoff
                    mov edi,[ebx].ll.ll_list
                    mov edi,[edi+eax*4]
                    add edi,S_SBLK.sb_file
                    .if strrchr(edi, '\')
                        mov byte ptr [eax],0
                        cpanel_setpath(edi)
                    .endif
                .endif
            .endif
        .endif
    .endif
    [ebx].ClearList()
    free(ebx)
    ret

FileSearch::Release endp


FileSearch::WndProc proc uses esi edi ebx cmd:uint_t

    mov ebx,this
    mov ecx,cmd
    mov eax,_C_NORMAL

    .switch ecx

    .case KEY_F2 ; EventList
        .return _C_NORMAL

    .case KEY_F3
        mov esi,[ebx].dialog
        .return .if [esi].dl_index > ID_FILE
        .return _C_NORMAL .if ![ebx].CurFile()
        tview(eax, [eax-4]) ; .S_SBLK.sb_offs
        .return _C_NORMAL

    .case KEY_F4
        .return _C_NORMAL .if ![ebx].CurFile()
        mov esi,eax
        mov ebx,[ebx].dialog
        dlhide(ebx)
        tedit(esi, [esi-8])
        dlshow(ebx)
        .return _C_NORMAL

    .case KEY_F5
        cmfilter()
        mov edx,[ebx].dialog
        mov dx,[edx+4]
        add dx,0x1410
        mov cl,dh
        mov eax,7
        .if !filter
            mov al,' '
        .endif
        scputw(edx, ecx, 1, eax)
        .return _C_NORMAL

    .case KEY_F6 ; EventToggleHex
        .return _C_NORMAL

    .case KEY_F7
        .return [ebx].Find()

    .case KEY_F8
    .case KEY_DEL
        .return .if ![ebx].CurItem()
        .repeat
            mov ecx,[edx+4]
            mov [edx],ecx
            add edx,4
        .until !ecx
        free(eax)
        dec [ebx].ll.ll_count
        mov eax,[ebx].ll.ll_count
        mov edx,[ebx].ll.ll_index
        mov ecx,[ebx].ll.ll_celoff
        .ifz
            mov edx,eax
            mov ecx,eax
        .else
            .if edx
                mov esi,eax
                sub esi,edx
                .if esi < ID_FILE+1
                    dec edx
                    inc ecx
                .endif
            .endif
            sub eax,edx
            .if eax >= ID_FILE+1
                mov eax,ID_FILE+1
            .endif
            .if ecx >= eax
                dec ecx
            .endif
        .endif
        mov [ebx].ll.ll_index,edx
        mov [ebx].ll.ll_celoff,ecx
        mov [ebx].ll.ll_numcel,eax
        mov esi,[ebx].dialog
        test eax,eax
        mov al,cl
        .ifz
            mov al,ID_FILE+1
        .endif
        mov [esi].dl_index,al
        [ebx].List()
        .return _C_NORMAL

    .case KEY_F9
        .return cmfilter_load()

    .case KEY_F10
        mov eax,[ebx].flags
        .if eax & FF_OUTLINE
            and eax,not (FF_OUTTEXT or FF_OUTLINE)
        .elseif eax & FF_OUTTEXT
            and eax,not (FF_OUTTEXT or FF_OUTLINE)
            or  eax,FF_OUTLINE
        .else
            or eax,FF_OUTTEXT
        .endif
        mov [ebx].flags,eax
        .return [ebx].List()

    .case KEY_F11
        .if GetPathFromHistory(cpanel)
            mov ecx,[ebx].dialog
            mov ecx,[ecx].S_TOBJ.to_data[ID_LOCATION*TOFFSET]
            strcpy(ecx, [eax].S_DIRECTORY.path)
            dlinit([ebx].dialog)
            mov eax,_C_NORMAL
        .endif
        .return

    .case KEY_ALTX
        .return _C_ESCAPE
    .endsw
    ret

FileSearch::WndProc endp


EventXCell proc
    ff.PutCellId()
    dlxcellevent()
    ret
EventXCell endp

EventList proc
    ff.List()
    ret
EventList endp

EventFind proc
    ff.Find()
    ret
EventFind endp

EventOptions proc
    ff.Options()
    ret
EventOptions endp

EventHelp proc
    view_readme(HELPID_10)
    ret
EventHelp endp

EventProc proc
    ff.WndProc(eax)
    ret
EventProc endp

    option proc: public

FileSearch::FileSearch proc uses esi edi ebx directory:string_t


    .if !malloc( FileSearch + FileSearchVtbl + FFMAXHIT * 4 + 4 )

        ermsg(0, _sys_errlist[ENOMEM*4])
        .return 0
    .endif

    mov ebx,eax
    mov edi,eax
    mov ecx,( ( FileSearch + FileSearchVtbl + FFMAXHIT * 4 + 4 ) / 4 )
    xor eax,eax
    rep stosb

    lea eax,[ebx+FileSearch]
    mov [ebx].lpVtbl,eax
    mov [ebx].oldhelp,thelp
    mov [ebx].oldff,ff

    mov thelp,EventHelp
    mov ff,ebx

    lea edi,[ebx].ll
    mov tdllist,edi

    mov edi,[ebx].lpVtbl
    lea eax,[edi+FileSearchVtbl]
    mov [ebx].ll.ll_list,eax

    for m,<Release,WndProc,Find,Modal,Options,PutCellId,UpdateCell,CurItem,\
           CurFile,List,ClearList,SearchPath>
        mov [edi].FileSearchVtbl.m,FileSearch_&m&
        endm

    mov [ebx].ll.ll_dcount,ID_FILE+1
    mov [ebx].ll.ll_proc,EventList

    clrcmdl()
    CursorGet(&[ebx].cursor)

    mov [ebx].dialog,rsopen(IDD_DZFindFile)
    .if eax == NULL

        [ebx].Release()

        ermsg(0, _sys_errlist[ENOMEM*4])

        .return 0
    .endif

 assume edi:ptr S_TOBJ

    mov edi,eax
    mov [edi].to_data[ID_GCMD*TOFFSET],offset GlobalKeys

    lea ecx,findfilemask
    mov [edi].to_data[ID_MASK*TOFFSET],ecx

    .if byte ptr [ecx] == 0

        strcpy(ecx, &cp_stdmask)
    .endif

    mov [edi].to_data[ID_STRING   * TOFFSET],&searchstring
    mov [edi].to_data[ID_LOCATION * TOFFSET],directory
    mov [edi].to_proc[ID_START    * TOFFSET],EventFind
    mov [edi].to_proc[ID_OPTIONS  * TOFFSET],EventOptions

    mov eax,fsflag
    and eax,IO_SEARCHCASE or IO_SEARCHHEX or IO_SEARCHSUB
    or  eax,ffflag
    mov [ebx].flags,eax

    .for edx = &[edi].to_proc[S_TOBJ],
         eax = EventXCell,
         ecx = 0 : ecx <= ID_FILE : ecx++, edx += S_TOBJ

        mov [edx],eax
    .endf

 assume edi:nothing

    dlshow(edi)
    dlinit(edi)

    mov eax,ebx
    ret

FileSearch::FileSearch endp

    end
