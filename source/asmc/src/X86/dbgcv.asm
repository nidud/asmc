; DBGCV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: Generate CodeView symbolic debug info
;

include stddef.inc
include direct.inc
include MD5.inc

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include coff.inc
include fixup.inc
include dbgcv.inc
include linnum.inc

extern CV8Label:ptr asym

define SIZE_CV_SEGBUF ( MAX_LINE_LEN * 2 )

define EQUATESYMS 1 ;; 1=generate info for EQUates ( -Zi3 )

szCVCompiler equ <"Asmc Macro Assembler">

.pragma pack(push, 1)

.template cvfile
    name string_t ?
    offs dd ? ; offset into string table
   .ends

.template cvsection
    signature dd ?
    length dd ?
   .ends

;; structure for field enumeration callback function

.template counters
    cnt  dd ? ; number of fields
    size dd ? ; size of field list
    ofs  dd ? ; current start offset for member
   .ends

.template leaf32
    leaf dw ?
    value32 dd ?
   .ends

.pragma pack(pop)

;; type of field enumeration callback function
CALLBACK(cv_enum_func, :ptr dbgcv, :ptr dsym, :ptr asym, :ptr counters)

.class dbgcv

    ps ptr byte ?
    pt ptr byte ?

    section ptr cvsection ?
    symbols ptr dsym ?
    types ptr dsym ?
    param ptr ?
    level dd ?          ; nesting level
    currtype dd ?       ; current type ( starts with 0x1000 )
    files ptr cvfile ?
    currdir string_t ?

    flushpt proc fastcall :dword
    flushps proc fastcall :dword
    padbytes proc fastcall :ptr byte
    alignps proc fastcall
    flush_section proc :dword, :dword

    write_bitfield proc :ptr dsym, :ptr asym
    write_array_type proc :ptr asym, :dword, :byte
    write_ptr_type proc fastcall :ptr asym
    write_type proc :ptr asym
    write_type_procedure proc :ptr asym, :int_t
    write_symbol proc :ptr asym

    cntproc proc stdcall :ptr dsym, :ptr asym, :ptr counters
    memberproc proc stdcall :ptr dsym, :ptr asym, :ptr counters
    enum_fields proc :ptr dsym, :cv_enum_func, :ptr counters

   .ends

   .data

padtab db LF_PAD1, LF_PAD2, LF_PAD3
reg64  db 0, 2, 3, 1, 7, 6, 4, 5

   .code

;; translate symbol's mem_type to a codeview typeref

GetTyperef proc uses esi sym:ptr asym, Ofssize:byte

    mov esi,sym
    mov cl,[esi].asym.mem_type
    .if ( !( cl & MT_SPECIAL ) )
        SizeFromMemtype( cl, Ofssize, [esi].asym.type )
        mov cl,[esi].asym.mem_type
        .if ( cl & MT_FLOAT )
            .switch eax
            .case 2  : .return ST_REAL16
            .case 4  : .return ST_REAL32
            .case 8  : .return ST_REAL64
            .case 10 : .return ST_REAL80
            .case 16 : .return ST_UINT8
            .endsw
        .else
            .if ( cl & MT_SIGNED )
                .switch eax
                .case 1  : .return ST_CHAR
                .case 2  : .return ST_INT2
                .case 4  : .return ST_INT4
                .case 8  : .return ST_INT8
                .case 16 : .return ST_UINT8
                .endsw
            .else
                .switch eax
                .case 1  : .return ST_UCHAR
                .case 4  : .return ST_UINT4
                .case 6  : .return ST_REAL48
                .case 8  : .return ST_UINT8
                .case 16 : .return ST_UINT8
                .case 2
                    .if ( [esi].asym.flag1 & S_ISARRAY && Options.debug_symbols == CV_SIGNATURE_C13 )
                        .return ST_CHAR16
                    .endif
                    .return ST_UINT2
                .endsw

            .endif
            .if ( [esi].asym.Ofssize == USE32 )
                .return ST_UINT4
            .endif
            .return ST_UINT8
        .endif
    .else
        .switch cl
        .case MT_PTR
            mov al,[esi].asym.Ofssize
            .switch al
            .case USE16
                .if ( [esi].asym.sflags & S_ISFAR )
                    .return ST_PFVOID
                .endif
                .return ST_PVOID
            .case USE32
                .if ( [esi].asym.sflags & S_ISFAR )
                    .return ST_32PFVOID
                .endif
                .return ST_32PVOID
            .case USE64
                mov al,[esi].asym.ptr_memtype
                .switch al
                .case MT_BYTE:   .return ST_64PUCHAR
                .case MT_SBYTE:  .return ST_64PCHAR
                .case MT_WORD:   .return ST_64PCHAR16
                .case MT_SWORD:  .return ST_64PSHORT
                .case MT_REAL2:  .return ST_64PUINT2
                .case MT_DWORD:  .return ST_64PUINT4
                .case MT_SDWORD: .return ST_64PINT4
                .case MT_REAL4:  .return ST_64PREAL32
                .case MT_QWORD:  .return ST_64PUINT8
                .case MT_SQWORD: .return ST_64PINT8
                .case MT_REAL8:  .return ST_64PREAL64
                .case MT_OWORD:  .return ST_64PUINT8
                .case MT_REAL16: .return ST_64PUINT8
                .endsw
                .return ST_PVOID
            .endsw
            .endc
        .case MT_BITS
            .if ( [esi].asym.cvtyperef )
                .return( [esi].asym.cvtyperef )
            .endif
            .endc
        .case MT_NEAR : .return ST_PVOID
        .case MT_FAR  : .return ST_PFVOID
        .case MT_TYPE
            .for ( esi = [esi].asym.type: [esi].asym.type: esi = [esi].asym.type )
            .endf
            .if ( [esi].asym.cvtyperef )
                .return( [esi].asym.cvtyperef )
            .endif
            .return( GetTyperef( esi, Ofssize ) )
        .endsw
    .endif
    .return( ST_NOTYPE )
GetTyperef endp

SetPrefixName proc fastcall p:ptr byte, name:ptr byte, len:dword

    xchg edx,esi
    mov eax,edi
    mov edi,p
    mov ecx,len
    .if Options.debug_symbols == CV_SIGNATURE_C7
        mov [edi],cl
        inc edi
        rep movsb
    .else
        rep movsb
        mov byte ptr [edi],0
        inc edi
    .endif
    xchg edi,eax
    mov esi,edx
    ret

SetPrefixName endp

;; calc size of a codeview item in symbols segment

GetStructLen proc sym:ptr asym, Ofssize:byte

    mov ecx,sym
    .if Options.debug_symbols == CV_SIGNATURE_C7

        .if ( [ecx].asym.state == SYM_TYPE )
            .return( sizeof( UDTSYM_16t ) - 1 )
        .endif
        .if ( [ecx].asym.flag1 & S_ISPROC && Options.debug_ext >= CVEX_REDUCED )
            .if ( Ofssize == USE16 )
                .return sizeof( PROCSYM16 ) - 1
            .endif
            .return sizeof( PROCSYM32_16t ) - 1
        .endif
        .if ( [ecx].asym.mem_type == MT_NEAR || [ecx].asym.mem_type == MT_FAR )
            .if ( Ofssize == USE16 )
                .return sizeof( LABELSYM16 ) - 1
            .endif
            .return sizeof( LABELSYM32 ) - 1
        .endif
if EQUATESYMS
        .if ( [ecx].asym.flags & S_ISEQUATE )
            mov eax,sizeof( CONSTSYM_16t )
            .if ( [ecx].asym.value >= LF_NUMERIC )
                add eax,2
            .endif
            .return
        .endif
endif
        .return sizeof( DATASYM32_16t ) - 1
    .endif
    .if ( [ecx].asym.state == SYM_TYPE )
        .return( sizeof( UDTSYM ) - 1 )
    .endif
    .if ( [ecx].asym.flag1 & S_ISPROC && Options.debug_ext >= CVEX_REDUCED )
        .return sizeof( PROCSYM32 ) - 1
    .endif
    .if ( [ecx].asym.mem_type == MT_NEAR || [ecx].asym.mem_type == MT_FAR )
        .return sizeof( LABELSYM32 ) - 1
    .endif
if EQUATESYMS
    .if ( [ecx].asym.flags & S_ISEQUATE )
        mov eax,sizeof( CONSTSYM )
        .if ( [ecx].asym.value >= LF_NUMERIC )
            add eax,2
        .endif
        .return
    .endif
endif
    .return sizeof( DATASYM32 ) - 1
GetStructLen endp

;; flush the segment buffer for symbols and types.
;; For OMF, the buffer is written to disk. For COFF, it's
;; more complicated, because we cannot write now, but also
;; don't know yet the final size of the segment. So a linked
;; list of buffer items has to be created. The contents will
;; later be written inside coff_write_header().

    assume ebx:ptr dbgcv

dbgcv::flushpt proc fastcall uses ebx size:dword
    mov ebx,this
    mov ecx,[ebx].types
    mov eax,[ecx].dsym.seginfo
    mov [ebx].pt,[eax].seg_info.flushfunc( ecx, [ebx].pt, edx, [ebx].param )
    ret
dbgcv::flushpt endp

dbgcv::flushps proc fastcall uses ebx size:dword
    mov ebx,this
    mov ecx,[ebx].symbols
    mov eax,[ecx].dsym.seginfo
    mov [ebx].ps,[eax].seg_info.flushfunc( ecx, [ebx].ps, edx, [ebx].param )
    ret
dbgcv::flushps endp

dbgcv::padbytes proc fastcall curr:ptr byte
    mov ecx,[ecx].dbgcv.types
    mov ecx,[ecx].dsym.seginfo
    mov ecx,[ecx].seg_info.CodeBuffer
    .for ( :: edx++ )
        mov eax,edx
        sub eax,ecx
        .break .if ( !( eax & 3 ) )
        not eax
        and eax,3
        mov al,padtab[eax]
        mov [edx],al
    .endf
    ret
dbgcv::padbytes endp

dbgcv::alignps proc fastcall
    mov edx,[ecx].dbgcv.section
    mov eax,[edx].cvsection.length
    and eax,3
    .ifnz
        mov edx,4
        sub edx,eax
        .while ( edx )
            mov eax,[ecx].dbgcv.ps
            mov byte ptr [eax],0
            inc [ecx].dbgcv.ps
            dec edx
        .endw
    .endif
    mov eax,[ecx].dbgcv.ps
    ret
dbgcv::alignps endp

; write a bitfield to $$TYPES

dbgcv::write_bitfield proc uses esi edi ebx types:ptr dsym, sym:ptr asym

    mov ebx,this
    mov esi,CV_BITFIELD
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov esi,CV_BITFIELD_16t
    .endif
    mov edi,[ebx].flushpt( esi )
    mov ecx,sym
    mov [ecx].asym.cvtyperef,[ebx].currtype
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [edi].CV_BITFIELD_16t.size,( CV_BITFIELD_16t - sizeof(uint_16) )
        mov [edi].CV_BITFIELD_16t.leaf,LF_BITFIELD_16t
        mov [edi].CV_BITFIELD_16t.length,[ecx].asym.total_size
        mov [edi].CV_BITFIELD_16t.position,[ecx].asym.offs
        mov [edi].CV_BITFIELD_16t.type,GetTyperef( types, USE16 )
    .else
        mov [edi].CV_BITFIELD.size,( CV_BITFIELD - sizeof(uint_16) )
        mov [edi].CV_BITFIELD.leaf,LF_BITFIELD
        mov [edi].CV_BITFIELD.length,[ecx].asym.total_size
        mov [edi].CV_BITFIELD.position,[ecx].asym.offs
        mov [edi].CV_BITFIELD.type,GetTyperef( types, USE16 )
        mov [edi].CV_BITFIELD.reserved,0xF1F2 ; added for alignment
    .endif
    inc [ebx].currtype
    add [ebx].pt,esi
    ret

dbgcv::write_bitfield endp

dbgcv::write_array_type proc uses esi edi ebx sym:ptr asym, elemtype:dword, Ofssize:byte
    .if ( elemtype == 0 )
        mov elemtype,GetTyperef( sym, Ofssize )
    .endif
    mov ebx,this
    mov ecx,sym
    xor esi,esi
    .if ( [ecx].asym.total_size >= LF_NUMERIC )
        add esi,sizeof( uint_32 )
    .endif
    mov eax,sizeof( CV_ARRAY )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov eax,sizeof( CV_ARRAY_16t )
    .endif
    lea edi,[esi+eax+sizeof(uint_16)+1+3]
    and edi,not 3
    [ebx].flushpt(edi)
    mov ecx,edi
    mov edi,eax
    add [ebx].pt,ecx
    sub ecx,sizeof(uint_16)
    mov [edi].CV_ARRAY_16t.size,cx
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [edi].CV_ARRAY_16t.leaf,LF_ARRAY_16t
        mov [edi].CV_ARRAY_16t.elemtype,elemtype
        mov [edi].CV_ARRAY_16t.idxtype,ST_LONG ;; ok?
        lea edx,[edi].CV_ARRAY_16t.data
    .else
        mov [edi].CV_ARRAY.leaf,LF_ARRAY
        mov [edi].CV_ARRAY.elemtype,elemtype
        mov [edi].CV_ARRAY.idxtype,GetTyperef( sym, Ofssize )
        lea edx,[edi].CV_ARRAY.data
    .endif
    mov ecx,sym
    mov eax,[ecx].asym.total_size
    .if ( esi )
        mov word ptr [edx],LF_ULONG
        mov [edx+2],eax
        add edx,6
    .else
        mov [edx],ax
        add edx,2
    .endif
    mov byte ptr [edx],0 ; the array type name is empty
    inc edx
    [ebx].padbytes(edx)
    inc [ebx].currtype
    ret

dbgcv::write_array_type endp


;; create a pointer type for procedure params and locals.
;; the symbol's mem_type is MT_PTR.

dbgcv::write_ptr_type proc fastcall uses esi edi ebx sym:ptr asym

    mov ebx,this
    mov esi,sym

    .if ( ( [esi].asym.ptr_memtype == MT_EMPTY && [esi].asym.target_type == NULL ) || \
          [esi].asym.ptr_memtype == MT_PROC )
        .return( GetTyperef( esi, [esi].asym.Ofssize ) )
    .endif
    mov edi,sizeof( CV_POINTER )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov edi,sizeof( CV_POINTER_16t )
    .endif
    [ebx].flushpt(edi)
    xchg edi,eax

    add [ebx].pt,eax
    sub eax,sizeof( uint_16 )
    mov [edi].CV_POINTER_16t.size,ax

    .if ( [esi].asym.Ofssize == USE16 )
        mov eax,CV_PTR_NEAR
        .if ( [esi].asym.sflags & S_ISFAR )
            mov eax,CV_PTR_FAR
        .endif
    .elseif ( [esi].asym.Ofssize == USE32 )
        mov eax,CV_PTR_NEAR32
        .if ( [esi].asym.sflags & S_ISFAR )
            mov eax,CV_PTR_FAR32
        .endif
    .else
        mov eax,CV_PTR_64
    .endif
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [edi].CV_POINTER_16t.leaf,LF_POINTER_16t
        mov [edi].CV_POINTER_16t.attr,ax
        mov [edi].CV_POINTER_16t.pmclass,0
        mov [edi].CV_POINTER_16t.pmenum,0
    .else
        mov [edi].CV_POINTER.leaf,LF_POINTER
        mov [edi].CV_POINTER.attr,eax
        mov [edi].CV_POINTER.pmclass,0
        mov [edi].CV_POINTER.pmenum,0
    .endif

    ;; if indirection is > 1, define an untyped pointer - to be improved

    .if ( [esi].asym.is_ptr > 1 )
        GetTyperef( esi, [esi].asym.Ofssize )
    .elseif ( [esi].asym.target_type )
        ;; the target's typeref must have been set here
        mov ecx,[esi].asym.target_type
        .if ( [ecx].asym.cvtyperef )
            movzx eax,[ecx].asym.cvtyperef
        .else
            GetTyperef( esi, [esi].asym.Ofssize )
        .endif
    .else ;; pointer to simple type
        mov al,[esi].asym.mem_type      ; the target type is tmp. copied to mem_type
        mov ah,[esi].asym.ptr_memtype   ; thus GetTyperef() can be used
        mov [esi].asym.mem_type,ah
        push eax
        GetTyperef( esi, [esi].asym.Ofssize )
        pop ecx
        mov [esi].asym.mem_type,cl
    .endif
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [edi].CV_POINTER_16t.utype,ax
    .else
        mov [edi].CV_POINTER.utype,eax
    .endif
    mov eax,[ebx].currtype
    inc [ebx].currtype
    ret

dbgcv::write_ptr_type endp


;; field enumeration callback, does:
;; - count number of members in a field list
;; - calculate the size LF_MEMBER records inside the field list
;; - create types ( array, structure ) if not defined yet

dbgcv::cntproc proc uses esi edi ebx type:ptr dsym, mbr:ptr asym, cc:ptr counters

    mov ebx,this
    mov esi,cc
    inc [esi].counters.cnt
    mov eax,sizeof( CV_MEMBER )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov eax,sizeof( CV_MEMBER_16t )
    .endif
    mov edi,mbr
    mov ecx,type
    xor edx,edx
    .if ( [ecx].asym.typekind != TYPE_RECORD )
        add edx,[edi].asym.offs
        add edx,[esi].counters.ofs
    .endif
    .if ( edx >= LF_NUMERIC )
        add edx,DWORD
    .endif
    movzx ecx,[edi].asym.name_size
    lea eax,[ecx+eax+2+1+3]
    and eax,not 3
    add [esi].counters.size,eax

    ;; field cvtyperef can only be queried from SYM_TYPE items!
    mov ecx,[edi].asym.type
    .if ( [edi].asym.mem_type == MT_TYPE && [ecx].asym.cvtyperef == 0 )
        inc [ebx].level
        [ebx].write_type( [edi].asym.type )
        dec [ebx].level
    .elseif ( [edi].asym.mem_type == MT_BITS && [edi].asym.cvtyperef == 0 )
        [ebx].write_bitfield( type, edi )
    .endif
    .if ( [edi].asym.flag1 & S_ISARRAY )
        ;; temporarily (mis)use ext_idx1 member to store the type;
        ;; this field usually isn't used by struct fields
        mov [edi].asym.ext_idx1,[ebx].currtype
        [ebx].write_array_type( edi, 0, USE16 )
    .endif
    ret

dbgcv::cntproc endp

;; field enumeration callback, does:
;; - create LF_MEMBER record

dbgcv::memberproc proc uses esi edi ebx type:ptr dsym, mbr:ptr asym, cc:ptr counters

  local offs:dword
  local typelen:dword

    mov ebx,this
    mov esi,cc
    mov edi,mbr
    mov ecx,type

    xor eax,eax
    xor edx,edx
    .if ( [ecx].asym.typekind != TYPE_RECORD )
        add edx,[edi].asym.offs
        add edx,[esi].counters.ofs
    .endif
    mov offs,edx
    .if ( edx >= LF_NUMERIC )
        add eax,sizeof( uint_32 )
    .endif
    mov typelen,eax
    mov edx,sizeof( CV_MEMBER )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov edx,sizeof( CV_MEMBER_16t )
    .endif
    add eax,edx
    movzx ecx,[edi].asym.name_size
    lea esi,[eax+ecx+2+1+3]
    and esi,not 3
    mov edi,[ebx].flushpt(esi)
    add [ebx].pt,esi
    mov eax,LF_MEMBER
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov eax,LF_MEMBER_16t
    .endif
    mov [edi].CV_MEMBER_16t.leaf,ax
    mov esi,mbr
    .if ( [esi].asym.flag1 & S_ISARRAY )
        movzx eax,[esi].asym.ext_idx1
        mov [esi].asym.ext_idx1,0 ; reset the temporarily used field
    .else
        GetTyperef( esi, USE16 )
    .endif
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [edi].CV_MEMBER_16t.index,ax
        mov [edi].CV_MEMBER_16t.attr,CV_public or ( CV_MTvanilla shl 2 )
        lea ecx,[edi].CV_MEMBER_16t.offs
    .else
        mov [edi].CV_MEMBER.index,eax
        mov [edi].CV_MEMBER.attr,CV_public or ( CV_MTvanilla shl 2 )
        lea ecx,[edi].CV_MEMBER.offs
    .endif
    mov eax,offs
    .if ( typelen == 0 )
        mov [ecx],ax
        add ecx,2
    .else
        mov word ptr [ecx],LF_ULONG
        mov [ecx+2],eax
        add ecx,6
    .endif
    SetPrefixName( ecx, [esi].asym.name, [esi].asym.name_size )
    [ebx].padbytes(eax)
    ret

dbgcv::memberproc endp

;; field enumeration function.
;; The MS debug engine has problem with anonymous members (both members
;; and embedded structs).
;; If such a member is included, the containing struct can't be "opened".
;; The OW debugger and PellesC debugger have no such problems.
;; However, for Masm-compatibility, anonymous members are avoided and
;; anonymous struct members or embedded anonymous structs are "unfolded"
;; in this function.

dbgcv::enum_fields proc uses esi edi ebx symb:ptr dsym, enumfunc:cv_enum_func, cc:ptr counters

    mov esi,symb
    mov ecx,[esi].dsym.structinfo
    .for ( edi = [ecx].struct_info.head, ebx = 0: edi: edi = [edi].sfield.next )
        .if ( [edi].sfield.sym.name_size ) ;; has member a name?
            enumfunc( this, esi, &[edi].sfield.sym, cc )
        .elseif ( [edi].sfield.sym.type ) ;; is member a type (struct, union, record)?
            mov ecx,cc
            add [ecx].counters.ofs,[edi].sfield.sym.offs
            this.enum_fields( [edi].sfield.sym.type, enumfunc, cc )
            mov ecx,cc
            sub [ecx].counters.ofs,[edi].sfield.sym.offs
        .elseif ( [esi].asym.typekind == TYPE_UNION )
            ;; v2.11: include anonymous union members.
            ;; to make the MS debugger work with those members, they must have a name -
            ;; a temporary name is generated below which starts with "@@".
            ;;
            .new pold:string_t = [edi].sfield.sym.name
            .new tmpname[8]:char_t

            sprintf( &tmpname, "@@%u", ebx )
            mov [edi].sfield.sym.name_size,ax
            inc ebx
            mov [edi].sfield.sym.name,&tmpname
            enumfunc( this, esi, &[edi].sfield.sym, cc )
            mov [edi].sfield.sym.name,pold
            mov [edi].sfield.sym.name_size,0
        .endif
    .endf
    ret
dbgcv::enum_fields endp

;; write a LF_PROCEDURE & LF_ARGLIST type for procedures

dbgcv::write_type_procedure proc uses esi edi ebx sym:ptr asym, cnt:int_t

    mov ebx,this
    mov esi,sizeof( CV_PROCEDURE )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov esi,sizeof( CV_PROCEDURE_16t )
    .endif
    mov edi,[ebx].flushpt(esi)
    add [ebx].pt,esi
    sub esi,sizeof( uint_16 )
    mov [edi].CV_PROCEDURE_16t.size,si
    inc [ebx].currtype

    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [edi].CV_PROCEDURE_16t.leaf,LF_PROCEDURE_16t
        mov [edi].CV_PROCEDURE_16t.rvtype,ST_VOID
        mov [edi].CV_PROCEDURE_16t.calltype,0
        mov [edi].CV_PROCEDURE_16t.funcattr,0
        mov [edi].CV_PROCEDURE_16t.parmcount,cnt
        mov [edi].CV_PROCEDURE_16t.arglist,[ebx].currtype
        mov esi,sizeof( CV_ARGLIST_16t )
        mov eax,CV_typ16_t
    .else
        mov [edi].CV_PROCEDURE_16t.leaf,LF_PROCEDURE
        mov [edi].CV_PROCEDURE.rvtype,ST_VOID
        mov [edi].CV_PROCEDURE.calltype,0
        mov [edi].CV_PROCEDURE.funcattr,0
        mov [edi].CV_PROCEDURE.parmcount,cnt
        mov [edi].CV_PROCEDURE.arglist,[ebx].currtype
        mov esi,sizeof( CV_ARGLIST )
        mov eax,CV_typ_t
    .endif
    mul cnt
    add esi,eax
    mov edi,[ebx].flushpt(esi)
    add [ebx].pt,esi
    sub esi,sizeof( uint_16 )
    mov [edi].CV_ARGLIST_16t.size,si

    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [edi].CV_ARGLIST_16t.leaf,LF_ARGLIST_16t
        mov [edi].CV_ARGLIST_16t.count,cnt
        add edi,sizeof( CV_ARGLIST_16t )
    .else
        mov [edi].CV_ARGLIST_16t.leaf,LF_ARGLIST
        mov [edi].CV_ARGLIST.count,cnt
        add edi,sizeof( CV_ARGLIST )
    .endif
    ;; fixme: order might be wrong ( is "push" order )
    mov esi,sym
    mov esi,[esi].dsym.procinfo
    .for ( esi = [esi].proc_info.paralist: esi: esi = [esi].dsym.nextparam )
        movzx eax,[esi].asym.ext_idx1
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            stosw
        .else
            .if ( ModuleInfo.defOfssize == USE64 ) ;; ...
                dec cnt
                mov ecx,cnt
                mov [edi+ecx*4],eax
            .else
                stosd
            .endif
        .endif
    .endf
    inc [ebx].currtype
    ret
dbgcv::write_type_procedure endp


;; write a type. Items are dword-aligned,
;;    cv: debug state
;;   sym: type to dump

dbgcv::write_type proc uses esi edi ebx sym:ptr asym

  local namesize:dword
  local typelen:dword
  local size:dword
  local leaf:word
  local property:CV_prop_t
  local count:counters

    mov ebx,this
    mov esi,sym

    ;; v2.10: handle typedefs. when the types are enumerated,
    ;; typedefs are ignored.

    .if ( [esi].asym.typekind == TYPE_TYPEDEF )

        .if ( [esi].asym.mem_type == MT_PTR )
            mov ecx,[esi].asym.target_type
            .if ( [esi].asym.ptr_memtype != MT_PROC && ecx && [ecx].asym.cvtyperef == 0 )
                .if ( [ebx].level == 0 ) ;; avoid circles
                    [ebx].write_type( [esi].asym.target_type )
                .endif
            .endif
            mov [esi].asym.cvtyperef,[ebx].write_ptr_type( esi )
        .endif
        .return
    .elseif ( [esi].asym.typekind == TYPE_NONE )
        .return
    .endif

    xor eax,eax
    mov property,ax
    .if ( [esi].asym.total_size >= LF_NUMERIC )
        mov eax,sizeof( uint_32 )
    .endif
    mov typelen,eax
    .if ( [ebx].level )
        mov property,CV_prop_isnested
    .endif

    ;; Count the member fields. If a member's type is unknown, create it!
    mov count.cnt,0
    mov count.size,0
    mov count.ofs,0
    mov ecx,[ebx]
    [ebx].enum_fields( esi, [ecx].dbgcvVtbl.cntproc, &count )

    ;; WinDbg wants embedded structs to have a name - else it won't allow to "open" it.
    mov eax,9
    .if ( [esi].asym.name_size )
        movzx eax,[esi].asym.name_size ;; 9 is sizeof("__unnamed")
    .endif
    mov namesize,eax

    mov [esi].asym.cvtyperef,[ebx].currtype
    inc [ebx].currtype
    movzx eax,[esi].asym.typekind
    .switch eax
    .case TYPE_UNION
        mov esi,sizeof( CV_UNION )
        mov leaf,LF_UNION
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov esi,sizeof( CV_UNION_16t )
            mov leaf,LF_UNION_16t
        .endif
        add esi,typelen
        add esi,namesize
        add esi,2+1+3
        and esi,not 3
        mov size,esi
        mov edi,[ebx].flushpt(esi)
        sub esi,sizeof( uint_16 )
        mov [edi].CV_UNION_16t.size,si
        mov [edi].CV_UNION_16t.leaf,leaf
        mov [edi].CV_UNION_16t.count,count.cnt
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov [edi].CV_UNION_16t.field,[ebx].currtype
            mov [edi].CV_UNION_16t.property,property
            lea esi,[edi].CV_UNION_16t.data
        .else
            mov [edi].CV_UNION.field,[ebx].currtype
            mov [edi].CV_UNION.property,property
            lea esi,[edi].CV_UNION.data
        .endif
        inc [ebx].currtype
        .endc
    .case TYPE_RECORD
        or property,CV_prop_packed ; is "packed"
        ;; no break
    .case TYPE_STRUCT
        mov esi,sizeof( CV_STRUCT )
        mov leaf,LF_STRUCTURE
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov esi,sizeof( CV_STRUCT_16t )
            mov leaf,LF_STRUCTURE_16t
        .endif
        add esi,typelen
        add esi,namesize
        add esi,2+1+3
        and esi,not 3
        mov size,esi
        mov edi,[ebx].flushpt(esi)
        sub esi,sizeof( uint_16 )
        mov [edi].CV_STRUCT_16t.size,si
        mov [edi].CV_STRUCT_16t.leaf,leaf
        mov [edi].CV_STRUCT_16t.count,count.cnt
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov [edi].CV_STRUCT_16t.field,[ebx].currtype
            mov [edi].CV_STRUCT_16t.property,property
            mov [edi].CV_STRUCT_16t.derived,0
            mov [edi].CV_STRUCT_16t.vshape,0
            lea esi,[edi].CV_STRUCT_16t.data
        .else
            mov [edi].CV_STRUCT.field,[ebx].currtype
            mov [edi].CV_STRUCT.property,property
            mov [edi].CV_STRUCT.derived,0
            mov [edi].CV_STRUCT.vshape,0
            lea esi,[edi].CV_STRUCT.data
        .endif
        inc [ebx].currtype
        .endc
    .endsw

    mov ecx,sym
    mov eax,[ecx].asym.total_size
    .if ( typelen == 0 )
        mov [esi],ax
        add esi,2
    .else
        mov word ptr [esi],LF_ULONG
        mov [esi+2],eax
        add esi,6
    .endif
    lea eax,@CStr("__unnamed")
    .if ( [ecx].asym.name_size )
        mov eax,[ecx].asym.name
    .endif
    SetPrefixName( esi, eax, namesize )
    [ebx].padbytes(eax)
    add [ebx].pt,size

    ;; write the fieldlist record
    mov edi,[ebx].flushpt(CV_FIELDLIST)
    add [ebx].pt,CV_FIELDLIST

    mov eax,sizeof(CV_FIELDLIST) - sizeof(uint_16)
    add eax,count.size
    mov [edi].CV_FIELDLIST.size,ax
    mov eax,LF_FIELDLIST
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov eax,LF_FIELDLIST_16t
    .endif
    mov [edi].CV_FIELDLIST.leaf,ax

    ;; add the struct's members to the fieldlist.
    mov count.ofs,0
    mov ecx,[ebx]
    [ebx].enum_fields( sym, [ecx].dbgcvVtbl.memberproc, &count )
    ret
dbgcv::write_type endp

;; get register values for S_REGISTER

get_register proc fastcall uses esi edi ebx sym:ptr asym

    mov esi,sym
    .for ( edi = 0, ebx = 0: ebx < 2: ebx++ )
        movzx edx,[esi].asym.regist[ebx*2]
        .if ( edx )
            mov ecx,GetValueSp( edx )
            movzx eax,GetRegNo( edx )
            inc eax
            .if ( ecx & OP_R16 )
                add eax,8
            .elseif ( ecx & OP_R32 )
                add eax,16
            .elseif ( ecx & OP_SR )
                add eax,24
            .endif
            lea ecx,[ebx*8]
            shl eax,cl
            or edi,eax
        .endif
    .endf
    .return( edi )

get_register endp

;;
;;  convert register number
;;        0  1  2  3  4  5  6  7
;; -----------------------------
;; from: ax cx dx bx sp bp si di
;;   to: ax bx cx dx si di bp sp
;;

get_x64_regno proc fastcall regno:dword

    .if ( regno >= T_RAX && regno <= T_RDI )
        movzx eax,reg64[regno-T_RAX]
        add eax,CV_AMD64_RAX
        .return
    .endif
    .if ( regno >= T_R8 && regno <= T_R15 )
        lea eax,[regno-T_R8+CV_AMD64_RAX+8]
        .return
    .endif
    ;; it's a 32-bit register r8d-r15d
    lea eax,[regno-T_R8D+CV_AMD64_R8D]
    ret

get_x64_regno endp

;; write a symbol
;;    cv: debug state
;;   sym: symbol to write
;; the symbol has either state SYM_INTERNAL or SYM_TYPE.
;;

dbgcv::write_symbol proc uses esi edi ebx sym:ptr asym

  local len:int_t
  local ofs:dword
  local rlctype:fixup_types
  local Ofssize:byte
  local fixp:ptr fixup
  local pproc:ptr dsym
  local lcl:ptr dsym
  local i:int_t, j:int_t, k:int_t
  local cnt[2]:int_t
  local locals[2]:ptr dsym
  local q:ptr dsym
  local size:dword
  local leaf:word
  local typeref:uint_16

    mov esi,sym
    mov ebx,this

    mov Ofssize,GetSymOfssize( esi )
    mov len,GetStructLen( esi, al )

    movzx ecx,[esi].asym.name_size
    add eax,ecx
    inc eax
    mov edi,[ebx].flushps(eax)

    .if ( [esi].asym.state == SYM_TYPE )

        ;; Masm does only generate an UDT for typedefs
        ;; if the underlying type is "used" somewhere.
        ;; example:
        ;; LPSTR typedef ptr BYTE
        ;; will only generate an S_UDT for LPSTR if either
        ;; "LPSTR" or "ptr BYTE" is used in the source.

        mov eax,sizeof( UDTSYM )
        mov edx,S_UDT
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov eax,sizeof( UDTSYM_16t )
            mov edx,S_UDT_16t
        .endif
        mov [edi].UDTSYM_16t.rectyp,dx
        sub eax,sizeof(uint_16)
        movzx ecx,[esi].asym.name_size
        add eax,ecx
        mov [edi].UDTSYM_16t.reclen,ax

        ;; v2.10: pointer typedefs will now have a cv_typeref

        .if ( [esi].asym.cvtyperef )
            movzx eax,[esi].asym.cvtyperef
        .else
            GetTyperef( esi, Ofssize )
        .endif
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov [edi].UDTSYM_16t.typind,ax
        .else
            mov [edi].UDTSYM.typind,eax
        .endif

        ;; Some typedefs won't get a valid type (<name> TYPEDEF PROTO ...).
        ;; In such cases just skip the type!

        .if ( eax )
            add [ebx].ps,len
            mov [ebx].ps,SetPrefixName( [ebx].ps, [esi].asym.name, [esi].asym.name_size )
            .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
                movzx eax,[esi].asym.name_size
                add eax,len
                inc eax
                mov ecx,[ebx].section
                add [ecx].cvsection.length,eax
            .endif
        .endif
        .return
    .endif

    ;; rest is SYM_INTERNAL
    ;; there are 3 types of INTERNAL symbols:
    ;; - numeric constants ( equates, memtype MT_EMPTY )
    ;; - code labels, memtype == MT_NEAR | MT_FAR
    ;;   - procs
    ;;   - simple labels
    ;; - data labels, memtype != MT_NEAR | MT_FAR

    .if ( [esi].asym.flag1 & S_ISPROC && Options.debug_ext >= CVEX_REDUCED ) ;; v2.10: no locals for -Zi0

        mov edx,[esi].dsym.procinfo
        mov pproc,edx

        ;; for PROCs, scan parameters and locals and create their types.

        ;; scan local symbols

        mov locals[0],[edx].proc_info.paralist
        mov locals[4],[edx].proc_info.locallist

        .for ( i = 0: i < 2: i++ )

            .if ( ModuleInfo.defOfssize == USE64 && i == 0 )
                .for ( j = 0, ecx = locals[0]: ecx: esi = ecx, ecx = [ecx].dsym.nextparam )
                    inc j
                .endf
            .endif

            mov ecx,i
            mov cnt[ecx*4],0
            .for ( edi = locals[ecx*4]: edi: edi = [edi].dsym.nextparam )

                .if ( !( ModuleInfo.defOfssize == USE64 && i == 0 ) )
                    mov esi,edi
                .endif

                mov ecx,i
                inc cnt[ecx*4]

                .if ( [esi].asym.mem_type == MT_EMPTY && [esi].asym.sflags & S_ISVARARG )
                    mov typeref,ST_PVOID
                .else
                    .if ( [esi].asym.mem_type == MT_PTR )
                        [ebx].write_ptr_type( esi )
                    .else
                        GetTyperef( esi, Ofssize )
                    .endif
                    mov typeref,ax
                .endif
                .if ( [esi].asym.flag1 & S_ISARRAY )
                    [ebx].write_array_type( esi, typeref, Ofssize )
                    mov eax,[ebx].currtype
                    dec eax
                    mov typeref,ax
                .endif
                mov [esi].asym.ext_idx1,typeref
                .if ( ModuleInfo.defOfssize == USE64 && i == 0 )
                    .for ( ecx = 1, j--, esi = locals[0]: j > ecx: ecx++, esi = [esi].dsym.nextparam )
                    .endf
                .endif
            .endf
        .endf

        mov edi,[ebx].ps
        mov esi,sym

        .if ( Ofssize == USE16 )

            movzx eax,[esi].asym.name_size
            add eax,sizeof( PROCSYM16 ) - sizeof(uint_16)
            mov [edi].PROCSYM16.reclen,ax
            mov eax,S_LPROC16
            .if ( [esi].asym.flags & S_ISPUBLIC )
                mov eax,S_GPROC16
            .endif
            mov [edi].PROCSYM16.rectyp,ax

            mov [edi].PROCSYM16.pParent,0  ;; filled by CVPACK
            mov [edi].PROCSYM16.pEnd,0     ;; filled by CVPACK
            mov [edi].PROCSYM16.pNext,0    ;; filled by CVPACK
            mov [edi].PROCSYM16.len,[esi].asym.total_size
            mov ecx,[esi].dsym.procinfo
            mov [edi].PROCSYM16.DbgStart,[ecx].proc_info.size_prolog
            mov [edi].PROCSYM16.DbgEnd,[esi].asym.total_size
            mov [edi].PROCSYM16.off,0
            mov [edi].PROCSYM16._seg,0
            mov [edi].PROCSYM16.typind,[ebx].currtype ;; typeref LF_PROCEDURE
            xor eax,eax
            .if ( [esi].asym.mem_type == MT_FAR )
                mov eax,CV_PROCF_FAR
            .endif
            mov [edi].PROCSYM16.flags,al
            mov rlctype,FIX_PTR16
            mov ofs,offsetof( PROCSYM16, off )
        .else

            mov size,sizeof( PROCSYM32 )
            mov eax,S_LPROC32
            .if ( [esi].asym.flags & S_ISPUBLIC )
                mov eax,S_GPROC32
            .endif
            mov leaf,ax
            .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                mov size,sizeof( PROCSYM32_16t )
                mov eax,S_LPROC32_16t
                .if ( [esi].asym.flags & S_ISPUBLIC )
                    mov eax,S_GPROC32_16t
                .endif
                mov leaf,ax
            .endif
            mov eax,size
            sub eax,sizeof(uint_16)
            movzx ecx,[esi].asym.name_size
            add eax,ecx
            mov [edi].PROCSYM32_16t.reclen,ax
            mov [edi].PROCSYM32_16t.rectyp,leaf
            mov [edi].PROCSYM32_16t.pParent,0   ; filled by CVPACK
            mov [edi].PROCSYM32_16t.pEnd,0      ; filled by CVPACK
            mov [edi].PROCSYM32_16t.pNext,0     ; filled by CVPACK
            mov [edi].PROCSYM32_16t.len,[esi].asym.total_size
            mov ecx,[esi].dsym.procinfo
            movzx eax,[ecx].proc_info.size_prolog
            mov [edi].PROCSYM32_16t.DbgStart,eax
            mov [edi].PROCSYM32_16t.DbgEnd,[esi].asym.total_size
            .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                mov [edi].PROCSYM32_16t.off,0
                mov [edi].PROCSYM32_16t._seg,0
                mov [edi].PROCSYM32_16t.typind,[ebx].currtype ; typeref LF_PROCEDURE
                mov [edi].PROCSYM32_16t.flags,0
                .if ( [esi].asym.mem_type == MT_FAR )
                    mov [edi].PROCSYM32_16t.flags,CV_PFLAG_FAR
                .endif
                mov ecx,pproc
                .if ( [ecx].proc_info.flags & PROC_FPO )
                    mov [edi].PROCSYM32_16t.flags,CV_PFLAG_NOFPO
                .endif
                mov ofs,offsetof( PROCSYM32_16t, off )
            .else
                mov [edi].PROCSYM32.off,0
                mov [edi].PROCSYM32._seg,0
                mov [edi].PROCSYM32.typind,[ebx].currtype
                mov [edi].PROCSYM32.flags,0
                .if ( [esi].asym.mem_type == MT_FAR )
                    mov [edi].PROCSYM32.flags,CV_PFLAG_FAR
                .endif
                mov ecx,pproc
                .if ( [ecx].proc_info.flags & PROC_FPO )
                    mov [edi].PROCSYM32.flags,CV_PFLAG_NOFPO
                .endif
                mov ofs,offsetof( PROCSYM32, off )
            .endif
            mov rlctype,FIX_PTR32
        .endif
        [ebx].write_type_procedure( sym, cnt[0] )

    .elseif ( [esi].asym.mem_type == MT_NEAR || [esi].asym.mem_type == MT_FAR )

        .if ( Ofssize == USE16 )

            movzx eax,[esi].asym.name_size
            add eax,sizeof( LABELSYM16 ) - sizeof(uint_16)
            mov [edi].LABELSYM16.reclen,ax
            mov [edi].LABELSYM16.rectyp,S_LABEL16
            xor eax,eax
            mov [edi].LABELSYM16.off,ax
            mov [edi].LABELSYM16._seg,ax
            .if ( [esi].asym.mem_type == MT_FAR )
                mov eax,CV_PROCF_FAR
            .endif
            mov [edi].LABELSYM16.flags,al
            mov rlctype,FIX_PTR16
            mov ofs,offsetof( LABELSYM16, off )
        .else
            movzx eax,[esi].asym.name_size
            add eax,sizeof( LABELSYM32 ) - sizeof(uint_16)
            mov [edi].LABELSYM32.reclen,ax
            .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                mov [edi].LABELSYM32.rectyp,S_LABEL32_ST
            .else
                mov [edi].LABELSYM32.rectyp,S_LABEL32
            .endif
            xor eax,eax
            mov [edi].LABELSYM32.off,eax
            mov [edi].LABELSYM32._seg,ax
            .if ( [esi].asym.mem_type == MT_FAR )
                mov eax,CV_PROCF_FAR
            .endif
            mov [edi].LABELSYM32.flags,al
            mov rlctype,FIX_PTR32
            mov ofs,offsetof( LABELSYM32, off )
        .endif
    .else

        ;; v2.10: set S_GDATA[16|32] if symbol is public

        ;.new typeref:uint_32

        .if ( [esi].asym.flag1 & S_ISARRAY )
            [ebx].write_array_type( esi, 0, Ofssize )
            mov eax,[ebx].currtype
            dec eax
        .else
            GetTyperef( esi, Ofssize )
        .endif
        mov typeref,ax

        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov size,sizeof( DATASYM32_16t )
            mov [edi].DATASYM32_16t.off,0
            mov [edi].DATASYM32_16t._seg,0
            mov [edi].DATASYM32_16t.typind,ax
            mov ofs,offsetof( DATASYM32_16t, off )
        .else
            mov size,sizeof( DATASYM32 )
            mov [edi].DATASYM32.off,0
            mov [edi].DATASYM32._seg,0
            mov [edi].DATASYM32.typind,eax
            mov ofs,offsetof( DATASYM32, off )
        .endif
        movzx eax,[esi].asym.name_size
        add eax,size
        sub eax,sizeof(uint_16)
        mov [edi].DATASYM32_16t.reclen,ax
        .if ( Ofssize == USE16 )
            mov eax,S_LDATA16
            .if ( [esi].asym.flags & S_ISPUBLIC )
                mov eax,S_GDATA16
            .endif
            mov leaf,ax
            mov rlctype,FIX_PTR16
        .else
            mov ecx,esi
            mov ecx,[ecx].asym.segm
            mov eax,1
            .if ( ( ModuleInfo.cv_opt & CVO_STATICTLS ) && [ecx].seg_info.clsym )
                mov ecx,[ecx].seg_info.clsym
                .if ( strcmp( [ecx].asym.name, "TLS" ) == 0 )
                    mov ecx,S_LTHREAD32_16t
                    .if ( [esi].asym.flags & S_ISPUBLIC )
                        mov ecx,S_GTHREAD32_16t
                    .endif
                .endif
            .endif
            .if ( eax )
                .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                    mov ecx,S_LDATA32_16t
                    .if ( [esi].asym.flags & S_ISPUBLIC )
                        mov ecx,S_GDATA32_16t
                    .endif
                .else
                    mov ecx,S_LDATA32
                    .if ( [esi].asym.flags & S_ISPUBLIC )
                        mov ecx,S_GDATA32
                    .endif
                .endif
            .endif
            mov leaf,cx
            mov rlctype,FIX_PTR32
        .endif
        mov [edi].DATASYM32_16t.rectyp,leaf
    .endif
    add [ebx].ps,ofs
    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
        mov ecx,[ebx].section
        add [ecx].cvsection.length,eax
    .endif

    mov eax,[ebx].symbols
    mov edi,[eax].dsym.seginfo
    mov eax,[ebx].ps
    sub eax,[edi].seg_info.CodeBuffer
    add eax,[edi].seg_info.start_loc
    mov [edi].seg_info.current_loc,eax

    .if ( Options.output_format == OFORMAT_COFF )

        ;; COFF has no "far" fixups. Instead Masm creates a
        ;; section-relative fixup + a section fixup.

        mov ecx,CreateFixup( esi, FIX_OFF32_SECREL, OPTJ_NONE )
        mov [ecx].fixup.locofs,[edi].seg_info.current_loc
        store_fixup( ecx, [ebx].symbols, [ebx].ps )
        mov ecx,CreateFixup( esi, FIX_SEG, OPTJ_NONE )
        mov eax,sizeof( int_16 )
        .if ( rlctype == FIX_PTR32 )
            mov eax,sizeof( int_32 )
        .endif
        add eax,[edi].seg_info.current_loc
        mov [ecx].fixup.locofs,eax
        store_fixup( ecx, [ebx].symbols, [ebx].ps )
    .else
        mov ecx,CreateFixup( esi, rlctype, OPTJ_NONE )
        mov [ecx].fixup.locofs,[edi].seg_info.current_loc
        ;; todo: for OMF, delay fixup store until checkflush has been called!
        store_fixup( ecx, [ebx].symbols, [ebx].ps )
    .endif
    mov eax,len
    sub eax,ofs
    add [ebx].ps,eax
    mov [ebx].ps,SetPrefixName( [ebx].ps, [esi].asym.name, [esi].asym.name_size )
    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
        movzx eax,[esi].asym.name_size
        add eax,len
        sub eax,ofs
        inc eax
        mov ecx,[ebx].section
        add [ecx].cvsection.length,eax
    .endif

    ;; for PROCs, scan parameters and locals.
    ;; to mark the block's end, write an ENDBLK item.

    ;; v2.10: no locals for -Zi0

    .if ( [esi].asym.flag1 & S_ISPROC && Options.debug_ext >= CVEX_REDUCED )

        ;; scan local symbols again

        .for ( i = 0: i < 2 : i++ )
            .if ( ModuleInfo.defOfssize == USE64 && i == 0 )
                .for ( j = 0, ecx = locals[0]: ecx: esi = ecx, ecx = [ecx].dsym.nextparam )
                    inc j
                .endf
            .endif
            mov ecx,i
            .for ( edi = locals[ecx*4]: edi: edi = [edi].dsym.nextparam )
                .if ( !( ModuleInfo.defOfssize == USE64 && i == 0 ) )
                    mov esi,edi
                .endif
                ;; FASTCALL register argument?
                .if ( [esi].asym.state == SYM_TMACRO )
                    mov len,sizeof( REGSYM ) - 1
                    mov leaf,S_REGISTER
                    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                        mov len,sizeof( REGSYM_16t ) - 1
                        mov leaf,S_REGISTER_16t
                    .endif
                    movzx eax,[esi].asym.name_size
                    add eax,len
                    inc eax
                    mov edx,[ebx].flushps(eax)
                    movzx eax,[esi].asym.name_size
                    add eax,len
                    sub eax,sizeof(uint_16)
                    inc eax
                    mov [edx].REGSYM_16t.reclen,ax
                    mov [edx].REGSYM_16t.rectyp,leaf
                    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                        mov [edx].REGSYM_16t.typind,[esi].asym.ext_idx1
                        get_register( esi )
                        mov edx,[ebx].ps
                        mov [edx].REGSYM_16t.reg,ax
                    .else
                        mov [edx].REGSYM.typind,[esi].asym.ext_idx1
                        get_register( esi )
                        mov edx,[ebx].ps
                        mov [edx].REGSYM.reg,ax
                    .endif
                .elseif ( Ofssize == USE16 )
                    mov len,sizeof( BPRELSYM16 ) - 1
                    movzx eax,[esi].asym.name_size
                    add eax,len
                    inc eax
                    mov edx,[ebx].flushps(eax)
                    mov eax,sizeof( BPRELSYM16 ) - sizeof(uint_16)
                    add ax,[esi].asym.name_size
                    mov [edx].BPRELSYM16.reclen,ax
                    mov [edx].BPRELSYM16.rectyp,S_BPREL16
                    mov [edx].BPRELSYM16.off,[esi].asym.offs
                    mov [edx].BPRELSYM16.typind,[esi].asym.ext_idx1
                .else

                    ;; v2.11: use S_REGREL if 64-bit or frame reg != [E|BP

                    mov ecx,pproc
                    movzx ecx,[ecx].proc_info.basereg
                    .if ( Ofssize == USE64 || ( GetRegNo( ecx ) != 5 ))

                        mov len,sizeof( REGREL32 ) - 1
                        mov leaf,S_REGREL32
                        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                            mov len,sizeof( REGREL32_16t ) - 1
                            mov leaf,S_REGREL32_16t
                        .endif
                        movzx eax,[esi].asym.name_size
                        add eax,len
                        inc eax
                        mov edx,[ebx].flushps(eax)
                        movzx eax,[esi].asym.name_size
                        add eax,len
                        sub eax,sizeof(uint_16) - 1
                        mov [edx].REGREL32_16t.reclen,ax
                        mov [edx].REGREL32_16t.rectyp,leaf

                        ;; x64 register numbers are different
                        mov ecx,pproc
                        movzx ecx,[ecx].proc_info.basereg
                        imul eax,ecx,special_item
                        .if ( SpecialTable[eax].cpu == P_64 )
                            mov size,get_x64_regno( ecx )
                        .else
                            mov size,GetRegNo( ecx )
                            add size,CV_REG_EAX
                        .endif
                        mov edx,[ebx].ps
                        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                            mov [edx].REGREL32_16t.off,[esi].asym.offs
                            mov [edx].REGREL32_16t.typind,[esi].asym.ext_idx1
                            mov [edx].REGREL32_16t.reg,size
                        .else
                            mov [edx].REGREL32.off,[esi].asym.offs
                            mov [edx].REGREL32.typind,[esi].asym.ext_idx1
                            mov [edx].REGREL32.reg,size
                        .endif
                    .else
                        mov len,sizeof( BPRELSYM32 ) - 1
                        mov leaf,S_BPREL32
                        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                            mov len,sizeof( BPRELSYM32_16t ) - 1
                            mov leaf,S_BPREL32_16t
                        .endif
                        movzx eax,[esi].asym.name_size
                        add eax,len
                        inc eax
                        mov edx,[ebx].flushps(eax)
                        movzx eax,[esi].asym.name_size
                        add eax,len
                        sub eax,sizeof(uint_16) - 1
                        mov [edx].BPRELSYM32_16t.reclen,ax
                        mov [edx].BPRELSYM32_16t.rectyp,leaf
                        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                            mov [edx].BPRELSYM32_16t.off,[esi].asym.offs
                            mov [edx].BPRELSYM32_16t.typind,[esi].asym.ext_idx1
                        .else
                            mov [edx].BPRELSYM32.off,[esi].asym.offs
                            mov [edx].BPRELSYM32.typind,[esi].asym.ext_idx1
                        .endif
                    .endif
                .endif
                mov [esi].asym.ext_idx1,0 ;; to be safe, clear the temp. used field
                add [ebx].ps,len
                mov [ebx].ps,SetPrefixName( [ebx].ps, [esi].asym.name, [esi].asym.name_size )
                .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
                    movzx eax,[esi].asym.name_size
                    add eax,len
                    inc eax
                    mov ecx,[ebx].section
                    add [ecx].cvsection.length,eax
                .endif

                .if ( ModuleInfo.defOfssize == USE64 && i == 0 )
                    .for ( ecx = 1, j--, esi = locals[0]: j > ecx: ecx++, esi = [esi].dsym.nextparam )
                    .endf
                .endif
            .endf
        .endf

        [ebx].flushps( sizeof( ENDARGSYM ) )
        mov [eax].ENDARGSYM.reclen,sizeof( ENDARGSYM ) - sizeof(uint_16)
        mov [eax].ENDARGSYM.rectyp,S_END
        add [ebx].ps,sizeof( ENDARGSYM )
        .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
            mov ecx,[ebx].section
            add [ecx].cvsection.length,sizeof( ENDARGSYM )
        .endif
    .endif
    ret

dbgcv::write_symbol endp

;; flush section header and return memory address

dbgcv::flush_section proc uses esi edi ebx signature:dword, ex:dword

    mov ebx,this
    mov edi,[ebx].symbols
    mov esi,[ebx].ps
    mov ecx,[edi].dsym.seginfo
    mov [ebx].ps,[ecx].seg_info.CodeBuffer
    sub esi,eax
    mov eax,ex
    lea ecx,[esi + eax + sizeof( qditem ) + sizeof( cvsection )]
    mov edi,LclAlloc( ecx )

    mov [edi].qditem.next,NULL
    lea eax,[esi+sizeof(cvsection)]
    add eax,ex
    mov [edi].qditem.size,eax
    lea ecx,[edi+esi+sizeof(qditem)]
    mov [ebx].section,ecx
    mov [ecx].cvsection.signature,signature
    mov [ecx].cvsection.length,ex

    .if ( esi )
        mov ecx,esi
        lea edx,[edi+sizeof(qditem)]
        mov eax,[ebx].ps
        xchg esi,eax
        xchg edi,edx
        rep movsb
        mov edi,edx
        mov esi,eax
    .endif
    mov edx,[ebx].param
    lea ecx,[edx].coffmod.SymDeb[dbg_section]
    mov edx,[ecx].dbg_section.s
    .if edx != [ebx].symbols
        sub ecx,sizeof( dbg_section )
    .endif
    .if ( [ecx].dbg_section.q.head == NULL )
        mov [ecx].dbg_section.q.head,edi
        mov [ecx].dbg_section.q.tail,edi
    .else
        mov edx,[ecx].dbg_section.q.tail
        mov [edx].qditem.next,edi
        mov [ecx].dbg_section.q.tail,edi
    .endif

    mov edx,[ebx].symbols
    mov ecx,[edx].dsym.seginfo
    mov eax,[ecx].seg_info.start_loc
    lea eax,[esi+eax+sizeof(cvsection)]
    add eax,ex
    mov [ecx].seg_info.current_loc,eax
    mov [ecx].seg_info.start_loc,eax
    mov eax,[ebx].section
    ret

dbgcv::flush_section endp

    assume ebx:nothing

ifndef __UNIX__
define USEMD5
endif

ifdef USEMD5
define MD5BUFSIZ 1024*4
define MD5_LENGTH ( sizeof( uint_32 ) + sizeof( uint_16 ) + 16 + sizeof( uint_16 ) )

calc_md5 proc uses esi edi ebx filename:string_t, sum:ptr byte

  local ctx:MD5_CTX

    .return .if ( fopen( filename, "rb" ) == NULL )

    lea edi,ctx
    mov esi,eax
    mov ebx,MemAlloc( MD5BUFSIZ )
    MD5Init( &ctx )

    .while 1
        .break .if !fread( ebx, 1, MD5BUFSIZ, esi )
        MD5Update( edi, ebx, eax )
    .endw

    fclose( esi )
    MD5Final( edi )
    MemFree( ebx )

    mov edi,sum
    lea esi,ctx.digest
    mov ecx,16
    rep movsb
    mov eax,1
    ret

calc_md5 endp

else
define MD5_LENGTH ( sizeof( uint_32 ) + sizeof( uint_16 ) + sizeof( uint_16 ) )
endif

.data

vtable dbgcvVtbl {
    dbgcv_flushpt,
    dbgcv_flushps,
    dbgcv_padbytes,
    dbgcv_alignps,
    dbgcv_flush_section,
    dbgcv_write_bitfield,
    dbgcv_write_array_type,
    dbgcv_write_ptr_type,
    dbgcv_write_type,
    dbgcv_write_type_procedure,
    dbgcv_write_symbol,
    dbgcv_cntproc,
    dbgcv_memberproc,
    dbgcv_enum_fields
    }

.code

;; option -Zi: write debug symbols and types
;; - symbols: segment $$SYMBOLS (OMF) or .debug$S (COFF)
;; - types:   segment $$TYPES (OMF) or .debug$T (COFF)
;; field Options.debug_symbols contains the format version
;; which is to be generated (CV4_, CV5_ or CV8_SIGNATURE)


cv_write_debug_tables proc uses esi edi ebx symbols:ptr dsym, types:ptr dsym, pv:ptr

  local i:int_t
  local len:int_t
  local objname:string_t
  local cv:dbgcv
  local lineTable:int_t

    mov cv.lpVtbl,&vtable
    mov esi,symbols
    mov cv.symbols,esi
    mov ecx,[esi].dsym.seginfo
    mov esi,[ecx].seg_info.CodeBuffer
    mov edi,types
    mov cv.types,edi
    mov ecx,[edi].dsym.seginfo
    mov edi,[ecx].seg_info.CodeBuffer

    mov cv.currtype,0x1000          ;; user-defined types start at 0x1000
    mov cv.level,0
    mov cv.param,pv
    movzx eax,Options.debug_symbols ;; "signature"
    stosd                           ;; init types
    mov cv.pt,edi
    mov [esi],eax                   ;; init symbols
    add esi,sizeof(uint_32)
    mov cv.ps,esi

    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )

        imul ecx,ModuleInfo.cnt_fnames,sizeof( cvfile )
        mov cv.files,LclAlloc( ecx )
        .for ( edi = eax,
               eax = 0,
               esi = ModuleInfo.FNames,
               ebx = ModuleInfo.cnt_fnames : ebx : ebx-- )
            movsd
            stosd
        .endf

        mov edi,LclAlloc( _MAX_PATH * 4 )
        _getcwd( edi, _MAX_PATH * 4 )
       .new cwdsize:dword = strlen( edi )
        add eax,edi
        mov objname,eax
        mov cv.currdir,edi

        ;; source filename string table

        mov ebx,cv.flush_section( 0x000000F3, 0 )
        inc [ebx].cvsection.length
        mov edi,cv.ps
        mov byte ptr [edi],0
        inc cv.ps

        ;; for each source file

        .for ( edi = cv.files, i = 0: i < ModuleInfo.cnt_fnames: i++, edi += cvfile )

            mov [edi].cvfile.offs,[ebx].cvsection.length
            mov esi,[edi].cvfile.name

            mov eax,[esi]
            .if ( al != '\' && al != '.' && ah != ':' )
                strcpy( objname, "\\" )
                strcat( objname, esi )
                mov esi,cv.currdir
            .endif

            inc strlen( esi )
            mov len,eax
            cv.flushps( eax )
            xchg edi,eax

            mov ecx,len
            add cv.ps,ecx
            add [ebx].cvsection.length,ecx
            rep movsb
            mov edi,eax

        .endf
        mov ecx,objname
        mov byte ptr [ecx],0
        cv.alignps()

        ;; $$000000 to line table

        mov eax,[ebx].cvsection.length
        add eax,3
        and eax,not 3
        add eax,cvsection
        mov lineTable,eax

        ;; source file info

        mov ebx,cv.flush_section( 0x000000F4, 0 )

        .for ( esi = cv.files, i = 0: i < ModuleInfo.cnt_fnames: i++, esi += cvfile )

            mov edi,cv.flushps( MD5_LENGTH )
            mov eax,[esi].cvfile.offs
            stosd
            mov [esi].cvfile.offs,[ebx].cvsection.length
ifdef USEMD5
            mov eax,0x0110
            stosw
            calc_md5( [esi].cvfile.name, edi )
            add edi,16
            xor eax,eax
            stosw
else
            xor eax,eax
            stosd
endif
            add [ebx].cvsection.length,MD5_LENGTH
            mov cv.ps,edi
        .endf

        mov eax,[ebx].cvsection.length
        add eax,3
        and eax,not 3
        add eax,cvsection + 12
        add lineTable,eax

        .if ( CV8Label )

           .new data:dword = 0
            mov ecx,CreateFixup( CV8Label, FIX_OFF32_SECREL, OPTJ_NONE )
            mov [ecx].fixup.locofs,lineTable
            store_fixup( ecx, cv.symbols, &data )
            mov ecx,CreateFixup( CV8Label, FIX_SEG, OPTJ_NONE )
            mov eax,lineTable
            add eax,4
            mov [ecx].fixup.locofs,eax
            store_fixup( ecx, cv.symbols, &data )
        .endif

        ;; line numbers for section

        mov cv.section,NULL

        .for ( esi = SegTable: esi: esi = [esi].dsym.next )

            mov ebx,[esi].dsym.seginfo

            .if ( [ebx].seg_info.LinnumQueue )

               .new Header:ptr CV_DebugSLinesHeader_t
               .new File:ptr CV_DebugSLinesFileBlockHeader_t
               .new Queue:ptr line_num_info

                .if ( cv.section )
                    cv.alignps()
                .endif

                mov edi,cv.flush_section( 0x000000F2,
                    sizeof( CV_DebugSLinesHeader_t ) + sizeof( CV_DebugSLinesFileBlockHeader_t ) )

                add edi,sizeof( cvsection )
                mov Header,edi
                mov [edi].CV_DebugSLinesHeader_t.offCon,0
                mov [edi].CV_DebugSLinesHeader_t.segCon,0
                mov [edi].CV_DebugSLinesHeader_t.flags,0
                mov [edi].CV_DebugSLinesHeader_t.cbCon,[esi].asym.max_offset
                add edi,sizeof( CV_DebugSLinesHeader_t )
                mov File,edi
                mov [edi].CV_DebugSLinesFileBlockHeader_t.offFile,0
                mov [edi].CV_DebugSLinesFileBlockHeader_t.nLines,0
                mov [edi].CV_DebugSLinesFileBlockHeader_t.cbBlock,0

                mov ebx,[ebx].seg_info.LinnumQueue
                mov ebx,[ebx].qdesc.head

                assume ebx:ptr line_num_info

                .while ( ebx )

                   .new Line:ptr CV_Line_t
                   .new Prev:ptr CV_Line_t
                   .new fileStart:int_t

                    mov eax,[ebx].srcfile
                    .if ( [ebx].number == 0 )
                        mov eax,[ebx].line_number
                        shr eax,20
                    .endif
                    mov fileStart,eax

                    mov ecx,File
                    mov [ecx].CV_DebugSLinesFileBlockHeader_t.cbBlock,12
                    mov edx,cv.files
                    mov [ecx].CV_DebugSLinesFileBlockHeader_t.offFile,[edx+eax*cvfile].cvfile.offs
                    mov Prev,NULL

                    .for ( : ebx: ebx = [ebx].next )

                        .new fileCur:int_t
                        .new linenum:int_t
                        .new offs:int_t

                        .if ( [ebx].number == 0 )
                            mov eax,[ebx].line_number
                            shr eax,20
                            mov ecx,[ebx].line_number
                            mov edx,[ebx].sym
                            mov edx,[edx].asym.offs
                        .else
                            mov eax,[ebx].srcfile
                            mov ecx,[ebx].number
                            mov edx,[ebx].line_number
                        .endif
                        .break .if ( fileStart != eax )

                        mov fileCur,eax
                        mov linenum,ecx
                        mov offs,edx

                        mov ecx,Prev
                        .if ( ecx )
                            mov eax,[ecx].CV_Line_t.flags
                            and eax,CV_lineflags_linenumStart
                            .if ( edx < [ecx].CV_Line_t.offs || \
                                  edx == [ecx].CV_Line_t.offs && \
                                  linenum == eax )
                                .continue
                            .endif
                        .endif

                        mov Line,cv.flushps( sizeof( CV_Line_t ) )
                        add cv.ps,sizeof( CV_Line_t )
                        mov ecx,cv.section
                        add [ecx].cvsection.length,sizeof( CV_Line_t )

                        mov ecx,File
                        inc [ecx].CV_DebugSLinesFileBlockHeader_t.nLines
                        add [ecx].CV_DebugSLinesFileBlockHeader_t.cbBlock,8

                        mov ecx,Line
                        mov [ecx].CV_Line_t.offs,offs
                        mov eax,linenum
                        or  eax,CV_lineflags_fStatement
                        mov [ecx].CV_Line_t.flags,eax
                        mov Prev,ecx
                    .endf
                .endw

                assume ebx:nothing

            .endif
        .endf
        .if ( cv.section )
            cv.alignps()
        .endif

        ;; symbol information

        cv.flush_section( 0x000000F1, 0 )
        mov esi,cv.ps
        .new start:ptr = esi

        ;; Name of object file

        mov edi,CurrFName[OBJ*4]
        mov eax,[edi]
        .if ( al != '\' && al != '.' && ah != ':' )
            strcpy( objname, "\\" )
            strcat( objname, edi )
            mov edi,cv.currdir
       .endif
        mov len,strlen( edi )
        add eax,sizeof( OBJNAMESYM ) - sizeof( word )
        mov [esi].OBJNAMESYM.reclen,ax
        mov [esi].OBJNAMESYM.rectyp,S_OBJNAME
        mov [esi].OBJNAMESYM.signature,0
        add cv.ps,sizeof( OBJNAMESYM ) - 1
        mov cv.ps,SetPrefixName( cv.ps, edi, len )
        mov ecx,objname
        mov byte ptr [ecx],0

        ;; compile flags

        mov edi,cv.ps
        mov [edi].COMPILESYM3.rectyp,S_COMPILE3
        strcpy( &[edi].COMPILESYM3.verSz, szCVCompiler )
        mov [edi].COMPILESYM3.reclen,sizeof(COMPILESYM3) + sizeof(@CStr(0)) - 2
        add cv.ps,sizeof(COMPILESYM3) + sizeof(@CStr(0))

        mov edx,cv.ps
        mov byte ptr [edx-1],0

        mov [edi].COMPILESYM3.flags,CV_CFL_MASM
        mov eax,ModuleInfo.curr_cpu
        and eax,P_CPU_MASK
        shr eax,4
        .if ( ModuleInfo.Ofssize == USE64 )
            mov eax,CV_CFL_X64
        .endif
        mov [edi].COMPILESYM3.machine,     ax
        mov [edi].COMPILESYM3.verFEMajor,  0
        mov [edi].COMPILESYM3.verFEMinor,  0
        mov [edi].COMPILESYM3.verFEBuild,  0
        mov [edi].COMPILESYM3.verFEQFE,    0
        mov [edi].COMPILESYM3.verMajor,    ASMC_MAJOR_VER
        mov [edi].COMPILESYM3.verMinor,    ASMC_MINOR_VER
        mov [edi].COMPILESYM3.verBuild,    ASMC_SUBMINOR_VER*100
        mov [edi].COMPILESYM3.verQFE,      0

        mov edi,cv.ps
        mov [edi].ENVBLOCKSYM.flags,0
        mov [edi].ENVBLOCKSYM.rectyp,S_ENVBLOCK
        lea edi,[edi].ENVBLOCKSYM.rgsz

        ;; pairs of 0-terminated strings - keys/values
        ;;
        ;; cwd - current working directory
        ;; exe - full path of executable
        ;; src - relative path to source (from cwd)

        mov esi,cv.currdir
        mov ebx,cwdsize
        mov eax,"dwc"
        stosd
        lea ecx,[ebx+1]
        rep movsb
        mov eax,"exe"
        stosd
        mov esi,_pgmptr
        inc strlen( esi )
        mov ecx,eax
        rep movsb
        mov eax,"crs"
        stosd
        mov edx,cv.files
        mov esi,[edx].cvfile.name
        .if ( _memicmp( esi, cv.currdir, ebx ) == 0 )
            lea esi,[esi+ebx+1]
        .endif
        inc strlen( esi )
        mov ecx,eax
        rep movsb
        xor eax,eax
        stosb
        mov eax,edi
        mov edx,cv.ps
        sub eax,edx
        sub eax,2
        mov [edx].ENVBLOCKSYM.reclen,ax
        mov cv.ps,edi

        ;; length needs to be added for each symbol

        mov ebx,cv.section
        sub edi,start
        add [ebx].cvsection.length,edi
    .else

        ;; 1. symbol record: object name

        mov esi,CurrFName[OBJ*4]
        .for ( ebx = strlen( esi ) : ebx : ebx-- )
            mov al,[esi+ebx-1]
            .if ( al == '/' || al == '\' )
                .break
            .endif
        .endf
        add esi,ebx
        mov ecx,strlen( esi )
        mov edi,cv.ps
        add eax,sizeof( OBJNAMESYM ) - sizeof(uint_16)
        mov [edi].OBJNAMESYM.reclen,ax
        mov [edi].OBJNAMESYM.rectyp,S_OBJNAME_ST
        mov [edi].OBJNAMESYM.signature,1
        add edi,sizeof( OBJNAMESYM ) - 1
        mov edi,SetPrefixName( edi, esi, ecx )

        ;; 2. symbol record: compiler

        mov ebx,strlen( szCVCompiler )
        add eax,sizeof( CFLAGSYM ) - sizeof(uint_16)
        mov [edi].CFLAGSYM.reclen,ax
        mov [edi].CFLAGSYM.rectyp,S_COMPILE

        ;; v2.11: use a valid 64-bit value

        mov eax,CV_CFL_X64
        .if ( ModuleInfo.defOfssize != USE64 )
             mov eax,ModuleInfo.curr_cpu
             and eax,P_CPU_MASK
             shr eax,4
        .endif

        ;; 0 isnt possible, 1 is 8086 and 80186

        .if ( al == 0 )
            mov al,CV_CFL_8086
        .endif
        mov [edi].CFLAGSYM.machine,al
        mov [edi].CFLAGSYM.language,CV_CFL_MASM
        mov [edi].CFLAGSYM.flags,0

        mov cl,ModuleInfo._model
        .if ( cl )
            mov edx,1
            shl edx,cl
            .if ( cl == MODEL_HUGE )
                or [edi].CFLAGSYM.flags,CV_AMB_HUGE shr 5
            .else
                mov eax,CV_AMB_NEAR
                .if edx & SIZE_DATAPTR
                    mov eax,CV_AMB_FAR
                .endif
                shl eax,5
                or [edi].CFLAGSYM.flags,ax
            .endif
            mov eax,CV_AMB_NEAR
            .if edx & SIZE_CODEPTR
                mov eax,CV_AMB_FAR
            .endif
            shl eax,8
            or [edi].CFLAGSYM.flags,ax
        .endif
        add edi,sizeof( CFLAGSYM ) - 1
        mov cv.ps,SetPrefixName( edi, szCVCompiler, ebx )
    .endif

    ;; scan symbol table for types

    xor esi,esi
    .while ( SymEnum( esi, &i ) )
        mov esi,eax
        .if ( [esi].asym.state == SYM_TYPE && \
              [esi].asym.typekind != TYPE_TYPEDEF && [esi].asym.cvtyperef == 0 )
            cv.write_type( esi )
        .endif
    .endw

    ;; scan symbol table for SYM_TYPE, SYM_INTERNAL

    xor esi,esi
    .while ( SymEnum( esi, &i ) )
        mov esi,eax
        .switch ( [esi].asym.state )
        .case SYM_TYPE
            ;; may create an S_UDT entry in the symbols table
            ;; v2.10: no UDTs for -Zi0 and -Zi1
            .break .if ( Options.debug_ext < CVEX_NORMAL )
        .case SYM_INTERNAL
            movzx eax,[esi].asym.flags
            mov edx,eax
            and edx,S_PREDEFINED
if EQUATESYMS
            ;; emit constants if -Zi3
            mov ecx,eax
            and ecx,S_ISEQUATE
            and eax,S_VARIABLE
            .if ( Options.debug_ext < CVEX_MAX )
                mov eax,ecx
            .endif
else
            and eax,S_ISEQUATE
endif
            .if ( ( Options.debug_symbols == CV_SIGNATURE_C13 && esi == CV8Label ) \
                || eax || edx ) ;; EQUates?

                .endc
            .endif
            cv.write_symbol( esi )
            .endc
        .endsw
    .endw

    ;; final flush for both types and symbols.
    ;; use 'fictional' size of SIZE_CV_SEGBUF!
    cv.flushpt( SIZE_CV_SEGBUF )
    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
        cv.alignps()
    .endif
    cv.flushps( SIZE_CV_SEGBUF )

    mov edi,types
    mov edx,[edi].dsym.seginfo
    mov eax,[edx].seg_info.current_loc
    mov [edi].asym.max_offset,eax
    mov [edx].seg_info.start_loc,0 ; required for COFF
    mov edi,symbols
    mov edx,[edi].dsym.seginfo
    mov eax,[edx].seg_info.current_loc
    mov [edi].asym.max_offset,eax
    mov [edx].seg_info.start_loc,0 ; required for COFF
    ret

cv_write_debug_tables endp


    end
