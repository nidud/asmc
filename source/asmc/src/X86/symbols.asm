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

SymSetCmpFunc proc
    mov SymCmpFunc,_memicmp
    .if ModuleInfo.case_sensitive
	mov SymCmpFunc,memcmp
    .endif
    ret
SymSetCmpFunc ENDP

; reset local hash table

SymClearLocal PROC
    xor	 eax,eax
    lea	 edx,lsym_table
    mov	 ecx,sizeof(lsym_table) / 4
    xchg edx,edi
    rep	 stosd
    mov	 edi,edx
    ret
SymClearLocal ENDP

; store local hash table in proc's list of local symbols

SymGetLocal proc psym

    mov ecx,psym
    mov edx,[ecx].nsym.procinfo
    lea edx,[edx].proc_info.labellist
    xor ecx,ecx
    .while ecx < LHASH_TABLE_SIZE

	mov eax,lsym_table[ecx*4]
	add ecx,1
	.continue .if !eax

	mov [edx],eax
	lea edx,[eax].nsym.nextll
    .endw
    xor eax,eax
    mov [edx],eax
    ret

SymGetLocal endp

; restore local hash table.
; - proc: procedure which will become active.
; fixme: It might be necessary to reset the "defined" flag
; for local labels (not for params and locals!). Low priority!
SymSetLocal proc uses edi psym
    xor eax,eax
    lea edi,lsym_table
    mov ecx,sizeof(lsym_table) / 4
    rep stosd
    mov ecx,psym
    mov edi,[ecx].nsym.procinfo
    mov edi,[edi].proc_info.labellist
    .while edi
	mov ecx,[edi].asym._name
	xor eax,eax
	movzx edx,BYTE PTR [ecx]
	.while edx
	    add ecx,1
	    or	edx,0x20
	    shl eax,5
	    add eax,edx
	    mov edx,eax
	    and edx,not HASH_MASK
	    xor eax,edx
	    shr edx,HASH_MAGNITUDE
	    xor eax,edx
	    movzx edx,BYTE PTR [ecx]
	.endw
	.while eax >= LHASH_TABLE_SIZE
	    sub eax,LHASH_TABLE_SIZE
	.endw
	mov lsym_table[eax*4],edi
	mov edi,[edi].nsym.nextll
    .endw
    ret
SymSetLocal endp

SymAlloc proc uses esi edi sname
    mov esi,sname
    mov edi,strlen(esi)
    LclAlloc(&[edi+sizeof(nsym)+1])
    mov [eax].asym.name_size,di
    mov [eax].asym.mem_type,MT_EMPTY
    lea edx,[eax+sizeof(nsym)]
    mov [eax].asym._name,edx
    .if ModuleInfo.cref
	or [eax].asym.flag,SFL_LIST
    .endif
    .if edi
	mov ecx,edi
	mov edi,edx
	rep movsb
    .endif
    ret
SymAlloc ENDP

GETHASH MACRO value
    ;
    ; Divide total by array count not using DIV
    ;
    .if eax >= value * 8
	sub eax,value * 8
    .endif
    .while eax >= value
	sub eax,value
    .endw
    ENDM

SymFind proc fastcall uses esi edi ebx ebp sname
    ;
    ; find a symbol in the local/global symbol table,
    ; return ptr to next free entry in global table if not found.
    ; Note: lsym must be global, thus if the symbol isn't
    ; found and is to be added to the local table, there's no
    ; second scan necessary.
    ;
    mov esi,ecx
    xor eax,eax
    movzx edx,byte ptr [ecx]

    .repeat

	.break .if !edx

	.repeat
	    add ecx,1
	    or	edx,20h
	    shl eax,5
	    add eax,edx
	    mov edx,eax
	    and edx,not HASH_MASK
	    xor eax,edx
	    shr edx,HASH_MAGNITUDE
	    xor eax,edx
	    movzx edx,BYTE PTR [ecx]
	.until !edx

	sub ecx,esi
	mov ebp,eax

	.if CurrProc

	    .if eax >= LHASH_TABLE_SIZE*8
		sub eax,LHASH_TABLE_SIZE*8
	    .endif
	    .while eax >= LHASH_TABLE_SIZE
		sub eax,LHASH_TABLE_SIZE
	    .endw
	    lea edx,lsym_table[eax*4]
	    mov eax,[edx]

	    .if ModuleInfo.case_sensitive

		.while eax
		    .if cx == [eax].asym.name_size
			mov edi,[eax].asym._name
			.repeat
			    .if ecx >= 4
				sub ecx,4
				mov ebx,[esi+ecx]
				.break .if ebx != [edi+ecx]
				.continue(0)
			    .endif
			    .while ecx
				sub ecx,1
				mov bl,[esi+ecx]
				.break(1) .if bl != [edi+ecx]
			    .endw
			    mov lsym,edx
			    .break(2)
			.until 1
			movzx ecx,[eax].asym.name_size
		    .endif
		    lea edx,[eax].asym.nextitem
		    mov eax,[edx]
		.endw

	    .else

		.while eax
		    .if cx == [eax].asym.name_size
			mov edi,[eax].asym._name
			.while 1
			    .if ecx >= 4
				sub ecx,4
				mov ebx,[esi+ecx]
				.continue(0) .if ebx == [edi+ecx]
				add ecx,4
			    .endif
			    .while ecx
				sub ecx,1
				mov bl,[esi+ecx]
				.continue .if bl == [edi+ecx]
				mov bh,[edi+ecx]
				or ebx,0x2020
				.break(1) .if bl != bh
			    .endw
			    mov lsym,edx
			    .break(2)
			.endw
			movzx ecx,[eax].asym.name_size
		    .endif
		    lea edx,[eax].asym.nextitem
		    mov eax,[edx]
		.endw
	    .endif
	    mov lsym,edx
	    mov eax,ebp
	.endif


	.if eax >= GHASH_TABLE_SIZE*8
	    sub eax,GHASH_TABLE_SIZE*8
	.endif
	.while eax >= GHASH_TABLE_SIZE
	    sub eax,GHASH_TABLE_SIZE
	.endw
	lea edx,gsym_table[eax*4]
	mov eax,[edx]

	.if ModuleInfo.case_sensitive

	    .while eax
		.if cx == [eax].asym.name_size
		    mov edi,[eax].asym._name
		    .while 1
			.if ecx >= 4
			    sub ecx,4
			    mov ebx,[esi+ecx]
			    .break .if ebx != [edi+ecx]
			    .continue(0)
			.endif
			.while ecx
			    sub ecx,1
			    mov bl,[esi+ecx]
			    .break(1) .if bl != [edi+ecx]
			.endw
			mov gsym,edx
			.break(2)
		    .endw
		    movzx ecx,[eax].asym.name_size
		.endif
		lea edx,[eax].asym.nextitem
		mov eax,[edx]
	    .endw

	.else

	    .while eax
		.if cx == [eax].asym.name_size
		    mov edi,[eax].asym._name
		    .while 1
			.if ecx >= 4
			    sub ecx,4
			    mov ebx,[esi+ecx]
			    .continue(0) .if ebx == [edi+ecx]
			    add ecx,4
			.endif
			.while ecx
			    sub ecx,1
			    mov bl,[esi+ecx]
			    .continue .if bl == [edi+ecx]
			    mov bh,[edi+ecx]
			    or ebx,0x2020
			    .break(1) .if bl != bh
			.endw
			mov gsym,edx
			.break(2)
		    .endw
		    movzx ecx,[eax].asym.name_size
		.endif
		lea edx,[eax].asym.nextitem
		mov eax,[edx]
	    .endw
	.endif
	mov gsym,edx
	xor eax,eax
    .until 1
    ret

SymFind endp

;
; SymLookup() creates a global label if it isn't defined yet
;
SymLookup proc sname

    .if !SymFind(sname)

	SymAlloc(sname)
	mov ecx,gsym
	mov [ecx],eax
	inc SymCount
    .endif
    ret
SymLookup endp

;
; SymLookupLocal() creates a local label if it isn't defined yet.
; called by LabelCreate() [see labels.c]
;
SymLookupLocal proc sname

    .if !SymFind(sname)
	SymAlloc(sname)
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

SymLookupLocal endp

;
; free a symbol.
; the symbol is no unlinked from hash tables chains,
; hence it is assumed that this is either not needed
; or done by the caller.
;
SymFree proc sym
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
	ReleaseMacroData(ecx)
	.endc
    .endsw
    ret
SymFree endp

;
; add a symbol to local table and set the symbol's name.
; the previous name was "", the symbol wasn't in a symbol table.
; Called by:
; - ParseParams() in proc.c for procedure parameters.
;
SymAddLocal proc uses esi edi ebx sym, sname
    mov ebx,sym
    mov esi,sname
    .repeat
	.if SymFind(esi)
	    .if [eax].asym.state != SYM_UNDEFINED
		;
		; shouldn't happen
		;
		asmerr(2005, esi)
		xor eax,eax
		.break
	    .endif
	.endif
	strlen(esi)
	mov [ebx].asym.name_size,ax
	lea edi,[eax+1]
	LclAlloc(edi)
	mov [ebx].asym._name,eax
	mov ecx,edi
	mov edi,eax
	rep movsb
	mov ecx,lsym
	mov [ecx],ebx
	mov [ebx].asym.nextitem,0
	mov eax,ebx
    .until 1
    ret
SymAddLocal endp

;
; add a symbol to the global symbol table.
; Called by:
; - RecordDirective() in types.c to add bitfield fields (which have global scope).
;
SymAddGlobal proc sym
    mov eax,sym
    .if SymFind([eax].asym._name)
	mov eax,sym
	asmerr(2005, [eax].asym._name)
	xor eax,eax
    .else
	mov eax,sym
	inc SymCount
	mov ecx,gsym
	mov [ecx],eax
	mov [eax].asym.nextitem,0
    .endif
    ret
SymAddGlobal endp

;
; Create symbol and optionally insert it into the symbol table
;
SymCreate proc sname
    .if SymFind(sname)
	asmerr(2005, sname)
	xor eax,eax
    .else
	SymAlloc(sname)
	inc SymCount
	mov ecx,gsym
	mov [ecx],eax
    .endif
    ret
SymCreate endp

;
; Create symbol and insert it into the local symbol table.
; This function is called by LocalDir() and ParseParams()
; in proc.c ( for LOCAL directive and PROC parameters ).
;
SymLCreate proc sname

    .repeat
	.if SymFind(sname)
	    .if [eax].asym.state != SYM_UNDEFINED
		;
		; shouldn't happen
		;
		asmerr(2005, sname)
		xor eax,eax
		.break
	    .endif
	.endif
	SymAlloc(sname)
	mov ecx,lsym
	mov [ecx],eax
    .until 1
    ret

SymLCreate endp

SymGetCount proc
    mov eax,SymCount
    ret
SymGetCount endp

SymMakeAllSymbolsPublic proc uses esi edi

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
		    AddPublicData(edi)
		.endif

	    .endif
	    mov edi,[edi].asym.nextitem
	.endw
	add esi,1
    .until  esi == GHASH_TABLE_SIZE
    ret

SymMakeAllSymbolsPublic endp

; initialize global symbol table

SymInit proc uses esi edi ebx

    local time_of_day

    xor eax,eax
    mov SymCount,eax
    ;
    ; v2.11: ensure CurrProc is NULL - might be a problem if multiple files are assembled
    ;
    mov CurrProc,eax
    lea edi,gsym_table
    mov ecx,sizeof(gsym_table)
    rep stosb

    time(&time_of_day)
    localtime(&time_of_day)
    mov esi,eax

if USESTRFTIME
    strftime(&szDate, 9, "%D", esi)   ; POSIX date (mm/dd/yy)
    strftime(&szTime, 9, "%T", esi)   ; POSIX time (HH:MM:SS)
else
    mov eax,[esi].tm.tm_year
    sub eax,100
    mov ecx,[esi].tm.tm_mon
    add ecx,1
;   sprintf(&szDate, "%02u/%02u/%02u", ecx, [esi].tm.tm_mday, eax)
    add eax,2000
    sprintf(&szDate, "%u-%02u-%02u", eax, ecx, [esi].tm.tm_mday)
    sprintf(&szTime, "%02u:%02u:%02u", [esi].tm.tm_hour, [esi].tm.tm_min, [esi].tm.tm_sec)
endif
    lea esi,tmtab
    .while [esi].tmitem._name
	SymCreate([esi].tmitem._name)
	mov [eax].asym.state,SYM_TMACRO
	or  [eax].asym.flag,SFL_ISDEFINED or SFL_PREDEFINED
	mov ecx,[esi].tmitem.value
	mov [eax].asym.string_ptr,ecx
	mov ecx,[esi].tmitem.store
	add esi,sizeof(tmitem)
	.continue .if !ecx
	mov [ecx],eax
    .endw

    lea esi,eqtab
    .while [esi].eqitem._name
	SymCreate([esi].eqitem._name)
	mov [eax].asym.state,SYM_INTERNAL
	or  [eax].asym.flag,SFL_ISDEFINED or SFL_PREDEFINED
	mov ecx,[esi].eqitem.value
	mov [eax].asym._offset,ecx
	mov ecx,[esi].eqitem.sfunc_ptr
	mov [eax].asym.sfunc_ptr,ecx
	mov ecx,[esi].eqitem.store
	add esi,sizeof(eqitem)
	.continue .if !ecx
	mov [ecx],eax
    .endw
    ;
    ; @WordSize should not be listed
    ;
    and [eax].asym.flag,not SFL_LIST

    .if define_LINUX
	SymCreate("_LINUX")
	mov [eax].asym.state,SYM_TMACRO
	or  [eax].asym.flag,SFL_ISDEFINED or SFL_PREDEFINED
	mov ecx,define_LINUX
	mov [eax].asym._offset,ecx
	mov [eax].asym.sfunc_ptr,0
    .endif

    .if define_WIN64
	SymCreate("_WIN64")
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
    or	[eax].asym.flag,SFL_VARIABLE
    mov eax,LineCur
    and [eax].asym.flag,not SFL_LIST
    ret

SymInit endp

SymPassInit proc pass

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
		    .if !([eax].asym.flag & SFL_PREDEFINED)
			and [eax].asym.flag,not SFL_ISDEFINED
		    .endif
		    mov eax,[eax].asym.nextitem
		.endw

		add ecx,1
	    .until  ecx == GHASH_TABLE_SIZE

	.endif
    .endif
    ret

SymPassInit endp

; get all symbols in global hash table

SymGetAll proc syms

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
    .until  ecx == GHASH_TABLE_SIZE

    ret

SymGetAll endp

; enum symbols in global hash table.
; used for codeview symbolic debug output.
SymEnum proc sym, pi
    mov edx,pi
    mov eax,sym
    .if eax
	mov eax,[eax].asym.nextitem
	mov ecx,[edx]
    .else
	xor ecx,ecx
	mov [edx],ecx
	mov eax,gsym_table
    .endif
    .while !eax && ecx < GHASH_TABLE_SIZE - 1
	add ecx,1
	mov [edx],ecx
	mov eax,gsym_table[ecx*4]
    .endw
    ret
SymEnum endp

;
; add a new node to a queue
;
AddPublicData proc fastcall sym

    mov edx,sym
    lea ecx,ModuleInfo.PubQueue

AddPublicData endp

QAddItem proc fastcall q, d

    push ecx
    push edx
    LclAlloc(sizeof(qnode))
    pop edx
    pop ecx
    mov [eax].qnode.elmt,edx
    mov edx,eax

QAddItem endp

QEnqueue proc fastcall q, item

    xor eax,eax
    .if eax == [ecx].qdesc.head
	mov [ecx].qdesc.head,edx
	mov [ecx].qdesc.tail,edx
	mov [edx],eax
    .else
	mov eax,[ecx].qdesc.tail
	mov [ecx].qdesc.tail,edx
	mov [eax],edx
	xor eax,eax
	mov [edx],eax
    .endif
    ret

QEnqueue endp

get_hash proc fastcall uses ebx s, z

    xor	 eax,eax
    and	 edx,0x000000FF
    .while edx
	movzx ebx,byte ptr [ecx]
	inc   ecx
	or    ebx,0x20
	shl   eax,3
	add   eax,ebx
	mov   ebx,eax
	and   ebx,not 0x00001FFF
	xor   eax,ebx
	shr   ebx,13
	xor   eax,ebx
	dec   edx
    .endw
    mov ecx,HASH_TABITEMS
    xor edx,edx
    div ecx
    mov eax,edx
    ret

get_hash endp

FindResWord proc fastcall w_name, w_size

    movzx eax,BYTE PTR [ecx]
    or al,0x20

    .switch edx

      .case 0
	xor eax,eax
	ret

      .case 1
	movzx eax,resw_table[eax*2]
	.while eax
	    .if ResWordTable[eax*8].len == 1
		mov edx,ResWordTable[eax*8]._name
		mov dh,[edx]
		mov dl,[ecx]
		or  edx,0x2020
		.break .if dl == dh
	    .endif
	    movzx eax,ResWordTable[eax*8].next
	.endw
	ret

      .case 2
	shl eax,3
	movzx edx,BYTE PTR [ecx+1]
	or edx,0x20
	add eax,edx
	cmp eax,HASH_TABITEMS
	sbb edx,edx
	not edx
	and edx,HASH_TABITEMS
	sub eax,edx
	movzx eax,resw_table[eax*2]
	movzx ecx,WORD PTR [ecx]
	or ecx,0x2020
	.while eax
	    .if ResWordTable[eax*8].len == 2
		mov edx,ResWordTable[eax*8]._name
		movzx edx,WORD PTR [edx]
		or edx,0x2020
		.break .if dx == cx
	    .endif
	    movzx eax,ResWordTable[eax*8].next
	.endw
	ret

      .case 3
	shl eax,3
	movzx edx,BYTE PTR [ecx+1]
	or  edx,0x20
	add eax,edx
	shl eax,3
	movzx edx,BYTE PTR [ecx+2]
	or  edx,0x20
	add eax,edx
	mov edx,eax
	and edx,not 0x00001FFF
	xor eax,edx
	shr edx,13
	xor eax,edx
	GETHASH HASH_TABITEMS
	movzx eax,resw_table[eax*2]
	mov ecx,[ecx]
	or  ecx,0x00202020
	and ecx,0x00FFFFFF
	.while	eax
	    .if ResWordTable[eax*8].len == 3
		mov edx,ResWordTable[eax*8]._name
		mov edx,[edx]
		or  edx,0x00202020
		and edx,0x00FFFFFF
		.break .if edx == ecx
	    .endif
	    movzx eax,ResWordTable[eax*8].next
	.endw
	ret

      .case 4
	movzx edx,BYTE PTR [ecx+1]
	or  dl,0x20
	shl eax,3
	add eax,edx
	mov dl,[ecx+2]
	or  dl,20h
	shl eax,3
	add eax,edx
	mov edx,eax
	and edx,not 0x1FFF
	xor eax,edx
	shr edx,13
	xor eax,edx
	movzx edx,BYTE PTR [ecx+3]
	or  dl,0x20
	shl eax,3
	add eax,edx
	mov edx,eax
	and edx,not 0x1FFF
	xor eax,edx
	shr edx,13
	xor eax,edx
	GETHASH HASH_TABITEMS
	movzx eax,resw_table[eax*2]
	mov ecx,[ecx]
	or  ecx,0x20202020
	.while eax
	    .if ResWordTable[eax*8].len == 4
		mov edx,ResWordTable[eax*8]._name
		.break .if ecx == [edx]
	    .endif
	    movzx eax,ResWordTable[eax*8].next
	.endw
	ret

      .case 5
      .case 6
      .case 7
	push edi
	push ebx
	mov ebx,edx
	mov edi,ecx
	mov ecx,1
	.repeat
	    movzx edx,BYTE PTR [ecx+edi]
	    or	edx,0x20
	    shl eax,3
	    add eax,edx
	    mov edx,eax
	    and edx,not 0x00001FFF
	    xor eax,edx
	    shr edx,13
	    xor eax,edx
	    add ecx,1
	    cmp ecx,ebx
	.untilnl
	.if eax >= HASH_TABITEMS * 8
	    sub eax,HASH_TABITEMS * 8
	.endif
	cmp eax,HASH_TABITEMS
	sbb ecx,ecx
	not ecx
	and ecx,HASH_TABITEMS
	.repeat
	    sub eax,ecx
	.until eax < HASH_TABITEMS
	movzx eax,resw_table[eax*2]
	.while eax
	    .if ResWordTable[eax*8].len == bl
		mov edx,ResWordTable[eax*8]._name
		mov edx,[edx]
		or  edx,0x20202020
		mov ecx,[edi]
		or  ecx,0x20202020
		.if edx == ecx
		    mov edx,ResWordTable[eax*8]._name
		    mov cl,[edx+4]
		    mov ch,[edi+4]
		    or	ecx,2020h
		    .if cl == ch
			.break .if ebx == 5
			mov cl,[edx+5]
			mov ch,[edi+5]
			or  ecx,0x2020
			.if cl == ch
			    .break .if ebx == 6
			    mov cl,[edx+6]
			    mov ch,[edi+6]
			    or	ecx,0x2020
			    .break .if cl == ch
			.endif
		    .endif
		.endif
	    .endif
	    movzx eax,ResWordTable[eax*8].next
	.endw
	pop ebx
	pop edi
	ret

      .default
	push esi
	push edi
	push ebx
	mov ebx,edx
	mov edi,ecx
	mov ecx,1
	.repeat
	    movzx edx,BYTE PTR [ecx+edi]
	    or	edx,0x20
	    shl eax,3
	    add eax,edx
	    mov edx,eax
	    and edx,not 0x00001FFF
	    xor eax,edx
	    shr edx,13
	    xor eax,edx
	    add ecx,1
	    cmp ecx,ebx
	.untilnl
	.if eax >= HASH_TABITEMS * 8
	    sub eax,HASH_TABITEMS * 8
	.endif
	cmp eax,HASH_TABITEMS
	sbb ecx,ecx
	not ecx
	and ecx,HASH_TABITEMS
	.repeat
	    sub eax,ecx
	.until eax < HASH_TABITEMS
	movzx eax,resw_table[eax*2]
	.while eax
	    .if ResWordTable[eax*8].len == bl
		mov esi,ResWordTable[eax*8]._name
		mov edx,[esi]
		or  edx,0x20202020
		mov ecx,[edi]
		or  ecx,0x20202020
		.if edx == ecx
		    mov ecx,[edi+4]
		    or	ecx,0x20202020
		    .if ecx == [esi+4]
			mov edx,ebx
			.repeat
			    .break(1) .if edx == 8
			    sub edx,1
			    mov cl,[edi+edx]
			    mov ch,[edi+edx]
			    or	ecx,0x2020
			.until cl != ch
		    .endif
		.endif
	    .endif
	    movzx eax,ResWordTable[eax*8].next
	.endw
	pop ebx
	pop edi
	pop esi
	ret
    .endsw

FindResWord endp

    end
