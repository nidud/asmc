;
; Code Info is a RAM-resident (TSR) utility that accesses
; Code Information (help) using an editor or similar
;
; The program activates by Shift-Left + Shift-Right
;
; Change history:
; 2015-07-31 - expand environ in source path [.file]
; 2014-09-11 - added option create file to edit source
; 2014-09-11 - read [CodeInfo] at startup to avoid use dz.ci
; 2014-08-25 - changed library -- auto SSE usage
; 2014-08-25 - changed to GlobalAlloc() -- use more memory
; 2014-08-18 - fixed bug in CIPutSection()
; 2014-08-18 - fixed bug in EditText()
; 2014-08-18 - Changed short key Tab to F6
; 2014-08-18 - expanded size of struct to 2048
; 2014-08-12 - update screen metrics before pop-up..
; 2013-11-23 - made edit dialog movable -- Mouse/Alt-Up...
; 2013-11-20 - fixed bug in CIDelSection
; 2013-11-04 - converted to 32-bit
;
include consx.inc
include direct.inc
include io.inc
include string.inc
include alloc.inc
include errno.inc
include stdlib.inc
include cfini.inc
include tview.inc
include tinfo.inc
include dzlib.inc

    .data

externdef   _pgmpath:dword
externdef   IDD_CIEdit:dword
externdef   IDD_CISetup:dword
externdef   IDD_CIHelp:dword
externdef   IDD_CICreate:dword

;-------------------------------------------------------------------------
; DZCI
;-------------------------------------------------------------------------

POPUPKEY    equ SHIFT_RIGHT or SHIFT_LEFT

CICallStack dd 0
CIActive    dd 0
OldIdleHandler  dd 0    ; current idle() pointer

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MAXLABEL    equ 32  ; label size in memory
MAXENTRY    equ 256
MAXENTRIES  equ 24
MAXLSTACK   equ 9

_CI_DECL    equ 0
_CI_ARG0    equ 1
_CI_ARG1    equ 2
_CI_ARG2    equ 3
_CI_ARG3    equ 4
_CI_ARG4    equ 5
_CI_ARG5    equ 6
_CI_ARG6    equ 7
_CI_RET0    equ 8
_CI_RET1    equ 9
_CI_RET2    equ 10
_CI_INCFILE equ 11
_CI_INFO    equ 12
_CI_REF0    equ 13
_CI_REF1    equ 14
_CI_REF2    equ 15
_CI_REF3    equ 16
_CI_REF4    equ 17
_CI_REF5    equ 18
_CI_REF6    equ 19
_CI_REF7    equ 20
_CI_REF8    equ 21
_CI_REF9    equ 22
_CI_SRCFILE equ 23

CISECTION   STRUC
s_name      db MAXLABEL dup(?)
s_entry     db MAXENTRY*MAXENTRIES dup(?)
CISECTION   ENDS

CIDATA      STRUC
ci_section  CISECTION <>
ci_lstack   CISECTION MAXLSTACK dup(<>)
ci_lcount   UINT ?
ci_srcpath  sbyte _MAX_PATH dup(?)
ci_incpath  sbyte _MAX_PATH dup(?)
ci_curfile  sbyte _MAX_PATH dup(?)
ci_file     dd ?
ci_fileid   dd ?
ci_dialog   dd ?
ci_textvalue    dd ?
ci_txtvaled dd ?
CIDATA      ENDS

PCISECTION  TYPEDEF ptr CISECTION
PCIDATA     TYPEDEF ptr CIDATA

CIFile      dd 0
CIFileID    dd 0

CICommand   dd KEY_F2,      CIEventSave
            dd KEY_F3,      CIEventView
            dd KEY_F4,      CIEventEdit
            dd KEY_F5,      CIEventFind
            dd KEY_F8,      CIEventDelete
            dd KEY_F9,      CIEventSetup
            dd KEY_CTRLUP,  CIEventCTRLUP
            dd KEY_CTRLDN,  CIEventCTRLDN
            dd KEY_ALTX,    CIEventExit
            dd 0

CI_LABELS   db 1            ; [section]
            db 0            ; 00 c_decl
            db 0,0,0,0,0,0,0; 01 arg0
            db 0,0,0        ; 08 ret0
            db 3            ; 11 include
            db 2            ; 12 info
            db 1,1,1,1,1,1,1; 13 ref0
            db 1,1,1
            db 4            ; 23 srcfile
            db 5            ; 24 time

    .code

    option proc:private
    assume esi:ptr CIDATA

CIRead proc uses esi edi ebx ci:PCIDATA

    mov esi,ci

    .if !INIRead(0, &[esi].ci_curfile)

        INIAlloc()
    .endif

    .if eax

        mov edi,eax

        .if [esi].ci_file

            INIClose([esi].ci_file)
        .endif
        mov [esi].ci_file,edi

        .if INIGetSection(edi, ".file")

            mov edi,eax

            .if INIGetEntryID(edi, _CI_INCFILE)

                lea edx,[esi].ci_incpath
                expenviron(strcpy(edx, eax))
            .endif

            .if INIGetEntryID(edi, _CI_SRCFILE)

                lea edx,[esi].ci_srcpath
                expenviron(strcpy(edx, eax))
            .endif
        .endif
        mov eax,1
    .endif
    ret
CIRead endp

CIWrite proc uses esi edi ebx ci:PCIDATA

local bak[_MAX_PATH]:byte

    mov esi,ci
    lea edi,bak
    lea ebx,[esi].ci_curfile
    remove(setfext(strcpy(edi, ebx), ".bak"))
    rename(ebx, edi)
    INIWrite([esi].ci_file, ebx)
    ret

CIWrite endp

CICopySection proc uses esi edi CILabel, Section

    mov edi,CILabel
    mov ecx,sizeof(CISECTION)
    xor eax,eax
    rep stosb

    mov esi,CILabel
    mov edi,Section
    strcpy(esi, [edi].S_INI.entry)
    add esi,MAXLABEL
    xor edi,edi

    .while edi < MAXENTRIES

        .if INIGetEntryID(Section, edi)

            strcpy(esi, eax)
        .endif
        inc edi
        add esi,MAXENTRY
    .endw
    ret

CICopySection endp

CIGetTextValue proc uses ebx CILabel

    mov edx,CILabel
    mov ecx,sizeof(CISECTION)
    xor eax,eax
    xor ebx,ebx
    .repeat
        mov al,[edx]
        add edx,1
        add ebx,eax
        shl ebx,1
        adc ebx,0
    .untilcxz
    mov eax,ebx
    ret

CIGetTextValue endp

; Get value of edited text to put '*' (not saved)

CIPutTextValue proc uses esi CILabel

    mov esi,CILabel
    CIGetTextValue(esi)

    mov edx,[esi].ci_dialog
    movzx ecx,[edx].S_DOBJ.dl_rect.rc_x
    add ecx,1
    movzx edx,[edx].S_DOBJ.dl_rect.rc_y
    add edx,2
    cmp eax,[esi].ci_textvalue
    mov eax,' ';0C4h

    .ifnz
        mov eax,'*'
    .endif
    scputc(ecx, edx, 1, eax)
    ret

CIPutTextValue endp

CIPutSection proc uses esi edi ebx ci:PCIDATA

local x,y

    mov esi,ci

    mov eax,[esi].ci_dialog
    movzx ebx,[eax].S_DOBJ.dl_rect.rc_x
    add ebx,35
    mov x,ebx

    movzx edx,[eax].S_DOBJ.dl_rect.rc_y
    add edx,6
    mov y,edx
    mov ecx,11

    .repeat
        scputc(ebx, edx, 31, ' ')
        inc edx
    .untilcxz

    lea edi,[esi+_CI_REF0*MAXENTRY].ci_section.s_entry
    mov ebx,7
    put_section_info()
    inc y
    mov ebx,3
    put_section_info()

    add y,2
    sub x,33

    scputc(x, y, 40, ' ')
    scputs(x, y, 0, 40, strfn(&[esi].ci_curfile))
    dlinit([esi].ci_dialog)
    ret

put_section_info:

    .repeat
        .if byte ptr [edi]
            .if INIGetSection([esi].ci_file, edi)
                .if INIGetEntryID(eax, _CI_INFO)
                    scputs(x, y, 0, 31, eax)
                .endif
            .endif
        .endif
        inc y
        add edi,MAXENTRY
    .untilbxz
    retn

CIPutSection endp

CIReadSection proc uses esi edi ebx ci:PCIDATA, section:LPSTR

  local tmp[MAXLABEL]:byte

    mov esi,ci
    lea edi,tmp
    mov ebx,section

    .if strcmp(esi, ebx)

        memmove(&[esi].ci_lstack, esi, sizeof(CISECTION) * MAXLSTACK)
    .endif

    strncpy(edi, ebx, MAXLABEL-1)
    mov byte ptr [eax+MAXLABEL-1],0
    strncpy(esi, edi, MAXLABEL)

    .if INIGetSection([esi].ci_file, eax)

        CICopySection(esi, eax)
        mov [esi].ci_textvalue,CIGetTextValue(esi)
    .else
        mov [esi].ci_textvalue,0
    .endif

    CIPutTextValue(esi)
    CIPutSection(esi)
    ret

CIReadSection endp

CIViewSrc proc uses esi edi ebx ci:PCIDATA

  local path[_MAX_PATH]:byte

    mov esi,ci
    lea ebx,[esi].ci_section.s_entry + _CI_SRCFILE * MAXENTRY

    .if byte ptr [ebx]

        tview(strfcat(&path, &[esi].ci_srcpath, ebx), 0)
    .endif
    mov eax,_C_NORMAL
    ret

CIViewSrc endp

CIViewInc proc uses esi edi ebx ci:PCIDATA

  local path[_MAX_PATH]:byte

    mov esi,ci
    lea ebx,[esi].ci_section.s_entry + _CI_INCFILE * MAXENTRY

    .if byte ptr [ebx]

        tview(strfcat(&path, &[esi].ci_incpath, ebx), 0)
    .endif

    mov eax,_C_NORMAL
    ret

CIViewInc endp

CIEditFile proc uses edi ci:PCIDATA, file:LPSTR

    mov edi,tinfo
    mov tinfo,0

    .if topen(file, 0)

        tmodal()
        tclose()
        CIPutSection(ci)
    .endif

    mov tinfo,edi
    ret

CIEditFile endp

CIEditSrc proc uses esi edi ebx ci:PCIDATA

  local path[_MAX_PATH]:byte

    mov esi,ci
    lea ebx,[esi].ci_section.s_entry + _CI_SRCFILE * MAXENTRY

    .repeat
        .break .if byte ptr [ebx] == 0

        .if _access(strfcat(&path, &[esi].ci_srcpath, ebx), 0)

            .break .if !rsmodal(IDD_CICreate)

            .if osopen(&path, _A_NORMAL, M_WRONLY, A_CREATE) != -1

                _close(eax)
            .endif
        .endif

        CIEditFile(esi, &path)

    .until 1

    mov eax,_C_NORMAL
    ret

CIEditSrc endp

CIEditInc proc uses esi edi ci:PCIDATA

local   path[_MAX_PATH]:byte

    mov esi,ci
    lea edi,[esi].ci_section.s_entry + _CI_INCFILE * MAXENTRY

    .if byte ptr [edi]

        CIEditFile(esi, strfcat(&path, &[esi].ci_srcpath, edi))
    .endif

    mov eax,_C_NORMAL
    ret

CIEditInc endp

CINextFile proc uses esi edi ebx ci:PCIDATA

    mov esi,ci
    mov ebx,CIFileID
    inc ebx

    .if CFGetSection("CodeInfo")

        mov edi,eax

        .if !INIGetEntryID(edi, ebx)

            xor ebx,ebx
            INIGetEntryID(edi, ebx)
        .endif
    .endif

    .if eax

        mov edi,eax
        CIWrite(esi)

        mov dx,[edi]
        .if dl == '%' || dl == '\' || dl == '/' || dh == ':'

            strcpy(&[esi].ci_curfile, edi)
        .else
            strfcat(&[esi].ci_curfile, _pgmpath, edi)
        .endif
        expenviron(eax)

        mov CIFileID,ebx

        CIRead(esi)
        mov [esi].ci_textvalue,0

        CIPutSection(esi)

        mov eax,[esi].ci_dialog
        mov [eax].S_DOBJ.dl_index,0
        mov eax,1
    .endif
    ret

CINextFile endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CIEventHelp proc

    rsmodal(IDD_CIHelp)
    ret

CIEventHelp endp

CIEventSave proc uses esi edi ebx

    mov esi,CIFile

    .if INIAddSection([esi].ci_file, esi)

        lea edi,[esi].ci_section.s_entry
        mov esi,eax
        xor ebx,ebx

        .while ebx < MAXENTRIES

            .if byte ptr [edi]

                INIAddEntryX(esi, "%d=%s", ebx, edi)
            .endif
            add ebx,1
            add edi,MAXENTRY
        .endw

        mov esi,CIFile
        mov [esi].ci_textvalue,CIGetTextValue(esi)
    .endif

    CIPutTextValue(esi)
    mov eax,_C_NORMAL
    ret

CIEventSave endp

CIEventView proc uses esi

    mov esi,CIFile
    lea ecx,[esi].ci_section.s_entry + _CI_SRCFILE * MAXENTRY
    mov edx,[esi].ci_dialog

    .if [edx].S_DOBJ.dl_index == _CI_INCFILE || byte ptr [ecx] == 0

        CIViewInc(esi)
    .else
        CIViewSrc(esi)
    .endif

    mov eax,_C_NORMAL
    ret

CIEventView endp

CIEventEdit proc uses esi

    mov esi,CIFile
    lea ecx,[esi].ci_section.s_entry + _CI_SRCFILE * MAXENTRY
    mov edx,[esi].ci_dialog

    .if [edx].S_DOBJ.dl_index == _CI_INCFILE || byte ptr [ecx] == 0

        CIEditInc(esi)
    .else
        CIEditSrc(esi)
    .endif

    mov eax,_C_NORMAL
    ret

CIEventEdit endp

CIEventFind proc uses esi edi ebx

    mov esi,CIFile

    .if CFFindSection([esi].ci_file, esi, "12")

        .if INIGetSection([esi].ci_file, eax)

            CICopySection(esi, eax)
            mov [esi].ci_textvalue,CIGetTextValue(esi)
            CIPutSection(esi)
            CIPutTextValue(esi)
        .endif
    .endif

    mov eax,_C_NORMAL
    ret

CIEventFind endp

CIEventDelete proc uses edi

    mov edi,CIFile

    .if byte ptr [edi]

        INIDelSection([edi].CIDATA.ci_file, edi)
    .endif

    xor eax,eax
    mov [edi].CIDATA.ci_textvalue,eax
    mov ecx,sizeof(CISECTION)
    rep stosb
    mov eax,_C_NORMAL
    ret

CIEventDelete endp

CIEventSetup proc uses esi edi ebx

    mov esi,CIFile

    .if rsopen(IDD_CISetup)

        mov edi,eax
        xor ebx,ebx

        .if INIGetSection([esi].ci_file, ".file")

            mov ebx,eax

            .if INIGetEntryID(ebx, _CI_INCFILE)

                strcpy([edi].S_TOBJ.to_data[32], eax)
            .endif
            .if INIGetEntryID(ebx, _CI_SRCFILE)

                strcpy([edi].S_TOBJ.to_data[16], eax)
            .endif
        .endif

        dlinit(edi)

        .if dlevent(edi)

            expenviron(strcpy(&[esi].ci_srcpath, [edi].S_TOBJ.to_data[16]))
            expenviron(strcpy(&[esi].ci_incpath, [edi].S_TOBJ.to_data[32]))

            .if !ebx

                mov ebx,INIAddSection([esi].ci_file, ".file")
            .endif

            .if ebx

                INIAddEntryX(ebx, "%d=%s", _CI_SRCFILE, [edi].S_TOBJ.to_data[16])
                INIAddEntryX(ebx, "%d=%s", _CI_INCFILE, [edi].S_TOBJ.to_data[32])
            .endif
        .endif

        dlclose(edi)
    .endif

    mov eax,_C_NORMAL
    ret

CIEventSetup endp

CIEventCTRLUP proc uses esi

  local ll:CISECTION

    mov esi,CIFile

    memcpy(&ll, esi, sizeof(CISECTION))

    memcpy(esi, &[esi].ci_lstack, sizeof(CISECTION) * MAXLSTACK)
    memcpy(&[esi + sizeof(CISECTION) * MAXLSTACK], &ll, sizeof(CISECTION))

    mov eax,_C_NORMAL
    ret

CIEventCTRLUP endp

CIEventCTRLDN proc uses esi

  local ll:CISECTION

    mov esi,CIFile

    memcpy(&ll, &[esi + sizeof(CISECTION) * MAXLSTACK], sizeof(CISECTION))
    memcpy(&[esi].ci_lstack, esi, sizeof(CISECTION) * MAXLSTACK)
    memcpy(esi, &ll, sizeof(CISECTION))

    mov eax,_C_NORMAL
    ret

CIEventCTRLDN endp

CIEventExit proc

    mov eax,_C_ESCAPE
    ret

CIEventExit endp

CIEditEvent proc uses esi edi ebx

  local cursor:S_CURSOR

    CursorGet(&cursor)

    mov esi,CIFile
    mov edx,[esi].ci_dialog

    movzx   edi,[edx].S_DOBJ.dl_index
    shl edi,4
    add edi,[edx].S_DOBJ.dl_object
    mov eax,[edx].S_DOBJ.dl_rect
    mov edx,[edi].S_TOBJ.to_rect
    add dx,ax
    movzx   ecx,[edi].S_TOBJ.to_count
    shl ecx,4
    movzx   eax,[edi].S_TOBJ.to_flag
    mov edi,[edi].S_TOBJ.to_data
    mov ebx,dledit(edi,edx,ecx,eax)

    CursorSet(&cursor)

    .if ebx == KEY_ENTER

        mov eax,[esi].ci_dialog
        movzx   ecx,[eax].S_DOBJ.dl_index
        imul    eax,ecx,MAXENTRY
        lea edi,[esi+eax].ci_section.s_entry

        movzx   eax,CI_LABELS[ecx]
        .switch al
        .case   1
            .if byte ptr [esi]

                CIReadSection(esi, esi)
            .endif
            .endc
        .case   3
            CIViewInc(esi)
            .endc
        .case   4
            CIViewSrc(esi)
            .endc
        .endsw
        xor ebx,ebx

    .elseif ebx == KEY_F6

        CINextFile(esi)
        xor ebx,ebx
    .endif


    .if CIGetTextValue(esi) != [esi].ci_txtvaled

        mov [esi].ci_txtvaled,eax
        CIPutSection(esi)
    .endif

    CIPutTextValue(esi)
    mov eax,ebx
    ret

CIEditEvent endp


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CIPopUp proc uses esi edi ebx

  local scword[128]:byte, ascii:byte

    mov al,tclrascii
    mov ascii,al
    inc CICallStack

    .if scgetword(&scword)

        .if !CFGetSectionID("CodeInfo", CIFileID)

            mov CIFileID,0
            .if !CFGetSectionID("CodeInfo", 0)

                mov eax,@CStr("%DZ%\\default.ci")
            .endif
        .endif
        mov ebx,eax

        .if malloc(sizeof(CIDATA))

            mov esi,eax
            mov edi,eax
            mov ecx,sizeof(CIDATA)
            xor eax,eax
            rep stosb

            lea ecx,[esi].ci_curfile
            mov edx,[ebx]
            .switch
              .case dl == '%'
              .case dl == '\'
              .case dl == '/'
              .case dh == ':'
                strcpy(ecx, ebx)
                .endc
            .default
                strfcat(ecx, _pgmpath, ebx)
            .endsw
            expenviron(eax)

            .if CICallStack == 1

                CIRead(esi)
            .else
                mov edx,CIFile
                mov eax,[edx].CIDATA.ci_file
                mov [esi].CIDATA.ci_file,eax
                memcpy(&[esi].CIDATA.ci_lstack,
                       &[edx].CIDATA.ci_lstack,
                       sizeof(CISECTION) * MAXLSTACK)
            .endif

            push CIFile
            mov CIFile,esi

            .if rsopen(IDD_CIEdit)

                mov [esi].ci_dialog,eax

                push thelp
                mov tclrascii,' '

                mov edx,[eax].S_DOBJ.dl_object
                mov thelp,CIEventHelp
                mov [edx].S_TOBJ.to_data,esi
                mov [edx].S_TOBJ.to_proc,CIEditEvent

                mov ecx,MAXENTRIES
                lea eax,[esi].ci_section.s_entry
                .repeat
                    add edx,sizeof(S_TOBJ)
                    mov [edx].S_TOBJ.to_data,eax
                    mov [edx].S_TOBJ.to_proc,CIEditEvent
                    add eax,MAXENTRY
                .untilcxz

                mov [edx+16].S_TOBJ.to_data,offset CICommand

                dlshow([esi].ci_dialog)

                CIReadSection(esi, &scword)
                rsevent(IDD_CIEdit, [esi].ci_dialog)
                dlclose([esi].ci_dialog)

                mov al,ascii
                mov tclrascii,al
                pop eax
                mov thelp,eax
                mov [esi].ci_txtvaled,0

                CIWrite(esi)
            .endif

            pop CIFile

            .if CICallStack == 1

                INIClose([esi].ci_file)
            .endif

            free(esi)
        .endif
    .endif

    dec CICallStack
    xor eax,eax
    ret

CIPopUp endp

CIIdleHandler proc

    mov eax,keyshift
    mov eax,[eax]
    and eax,POPUPKEY

    .if eax == POPUPKEY

        .if CIActive != 1

            mov CIActive,1
            CIPopUp()
        .endif
    .else
        mov CIActive,0
        OldIdleHandler()
    .endif
    ret

CIIdleHandler endp

CodeInfo proc PUBLIC

    mov eax,tdidle
    mov OldIdleHandler,eax
    mov tdidle,CIIdleHandler
    ret

CodeInfo endp

    END
