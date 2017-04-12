; TIMER.ASM--
;
; Test SetConsoleSize( cols, rows )
;
; And Calendar functions for dates 0..3000
;
;	DaysInFebruary( year )
;	DaysInMonth( year, month )
;
include consx.inc
include time.inc
include string.inc
include stdio.inc
include stdlib.inc
include process.inc
include winbase.inc
include crtl.inc

STARTYEAR	equ 0
MAXYEAR		equ 3000

externdef	IDD_TMain:PTR S_ROBJ
externdef	IDD_About:PTR S_ROBJ
externdef	IDD_Help1:PTR S_ROBJ
externdef	IDD_Help2:PTR S_ROBJ

	.data

cp_usage	db "TIMER Version 1.0 Copyright (c) 2016 GNU General Public License",10,10
		db "USAGE:     TIMER [-/option] [Command]",10
		db 10
		db "/C         Create New Console",10
		db "/D#        Date /DYYYY-MM-DD",10
		db "/T#        Time /THH:MM:SS",10
		db 10
		db "Command    Program to execute on time out",10
		db "           default is .\popup.bat",10
		db 10,0

cp_batch	db "popup.bat",0
keypos		db 1,5,9,13,17,21,25
format_2d	db "%2d",0
format_q	db "%19I64d",0
format_date	db "%4d-%02d-%02d",0
format_time	db "%02d:%02d:%02d %7s",0

		ALIGN	4

cp_command	db 256 dup(0)

cp_months	db "Jan",0
		db "Feb",0
		db "Mar",0
		db "Apr",0
		db "May",0
		db "Jun",0
		db "Jul",0
		db "Aug",0
		db "Sep",0
		db "Oct",0
		db "Nov",0
		db "Dec",0

DLG_TMain	dd 0
mainswitch	dd 1
xpos		dd 0
ypos		dd 5
l_time		SYSTEMTIME <>	; local time
c_time		SYSTEMTIME <>	; user time
diff_t		dd 0		; -1, 0, 1
week_day	dd 0		; first week-day in current month
days_in_month	dd 0
old_year	dd -1
old_month	dd -1
old_day		dd -1
old_sec		dd -1
o_scrcol	dd 80
o_scrrow	dd 25

l_time_x	equ 1
l_time_y	equ 0
c_time_y	equ 7
c_days_y	equ 2

	.code

dummy	PROC
	xor	eax,eax
	ret
dummy	ENDP

event_help PROC
	invoke	rsmodal,IDD_About
	cmp	eax,1
	je	event_help1
	cmp	eax,2
	je	event_help2
	xor	eax,eax
	ret
event_help ENDP

event_help1 PROC
	invoke	rsmodal,IDD_Help1
	cmp	eax,1
	je	event_help
	cmp	eax,2
	je	event_help2
	xor	eax,eax
	ret
event_help1 ENDP

event_help2 PROC
	invoke	rsmodal,IDD_Help2
	cmp	eax,1
	je	event_help
	cmp	eax,2
	je	event_help1
	xor	eax,eax
	ret
event_help2 ENDP
;
; Add up days from year zero
;
DaysInYMD PROC USES esi edi ebx Years, Months, Days
	mov	eax,Years
	mov	ebx,eax
	shr	eax,2
	mov	ecx,365 * 4 + 1
	mul	ecx
	mov	esi,eax
	.while	ebx & 3
		DaysInFebruary(ebx)
		add	eax,365-28
		add	esi,eax
		sub	ebx,1
	.endw
	mov	ebx,Years
	.if	ebx
		DaysInFebruary(ebx)
		add	eax,365-28
		sub	esi,eax
	.endif
	mov	edi,Months
	.while	edi > 1
		sub	edi,1
		DaysInMonth(ebx, edi)
		add	esi,eax
	.endw
	mov	eax,Days
	add	eax,esi
	dec	eax
	ret
DaysInYMD ENDP
;
; Add up days and time in seconds
;
SecondsInDHMS PROC USES esi edi Days, Hours, Minutes, Seconds
	mov	esi,Days
	mov	eax,24*60*60
	mul	esi
	mov	edi,eax
	mov	esi,edx
	mov	eax,Seconds
	add	edi,eax
	adc	esi,0
	mov	eax,Minutes
	mov	ecx,60
	mul	ecx
	add	edi,eax
	adc	esi,edx
	mov	eax,Hours
	mov	ecx,60*60
	mul	ecx
	add	eax,edi
	adc	edx,esi
	ret
SecondsInDHMS ENDP
;
; Home
;
set_local_time PROC
	GetLocalTime( addr c_time )
set_local_time ENDP
;
; Set first week-day and day-count for month
;
set_time PROC
	mov	diff_t,0
	dec	old_sec
	movzx	eax,c_time.wMonth
	movzx	edx,c_time.wYear
	push	eax
	push	edx
	DaysInYMD(edx, eax, 0)
	mov	ecx,7
	xor	edx,edx
	div	ecx
	mov	week_day,edx	; 0..6 - sun = 0
	call	DaysInMonth
	mov	days_in_month,eax
	ret
set_time ENDP
;
; Print Date Time Month string
;
PutDate PROC USES esi edi ebx y, SystemTime
	mov	esi,SystemTime
	movzx	eax,[esi].SYSTEMTIME.wDay
	movzx	ecx,[esi].SYSTEMTIME.wMonth
	movzx	edx,[esi].SYSTEMTIME.wYear
	lea	ebx,cp_months[ecx*4-4]
	scputf( l_time_x, y, 0, 0, addr format_date, edx, ecx, eax )
	movzx	eax,[esi].SYSTEMTIME.wSecond
	movzx	ecx,[esi].SYSTEMTIME.wMinute
	movzx	edx,[esi].SYSTEMTIME.wHour
	mov	esi,l_time_x
	add	esi,11
	scputf( esi, y, 0, 0, addr format_time, edx, ecx, eax, ebx )
	ret
PutDate ENDP
;
; Print current Date
;
PrintDate PROC USES esi edi ebx

	mov	ebx,xpos
	mov	edx,ypos
	mov	ecx,6
	mov	eax,20h
	or	ah,at_background[B_Dialog]
	or	ah,at_foreground[F_Dialog]
	.repeat
		scputw( ebx, edx, 29, eax )
		add	edx,1
	.untilcxz
	xor	esi,esi
	xor	edi,edi
	.while	esi < days_in_month && edi < 7
		xor	ebx,ebx
		.while	ebx < 7 && esi < days_in_month
			.if	edi || week_day <= ebx
				add	esi,1
				mov	ax,l_time.wMonth
				mov	cx,l_time.wYear
				mov	dl,at_foreground[F_Dialog]
				.if	si == l_time.wDay && ax == c_time.wMonth && cx == c_time.wYear
					mov	dl,4
				.elseif si == c_time.wDay
					mov	dl,at_foreground[F_DialogKey]
				.endif
				or	dl,at_background[B_Dialog]
				movzx	eax,keypos[ebx]
				mov	ecx,edi
				add	ecx,ypos
				add	eax,xpos
				scputf( eax, ecx, edx, 2, addr format_2d, esi )
			.endif
			add	ebx,1
		.endw
		add	edi,1
	.endw
	PutDate(c_time_y, addr c_time )
	ret
PrintDate ENDP
;
; Pop-Up
;
TimeOut PROC USES esi edi ebx
	local	args[128]
	SetConsoleTitle( "Timer" )
	movzx	esi,c_time.wYear
	movzx	edi,c_time.wMonth
	movzx	ebx,c_time.wDay
	movzx	edx,c_time.wHour
	movzx	ecx,c_time.wMinute
	movzx	eax,c_time.wSecond
	sprintf( addr args, "%s %04d-%02d-%02dT%02d:%02d:%02d",
		addr cp_command, esi, edi, ebx, edx, ecx, eax )
	CreateConsole( addr args, _P_NOWAIT or CREATE_NEW_CONSOLE )
	ret
TimeOut ENDP
;
; Update functions
;
TimerUpdate PROC USES esi edi ebx

	local	diff_eax,
		diff_edx,
		diff_ecx,
		buffer[16]

	GetLocalTime( addr l_time )
	movzx	ebx,l_time.wSecond
	.if	ebx != old_sec
		mov	old_sec,ebx

		movzx	edx,c_time.wYear
		movzx	ecx,c_time.wMonth
		movzx	eax,c_time.wDay
		DaysInYMD(edx, ecx, eax)
		movzx	ebx,c_time.wHour
		movzx	edx,c_time.wMinute
		movzx	ecx,c_time.wSecond
		SecondsInDHMS(eax, ebx, edx, ecx)
		push	edx
		push	eax
		movzx	edx,l_time.wYear
		movzx	ecx,l_time.wMonth
		movzx	eax,l_time.wDay
		DaysInYMD(edx, ecx, eax)
		movzx	ebx,l_time.wHour
		movzx	edx,l_time.wMinute
		movzx	ecx,l_time.wSecond
		SecondsInDHMS(eax, ebx, edx, ecx)
		mov	edi,eax
		mov	esi,edx
		pop	eax
		pop	edx
		xor	ecx,ecx
		.if	esi > edx || (esi == edx && edi > eax)
			sub	edi,eax
			sbb	esi,edx
			mov	eax,edi
			mov	edx,esi
			dec	ecx
		.else
			.if	edx > esi || (edx == esi && eax > edi)
				inc	ecx
			.endif
			sub	eax,edi
			sbb	edx,esi
		.endif
		mov	diff_eax,eax
		mov	diff_edx,edx
		mov	diff_ecx,ecx
		mov	esi,eax
		or	eax,edx
		mov	eax,esi
		jz	toend

		.if	ecx != diff_t
			movzx	eax,at_background[B_Desktop]
			.if	ecx == 1
				mov	al,at_background[B_Error]
			.elseif ecx == -1
				mov	al,at_background[B_Panel]
			.endif
			or	al,at_foreground[F_Desktop]
			mov	edx,DLG_TMain
			movzx	edi,[edx].S_DOBJ.dl_rect.rc_col
			movzx	ebx,[edx].S_DOBJ.dl_rect.rc_x
			movzx	edx,[edx].S_DOBJ.dl_rect.rc_y
			add	edx,1
			mov	esi,6
			.repeat
				scputbg( ebx, edx, edi, eax )
				add	edx,1
				sub	esi,1
			.until	ZERO?
			.if	diff_ecx != 1
				SetConsoleTitle( "Timer" )
			.endif
		.endif

		PutDate(l_time_y, addr l_time )

		mov	eax,diff_eax
		mov	edx,diff_edx
		mov	esi,l_time_x + 8
		mov	edi,c_days_y + 3
		scputf( esi, edi, 0, 0, addr format_q, edx::eax )

		mov	eax,diff_eax
		mov	edx,diff_edx
		mov	ebx,60
		xor	ecx,ecx
		call	_U8D
		sub	edi,1
		scputf( esi, edi, 0, 0, addr format_q, edx::eax )

		mov	eax,diff_eax
		mov	edx,diff_edx
		mov	ebx,60*60
		xor	ecx,ecx
		call	_U8D
		sub	edi,1
		scputf( esi, edi, 0, 0, addr format_q, edx::eax )

		mov	eax,diff_eax
		mov	edx,diff_edx
		mov	ebx,60*60*24
		xor	ecx,ecx
		call	_U8D
		sub	edi,1
		scputf( esi, edi, 0, 0, addr format_q, edx::eax )

		mov	ecx,diff_ecx
		.if	ecx != 1 && diff_t == 1
			dec	diff_t
			call	TimeOut
			xor	ecx,ecx
		.else
			mov	diff_t,ecx
		.endif
		.if	ecx == 1
			lea	ebx,buffer
			mov	eax,diff_eax
			mov	edx,diff_edx
			sprintf( ebx, "T%I64d", edx::eax )
			SetConsoleTitle( ebx )
		.endif

	.endif
toend:
	xor	eax,eax
	ret
TimerUpdate ENDP
;
; Parse YYYY-MM-DD to c_time
;
parse_date PROC USES esi ebx string
	mov	ebx,string
	.if	strrchr( ebx, '-' )
		mov	esi,eax
		.if	strchr( ebx, '-' ) && esi != eax
			inc	eax
			.if	atol( eax ) && eax < 13
				mov	c_time.wMonth,ax
				.if	atol( ebx ) < MAXYEAR
					mov	c_time.wYear,ax
					call	set_time
					inc	esi
					.if	atol( esi ) && eax <= days_in_month
						mov	c_time.wDay,ax
						call	set_time
					.endif
				.endif
			.endif
		.endif
	.endif
	ret
parse_date ENDP
;
; Parse HH:MM:SS to c_time
;
parse_time PROC USES esi ebx string
	mov	ebx,string
	xor	esi,esi
	.if	atol( ebx ) < 24
		mov	c_time.wHour,ax
		inc	esi
	.endif
	.if	strchr( ebx, ':' )
		lea	ebx,[eax+1]
		.if	atol( ebx ) < 60
			mov	c_time.wMinute,ax
			inc	esi
		.endif
	.endif
	.if	strchr( ebx, ':' )
		lea	ebx,[eax+1]
		.if	atol( ebx ) < 60
			mov	c_time.wSecond,ax
			inc	esi
		.endif
	.endif
	.if	esi
		call	set_time
	.endif
	mov	eax,esi
	ret
parse_time ENDP
;
; Edit Time
;
event_gettime PROC USES esi edi ebx

local	wc[4]

	mov	esi,DLG_TMain
	mov	ebx,[esi+2*16].S_TOBJ.to_data
	lea	edi,wc
	mov	eax,0F200F20h;3F203F20h
	mov	ecx,4
	rep	stosd
	mov	edi,[esi+2*16].S_TOBJ.to_rect
	add	di,WORD PTR [esi].S_DOBJ.dl_rect
	rcxchg( edi, addr wc )
	SystemTimeToString( ebx, addr c_time )

	.if	dledit( ebx, edi, 64, 0 ) == KEY_ENTER || eax == KEY_KPENTER

		parse_time( ebx )
	.endif
	rcxchg( edi, addr wc )
	ret

event_gettime ENDP
;
; Edit Date
;
event_getdate PROC USES esi edi ebx
	local	wc[5]
	mov	esi,DLG_TMain
	mov	ebx,[esi+1*16].S_TOBJ.to_data
	movzx	eax,c_time.wDay
	movzx	ecx,c_time.wMonth
	movzx	edx,c_time.wYear
	sprintf(ebx, "%04d-%02d-%02d", edx, ecx, eax)
	lea	edi,wc
	mov	eax,0F200F20h
	mov	ecx,5
	rep	stosd
	mov	edi,[esi+1*16].S_TOBJ.to_rect
	add	di,WORD PTR [esi].S_DOBJ.dl_rect
	rcxchg( edi, addr wc )
	.if	dledit( ebx, edi, 64, 0 ) == KEY_ENTER || eax == KEY_KPENTER
		parse_date( ebx )
	.endif
	rcxchg( edi, addr wc )
	ret
event_getdate ENDP
;
; Main program
;
main	PROC C
local	cursor:S_CURSOR
	CursorGet( addr cursor )
	CursorOff()

	mov	tupdate,TimerUpdate
	mov	tdidle,ConsoleIdle
	or	console,CON_SLEEP

	mov	ebx,__argv
	mov	eax,[ebx]
	strcpy ( strfn( strcpy( addr cp_command, eax ) ), addr cp_batch )

	call	set_local_time
	mov	c_time.wSecond,0

	mov	edi,1
	.while	edi < __argc
		mov	esi,[ebx+edi*4]
		mov	eax,[esi]
		.if	al == '-' || al == '/'
			shr	eax,8
			.switch al
			  .case '?'
			  .case 'h'
				printf( addr cp_usage )
				jmp	toend
			  .case 'C'
				mov	eax,[ebx]
				strcpy( addr cp_command, eax )
				add	edi,1
				.while	edi < __argc
					strcat( eax, " " )
					strcat( eax, [ebx+edi*4] )
					add	edi,1
				.endw
				CreateConsole( eax, _P_NOWAIT or CREATE_NEW_CONSOLE )
				jmp	toend
			  .case 'D'
				lea	eax,[esi+2]
				parse_date( eax )
				call	set_time
				.endc
			  .case 'T'
				lea	eax,[esi+2]
				parse_time( eax )
				call	set_time
				.endc
			.endsw
		.else
			strcpy(addr cp_command, esi )
		.endif
		add	edi,1
	.endw

	mov	at_background[B_Inverse],70h
	.if	rsopen( IDD_TMain )
		mov	DLG_TMain,eax
		mov	ebx,eax
		movzx	ecx,[eax].S_DOBJ.dl_rect.rc_x
		mov	xpos,ecx
		mov	cl,[eax].S_DOBJ.dl_rect.rc_y
		add	ecx,4+7
		mov	ypos,ecx
		_gotoxy( 0, 0 )
		dlshow( DLG_TMain )

		mov	eax,_scrcol
		mov	edx,_scrrow
		inc	edx
		mov	o_scrcol,eax
		mov	o_scrrow,edx
		movzx	eax,[ebx].S_DOBJ.dl_rect.rc_col
		movzx	edx,[ebx].S_DOBJ.dl_rect.rc_row
		SetConsoleSize( eax, edx )

		GetLocalTime( addr l_time )

		call	msloop
		.while	mainswitch
			call	PrintDate
			.switch tgetevent()
			  .case KEY_F1
				mov	tupdate,dummy
				call	event_help
				mov	tupdate,TimerUpdate
				.endc
			  .case KEY_F2
				call	event_getdate
				.endc
			  .case KEY_F3
			  .case KEY_ENTER
				call	event_gettime
				.endc
			  .case MOUSECMD
				call	mousex
				mov	edi,eax
				call	mousey
				mov	esi,eax
				mov	ebx,DLG_TMain
				.switch rcxyrow( DWORD PTR [ebx].S_DOBJ.dl_rect, edi, esi )
				  .case 8
					.if	edi >= l_time_x && edi <= l_time_x + 10
						call	event_getdate
					.elseif edi >= l_time_x + 11 && edi <= l_time_x + 11 + 8
						call	event_gettime
					.endif
					.endc
				  .case 12..17
					mov	eax,[ebx].S_DOBJ.dl_rect
					and	eax,00FFFFFFh
					add	eax,06000B01h
					sub	eax,00020000h
					.if	rcxyrow( eax, edi, esi )
						dec	edi
						getxyc( edi, esi )
						mov	ebx,eax
						inc	edi
						getxyc( edi, esi )
						mov	bh,al
						inc	edi
						getxyc( edi, esi )
						shl	eax,16
						mov	ax,bx
						push	eax
						mov	eax,esp
						invoke	atol,eax
						pop	ecx
						.if	eax && eax <= days_in_month
							mov	c_time.wDay,ax
							call	set_time
							call	PrintDate
						.endif
					.endif
				  .default
					call	msloop
				.endsw
				.endc
			  .case KEY_ALTX
			  .case KEY_ESC
				mov	mainswitch,0
				.endc
			  .case KEY_HOME
				set_local_time()
				mov	diff_t,0
				.endc
			  .case KEY_RIGHT
				movzx	eax,c_time.wDay
				.if	eax < days_in_month
					add	eax,1
					mov	c_time.wDay,ax
					call	set_time
					.endc
				.endif
				mov	c_time.wDay,1
			  .case KEY_PGUP
				movzx	eax,c_time.wMonth
				.if	eax < 12
					add	eax,1
					mov	c_time.wMonth,ax
					call	set_time
					.endc
				.endif
				mov	c_time.wMonth,1
			  .case KEY_CTRLPGUP
				movzx	eax,c_time.wYear
				.if	eax < MAXYEAR
					add	eax,1
				.else
					mov	eax,STARTYEAR
				.endif
				mov	c_time.wYear,ax
				call	set_time
				.endc
			  .case KEY_LEFT
				.if	c_time.wDay > 1
					sub	c_time.wDay,1
					call	set_time
					.endc
				.endif
			  .case KEY_PGDN
				.if	c_time.wMonth > 1
					sub	c_time.wMonth,1
					call	set_time
					mov	eax,days_in_month
					mov	c_time.wDay,ax
					call	set_time
					.endc
				.elseif c_time.wYear
					sub	c_time.wYear,1
					mov	c_time.wDay,31
					mov	c_time.wMonth,12
					call	set_time
					.endc
				.endif
			  .case KEY_CTRLPGDN
				mov	c_time.wDay,1
				mov	c_time.wMonth,1
				.if	c_time.wYear
					sub	c_time.wYear,1
				.else
					mov	c_time.wYear,MAXYEAR
				.endif
				call	set_time
				.endc
			  .case KEY_UP
				.if	c_time.wDay > 7
					sub	c_time.wDay,7
				.else
					mov	c_time.wDay,1
				.endif
				call	set_time
				.endc
			  .case KEY_DOWN
				movzx	eax,c_time.wDay
				mov	ecx,days_in_month
				add	eax,7
				.if	eax > ecx
					mov	eax,ecx
				.endif
				mov	c_time.wDay,ax
				call	set_time
				.endc
			  .case KEY_CTRLUP
				.if	c_time.wHour < 23
					inc	c_time.wHour
					call	set_time
				.endif
				.endc
			  .case KEY_CTRLDN
				.if	c_time.wHour
					dec	c_time.wHour
					call	set_time
				.endif
				.endc
			  .case KEY_CTRLRIGHT
				.if	c_time.wMinute < 59
					inc	c_time.wMinute
					call	set_time
				.endif
				.endc
			  .case KEY_CTRLLEFT
				.if	c_time.wMinute
					dec	c_time.wMinute
					call	set_time
				.endif
				.endc
			.endsw
		.endw
		dlclose( DLG_TMain )
		SetConsoleSize( o_scrcol, o_scrrow )
	.endif
toend:
	CursorSet( addr cursor )
	xor	eax,eax
	ret
main	ENDP

	END
