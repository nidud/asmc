; CPUMODEL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: processes .MODEL and cpu directives
;

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include assume.inc
include tokenize.inc
include expreval.inc
include fastpass.inc
include listing.inc
include proc.inc
include macro.inc
include fixup.inc
include lqueue.inc
include bin.inc

define DOT_XMMARG 0 ;; 1=optional argument for .XMM directive

public sym_Cpu
public sym_Interface

.data

sym_Interface   asym_t 0 ; numeric. requires model
sym_Cpu         asym_t 0 ; numeric. This is ALWAYS set

coff64_fmtopt format_options { NULL, COFF64_DISALLOWED, "PE32+" }
elf64_fmtopt  format_options { NULL, ELF64_DISALLOWED,  "ELF64" }

ifndef ASMC64

extern szDgroup:char_t

;; prototypes

;; the following flags assume the MODEL_xxx enumeration.
;; must be sorted like MODEL_xxx enum:
;; TINY=1, SMALL=2, COMPACT=3, MEDIUM=4, LARGE=5, HUGE=6, FLAT=7

ModelToken string_t \
    @CStr("TINY"),
    @CStr("SMALL"),
    @CStr("COMPACT"),
    @CStr("MEDIUM"),
    @CStr("LARGE"),
    @CStr("HUGE"),
    @CStr("FLAT")

define INIT_LANG       0x1
define INIT_STACK      0x2
define INIT_OS         0x4

.template typeinfo
    value db ? ; value assigned to the token
    init  db ? ; kind of token
   .ends


ModelAttr string_t \
    @CStr("NEARSTACK"),
    @CStr("FARSTACK"),
    @CStr("OS_DOS"),
    @CStr("OS_OS2")

ModelAttrValue typeinfo \
    { STACK_NEAR,     INIT_STACK      },
    { STACK_FAR,      INIT_STACK      },
    { OPSYS_DOS,      INIT_OS         },
    { OPSYS_OS2,      INIT_OS         }


sym_CodeSize  asym_t 0 ; numeric. requires model
sym_DataSize  asym_t 0 ; numeric. requires model
sym_Model     asym_t 0 ; numeric. requires model

endif

.code

AddPredefinedConstant proc fastcall private name:string_t, value:int_t
    .if CreateVariable( rcx, edx )
        mov [rax].asym.predefined,1
    .endif
    ret
    endp

ifndef ASMC64

;; set default wordsize for segment definitions

SetDefaultOfssize proc fastcall private size:int_t
    ;
    ; outside any segments?
    ;
    .if ( CurrSeg == NULL )
        mov MODULE.defOfssize,cl
    .endif
    .return( SetOfssize() )
    endp

; set memory model, called by ModelDirective()
; also set predefined symbols:
; - @CodeSize  (numeric)
; - @code      (text)
; - @DataSize  (numeric)
; - @data      (text)
; - @stack     (text)
; - @Model     (numeric)
; - @Interface (numeric)
; inactive:
; - @fardata   (text)
; - @fardata?  (text)
; Win64 only:
; - @ReservedStack (numeric)

SetModel proc __ccall private uses rsi rdi rbx

    ;; if model is set, it disables OT_SEGMENT of -Zm switch

    .if ( MODULE._model == MODEL_FLAT )

        mov MODULE.offsettype,OT_FLAT
        mov esi,GetCurrCpu()
        mov eax,USE32
        .if ( esi & P_64 )
            mov eax,USE64
        .endif
        SetDefaultOfssize( eax )

        ;; v2.03: if cpu is x64 and language is fastcall,
        ;; set fastcall type to win64.
        ;; This is rather hackish, but currently there's no other possibility
        ;; to enable the win64 ABI from the source.

        mov al,MODULE.langtype
        mov cl,MODULE.fctype
        .if ( esi & P_64 )

            .if ( al == LANG_NONE )
ifdef __UNIX__
                mov al,LANG_SYSCALL
else
                mov al,LANG_FASTCALL
endif
            .endif
            .if ( Options.sub_format == SFORMAT_NONE )
                mov Options.sub_format,SFORMAT_64BIT
            .endif
            .if ( Options.output_format == OFORMAT_OMF )
                .if ( al == LANG_SYSCALL )
                    mov Options.output_format,OFORMAT_ELF
                .else
                    mov Options.output_format,OFORMAT_COFF
                .endif
            .endif
            .if ( al == LANG_FASTCALL || al == LANG_SYSCALL || al == LANG_VECTORCALL )

                .if ( al == LANG_VECTORCALL )
                    mov cl,FCT_VEC64
                .elseif ( Options.output_format != OFORMAT_ELF )
                    mov cl,FCT_WIN64
                .else
                    mov cl,FCT_ELF64
                .endif
            .endif
        .elseif ( al == LANG_VECTORCALL )
            mov cl,FCT_VEC32
        .endif
        mov MODULE.fctype,cl

        ;; v2.11: define symbol FLAT - after default offset size has been set!
        DefineFlatGroup()
    .else
        mov MODULE.offsettype,OT_GROUP
    .endif

    ModelSimSegmInit( MODULE._model ) ;; create segments in first pass
    ModelAssumeInit()
    .if ( MODULE.list )
        LstWriteSrcLine()
    .endif
    RunLineQueue()
    .return .if ( Parse_Pass != PASS_1 )

    ;; Set @CodeSize
    mov eax,1
    mov cl,MODULE._model
    shl eax,cl
    and eax,SIZE_CODEPTR
    setnz al
    mov sym_CodeSize,AddPredefinedConstant( "@CodeSize", eax )
    AddPredefinedText( "@code", SimGetSegName( SIM_CODE ) )

    ;; Set @DataSize
    mov cl,MODULE._model
    xor eax,eax
    .switch cl
    .case MODEL_COMPACT
    .case MODEL_LARGE
        mov eax,1
        .endc
    .case MODEL_HUGE
        mov eax,2
        .endc
    .endsw
    mov sym_DataSize,AddPredefinedConstant( "@DataSize", eax )
    lea rsi,szDgroup
    .if ( MODULE._model == MODEL_FLAT )
        lea rsi,@CStr("FLAT")
    .endif
    AddPredefinedText( "@data", rsi )
    .if ( MODULE.distance == STACK_FAR )
        lea rsi,@CStr("STACK")
    .endif
    AddPredefinedText( "@stack", rsi )

    ;; Set @Model and @Interface
    mov sym_Model,     AddPredefinedConstant( "@Model", MODULE._model )
    mov sym_Interface, AddPredefinedConstant( "@Interface", MODULE.langtype )
    .if ( MODULE.defOfssize == USE64 &&
         ( MODULE.fctype == FCT_WIN64 ||
           MODULE.fctype == FCT_VEC64 ||
           MODULE.fctype == FCT_ELF64 ) ) ; v2.28: added
        mov sym_ReservedStack,AddPredefinedConstant( "@ReservedStack", 0 )
    .endif
    .if ( MODULE.sub_format == SFORMAT_PE ||
         ( MODULE.sub_format == SFORMAT_64BIT &&
           Options.output_format == OFORMAT_BIN ) )
        pe_create_PE_header()
    .endif
    ret
    endp


; handle .model directive
; syntax: .MODEL <FLAT|TINY|SMALL...> [,<C|PASCAL|STDCALL...>][,<NEARSTACK|FARSTACK>][,<OS_DOS|OS_OS2>]
; sets fields
; - ModuleInfo.model
; - ModuleInfo.language
; - ModuleInfo.distance
; - ModuleInfo.ostype
; if model is FLAT, defines FLAT pseudo-group
; set default segment names for code and data

    assume rbx:token_t

ModelDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local distance:byte
  local language:byte
  local ostype:byte
  local init:byte

    ; v2.03: it may occur that "code" is defined BEFORE the MODEL
    ; directive (i.e. DB directives in AT-segments). For FASTPASS,
    ; this may have caused errors because contents of the ModuleInfo
    ; structure was saved before the .MODEL directive.

    .if ( Parse_Pass != PASS_1 && MODULE._model != MODEL_NONE )

        ; just set the model with SetModel() if pass is != 1.
        ; This won't set the language ( which can be modified by
        ; OPTION LANGUAGE directive ), but the language in ModuleInfo
        ; isn't needed anymore once pass one is done.

        SetModel()
       .return( NOT_ERROR )
    .endif

    inc i
    imul ebx,i,asm_tok
    add rbx,tokenarray
    .if ( [rbx].token == T_FINAL )
        .return( asmerr( 2013 ) )
    .endif
    mov edi,i
    xor esi,esi

    ; get the model argument

    FindToken( [rbx].string_ptr, &ModelToken, lengthof( ModelToken ) )
    .ifs ( eax >= 0 )
        lea esi,[rax+1] ; model is one-base ( 0 is MODEL_NONE )
        add rbx,asm_tok
        inc edi
        .if ( MODULE._model != MODEL_NONE )
            asmerr( 4011 )
        .endif
    .else
        .return( asmerr(2008, [rbx].string_ptr ) )
    .endif

    ;; get the optional arguments: language, stack distance, os

    mov init,0
    .while ( [rbx].token == T_COMMA )
        .break .if edi >= TokenCount
        inc edi
        add rbx,asm_tok
        .if ( [rbx].token != T_COMMA )
            mov i,0
            .ifd ( GetLangType( &i, rbx, &language ) == NOT_ERROR )
                inc edi
                add rbx,asm_tok
                mov cl,INIT_LANG
            .else
                FindToken( [rbx].string_ptr, &ModelAttr, lengthof( ModelToken ) )
                .break .ifs ( eax < 0 )
                lea rdx,ModelAttrValue
                mov cl,[rdx+rax*2].typeinfo.init
                mov al,[rdx+rax*2].typeinfo.value
                .if cl == INIT_STACK
                    .if ( esi == MODEL_FLAT )
                        .return( asmerr( 2178 ) )
                    .endif
                    mov distance,al
                .elseif cl == INIT_OS
                    mov ostype,al
                .endif
                inc edi
                add rbx,asm_tok
            .endif
            ;
            ; attribute set already?
            ;
            .if ( cl & init )
                dec edi
                sub rbx,asm_tok
               .break
            .endif
            or init,cl
        .endif
    .endw

    ;; everything parsed successfully?

    .if ( [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].tokpos ) )
    .endif
    .if ( esi == MODEL_FLAT )
        .ifd ( GetCurrCpu() < P_386 )
            .return( asmerr( 2085 ) )
        .endif
        .if ( CurrCpu.x64 ) ;; cpu 64-bit?
            .if ( Options.output_format == OFORMAT_COFF )
                mov MODULE.fmtopt,&coff64_fmtopt
            .elseif ( Options.output_format == OFORMAT_ELF )
                mov MODULE.fmtopt,&elf64_fmtopt
            .endif
        .endif
    .endif
    mov eax,esi
    mov MODULE._model,al
    mov cl,init
    .if ( cl & INIT_LANG )
        mov MODULE.langtype,language
    .endif
    .if ( cl & INIT_STACK )
        mov MODULE.distance,distance
    .endif
    .if ( cl & INIT_OS )
        mov MODULE.ostype,ostype
    .endif
    SetModelDefaultSegNames()
    SetModel()
    .return( NOT_ERROR )
    endp

endif

; set CPU and FPU parameter in ModuleInfo.cpu + ModuleInfo.curr_cpu.
; ModuleInfo.cpu is the value of Masm's @CPU symbol.
; ModuleInfo.curr_cpu is the old OW Wasm value.
; additional notes:
; .[1|2|3|4|5|6]86 will reset .MMX, .K3D and .XMM,
; OTOH, .MMX/.XMM won't automatically enable .586/.686 ( Masm does! )


SetCPU proc __ccall newcpu:CPU

    ldr cl,newcpu

    mov edx,GetCpuExtensions(cl)
    GetCpu(cl)

    .if ( cl == P_86 || ( eax && !edx ) )

        ;; reset CPU and EXT bits

        SetCurrCpu(eax)
        mov CurrCpu.Pm,0

        ;; set CPU bits

        mov al,cl
        and al,P_PM
        or CurrCpu,al

        ;; set default FPU bits if nothing is given and .NO87 not active

        .if ( !Options.no_cpu && !( cl & P_FPU_MASK ) )
            mov CurrCpu.Fpu,1
        .endif
    .endif

    ;; enable MMX, K3D, SSEx for 64bit cpus

    .if ( cl & P_64 )
        SetCurrCpu(P_64 or P_EXT_ALL)
    .endif
    .if ( edx )
        SetCurrCpuExtensions( edx )
    .endif

    ;; set the Masm compatible @Cpu value

ifndef ASMC64

    mov ecx,GetCurrCpu()
    .switch ecx
    .case P_186
        mov eax,M_8086 or M_186
       .endc
    .case P_286
        mov eax,M_8086 or M_186 or M_286
       .endc
    .case P_386
        mov eax,M_8086 or M_186 or M_286 or M_386
       .endc
    .case P_486
        mov eax,M_8086 or M_186 or M_286 or M_386 or M_486
       .endc
    .case P_586
        mov eax,M_8086 or M_186 or M_286 or M_386 or M_486 or M_586
       .endc
    .case P_64
    .case P_686
        mov eax,M_8086 or M_186 or M_286 or M_386 or M_486 or M_686
       .endc
    .default
        mov eax,M_8086
       .endc
    .endsw
    .if ( CurrCpu.Pm )
        or eax,M_PROT
    .endif
    .if ( CurrCpu.Fpu )
        mov edx,ecx
        .if ( edx > P_386 )
            mov edx,P_386
        .endif
        .switch edx
        .case P_86
            or eax,M_8087
           .endc
        .case P_286
            or eax,M_8087 or M_287
           .endc
        .case P_386
            or eax,M_8087 or M_287 or M_387
           .endc
        .endsw
    .endif
    mov MODULE.cpu,eax
    .if ( MODULE._model == MODEL_NONE )
        .if ( ecx & P_64 )
            mov eax,USE64
        .else
            mov eax,USE16
            .if ( ecx >= P_386)
                mov eax,USE32
            .endif
        .endif
        SetDefaultOfssize( eax )
    .endif

    ; Set @Cpu
    ; differs from Codeinfo cpu setting

    mov sym_Cpu,CreateVariable( "@Cpu", MODULE.cpu )

else

    mov edx,M_8086 or M_186 or M_286 or M_386 or M_486 or M_686
    .if ( CurrCpu.Pm )
        or edx,M_PROT
    .endif

    or edx,M_8087 or M_287 or M_387
    mov MODULE._model,MODEL_FLAT
    mov MODULE.cpu,edx

    ;; Set @Cpu
    ;; differs from Codeinfo cpu setting
    mov sym_Cpu,CreateVariable( "@Cpu", edx )

    .if ( Options.output_format == OFORMAT_ELF )
        lea rax,elf64_fmtopt
    .else
        lea rax,coff64_fmtopt
    .endif
    mov MODULE.fmtopt,rax
    SetModelDefaultSegNames()
    mov MODULE.offsettype,OT_FLAT
    .if ( CurrSeg == NULL )
        mov MODULE.defOfssize,USE64
    .endif
    SetOfssize()

    .if ( MODULE.langtype == LANG_VECTORCALL )
        mov al,FCT_VEC64
    .elseif ( Options.output_format != OFORMAT_ELF )
        mov al,FCT_WIN64
    .else
        mov al,FCT_ELF64
    .endif
    mov MODULE.fctype,al
    DefineFlatGroup()
    ModelSimSegmInit( MODULE._model ) ;; create segments in first pass
    ModelAssumeInit()
    .if ( MODULE.list )
        LstWriteSrcLine()
    .endif
    .if ( Parse_Pass != PASS_1 )
        .return( NOT_ERROR )
    .endif

    AddPredefinedConstant( "@CodeSize", 0 )
    AddPredefinedText( "@code", SimGetSegName( SIM_CODE ) )
    AddPredefinedConstant( "@DataSize", 0 )
    AddPredefinedText( "@data",  "FLAT" )
    AddPredefinedText( "@stack", "FLAT" )

    ;; Set @Model and @Interface

    AddPredefinedConstant( "@Model", MODULE._model );
    mov sym_Interface,AddPredefinedConstant( "@Interface", MODULE.langtype )
    mov al,MODULE.fctype
    .if ( al == FCT_WIN64 || al == FCT_VEC64  || al == FCT_ELF64 ) ;; v2.28: added
        mov sym_ReservedStack,AddPredefinedConstant( "@ReservedStack", 0 )
    .endif
    .if ( MODULE.sub_format == SFORMAT_PE ||
        ( MODULE.sub_format == SFORMAT_64BIT && Options.output_format == OFORMAT_BIN ) )
        pe_create_PE_header()
    .endif
endif
    .return( NOT_ERROR )
    endp

ifndef ASMC64

; handles
; .8086,
; .[1|2|3|4|5|6]86[p],
; .8087,
; .[2|3]87,
; .NO87, .MMX, .K3D, .XMM directives.

CpuDirective proc __ccall uses rbx i:int_t, tokenarray:token_t
    imul ebx,i,asm_tok
    add rbx,tokenarray
    mov edx,GetSflagsSp( [rbx].tokval )
    add rbx,asm_tok
    .if ( [rbx].token != T_FINAL )
        .return( asmerr(2008, [rbx].tokpos ) )
    .endif
    .return( SetCPU( dl ) )
    endp

endif
    end
