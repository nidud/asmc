; CMSELECT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc

externdef cp_select:byte
externdef cp_deselect:byte
externdef cp_selectmask:byte

    .code

cmselect proc uses esi edi

    .if !cp_selectmask

	strcpy(&cp_selectmask, &cp_stdmask)
    .endif

    .if tgetline(&cp_select, &cp_selectmask, 12, 32+8000h)

	.if cp_selectmask

	    .if panel_state(cpanel)

		mov edi,[eax].S_PANEL.pn_wsub
		mov esi,[eax].S_PANEL.pn_fcb_count
		mov edi,[edi].S_WSUB.ws_fcb

		.while	esi

		    mov eax,[edi]

		    .if cmpwarg(&[eax].S_FBLK.fb_name, &cp_selectmask)

			fblk_select([edi])
		    .endif

		    add edi,4
		    dec esi
		.endw

		panel_putitem(cpanel, 0)
		mov eax,1
	    .endif
	.endif
    .endif
    ret
cmselect endp

cmdeselect proc uses esi edi

    .if !cp_selectmask

	strcpy(&cp_selectmask, &cp_stdmask)
    .endif

    .if tgetline(&cp_deselect, &cp_selectmask, 12, 32+8000h)

	.if cp_selectmask

	    .if panel_state(cpanel)

		mov edi,[eax].S_PANEL.pn_wsub
		mov esi,[eax].S_PANEL.pn_fcb_count
		mov edi,[edi].S_WSUB.ws_fcb

		.while	esi

		    mov eax,[edi]
		    add eax,S_FBLK.fb_name

		    .if cmpwarg(eax, &cp_selectmask)

			mov eax,[edi]
			and [eax].S_FBLK.fb_flag,not _FB_SELECTED
		    .endif
		    add edi,4
		    dec esi
		.endw

		panel_putitem(cpanel, 0)
		mov eax,1
	    .endif
	.endif
    .endif
    ret
cmdeselect endp

cminvert proc uses esi edi

    .if panel_state(cpanel)

	mov edi,[eax].S_PANEL.pn_wsub
	mov esi,[eax].S_PANEL.pn_fcb_count
	mov edi,[edi].S_WSUB.ws_fcb

	.while	esi

	    fblk_invert([edi])
	    add edi,4
	    dec esi
	.endw

	panel_putitem(cpanel, 0)
	mov eax,1
    .endif
    ret
cminvert endp

    END
