; CPUMODEL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef _CPUMODEL_
define _CPUMODEL_

define P_64         0x80 ; x64 cpu
define P_PM         0x40 ; privileged opcode
define P_FPU        0x20 ; CPU <= 386
define P_EXT        0x10 ; CPU <= 686

define P_NO87       0x00 ; no FPU --> Options.no_cpu
define P_87         0x20 ; 8087
define P_287        0x22 ; 80287
define P_387        0x23 ; 80387

define P_86         0x00 ; 8086, default
define P_186        0x01 ; 80186
define P_286        0x02 ; 80286
define P_386        0x03 ; 80386
define P_486        0x04 ; 80486
define P_586        0x05 ; pentium
define P_686        0x06 ; ppro

define P_286p       0x42 ; 286, priv mode
define P_386p       0x43 ; 386, priv mode
define P_486p       0x44 ; 486, priv mode
define P_586p       0x45 ; 586, priv mode
define P_686p       0x46 ; 686, priv mode
define P_64p        0xC0 ; x64, priv mode

define P_MMX        0x10 ; MMX extension instructions
define P_K3D        0x11 ; 3DNow extension instructions
define P_SSE1       0x12 ; SSE1 extension instructions
define P_SSE2       0x13 ; SSE2 extension instructions
define P_SSE3       0x14 ; SSE3 extension instructions
define P_SSSE3      0x15 ; SSSE3 extension instructions

define P_SSE4       0x16 ; SSE4 extension instructions
define P_SSE41      0x16 ; SSE4.1 extension instructions
define P_SSE42      0x16 ; SSE4.2 extension instructions
define P_CRC32      0x16 ; SSE4.2
define P_POPCNT     0x16 ; SSE4.2
define P_AESNI      0x16 ; SSE4.2

define P_AVX        0x17 ; AVX extension instructions
define P_F16C       0x17 ; AVX
define P_RDRAND     0x17 ; AVX

define P_AVX2       0x18 ; AVX-2 extension instructions
define P_FMA        0x18 ; AVX-2
define P_BMI1       0x18 ; AVX-2
define P_BMI2       0x18 ; AVX-2
define P_INVPCID    0x18 ; AVX-2
define P_LZCNT      0x18 ; AVX-2
define P_TSX        0x18 ; AVX-2
define P_MOVBE      0x18 ; AVX-2
define P_PREFETCHW  0x18 ; AVX-2
define P_ADX        0x18 ; AVX-2
define P_RDSEED     0x18 ; AVX-2
define P_CLAC       0x18 ; AVX-2
define P_STAC       0x18 ; AVX-2

define P_AVX512     0x19
define P_AVX512F    0x19 ; Foundation
define P_AVX512CD   0x19 ; Conflict Detection
define P_AVX512BW   0x19 ; BYTE/WORD extension
define P_AVX512DQ   0x19 ; DWORD/QWORD extension
define P_AVX512VL   0x19 ; Vector Length extension
define P_IFMA       0x19 ; Integer Fused Multiply-Add using 52-bit precision
define P_VBMI       0x19 ;
define P_SHANI      0x19 ; SHA Extensions (Intel SHA-NI)
define P_GFNI       0x19 ; Galois Field New Instructions (SSE)
define P_VBMI2      0x19 ;
define P_BF16       0x19 ; Native hardware support for REAL2
define P_VAES       0x1A ; Vector implementations of the AES encryption
define P_VNNI       0x1B ; Vector Neural Network Instructions
define P_AMX        0x1B ; Advanced Matrix Extensions (2023)
define P_AVX10      0x1C ; Advanced Vector Extensions 10
define P_APX        0x1D ;

define P_FPU_MASK   0x20
define P_CPU_MASK   0x1F
define P_EXT_ALL    P_APX

; option -0..10

.enum cpu_type {
    CPU_86                  ;  0  __P86__
    CPU_186,                ;  1  __P186__
    CPU_286,                ;  2  __P286__
    CPU_386,                ;  3  __P386__
    CPU_486,                ;  4  __P486__
    CPU_586,                ;  5  __P586__
    CPU_686,                ;  6  __P686__
    CPU_MMX,                ;  7  __P686__
    CPU_SSE,                ;  8  __SSE__
    CPU_SSE2,               ;  9  __SSE2__
    CPU_64                  ; 10  __P64__
    }


; option -arch:[IA32|SSE|SSE2|AVX|AVX2|AVX512]

.enum cpu_architecture {
    ARCH_IX86_FP,           ; 0  _M_IX86_FP
    ARCH_SSE,               ; 1  __SSE__
    ARCH_SSE2,              ; 2  __SSE2__
    ARCH_AVX,               ; 3  __AVX__
    ARCH_AVX2,              ; 4  __AVX2__
    ARCH_AVX512             ; 5  __AVX512F__, __AVX512CD__, __AVX512BW__,
    }                       ;    __AVX512DQ__ and __AVX512VL__


; the MASM compatible @CPU value flags:

.enum masm_cpu {
    M_8086      = 0x0001,   ; 8086
    M_186       = 0x0002,   ; 186
    M_286       = 0x0004,   ; 286
    M_386       = 0x0008,   ; 386
    M_486       = 0x0010,   ; 486
    M_586       = 0x0020,   ; Pentium
    M_686       = 0x0040,   ; PPro
    M_CPUMSK    = 0x007F,
    M_PROT      = 0x0080,   ; protected instructions ok
    M_8087      = 0x0100,   ; 8087
    M_287       = 0x0400,   ; 287
    M_387       = 0x0800    ; 387
    }


.template CPU
    record
     Cpu    db : 5 ?
     Fpu    db : 1 ?
     Pm     db : 1 ?
     x64    db : 1 ?
    ends
   .ends


GetCpuFlags proto watcall cpu:CPU {
    and eax,P_64 or P_CPU_MASK
    }

GetCpu proto watcall cpu:CPU {
    and eax,P_64 or P_CPU_MASK
    .if ( eax & P_64 )
        mov eax,P_64
    .elseif ( eax >= P_686 )
        ;
        ; this could also be 586 + MMX..
        ;
        mov eax,P_686
    .endif
    }

GetFpu proto watcall cpu:CPU {
    mov ah,1
    .if ( al & P_FPU )
        inc ah
        and al,P_64 or P_CPU_MASK
        .if ( al >= P_386 )
            mov ah,4
        .elseif ( al == P_286 )
            inc ah
        .endif
    .endif
    movzx eax,ah
    }

; Cpu flag for Code View: .machine

GetCurrCFL proto watcall {
    mov al,CurrCpu
    and eax,P_64 or P_CPU_MASK
    .if ( eax & P_64 )
        mov eax,0xD0    ; CV_CFL_AMD64
    .elseif ( eax >= P_686 )
        mov eax,P_686
    .elseif ( eax == 0 )
        inc eax         ; 0 isnt possible, 1 is 8086 and 80186
    .endif
    }

GetCpuExtensions proto watcall cpu:CPU {
    and eax,P_CPU_MASK
    .if ( eax <= P_686 )
        xor eax,eax
    .endif
    }

SetCurrCpu proto watcall cpu:CPU {
    and CurrCpu,not ( P_64 or P_CPU_MASK )
    or  CurrCpu,al
    }

SetCurrCpuExtensions proto watcall extensions:byte {
    and CurrCpu,not P_CPU_MASK
    or  CurrCpu,al
    }

GetCurrCpu macro
    exitm<GetCpu(CurrCpu)>
    endm


SetCPU proto __ccall :CPU

endif
