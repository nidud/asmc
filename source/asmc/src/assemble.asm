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

define USELSLINE 1 ; must match switch in listing.asm!

public  jmpenv
extern  MacroLocals:dword

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
iddcfile        db 256 dup(?)

.data

Parse_Pass      dd 0
write_to_file   dd 0

cp_text1        db "_TEXT",0
if not defined(__UNIX__) and defined(ASMC64)
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

    align size_t

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
currentftype    dd 0,0
remove_obj      dd 0

.code

; translate section names (COFF+PE):
; _TEXT -> .text
; _DATA -> .data
; CONST -> .rdata
; _BSS   -> .bss

ConvertSectionName proc __ccall uses rsi rdi rbx sym:ptr asym, pst:ptr dword, buffer:string_t

    assume rbx:ptr conv_section

    .for ( rbx = &cst, rdi = sym, esi = 0 : esi < 4 : rbx += conv_section )

        inc esi

        .if !tmemcmp( [rdi].asym.name, [rbx].src, [rbx].len )

            mov edx,[rbx].len
            add rdx,[rdi].asym.name
            mov al,[rdx]
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
            .if byte ptr [rdx]
                mov rbx,rdx
                tstrcat( tstrcpy( buffer, rax ), rbx )
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

    mov rsi,MODULE.currseg
    mov rdi,[rsi].dsym.seginfo

    .if ( write_to_file )

        mov ebx,[rdi].seg_info.current_loc
        sub ebx,[rdi].seg_info.start_loc

        .if ( Options.output_format == OFORMAT_OMF && ebx >= MAX_LEDATA_THRESHOLD )

            omf_FlushCurrSeg()

            mov ebx,[rdi].seg_info.current_loc
            sub ebx,[rdi].seg_info.start_loc
        .endif

        mov eax,char
        mov rcx,[rdi].seg_info.CodeBuffer
        mov [rcx+rbx],al

    .else

        mov eax,[rdi].seg_info.current_loc
        .if ( eax < [rdi].seg_info.start_loc )

            mov [rdi].seg_info.start_loc,eax
        .endif
    .endif

    inc [rdi].seg_info.current_loc
    inc [rdi].seg_info.bytes_written
    mov [rdi].seg_info.written,1
    mov eax,[rdi].seg_info.current_loc

    .if ( eax > [rsi].dsym.max_offset )

        mov [rsi].dsym.max_offset,eax
    .endif
    ret
OutputByte endp


FillDataBytes proc __ccall char:byte, len:int_t

    .if ( MODULE.CommentDataInCode )
        omf_OutSelect(1)
    .endif
    .while len
        OutputByte(char)
        dec len
    .endw
    ret

FillDataBytes endp


OutputBytes proc __ccall uses rsi rdi rbx pbytes:ptr byte, len:int_t, fxptr:ptr fixup

    mov rsi,MODULE.currseg
    mov rdi,[rsi].dsym.seginfo

    .if ( write_to_file )

        mov ebx,[rdi].seg_info.current_loc
        sub ebx,[rdi].seg_info.start_loc
        ldr edx,len
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

    ldr ebx,value
    ldr rsi,dseg
    ldr eax,relative
    mov ecx,write_to_file
    mov rdi,[rsi].dsym.seginfo

    .if eax
        add ebx,[rdi].seg_info.current_loc
    .endif
    .if Options.output_format == OFORMAT_OMF
        .if rsi == MODULE.currseg
            .if ecx
                omf_FlushCurrSeg()
            .endif
            ;
            ; for debugging, tell if data is located in code sections
            ;
            .if select_data && MODULE.CommentDataInCode
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
    .return(NOT_ERROR)

SetCurrOffset endp

;
; write object module
;
WriteModule proc private uses rsi rdi rbx

    mov rbx,SymTables[TAB_SEG*symbol_queue].head

    .while rbx

        mov rax,[rbx].dsym.seginfo

        .if ( [rax].seg_info.Ofssize == USE16 && [rbx].dsym.max_offset > 0x10000 )

            .if Options.output_format == OFORMAT_OMF

                asmerr( 2103, [rbx].dsym.name )
            .endif
        .endif
        mov rbx,[rbx].dsym.next
    .endw

    MODULE.WriteModule()

    mov rbx,Options.names[OPTN_LNKDEF_FN*string_t]
    .if rbx

        .if !fopen( rbx, "w" )

            asmerr( 3020, rbx )

        .else

           .new fp:ptr FILE = rax

            mov rbx,SymTables[TAB_EXT*symbol_queue].head

            .while rbx

                mov rcx,[rbx].asym.dll
                .if ( [rbx].asym.flags & S_ISPROC && rcx && [rcx].dll_desc.name &&
                      ( !( [rbx].asym.sflags & S_WEAK) || [rbx].asym.flags & S_IAT_USED ) )

                    Mangle(rbx, StringBufferEnd)

                    mov rcx,[rbx].asym.dll
                    tsprintf(CurrSource, "import '%s'  %s.%s\n",
                        StringBufferEnd,
                        &[rcx].dll_desc.name, [rbx].asym.name)

                    .new len:uint_t = eax

                    fwrite( CurrSource, 1, len, fp )

                    .if ( len != eax )

                        WriteError()
                    .endif
                .endif
                mov rbx,[rbx].dsym.next
            .endw
            fclose(fp)
        .endif
    .endif
    .return( NOT_ERROR )

WriteModule endp


is_valid_first_char proto watcall c:byte {
    retm<( al == '.' || islabel(eax) )>
    }


add_cmdline_tmacros proc __ccall private uses rsi rdi rbx

    mov rsi,Options.queues[OPTQ_MACRO*string_t]

    .while rsi

        lea rdi,[rsi].qitem.value
        .if !tstrchr( rdi, '=' )

            tstrlen( rdi )
            lea rbx,[rdi+rax]
        .else

           .new len:int_t
            mov rbx,rax
            mov rax,rbx
            sub rax,rdi
            inc eax
            mov len,eax
            tmemcpy(alloca(len), rdi, len)
            mov ecx,len
            mov byte ptr [rax+rcx-1],0
            inc rbx
            mov rdi,rax
        .endif

        xor ecx,ecx
        .if ( !is_valid_first_char( [rdi] ) )
            inc ecx
        .else
            .for ( rdx = &[rdi+1], al = [rdx] : eax: rdx++, al = [rdx] )
                .if ( !islabel( eax ) )
                    inc ecx
                    .break
                .endif
            .endf
        .endif
        .if ecx
            asmerr( 2008, rdi )
            .break
        .endif

        .if !SymFind( rdi )

            SymCreate( rdi )
            mov [rax].asym.state,SYM_TMACRO
        .endif

        .if ( [rax].asym.state != SYM_TMACRO )

            asmerr( 2005, rdi )
           .break
        .endif
        or  [rax].asym.flags,S_ISDEFINED or S_PREDEFINED
        mov [rax].asym.string_ptr,rbx
        mov rsi,[rsi].qitem.next
    .endw
    ret

add_cmdline_tmacros endp


add_incpaths proc __ccall private uses rsi

    mov rsi,Options.queues[OPTQ_INCPATH*string_t]
    .while rsi
        AddStringToIncludePath(&[rsi].qitem.value)
        mov rsi,[rsi].qitem.next
    .endw
    ret

add_incpaths endp


CmdlParamsInit proc __ccall private pass:int_t

    .if ( ldr(pass) == PASS_1 )

        add_cmdline_tmacros()
        add_incpaths()

        .if !Options.ignore_include

            .if tgetenv("INCLUDE")

                AddStringToIncludePath(rax)
            .endif
        .endif
    .endif
    ret

CmdlParamsInit endp


    .data
     PrintEmptyLine db 1

    .code

WritePreprocessedLine proc __ccall string:string_t

    .if ( TokenCount > 0 )

        ldr rcx,string
        .while islspace( [rcx] )
            inc rcx
        .endw
        .if ( eax == '%' )
            inc rcx
        .else
            mov rcx,string
        .endif

        tprintf( "%s\n", rcx )
        mov PrintEmptyLine,1

    .elseif PrintEmptyLine

        mov PrintEmptyLine,0
        tprintf("\n")
    .endif
    ret

WritePreprocessedLine endp


SetMasm510 proc __ccall value:int_t

    ldr eax,value

    mov MODULE.m510,al
    mov MODULE.oldstructs,al
    mov MODULE.dotname,al
    mov MODULE.setif2,al

    .if ( eax && MODULE._model == MODEL_NONE )

        ;
        ; if no model is specified, set OFFSET:SEGMENT
        ;
        mov MODULE.offsettype,OT_SEGMENT

        .if ( MODULE.langtype == LANG_NONE )

            mov MODULE.scoped,0
            mov MODULE.procs_private,0
        .endif
    .endif
    ret

SetMasm510 endp

    assume rdi:ptr global_options

ModulePassInit proc __ccall private uses rsi rdi rbx

    lea rdi,Options

    mov ecx,[rdi].cpu
    mov esi,[rdi]._model
    ;
    ; set default values not affected by the masm 5.1 compat switch
    ;
    mov MODULE.procs_private,0
    mov MODULE.procs_export,0
    mov MODULE.offsettype,OT_GROUP
    mov MODULE.scoped,1
ifdef ASMC64
    mov MODULE.accumulator,T_RAX
else
    mov MODULE.accumulator,T_AX
endif

    .if ( !UseSavedState )

        mov eax,[rdi].langtype
        mov MODULE.langtype,al
        mov eax,[rdi].fctype
        mov MODULE.fctype,al
        mov eax,ecx
        and eax,P_CPU_MASK

ifndef ASMC64
        .if ( MODULE.sub_format == SFORMAT_64BIT )
endif
            ;
            ; v2.06: force cpu to be at least P_64, without side effect to Options.cpu
            ;
            .if ( eax < P_64 ) ; enforce cpu to be 64-bit

                mov ecx,P_64 or P_PM ; added v2.32.41 for asmc -win64
            .endif
            ;
            ; ignore -m switch for 64-bit formats.
            ; there's no other model than FLAT possible.
            ;
            mov esi,MODEL_FLAT
            .if ( MODULE.langtype == LANG_NONE )
                ;
                ; v2.27.38: asmc -pe -win64
                ;           asmc -win64 -pe
                ;           asmc64 -pe
                ;
                .if ( [rdi].output_format == OFORMAT_COFF || [rdi].output_format == OFORMAT_BIN )
                    mov MODULE.langtype,LANG_FASTCALL
                .elseif ( [rdi].output_format == OFORMAT_ELF )
                    mov MODULE.langtype,LANG_SYSCALL
                .endif
            .endif
ifndef ASMC64
        .else
            ;
            ; if model FLAT is to be set, ensure that cpu is compat.
            ;
            .if ( esi == MODEL_FLAT && eax < P_386 ) ; cpu < 386?

                mov ecx,P_386
            .endif
        .endif
endif
        SetCPU( ecx )
        ;
        ; table ModelToken starts with MODEL_TINY, which is index 1"
        ;
ifndef ASMC64
        .if ( esi != MODEL_NONE )

            lea rcx,ModelToken
            mov rcx,[rcx+rsi*string_t-string_t]
            AddLineQueueX( "%r %s", T_DOT_MODEL, rcx )
        .endif
endif
    .endif

    movzx eax,[rdi].masm51_compat
    SetMasm510( eax )
ifndef ASMC64
    mov MODULE.defOfssize,USE16
else
    mov MODULE.defOfssize,USE64
endif
    mov MODULE.ljmp,1
    mov MODULE.list,[rdi].write_listing
    mov MODULE.cref,1
    mov MODULE.listif,[rdi].listif
    mov MODULE.list_generated_code,[rdi].list_generated_code
    mov MODULE.list_macro,[rdi].list_macro
    mov MODULE.case_sensitive,[rdi].case_sensitive
    mov MODULE.convert_uppercase,[rdi].convert_uppercase
    SymSetCmpFunc()
    mov MODULE.segorder,SEGORDER_SEQ
    mov MODULE.radix,10
    mov MODULE.fieldalign,[rdi].fieldalign
    mov MODULE.procalign,0
    mov al,MODULE.xflag
    and al,OPT_LSTRING
    or  al,[rdi].xflag
    mov MODULE.xflag,al
    mov MODULE.loopalign,[rdi].loopalign
    mov MODULE.casealign,[rdi].casealign
    mov MODULE.codepage,[rdi].codepage
    mov MODULE.win64_flags,[rdi].win64_flags
    mov MODULE.frame_auto,[rdi].frame_auto
    mov MODULE.floatformat,[rdi].floatformat
    mov MODULE.floatdigits,[rdi].floatdigits
    mov MODULE.flt_size,[rdi].flt_size
    mov MODULE.pic,[rdi].pic
    mov MODULE.endbr,[rdi].endbr
    mov MODULE.dotname,[rdi].dotname
    mov MODULE.dotnamex,[rdi].dotnamex
    mov MODULE.sysvregs,[rdi].sysvregs
    mov MODULE.masm_compat_gencode,[rdi].masm_compat_gencode
    mov MODULE.avxencoding,0

    ;
    ; if OPTION DLLIMPORT was used, reset all iat_used flags
    ;
    .if ( MODULE.DllQueue )

        mov rax,SymTables[TAB_EXT*symbol_queue].head
        .while rax

            and [rax].asym.flags,not S_IAT_USED
            mov rax,[rax].dsym.next
        .endw
    .endif
    ret

ModulePassInit endp

    assume rdi:nothing

; checks after pass one has been finished without errors

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

    .if ( !MODULE.EndDirFound )

        asmerr( 2088 )
    .endif

    ; v2.04: check the publics queue.
    ; - only internal symbols can be public.
    ; - weak external symbols are filtered ( since v2.11 )
    ; - anything else is an error
    ; v2.11: moved here ( from inside the "#if FASTPASS"-block )
    ; because the loop will now filter weak externals [ this
    ; was previously done in GetPublicSymbols() ]
    ;

    lea rdx,MODULE.PubQueue
    mov rcx,[rdx].qdesc.head

    .while rcx

        mov rax,[rcx].qnode.sym
        .if ( [rax].asym.state == SYM_INTERNAL )

            mov rdx,rcx
        .elseif ( [rax].asym.state == SYM_EXTERNAL && [rax].asym.sflags & S_WEAK )

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
    mov rax,MODULE.SafeSEHQueue.head
    .while rax
        .if [rax].asym.state != SYM_INTERNAL || !( [rax].asym.flags & S_ISPROC )

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
            .if ( !rax || [rax].asym.state != SYM_EXTERNAL
                && ( [rax].asym.state != SYM_INTERNAL || !( [rax].asym.flags & S_ISPUBLIC ) ) )

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
        .if ( [rsi].asym.flags & S_USED )

            and [rsi].asym.sflags,not S_WEAK
        .endif
        .if ( [rsi].asym.sflags & S_WEAK && !( [rsi].asym.flags & S_IAT_USED ) )
            ;
            ; remove unused EXTERNDEF/PROTO items from queue.
            ;
            sym_remove_table( &SymTables[TAB_EXT*symbol_queue], rsi )
            .continue
        .endif
        .continue .if ( [rsi].asym.sflags & S_ISCOM )
        ;
        ; optional alternate symbol must be INTERNAL or EXTERNAL. COFF (and ELF?)
        ; also wants internal symbols to be public (which is reasonable, since
        ; the linker won't know private symbols and hence will search for a symbol
        ; of that name "elsewhere").
        ;
        mov rax,[rsi].asym.altname
        .if rax

            .if ( [rax].asym.state == SYM_INTERNAL )

                .if ( !( [rax].asym.flags & S_ISPUBLIC ) &&
                     ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF ) )

                    SkipSavedState()
                .endif
            .elseif ( [rax].asym.state != SYM_EXTERNAL )

                mov UseSavedState,0
            .endif
        .endif
    .endw

    .if ( !MODULE.error_count )
        ;
        ; make all symbols of type SYM_INTERNAL, which aren't
        ; a constant, public.
        ;
        .if ( Options.all_symbols_public )

            SymMakeAllSymbolsPublic()
        .endif

        .if ( !Options.syntax_check_only )

            mov write_to_file,1
        .endif

        .if ( MODULE.Pass1Checks )
            MODULE.Pass1Checks()
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
    mov MODULE.EndDirFound,al
    mov MODULE.PhaseError,al
    LinnumInit()
    .if ( MODULE.line_queue.head )
        RunLineQueue()
    .endif

    mov StoreState,0
    .if ( Parse_Pass > PASS_1 && UseSavedState == 1 )

        RestoreState()
        mov LineStoreCurr,rax
        mov rsi,rax

        .while ( rsi && !MODULE.EndDirFound )

if ( USELSLINE eq 0 )
            tstrcpy( CurrSource, &[rsi].line_item.line )
endif
            set_curr_srcfile([rsi].line_item.srcfile, [rsi].line_item.lineno)
            mov MODULE.line_flags,0
            mov MacroLevel,[rsi].line_item.macro_level
            mov CurrComment,0
if USELSLINE
            .ifd ( Tokenize( &[rsi].line_item.line, 0, TokenArray, TOK_DEFAULT ) )
else
            .ifd ( Tokenize( CurrSource, 0, TokenArray, TOK_DEFAULT ) )
endif
                mov TokenCount,eax
                ParseLine(TokenArray)
            .endif
            mov rsi,[rsi].line_item.next
            mov LineStoreCurr,rsi
        .endw

    .else

        mov rsi,Options.queues[OPTQ_FINCLUDE*size_t]
        .while rsi
            lea rax,[rsi].qitem.value
            mov rsi,[rsi].qitem.next
            .if SearchFile(rax, 1)

                ProcessFile(TokenArray)
            .endif
        .endw
        ProcessFile(TokenArray)
    .endif

    LinnumFini()
    .if ( Parse_Pass == PASS_1 )
        PassOneChecks()
    .endif
    ClearSrcStack()
   .return(1)

OnePass endp


get_module_name proc __ccall private uses rsi rdi

    mov rsi,Options.names[OPTN_MODULE_NAME*string_t]
    .if rsi

        tstrncpy( &MODULE.name, rsi, sizeof(ModuleInfo.name) )
        mov MODULE.name[sizeof(ModuleInfo.name)-1],0

    .else

        GetFNamePart( MODULE.curr_fname[ASM*string_t] )
        mov rsi,rax
        .if ( GetExtPart( rax ) == rsi )
            tstrlen(rsi)
            add rax,rsi
        .endif
        sub rax,rsi
        lea rcx,MODULE.name
        mov byte ptr [rcx+rax],0
        tmemcpy( rcx, rsi, eax )
    .endif
    ;
    ; the module name must be a valid identifier, because it's used
    ; as part of a segment name in certain memory models.
    ;
    lea rsi,MODULE.name
    tstrupr( rsi )
    xor eax,eax
    .while 1
        lodsb
        .break .if !al
        .continue .if islabel( eax )
        mov byte ptr [rsi-1],'_'
    .endw
    ;
    ; first character can't be a digit either
    ;
    .if ( MODULE.name <= '9' && MODULE.name >= '0' )

        mov MODULE.name,'_'
    .endif
    ret

get_module_name endp


ModuleInit proc private

    mov eax,Options.sub_format
    mov MODULE.sub_format,al
    mov eax,Options.output_format
    mov ecx,format_options
    mul ecx
    lea rdx,formatoptions
    add rax,rdx
    mov MODULE.fmtopt,rax
   .new fm:ptr format_options = rax

    xor eax,eax
    .if ( Options.output_format == OFORMAT_OMF && !Options.no_comment_in_code_rec )
        inc eax
    .endif

    mov MODULE.CommentDataInCode,al
    mov MODULE.error_count,0
    mov MODULE.warning_count,0
    mov MODULE._model,MODEL_NONE
    mov MODULE.ostype,OPSYS_DOS
    mov MODULE.emulator,0

    .if ( Options.floating_point == FPO_EMULATION )
        inc MODULE.emulator
    .endif

    get_module_name()

    mov rdx,rdi
    lea rdi,SymTables
    mov ecx,symbol_queue * TAB_LAST
    xor eax,eax
    rep stosb
    mov rdi,rdx

    fm.init()
    ret

ModuleInit endp


ReswTableInit proc __ccall private

    ResWordsInit()
    .if ( Options.output_format == OFORMAT_OMF )

        DisableKeyword( T_IMAGEREL )
        DisableKeyword( T_SECTIONREL )
    .endif
    .if ( Options.strict_masm_compat == 0 )

        DisableKeyword( T_NAME )
        DisableKeyword( T_TITLE )
        DisableKeyword( T_PAGE )
        DisableKeyword( T_SIZE )
        DisableKeyword( T_LENGTH )
        DisableKeyword( T_THIS )
        DisableKeyword( T_MASK )
        DisableKeyword( T_WIDTH )
        DisableKeyword( T_TYPE )
        DisableKeyword( T_HIGH )
        DisableKeyword( T_LOW )
    .endif
    ret

ReswTableInit endp


open_files proc __ccall private uses rsi rdi

    .if !fopen( MODULE.curr_fname[ASM*string_t], "rb" )
        ;
        ; will not return..
        ;
        asmerr( 1000, MODULE.curr_fname[ASM*string_t] )
    .endif
    mov MODULE.curr_file[ASM*string_t],rax

    .if ( !Options.syntax_check_only )

        .if !fopen( MODULE.curr_fname[OBJ*string_t], "wb" )

            asmerr( 1000, MODULE.curr_fname[OBJ*string_t] )
        .endif
        mov MODULE.curr_file[OBJ*string_t],rax
    .endif
    .if ( Options.write_listing )
        .if !fopen( MODULE.curr_fname[LST*string_t],"wb" )
            asmerr( 1000, MODULE.curr_fname[LST*string_t] )
        .endif
        mov MODULE.curr_file[LST*string_t],rax
    .endif
    ret

open_files endp

iddc_file proc __ccall private uses rsi rdi rbx source:string_t

   .new iddc[260]:byte
   .new file:string_t
   .new fp:ptr FILE

    mov rbx,tstrcpy(&iddc, GetFNamePart( ldr(source) ) )

    .if ( GetExtPart( rbx ) == rbx )

        tstrcat( rax, ".s" )
    .else
        tstrcpy( rax, ".s" )
    .endif
    mov file,tstrcpy( &iddcfile, rbx )
    .if ( fopen( rax, "wb" ) == NULL )
        asmerr( 1000, file )
    .endif
    mov fp,rax
    GetExtPart( rbx )
    mov byte ptr [rax],0

    tfprintf( fp,
        "public IDD_%s\n"
        ".data\n"
        "PIDD typedef ptr\n"
        "IDD_%s PIDD %s_RC\n"
        "%s_RC label byte\n"
        "incbin <%s>\n",
        rbx, rbx, rbx, rbx, source)
    .if ( Options.iddc == 2 )
        tfprintf( fp, "db 0\n" )
    .endif
    tfprintf( fp, "end\n" )
    fclose(fp)
   .return( file )

iddc_file endp

close_files proc __ccall uses rsi rdi

    ; v2.11: no fatal errors anymore if fclose() fails.
    ; That's because Fatal() may cause close_files() to be
    ; reentered and thus cause an endless loop.

    mov rax,MODULE.curr_file[ASM*string_t]
    .if rax

        .if fclose( rax )

            asmerr( 3021, MODULE.curr_fname[ASM*string_t] )
        .endif
    .endif

    mov rax,MODULE.curr_file[OBJ*string_t]
    .if rax
        .if fclose( rax )

            asmerr( 3021, MODULE.curr_fname[OBJ*string_t] )
        .endif
    .endif

    .if ( ( !Options.syntax_check_only && MODULE.error_count ) || remove_obj )

        mov remove_obj,0
        remove( MODULE.curr_fname[OBJ*string_t] )
    .endif

    mov rax,MODULE.curr_file[LST*string_t]
    .if rax

        fclose( rax )
        mov MODULE.curr_file[LST*string_t],0
    .endif

    mov rax,MODULE.curr_file[ERR*string_t]
    .if rax

        fclose( rax )
        mov MODULE.curr_file[ERR*string_t],0
    .elseif ( MODULE.curr_fname[ERR*string_t] )

        remove( MODULE.curr_fname[ERR*string_t] )
    .endif
    ret

close_files endp

;
; get default file extension for error, object and listing files
;
GetExt proc fastcall private ftype:int_t

    lea rax,currentftype
    mov edx,'msa.'
    .switch ecx
    .case OBJ
        mov edx,'jbo.'
        .if ( Options.output_format == OFORMAT_BIN )
            mov edx,'nib.'
            .if ( Options.sub_format == SFORMAT_MZ ||
                  Options.sub_format == SFORMAT_PE ||
                  Options.sub_format == SFORMAT_64BIT )
                mov edx,'exe.'
                .if ( Options.pe_dll )
                    mov edx,'lld.'
                .endif
            .endif
        .elseif ( Options.output_format == OFORMAT_ELF )
            and edx,0xFFFF
        .endif
        .endc
    .case LST
        mov edx,'tsl.'
        .endc
    .case ERR
        mov edx,'rre.'
        .endc
    .endsw
    mov [rax],edx
    ret

GetExt endp


; set filenames for .obj, .lst and .err
; in:
;  name: assembly source name
;  DefaultDir[]: default directory part for .obj, .lst and .err
; in:
;  CurrFName[] for .obj, .lst and .err ( may be NULL )
; v2.12: _splitpath()/_makepath() removed.

SetFilenames proc __ccall private uses rsi rdi rbx fn:string_t

   .new path[260]:byte

    mov MODULE.curr_fname[ASM*string_t],LclDup( ldr(fn) )

    mov rsi,GetFNamePart( rax )
    mov edi,ASM+1
    lea rbx,path

    .while ( rdi < NUM_FILE_TYPES )

        lea rax,Options
        mov rax,[rax].global_options.names[rdi*string_t]

        .if !rax

            mov byte ptr [rbx],0
            lea rcx,DefaultDir
            mov rax,[rcx+rdi*string_t]

            .if rax
                tstrcpy( rbx, rax )
            .endif
            GetExtPart( tstrcat( rbx, rsi ) )

            mov rbx,rax
            tstrcpy(rbx, GetExt( edi ) )
            lea rbx,path

        .else
            ;
            ; filename has been set by cmdline option -Fo, -Fl or -Fr
            ;

            GetFNamePart( tstrcpy( rbx, rax ) )
            .if byte ptr [rax] == 0
                tstrcpy( rax, rsi )
            .endif
            GetExtPart( rax )
            .if ( byte ptr [rax] == 0 )

                mov rbx,rax
                tstrcpy( rbx, GetExt( edi ) )
                lea rbx,path
            .endif
        .endif

        LclDup( rbx )
        lea rcx,ModuleInfo
        mov [rcx].module_info.curr_fname[rdi*string_t],rax
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
    mov MODULE.PubQueue.head,0
    InputFini()
    close_files()
    xor eax,eax
    mov ecx,NUM_FILE_TYPES
    lea rdx,MODULE.curr_fname
    .repeat
        mov [rdx+rcx*string_t-string_t],rax
    .untilcxz
    MemFini()
    ret

AssembleFini endp


AssembleModule proc __ccall uses rsi rdi rbx source:string_t

   .new curr_written:uint_t
   .new prev_written:uint_t

    xor eax,eax
    mov MacroLocals,eax
    mov MODULE.StrStack,rax ; reset string label counter
    lea rdi,ModuleInfo
    mov ecx,sizeof(ModuleInfo)
    rep stosb
    mov MODULE.radix,10
    dec eax
    mov prev_written,eax

    .if ( !Options.quiet )

        tprintf( " Assembling: %s\n", source )
    .endif

    .if _setjmp(&jmpenv)

        .if ( eax == 1 )

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

            .if ( MODULE.src_stack )

                ClearSrcStack()
            .endif
            jmp done
        .endif
    .endif

    .if ( Options.iddc )

        mov source,iddc_file( source )
    .endif

    AssembleInit( source )
    mov Parse_Pass,PASS_1

    .while 1

        OnePass()

        xor eax,eax
        .break .if ( MODULE.error_count > eax )

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
        .break .if ( !MODULE.PhaseError && eax == prev_written )

        mov prev_written,eax
        .if ( Parse_Pass >= 199 )

            asmerr( 3000, 200 )
        .endif

        .if ( Options.line_numbers )

            .if ( Options.output_format == OFORMAT_COFF )

                mov rsi,SymTables[TAB_SEG*symbol_queue].head

                .while rsi

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

        rewind( MODULE.curr_file[ASM*string_t] )
        .if ( write_to_file && Options.output_format == OFORMAT_OMF )
            omf_set_filepos()
        .endif

        inc Parse_Pass
        .if ( MODULE.curr_file[LST*string_t] )

            .if ( !UseSavedState )

                rewind( MODULE.curr_file[LST*string_t] )
                LstInit()

            .elseif ( Parse_Pass == PASS_2 && Options.first_pass_listing )

                LstInit()
            .endif
        .endif
    .endw

    .if ( Parse_Pass > PASS_1 && write_to_file )

        WriteModule()
    .endif
    LstWriteCRef()

done:

    AssembleFini()
    xor eax,eax
    .if ( eax == MODULE.error_count )
        inc eax
    .endif
    ret

AssembleModule endp

    END
