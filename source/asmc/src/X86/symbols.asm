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

UpdateLineNumber    proto :asym_t, :ptr
UpdateWordSize      proto :asym_t, :ptr
UpdateCurPC         proto :asym_t, :ptr

HASH_MAGNITUDE      equ 15  ; is 15 since v1.94, previously 12
HASH_MASK           equ 0x7FFF
;
; size of global hash table for symbol table searches. This affects
; assembly speed.
;
GHASH_TABLE_SIZE    equ 8192
;
; size of local hash table
;
LHASH_TABLE_SIZE    equ 128
;
; use memcpy()/memcmpi() directly?
; this may speed-up things, but not with OW.
; MSVC is a bit faster then.
;
USEFIXSYMCMP        equ 0   ; 1=don't use a function pointer for string compare
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
sfunc_ptr           proc :asym_t, :ptr
store               symptr_t ?
eqitem              ends

.data?
                    align 16
SymCmpFunc          StrCmpFunc ?
gsym                symptr_t ?          ; asym ** pointer into global hash table
lsym                symptr_t ?          ; asym ** pointer into local hash table
SymCount            uint_t ?            ; Number of symbols in global table
szDate              char_t 16 dup(?)    ; value of @Date symbol
szTime              char_t 16 dup(?)    ; value of @Time symbol
lsym_table          asym_t LHASH_TABLE_SIZE+1 dup(?)
                    align 16
gsym_table          asym_t GHASH_TABLE_SIZE dup(?)

.data
align 4
symPC asym_t 0  ; the $ symbol

; table of predefined text macros

tmtab label tmitem

    ; @Version contains the Masm compatible version
    ; v2.06: value of @Version changed to 800

ifdef __ASMC64__
    tmitem  <@CStr("@Version"),  @CStr("1000"), 0>
else
    tmitem  <@CStr("@Version"),  @CStr("800"), 0>
endif
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
ifdef __ASMC64__
    eqitem  < @CStr("__ASMC64__"), ASMC_VERSION, 0, 0 >
endif
    eqitem  < @CStr("__JWASM__"),  212, 0, 0 >
    eqitem  < @CStr("$"),          0, UpdateCurPC, symPC >
    eqitem  < @CStr("@Line"),      0, UpdateLineNumber, LineCur >
    eqitem  < @CStr("@WordSize"),  0, UpdateWordSize, 0 > ; must be last (see SymInit())
    string_t NULL

_MAX_DYNEQ equ 10
dyneqcount int_t 0
dyneqtable string_t _MAX_DYNEQ dup(0)
dyneqvalue string_t _MAX_DYNEQ dup(0)

    .code

define_name proc string:string_t, value:string_t
    mov edx,dyneqcount
    mov dyneqtable[edx*4],string
    mov dyneqvalue[edx*4],value
    inc dyneqcount
    ret
define_name endp

SymSetCmpFunc proc
    mov SymCmpFunc,_memicmp
    .if ModuleInfo.case_sensitive
        mov SymCmpFunc,memcmp
    .endif
    ret
SymSetCmpFunc endp

; reset local hash table

SymClearLocal proc
    xor  eax,eax
    lea  edx,lsym_table
    mov  ecx,sizeof(lsym_table) / 4
    xchg edx,edi
    rep  stosd
    mov  edi,edx
    ret
SymClearLocal endp

; store local hash table in proc's list of local symbols

SymGetLocal proc psym:asym_t

    mov ecx,psym
    mov edx,[ecx].esym.procinfo
    lea edx,[edx].proc_info.labellist
    xor ecx,ecx
    .while ecx < LHASH_TABLE_SIZE

        mov eax,lsym_table[ecx*4]
        add ecx,1
        .continue .if !eax

        mov [edx],eax
        lea edx,[eax].esym.nextll
    .endw
    xor eax,eax
    mov [edx],eax
    ret

SymGetLocal endp

; restore local hash table.
; - proc: procedure which will become active.
; fixme: It might be necessary to reset the "defined" flag
; for local labels (not for params and locals!). Low priority!
SymSetLocal proc uses edi psym:asym_t
    xor eax,eax
    lea edi,lsym_table
    mov ecx,sizeof(lsym_table) / 4
    rep stosd
    mov ecx,psym
    mov edi,[ecx].esym.procinfo
    mov edi,[edi].proc_info.labellist
    .while edi
        mov ecx,[edi].asym.name
        xor eax,eax
        movzx edx,BYTE PTR [ecx]
        .while edx
            add ecx,1
            or  edx,0x20
            shl eax,5
            add eax,edx
            mov edx,eax
            and edx,not HASH_MASK
            xor eax,edx
            shr edx,HASH_MAGNITUDE
            xor eax,edx
            movzx edx,BYTE PTR [ecx]
        .endw
        and eax,LHASH_TABLE_SIZE - 1
        mov lsym_table[eax*4],edi
        mov edi,[edi].esym.nextll
    .endw
    ret
SymSetLocal endp

SymAlloc proc uses esi edi name:string_t
    mov esi,name
    mov edi,strlen(esi)
    LclAlloc(&[edi+esym+1])
    mov [eax].asym.name_size,di
    mov [eax].asym.mem_type,MT_EMPTY
    lea edx,[eax+esym]
    mov [eax].asym.name,edx
    .if ModuleInfo.cref
        or [eax].asym.flag,S_LIST
    .endif
    .if edi
        mov ecx,edi
        mov edi,edx
        rep movsb
    .endif
    ret
SymAlloc ENDP

.pragma warning(disable: 6004)

SymFind proc fastcall uses esi edi ebx ebp string:string_t
    ;
    ; find a symbol in the local/global symbol table,
    ; return ptr to next free entry in global table if not found.
    ; Note: lsym must be global, thus if the symbol isn't
    ; found and is to be added to the local table, there's no
    ; second scan necessary.
    ;
    mov esi,ecx
    xor eax,eax
    movzx edx,byte ptr [ecx]

    .return .if !edx

    .repeat
        add ecx,1
        or  edx,0x20
        shl eax,5
        add eax,edx
        mov edx,eax
        and edx,not HASH_MASK
        xor eax,edx
        shr edx,HASH_MAGNITUDE
        xor eax,edx
        movzx edx,BYTE PTR [ecx]
    .until !edx

    sub ecx,esi
    mov ebp,eax

    .if CurrProc

        and eax,LHASH_TABLE_SIZE - 1
        lea edx,lsym_table[eax*4]
        mov eax,[edx]

        .repeat

            .break .if !eax

            .if ModuleInfo.case_sensitive

                .repeat

                    .if cx == [eax].asym.name_size

                        mov edi,[eax].asym.name

                        .repeat

                            .if ecx >= 4
                                sub ecx,4
                                mov ebx,[esi+ecx]
                                .break .if ebx != [edi+ecx]
                                .continue(0)
                            .endif

                            .while ecx

                                sub ecx,1
                                mov bl,[esi+ecx]
                                .break(1) .if bl != [edi+ecx]
                            .endw

                            mov lsym,edx
                            .return
                        .until 1
                        movzx ecx,[eax].asym.name_size
                    .endif

                    lea edx,[eax].asym.nextitem
                    mov eax,[edx]
                .until !eax

            .else

                .repeat

                    .if cx == [eax].asym.name_size

                        mov edi,[eax].asym.name

                        .while 1

                            .if ecx >= 4

                                sub ecx,4
                                mov ebx,[esi+ecx]
                                .continue(0) .if ebx == [edi+ecx]
                                add ecx,4
                            .endif

                            .while ecx

                                sub ecx,1
                                mov bl,[esi+ecx]
                                .continue .if bl == [edi+ecx]
                                mov bh,[edi+ecx]
                                or ebx,0x2020
                                .break(1) .if bl != bh
                            .endw

                            mov lsym,edx
                            .return
                        .endw
                        movzx ecx,[eax].asym.name_size
                    .endif

                    lea edx,[eax].asym.nextitem
                    mov eax,[edx]
                .until !eax
            .endif

        .until 1

        mov lsym,edx
        mov eax,ebp
    .endif

    and eax,GHASH_TABLE_SIZE - 1
    lea edx,gsym_table[eax*4]
    mov eax,[edx]

    .repeat

        .break .if !eax

        .if ModuleInfo.case_sensitive

            .repeat

                .if cx == [eax].asym.name_size

                    mov edi,[eax].asym.name

                    .while 1

                        .if ecx >= 4

                            sub ecx,4
                            mov ebx,[esi+ecx]
                            .break .if ebx != [edi+ecx]
                            .continue(0)
                        .endif

                        .while ecx

                            sub ecx,1
                            mov bl,[esi+ecx]
                            .break(1) .if bl != [edi+ecx]
                        .endw

                        mov gsym,edx
                        .return
                    .endw
                    movzx ecx,[eax].asym.name_size
                .endif

                lea edx,[eax].asym.nextitem
                mov eax,[edx]
            .until !eax

        .else

            .repeat

                .if cx == [eax].asym.name_size

                    mov edi,[eax].asym.name

                    .while 1

                        .if ecx >= 4

                            sub ecx,4
                            mov ebx,[esi+ecx]
                            .continue(0) .if ebx == [edi+ecx]
                            add ecx,4
                        .endif

                        .while ecx

                            sub ecx,1
                            mov bl,[esi+ecx]
                            .continue .if bl == [edi+ecx]
                            mov bh,[edi+ecx]
                            or ebx,0x2020
                            .break(1) .if bl != bh
                        .endw
                        mov gsym,edx
                        .return
                    .endw
                    movzx ecx,[eax].asym.name_size
                .endif

                lea edx,[eax].asym.nextitem
                mov eax,[edx]
            .until !eax
        .endif
    .until 1
    mov gsym,edx
    xor eax,eax
    ret

SymFind endp

;
; SymLookup() creates a global label if it isn't defined yet
;
SymLookup proc name:string_t

    .if !SymFind(name)

        SymAlloc(name)
        mov ecx,gsym
        mov [ecx],eax
        inc SymCount
    .endif
    ret
SymLookup endp

;
; SymLookupLocal() creates a local label if it isn't defined yet.
; called by LabelCreate() [see labels.c]
;
SymLookupLocal proc name:string_t

    .if !SymFind(name)
        SymAlloc(name)
        or [eax].asym.flag,S_SCOPED
        ;
        ; add the label to the local hash table
        ;
        mov ecx,lsym
        mov [ecx],eax

    .elseif [eax].asym.state == SYM_UNDEFINED && !([eax].asym.flag & S_SCOPED)
        ;
        ; if the label was defined due to a FORWARD reference,
        ; its scope is to be changed from global to local.
        ;
        ; remove the label from the global hash table
        ;
        mov edx,[eax].asym.nextitem
        mov ecx,gsym
        mov [ecx],edx
        dec SymCount
        or  [eax].asym.flag,S_SCOPED
        mov [eax].asym.nextitem,0
        mov ecx,lsym
        mov [ecx],eax
    .endif
    ret

SymLookupLocal endp

;
; free a symbol.
; the symbol is no unlinked from hash tables chains,
; hence it is assumed that this is either not needed
; or done by the caller.
;
SymFree proc sym:asym_t
    mov ecx,sym
    movzx eax,[ecx].asym.state
    .switch eax
      .case SYM_INTERNAL
        .if [ecx].asym.flag & S_ISPROC
            DeleteProc( ecx )
        .endif
        .endc
      .case SYM_EXTERNAL
        .if [ecx].asym.flag & S_ISPROC
            DeleteProc( ecx )
        .endif
        mov ecx,sym
        mov [ecx].asym.first_size,0
        ;
        ; The altname field may contain a symbol (if weak == FALSE).
        ; However, this is an independant item and must not be released here
        ;
        .endc
      .case SYM_MACRO
        ReleaseMacroData(ecx)
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
SymAddLocal proc uses esi edi ebx sym:asym_t, name:string_t

    mov ebx,sym
    mov esi,name

    .if SymFind(esi)

        .if [eax].asym.state != SYM_UNDEFINED

            ;; shouldn't happen

            asmerr(2005, esi)
            .return 0
        .endif
    .endif

    strlen(esi)
    mov [ebx].asym.name_size,ax
    lea edi,[eax+1]
    LclAlloc(edi)
    mov [ebx].asym.name,eax
    mov ecx,edi
    mov edi,eax
    rep movsb
    mov ecx,lsym
    mov [ecx],ebx
    mov [ebx].asym.nextitem,0
    mov eax,ebx
    ret

SymAddLocal endp

;
; add a symbol to the global symbol table.
; Called by:
; - RecordDirective() in types.c to add bitfield fields (which have global scope).
;
SymAddGlobal proc sym:asym_t
    mov eax,sym
    .if SymFind([eax].asym.name)
        mov eax,sym
        asmerr(2005, [eax].asym.name)
        xor eax,eax
    .else
        mov eax,sym
        inc SymCount
        mov ecx,gsym
        mov [ecx],eax
        mov [eax].asym.nextitem,0
    .endif
    ret
SymAddGlobal endp

;
; Create symbol and optionally insert it into the symbol table
;
SymCreate proc name:string_t
    .if SymFind(name)
        asmerr(2005, name)
        xor eax,eax
    .else
        SymAlloc(name)
        inc SymCount
        mov ecx,gsym
        mov [ecx],eax
    .endif
    ret
SymCreate endp

;
; Create symbol and insert it into the local symbol table.
; This function is called by LocalDir() and ParseParams()
; in proc.c ( for LOCAL directive and PROC parameters ).
;
SymLCreate proc name:string_t

    .if SymFind(name)

        .if [eax].asym.state != SYM_UNDEFINED
            ;
            ; shouldn't happen
            ;
            asmerr(2005, name)
            .return 0
        .endif
    .endif

    SymAlloc(name)
    mov ecx,lsym
    mov [ecx],eax
    ret

SymLCreate endp

SymGetCount proc
    mov eax,SymCount
    ret
SymGetCount endp

SymMakeAllSymbolsPublic proc uses esi edi

    xor esi,esi
    .repeat
        mov edi,gsym_table[esi*4]
        .while edi

            .if [edi].asym.state == SYM_INTERNAL

                mov ecx,[edi].asym.name
                ;
                ; no EQU or '=' constants
                ; no predefined symbols ($)
                ; v2.09: symbol already added to public queue?
                ; v2.10: no @@ code labels
                ;
                movzx eax,[edi].asym.flag
                and eax,S_ISEQUATE or S_PREDEFINED or S_INCLUDED or S_ISPUBLIC

                .if ZERO? && BYTE PTR [ecx+1] != '&'
                    or [edi].asym.flag,S_ISPUBLIC
                    AddPublicData(edi)
                .endif

            .endif
            mov edi,[edi].asym.nextitem
        .endw
        add esi,1
    .until esi == GHASH_TABLE_SIZE
    ret

SymMakeAllSymbolsPublic endp

; initialize global symbol table

SymInit proc uses esi edi ebx

    local time_of_day

    xor eax,eax
    mov SymCount,eax
    ;
    ; v2.11: ensure CurrProc is NULL - might be a problem if multiple files are assembled
    ;
    mov CurrProc,eax
    lea edi,gsym_table
    mov ecx,sizeof(gsym_table)
    rep stosb
    time(&time_of_day)
    localtime(&time_of_day)
    mov esi,eax

if USESTRFTIME
    strftime(&szDate, 9, "%D", esi)   ; POSIX date (mm/dd/yy)
    strftime(&szTime, 9, "%T", esi)   ; POSIX time (HH:MM:SS)
else
    mov eax,[esi].tm.tm_year
    sub eax,100
    mov ecx,[esi].tm.tm_mon
    add ecx,1
;   sprintf(&szDate, "%02u/%02u/%02u", ecx, [esi].tm.tm_mday, eax)
    add eax,2000
    sprintf(&szDate, "%u-%02u-%02u", eax, ecx, [esi].tm.tm_mday)
    sprintf(&szTime, "%02u:%02u:%02u", [esi].tm.tm_hour, [esi].tm.tm_min, [esi].tm.tm_sec)
endif
    lea esi,tmtab
    .while [esi].tmitem.name
        SymCreate([esi].tmitem.name)
        mov [eax].asym.state,SYM_TMACRO
        or  [eax].asym.flag,S_ISDEFINED or S_PREDEFINED
        mov ecx,[esi].tmitem.value
        mov [eax].asym.string_ptr,ecx
        mov ecx,[esi].tmitem.store
        add esi,tmitem
        .continue .if !ecx
        mov [ecx],eax
    .endw

    lea esi,eqtab
    .while [esi].eqitem.name
        SymCreate([esi].eqitem.name)
        mov [eax].asym.state,SYM_INTERNAL
        or  [eax].asym.flag,S_ISDEFINED or S_PREDEFINED
        mov ecx,[esi].eqitem.value
        mov [eax].asym._offset,ecx
        mov ecx,[esi].eqitem.sfunc_ptr
        mov [eax].asym.sfunc_ptr,ecx
        mov ecx,[esi].eqitem.store
        add esi,eqitem
        .continue .if !ecx
        mov [ecx],eax
    .endw
    ;
    ; @WordSize should not be listed
    ;
    and [eax].asym.flag,not S_LIST

    xor esi,esi
    .while esi < dyneqcount
        SymCreate(dyneqtable[esi*4])
if 0
        mov [eax].asym.state,SYM_INTERNAL
        or  [eax].asym.flag,S_ISDEFINED or S_ISEQUATE or S_VARIABLE
else
        mov [eax].asym.state,SYM_TMACRO
        or  [eax].asym.flag,S_ISDEFINED or S_PREDEFINED
endif
        mov ecx,dyneqvalue[esi*4]
        ;mov [eax].asym._offset,ecx
        mov [eax].asym.string_ptr,ecx
        mov [eax].asym.sfunc_ptr,0
        inc esi
    .endw
    ;
    ; $ is an address (usually). Also, don't add it to the list
    ;
    mov eax,symPC
    and [eax].asym.flag,not S_LIST
    or  [eax].asym.flag,S_VARIABLE
    mov eax,LineCur
    and [eax].asym.flag,not S_LIST
    ret

SymInit endp

SymPassInit proc pass:int_t

    .if pass != PASS_1

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

                mov eax,gsym_table[ecx*4]
                .while eax
                    .if !([eax].asym.flag & S_PREDEFINED)
                        and [eax].asym.flag,not S_ISDEFINED
                    .endif
                    mov eax,[eax].asym.nextitem
                .endw

                add ecx,1
            .until  ecx == GHASH_TABLE_SIZE
        .endif
    .endif
    ret

SymPassInit endp

; get all symbols in global hash table

SymGetAll proc syms:asym_t

    xor ecx,ecx
    mov edx,syms
    ;
    ; copy symbols to table
    ;
    .repeat
        mov eax,gsym_table[ecx*4]
        .while eax
            mov [edx],eax
            add edx,4
            mov eax,[eax].asym.nextitem
        .endw
        add ecx,1
    .until ecx == GHASH_TABLE_SIZE
    ret

SymGetAll endp

; enum symbols in global hash table.
; used for codeview symbolic debug output.
SymEnum proc sym:asym_t, pi:ptr int_t
    mov edx,pi
    mov eax,sym
    .if eax
        mov eax,[eax].asym.nextitem
        mov ecx,[edx]
    .else
        xor ecx,ecx
        mov [edx],ecx
        mov eax,gsym_table
    .endif
    .while !eax && ecx < GHASH_TABLE_SIZE - 1
        add ecx,1
        mov [edx],ecx
        mov eax,gsym_table[ecx*4]
    .endw
    ret
SymEnum endp

;
; add a new node to a queue
;
AddPublicData proc fastcall sym:asym_t

    mov edx,sym
    lea ecx,ModuleInfo.PubQueue

AddPublicData endp

QAddItem proc fastcall q:qdesc_t, d:ptr

    push ecx
    push edx
    LclAlloc(qnode)
    pop edx
    pop ecx
    mov [eax].qnode.elmt,edx
    mov edx,eax

QAddItem endp

QEnqueue proc fastcall q:qdesc_t, item:ptr

    xor eax,eax
    .if eax == [ecx].qdesc.head
        mov [ecx].qdesc.head,edx
        mov [ecx].qdesc.tail,edx
        mov [edx],eax
    .else
        mov eax,[ecx].qdesc.tail
        mov [ecx].qdesc.tail,edx
        mov [eax],edx
        xor eax,eax
        mov [edx],eax
    .endif
    ret

QEnqueue endp

    end
