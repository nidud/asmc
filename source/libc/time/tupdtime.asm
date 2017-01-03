include time.inc
include consx.inc

	.data
	_sec	dd 61
	iso_s	db "dd.MM.yy",0

.code

TIME_NOMINUTESORSECONDS equ 1	; do not use minutes or seconds
TIME_NOSECONDS		equ 2	; do not use seconds
TIME_NOTIMEMARKER	equ 4	; do not use time marker
TIME_FORCE24HOURFORMAT	equ 8	; always use 24 hour format
;
;  Date Flags for GetDateFormat.
;
DATE_SHORTDATE		equ 1	; use short date picture
DATE_LONGDATE		equ 2	; use long date picture
DATE_USE_ALT_CALENDAR	equ 4	; use alternate calendar (if any)
DATE_YEARMONTH		equ 8	; use year month

tupdtime PROC USES esi edi ebx
  local ts:SYSTEMTIME
  local buf[64]:byte
	mov	eax,console
	mov	ebx,eax
	and	eax,CON_UTIME or CON_UDATE
	jz	toend

	xor	eax,eax
	mov	buf,al
	mov	ecx,SIZE SYSTEMTIME/4
	lea	edi,ts
	rep	stosd
	mov	edi,ebx
	GetLocalTime( addr ts )

	mov	eax,edi
	and	eax,CON_UTIME or CON_LTIME
	cmp	eax,CON_UTIME or CON_LTIME
	movzx	eax,ts.wSecond
	je	@F
	movzx	eax,ts.wMinute
@@:
	cmp	eax,_sec
	je	toend

	mov	_sec,eax
	call	GetUserDefaultLCID
	mov	esi,eax
	mov	ebx,_scrcol
	inc	ebx
	test	edi,CON_UTIME
	jz	@date
	mov	edx,TIME_NOSECONDS
	test	edi,CON_LTIME
	jz	@F
	sub	edx,edx
@@:
	GetTimeFormat( esi, edx, addr ts, 0, addr buf, 32 )
	test	eax,eax
	jz	@date
	sub	ebx,eax
	scputs( ebx, 0, 0, 0, addr buf )
@date:
	test	edi,CON_UDATE
	jz	toend
	lea	edx,iso_s
	test	edi,CON_LDATE
	jz	@F
	sub	edx,edx
@@:
	GetDateFormat( esi, 0, addr ts, edx, addr buf, 32 )
	test	eax,eax
	jz	toend
	sub	ebx,eax
	scputs( ebx, 0, 0, 0, addr buf )
toend:
	ret
tupdtime ENDP

	END
