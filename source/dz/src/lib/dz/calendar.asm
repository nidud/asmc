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

keylocal label dword
    dd MOUSECMD,    event_mouse
    dd KEY_ESC,     event_ESC
    dd KEY_HOME,    event_HOME
    dd KEY_RIGHT,   event_nextday
    dd KEY_LEFT,    event_prevday
    dd KEY_UP,      event_UP
    dd KEY_DOWN,    event_DOWN
    dd KEY_PGUP,    event_prevmnd
    dd KEY_PGDN,    event_nextmnd
    dd KEY_CTRLPGUP,event_prevyear
    dd KEY_CTRLPGDN,event_nextyear
    dd KEY_ENTER,   event_ENTER
    dd KEY_ALTX,    event_ESC
ifdef USE_MDALTKEYS
    dd KEY_ALTUP,   event_ALTUP
    dd KEY_ALTDN,   event_ALTDN
    dd KEY_ALTLEFT, event_ALTLEFT
    dd KEY_ALTRIGHT,event_ALTRIGHT
endif
    keycount = (($ - offset keylocal) / 8)
    keypos          db 1,5,9,13,17,21,25
    format_s_d      db '%s %d',0
    format_2d       db '%2d',0

    DLG_Calendar    dd 0
    DLG_Calendar2   dd 0
    xpos            dd 0
    ypos            dd 0
    curyear         dd 0
    curmonth        dd 0
    curday          dd 0
    year            dd 0
    month           dd 0
    day             dd 0
    week_day        dd 0
    days_in_month   dd 0
    current_year    dd 0
    current_month   dd 0
    calender        dd 0
    result          dd 0


    .code

    option  proc: private

getcurdate proc  ; GET SYSTEM DATE
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
    ret
getcurdate endp

incyear proc
    mov ecx,year
    cmp ecx,MAXYEAR
    je  @F
    inc ecx
    ret
@@:
    mov ecx,STARTYEAR
    ret
incyear endp

decyear proc
    mov ecx,year
    test    ecx,ecx
    jz  @F
    dec ecx
    ret
@@:
    mov ecx,MAXYEAR
    ret
decyear endp

putdate proc uses esi edi

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
    scputf(eax, edx, 0, 0, &format_s_d, ebx, year)
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
    .while  esi < days_in_month && edi < 10
        xor ecx,ecx
        .while  ecx < 7
            mov eax,3   ; first line
            .if  (week_day <= ecx && edi == eax) || \
                ((week_day > ecx || edi != eax) && edi > eax && esi < days_in_month)
                inc esi
                push    ecx
                push    edi
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
        scputf(eax, ebx, ecx, 2, &format_2d, esi)
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
    ret
putdate endp

setdate proc
    mov day,edx
    mov month,ebx
    mov year,ecx
    GetWeekDay(ecx, ebx, 0)
    mov week_day,eax
    DaysInMonth(year, ebx)
    mov days_in_month,eax
    putdate()
    ret
setdate endp

ifdef USE_MDALTKEYS

event_ALTUP proc
    mov eax,rcmoveup
    jmp DLMOVE_MOVE
event_ALTUP endp

event_ALTDN proc
    mov eax,rcmovedn
    jmp DLMOVE_MOVE
event_ALTDN endp

event_ALTLEFT proc
    mov eax,rcmoveleft
    jmp DLMOVE_MOVE
event_ALTLEFT endp

event_ALTRIGHT proc
    mov eax,rcmoveright
event_ALTRIGHT endp

DLMOVE_MOVE proc uses esi edi ebx
    mov ebx,DLG_Calendar
    mov esi,[ebx].S_DOBJ.dl_wp
    mov edi,[ebx].S_DOBJ.dl_rect
    push    eax
    dlhide(DLG_Calendar2)
    rcclrshade(edi, esi)
    pop eax
    push dword ptr [ebx].S_DOBJ.dl_flag
    push esi
    push edi
    call eax
    mov di,ax
    mov word ptr [ebx].S_DOBJ.dl_rect,ax
    mov byte ptr xpos,al
    mov byte ptr ypos,ah
    add eax,0A03h
    mov ebx,DLG_Calendar2
    mov word ptr [ebx].S_DOBJ.dl_rect,ax
    rcsetshade(edi, esi)
    dlshow(ebx)
    ret
DLMOVE_MOVE endp

endif

event_ENTER proc
    mov eax,1
    mov result,eax
event_ENTER endp

event_ESC proc
    inc byte ptr calender
    ret
event_ESC endp

event_HOME proc
    call    getcurdate
    jmp putdate
event_HOME endp

event_nextday proc
    mov edx,day
    inc edx
    cmp edx,days_in_month
    ja  event_nextmnd
    mov day,edx
    jmp putdate
event_nextday endp

event_prevday proc
    mov edx,day
    cmp edx,1
    je  @F
    mov ecx,year
    mov ebx,month
    dec edx
    jmp setdate
@@:
    event_prevmnd()
    mov eax,days_in_month
    mov day,eax
    jmp putdate
event_prevday endp

event_UP proc
    mov eax,7
    cmp day,eax
    jbe event_prevday
    sub day,eax
    jmp putdate
event_UP endp

event_DOWN proc
    mov eax,day
    add eax,7
    cmp eax,days_in_month
    ja  event_nextday
    mov day,eax
    jmp putdate
event_DOWN endp

event_prevmnd proc
    mov edx,1
    mov ebx,month
    mov ecx,year
    cmp ebx,1
    je  @F
    dec ebx
    jmp setdate
@@:
    mov ebx,12
    decyear()
    jmp setdate
event_prevmnd endp

event_nextmnd proc
    mov ebx,month
    cmp ebx,12
    je  event_nextyear
    mov edx,1
    mov ecx,year
    inc ebx
    jmp setdate
event_nextmnd endp

event_prevyear proc
    mov edx,1
    mov ebx,edx
    decyear()
    jmp setdate
event_prevyear endp

event_nextyear proc
    mov edx,1
    mov ebx,edx
    incyear()
    jmp setdate
event_nextyear endp

event_mouse proc
    mousex()
    mov edx,eax
    mousey()
    mov ebx,DLG_Calendar
    rcxyrow(dword ptr [ebx].S_DOBJ.dl_rect, edx, eax)
    test    eax,eax
    jz  event_ESC
    dlhide(DLG_Calendar2)
    dlmove(DLG_Calendar)
    mov ebx,DLG_Calendar
    sub eax,eax
    mov al,[ebx+4]
    mov dl,al
    mov xpos,eax
    mov al,[ebx+5]
    mov ypos,eax
    mov ah,al
    mov al,dl
    add ax,0A03h
    mov ebx,DLG_Calendar2
    mov [ebx+4],ax
    dlshow(DLG_Calendar2)
    ret
event_mouse endp

    option proc:PUBLIC

cmcalendar proc uses ebx
  local t:SYSTEMTIME
    GetLocalTime(&t)
    movzx eax,t.wDay
    mov curday,eax
    mov ax,t.wMonth
    mov curmonth,eax
    mov ax,t.wYear
    mov curyear,eax
    xor eax,eax
    mov calender,eax
    mov current_year,eax
    mov current_month,eax
    mov result,eax
    .if rsopen(&CALENDAR_RC)
        mov DLG_Calendar,eax
        mov ebx,eax
        sub eax,eax
        mov al,[ebx][4]
        mov xpos,eax
        mov al,[ebx][5]
        mov ypos,eax
        dlshow(DLG_Calendar)
    rsopen(&CALENDAR2_RC)
        mov DLG_Calendar2,eax
        dlshow(eax)
    getcurdate()
    setdate()
    msloop()
        .while !calender
        tgetevent()
            mov ecx,keycount
            xor ebx,ebx
            .repeat
                .if eax == keylocal[ebx]
                    call keylocal[ebx+4]
                    .break
                .endif
                add ebx,8
            .untilcxz
        .endw
        dlclose(DLG_Calendar2)
        dlclose(DLG_Calendar)
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
