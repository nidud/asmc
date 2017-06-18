include stdio.inc
include time.inc
include string.inc

include asmc.inc
include token.inc

public	SymCmpFunc
public	resw_table
extern	define_LINUX:DWORD
extern	define_WIN64:DWORD

DeleteProc		PROTO :DWORD
ReleaseMacroData	PROTO :DWORD
AddPublicData		PROTO FASTCALL :DWORD
UpdateLineNumber	PROTO :DWORD, :DWORD
UpdateWordSize		PROTO :DWORD, :DWORD
UpdateCurPC		PROTO :DWORD, :DWORD

HASH_MAGNITUDE		equ 15	; is 15 since v1.94, previously 12
HASH_MASK		equ 0x7FFF
;
; size of global hash table for symbol table searches. This affects
; assembly speed.
;
GHASH_TABLE_SIZE	equ 8009
;
; size of local hash table
;
LHASH_TABLE_SIZE	equ 127
;
; use memcpy()/memcmpi() directly?
; this may speed-up things, but not with OW.
; MSVC is a bit faster then.
;
USEFIXSYMCMP	equ 0	; 1=don't use a function pointer for string compare
USESTRFTIME	equ 0	; 1=use strftime()

HASH_TABITEMS	equ 811

tmitem		STRUC
_name		dd ?
value		dd ?
store		dd ?
tmitem		ENDS

eqitem		STRUC
_name		dd ?
value		dd ?
sfunc_ptr	dd ?	; ( struct asym *, void * );
store		dd ?	; asym **
eqitem		ENDS

ReservedWord	STRUC
next		dw ?	; index next entry (used for hash table)
len		db ?	; length of reserved word, i.e. 'AX' = 2
flags		db ?	; see enum reservedword_flags
_name		dd ?	; reserved word (char[])
ReservedWord	ENDS

extrn	FileCur		: DWORD ; @FileCur symbol
extrn	LineCur		: DWORD ; @Line symbol
extrn	symCurSeg	: DWORD ; @CurSeg symbol
extrn	CurrProc	: DWORD ;
extrn	ResWordTable	: ReservedWord

	.data?

SymCmpFunc	dd ?
gsym		dd ?		; asym ** pointer into global hash table
lsym		dd ?		; asym ** pointer into local hash table
SymCount	dd ?		; Number of symbols in global table
szDate		db 16 dup(?)	; value of @Date symbol
szTime		db 16 dup(?)	; value of @Time symbol
lsym_table	dd LHASH_TABLE_SIZE+1 dup(?)
gsym_table	dd GHASH_TABLE_SIZE dup(?)
		ALIGN 16
resw_table	LABEL WORD
		dd HASH_TABITEMS / 2 + 1 dup(?)

	.data

symPC		dd 0		; the $ symbol -- asym *

@@Version	db "@Version",0
MLVersion	db "800",0
@@Date		db "@Date",0
@@Time		db "@Time",0
@@FileName	db "@FileName",0
@@FileCur	db "@FileCur",0
@@CurSeg	db "@CurSeg"
@@Null		db 0

	ALIGN	4

;
; table of predefined text macros
;
tmtab	LABEL tmitem
	;
	; @Version contains the Masm compatible version
	; v2.06: value of @Version changed to 800
	;
	tmitem	<@@Version,  MLVersion, 0>
	tmitem	<@@Date,     szDate,	0>
	tmitem	<@@Time,     szTime,	0>
	tmitem	<@@FileName, ModuleInfo._name, 0>
	tmitem	<@@FileCur,  0, FileCur>
	;
	; v2.09: @CurSeg value is never set if no segment is ever opened.
	; this may have caused an access error if a listing was written.
	;
	tmitem	<@@CurSeg,   @@Null, symCurSeg>
	dd	0

;
; table of predefined numeric equates
;
CP__ASMC__	db "__ASMC__",0
CP__JWASM__	db "__JWASM__",0
CP_$		db "$",0
@@Line		db "@Line",0
@@WordSize	db "@WordSize",0

	ALIGN	4

eqtab	LABEL eqitem
	eqitem	< CP__ASMC__,  ASMC_VERSION, 0, 0 >
	eqitem	< CP__JWASM__, 212, 0, 0 >
	eqitem	< CP_$,	       0, UpdateCurPC, symPC >
	eqitem	< @@Line,      0, UpdateLineNumber, LineCur >
	eqitem	< @@WordSize,  0, UpdateWordSize, 0 > ; must be last (see SymInit())
	dd	0

	.code

	OPTION PROCALIGN:4

SymSetCmpFunc proc
	mov SymCmpFunc,_memicmp
	.if ModuleInfo.case_sensitive
		mov SymCmpFunc,memcmp
	.endif
	ret
SymSetCmpFunc ENDP

; reset local hash table

SymClearLocal PROC
	xor	eax,eax
	lea	edx,lsym_table
	mov	ecx,sizeof( lsym_table ) / 4
	xchg	edx,edi
	rep	stosd
	mov	edi,edx
	ret
SymClearLocal ENDP

; store local hash table in proc's list of local symbols

SymGetLocal PROC psym

	mov	ecx,psym
	mov	edx,[ecx].dsym.procinfo
	lea	edx,[edx].proc_info.labellist
	xor	ecx,ecx
	.while	ecx < LHASH_TABLE_SIZE

		mov	eax,lsym_table[ecx*4]
		add	ecx,1
		.continue .if !eax

		mov	[edx],eax
		lea	edx,[eax].dsym.nextll
	.endw
	xor	eax,eax
	mov	[edx],eax
	ret

SymGetLocal ENDP

; restore local hash table.
; - proc: procedure which will become active.
; fixme: It might be necessary to reset the "defined" flag
; for local labels (not for params and locals!). Low priority!

SymSetLocal PROC USES edi psym
	xor	eax,eax
	lea	edi,lsym_table
	mov	ecx,sizeof( lsym_table ) / 4
	rep	stosd
	mov	ecx,psym
	mov	edi,[ecx].dsym.procinfo
	mov	edi,[edi].proc_info.labellist
	.while	edi
		mov	ecx,[edi].asym._name
		xor	eax,eax
		movzx	edx,BYTE PTR [ecx]

		.while	edx
			add	ecx,1
			or	edx,20h
			shl	eax,5
			add	eax,edx
			mov	edx,eax
			and	edx,not HASH_MASK
			xor	eax,edx
			shr	edx,HASH_MAGNITUDE
			xor	eax,edx
			movzx	edx,BYTE PTR [ecx]
		.endw

		.while eax >= LHASH_TABLE_SIZE

			sub eax,LHASH_TABLE_SIZE
		.endw
		mov	lsym_table[eax*4],edi
		mov	edi,[edi].dsym.nextll
	.endw
	ret
SymSetLocal ENDP

SymAlloc PROC USES esi edi sname
	mov	esi,sname
	strlen( esi )
	push	eax
	add	eax,sizeof( dsym ) + 1
	LclAlloc( eax )
	pop	edx
	mov	[eax].asym.name_size,dx
	mov	[eax].asym.mem_type,MT_EMPTY
	lea	edi,[eax + sizeof( dsym )]
	mov	[eax].asym._name,edi
	cmp	ModuleInfo.cref,0
	jne	crefl
done:
	test	edx,edx
	jz	toend
	mov	ecx,edx
	rep	movsb
toend:
	ret
crefl:
	or	[eax].asym.flag,SFL_LIST
	jmp	done
SymAlloc ENDP

	ALIGN	16

	GETHASH MACRO value
		;
		; Divide total by array count not using DIV
		;
		.if eax >= value * 8
			sub eax,value * 8
		.endif
		.while	eax >= value
			sub eax,value
		.endw
		ENDM

	CMPSYM	MACRO success
		LOCAL l1, l2, l3, l4
		cmp	cx,[eax].asym.name_size
		jne	l4
		mov	edi,[eax].asym._name
		ALIGN	4
		l1:
		cmp	ecx,4
		jb	l2
		sub	ecx,4
		mov	ebx,[esi+ecx]
		cmp	ebx,[edi+ecx]
		je	l1
		jmp	l3
		ALIGN	4
		l2:
		test	ecx,ecx
		jz	success
		sub	ecx,1
		mov	bl,[esi+ecx]
		cmp	bl,[edi+ecx]
		je	l2
		l3:
		movzx	ecx,[eax].asym.name_size
		l4:
		ENDM

	CMPISYM MACRO success
		LOCAL l1, l2, l3, l4
		cmp	cx,[eax].asym.name_size
		jne	l4
		mov	edi,[eax].asym._name
		ALIGN	4
		l1:
		cmp	ecx,4
		jb	l2
		sub	ecx,4
		mov	ebx,[esi+ecx]
		cmp	ebx,[edi+ecx]
		je	l1
		add	ecx,4
		ALIGN	4
		l2:
		test	ecx,ecx
		jz	success
		sub	ecx,1
		mov	bl,[esi+ecx]
		cmp	bl,[edi+ecx]
		je	l2
		mov	bh,[edi+ecx]
		or	bx,2020h
		cmp	bl,bh
		je	l2
		l3:
		movzx	ecx,[eax].asym.name_size
		l4:
		ENDM

SymFind PROC FASTCALL USES esi edi ebx ebp sname
;
; find a symbol in the local/global symbol table,
; return ptr to next free entry in global table if not found.
; Note: lsym must be global, thus if the symbol isn't
; found and is to be added to the local table, there's no
; second scan necessary.
;
	mov	esi,ecx
	xor	eax,eax
	movzx	edx,BYTE PTR [ecx]
	test	edx,edx
	jz	toend

	ALIGN	4
	.repeat
		add ecx,1
		or  edx,20h
		shl eax,5
		add eax,edx
		mov edx,eax
		and edx,not HASH_MASK
		xor eax,edx
		shr edx,HASH_MAGNITUDE
		xor eax,edx
		movzx edx,BYTE PTR [ecx]
	.until !edx

	sub	ecx,esi

	mov	ebx,eax
	GETHASH GHASH_TABLE_SIZE
	lea	edx,gsym_table[eax*4]

	cmp	ModuleInfo.case_sensitive,0
	jne	case_global?
	cmp	CurrProc,0
	jne	nocase_local

nocase_global:
	mov	eax,[edx]
	.while	eax
		CMPISYM found_gsym
		lea edx,[eax].asym.nextitem
		mov eax,[edx]
	.endw
	mov	gsym,edx
	xor	eax,eax
	jmp	toend

case_global?:
	cmp	CurrProc,0
	jne	case_local

case_global:
	mov	eax,[edx]
	.while	eax
		CMPSYM	found_gsym
		lea edx,[eax].asym.nextitem
		mov eax,[edx]
	.endw
	mov	gsym,edx
	xor	eax,eax
	jmp	toend

case_local:
	mov	eax,ebx
	mov	ebp,edx
	GETHASH LHASH_TABLE_SIZE
	lea	edx,lsym_table[eax*4]
	mov	eax,[edx]
	.while	eax
		CMPSYM found_lsym
		lea edx,[eax].asym.nextitem
		mov eax,[edx]
	.endw
	mov	lsym,edx
	mov	edx,ebp
	jmp	case_global

nocase_local:
	mov	eax,ebx
	mov	ebp,edx
	GETHASH LHASH_TABLE_SIZE
	lea	edx,lsym_table[eax*4]
	mov	eax,[edx]

	.while	eax
		CMPISYM found_lsym
		lea edx,[eax].asym.nextitem
		mov eax,[edx]
	.endw

	mov	lsym,edx
	mov	edx,ebp
	jmp	nocase_global

found_lsym:
	mov	lsym,edx
	jmp	toend
found_gsym:
	mov	gsym,edx
toend:
	ret

SymFind ENDP

;
; SymLookup() creates a global label if it isn't defined yet
;
SymLookup PROC sname

	.if !SymFind( sname )

		SymAlloc( sname )
		mov ecx,gsym
		mov [ecx],eax
		inc SymCount
	.endif

	ret
SymLookup ENDP

;
; SymLookupLocal() creates a local label if it isn't defined yet.
; called by LabelCreate() [see labels.c]
;
SymLookupLocal PROC sname

	.if !SymFind( sname )
		SymAlloc( sname )
		or [eax].asym.flag,SFL_SCOPED
		;
		; add the label to the local hash table
		;
		mov ecx,lsym
		mov [ecx],eax

	.elseif [eax].asym.state == SYM_UNDEFINED && !([eax].asym.flag & SFL_SCOPED)
		;
		; if the label was defined due to a FORWARD reference,
		; its scope is to be changed from global to local.
		;
		; remove the label from the global hash table
		;
		mov edx,[eax].asym.nextitem
		mov ecx,gsym
		mov [ecx],edx
		dec SymCount
		or  [eax].asym.flag,SFL_SCOPED
		mov [eax].asym.nextitem,0
		mov ecx,lsym
		mov [ecx],eax
	.endif

	ret
SymLookupLocal ENDP

;
; free a symbol.
; the symbol is no unlinked from hash tables chains,
; hence it is assumed that this is either not needed
; or done by the caller.
;

SymFree PROC sym

	mov ecx,sym
	movzx eax,[ecx].asym.state

	.switch eax

	  .case SYM_INTERNAL
		.if [ecx].asym.flag & SFL_ISPROC
			DeleteProc( ecx )
		.endif
		.endc

	  .case SYM_EXTERNAL
		.if [ecx].asym.flag & SFL_ISPROC
			DeleteProc( ecx )
		.endif
		mov ecx,sym
		mov [ecx].asym.first_size,0
		;
		; The altname field may contain a symbol (if weak == FALSE).
		; However, this is an independant item and must not be released here
		;
		.endc

	  .case SYM_MACRO
		ReleaseMacroData( ecx )

	.endsw

	ret
SymFree ENDP

;
; add a symbol to local table and set the symbol's name.
; the previous name was "", the symbol wasn't in a symbol table.
; Called by:
; - ParseParams() in proc.c for procedure parameters.
;
SymAddLocal PROC USES esi edi sym, sname
	mov	esi,sname
	SymFind(esi)

	test	eax,eax
	jnz	exist
undef:
	strlen( esi )
	mov	edx,sym
	mov	[edx].asym.name_size,ax
	add	eax,1
	mov	edi,eax
	LclAlloc( eax )
	mov	edx,sym
	mov	[edx].asym._name,eax
	mov	ecx,edi
	mov	edi,eax
	rep	movsb
	mov	ecx,lsym
	mov	[ecx],edx
	mov	[edx].asym.nextitem,0
	mov	eax,edx
toend:
	ret
exist:
	cmp	[eax].asym.state,SYM_UNDEFINED
	je	undef
error:
	;
	; shouldn't happen
	;
	asmerr( 2005, esi )
	xor	eax,eax
	jmp	toend
SymAddLocal ENDP

;
; add a symbol to the global symbol table.
; Called by:
; - RecordDirective() in types.c to add bitfield fields (which have global scope).
;
SymAddGlobal PROC sym
	mov	eax,sym
	SymFind([eax].asym._name)
	test	eax,eax
	jnz	error
	mov	eax,sym
	inc	SymCount
	mov	ecx,gsym
	mov	[ecx],eax
	mov	[eax].asym.nextitem,0
toend:
	ret
error:
	mov	eax,sym
	asmerr( 2005, [eax].asym._name )
	xor	eax,eax
	jmp	toend
SymAddGlobal ENDP

;
; Create symbol and optionally insert it into the symbol table
;
SymCreate PROC sname
	SymFind( sname )
	test	eax,eax
	jnz	error
	SymAlloc( sname )
	inc	SymCount
	mov	ecx,gsym
	mov	[ecx],eax
toend:
	ret
error:
	asmerr( 2005, sname )
	xor	eax,eax
	jmp	toend
SymCreate ENDP

;
; Create symbol and insert it into the local symbol table.
; This function is called by LocalDir() and ParseParams()
; in proc.c ( for LOCAL directive and PROC parameters ).
;
SymLCreate PROC sname
	SymFind(sname)
	test	eax,eax
	jnz	exist
undef:
	SymAlloc(sname)
	mov	ecx,lsym
	mov	[ecx],eax
toend:
	ret
exist:
	cmp	[eax].asym.state,SYM_UNDEFINED
	je	undef
error:
	;
	; shouldn't happen
	;
	asmerr( 2005, sname )
	xor	eax,eax
	jmp	toend
SymLCreate ENDP

SymGetCount PROC
	mov	eax,SymCount
	ret
SymGetCount ENDP

SymMakeAllSymbolsPublic PROC USES esi edi

	xor esi,esi

	.repeat
		mov edi,gsym_table[esi*4]
		.while edi

			.if [edi].asym.state == SYM_INTERNAL

				mov ecx,[edi].asym._name
				;
				; no EQU or '=' constants
				; no predefined symbols ($)
				; v2.09: symbol already added to public queue?
				; v2.10: no @@ code labels
				;
				movzx eax,[edi].asym.flag
				and eax,SFL_ISEQUATE or SFL_PREDEFINED or SFL_INCLUDED or SFL_ISPUBLIC

				.if ZERO? && BYTE PTR [ecx+1] != '&'
					or [edi].asym.flag,SFL_ISPUBLIC
					AddPublicData( edi )
				.endif

			.endif
			mov	edi,[edi].asym.nextitem
		.endw
		add esi,1
	.until	esi == GHASH_TABLE_SIZE
	ret
SymMakeAllSymbolsPublic ENDP

; initialize global symbol table

SymInit PROC USES esi edi ebx

	local time_of_day

	xor	eax,eax
	mov	SymCount,eax
	;
	; v2.11: ensure CurrProc is NULL - might be a problem if multiple files are assembled
	;
	mov	CurrProc,eax
	lea	edi,gsym_table
	mov	ecx,sizeof(gsym_table)
	rep	stosb

	time( &time_of_day )
	localtime( &time_of_day )
	mov	esi,eax

if USESTRFTIME
	strftime( &szDate, 9, "%D", esi )	; POSIX date (mm/dd/yy)
	strftime( &szTime, 9, "%T", esi )	; POSIX time (HH:MM:SS)
else
	mov	eax,[esi].tm.tm_year
	sub	eax,100
	mov	ecx,[esi].tm.tm_mon
	add	ecx,1
;	sprintf(&szDate, "%02u/%02u/%02u", ecx, [esi].tm.tm_mday, eax)
	add	eax,2000
	sprintf(&szDate, "%u-%02u-%02u", eax, ecx, [esi].tm.tm_mday )
	sprintf(&szTime, "%02u:%02u:%02u", [esi].tm.tm_hour, [esi].tm.tm_min, [esi].tm.tm_sec)
endif
	lea	esi,tmtab
	.while [esi].tmitem._name

		SymCreate( [esi].tmitem._name )
		mov [eax].asym.state,SYM_TMACRO
		or  [eax].asym.flag,SFL_ISDEFINED or SFL_PREDEFINED
		mov ecx,[esi].tmitem.value
		mov [eax].asym.string_ptr,ecx
		mov ecx,[esi].tmitem.store
		add esi,sizeof( tmitem )
		.continue .if !ecx
		mov [ecx],eax
	.endw

	lea	esi,eqtab
	.while [esi].eqitem._name

		SymCreate( [esi].eqitem._name )
		mov [eax].asym.state,SYM_INTERNAL
		or  [eax].asym.flag,SFL_ISDEFINED or SFL_PREDEFINED
		mov ecx,[esi].eqitem.value
		mov [eax].asym._offset,ecx
		mov ecx,[esi].eqitem.sfunc_ptr
		mov [eax].asym.sfunc_ptr,ecx
		mov ecx,[esi].eqitem.store
		add esi,sizeof( eqitem )
		.continue .if !ecx
		mov [ecx],eax
	.endw
	;
	; @WordSize should not be listed
	;
	and [eax].asym.flag,not SFL_LIST

	.if define_LINUX

		SymCreate( "_LINUX" )
		mov [eax].asym.state,SYM_TMACRO
		or  [eax].asym.flag,SFL_ISDEFINED or SFL_PREDEFINED
		mov ecx,define_LINUX
		mov [eax].asym._offset,ecx
		mov [eax].asym.sfunc_ptr,0
	.endif

	.if define_WIN64

		SymCreate( "_WIN64" )
		mov [eax].asym.state,SYM_TMACRO
		or  [eax].asym.flag,SFL_ISDEFINED or SFL_PREDEFINED
		mov ecx,define_WIN64
		mov [eax].asym._offset,ecx
		mov [eax].asym.sfunc_ptr,0
	.endif

	;
	; $ is an address (usually). Also, don't add it to the list
	;
	mov eax,symPC
	and [eax].asym.flag,not SFL_LIST
	or  [eax].asym.flag,SFL_VARIABLE
	mov eax,LineCur
	and [eax].asym.flag,not SFL_LIST
	ret

SymInit ENDP

SymPassInit PROC pass

	.if pass != PASS_1

		; No need to reset the "defined" flag if FASTPASS is on.
		; Because then the source lines will come from the line store,
		; where inactive conditional lines are NOT contained.
		;

		.if !UseSavedState
			;
			; mark as "undefined":
			; - SYM_INTERNAL - internals
			; - SYM_MACRO - macros
			; - SYM_TMACRO - text macros
			;
			xor ecx,ecx
			.repeat

				mov eax,gsym_table[ecx*4]
				.while eax
					.if !( [eax].asym.flag & SFL_PREDEFINED )
						and [eax].asym.flag,not SFL_ISDEFINED
					.endif
					mov eax,[eax].asym.nextitem
				.endw

				add ecx,1
			.until	ecx == GHASH_TABLE_SIZE

		.endif
	.endif
	ret
SymPassInit ENDP

; get all symbols in global hash table

SymGetAll PROC syms

	xor ecx,ecx
	mov edx,syms
	;
	; copy symbols to table
	;
	.repeat
		mov eax,gsym_table[ecx*4]
		.while eax
			mov [edx],eax
			add edx,4
			mov eax,[eax].asym.nextitem
		.endw
		add ecx,1
	.until	ecx == GHASH_TABLE_SIZE

	ret
SymGetAll ENDP

; enum symbols in global hash table.
; used for codeview symbolic debug output.

SymEnum PROC sym, pi
	mov	edx,pi
	mov	eax,sym
	test	eax,eax
	jz	@F
	mov	eax,[eax].asym.nextitem
	mov	ecx,[edx]
	jmp	lupe
@@:
	xor	ecx,ecx
	mov	[edx],ecx
	mov	eax,gsym_table
lupe:
	test	eax,eax
	jnz	toend
	cmp	ecx,GHASH_TABLE_SIZE - 1
	jnb	toend
	add	ecx,1
	mov	[edx],ecx
	mov	eax,gsym_table[ecx*4]
	jmp	lupe
toend:
	ret
SymEnum ENDP

;
; add a new node to a queue */
;
	ALIGN	4

AddPublicData PROC FASTCALL sym

	mov	edx,sym
	lea	ecx,ModuleInfo.PubQueue

AddPublicData ENDP

	ALIGN	4

QAddItem PROC FASTCALL q, d

	push	ecx
	push	edx
	LclAlloc(sizeof(qnode))
	pop	edx
	pop	ecx
	mov	[eax].qnode.elmt,edx
	mov	edx,eax

QAddItem ENDP

QEnqueue PROC FASTCALL q, item

	xor	eax,eax
	cmp	[ecx].qdesc.head,eax
	jne	@F
	mov	[ecx].qdesc.head,edx
	mov	[ecx].qdesc.tail,edx
	mov	[edx],eax
	ret

	ALIGN	4
@@:
	mov	eax,[ecx].qdesc.tail
	mov	[ecx].qdesc.tail,edx
	mov	[eax],edx
	xor	eax,eax
	mov	[edx],eax
	ret

QEnqueue ENDP

	ALIGN	4

get_hash PROC FASTCALL s, z
	push	ebx
	xor	eax,eax
	and	edx,000000FFh
	jz	toend
lupe:
	movzx	ebx,BYTE PTR [ecx]
	inc	ecx
	or	ebx,20h
	shl	eax,3
	add	eax,ebx
	mov	ebx,eax
	and	ebx,not 00001FFFh
	xor	eax,ebx
	shr	ebx,13
	xor	eax,ebx
	dec	edx
	jnz	lupe
toend:
	mov	ecx,HASH_TABITEMS
	xor	edx,edx
	div	ecx
	mov	eax,edx
	pop	ebx
	ret
get_hash ENDP

	ALIGN	16

FindResWord PROC FASTCALL w_name, w_size

	movzx	eax,BYTE PTR [ecx]
	or	eax,20h

	cmp	w_size,7
	ja	case_8
	jmp	table[edx*4]
table:
	dd case_0
	dd case_1
	dd case_2
	dd case_3
	dd case_4
	dd case_5
	dd case_5
	dd case_5

case_0:
	xor eax,eax
	ret
case_1:
	movzx	eax,resw_table[eax*2]
	.while	eax

		.if ResWordTable[eax*8].len == 1

			mov edx,ResWordTable[eax*8]._name
			mov dh,[edx]
			mov dl,[ecx]
			or  edx,2020h
			.break .if dl == dh
		.endif
		movzx eax,ResWordTable[eax*8].next
	.endw
	ret
case_2:
	shl	eax,3
	movzx	edx,BYTE PTR [ecx+1]
	or	edx,20h
	add	eax,edx
	cmp	eax,HASH_TABITEMS
	sbb	edx,edx
	not	edx
	and	edx,HASH_TABITEMS
	sub	eax,edx
	movzx	eax,resw_table[eax*2]
	movzx	ecx,WORD PTR [ecx]
	or	ecx,2020h

	.while	eax
		.if ResWordTable[eax*8].len == 2
			mov edx,ResWordTable[eax*8]._name
			movzx edx,WORD PTR [edx]
			or edx,2020h
			.break .if dx == cx
		.endif
		movzx eax,ResWordTable[eax*8].next
	.endw
	ret
case_3:
	shl	eax,3
	movzx	edx,BYTE PTR [ecx+1]
	or	edx,20h
	add	eax,edx
	shl	eax,3
	movzx	edx,BYTE PTR [ecx+2]
	or	edx,20h
	add	eax,edx
	mov	edx,eax
	and	edx,not 00001FFFh
	xor	eax,edx
	shr	edx,13
	xor	eax,edx
	GETHASH HASH_TABITEMS
	movzx	eax,resw_table[eax*2]
	mov	ecx,[ecx]
	or	ecx,00202020h
	and	ecx,00FFFFFFh

	.while	eax

		.if ResWordTable[eax*8].len == 3
			mov edx,ResWordTable[eax*8]._name
			mov edx,[edx]
			or  edx,00202020h
			and edx,00FFFFFFh
			.break	.if edx == ecx
		.endif
		movzx eax,ResWordTable[eax*8].next
	.endw
	ret
case_4:
	movzx	edx,BYTE PTR [ecx+1]
	or	dl,20h
	shl	eax,3
	add	eax,edx
	mov	dl,[ecx+2]
	or	dl,20h
	shl	eax,3
	add	eax,edx

	mov	edx,eax
	and	edx,not 1FFFh
	xor	eax,edx
	shr	edx,13
	xor	eax,edx

	movzx	edx,BYTE PTR [ecx+3]
	or	dl,20h
	shl	eax,3
	add	eax,edx

	mov	edx,eax
	and	edx,not 1FFFh
	xor	eax,edx
	shr	edx,13
	xor	eax,edx

	GETHASH HASH_TABITEMS
	movzx	eax,resw_table[eax*2]
	mov	ecx,[ecx]
	or	ecx,20202020h

	.while	eax

		.if ResWordTable[eax*8].len == 4

			mov edx,ResWordTable[eax*8]._name
			.break .if ecx == [edx]
		.endif
		movzx eax,ResWordTable[eax*8].next
	.endw
	ret
case_5:
	push	edi
	push	ebx
	mov	ebx,edx
	mov	edi,ecx

	mov	ecx,1
@@:
	movzx	edx,BYTE PTR [ecx+edi]
	or	edx,20h
	shl	eax,3
	add	eax,edx
	mov	edx,eax
	and	edx,not 00001FFFh
	xor	eax,edx
	shr	edx,13
	xor	eax,edx
	add	ecx,1
	cmp	ecx,ebx
	jl	@B

	.if eax >= HASH_TABITEMS * 8

		sub eax,HASH_TABITEMS * 8
	.endif

	cmp	eax,HASH_TABITEMS
	sbb	ecx,ecx
	not	ecx
	and	ecx,HASH_TABITEMS
@@:
	sub	eax,ecx
	cmp	eax,HASH_TABITEMS
	jnb	@B
	movzx	eax,resw_table[eax*2]

	.while	eax

		.if ResWordTable[eax*8].len == bl

			mov edx,ResWordTable[eax*8]._name
			mov edx,[edx]
			or  edx,20202020h
			mov ecx,[edi]
			or  ecx,20202020h
			.if edx == ecx
				mov edx,ResWordTable[eax*8]._name
				mov cl,[edx+4]
				mov ch,[edi+4]
				or  ecx,2020h
				.if cl == ch
					.break .if ebx == 5
					mov cl,[edx+5]
					mov ch,[edi+5]
					or  ecx,2020h
					.if cl == ch
						.break .if ebx == 6
						mov cl,[edx+6]
						mov ch,[edi+6]
						or  ecx,2020h
						.break .if cl == ch
					.endif
				.endif
			.endif
		.endif
		movzx eax,ResWordTable[eax*8].next
	.endw

	pop	ebx
	pop	edi
	ret

case_8:
	push	esi
	push	edi
	push	ebx

	mov	ebx,edx
	mov	edi,ecx

	mov	ecx,1
@@:
	movzx	edx,BYTE PTR [ecx+edi]
	or	edx,20h
	shl	eax,3
	add	eax,edx
	mov	edx,eax
	and	edx,not 00001FFFh
	xor	eax,edx
	shr	edx,13
	xor	eax,edx
	add	ecx,1
	cmp	ecx,ebx
	jl	@B

	.if eax >= HASH_TABITEMS * 8
		sub eax,HASH_TABITEMS * 8
	.endif

	cmp	eax,HASH_TABITEMS
	sbb	ecx,ecx
	not	ecx
	and	ecx,HASH_TABITEMS
@@:
	sub	eax,ecx
	cmp	eax,HASH_TABITEMS
	jnb	@B
	movzx	eax,resw_table[eax*2]

	.while	eax

		.if ResWordTable[eax*8].len == bl

			mov esi,ResWordTable[eax*8]._name
			mov edx,[esi]
			or  edx,20202020h
			mov ecx,[edi]
			or  ecx,20202020h
			.if edx == ecx
				;mov	edx,[esi+4]
				;or	edx,20202020h
				mov ecx,[edi+4]
				or  ecx,20202020h
				;.if	edx == ecx
				.if ecx == [esi+4]
					mov edx,ebx
					loop_c:
					.break	.if edx == 8
					sub edx,1
					mov cl,[edi+edx]
					mov ch,[edi+edx]
					or  ecx,2020h
					cmp cl,ch
					je  loop_c
				.endif
			.endif
		.endif
		movzx eax,ResWordTable[eax*8].next
	.endw
	pop ebx
	pop edi
	pop esi
	ret

FindResWord ENDP

	END
