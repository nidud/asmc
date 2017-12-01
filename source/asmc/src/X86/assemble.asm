; ASSEMBLE.ASM--
; Copyright (C) 2017 Asmc Developers

include malloc.inc
include stdio.inc
include stdlib.inc
include string.inc
include io.inc
include errno.inc
include setjmp.inc

include asmc.inc
include token.inc

public	jmpenv
extern	MacroLocals:dword

conv_section	STRUC
len		dd ?
flags		dd ?
src		dd ?
dst		dd ?
conv_section	ENDS

.data?

ModuleInfo	module_info <>
LinnumQueue	qdesc <>
jmpenv		S_JMPBUF <>

.data

Parse_Pass	dd 0
write_to_file	dd 0

cp_text1	db "_TEXT",0
cp_text2	db ".text",0
cp_data1	db "_DATA",0
cp_data2	db ".data",0
cp_const	db "CONST",0
cp_rdata	db ".rdata",0
cp_bss1		db "_BSS",0
cp_bss2		db ".bss",0

    align 4

formatoptions	label format_options
format_options	< bin_init,  0000h, <"BIN",0,0,0>>
format_options	< omf_init,  0000h, <"OMF",0,0,0>>
format_options	< coff_init, 0E12h, <"COFF", 0,0>>
format_options	< elf_init,  0F00h, <"ELF",0,0,0>>

cst		label conv_section
		dd 5, CSF_GRPCHK, cp_text1, cp_text2
		dd 5, CSF_GRPCHK, cp_data1, cp_data2
		dd 5, CSF_GRPCHK, cp_const, cp_rdata
		dd 4,	       0, cp_bss1,  cp_bss2
stt		db SEGTYPE_CODE,SEGTYPE_DATA,SEGTYPE_DATA,SEGTYPE_BSS
filetypes	dd 'msa.','jbo.','tsl.','rre.','nib.','exe.'
currentftype	dd 0,0
remove_obj	dd 0

.code

;
; translate section names (COFF+PE):
; _TEXT -> .text
; _DATA -> .data
; CONST -> .rdata
; _BSS	 -> .bss
;
ConvertSectionName proc uses esi edi ebx sym, pst, buffer

    .repeat

	.for edi=sym, esi=0: esi < 4:

	    mov ebx,esi
	    add esi,1
	    shl ebx,4
	    mov edx,cst[ebx].len

	    .if !memcmp( [edi].asym._name, cst[ebx].src, edx )

		add edx,[edi].asym._name
		mov al,[edx]
		.continue .if al && ( al != '$' || cst[ebx].flags & CSF_GRPCHK )

		mov ecx,pst
		.if ecx

		    mov eax,[edi].nsym.seginfo
		    .if !( esi == CSI_BSS + 1 && [eax].seg_info.bytes_written )
			;
			; don't set segment type to BSS if the segment
			; contains initialized data
			;
			movzx eax,stt[esi-1]
			mov [ecx],eax
		    .endif
		.endif
		mov eax,cst[ebx].dst
		.if byte ptr [edx]

			strcat(strcpy(buffer, eax), edx)
		.endif
		.break(1)
	    .endif
	.endf
	mov eax,sym
	mov eax,[eax].asym._name
    .until 1
    ret

ConvertSectionName endp
;
; Write a byte to the segment buffer.
; in OMF, the segment buffer is flushed when the max. record size is reached.
;

MAX_LEDATA_THRESHOLD equ 1024 - 10

OutputByte proc uses esi edi ebx char

    mov esi,ModuleInfo.currseg
    mov edi,[esi].nsym.seginfo

    .if write_to_file

	mov ebx,[edi].seg_info.current_loc
	sub ebx,[edi].seg_info.start_loc

	.if Options.output_format == OFORMAT_OMF && ebx >= MAX_LEDATA_THRESHOLD

	    omf_FlushCurrSeg()

	    mov ebx,[edi].seg_info.current_loc
	    sub ebx,[edi].seg_info.start_loc
	.endif

	mov eax,char
	mov ecx,[edi].seg_info.CodeBuffer
	mov [ecx+ebx],al

    .else

	mov eax,[edi].seg_info.current_loc
	.if eax < [edi].seg_info.start_loc

	    mov [edi].seg_info.start_loc,eax
	.endif
    .endif

    inc [edi].seg_info.current_loc
    inc [edi].seg_info.bytes_written
    mov [edi].seg_info.written,1
    mov eax,[edi].seg_info.current_loc

    .if eax > [esi].nsym.sym.max_offset

	mov [esi].nsym.sym.max_offset,eax
    .endif
    ret
OutputByte endp

FillDataBytes proc uses esi char, len
    .if ModuleInfo.CommentDataInCode
	omf_OutSelect(1)
    .endif
    mov esi,len
    .while esi
	OutputByte(char)
	dec esi
    .endw
    ret
FillDataBytes endp

OutputBytes proc uses esi edi ebx pbytes, len, fixup

    mov esi,ModuleInfo.currseg
    mov edi,[esi].nsym.seginfo

    .if write_to_file

	mov ebx,[edi].seg_info.current_loc
	sub ebx,[edi].seg_info.start_loc
	mov eax,len
	add eax,ebx

	.if Options.output_format == OFORMAT_OMF && eax >= MAX_LEDATA_THRESHOLD

	    omf_FlushCurrSeg()

	    mov ebx,[edi].seg_info.current_loc
	    sub ebx,[edi].seg_info.start_loc
	.endif

	.if fixup
	    store_fixup(fixup, esi, pbytes)
	.endif

	mov edx,edi
	mov eax,esi
	mov edi,[edi].seg_info.CodeBuffer
	add edi,ebx
	mov ecx,len
	mov esi,pbytes
	rep movsb
	mov edi,edx
	mov esi,eax
    .else
	mov eax,[edi].seg_info.current_loc
	.if eax < [edi].seg_info.start_loc
	    mov [edi].seg_info.start_loc,eax
	.endif
    .endif

    mov eax,len
    add [edi].seg_info.current_loc,eax
    add [edi].seg_info.bytes_written,eax
    mov [edi].seg_info.written,1
    mov eax,[edi].seg_info.current_loc
    .if eax > [esi].nsym.sym.max_offset
	mov [esi].nsym.sym.max_offset,eax
    .endif
    ret
OutputBytes endp

;
; set current offset in a segment (usually CurrSeg) without to write anything
;
SetCurrOffset proc uses esi edi ebx dseg, value, relative, select_data

    mov ebx,value
    mov esi,dseg
    mov eax,relative
    mov ecx,write_to_file
    mov edi,[esi].nsym.seginfo

    .if eax
	add ebx,[edi].seg_info.current_loc
    .endif
    .if Options.output_format == OFORMAT_OMF
	.if esi == ModuleInfo.currseg
	    .if ecx
		omf_FlushCurrSeg()
	    .endif
	    ;
	    ; for debugging, tell if data is located in code sections
	    ;
	    .if select_data && ModuleInfo.CommentDataInCode
		omf_OutSelect(1)
	    .endif
	    mov LastCodeBufSize,ebx
	.endif
	mov [edi].seg_info.start_loc,ebx
    .elseif !ecx && !eax && ![edi].seg_info.bytes_written
	;
	; if there's an ORG (relative==false) and no initialized data
	; has been set yet, set start_loc!
	;
	mov [edi].seg_info.start_loc,ebx
    .endif
    mov [edi].seg_info.current_loc,ebx
    mov [edi].seg_info.written,0
    mov eax,[edi].seg_info.current_loc
    .if eax > [esi].nsym.sym.max_offset
	mov [esi].nsym.sym.max_offset,eax
    .endif
    mov eax,NOT_ERROR
    ret
SetCurrOffset endp

;
; write object module
;
WriteModule proc uses esi edi ebx modinfo

    mov esi,SymTables[TAB_SEG*sizeof(symbol_queue)].head
    .while  esi
	mov eax,[esi].nsym.seginfo
	.if [eax].seg_info.Ofssize == USE16 && [esi].nsym.sym.max_offset > 10000h
	    .if Options.output_format == OFORMAT_OMF
		asmerr( 2103, [esi].nsym.sym._name )
	    .endif
	.endif
	mov esi,[esi].nsym.next
    .endw

    mov	    eax,modinfo
    push    eax
    call    [eax].module_info.WriteModule
    add	    esp,4

    mov edi,Options.names[OPTN_LNKDEF_FN*4]
    .if edi
	.if !fopen(edi, "w")
	    asmerr(3020, edi)
	.else
	    mov edi,eax
	    mov esi,SymTables[TAB_EXT*sizeof(symbol_queue)].head
	    .while  esi
		mov ebx,[esi].asym.dll
		.if [esi].asym.flag & SFL_ISPROC && [esi].asym.dll && [ebx].dll_desc.dname \
		    && ( !( [esi].asym.sint_flag & SINT_WEAK) || [esi].asym.flag & SFL_IAT_USED )

		    Mangle(esi, ModuleInfo.stringbufferend)
		    sprintf(ModuleInfo.currsource, "import '%s'  %s.%s\n",
			ModuleInfo.stringbufferend,
			&[ebx].dll_desc.dname, [esi].asym._name)
		    mov ebx,eax
		    .if fwrite(ModuleInfo.currsource, 1, ebx, edi) != ebx
			WriteError()
		    .endif
		.endif
		mov esi,[esi].nsym.next
	    .endw
	    fclose(edi)
	.endif
    .endif
    mov eax,NOT_ERROR
    ret
WriteModule endp

add_cmdline_tmacros proc uses esi edi ebx

    push ebp
    mov	 ebp,esp

    mov edi,Options.queues[OPTQ_MACRO*4]
    .while edi
	lea esi,[edi].qitem.value
	.if !strchr(esi, '=')
	    strlen(esi)
	    lea ebx,[esi+eax]
	.else
	    mov ebx,eax
	    mov edx,ebx
	    sub edx,esi
	    inc edx
	    memcpy(alloca(edx), esi, edx)
	    mov byte ptr [eax+edx-1],0
	    inc ebx
	    mov esi,eax
	.endif

	xor ecx,ecx
	movzx eax,byte ptr [esi]
	.if !((_ltype[eax+1] & _LABEL) || al == '.')
	    inc ecx
	.else
	    .for edx = &[esi+1], al = [edx] : eax: edx++, al = [edx]

		.if !(_ltype[eax+1] & (_LABEL or _DIGIT))
		    inc ecx
		    .break
		.endif
	    .endf
	.endif
	.if ecx
	    asmerr(2008, esi)
	    .break
	.endif

	.if !SymFind(esi)
	    SymCreate(esi)
	    mov [eax].asym.state,SYM_TMACRO
	.endif
	.if [eax].asym.state != SYM_TMACRO
	    asmerr(2005, esi)
	    .break
	.endif
	or  [eax].asym.flag,SFL_ISDEFINED or SFL_PREDEFINED
	mov [eax].asym.string_ptr,ebx
	mov edi,[edi].qitem.next
    .endw
    mov esp,ebp
    pop ebp
    ret
add_cmdline_tmacros endp

add_incpaths proc uses esi
    mov esi,Options.queues[OPTQ_INCPATH*4]
    .while esi
	AddStringToIncludePath(&[esi].qitem.value)
	mov esi,[esi].qitem.next
    .endw
    ret
add_incpaths endp

CmdlParamsInit proc pass
    .if pass == PASS_1

	add_cmdline_tmacros()
	add_incpaths()

	.if !Options.ignore_include

	    .if getenv("INCLUDE")

		AddStringToIncludePath(eax)
	    .endif
	.endif
    .endif
    ret
CmdlParamsInit endp

WritePreprocessedLine proc string
    .data
    PrintEmptyLine db 1
    .code
    .if ModuleInfo.token_count > 0
	mov eax,string
	movzx ecx,byte ptr [eax]
	.while byte ptr _ltype[ecx+1] & _SPACE
	    add eax,1
	    mov cl,[eax]
	.endw
	.if ecx == '%'
	    inc eax
	.else
	    mov eax,string
	.endif
	printf("%s\n", eax)
	mov PrintEmptyLine,1
    .elseif PrintEmptyLine
	mov PrintEmptyLine,0
	printf("\n")
    .endif
    ret
WritePreprocessedLine endp

SetMasm510 proc value
    mov eax,value
    mov ModuleInfo.m510,al
    mov ModuleInfo.oldstructs,al
    mov ModuleInfo.dotname,al
    mov ModuleInfo.setif2,al
    .if eax
	.if ModuleInfo._model == MODEL_NONE
	    ;
	    ; if no model is specified, set OFFSET:SEGMENT
	    ;
	    mov ModuleInfo.offsettype,OT_SEGMENT
	    .if ModuleInfo.langtype == LANG_NONE

		mov ModuleInfo.scoped,0
		mov ModuleInfo.procs_private,0
	    .endif
	.endif
    .endif
    ret
SetMasm510 endp

ModulePassInit proc uses esi

    mov ecx,Options.cpu
    mov esi,Options._model
    ;
    ; set default values not affected by the masm 5.1 compat switch
    ;
    mov ModuleInfo.procs_private,0
    mov ModuleInfo.procs_export,0
    mov ModuleInfo.offsettype,OT_GROUP
    mov ModuleInfo.scoped,1

    .if !UseSavedState

	mov eax,Options.langtype
	mov ModuleInfo.langtype,al
	mov eax,Options.fctype
	mov ModuleInfo.fctype,al
	mov eax,ecx
	and eax,P_CPU_MASK

	.if ModuleInfo.sub_format == SFORMAT_64BIT
	    ;
	    ; v2.06: force cpu to be at least P_64, without side effect to Options.cpu
	    ;
	    .if eax < P_64  ; enforce cpu to be 64-bit

		mov ecx,P_64
	    .endif
	    ;
	    ; ignore -m switch for 64-bit formats.
	    ; there's no other model than FLAT possible.
	    ;
	    mov esi,MODEL_FLAT
	    .if ModuleInfo.langtype == LANG_NONE

		.if Options.output_format == OFORMAT_COFF
		    mov ModuleInfo.langtype,LANG_FASTCALL
		.else
		    mov ModuleInfo.langtype,LANG_SYSCALL
		.endif
	    .endif
	.else
	    ;
	    ; if model FLAT is to be set, ensure that cpu is compat.
	    ;
	    .if esi == MODEL_FLAT && eax < P_386    ; cpu < 386?

		mov ecx,P_386
	    .endif
	.endif
	SetCPU(ecx)
	;
	; table ModelToken starts with MODEL_TINY, which is index 1"
	;
	.if esi != MODEL_NONE

	    AddLineQueueX("%r %s", T_DOT_MODEL, ModelToken[esi*4-4])
	.endif
    .endif

    movzx eax,Options.masm51_compat
    SetMasm510(eax)
    mov ModuleInfo.defOfssize,USE16
    mov ModuleInfo.ljmp,1
    mov al,Options.write_listing
    mov ModuleInfo.list,al
    mov ModuleInfo.cref,1
    mov al,Options.listif
    mov ModuleInfo.listif,al
    mov al,Options.list_generated_code
    mov ModuleInfo.list_generated_code,al
    mov eax,Options.list_macro
    mov ModuleInfo.list_macro,eax
    mov al,Options.case_sensitive
    mov ModuleInfo.case_sensitive,al
    mov al,Options.convert_uppercase
    mov ModuleInfo.convert_uppercase,al
    SymSetCmpFunc()
    mov ModuleInfo.segorder,SEGORDER_SEQ;
    mov ModuleInfo.radix,10
    mov al,Options.fieldalign
    mov ModuleInfo.fieldalign,al
    mov ModuleInfo.procalign,0
    mov al,Options.xflag
    mov ModuleInfo.xflag,al
    mov al,ModuleInfo.aflag
    and al,_AF_LSTRING
    or	al,Options.aflag
    mov ModuleInfo.aflag,al
    mov al,Options.loopalign
    mov ModuleInfo.loopalign,al
    mov al,Options.casealign
    mov ModuleInfo.casealign,al
    mov eax,Options.codepage
    mov ModuleInfo.codepage,eax
    mov al,Options.epilogueflags
    mov ModuleInfo.epilogueflags,al

    ;
    ; if OPTION DLLIMPORT was used, reset all iat_used flags
    ;
    .if ModuleInfo.DllQueue

	mov eax,SymTables[TAB_EXT*sizeof(symbol_queue)].head
	.while eax

	    and [eax].asym.flag,not SFL_IAT_USED
	    mov eax,[eax].nsym.next
	.endw
    .endif
    ret
ModulePassInit endp
;
; checks after pass one has been finished without errors
;
PassOneChecks proc uses esi edi
    ;
    ; check for open structures and segments has been done inside the
    ; END directive handling already
    ;
    ; v2.10: now done for PROCs as well, since procedures
    ; must be closed BEFORE segments are to be closed.
    ;
    HllCheckOpen()
    CondCheckOpen()
    .if !ModuleInfo.EndDirFound

	asmerr(2088)
    .endif

    ; v2.04: check the publics queue.
    ; - only internal symbols can be public.
    ; - weak external symbols are filtered ( since v2.11 )
    ; - anything else is an error
    ; v2.11: moved here ( from inside the "#if FASTPASS"-block )
    ; because the loop will now filter weak externals [ this
    ; was previously done in GetPublicSymbols() ]
    ;
    lea edx,ModuleInfo.PubQueue
    mov ecx,[edx].qdesc.head
    .while ecx
	mov eax,[ecx].qnode.sym
	.if [eax].asym.state == SYM_INTERNAL

	    mov edx,ecx
	.elseif [eax].asym.state == SYM_EXTERNAL && [eax].asym.sint_flag & SINT_WEAK

	    mov eax,[ecx].qnode.next
	    mov [edx].qnode.next,eax
	    mov ecx,edx
	.else
	    mov UseSavedState,0
	    jmp aliases
	.endif
	mov ecx,[ecx].qnode.next
    .endw
    ;
    ; check if there's an undefined segment reference.
    ; This segment was an argument to a group definition then.
    ; Just do a full second pass, the GROUP directive will report
    ; the error.
    ;
    mov eax,SymTables[TAB_SEG*sizeof(symbol_queue)].head
    .while eax
	.if ![eax].asym._segment

	    mov UseSavedState,0
	    jmp aliases
	.endif
	mov eax,[eax].nsym.next
    .endw
    ;
    ; if there's an item in the safeseh list which is not an
    ; internal proc, make a full second pass to emit a proper
    ; error msg at the .SAFESEH directive
    ;
    mov eax,ModuleInfo.SafeSEHQueue.head
    .while eax
	.if [eax].asym.state != SYM_INTERNAL || !([eax].asym.flag & SFL_ISPROC)

	    mov UseSavedState,0
	    jmp aliases
	.endif
	mov eax,[eax].nsym.next
    .endw
aliases:
    ;
    ; scan ALIASes for COFF/ELF
    ;
    .if Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF

	mov ecx,SymTables[TAB_ALIAS*sizeof(symbol_queue)].head
	.while ecx
	    mov eax,[ecx].asym.substitute
	    ;
	    ; check if symbol is external or public
	    ;
	    .if !eax || [eax].asym.state != SYM_EXTERNAL \
		&& ([eax].asym.state != SYM_INTERNAL || !([eax].asym.flag & SFL_ISPUBLIC))

		mov UseSavedState,0
		.break
	    .endif
	    ;
	    ; make sure it becomes a strong external
	    ;
	    .if [eax].asym.state == SYM_EXTERNAL

		or [eax].asym.flag,SFL_USED
	    .endif
	    mov ecx,[ecx].nsym.next
	.endw
    .endif
    ;
    ; scan the EXTERN/EXTERNDEF items
    ;
    mov edi,SymTables[TAB_EXT*sizeof(symbol_queue)].head
    .while edi
	mov esi,edi
	mov edi,[esi].nsym.next
	.if [esi].asym.flag & SFL_USED

	    and [esi].asym.sint_flag,not SINT_WEAK
	.endif
	.if [esi].asym.sint_flag & SINT_WEAK && !([esi].asym.flag & SFL_IAT_USED)
	    ;
	    ; remove unused EXTERNDEF/PROTO items from queue.
	    ;
	    sym_remove_table(&SymTables[TAB_EXT*sizeof(symbol_queue)], esi)
	    .continue
	.endif
	.continue .if [esi].asym.sint_flag & SINT_ISCOM
	;
	; optional alternate symbol must be INTERNAL or EXTERNAL. COFF (and ELF?)
	; also wants internal symbols to be public (which is reasonable, since
	; the linker won't know private symbols and hence will search for a symbol
	; of that name "elsewhere").
	;
	mov eax,[esi].asym.altname
	.if eax

	    .if [eax].asym.state == SYM_INTERNAL

		.if !( [eax].asym.flag & SFL_ISPUBLIC ) && \
		    ( Options.output_format == OFORMAT_COFF || \
		      Options.output_format == OFORMAT_ELF)

		    SkipSavedState()
		.endif
	    .elseif [eax].asym.state != SYM_EXTERNAL

		mov UseSavedState,0
	    .endif
	.endif
    .endw

    .if !ModuleInfo.error_count
	;
	; make all symbols of type SYM_INTERNAL, which aren't
	; a constant, public.
	;
	.if Options.all_symbols_public

	    SymMakeAllSymbolsPublic()
	.endif

	.if !Options.syntax_check_only

	    mov write_to_file,1
	.endif

	.if ModuleInfo.Pass1Checks

	    push offset ModuleInfo
	    call ModuleInfo.Pass1Checks
	    add esp,4
	.endif
    .endif
    ret
PassOneChecks endp
;
; do ONE assembly pass
; the FASTPASS variant (which is default now) doesn't scan the full source
; for each pass. For this to work, the following things are implemented:
; 1. in pass one, save state if the first byte is to be emitted.
;    <state> is the segment stack, moduleinfo state, ...
; 2. once the state is saved, all preprocessed lines must be stored.
;    this can be done here, in OnePass, the line is in <string>.
;    Preprocessed macro lines are stored in RunMacro().
; 3. for subsequent passes do
;    - restore the state
;    - read preprocessed lines and feed ParseLine() with it
;
OnePass proc uses esi edi

    InputPassInit()
    ModulePassInit()
    SymPassInit(Parse_Pass)
    LabelInit()
    SegmentInit(Parse_Pass)
    ContextInit(Parse_Pass)
    ProcInit()
    TypesInit()
    HllInit(Parse_Pass)
    MacroInit(Parse_Pass)
    AssumeInit(Parse_Pass)
    CmdlParamsInit(Parse_Pass)

    xor eax,eax
    mov ModuleInfo.EndDirFound,al
    mov ModuleInfo.PhaseError,al
    LinnumInit()
    .if ModuleInfo.line_queue.head

	RunLineQueue()
    .endif

    mov StoreState,0
    .if Parse_Pass > PASS_1 && UseSavedState == 1

	RestoreState()
	mov LineStoreCurr,eax
	mov esi,eax

	.while	esi && !ModuleInfo.EndDirFound

	    set_curr_srcfile([esi].line_item.srcfile, [esi].line_item.lineno)

	    mov ModuleInfo.line_flags,0
	    mov eax,[esi].line_item.macro_level
	    mov MacroLevel,eax
	    mov ModuleInfo.CurrComment,0
	    Tokenize(&[esi].line_item.line, 0, ModuleInfo.tokenarray, TOK_DEFAULT)
	    mov ModuleInfo.token_count,eax
	    .if eax

		ParseLine(ModuleInfo.tokenarray)
	    .endif
	    mov esi,[esi].line_item.next
	    mov LineStoreCurr,esi
	.endw
    .else
	mov esi,Options.queues[OPTQ_FINCLUDE*4]
	.while esi
	    lea eax,[esi].qitem.value
	    mov esi,[esi].qitem.next
	    .if SearchFile(eax,1)

		ProcessFile(ModuleInfo.tokenarray)
	    .endif
	.endw
	ProcessFile(ModuleInfo.tokenarray)
    .endif

    LinnumFini()
    .if Parse_Pass == PASS_1

	PassOneChecks()
    .endif
    ClearSrcStack()
    mov eax,1
    ret
OnePass endp

get_module_name proc private uses esi edi

    mov esi,Options.names[OPTN_MODULE_NAME*4]
    .if esi

	strncpy( &ModuleInfo._name, esi, sizeof(ModuleInfo._name))
	mov ModuleInfo._name[sizeof(ModuleInfo._name)-1],0
    .else
	GetFNamePart(ModuleInfo.curr_fname[ASM*4])
	mov esi,eax
	.if GetExtPart(eax) == esi
	    strlen(esi)
	    add eax,esi
	.endif
	sub eax,esi
	mov ModuleInfo._name[eax],0
	memcpy(&ModuleInfo._name, esi, eax)
    .endif
    ;
    ; the module name must be a valid identifier, because it's used
    ; as part of a segment name in certain memory models.
    ;
    lea esi,ModuleInfo._name
    _strupr(esi)
    .while 1
	movzx	eax,byte ptr [esi]
	add esi,1
	.break	.if !eax
	.continue .if _ltype[eax+1] & _DIGIT or _LABEL
	mov byte ptr [esi-1],'_'
    .endw
    ;
    ; first character can't be a digit either
    ;
    .if ModuleInfo._name <= '9' && ModuleInfo._name >= '0'

	mov ModuleInfo._name,'_'
    .endif
    ret
get_module_name endp

ModuleInit proc private

    mov eax,Options.sub_format
    mov ModuleInfo.sub_format,al
    mov eax,Options.output_format
    mov ecx,sizeof(format_options)
    mul ecx
    lea eax,formatoptions[eax]
    mov ModuleInfo.fmtopt,eax

    xor eax,eax
    .if Options.output_format == OFORMAT_OMF && !Options.no_comment_in_code_rec

	inc eax
    .endif

    mov ModuleInfo.CommentDataInCode,al
    mov ModuleInfo.error_count,0
    mov ModuleInfo.warning_count,0
    mov ModuleInfo._model,MODEL_NONE
    mov ModuleInfo.ostype,OPSYS_DOS
    mov ModuleInfo.emulator,0

    .if Options.floating_point == FPO_EMULATION

	inc ModuleInfo.emulator
    .endif

    get_module_name()

    mov edx,edi
    lea edi,SymTables
    mov ecx,sizeof(symbol_queue) * TAB_LAST
    xor eax,eax
    rep stosb
    mov edi,edx

    push offset ModuleInfo
    mov	 eax,ModuleInfo.fmtopt
    call [eax].format_options.init
    add	 esp,4
    ret
ModuleInit endp

ReswTableInit proc private
    ResWordsInit()
    .if Options.output_format == OFORMAT_OMF

	DisableKeyword(T_IMAGEREL)
	DisableKeyword(T_SECTIONREL)
    .endif
    .if Options.strict_masm_compat == 1

	DisableKeyword(T_INCBIN)
	DisableKeyword(T_FASTCALL)
    .endif
    .if !(Options.aflag & _AF_ON)
	;
	; added v2.22 - HSE
	;
	push ebx
	mov  ebx,T_DOT_IFA
	.repeat
	    DisableKeyword(ebx)
	    add ebx,1
	.until ebx > T_DOT_ENDSW
	pop ebx
    .endif
    ret

ReswTableInit endp

open_files proc private

    .if !fopen(ModuleInfo.curr_fname[ASM*4], "rb")
	;
	; will not return..
	;
	asmerr(1000, ModuleInfo.curr_fname[ASM*4])
    .endif
    mov ModuleInfo.curr_file[ASM*4],eax
    .if !Options.syntax_check_only
	.if !fopen(ModuleInfo.curr_fname[OBJ*4], "wb")
	    asmerr(1000, ModuleInfo.curr_fname[OBJ*4])
	.endif
	mov ModuleInfo.curr_file[OBJ*4],eax
    .endif
    .if Options.write_listing
	.if !fopen(ModuleInfo.curr_fname[LST*4],"wb")
	    asmerr(1000, ModuleInfo.curr_fname[LST*4])
	.endif
	mov ModuleInfo.curr_file[LST*4],eax
    .endif
    ret

open_files endp

close_files proc uses ebx

    ; v2.11: no fatal errors anymore if fclose() fails.
    ; That's because Fatal() may cause close_files() to be
    ; reentered and thus cause an endless loop.

    mov eax,ModuleInfo.curr_file[ASM*4]
    .if eax

	.if fclose(eax)

	    asmerr(3021, ModuleInfo.curr_fname[ASM*4])
	.endif
    .endif

    mov eax,ModuleInfo.curr_file[OBJ*4]
    .if eax
	.if fclose(eax)

	    asmerr(3021, ModuleInfo.curr_fname[OBJ*4])
	.endif
    .endif

    .if ( ( !Options.syntax_check_only && ModuleInfo.error_count ) || remove_obj )

	mov remove_obj,0
	remove(ModuleInfo.curr_fname[OBJ*4])
    .endif

    mov eax,ModuleInfo.curr_file[LST*4]
    .if eax

	fclose(eax)
	mov ModuleInfo.curr_file[LST*4],0
    .endif

    mov eax,ModuleInfo.curr_file[ERR*4]
    .if eax

	fclose(eax)
	mov ModuleInfo.curr_file[ERR*4],0
    .elseif ModuleInfo.curr_fname[ERR*4]

	remove(ModuleInfo.curr_fname[ERR*4])
    .endif
    ret

close_files endp

;
; get default file extension for error, object and listing files
;
GetExt proc private ftype

    mov ecx,ftype
    .if ecx == OBJ && Options.output_format == OFORMAT_BIN

	mov ecx,4
	.if Options.sub_format == SFORMAT_MZ || \
	    Options.sub_format == SFORMAT_PE || \
	    Options.sub_format == SFORMAT_64BIT
	    inc ecx
	.endif
    .endif
    mov ecx,filetypes[ecx*4]
    lea eax,currentftype
    mov [eax],ecx
    ret

GetExt endp

;; set filenames for .obj, .lst and .err
;; in:
;;  name: assembly source name
;;  DefaultDir[]: default directory part for .obj, .lst and .err
;; in:
;;  CurrFName[] for .obj, .lst and .err ( may be NULL )
;; v2.12: _splitpath()/_makepath() removed.

SetFilenames proc private uses esi edi ebx fn
  local path[260]:byte

    strlen(fn)
    inc eax
    strcpy(LclAlloc(eax), fn)
    mov ModuleInfo.curr_fname[ASM*4],eax
    GetFNamePart(eax)
    mov esi,eax
    mov edi,ASM+1
    lea ebx,path
    .while edi < NUM_FILE_TYPES

	mov eax,Options.names[edi*4]
	.if !eax
	    mov byte ptr [ebx],0
	    mov eax,DefaultDir[edi*4]
	    .if eax
		strcpy(ebx, eax)
	    .endif
	    GetExtPart(strcat(ebx, esi))
	    @@:
	    push eax
	    GetExt(edi)
	    pop ecx
	    strcpy(ecx, eax)
	.else
	    ;
	    ; filename has been set by cmdline option -Fo, -Fl or -Fr
	    ;
	    strcpy(ebx, eax)
	    GetFNamePart(ebx)
	    .if byte ptr [eax] == 0
		strcpy(eax, esi)
	    .endif
	    GetExtPart(eax)
	    cmp byte ptr [eax],0
	    je	@B
	.endif
	strlen(ebx)
	inc eax
	strcpy(LclAlloc(eax), ebx)
	mov ModuleInfo.curr_fname[edi*4],eax
	inc edi
    .endw
    ret
SetFilenames endp

AssembleInit proc private source
    MemInit()
    mov write_to_file,0
    mov LinnumQueue.head,0
    SetFilenames(source)
    FastpassInit()
    open_files()
    ReswTableInit()
    SymInit()
    InputInit()
    ModuleInit()
    CondInit()
    ExprEvalInit()
    LstInit()
    ret
AssembleInit endp

AssembleFini proc private
    SegmentFini()
    ResWordsFini()
    mov ModuleInfo.PubQueue.head,0
    InputFini()
    close_files()
    xor eax,eax
    mov ecx,NUM_FILE_TYPES
    .repeat
	mov ModuleInfo.curr_fname[ecx*4-4],eax
    .untilcxz
    MemFini()
    ret
AssembleFini endp

RewindToWin64 proc

    .if !( Options.output_format == OFORMAT_BIN && Options.sub_format == SFORMAT_NONE )

	.if ( Options.output_format != OFORMAT_BIN )
	    mov Options.output_format,OFORMAT_COFF
	.else
	    mov Options.langtype,LANG_FASTCALL
	.endif
	mov Options.sub_format,SFORMAT_64BIT
	mov remove_obj,1
	longjmp( &jmpenv, 1 )
    .endif
    ret

RewindToWin64 endp

AssembleModule proc uses esi edi ebx source

  local curr_written, prev_written

    xor eax,eax
    mov MacroLocals,eax
    mov ModuleInfo.StrStack,eax ; reset string label counter
    lea edi,ModuleInfo
    mov ecx,sizeof(ModuleInfo)
    rep stosb
    dec eax
    mov prev_written,eax

    .if !Options.quiet

	printf(" Assembling: %s\n", source)
    .endif

    .if _setjmp(&jmpenv)

	.if eax == 1

	    ClearSrcStack()
	    AssembleFini()
	    xor eax,eax
	    mov MacroLocals,eax
	    lea edi,ModuleInfo
	    mov ecx,sizeof(ModuleInfo)
	    rep stosb
	    dec eax
	    mov prev_written,eax
	.else

	    .if ModuleInfo.src_stack

		ClearSrcStack()
	    .endif
	    jmp done
	.endif
    .endif

    AssembleInit( source )
    mov Parse_Pass,PASS_1

    .while 1

	OnePass()

	xor eax,eax
	.break .if ModuleInfo.error_count > eax

	;
	; calculate total size of segments
	;
	mov curr_written,eax
	mov esi,SymTables[TAB_SEG*sizeof(symbol_queue)].head
	.while esi

	    mov eax,[esi].asym.max_offset
	    add curr_written,eax
	    mov esi,[esi].nsym.next
	.endw
	;
	; if there's no phase error and size of segments didn't change, we're done
	;
	mov eax,curr_written
	.break	.if !ModuleInfo.PhaseError && eax == prev_written
	mov prev_written,eax

	mov eax,Parse_Pass
	.if eax >= 199

	    asmerr( 3000, eax )
	.endif

	.if Options.line_numbers

	    .if Options.output_format == OFORMAT_COFF

		mov esi,SymTables[TAB_SEG*8].head
		.while	esi
		    mov ebx,[esi].nsym.seginfo
		    .if [ebx].seg_info.LinnumQueue
			QueueDeleteLinnum( [ebx].seg_info.LinnumQueue )
		    .endif
		    mov [ebx].seg_info.LinnumQueue,0
		    mov esi,[esi].nsym.next
		.endw
	    .else
		QueueDeleteLinnum( &LinnumQueue )
		mov LinnumQueue.head,0
	    .endif
	.endif

	rewind( ModuleInfo.curr_file[ASM*4] )
	.if write_to_file && Options.output_format == OFORMAT_OMF
	    omf_set_filepos()
	.endif

	.if !UseSavedState && ModuleInfo.curr_file[LST*4]
	    rewind( ModuleInfo.curr_file[LST*4] )
	    LstInit()
	.endif

	inc Parse_Pass
    .endw

    .if Parse_Pass > PASS_1 && write_to_file

	WriteModule(&ModuleInfo)
    .endif

    LstWriteCRef()
done:
    AssembleFini()

    xor eax,eax
    cmp ModuleInfo.error_count,eax
    jne toend
    inc eax
toend:
    ret
AssembleModule endp

    END
