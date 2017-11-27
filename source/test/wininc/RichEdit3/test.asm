; RichEdit Control
; Unicode with Syntax Highlighting and Font Menu
;
_CType equ <stdcall>
include lang/en.txt
include windows.inc
include richedit.inc
include winres.inc
include ltype.inc

IDR_MAINMENU        equ 100
IDM_OPEN            equ 40001
IDM_SAVE            equ 40002
IDM_CLOSE           equ 40003
IDM_SAVEAS          equ 40004
IDM_EXIT            equ 40005
IDM_UNDO            equ 40006
IDM_REDO            equ 40007
IDM_COPY            equ 40008
IDM_CUT             equ 40009
IDM_PASTE           equ 40010
IDM_DELETE          equ 40011
IDM_SELECTALL       equ 40012
IDM_FIND            equ 40013
IDM_FINDNEXT        equ 40014
IDM_FINDPREV        equ 40015
IDM_REPLACE         equ 40016
IDM_GOTOLINE        equ 40017
IDM_FONT            equ 40018
IDM_COLOR           equ 40019
IDM_STATUSBAR       equ 40020
IDM_VIEWHELP        equ 40021
IDM_ABOUT           equ 40022

IDD_OPTIONDLG       equ 101
IDC_BACKCOLORBOX    equ 1000
IDC_TEXTCOLORBOX    equ 1001
IDR_MAINACCEL       equ 105
IDD_FINDDLG         equ 102
IDD_GOTODLG         equ 103
IDD_REPLACEDLG      equ 104
IDC_FINDEDIT        equ 1000
IDC_MATCHCASE       equ 1001
IDC_REPLACEEDIT     equ 1001
IDC_WHOLEWORD       equ 1002
IDC_DOWN            equ 1003
IDC_UP              equ 1004
IDC_LINENO          equ 1005
RichEditID          equ 300
;
; Attrib  A - Set forground color
; Quote   Q - Set color of quoted text
; Digit   D - Set color of numbers
; Char    C - Set color of chars
; Start   S - Set color from start of string
; Word    W - Set color of words
; Nested  N - Set color of nested strings
;
ST_ATTRIB   equ 1   ; attrib    <at>
ST_QUOTE    equ 2   ; quote     <at>
ST_NUMBER   equ 3   ; number    <at>
ST_CHAR     equ 4   ; char      <at> <chars>
ST_START    equ 5   ; start     <at> <string>
ST_WORD     equ 6   ; word      <at> <words> ...
ST_NESTED   equ 7   ; nested    <at> <string1> <string2>
ST_COUNT    equ 7

STYLESIZE   equ 0x4000
MAX_ENTRY   equ 256

.data?
style           db STYLESIZE dup(?)
TextBuffer      TCHAR 1024*10 dup(?)
FileName        TCHAR 256 dup(?)
AltFileName     TCHAR 256 dup(?)
FindBuffer      TCHAR 256 dup(?)
ReplBuffer      TCHAR 256 dup(?)
Profile         TCHAR 512 dup(?)
hEdit           HWND ?
hAccel          HACCEL ?
hInstance       HINSTANCE ?
OldWndProc      PVOID ?
uFlags          dd ?
hSearch         HANDLE ?    ; handle to the search/replace dialog box
FileOpened      dd ?
findtext        FINDTEXTEX <>
AppFont         LOGFONT <>

.data
debug           dd 0
TextColor       dd RGB(192,192,192) ; default to gray
BackColor       dd RGB(0,0,0)       ; default to black
SyntaxColors    dd RGB(0,0,0)
                dd RGB(0,0,128)
                dd RGB(0,128,0)
                dd RGB(0,128,128)
                dd RGB(128,0,0)
                dd RGB(116,65,65)
                dd RGB(128,128,0)
                dd RGB(192,192,192)
                dd RGB(128,128,128)
                dd RGB(0,0,255)
                dd RGB(0,255,0)
                dd RGB(0,255,255)
                dd RGB(145,0,0)
                dd RGB(255,0,255)
                dd RGB(255,255,0)
                dd RGB(255,255,255)
hFont           dd 0
AppName         TCHAR "Testpad",0
ASMFilter       TCHAR "ASM Source code (*.asm)",0,"*.asm",0
                TCHAR "All Files (*.*)",0,"*.*",0,0
typech          db "aqdcswn",0

_ltype label byte
        db 0
        db _CONTROL             ; 00 (NUL)
        db _CONTROL             ; 01 (SOH)
        db _CONTROL             ; 02 (STX)
        db _CONTROL             ; 03 (ETX)
        db _CONTROL             ; 04 (EOT)
        db _CONTROL             ; 05 (ENQ)
        db _CONTROL             ; 06 (ACK)
        db _CONTROL             ; 07 (BEL)
        db _CONTROL             ; 08 (BS)
        db _SPACE+_CONTROL      ; 09 (HT)
        db _SPACE+_CONTROL      ; 0A (LF)
        db _SPACE+_CONTROL      ; 0B (VT)
        db _SPACE+_CONTROL      ; 0C (FF)
        db _SPACE+_CONTROL      ; 0D (CR)
        db _CONTROL             ; 0E (SI)
        db _CONTROL             ; 0F (SO)
        db _CONTROL             ; 10 (DLE)
        db _CONTROL             ; 11 (DC1)
        db _CONTROL             ; 12 (DC2)
        db _CONTROL             ; 13 (DC3)
        db _CONTROL             ; 14 (DC4)
        db _CONTROL             ; 15 (NAK)
        db _CONTROL             ; 16 (SYN)
        db _CONTROL             ; 17 (ETB)
        db _CONTROL             ; 18 (CAN)
        db _CONTROL             ; 19 (EM)
        db _CONTROL             ; 1A (SUB)
        db _CONTROL             ; 1B (ESC)
        db _CONTROL             ; 1C (FS)
        db _CONTROL             ; 1D (GS)
        db _CONTROL             ; 1E (RS)
        db _CONTROL             ; 1F (US)
        db _SPACE               ; 20 SPACE
        db _PUNCT               ; 21 !
        db _PUNCT               ; 22 ""
        db _PUNCT               ; 23 #
        db _PUNCT+_LABEL        ; 24 $
        db _PUNCT               ; 25 %
        db _PUNCT               ; 26 &
        db _PUNCT               ; 27 '
        db _PUNCT               ; 28 (
        db _PUNCT               ; 29 )
        db _PUNCT               ; 2A *
        db _PUNCT               ; 2B +
        db _PUNCT               ; 2C
        db _PUNCT               ; 2D -
        db _PUNCT               ; 2E .
        db _PUNCT               ; 2F /
        db _DIGIT+_HEX          ; 30 0
        db _DIGIT+_HEX          ; 31 1
        db _DIGIT+_HEX          ; 32 2
        db _DIGIT+_HEX          ; 33 3
        db _DIGIT+_HEX          ; 34 4
        db _DIGIT+_HEX          ; 35 5
        db _DIGIT+_HEX          ; 36 6
        db _DIGIT+_HEX          ; 37 7
        db _DIGIT+_HEX          ; 38 8
        db _DIGIT+_HEX          ; 39 9
        db _PUNCT               ; 3A :
        db _PUNCT               ; 3B ;
        db _PUNCT               ; 3C <
        db _PUNCT               ; 3D =
        db _PUNCT               ; 3E >
        db _PUNCT+_LABEL        ; 3F ?
        db _PUNCT+_LABEL        ; 40 @
        db _UPPER+_LABEL+_HEX   ; 41 A
        db _UPPER+_LABEL+_HEX   ; 42 B
        db _UPPER+_LABEL+_HEX   ; 43 C
        db _UPPER+_LABEL+_HEX   ; 44 D
        db _UPPER+_LABEL+_HEX   ; 45 E
        db _UPPER+_LABEL+_HEX   ; 46 F
        db _UPPER+_LABEL        ; 47 G
        db _UPPER+_LABEL        ; 48 H
        db _UPPER+_LABEL        ; 49 I
        db _UPPER+_LABEL        ; 4A J
        db _UPPER+_LABEL        ; 4B K
        db _UPPER+_LABEL        ; 4C L
        db _UPPER+_LABEL        ; 4D M
        db _UPPER+_LABEL        ; 4E N
        db _UPPER+_LABEL        ; 4F O
        db _UPPER+_LABEL        ; 50 P
        db _UPPER+_LABEL        ; 51 Q
        db _UPPER+_LABEL        ; 52 R
        db _UPPER+_LABEL        ; 53 S
        db _UPPER+_LABEL        ; 54 T
        db _UPPER+_LABEL        ; 55 U
        db _UPPER+_LABEL        ; 56 V
        db _UPPER+_LABEL        ; 57 W
        db _UPPER+_LABEL        ; 58 X
        db _UPPER+_LABEL        ; 59 Y
        db _UPPER+_LABEL        ; 5A Z
        db _PUNCT               ; 5B [
        db _PUNCT               ; 5C \
        db _PUNCT               ; 5D ]
        db _PUNCT               ; 5E ^
        db _PUNCT+_LABEL        ; 5F _
        db _PUNCT               ; 60 `
        db _LOWER+_LABEL+_HEX   ; 61 a
        db _LOWER+_LABEL+_HEX   ; 62 b
        db _LOWER+_LABEL+_HEX   ; 63 c
        db _LOWER+_LABEL+_HEX   ; 64 d
        db _LOWER+_LABEL+_HEX   ; 65 e
        db _LOWER+_LABEL+_HEX   ; 66 f
        db _LOWER+_LABEL        ; 67 g
        db _LOWER+_LABEL        ; 68 h
        db _LOWER+_LABEL        ; 69 i
        db _LOWER+_LABEL        ; 6A j
        db _LOWER+_LABEL        ; 6B k
        db _LOWER+_LABEL        ; 6C l
        db _LOWER+_LABEL        ; 6D m
        db _LOWER+_LABEL        ; 6E n
        db _LOWER+_LABEL        ; 6F o
        db _LOWER+_LABEL        ; 70 p
        db _LOWER+_LABEL        ; 71 q
        db _LOWER+_LABEL        ; 72 r
        db _LOWER+_LABEL        ; 73 s
        db _LOWER+_LABEL        ; 74 t
        db _LOWER+_LABEL        ; 75 u
        db _LOWER+_LABEL        ; 76 v
        db _LOWER+_LABEL        ; 77 w
        db _LOWER+_LABEL        ; 78 x
        db _LOWER+_LABEL        ; 79 y
        db _LOWER+_LABEL        ; 7A z
        db _PUNCT               ; 7B {
        db _PUNCT               ; 7C |
        db _PUNCT               ; 7D }
        db _PUNCT               ; 7E ~
        db _CONTROL             ; 7F (DEL)

        ; and the rest are 0...

        db 129 dup(0);257 - ($ - _ltype) dup(0)

.code

TOUPPER MACRO p
        movzx eax,byte ptr p
        sub al,'a'
        cmp al,'z'-'a'+1
        sbb dl,dl
        and dl,'a'-'A'
        sub al,dl
        add al,'a'
        ENDM

TOLOWER MACRO p
        movzx eax,byte ptr p
        sub al,'A'
        cmp al,'Z'-'A'+1
        sbb dl,dl
        and dl,'a'-'A'
        add al,dl
        add al,'A'
        ENDM

;
; Read style
;
GetEntry proc file, section, entry, buffer
    .if GetPrivateProfileString(section, entry, 0, buffer, MAX_ENTRY, file)
        mov ecx,eax
        mov eax,buffer
    .endif
    ret
GetEntry endp

GetEntryID proc file, section, ID, buffer
local entry[2]
    xor edx,edx
    mov eax,ID ; 0..99
    .while  al > 9
        add dl,1
        sub al,10
    .endw
    .if dl
        xchg al,dl
        or dl,'0'
    .endif
    or  al,'0'
    shl edx,16
    or eax,edx
    mov entry,eax
    mov entry[4],0
    GetEntry(file, section, &entry, buffer)
    ret
GetEntryID endp

ReadLabel PROC USES esi edi ebx file, section, buffer, endbuf

local entry[MAX_ENTRY]:byte
local st_type,i,p,q

    .repeat

        .break .if !GetEntryID( file, section, 0, &entry )

        mov p,eax
        mov al,[eax]
        or  al,20h
        lea edi,typech
        mov ecx,sizeof(typech)
        repnz scasb
        .break .ifnz

        mov eax,edi
        sub eax,offset typech
        mov st_type,eax

        mov edi,buffer
        mov edi,[edi]
        .break .if edi >= endbuf

        stosb           ; store type
        mov esi,p
        xor eax,eax
        mov i,eax

        .repeat
            add esi,TCHAR
            mov al,[esi]
        .until (al == 9 || al == ' ' || al == '_')

        .repeat

            lodsw
            .switch
              .case al == ' '
                mov eax,esi
                .endc
              .case al
                .continue
              .default
                mov i,1
                .break .if !GetEntryID( file, section, 1, &entry)
            .endsw

            mov esi,eax
            add eax,2
            mov p,eax
            mov al,[esi]
            sub al,'0'
            .if al > 9
                sub al,7
            .endif
            stosb ; store attrib

            mov esi,p
            .while TCHAR PTR [esi] == ' '
                add esi,TCHAR
            .endw

            .while 1
                .while 1
                    lodsw
                    .break .if !ax
                    .break .if edi >= endbuf
                    cmp  al,' '
                    sete dl
                    dec  dl
                    and  al,dl
                    stosb
                .endw
                .break .if al
                stosb
                inc i
                .break .if i == 100
                .break .if !GetEntryID( file, section, i, &entry)
                mov esi,eax
            .endw
        .until 1

        xor eax,eax
        .if [edi-1] != al
            stosb
        .endif
        stosb
        mov ecx,buffer
        mov [ecx],edi
        inc eax
    .until 1
    ret
ReadLabel endp

ReadStyle proc uses esi edi file:ptr
local buffer:ptr
local endbuf:ptr
local entry[MAX_ENTRY]:byte

    lea eax,style
    mov buffer,eax
    mov edi,eax
    add eax,STYLESIZE-4
    mov endbuf,eax
    xor eax,eax
    mov ecx,STYLESIZE/4
    rep stosd
    xor esi,esi
    lea edi,entry
    .while GetEntryID(file, "Style", esi, edi)
        ReadLabel(file, edi, &buffer, endbuf)
        inc esi
    .endw
    mov edi,buffer
    xor eax,eax
    stosw
    inc eax
    ret
ReadStyle endp

;
; Read Config
;
lxtol proc string:LPSTR
    mov edx,string
    xor eax,eax
    xor ecx,ecx
    .while 1
        mov cl,[edx]
        add edx,2
        and cl,0xDF
        .break .if cl < 0x10
        .break .if cl > 'F'
        .if cl > 0x19
            .break .if cl < 'A'
            sub cl,'A' - 0x1A
        .endif
        sub cl,0x10
        shl eax,4
        add eax,ecx
    .endw
    ret
lxtol endp

latol proc string:LPSTR
    mov edx,string
    movzx ecx,byte ptr [edx]
    xor eax,eax
    .while 1
        sub ecx,'0'
        .break .ifc
        .break .if ecx > 9
        lea ecx,[eax*8+ecx]
        lea eax,[eax*2+ecx]
        add edx,2
        movzx ecx,byte ptr [edx]
    .endw
    ret
latol endp

ReadConfig proc uses esi edi file:ptr
local entry[MAX_ENTRY]:byte
    lea edi,entry
    .if GetEntry(file, "Colors", "Text", edi)
        lxtol(edi)
        mov TextColor,eax
        .if GetEntry(file, "Colors", "Back", edi)
            lxtol(edi)
            mov BackColor,eax
        .endif
        xor esi,esi
        .while GetEntryID(file, "Colors", esi, edi)
            lxtol(edi)
            mov SyntaxColors[esi*4],eax
            inc esi
        .endw
    .endif
    mov AppFont.lfHeight,24
    mov AppFont.lfWeight,FW_NORMAL
    mov AppFont.lfCharSet,DEFAULT_CHARSET
    lstrcpy(&AppFont.lfFaceName, "Courier New")
    .if GetEntry(file, "Font", "Face", edi)
        lstrcpy(&AppFont.lfFaceName, edi)
    .endif
    .if GetEntry(file, "Font", "Height", edi)
        latol(edi)
        shl eax,1
        mov AppFont.lfHeight,eax
    .endif
    ret
ReadConfig endp

SetColor proc

    local cfm:CHARFORMAT2

    SendMessage(hEdit, EM_GETMODIFY, 0, 0)
    push eax
    mov edx,edi
    lea edi,cfm
    mov ecx,sizeof(cfm)
    xor eax,eax
    rep stosb
    mov edi,edx
    mov cfm.cbSize,sizeof(cfm)
    mov eax,TextColor
    mov cfm.crTextColor,eax
    mov cfm.dwMask,CFM_COLOR; or CFM_BACKCOLOR
    SendMessage(hEdit, EM_SETCHARFORMAT, SCF_ALL, &cfm)
    SendMessage(hEdit, EM_SETBKGNDCOLOR, 0, BackColor)
    pop eax
    SendMessage(hEdit, EM_SETMODIFY, eax, 0)
    ret

SetColor endp

DLGSelectFont proc uses edi hWnd:HWND

    local cfm:CHARFORMAT
    local Font:CHOOSEFONT

    lea edi,Font
    xor eax,eax
    mov ecx,sizeof(CHOOSEFONT)
    rep stosb

    mov Font.lStructSize,sizeof(CHOOSEFONT)
    mov eax,hWnd
    mov Font.hwndOwner,eax
    lea eax,AppFont
    mov Font.lpLogFont,eax
    mov eax,TextColor
    mov Font.rgbColors,eax
    mov Font.Flags,CF_SCREENFONTS or CF_NOVERTFONTS or CF_INITTOLOGFONTSTRUCT

    .if ChooseFont(&Font)

        mov edi,hFont
        mov hFont,CreateFontIndirect(&AppFont)
        SendMessage(hEdit, WM_SETFONT, eax, 1)
        .if edi
            DeleteObject(edi)
        .endif
        SetColor()
    .endif
    ret

DLGSelectFont endp

SetStyle PROC USES esi edi ebx hWnd:HWND

    local endbuf, string
    local ctype:byte, attrib:byte
    local hdc:HDC
    local firstchar
    local rect:RECT
    local txtrange:TEXTRANGE
    local hRgn,hOldRgn
    local buffer,bufsize

    mov hdc,GetDC(hWnd)
    SetBkMode(hdc, TRANSPARENT)
    SendMessage(hWnd, EM_GETRECT,0, &rect)
    SendMessage(hWnd, EM_CHARFROMPOS, 0, &rect)
    SendMessage(hWnd, EM_LINEFROMCHAR, eax, 0)
    SendMessage(hWnd, EM_LINEINDEX, eax, 0)
    mov txtrange.chrg.cpMin,eax
    mov firstchar,eax
    SendMessage(hWnd, EM_CHARFROMPOS, 0, &rect.right)
    mov txtrange.chrg.cpMax,eax
    mov hRgn,CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom)
    mov hOldRgn,SelectObject(hdc, hRgn)
    SelectObject(hdc, hFont)

    ;
    ; Get the visible text into buffer
    ;
    lea eax,TextBuffer
    mov buffer,eax
    mov txtrange.lpstrText,eax

    .repeat

        .break .if !SendMessage(hWnd, EM_GETTEXTRANGE, 0, &txtrange)

        mov bufsize,eax
        mov ecx,buffer
        add ecx,eax
        add ecx,eax
        mov endbuf,ecx
        lea esi,style

        .while 1

            movzx eax,BYTE PTR [esi]
            movzx ebx,BYTE PTR [esi+1]
            add   esi,2
            mov   ctype,al
            mov   attrib,bl

            .break .if !eax
            .break .if eax > ST_COUNT

            mov string,esi
            mov edx,endbuf
            .break .if edx <= buffer

            .switch al
              .case ST_ATTRIB
                ;
                ; 1. A Attrib <at>
                ;
                mov eax,SyntaxColors[ebx*4]
                .if eax != TextColor
                    mov TextColor,eax
                    SetColor()
                .endif
                .endc

              .case ST_QUOTE
                ;
                ; 2. Q Quote - match on '"' and "'"
                ;
                mov eax,SyntaxColors[ebx*4]
                SetTextColor(hdc, eax)
                .for ebx=0,esi=0,edi=buffer: edi < endbuf: edi+=TCHAR

                    mov ax,[edi]
                    .if ax == '"' || ax == "'"
                        .if !ebx
                            .if ax == '"'
                                mov bx,ax
                            .else
                                .if edi > buffer
                                    movzx ecx,byte ptr [edi-2]
                                    .if !(_ltype[ecx+1] & _LABEL)
                                        mov bx,ax
                                    .endif
                                .endif
                            .endif
                            mov edx,edi
                        .elseif bx == ax
                            xor ebx,ebx
                            mov esi,edx
                        .endif
                    .endif
                    .if esi
                        mov eax,esi
                        sub eax,buffer
                        shr eax,1
                        add eax,firstchar
                        SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                        add edi,2
                        mov ecx,edi
                        sub ecx,esi
                        shr ecx,1
                        DrawText(hdc, esi, ecx, &rect, DT_NOPREFIX)
                        mov ecx,edi
                        sub ecx,esi
                        mov edi,esi
                        xor eax,eax
                        rep stosb
                        xor esi,esi
                    .endif
                .endf
                .endc

              .case ST_NUMBER
                ;
                ; 3. D Digit - match on 0x 0123456789ABCDEF and Xh
                ;
                mov eax,SyntaxColors[ebx*4]
                SetTextColor(hdc, eax)

                .for ebx=0,esi=0,edi=buffer: edi < endbuf: edi+=TCHAR

                    movzx eax,word ptr [edi]
                    .switch
                      .case ah
                      .case !eax
                      .case _ltype[eax+1] & _CONTROL or _SPACE or _PUNCT
                        .endc .if !ebx
                        mov esi,edi
                        .endc
                      .case _ltype[eax+1] & _DIGIT
                        .endc .if ebx
                        .if edi > buffer
                            mov al,[edi-2]
                            .endc .if _ltype[eax+1] & _LABEL
                        .endif
                        mov ebx,edi
                        .endc
                      .case 'x'
                      .case 'X'
                      .case 'h'
                      .case 'H'
                      .case _ltype[eax+1] & _HEX
                        .endc
                      .default
                        .endc .if !ebx
                        mov esi,edi
                        .endc
                    .endsw

                    .if esi
                        mov eax,ebx
                        sub eax,buffer
                        shr eax,1
                        add eax,firstchar
                        SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)

                        mov ecx,edi
                        sub ecx,ebx
                        shr ecx,1
                        DrawText(hdc, ebx, ecx, &rect, DT_NOPREFIX)
                        mov ecx,edi
                        sub ecx,ebx
                        mov edi,ebx
                        xor eax,eax
                        rep stosb
                        xor esi,esi
                        xor ebx,ebx
                    .endif
                .endf
                .endc

              .case ST_CHAR
                ;
                ; 4. C Char <at> <chars>
                ;
                mov eax,SyntaxColors[ebx*4]
                SetTextColor(hdc, eax)
                .for edi=buffer: edi < endbuf: edi+=TCHAR
                    mov ax,[edi]
                    .if ax && !ah
                        mov ebx,esi
                        .while byte ptr [ebx]
                            .if al == [ebx]
                                mov eax,edi
                                sub eax,buffer
                                shr eax,1
                                add eax,firstchar
                                SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                                DrawText(hdc, edi, 1, &rect, DT_NOPREFIX)
                                .break
                            .endif
                            inc ebx
                        .endw
                    .endif
                .endf
                .endc

              .case ST_START
                ;
                ; 5. S Start - X string
                ;    set color X from string to end of line
                ;
                mov eax,SyntaxColors[ebx*4]
                SetTextColor(hdc, eax)

                .while byte ptr [esi]

                    mov edi,buffer
                    .while edi < endbuf

                        TOLOWER [esi]
                        mov ecx,endbuf
                        sub ecx,edi
                        shr ecx,1
                        .break .ifz
                        mov ebx,edi
                        mov edx,ecx
                        repne scasw
                        .ifnz
                            mov ecx,edx
                            mov edi,ebx
                            TOUPPER [esi]
                            repne scasw
                        .endif
                        .break .ifnz

                        mov edx,esi
                        lea ecx,[edi-2]
                        .if ecx > buffer
                            movzx eax,BYTE PTR [ecx-2]
                            .continue .if _ltype[eax+1] & _LABEL or _DIGIT
                        .endif
                        mov ebx,ecx
                        .repeat
                            add edx,1
                            add ecx,2
                            mov al,[edx]
                            .break .if !al
                            .continue(0) .if al == [ecx]
                            mov ah,[ecx]
                            or  eax,0x2020
                            .continue(0) .if al == ah
                        .until 1
                        .continue .if al
                        .if byte ptr [esi+1]
                            movzx eax,BYTE PTR [ecx]
                            .continue .if _ltype[eax+1] & _LABEL or _DIGIT
                        .endif

                        .while edi < endbuf
                            mov ax,[edi]
                            .break .if !ax
                            .break .if ax == 0x0D
                            .break .if ax == 0x0A
                            add edi,2
                        .endw
                        mov eax,ebx
                        sub eax,buffer
                        shr eax,1
                        add eax,firstchar
                        SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                        mov ecx,edi
                        sub ecx,ebx
                        shr ecx,1
                        DrawText(hdc, ebx, ecx, &rect, DT_NOPREFIX)
                        mov ecx,edi
                        sub ecx,ebx
                        mov edi,ebx
                        xor eax,eax
                        rep stosb
                    .endw
                    .repeat
                        lodsb
                    .until !al
                .endw
                .endc

              .case ST_WORD
                ;
                ; 6. W Word - match on all equal words
                ;
                mov eax,SyntaxColors[ebx*4]
                SetTextColor(hdc, eax)

                .while byte ptr [esi]
                    mov edi,buffer
                    .while edi < endbuf
                        TOLOWER [esi]
                        mov ecx,endbuf
                        sub ecx,edi
                        shr ecx,1
                        .break .ifz
                        mov ebx,edi
                        mov edx,ecx
                        repne scasw
                        .ifnz
                            mov ecx,edx
                            mov edi,ebx
                            TOUPPER [esi]
                            repne scasw
                        .endif
                        .break .ifnz
                        mov edx,esi
                        lea ecx,[edi-2]
                        .if ecx > buffer
                            movzx eax,BYTE PTR [ecx-2]
                            .continue .if _ltype[eax+1] & _LABEL or _DIGIT
                        .endif
                        mov ebx,ecx
                        .repeat
                            add edx,1
                            add ecx,2
                            mov al,[edx]
                            .break .if !al
                            .continue(0) .if al == [ecx]
                            mov ah,[ecx]
                            or  eax,0x2020
                            .continue(0) .if al == ah
                        .until 1
                        .continue .if al
                        movzx eax,BYTE PTR [ecx]
                        .continue .if _ltype[eax+1] & _LABEL or _DIGIT
                        mov edi,ebx
                        mov ebx,edx
                        sub ebx,esi
                        mov eax,edi
                        sub eax,buffer
                        shr eax,1
                        add eax,firstchar
                        SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                        DrawText(hdc, edi, ebx, &rect, DT_NOPREFIX)
                        mov ecx,ebx
                        xor eax,eax
                        rep stosw
                    .endw
                    .repeat
                        lodsb
                    .until !al
                .endw
                .endc

              .case ST_NESTED
                ;
                ; 7. N Nested -- /* */
                ;
                .endc

            .endsw

            mov esi,string
            .repeat
                lodsb
                .continue .if al
                lodsb
            .until !al
        .endw
    .until 1

    SelectObject(hdc, hOldRgn)
    DeleteObject(hRgn)
    ReleaseDC(hWnd, hdc)
    ret

SetStyle endp

InitProfile proc uses esi edi ebx
    lea edi,Profile
    GetModuleFileName(hInstance, edi, sizeof(Profile))
    lea edi,[edi+eax*TCHAR-3*TCHAR]
    lstrcpy(edi, "ini")
    ret
InitProfile endp

RichEditProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch uMsg
      .case WM_PAINT
        HideCaret(hWnd)
        CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam)
        push eax
        SetStyle(hWnd)
        ShowCaret(hWnd)
        pop eax
        .endc
      .case WM_CLOSE
        SetWindowLong(hWnd, GWL_WNDPROC, OldWndProc)
        .endc
      .default
        CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam)
    .endsw
    ret

RichEditProc endp

PrepareEditMenu proc hSubMenu:DWORD

    local chrg:CHARRANGE
    ;
    ; Check whether there is some text in the clipboard. If so,
    ; we enable the paste menuitem
    ;
    .if !SendMessage(hEdit, EM_CANPASTE, CF_TEXT, 0)      ; no text in the clipboard
        EnableMenuItem(hSubMenu, IDM_PASTE, MF_GRAYED)
    .else
        EnableMenuItem(hSubMenu, IDM_PASTE, MF_ENABLED)
    .endif
    ;
    ; check whether the undo queue is empty
    ;
    .if !SendMessage(hEdit, EM_CANUNDO, 0, 0)
        EnableMenuItem(hSubMenu, IDM_UNDO, MF_GRAYED)
    .else
        EnableMenuItem(hSubMenu, IDM_UNDO, MF_ENABLED)
    .endif
    ;
    ; check whether the redo queue is empty
    ;
    .if !SendMessage(hEdit, EM_CANREDO, 0, 0)
        EnableMenuItem(hSubMenu, IDM_REDO, MF_GRAYED)
    .else
        EnableMenuItem(hSubMenu, IDM_REDO, MF_ENABLED)
    .endif
    ;
    ; check whether there is a current selection in the richedit control.
    ; If there is, we enable the cut/copy/delete menuitem
    ;
    SendMessage(hEdit, EM_EXGETSEL, 0, &chrg)
    mov eax,chrg.cpMin
    .if eax == chrg.cpMax     ; no current selection
        EnableMenuItem(hSubMenu, IDM_COPY, MF_GRAYED)
        EnableMenuItem(hSubMenu, IDM_CUT, MF_GRAYED)
        EnableMenuItem(hSubMenu, IDM_DELETE, MF_GRAYED)
    .else
        EnableMenuItem(hSubMenu, IDM_COPY, MF_ENABLED)
        EnableMenuItem(hSubMenu, IDM_CUT, MF_ENABLED)
        EnableMenuItem(hSubMenu, IDM_DELETE, MF_ENABLED)
    .endif
    ret

PrepareEditMenu endp

StreamInProc proc hFile:HANDLE, pBuffer:LPSTR, NumBytes:UINT, pBytesRead:LPDWORD
    ReadFile(hFile, pBuffer, NumBytes, pBytesRead, 0)
    xor eax,1
    ret
StreamInProc endp

StreamOutProc proc hFile:HANDLE, pBuffer:LPSTR, NumBytes:UINT, pBytesWritten:LPDWORD
    WriteFile(hFile, pBuffer, NumBytes, pBytesWritten, 0)
    xor eax,1
    ret
StreamOutProc endp

CheckModifyState proc uses esi hWnd:HWND

    mov esi,1
    .if SendMessage(hEdit, EM_GETMODIFY, 0, 0)

        .if MessageBox(hWnd,
                "The data in the control is modified. Want to save it?",
                &AppName, MB_YESNOCANCEL) == IDYES
            SendMessage(hWnd, WM_COMMAND, IDM_SAVE, 0)
        .elseif eax==IDCANCEL
            dec esi
        .endif
    .endif
    mov eax,esi
    ret

CheckModifyState endp

OptionProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local clr:CHOOSECOLOR

    mov eax,uMsg
    .switch eax

      .case WM_INITDIALOG
        mov eax,TRUE
        .endc

      .case WM_COMMAND
        mov eax,wParam
        shr eax,16
        .if ax == BN_CLICKED
            mov eax,wParam
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax == IDC_BACKCOLORBOX
                RtlZeroMemory(&clr, sizeof(clr))
                mov  clr.lStructSize,sizeof(clr)
                push hWnd
                pop  clr.hwndOwner
                push hInstance
                pop  clr.hInstance
                push BackColor
                pop  clr.rgbResult
                mov  clr.lpCustColors,offset SyntaxColors
                mov  clr.Flags,CC_ANYCOLOR or CC_RGBINIT

                .if ChooseColor(&clr)
                    push clr.rgbResult
                    pop  BackColor
                    InvalidateRect(GetDlgItem(hWnd, IDC_BACKCOLORBOX), 0, TRUE)
                .endif
            .elseif ax==IDC_TEXTCOLORBOX
                RtlZeroMemory(&clr, sizeof(clr))
                mov  clr.lStructSize,sizeof(clr)
                push hWnd
                pop  clr.hwndOwner
                push hInstance
                pop  clr.hInstance
                push TextColor
                pop  clr.rgbResult
                mov  clr.lpCustColors,offset SyntaxColors
                mov  clr.Flags,CC_ANYCOLOR or CC_RGBINIT

                .if ChooseColor(&clr)
                    push clr.rgbResult
                    pop  TextColor
                    InvalidateRect(GetDlgItem(hWnd, IDC_TEXTCOLORBOX), 0, TRUE)
                .endif
            .elseif ax==IDOK
                ;
                ; Save the modify state of the richedit control because changing
                ; the text color changes the modify state of the richedit control.
                ;
                ;SendMessage(hEdit, EM_GETMODIFY, 0, 0)
                ;push eax
                SetColor()
                ;pop eax
                ;SendMessage(hEdit, EM_SETMODIFY, eax, 0)
                EndDialog(hWnd, 0)
            .endif
        .endif
        mov eax,TRUE
        .endc

      .case WM_CTLCOLORSTATIC
        .if GetDlgItem(hWnd, IDC_BACKCOLORBOX) == lParam
            CreateSolidBrush(BackColor)
        .elseif GetDlgItem(hWnd, IDC_TEXTCOLORBOX) == lParam
            CreateSolidBrush(TextColor)
        .else
            mov eax,FALSE
        .endif
        .endc

      .case WM_CLOSE
        EndDialog(hWnd, 0)
        mov eax,TRUE
        .endc

      .default
        mov eax,FALSE
        .endc
    .endsw
    ret

OptionProc endp

SearchProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov eax,uMsg
    .switch eax

      .case WM_INITDIALOG
        push hWnd
        pop  hSearch
        ;
        ; Select the default search down option
        ;
        CheckRadioButton(hWnd, IDC_DOWN, IDC_UP, IDC_DOWN)
        SendDlgItemMessage(hWnd, IDC_FINDEDIT, WM_SETTEXT, 0, &FindBuffer)
        mov eax,TRUE
        .endc

      .case WM_COMMAND
        mov eax,wParam
        shr eax,16
        .if ax==BN_CLICKED
            mov eax,wParam
            .if ax == IDOK
                mov uFlags,0
                SendMessage(hEdit, EM_EXGETSEL, 0, &findtext.chrg)

                .if GetDlgItemText(hWnd, IDC_FINDEDIT, &FindBuffer, sizeof(FindBuffer))

                    .if IsDlgButtonChecked(hWnd, IDC_DOWN) == BST_CHECKED
                        or uFlags,FR_DOWN
                        mov eax,findtext.chrg.cpMin
                        .if eax!=findtext.chrg.cpMax
                            push findtext.chrg.cpMax
                            pop  findtext.chrg.cpMin
                        .endif
                        mov findtext.chrg.cpMax,-1
                    .else
                        mov findtext.chrg.cpMax,0
                    .endif

                    .if IsDlgButtonChecked(hWnd, IDC_MATCHCASE) == BST_CHECKED
                        or uFlags,FR_MATCHCASE
                    .endif

                    .if IsDlgButtonChecked(hWnd, IDC_WHOLEWORD) == BST_CHECKED
                        or uFlags,FR_WHOLEWORD
                    .endif
                    mov findtext.lpstrText,offset FindBuffer

                    .if SendMessage(hEdit, EM_FINDTEXTEX, uFlags, &findtext) != -1
                        SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    .endif
                .endif
            .elseif ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .else
                mov eax,FALSE
                .endc
            .endif
        .endif
        mov eax,TRUE
        .endc

      .case WM_CLOSE
        mov hSearch,0
        EndDialog(hWnd, 0)
        mov eax,TRUE    ; yes..
        .endc

      .default
        mov eax,FALSE
        .endc
    .endsw
    ret

SearchProc endp

ReplaceProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local settext:SETTEXTEX

    mov eax,uMsg
    .switch eax

      .case WM_INITDIALOG
        push hWnd
        pop  hSearch
        SetDlgItemText(hWnd, IDC_FINDEDIT,    &FindBuffer)
        SetDlgItemText(hWnd, IDC_REPLACEEDIT, &ReplBuffer)
        mov eax,TRUE
        .endc

      .case WM_COMMAND
        mov eax,wParam
        shr eax,16
        .if ax == BN_CLICKED
            mov eax,wParam
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax==IDOK
                GetDlgItemText(hWnd, IDC_FINDEDIT,    &FindBuffer, sizeof(FindBuffer))
                GetDlgItemText(hWnd, IDC_REPLACEEDIT, &ReplBuffer, sizeof(ReplBuffer))
                mov findtext.chrg.cpMin,0
                mov findtext.chrg.cpMax,-1
                mov findtext.lpstrText,offset FindBuffer
                mov settext.flags,ST_SELECTION
                mov settext.codepage,0;CP_ACP
                .while 1
                    .break .if SendMessage(hEdit, EM_FINDTEXTEX, FR_DOWN, &findtext) == -1
                    SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    SendMessage(hEdit, EM_SETTEXTEX, &settext, &ReplBuffer)
                .endw
            .endif
        .endif
        mov eax,TRUE
        .endc

      .case WM_CLOSE
        mov hSearch,0
        EndDialog(hWnd, 0)
        mov eax,TRUE    ; ...
        .endc

      .default
        mov eax,FALSE
    .endsw
    ret
ReplaceProc endp

GoToProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local LineNo:DWORD
    local chrg:CHARRANGE

    mov eax,uMsg
    .switch eax

      .case WM_INITDIALOG
        push hWnd
        pop  hSearch
        mov eax,TRUE
        .endc

      .case WM_COMMAND
        mov eax,wParam
        shr eax,16
        .if ax == BN_CLICKED
            mov eax,wParam
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax == IDOK
                mov LineNo,GetDlgItemInt(hWnd, IDC_LINENO, NULL, FALSE)
                .if SendMessage(hEdit, EM_GETLINECOUNT, 0, 0) > LineNo
                    SendMessage(hEdit, EM_LINEINDEX, LineNo, 0)
                    SendMessage(hEdit, EM_SETSEL, eax, eax)
                    SetFocus(hEdit)
                .endif
            .endif
        .endif
        mov eax,TRUE
        .endc

      .case WM_CLOSE
        mov hSearch,0
        EndDialog(hWnd, 0)
        mov eax,TRUE    ; ...
        .endc

      .default
        mov eax,FALSE
    .endsw
    ret

GoToProc endp

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    local buffer[256]:sbyte
    local hPopup:HMENU
    local pt:POINT
    local ofn:OPENFILENAME
    local hFile:HANDLE
    local editstream:EDITSTREAM
    local chrg:CHARRANGE

    .switch message

      .case WM_CREATE

        .if !LoadLibrary("Msftedit.dll")

            PostQuitMessage(1)
            xor eax,eax
            .endc
        .endif

        mov hEdit,CreateWindowEx(
                WS_EX_CLIENTEDGE,
                MSFTEDIT_CLASS,
                0,
                ES_MULTILINE or WS_VISIBLE or WS_CHILD or WS_BORDER or WS_VSCROLL or WS_HSCROLL or ES_NOHIDESEL,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                hWnd,
                RichEditID,
                hInstance,
                NULL
        )
        SendMessage(hEdit, EM_SETTYPOGRAPHYOPTIONS, TO_SIMPLELINEBREAK, TO_SIMPLELINEBREAK)
        SendMessage(hEdit, EM_GETTYPOGRAPHYOPTIONS, 1, 1)
        SendMessage(hEdit, EM_SETEDITSTYLE, SES_EMULATESYSEDIT, SES_EMULATESYSEDIT)
        mov OldWndProc,SetWindowLong(hEdit, GWL_WNDPROC, &RichEditProc)
        SendMessage(hEdit, EM_LIMITTEXT, -1, 0)
        SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
        SendMessage(hEdit, EM_SETEVENTMASK, 0, ENM_MOUSEEVENTS)
        SendMessage(hEdit, EM_EMPTYUNDOBUFFER, 0, 0)
        InitProfile()
        ReadStyle(&Profile)
        ReadConfig(&Profile)
        mov hFont,CreateFontIndirect(&AppFont)
        SendMessage(hEdit, WM_SETFONT, eax, 1)
        SetColor()
        xor eax,eax
        .endc

      .case WM_NOTIFY
        push esi
        mov esi,lParam
        assume esi:ptr NMHDR
        .if [esi].code == EN_MSGFILTER
            assume esi:ptr MSGFILTER
            .if [esi].msg == WM_RBUTTONDOWN

                mov hPopup,GetSubMenu(GetMenu(hWnd), 1)
                PrepareEditMenu(eax)
                mov edx,[esi].lParam
                mov ecx,edx
                and edx,0xFFFF
                shr ecx,16
                mov pt.x,edx
                mov pt.y,ecx
                ClientToScreen(hWnd, &pt)
                TrackPopupMenu(hPopup, TPM_LEFTALIGN or TPM_BOTTOMALIGN,
                    pt.x, pt.y, NULL, hWnd, NULL)
            .endif
        .endif
        pop esi
        xor eax,eax
        .endc

      .case WM_INITMENUPOPUP
        movzx eax,word ptr lParam
        .switch eax
          .case 0       ; file menu
            .if FileOpened == TRUE    ; a file is already opened
                EnableMenuItem(wParam, IDM_OPEN, MF_GRAYED)
                EnableMenuItem(wParam, IDM_CLOSE, MF_ENABLED)
                EnableMenuItem(wParam, IDM_SAVE, MF_ENABLED)
                EnableMenuItem(wParam, IDM_SAVEAS, MF_ENABLED)
            .else
                EnableMenuItem(wParam, IDM_OPEN, MF_ENABLED)
                EnableMenuItem(wParam, IDM_CLOSE, MF_GRAYED)
                EnableMenuItem(wParam, IDM_SAVE, MF_GRAYED)
                EnableMenuItem(wParam, IDM_SAVEAS, MF_GRAYED)
            .endif
            .endc
          .case 1   ; edit menu
            PrepareEditMenu(wParam)
            ; search menu bar
            .if FileOpened==TRUE
                EnableMenuItem(wParam, IDM_FIND, MF_ENABLED)
                EnableMenuItem(wParam, IDM_FINDNEXT, MF_ENABLED)
                EnableMenuItem(wParam, IDM_FINDPREV, MF_ENABLED)
                EnableMenuItem(wParam, IDM_REPLACE, MF_ENABLED)
                EnableMenuItem(wParam, IDM_GOTOLINE, MF_ENABLED)
            .else
                EnableMenuItem(wParam, IDM_FIND, MF_GRAYED)
                EnableMenuItem(wParam, IDM_FINDNEXT, MF_GRAYED)
                EnableMenuItem(wParam, IDM_FINDPREV, MF_GRAYED)
                EnableMenuItem(wParam, IDM_REPLACE, MF_GRAYED)
                EnableMenuItem(wParam, IDM_GOTOLINE, MF_GRAYED)
            .endif
            .endc
        .endsw
        xor eax,eax
        .endc

      .case WM_COMMAND

        .if !lParam       ; menu commands

            movzx eax,word ptr wParam
            .switch eax

              .case IDM_OPEN

                RtlZeroMemory(&ofn, sizeof(ofn))
                mov  ofn.lStructSize,sizeof(ofn)
                push hWnd
                pop  ofn.hwndOwner
                push hInstance
                pop  ofn.hInstance
                mov ofn.lpstrFilter,offset ASMFilter
                mov ofn.lpstrFile,offset FileName
                mov byte ptr [FileName],0
                mov ofn.nMaxFile,sizeof FileName
                mov ofn.Flags,OFN_FILEMUSTEXIST or OFN_HIDEREADONLY or OFN_PATHMUSTEXIST

                .if GetOpenFileName(&ofn)

                    .if CreateFile(&FileName,
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            0) != INVALID_HANDLE_VALUE

                        mov hFile,eax
                        mov editstream.dwCookie,eax
                        mov editstream.pfnCallback,offset StreamInProc

                        SendMessage(hEdit, EM_STREAMIN, SF_TEXT, &editstream)
                        SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
                        CloseHandle(hFile)
                        mov FileOpened,TRUE

                    .else
                        MessageBox(hWnd, "Cannot open the file",
                            &AppName, MB_OK or MB_ICONERROR)
                    .endif
                .endif
                .endc

              .case IDM_CLOSE

                .if CheckModifyState(hWnd)
                    SetWindowText(hEdit, 0)
                    mov FileOpened,FALSE
                .endif
                .endc

              .case IDM_SAVE

                .if CreateFile(&FileName,
                        GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        0) != INVALID_HANDLE_VALUE

                    mov hFile,eax
                    mov editstream.dwCookie,eax
                    mov editstream.pfnCallback,offset StreamOutProc

                    SendMessage(hEdit, EM_STREAMOUT, SF_TEXT, &editstream)
                    SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
                    CloseHandle(hFile)
                .else
                    MessageBox(hWnd, "Cannot open the file",
                            &AppName,  MB_OK or MB_ICONERROR)
                .endif
                .endc

              .case IDM_COPY
                SendMessage(hEdit, WM_COPY, 0, 0)
                .endc

              .case IDM_CUT
                SendMessage(hEdit, WM_CUT, 0, 0)
                .endc

              .case IDM_PASTE
                SendMessage(hEdit, WM_PASTE, 0, 0)
                .endc

              .case IDM_DELETE
                SendMessage(hEdit, EM_REPLACESEL, TRUE, 0)
                .endc

              .case IDM_SELECTALL
                mov chrg.cpMin,0
                mov chrg.cpMax,-1
                SendMessage(hEdit, EM_EXSETSEL, 0, &chrg)
                .endc

              .case IDM_UNDO
                SendMessage(hEdit, EM_UNDO, 0, 0)
                .endc

              .case IDM_REDO
                SendMessage(hEdit, EM_REDO, 0, 0)
                .endc

              .case IDM_SAVEAS
                RtlZeroMemory(&ofn, sizeof(ofn))
                mov ofn.lStructSize,sizeof(ofn)
                push hWnd
                pop ofn.hwndOwner
                push hInstance
                pop ofn.hInstance
                mov ofn.lpstrFilter,offset ASMFilter
                mov ofn.lpstrFile,offset AltFileName
                mov AltFileName,0
                mov ofn.nMaxFile,sizeof AltFileName
                mov ofn.Flags,OFN_FILEMUSTEXIST or OFN_HIDEREADONLY or OFN_PATHMUSTEXIST

                .if GetSaveFileName(&ofn)
                    .if CreateFile(&AltFileName,
                        GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        0) != INVALID_HANDLE_VALUE

                        mov hFile,eax
                        mov editstream.dwCookie,eax
                        mov editstream.pfnCallback,offset StreamOutProc
                        SendMessage(hEdit, EM_STREAMOUT, SF_TEXT, &editstream)
                        SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
                        CloseHandle(hFile)
                    .endif
                .endif
                .endc

              .case IDM_FIND
                .if !hSearch
                    CreateDialogParam(hInstance, IDD_FINDDLG, hWnd, &SearchProc, 0)
                .endif
                .endc

              .case IDM_REPLACE
                .if !hSearch
                    CreateDialogParam(hInstance, IDD_REPLACEDLG, hWnd, &ReplaceProc, 0)
                .endif
                .endc

              .case IDM_GOTOLINE
                .if !hSearch
                    CreateDialogParam(hInstance, IDD_GOTODLG, hWnd, &GoToProc, 0)
                .endif
                .endc

              .case IDM_FINDNEXT
                .if FindBuffer
                    SendMessage(hEdit, EM_EXGETSEL, 0, &findtext.chrg)
                    mov eax,findtext.chrg.cpMin
                    .if eax != findtext.chrg.cpMax
                        push findtext.chrg.cpMax
                        pop  findtext.chrg.cpMin
                    .endif
                    mov findtext.chrg.cpMax,-1
                    mov findtext.lpstrText,offset FindBuffer

                    .if SendMessage(hEdit, EM_FINDTEXTEX, FR_DOWN, &findtext) != -1
                        SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    .endif
                .endif
                .endc

              .case IDM_FINDPREV
                .if FindBuffer
                    SendMessage(hEdit, EM_EXGETSEL, 0, &findtext.chrg)
                    mov findtext.chrg.cpMax,0
                    mov findtext.lpstrText,offset FindBuffer

                    .if SendMessage(hEdit, EM_FINDTEXTEX, 0, &findtext) != -1
                        SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    .endif
                .endif
                .endc

              .case IDM_FONT
                DLGSelectFont(hWnd)
                .endc

              .case IDM_COLOR
                DialogBoxParam(hInstance, IDD_OPTIONDLG, hWnd, &OptionProc, 0)
                .endc

              .case IDM_STATUSBAR
                MessageBox(hEdit, "Status Bar", "View", MB_OK)
                .endc

              .case IDM_VIEWHELP
                MessageBox(hEdit, "View Help", "Help", MB_OK)
                .endc

              .case IDM_ABOUT
                MessageBox(hEdit, "About", "Help", MB_OK)
                .endc

              .case IDM_EXIT
                SendMessage(hWnd, WM_CLOSE, 0, 0)
                .endc
            .endsw
        .endif
        xor eax,eax
        .endc

      .case WM_CLOSE

        .if CheckModifyState(hWnd)
            DestroyWindow(hWnd)
        .endif
        .endc

      .case WM_SIZE
        mov eax,lParam
        mov edx,eax
        and eax,0FFFFh
        shr edx,16
        MoveWindow(hEdit, 0, 0, eax, edx, TRUE)
        .endc

      .case WM_DESTROY
        PostQuitMessage(0)
        xor eax,eax
        .endc

      .default
        DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    ret

WndProc endp

WinMain proc WINAPI hInst: HINSTANCE,
     hPrevInstance: HINSTANCE,
         lpCmdLine: LPSTR,
          nShowCmd: SINT

    local wc:WNDCLASSEX
    local msg:MSG
    local hwnd:HANDLE

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,WndProc

    mov ecx,hInst
    xor eax,eax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov hInstance,ecx
    mov wc.hInstance,ecx
    mov wc.hbrBackground,COLOR_WINDOW+1
    mov wc.lpszMenuName,IDR_MAINMENU

    lea eax,@CStr("TestClass")
    mov wc.lpszClassName,eax
    mov wc.hIcon,LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,eax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)

    RegisterClassEx(&wc)

    mov eax,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0, "TestClass", "Testpad", WS_OVERLAPPEDWINDOW,
        eax, eax, eax, eax, 0, 0, hInstance, 0)

    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)
    mov hAccel,LoadAccelerators(hInstance, IDR_MAINACCEL)

    .while GetMessage(&msg, 0, 0, 0)

        .if !TranslateAccelerator(hwnd, hAccel, &msg)

            TranslateMessage(&msg)
            DispatchMessage(&msg)
        .endif
    .endw
    mov eax,msg.wParam
    ret

WinMain endp

WinStart proc
    mov ebx,GetModuleHandle(0)
    ExitProcess(WinMain(ebx, 0, GetCommandLine(), SW_SHOWDEFAULT))
WinStart endp

RCBEGIN

    RCTYPES 3
    RCENTRY RT_MENU
    RCENTRY RT_DIALOG
    RCENTRY RT_ACCELERATOR

    RCENUMN 1
    RCENUMX IDR_MAINMENU
    RCENUMN 4
    RCENUMX IDD_OPTIONDLG
    RCENUMX IDD_FINDDLG
    RCENUMX IDD_GOTODLG
    RCENUMX IDD_REPLACEDLG
    RCENUMN 1
    RCENUMX 105
    REPEAT 6
    RCLANGX LANGUAGEID
    ENDM

    MENUBEGIN
      MENUNAME IDS_FILE
        MENUITEM IDM_OPEN,   IDS_OPEN
        MENUITEM IDM_CLOSE,  IDS_CLOSE
        MENUITEM IDM_SAVE,   IDS_SAVE
        MENUITEM IDM_SAVEAS, IDS_SAVEAS
        SEPARATOR
        MENUITEM IDM_EXIT, IDS_EXIT, MF_END
      MENUNAME IDS_EDIT
        MENUITEM IDM_UNDO,   IDS_UNDO
        MENUITEM IDM_REDO,   IDS_REDO
        SEPARATOR
        MENUITEM IDM_COPY,   IDS_COPY
        MENUITEM IDM_CUT,    IDS_CUT
        MENUITEM IDM_PASTE,  IDS_PASTE
        MENUITEM IDM_DELETE, IDS_DELETE
        SEPARATOR
        MENUITEM IDM_FIND,     IDS_FIND
        MENUITEM IDM_FINDNEXT, IDS_FINDNEXT
        MENUITEM IDM_FINDPREV, IDS_FINDPREV
        MENUITEM IDM_REPLACE,  IDS_REPLACE
        MENUITEM IDM_GOTOLINE, IDS_GOTO
        SEPARATOR
        MENUITEM IDM_SELECTALL, IDS_SELECTALL, MF_END
      MENUNAME "Format"
        MENUITEM IDM_FONT,     "Font..."
        MENUITEM IDM_COLOR,    "Color...", MF_END
      MENUNAME "View"
        MENUITEM IDM_STATUSBAR,"Status Bar", MF_END
      MENUNAME "Help", MF_END
        MENUITEM IDM_VIEWHELP, "View Help"
        MENUITEM IDM_ABOUT,    "About", MF_END
    MENUEND

    DLGFLAGS equ DS_MODALFRAME or DS_SETFONT or WS_POPUP or WS_VISIBLE or WS_CAPTION or WS_SYSMENU

    DLGBEGIN DLGFLAGS,7,0,0,196,60
     CAPTION IDS_OPTIONS
     FONT 8, "MS Sans Serif"
      DEFPUSHBUTTON   IDS_OK,IDOK,137,7,50,14;39,14
      PUSHBUTTON      IDS_CANCEL,IDCANCEL,137,25,50,14
      GROUPBOX        0,IDC_STATIC,5,0,124,49
      LTEXT           IDS_BACKGR,IDC_STATIC,20,14,60,8
      LTEXT           0,IDC_BACKCOLORBOX,85,11,28,14,SS_NOTIFY or WS_BORDER
      LTEXT           IDS_FOREGR,IDC_STATIC,20,33,35,8
      LTEXT           0,IDC_TEXTCOLORBOX,85,29,28,14,SS_NOTIFY or WS_BORDER
    DLGEND

    DLGBEGIN DLGFLAGS,9,0,0,186,54
     CAPTION IDS_FIND2
     FONT 8, "MS Sans Serif"
      EDITTEXT        IDC_FINDEDIT,42,3,94,12,ES_AUTOHSCROLL
      CONTROL         IDS_MATCHCASE,IDC_MATCHCASE,RC_BUTTON,BS_AUTOCHECKBOX or WS_TABSTOP,6,24,54,10
      CONTROL         IDS_WHOLEWORD,IDC_WHOLEWORD,RC_BUTTON,BS_AUTOCHECKBOX or WS_TABSTOP,6,37,56,10
      CONTROL         IDS_DOWN,IDC_DOWN,RC_BUTTON,BS_AUTORADIOBUTTON or WS_TABSTOP,83,27,35,10
      CONTROL         IDS_UP,IDC_UP,RC_BUTTON,BS_AUTORADIOBUTTON or WS_TABSTOP,83,38,25,10
      DEFPUSHBUTTON   IDS_OK,IDOK,141,3,39,12
      PUSHBUTTON      IDS_CANCEL,IDCANCEL,141,18,39,12
      LTEXT           IDS_FINDWHAT,IDC_STATIC,5,4,34,8
      GROUPBOX        IDS_DIRECTION,IDC_STATIC,70,18,64,32
    DLGEND

    DLGBEGIN DLGFLAGS,4,0,0,106,30,WS_EX_TOOLWINDOW
     CAPTION IDS_GOTO2
     FONT 8, "MS Sans Serif", 0, 0, 0x1
      EDITTEXT        IDC_LINENO,29,4,35,11,ES_AUTOHSCROLL or ES_NUMBER,WS_EX_CLIENTEDGE
      DEFPUSHBUTTON   IDS_OK,IDOK,70,4,31,11
      PUSHBUTTON      IDS_CANCEL,IDCANCEL,70,17,31,11
      LTEXT           IDS_LINE,IDC_STATIC,8,5,18,8
    DLGEND

    DLGBEGIN DLGFLAGS,6,0,0,186,33
     CAPTION IDS_REPLACE2
     FONT 8, "MS Sans Serif"
      EDITTEXT        IDC_FINDEDIT,51,3,84,12,ES_AUTOHSCROLL
      EDITTEXT        IDC_REPLACEEDIT,51,17,84,11,ES_AUTOHSCROLL
      DEFPUSHBUTTON   IDS_OK,IDOK,142,3,39,11
      PUSHBUTTON      IDS_CANCEL,IDCANCEL,142,17,39,11
      LTEXT           IDS_FINDWHAT,IDC_STATIC,3,4,34,8
      LTEXT           IDS_REPLACEWITH,IDC_STATIC,3,18,42,8
    DLGEND

    DLGBEGIN 0x0046000B,0x00009C4E,11,71,0x9C51,0,11
      db 70,0, 78,156,0,0, 11,0, 71,0, 81,156, 0,0
      db 11,0,82,0,80,156,0,0,3,0,114,0,79,156,0,0
      db 139,0,114,0,82,156,0,0
    DLGEND

RCEND

    end WinStart
