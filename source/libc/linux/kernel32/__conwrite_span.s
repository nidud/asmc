; __CONWRITE_SPAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; This produce line output for WriteConsoleOutputW() and _conpaint()
;
include stdlib.inc
include stdio.inc
include conio.inc

.code

__conwrite_span proc WINAPI uses rbx fp:HANDLE, pCells:PCHAR_INFO, x:int_t, y:int_t, cols:int_t

   .new l:int_t
   .new wc:int_t
   .new color_changed:int_t = 0
   .new foreground:int_t = -1
   .new background:int_t = -1

    ldr rbx,pCells
    ldr eax,x
    inc eax
    ldr edx,y
    inc edx
    fprintf(fp, CSI "%d;%dH", edx, eax)

    .for ( l = cols : l > 0 : l--, rbx+=4 )

        movzx eax,byte ptr [rbx+2]
        mov ecx,eax
        and eax,0x0F
        shr ecx,4
        .if ( eax != foreground || ecx != background )
            mov color_changed,1
            mov foreground,eax
            mov background,ecx
            lea rdx,_terminalcolorid
            mov al,[rdx+rax]
            mov cl,[rdx+rcx]
            fprintf(fp, CSI "38;5;%dm" CSI "48;5;%dm", eax, ecx)
        .endif
        movzx ecx,[rbx].CHAR_INFO.Char.UnicodeChar
        .if ( ecx >= 0xD800 && ecx <= 0xDBFF ) ; High Surrogate ?
            .if ( l > 1 )
                movzx edx,[rbx+4].CHAR_INFO.Char.UnicodeChar
                .if ( edx >= 0xDC00 && edx <= 0xDFFF )
                    ;
                    ; Combine lead + trail for _wtoutf()
                    ;
                    shl edx,16
                    or  ecx,edx
                    add rbx,4 ; consume the second CHAR_INFO cell
                    dec l
                    jmp emit_char
                .endif
            .endif
            mov ecx,' '
        .elseif ( ecx >= 0xDC00 && ecx <= 0xDFFF )
            ;
            ; Orphaned low surrogate at left edge -> space
            ;
            mov ecx,' '
        .endif
       emit_char:
        mov wc,_wtoutf(ecx)
        mov edx,ecx
        fwrite(&wc, 1, edx, fp)
    .endf
    .if ( color_changed )
        fprintf(fp, CSI "m")
    .endif
    ret
    endp

    end
