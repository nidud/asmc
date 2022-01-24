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

public              SymCmpFunc
externdef           FileCur   :asym_t ; @FileCur symbol
externdef           LineCur   :asym_t ; @Line symbol
externdef           symCurSeg :asym_t ; @CurSeg symbol

UpdateLineNumber    proto __ccall :asym_t, :ptr
UpdateWordSize      proto __ccall :asym_t, :ptr
UpdateCurPC         proto __ccall :asym_t, :ptr

GHASH_TABLE_SIZE    equ 0x8000
LHASH_TABLE_SIZE    equ 256

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
sfunc_ptr           proc __ccall :asym_t, :ptr
store               symptr_t ?
eqitem              ends

.data?
gsym                symptr_t ?          ; asym ** pointer into global hash table
lsym                symptr_t ?          ; asym ** pointer into local hash table
szDate              char_t 16 dup(?)    ; value of @Date symbol
szTime              char_t 16 dup(?)    ; value of @Time symbol
lsym_table          asym_t LHASH_TABLE_SIZE+1 dup(?)
gsym_table          asym_t GHASH_TABLE_SIZE dup(?)
SymCmpFunc          StrCmpFunc ?
SymCount            uint_t ?            ; Number of symbols in global table

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

    ; v2.09: @CurSeg value is never set if no segment is ever opened.
    ; this may have caused an access error if a listing was written.

    tmitem  <@CStr("@CurSeg"), @CStr(""), symCurSeg>
    string_t NULL

; table of predefined numeric equates

eqtab LABEL eqitem
    eqitem  < @CStr("__ASMC__"), ASMC_VERSION, 0, 0 >
ifdef ASMC64
    eqitem  < @CStr("__ASMC64__"), ASMC_VERSION, 0, 0 >
endif
    eqitem  < @CStr("__JWASM__"),  212, 0, 0 >
    eqitem  < @CStr("$"),          0, UpdateCurPC, symPC >
    eqitem  < @CStr("@Line"),      0, UpdateLineNumber, LineCur >
    eqitem  < @CStr("@WordSize"),  0, UpdateWordSize, 0 > ; must be last (see SymInit())
    string_t NULL

_MAX_DYNEQ equ 20
dyneqtable string_t _MAX_DYNEQ dup(0)
dyneqvalue string_t _MAX_DYNEQ dup(0)
dyneqcount int_t 0

    .code

define_name proc fastcall string:string_t, value:string_t

    mov r8d,dyneqcount
    lea rax,dyneqtable
    mov [rax+r8*string_t],rcx
    lea rax,dyneqvalue
    mov [rax+r8*string_t],rdx
    inc dyneqcount
    ret

define_name endp

SymSetCmpFunc proc fastcall

    lea rax,tmemicmp
    .if ModuleInfo.case_sensitive
        lea rax,tmemcmp
    .endif
    mov SymCmpFunc,rax
    ret

SymSetCmpFunc endp

; reset local hash table

SymClearLocal proc fastcall

    xor  eax,eax
    lea  rdx,lsym_table
    mov  ecx,sizeof(lsym_table) / 8
    xchg rdx,rdi
    rep  stosq
    mov  rdi,rdx
    ret

SymClearLocal endp

; store local hash table in proc's list of local symbols

SymGetLocal proc fastcall psym:asym_t

    mov rdx,[rcx].dsym.procinfo
    lea rdx,[rdx].proc_info.labellist
    xor ecx,ecx
    lea r8,lsym_table
    .while ecx < LHASH_TABLE_SIZE
        mov rax,[r8+rcx*asym_t]
        inc ecx
        .continue .if !rax
        mov [rdx],rax
        lea rdx,[rax].dsym.nextll
    .endw
    xor eax,eax
    mov [rdx],eax
    ret

SymGetLocal endp

; restore local hash table.
; - proc: procedure which will become active.
; fixme: It might be necessary to reset the "defined" flag
; for local labels (not for params and locals!). Low priority!

define FNVPRIME 0x01000193
define FNVBASE  0x811c9dc5

SymSetLocal proc fastcall psym:asym_t

    xor eax,eax
    mov r8,rcx
    lea r9,lsym_table
    mov rdx,rdi
    mov rdi,r9
    mov ecx,sizeof(lsym_table) / 8
    rep stosq
    mov rdi,rdx

    mov r8,[r8].dsym.procinfo
    mov r8,[r8].proc_info.labellist

    .while r8

        mov rcx,[r8].asym.name
        mov eax,FNVBASE
        mov dl,[rcx]
        .while dl
            inc  rcx
            or   dl,0x20
            imul eax,eax,FNVPRIME
            xor  al,dl
            mov  dl,[rcx]
        .endw
        and eax,LHASH_TABLE_SIZE - 1
        mov [r9+rax*8],r8
        mov r8,[r8].dsym.nextll
    .endw
    ret

SymSetLocal endp

SymAlloc proc fastcall uses rsi rdi name:string_t

    mov rsi,rcx
    mov edi,tstrlen(rcx)
    LclAlloc( &[rdi+dsym+1] )

    mov [rax].asym.name_size,edi
    mov [rax].asym.mem_type,MT_EMPTY

    lea rdx,[rax+dsym]
    mov [rax].asym.name,rdx

    .if ModuleInfo.cref

        or [rax].asym.flag1,S_LIST
    .endif

    .if edi

        mov ecx,edi
        mov rdi,rdx
        rep movsb
    .endif
    ret

SymAlloc endp

.pragma warning(disable: 6004)

    option dotname
    option win64:rsp noauto nosave

SymFind proc fastcall string:string_t
    ;
    ; find a symbol in the local/global symbol table,
    ; return ptr to next free entry in global table if not found.
    ; Note: lsym must be global, thus if the symbol isn't
    ; found and is to be added to the local table, there's no
    ; second scan necessary.
    ;
    movzx   eax,byte ptr [rcx]
    test    eax,eax
    jz      .done

    mov     r10,rcx
    or      al,0x20
    xor     eax,( FNVPRIME * FNVBASE ) and 0xFFFFFFFF
    inc     rcx
if 0
    mov     r8d,1
.0:
    mov     rdx,0x2020202020202020
    or      rdx,[rcx]
    cmp     dl,0x20
    je      .1
    imul    eax,eax,FNVPRIME
    xor     al,dl
    inc     r8d
    cmp     dh,0x20
    je      .1
    imul    eax,eax,FNVPRIME
    xor     al,dh
    inc     r8d
    shr     rdx,16
    cmp     dl,0x20
    je      .1
    imul    eax,eax,FNVPRIME
    xor     al,dl
    inc     r8d
    cmp     dh,0x20
    je      .1
    imul    eax,eax,FNVPRIME
    xor     al,dh
    inc     r8d
    shr     rdx,16
    cmp     dl,0x20
    je      .1
    imul    eax,eax,FNVPRIME
    xor     al,dl
    inc     r8d
    cmp     dh,0x20
    je      .1
    imul    eax,eax,FNVPRIME
    xor     al,dh
    inc     r8d
    shr     rdx,16
    cmp     dl,0x20
    je      .1
    imul    eax,eax,FNVPRIME
    xor     al,dl
    inc     r8d
    cmp     dh,0x20
    je      .1
    imul    eax,eax,FNVPRIME
    xor     al,dh
    inc     r8d
    add     rcx,8
    jmp     .0
.1:
else
    mov     dl,[rcx]
    test    dl,dl
    jz      .1
.0:
    inc     rcx
    or      dl,0x20
    imul    eax,eax,FNVPRIME
    xor     al,dl
    mov     dl,[rcx]
    test    dl,dl
    jnz     .0
.1:
    sub     rcx,r10
    mov     r8d,ecx
endif

    cmp     CurrProc,0
    je      .global

    mov     r9d,eax
    and     eax,LHASH_TABLE_SIZE - 1
    lea     rdx,lsym_table
    lea     rdx,[rdx+rax*8]
    mov     rax,[rdx]
    test    rax,rax
    jz      .end_l
    cmp     ModuleInfo.case_sensitive,0
    je      .cmp_li
.cmp_l:
    cmp     r8d,[rax].asym.name_size
    jne     .next_l
    mov     r11,[rax].asym.name
.dd_l:
    test    r8d,-4
    jz      .db_l
    sub     r8d,4
    mov     ecx,[r10+r8]
    cmp     ecx,[r11+r8]
    je      .dd_l
    jmp     .size_l
.db_l:
    test    r8d,r8d
    jz      .exit_l
    sub     r8d,1
    mov     cl,[r10+r8]
    cmp     cl,[r11+r8]
    je      .db_l
.size_l:
    mov     r8d,[rax].asym.name_size
.next_l:
    mov     rdx,rax
    mov     rax,[rax].asym.nextitem
    test    rax,rax
    jnz     .cmp_l
    jmp     .end_l
.exit_l:
    mov     lsym,rdx
    jmp     .done
.cmp_li:
    cmp     r8d,[rax].asym.name_size
    jne     .next_li
    mov     r11,[rax].asym.name
.dd_li:
    test    r8d,-4
    jz      .db_li
    sub     r8d,4
    mov     ecx,[r10+r8]
    cmp     ecx,[r11+r8]
    je      .dd_li
    add     r8d,4
.db_li:
    test    r8d,r8d
    jz      .exit_l
    sub     r8d,1
    mov     cl,[r10+r8]
    cmp     cl,[r11+r8]
    je      .db_li
    mov     ch,cl
    mov     cl,[r11+r8]
    or      ecx,0x2020
    cmp     cl,ch
    je      .db_li
    mov     r8d,[rax].asym.name_size
.next_li:
    mov     rdx,rax
    mov     rax,[rax].asym.nextitem
    test    rax,rax
    jnz     .cmp_li
.end_l:
    mov     lsym,rdx
    mov     eax,r9d
.global:
    and     eax,GHASH_TABLE_SIZE-1
    lea     rdx,gsym_table
    lea     rdx,[rdx+rax*8]
    mov     rax,[rdx]
    test    rax,rax
    jz      .end_g
    cmp     ModuleInfo.case_sensitive,0
    je      .cmp_gi
.cmp_g:
    cmp     r8d,[rax].asym.name_size
    jne     .next_g
    mov     r11,[rax].asym.name
    mov     r9d,r8d
.dd_g:
    test    r9d,-4
    jz      .db_g
    sub     r9d,4
    mov     ecx,[r10+r9]
    cmp     ecx,[r11+r9]
    je      .dd_g
    jmp     .next_g
.db_g:
    test    r9d,r9d
    jz      .end_g
    sub     r9d,1
    mov     cl,[r10+r9]
    cmp     cl,[r11+r9]
    je      .db_g
.next_g:
    mov     rdx,rax
    mov     rax,[rax].asym.nextitem
    test    rax,rax
    jnz     .cmp_g
    jmp     .end_g
.cmp_gi:
    cmp     r8d,[rax].asym.name_size
    jne     .next_gi
    mov     r11,[rax].asym.name
    mov     r9d,r8d
.dd_gi:
    test    r9d,-4
    jz      .db_gi
    sub     r9d,4
    mov     ecx,[r10+r9]
    cmp     ecx,[r11+r9]
    je      .dd_gi
    add     r9d,4
.db_gi:
    test    r9d,r9d
    jz      .end_g
    sub     r9d,1
    mov     cl,[r10+r9]
    cmp     cl,[r11+r9]
    je      .db_gi
    mov     ch,cl
    mov     cl,[r11+r9]
    or      ecx,0x2020
    cmp     cl,ch
    je      .db_gi
.size_gi:
    mov     r8d,[rax].asym.name_size
.next_gi:
    mov     rdx,rax
    mov     rax,[rax].asym.nextitem
    test    rax,rax
    jnz     .cmp_gi
.end_g:
    mov     gsym,rdx
.done:
    ret

SymFind endp

    option win64:rbp auto save

;
; SymLookup() creates a global label if it isn't defined yet
;
SymLookup proc fastcall name:string_t

    .if !SymFind(rcx)

        SymAlloc(name)
        mov rcx,gsym
        mov [rcx],rax
        inc SymCount
    .endif
    ret
SymLookup endp

;
; SymLookupLocal() creates a local label if it isn't defined yet.
; called by LabelCreate() [see labels.c]
;
SymLookupLocal proc fastcall name:string_t

    .if !SymFind(rcx)
        SymAlloc(name)
        or [rax].asym.flags,S_SCOPED
        ;
        ; add the label to the local hash table
        ;
        mov rcx,lsym
        mov [rcx],rax

    .elseif [rax].asym.state == SYM_UNDEFINED && !( [rax].asym.flags & S_SCOPED )
        ;
        ; if the label was defined due to a FORWARD reference,
        ; its scope is to be changed from global to local.
        ;
        ; remove the label from the global hash table
        ;
        mov rdx,[rax].asym.nextitem
        mov rcx,gsym
        mov [rcx],rdx
        dec SymCount
        or  [rax].asym.flags,S_SCOPED
        mov [rax].asym.nextitem,0
        mov rcx,lsym
        mov [rcx],rax
    .endif
    ret

SymLookupLocal endp

;
; free a symbol.
; the symbol is no unlinked from hash tables chains,
; hence it is assumed that this is either not needed
; or done by the caller.
;
SymFree proc fastcall sym:asym_t

    movzx eax,[rcx].asym.state
    .switch eax
      .case SYM_INTERNAL
        .if [rcx].asym.flag1 & S_ISPROC
            DeleteProc( rcx )
        .endif
        .endc
      .case SYM_EXTERNAL
        .if [rcx].asym.flag1 & S_ISPROC
            DeleteProc( rcx )
        .endif
        mov rcx,sym
        mov [rcx].asym.first_size,0
        ;
        ; The altname field may contain a symbol (if weak == FALSE).
        ; However, this is an independant item and must not be released here
        ;
        .endc
      .case SYM_MACRO
        ReleaseMacroData(rcx)
        .endc
    .endsw
    ret
SymFree endp

;
; add a symbol to local table and set the symbol's name.
; the previous name was "", the symbol wasn't in a symbol table.
; Called by:
; - ParseParams() in proc.c for procedure parameters.
;
SymAddLocal proc fastcall uses rsi rdi rbx sym:asym_t, name:string_t

    mov rbx,rcx
    mov rsi,rdx

    .if SymFind(rsi)

        .if [rax].asym.state != SYM_UNDEFINED

            ; shouldn't happen

            asmerr(2005, rsi)
           .return 0
        .endif
    .endif

    tstrlen(rsi)
    mov [rbx].asym.name_size,eax
    lea edi,[rax+1]
    LclAlloc(edi)
    mov [rbx].asym.name,rax
    mov ecx,edi
    mov rdi,rax
    rep movsb
    mov rcx,lsym
    mov [rcx],rbx
    mov [rbx].asym.nextitem,0
    mov rax,rbx
    ret

SymAddLocal endp

;
; add a symbol to the global symbol table.
; Called by:
; - RecordDirective() in types.c to add bitfield fields (which have global scope).
;
SymAddGlobal proc fastcall sym:asym_t

    .if SymFind([rcx].asym.name)
        mov rax,sym
        asmerr(2005, [rax].asym.name)
        xor eax,eax
    .else
        mov rax,sym
        inc SymCount
        mov rcx,gsym
        mov [rcx],rax
        mov [rax].asym.nextitem,0
    .endif
    ret
SymAddGlobal endp

;
; Create symbol and optionally insert it into the symbol table
;
SymCreate proc fastcall name:string_t
    .if SymFind(rcx)
        asmerr(2005, name)
        xor eax,eax
    .else
        SymAlloc(name)
        inc SymCount
        mov rcx,gsym
        mov [rcx],rax
    .endif
    ret
SymCreate endp

;
; Create symbol and insert it into the local symbol table.
; This function is called by LocalDir() and ParseParams()
; in proc.c ( for LOCAL directive and PROC parameters ).
;
SymLCreate proc fastcall name:string_t

    .if SymFind(rcx)

        .if [rax].asym.state != SYM_UNDEFINED
            ;
            ; shouldn't happen
            ;
            asmerr(2005, name)
            .return 0
        .endif
    .endif

    SymAlloc(name)
    mov rcx,lsym
    mov [rcx],rax
    ret

SymLCreate endp

SymGetCount proc fastcall
    mov eax,SymCount
    ret
SymGetCount endp

SymMakeAllSymbolsPublic proc fastcall uses rsi rdi

    xor esi,esi
    .repeat
        lea rax,gsym_table
        mov rdi,[rax+rsi*8]
        .while rdi

            .if [rdi].asym.state == SYM_INTERNAL

                mov rcx,[rdi].asym.name
                ;
                ; no EQU or '=' constants
                ; no predefined symbols ($)
                ; v2.09: symbol already added to public queue?
                ; v2.10: no @@ code labels
                ;
                mov al,[rcx+1]
                .if ( !( [rdi].asym.flags & S_ISEQUATE or S_PREDEFINED or S_ISPUBLIC ) && \
                      !( [rdi].asym.flag1 & S_INCLUDED ) && al != '&' )
                    or [rdi].asym.flags,S_ISPUBLIC
                    AddPublicData(rdi)
                .endif

            .endif
            mov rdi,[rdi].asym.nextitem
        .endw
        add esi,1
    .until esi == GHASH_TABLE_SIZE
    ret

SymMakeAllSymbolsPublic endp

; initialize global symbol table

SymInit proc fastcall uses rsi rdi rbx

  local time_of_day:time_t

    xor eax,eax
    mov SymCount,eax
    ;
    ; v2.11: ensure CurrProc is NULL - might be a problem if multiple files are assembled
    ;
    mov CurrProc,rax
    lea rdi,gsym_table
    mov ecx,sizeof(gsym_table)/4
    rep stosd
    time(&time_of_day)
    mov rsi,localtime(&time_of_day)

if USESTRFTIME
    strftime(&szDate, 9, "%D", esi)   ; POSIX date (mm/dd/yy)
    strftime(&szTime, 9, "%T", esi)   ; POSIX time (HH:MM:SS)
else
    mov edx,[rsi].tm.tm_year
    sub edx,100
    mov ecx,[rsi].tm.tm_mon
    add ecx,1
;   sprintf(&szDate, "%02u/%02u/%02u", ecx, [rsi].tm.tm_mday, eax)
    add edx,2000
    tsprintf(&szDate, "%u-%02u-%02u", edx, ecx, [rsi].tm.tm_mday)
    tsprintf(&szTime, "%02u:%02u:%02u", [rsi].tm.tm_hour, [rsi].tm.tm_min, [rsi].tm.tm_sec)
endif
    lea rsi,tmtab
    .while [rsi].tmitem.name
        SymCreate([rsi].tmitem.name)
        mov [rax].asym.state,SYM_TMACRO
        or  [rax].asym.flags,S_ISDEFINED or S_PREDEFINED
        mov rcx,[rsi].tmitem.value
        mov [rax].asym.string_ptr,rcx
        mov rcx,[rsi].tmitem.store
        add rsi,tmitem
        .continue .if !rcx
        mov [rcx],rax
    .endw

    lea rsi,eqtab
    .while [rsi].eqitem.name
        SymCreate([rsi].eqitem.name)
        mov [rax].asym.state,SYM_INTERNAL
        or  [rax].asym.flags,S_ISDEFINED or S_PREDEFINED
        mov rcx,[rsi].eqitem.value
        mov [rax].asym.offs,ecx
        mov rcx,[rsi].eqitem.sfunc_ptr
        mov [rax].asym.sfunc_ptr,rcx
        mov rcx,[rsi].eqitem.store
        add rsi,eqitem
        .continue .if !rcx
        mov [rcx],rax
    .endw
    ;
    ; @WordSize should not be listed
    ;
    and [rax].asym.flag1,not S_LIST

    xor esi,esi
    .while esi < dyneqcount
        lea rax,dyneqtable
        SymCreate([rax+rsi*string_t])
if 0
        mov [rax].asym.state,SYM_INTERNAL
        or  [rax].asym.flags,S_ISDEFINED or S_ISEQUATE or S_VARIABLE
else
        mov [rax].asym.state,SYM_TMACRO
        or  [rax].asym.flags,S_ISDEFINED or S_PREDEFINED
endif
        lea rdx,dyneqvalue
        mov rcx,[rdx+rsi*string_t]
        ;mov [rax].asym.offs,ecx
        mov [rax].asym.string_ptr,rcx
        mov [rax].asym.sfunc_ptr,0
        inc esi
    .endw
    ;
    ; $ is an address (usually). Also, don't add it to the list
    ;
    mov rax,symPC
    and [rax].asym.flag1,not S_LIST
    or  [rax].asym.flags,S_VARIABLE
    mov rax,LineCur
    and [rax].asym.flag1,not S_LIST
    ret

SymInit endp

SymPassInit proc fastcall pass:int_t

    .if ecx != PASS_1

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
                .while eax
                    .if !( [rax].asym.flags & S_PREDEFINED )
                        and [rax].asym.flags,not S_ISDEFINED
                    .endif
                    mov rax,[rax].asym.nextitem
                .endw
                add ecx,1
            .until ecx == GHASH_TABLE_SIZE
        .endif
    .endif
    ret

SymPassInit endp

; get all symbols in global hash table

SymGetAll proc fastcall syms:asym_t

    mov rdx,rcx
    xor ecx,ecx
    ;
    ; copy symbols to table
    ;
    .repeat

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

SymGetAll endp

; enum symbols in global hash table.
; used for codeview symbolic debug output.

SymEnum proc fastcall sym:asym_t, pi:ptr int_t

    lea r8,gsym_table
    mov rax,rcx
    .if rax
        mov rax,[rax].asym.nextitem
        mov ecx,[rdx]
    .else
        xor ecx,ecx
        mov [rdx],ecx
        mov rax,[r8]
    .endif
    .while !rax && ecx < GHASH_TABLE_SIZE - 1
        add ecx,1
        mov [rdx],ecx
        mov rax,[r8+rcx*asym_t]
    .endw
    ret
SymEnum endp

;
; add a new node to a queue
;

QEnqueue proc fastcall q:qdesc_t, item:ptr

    xor eax,eax
    .if rax == [rcx].qdesc.head
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

QEnqueue endp

QAddItem proc fastcall q:qdesc_t, d:ptr

    LclAlloc(qdesc)
    mov rdx,d
    mov [rax].qnode.elmt,rdx
    QEnqueue(q, rax)
    ret

QAddItem endp

AddPublicData proc fastcall sym:asym_t

    QAddItem(&ModuleInfo.PubQueue, rcx)
    ret

AddPublicData endp

    end
