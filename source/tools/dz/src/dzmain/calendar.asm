include time.inc
include consx.inc

STARTYEAR   equ 0
MAXYEAR     equ 3000

USE_MDALTKEYS equ 1

.data

;******** Resource begin CALENDAR *
;   { 0x005C,   0,   0, {42, 2,29,10} },
;******** Resource data  *******************
CALENDAR_RC label word
    dw  00283h  ; Alloc size
    dw  0005Ch,00000h,0022Ah,00A1Dh,03AF0h,0F02Fh,0293Ah,01DF0h
    dw  0F02Fh,02974h,01DF0h,0F02Fh,0DF1Dh,04D20h,06E6Fh,05420h
    dw  06575h,05720h,06465h,05420h,07568h,04620h,06972h,05320h
    dw  07461h,05320h,06E75h,02020h,01BF0h,0F0C4h,020AFh,01DF0h
    dw  02FDCh
;   68 byte
IDD_CALENDAR dd CALENDAR_RC

;   public  IDD_CALENDAR

;******** Resource end   CALENDAR *

;******** Resource begin CALENDAR2 *
;   { 0x0010,   0,   0, {45,12,14, 1} },
;******** Resource data  *******************
CALENDAR2_RC label word
    dw  0002Ch  ; Alloc size
    dw  00010h,00000h,00C2Dh,0010Eh,00EF0h,0F007h,0200Eh,00707h
;   18 byte
;******** Resource end   CALENDAR2 *

    cp_jan  db "January",0
    cp_feb  db "February",0
    cp_mar  db "March",0
    cp_apr  db "April",0
    cp_may  db "May",0
    cp_jun  db "June",0
    cp_jul  db "July",0
    cp_aug  db "August",0
    cp_sep  db "September",0
    cp_oct  db "October",0
    cp_nov  db "November",0
    cp_dec  db "December",0
    cp_month label dword
            dd cp_jan,cp_feb,cp_mar,cp_apr,cp_may,cp_jun
            dd cp_jul,cp_aug,cp_sep,cp_oct,cp_nov,cp_dec
    keypos  db 1,5,9,13,17,21,25

    .code

cmcalendar proc uses esi edi ebx

  local t:SYSTEMTIME
  local mouseloop
  local dialog,dialog2
  local xpos,ypos
  local curyear,curmonth,curday
  local year,month,day
  local week_day
  local days_in_month
  local current_year
  local current_month
  local result

    GetLocalTime(&t)

    movzx eax,t.wDay
    mov curday,eax
    mov ax,t.wMonth
    mov curmonth,eax
    mov ax,t.wYear
    mov curyear,eax
    xor eax,eax
    mov current_year,eax
    mov current_month,eax
    mov result,eax

    .if rsopen(&CALENDAR_RC)

        mov dialog,eax
        mov ebx,eax
        sub eax,eax
        mov al,[ebx][4]
        mov xpos,eax
        mov al,[ebx][5]
        mov ypos,eax
        dlshow(dialog)
        rsopen(&CALENDAR2_RC)
        mov dialog2,eax
        dlshow(eax)
        mov edx,curday
        mov ebx,curmonth
        mov ecx,curyear
        mov esi,1
        xor edi,edi
        mov mouseloop,1

        .while 1

            .if esi
                mov day,edx
                mov month,ebx
                mov year,ecx
                mov week_day,GetWeekDay(ecx, ebx, 0)
                mov days_in_month,DaysInMonth(year, ebx)
                inc edi
                xor esi,esi
            .endif

            .if edi

                mov eax,year
                mov edx,month

                .if eax != current_year || edx != current_month

                    mov current_month,edx
                    mov current_year,eax
                    mov eax,xpos
                    mov edx,ypos
                    add al,3
                    add dl,10
                    scputw(eax, edx, 14, 0020h)
                    mov ebx,month
                    mov ebx,cp_month[ebx*4-4]
                    scputf(eax, edx, 0, 0, "%s %d", ebx, year)
                    mov ebx,xpos
                    mov edx,ypos
                    add dl,3
                    mov ecx,6
                    mov eax,20h
                    or  ah,at_background[B_Dialog]
                    or  ah,at_foreground[F_Dialog]
                    .repeat
                        scputw(ebx, edx, 29, eax)
                        inc dl
                    .untilcxz
                .endif

                xor esi,esi
                mov edi,3
                .while esi < days_in_month && edi < 10
                    xor ecx,ecx
                    .while ecx < 7
                        mov eax,3   ; first line
                        .if (week_day <= ecx && edi == eax) || \
                            ((week_day > ecx || edi != eax) && edi > eax && esi < days_in_month)
                            inc esi
                            push ecx
                            push edi
                            mov ebx,ecx
                            mov cl,at_background[B_Dialog]
                            mov al,at_foreground[F_DialogKey]
                            .if esi != day
                                mov al,at_foreground[F_Dialog]
                            .endif
                            or  cl,al
                            mov al,keypos[ebx]
                            mov ebx,edi
                            add ebx,ypos
                            add eax,xpos
                            mov edi,eax
                            scputf(eax, ebx, ecx, 2, "%2d", esi)
                            .if curday == esi
                                mov eax,curmonth
                                .if eax == month
                                    mov eax,curyear
                                    .if eax == year
                                        mov al,4
                                        or  al,at_background[B_Dialog]
                                        scputa(edi, ebx, 2, eax)
                                    .endif
                                .endif
                            .endif
                            pop edi
                            pop ecx
                        .endif
                        add ecx,1
                    .endw
                    add edi,1
                .endw

                .if mouseloop

                    msloop()
                    dec mouseloop
                .endif
                xor edi,edi
                xor esi,esi
            .endif

            .switch tgetevent()

            .case MOUSECMD
                mousex()
                mov edx,eax
                mousey()
                mov ebx,dialog
                .break .if !rcxyrow(dword ptr [ebx].S_DOBJ.dl_rect, edx, eax)
                dlhide(dialog2)
                dlmove(dialog)
                mov ebx,dialog
                sub eax,eax
                mov al,[ebx+4]
                mov dl,al
                mov xpos,eax
                mov al,[ebx+5]
                mov ypos,eax
                mov ah,al
                mov al,dl
                add ax,0x0A03
                mov ebx,dialog2
                mov [ebx+4],ax
                dlshow(dialog2)
                .endc

            .case KEY_ENTER
                mov eax,1
                mov result,eax
            .case KEY_ALTX
            .case KEY_ESC
                .break

            .case KEY_HOME
                GetWeekDay(curyear, curmonth, 0)
                mov week_day,eax
                DaysInMonth(curyear, curmonth)
                mov days_in_month,eax
                mov edx,curday
                mov day,edx
                mov ebx,curmonth
                mov month,ebx
                mov ecx,curyear
                mov year,ecx
                inc edi
                .endc

            .case KEY_RIGHT
                mov edx,day
                inc edx
                .if edx > days_in_month
                    .gotosw(KEY_PGDN)
                .endif
                mov day,edx
                inc edi
                .endc

            .case KEY_LEFT
                mov edx,day
                .if edx != 1
                    mov ecx,year
                    mov ebx,month
                    dec edx
                    inc edi
                .else
                    mov edx,1
                    mov ebx,month
                    mov ecx,year
                    .if ebx != 1
                        dec ebx
                    .else
                        mov ebx,12
                        .if ecx
                            dec ecx
                        .else
                            mov ecx,MAXYEAR
                        .endif
                    .endif
                    mov day,edx
                    mov month,ebx
                    mov year,ecx
                    mov week_day,GetWeekDay(ecx, ebx, 0)
                    mov days_in_month,DaysInMonth(year, ebx)
                    mov day,eax
                    inc edi
                .endif
                .endc

            .case KEY_UP
                mov eax,7
                .if day <= eax

                    .gotosw(KEY_LEFT)
                .endif
                sub day,eax
                inc edi
                .endc

            .case KEY_DOWN
                mov eax,day
                add eax,7
                .if eax > days_in_month

                    .gotosw(KEY_RIGHT)
                .endif
                mov day,eax
                inc edi
                .endc

            .case KEY_PGUP
                mov edx,1
                mov ebx,month
                mov ecx,year
                .if ebx != 1
                    dec ebx
                .else
                    mov ebx,12
                    mov ecx,year
                    .if ecx
                        dec ecx
                    .else
                        mov ecx,MAXYEAR
                    .endif
                .endif
                inc esi
                .endc

            .case KEY_PGDN
                mov ebx,month
                .if ebx == 12

                    .gotosw(KEY_CTRLPGDN)
                .endif
                mov edx,1
                mov ecx,year
                inc ebx
                inc esi
                .endc

            .case KEY_CTRLPGUP
                mov edx,1
                mov ebx,edx
                mov ecx,year
                .if ecx
                    dec ecx
                .else
                    mov ecx,MAXYEAR
                .endif
                inc esi
                .endc

            .case KEY_CTRLPGDN
                mov edx,1
                mov ebx,edx
                mov ecx,year
                .if ecx != MAXYEAR
                    inc ecx
                .else
                    mov ecx,STARTYEAR
                .endif
                inc esi
                .endc
            .endsw
        .endw

        dlclose(dialog2)
        dlclose(dialog)
        mov edx,day
        mov ebx,month
        mov ecx,year
        mov eax,result
        .if eax
            mov eax,ebx
        .endif
    .endif
    ret
cmcalendar endp

    END
