; SYMBOLS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

include asmc.inc
include memalloc.inc
include proc.inc
include macro.inc
include extern.inc
include fastpass.inc
include input.inc
include segment.inc

public SymCmpFunc
public strFUNC
public strFILE
public szDate
public szTime

externdef FileCur   :asym_t ; @FileCur symbol
externdef LineCur   :asym_t ; @Line symbol
externdef symCurSeg :asym_t ; @CurSeg symbol

GHASH_TABLE_SIZE    equ 0x8000
LHASH_TABLE_SIZE    equ 0x1000

USESTRFTIME         equ 0   ; 1=use strftime()

symptr_t            typedef ptr asym_t
tmitem              struct
name                string_t ?
value               string_t ?
store               symptr_t ?
tmitem              ends

eqitem              struct
name                string_t ?
value               string_t ?
sfunc_ptr           proc fastcall :asym_t, :ptr
store               symptr_t ?
eqitem              ends

define _MAX_DYNEQ 64

.data?
szDate              char_t 16 dup(?)    ; value of @Date symbol
szTime              char_t 16 dup(?)    ; value of @Time symbol
gsym_table          asym_t GHASH_TABLE_SIZE dup(?)
lsym_table          asym_t LHASH_TABLE_SIZE+1 dup(?)
lsym                symptr_t ?          ; asym ** pointer into local hash table
SymCmpFunc          StrCmpFunc ?
dyneqtable          string_t _MAX_DYNEQ dup(?)
dyneqvalue          string_t _MAX_DYNEQ dup(?)
SymCount            uint_t ?            ; Number of symbols in global table
strFILE             char_t 1024 dup(?)  ; value of __FILE__ symbol
strFUNC             char_t 256 dup(?)   ; value of __func__ symbol

.data
symPC asym_t 0  ; the $ symbol

; table of predefined text macros

tmtab label tmitem

    ; @Version contains the Masm compatible version
    ; v2.06: value of @Version changed to 800

    tmitem  <@CStr("@Version"),  @CStr("1000"), 0>
    tmitem  <@CStr("@Date"),     szDate,    0>
    tmitem  <@CStr("@Time"),     szTime,    0>
    tmitem  <@CStr("@FileName"), ModuleInfo.name, 0>
    tmitem  <@CStr("@FileCur"),  0, FileCur>

    ; added 2.33.58

    tmitem  <@CStr("__FILE__"),  strFILE, 0>
    tmitem  <@CStr("__LINE__"),  @CStr("@Line"), 0>
    tmitem  <@CStr("__func__"),  strFUNC, 0>

    ; v2.09: @CurSeg value is never set if no segment is ever opened.
    ; this may have caused an access error if a listing was written.

    tmitem  <@CStr("@CurSeg"), @CStr(""), symCurSeg>
    string_t NULL

; table of predefined numeric equates

eqtab LABEL eqitem
    eqitem  < @CStr("__ASMC__"), _ASMC_VER, 0, 0 >
ifdef ASMC64
    eqitem  < @CStr("__ASMC64__"), _ASMC_VER, 0, 0 >
endif
    eqitem  < @CStr("__JWASM__"),  212, 0, 0 >

    eqitem  < @CStr("$"),          0, UpdateCurPC, symPC >
    eqitem  < @CStr("@Line"),      0, UpdateLineNumber, LineCur >
    eqitem  < @CStr("@WordSize"),  0, UpdateWordSize, 0 > ; must be last (see SymInit())

    string_t NULL

dyneqcount int_t 0

    .code

FindDefinedName proc fastcall private uses rsi rdi rbx name:string_t
    .for ( rbx = rcx, rsi = &dyneqtable, edi = 0 : edi < dyneqcount : edi++, rsi+=string_t )
        .ifd !tstrcmp( rbx, [rsi] )
            inc edi
           .return( edi )
        .endif
    .endf
    .return 0
    endp


define_name proc __ccall name:string_t, value:string_t
    .ifd !FindDefinedName( ldr(name) )
        mov ecx,dyneqcount
        lea rdx,dyneqtable
        mov rax,name
        mov [rdx+rcx*string_t],rax
        lea rdx,dyneqvalue
        mov rax,value
        mov [rdx+rcx*string_t],rax
        inc dyneqcount
    .endif
    ret
    endp


undef_name proc __ccall name:string_t
    .ifd FindDefinedName( ldr(name) )
        .for ( ecx = eax : ecx < dyneqcount : ecx++ )
            lea rdx,dyneqtable
            mov rax,[rdx+rcx*string_t]
            mov [rdx+rcx*string_t-string_t],rax
            lea rdx,dyneqvalue
            mov rax,[rdx+rcx*string_t]
            mov [rdx+rcx*string_t-string_t],rax
        .endf
        dec dyneqcount
    .endif
    ret
    endp


SymSetCmpFunc proc __ccall
    lea rax,tmemicmp
    .if ( MODULE.case_sensitive )
        lea rax,tmemcmp
    .endif
    mov SymCmpFunc,rax
    ret
    endp


; reset local hash table

SymClearLocal proc __ccall
    xor  eax,eax
    lea  rdx,lsym_table
    mov  ecx,sizeof(lsym_table) / 4
    xchg rdx,rdi
    rep  stosd
    mov  rdi,rdx
    ret
    endp

; store local hash table in proc's list of local symbols

SymGetLocal proc __ccall uses rbx psym:asym_t
    ldr rcx,psym
    mov rdx,[rcx].asym.procinfo
    lea rdx,[rdx].proc_info.labellist
    xor ecx,ecx
    lea rbx,lsym_table
    .while ecx < LHASH_TABLE_SIZE
        mov rax,[rbx+rcx*asym_t]
        inc ecx
        .continue .if !rax
        mov [rdx],rax
        lea rdx,[rax].asym.nextll
    .endw
    xor eax,eax
    mov [rdx],rax
    ret
    endp


; restore local hash table.
; - proc: procedure which will become active.
; fixme: It might be necessary to reset the "defined" flag
; for local labels (not for params and locals!). Low priority!

SymSetLocal proc __ccall uses rsi rdi psym:asym_t

    ldr rsi,psym
    xor eax,eax
    lea rdx,lsym_table
    mov rdi,rdx
    mov ecx,sizeof(lsym_table) / 4
    rep stosd
    mov rdi,rdx
    mov rsi,[rsi].asym.procinfo
    mov rsi,[rsi].proc_info.labellist
    .while rsi
        mov eax,[rsi].asym.hash
        .if ( [rsi].asym.casesensitive )
            mov rcx,[rsi].asym.name
            mov eax,FNVBASE
            mov dl,[rcx]
            .while dl
                inc  rcx
                or   dl,0x20
                imul eax,eax,FNVPRIME
                xor  al,dl
                mov  dl,[rcx]
            .endw
        .endif
        and eax,LHASH_TABLE_SIZE - 1
        mov [rdi+rax*size_t],rsi
        mov rsi,[rsi].asym.nextll
    .endw
    ret
    endp

;
; CASEMAP is set on symbol creation here.
;
; option casemap:none
; abc db 1
; ABC db 2
; option casemap:all
;
; Result:     Asmc Masm JWasm
; mov al,abc  abc  ABC  abc
; mov cl,ABC  ABC  ABC  abc
;

SymHash proc fastcall name:string_t
    mov edx,0x2000
    .if ( MODULE.case_sensitive )
        xor edx,edx
    .endif
    .for ( eax = FNVBASE : byte ptr [rcx] : rcx++ )
        mov  dl,[rcx]
        or   dl,dh
        imul eax,eax,FNVPRIME
        xor  al,dl
    .endf
    ret
    endp


SymAlloc proc __ccall uses rsi rdi rbx name:string_t
    ldr rsi,name
    mov ebx,SymHash(rsi)
    sub rcx,rsi
    mov edi,ecx
    LclAlloc( &[rdi+asym+1] )
    mov [rax].asym.hash,ebx
    mov [rax].asym.name_size,edi
    mov [rax].asym.mem_type,MT_EMPTY
    lea rdx,[rax+asym]
    mov [rax].asym.name,rdx
    .if ( MODULE.cref )
        mov [rax].asym.list,1
    .endif
    .if ( MODULE.case_sensitive )
        mov [rax].asym.casesensitive,1
    .endif
    .if edi
        mov ecx,edi
        mov rdi,rdx
        rep movsb
    .endif
    ret
    endp


.pragma warning(disable: 6004)


; find a symbol in the local/global symbol table,
; return ptr to next free entry in global table if not found.
; Note: lsym must be global, thus if the symbol isn't
; found and is to be added to the local table, there's no
; second scan necessary.


ifdef _WIN64
option win64:rsp noauto nosave
else
define r8d <esi>
define r9d <ebx>
define r10d <edi>
assume uses esi edi ebx
endif

_LK_SYMFIND macro
    cmp     rax,CurrProc
    jz      .gsym
    mov     eax,r8d
    and     eax,LHASH_TABLE_SIZE-1
ifdef _WIN64
    lea     r10,lsym_table
    lea     rdx,[r10+rax*size_t]
else
    lea     edx,lsym_table[eax*size_t]
endif
    mov     rax,[rdx]
    test    rax,rax
    jz      .lend
.lcmp:
    cmp     ecx,[rax].asym.name_size
    jne     .llup
    test    [rax].asym.casesensitive,1
    mov     r10d,r9d
ifdef __P686__
    cmovz   r10d,r8d
else
    jnz     @F
    mov     r10d,r8d
@@:
endif
    cmp     r10d,[rax].asym.hash
    je      .done
.llup:
    mov     rdx,rax
    mov     rax,[rax].asym.nextitem
    test    rax,rax
    jnz     .lcmp
.lend:
    mov     lsym,rdx
.gsym:
    mov     eax,r8d
    and     eax,GHASH_TABLE_SIZE-1
ifdef _WIN64
    lea     r10,gsym_table
    lea     rdx,[r10+rax*size_t]
else
    lea     edx,gsym_table[eax*size_t]
endif
    mov     rax,[rdx]
    test    rax,rax
    jz      .done
.gcmp:
    cmp     ecx,[rax].asym.name_size
    jne     .glup
    test    [rax].asym.casesensitive,1
    mov     r10d,r9d
ifdef __P686__
    cmovz   r10d,r8d
else
    jnz     @F
    mov     r10d,r8d
@@:
endif
    cmp     r10d,[rax].asym.hash
    je      .done
.glup:
    mov     rdx,rax
    mov     rax,[rax].asym.nextitem
    test    rax,rax
    jnz     .gcmp
.done:
    endm

align size_t*2

SymFindID proc fastcall tok:token_t
    xor     eax,eax
    mov     r8d,[rcx].asm_tok.hash1
    mov     r9d,[rcx].asm_tok.hash2
    movzx   ecx,[rcx].asm_tok.idlen
    test    ecx,ecx
    jz      .done
    _LK_SYMFIND
    ret
    endp

align size_t*2

SymFind proc fastcall string:string_t
    movzx   eax,byte ptr [rcx]
    mov     r8d,FNVBASE
    mov     r9d,FNVBASE
    mov     rdx,rcx
    test    eax,eax
    jz      .done
.0:
    imul    r9d,r9d,FNVPRIME
    imul    r8d,r8d,FNVPRIME
    xor     r9d,eax
    or      eax,0x20
    inc     rcx
    xor     r8d,eax
    mov     al,[rcx]
    test    eax,eax
    jnz     .0
    sub     rcx,rdx
    _LK_SYMFIND
    ret
    endp

ifdef _WIN64
option win64:rbp auto save
else
assume uses:nothing
endif

;
; SymLookup() creates a global label if it isn't defined yet
;
SymLookup proc __ccall uses rbx name:string_t
    ldr rbx,name
    .if !SymFind( rbx )
        xchg rdx,rbx
        SymAlloc( rdx )
        mov [rbx],rax
        inc SymCount
    .endif
    ret
    endp


; SymLookupLocal() creates a local label if it isn't defined yet.
; called by LabelCreate() [see labels.c]

SymLookupLocal proc __ccall uses rbx tokenarray:token_t, name:string_t

    ldr rcx,tokenarray
    ldr rbx,name

    .if ( rcx )
        SymFindID( rcx )
    .else
        SymFind( rbx )
    .endif

    ; v2.19: don't move a label marked as public if -Zm isn't set

    .if ( rax == NULL || ( [rax].asym.ispublic && MODULE.m510 == 0 ) )

        SymAlloc( rbx )
        mov [rax].asym.scoped,1

        ; add the label to the local hash table

        mov rcx,lsym
        mov [rcx],rax

    .elseif ( [rax].asym.state == SYM_UNDEFINED && !( [rax].asym.scoped ) )

        ; if the label was defined due to a FORWARD reference,
        ; its scope is to be changed from global to local.
        ;
        ; remove the label from the global hash table

        mov rcx,[rax].asym.nextitem
        mov [rdx],rcx
        dec SymCount
        mov [rax].asym.scoped,1
        mov [rax].asym.nextitem,0
        mov rcx,lsym
        mov [rcx],rax
    .endif
    ret
    endp


; free a symbol.
; the symbol is no unlinked from hash tables chains,
; hence it is assumed that this is either not needed
; or done by the caller.


SymFree proc __ccall sym:asym_t

    ldr rcx,sym
    movzx eax,[rcx].asym.state
    .switch eax
    .case SYM_INTERNAL
        .if ( [rcx].asym.isproc )
            DeleteProc( rcx )
        .endif
        .endc
    .case SYM_EXTERNAL
        .if ( [rcx].asym.isproc )
            DeleteProc( rcx )
        .endif
        mov rcx,sym
        mov [rcx].asym.first_size,0

        ; The altname field may contain a symbol (if weak == FALSE).
        ; However, this is an independant item and must not be released here

        .endc
    .case SYM_MACRO
        ReleaseMacroData( rcx )
       .endc
    .endsw
    ret
    endp


; add a symbol to local table and set the symbol's name.
; the previous name was "", the symbol wasn't in a symbol table.
; Called by:
; - ParseParams() in proc.c for procedure parameters.

SymAddLocal proc __ccall uses rsi rdi rbx sym:asym_t, name:string_t

    ldr rbx,sym
    ldr rsi,name

    .if SymFind( rsi )
        .if ( [rax].asym.state != SYM_UNDEFINED )
            ; shouldn't happen
            asmerr( 2005, rsi )
           .return 0
        .endif
    .endif

    SymHash(rsi)
    sub rcx,rsi
    mov [rbx].asym.hash,eax
    mov [rbx].asym.name_size,ecx
    lea edi,[rcx+1]
    LclAlloc( edi )
    mov [rbx].asym.name,rax
    mov ecx,edi
    mov rdi,rax
    rep movsb
    mov rcx,lsym
    mov [rcx],rbx
    mov [rbx].asym.nextitem,0
    mov rax,rbx
    ret
    endp


; add a symbol to the global symbol table.
; Called by:
; - RecordDirective() in types.c to add bitfield fields (which have global scope).

SymAddGlobal proc __ccall uses rbx sym:asym_t

    ldr rbx,sym
    .if SymFind( [rbx].asym.name )
        asmerr( 2005, [rbx].asym.name )
        xor eax,eax
    .else
        mov rax,rbx
        inc SymCount
        mov [rdx],rax
        mov [rax].asym.nextitem,0
    .endif
    ret
    endp


; Create symbol and optionally insert it into the symbol table

SymCreate proc __ccall uses rbx name:string_t
    ldr rbx,name
    .if SymFind( rbx )
        asmerr( 2005, rbx )
        xor eax,eax
    .else
        xchg rdx,rbx
        SymAlloc( rdx )
        inc SymCount
        mov [rbx],rax
    .endif
    ret
    endp

; short version of SymCreate()

SymGCreate proc fastcall uses rbx name:string_t
    mov rbx,rdx
    SymAlloc( rcx )
    inc SymCount
    mov [rbx],rax
    ret
    endp


; Create symbol and insert it into the local symbol table.
; This function is called by LocalDir() and ParseParams()
; in proc.c ( for LOCAL directive and PROC parameters ).

SymLCreate proc __ccall name:string_t
    .if SymFind( name )
        .if ( [rax].asym.state != SYM_UNDEFINED )
            ; shouldn't happen
            asmerr( 2005, name )
           .return 0
        .endif
    .endif
    SymAlloc( name )
    mov rcx,lsym
    mov [rcx],rax
    ret
    endp


SymGetCount proc __ccall
    mov eax,SymCount
    ret
    endp


SymMakeAllSymbolsPublic proc __ccall uses rsi rdi
    xor esi,esi
    .repeat
        lea rax,gsym_table
        mov rdi,[rax+rsi*size_t]
        .while ( rdi )
            .if ( [rdi].asym.state == SYM_INTERNAL )
                mov rcx,[rdi].asym.name

                ; no EQU or '=' constants
                ; no predefined symbols ($)
                ; v2.09: symbol already added to public queue?
                ; v2.10: no @@ code labels
                ; v2.37.58: no string/float/switch labels

                movzx eax,word ptr [rcx]
                .if ( ![rdi].asym.isequate &&
                      ![rdi].asym.predefined &&
                      ![rdi].asym.ispublic &&
                      ![rdi].asym.included && ah != '&' )
                    xor ecx,ecx
                    .if ( ah == '$' )
                        .if ( ( al == 'D' || al == 'F' ) && [rdi].asym.name_size == 6 )
                            inc ecx
                        .elseif ( ( al == 'T' || al == 'I' ) && [rdi].asym.name_size == 8 )
                            inc ecx
                        .endif
                    .endif
                    .if ( ecx == 0 )
                        mov [rdi].asym.ispublic,1
                        AddPublicData( rdi )
                    .endif
                .endif
            .endif
            mov rdi,[rdi].asym.nextitem
        .endw
        add esi,1
    .until esi == GHASH_TABLE_SIZE
    ret
    endp


; initialize global symbol table

SymInit proc __ccall uses rsi rdi rbx

  local time_of_day:time_t

    xor eax,eax
    mov SymCount,eax

    ; v2.11: ensure CurrProc is NULL - might be a problem if multiple files are assembled

    mov CurrProc,rax
    lea rdi,gsym_table
    mov ecx,sizeof(gsym_table)/4
    rep stosd
    time( &time_of_day )
    mov rsi,localtime(&time_of_day)
if USESTRFTIME
    strftime( &szDate, 9, "%D", esi )   ; POSIX date (mm/dd/yy)
    strftime( &szTime, 9, "%T", esi )   ; POSIX time (HH:MM:SS)
else
    mov edx,[rsi].tm.tm_year
    sub edx,100
    mov ecx,[rsi].tm.tm_mon
    add ecx,1
if 1 ; changed in v2.34
    tsprintf( &szDate, "%02u/%02u/%02u", ecx, [rsi].tm.tm_mday, edx )
else
    add edx,2000
    tsprintf( &szDate, "%u-%02u-%02u", edx, ecx, [rsi].tm.tm_mday )
endif
    tsprintf( &szTime, "%02u:%02u:%02u", [rsi].tm.tm_hour, [rsi].tm.tm_min, [rsi].tm.tm_sec )
endif
    lea rsi,tmtab
    .while ( [rsi].tmitem.name )
        SymCreate( [rsi].tmitem.name )
        mov [rax].asym.state,SYM_TMACRO
        mov [rax].asym.isdefined,1
        mov [rax].asym.predefined,1
        mov rcx,[rsi].tmitem.value
        mov [rax].asym.string_ptr,rcx
        mov rcx,[rsi].tmitem.store
        add rsi,tmitem
        .if ( rcx )
            mov [rcx],rax
        .endif
    .endw
    lea rsi,eqtab
    .while [rsi].eqitem.name
        SymCreate( [rsi].eqitem.name )
        mov [rax].asym.state,SYM_INTERNAL
        mov [rax].asym.isdefined,1
        mov [rax].asym.predefined,1
        mov rcx,[rsi].eqitem.value
        mov [rax].asym.offs,ecx
        mov rcx,[rsi].eqitem.sfunc_ptr
        mov [rax].asym.sfunc_ptr,rcx
        mov rcx,[rsi].eqitem.store
        add rsi,eqitem
        .if ( rcx )
            mov [rcx],rax
        .endif
    .endw

    ; @WordSize should not be listed

    mov [rax].asym.list,0
    xor esi,esi
    .while ( esi < dyneqcount )
        lea rax,dyneqtable
        .if SymCreate( [rax+rsi*string_t] )
            mov [rax].asym.state,SYM_TMACRO
            mov [rax].asym.isdefined,1
            mov [rax].asym.predefined,1
            lea rdx,dyneqvalue
            mov rcx,[rdx+rsi*string_t]
            mov [rax].asym.string_ptr,rcx
            mov [rax].asym.sfunc_ptr,0
        .endif
        inc esi
    .endw

    ; $ is an address (usually). Also, don't add it to the list

    mov rax,symPC
    mov [rax].asym.list,0
    mov [rax].asym.isvariable,1
    mov rax,LineCur
    mov [rax].asym.list,0
    ret
    endp


SymPassInit proc __ccall pass:int_t

    .if ( pass != PASS_1 )

        ; No need to reset the "defined" flag if FASTPASS is on.
        ; Because then the source lines will come from the line store,
        ; where inactive conditional lines are NOT contained.

        .if !UseSavedState

            ; mark as "undefined":
            ; - SYM_INTERNAL - internals
            ; - SYM_MACRO - macros
            ; - SYM_TMACRO - text macros

            xor ecx,ecx
            .repeat
                lea rax,gsym_table
                mov rax,[rax+rcx*asym_t]
                .while ( rax )
                    .if !( [rax].asym.predefined )
                        mov [rax].asym.isdefined,0
                    .endif
                    mov rax,[rax].asym.nextitem
                .endw
                add ecx,1
            .until ecx == GHASH_TABLE_SIZE
        .endif
    .endif
    ret
    endp


; get all symbols in global hash table

SymGetAll proc __ccall syms:asym_t
    ldr rdx,syms
    xor ecx,ecx
    .repeat ; copy symbols to table
        lea rax,gsym_table
        mov rax,[rax+rcx*asym_t]
        .while rax
            mov [rdx],rax
            add rdx,asym_t
            mov rax,[rax].asym.nextitem
        .endw
        add ecx,1
    .until ecx == GHASH_TABLE_SIZE
    ret
    endp


; enum symbols in global hash table.
; used for codeview symbolic debug output.

SymEnum proc __ccall uses rbx sym:asym_t, pi:ptr int_t
    lea rbx,gsym_table
    ldr rax,sym
    ldr rdx,pi
    .if ( rax )
        mov rax,[rax].asym.nextitem
        mov ecx,[rdx]
    .else
        xor ecx,ecx
        mov [rdx],ecx
        mov rax,[rbx]
    .endif
    .while ( !rax && ecx < GHASH_TABLE_SIZE - 1 )
        add ecx,1
        mov [rdx],ecx
        mov rax,[rbx+rcx*asym_t]
    .endw
    ret
    endp


; add a new node to a queue

QEnqueue proc fastcall q:qdesc_t, item:ptr
    xor eax,eax
    .if ( rax == [rcx].qdesc.head )
        mov [rcx].qdesc.head,rdx
        mov [rcx].qdesc.tail,rdx
        mov [rdx],rax
    .else
        mov rax,[rcx].qdesc.tail
        mov [rcx].qdesc.tail,rdx
        mov [rax],rdx
        xor eax,eax
        mov [rdx],rax
    .endif
    ret
    endp


QAddItem proc fastcall uses rsi rdi q:qdesc_t, d:ptr
    mov rsi,rcx
    mov rdi,rdx
    LclAlloc( qdesc )
    mov [rax].qnode.elmt,rdi
    QEnqueue( rsi, rax )
    ret
    endp

; add a symbol into the Publics queue.
; called by:
; - EXTERNDEF (if symbol is internal and public=0) - this cannot happen in pass 1
;   ( and it's a very questionable thing!)
; - PUBLIC ( this usually happens in pass 1 )
; - END ( if the label hasn't been marked as public )
; - PROC
; - sym_ext2int() in parser.asm, for public data, constants, labels ( not PROCs )

AddPublicData proc fastcall sym:asym_t
    QAddItem( &MODULE.PubQueue, rcx )
    ret
    endp

    end
