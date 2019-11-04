include windows.inc
include objbase.inc
include intrin.inc
include stdio.inc
include IConfig.inc
include locals.inc

.comdef CIClassFactory

    ref_count       dd ?

    QueryInterface  proc :REFIID, :ptr
    AddRef          proc
    Release         proc

    CreateInstance  proc :ptr, :REFIID, :ptr
    LockServer      proc :BOOL

    .ends


_I_BASE             equ 0x01
_I_SECTION          equ 0x02
_I_ENTRY            equ 0x04
_I_COMMENT          equ 0x08


.comdef CIConfig

    count           uint_t ?
    flags           uint_t ?
    name            string_t ?
    union
      value         string_t ?
      list          ptr_t ?
    ends
    next            ptr_t ?
    Compare         proc local :string_t, :string_t

    QueryInterface  proc :REFIID, :ptr
    AddRef          proc
    Release         proc

    read            proc :string_t
    write           proc :string_t
    find            proc :string_t
    create          proc :string_t, :vararg
    getvalue        proc :string_t, :string_t
    delete          proc :string_t
    new             proc
    unlink          proc :ptr_t

    .ends


    .data

    IID_IUnknown    IID _IID_IUnknown
    IID_IConfig     IID _IID_IConfig
    CLSID_IConfig   IID _CLSID_IConfig
    IID_IClassFactory IID _IID_IClassFactory

    ClassFactoryVtbl CIClassFactoryVtbl { \
        CIClassFactory_QueryInterface,
        CIClassFactory_AddRef,
        CIClassFactory_Release,
        CIClassFactory_CreateInstance,
        CIClassFactory_LockServer }

    ConfigVtbl CIConfigVtbl { \
        CIConfig_QueryInterface,
        CIConfig_AddRef,
        CIConfig_Release,
        CIConfig_read,
        CIConfig_write,
        CIConfig_find,
        CIConfig_create,
        CIConfig_getvalue,
        CIConfig_delete,
        CIConfig_new,
        CIConfig_unlink }

    Config CIConfig { ConfigVtbl, 0, }
    ClassFactory CIClassFactory { ClassFactoryVtbl, 0 }
    OutstandingObjects int_t 0
    LockCount int_t 0

    .code

    assume rcx:ptr CIConfig

CIConfig::QueryInterface proc riid:LPIID, ppv:ptr ptr

    mov rax,[rdx]
    mov rdx,[rdx+8]
    .if rax == qword ptr IID_IUnknown
        cmp rdx,qword ptr IID_IUnknown[8]
    .endif
    .ifnz
        .if rax == qword ptr IID_IConfig
            cmp rdx,qword ptr IID_IConfig[8]
        .endif
    .endif
    .ifz
        mov [r8],rcx
        [rcx].AddRef()
        mov eax,NOERROR
    .else
        xor eax,eax
        mov [r8],rax
        mov eax,E_NOINTERFACE
    .endif
    ret

CIConfig::QueryInterface endp


CIConfig::AddRef proc

    inc [rcx].count
    mov eax,[rcx].count
    ret

CIConfig::AddRef endp


    assume rbx:ptr CIConfig

CIConfig::Release proc uses rbx

    dec [rcx].count
    .ifz

        mov rbx,rcx
        _InterlockedDecrement(&OutstandingObjects)

        .while rbx
            free([rbx].name)
            .if [rbx].flags & _I_SECTION
                mov rcx,[rbx].list
                .if rcx
                    [rcx].Release()
                .endif
            .endif
            mov rcx,rbx
            mov rbx,[rbx].next
            free(rcx)
        .endw

        xor eax,eax
    .else
        mov eax,[rcx].count
    .endif
    ret

CIConfig::Release endp


TruncateString proc private string:LPSTR

    .repeat

        mov al,[rcx]
        inc rcx

        .continue(0) .if al == ' '
        .continue(0) .if al == 9
        .continue(0) .if al == 10
        .continue(0) .if al == 13
    .until 1
    dec rcx

    mov rdx,rcx
    xor eax,eax
    .while [rcx] != al

        inc rcx
    .endw

    .repeat

        .break .if rcx <= rdx

        dec rcx
        mov al,[rcx]
        mov [rcx],ah

        .continue(0) .if al == ' '
        .continue(0) .if al == 9
        .continue(0) .if al == 10
        .continue(0) .if al == 13

        mov [rcx],al
        inc rcx

    .until 1

    sub rcx,rdx
    mov rax,rcx
    ret

TruncateString endp


CIConfig::read proc uses rsi rdi rbx r12 file:string_t

  local fp:LPFILE, buffer[256]:sbyte

    mov r12,rcx
    mov rbx,rcx
    mov rcx,rdx
    .if fopen(rcx, "rt")

        .for ( rdi = rax, rsi = &buffer : fgets(rsi, 256, rdi) : )

            .continue .ifd !TruncateString(rsi)

            .if byte ptr [rdx] == '['

                .if strchr(rsi, ']')

                    mov byte ptr [rax],0
                    .break .if ![rbx].create(&[rsi+1])
                    mov rbx,rax
                .endif
            .else
                [rbx].create(rdx)
            .endif
        .endf
        fclose(rdi)
        mov rax,r12
    .endif
    ret

CIConfig::read endp


CIConfig::write proc uses rsi rdi rbx file:string_t

    mov rbx,rcx
    mov rcx,rdx
    .if fopen(rcx, "wt")

        .for ( rdi = rax : rbx : rbx = [rbx].next )

            .if [rbx].flags & _I_SECTION

                fprintf(rdi, "\n[%s]\n", [rbx].name)
            .endif

            .for ( rsi=[rbx].list : rsi : rsi=[rsi].CIConfig.next )

                mov r8,[rsi].CIConfig.name
                mov eax,[rsi].CIConfig.flags
                .if eax & _I_ENTRY

                    fprintf(rdi, "%s=%s\n", r8, [rsi].CIConfig.value)
                .elseif eax & _I_COMMENT
                    fprintf(rdi, "%s\n", r8)
                .else
                    fprintf(rdi, ";%s\n", r8)
                .endif
            .endf
        .endf
        fclose(rdi)
        mov eax,1
    .endif
    ret
CIConfig::write endp


CIConfig::find proc uses rsi rdi rbx string:string_t

    xor edi,edi
    mov rsi,rdx
    xor eax,eax

    .while rcx

        .if ( [rcx].flags & ( _I_SECTION or _I_ENTRY ) )

            mov rbx,rcx
            .if !( [rbx].Compare([rbx].name, rsi) )

                mov rdx,rdi
                mov rcx,rbx
                mov rax,rbx
                .break
            .endif
            xor eax,eax
            mov rcx,rbx
        .endif
        mov rdi,rcx
        mov rcx,[rcx].next
    .endw
    ret

CIConfig::find endp


CIConfig::getvalue proc uses rsi rdi rbx Section:string_t, Entry:string_t

    mov rbx,rcx
    mov rsi,rdx
    mov rdi,r8

    .if [rbx].find(rdx)

        mov rax,[rcx].list
        .if rax

            [rax].CIConfig.find(rdi)
        .endif
    .endif
    ret

CIConfig::getvalue endp


CIConfig::create proc uses rsi rdi rbx r12 format:string_t, argptr:vararg

 local string[256]:sbyte

    mov rbx,rcx
    lea rdi,string

    .repeat

        .break .ifd !vsprintf(rdi, rdx, &argptr)
        .break .ifd !TruncateString(rdi)

        xor esi,esi
        mov rdi,rdx

        .if byte ptr [rdx] != ';'

            mov al,'='
            repnz scasb
            .ifz
                mov rsi,rdi
                mov byte ptr [rdi-1],0
                mov rdi,rdx
                TruncateString(rsi)
                TruncateString(rdi)
                mov rdx,rdi
            .endif
            mov rdi,rdx
        .endif

        .break .if [rbx].find(rdx)
        .break .if ![rbx].new()

        mov ecx,_I_SECTION
        .if esi
            mov byte ptr [rsi-1],'='
            mov ecx,_I_ENTRY
        .elseif byte ptr [rdi] == ';'
            mov ecx,_I_COMMENT
        .endif
        mov [rax].CIConfig.flags,ecx

        mov r12,rdi
        mov rdi,rax

        .break .if !malloc( &[ strlen( r12 ) + 1 ] )
        mov [rdi].CIConfig.name,strcpy( rax, r12 )

        mov rax,[rbx].next
        .if esi && [rbx].flags & _I_SECTION

            mov rax,[rbx].list
            .if !rax

                mov [rbx].list,rdi
                xor rbx,rbx
            .endif
        .endif

        .while rax

            mov rbx,rax
            mov rax,[rbx].next
        .endw

        .if rbx

            mov [rbx].next,rdi
        .endif

        mov rbx,rdi
        .if esi

            .if strchr([rbx].name, '=')

                mov byte ptr [rax],0
                inc rax
                mov [rbx].value,rax
            .endif
        .endif

        mov rax,rdi
    .until 1
    mov rcx,rax
    ret

CIConfig::create endp


CIConfig::new proc

    .return .if !malloc(CIConfig)

    mov rcx,rax
    mov [rcx].count,1
    lea rax,ConfigVtbl
    mov [rcx].lpVtbl,rax
    xor eax,eax
    mov [rcx].next,rax
    mov [rcx].name,rax
    mov [rcx].list,rax
    mov [rcx].flags,eax
    lea rax,strcmp
    mov [rcx].Compare,rax
    mov rax,rcx
    ret

CIConfig::new endp


CIConfig::delete proc SectionName:string_t

    .if [rcx].find(rdx)

        .if rdx

            [rax].CIConfig.unlink(rdx)
        .endif
    .endif
    ret

CIConfig::delete endp


CIConfig::unlink proc Parent:ptr

    mov rax,[rcx].next
    mov [rdx].CIConfig.next,rax
    xor eax,eax
    mov [rcx].next,rax
    [rcx].Release()
    ret

CIConfig::unlink endp


    assume rbx:nothing
    assume rcx:ptr CIClassFactory

CIClassFactory::QueryInterface proc riid:LPIID, ppv:ptr ptr

    mov rax,[rdx]
    mov rdx,[rdx+8]
    .if rax == qword ptr IID_IUnknown
        cmp rdx,qword ptr IID_IUnknown[8]
    .endif
    .ifnz
        .if rax == qword ptr IID_IClassFactory
            cmp rdx,qword ptr IID_IClassFactory[8]
        .endif
    .endif
    .ifz

        mov [r8],rcx
        [rcx].AddRef()
        mov eax,NOERROR

    .else

        xor eax,eax
        mov [r8],rax
        mov eax,E_NOINTERFACE
    .endif
    ret

CIClassFactory::QueryInterface endp


CIClassFactory::AddRef proc

    _InterlockedIncrement(&OutstandingObjects)
    ret

CIClassFactory::AddRef endp


CIClassFactory::Release proc

    _InterlockedDecrement(&OutstandingObjects)
    ret

CIClassFactory::Release endp


CIClassFactory::CreateInstance proc uses rdi rdi Unknown:ptr IUnknown, riid:REFIID, ppv:ptr

    xor eax,eax
    mov [r9],rax

    .if rdx

        mov eax,CLASS_E_NOAGGREGATION
    .else

        .if !malloc(sizeof(CIConfig))

            mov eax,E_OUTOFMEMORY
        .else

            assume rsi:ptr CIConfig
            mov rsi,rax
            lea rax,ConfigVtbl
            mov [rsi].lpVtbl,rax
            mov [rsi].count,1
            xor eax,eax
            mov [rsi].next,rax
            mov [rsi].name,rax
            mov [rsi].list,rax
            mov [rsi].flags,eax
            lea rax,strcmp
            mov [rsi].Compare,rax
            mov edi,[rsi].QueryInterface(riid, ppv)
            [rsi].Release()
            .if !edi

                _InterlockedIncrement(&OutstandingObjects)
            .endif
            assume rsi:nothing
            mov eax,edi
        .endif
    .endif
    ret

CIClassFactory::CreateInstance endp


CIClassFactory::LockServer proc flock:BOOL

    .if edx
        _InterlockedIncrement(&LockCount)
    .else
        _InterlockedDecrement(&LockCount)
    .endif

    mov eax,NOERROR
    ret

CIClassFactory::LockServer endp


    option win64:rsp nosave noauto

DllGetClassObject proc export frame rclsid:REFCLSID, riid:REFIID, ppv:ptr ptr

    mov rax,[rcx]
    mov rcx,[rcx+8]
    .if rax == qword ptr CLSID_IConfig
        cmp rcx,qword ptr CLSID_IConfig[8]
    .endif
    .ifz
        CIClassFactory::QueryInterface(&ClassFactory, rdx, r8)
    .else
        xor eax,eax
        mov [r8],rax
        mov eax,CLASS_E_CLASSNOTAVAILABLE
    .endif
    ret

DllGetClassObject endp


DllCanUnloadNow proc export

    mov eax,OutstandingObjects
    or  eax,LockCount
    .if eax
        mov eax,S_FALSE
    .else
        mov eax,S_OK
    .endif
    ret

DllCanUnloadNow endp


DllMain proc frame hinstDLL:HINSTANCE, fdwReason:DWORD, lpvReserved:LPVOID

    .if edx == DLL_PROCESS_ATTACH

        DisableThreadLibraryCalls(rcx)
    .endif
    mov eax,TRUE
    ret

DllMain endp

    end DllMain
