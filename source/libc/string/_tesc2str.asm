; _TESC2STR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert Escape Sequences. Return number of chars converted.
;
; int _aesc2str(char *, char *);
; int _wesc2str(wchar_t *, wchar_t *);
;
include string.inc
include tchar.inc

.code

_tesc2str proc uses rsi rdi buffer:LPTSTR, string:LPTSTR

    ldr rsi,string
    ldr rdi,buffer

    xor eax,eax
    .while ( TCHAR ptr [rsi] )

        _tlodsb
        .if ( eax == '\' )   ; escape char ?

            xor ecx,ecx
            _tlodsb
            .switch eax
            .case 'a'        ; Alert (Beep, Bell)
                mov al,0x07
               .endc
            .case 'b'        ; Backspace
                mov al,0x08
               .endc
            .case 'e'        ; Escape character
                mov al,0x1B
               .endc
            .case 'f'        ; Formfeed Page Break
                mov al,0x0C
               .endc
            .case 'n'        ; Newline (Line Feed)
                mov al,0x0A
               .endc
            .case 'r'        ; Carriage Return
                mov al,0x0D
               .endc
            .case 't'        ; Horizontal Tab
                mov al,0x09
               .endc
            .case 'v'        ; Vertical Tab
                mov al,0x0B
               .endc
            .case 'U'        ; 8 hexadecimal digits (DWORD)
                add ecx,4
            .case 'u'        ; 4 hexadecimal digits (WORD)
ifndef _UNICODE
                add ecx,2
endif
            .case 'x'        ; 2/4 hexadecimal digits (BYTE/WORD)
                add ecx,2*TCHAR
                xor edx,edx
                .repeat
                    movzx eax,TCHAR ptr [rsi]
                    or al,0x20
                    .if ( eax >= '0' && eax <= '9' )
                        sub al,'0'
                    .elseif ( eax >= 'a' && eax <= 'f' )
                        sub al,'a'-10
                    .else
                        .break
                    .endif
                    add rsi,TCHAR
                    shl edx,4
                    add edx,eax
                .untilcxz
                movzx eax,_tdl
                .if ( eax != edx )

                    _tstosb
                    shr edx,8*TCHAR
                    mov _tal,_tdl
                .endif
                .endc
            .case '0'..'7'  ; ooo
                sub eax,'0'
                movzx ecx,TCHAR ptr [rsi]
                .if ( ecx >= '0' && ecx <= '7' )

                    sub ecx,'0'
                    shl eax,3
                    add eax,ecx
                    add rsi,TCHAR
                    movzx ecx,TCHAR ptr [rsi]
                    .if ( ecx >= '0' && ecx <= '7' )

                        sub ecx,'0'
                        shl eax,3
                        add eax,ecx
                        add rsi,TCHAR
                    .endif
                .endif
                .endc
if 0
            .case 0x27       ; apostrophe or single quotation mark
            .case '"'        ; double quotation mark
            .case '\'        ; another slash..
            .case '?'        ; question mark (used to avoid trigraphs)
               .endc
endif
            .default
                ;
                ; Use Microsoft Specific: \c --> c
                ;
            .endsw
        .endif
        _tstosb
    .endw
    mov TCHAR ptr [rdi],0
    mov rax,rdi
    sub rax,buffer
ifdef _UNICODE
    shr eax,1
endif
    ret

_tesc2str endp

    end
