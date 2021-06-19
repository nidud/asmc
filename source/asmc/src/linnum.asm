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

AddLinnumData proc private uses esi edi ebx data:ptr line_num_info

    mov ebx,CurrSeg
    mov edi,[ebx].dsym.seginfo

    .if ( Options.output_format == OFORMAT_COFF )
        mov esi,[edi].seg_info.LinnumQueue
        .if ( esi == NULL )
            mov esi,LclAlloc( sizeof( qdesc ) )
            mov [edi].seg_info.LinnumQueue,esi
            mov [esi].qdesc.head,NULL
        .endif
    .else
        lea esi,LinnumQueue
    .endif
    mov edi,data
    mov [edi].line_num_info.next,NULL
    .if ( [esi].qdesc.head == NULL )
        mov [esi].qdesc.head,edi
        mov [esi].qdesc.tail,edi
    .else
        mov ecx,[esi].qdesc.tail
        mov [ecx].line_num_info.next,edi
        mov [esi].qdesc.tail,edi
    .endif
    ret

AddLinnumData endp

;; store a reference for the current line at the current address
;; called by
;; - codegen.output_opc()
;; - proc.ProcDir() - in COFF, line_num is 0 then

AddLinnumDataRef proc uses esi edi ebx srcfile:dword, line_num:dword

    ;; COFF line number info is related to functions/procedures. Since
    ;; assembly allows code lines outside of procs, "dummy" procs must
    ;; be generated. A dummy proc lasts until
    ;; - a true PROC is detected or
    ;; - the source file changes or
    ;; - the segment/section changes ( added in v2.11 )

    mov ebx,CurrProc
    mov esi,dmyproc
    .if ( esi )
        mov edi,[esi].asym.debuginfo
    .endif

    .if ( Options.output_format == OFORMAT_COFF && Options.debug_symbols != 4 && \
        ebx == NULL && ( esi == NULL || [edi].debug_info.file != srcfile || \
        [esi].asym.segm != CurrSeg ) )

        .new procname[12]:char_t
        .if ( esi )
            mov ecx,[esi].asym.segm
            mov ecx,[ecx].dsym.seginfo
            mov eax,[ecx].seg_info.current_loc
            sub eax,[esi].asym.offs
            mov [esi].asym.total_size,eax
        .endif
        sprintf( &procname, "$$$%05u", procidx )
        mov dmyproc,SymSearch( &procname )
        mov esi,eax
        ;; in pass 1, create the proc
        .if ( esi == NULL )
            mov dmyproc,CreateProc( NULL, &procname, SYM_INTERNAL )
            mov esi,eax
            or [esi].asym.flag1,S_ISPROC ;; flag is usually set inside ParseProc()
            or [esi].asym.flag1,S_INCLUDED
            AddPublicData( esi )
        .else
            inc procidx ;; for passes > 1, adjust procidx
        .endif

        ;; if the symbols isn't a PROC, the symbol name has been used
        ;; by the user - bad! A warning should be displayed

        .if ( [esi].asym.flag1 & S_ISPROC )
            SetSymSegOfs( esi )
            mov [esi].asym.Ofssize,ModuleInfo.Ofssize
            mov [esi].asym.langtype,ModuleInfo.langtype
            .if ( write_to_file == TRUE )
                mov edi,LclAlloc( sizeof( line_num_info ) )
                mov [edi].line_num_info.sym,esi
                mov [edi].line_num_info.line_number,GetLineNumber()
                mov eax,srcfile
                shl eax,20
                or [edi].line_num_info.line_number,eax
                mov [edi].line_num_info.number,0
                AddLinnumData( edi )
            .endif
        .endif
    .endif

    .return .if ( line_num && ( write_to_file == FALSE || lastLineNumber == line_num ) )

    mov edi,LclAlloc( sizeof( line_num_info ) )
    mov [edi].line_num_info.number,line_num
    .if ( line_num == 0 ) ;; happens for COFF only
        mov ecx,CurrProc
        .if ( Parse_Pass == PASS_1 && \
            Options.output_format == OFORMAT_COFF && ecx && !( [ecx].asym.flags & S_ISPUBLIC ) )
            or [ecx].asym.flag1,S_INCLUDED
            AddPublicData( ecx )
        .endif
        mov eax,dmyproc
        .if ( CurrProc )
            mov eax,CurrProc
        .endif
        mov [edi].line_num_info.sym,eax
        mov [edi].line_num_info.line_number,GetLineNumber()
        mov eax,srcfile
        shl eax,20
        or [edi].line_num_info.line_number,eax
        ;; set the function's size!
        mov esi,dmyproc
        .if ( esi )
            mov ecx,[esi].asym.segm
            mov ecx,[ecx].dsym.seginfo
            mov eax,[ecx].seg_info.current_loc
            sub eax,[esi].asym.offs
            mov [esi].asym.total_size,eax
            mov dmyproc,NULL
        .endif
        ;; v2.11: write a 0x7fff line item if prologue exists
        mov ecx,CurrProc
        mov edx,[ecx].dsym.procinfo
        .if ( ecx && [edx].proc_info.size_prolog )
            AddLinnumData( edi )
            mov edi,LclAlloc( sizeof( line_num_info ) )
            mov [edi].line_num_info.number,GetLineNumber()
            mov [edi].line_num_info.offs,GetCurrOffset()
            mov [edi].line_num_info.srcfile,srcfile
        .endif
    .else
        mov [edi].line_num_info.offs,GetCurrOffset()
        mov [edi].line_num_info.srcfile,srcfile
    .endif
    mov lastLineNumber,line_num

    ;; v2.11: added, improved multi source support for CV.
    ;; Also, the size of line number info could have become > 1024,
    ;; ( even > 4096, thus causing an "internal error in omfint.c" )

    .if ( Options.output_format == OFORMAT_OMF )
        omf_check_flush( edi )
    .endif

    ;; v2.10: warning if line-numbers for segments without class code!
    mov ebx,CurrSeg
    mov esi,[ebx].dsym.seginfo
    .if ( [esi].seg_info.linnum_init == FALSE )
        mov [esi].seg_info.linnum_init,TRUE
        .if ( TypeFromClassName( ebx, [esi].seg_info.clsym ) != SEGTYPE_CODE )
            asmerr( 4012, [ebx].asym.name )
        .endif
    .endif
    AddLinnumData( edi )

    ret
AddLinnumDataRef endp

QueueDeleteLinnum proc queue:ptr qdesc

    mov ecx,queue
    .if ( ecx != NULL )
        mov edx,[ecx].qdesc.head
        .for( : edx : edx = eax )
            mov eax,[edx].line_num_info.next
        .endf
    .endif
    ret

QueueDeleteLinnum endp

;; if -Zd is set and there is trailing code not inside
;; a function, set the dummy function's length now.

LinnumFini proc

    mov eax,dmyproc
    .if ( eax )
        mov ecx,[eax].asym.segm
        mov ecx,[ecx].dsym.seginfo
        mov edx,[ecx].seg_info.current_loc
        sub edx,[eax].asym.offs
        mov [eax].asym.total_size,edx
    .endif
    ret

LinnumFini endp

LinnumInit proc

    mov lastLineNumber,0
    mov dmyproc,NULL
    ret

LinnumInit endp

    end
