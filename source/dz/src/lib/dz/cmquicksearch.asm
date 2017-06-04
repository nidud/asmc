; CMQUICKSEARCH.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include string.inc

; (PG)UP,DOWN:	Move
; ESC,TAB,ALTX: Quit
; ENTER:	Quit
; BKSP:		Search from start
; insert char:	Search from current pos.

;SKIPSUBDIR = 1 ; Exclude directories in search

	.data

cp_quicksearch	db '&Quick Search: ',1Ah,'   ',0

	.code

psearch PROC PRIVATE USES esi edi ebx cname, l, direction

  local fcb, cindex, lindex

	mov ebx,cpanel		; current index
	mov esi,[ebx].S_PANEL.pn_fcb_index
	add esi,[ebx].S_PANEL.pn_cel_index
	mov lindex,esi
	mov cindex,esi
	mov edi,[ebx].S_PANEL.pn_fcb_count
	mov ebx,[ebx].S_PANEL.pn_wsub
	mov eax,[ebx].S_WSUB.ws_fcb
	mov fcb,eax

	.if !direction		; if (direction == 0) search from start

		mov lindex,edi	; (case BKSP)
		mov esi,edi
	.endif

	.while	1

		.if esi >= edi

			xor esi,esi
			mov edi,lindex
			mov lindex,esi
			.continue .if edi

			xor eax,eax
			.break
		.endif

		mov ebx,fcb
		mov ebx,[ebx+esi*4]
	  ifdef SKIPSUBDIR
		.if !( BYTE PTR [ebx] & _A_SUBDIR )
	  endif
		.if !_strnicmp(cname, addr [ebx].S_FBLK.fb_name, l)

			mov ebx,cpanel
			dlclose([ebx].S_PANEL.pn_xl)
			panel_setid(ebx, esi)
			panel_putitem(ebx, 0)
			pcell_show(ebx)
			mov eax,1
			.break
		.endif
	  ifdef SKIPSUBDIR
		.endif
	  endif
		inc esi
	.endw

	mov edx,cindex
	ret

psearch ENDP

cmquicksearch PROC USES esi edi ebx

  local cursor:S_CURSOR,
	stline[256]:WORD,
	fname[256]:BYTE

	.if cpanel_state()

		CursorGet(addr cursor)
		CursorOn()
		wcpushst(addr stline, addr cp_quicksearch)

		lea ebx,fname
		mov esi,15		; SI = x
		mov edi,_scrrow		; DI = y
		_gotoxy(esi, edi)	; cursor to (x,y)

		.repeat
			tupdate()
			.switch getkey() ; get key
			  .case 0
			  .case KEY_ESC
			  .case KEY_TAB
			  .case KEY_ALTX
				.endc
			  .case KEY_ENTER
			  .case KEY_KPENTER
				lea eax,[esi-15]
				psearch( ebx, eax, 1 )
			  ifdef SKIPSUBDIR
				xor eax,eax
			  else
				.if eax

					mov ecx,cpanel
					mov eax,[ecx].S_PANEL.pn_fcb_index
					add eax,[ecx].S_PANEL.pn_cel_index
					.if eax == edx

						inc eax
					.else
						xor eax,eax
					.endif
				.endif
			  endif
				.endc
			  .case KEY_LEFT
			  .case KEY_RIGHT
			  .case KEY_UP
			  .case KEY_PGUP
			  .case KEY_DOWN
			  .case KEY_PGDN
			  .case KEY_HOME
			  .case KEY_END
				panel_event(cpanel, eax)
				xor eax,eax
				.endc
			  .case KEY_BKSP
				;
				; delete char and search from start
				;
				.if SDWORD PTR esi > 15

					dec esi
					mov edx,edi
					scputw(esi, edi, 2, ' ')
					_gotoxy(esi, edi)
					xor eax,eax
					mov ecx,15
					jmp event_back
				.endif
				xor eax,eax
				.endc

			  .default
				movzx eax,al
				mov [ebx+esi-15],al
				mov ecx,14

			   event_back:
				push eax
				mov edx,esi
				sub edx,ecx
				psearch(ebx, edx, eax)
				test eax,eax
				pop eax

				.if !ZERO?

					.if eax

						scputw(esi, edi, 1, eax)
						.if SDWORD PTR esi < 78

							inc esi
							_gotoxy(esi, edi)
						.endif
					.endif
				.endif
				xor eax,eax
			.endsw
		.until	eax
		wcpopst(addr stline)
		CursorSet(addr cursor)
	.endif
	xor eax,eax
	ret
cmquicksearch ENDP

	END
