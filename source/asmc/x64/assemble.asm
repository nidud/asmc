; ASSEMBLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include io.inc
include setjmp.inc

include asmc.inc
include parser.inc
include segment.inc
include reswords.inc
include types.inc
include omf.inc
include mangle.inc
include input.inc
include lqueue.inc
include context.inc
include hll.inc
include macro.inc
include assume.inc
include tokenize.inc
include memalloc.inc
include linnum.inc
include bin.inc
include coff.inc
include elf.inc
include fastpass.inc
include condasm.inc
include label.inc
include proc.inc
include expreval.inc
include listing.inc

public  jmpenv

extern  MacroLocals:dword

ifdef __UNIX__
define OBJ_EXT <'o.'>
else
define OBJ_EXT <'jbo.'>
endif

.template conv_section
    len         dd ?
    flags       dd ?
    src         string_t ?
    dst         string_t ?
   .ends


.data?
ModuleInfo      module_info <>
LinnumQueue     qdesc <>
jmpenv          _JUMP_BUFFER <>

.data

Parse_Pass      dd 0
write_to_file   dd 0

cp_text1        db "_TEXT",0
ifdef ASMC64
cp_text2        db ".text$mn",0
else
cp_text2        db ".text",0
endif
cp_data1        db "_DATA",0
cp_data2        db ".data",0
cp_const        db "CONST",0
cp_rdata        db ".rdata",0
cp_bss1         db "_BSS",0
cp_bss2         db ".bss",0

    align 8

formatoptions   label format_options
format_options  <bin_init,  0000h, <"BIN",0,0,0>>
format_options  <omf_init,  0000h, <"OMF",0,0,0>>
format_options  <coff_init, 0E12h, <"COFF", 0,0>>
format_options  <elf_init,  0F00h, <"ELF",0,0,0>>

cst conv_section \
        { 5, CSF_GRPCHK, cp_text1, cp_text2 },
        { 5, CSF_GRPCHK, cp_data1, cp_data2 },
        { 5, CSF_GRPCHK, cp_const, cp_rdata },
        { 4,          0, cp_bss1,  cp_bss2 }

stt             db SEGTYPE_CODE,SEGTYPE_DATA,SEGTYPE_DATA,SEGTYPE_BSS
filetypes       dd 'msa.',OBJ_EXT,'tsl.','rre.','nib.','exe.'
currentftype    dd 0,0
remove_obj      dd 0

.code

; translate section names (COFF+PE):
; _TEXT -> .text
; _DATA -> .data
; CONST -> .rdata
; _BSS   -> .bss

ConvertSectionName proc __ccall uses rsi rdi rbx r12 sym:ptr asym, pst:ptr dword, buffer:string_t

    assume rbx:ptr conv_section

    .for ( rbx = &cst, rdi = sym, esi = 0 : esi < 4 : rbx += conv_section )

        inc esi
        mov r12d,[rbx].len

        .if !tmemcmp( [rdi].asym.name, [rbx].src, r12d )

            add r12,[rdi].asym.name
            mov al,[r12]
            .continue .if al && ( al != '$' || [rbx].flags & CSF_GRPCHK )

            mov rcx,pst
            .if rcx

                mov rax,[rdi].dsym.seginfo
                .if !( esi == CSI_BSS + 1 && [rax].seg_info.bytes_written )
                    ;
                    ; don't set segment type to BSS if the segment
                    ; contains initialized data
                    ;
                    lea rax,stt
                    movzx eax,byte ptr [rax+rsi-1]
                    mov [rcx],eax
                .endif
            .endif
            mov rax,[rbx].dst
            .if byte ptr [r12]

                tstrcat(tstrcpy(buffer, rax), r12)
            .endif
            .return
        .endif
    .endf
    assume rbx:nothing

    mov rax,sym
    mov rax,[rax].asym.name
    ret

ConvertSectionName endp

;
; Write a byte to the segment buffer.
; in OMF, the segment buffer is flushed when the max. record size is reached.
;

MAX_LEDATA_THRESHOLD equ 1024 - 10

OutputByte proc __ccall uses rsi rdi rbx char:int_t

    mov rsi,ModuleInfo.currseg
    mov rdi,[rsi].dsym.seginfo

    .if write_to_file

        mov ebx,[rdi].seg_info.current_loc
        sub ebx,[rdi].seg_info.start_loc

        .if Options.output_format == OFORMAT_OMF && ebx >= MAX_LEDATA_THRESHOLD

            omf_FlushCurrSeg()

            mov ebx,[rdi].seg_info.current_loc
            sub ebx,[rdi].seg_info.start_loc
        .endif

        mov eax,char
        mov rcx,[rdi].seg_info.CodeBuffer
        mov [rcx+rbx],al

    .else

        mov eax,[rdi].seg_info.current_loc
        .if eax < [rdi].seg_info.start_loc

            mov [rdi].seg_info.start_loc,eax
        .endif
    .endif

    inc [rdi].seg_info.current_loc
    inc [rdi].seg_info.bytes_written
    mov [rdi].seg_info.written,1
    mov eax,[rdi].seg_info.current_loc

    .if eax > [rsi].dsym.max_offset

        mov [rsi].dsym.max_offset,eax
    .endif
    ret
OutputByte endp

FillDataBytes proc __ccall uses rsi char:byte, len:int_t
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

OutputBytes proc __ccall uses rsi rdi rbx pbytes:ptr byte, len:int_t, fxptr:ptr fixup

    mov rsi,ModuleInfo.currseg
    mov rdi,[rsi].dsym.seginfo

    .if write_to_file

        mov ebx,[rdi].seg_info.current_loc
        sub ebx,[rdi].seg_info.start_loc
        add edx,ebx

        .if Options.output_format == OFORMAT_OMF && edx >= MAX_LEDATA_THRESHOLD

            omf_FlushCurrSeg()

            mov ebx,[rdi].seg_info.current_loc
            sub ebx,[rdi].seg_info.start_loc
        .endif

        .if fxptr
            store_fixup(fxptr, rsi, pbytes)
        .endif

        mov rdx,rdi
        mov rax,rsi
        mov rdi,[rdi].seg_info.CodeBuffer
        add rdi,rbx
        mov ecx,len
        mov rsi,pbytes
        rep movsb
        mov rdi,rdx
        mov rsi,rax
    .else
        mov eax,[rdi].seg_info.current_loc
        .if eax < [rdi].seg_info.start_loc
            mov [rdi].seg_info.start_loc,eax
        .endif
    .endif

    mov eax,len
    add [rdi].seg_info.current_loc,eax
    add [rdi].seg_info.bytes_written,eax
    mov [rdi].seg_info.written,1
    mov eax,[rdi].seg_info.current_loc
    .if eax > [rsi].dsym.max_offset
        mov [rsi].dsym.max_offset,eax
    .endif
    ret
OutputBytes endp

;
; set current offset in a segment (usually CurrSeg) without to write anything
;
SetCurrOffset proc __ccall uses rsi rdi rbx dseg:dsym_t, value:uint_t, relative:int_t, select_data:int_t

    mov ebx,edx
    mov rsi,rcx
    mov eax,r8d
    mov ecx,write_to_file
    mov rdi,[rsi].dsym.seginfo

    .if eax
        add ebx,[rdi].seg_info.current_loc
    .endif
    .if Options.output_format == OFORMAT_OMF
        .if rsi == ModuleInfo.currseg
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
        mov [rdi].seg_info.start_loc,ebx
    .elseif !ecx && !eax && ![rdi].seg_info.bytes_written
        ;
        ; if there's an ORG (relative==false) and no initialized data
        ; has been set yet, set start_loc!
        ;
        mov [rdi].seg_info.start_loc,ebx
    .endif
    mov [rdi].seg_info.current_loc,ebx
    mov [rdi].seg_info.written,0
    mov eax,[rdi].seg_info.current_loc
    .if eax > [rsi].dsym.max_offset
        mov [rsi].dsym.max_offset,eax
    .endif
    mov eax,NOT_ERROR
    ret
SetCurrOffset endp

;
; write object module
;
ifdef __UNIX__
WriteModule proc __ccall private uses rsi rdi r12 r13 rbx modinfo:ptr module_info
else
WriteModule proc __ccall private uses r12 r13 rbx modinfo:ptr module_info
endif
    mov r12,SymTables[TAB_SEG*symbol_queue].head
    .while r12
        mov rax,[r12].dsym.seginfo
        .if [rax].seg_info.Ofssize == USE16 && [r12].dsym.max_offset > 10000h
            .if Options.output_format == OFORMAT_OMF
                asmerr( 2103, [r12].dsym.name )
            .endif
        .endif
        mov r12,[r12].dsym.next
    .endw

    modinfo.WriteModule(modinfo)

    mov r13,Options.names[OPTN_LNKDEF_FN*8]
    .if r13
        .if !fopen(r13, "w")
            asmerr(3020, r13)
        .else
            mov r13,rax
            mov r12,SymTables[TAB_EXT*symbol_queue].head
            .while r12
                mov rbx,[r12].asym.dll
                .if ( [r12].asym.flag1 & S_ISPROC && rbx && [rbx].dll_desc.name &&
                      ( !( [r12].asym.sflags & S_WEAK) || [r12].asym.flags & S_IAT_USED ) )

                    Mangle(r12, ModuleInfo.stringbufferend)
                    tsprintf(ModuleInfo.currsource, "import '%s'  %s.%s\n",
                        ModuleInfo.stringbufferend,
                        &[rbx].dll_desc.name, [r12].asym.name)
                    mov ebx,eax
                    .if fwrite(ModuleInfo.currsource, 1, ebx, r13) != rbx
                        WriteError()
                    .endif
                .endif
                mov r12,[r12].dsym.next
            .endw
            fclose(r13)
        .endif
    .endif
    .return( NOT_ERROR )

WriteModule endp

add_cmdline_tmacros proc __ccall private uses r13 r14 rbx r12

    mov r14,Options.queues[OPTQ_MACRO*8]
    .while r14
        lea r13,[r14].qitem.value
        .if !tstrchr(r13, '=')
            tstrlen(r13)
            lea rbx,[r13+rax]
        .else
            mov rbx,rax
            mov r12,rbx
            sub r12,r13
            inc r12
            tmemcpy(alloca(r12d), r13, r12d)
            mov byte ptr [rax+r12-1],0
            inc rbx
            mov r13,rax
        .endif

        xor ecx,ecx
        .if ( !is_valid_first_char( [r13] ) )
            inc ecx
        .else
            .for ( rdx = &[r13+1], al = [rdx] : eax: rdx++, al = [rdx] )
                .if ( !is_valid_id_char( eax ) )
                    inc ecx
                    .break
                .endif
            .endf
        .endif
        .if ecx
            asmerr(2008, r13)
            .break
        .endif

        .if !SymFind(r13)
            SymCreate(r13)
            mov [rax].asym.state,SYM_TMACRO
        .endif
        .if [rax].asym.state != SYM_TMACRO
            asmerr(2005, r13)
            .break
        .endif
        or  [rax].asym.flags,S_ISDEFINED or S_PREDEFINED
        mov [rax].asym.string_ptr,rbx
        mov r14,[r14].qitem.next
    .endw
    ret

add_cmdline_tmacros endp

add_incpaths proc __ccall private uses rsi

    mov rsi,Options.queues[OPTQ_INCPATH*8]
    .while rsi
        AddStringToIncludePath(&[rsi].qitem.value)
        mov rsi,[rsi].qitem.next
    .endw
    ret

add_incpaths endp

ifdef __UNIX__
CmdlParamsInit proc __ccall private uses rsi rdi pass:int_t
else
CmdlParamsInit proc __ccall private pass:int_t
endif
    .if ecx == PASS_1

        add_cmdline_tmacros()
        add_incpaths()

        .if !Options.ignore_include

            .if getenv("INCLUDE")

                AddStringToIncludePath(rax)
            .endif
        .endif
    .endif
    ret

CmdlParamsInit endp

WritePreprocessedLine proc __ccall string:string_t
    .data
    PrintEmptyLine db 1
    .code
    .if ModuleInfo.token_count > 0
        .while islspace( [rcx] )
            inc rcx
        .endw
        .if eax == '%'
            inc rcx
        .else
            mov rcx,string
        .endif
        tprintf("%s\n", rcx)
        mov PrintEmptyLine,1
    .elseif PrintEmptyLine
        mov PrintEmptyLine,0
        tprintf("\n")
    .endif
    ret
WritePreprocessedLine endp

SetMasm510 proc __ccall value:int_t

    mov eax,ecx
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

ModulePassInit proc __ccall private uses rsi

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

ifndef ASMC64
        .if ModuleInfo.sub_format == SFORMAT_64BIT
endif
            ;
            ; v2.06: force cpu to be at least P_64, without side effect to Options.cpu
            ;
            .if eax < P_64  ; enforce cpu to be 64-bit

                mov ecx,P_64 or P_PM ; added v2.32.41 for asmc -win64
            .endif
            ;
            ; ignore -m switch for 64-bit formats.
            ; there's no other model than FLAT possible.
            ;
            mov esi,MODEL_FLAT
            .if ModuleInfo.langtype == LANG_NONE
                ;
                ; v2.27.38: asmc -pe -win64
                ;           asmc -win64 -pe
                ;           asmc64 -pe
                ;
                .if Options.output_format == OFORMAT_COFF || \
                    Options.output_format == OFORMAT_BIN
                    mov ModuleInfo.langtype,LANG_FASTCALL
                .elseif Options.output_format == OFORMAT_ELF
                    mov ModuleInfo.langtype,LANG_SYSCALL
                .endif
            .endif
ifndef ASMC64
        .else
            ;
            ; if model FLAT is to be set, ensure that cpu is compat.
            ;
            .if esi == MODEL_FLAT && eax < P_386    ; cpu < 386?

                mov ecx,P_386
            .endif
        .endif
endif
        SetCPU(ecx)
        ;
        ; table ModelToken starts with MODEL_TINY, which is index 1"
        ;
ifndef ASMC64
        .if esi != MODEL_NONE
            lea rcx,ModelToken
            mov r8,[rcx+rsi*8-8]
            AddLineQueueX("%r %s", T_DOT_MODEL, r8)
        .endif
endif
    .endif

    movzx eax,Options.masm51_compat
    SetMasm510(eax)
ifndef ASMC64
    mov ModuleInfo.defOfssize,USE16
else
    mov ModuleInfo.defOfssize,USE64
endif
    mov ModuleInfo.ljmp,1
    mov ModuleInfo.list,Options.write_listing
    mov ModuleInfo.cref,1
    mov ModuleInfo.listif,Options.listif
    mov ModuleInfo.list_generated_code,Options.list_generated_code
    mov ModuleInfo.list_macro,Options.list_macro
    mov ModuleInfo.case_sensitive,Options.case_sensitive
    mov ModuleInfo.convert_uppercase,Options.convert_uppercase
    SymSetCmpFunc()
    mov ModuleInfo.segorder,SEGORDER_SEQ;
    mov ModuleInfo.radix,10
    mov ModuleInfo.fieldalign,Options.fieldalign
    mov ModuleInfo.procalign,0
    mov al,ModuleInfo.xflag
    and al,OPT_LSTRING
    or  al,Options.xflag
    mov ModuleInfo.xflag,al
    mov ModuleInfo.loopalign,Options.loopalign
    mov ModuleInfo.casealign,Options.casealign
    mov ModuleInfo.codepage,Options.codepage
    mov ModuleInfo.epilogueflags,Options.epilogueflags
    mov ModuleInfo.win64_flags,Options.win64_flags
    mov ModuleInfo.strict_masm_compat,Options.strict_masm_compat
    mov ModuleInfo.frame_auto,Options.frame_auto
    mov ModuleInfo.floatformat,Options.floatformat
    mov ModuleInfo.floatdigits,Options.floatdigits
    mov ModuleInfo.flt_size,Options.flt_size

    ;
    ; if OPTION DLLIMPORT was used, reset all iat_used flags
    ;
    .if ModuleInfo.DllQueue

        mov rax,SymTables[TAB_EXT*symbol_queue].head
        .while rax

            and [rax].asym.flags,not S_IAT_USED
            mov rax,[rax].dsym.next
        .endw
    .endif
    ret
ModulePassInit endp
;
; checks after pass one has been finished without errors
;
PassOneChecks proc __ccall private uses rsi rdi
    ;
    ; check for open structures and segments has been done inside the
    ; END directive handling already
    ;
    ; v2.10: now done for PROCs as well, since procedures
    ; must be closed BEFORE segments are to be closed.
    ;
    HllCheckOpen()
    CondCheckOpen()
    ClassCheckOpen()
    PragmaCheckOpen()

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
    lea rdx,ModuleInfo.PubQueue
    mov rcx,[rdx].qdesc.head
    .while rcx
        mov rax,[rcx].qnode.sym
        .if [rax].asym.state == SYM_INTERNAL

            mov rdx,rcx
        .elseif [rax].asym.state == SYM_EXTERNAL && [rax].asym.sflags & S_WEAK

            mov rax,[rcx].qnode.next
            mov [rdx].qnode.next,rax
            mov rcx,rdx
        .else
            mov UseSavedState,0
            jmp aliases
        .endif
        mov rcx,[rcx].qnode.next
    .endw
    ;
    ; check if there's an undefined segment reference.
    ; This segment was an argument to a group definition then.
    ; Just do a full second pass, the GROUP directive will report
    ; the error.
    ;
    mov rax,SymTables[TAB_SEG*symbol_queue].head
    .while rax
        .if ![rax].asym.segm

            mov UseSavedState,0
            jmp aliases
        .endif
        mov rax,[rax].dsym.next
    .endw
    ;
    ; if there's an item in the safeseh list which is not an
    ; internal proc, make a full second pass to emit a proper
    ; error msg at the .SAFESEH directive
    ;
    mov rax,ModuleInfo.SafeSEHQueue.head
    .while rax
        .if [rax].asym.state != SYM_INTERNAL || !( [rax].asym.flag1 & S_ISPROC )

            mov UseSavedState,0
            jmp aliases
        .endif
        mov rax,[rax].dsym.next
    .endw
aliases:
    ;
    ; scan ALIASes for COFF/ELF
    ;
    .if Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF

        mov rcx,SymTables[TAB_ALIAS*symbol_queue].head
        .while rcx
            mov rax,[rcx].asym.substitute
            ;
            ; check if symbol is external or public
            ;
            .if !rax || [rax].asym.state != SYM_EXTERNAL \
                && ( [rax].asym.state != SYM_INTERNAL || !( [rax].asym.flags & S_ISPUBLIC ) )

                mov UseSavedState,0
                .break
            .endif
            ;
            ; make sure it becomes a strong external
            ;
            .if [rax].asym.state == SYM_EXTERNAL

                or [rax].asym.flags,S_USED
            .endif
            mov rcx,[rcx].dsym.next
        .endw
    .endif
    ;
    ; scan the EXTERN/EXTERNDEF items
    ;
    mov rdi,SymTables[TAB_EXT*symbol_queue].head
    .while rdi
        mov rsi,rdi
        mov rdi,[rsi].dsym.next
        .if [rsi].asym.flags & S_USED

            and [rsi].asym.sflags,not S_WEAK
        .endif
        .if [rsi].asym.sflags & S_WEAK && !([rsi].asym.flags & S_IAT_USED)
            ;
            ; remove unused EXTERNDEF/PROTO items from queue.
            ;
            sym_remove_table(&SymTables[TAB_EXT*symbol_queue], rsi)
            .continue
        .endif
        .continue .if [rsi].asym.sflags & S_ISCOM
        ;
        ; optional alternate symbol must be INTERNAL or EXTERNAL. COFF (and ELF?)
        ; also wants internal symbols to be public (which is reasonable, since
        ; the linker won't know private symbols and hence will search for a symbol
        ; of that name "elsewhere").
        ;
        mov rax,[rsi].asym.altname
        .if rax

            .if [rax].asym.state == SYM_INTERNAL

                .if !( [rax].asym.flags & S_ISPUBLIC ) && \
                    ( Options.output_format == OFORMAT_COFF || \
                      Options.output_format == OFORMAT_ELF)

                    SkipSavedState()
                .endif
            .elseif [rax].asym.state != SYM_EXTERNAL

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
            ModuleInfo.Pass1Checks(&ModuleInfo)
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
OnePass proc __ccall private uses rsi rdi

    InputPassInit()
    ModulePassInit()
    SymPassInit(Parse_Pass)
    LabelInit()
    SegmentInit(Parse_Pass)
    ContextInit(Parse_Pass)
    ProcInit()
    TypesInit()
    HllInit(Parse_Pass)
    ClassInit()
    PragmaInit()
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
        mov LineStoreCurr,rax
        mov rsi,rax

        .while rsi && !ModuleInfo.EndDirFound

            set_curr_srcfile([rsi].line_item.srcfile, [rsi].line_item.lineno)

            mov ModuleInfo.line_flags,0
            mov MacroLevel,[rsi].line_item.macro_level
            mov ModuleInfo.CurrComment,0
            Tokenize(&[rsi].line_item.line, 0, ModuleInfo.tokenarray, TOK_DEFAULT)
            mov ModuleInfo.token_count,eax
            .if eax

                ParseLine(ModuleInfo.tokenarray)
            .endif
            mov rsi,[rsi].line_item.next
            mov LineStoreCurr,rsi
        .endw
    .else
        mov rsi,Options.queues[OPTQ_FINCLUDE*8]
        .while rsi
            lea rax,[rsi].qitem.value
            mov rsi,[rsi].qitem.next
            .if SearchFile(rax, 1)

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

get_module_name proc __ccall private uses rsi rdi

    mov rsi,Options.names[OPTN_MODULE_NAME*8]
    .if rsi

        tstrncpy( &ModuleInfo.name, rsi, sizeof(ModuleInfo.name))
        mov ModuleInfo.name[sizeof(ModuleInfo.name)-1],0
    .else
        GetFNamePart(ModuleInfo.curr_fname[ASM*8])
        mov rsi,rax
        .if GetExtPart(rax) == rsi
            tstrlen(rsi)
            add rax,rsi
        .endif
        sub rax,rsi
        lea rcx,ModuleInfo.name
        mov byte ptr [rcx+rax],0
        tmemcpy(rcx, rsi, eax)
    .endif
    ;
    ; the module name must be a valid identifier, because it's used
    ; as part of a segment name in certain memory models.
    ;
    lea rsi,ModuleInfo.name
    tstrupr(rsi)
    xor eax,eax
    .while 1
        lodsb
        .break  .if !al
        .continue .if is_valid_id_char( eax )
        mov byte ptr [rsi-1],'_'
    .endw
    ;
    ; first character can't be a digit either
    ;
    .if ModuleInfo.name <= '9' && ModuleInfo.name >= '0'

        mov ModuleInfo.name,'_'
    .endif
    ret

get_module_name endp

ModuleInit proc __ccall private

    mov eax,Options.sub_format
    mov ModuleInfo.sub_format,al
    mov eax,Options.output_format
    mov ecx,format_options
    mul ecx
    lea rdx,formatoptions
    add rax,rdx
    mov ModuleInfo.fmtopt,rax

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

    mov rdx,rdi
    lea rdi,SymTables
    mov ecx,symbol_queue * TAB_LAST
    xor eax,eax
    rep stosb
    mov rdi,rdx

    lea rcx,ModuleInfo
    mov rax,ModuleInfo.fmtopt
    call [rax].format_options.init
    ret

ModuleInit endp

ifdef OLDKEYWORDS

MASMKEYW        STRUC
token           dw ?
oldlen          db ?
newlen          db ?
oldname         string_t ?
newname         string_t ?
MASMKEYW        ENDS

res macro token, oldlen, newlen, oldname, newname
    exitm<MASMKEYW { token, oldlen, newlen, @CStr("&oldname"), @CStr("&newname") }>
    endm

    .data

masmkeyw label MASMKEYW
include oldkeyw.inc
OLDKCOUNT equ ($ - masmkeyw) / sizeof(MASMKEYW)

    .code

    assume r12:ptr MASMKEYW

MasmKeywords proc __ccall private uses rbx r12 disable:int_t

    lea r12,masmkeyw
    .if ( ecx == 0 )
        .for( ebx = 0: ebx < OLDKCOUNT: ebx++ )
            imul ecx,ebx,sizeof(MASMKEYW)
            RenameKeyword( [r12+rcx].token, [r12+rcx].oldname, [r12+rcx].oldlen )
        .endf
    .else
        .for( ebx = 0: ebx < OLDKCOUNT: ebx++ )
            imul ecx,ebx,sizeof(MASMKEYW)
            RenameKeyword( [r12+rcx].token, [r12+rcx].newname, [r12+rcx].newlen )
        .endf
    .endif
    ret

MasmKeywords endp

    assume r12:nothing

endif

EnableKeyword proto __ccall :uint_t

AsmcKeywords proc __ccall uses rbx enable:int_t

    .if ( ecx == 0 )
        .for ( ebx = T_DOT_IFA : ebx <= T_DOT_ENDSW : ebx++ )
            DisableKeyword(ebx)
        .endf
    .else
        .for ( ebx = T_DOT_IFA : ebx <= T_DOT_ENDSW : ebx++ )
            EnableKeyword(ebx)
        .endf
    .endif
ifdef OLDKEYWORDS
    MasmKeywords(enable)
endif
    ret

AsmcKeywords endp

ReswTableInit proc __ccall private uses rbx

    ResWordsInit()
    .if ( Options.output_format == OFORMAT_OMF )
        DisableKeyword(T_IMAGEREL)
        DisableKeyword(T_SECTIONREL)
    .endif
    .if ( Options.strict_masm_compat == 1 )
        DisableKeyword(T_INCBIN)
        DisableKeyword(T_FASTCALL)
        AsmcKeywords(0)
    .elseif ( Options.masm_keywords == 1 )
        MasmKeywords(0)
    .endif
    ret

ReswTableInit endp

ifdef __UNIX__
open_files proc __ccall private uses rsi rdi
else
open_files proc __ccall private
endif
    .if !fopen(ModuleInfo.curr_fname[ASM*8], "rb")
        ;
        ; will not return..
        ;
        asmerr(1000, ModuleInfo.curr_fname[ASM*8])
    .endif
    mov ModuleInfo.curr_file[ASM*8],rax
    .if !Options.syntax_check_only
        .if !fopen(ModuleInfo.curr_fname[OBJ*8], "wb")
            asmerr(1000, ModuleInfo.curr_fname[OBJ*8])
        .endif
        mov ModuleInfo.curr_file[OBJ*8],rax
    .endif
    .if Options.write_listing
        .if !fopen(ModuleInfo.curr_fname[LST*8],"wb")
            asmerr(1000, ModuleInfo.curr_fname[LST*8])
        .endif
        mov ModuleInfo.curr_file[LST*8],rax
    .endif
    ret

open_files endp

ifdef __UNIX__
close_files proc __ccall uses rsi rdi
else
close_files proc __ccall
endif
    ; v2.11: no fatal errors anymore if fclose() fails.
    ; That's because Fatal() may cause close_files() to be
    ; reentered and thus cause an endless loop.

    mov rax,ModuleInfo.curr_file[ASM*8]
    .if rax

        .if fclose(rax)

            asmerr(3021, ModuleInfo.curr_fname[ASM*8])
        .endif
    .endif

    mov rax,ModuleInfo.curr_file[OBJ*8]
    .if rax
        .if fclose(rax)

            asmerr(3021, ModuleInfo.curr_fname[OBJ*8])
        .endif
    .endif

    .if ( ( !Options.syntax_check_only && ModuleInfo.error_count ) || remove_obj )

        mov remove_obj,0
        remove(ModuleInfo.curr_fname[OBJ*8])
    .endif

    mov rax,ModuleInfo.curr_file[LST*8]
    .if rax

        fclose(rax)
        mov ModuleInfo.curr_file[LST*8],0
    .endif

    mov rax,ModuleInfo.curr_file[ERR*8]
    .if rax

        fclose(rax)
        mov ModuleInfo.curr_file[ERR*8],0
    .elseif ModuleInfo.curr_fname[ERR*8]

        remove(ModuleInfo.curr_fname[ERR*8])
    .endif
    ret

close_files endp

;
; get default file extension for error, object and listing files
;
GetExt proc fastcall private ftype:int_t

    .if ecx == OBJ && Options.output_format == OFORMAT_BIN

        mov ecx,4
        .if Options.sub_format == SFORMAT_MZ || \
            Options.sub_format == SFORMAT_PE || \
            Options.sub_format == SFORMAT_64BIT
            inc ecx
        .endif
    .endif
    lea rax,filetypes
    mov ecx,[rax+rcx*4]
    lea rax,currentftype
    mov [rax],ecx
    ret

GetExt endp

; set filenames for .obj, .lst and .err
; in:
;  name: assembly source name
;  DefaultDir[]: default directory part for .obj, .lst and .err
; in:
;  CurrFName[] for .obj, .lst and .err ( may be NULL )
; v2.12: _splitpath()/_makepath() removed.

SetFilenames proc __ccall private uses rsi rdi rbx r12 fn:string_t

  local path[260]:byte

    mov ModuleInfo.curr_fname[ASM*8],LclDup(rcx)
    GetFNamePart(rax)
    mov rsi,rax
    mov edi,ASM+1
    lea rbx,path
    .while rdi < NUM_FILE_TYPES

        lea rax,Options
        mov rax,[rax].global_options.names[rdi*8]
        .if !rax
            mov byte ptr [rbx],0
            lea rcx,DefaultDir
            mov rax,[rcx+rdi*8]
            .if rax
                tstrcpy(rbx, rax)
            .endif
            GetExtPart(tstrcat(rbx, rsi))
            @@:
            mov r12,rax
            GetExt(edi)
            tstrcpy(r12, rax)
        .else
            ;
            ; filename has been set by cmdline option -Fo, -Fl or -Fr
            ;
            tstrcpy(rbx, rax)
            GetFNamePart(rbx)
            .if byte ptr [rax] == 0
                tstrcpy(rax, rsi)
            .endif
            GetExtPart(rax)
            cmp byte ptr [rax],0
            je  @B
        .endif
        LclDup(rbx)
        lea rcx,ModuleInfo
        mov [rcx].module_info.curr_fname[rdi*8],rax
        inc edi
    .endw
    ret

SetFilenames endp

AssembleInit proc __ccall private source:string_t

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

AssembleFini proc __ccall private

    SegmentFini()
    ResWordsFini()
    mov ModuleInfo.PubQueue.head,0
    InputFini()
    close_files()
    xor eax,eax
    mov ecx,NUM_FILE_TYPES
    lea rdx,ModuleInfo.curr_fname
    .repeat
        mov [rdx+rcx*8-8],rax
    .untilcxz
    MemFini()
    ret
AssembleFini endp

AssembleModule proc __ccall uses rsi rdi rbx source:string_t

  local curr_written, prev_written

    xor eax,eax
    mov MacroLocals,eax
    mov ModuleInfo.StrStack,rax ; reset string label counter
    lea rdi,ModuleInfo
    mov ecx,sizeof(ModuleInfo)
    rep stosb
    mov ModuleInfo.radix,10
    dec eax
    mov prev_written,eax

    .if !Options.quiet

        tprintf(" Assembling: %s\n", source)
    .endif

    .if _setjmp(&jmpenv)

        .if eax == 1

            ClearSrcStack()
            AssembleFini()
            xor eax,eax
            mov MacroLocals,eax
            lea rdi,ModuleInfo
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
        mov rsi,SymTables[TAB_SEG*symbol_queue].head
        .while rsi

            mov eax,[rsi].asym.max_offset
            add curr_written,eax
            mov rsi,[rsi].dsym.next
        .endw
        ;
        ; if there's no phase error and size of segments didn't change, we're done
        ;
        mov eax,curr_written
        .break  .if !ModuleInfo.PhaseError && eax == prev_written
        mov prev_written,eax

        .if Parse_Pass >= 199

            asmerr( 3000, 200 )
        .endif

        .if Options.line_numbers

            .if Options.output_format == OFORMAT_COFF

                mov rsi,SymTables[TAB_SEG*symbol_queue].head
                .while  rsi
                    mov rbx,[rsi].dsym.seginfo
                    .if rbx
                        .if [rbx].seg_info.LinnumQueue
                            QueueDeleteLinnum( [rbx].seg_info.LinnumQueue )
                        .endif
                        mov [rbx].seg_info.LinnumQueue,0
                    .endif
                    mov rsi,[rsi].dsym.next
                .endw
            .else
                QueueDeleteLinnum( &LinnumQueue )
                mov LinnumQueue.head,0
            .endif
        .endif

        rewind( ModuleInfo.curr_file[ASM*8] )
        .if write_to_file && Options.output_format == OFORMAT_OMF
            omf_set_filepos()
        .endif

        .if !UseSavedState && ModuleInfo.curr_file[LST*8]
            rewind( ModuleInfo.curr_file[LST*8] )
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
   .return( false ) .if ModuleInfo.error_count
   .return( true )

AssembleModule endp

    END
