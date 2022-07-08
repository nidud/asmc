; LISTING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; listing support
;

include stdarg.inc
include malloc.inc

include asmc.inc
include memalloc.inc
include parser.inc
include reswords.inc
include segment.inc
include tokenize.inc
include macro.inc
include fastpass.inc
include listing.inc
include input.inc
include types.inc
include omfspec.inc

define CODEBYTES 9
define OFSSIZE 8
define PREFFMTSTR <"20"> ; v2.24 -- memory error: johnsa
define USELSLINE 1       ; also in assemble.asm!

ifdef __UNIX__
define NLSIZ 1
define NLSTR <"\n">
else
define NLSIZ 2
define NLSTR <"\r\n">
endif

externdef LastCodeBufSize:int_t
externdef basereg:special_token
externdef cp_logo:char_t

public list_pos

log_macro   proto __ccall :ptr asym
log_struct  proto __ccall :ptr asym, :ptr sbyte, :sdword
log_record  proto __ccall :ptr asym
log_typedef proto __ccall :ptr asym
log_segment proto __ccall :ptr asym, :ptr asym
log_group   proto __ccall :ptr asym, :ptr dsym
log_proc    proto __ccall :ptr asym

.data

list_pos uint_t 0 ; current pos in LST file

define DOTSMAX 32
dots db " . . . . . . . . . . . . . . . .",0

define szFmtProcStk <"  %s %s        %-17s %s %c %04X">

ltext macro index, string
  exitm<LS_&index&,>
  endm
.enumt list_strings : string_t {
include ltext.inc
}
undef ltext

ltext macro index, string
  exitm<string_t @CStr(string)>
  endm
strings label string_t
include ltext.inc
undef ltext

define szCount <"count">

;; cref definitions

.enum list_queues {
    LQ_MACROS,
    LQ_STRUCTS,
    LQ_RECORDS,
    LQ_TYPEDEFS,
    LQ_SEGS,
    LQ_GRPS,
    LQ_PROCS,
    LQ_LAST
    }

.enum pr_flags {
    PRF_ADDSEG = 0x01
    }

.template print_item
    type dw ?
    flags dw ?
    capitems ptr word ?
    function proc local __ccall :ptr asym, :ptr asym, :int_32
   .ends


maccap dw LS_TXT_MACROS,  LS_TXT_MACROCAP  ,0
strcap dw LS_TXT_STRUCTS, LS_TXT_STRUCTCAP, 0
reccap dw LS_TXT_RECORDS, LS_TXT_RECORDCAP, 0
tdcap  dw LS_TXT_TYPEDEFS,LS_TXT_TYPEDEFCAP, 0
segcap dw LS_TXT_SEGS,    LS_TXT_SEGCAP, 0
prccap dw LS_TXT_PROCS,   LS_TXT_PROCCAP, 0

cr print_item \
    { LQ_MACROS,          0, maccap, log_macro   },
    { LQ_STRUCTS,         0, strcap, log_struct  },
    { LQ_RECORDS,         0, reccap, log_record  },
    { LQ_TYPEDEFS,        0, tdcap,  log_typedef },
    { LQ_SEGS,            0, segcap, log_segment },
    { LQ_GRPS,   PRF_ADDSEG, NULL,   log_group   },
    { LQ_PROCS,           0, prccap, log_proc    }


.template lstleft
    next    ptr lstleft ?
    buffer  char_t 4*8 dup(?)
    last    char_t ?
   .ends

.code
;
; write a source line to the listing file
; global variables used inside:
;  CurrSource:    the - expanded - source line
;  CurrSeg:       current segment
;  GeneratedCode: flag if code is generated
;  MacroLevel:    macro depth
;

LstWrite proc __ccall uses rsi rdi rbx type:lsttype, oldofs:uint_t, value:ptr

   .new newofs:uint_t
   .new sym:ptr asym = value
   .new len:int_t
   .new len2:int_t
   .new idx:int_t
   .new srcfile:int_t
   .new p1:string_t
   .new p2:string_t
   .new pSrcline:string_t
   .new pll:ptr lstleft
   .new ll:lstleft

    .if ( ModuleInfo.list == FALSE || CurrFile[LST*size_t] == NULL ||
          ( ModuleInfo.line_flags & LOF_LISTED ) )
        .return
    .endif
    .if ( ModuleInfo.GeneratedCode && ( ModuleInfo.list_generated_code == FALSE ) )
        .return
    .endif

    .if ( MacroLevel )
        .switch ( ModuleInfo.list_macro )
        .case LM_NOLISTMACRO
            .return
        .case LM_LISTMACRO
            ; todo: filter certain macro lines
            .endc
        .endsw
    .endif

    or ModuleInfo.line_flags,LOF_LISTED
    mov pSrcline,CurrSource

    .if ( ( Parse_Pass > PASS_1 ) && UseSavedState )
        .if ( ModuleInfo.GeneratedCode == 0 )
            .if ( !( ModuleInfo.line_flags & LOF_SKIPPOS ) )
                mov list_pos,LineStoreCurr.get_pos()
            .endif
if USELSLINE
            ; either use CurrSource + CurrComment or LineStoreCurr->line
            ; (see assemble.asm, OnePass())

            mov pSrcline,LineStoreCurr.get_line()
            .if ( ModuleInfo.CurrComment ) ; if comment was removed, readd it!

                mov rbx,rax
                mov byte ptr [rbx+tstrlen(rax)],';'
                mov ModuleInfo.CurrComment,NULL
            .endif
endif
        .endif
        fseek( CurrFile[LST*size_t], list_pos, SEEK_SET )
    .endif

    mov ll.next,NULL
    tmemset( &ll.buffer, ' ', sizeof( ll.buffer ) )
    mov srcfile,get_curr_srcfile()
    mov rbx,CurrSeg

    .switch ( type )
    .case LSTTYPE_DATA
        .endc .if ( Parse_Pass == PASS_1 && Options.first_pass_listing == FALSE )

        ; no break

    .case LSTTYPE_CODE
        mov newofs,GetCurrOffset()
        tsprintf( &ll.buffer, "%08X", oldofs )
        mov ll.buffer[OFSSIZE],' '

        .endc .if ( rbx == NULL )
        .if ( Parse_Pass > PASS_1 && Options.first_pass_listing )
            .endc
        .elseif ( Parse_Pass == PASS_1 )
;            .endc
        .endif

        mov len,CODEBYTES
        lea rdi,ll.buffer[OFSSIZE+2]
        mov rdx,[rbx].dsym.seginfo

        .if ( [rdx].seg_info.CodeBuffer == NULL || [rdx].seg_info.written == FALSE )

            mov eax,'00'
            mov ecx,newofs
            .while ( oldofs < ecx && len )
                stosw
                inc oldofs
                dec len
            .endw
            .endc
        .endif

        ; OMF hold just a small buffer for one LEDATA record
        ; if it has been flushed, use LastCodeBufSize

        mov eax,[rdx].seg_info.current_loc
        sub eax,[rdx].seg_info.start_loc
        mov ecx,newofs
        sub ecx,oldofs
        sub eax,ecx
        mov idx,eax

        .if ( Options.output_format == OFORMAT_OMF )

            ; v2.11: additional check to make the hack more robust
            ; [ test case:  db 800000h dup (0) ]

            add eax,LastCodeBufSize
            .endc .ifs ( eax < 0 ) ; just exit. The code bytes area will remain empty

            mov rsi,[rdx].seg_info.CodeBuffer
            add rsi,rax
            .while ( idx < 0 && len )
                movzx eax,byte ptr [rsi]
                inc rsi
                tsprintf( rdi, "%02X", eax )
                add rdi,2
                inc idx
                inc oldofs
                dec len
            .endw
        .elseif ( idx < 0 )
            mov idx,0
        .endif

        mov rdx,[rbx].dsym.seginfo
        mov rsi,[rdx].seg_info.CodeBuffer
        mov eax,idx
        add rsi,rax

        .while ( oldofs < newofs && len )

            movzx eax,byte ptr [rsi]
            inc rsi
            tsprintf( rdi, "%02X", eax )
            add rdi,2
            inc idx
            inc oldofs
            dec len
        .endw
         mov byte ptr [rdi],' '
        .endc

    .case LSTTYPE_EQUATE

        ; v2.10: display current offset if equate is an alias for a label in this segment

        mov edi,1
        mov rsi,sym
        .if ( [rsi].asym.segm && [rsi].asym.segm == rbx )

            tsprintf( &ll.buffer, "%08X", GetCurrOffset() )
            mov edi,10
        .endif
        mov ll.buffer[rdi],'='
        .if ( [rsi].asym.value3264 != 0 && ( [rsi].asym.value3264 != -1 || [rsi].asym.value >= 0 ) )

            tsprintf( &ll.buffer[rdi+2], "%-" PREFFMTSTR "lX", [rsi].asym.value, [rsi].asym.value3264 )
        .else
            tsprintf( &ll.buffer[rdi+2], "%-" PREFFMTSTR "X", [rsi].asym.value )
        .endif
        mov ll.buffer[rdi+22],' ' ; v2.25 - binary zero fix -- John Hankinson
       .endc

    .case LSTTYPE_TMACRO

        mov ll.buffer[1],'='
        mov rcx,sym

        .for ( rsi = [rcx].asym.string_ptr, rdi = &ll.buffer[3], rbx = &ll : byte ptr [rsi] : )

            lea rax,[rbx].lstleft.buffer[28]

            .if ( rdi >= rax )

                mov [rbx].lstleft.next,alloca( sizeof( lstleft ) )
                mov rbx,rax
                mov [rbx].lstleft.next,NULL
                tmemset( &[rbx].lstleft.buffer, ' ', sizeof( ll.buffer ) )
                lea rdi,[rbx].lstleft.buffer[3]
            .endif
            movsb
        .endf
        .endc

    .case LSTTYPE_MACROLINE
        mov ll.buffer[1],'>'
        mov pSrcline,value
        .endc
    .case LSTTYPE_LABEL
        mov oldofs,GetCurrOffset()
        ; no break
    .case LSTTYPE_STRUCT
        tsprintf( &ll.buffer, "%08X", oldofs )
        mov ll.buffer[8],' '
        .endc
    .case LSTTYPE_DIRECTIVE
        .if ( rbx || value )
            tsprintf( &ll.buffer, "%08X", oldofs )
            mov ll.buffer[8],' '
        .endif
        .endc
    .default ; LSTTYPE_MACRO
        mov rcx,pSrcline
        mov dl,[rcx]
        .if ( dl == 0 && ModuleInfo.CurrComment == NULL && srcfile == ModuleInfo.srcfile )
            fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*size_t] )
            add list_pos,NLSIZ
            .return
        .endif
        .endc
    .endsw

    mov idx,sizeof( ll.buffer )
    .if ( ModuleInfo.GeneratedCode )
        mov ll.buffer[28],'*'
    .endif
    .if ( MacroLevel )
        mov len,tsprintf( &ll.buffer[29], "%u", MacroLevel )
        mov ll.buffer[rax+29],' '
    .endif
    .if ( srcfile != ModuleInfo.srcfile )
        mov ll.buffer[30],'C'
    .endif
    fwrite( &ll.buffer, 1, idx, CurrFile[LST*size_t] )

    mov len,tstrlen( pSrcline )
    mov len2,0
    .if ( ModuleInfo.CurrComment )
        mov len2,tstrlen( ModuleInfo.CurrComment )
    .endif
    mov eax,len2
    add eax,len
    add eax,sizeof( ll.buffer ) + NLSIZ
    add list_pos,eax

    ; write source and comment part
    .if ( len )
        fwrite( pSrcline, 1, len, CurrFile[LST*size_t] )
    .endif
    .if ( len2 )
        fwrite( ModuleInfo.CurrComment, 1, len2, CurrFile[LST*size_t] )
    .endif
    fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*size_t] )


    ; write optional additional lines.
    ; currently works in pass one only.

    .for ( rbx = ll.next: rbx: rbx = [rbx].lstleft.next )

        fwrite( &[rbx].lstleft.buffer, 1, 32, CurrFile[LST*size_t] )
        fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*size_t] )

        add list_pos,32 + NLSIZ
    .endf
    ret

LstWrite endp


LstWriteSrcLine proc __ccall

    LstWrite( LSTTYPE_MACRO, 0, NULL )
    ret

LstWriteSrcLine endp


LstPrintf proc __ccall format:string_t, args:vararg

    .if ( CurrFile[LST*size_t] )

        add list_pos,tvfprintf( CurrFile[LST*size_t], format, &args )
    .endif
    ret

LstPrintf endp


LstNL proc __ccall uses rsi rdi

    .if ( CurrFile[LST*size_t] )

        fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*size_t] )
        add list_pos,NLSIZ
    .endif
    ret

LstNL endp


; set the list file's position
; this is only needed if generated code is to be
; executed BEFORE the original source line is listed.

LstSetPosition proc __ccall uses rsi rdi

    .if ( CurrFile[LST*size_t] && Parse_Pass > PASS_1 &&  UseSavedState && ModuleInfo.GeneratedCode == 0 )

        mov list_pos,LineStoreCurr.get_pos()
        fseek( CurrFile[LST*size_t], list_pos, SEEK_SET )
        or ModuleInfo.line_flags,LOF_SKIPPOS
    .endif
    ret

LstSetPosition endp


    option proc: private

get_seg_align proc __ccall s:ptr seg_info, buffer:string_t

    mov   rcx,s
    movzx ecx,[rcx].seg_info.alignment
    lea   rdx,strings

    .switch( ecx )
    .case 0: .return( [rdx+LS_BYTE]  )
    .case 1: .return( [rdx+LS_WORD]  )
    .case 2: .return( [rdx+LS_DWORD] )
    .case 3: .return( [rdx+LS_QWORD] )
    .case 4: .return( [rdx+LS_PARA]  )
    .case 8: .return( [rdx+LS_PAGE]  )
    .case MAX_SEGALIGNMENT
        .return( [rdx+LS_ABS] )
    .default
        mov eax,1
        shl eax,cl
        tsprintf( buffer, "%u", eax )
        mov rax,buffer
    .endsw
    ret

get_seg_align endp


get_seg_combine proc fastcall s:ptr seg_info

    lea rdx,strings
    .switch( [rcx].seg_info.combine )
    .case COMB_INVALID:    .return( [rdx+LS_PRIVATE] )
    .case COMB_STACK:      .return( [rdx+LS_STACK]   )
    .case COMB_ADDOFF:     .return( [rdx+LS_PUBLIC]  )
    ; v2.06: added
    .case COMB_COMMON:     .return( [rdx+LS_COMMON]  )
    .endsw
    .return( "?" )

get_seg_combine endp


log_macro proc __ccall uses rbx sym:ptr asym

    mov rcx,sym
    lea rax,strings
    mov rdx,[rax+LS_PROC]
    .if ( [rcx].asym.mac_flag &  M_ISFUNC )
        mov rdx,[rax+LS_FUNC]
    .endif
    mov eax,[rcx].asym.name_size
    .if ( eax >= DOTSMAX )
        lea rax,@CStr("")
    .else
        lea rbx,dots
        lea rax,[rbx+rax+1]
    .endif
    LstPrintf( "%s %s        %s", [rcx].asym.name, rax, rdx )
    LstNL()
    ret

log_macro endp


SimpleTypeString proc fastcall mem_type:byte

    .if ecx == MT_ZWORD
        mov ecx,64
    .else
        and ecx,MT_SIZE_MASK
        inc ecx
    .endif
    lea rdx,strings
    .switch ecx
    .case  1:   .return( [rdx+LS_BYTE] )
    .case  2:   .return( [rdx+LS_WORD] )
    .case  4:   .return( [rdx+LS_DWORD] )
    .case  6:   .return( [rdx+LS_FWORD] )
    .case  8:   .return( [rdx+LS_QWORD] )
    .case 10:   .return( [rdx+LS_TBYTE] )
    .case 16:   .return( [rdx+LS_OWORD] )
    .case 32:   .return( [rdx+LS_YWORD] )
    .case 64:   .return( [rdx+LS_ZWORD] )
    .endsw
    .return( "" )

SimpleTypeString endp


; called by log_and log_typedef
; that is, the symbol is ensured to be a TYPE!
; argument 'buffer' is either NULL or "very" large ( StringBufferEnd ).

GetMemtypeString proc __ccall uses rsi rdi rbx sym:ptr asym, buffer:string_t

  local i:int_t
  local mem_type:byte

    mov rsi,sym

    .if ( !( [rsi].asym.mem_type & MT_SPECIAL) )
        .return( SimpleTypeString( [rsi].asym.mem_type ) )
    .endif

    ; v2.05: improve display of stack vars
    mov mem_type,[rsi].asym.mem_type
    .if ( [rsi].asym.state == SYM_STACK && [rsi].asym.is_ptr )
        mov mem_type,MT_PTR
    .endif

    lea rdx,strings
    .switch ( mem_type )
    .case MT_PTR

        .if ( [rsi].asym.Ofssize == USE64 )
            mov rdi,[rdx+LS_NEAR]
        .else
            movzx ecx,[rsi].asym.Ofssize
            .if ( [rsi].asym.is_far )
                mov rdi,[rdx+LS_FAR16+rcx*string_t]
            .else
                mov rdi,[rdx+LS_NEAR16+rcx*string_t]
            .endif
        .endif

        .if ( buffer ) ; Currently, 'buffer' is only != NULL for typedefs

            mov rbx,buffer

            ; v2.10: improved pointer TYPEDEF display

            .for ( i = [rsi].asym.is_ptr: i: i-- )
                lea rdx,strings
                add rbx,tsprintf( rbx, "%s %s ", rdi, string_t ptr [rdx+LS_PTR] )
            .endf

            ; v2.05: added.

            .if ( [rsi].asym.state == SYM_TYPE && [rsi].asym.typekind == TYPE_TYPEDEF )

                .if ( [rsi].asym.target_type )

                    mov rcx,[rsi].asym.target_type
                    tstrcpy( rbx, [rcx].asym.name )

                .elseif ( !( [rsi].asym.ptr_memtype & MT_SPECIAL ) )

                    tstrcpy( rbx, SimpleTypeString( [rsi].asym.ptr_memtype ) )
                .endif
            .endif
            .return( buffer )
        .endif
        .return( rdi )

    .case MT_FAR
        .if ( [rsi].asym.segm )
            .return( [rdx+LS_LFAR] )
        .endif
        mov ecx,GetSymOfssize( rsi )
        lea rdx,strings
       .return( [rdx+LS_LFAR16+rcx*string_t] )

    .case MT_NEAR
        .if ( [rsi].asym.segm )
            .return( [rdx+LS_LNEAR] )
        .endif
        mov ecx,GetSymOfssize( rsi )
        lea rdx,strings
       .return( [rdx+LS_LNEAR16+rcx*string_t] )

    .case MT_TYPE
        mov rcx,[rsi].asym.type
        mov rax,[rcx].asym.name
        .if ( byte ptr [rax] )  ;; there are a lot of unnamed types
            .return( rax )
        .endif
        .return( GetMemtypeString( [rsi].asym.type, buffer ) )

    .case MT_EMPTY ; number = via EQU or directive
        .return( [rdx+LS_NUMBER] )
    .endsw
    .return("?")

GetMemtypeString endp


GetLanguage proc fastcall sym:ptr asym

    movzx eax,[rcx].asym.langtype
    .if ( eax <= LANG_WATCALL )
        lea rdx,strings
        .return( [rdx+rax*string_t+LS_VOID] )
    .endif
    .return( "?" )

GetLanguage endp


; display STRUCTs and UNIONs

log_struct proc __ccall uses rsi rdi rbx sym:ptr asym, name:string_t, ofs:int_32

  local pdots:string_t

    .data
     prefix int_t 0
    .code

    mov rdi,sym
    mov rsi,[rdi].dsym.structinfo

    .if ( !name )
        mov name,[rdi].asym.name
    .endif

    .if ( tstrlen( name ) >= DOTSMAX )
        lea rcx,@CStr("")
    .else
        lea rcx,dots
        lea rcx,[rcx+rax+1]
    .endif

    .if ( [rsi].struct_info.alignment > 1 )

        LstPrintf( "%s %s        %8X (%u)",
            name, rcx, [rdi].asym.total_size, [rsi].struct_info.alignment )
    .else
        LstPrintf( "%s %s        %8X", name, rcx, [rdi].asym.total_size )
    .endif

    LstNL()
    add prefix,2

    assume rbx:ptr sfield

    .for( rbx = [rsi].struct_info.head : rbx : rbx = [rbx].next )

        .if ( [rbx].mem_type == MT_TYPE && [rbx].ivalue[0] == NULLC )

            mov ecx,[rbx].offs
            add ecx,ofs
            log_struct( [rbx].type, [rbx].name, ecx )

        .else

            ; don't list unstructured fields without name
            ; but do list them if they are structured

            mov rcx,[rbx].name

            .if ( byte ptr [rcx] || ( [rbx].mem_type == MT_TYPE ) )

                mov eax,[rbx].name_size
                add eax,prefix
                mov ecx,eax
                lea rdx,dots
                lea rax,[rax+rdx+1]

                .if ( ( ecx >= DOTSMAX ) )
                    lea rax,@CStr("")
                .endif
                mov pdots,rax

                .for ( esi = 0: esi < prefix: esi++ )
                    LstPrintf(" ")
                .endf

                mov ecx,[rbx].offs
                add ecx,[rdi].asym.offs
                add ecx,ofs

                LstPrintf( "%s %s        %8X   ", [rbx].name, pdots, ecx )
                LstPrintf( "%s", GetMemtypeString( rbx, NULL ) )

                .if ( [rbx].flag1 & S_ISARRAY )
                    LstPrintf( "[%u]", [rbx].total_length )
                .endif
                LstNL()
            .endif
        .endif
    .endf
    sub prefix,2
    ret

log_struct endp


log_record proc __ccall uses rsi rdi rbx sym:ptr asym

  local mask:qword
  local pdots:string_t

    mov rdi,sym
    lea rdx,dots
    lea rax,[rdx+1]

    .if ( [rdi].asym.name_size >= DOTSMAX )
        lea rax,@CStr("")
    .endif
    mov pdots,rax
    mov rsi,[rdi].dsym.structinfo

    .for ( edx = 0, rbx = [rsi].struct_info.head: rbx: rbx = [rbx].next, edx++ )
    .endf

    imul ecx,[rdi].asym.total_size,8
    LstPrintf( "%s %s      %6X  %7X", [rdi].asym.name, pdots, ecx, edx )
    LstNL()

    .for ( rbx = [rsi].struct_info.head: rbx: rbx = [rbx].next )

        mov eax,[rbx].name_size
        add eax,2
        mov ecx,eax
        lea rdx,dots
        lea rax,[rdx+rax+1]
        .if ( ( ecx >= DOTSMAX ) )
            lea rax,@CStr("")
        .endif
        mov pdots,rax

        xor eax,eax
        .z8 mask,rax
        mov esi,[rbx].offs
        add esi,[rbx].total_size

        .for ( ecx = [rbx].offs, edx = 0: ecx < esi: ecx++ )

            mov eax,1
            .if ecx >= 32
                sub ecx,32
                shl eax,cl
                or  dword ptr mask[4],eax
                add ecx,32
            .else
                shl eax,cl
                or  dword ptr mask[0],eax
            .endif
        .endf

        lea rcx,@CStr("?")
        .if ( [rbx].ivalue )
            lea rcx,[rbx].ivalue
        .endif
        .if ( [rdi].asym.total_size > 4 )
            LstPrintf( "  %s %s      %6X  %7X  %016lX %s",
                [rbx].name, pdots, [rbx].offs, [rbx].total_size, mask, rcx )
        .else
            LstPrintf( "  %s %s      %6X  %7X  %08X %s",
                [rbx].name, pdots, [rbx].offs, [rbx].total_size, mask, rcx )
        .endif
        LstNL()
    .endf
    ret

log_record endp


    assume rbx:nothing

; a typedef is a simple with no fields. Size might be 0.

log_typedef proc __ccall uses rsi rdi rbx sym:ptr asym

  local pdots:string_t

    mov rsi,sym
    mov ecx,[rsi].asym.name_size
    lea rdx,dots
    lea rax,[rdx+rcx+1]
    .if ( ecx >= DOTSMAX )
        lea rax,@CStr("")
    .endif
    mov pdots,rax

    mov rdi,StringBufferEnd
    mov byte ptr [rdi],NULLC
    mov rbx,[rsi].asym.target_type

    .if ( [rsi].asym.mem_type == MT_PROC && rbx ) ; typedef proto?

        lea rdx,strings
        tstrcat( rdi, [rdx+LS_PROC] )
        tstrcat( rdi, " " )

        mov rcx,[rbx].asym.name
        .if ( byte ptr [rcx] ) ; the name may be ""

            tstrcat( rdi, rcx )
            tstrcat( rdi, " ")
        .endif

        ; v2.11: target_type has state SYM_TYPE (since v2.09).
        ; This state isn't handled properly by GetSymOfsSize(),
        ; which is called by GetMemtypeString(), so get the strings here.

        mov ecx,LS_LFAR16
        .if ( [rbx].asym.mem_type == MT_NEAR )
            mov ecx,LS_LNEAR16
        .endif

        movzx eax,[rsi].asym.Ofssize
        lea rcx,[rcx+rax*4]
        lea rdx,strings

        tstrcat( rdi, [rdx+rcx] )
        tstrcat( rdi, " " )
        tstrcat( rdi, GetLanguage( [rsi].asym.target_type ) )
    .else
        mov rdi,GetMemtypeString( rsi, rdi )
    .endif
    LstPrintf( "%s %s    %8u  %s", [rsi].asym.name, pdots, [rsi].asym.total_size, rdi )
    LstNL()
    ret

log_typedef endp


log_segment proc __ccall uses rsi rdi rbx sym:ptr asym, grp:ptr asym

  local buffer[32]:sbyte

    mov rsi,sym
    mov rdi,[rsi].dsym.seginfo

    .if ( [rdi].seg_info.sgroup == grp )

        mov eax,[rsi].asym.name_size
        lea rdx,dots
        lea rcx,[rdx+rax+1]
        .if ( eax >= DOTSMAX )
            lea rcx,@CStr("")
        .endif
        LstPrintf( "%s %s        ", [rsi].asym.name, rcx )

        .if ( [rdi].seg_info.Ofssize == USE32 )
            LstPrintf( "32 Bit   %08X ", [rsi].asym.max_offset )
        .elseif ( [rdi].seg_info.Ofssize == USE64 )
            LstPrintf( "64 Bit   %08X ", [rsi].asym.max_offset )
        .else
            LstPrintf( "16 Bit   %04X     ", [rsi].asym.max_offset )
        .endif

        mov rbx,get_seg_align( rdi, &buffer )
        LstPrintf( "%-7s %-8s", rbx, get_seg_combine( rdi ) )

        lea rcx,@CStr("")
        mov rdx,[rdi].seg_info.clsym
        .if ( rdx )
            mov rcx,[rdx].asym.name
        .endif
        LstPrintf( "'%s'", rcx )
        LstNL()
    .endif
    ret

log_segment endp


log_group proc __ccall uses rsi rdi grp:ptr asym, segs:ptr dsym

    mov rsi,grp
    mov eax,[rsi].asym.name_size

    lea rcx,dots
    lea rdx,[rcx+rax+1]
    .if ( eax >= DOTSMAX )
        lea rdx,@CStr("")
    .endif

    lea rdi,strings
    mov rdi,[rdi+LS_GROUP]
    LstPrintf( "%s %s        %s", [rsi].asym.name, rdx, rdi )
    LstNL()

    ; the FLAT groups is always empty

    .if ( rsi == ModuleInfo.flat_grp )
        .for( rdi = segs : rdi : rdi = [rdi].dsym.next )
            log_segment( rdi, rsi )
        .endf
    .else
        mov rdi,[rsi].dsym.grpinfo
        .for( rdi = [rdi].grp_info.seglist : rdi : rdi = [rdi].seg_item.next )
            log_segment( [rdi].seg_item.iseg, rsi )
        .endf
    .endif
    ret

log_group endp


get_proc_type proc fastcall sym:ptr asym

    ; if there's no segment associated with the symbol,
    ; add the symbol's offset size to the distance

    .switch( [rcx].asym.mem_type )
    .case MT_NEAR
        .if ( [rcx].asym.segm == NULL )
            GetSymOfssize( rcx )
            lea rdx,strings
            .return( [rdx+rax*string_t+LS_NEAR16] )
        .endif
        lea rdx,strings
        .return( [rdx+LS_NEAR] )
    .case MT_FAR
        .if ( [rcx].asym.segm == NULL )
            GetSymOfssize( rcx )
            lea rdx,strings
            .return( [rdx+rax*string_t+LS_FAR16] )
        .endif
        lea rdx,strings
        .return( [rdx+LS_FAR] )
    .endsw
    .return( " " )

get_proc_type endp


get_sym_seg_name proc fastcall sym:ptr asym

    .if ( [rcx].asym.segm )
        mov rcx,[rcx].asym.segm
        .return( [rcx].asym.name )
    .else
        lea rdx,strings
        .return( [rdx+LS_NOSEG] )
    .endif
    ret

get_sym_seg_name endp


; list Procedures and Prototypes

log_proc proc __ccall uses rsi rdi rbx sym:ptr asym

  local Ofssize:byte
  local p:string_t
  local pdots:string_t
  local buffer[MAX_ID_LEN+1]:char_t

    mov rsi,sym
    mov Ofssize,GetSymOfssize( rsi )

    mov eax,[rsi].asym.name_size
    lea rdx,dots
    lea rcx,[rdx+rax+1]
    .if ( eax >= DOTSMAX )
        lea rcx,@CStr("")
    .endif
    mov pdots,rcx

    lea rdi,@CStr("%s %s        P %-6s %04X     %-8s ")
    .if ( Ofssize )
        lea rdi,@CStr("%s %s        P %-6s %08X %-8s ")
    .endif
    mov p,rdi
    mov rbx,get_proc_type( rsi )
    LstPrintf( rdi, [rsi].asym.name, pdots, rbx, [rsi].asym.offs, get_sym_seg_name( rsi ) )

    ; externals (PROTO) don't have a size. Masm always prints 0000 or 00000000

    mov ecx,4
    .if ( Ofssize > USE16 )
        mov ecx,8
    .endif
    xor edx,edx
    .if ( [rsi].asym.state == SYM_INTERNAL )
        mov edx,[rsi].asym.total_size
    .endif
    LstPrintf( "%0*X ", ecx, edx )

    lea rdx,strings
    .if ( [rsi].asym.flags & S_ISPUBLIC )
        mov rdx,[rdx+LS_PUBLIC]
        LstPrintf( "%-9s", rdx )
    .elseif ( [rsi].asym.state == SYM_INTERNAL )
        mov rdx,[rdx+LS_PRIVATE]
        LstPrintf( "%-9s", rdx )
    .else
        lea rcx,@CStr("%-9s ")
        .if ( [rsi].asym.sflags & S_WEAK )
            lea rcx,@CStr("*%-8s ")
        .endif
        mov rdx,[rdx+LS_EXTERNAL]
        LstPrintf( rcx, rdx )
        mov rcx,[rsi].asym.dll
        .if ( rcx )
            LstPrintf( "(%.8s) ", &[rcx].dll_desc.name )
        .endif
    .endif

    LstPrintf( "%s", GetLanguage( rsi ) )
    LstNL()

    ; for PROTOs, list optional altname

    .if ( [rsi].asym.state == SYM_EXTERNAL && [rsi].asym.altname )

        LstPrintf( "  ")
        mov rbx,[rsi].asym.altname
       .new tmp:ptr = get_proc_type( rbx )
        get_sym_seg_name( rbx )
        mov rdx,pdots
        add rdx,2
        LstPrintf( rdi, [rbx].asym.name, rdx, tmp, [rbx].asym.offs, rax )
        LstNL()
    .endif

    ; for PROCs, list parameters and locals

    .if ( [rsi].asym.state == SYM_INTERNAL )

        ; print the procedure's parameters

        movzx eax,[rsi].asym.langtype
        .if ( eax == LANG_STDCALL || eax == LANG_C || eax == LANG_SYSCALL || eax == LANG_VECTORCALL ||
             ( eax == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) )

            .new cnt:int_t

            ; position f2 to last param

            mov rcx,[rsi].dsym.procinfo
            .for ( cnt = 0, rcx = [rcx].proc_info.paralist: rcx: rcx = [rcx].dsym.nextparam )
                inc cnt
            .endf
            .for ( : cnt: cnt-- )

                mov rdi,[rsi].dsym.procinfo
                .for ( ecx = 1, rdi = [rdi].proc_info.paralist: ecx < cnt: rdi = [rdi].dsym.nextparam, ecx++ )
                .endf
                mov eax,[rdi].asym.name_size
                lea rdx,dots
                lea rcx,[rdx+rax+1+2]
                .if ( eax >= DOTSMAX-2 )
                    lea rcx,@CStr("")
                .endif
                mov pdots,rcx

                ; FASTCALL: parameter may be a text macro (=register name)

                .if ( [rdi].asym.state == SYM_TMACRO )
                    mov rcx,GetMemtypeString( rdi, NULL )
                    LstPrintf( "  %s %s        %-17s %s",
                        [rdi].asym.name, pdots, rcx, [rdi].asym.string_ptr )
                .else
                    mov rcx,[rsi].dsym.procinfo
                    mov tmp,GetResWName( [rcx].proc_info.basereg, NULL )
                    mov rcx,GetMemtypeString( rdi, NULL )
                    .if ( [rdi].asym.sflags & S_ISVARARG )
                        lea rcx,strings
                        mov rcx,[rcx+LS_VARARG]
                    .endif
                    LstPrintf( szFmtProcStk, [rdi].asym.name, pdots, rcx, tmp, '+', [rdi].asym.offs )
                .endif
                LstNL()
            .endf

        .else

            mov rdi,[rsi].dsym.procinfo
            .for ( rdi = [rdi].proc_info.paralist: rdi : rdi = [rdi].dsym.nextparam )

                mov eax,[rdi].asym.name_size
                lea rdx,dots
                lea rcx,[rdx+rax+1+2]
                .if ( eax >= DOTSMAX-2 )
                    lea rcx,@CStr("")
                .endif
                mov pdots,rcx
                mov rcx,[rsi].dsym.procinfo
                mov rbx,GetResWName( [rcx].proc_info.basereg, NULL )
                mov rdx,GetMemtypeString( rdi, NULL )
                LstPrintf( szFmtProcStk, [rdi].asym.name, pdots, rdx,
                          rbx, '+', [rdi].asym.offs )
                LstNL()
            .endf
        .endif

        ; print the procedure's locals

        mov rdi,[rsi].dsym.procinfo
        .for ( rdi = [rdi].proc_info.locallist: rdi : rdi = [rdi].dsym.nextlocal )

            mov eax,[rdi].asym.name_size
            lea rdx,dots
            lea rcx,[rdx+rax+1+2]
            .if ( eax >= DOTSMAX-2 )
                lea rcx,@CStr("")
            .endif
            mov pdots,rcx

            .if ( [rdi].asym.flag1 & S_ISARRAY )
                tsprintf( &buffer, "%s[%u]", GetMemtypeString( rdi, NULL), [rdi].asym.total_length )
            .else
                tstrcpy( &buffer, GetMemtypeString( rdi, NULL ) )
            .endif
            mov rcx,[rsi].dsym.procinfo
            mov rbx,GetResWName( [rcx].proc_info.basereg, NULL )
            mov ecx,'+'
            mov edx,[rdi].asym.offs
            .ifs ( edx < 0 )
                mov ecx,'-'
                neg edx
            .endif
            LstPrintf( szFmtProcStk, [rdi].asym.name, pdots, &buffer, rbx, ecx, edx )
            LstNL()
        .endf

        mov rdi,[rsi].dsym.procinfo
        .for ( rdi = [rdi].proc_info.labellist: rdi : rdi = [rdi].dsym.nextll )

            .for ( rbx = rdi: rbx: rbx = [rbx].asym.nextitem )

                ; filter params and locals!

                .if ( [rbx].asym.state == SYM_STACK || [rbx].asym.state == SYM_TMACRO )
                    .continue
                .endif
                mov eax,[rdi].asym.name_size
                lea rdx,dots
                lea rcx,[rdx+rax+1+2]
                .if ( eax >= DOTSMAX-2 )
                    lea rcx,@CStr("")
                .endif
                mov pdots,rcx
                .if ( Ofssize )
                    lea rax,@CStr("  %s %s        L %-6s %08X %s")
                .else
                    lea rax,@CStr("  %s %s        L %-6s %04X     %s")
                .endif
                mov p,rax
                mov tmp,get_proc_type( rbx )
                get_sym_seg_name( rbx )
                LstPrintf( p, [rbx].asym.name, pdots, tmp, [rbx].asym.offs, eax )
                LstNL()
            .endf
        .endf
    .endif
    ret

log_proc endp


; list symbols

log_symbol proc __ccall uses rsi rdi rbx sym:ptr asym

  local pdots:string_t

    mov rdi,sym
    mov eax,[rdi].asym.name_size
    lea rdx,dots
    lea rcx,[rdx+rax+1]
    .if ( eax >= DOTSMAX )
        lea rcx,@CStr("")
    .endif
    mov pdots,rcx

    .switch ( [rdi].asym.state )
    .case SYM_UNDEFINED
    .case SYM_INTERNAL
    .case SYM_EXTERNAL
        LstPrintf( "%s %s        ", [rdi].asym.name, pdots )

        .if ( [rdi].asym.flag1 & S_ISARRAY )

            mov ebx,tsprintf( StringBufferEnd, "%s[%u]", GetMemtypeString( rdi, NULL ), [rdi].asym.total_length )
            LstPrintf( "%-10s ", StringBufferEnd )

        .elseif ( [rdi].asym.state == SYM_EXTERNAL && [rdi].asym.sflags & S_ISCOM )

            lea rdx,strings
            mov rdx,[rdx+LS_COMM]
            LstPrintf( "%-10s ", rdx )
        .else
            LstPrintf( "%-10s ", GetMemtypeString( rdi, NULL ) )
        .endif

        ; print value

        .if ( [rdi].asym.state == SYM_EXTERNAL && [rdi].asym.sflags & S_ISCOM )

            mov eax,[rdi].asym.total_size
            cdq
            div [rdi].asym.total_length
            LstPrintf( " %8Xh ", eax )

        .elseif ( [rdi].asym.mem_type == MT_EMPTY )

            ; also check segment? might be != NULL for equates (var = offset x)

            .if ( [rdi].asym.value3264 != 0 && [rdi].asym.value3264 != -1 )

                LstPrintf( " %lXh ", [rdi].asym.uvalue, [rdi].asym.value3264 )

            .elseif ( [rdi].asym.value3264 < 0 )

                xor ecx,ecx
                sub ecx,[rdi].asym.uvalue
                LstPrintf( "-%08Xh ", ecx )
            .else

                LstPrintf( " %8Xh ", [rdi].asym.offs )
            .endif
        .else
            LstPrintf( " %8Xh ", [rdi].asym.offs )
        .endif

        ; print segment

        .if ( [rdi].asym.segm )
            LstPrintf( "%s ", get_sym_seg_name( rdi ) )
        .endif

        .if ( [rdi].asym.state == SYM_EXTERNAL && [rdi].asym.sflags & S_ISCOM )
            LstPrintf( "%s=%u ", szCount, [rdi].asym.total_length )
        .endif

        .if ( [rdi].asym.flags & S_ISPUBLIC )

            lea rdx,strings
            mov rdx,[rdx+LS_PUBLIC]
            LstPrintf( "%s ", rdx )
        .endif

        .if ( [rdi].asym.state == SYM_EXTERNAL )

            lea rcx,@CStr("%s ")
            .if ( [rdi].asym.sflags & S_WEAK )
                 lea rcx,@CStr("*%s ")
            .endif

            lea rdx,strings
            mov rdx,[rdx+LS_EXTERNAL]
            LstPrintf( rcx, rdx )

        .elseif ( [rdi].asym.state == SYM_UNDEFINED )

            lea rdx,strings
            mov rdx,[rdx+LS_UNDEFINED]
            LstPrintf( "%s ", rdx )
        .endif

        LstPrintf( "%s", GetLanguage( rdi ) )
        LstNL()
       .endc

    .case SYM_TMACRO
        lea rdx,strings
        mov rdx,[rdx+LS_TEXT]
        LstPrintf( "%s %s        %s   %s", [rdi].asym.name, pdots, rdx, [rdi].asym.string_ptr )
        LstNL()
       .endc

    .case SYM_ALIAS
        mov rcx,[rdi].asym.substitute
        lea rdx,strings
        mov rdx,[rdx+LS_ALIAS]
        LstPrintf( "%s %s        %s  %s", [rdi].asym.name, pdots, rdx, [rcx].asym.name )
        LstNL()
       .endc
    .endsw
    ret

log_symbol endp


LstCaption proc __ccall uses rsi caption:string_t, prefNL:int_t

    .for ( esi = prefNL : esi : esi-- )
        LstNL()
    .endf
    LstPrintf( caption )
    LstNL()
    LstNL()
    ret

LstCaption endp


compare_syms proc fastcall p1:ptr, p2:ptr

    mov rcx,[rcx]
    mov rdx,[rdx]

   .return( tstrcmp( [rcx].asym.name, [rdx].asym.name ) )

compare_syms endp


    option proc: public


; write symbol table listing

LstWriteCRef proc __ccall uses rsi rdi rbx

  local syms:ptr ptr asym
  local dir:ptr dsym
  local s:ptr struct_info
  local idx:int_t
  local i:uint_32
  local SymCount:uint_32
  local queues[LQ_LAST]:qdesc

    ; no point going through the motions if lst file isn't open

    .if ( CurrFile[LST*size_t] == NULL || Options.no_symbol_listing == TRUE )
        .return
    .endif

    ; go to EOF

    fseek( CurrFile[LST*size_t], 0, SEEK_END )

    mov SymCount,SymGetCount()
    mov syms,MemAlloc( &[rax * sizeof( asym_t )] )
    SymGetAll( syms )

    ; sort 'em
    tqsort( syms, SymCount, sizeof( asym_t ), &compare_syms )
    tmemset( &queues, 0, sizeof( queues ) )

    .for ( ebx = 0: ebx < SymCount: ++ebx )

        mov rcx,syms
        mov rdi,[rcx+rbx*asym_t]

        .continue .if !( [rdi].asym.flag1 & S_LIST )

        .switch ( [rdi].asym.state )
        .case SYM_TYPE

            mov s,[rdi].dsym.structinfo

            .switch ( [rdi].asym.typekind )
            .case TYPE_RECORD
                mov ecx,LQ_RECORDS
                .endc
            .case TYPE_TYPEDEF
                mov ecx,LQ_TYPEDEFS
                .endc
            .case TYPE_STRUCT
            .case TYPE_UNION
                mov ecx,LQ_STRUCTS
                .endc
            .default
                .continue ; skip "undefined" types
            .endsw
            .endc

        .case SYM_MACRO:
            mov ecx,LQ_MACROS
            .endc
        .case SYM_SEG:
            mov ecx,LQ_SEGS
            .endc
        .case SYM_GRP:
            mov ecx,LQ_GRPS
            .endc
        .case SYM_INTERNAL
        .case SYM_EXTERNAL ; v2.04: added, since PROTOs are now externals
            .if ( [rdi].asym.flag1 & S_ISPROC )
                mov ecx,LQ_PROCS
                .endc
            .endif
            ; no break
        .default
            .continue
        .endsw

        imul ecx,ecx,qdesc
        lea rax,queues
        lea rdx,[rax+rcx]

        .if ( [rdx].qdesc.head == NULL )
            mov [rdx].qdesc.head,rdi
        .else
            mov rax,[rdx].qdesc.tail
            mov [rax].dsym.next,rdi
        .endif
        mov [rdx].qdesc.tail,rdi
        mov [rdi].dsym.next,NULL
    .endf

    assume rdi:ptr print_item

    .for ( rdi = &cr, ebx = 0 : ebx < lengthof(cr) : ebx++, rdi += print_item )

        movzx   ecx,[rdi].type
        imul    ecx,ecx,qdesc
        lea     rax,queues

        .if ( [rax+rcx].qdesc.head )

            .if ( [rdi].capitems )

                .for ( rsi = [rdi].capitems : word ptr [rsi] : rsi += 2 )

                    mov eax,2
                    .if ( rsi != [rdi].capitems )
                        xor eax,eax
                    .endif
                    movzx ecx,word ptr [rsi]
                    lea rdx,strings
                    mov rcx,[rdx+rcx]
                    LstCaption( rcx, eax )
                .endf
            .endif

            movzx ecx,[rdi].type
            imul ecx,ecx,qdesc
            lea rax,queues

            .for ( rsi = [rax+rcx].qdesc.head: rsi : rsi = [rsi].dsym.next )

                xor ecx,ecx
                .if ( [rdi].print_item.flags & PRF_ADDSEG )
                    mov rcx,queues[LQ_SEGS*qdesc].head
                .endif
                [rdi].function( rsi, rcx, 0 )
            .endf
        .endif
    .endf

    assume rdi:nothing

    ; write out symbols

    lea rcx,strings
    LstCaption( [ rcx + LS_TXT_SYMBOLS ], 2 )
    lea rcx,strings
    LstCaption( [ rcx + LS_TXT_SYMCAP ], 0 )

    .for ( ebx = 0: ebx < SymCount: ++ebx )

        mov rcx,syms
        mov rdi,[rcx+rbx*size_t]

        .if ( [rdi].asym.flag1 & S_LIST && !( [rdi].asym.flag1 & S_ISPROC ) )
            log_symbol( rdi )
        .endif
    .endf
    LstNL()

    ; free the sorted symbols

    MemFree( syms )
    ret

LstWriteCRef endp


; .[NO|X]LIST, .[NO|X]CREF, .LISTALL,
; .[NO]LISTIF, .[LF|SF|TF]COND,
; PAGE, TITLE, SUBTITLE, SUBTTL directives

    assume rbx:ptr asm_tok

ListingDirective proc __ccall uses rsi rbx i:int_t, tokenarray:ptr asm_tok

    mov  esi,i
    imul ebx,esi,asm_tok
    add  rbx,tokenarray
    mov  eax,[rbx].tokval
    inc  esi
    add  rbx,asm_tok

    .switch ( eax )
    .case T_DOT_LIST
        .if ( CurrFile[LST*size_t] )
            mov ModuleInfo.list,TRUE
        .endif
        .endc
    .case T_DOT_CREF
        mov ModuleInfo.cref,TRUE
        .endc
    .case T_DOT_NOLIST
    .case T_DOT_XLIST
        mov ModuleInfo.list,FALSE
        .endc
    .case T_DOT_NOCREF
    .case T_DOT_XCREF

        .if ( esi == Token_Count )
            mov ModuleInfo.cref,FALSE
            .endc
        .endif

        .repeat

            .if ( [rbx].token != T_ID )
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif

            ; the name may be a forward reference. In this case it will
            ; be created here.
            ; v2.11: function call cannot fail. no need for checks.

            SymLookup( [rbx].string_ptr )

            and [rax].asym.flag1,not S_LIST
            inc esi
            add rbx,asm_tok

            .if ( esi < Token_Count )

                .if ( [rbx].token != T_COMMA )
                    .return( asmerr( 2008, [rbx].tokpos ) )
                .endif

                ; if there's nothing after the comma, don't increment

                mov ecx,Token_Count
                dec ecx
                .if ( esi < ecx )

                    inc esi
                    add rbx,asm_tok
                .endif
            .endif

        .until !( esi < Token_Count )
        .endc

    .case T_DOT_LISTALL ; list false conditionals and generated code
        .if ( CurrFile[LST*size_t] )
            mov ModuleInfo.list,TRUE
        .endif
        mov ModuleInfo.list_generated_code,TRUE
        ; fall through
    .case T_DOT_LISTIF
    .case T_DOT_LFCOND ; .LFCOND is synonym for .LISTIF
        mov ModuleInfo.listif,TRUE
        .endc
    .case T_DOT_NOLISTIF
    .case T_DOT_SFCOND ; .SFCOND is synonym for .NOLISTIF
        mov ModuleInfo.listif,FALSE
        .endc
    .case T_DOT_TFCOND ; .TFCOND toggles .LFCOND, .SFCOND
        xor ModuleInfo.listif,1
        .endc
    .case T_DOT_PAGE
    .default ; TITLE, SUBTITLE, SUBTTL

        ; tiny checks to ensure that these directives
        ; aren't used as code labels or fields

        .endc .if ( [rbx].token == T_COLON )

        ; this isn't really Masm-compatible, but ensures we don't get
        ; fields with names page, title, subtitle, subttl.

        .if ( CurrStruct )
            .return( asmerr( 2037 ) )
        .endif
        .if ( Parse_Pass == PASS_1 )
            asmerr( 7005, [rbx-asm_tok].string_ptr )
        .endif
        .while ( [rbx].token != T_FINAL)
            inc esi
            add rbx,asm_tok
        .endw
    .endsw

    .if ( [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif
    .return( NOT_ERROR )

ListingDirective endp


; directives .[NO]LISTMACRO, .LISTMACROALL, .[X|L|S]ALL

ListMacroDirective proc __ccall i:int_t, tokenarray:ptr asm_tok

    imul ecx,i,asm_tok
    add rcx,tokenarray
    .if ( [rcx+asm_tok].asm_tok.token != T_FINAL )
        .return( asmerr( 2008, [rcx+asm_tok].asm_tok.string_ptr ) )
    .endif
    mov ModuleInfo.list_macro,GetSflagsSp( [rcx].asm_tok.tokval )
   .return( NOT_ERROR )

ListMacroDirective endp


LstInit proc __ccall uses rsi rdi

    mov list_pos,0

    .if ( Options.write_listing )

        mov list_pos,tstrlen( &cp_logo )
        fwrite( &cp_logo, 1, list_pos, CurrFile[LST*size_t] )
        LstNL()
        mov rdi,GetFName( ModuleInfo.srcfile )
        add list_pos,tstrlen( rdi )
        fwrite( rdi, 1, eax, CurrFile[LST*size_t] )
        LstNL()
    .endif
    ret

LstInit endp

    end
