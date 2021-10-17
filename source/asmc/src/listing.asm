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

log_macro   proto :ptr asym
log_struct  proto :ptr asym, :ptr sbyte, :sdword
log_record  proto :ptr asym
log_typedef proto :ptr asym
log_segment proto :ptr asym, :ptr asym
log_group   proto :ptr asym, :ptr dsym
log_proc    proto :ptr asym

.data

list_pos uint_t 0 ; current pos in LST file

define DOTSMAX 32
dots db " . . . . . . . . . . . . . . . .",0

define szFmtProcStk <"  %s %s        %-17s %s %c %04X">

ltext macro index, string
  exitm<LS_&index&,>
  endm
.enumt list_strings {
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
    function proc local :ptr asym, :ptr asym, :int_32
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

LstWrite proc uses esi edi ebx type:lsttype, oldofs:uint_t, value:ptr

  local newofs:uint_t
  local sym:ptr asym
  local len:int_t
  local len2:int_t
  local idx:int_t
  local srcfile:int_t
  local p1:string_t
  local p2:string_t
  local pSrcline:string_t
  local pll:ptr lstleft
  local ll:lstleft

    mov sym,value

    .if ( ModuleInfo.list == FALSE || CurrFile[LST*4] == NULL  || ( ModuleInfo.line_flags & LOF_LISTED ) )
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

if USELSLINE
                ; either use CurrSource + CurrComment or LineStoreCurr->line
                ; (see assemble.asm, OnePass())

                mov pSrcline,LineStoreCurr.get_line()
                .if ( ModuleInfo.CurrComment ) ; if comment was removed, readd it!
                    mov ebx,eax
                    mov byte ptr [ebx+strlen(eax)],';'
                    mov ModuleInfo.CurrComment,NULL
                .endif
endif
            .endif
        .endif
        fseek( CurrFile[LST*4], list_pos, SEEK_SET )
    .endif

    mov ll.next,NULL
    memset( &ll.buffer, ' ', sizeof( ll.buffer ) )
    mov srcfile,get_curr_srcfile()
    mov ebx,CurrSeg

    .switch ( type )
    .case LSTTYPE_DATA
        .endc .if ( Parse_Pass == PASS_1 && Options.first_pass_listing == FALSE )

        ; no break

    .case LSTTYPE_CODE
        mov newofs,GetCurrOffset()
        tsprintf( &ll.buffer, "%08X", oldofs )
        mov ll.buffer[OFSSIZE],' '

        .endc .if ( ebx == NULL )
        .if ( Options.first_pass_listing )
            .endc .if ( Parse_Pass > PASS_1 )
        .elseif ( Parse_Pass == PASS_1 )  ; changed v1.96
            .endc
        .endif

        mov len,CODEBYTES
        lea edi,ll.buffer[OFSSIZE+2]
        mov edx,[ebx].dsym.seginfo

        .if ( [edx].seg_info.CodeBuffer == NULL || \
              [edx].seg_info.written == FALSE )

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

        mov eax,[edx].seg_info.current_loc
        sub eax,[edx].seg_info.start_loc
        mov ecx,newofs
        sub ecx,oldofs
        sub eax,ecx
        mov idx,eax

        .if ( Options.output_format == OFORMAT_OMF )

            ; v2.11: additional check to make the hack more robust
            ; [ test case:  db 800000h dup (0) ]

            add eax,LastCodeBufSize
            .endc .ifs ( eax < 0 ) ; just exit. The code bytes area will remain empty

            mov esi,[edx].seg_info.CodeBuffer
            add esi,eax
            .while ( idx < 0 && len )
                lodsb
                tsprintf( edi, "%02X", eax )
                add edi,2
                inc idx
                inc oldofs
                dec len
            .endw
        .elseif ( idx < 0 )
            mov idx,0
        .endif

        mov edx,[ebx].dsym.seginfo
        mov esi,[edx].seg_info.CodeBuffer
        add esi,idx

        .while ( oldofs < newofs && len )
            lodsb
            tsprintf( edi, "%02X", eax )
            add edi,2
            inc idx
            inc oldofs
            dec len
        .endw
        mov byte ptr [edi],' '
        .endc

    .case LSTTYPE_EQUATE
        ; v2.10: display current offset if equate is an alias for a label in this segment
        mov edi,1
        mov esi,sym
        .if ( [esi].asym.segm && [esi].asym.segm == ebx )
            tsprintf( &ll.buffer, "%08X", GetCurrOffset() )
            mov edi,10
        .endif
        mov ll.buffer[edi],'='
        .if ( [esi].asym.value3264 != 0 && ( [esi].asym.value3264 != -1 || [esi].asym.value >= 0 ) )
            tsprintf( &ll.buffer[edi+2], "%-" PREFFMTSTR "lX", [esi].asym.value, [esi].asym.value3264 )
        .else
            tsprintf( &ll.buffer[edi+2], "%-" PREFFMTSTR "X", [esi].asym.value )
        .endif
        mov ll.buffer[edi+22],' ' ; v2.25 - binary zero fix -- John Hankinson
        .endc

    .case LSTTYPE_TMACRO
        mov ll.buffer[1],'='
        mov ecx,sym
        .for ( esi = [ecx].asym.string_ptr, edi = &ll.buffer[3], ebx = &ll : byte ptr [esi] : )
            lea eax,[ebx].lstleft.buffer[28]
            .if ( edi >= eax )
                mov [ebx].lstleft.next,alloca( sizeof( lstleft ) )
                mov ebx,eax
                mov [ebx].lstleft.next,NULL
                memset( &[ebx].lstleft.buffer, ' ', sizeof( ll.buffer ) )
                lea edi,[ebx].lstleft.buffer[3]
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
        .if ( ebx || value )
            tsprintf( &ll.buffer, "%08X", oldofs )
            mov ll.buffer[8],' '
        .endif
        .endc
    .default ; LSTTYPE_MACRO
        mov ecx,pSrcline
        mov dl,[ecx]
        .if ( dl == 0 && ModuleInfo.CurrComment == NULL && srcfile == ModuleInfo.srcfile )
            fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*4] )
            add list_pos,NLSIZ
            .return
        .endif
        .endc
    .endsw

    .if ( Parse_Pass == PASS_1 || UseSavedState == FALSE )
        mov idx,sizeof( ll.buffer )
        .if ( ModuleInfo.GeneratedCode )
            mov ll.buffer[28],'*'
        .endif
        .if ( MacroLevel )
            mov len,tsprintf( &ll.buffer[29], "%u", MacroLevel )
            mov ll.buffer[29+eax],' '
        .endif
        .if ( srcfile != ModuleInfo.srcfile )
            mov ll.buffer[30],'C'
        .endif
    .else
        mov idx,OFSSIZE + 2 + 2 * CODEBYTES
    .endif
    fwrite( &ll.buffer, 1, idx, CurrFile[LST*4] )

    mov len,strlen( pSrcline )
    mov len2,0
    .if ( ModuleInfo.CurrComment )
        mov len2,strlen( ModuleInfo.CurrComment )
    .endif
    mov eax,len2
    add eax,len
    add eax,sizeof( ll.buffer ) + NLSIZ
    add list_pos,eax

    ; write source and comment part

    .if ( Parse_Pass == PASS_1 || UseSavedState == FALSE )
        .if ( len )
            fwrite( pSrcline, 1, len, CurrFile[LST*4] )
        .endif
        .if ( len2 )
            fwrite( ModuleInfo.CurrComment, 1, len2, CurrFile[LST*4] )
        .endif
        fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*4] )
    .endif

    ; write optional additional lines.
    ; currently works in pass one only.

    .for ( ebx = ll.next: ebx: ebx = [ebx].lstleft.next )
        fwrite( &[ebx].lstleft.buffer, 1, 32, CurrFile[LST*4] )
        fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*4] )
        add list_pos,32 + NLSIZ
    .endf
    ret

LstWrite endp

LstWriteSrcLine proc

    LstWrite( LSTTYPE_MACRO, 0, NULL )
    ret

LstWriteSrcLine endp

LstPrintf proc format:string_t, args:vararg

    .if ( CurrFile[LST*4] )

        add list_pos,tvfprintf( CurrFile[LST*4], format, &args )
    .endif
    ret

LstPrintf endp

LstNL proc

    .if ( CurrFile[LST*4] )
        fwrite( NLSTR, 1, NLSIZ, CurrFile[LST*4] )
        add list_pos,NLSIZ
    .endif
    ret

LstNL endp

; set the list file's position
; this is only needed if generated code is to be
; executed BEFORE the original source line is listed.

LstSetPosition proc

    .if ( CurrFile[LST*4] && \
          Parse_Pass > PASS_1 && \
          UseSavedState && \
          ModuleInfo.GeneratedCode == 0 )

        mov list_pos,LineStoreCurr.get_pos()
        fseek( CurrFile[LST*4], list_pos, SEEK_SET )
        or ModuleInfo.line_flags,LOF_SKIPPOS
    .endif
    ret

LstSetPosition endp

    option proc: private

get_seg_align proc fastcall s:ptr seg_info, buffer:string_t

    movzx ecx,[ecx].seg_info.alignment
    .switch( ecx )
    .case 0: .return( strings[LS_BYTE]  )
    .case 1: .return( strings[LS_WORD]  )
    .case 2: .return( strings[LS_DWORD] )
    .case 3: .return( strings[LS_QWORD] )
    .case 4: .return( strings[LS_PARA]  )
    .case 8: .return( strings[LS_PAGE]  )
    .case MAX_SEGALIGNMENT: .return( strings[LS_ABS] )
    .default
        mov eax,1
        shl eax,cl
        push buffer
        tsprintf( buffer, "%u", eax )
        pop eax
    .endsw
    ret

get_seg_align endp

get_seg_combine proc fastcall s:ptr seg_info

    .switch( [ecx].seg_info.combine )
    .case COMB_INVALID:    .return( strings[LS_PRIVATE] )
    .case COMB_STACK:      .return( strings[LS_STACK]   )
    .case COMB_ADDOFF:     .return( strings[LS_PUBLIC]  )
    ; v2.06: added
    .case COMB_COMMON:     .return( strings[LS_COMMON]  )
    .endsw
    .return( "?" )

get_seg_combine endp

log_macro proc sym:ptr asym

    mov ecx,sym
    mov eax,[ecx].asym.name_size
    mov edx,strings[LS_PROC]
    .if ( [ecx].asym.mac_flag &  M_ISFUNC )
        mov edx,strings[LS_FUNC]
    .endif
    .if ( eax >= DOTSMAX )
        lea eax,@CStr("")
    .else
        lea eax,dots[eax+1]
    .endif
    LstPrintf( "%s %s        %s", [ecx].asym.name, eax, edx )
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
    .switch ( ecx )
    .case 1: .return( strings[LS_BYTE] )
    .case 2: .return( strings[LS_WORD] )
    .case 4: .return( strings[LS_DWORD] )
    .case 6: .return( strings[LS_FWORD] )
    .case 8: .return( strings[LS_QWORD] )
    .case 10:.return( strings[LS_TBYTE] )
    .case 16:.return( strings[LS_OWORD] )
    .case 32:.return( strings[LS_YWORD] )
    .case 64:.return( strings[LS_ZWORD] )
    .endsw
    .return( "" )

SimpleTypeString endp

; called by log_and log_typedef
; that is, the symbol is ensured to be a TYPE!
; argument 'buffer' is either NULL or "very" large ( StringBufferEnd ).

GetMemtypeString proc uses esi edi ebx sym:ptr asym, buffer:string_t

  local i:int_t
  local mem_type:byte

    mov esi,sym

    .if ( !( [esi].asym.mem_type & MT_SPECIAL) )
        .return( SimpleTypeString( [esi].asym.mem_type ) )
    .endif

    ; v2.05: improve display of stack vars
    mov mem_type,[esi].asym.mem_type
    .if ( [esi].asym.state == SYM_STACK && [esi].asym.is_ptr )
        mov mem_type,MT_PTR
    .endif

    .switch ( mem_type )
    .case MT_PTR
        .if ( [esi].asym.Ofssize == USE64 )
            mov edi,strings[LS_NEAR]
        .else
            movzx ecx,[esi].asym.Ofssize
            .if ( [esi].asym.is_far )
                mov edi,strings[LS_FAR16+ecx*4]
            .else
                mov edi,strings[LS_NEAR16+ecx*4]
            .endif
        .endif

        .if ( buffer ) ; Currently, 'buffer' is only != NULL for typedefs

            mov ebx,buffer

            ; v2.10: improved pointer TYPEDEF display

            .for ( i = [esi].asym.is_ptr: i: i-- )
                add ebx,tsprintf( ebx, "%s %s ", edi, strings[LS_PTR] )
            .endf

            ; v2.05: added.

            .if ( [esi].asym.state == SYM_TYPE && [esi].asym.typekind == TYPE_TYPEDEF )
                .if ( [esi].asym.target_type )
                    mov ecx,[esi].asym.target_type
                    strcpy( ebx, [ecx].asym.name )
                .elseif ( !( [esi].asym.ptr_memtype & MT_SPECIAL ) )
                    strcpy( ebx, SimpleTypeString( [esi].asym.ptr_memtype ) )
                .endif
            .endif
            .return( buffer )
        .endif
        .return( edi )
    .case MT_FAR
        .if ( [esi].asym.segm )
            .return( strings[LS_LFAR] )
        .endif
        mov ecx,GetSymOfssize( esi )
        .return( strings[LS_LFAR16+ecx*4] )
    .case MT_NEAR
        .if ( [esi].asym.segm )
            .return( strings[LS_LNEAR] )
        .endif
        mov ecx,GetSymOfssize( esi )
        .return( strings[LS_LNEAR16+ecx*4] )
    .case MT_TYPE
        mov ecx,[esi].asym.type
        mov eax,[ecx].asym.name
        .if ( byte ptr [eax] )  ;; there are a lot of unnamed types
            .return( eax )
        .endif
        .return( GetMemtypeString( [esi].asym.type, buffer ) )
    .case MT_EMPTY ; number = via EQU or directive
        .return( strings[LS_NUMBER] )
    .endsw
    .return("?")

GetMemtypeString endp

GetLanguage proc fastcall sym:ptr asym

    movzx eax,[ecx].asym.langtype
    .if ( eax <= LANG_WATCALL )
        .return( strings[eax*4 + LS_VOID] )
    .endif
    .return( "?" )

GetLanguage endp

; display STRUCTs and UNIONs

log_struct proc uses esi edi ebx sym:ptr asym, name:string_t, ofs:int_32

  local pdots:string_t

    .data
     prefix int_t 0
    .code

    mov edi,sym
    mov esi,[edi].dsym.structinfo

    .if ( !name )
        mov name,[edi].asym.name
    .endif
    .if ( strlen(name) >= DOTSMAX )
        lea ecx,@CStr("")
    .else
        lea ecx,dots[eax+1]
    .endif
    .if ( [esi].struct_info.alignment > 1 )
        LstPrintf( "%s %s        %8X (%u)",
            name, ecx, [edi].asym.total_size, [esi].struct_info.alignment )
    .else
        LstPrintf( "%s %s        %8X", name, ecx, [edi].asym.total_size )
    .endif

    LstNL()
    add prefix,2

    assume ebx:ptr sfield

    .for( ebx = [esi].struct_info.head : ebx : ebx = [ebx].next )

        .if ( [ebx].mem_type == MT_TYPE && [ebx].ivalue[0] == NULLC )

            mov ecx,[ebx].offs
            add ecx,ofs
            log_struct( [ebx].type, [ebx].name, ecx )

        .else

            ; don't list unstructured fields without name
            ; but do list them if they are structured

            mov ecx,[ebx].name

            .if ( byte ptr [ecx] || ( [ebx].mem_type == MT_TYPE ) )

                mov eax,[ebx].name_size
                add eax,prefix
                mov ecx,eax
                add eax,offset dots
                inc eax
                .if ( ( ecx >= DOTSMAX ) )
                    lea eax,@CStr("")
                .endif
                mov pdots,eax
                .for ( esi = 0: esi < prefix: esi++ )
                    LstPrintf(" ")
                .endf
                mov ecx,[ebx].offs
                add ecx,[edi].asym.offs
                add ecx,ofs
                LstPrintf( "%s %s        %8X   ", [ebx].name, pdots, ecx )
                LstPrintf( "%s", GetMemtypeString( ebx, NULL ) )
                .if ( [ebx].flag1 & S_ISARRAY )
                    LstPrintf( "[%u]", [ebx].total_length )
                .endif
                LstNL()
            .endif
        .endif
    .endf
    sub prefix,2
    ret

log_struct endp

log_record proc uses esi edi ebx sym:ptr asym

  local mask:qword
  local pdots:string_t

    mov edi,sym
    lea eax,dots[1]
    .if ( [edi].asym.name_size >= DOTSMAX )
        lea eax,@CStr("")
    .endif
    mov pdots,eax
    mov esi,[edi].dsym.structinfo

    .for ( edx = 0, ebx = [esi].struct_info.head: ebx: ebx = [ebx].next, edx++ )
    .endf

    imul ecx,[edi].asym.total_size,8
    LstPrintf( "%s %s      %6X  %7X", [edi].asym.name, pdots, ecx, edx )
    LstNL()

    .for ( ebx = [esi].struct_info.head: ebx: ebx = [ebx].next )

        mov eax,[ebx].name_size
        add eax,2
        mov ecx,eax
        add eax,offset dots
        inc eax
        .if ( ( ecx >= DOTSMAX ) )
            lea eax,@CStr("")
        .endif
        mov pdots,eax
        xor eax,eax
        mov dword ptr mask[0],eax
        mov dword ptr mask[4],eax
        mov esi,[ebx].offs
        add esi,[ebx].total_size

        .for ( ecx = [ebx].offs, edx = 0: ecx < esi: ecx++ )

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

        lea ecx,@CStr("?")
        .if ( [ebx].ivalue )
            lea ecx,[ebx].ivalue
        .endif
        .if ( [edi].asym.total_size > 4 )
            LstPrintf( "  %s %s      %6X  %7X  %016lX %s",
                [ebx].name, pdots, [ebx].offs, [ebx].total_size, mask, ecx )
        .else
            LstPrintf( "  %s %s      %6X  %7X  %08X %s",
                [ebx].name, pdots, [ebx].offs, [ebx].total_size, mask, ecx )
        .endif
        LstNL()
    .endf
    ret

log_record endp

    assume ebx:nothing

; a typedef is a simple with no fields. Size might be 0.

log_typedef proc uses esi edi ebx sym:ptr asym

  local pdots:string_t

    mov esi,sym
    mov ecx,[esi].asym.name_size
    lea eax,dots[ecx+1]
    .if ( ecx >= DOTSMAX )
        lea eax,@CStr("")
    .endif
    mov pdots,eax

    mov edi,StringBufferEnd
    mov byte ptr [edi],NULLC
    mov ebx,[esi].asym.target_type

    .if ( [esi].asym.mem_type == MT_PROC && ebx ) ; typedef proto?

        strcat( edi, strings[LS_PROC] )
        strcat( edi, " " )
        mov ecx,[ebx].asym.name
        .if ( byte ptr [ecx] ) ; the name may be ""
            strcat( edi, ecx )
            strcat( edi, " ")
        .endif

        ; v2.11: target_type has state SYM_TYPE (since v2.09).
        ; This state isn't handled properly by GetSymOfsSize(),
        ; which is called by GetMemtypeString(), so get the strings here.

        mov ecx,LS_LFAR16
        .if ( [ebx].asym.mem_type == MT_NEAR )
            mov ecx,LS_LNEAR16
        .endif
        movzx eax,[esi].asym.Ofssize
        lea ecx,[ecx+eax*4]
        strcat( edi, strings[ecx] )
        strcat( edi, " " )
        strcat( edi, GetLanguage( [esi].asym.target_type ) )
    .else
        mov edi,GetMemtypeString( esi, edi )
    .endif
    LstPrintf( "%s %s    %8u  %s", [esi].asym.name, pdots, [esi].asym.total_size, edi )
    LstNL()
    ret

log_typedef endp

log_segment proc uses esi edi ebx sym:ptr asym, grp:ptr asym

  local buffer[32]:sbyte

    mov esi,sym
    mov edi,[esi].dsym.seginfo

    .if ( [edi].seg_info.sgroup == grp )

        mov eax,[esi].asym.name_size
        lea ecx,dots[eax+1]
        .if ( eax >= DOTSMAX )
            lea ecx,@CStr("")
        .endif
        LstPrintf( "%s %s        ", [esi].asym.name, ecx )
        .if ( [edi].seg_info.Ofssize == USE32 )
            LstPrintf( "32 Bit   %08X ", [esi].asym.max_offset )
        .elseif ( [edi].seg_info.Ofssize == USE64 )
            LstPrintf( "64 Bit   %08X ", [esi].asym.max_offset )
        .else
            LstPrintf( "16 Bit   %04X     ", [esi].asym.max_offset )
        .endif
        mov ebx,get_seg_align( edi, &buffer )
        LstPrintf( "%-7s %-8s", ebx, get_seg_combine( edi ) )
        lea ecx,@CStr("")
        mov edx,[edi].seg_info.clsym
        .if ( edx )
            mov ecx,[edx].asym.name
        .endif
        LstPrintf( "'%s'", ecx )
        LstNL()
    .endif
    ret

log_segment endp

log_group proc uses esi edi grp:ptr asym, segs:ptr dsym

    mov esi,grp
    mov eax,[esi].asym.name_size
    lea ecx,dots[eax+1]
    .if ( eax >= DOTSMAX )
        lea ecx,@CStr("")
    .endif

    LstPrintf( "%s %s        %s", [esi].asym.name, ecx, strings[LS_GROUP] )
    LstNL()

    ; the FLAT groups is always empty

    .if ( esi == ModuleInfo.flat_grp )
        .for( edi = segs : edi : edi = [edi].dsym.next )
            log_segment( edi, esi )
        .endf
    .else
        mov edi,[esi].dsym.grpinfo
        .for( edi = [edi].grp_info.seglist : edi : edi = [edi].seg_item.next )
            log_segment( [edi].seg_item.iseg, esi )
        .endf
    .endif
    ret

log_group endp

get_proc_type proc fastcall sym:ptr asym

    ; if there's no segment associated with the symbol,
    ; add the symbol's offset size to the distance

    .switch( [ecx].asym.mem_type )
    .case MT_NEAR
        .if ( [ecx].asym.segm == NULL )
            GetSymOfssize( ecx )
            .return( strings[eax*4+LS_NEAR16] )
        .endif
        .return( strings[LS_NEAR] )
    .case MT_FAR
        .if ( [ecx].asym.segm == NULL )
            GetSymOfssize( ecx )
            .return( strings[eax*4+LS_FAR16] )
        .endif
        .return( strings[LS_FAR] )
    .endsw
    .return( " " )

get_proc_type endp


get_sym_seg_name proc fastcall sym:ptr asym

    .if ( [ecx].asym.segm )
        mov ecx,[ecx].asym.segm
        .return( [ecx].asym.name )
    .else
        .return( strings[LS_NOSEG] )
    .endif
    ret

get_sym_seg_name endp

; list Procedures and Prototypes

log_proc proc uses esi edi ebx sym:ptr asym

  local Ofssize:byte
  local p:string_t
  local pdots:string_t
  local buffer[32]:char_t

    mov esi,sym
    mov Ofssize,GetSymOfssize( esi )

    mov eax,[esi].asym.name_size
    lea ecx,dots[eax+1]
    .if ( eax >= DOTSMAX )
        lea ecx,@CStr("")
    .endif
    mov pdots,ecx

    lea edi,@CStr("%s %s        P %-6s %04X     %-8s ")
    .if ( Ofssize )
        lea edi,@CStr("%s %s        P %-6s %08X %-8s ")
    .endif
    mov p,edi
    mov ebx,get_proc_type( esi )
    LstPrintf( edi, [esi].asym.name, pdots, ebx, [esi].asym.offs, get_sym_seg_name( esi ) )

    ; externals (PROTO) don't have a size. Masm always prints 0000 or 00000000

    mov ecx,4
    .if ( Ofssize > USE16 )
        mov ecx,8
    .endif
    xor edx,edx
    .if ( [esi].asym.state == SYM_INTERNAL )
        mov edx,[esi].asym.total_size
    .endif
    LstPrintf( "%0*X ", ecx, edx )

    .if ( [esi].asym.flags & S_ISPUBLIC )
        LstPrintf( "%-9s", strings[LS_PUBLIC] )
    .elseif ( [esi].asym.state == SYM_INTERNAL )
        LstPrintf( "%-9s", strings[LS_PRIVATE] )
    .else
        lea ecx,@CStr("%-9s ")
        .if ( [esi].asym.sflags & S_WEAK )
            lea ecx,@CStr("*%-8s ")
        .endif
        LstPrintf( ecx, strings[LS_EXTERNAL] )
        mov ecx,[esi].asym.dll
        .if ( ecx )
            LstPrintf( "(%.8s) ", &[ecx].dll_desc.name )
        .endif
    .endif

    LstPrintf( "%s", GetLanguage( esi ) )
    LstNL()

    ; for PROTOs, list optional altname

    .if ( [esi].asym.state == SYM_EXTERNAL && [esi].asym.altname )

        LstPrintf( "  ")
        mov ebx,[esi].asym.altname
        push get_proc_type( ebx )
        get_sym_seg_name( ebx )
        pop ecx
        mov edx,pdots
        add edx,2
        LstPrintf( edi, [ebx].asym.name, edx, ecx, [ebx].asym.offs, eax )
        LstNL()
    .endif

    ; for PROCs, list parameters and locals

    .if ( [esi].asym.state == SYM_INTERNAL )

        ; print the procedure's parameters

        movzx eax,[esi].asym.langtype
        .if ( eax == LANG_STDCALL || eax == LANG_C || eax == LANG_SYSCALL || eax == LANG_VECTORCALL || \
             ( eax == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) )

            .new cnt:int_t

            ; position f2 to last param

            mov ecx,[esi].dsym.procinfo
            .for ( cnt = 0, ecx = [ecx].proc_info.paralist: ecx: ecx = [ecx].dsym.nextparam )
                inc cnt
            .endf
            .for ( : cnt: cnt-- )

                mov edi,[esi].dsym.procinfo
                .for ( ecx = 1, edi = [edi].proc_info.paralist: ecx < cnt: edi = [edi].dsym.nextparam, ecx++ )
                .endf
                mov eax,[edi].asym.name_size
                lea ecx,dots[eax+1+2]
                .if ( eax >= DOTSMAX-2 )
                    lea ecx,@CStr("")
                .endif
                mov pdots,ecx

                ; FASTCALL: parameter may be a text macro (=register name)

                .if ( [edi].asym.state == SYM_TMACRO )
                    LstPrintf( "  %s %s        %-17s %s",
                        [edi].asym.name, pdots, GetMemtypeString( edi, NULL ), [edi].asym.string_ptr )
                .else
                    mov ecx,[esi].dsym.procinfo
                    mov edx,GetResWName( [ecx].proc_info.basereg, NULL )
                    mov ecx,GetMemtypeString( edi, NULL )
                    .if ( [edi].asym.sflags & S_ISVARARG )
                        mov ecx,strings[LS_VARARG]
                    .endif
                    LstPrintf( szFmtProcStk, [edi].asym.name, pdots, ecx, edx, '+', [edi].asym.offs )
                .endif
                LstNL()
            .endf
        .else
            mov edi,[esi].dsym.procinfo
            .for ( edi = [edi].proc_info.paralist: edi : edi = [edi].dsym.nextparam )

                mov eax,[edi].asym.name_size
                lea ecx,dots[eax+1+2]
                .if ( eax >= DOTSMAX-2 )
                    lea ecx,@CStr("")
                .endif
                mov pdots,ecx
                mov ecx,[esi].dsym.procinfo
                mov ebx,GetResWName( [ecx].proc_info.basereg, NULL )
                LstPrintf( szFmtProcStk, [edi].asym.name, pdots, GetMemtypeString( edi, NULL ),
                          ebx, '+', [edi].asym.offs )
                LstNL()
            .endf
        .endif

        ; print the procedure's locals

        mov edi,[esi].dsym.procinfo
        .for ( edi = [edi].proc_info.locallist: edi : edi = [edi].dsym.nextlocal )

            mov eax,[edi].asym.name_size
            lea ecx,dots[eax+1+2]
            .if ( eax >= DOTSMAX-2 )
                lea ecx,@CStr("")
            .endif
            mov pdots,ecx

            .if ( [edi].asym.flag1 & S_ISARRAY )
                tsprintf( &buffer, "%s[%u]", GetMemtypeString( edi, NULL), [edi].asym.total_length )
            .else
                strcpy( &buffer, GetMemtypeString( edi, NULL ) )
            .endif
            mov ecx,[esi].dsym.procinfo
            mov ebx,GetResWName( [ecx].proc_info.basereg, NULL )
            mov ecx,'+'
            mov edx,[edi].asym.offs
            .ifs ( edx < 0 )
                mov ecx,'-'
                neg edx
            .endif
            LstPrintf( szFmtProcStk, [edi].asym.name, pdots, &buffer, ebx, ecx, edx )
            LstNL()
        .endf

        mov edi,[esi].dsym.procinfo
        .for ( edi = [edi].proc_info.labellist: edi : edi = [edi].dsym.nextll )

            .for ( ebx = edi: ebx: ebx = [ebx].asym.nextitem )

                ; filter params and locals!

                .if ( [ebx].asym.state == SYM_STACK || [ebx].asym.state == SYM_TMACRO )
                    .continue
                .endif
                mov eax,[edi].asym.name_size
                lea ecx,dots[eax+1+2]
                .if ( eax >= DOTSMAX-2 )
                    lea ecx,@CStr("")
                .endif
                mov pdots,ecx
                .if ( Ofssize )
                    lea eax,@CStr("  %s %s        L %-6s %08X %s")
                .else
                    lea eax,@CStr("  %s %s        L %-6s %04X     %s")
                .endif
                mov p,eax
                push get_proc_type( ebx )
                get_sym_seg_name( ebx )
                pop ecx
                LstPrintf( p, [ebx].asym.name, pdots, ecx, [ebx].asym.offs, eax )
                LstNL()
            .endf
        .endf
    .endif
    ret

log_proc endp

; list symbols

log_symbol proc uses esi edi ebx sym:ptr asym

  local pdots:string_t

    mov edi,sym
    mov eax,[edi].asym.name_size
    lea ecx,dots[eax+1]
    .if ( eax >= DOTSMAX )
        lea ecx,@CStr("")
    .endif
    mov pdots,ecx

    .switch ( [edi].asym.state )
    .case SYM_UNDEFINED
    .case SYM_INTERNAL
    .case SYM_EXTERNAL
        LstPrintf( "%s %s        ", [edi].asym.name, pdots )

        .if ( [edi].asym.flag1 & S_ISARRAY )
            mov ebx,tsprintf( StringBufferEnd, "%s[%u]", GetMemtypeString( edi, NULL ), [edi].asym.total_length )
            LstPrintf( "%-10s ", StringBufferEnd )
        .elseif ( [edi].asym.state == SYM_EXTERNAL && [edi].asym.sflags & S_ISCOM )
            LstPrintf( "%-10s ", strings[LS_COMM] )
        .else
            LstPrintf( "%-10s ", GetMemtypeString( edi, NULL ) )
        .endif

        ; print value

        .if ( [edi].asym.state == SYM_EXTERNAL && [edi].asym.sflags & S_ISCOM )
            mov eax,[edi].asym.total_size
            cdq
            div [edi].asym.total_length
            LstPrintf( " %8Xh ", eax )
        .elseif ( [edi].asym.mem_type == MT_EMPTY )
            ; also check segment? might be != NULL for equates (var = offset x)
            .if ( [edi].asym.value3264 != 0 && [edi].asym.value3264 != -1 )
                LstPrintf( " %lXh ", [edi].asym.uvalue, [edi].asym.value3264 )
            .elseif ( [edi].asym.value3264 < 0 )
                xor ecx,ecx
                sub ecx,[edi].asym.uvalue
                LstPrintf( "-%08Xh ", ecx )
            .else
                LstPrintf( " %8Xh ", [edi].asym.offs )
            .endif
        .else
            LstPrintf( " %8Xh ", [edi].asym.offs )
        .endif

        ; print segment

        .if ( [edi].asym.segm )
            LstPrintf( "%s ", get_sym_seg_name( edi ) )
        .endif

        .if ( [edi].asym.state == SYM_EXTERNAL && [edi].asym.sflags & S_ISCOM )
            LstPrintf( "%s=%u ", szCount, [edi].asym.total_length )
        .endif

        .if ( [edi].asym.flags & S_ISPUBLIC )
            LstPrintf( "%s ", strings[LS_PUBLIC] )
        .endif

        .if ( [edi].asym.state == SYM_EXTERNAL )
            lea ecx,@CStr("%s ")
            .if ( [edi].asym.sflags & S_WEAK )
                 lea ecx,@CStr("*%s ")
            .endif
            LstPrintf( ecx, strings[LS_EXTERNAL] )
        .elseif ( [edi].asym.state == SYM_UNDEFINED )
            LstPrintf( "%s ", strings[LS_UNDEFINED] )
        .endif

        LstPrintf( "%s", GetLanguage( edi ) )
        LstNL()
        .endc
    .case SYM_TMACRO
        LstPrintf( "%s %s        %s   %s", [edi].asym.name, pdots, strings[LS_TEXT], [edi].asym.string_ptr )
        LstNL()
        .endc
    .case SYM_ALIAS
        mov ecx,[edi].asym.substitute
        LstPrintf( "%s %s        %s  %s", [edi].asym.name, pdots, strings[LS_ALIAS], [ecx].asym.name )
        LstNL()
        .endc
    .endsw
    ret

log_symbol endp

LstCaption proc uses esi caption:string_t, prefNL:int_t

    .for ( esi = prefNL : esi : esi-- )
        LstNL()
    .endf
    LstPrintf( caption )
    LstNL()
    LstNL()
    ret

LstCaption endp

compare_syms proc p1:ptr, p2:ptr

    mov ecx,p1
    mov edx,p2
    mov ecx,[ecx]
    mov edx,[edx]
    .return( strcmp( [ecx].asym.name, [edx].asym.name ) )

compare_syms endp

    option proc: public

; write symbol table listing

LstWriteCRef proc uses esi edi ebx

  local syms:ptr ptr asym
  local dir:ptr dsym
  local s:ptr struct_info
  local idx:int_t
  local i:uint_32
  local SymCount:uint_32
  local queues[LQ_LAST]:qdesc

    ; no point going through the motions if lst file isn't open

    .if ( CurrFile[LST*4] == NULL || Options.no_symbol_listing == TRUE )
        .return
    .endif

    ; go to EOF

    fseek( CurrFile[LST*4], 0, SEEK_END )

    mov SymCount,SymGetCount()
    mov syms,MemAlloc( &[eax * sizeof( asym_t )] )
    SymGetAll( syms )

    ; sort 'em
    qsort( syms, SymCount, sizeof( asym_t ), compare_syms )
    memset( &queues, 0, sizeof( queues ) )

    .for ( ebx = 0: ebx < SymCount: ++ebx )

        mov ecx,syms
        mov edi,[ecx+ebx*4]

        ;qdesc *q
        .continue .if !( [edi].asym.flag1 & S_LIST )

        .switch ( [edi].asym.state )
        .case SYM_TYPE

            mov s,[edi].dsym.structinfo

            .switch ( [edi].asym.typekind )
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
            .if ( [edi].asym.flag1 & S_ISPROC )
                mov ecx,LQ_PROCS
                .endc
            .endif
            ; no break
        .default
            .continue
        .endsw
        lea edx,queues[ecx*qdesc]
        .if ( [edx].qdesc.head == NULL )
            mov [edx].qdesc.head,edi
        .else
            mov eax,[edx].qdesc.tail
            mov [eax].dsym.next,edi
        .endif
        mov [edx].qdesc.tail,edi
        mov [edi].dsym.next,NULL
    .endf

    .for ( ebx = 0: ebx < lengthof(cr): ebx++ )
        imul edi,ebx,print_item
        movzx ecx,cr[edi].type

        .if ( queues[ecx*qdesc].head )
            .if ( cr[edi].capitems )
                .for ( esi = cr[edi].capitems: word ptr [esi]: esi += 2 )
                    mov eax,2
                    .if ( esi != cr[edi].capitems )
                        xor eax,eax
                    .endif
                    movzx ecx,word ptr [esi]
                    LstCaption( strings[ecx], eax )
                .endf
            .endif
            movzx ecx,cr[edi].type
            .for ( esi = queues[ecx*qdesc].head: esi : esi = [esi].dsym.next )
                xor ecx,ecx
                .if ( cr[edi].flags & PRF_ADDSEG )
                    mov ecx,queues[LQ_SEGS*qdesc].head
                .endif
                cr[edi].function( esi, ecx, 0 )
            .endf
        .endif
    .endf

    ; write out symbols
    LstCaption( strings[ LS_TXT_SYMBOLS ], 2 )
    LstCaption( strings[ LS_TXT_SYMCAP ], 0 )
    .for ( ebx = 0: ebx < SymCount: ++ebx )
        mov ecx,syms
        mov edi,[ecx+ebx*4]
        .if ( [edi].asym.flag1 & S_LIST && !( [edi].asym.flag1 & S_ISPROC ) )
            log_symbol( edi )
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

    assume ebx:ptr asm_tok

ListingDirective proc uses esi ebx i:int_t, tokenarray:ptr asm_tok

    mov  esi,i
    imul ebx,esi,asm_tok
    add  ebx,tokenarray
    mov  eax,[ebx].tokval
    inc  esi
    add  ebx,16

    .switch ( eax )
    .case T_DOT_LIST
        .if ( CurrFile[LST*4] )
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

            .if ( [ebx].token != T_ID )
                .return( asmerr( 2008, [ebx].tokpos ) )
            .endif

            ; the name may be a forward reference. In this case it will
            ; be created here.
            ; v2.11: function call cannot fail. no need for checks.

            SymLookup( [ebx].string_ptr )
            and [eax].asym.flag1,not S_LIST
            inc esi
            add ebx,16

            .if ( esi < Token_Count )
                .if ( [ebx].token != T_COMMA )
                    .return( asmerr( 2008, [ebx].tokpos ) )
                .endif

                ; if there's nothing after the comma, don't increment

                mov ecx,Token_Count
                dec ecx
                .if ( esi < ecx )
                    inc esi
                    add ebx,16
                .endif
            .endif
        .until !( esi < Token_Count )
        .endc
    .case T_DOT_LISTALL ; list false conditionals and generated code
        .if ( CurrFile[LST*4] )
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

        .endc .if ( [ebx].token == T_COLON )

        ; this isn't really Masm-compatible, but ensures we don't get
        ; fields with names page, title, subtitle, subttl.

        .if ( CurrStruct )
            .return( asmerr( 2037 ) )
        .endif
        .if ( Parse_Pass == PASS_1 )
            asmerr( 7005, [ebx-16].string_ptr )
        .endif
        .while ( [ebx].token != T_FINAL)
            inc esi
            add ebx,16
        .endw
    .endsw

    .if ( [ebx].token != T_FINAL )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif
    .return( NOT_ERROR )

ListingDirective endp

; directives .[NO]LISTMACRO, .LISTMACROALL, .[X|L|S]ALL

ListMacroDirective proc i:int_t, tokenarray:ptr asm_tok

    imul ecx,i,asm_tok
    add ecx,tokenarray
    .if ( [ecx+16].asm_tok.token != T_FINAL )
        .return( asmerr( 2008, [ecx+16].asm_tok.string_ptr ) )
    .endif
    mov ModuleInfo.list_macro,GetSflagsSp( [ecx].asm_tok.tokval )
    .return( NOT_ERROR )

ListMacroDirective endp

LstInit proc uses esi

  local buffer[128]:char_t
    mov list_pos,0
    .if ( Options.write_listing )
        mov list_pos,strlen( &cp_logo )
        fwrite( &cp_logo, 1, list_pos, CurrFile[LST*4] )
        LstNL()
        mov esi,GetFName( ModuleInfo.srcfile )
        add list_pos,strlen( esi )
        fwrite( esi, 1, eax, CurrFile[LST*4] )
        LstNL()
    .endif
    ret

LstInit endp

    end
