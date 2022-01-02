; LINNUM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: handles line numbers if -Zd or -Zi is set.
;

include time.inc
include asmc.inc
include memalloc.inc
include input.inc
include segment.inc
include proc.inc
include extern.inc
include linnum.inc
include omf.inc

externdef LinnumQueue:qdesc ; queue of line_num_info items ( OMF only )
externdef procidx:int_t

.data
dmyproc ptr asym 0
lastLineNumber uint_t 0

.code

AddLinnumData proc private uses rsi rdi rbx data:ptr line_num_info

    mov rbx,CurrSeg
    mov rdi,[rbx].dsym.seginfo

    .if ( Options.output_format == OFORMAT_COFF )
        mov rsi,[rdi].seg_info.LinnumQueue
        .if ( rsi == NULL )
            mov rsi,LclAlloc( sizeof( qdesc ) )
            mov [rdi].seg_info.LinnumQueue,rsi
            mov [rsi].qdesc.head,NULL
        .endif
    .else
        lea rsi,LinnumQueue
    .endif
    mov rdi,data
    mov [rdi].line_num_info.next,NULL
    .if ( [rsi].qdesc.head == NULL )
        mov [rsi].qdesc.head,rdi
        mov [rsi].qdesc.tail,rdi
    .else
        mov rcx,[rsi].qdesc.tail
        mov [rcx].line_num_info.next,rdi
        mov [rsi].qdesc.tail,rdi
    .endif
    ret

AddLinnumData endp

;; store a reference for the current line at the current address
;; called by
;; - codegen.output_opc()
;; - proc.ProcDir() - in COFF, line_num is 0 then

AddLinnumDataRef proc uses rsi rdi rbx srcfile:dword, line_num:dword

    ;; COFF line number info is related to functions/procedures. Since
    ;; assembly allows code lines outside of procs, "dummy" procs must
    ;; be generated. A dummy proc lasts until
    ;; - a true PROC is detected or
    ;; - the source file changes or
    ;; - the segment/section changes ( added in v2.11 )

    mov rbx,CurrProc
    mov rsi,dmyproc
    .if ( rsi )
        mov rdi,[rsi].asym.debuginfo
    .endif

    .if ( Options.output_format == OFORMAT_COFF && Options.debug_symbols != 4 &&
          rbx == NULL && ( rsi == NULL || [rdi].debug_info.file != srcfile ||
          [rsi].asym.segm != CurrSeg ) )

        .new procname[12]:char_t
        .if ( rsi )
            mov rcx,[rsi].asym.segm
            mov rcx,[rcx].dsym.seginfo
            mov eax,[rcx].seg_info.current_loc
            sub eax,[rsi].asym.offs
            mov [rsi].asym.total_size,eax
        .endif
        tsprintf( &procname, "$$$%05u", procidx )
        mov dmyproc,SymSearch( &procname )
        mov rsi,rax
        ;; in pass 1, create the proc
        .if ( rsi == NULL )
            mov dmyproc,CreateProc( NULL, &procname, SYM_INTERNAL )
            mov rsi,rax
            or [rsi].asym.flag1,S_ISPROC ;; flag is usually set inside ParseProc()
            or [rsi].asym.flag1,S_INCLUDED
            AddPublicData( rsi )
        .else
            inc procidx ;; for passes > 1, adjust procidx
        .endif

        ;; if the symbols isn't a PROC, the symbol name has been used
        ;; by the user - bad! A warning should be displayed

        .if ( [rsi].asym.flag1 & S_ISPROC )
            SetSymSegOfs( rsi )
            mov [rsi].asym.Ofssize,ModuleInfo.Ofssize
            mov [rsi].asym.langtype,ModuleInfo.langtype
            .if ( write_to_file == TRUE )
                mov rdi,LclAlloc( sizeof( line_num_info ) )
                mov [rdi].line_num_info.sym,rsi
                mov [rdi].line_num_info.line_number,GetLineNumber()
                mov eax,srcfile
                shl eax,20
                or [rdi].line_num_info.line_number,eax
                mov [rdi].line_num_info.number,0
                AddLinnumData( rdi )
            .endif
        .endif
    .endif

    .return .if ( line_num && ( write_to_file == FALSE || lastLineNumber == line_num ) )

    mov rdi,LclAlloc( sizeof( line_num_info ) )
    mov [rdi].line_num_info.number,line_num
    .if ( line_num == 0 ) ;; happens for COFF only
        mov rcx,CurrProc
        .if ( Parse_Pass == PASS_1 && \
            Options.output_format == OFORMAT_COFF && rcx && !( [rcx].asym.flags & S_ISPUBLIC ) )
            or [rcx].asym.flag1,S_INCLUDED
            AddPublicData( rcx )
        .endif
        mov rax,dmyproc
        .if ( CurrProc )
            mov rax,CurrProc
        .endif
        mov [rdi].line_num_info.sym,rax
        mov [rdi].line_num_info.line_number,GetLineNumber()
        mov eax,srcfile
        shl eax,20
        or [rdi].line_num_info.line_number,eax
        ;; set the function's size!
        mov rsi,dmyproc
        .if ( rsi )
            mov rcx,[rsi].asym.segm
            mov rcx,[rcx].dsym.seginfo
            mov eax,[rcx].seg_info.current_loc
            sub eax,[rsi].asym.offs
            mov [rsi].asym.total_size,eax
            mov dmyproc,NULL
        .endif
        ;; v2.11: write a 0x7fff line item if prologue exists
        mov rcx,CurrProc
        mov rdx,[rcx].dsym.procinfo
        .if ( ecx && [rdx].proc_info.size_prolog )
            AddLinnumData( rdi )
            mov rdi,LclAlloc( sizeof( line_num_info ) )
            mov [rdi].line_num_info.number,GetLineNumber()
            mov [rdi].line_num_info.offs,GetCurrOffset()
            mov [rdi].line_num_info.srcfile,srcfile
        .endif
    .else
        mov [rdi].line_num_info.offs,GetCurrOffset()
        mov [rdi].line_num_info.srcfile,srcfile
    .endif
    mov lastLineNumber,line_num

    ;; v2.11: added, improved multi source support for CV.
    ;; Also, the size of line number info could have become > 1024,
    ;; ( even > 4096, thus causing an "internal error in omfint.c" )

    .if ( Options.output_format == OFORMAT_OMF )
        omf_check_flush( rdi )
    .endif

    ;; v2.10: warning if line-numbers for segments without class code!
    mov rbx,CurrSeg
    mov rsi,[rbx].dsym.seginfo
    .if ( [rsi].seg_info.linnum_init == FALSE )
        mov [rsi].seg_info.linnum_init,TRUE
        .if ( TypeFromClassName( rbx, [rsi].seg_info.clsym ) != SEGTYPE_CODE )
            asmerr( 4012, [rbx].asym.name )
        .endif
    .endif
    AddLinnumData( rdi )
    ret

AddLinnumDataRef endp

QueueDeleteLinnum proc queue:ptr qdesc

    .if ( rcx != NULL )
        mov rdx,[rcx].qdesc.head
        .for( : rdx : rdx = rax )
            mov rax,[rdx].line_num_info.next
        .endf
    .endif
    ret

QueueDeleteLinnum endp

;; if -Zd is set and there is trailing code not inside
;; a function, set the dummy function's length now.

LinnumFini proc

    mov rax,dmyproc
    .if ( rax )
        mov rcx,[rax].asym.segm
        mov rcx,[rcx].dsym.seginfo
        mov edx,[rcx].seg_info.current_loc
        sub edx,[rax].asym.offs
        mov [rax].asym.total_size,edx
    .endif
    ret

LinnumFini endp

LinnumInit proc

    mov lastLineNumber,0
    mov dmyproc,NULL
    ret

LinnumInit endp

    end
