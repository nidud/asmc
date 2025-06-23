; DBGCV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: Generate CodeView symbolic debug info
;

include stddef.inc
include direct.inc

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include coff.inc
include fixup.inc
include dbgcv.inc
include linnum.inc

ifndef __UNIX__
define USEMD5
endif

extern CV8Label:asym_t

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

; structure for field enumeration callback function

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

; type of field enumeration callback function

CCALLBACK(cv_enum_func, :ptr dbgcv, :asym_t, :asym_t, :ptr counters)

.class dbgcv

    ps ptr byte ?
    pt ptr byte ?

    section ptr cvsection ?
    symbols asym_t ?
    types asym_t ?
    param ptr ?
    level dd ?          ; nesting level
    currtype dd ?       ; current type ( starts with 0x1000 )
    files ptr cvfile ?
    currdir string_t ?

    flushpt proc fastcall :dword
    flushps proc fastcall :dword
    padbytes proc fastcall :ptr byte
    alignps proc fastcall
    flush_section proc __ccall :dword, :dword

    write_bitfield proc __ccall :asym_t, :asym_t
    write_array_type proc __ccall :asym_t, :dword, :byte
    write_ptr_type proc __ccall :asym_t
    write_type proc __ccall :asym_t
    write_type_procedure proc __ccall :asym_t, :int_t
    write_symbol proc __ccall :asym_t

    cntproc proc __ccall :asym_t, :asym_t, :ptr counters
    memberproc proc __ccall :asym_t, :asym_t, :ptr counters
    enum_fields proc __ccall :asym_t, :cv_enum_func, :ptr counters
   .ends

   .data

padtab db LF_PAD1, LF_PAD2, LF_PAD3
reg64  db 0, 2, 3, 1, 7, 6, 4, 5

   .code

    option proc:private

; translate symbol's mem_type to a codeview typeref

GetTyperef proc fastcall uses rsi rdi _sym:asym_t, _Ofssize:byte

    mov rsi,rcx
    movzx edi,dl

    mov cl,[rsi].asym.mem_type
    .if ( !( cl & MT_SPECIAL ) )
        SizeFromMemtype( cl, edi, [rsi].asym.type )
        mov cl,[rsi].asym.mem_type
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
                    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
                        .return ST_CHAR16
                    .endif
                    .return ST_USHORT;ST_UINT2
                .endsw

            .endif
            .if ( [rsi].asym.Ofssize == USE32 )
                .return ST_UINT4
            .endif
            .return ST_UINT8
        .endif
    .else
        .switch cl
        .case MT_PTR
            mov al,[rsi].asym.Ofssize
            .switch al
            .case USE16
                .if ( [rsi].asym.is_far )
                    .return ST_PFVOID
                .endif
                .return ST_PVOID
            .case USE32
                .if ( [rsi].asym.is_far )
                    .return ST_32PFVOID
                .endif
                .return ST_32PVOID
            .case USE64
                mov al,[rsi].asym.ptr_memtype
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
                .case MT_PROC:   .return ST_64PVOID
                .endsw
                .return ST_PFCHAR;ST_PVOID
            .endsw
            .endc
        .case MT_BITS
            .if ( [rsi].asym.cvtyperef )
                .return( [rsi].asym.cvtyperef )
            .endif
            .endc
        .case MT_NEAR : .return ST_PVOID
        .case MT_FAR  : .return ST_PFVOID
        .case MT_TYPE
            .for ( rsi = [rsi].asym.type: [rsi].asym.type: rsi = [rsi].asym.type )
            .endf
            .if ( [rsi].asym.cvtyperef )
                .return( [rsi].asym.cvtyperef )
            .endif
             mov edx,edi
            .return( GetTyperef( rsi, dl ) )
        .endsw
    .endif
    .return( ST_NOTYPE )

GetTyperef endp


SetPrefixName proc fastcall p:ptr byte, name:ptr byte, len:dword

    xchg rdx,rsi
    mov rax,rdi
    mov rdi,rcx
    mov ecx,len

    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )

        mov [rdi],cl
        inc rdi
        rep movsb
    .else
        rep movsb
        mov byte ptr [rdi],0
        inc rdi
    .endif
    xchg rdi,rax
    mov rsi,rdx
    ret

SetPrefixName endp


; calc size of a codeview item in symbols segment

GetStructLen proc fastcall sym:asym_t, Ofssize:byte

    UNREFERENCED_PARAMETER(sym)
    UNREFERENCED_PARAMETER(Ofssize)

    .if Options.debug_symbols == CV_SIGNATURE_C7

        .if ( [rcx].asym.state == SYM_TYPE )
            .return( sizeof( UDTSYM_16t ) - 1 )
        .endif
        .if ( [rcx].asym.isproc && Options.debug_ext >= CVEX_REDUCED )
            .if ( dl == USE16 )
                .return sizeof( PROCSYM16 ) - 1
            .endif
            .return sizeof( PROCSYM32_16t ) - 1
        .endif
        .if ( [rcx].asym.mem_type == MT_NEAR || [rcx].asym.mem_type == MT_FAR )
            .if ( dl == USE16 )
                .return sizeof( LABELSYM16 ) - 1
            .endif
            .return sizeof( LABELSYM32 ) - 1
        .endif
if EQUATESYMS
        .if ( [rcx].asym.isequate )
            mov eax,sizeof( CONSTSYM_16t )
            .if ( [rcx].asym.value3264 || [rcx].asym.uvalue >= LF_NUMERIC )
                add eax,2
            .endif
            .return
        .endif
endif
        .return sizeof( DATASYM32_16t ) - 1
    .endif
    .if ( [rcx].asym.state == SYM_TYPE )
        .return( sizeof( UDTSYM ) - 1 )
    .endif
    .if ( [rcx].asym.isproc && Options.debug_ext >= CVEX_REDUCED )
        .return sizeof( PROCSYM32 ) - 1
    .endif
    .if ( [rcx].asym.mem_type == MT_NEAR || [rcx].asym.mem_type == MT_FAR )
        .return sizeof( LABELSYM32 ) - 1
    .endif
if EQUATESYMS
    .if ( [rcx].asym.isequate )
        mov eax,sizeof( CONSTSYM )
        .if ( [rcx].asym.value3264 || [rcx].asym.uvalue >= LF_NUMERIC )
            add eax,2
        .endif
        .return
    .endif
endif
    .return( sizeof( DATASYM32 ) - 1 )

GetStructLen endp

.enum {
    SYM_NOTYPE,
    SYM_SIMPLE,
    SYM_FWDREF,
    }

sym_type proc fastcall sym:ptr asym

    ldr rcx,sym

    .if ( [rcx].asym.state != SYM_TYPE || [rcx].asym.cvtyperef ||
          [rcx].asym.total_size == 0 || [rcx].asym.name_size == 0 ||
        ( [rcx].asym.typekind != TYPE_STRUCT && [rcx].asym.typekind != TYPE_UNION ) )
        .return( SYM_NOTYPE )
    .endif
    .if ( [rcx].asym.isvtable )
        .return( SYM_SIMPLE )
    .endif
    .for ( rcx = [rcx].asym.structinfo,
           rcx = [rcx].struct_info.head : rcx : rcx = [rcx].asym.next )

        mov rdx,[rcx].asym.type
        .if ( rdx && [rdx].asym.state == SYM_TYPE && [rdx].asym.cvtyperef == 0 )

            xor eax,eax
            .if ( [rdx].asym.typekind == TYPE_STRUCT || [rdx].asym.typekind == TYPE_UNION )
                mov rax,rdx
            .elseif ( [rdx].asym.typekind == TYPE_TYPEDEF && [rdx].asym.mem_type == MT_PTR &&
                      [rdx].asym.ptr_memtype == MT_EMPTY )
                mov rdx,[rdx].asym.target_type
                .if ( ( rdx && [rdx].asym.state == SYM_TYPE ) &&
                      ( [rdx].asym.typekind == TYPE_STRUCT || [rdx].asym.typekind == TYPE_UNION ) )
                    mov rax,rdx
                .endif
            .endif
            .if ( rax && [rax].asym.name_size && [rax].asym.total_size && [rax].asym.cvtyperef == 0 )
                .return( SYM_FWDREF )
            .endif
        .endif
    .endf
    .return( SYM_SIMPLE )

sym_type endp


; flush the segment buffer for symbols and types.
; For OMF, the buffer is written to disk. For COFF, it's
; more complicated, because we cannot write now, but also
; don't know yet the final size of the segment. So a linked
; list of buffer items has to be created. The contents will
; later be written inside coff_write_header().

    assume rbx:ptr dbgcv

dbgcv::flushpt proc fastcall uses rbx size:dword

    mov rbx,rcx
    mov rcx,[rbx].types
    mov rax,[rcx].asym.seginfo
    mov [rbx].pt,[rax].seg_info.flushfunc( rcx, [rbx].pt, edx, [rbx].param )
    ret

dbgcv::flushpt endp


dbgcv::flushps proc fastcall uses rbx size:dword

    mov rbx,rcx
    mov rcx,[rbx].symbols
    mov rax,[rcx].asym.seginfo
    mov [rbx].ps,[rax].seg_info.flushfunc( rcx, [rbx].ps, edx, [rbx].param )
    ret

dbgcv::flushps endp


dbgcv::padbytes proc fastcall uses rbx curr:ptr byte

    mov rcx,[rcx].dbgcv.types
    mov rcx,[rcx].asym.seginfo
    mov rcx,[rcx].seg_info.CodeBuffer

    .for ( :: rdx++ )

        mov rax,rdx
        sub rax,rcx
        .break .if ( !( eax & 3 ) )
        not eax
        and eax,3
        lea rbx,padtab
        mov al,[rbx+rax]
        mov [rdx],al
    .endf
    ret

dbgcv::padbytes endp


dbgcv::alignps proc fastcall

    mov rdx,[rcx].dbgcv.section
    mov eax,[rdx].cvsection.length
    and eax,3
    .ifnz

        mov edx,4
        sub edx,eax

        .while ( edx )

            mov rax,[rcx].dbgcv.ps
            mov byte ptr [rax],0
            inc [rcx].dbgcv.ps
            dec edx
        .endw
    .endif
    .return( [rcx].dbgcv.ps )

dbgcv::alignps endp


; write a bitfield to $$TYPES

dbgcv::write_bitfield proc __ccall uses rsi rdi rbx types:asym_t, sym:asym_t

    ldr rbx,this

    mov esi,CV_BITFIELD
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov esi,CV_BITFIELD_16t
    .endif
    mov rdi,[rbx].flushpt( esi )
    mov rcx,sym
    mov [rcx].asym.cvtyperef,[rbx].currtype
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [rdi].CV_BITFIELD_16t.size,( CV_BITFIELD_16t - sizeof(uint_16) )
        mov [rdi].CV_BITFIELD_16t.leaf,LF_BITFIELD_16t
        mov [rdi].CV_BITFIELD_16t.length,[rcx].asym.bitf_bits
        mov [rdi].CV_BITFIELD_16t.position,[rcx].asym.bitf_offs
        mov [rdi].CV_BITFIELD_16t.type,GetTyperef( types, USE16 )
    .else
        mov [rdi].CV_BITFIELD.size,( CV_BITFIELD - sizeof(uint_16) )
        mov [rdi].CV_BITFIELD.leaf,LF_BITFIELD
        mov [rdi].CV_BITFIELD.length,[rcx].asym.bitf_bits
        mov [rdi].CV_BITFIELD.position,[rcx].asym.bitf_offs
        mov [rdi].CV_BITFIELD.type,GetTyperef( types, USE16 )
        mov [rdi].CV_BITFIELD.reserved,0xF1F2 ; added for alignment
    .endif
    inc [rbx].currtype
    add [rbx].pt,rsi
    ret

dbgcv::write_bitfield endp


dbgcv::write_array_type proc __ccall uses rsi rdi rbx sym:asym_t, elemtype:dword, Ofssize:byte

    ldr rbx,this
    ldr rdi,sym

    .if ( elemtype == 0 )
        mov elemtype,GetTyperef( rdi, Ofssize )
    .endif

    xor esi,esi
    .if ( [rdi].asym.total_size >= LF_NUMERIC )
        add esi,sizeof( uint_32 )
    .endif
    mov eax,sizeof( CV_ARRAY )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov eax,sizeof( CV_ARRAY_16t )
    .endif

    lea edi,[rsi+rax+sizeof(uint_16)+1+3]
    and edi,not 3
    [rbx].flushpt(edi)

    mov ecx,edi
    mov rdi,rax
    add [rbx].pt,rcx

    sub ecx,sizeof(uint_16)
    mov [rdi].CV_ARRAY_16t.size,cx
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [rdi].CV_ARRAY_16t.leaf,LF_ARRAY_16t
        mov [rdi].CV_ARRAY_16t.elemtype,elemtype
        mov [rdi].CV_ARRAY_16t.idxtype,ST_LONG ;; ok?
        lea rdx,[rdi].CV_ARRAY_16t.data
    .else
        mov [rdi].CV_ARRAY.leaf,LF_ARRAY
        mov [rdi].CV_ARRAY.elemtype,elemtype
        mov [rdi].CV_ARRAY.idxtype,GetTyperef( sym, Ofssize )
        lea rdx,[rdi].CV_ARRAY.data
    .endif

    mov rcx,sym
    mov eax,[rcx].asym.total_size
    .if ( esi )
        mov word ptr [rdx],LF_ULONG
        mov [rdx+2],eax
        add rdx,6
    .else
        mov [rdx],ax
        add rdx,2
    .endif
    mov byte ptr [rdx],0 ; the array type name is empty
    inc rdx
    [rbx].padbytes(rdx)
    ret

dbgcv::write_array_type endp


; create a pointer type for procedure params and locals.
; the symbol's mem_type is MT_PTR.

dbgcv::write_ptr_type proc __ccall uses rsi rdi rbx sym:asym_t

    ldr rbx,this
    ldr rsi,sym

    .if ( ( [rsi].asym.ptr_memtype == MT_EMPTY && [rsi].asym.target_type == NULL ) ||
          ( [rsi].asym.ptr_memtype == MT_PROC ) )
        .return( GetTyperef( rsi, [rsi].asym.Ofssize ) )
    .endif
    mov edi,sizeof( CV_POINTER )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov edi,sizeof( CV_POINTER_16t )
    .endif
    [rbx].flushpt(edi)
    xchg rdi,rax

    add [rbx].pt,rax
    sub eax,sizeof( uint_16 )
    mov [rdi].CV_POINTER_16t.size,ax

    .if ( [rsi].asym.Ofssize == USE16 )
        mov eax,CV_PTR_NEAR
        .if ( [rsi].asym.is_far )
            mov eax,CV_PTR_FAR
        .endif
    .elseif ( [rsi].asym.Ofssize == USE32 )
        mov eax,CV_PTR_NEAR32
        .if ( [rsi].asym.is_far )
            mov eax,CV_PTR_FAR32
        .endif
    .else
        mov eax,CV_PTR_NEAR32
        .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
            mov eax,CV_PTR_64
        .endif
    .endif
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [rdi].CV_POINTER_16t.leaf,LF_POINTER_16t
        mov [rdi].CV_POINTER_16t.attr,ax
        mov [rdi].CV_POINTER_16t.pmclass,0
        mov [rdi].CV_POINTER_16t.pmenum,0
    .else
        mov [rdi].CV_POINTER.leaf,LF_POINTER
        mov [rdi].CV_POINTER.attr,eax
        mov [rdi].CV_POINTER.pmclass,0
        mov [rdi].CV_POINTER.pmenum,0
    .endif

    ; if indirection is > 1, define an untyped pointer - to be improved

    .if ( [rsi].asym.is_ptr > 1 )
        GetTyperef( rsi, [rsi].asym.Ofssize )
    .elseif ( [rsi].asym.target_type )
        ; the target's typeref must have been set here
        mov rcx,[rsi].asym.target_type
        .if ( [rcx].asym.cvtyperef )
            movzx eax,[rcx].asym.cvtyperef
        .else
            GetTyperef( rsi, [rsi].asym.Ofssize )
        .endif
    .else ; pointer to simple type
       .new memtype:byte = [rsi].asym.mem_type
        ; the target type is tmp. copied to mem_type
        ; thus GetTyperef() can be used
        mov [rsi].asym.mem_type,[rsi].asym.ptr_memtype
        GetTyperef( rsi, [rsi].asym.Ofssize )
        mov cl,memtype
        mov [rsi].asym.mem_type,cl
    .endif
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [rdi].CV_POINTER_16t.utype,ax
    .else
        mov [rdi].CV_POINTER.utype,eax
    .endif
    mov eax,[rbx].currtype
    inc [rbx].currtype
    ret

dbgcv::write_ptr_type endp


; field enumeration callback, does:
; - count number of members in a field list
; - calculate the size LF_MEMBER records inside the field list
; - create types ( array, structure ) if not defined yet

dbgcv::cntproc proc __ccall uses rsi rdi rbx type:asym_t, mbr:asym_t, cc:ptr counters

    ldr rbx,this
    ldr rdi,mbr
    ldr rsi,cc

    inc [rsi].counters.cnt
    mov eax,sizeof( CV_MEMBER )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov eax,sizeof( CV_MEMBER_16t )
    .endif

    mov rcx,type
    xor edx,edx
    .if ( [rcx].asym.typekind != TYPE_RECORD )
        add edx,[rdi].asym.offs
        add edx,[rsi].counters.ofs
    .endif
    .if ( edx >= LF_NUMERIC )
        add eax,DWORD ; v2.36.24 ...
    .endif

    mov ecx,[rdi].asym.name_size
    lea rax,[rcx+rax+2+1+3]
    and eax,not 3
    add [rsi].counters.size,eax

    ; field cvtyperef can only be queried from SYM_TYPE items!
    mov rcx,[rdi].asym.type
    .if ( [rdi].asym.mem_type == MT_TYPE && [rcx].asym.cvtyperef == 0 )
        inc [rbx].level
        [rbx].write_type( [rdi].asym.type )
        dec [rbx].level
    .elseif ( [rdi].asym.mem_type == MT_BITS && [rdi].asym.cvtyperef == 0 )
        [rbx].write_bitfield( type, rdi )
    .endif

    .if ( [rdi].asym.isarray )

        ; temporarily (mis)use ext_idx1 member to store the type;
        ; this field usually isn't used by struct fields

        mov [rdi].asym.ext_idx1,[rbx].currtype
        inc [rbx].currtype
        [rbx].write_array_type( rdi, 0, USE16 )
    .endif
    ret

dbgcv::cntproc endp


; field enumeration callback, does:
; - create LF_MEMBER record

dbgcv::memberproc proc __ccall uses rsi rdi rbx type:asym_t, mbr:asym_t, cc:ptr counters

   .new offs:int_t
   .new typelen:int_t

    ldr rbx,this
    ldr rsi,cc
    ldr rdi,mbr
    ldr rcx,type

    xor eax,eax
    xor edx,edx
    .if ( [rcx].asym.typekind != TYPE_RECORD )
        add edx,[rdi].asym.offs
        add edx,[rsi].counters.ofs
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

    mov ecx,[rdi].asym.name_size
    lea esi,[rax+rcx+2+1+3]

    and esi,not 3
    mov rdi,[rbx].flushpt(esi)
    add [rbx].pt,rsi
    mov eax,LF_MEMBER
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov eax,LF_MEMBER_16t
    .endif
    mov [rdi].CV_MEMBER_16t.leaf,ax

    mov rsi,mbr

    .if ( [rsi].asym.isarray )

        movzx eax,[rsi].asym.ext_idx1
        mov [rsi].asym.ext_idx1,0 ; reset the temporarily used field
    .else
        GetTyperef( rsi, USE16 )
    .endif

    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )

        mov [rdi].CV_MEMBER_16t.index,ax
        mov [rdi].CV_MEMBER_16t.attr,CV_public or ( CV_MTvanilla shl 2 )
        lea rcx,[rdi].CV_MEMBER_16t.offs
    .else
        mov [rdi].CV_MEMBER.index,eax
        mov [rdi].CV_MEMBER.attr,CV_public or ( CV_MTvanilla shl 2 )
        lea rcx,[rdi].CV_MEMBER.offs
    .endif

    mov eax,offs
    .if ( typelen == 0 )
        mov [rcx],ax
        add rcx,2
    .else
        mov word ptr [rcx],LF_ULONG
        mov [rcx+2],eax
        add rcx,6
    .endif
    SetPrefixName( rcx, [rsi].asym.name, [rsi].asym.name_size )
    [rbx].padbytes(rax)
    ret

dbgcv::memberproc endp


; field enumeration function.
; The MS debug engine has problem with anonymous members (both members
; and embedded structs).
; If such a member is included, the containing struct can't be "opened".
; The OW debugger and PellesC debugger have no such problems.
; However, for Masm-compatibility, anonymous members are avoided and
; anonymous struct members or embedded anonymous structs are "unfolded"
; in this function.


dbgcv::enum_fields proc __ccall uses rsi rdi rbx symb:asym_t, enumfunc:cv_enum_func, cc:ptr counters

    ldr rsi,symb
    mov rcx,[rsi].asym.structinfo

    .for ( rdi = [rcx].struct_info.head, ebx = 0: rdi: rdi = [rdi].asym.next )

        mov rcx,[rdi].asym.type
        mov eax,[rdi].asym.name_size

        .if ( rcx && eax == 0 && Options.debug_symbols == CV_SIGNATURE_C13 )

            ; v2.36.38 - add a name
            ;
            ; this is the "Name" in Visual Studio Watch list
            ;
            ;   Name         Type
            ;
            ; - record       byte
            ; - union        qword

            mov eax,6
            lea rdx,@CStr("struct")
            .if ( [rcx].asym.typekind == TYPE_UNION )
                lea rdx,@CStr("union")
                dec eax
            .elseif ( [rcx].asym.typekind == TYPE_RECORD )
                lea rdx,@CStr("record")
            .endif
            mov [rdi].asym.name,rdx
            mov [rdi].asym.name_size,eax
        .endif

        .if ( eax ) ; has member a name?

            enumfunc( this, rsi, rdi, cc )

        .elseif ( rcx )  ; is member a type (struct, union, record)?

            mov rdx,cc
            add [rdx].counters.ofs,[rdi].asym.offs
            this.enum_fields( rcx, enumfunc, rdx )

            mov rcx,cc
            sub [rcx].counters.ofs,[rdi].asym.offs

        .elseif ( [rsi].asym.typekind == TYPE_UNION )

            ; v2.11: include anonymous union members.
            ; to make the MS debugger work with those members, they must have a name -
            ; a temporary name is generated below which starts with "@@".

           .new pold:string_t = [rdi].asym.name
           .new tmpname[8]:char_t

            tsprintf( &tmpname, "@@%u", ebx )
            mov [rdi].asym.name_size,eax
            inc ebx
            mov [rdi].asym.name,&tmpname
            enumfunc( this, rsi, rdi, cc )
            mov [rdi].asym.name,pold
            mov [rdi].asym.name_size,0
        .endif
    .endf
    ret

dbgcv::enum_fields endp


; write a LF_PROCEDURE & LF_ARGLIST type for procedures

dbgcv::write_type_procedure proc __ccall uses rsi rdi rbx sym:asym_t, cnt:int_t

    ldr rbx,this
    mov esi,sizeof( CV_PROCEDURE )
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov esi,sizeof( CV_PROCEDURE_16t )
    .endif
    mov rdi,[rbx].flushpt(esi)
    add [rbx].pt,rsi
    sub esi,sizeof( uint_16 )
    mov [rdi].CV_PROCEDURE_16t.size,si
    inc [rbx].currtype

    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [rdi].CV_PROCEDURE_16t.leaf,LF_PROCEDURE_16t
        mov [rdi].CV_PROCEDURE_16t.rvtype,ST_VOID
        mov [rdi].CV_PROCEDURE_16t.calltype,0
        mov [rdi].CV_PROCEDURE_16t.funcattr,0
        mov [rdi].CV_PROCEDURE_16t.parmcount,cnt
        mov [rdi].CV_PROCEDURE_16t.arglist,[rbx].currtype
        mov esi,sizeof( CV_ARGLIST_16t )
        mov eax,CV_typ16_t
    .else
        mov [rdi].CV_PROCEDURE_16t.leaf,LF_PROCEDURE
        mov [rdi].CV_PROCEDURE.rvtype,ST_VOID
        mov [rdi].CV_PROCEDURE.calltype,0
        mov [rdi].CV_PROCEDURE.funcattr,0
        mov [rdi].CV_PROCEDURE.parmcount,cnt
        mov [rdi].CV_PROCEDURE.arglist,[rbx].currtype
        mov esi,sizeof( CV_ARGLIST )
        mov eax,CV_typ_t
    .endif

    mul cnt
    add esi,eax
    mov rdi,[rbx].flushpt(esi)
    add [rbx].pt,rsi
    sub esi,sizeof( uint_16 )
    mov [rdi].CV_ARGLIST_16t.size,si

    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov [rdi].CV_ARGLIST_16t.leaf,LF_ARGLIST_16t
        mov [rdi].CV_ARGLIST_16t.count,cnt
        add rdi,sizeof( CV_ARGLIST_16t )
    .else
        mov [rdi].CV_ARGLIST_16t.leaf,LF_ARGLIST
        mov [rdi].CV_ARGLIST.count,cnt
        add rdi,sizeof( CV_ARGLIST )
    .endif

    ; fixme: order might be wrong ( is "push" order )

    mov rsi,sym
    mov rsi,[rsi].asym.procinfo

    .for ( rsi = [rsi].proc_info.paralist: rsi: rsi = [rsi].asym.nextparam )

        movzx eax,[rsi].asym.ext_idx1
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            stosw
        .elseif ( MODULE.defOfssize == USE64 ) ;; ...
            dec cnt
            mov ecx,cnt
            mov [rdi+rcx*4],eax
        .else
            stosd
        .endif
    .endf
    inc [rbx].currtype
    ret

dbgcv::write_type_procedure endp


; write a type. Items are dword-aligned,
;    cv: debug state
;   sym: type to dump

dbgcv::write_type proc __ccall uses rsi rdi rbx sym:asym_t

  local name:LPSTR
  local namesize:dword
  local typelen:dword
  local size:dword
  local leaf:word
  local property:CV_prop_t
  local count:counters

    ldr rbx,this
    ldr rsi,sym

    ; v2.10: handle typedefs. when the types are enumerated,
    ; typedefs are ignored.

    .if ( [rsi].asym.typekind == TYPE_TYPEDEF )

        .if ( [rsi].asym.mem_type == MT_PTR )

            mov rcx,[rsi].asym.target_type
            .if ( [rsi].asym.ptr_memtype != MT_PROC && rcx && [rcx].asym.cvtyperef == 0 )
                .if ( [rbx].level == 0 ) ; avoid circles
                    [rbx].write_type( [rsi].asym.target_type )
                .endif
            .endif
            mov [rsi].asym.cvtyperef,[rbx].write_ptr_type( rsi )
            .return
        .endif

        ; v2.34.15: added for struct typedefs

        .if ( [rsi].asym.mem_type == MT_TYPE && [rsi].asym.type )

            mov rdi,rsi
            .while ( [rdi].asym.type )
                mov rdi,[rdi].asym.type
            .endw
            .if ( [rdi].asym.cvtyperef == 0 )
                [rbx].write_type( rdi )
            .endif
            mov [rsi].asym.cvtyperef,[rdi].asym.cvtyperef
        .endif
        .return

    .elseif ( [rsi].asym.typekind == TYPE_NONE )
        .return
    .endif

    ; v2.34.34 - change the write order

    xor eax,eax
    mov property,ax
    .if ( [rsi].asym.total_size >= LF_NUMERIC )
        mov eax,sizeof( uint_32 )
    .endif
    mov typelen,eax
    .if ( [rbx].level )
        mov property,CV_prop_isnested
    .endif

    mov rax,[rsi].asym.name
    mov ecx,[rsi].asym.name_size
    .if ( ecx == 0 )

        lea rax,@CStr("__unnamed")
        mov ecx,9 ; 9 is sizeof("__unnamed")

        .if ( Options.debug_symbols == CV_SIGNATURE_C13 )

            ; v2.36.38 - add a type name

            mov ecx,6
            lea rax,@CStr("struct")
            .if ( [rsi].asym.typekind == TYPE_UNION )
                lea rax,@CStr("union")
                dec ecx
            .elseif ( [rsi].asym.typekind == TYPE_RECORD )
                lea rax,@CStr("record")
            .endif

            ; this is the "Type" in Visual Studio Watch list
            ;
            ;   Name         Type
            ;
            ; - record       byte
            ; - union        qword

            mov edx,[rsi].asym.total_size
            .switch edx
            .case 1
                lea rax,@CStr("byte")
                mov ecx,4
               .endc
            .case 2
                lea rax,@CStr("word")
                mov ecx,4
               .endc
            .case 4
                lea rax,@CStr("dword")
                mov ecx,5
               .endc
            .case 8
                lea rax,@CStr("qword")
                mov ecx,5
               .endc
            .case 16
                lea rax,@CStr("oword")
                mov ecx,5
               .endc
            .endsw
        .endif
    .elseif ( [rsi].asym.cvtyperef == 0 && [rsi].asym.fwdref )
        or property,CV_prop_fwdref
    .endif
    mov name,rax
    mov namesize,ecx

    movzx eax,[rsi].asym.typekind
    .switch eax
    .case TYPE_UNION
        mov eax,sizeof( CV_UNION )
        mov leaf,LF_UNION
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov eax,sizeof( CV_UNION_16t )
            mov leaf,LF_UNION_16t
        .elseif ( Options.debug_symbols == CV_SIGNATURE_C11 )
            mov eax,sizeof( CV_UNION_16t )
            mov leaf,LF_UNION_ST
        .endif
        add eax,typelen
        add eax,namesize
        add eax,2+1+3
        and eax,not 3
        mov size,eax
       .endc
    .case TYPE_RECORD
        or property,CV_prop_packed ; is "packed"
        ; no break
    .case TYPE_STRUCT
        mov eax,sizeof( CV_STRUCT )
        mov leaf,LF_STRUCTURE
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov eax,sizeof( CV_STRUCT_16t )
            mov leaf,LF_STRUCTURE_16t
        .elseif ( Options.debug_symbols == CV_SIGNATURE_C11 )
            mov eax,sizeof( CV_STRUCT_16t )
            mov leaf,LF_STRUCTURE_ST
        .endif
        add eax,typelen
        add eax,namesize
        add eax,2+1+3
        and eax,not 3
        mov size,eax
       .endc
    .endsw

    ; Count the member fields. If a member's type is unknown, create it!

    mov count.cnt,0
    mov count.size,0
    mov count.ofs,0

    .if !( property & CV_prop_fwdref )
        mov rcx,[rbx]
        [rbx].enum_fields( rsi, [rcx].dbgcvVtbl.cntproc, &count )
    .endif

    ; write the fieldlist record

    mov rdi,[rbx].flushpt(CV_FIELDLIST)
    add [rbx].pt,CV_FIELDLIST

    mov eax,sizeof(CV_FIELDLIST) - sizeof(uint_16)
    add eax,count.size
    mov [rdi].CV_FIELDLIST.size,ax
    mov eax,LF_FIELDLIST
    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
        mov eax,LF_FIELDLIST_16t
    .endif
    mov [rdi].CV_FIELDLIST.leaf,ax

    ; add the struct's members to the fieldlist.

    mov count.ofs,0
    .if !( property & CV_prop_fwdref )
        mov rcx,[rbx]
        [rbx].enum_fields( rsi, [rcx].dbgcvVtbl.memberproc, &count )
    .endif

    mov rdi,[rbx].flushpt(size)
    mov eax,size
    sub eax,sizeof( uint_16 )
    mov [rdi].CV_STRUCT.size,ax
    mov [rdi].CV_STRUCT.leaf,leaf
    mov [rdi].CV_STRUCT.count,count.cnt

    movzx eax,[rsi].asym.typekind
    .switch eax
    .case TYPE_UNION
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov [rdi].CV_UNION_16t.field,[rbx].currtype
            mov [rdi].CV_UNION_16t.property,property
            lea rcx,[rdi].CV_UNION_16t.data
        .else
            mov [rdi].CV_UNION.field,[rbx].currtype
            mov [rdi].CV_UNION.property,property
            lea rcx,[rdi].CV_UNION.data
        .endif
        inc [rbx].currtype
       .endc
    .case TYPE_RECORD
    .case TYPE_STRUCT
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov [rdi].CV_STRUCT_16t.field,[rbx].currtype
            mov [rdi].CV_STRUCT_16t.property,property
            mov [rdi].CV_STRUCT_16t.derived,0
            mov [rdi].CV_STRUCT_16t.vshape,0
            lea rcx,[rdi].CV_STRUCT_16t.data
        .else
            mov [rdi].CV_STRUCT.field,[rbx].currtype
            mov [rdi].CV_STRUCT.property,property
            mov [rdi].CV_STRUCT.derived,0
            mov [rdi].CV_STRUCT.vshape,0
            lea rcx,[rdi].CV_STRUCT.data
        .endif
        inc [rbx].currtype
       .endc
    .endsw

    mov rdx,sym
    mov eax,[rdx].asym.total_size
    .if ( typelen == 0 )
        mov [rcx],ax
        add rcx,2
    .else
        mov word ptr [rcx],LF_ULONG
        mov [rcx+2],eax
        add rcx,6
    .endif
    SetPrefixName( rcx, name, namesize )
    [rbx].padbytes(rax)
    mov eax,size
    add [rbx].pt,rax

    ; WinDbg wants embedded structs to have a name - else it won't allow to "open" it.

    mov [rsi].asym.cvtyperef,[rbx].currtype
    inc [rbx].currtype
    ret

dbgcv::write_type endp

; get register values for S_REGISTER

getregister proc fastcall uses rsi rdi rbx sym:asym_t

    mov rsi,rcx
    .for ( edi = 0, ebx = 0: ebx < 2: ebx++ )
        movzx edx,[rsi].asym.regist[rbx*2]
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
            lea rcx,[rbx*8]
            shl eax,cl
            or edi,eax
        .endif
    .endf
    .return( edi )

getregister endp

;
;  convert register number
;        0  1  2  3  4  5  6  7
; -----------------------------
; from: ax cx dx bx sp bp si di
;   to: ax bx cx dx si di bp sp
;

get_x64_regno proc fastcall regno:dword

    UNREFERENCED_PARAMETER(regno)

    .if ( ecx >= T_RAX && ecx <= T_RDI )
        lea rax,reg64
        movzx eax,byte ptr [rax+rcx-T_RAX]
        add eax,CV_AMD64_RAX
        .return
    .endif
    .if ( ecx >= T_R8 && ecx <= T_R15 )
        lea eax,[rcx-T_R8+CV_AMD64_RAX+8]
        .return
    .endif
    ; it's a 32-bit register r8d-r15d
    lea eax,[rcx-T_R8D+CV_AMD64_R8D]
    ret

get_x64_regno endp


; write a symbol
;    cv: debug state
;   sym: symbol to write
; the symbol has either state SYM_INTERNAL or SYM_TYPE.

dbgcv::write_symbol proc __ccall uses rsi rdi rbx sym:asym_t

  local len:int_t
  local ofs:dword
  local rlctype:fixup_types
  local Ofssize:byte
  local fixp:ptr fixup
  local pproc:asym_t
  local lcl:asym_t
  local i:int_t, j:int_t, k:int_t
  local cnt[2]:int_t
  local locals[2]:asym_t
  local q:asym_t
  local size:dword
  local leaf:word
  local typeref:uint_16

    ldr rsi,sym
    ldr rbx,this

    mov Ofssize,GetSymOfssize( rsi )
    mov len,GetStructLen( rsi, al )

if EQUATESYMS

    .if ( [rsi].asym.isequate )

        mov edi,LF_SHORT
        mov eax,[rsi].asym.value
        mov edx,[rsi].asym.value3264

        .if ( edx || eax >= LF_NUMERIC )

            test edx,edx
            .ifs
                neg eax
                neg edx
                sbb edx,0
            .endif
            .if !edx
                .if eax <= 0xFF
                    mov edi,LF_CHAR
                    dec len
                .elseif eax > 0xFFFF
                    mov edi,LF_LONG
                    add len,2
                .endif
            .else
                add len,6
                mov edi,LF_QUADWORD
            .endif
        .endif

        mov eax,len
        mov ecx,[rsi].asym.name_size
        lea edx,[rax+rcx+1]
        mov rcx,[rbx].flushps(edx)
        xchg rdi,rcx

        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )

            mov [rdi].CONSTSYM_16t.rectyp,S_CONSTANT_16t
            mov [rdi].CONSTSYM_16t.typind,ST_SHORT
            lea rdx,[rdi].CONSTSYM_16t.name
        .else
            mov [rdi].CONSTSYM.rectyp,S_CONSTANT
            mov [rdi].CONSTSYM.typind,ST_SHORT
            lea rdx,[rdi].CONSTSYM.name
        .endif

        mov eax,[rsi].asym.value
        .if ( [rsi].asym.value3264 || eax >= LF_NUMERIC )
            .if ( ecx == LF_CHAR )
                mov [rdx],al
                mov eax,ecx
                mov ecx,ST_CHAR
            .elseif ( ecx == LF_SHORT )
                mov [rdx],ax
                mov eax,ecx
                mov ecx,ST_SHORT
            .elseif ( ecx == LF_LONG )
                mov [rdx],eax
                mov eax,ecx
                mov ecx,ST_LONG
            .elseif ( ecx == LF_QUADWORD )
                mov [rdx],eax
                mov eax,[rsi].asym.value3264
                mov [rdx+4],eax
                mov eax,ecx
                mov ecx,ST_QUAD
            .endif
            mov [rdi].CONSTSYM_16t.typind,cx
        .endif

        mov [rdx-2],ax
        mov eax,len
        mov ecx,[rsi].asym.name_size
        lea edx,[rax+rcx-2+1]
        mov [rdi].CONSTSYM.reclen,dx
        add [rbx].ps,rax

        .if ( Options.debug_symbols == CV_SIGNATURE_C13 )

            add edx,2
            mov rcx,[rbx].section
            add [rcx].cvsection.length,edx
        .endif
        mov [rbx].ps,SetPrefixName( [rbx].ps, [rsi].asym.name, [rsi].asym.name_size )
       .return
    .endif
endif

    mov ecx,[rsi].asym.name_size
    lea eax,[rcx+rax+1]
    mov rdi,[rbx].flushps(eax)

    .if ( [rsi].asym.state == SYM_TYPE )

        ; Masm does only generate an UDT for typedefs
        ; if the underlying type is "used" somewhere.
        ; example:
        ; LPSTR typedef ptr BYTE
        ; will only generate an S_UDT for LPSTR if either
        ; "LPSTR" or "ptr BYTE" is used in the source.

        mov eax,sizeof( UDTSYM )
        mov edx,S_UDT
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov eax,sizeof( UDTSYM_16t )
            mov edx,S_UDT_16t
        .endif
        mov [rdi].UDTSYM_16t.rectyp,dx
        sub eax,sizeof(uint_16)
        mov ecx,[rsi].asym.name_size
        add eax,ecx
        mov [rdi].UDTSYM_16t.reclen,ax

        ; v2.10: pointer typedefs will now have a cv_typeref

        .if ( [rsi].asym.cvtyperef )
            movzx eax,[rsi].asym.cvtyperef
        .else
            GetTyperef( rsi, Ofssize )
        .endif
        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov [rdi].UDTSYM_16t.typind,ax
        .else
            mov [rdi].UDTSYM.typind,eax
        .endif

        ; Some typedefs won't get a valid type (<name> TYPEDEF PROTO ...).
        ; In such cases just skip the type!

        .if ( eax )

            mov eax,len
            add [rbx].ps,rax
            mov [rbx].ps,SetPrefixName( [rbx].ps, [rsi].asym.name, [rsi].asym.name_size )

            .if ( Options.debug_symbols == CV_SIGNATURE_C13 )

                mov eax,[rsi].asym.name_size
                add eax,len
                inc eax
                mov rcx,[rbx].section
                add [rcx].cvsection.length,eax
            .endif
        .endif
        .return
    .endif

    ; rest is SYM_INTERNAL
    ; there are 3 types of INTERNAL symbols:
    ; - numeric constants ( equates, memtype MT_EMPTY )
    ; - code labels, memtype == MT_NEAR | MT_FAR
    ;   - procs
    ;   - simple labels
    ; - data labels, memtype != MT_NEAR | MT_FAR

    .if ( [rsi].asym.isproc && Options.debug_ext >= CVEX_REDUCED ) ;; v2.10: no locals for -Zi0

        mov rdx,[rsi].asym.procinfo
        mov pproc,rdx

        ; for PROCs, scan parameters and locals and create their types.

        ; scan local symbols

        mov locals[0*asym_t],[rdx].proc_info.paralist
        mov locals[1*asym_t],[rdx].proc_info.locallist

        .for ( i = 0: i < 2: i++ )

            .if ( MODULE.defOfssize == USE64 && i == 0 )
                .for ( j = 0, rcx = locals[0*asym_t] : rcx : rsi = rcx,
                       rcx = [rcx].asym.nextparam, j++ )
                .endf
            .endif

            mov ecx,i
            mov cnt[rcx*int_t],0
            .for ( rdi = locals[rcx*asym_t] : rdi : rdi = [rdi].asym.nextparam )

                mov ecx,i
                .if ( !( MODULE.defOfssize == USE64 && ecx == 0 ) )
                    mov rsi,rdi
                .endif

                inc cnt[rcx*int_t]
                .if ( [rsi].asym.mem_type == MT_EMPTY && [rsi].asym.is_vararg )
                    mov typeref,ST_PVOID
                .else
                    .if ( [rsi].asym.mem_type == MT_PTR )
                        [rbx].write_ptr_type( rsi )
                    .else
                        GetTyperef( rsi, Ofssize )
                    .endif
                    mov typeref,ax
                .endif

                .if ( [rsi].asym.isarray )

                    [rbx].write_array_type( rsi, typeref, Ofssize )
                    mov eax,[rbx].currtype
                    inc [rbx].currtype
                    mov typeref,ax
                .endif

                mov [rsi].asym.ext_idx1,typeref
                .if ( MODULE.defOfssize == USE64 && i == 0 )
                    .fors ( ecx = 1, j--, rsi = locals[0]: j > ecx: ecx++,
                            rsi = [rsi].asym.nextparam )
                    .endf
                .endif
            .endf
        .endf

        mov rdi,[rbx].ps
        mov rsi,sym

        .if ( Ofssize == USE16 )

            mov eax,[rsi].asym.name_size
            add eax,sizeof( PROCSYM16 ) - sizeof(uint_16)
            mov [rdi].PROCSYM16.reclen,ax
            mov eax,S_LPROC16
            .if ( [rsi].asym.ispublic )
                mov eax,S_GPROC16
            .endif
            mov [rdi].PROCSYM16.rectyp,ax

            mov [rdi].PROCSYM16.pParent,0  ;; filled by CVPACK
            mov [rdi].PROCSYM16.pEnd,0     ;; filled by CVPACK
            mov [rdi].PROCSYM16.pNext,0    ;; filled by CVPACK
            mov [rdi].PROCSYM16.len,[rsi].asym.total_size
            mov rcx,[rsi].asym.procinfo
            mov [rdi].PROCSYM16.DbgStart,[rcx].proc_info.size_prolog
            mov [rdi].PROCSYM16.DbgEnd,[rsi].asym.total_size
            mov [rdi].PROCSYM16.off,0
            mov [rdi].PROCSYM16._seg,0
            mov [rdi].PROCSYM16.typind,[rbx].currtype ;; typeref LF_PROCEDURE
            xor eax,eax
            .if ( [rsi].asym.mem_type == MT_FAR )
                mov eax,CV_PROCF_FAR
            .endif
            mov [rdi].PROCSYM16.flags,al
            mov rlctype,FIX_PTR16
            mov ofs,offsetof( PROCSYM16, off )
        .else

            mov size,sizeof( PROCSYM32 )
            mov eax,S_LPROC32
            .if ( [rsi].asym.ispublic )
                mov eax,S_GPROC32
            .endif
            mov leaf,ax
            .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                mov size,sizeof( PROCSYM32_16t )
                mov eax,S_LPROC32_16t
                .if ( [rsi].asym.ispublic )
                    mov eax,S_GPROC32_16t
                .endif
                mov leaf,ax
            .endif
            mov eax,size
            sub eax,sizeof(uint_16)
            mov ecx,[rsi].asym.name_size
            add eax,ecx
            mov [rdi].PROCSYM32_16t.reclen,ax
            mov [rdi].PROCSYM32_16t.rectyp,leaf
            mov [rdi].PROCSYM32_16t.pParent,0   ; filled by CVPACK
            mov [rdi].PROCSYM32_16t.pEnd,0      ; filled by CVPACK
            mov [rdi].PROCSYM32_16t.pNext,0     ; filled by CVPACK
            mov [rdi].PROCSYM32_16t.len,[rsi].asym.total_size
            mov rcx,[rsi].asym.procinfo
            movzx eax,[rcx].proc_info.size_prolog
            mov [rdi].PROCSYM32_16t.DbgStart,eax
            mov [rdi].PROCSYM32_16t.DbgEnd,[rsi].asym.total_size
            .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                mov [rdi].PROCSYM32_16t.off,0
                mov [rdi].PROCSYM32_16t._seg,0
                mov [rdi].PROCSYM32_16t.typind,[rbx].currtype ; typeref LF_PROCEDURE
                mov [rdi].PROCSYM32_16t.flags,0
                .if ( [rsi].asym.mem_type == MT_FAR )
                    mov [rdi].PROCSYM32_16t.flags,CV_PFLAG_FAR
                .endif
                mov rcx,pproc
                .if ( [rcx].proc_info.fpo )
                    mov [rdi].PROCSYM32_16t.flags,CV_PFLAG_NOFPO
                .endif
                mov ofs,offsetof( PROCSYM32_16t, off )
            .else
                mov [rdi].PROCSYM32.off,0
                mov [rdi].PROCSYM32._seg,0
                mov [rdi].PROCSYM32.typind,[rbx].currtype
                mov [rdi].PROCSYM32.flags,0
                .if ( [rsi].asym.mem_type == MT_FAR )
                    mov [rdi].PROCSYM32.flags,CV_PFLAG_FAR
                .endif
                mov rcx,pproc
                .if ( [rcx].proc_info.fpo )
                    mov [rdi].PROCSYM32.flags,CV_PFLAG_NOFPO
                .endif
                mov ofs,offsetof( PROCSYM32, off )
            .endif
            mov rlctype,FIX_PTR32
        .endif
        [rbx].write_type_procedure( sym, cnt[0] )

    .elseif ( [rsi].asym.mem_type == MT_NEAR || [rsi].asym.mem_type == MT_FAR )

        mov eax,[rsi].asym.name_size
        .if ( Ofssize == USE16 )

            add eax,sizeof( LABELSYM16 ) - sizeof(uint_16)
            mov [rdi].LABELSYM16.reclen,ax
            mov [rdi].LABELSYM16.rectyp,S_LABEL16
            xor eax,eax
            mov [rdi].LABELSYM16.off,ax
            mov [rdi].LABELSYM16._seg,ax
            .if ( [rsi].asym.mem_type == MT_FAR )
                mov eax,CV_PROCF_FAR
            .endif
            mov [rdi].LABELSYM16.flags,al
            mov rlctype,FIX_PTR16
            mov ofs,offsetof( LABELSYM16, off )
        .else

            add eax,sizeof( LABELSYM32 ) - sizeof(uint_16)
            mov [rdi].LABELSYM32.reclen,ax
            .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                mov [rdi].LABELSYM32.rectyp,S_LABEL32_ST
            .else
                mov [rdi].LABELSYM32.rectyp,S_LABEL32
            .endif
            xor eax,eax
            mov [rdi].LABELSYM32.off,eax
            mov [rdi].LABELSYM32._seg,ax
            .if ( [rsi].asym.mem_type == MT_FAR )
                mov eax,CV_PROCF_FAR
            .endif
            mov [rdi].LABELSYM32.flags,al
            mov rlctype,FIX_PTR32
            mov ofs,offsetof( LABELSYM32, off )
        .endif

    .else

        ; v2.10: set S_GDATA[16|32] if symbol is public

        .if ( [rsi].asym.isarray )
            [rbx].write_array_type( rsi, 0, Ofssize )
            mov eax,[rbx].currtype
            inc [rbx].currtype
        .else
            GetTyperef( rsi, Ofssize )
        .endif
        mov typeref,ax

        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
            mov size,sizeof( DATASYM32_16t )
            mov [rdi].DATASYM32_16t.off,0
            mov [rdi].DATASYM32_16t._seg,0
            mov [rdi].DATASYM32_16t.typind,ax
            mov ofs,offsetof( DATASYM32_16t, off )
        .else
            mov size,sizeof( DATASYM32 )
            mov [rdi].DATASYM32.off,0
            mov [rdi].DATASYM32._seg,0
            mov [rdi].DATASYM32.typind,eax
            mov ofs,offsetof( DATASYM32, off )
        .endif
        mov eax,[rsi].asym.name_size
        add eax,size
        sub eax,sizeof(uint_16)
        mov [rdi].DATASYM32_16t.reclen,ax
        .if ( Ofssize == USE16 )
            mov eax,S_LDATA16
            .if ( [rsi].asym.ispublic )
                mov eax,S_GDATA16
            .endif
            mov leaf,ax
            mov rlctype,FIX_PTR16
        .else
            mov rcx,[rsi].asym.segm
            mov eax,1
            .if ( ( MODULE.cv_opt & CVO_STATICTLS ) && [rcx].seg_info.clsym )
                mov rcx,[rcx].seg_info.clsym
                .if ( tstrcmp( [rcx].asym.name, "TLS" ) == 0 )
                    mov ecx,S_LTHREAD32_16t
                    .if ( [rsi].asym.ispublic )
                        mov ecx,S_GTHREAD32_16t
                    .endif
                .endif
            .endif
            .if ( eax )
                .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                    mov ecx,S_LDATA32_16t
                    .if ( [rsi].asym.ispublic )
                        mov ecx,S_GDATA32_16t
                    .endif
                .else
                    mov ecx,S_LDATA32
                    .if ( [rsi].asym.ispublic )
                        mov ecx,S_GDATA32
                    .endif
                .endif
            .endif
            mov leaf,cx
            mov rlctype,FIX_PTR32
        .endif
        mov [rdi].DATASYM32_16t.rectyp,leaf
    .endif
    mov eax,ofs
    add [rbx].ps,rax
    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
        mov rcx,[rbx].section
        add [rcx].cvsection.length,eax
    .endif

    mov rax,[rbx].symbols
    mov rdi,[rax].asym.seginfo
    mov rax,[rbx].ps
    sub rax,[rdi].seg_info.CodeBuffer
    add eax,[rdi].seg_info.start_loc
    mov [rdi].seg_info.current_loc,eax

    .if ( Options.output_format == OFORMAT_COFF )

        ; COFF has no "far" fixups. Instead Masm creates a
        ; section-relative fixup + a section fixup.

        mov rcx,CreateFixup( rsi, FIX_OFF32_SECREL, OPTJ_NONE )
        mov [rcx].fixup.locofs,[rdi].seg_info.current_loc
        store_fixup( rcx, [rbx].symbols, [rbx].ps )
        mov rcx,CreateFixup( rsi, FIX_SEG, OPTJ_NONE )
        mov eax,sizeof( int_16 )
        .if ( rlctype == FIX_PTR32 )
            mov eax,sizeof( int_32 )
        .endif
        add eax,[rdi].seg_info.current_loc
        mov [rcx].fixup.locofs,eax
        store_fixup( rcx, [rbx].symbols, [rbx].ps )
    .else
        mov rcx,CreateFixup( rsi, rlctype, OPTJ_NONE )
        mov [rcx].fixup.locofs,[rdi].seg_info.current_loc

        ; todo: for OMF, delay fixup store until checkflush has been called!

        store_fixup( rcx, [rbx].symbols, [rbx].ps )
    .endif

    mov eax,len
    sub eax,ofs
    add [rbx].ps,rax
    mov [rbx].ps,SetPrefixName( [rbx].ps, [rsi].asym.name, [rsi].asym.name_size )

    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )

        mov eax,[rsi].asym.name_size
        add eax,len
        sub eax,ofs
        inc eax
        mov rcx,[rbx].section
        add [rcx].cvsection.length,eax
    .endif

    ; for PROCs, scan parameters and locals.
    ; to mark the block's end, write an ENDBLK item.

    ; v2.10: no locals for -Zi0

    .if ( [rsi].asym.isproc && Options.debug_ext >= CVEX_REDUCED )

        ; scan local symbols again

        .for ( i = 0: i < 2 : i++ )

            .if ( MODULE.defOfssize == USE64 && i == 0 )
                .for ( j = 0, rcx = locals[0]: rcx: rsi = rcx, rcx = [rcx].asym.nextparam )
                    inc j
                .endf
            .endif
            mov ecx,i
            .for ( rdi = locals[rcx*asym_t] : rdi : rdi = [rdi].asym.nextparam )
                .if ( !( MODULE.defOfssize == USE64 && i == 0 ) )
                    mov rsi,rdi
                .endif
                ;
                ; FASTCALL register argument?
                ;
                .if ( [rsi].asym.state == SYM_TMACRO )

                    mov len,sizeof( REGSYM ) - 1
                    mov leaf,S_REGISTER
                    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                        mov len,sizeof( REGSYM_16t ) - 1
                        mov leaf,S_REGISTER_16t
                    .endif

                    mov edx,[rsi].asym.name_size
                    add edx,len
                    inc edx
                    mov rdx,[rbx].flushps(edx)

                    mov eax,[rsi].asym.name_size
                    add eax,len
                    lea eax,[rax-sizeof(uint_16)+1]
                    mov [rdx].REGSYM_16t.reclen,ax
                    mov [rdx].REGSYM_16t.rectyp,leaf

                    .if ( Options.debug_symbols == CV_SIGNATURE_C7 )

                        mov [rdx].REGSYM_16t.typind,[rsi].asym.ext_idx1
                        getregister( rsi )
                        mov rdx,[rbx].ps
                        mov [rdx].REGSYM_16t.reg,ax
                    .else
                        mov [rdx].REGSYM.typind,[rsi].asym.ext_idx1
                        getregister( rsi )
                        mov rdx,[rbx].ps
                        mov [rdx].REGSYM.reg,ax
                    .endif

                .elseif ( Ofssize == USE16 )

                    mov len,sizeof( BPRELSYM16 ) - 1
                    mov edx,[rsi].asym.name_size
                    add edx,len
                    inc edx
                    mov rdx,[rbx].flushps(edx)

                    mov eax,sizeof( BPRELSYM16 ) - sizeof(uint_16)
                    add eax,[rsi].asym.name_size
                    mov [rdx].BPRELSYM16.reclen,ax
                    mov [rdx].BPRELSYM16.rectyp,S_BPREL16
                    mov [rdx].BPRELSYM16.off,[rsi].asym.offs
                    mov [rdx].BPRELSYM16.typind,[rsi].asym.ext_idx1

                .else

                    ; v2.11: use S_REGREL if 64-bit or frame reg != [E|BP

                    mov rcx,pproc
                    movzx ecx,[rcx].proc_info.basereg

                    .if ( Ofssize == USE64 || ( GetRegNo( ecx ) != 5 ))

                        mov len,sizeof( REGREL32 ) - 1
                        mov leaf,S_REGREL32

                        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )

                            mov len,sizeof( REGREL32_16t ) - 1
                            mov leaf,S_REGREL32_16t
                        .endif

                        mov edx,[rsi].asym.name_size
                        add edx,len
                        inc edx
                        mov rdx,[rbx].flushps(edx)

                        mov eax,[rsi].asym.name_size
                        add eax,len
                        lea eax,[rax-sizeof(uint_16)+1]
                        mov [rdx].REGREL32_16t.reclen,ax
                        mov [rdx].REGREL32_16t.rectyp,leaf

                        ; x64 register numbers are different

                        mov rcx,pproc
                        movzx ecx,[rcx].proc_info.basereg
                        imul eax,ecx,special_item
                        lea rdx,SpecialTable
                        .if ( [rdx+rax].special_item.cpu == P_64 )
                            mov size,get_x64_regno( ecx )
                        .else
                            mov size,GetRegNo( ecx )
                            add size,CV_REG_EAX
                        .endif

                        mov rdx,[rbx].ps
                        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )

                            mov [rdx].REGREL32_16t.off,[rsi].asym.offs
                            mov [rdx].REGREL32_16t.typind,[rsi].asym.ext_idx1
                            mov [rdx].REGREL32_16t.reg,size
                        .else
                            mov [rdx].REGREL32.off,[rsi].asym.offs
                            mov [rdx].REGREL32.typind,[rsi].asym.ext_idx1
                            mov [rdx].REGREL32.reg,size
                        .endif

                    .else

                        mov len,sizeof( BPRELSYM32 ) - 1
                        mov leaf,S_BPREL32
                        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )
                            mov len,sizeof( BPRELSYM32_16t ) - 1
                            mov leaf,S_BPREL32_16t
                        .endif

                        mov edx,[rsi].asym.name_size
                        add edx,len
                        inc edx
                        mov rdx,[rbx].flushps(edx)

                        mov eax,[rsi].asym.name_size
                        add eax,len
                        lea eax,[rax-sizeof(uint_16)+1]
                        mov [rdx].BPRELSYM32_16t.reclen,ax
                        mov [rdx].BPRELSYM32_16t.rectyp,leaf

                        .if ( Options.debug_symbols == CV_SIGNATURE_C7 )

                            mov [rdx].BPRELSYM32_16t.off,[rsi].asym.offs
                            mov [rdx].BPRELSYM32_16t.typind,[rsi].asym.ext_idx1
                        .else
                            mov [rdx].BPRELSYM32.off,[rsi].asym.offs
                            mov [rdx].BPRELSYM32.typind,[rsi].asym.ext_idx1
                        .endif
                    .endif
                .endif

                mov [rsi].asym.ext_idx1,0 ; to be safe, clear the temp. used field
                mov eax,len
                add [rbx].ps,rax
                mov [rbx].ps,SetPrefixName( [rbx].ps, [rsi].asym.name, [rsi].asym.name_size )

                .if ( Options.debug_symbols == CV_SIGNATURE_C13 )

                    mov eax,[rsi].asym.name_size
                    add eax,len
                    inc eax
                    mov rcx,[rbx].section
                    add [rcx].cvsection.length,eax
                .endif

                .if ( MODULE.defOfssize == USE64 && i == 0 )
                    .for ( ecx = 1, j--, rsi = locals[0] : j > ecx : ecx++,
                           rsi = [rsi].asym.nextparam )
                    .endf
                .endif
            .endf
        .endf

        [rbx].flushps( sizeof( ENDARGSYM ) )
        mov [rax].ENDARGSYM.reclen,sizeof( ENDARGSYM ) - sizeof(uint_16)
        mov [rax].ENDARGSYM.rectyp,S_END
        add [rbx].ps,sizeof( ENDARGSYM )
        .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
            mov rcx,[rbx].section
            add [rcx].cvsection.length,sizeof( ENDARGSYM )
        .endif
    .endif
    ret

dbgcv::write_symbol endp


; flush section header and return memory address

dbgcv::flush_section proc __ccall uses rsi rdi rbx signature:dword, ex:dword

    ldr rbx,this
    mov rdi,[rbx].symbols
    mov rsi,[rbx].ps
    mov rcx,[rdi].asym.seginfo
    mov [rbx].ps,[rcx].seg_info.CodeBuffer
    sub rsi,rax
    mov eax,ex
    lea rcx,[rsi+rax+sizeof(qditem)+sizeof(cvsection)]
    mov rdi,LclAlloc( ecx )

    mov [rdi].qditem.next,NULL
    lea rax,[rsi+sizeof(cvsection)]
    add eax,ex
    mov [rdi].qditem.size,eax
    lea rcx,[rdi+rsi+sizeof(qditem)]
    mov [rbx].section,rcx
    mov [rcx].cvsection.signature,signature
    mov [rcx].cvsection.length,ex

    .if ( esi )

        mov ecx,esi
        lea rdx,[rdi+sizeof(qditem)]
        mov rax,[rbx].ps
        xchg rsi,rax
        xchg rdi,rdx
        rep movsb
        mov rdi,rdx
        mov rsi,rax
    .endif

    mov rdx,[rbx].param
    lea rcx,[rdx].coffmod.SymDeb[dbg_section]
    mov rdx,[rcx].dbg_section.s

    .if rdx != [rbx].symbols
        sub rcx,sizeof( dbg_section )
    .endif
    .if ( [rcx].dbg_section.q.head == NULL )
        mov [rcx].dbg_section.q.head,rdi
        mov [rcx].dbg_section.q.tail,rdi
    .else
        mov rdx,[rcx].dbg_section.q.tail
        mov [rdx].qditem.next,rdi
        mov [rcx].dbg_section.q.tail,rdi
    .endif

    mov rdx,[rbx].symbols
    mov rcx,[rdx].asym.seginfo
    mov eax,[rcx].seg_info.start_loc
    lea rax,[rsi+rax+sizeof(cvsection)]
    add eax,ex
    mov [rcx].seg_info.current_loc,eax
    mov [rcx].seg_info.start_loc,eax
    mov rax,[rbx].section
    ret

dbgcv::flush_section endp

    assume rbx:nothing


ifdef USEMD5

.template MD5_CTX
    state   dd 4 dup(?)     ; state (ABCD)
    count   dd 2 dup(?)     ; number of bits, modulo 2^64 (lsb first)
    buffer  db 64 dup(?)    ; input buffer
    digest  dq 16 dup(?)    ; added: used in MD5Final(ntdll.dll)
   .ends

define MD5BUFSIZ 1024*4
define MD5_LENGTH ( sizeof( uint_32 ) + sizeof( uint_16 ) + 16 + sizeof( uint_16 ) )

ifdef _WIN64
define __icall <fastcall>
else
define __icall <watcall>
endif

; inline basic MD5 functions

F proto __icall x:dword, y:dword, z:abs { ; (((x) & (y)) | ((~x) & (z)))
    xor y,z
    and x,y
    xor x,z
    }

G proto __icall x:dword, y:dword, z:abs { ; (((x) & (z)) | ((y) & (~z)))
    xor x,y
    and x,z
    xor x,y
    }

H proto __icall x:dword, y:dword, z:abs { ; ((x) ^ (y) ^ (z))
    xor x,y
    xor x,z
    }

I proto __icall x:dword, y:dword, z:abs { ; ((y) ^ ((x) | (~z)))
    not z
    or  x,z
    not z
    xor x,y
    }

; rotates x left n bits

ROTATE_LEFT macro x, n ; (((x) << (n)) | ((x) >> (32-(n))))
    if n le 16
     rol x,n
    else
     ror x,32-n
    endif
    exitm<>
    endm

; transformations for rounds 1, 2, 3, and 4

FF macro f, w, x, y, z, i, ac, s, r
    add w,[r+i*4]
ifdef _WIN64
    f(x, y, z)
    add w,ecx
    add w,ac
else
    lea w,[w+f(x, y, z)+ac]
endif
    ROTATE_LEFT(w, s)
    add w,x
    exitm<>
    endm

; MD5 basic transformation. Transforms state based on block.

MD5_TRANSFORM macro a, b, c, d, r ; register arguments used

    push rcx
    mov  r,rdx
    mov  b,[rcx+0x04]
    mov  c,[rcx+0x08]
    mov  d,[rcx+0x0C]
    mov  a,[rcx+0x00]

    ; Round 1

    FF( F, a, b, c, d,  0, 0xd76aa478,  7, r )
    FF( F, d, a, b, c,  1, 0xe8c7b756, 12, r )
    FF( F, c, d, a, b,  2, 0x242070db, 17, r )
    FF( F, b, c, d, a,  3, 0xc1bdceee, 22, r )
    FF( F, a, b, c, d,  4, 0xf57c0faf,  7, r )
    FF( F, d, a, b, c,  5, 0x4787c62a, 12, r )
    FF( F, c, d, a, b,  6, 0xa8304613, 17, r )
    FF( F, b, c, d, a,  7, 0xfd469501, 22, r )
    FF( F, a, b, c, d,  8, 0x698098d8,  7, r )
    FF( F, d, a, b, c,  9, 0x8b44f7af, 12, r )
    FF( F, c, d, a, b, 10, 0xffff5bb1, 17, r )
    FF( F, b, c, d, a, 11, 0x895cd7be, 22, r )
    FF( F, a, b, c, d, 12, 0x6b901122,  7, r )
    FF( F, d, a, b, c, 13, 0xfd987193, 12, r )
    FF( F, c, d, a, b, 14, 0xa679438e, 17, r )
    FF( F, b, c, d, a, 15, 0x49b40821, 22, r )

    ; Round 2

    FF( G, a, b, c, d,  1, 0xf61e2562,  5, r )
    FF( G, d, a, b, c,  6, 0xc040b340,  9, r )
    FF( G, c, d, a, b, 11, 0x265e5a51, 14, r )
    FF( G, b, c, d, a,  0, 0xe9b6c7aa, 20, r )
    FF( G, a, b, c, d,  5, 0xd62f105d,  5, r )
    FF( G, d, a, b, c, 10, 0x02441453,  9, r )
    FF( G, c, d, a, b, 15, 0xd8a1e681, 14, r )
    FF( G, b, c, d, a,  4, 0xe7d3fbc8, 20, r )
    FF( G, a, b, c, d,  9, 0x21e1cde6,  5, r )
    FF( G, d, a, b, c, 14, 0xc33707d6,  9, r )
    FF( G, c, d, a, b,  3, 0xf4d50d87, 14, r )
    FF( G, b, c, d, a,  8, 0x455a14ed, 20, r )
    FF( G, a, b, c, d, 13, 0xa9e3e905,  5, r )
    FF( G, d, a, b, c,  2, 0xfcefa3f8,  9, r )
    FF( G, c, d, a, b,  7, 0x676f02d9, 14, r )
    FF( G, b, c, d, a, 12, 0x8d2a4c8a, 20, r )

    ; Round 3

    FF( H, a, b, c, d,  5, 0xfffa3942,  4, r )
    FF( H, d, a, b, c,  8, 0x8771f681, 11, r )
    FF( H, c, d, a, b, 11, 0x6d9d6122, 16, r )
    FF( H, b, c, d, a, 14, 0xfde5380c, 23, r )
    FF( H, a, b, c, d,  1, 0xa4beea44,  4, r )
    FF( H, d, a, b, c,  4, 0x4bdecfa9, 11, r )
    FF( H, c, d, a, b,  7, 0xf6bb4b60, 16, r )
    FF( H, b, c, d, a, 10, 0xbebfbc70, 23, r )
    FF( H, a, b, c, d, 13, 0x289b7ec6,  4, r )
    FF( H, d, a, b, c,  0, 0xeaa127fa, 11, r )
    FF( H, c, d, a, b,  3, 0xd4ef3085, 16, r )
    FF( H, b, c, d, a,  6, 0x04881d05, 23, r )
    FF( H, a, b, c, d,  9, 0xd9d4d039,  4, r )
    FF( H, d, a, b, c, 12, 0xe6db99e5, 11, r )
    FF( H, c, d, a, b, 15, 0x1fa27cf8, 16, r )
    FF( H, b, c, d, a,  2, 0xc4ac5665, 23, r )

    ; Round 4

    FF( I, a, b, c, d,  0, 0xf4292244,  6, r )
    FF( I, d, a, b, c,  7, 0x432aff97, 10, r )
    FF( I, c, d, a, b, 14, 0xab9423a7, 15, r )
    FF( I, b, c, d, a,  5, 0xfc93a039, 21, r )
    FF( I, a, b, c, d, 12, 0x655b59c3,  6, r )
    FF( I, d, a, b, c,  3, 0x8f0ccc92, 10, r )
    FF( I, c, d, a, b, 10, 0xffeff47d, 15, r )
    FF( I, b, c, d, a,  1, 0x85845dd1, 21, r )
    FF( I, a, b, c, d,  8, 0x6fa87e4f,  6, r )
    FF( I, d, a, b, c, 15, 0xfe2ce6e0, 10, r )
    FF( I, c, d, a, b,  6, 0xa3014314, 15, r )
    FF( I, b, c, d, a, 13, 0x4e0811a1, 21, r )
    FF( I, a, b, c, d,  4, 0xf7537e82,  6, r )
    FF( I, d, a, b, c, 11, 0xbd3af235, 10, r )
    FF( I, c, d, a, b,  2, 0x2ad7d2bb, 15, r )
    FF( I, b, c, d, a,  9, 0xeb86d391, 21, r )

    pop rdx
    add [rdx+0x00],a
    add [rdx+0x04],b
    add [rdx+0x08],c
    add [rdx+0x0C],d

    endm

ifdef _WIN64

MD5Transform proc fastcall buf:ptr dword, inp:ptr byte

    MD5_TRANSFORM eax, r8d, r9d, r10d, r11

else

MD5Transform proc fastcall uses esi edi ebx ebp buf:ptr dword, inp:ptr byte

    MD5_TRANSFORM ecx, edi, ebx, ebp, esi

endif
    ret

MD5Transform endp


    assume rbx:ptr MD5_CTX

MD5Update proc fastcall uses rsi rdi rbx ctx:ptr MD5_CTX, buf:ptr byte, len:dword

    mov rbx,rcx
    mov rsi,rdx
    mov edi,len

    mov ecx,[rbx].count[0]
    mov eax,edi
    shl eax,3
    add [rbx].count[0],eax
    adc [rbx].count[4],0

    mov eax,edi
    shr eax,29
    add [rbx].count[4],eax

    mov eax,ecx
    shr eax,3
    and eax,0x3f

    .ifnz

        lea rdi,[rbx].buffer[rax]
        mov ecx,64
        sub ecx,eax
        mov eax,ecx

        .if ( len < ecx )

            mov ecx,len
            rep movsb
           .return
        .endif
        rep movsb
        mov edi,len
        sub edi,eax

        MD5Transform( &[rbx].state, &[rbx].buffer )
    .endif

    .while ( edi >= 64 )

        lea  rdx,[rbx].buffer
        xchg rdx,rdi
        mov  ecx,64
        rep  movsb
        mov  edi,edx

        MD5Transform( &[rbx].state, &[rbx].buffer )
        sub edi,64
    .endw

    mov ecx,edi
    lea rdi,[rbx].buffer
    rep movsb
    ret

MD5Update endp


; MD5 finalization. Ends an MD5 message-digest operation, writing the
; the message digest and zeroizing the context.

MD5Final proc fastcall uses rsi rdi rbx ctx:ptr MD5_CTX

    mov rbx,rcx
    mov ecx,[rbx].count
    shr ecx,3
    and ecx,0x3F
    lea rsi,[rbx].buffer
    lea rdi,[rsi+rcx]
    mov al,0x80
    stosb
    mov eax,64 - 1
    sub eax,ecx
    mov ecx,eax
    xor eax,eax

    .if ( ecx < 8 )

        rep stosb

        MD5Transform( &[rbx].state, rsi )

        mov rdi,rsi
        mov ecx,56
        xor eax,eax
        rep stosb
    .else

        sub ecx,8
        rep stosb
    .endif

    mov [rsi+14*4],[rbx].count
    mov [rsi+15*4],[rbx].count[4]

    MD5Transform( &[rbx].state, rsi )

    lea rsi,[rbx].state
    lea rdi,[rbx].digest
    mov ecx,16/4
    rep movsd
    ret

MD5Final endp

    assume rbx:nothing

calc_md5 proc __ccall uses rsi rdi rbx filename:string_t, sum:ptr byte

   .new ctx:MD5_CTX
   .new fp:ptr FILE = fopen( filename, "rb" )
   .return .if ( rax == NULL )

    mov rbx,MemAlloc( MD5BUFSIZ )

    mov ctx.state[0x00],0x67452301
    mov ctx.state[0x04],0xefcdab89
    mov ctx.state[0x08],0x98badcfe
    mov ctx.state[0x0C],0x10325476
    mov ctx.count[0x00],0
    mov ctx.count[0x04],0

    .while 1

       .break .if !fread( rbx, 1, MD5BUFSIZ, fp )

        MD5Update( &ctx, rbx, eax )
    .endw

    fclose( fp )
    MD5Final( &ctx )
    MemFree( rbx )

    mov rdi,sum
    lea rsi,ctx.digest
    mov ecx,16/4
    rep movsd
   .return( true )

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

; option -Zi: write debug symbols and types
; - symbols: segment $$SYMBOLS (OMF) or .debug$S (COFF)
; - types:   segment $$TYPES (OMF) or .debug$T (COFF)
; field Options.debug_symbols contains the format version
; which is to be generated (CV4_, CV5_ or CV8_SIGNATURE)

    option proc:public

cv_write_debug_tables proc __ccall uses rsi rdi rbx symbols:asym_t, types:asym_t, pv:ptr

  local i:int_t
  local len:int_t
  local objname:string_t
  local cv:dbgcv
  local lineTable:int_t

    mov cv.lpVtbl,&vtable
    ldr rsi,symbols
    mov cv.symbols,rsi
    mov rcx,[rsi].asym.seginfo
    mov rsi,[rcx].seg_info.CodeBuffer
    mov rdi,types
    mov cv.types,rdi
    mov rcx,[rdi].asym.seginfo
    mov rdi,[rcx].seg_info.CodeBuffer

    mov cv.currtype,0x1000          ; user-defined types start at 0x1000
    mov cv.level,0
    mov cv.param,pv
    movzx eax,Options.debug_symbols ; "signature"
    stosd                           ; init types
    mov cv.pt,rdi
    mov [rsi],eax                   ; init symbols
    add rsi,sizeof(uint_32)
    mov cv.ps,rsi

    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )

        imul ecx,MODULE.cnt_fnames,sizeof( cvfile )
        mov cv.files,LclAlloc( ecx )

        .for ( rdi = rax,
               eax = 0,
               rsi = MODULE.FNames,
               ebx = MODULE.cnt_fnames : ebx : ebx-- )

           .movsd
            stosd
        .endf

        mov rdi,LclAlloc( _MAX_PATH * 4 )
        _getcwd( rdi, _MAX_PATH * 4 )

       .new cwdsize:dword = tstrlen( rdi )
        add rax,rdi
        mov objname,rax
        mov cv.currdir,rdi

        ;
        ; source filename string table
        ;

        mov rbx,cv.flush_section( 0x000000F3, 0 )
        inc [rbx].cvsection.length
        mov rdi,cv.ps
        mov byte ptr [rdi],0
        inc cv.ps

        ;
        ; for each source file
        ;

        .for ( rdi = cv.files, i = 0 : i < MODULE.cnt_fnames : i++, rdi += cvfile )

            mov [rdi].cvfile.offs,[rbx].cvsection.length
            mov rsi,[rdi].cvfile.name

            mov eax,[rsi]
            .if ( al != '\' && al != '.' && ah != ':' )

                tstrcpy( objname, "\\" )
                tstrcat( objname, rsi )
                mov rsi,cv.currdir
            .endif

            inc tstrlen( rsi )
            mov len,eax
            cv.flushps( eax )
            xchg rdi,rax

            mov ecx,len
            add cv.ps,rcx
            add [rbx].cvsection.length,ecx
            rep movsb
            mov rdi,rax
        .endf

        mov rcx,objname
        mov byte ptr [rcx],0
        cv.alignps()

        ;; $$000000 to line table

        mov eax,[rbx].cvsection.length
        add eax,3
        and eax,not 3
        add eax,cvsection
        mov lineTable,eax

        ;; source file info

        mov rbx,cv.flush_section( 0x000000F4, 0 )

        .for ( rsi = cv.files, i = 0: i < MODULE.cnt_fnames: i++, rsi += cvfile )

            mov rdi,cv.flushps( MD5_LENGTH )
            mov eax,[rsi].cvfile.offs
            stosd
            mov [rsi].cvfile.offs,[rbx].cvsection.length
ifdef USEMD5
            mov eax,0x0110
            stosw
            calc_md5( [rsi].cvfile.name, rdi )
            add rdi,16
            xor eax,eax
            stosw
else
            xor eax,eax
            stosd
endif
            add [rbx].cvsection.length,MD5_LENGTH
            mov cv.ps,rdi
        .endf

        mov eax,[rbx].cvsection.length
        add eax,3
        and eax,not 3
        add eax,cvsection + 12
        add lineTable,eax

        mov rcx,CV8Label ; added v2.33.56
        xor eax,eax
        .if ( rcx )
            mov rcx,[rcx].asym.segm
            mov rcx,[rcx].asym.seginfo
            mov eax,[rcx].seg_info.bytes_written
        .endif
        .if ( eax )

           .new data:dword = 0
            mov rcx,CreateFixup( CV8Label, FIX_OFF32_SECREL, OPTJ_NONE )
            mov [rcx].fixup.locofs,lineTable
            store_fixup( rcx, cv.symbols, &data )
            mov rcx,CreateFixup( CV8Label, FIX_SEG, OPTJ_NONE )
            mov eax,lineTable
            add eax,4
            mov [rcx].fixup.locofs,eax
            store_fixup( rcx, cv.symbols, &data )
        .endif

        ;; line numbers for section

        mov cv.section,NULL

        .for ( rsi = SegTable: rsi: rsi = [rsi].asym.next )

            mov rbx,[rsi].asym.seginfo

            .if ( [rbx].seg_info.LinnumQueue )

               .new Header:ptr CV_DebugSLinesHeader_t
               .new File:ptr CV_DebugSLinesFileBlockHeader_t
               .new Queue:ptr line_num_info

                .if ( cv.section )
                    cv.alignps()
                .endif

                mov rdi,cv.flush_section( 0x000000F2,
                    sizeof( CV_DebugSLinesHeader_t ) + sizeof( CV_DebugSLinesFileBlockHeader_t ) )

                add rdi,sizeof( cvsection )
                mov Header,rdi
                mov [rdi].CV_DebugSLinesHeader_t.offCon,0
                mov [rdi].CV_DebugSLinesHeader_t.segCon,0
                mov [rdi].CV_DebugSLinesHeader_t.flags,0
                mov [rdi].CV_DebugSLinesHeader_t.cbCon,[rsi].asym.max_offset

                add rdi,sizeof( CV_DebugSLinesHeader_t )
                mov File,rdi
                mov [rdi].CV_DebugSLinesFileBlockHeader_t.offFile,0
                mov [rdi].CV_DebugSLinesFileBlockHeader_t.nLines,0
                mov [rdi].CV_DebugSLinesFileBlockHeader_t.cbBlock,0

                mov rbx,[rbx].seg_info.LinnumQueue
                mov rbx,[rbx].qdesc.head

                assume rbx:ptr line_num_info

                .while ( rbx )

                   .new Line:ptr CV_Line_t
                   .new Prev:ptr CV_Line_t
                   .new fileStart:int_t

                    mov eax,[rbx].srcfile
                    .if ( [rbx].number == 0 )
                        mov eax,[rbx].line_number
                        shr eax,20
                    .endif
                    mov fileStart,eax

                    mov rcx,File
                    mov [rcx].CV_DebugSLinesFileBlockHeader_t.cbBlock,12
                    mov rdx,cv.files
                    imul eax,eax,cvfile
                    mov [rcx].CV_DebugSLinesFileBlockHeader_t.offFile,[rdx+rax].cvfile.offs
                    mov Prev,NULL

                    .for ( : rbx : rbx = [rbx].next )

                        .new fileCur:int_t
                        .new linenum:int_t
                        .new offs:int_t

                        .if ( [rbx].number == 0 )
                            mov eax,[rbx].line_number
                            shr eax,20
                            mov ecx,[rbx].line_number
                            mov rdx,[rbx].sym
                            mov edx,[rdx].asym.offs
                        .else
                            mov eax,[rbx].srcfile
                            mov ecx,[rbx].number
                            mov edx,[rbx].line_number
                        .endif
                        .if ( fileStart != eax )

                            mov File,cv.flushps( sizeof( CV_DebugSLinesFileBlockHeader_t ) )
                            xor edx,edx
                            mov ecx,sizeof( CV_DebugSLinesFileBlockHeader_t )
                            add cv.ps,rcx
                            mov [rax].CV_DebugSLinesFileBlockHeader_t.offFile,edx
                            mov [rax].CV_DebugSLinesFileBlockHeader_t.nLines,edx
                            mov [rax].CV_DebugSLinesFileBlockHeader_t.cbBlock,edx
                            mov rax,Header
                            add [rax-4],ecx
                           .break
                        .endif

                        mov fileCur,eax
                        mov linenum,ecx
                        mov offs,edx

                        mov rcx,Prev
                        .if ( rcx )
                            mov eax,[rcx].CV_Line_t.flags.linenumStart
                            .if ( edx < [rcx].CV_Line_t.offs || edx == [rcx].CV_Line_t.offs && eax == linenum )
                                .continue
                            .endif
                        .endif

                        mov Line,cv.flushps( sizeof( CV_Line_t ) )
                        add cv.ps,sizeof( CV_Line_t )
                        mov rcx,cv.section
                        add [rcx].cvsection.length,sizeof( CV_Line_t )

                        mov rcx,File
                        inc [rcx].CV_DebugSLinesFileBlockHeader_t.nLines
                        add [rcx].CV_DebugSLinesFileBlockHeader_t.cbBlock,8

                        mov rcx,Line
                        mov [rcx].CV_Line_t.offs,offs
                        mov [rcx].CV_Line_t.flags,linenum
                        mov [rcx].CV_Line_t.flags.fStatement,1
                        mov Prev,rcx
                    .endf
                .endw
                assume rbx:nothing
            .endif
        .endf
        .if ( cv.section )
            cv.alignps()
        .endif

        ;; symbol information

        cv.flush_section( 0x000000F1, 0 )
        mov rsi,cv.ps
        .new start:ptr = rsi

        ;; Name of object file

        mov rdi,CurrFName[OBJ*string_t]
        mov eax,[rdi]
        .if ( al != '\' && al != '.' && ah != ':' )

            tstrcpy( objname, "\\" )
            tstrcat( objname, rdi )
            mov rdi,cv.currdir
       .endif
        mov len,tstrlen( rdi )
        add eax,sizeof( OBJNAMESYM ) - sizeof( word )
        mov [rsi].OBJNAMESYM.reclen,ax
        mov [rsi].OBJNAMESYM.rectyp,S_OBJNAME
        mov [rsi].OBJNAMESYM.signature,0
        add cv.ps,sizeof( OBJNAMESYM ) - 1
        mov cv.ps,SetPrefixName( cv.ps, rdi, len )
        mov rcx,objname
        mov byte ptr [rcx],0

        ;; compile flags

        mov rdi,cv.ps
        mov [rdi].COMPILESYM3.rectyp,S_COMPILE3
        tstrcpy( &[rdi].COMPILESYM3.verSz, szCVCompiler )
        mov [rdi].COMPILESYM3.reclen,sizeof(COMPILESYM3) + sizeof(@CStr(0)) - 2
        add cv.ps,sizeof(COMPILESYM3) + sizeof(@CStr(0))

        mov rdx,cv.ps
        mov byte ptr [rdx-1],0

        mov [rdi].COMPILESYM3.flags,CV_CFL_MASM
        mov eax,MODULE.curr_cpu
        and eax,P_CPU_MASK
        shr eax,4
        .if ( MODULE.Ofssize == USE64 )
            mov eax,CV_CFL_X64
        .endif
        mov [rdi].COMPILESYM3.machine,     ax
        mov [rdi].COMPILESYM3.verFEMajor,  0
        mov [rdi].COMPILESYM3.verFEMinor,  0
        mov [rdi].COMPILESYM3.verFEBuild,  0
        mov [rdi].COMPILESYM3.verFEQFE,    0
        mov [rdi].COMPILESYM3.verMajor,    ASMC_MAJOR
        mov [rdi].COMPILESYM3.verMinor,    ASMC_MINOR
        mov [rdi].COMPILESYM3.verBuild,    0
        mov [rdi].COMPILESYM3.verQFE,      0

        mov rdi,cv.ps
        mov [rdi].ENVBLOCKSYM.flags,0
        mov [rdi].ENVBLOCKSYM.rectyp,S_ENVBLOCK
        lea rdi,[rdi].ENVBLOCKSYM.rgsz

        ;; pairs of 0-terminated strings - keys/values
        ;;
        ;; cwd - current working directory
        ;; exe - full path of executable
        ;; src - relative path to source (from cwd)

        mov     rsi,cv.currdir
        mov     ebx,cwdsize
        mov     eax,"dwc"
        stosd
        lea     ecx,[rbx+1]
        rep     movsb
        mov     eax,"exe"
        stosd
        mov     rsi,_pgmptr
        inc     tstrlen( rsi )
        mov     ecx,eax
        rep     movsb
        mov     eax,"crs"
        stosd
        mov     rdx,cv.files
        mov     rsi,[rdx].cvfile.name

        .ifd ( tmemicmp( rsi, cv.currdir, ebx ) == 0 )
            lea rsi,[rsi+rbx+1]
        .endif

        inc     tstrlen( rsi )
        mov     ecx,eax
        rep     movsb
        xor     eax,eax
        stosb
        mov     rax,rdi
        mov     rdx,cv.ps
        sub     rax,rdx
        sub     rax,2
        mov     [rdx].ENVBLOCKSYM.reclen,ax
        mov     cv.ps,rdi

        ;
        ; length needs to be added for each symbol
        ;

        mov rbx,cv.section
        sub rdi,start
        add [rbx].cvsection.length,edi

        ; v2.36.18 - recurse typedefs in structure
        ;
        ; asym struct
        ; type ptr asym ? ; char ** --> asym *
        ;
        ; This scans struct fields for undefined types
        ;
        xor esi,esi
        .while SymEnum( rsi, &i )
            mov rsi,rax
            .ifd ( sym_type( rax ) == SYM_SIMPLE )
                cv.write_type( rsi )
            .endif
        .endw
        xor esi,esi
        .while SymEnum( rsi, &i )
            mov rsi,rax
            .ifd ( sym_type( rax ) == SYM_SIMPLE )
                cv.write_type( rsi )
            .elseif ( eax == SYM_FWDREF )
                mov rdi,rdx
                .ifd ( sym_type( rdx ) == SYM_SIMPLE )
                    cv.write_type( rdi )
                    sym_type( rsi )
                .endif
                .if ( eax != SYM_SIMPLE )
                    mov [rsi].asym.fwdref,1
                .endif
                cv.write_type( rsi )
            .endif
        .endw

    .else

        ;; 1. symbol record: object name

        mov rsi,CurrFName[OBJ*string_t]
        .for ( rbx = tstrlen( rsi ) : ebx : ebx-- )
            mov al,[rsi+rbx-1]
            .if ( al == '/' || al == '\' )
                .break
            .endif
        .endf
        add rsi,rbx
        mov ecx,tstrlen( rsi )
        mov rdi,cv.ps
        add eax,sizeof( OBJNAMESYM ) - sizeof(uint_16)
        mov [rdi].OBJNAMESYM.reclen,ax
        mov [rdi].OBJNAMESYM.rectyp,S_OBJNAME_ST
        mov [rdi].OBJNAMESYM.signature,1
        add rdi,sizeof( OBJNAMESYM ) - 1
        mov rdi,SetPrefixName( rdi, rsi, ecx )

        ;; 2. symbol record: compiler

        mov ebx,tstrlen( szCVCompiler )
        add eax,sizeof( CFLAGSYM ) - sizeof(uint_16)
        mov [rdi].CFLAGSYM.reclen,ax
        mov [rdi].CFLAGSYM.rectyp,S_COMPILE

        ;; v2.11: use a valid 64-bit value

        mov eax,CV_CFL_X64
        .if ( MODULE.defOfssize != USE64 )
             mov eax,MODULE.curr_cpu
             and eax,P_CPU_MASK
             shr eax,4
        .endif

        ;; 0 isnt possible, 1 is 8086 and 80186

        .if ( al == 0 )
            mov al,CV_CFL_8086
        .endif
        mov [rdi].CFLAGSYM.machine,al
        mov [rdi].CFLAGSYM.language,CV_CFL_MASM
        mov [rdi].CFLAGSYM.flags,0

        mov cl,MODULE._model
        .if ( cl )
            mov edx,1
            shl edx,cl
            .if ( cl == MODEL_HUGE )
                or [rdi].CFLAGSYM.flags,CV_AMB_HUGE shr 5
            .else
                mov eax,CV_AMB_NEAR
                .if edx & SIZE_DATAPTR
                    mov eax,CV_AMB_FAR
                .endif
                shl eax,5
                or [rdi].CFLAGSYM.flags,ax
            .endif
            mov eax,CV_AMB_NEAR
            .if edx & SIZE_CODEPTR
                mov eax,CV_AMB_FAR
            .endif
            shl eax,8
            or [rdi].CFLAGSYM.flags,ax
        .endif
        add rdi,sizeof( CFLAGSYM ) - 1
        mov cv.ps,SetPrefixName( rdi, szCVCompiler, ebx )
    .endif

    ;; scan symbol table for types

    xor esi,esi
    .while ( SymEnum( rsi, &i ) )
        mov rsi,rax
        .if ( [rsi].asym.state == SYM_TYPE &&
              [rsi].asym.typekind != TYPE_TYPEDEF && [rsi].asym.cvtyperef == 0 )
            cv.write_type( rsi )
        .endif
    .endw

    .if ( Options.debug_symbols == CV_SIGNATURE_C13 )
        xor esi,esi
        .while ( SymEnum( rsi, &i ) )
            mov rsi,rax
            .if ( [rsi].asym.state == SYM_TYPE &&
                  [rsi].asym.typekind != TYPE_TYPEDEF && [rsi].asym.cvtyperef && [rsi].asym.fwdref )
                cv.write_type( rsi )
            .endif
        .endw
    .endif

    ;; scan symbol table for SYM_TYPE, SYM_INTERNAL

    xor esi,esi
    .while ( SymEnum( rsi, &i ) )
        mov rsi,rax
        .switch ( [rsi].asym.state )
        .case SYM_TYPE
            ;; may create an S_UDT entry in the symbols table
            ;; v2.10: no UDTs for -Zi0 and -Zi1
            .break .if ( Options.debug_ext < CVEX_NORMAL )
        .case SYM_INTERNAL
            mov edx,[rsi].asym.predefined
if EQUATESYMS
            ;; emit constants if -Zi3
            mov ecx,[rsi].asym.isequate
            mov eax,[rsi].asym.isvariable
            .if ( Options.debug_ext < CVEX_MAX )
                mov eax,ecx
            .endif
else
            mov eax,[rsi].asym.isequate
endif
            .if ( ( Options.debug_symbols == CV_SIGNATURE_C13 && rsi == CV8Label ) || eax || edx ) ;; EQUates?
                .endc
            .endif
            cv.write_symbol( rsi )
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

    mov rdi,types
    mov rdx,[rdi].asym.seginfo
    mov eax,[rdx].seg_info.current_loc
    mov [rdi].asym.max_offset,eax
    mov [rdx].seg_info.start_loc,0 ; required for COFF
    mov rdi,symbols
    mov rdx,[rdi].asym.seginfo
    mov eax,[rdx].seg_info.current_loc
    mov [rdi].asym.max_offset,eax
    mov [rdx].seg_info.start_loc,0 ; required for COFF
    ret

cv_write_debug_tables endp

    end
