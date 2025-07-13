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
include expreval.inc

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
externdef szDate:char_t
externdef szTime:char_t

public list_pos

; cref definitions

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

.data?
mtbuf char_t 256 dup(?)

.data

list_pos uint_t 0 ; current pos in LST file

define DOTSMAX 32
dots db " . . . . . . . . . . . . . . . .",0

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
   .new sym:asym_t = value
   .new len:int_t
   .new len2:int_t
   .new idx:int_t
   .new srcfile:int_t
   .new p1:string_t
   .new p2:string_t
   .new pSrcline:string_t
   .new pll:ptr lstleft
   .new ll:lstleft

    .if ( MODULE.list == FALSE || CurrFile[LST*size_t] == NULL ||
          ( MODULE.line_flags & LOF_LISTED ) )
        .return
    .endif
    .if ( MODULE.GeneratedCode && ( MODULE.list_generated_code == FALSE ) )
        .return
    .endif

    .if ( MacroLevel )
        .switch ( MODULE.list_macro )
        .case LM_NOLISTMACRO
            .return
        .case LM_LISTMACRO
            ; todo: filter certain macro lines
            .endc
        .endsw
    .endif

    or MODULE.line_flags,LOF_LISTED
    mov pSrcline,CurrSource

    .if ( ( Parse_Pass > PASS_1 ) && UseSavedState )

        .if ( MODULE.GeneratedCode == 0 )

            mov rcx,LineStoreCurr
            .if ( !( MODULE.line_flags & LOF_SKIPPOS ) )

                .if ( Parse_Pass == PASS_2 && Options.first_pass_listing )
                    mov [rcx].line_item.list_pos,list_pos
                .else
                    mov list_pos,[rcx].line_item.list_pos
                .endif
            .endif
if USELSLINE
            ; either use CurrSource + CurrComment or LineStoreCurr->line
            ; (see assemble.asm, OnePass())

            mov pSrcline,&[rcx].line_item.line
            .if ( CurrComment ) ; if comment was removed, readd it!

                mov rbx,rax
                mov byte ptr [rbx+tstrlen(rax)],';'
                mov CurrComment,NULL
            .endif
endif
        .endif
        fseek( CurrFile[LST*size_t], list_pos, SEEK_SET )
    .endif

    mov ll.next,NULL
    tmemset( &ll.buffer, ' ', sizeof( ll.buffer ) )
    mov srcfile,get_curr_srcfile()
    mov rbx,CurrSeg
    mov eax,type

    .switch eax
    .case LSTTYPE_DATA
        .endc .if ( Parse_Pass == PASS_1 && Options.first_pass_listing == FALSE )

        ; no break

    .case LSTTYPE_CODE
        mov newofs,GetCurrOffset()
        tsprintf( &ll.buffer, "%08X", oldofs )
        mov ll.buffer[OFSSIZE],' '

        .endc .if ( rbx == NULL )
        .endc .if ( Parse_Pass == PASS_1 );&& Options.first_pass_listing == FALSE )

        mov len,CODEBYTES
        lea rdi,ll.buffer[OFSSIZE+2]
        mov rdx,[rbx].asym.seginfo

        .if ( [rdx].seg_info.CodeBuffer == NULL || ![rdx].seg_info.written )

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

        mov rdx,[rbx].asym.seginfo
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
        .if ( dl == 0 && CurrComment == NULL && srcfile == MODULE.srcfile )
            fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*size_t] )
            add list_pos,NLSIZ
            .return
        .endif
        .endc
    .endsw

    mov idx,sizeof( ll.buffer )
    .if ( MODULE.GeneratedCode )
        mov ll.buffer[28],'*'
    .endif
    .if ( MacroLevel )
        mov len,tsprintf( &ll.buffer[29], "%u", MacroLevel )
        mov ll.buffer[rax+29],' '
    .endif
    .if ( srcfile != MODULE.srcfile )
        mov ll.buffer[30],'C'
    .endif
    fwrite( &ll.buffer, 1, idx, CurrFile[LST*size_t] )

    mov len,tstrlen( pSrcline )
    mov len2,0
    .if ( CurrComment )
        mov len2,tstrlen( CurrComment )
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
        fwrite( CurrComment, 1, len2, CurrFile[LST*size_t] )
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

    .if ( CurrFile[LST*size_t] && Parse_Pass > PASS_1 &&  UseSavedState && MODULE.GeneratedCode == 0 )

        mov rcx,LineStoreCurr
        mov list_pos,[rcx].line_item.list_pos
        fseek( CurrFile[LST*size_t], list_pos, SEEK_SET )
        or MODULE.line_flags,LOF_SKIPPOS
    .endif
    ret

LstSetPosition endp


    option proc: private

log_dots proc __ccall size:uint_t, name:string_t, offs:int_t

    ldr ecx,size
    ldr rdx,name

    add ecx,offs
    .if ( ecx >= DOTSMAX )
        xor eax,eax
    .else
        lea rax,dots
        lea rax,[rax+rcx+1]
    .endif
    lea ecx,[rcx-DOTSMAX-7]
    LstPrintf( "%*s%s %*s", offs, 0, rdx, ecx, rax )
    ret

log_dots endp


SimpleSizeString proc fastcall size:uint_t

    xor eax,eax
    .switch pascal ecx
    .case  1: mov eax,T_BYTE
    .case  2: mov eax,T_WORD
    .case  4: mov eax,T_DWORD
    .case  6: mov eax,T_FWORD
    .case  8: mov eax,T_QWORD
    .case 10: mov eax,T_TBYTE
    .case 16: mov eax,T_OWORD
    .case 32: mov eax,T_YWORD
    .case 64: mov eax,T_ZWORD
    .endsw
    ret

SimpleSizeString endp


SimpleTypeString proc fastcall mem_type:byte

    mov eax,ecx
    .if ecx == MT_ZWORD
        mov ecx,64
    .else
        and ecx,MT_SIZE_MASK
        inc ecx
    .endif
    .if ( !( eax & ( MT_SIGNED or MT_FLOAT ) ) || ecx > 16 )
        .return( SimpleSizeString( ecx ) )
    .endif
    .if ( eax & MT_FLOAT )
        xor eax,eax
        .switch pascal ecx
        .case  2: mov eax,T_REAL2
        .case  4: mov eax,T_REAL4
        .case  8: mov eax,T_REAL8
        .case 10: mov eax,T_REAL10
        .case 16: mov eax,T_REAL16
        .endsw
    .else
        xor eax,eax
        .switch pascal ecx
        .case  1: mov eax,T_SBYTE
        .case  2: mov eax,T_SWORD
        .case  4: mov eax,T_SDWORD
        .case  8: mov eax,T_SQWORD
        .case 16: mov eax,T_SOWORD
        .endsw
    .endif
    ret

SimpleTypeString endp


; called by log_and log_typedef
; that is, the symbol is ensured to be a TYPE!
; argument 'buffer' is either NULL or "very" large ( StringBufferEnd ).

GetMemtypeString proc __ccall uses rsi rdi rbx sym:asym_t, buffer:string_t

  local i:int_t

    ldr rsi,sym
    ldr rbx,buffer

    .if ( !( [rsi].asym.mem_type & MT_SPECIAL) )
        .return( GetResWName( SimpleTypeString( [rsi].asym.mem_type ), rbx ) )
    .endif

    ; v2.05: improve display of stack vars
    movzx eax,[rsi].asym.mem_type
    .if ( [rsi].asym.state == SYM_STACK && [rsi].asym.is_ptr )
        mov al,MT_PTR
    .endif
    lea rdx,mtbuf

    .switch eax
    .case MT_PTR
        mov edi,T_NEAR
        .if ( [rsi].asym.Ofssize < USE64 && [rsi].asym.is_far )
            mov edi,T_FAR
        .endif
        .if ( rbx ) ; Currently, 'buffer' is only != NULL for typedefs

            ; v2.10: improved pointer TYPEDEF display

            .for ( i = [rsi].asym.is_ptr: i: i-- )
                add rbx,tsprintf( rbx, "%r %r ", edi, T_PTR )
            .endf

            ; v2.05: added.

            .if ( [rsi].asym.state == SYM_TYPE && [rsi].asym.typekind == TYPE_TYPEDEF )
                .if ( [rsi].asym.target_type )
                    mov rcx,[rsi].asym.target_type
                    tstrcpy( rbx, [rcx].asym.name )
                .elseif ( !( [rsi].asym.ptr_memtype & MT_SPECIAL ) )
                    tsprintf( rbx, "%r", SimpleTypeString( [rsi].asym.ptr_memtype ) )
                .endif
            .endif
            .return( rbx )
        .endif
        .return( GetResWName( edi, rdx ) )
    .case MT_FAR
        mov rbx,rdx
        tsprintf( rbx, "L %r", T_FAR )
       .return( rbx )
    .case MT_NEAR
        mov rbx,rdx
        tsprintf( rbx, "L %r", T_NEAR )
       .return( rbx )
    .case MT_TYPE
        mov rcx,[rsi].asym.type
        mov rax,[rcx].asym.name
        .if ( byte ptr [rax] )  ;; there are a lot of unnamed types
            .return( rax )
        .endif
        .return( GetMemtypeString( [rsi].asym.type, rdx ) )
    .case MT_BITS
        .return( "bits" )
    .case MT_EMPTY ; number = via EQU or directive
        .return( "number" )
    .endsw
    .return( "?" )

GetMemtypeString endp


GetLanguage proc fastcall sym:asym_t

    movzx eax,[rcx].asym.langtype
    .if ( eax > LANG_NONE && eax <= LANG_ASMCALL )
        .return( &[rax+T_CCALL-1] )
    .endif
    .return( 0 )

GetLanguage endp


log_macro proc __ccall uses rbx sym:asym_t

    ldr rbx,sym

    log_dots( [rbx].asym.name_size, [rbx].asym.name, 0 )
    mov edx,T_PROC
    .if ( [rbx].asym.isfunc )
        mov edx,T_MACRO
    .endif
    LstPrintf( "%r", edx )
    LstNL()
    ret

log_macro endp


; display STRUCTs and UNIONs

log_struct proc __ccall uses rsi rdi rbx sym:asym_t, name:string_t, ofs:int_32

    .data
     prefix int_t 0
    .code

    ldr rdi,sym
    ldr rbx,name

    mov rsi,[rdi].asym.structinfo
    .if ( !rbx )
        mov rbx,[rdi].asym.name
    .endif
    log_dots( tstrlen(rbx), rbx, 0 )
    .if ( [rsi].struct_info.alignment > 1 )
        LstPrintf( "%8X (%u)", [rdi].asym.total_size, [rsi].struct_info.alignment )
    .else
        LstPrintf( "%8X", [rdi].asym.total_size )
    .endif

    LstNL()
    add prefix,2

    assume rbx:asym_t

    .for( rbx = [rsi].struct_info.head : rbx : rbx = [rbx].next )

        .if ( [rbx].mem_type == MT_TYPE && [rbx].ivalue == 0 )

            mov ecx,[rbx].offs
            add ecx,ofs
            log_struct( [rbx].type, [rbx].name, ecx )

        .else

            ; don't list unstructured fields without name
            ; but do list them if they are structured

            mov rcx,[rbx].name

            .if ( byte ptr [rcx] || ( [rbx].mem_type == MT_TYPE ) )

                log_dots( [rbx].name_size, [rbx].name, prefix )
                GetMemtypeString( rbx, NULL )
                mov ecx,[rbx].offs
                add ecx,[rdi].asym.offs
                add ecx,ofs
                .if ( [rbx].mem_type == MT_BITS )
                    movzx ecx,[rbx].asym.bitf_bits
                .endif
                LstPrintf( "%8X   %s", ecx, rax )
                .if ( [rbx].isarray )
                    LstPrintf( "[%u]", [rbx].total_length )
                .endif
                LstNL()
            .endif
        .endif
    .endf
    sub prefix,2
    ret

log_struct endp


log_record proc __ccall uses rsi rdi rbx sym:asym_t

  local mask:qword

    ldr rdi,sym

    log_dots( [rdi].asym.name_size, [rdi].asym.name, 0 )
    mov rsi,[rdi].asym.structinfo
    .for ( edx = 0, rbx = [rsi].struct_info.head: rbx: rbx = [rbx].next, edx++ )
    .endf
    imul ecx,[rdi].asym.total_size,8
    LstPrintf( "%6X  %7X", ecx, edx )
    LstNL()

    .for ( rbx = [rsi].struct_info.head: rbx: rbx = [rbx].next )

        log_dots( [rbx].name_size, [rbx].name, 2 )
        SetBitMask( rbx, &mask )
        lea rcx,[rbx].ivalue
        .if ( [rbx].ivalue == 0 )
            mov rcx,GetResWName( SimpleSizeString( [rdi].asym.total_size ), NULL )
        .endif
        .if ( [rdi].asym.total_size > 4 )
            LstPrintf( "%6X  %7X  %016lX %s", [rbx].bitf_offs, [rbx].bitf_bits, mask, rcx )
        .else
            LstPrintf( "%6X  %7X  %08X %s", [rbx].bitf_offs, [rbx].bitf_bits, mask, rcx )
        .endif
        LstNL()
    .endf
    ret

log_record endp


    assume rbx:nothing

; a typedef is a simple with no fields. Size might be 0.

log_typedef proc __ccall uses rsi rdi rbx sym:asym_t

    ldr rsi,sym

    log_dots( [rsi].asym.name_size, [rsi].asym.name, 0 )

    mov rdi,StringBufferEnd
    mov byte ptr [rdi],NULLC
    mov rbx,[rsi].asym.target_type

    .if ( [rsi].asym.mem_type == MT_PROC && rbx ) ; typedef proto?

        add rdi,tsprintf( rdi, "%r ", T_PROC )
        mov rcx,[rbx].asym.name
        .if ( byte ptr [rcx] ) ; the name may be ""
            add rdi,tsprintf( rdi, "%s ", rcx )
        .endif

        ; v2.11: target_type has state SYM_TYPE (since v2.09).
        ; This state isn't handled properly by GetSymOfsSize(),
        ; which is called by GetMemtypeString(), so get the strings here.

        GetLanguage( rbx )
        mov ecx,T_NEAR
        .if ( [rsi].asym.Ofssize < USE64 && [rbx].asym.is_far )
            mov ecx,T_FAR
        .endif
        tsprintf( rdi, "L %r %r", ecx, eax )
    .else
        GetMemtypeString( rsi, rdi )
    .endif
    LstPrintf( "%08X %s", [rsi].asym.total_size, StringBufferEnd )
    LstNL()
    ret

log_typedef endp


log_segment proc __ccall uses rsi rdi rbx sym:asym_t, grp:asym_t

  local buffer[32]:sbyte

    ldr rsi,sym
    mov rdi,[rsi].asym.seginfo

    .if ( [rdi].seg_info.sgroup == grp )

        log_dots( [rsi].asym.name_size, [rsi].asym.name, 0 )

        mov edx,16
        mov cl,[rdi].seg_info.Ofssize
        shl edx,cl
        LstPrintf( "%u bit   ", edx )
        mov edx,[rsi].asym.max_offset
        .if ( [rdi].seg_info.Ofssize >= USE32 )
            LstPrintf( "%08X ", edx )
        .else
            LstPrintf( "%04X     ", edx )
        .endif

        xor ecx,ecx
        xor edx,edx
        movzx eax,[rdi].seg_info.alignment
        .switch pascal eax
        .case 0: mov edx,T_BYTE
        .case 1: mov edx,T_WORD
        .case 2: mov edx,T_DWORD
        .case 3: mov edx,T_QWORD
        .case 4: lea rcx,@CStr("para")
        .case 8: mov edx,T_PAGE
        .case MAX_SEGALIGNMENT
            lea rcx,@CStr("abs")
        .default
            mov ecx,eax
            mov edx,1
            shl edx,cl
            tsprintf( &buffer, "%u", edx )
            lea rcx,buffer
            xor edx,edx
        .endsw
        .if ( edx )
            LstPrintf( "%-7r ", edx )
        .else
            LstPrintf( "%-7s ", rcx )
        .endif

        xor edx,edx
        movzx eax,[rdi].seg_info.combine
        .switch pascal eax
        .case COMB_INVALID: lea rcx,@CStr("private")
        .case COMB_STACK:   lea rcx,@CStr("stack")
        .case COMB_ADDOFF:  mov edx,T_PUBLIC
        ; v2.06: added
        .case COMB_COMMON:  lea rcx,@CStr("common")
        .default
            lea rcx,@CStr("?")
        .endsw
        .if ( edx )
            LstPrintf( "%-8r", edx )
        .else
            LstPrintf( "%-8s", rcx )
        .endif
        mov rcx,[rdi].seg_info.clsym
        .if ( rcx )
            mov rcx,[rcx].asym.name
        .endif
        LstPrintf( "'%s'", rcx )
        LstNL()
    .endif
    ret

log_segment endp


log_group proc __ccall uses rsi rdi grp:asym_t, segs:asym_t

    ldr rsi,grp

    log_dots([rsi].asym.name_size, [rsi].asym.name, 0)
    LstPrintf( "%r", T_GROUP )
    LstNL()

    ; the FLAT groups is always empty

    .if ( rsi == MODULE.flat_grp )
        .for( rdi = segs : rdi : rdi = [rdi].asym.next )
            log_segment( rdi, rsi )
        .endf
    .else
        mov rdi,[rsi].asym.grpinfo
        .for( rdi = [rdi].grp_info.seglist : rdi : rdi = [rdi].seg_item.next )
            log_segment( [rdi].seg_item.iseg, rsi )
        .endf
    .endif
    ret

log_group endp


get_proc_type proc fastcall sym:asym_t

    ; if there's no segment associated with the symbol,
    ; add the symbol's offset size to the distance

    xor eax,eax
    .if ( [rcx].asym.mem_type == MT_NEAR )
        mov eax,T_NEAR
    .elseif ( [rcx].asym.mem_type == MT_FAR )
        mov eax,T_FAR
    .endif
    ret

get_proc_type endp


get_sym_seg_name proc watcall sym:asym_t

    mov rax,[rax].asym.segm
    .if ( rax )
        mov rax,[rax].asym.name
    .else
        lea rax,@CStr("no seg")
    .endif
    ret

get_sym_seg_name endp


; list Procedures and Prototypes

log_proc proc __ccall uses rsi rdi rbx sym:asym_t

  local p:string_t
  local pdots:string_t
  local tmp:string_t
  local buffer[MAX_ID_LEN+1]:char_t
  local type:uint_t
  local Ofssize:byte

    ldr rsi,sym

    log_dots( [rsi].asym.name_size, [rsi].asym.name, 0 )
    mov Ofssize,GetSymOfssize( rsi )
    lea rdi,@CStr("P %-6r %04X     %-8s ")
    .if ( Ofssize )
        lea rdi,@CStr("P %-6r %08X %-8s ")
    .endif
    mov p,rdi
    mov ebx,get_proc_type( rsi )
    LstPrintf( rdi, ebx, [rsi].asym.offs, get_sym_seg_name( rsi ) )

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
    .if ( [rsi].asym.ispublic || ( [rsi].asym.isinline && ![rsi].asym.weak ) )
        LstPrintf( "%-8r ", T_PUBLIC )
    .elseif ( [rsi].asym.state == SYM_INTERNAL )
        LstPrintf( "private  " )
    .else
        lea rcx,@CStr("*%*r ")
        mov edx,-7
        .if !( [rsi].asym.weak )
            inc rcx
            dec edx
        .endif
        LstPrintf( rcx, edx, T_EXTERN )
        mov rcx,[rsi].asym.dll
        .if ( rcx )
            LstPrintf( "(%.8s) ", &[rcx].dll_desc.name )
        .endif
    .endif

    LstPrintf( "%r", GetLanguage( rsi ) )
    LstNL()

    ; for PROTOs, list optional altname

    .if ( [rsi].asym.state == SYM_EXTERNAL && [rsi].asym.altname )

        mov rbx,[rsi].asym.altname
        log_dots( [rbx].asym.name_size, [rbx].asym.name, 2 )
        mov type,get_proc_type( rbx )
        LstPrintf( rdi, type, [rbx].asym.offs, get_sym_seg_name( rbx ) )
        LstNL()
    .endif

    ; for PROCs, list parameters and locals

    .if ( [rsi].asym.state == SYM_INTERNAL || ( [rsi].asym.isinline && ![rsi].asym.weak ) )

        ; print the procedure's parameters

        movzx eax,[rsi].asym.langtype
        .if ( eax == LANG_STDCALL || eax == LANG_C || eax == LANG_SYSCALL || eax == LANG_VECTORCALL ||
             eax == LANG_WATCALL || eax == LANG_ASMCALL || ( eax == LANG_FASTCALL && MODULE.Ofssize != USE16 ) )

            .new cnt:int_t

            ; position f2 to last param

            mov rcx,[rsi].asym.procinfo
            .for ( cnt = 0, rcx = [rcx].proc_info.paralist: rcx: rcx = [rcx].asym.nextparam )
                inc cnt
            .endf
            .for ( : cnt: cnt-- )

                mov rdi,[rsi].asym.procinfo
                .for ( ecx = 1, rdi = [rdi].proc_info.paralist: ecx < cnt: rdi = [rdi].asym.nextparam, ecx++ )
                .endf

                log_dots( [rdi].asym.name_size, [rdi].asym.name, 2 )

                ; FASTCALL: parameter may be a text macro (=register name)

                .if ( [rdi].asym.regparam )
                    LstPrintf( "%-8s ", GetMemtypeString( rdi, NULL ) )
                    .if ( [rdi].asym.state == SYM_STACK )
                        mov rcx,[rsi].asym.procinfo
                        movzx ebx,[rcx].proc_info.basereg
                        LstPrintf( "[%r+%02X] ", ebx, [rdi].asym.offs )
                    .endif
                    LstPrintf( "%r", [rdi].asym.param_reg )
                .else
                    mov rcx,[rsi].asym.procinfo
                    movzx ebx,[rcx].proc_info.basereg
                    mov rcx,GetMemtypeString( rdi, NULL )
                    .if ( [rdi].asym.is_vararg )
                        mov rcx,GetResWName( T_VARARG, rcx )
                    .endif
                    LstPrintf( "%-8s [%r+%02X]", rcx, ebx, [rdi].asym.offs )
                .endif
                LstNL()
            .endf

        .else

            mov rdi,[rsi].asym.procinfo
            .for ( rdi = [rdi].proc_info.paralist: rdi : rdi = [rdi].asym.nextparam )

                log_dots( [rdi].asym.name_size, [rdi].asym.name, 2 )

                mov rcx,[rsi].asym.procinfo
                movzx ebx,[rcx].proc_info.basereg
                mov rdx,GetMemtypeString( rdi, NULL )
                LstPrintf( "%-8s [%r%c%02X]", rdx, ebx, '+', [rdi].asym.offs )
                LstNL()
            .endf
        .endif

        ; print the procedure's locals

        mov rdi,[rsi].asym.procinfo
        .for ( rdi = [rdi].proc_info.locallist: rdi : rdi = [rdi].asym.nextlocal )

            log_dots( [rdi].asym.name_size, [rdi].asym.name, 2 )

            .if ( [rdi].asym.isarray )
                tsprintf( &buffer, "%s[%u]", GetMemtypeString( rdi, NULL), [rdi].asym.total_length )
            .else
                tstrcpy( &buffer, GetMemtypeString( rdi, NULL ) )
            .endif
            mov rcx,[rsi].asym.procinfo
            movzx ebx,[rcx].proc_info.basereg
            mov ecx,'+'
            mov edx,[rdi].asym.offs
            .ifs ( edx < 0 )
                mov ecx,'-'
                neg edx
            .endif
            LstPrintf( "%-8s [%r%c%02X]", &buffer, ebx, ecx, edx )
            LstNL()
        .endf

        mov rdi,[rsi].asym.procinfo
        .for ( rdi = [rdi].proc_info.labellist: rdi : rdi = [rdi].asym.nextll )

            .for ( rbx = rdi: rbx: rbx = [rbx].asym.nextitem )

                ; filter params and locals!

                .if ( [rbx].asym.state == SYM_STACK || [rbx].asym.state == SYM_TMACRO )
                    .continue
                .endif

                log_dots( [rbx].asym.name_size, [rbx].asym.name, 2 )
                mov type,get_proc_type( rbx )
                mov tmp,get_sym_seg_name( rbx )
                .if ( Ofssize )
                    lea rcx,@CStr("L %-6r %08X %s")
                .else
                    lea rcx,@CStr("L %-6r %04X %s")
                .endif
                LstPrintf( rcx, type, [rbx].asym.offs, tmp )
                LstNL()
            .endf
        .endf
    .endif
    ret

log_proc endp


; list symbols

log_symbol proc __ccall uses rsi rdi rbx sym:asym_t

    ldr rdi,sym

    movzx eax,[rdi].asym.state
    .switch eax
    .case SYM_UNDEFINED
    .case SYM_INTERNAL
    .case SYM_EXTERNAL

        log_dots([rdi].asym.name_size, [rdi].asym.name, 0)
        .if ( [rdi].asym.isarray )
            mov ebx,tsprintf( StringBufferEnd, "%s[%u]", GetMemtypeString( rdi, NULL ), [rdi].asym.total_length )
            LstPrintf( "%-8s ", StringBufferEnd )
        .elseif ( [rdi].asym.state == SYM_EXTERNAL && [rdi].asym.iscomm )
            LstPrintf( "%-8r ", T_COMM )
        .else
            LstPrintf( "%-8s ", GetMemtypeString( rdi, NULL ) )
        .endif

        ; print value

        .if ( [rdi].asym.state == SYM_EXTERNAL && [rdi].asym.iscomm )

            mov eax,[rdi].asym.total_size
            cdq
            div [rdi].asym.total_length
            LstPrintf( "%08X ", eax )

        .elseif ( [rdi].asym.mem_type == MT_EMPTY )

            ; also check segment? might be != NULL for equates (var = offset x)

            .if ( [rdi].asym.value3264 != 0 && [rdi].asym.value3264 != -1 )

                LstPrintf( "%08X%08X ", [rdi].asym.value3264, [rdi].asym.uvalue )
            .elseif ( [rdi].asym.value3264 < 0 )
                LstPrintf( "%08X ", [rdi].asym.uvalue )
            .else
                LstPrintf( "%08X ", [rdi].asym.offs )
            .endif
        .else
            LstPrintf( "%08X ", [rdi].asym.offs )
        .endif

        ; print segment

        .if ( [rdi].asym.segm )
            LstPrintf( "%s ", get_sym_seg_name( rdi ) )
        .endif
        .if ( [rdi].asym.state == SYM_EXTERNAL && [rdi].asym.iscomm )
            LstPrintf( "count=%u ", [rdi].asym.total_length )
        .endif
        .if ( [rdi].asym.ispublic || ( [rdi].asym.isinline && ![rdi].asym.weak ) )
            LstPrintf( "%r ", T_PUBLIC )
        .endif
        .if ( [rdi].asym.state == SYM_EXTERNAL )
            lea rcx,@CStr("*%r ")
            .if ( ![rdi].asym.weak )
                 inc rcx
            .endif
            LstPrintf( rcx, T_EXTERN )
        .elseif ( [rdi].asym.state == SYM_UNDEFINED )
            LstPrintf( "un%r ", T_DEFINED )
        .endif
        LstPrintf( "%r", GetLanguage( rdi ) )
        LstNL()
       .endc

    .case SYM_TMACRO
        log_dots([rdi].asym.name_size, [rdi].asym.name, 0)
        LstPrintf( "text     %s", [rdi].asym.string_ptr )
        LstNL()
       .endc

    .case SYM_ALIAS
        log_dots([rdi].asym.name_size, [rdi].asym.name, 0)
        mov rcx,[rdi].asym.substitute
        LstPrintf( "%r  %s", T_ALIAS, [rcx].asym.name )
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

  local syms:ptr asym_t
  local dir:asym_t
  local s:struct_t
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

        .continue .if !( [rdi].asym.list )

        movzx eax,[rdi].asym.state
        .switch eax
        .case SYM_TYPE

            mov s,[rdi].asym.structinfo
            movzx eax,[rdi].asym.typekind
            .switch eax
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

        .case SYM_MACRO
            mov ecx,LQ_MACROS
           .endc
        .case SYM_SEG
            mov ecx,LQ_SEGS
           .endc
        .case SYM_GRP
            mov ecx,LQ_GRPS
           .endc
        .case SYM_INTERNAL
        .case SYM_EXTERNAL ; v2.04: added, since PROTOs are now externals
            .if ( [rdi].asym.isproc )
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
            mov [rax].asym.next,rdi
        .endif
        mov [rdx].qdesc.tail,rdi
        mov [rdi].asym.next,NULL
    .endf

    .if ( queues[qdesc*LQ_MACROS].qdesc.head )
        LstCaption( "Macros:", 2 )
        LstCaption( "                N a m e                 Type", 0 )
        .for ( rsi = queues[qdesc*LQ_MACROS].qdesc.head: rsi : rsi = [rsi].asym.next )
            log_macro( rsi )
        .endf
    .endif
    .if ( queues[qdesc*LQ_STRUCTS].qdesc.head )
        LstCaption( "Structures and Unions:", 2 )
        LstCaption( "                N a m e                 Size/Ofs   Type", 0 )
        .for ( rsi = queues[qdesc*LQ_STRUCTS].qdesc.head: rsi : rsi = [rsi].asym.next )
            log_struct( rsi, 0, 0 )
        .endf
    .endif
    .if ( queues[qdesc*LQ_RECORDS].qdesc.head )
        LstCaption( "Records:", 2 )
        LstCaption( "                N a m e                 Width   # fields\n"
                    "                                        Shift   Width    Mask   Initial", 0 )
        .for ( rsi = queues[qdesc*LQ_RECORDS].qdesc.head: rsi : rsi = [rsi].asym.next )
            log_record( rsi )
        .endf
    .endif
    .if ( queues[qdesc*LQ_TYPEDEFS].qdesc.head )
        LstCaption( "Types:", 2 )
        LstCaption( "                N a m e                 Size     Attr", 0 )
        .for ( rsi = queues[qdesc*LQ_TYPEDEFS].qdesc.head: rsi : rsi = [rsi].asym.next )
            log_typedef( rsi )
        .endf
    .endif
    .if ( queues[qdesc*LQ_SEGS].qdesc.head )
        LstCaption( "Segments and Groups:", 2 )
        LstCaption( "                N a m e                 Size     Length   Align   Combine Class", 0 )
        .for ( rsi = queues[qdesc*LQ_SEGS].qdesc.head: rsi : rsi = [rsi].asym.next )
            log_segment( rsi, 0 )
        .endf
    .endif
    .if ( queues[qdesc*LQ_GRPS].qdesc.head )
        .for ( rsi = queues[qdesc*LQ_GRPS].qdesc.head: rsi : rsi = [rsi].asym.next )
            log_group( rsi, queues[LQ_SEGS*qdesc].head )
        .endf
    .endif
    .if ( queues[qdesc*LQ_PROCS].qdesc.head )
        LstCaption( "Procedures, parameters and locals:", 2 )
        LstCaption( "                N a m e                 Type     Value    Segment  Length", 0 )
        .for ( rsi = queues[qdesc*LQ_PROCS].qdesc.head: rsi : rsi = [rsi].asym.next )
            log_proc( rsi )
        .endf
    .endif


    ; write out symbols

    LstCaption( "Symbols:", 2 )
    LstCaption( "                N a m e                 Type     Value     Attr", 0 )

    .for ( ebx = 0: ebx < SymCount: ++ebx )

        mov rcx,syms
        mov rdi,[rcx+rbx*size_t]

        .if ( [rdi].asym.list && !( [rdi].asym.isproc ) )
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

    assume rbx:token_t

ListingDirective proc __ccall uses rsi rbx i:int_t, tokenarray:token_t

    ldr  esi,i
    imul ebx,esi,asm_tok
    add  rbx,tokenarray
    mov  eax,[rbx].tokval
    inc  esi
    add  rbx,asm_tok

    .switch eax
    .case T_DOT_LIST
        .if ( CurrFile[LST*size_t] )
            mov MODULE.list,TRUE
        .endif
        .endc
    .case T_DOT_CREF
        mov MODULE.cref,TRUE
        .endc
    .case T_DOT_NOLIST
    .case T_DOT_XLIST
        mov MODULE.list,FALSE
        .endc
    .case T_DOT_NOCREF
    .case T_DOT_XCREF

        .if ( esi == TokenCount )
            mov MODULE.cref,FALSE
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

            mov [rax].asym.list,0
            inc esi
            add rbx,asm_tok

            .if ( esi < TokenCount )

                .if ( [rbx].token != T_COMMA )
                    .return( asmerr( 2008, [rbx].tokpos ) )
                .endif

                ; if there's nothing after the comma, don't increment

                mov ecx,TokenCount
                dec ecx
                .if ( esi < ecx )

                    inc esi
                    add rbx,asm_tok
                .endif
            .endif

        .until !( esi < TokenCount )
        .endc

    .case T_DOT_LISTALL ; list false conditionals and generated code
        .if ( CurrFile[LST*size_t] )
            mov MODULE.list,TRUE
        .endif
        mov MODULE.list_generated_code,TRUE
        ; fall through
    .case T_DOT_LISTIF
    .case T_DOT_LFCOND ; .LFCOND is synonym for .LISTIF
        mov MODULE.listif,TRUE
        .endc
    .case T_DOT_NOLISTIF
    .case T_DOT_SFCOND ; .SFCOND is synonym for .NOLISTIF
        mov MODULE.listif,FALSE
        .endc
    .case T_DOT_TFCOND ; .TFCOND toggles .LFCOND, .SFCOND
        xor MODULE.listif,1
        .endc
    .case T_PAGE
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

ListMacroDirective proc __ccall i:int_t, tokenarray:token_t

    imul ecx,i,asm_tok
    add rcx,tokenarray
    .if ( [rcx+asm_tok].asm_tok.token != T_FINAL )
        .return( asmerr( 2008, [rcx+asm_tok].asm_tok.string_ptr ) )
    .endif
    mov MODULE.list_macro,GetSflagsSp( [rcx].asm_tok.tokval )
   .return( NOT_ERROR )

ListMacroDirective endp


LstInit proc __ccall

    .new logo[64]:char_t

    .if ( Parse_Pass == PASS_1 )
        mov list_pos,0
    .endif
    .if ( Options.write_listing )

        tsprintf( &logo, &cp_logo, ASMC_MAJOR, ASMC_MINOR, ASMC_SUBVER )
        mov rdx,GetFName( MODULE.srcfile )
        lea rcx,@CStr("%s  %s %s\n%s\n")
        .if ( Parse_Pass == PASS_1 && Options.first_pass_listing )
            lea rcx,@CStr("%s  %s %s - First Pass\n%s\n")
        .elseif ( Options.first_pass_listing )
            lea rcx,@CStr("\n%s  %s %s\n%s\n\n")
        .endif
        LstPrintf( rcx, &logo, &szDate, &szTime, rdx )
    .endif
    ret

LstInit endp

    end
