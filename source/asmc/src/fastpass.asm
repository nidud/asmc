;
;  This code is Public Domain.
;
;  ========================================================================
;
; Description:	implements the "fastpass" handling.
;		"fastpass" is an optimization which increases
;		assembly time speed by storing preprocessed lines
;		in memory during the first pass. In further passes,
;		those lines are "read" instead of the original assembly
;		source files.
;		Speed increase is significant if there's a large include
;		file at the top of an assembly source which contains
;		just equates and type definitions, because there's no need
;		to save such lines during pass one.
;
include ctype.inc
include stdio.inc
include string.inc
include alloc.inc

include asmc.inc

GetLineNumber	 PROTO
get_curr_srcfile PROTO
SetOfssize	 PROTO
;
; current LST file position
;
externdef list_pos:DWORD

	.data?

LineStore	qdesc <>
LineStoreCurr	LPLINE ?	; must be global!
StoreState	dd ?
UseSavedState	dd ?
modstate	mod_state <>	; struct to store assembly status

	.data

NoLineStore	dd 0

	.code

	OPTION PROCALIGN:4
;
; save the current status (happens in pass one only) and
; switch to "save precompiled lines" mode.
; the status is then restored in further passes,
; and the precompiled lines are used for assembly then.
;
SaveState PROC
	xor eax,eax
	mov modstate.head,eax
	mov modstate.tail,eax
	inc eax
	mov StoreState,eax
	mov UseSavedState,eax
	mov modstate.init,eax

	memcpy( addr modstate.modinfo,
		addr ModuleInfo.proc_prologue,
		sizeof( modstate.modinfo ))
	SegmentSaveState()
	AssumeSaveState()
	ContextSaveState()	; save pushcontext/popcontext stack
	ret
SaveState ENDP

StoreLine PROC USES esi edi ebx sline, flags, lst_position

	xor eax,eax
	cmp eax,NoLineStore
	jne toend
	;
	; don't store generated lines!
	;
	.if ModuleInfo.GeneratedCode == eax
		.if StoreState == eax	; line store already started?
			SaveState()
		.endif
		strlen( sline )
		mov ebx,eax
		xor eax,eax
		.if flags == 1 && ModuleInfo.CurrComment != eax
			strlen( ModuleInfo.CurrComment )
		.endif
		mov edi,eax
		lea eax,[eax+ebx+sizeof(line_item)]
		LclAlloc( eax )
		mov ecx,LineStoreCurr
		mov LineStoreCurr,eax
		mov esi,eax
		mov [esi].line_item.prev,ecx
		mov [esi].line_item.next,0
		GetLineNumber()
		mov [esi].line_item.lineno,eax
		.if MacroLevel
			mov [esi].line_item.srcfile,0FFFh
		.else
			get_curr_srcfile()
			mov [esi].line_item.srcfile,eax
		.endif
		mov eax,lst_position
		.if !eax
			mov eax,list_pos
		.endif
		mov [esi].line_item.list_pos,eax
		.if edi
			memcpy( addr [esi].line_item.line, sline, ebx )
			inc edi
			add eax,ebx
			memcpy( eax, ModuleInfo.CurrComment, edi )
		.else
			inc ebx
			memcpy( addr [esi].line_item.line, sline, ebx )
		.endif
		lea ecx,[esi].line_item.line
		;
		; v2.08: don't store % operator at pos 0
		;
		movzx eax,BYTE PTR [ecx]
		.while BYTE PTR _ctype[eax*2+2] & _SPACE
			inc ecx
			mov al,[ecx]
		.endw
		.if eax == '%'
			mov eax,[ecx+1]
			movzx edx,BYTE PTR [ecx+4]
			and eax,00FFFFFFh
			or  eax,00202020h
			.if eax != 'tuo' || __ltype[edx+1] & _LABEL or _DIGIT
				mov BYTE PTR [ecx],' '
			.endif
		.endif
		.if LineStore.head
			mov eax,LineStore.tail
			mov [eax].line_item.next,esi
		.else
			mov LineStore.head,esi
		.endif
		mov LineStore.tail,esi
	.endif
toend:
	ret
StoreLine ENDP

; an error has been detected in pass one. it should be
; reported in pass 2, so ensure that a full source scan is done then
;
SkipSavedState PROC
	mov UseSavedState,0
	ret
SkipSavedState ENDP

; for FASTPASS, just pass 1 is a full pass, the other passes
; don't start from scratch and they just assemble the preprocessed
; source. To be able to restart the assembly process from a certain
; location within the source, it's necessary to save the value of
; assembly time variables.
; However, to reduce the number of variables that are saved, an
; assembly-time variable is only saved when
; - it is changed
; - it was defined when StoreState() is called
;
SaveVariableState PROC USES esi edi sym

	mov esi,sym
	or  [esi].asym.flag,SFL_ISSAVED
	LclAlloc( sizeof( equ_item ) )
	mov edi,eax
	mov [edi].equ_item.next,0
	mov [edi].equ_item.sym,esi
	mov [edi].equ_item.isdefined,0
	.if [esi].asym.flag & SFL_ISDEFINED

		inc [edi].equ_item.isdefined
	.endif

	mov eax,[esi].asym.value
	mov [edi].equ_item.lvalue,eax
	mov eax,[esi].asym.value3264
	mov [edi].equ_item.hvalue,eax
	mov al,[esi].asym.mem_type
	mov [edi].equ_item.mem_type,al

	.if modstate.tail

		mov eax,modstate.tail
		mov [eax].equ_item.next,edi
		mov modstate.tail,edi
	.else
		mov modstate.head,edi
		mov modstate.tail,edi
	.endif
	ret
SaveVariableState ENDP

RestoreState PROC

	.if modstate.init
		;
		; restore values of assembly time variables
		;
		mov edx,modstate.head
		.while	edx
			mov ecx,[edx].equ_item.sym
			mov eax,[edx].equ_item.lvalue
			mov [ecx].asym.value,eax
			mov eax,[edx].equ_item.hvalue
			mov [ecx].asym.value3264,eax
			mov al,[edx].equ_item.mem_type
			and [ecx].asym.flag,not SFL_ISDEFINED
			.if [edx].equ_item.isdefined

				and [ecx].asym.flag,not SFL_ISDEFINED
			.endif
			mov edx,[edx].equ_item.next
		.endw
		;
		; fields in module_vars are not to be restored.
		; v2.10: the module_vars fields are not saved either.
		;
		; v2.23: save L"Unicode" flag
		;
		mov al,ModuleInfo.aflag
		push eax
		memcpy( addr ModuleInfo.proc_prologue,
			addr modstate.modinfo,
			sizeof( modstate.modinfo ) )
		pop eax
		and eax,_AF_LSTRING
		or  ModuleInfo.aflag,al
		SetOfssize()
		SymSetCmpFunc()
	.endif

	mov eax,LineStore.head
	ret

RestoreState ENDP

FastpassInit PROC

	xor eax,eax
	mov StoreState,eax
	mov modstate.init,eax
	mov LineStore.head,eax
	mov LineStore.tail,eax
	mov UseSavedState,eax
	ret

FastpassInit ENDP

	END
