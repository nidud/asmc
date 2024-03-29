; INSTTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include direct.inc
include windows.inc
include wininet.inc
include sselevel.inc
include tchar.inc

define max_proc_size 4096

.enum Operand {
    None,
    immed,
    reg8,
    reg16,
    reg32,
    reg64,
    reg128,
    reg256,
    reg512,
    mem8,
    mem16,
    mem32,
    mem64,
    mem128,
    mem256,
    mem512,
    regcl,
    OperandCount
    }

.template Instruction
    name    string_t ?
    op1     Operand ?
    op2     Operand ?
    op3     Operand ?
    op4     Operand ?
    imm     int_t ?
   .ends

   .data
    align 16
    arg1 db 4096 dup(4)
    arg2 db 4096 dup(4)
    instruction_list string_t nullptr
    fpout LPFILE nullptr
    Assembler db "asmc64.exe"
         db 256-10 dup(0)

    Operands string_t \
     @CStr("immed"),
     @CStr("reg8"),
     @CStr("reg16"),
     @CStr("reg32"),
     @CStr("reg64"),
     @CStr("reg128"),
     @CStr("reg256"),
     @CStr("reg512"),
     @CStr("mem8"),
     @CStr("mem16"),
     @CStr("mem32"),
     @CStr("mem64"),
     @CStr("mem128"),
     @CStr("mem256"),
     @CStr("mem512"),
     @CStr("regcl")

   .code

    align   16
    proc_b  db max_proc_size dup(0xCC)

GetAssembler proc

  local wsaData:WSADATA
  local hINet:HINTERNET
  local hFile:HANDLE
  local dwNumberOfBytesRead:uint_t
  local fp:LPFILE
  local buffer[1024]:char_t

    .ifd ( GetFileAttributes("asmc64.exe") != INVALID_FILE_ATTRIBUTES )
        .return true
    .endif
    .ifd ( GetFileAttributes("\\asmc\\bin\\asmc64.exe") != INVALID_FILE_ATTRIBUTES )
        strcpy(&Assembler, "\\asmc\\bin\\asmc64.exe" )
        .return true
    .endif
    .if SearchPath( NULL, "asmc64.exe", NULL, 256, &buffer, NULL )
        strcpy(&Assembler, &buffer )
       .return true
    .endif


    .ifd WSAStartup(2, &wsaData)
        printf("WSAStartup failed with error: %d\n", eax)
        exit(1)
    .endif
    .if !InternetOpen("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)
        perror("InternetOpen()")
        exit(1)
    .endif
    mov hINet,rax
    .if InternetOpenUrl(hINet, "https://github.com/nidud/asmc/raw/master/bin/asmc64.exe", NULL, 0, 0, 0)
        mov hFile,rax
        .if fopen("asmc64.exe", "wb")
            mov fp,rax
            .while 1
                InternetReadFile(hFile, &buffer, 1024, &dwNumberOfBytesRead)
                .break .if !dwNumberOfBytesRead
                fwrite(&buffer, dwNumberOfBytesRead, 1, fp)
            .endw
            fclose(fp)
        .else
            perror("asmc64.exe")
        .endif
    .endif
    InternetCloseHandle(hINet)
    WSACleanup()
   .return true

GetAssembler endp

;-------------------------------------------------------------------------------
; Read binary file
;-------------------------------------------------------------------------------

ReadProc proc uses rsi rdi file_name:ptr sbyte

  .new read_size:qword = 0

    lea rdi,proc_b

    FlushInstructionCache( GetCurrentProcess(), rdi, max_proc_size )

    mov eax,0xCCCCCCCC
    mov ecx,max_proc_size/4
    rep stosd

    xor edi,edi
    .ifd CreateFileA( file_name, 0x80000000, edi, rdi, 3, edi, rdi ) != -1

        mov rsi,rax
        .ifd ReadFile( rsi, &proc_b, max_proc_size, &read_size, 0 )

            mov rdi,read_size
        .endif
        CloseHandle(rsi)
    .endif

    .if !rdi

        printf("error reading: %s\n", file_name)
    .endif
    mov rax,rdi
    ret

ReadProc endp

PutOperand proc fp:ptr FILE, mac:string_t, op:Operand, imm:int_t, reg:string_t

    .switch pascal r8d
    .case immed : fprintf(rcx, "%d", r9d)
    .case regcl : fprintf(rcx, "cl")
    .case mem8  : fprintf(rcx, "byte ptr [%s+I]", reg)
    .case mem16 : fprintf(rcx, "word ptr [%s+I*2]", reg)
    .case mem32 : fprintf(rcx, "dword ptr [%s+I*4]", reg)
    .case mem64 : fprintf(rcx, "qword ptr [%s+I*8]", reg)
    .case mem128: fprintf(rcx, "oword ptr [%s+I*16]", reg)
    .case mem256: fprintf(rcx, "yword ptr [%s+I*32]", reg)
    .case mem512: fprintf(rcx, "zword ptr [%s+I*64]", reg)
    .default
        fprintf(rcx, rdx)
    .endsw
    ret

PutOperand endp

CreateASM proc uses rsi rdi rbx file:string_t, inst:string_t, op_1:Operand, op_2:Operand, op_3:Operand, op_4:Operand, imm:int_t

  local fp:ptr FILE
  local file_name[128]:char_t

    mov rsi,strcpy(&file_name, "asm\\")
    strcat(rsi, file)
    strcat(rsi, ".asm")
    .ifd ( GetFileAttributes(rsi) != INVALID_FILE_ATTRIBUTES )
        .return true
    .endif

    .if ( fopen(rsi, "wt") == NULL )

        perror(rsi)
       .return false
    .endif
    mov fp,rax

    fprintf(fp,
        ".code\n"
        "Instruction proc uses rsi rdi rbx\n" )

    .if ( op_2 == regcl && op_3 == 0 )
        fprintf(fp,
            "mov ecx,2\n"
            "mov rsi,rdx\n")
    .else
        fprintf(fp,
            "mov rdi,rcx\n"
            "mov rsi,rdx\n")
    .endif
    fprintf(fp, "I = 0\n")
    lea r8,@CStr("<rcx,rdx,r8,r9,r10,r11,rax>")
    lea r9,@CStr("<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>")
    .switch pascal op_1
    .case reg8  : lea r8,@CStr("<cl,dl,r8b,r9b,r10b,r11b,al>")
    .case reg16 : lea r8,@CStr("<cx,dx,r8w,r9w,r10w,r11w,ax>")
    .case reg32 : lea r8,@CStr("<ecx,edx,r8d,r9d,r10d,r11d,eax>")
    .case reg128: lea r8,@CStr("<xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6>")
    .case reg256: lea r8,@CStr("<ymm0,ymm1,ymm2,ymm3,ymm4,ymm5,ymm6>")
    .case reg512: lea r8,@CStr("<zmm0,zmm1,zmm2,zmm3,zmm4,zmm5,zmm6>")
    .endsw
    .switch pascal op_2
    .case reg8  : lea r9,@CStr("<bl,r12b,r13b,r14b,r15b,cl,dl,r8b,r9b,r10b,r11b,al>")
    .case reg16 : lea r9,@CStr("<bx,r12w,r13w,r14w,r15w,cx,dx,r8w,r9w,r10w,r11w,ax>")
    .case reg32 : lea r9,@CStr("<ebx,r12d,r13d,r14d,r15d,ecx,edx,r8d,r9d,r10d,r11d,eax>")
    .case reg128: lea r9,@CStr("<xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm6,xmm5,xmm4,xmm3>")
    .case reg256: lea r9,@CStr("<ymm0,ymm1,ymm2,ymm3,ymm4,ymm5,ymm6,ymm7,ymm6,ymm5,ymm4,ymm3>")
    .case reg512: lea r9,@CStr("<zmm0,zmm1,zmm2,zmm3,zmm4,zmm5,zmm6,zmm7,zmm6,zmm5,zmm4,zmm3>")
    .endsw

    fprintf(fp,
        "for op1,%s\n"
        "for op2,%s\n", r8, r9 )

    .if strcmp(inst, "div")
        strcmp(inst, "idiv")
    .endif
    .if ( eax == 0 )
        fprintf(fp, "mov edx,0\n")
    .endif

    fprintf(fp, "%s", inst)
    .if ( op_1 )
        fprintf(fp, " ")
        PutOperand(fp, "op1", op_1, imm, "rdi")
        .if ( op_2 )
            fprintf(fp, ",")
            PutOperand(fp, "op2", op_2, imm, "rsi")
            .if ( op_3 )
                fprintf(fp, ",")
                lea rdx,@CStr("op2")
                .if ( op_3 == reg32 )
                    lea rdx,@CStr("eax")
                .elseif ( op_3 == reg64 )
                    lea rdx,@CStr("rax")
                .endif
                PutOperand(fp, rdx, op_3, imm, "rsi")
                .if ( op_4 )
                    fprintf(fp, ",")
                    PutOperand(fp, "op2", op_4, imm, "rsi")
                .endif
            .endif
        .endif
    .endif

    fprintf(fp,
        "\n"
        "I = I + 1\n"
        "endm\n"
        "endm\n"
        "ret\n"
        "Instruction endp\n"
        "end\n")
    fclose(fp)
   .return true

CreateASM endp

CreateBIN proc name:string_t

  local buffer[256]:char_t

    sprintf(&buffer, "%s -q -bin -Fo tmp\\%s.bin asm\\%s.asm", &Assembler, name, name)
    system(&buffer)
    ret

CreateBIN endp

TestProc proc uses rsi rdi rbx r12 r13 count:dword

    lea rsi,proc_b
    mov r13,rcx
    lea r12,arg2

    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS) ; REALTIME_PRIORITY_CLASS)

    xor eax,eax
    cpuid
    rdtsc
    mov edi,eax
    lea rbx,arg1
@@:
    mov  rdx,r12
    mov  rcx,rbx
    call rsi
    sub  r13d,1
    jnz  @B

    xor eax,eax
    cpuid
    rdtsc
    sub eax,edi
    mov edi,eax

    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS)
   .return edi

TestProc endp

AddOperator proc string:string_t, op:Operand

    .if ( edx && edx < OperandCount )
        lea rax,Operands
        mov rdx,[rax+rdx*8-8]
    .else
        lea rdx,@CStr("??")
    .endif
    strcat(rcx, rdx)
    ret

AddOperator endp

LoadInstruction proc uses rsi inst:string_t, op_1:Operand, op_2:Operand, op_3:Operand, op_4:Operand, imm:int_t

  local name[128]:char_t

    mov rsi,strcpy(&name, "tmp\\")
    add rsi,4
    strcpy(rsi, inst)

    .if ( op_1 )
        strcat(rsi, "_")
        AddOperator(rsi, op_1)
        .if ( op_2 )
            strcat(rsi, "_")
            AddOperator(rsi, op_2)
            .if ( op_3 )
                strcat(rsi, "_")
                AddOperator(rsi, op_3)
                .if ( op_4 )
                    strcat(rsi, "_")
                    AddOperator(rsi, op_4)
                .endif
            .endif
        .endif
    .endif

    .if CreateASM(rsi, inst, op_1, op_2, op_3, op_4, imm) == false
        .return
    .endif
    CreateBIN(rsi)

    sub rsi,4
    strcat(rsi, ".bin")
    ReadProc(rsi)
    ret

LoadInstruction endp

compare proc a:ptr, b:ptr

    xor eax,eax
    mov ecx,[rcx]
    mov edx,[rdx]
    .if edx > ecx
        inc eax
    .elseif !ZERO?
        dec eax
    .endif
    ret

compare endp

define TESTCOUNT 5

TimeInstruction proc uses rsi rdi rbx name:string_t, op1:Operand, op2:Operand, op3:Operand, op4:Operand, imm:int_t, count:uint_t

  local buffer[256]:char_t
  local size:int_t

    .return .if !LoadInstruction(rcx, edx, r8d, r9d, op4, imm)

    sub eax,13
    xor edx,edx
    mov ecx,84
    div ecx
    mov size,eax

    .for ( rdi = &buffer, ebx = 0: ebx < TESTCOUNT: ebx++ )

        TestProc(count)
        stosd
    .endf

    lea rsi,buffer
    qsort(rsi, TESTCOUNT, 4, &compare)

    mov eax,[rsi+8]
    xor edx,edx
    mov ecx,1000000
    div ecx
    .if edx > 500000
        inc eax
    .endif
    mov edi,eax

    lea rsi,buffer
    sprintf(rsi, "%-12s", name)

    .if ( op1 )
        strcat(rsi, " ")
        AddOperator(rsi, op1)
        .if ( op2 )
            strcat(rsi, ",")
            AddOperator(rsi, op2)
            .if ( op3 )
                strcat(rsi, ",")
                AddOperator(rsi, op3)
                .if ( op4 )
                    strcat(rsi, ",")
                    AddOperator(rsi, op4)
                .endif
            .endif
        .endif
    .endif
    fprintf(fpout, "%-40s %2d %7d\n", rsi, size, edi)
    ret

TimeInstruction endp

strtoop proc string:string_t
    mov eax,[rcx]
    .if ( ax == 'lc' )
        .return regcl
    .endif
    .switch pascal eax
    .case 'emmi': .return immed
    .case '8ger': .return reg8
    .case '1ger'
        .if byte ptr [rcx+4] == '6'
            .return reg16
        .endif
        .return reg128
    .case '2ger': .return reg256
    .case '3ger': .return reg32
    .case '5ger': .return reg512
    .case '6ger': .return reg64
    .case '8mem': .return mem8
    .case '1mem'
        .if byte ptr [rcx+4] == '6'
            .return mem16
        .endif
        .return mem128
    .case '2mem': .return mem256
    .case '3mem': .return mem32
    .case '5mem': .return mem512
    .case '6mem': .return mem64
    .case 'cger': .return regcl
    .endsw
    .return None
strtoop endp

TimeInstructions proc uses rsi rdi rbx count:dword

    .new fp:ptr FILE = fopen(instruction_list, "rt")
    .if ( rax == NULL )
        perror(instruction_list)
       .return false
    .endif
    .new b[256]:char_t
    lea rsi,b
    .while fgets(rsi, 256, fp)

        .new n:Instruction = {0}
        .break .if !strlen(rsi)
        .while rax && byte ptr [rsi+rax-1] <= ' '
            dec rax
            mov byte ptr [rsi+rax],0
        .endw
        .continue .if ( !eax || byte ptr [rsi] == ';' )
        .if strchr(rsi, ';')
            mov byte ptr [rax],0
        .endif
        mov n.name,strtok(rsi, "\t ,")
        .if strtok(NULL, "\t ,")
            mov n.op1,strtoop(rax)
            .if strtok(NULL, "\t ,")
                .if ( byte ptr [rax] >= '0' && byte ptr [rax] <= '9' )
                    mov n.imm,atol(rax)
                    mov n.op2,immed
                .else
                    mov n.op2,strtoop(rax)
                .endif
                .if strtok(NULL, "\t ,")
                    .if ( byte ptr [rax] >= '0' && byte ptr [rax] <= '9' )
                        mov n.imm,atol(rax)
                        mov n.op3,immed
                    .else
                        mov n.op3,strtoop(rax)
                    .endif
                    .if strtok(NULL, "\t ,")
                        .if ( byte ptr [rax] >= '0' && byte ptr [rax] <= '9' )
                            mov n.imm,atol(rax)
                            mov n.op4,immed
                        .else
                            mov n.op4,strtoop(rax)
                        .endif
                    .endif
                .endif
            .endif
        .endif
        TimeInstruction(n.name, n.op1, n.op2, n.op3, n.op4, n.imm, count)
    .endw
    fclose(fp)
    ret

TimeInstructions endp

;-------------------------------------------------------------------------------
; Startup and CPU detection
;-------------------------------------------------------------------------------

GetCPU proc uses rsi rdi rbx

  local lpflOldProtect:qword, cpustring[80]:byte

    xor esi,esi
    xor eax,eax
    cpuid
    .if rax
        .if ah == 5
            xor     eax,eax
        .else
            mov     eax,7
            xor     ecx,ecx
            cpuid               ; check AVX2 support
            xor     eax,eax
            bt      ebx,5       ; AVX2
            adc     eax,eax     ; into bit 9
            push    rax
            mov     eax,1
            cpuid
            pop     rax
            bt      ecx,28      ; AVX support by CPU
            adc     eax,eax     ; into bit 8
            bt      ecx,27      ; XGETBV supported
            adc     eax,eax     ; into bit 7
            bt      ecx,20      ; SSE4.2
            adc     eax,eax     ; into bit 6
            bt      ecx,19      ; SSE4.1
            adc     eax,eax     ; into bit 5
            bt      ecx,9       ; SSSE3
            adc     eax,eax     ; into bit 4
            bt      ecx,0       ; SSE3
            adc     eax,eax     ; into bit 3
            bt      edx,26      ; SSE2
            adc     eax,eax     ; into bit 2
            bt      edx,25      ; SSE
            adc     eax,eax     ; into bit 1
            bt      ecx,0       ; MMX
            adc     eax,eax     ; into bit 0
            mov     esi,eax
        .endif
    .endif

    .if eax & SSE_XGETBV

        xor ecx,ecx
        xgetbv
        .if eax & 6 ; AVX support by OS?
            or esi,SSE_AVXOS
        .endif

        and eax,0xE0
        .if eax == 0xE0

            xor ecx,ecx
            mov eax,7
            cpuid

            .if ebx & 1 shl 16      ; SSE_AVX512F ?

                xor eax,eax
                bt  ebx,30          ; SSE_AVX512BW
                adc eax,eax         ; into bit 28
                bt  ecx,1           ; SSE_AVX512VBMI
                adc eax,eax         ; into bit 27
                bt  ebx,31          ; SSE_AVX512VL
                adc eax,eax         ; into bit 26
                bt  edx,2           ; SSE_AVX5124VNNIW
                adc eax,eax         ; into bit 25
                bt  edx,3           ; SSE_AVX5124FMAPS
                adc eax,eax         ; into bit 24
                bt  ebx,21          ; SSE_AVX512IFMA
                adc eax,eax         ; into bit 23
                bt  ebx,17          ; SSE_AVX512DQ
                adc eax,eax         ; into bit 22
                bt  edx,8           ; SSE_AVX512VP2INTERSECT
                adc eax,eax         ; into bit 21
                bt  ecx,14          ; SSE_AVX512VPOPCNTDQ
                adc eax,eax         ; into bit 20
                bt  ecx,12          ; SSE_AVX512BITALG
                adc eax,eax         ; into bit 19
                bt  ecx,11          ; SSE_AVX512VNNI
                adc eax,eax         ; into bit 18
                bt  ecx,10          ; SSE_AVX512PVPCLMULQDQ
                adc eax,eax         ; into bit 17
                bt  ecx,9           ; SSE_AVX512PVAES
                adc eax,eax         ; into bit 16
                bt  ecx,8           ; SSE_AVX512PGFNI
                adc eax,eax         ; into bit 15
                bt  ecx,6           ; SSE_AVX512VBMI2
                adc eax,eax         ; into bit 14
                bt  ebx,28          ; SSE_AVX512CD
                adc eax,eax         ; into bit 13
                bt  ebx,27          ; SSE_AVX512ER
                adc eax,eax         ; into bit 12
                bt  ebx,26          ; SSE_AVX512PF
                adc eax,eax         ; into bit 11
                shl eax,11
                or  eax,SSE_AVX512F ; into bit 10
                or  esi,eax

                mov ecx,1
                mov eax,7
                cpuid
                .if ebx & 1 shl 5
                    or esi,SSE_AVX512BF16
                .endif
            .endif
        .endif
    .endif

    .ifd !( esi & SSE_SSE2 )

        printf("CPU error: Need SSE2 level\n")
        exit(0)
    .endif

    .for ( r8 = &cpustring, r9d = 0 : r9d < 3 : r9d++, r8 += 16 )

        lea rax,[r9+0x80000002]
        cpuid

        mov [r8+0x00],eax
        mov [r8+0x04],ebx
        mov [r8+0x08],ecx
        mov [r8+0x0C],edx
    .endf

    .for ( r8 = &cpustring: byte ptr [r8] == ' ' : r8++ )
    .endf
    mov eax,esi
    lea r9,@CStr("SSE2")
    .switch
    .case eax & SSE_AVX512F: lea r9,@CStr("AVX512") : .endc
    .case eax & SSE_AVX2:    lea r9,@CStr("AVX2")   : .endc
    .case eax & SSE_AVX:     lea r9,@CStr("AVX")    : .endc
    .case eax & SSE_SSE42:   lea r9,@CStr("SSE4.2") : .endc
    .case eax & SSE_SSE41:   lea r9,@CStr("SSE4.1") : .endc
    .case eax & SSE_SSSE3:   lea r9,@CStr("SSSE3")  : .endc
    .case eax & SSE_SSE3:    lea r9,@CStr("SSE3")   : .endc
    .endsw

    fprintf(fpout,
        "%s (%s)\n"
        "------------------------------------------------------\n"
        "Instr.                 Operands         Bytes  Clocks\n"
        "------------------------------------------------------\n", r8, r9)

    .ifd !VirtualProtect(&proc_b, max_proc_size, PAGE_EXECUTE_READWRITE, &lpflOldProtect)

        printf("VirtualProtect error..\n")
        exit(1)
    .endif
    ret
GetCPU endp

Calibrate proc uses rbx

    mov ebx,50000
    .while TestProc(ebx) > 1000000
        sub ebx,5000
    .endw
    .while eax < 1000000
        add ebx,5000
        TestProc(ebx)
    .endw
    .while eax > 1000000
        sub ebx,500
        TestProc(ebx)
    .endw
    .while eax < 1000000
        add ebx,500
        TestProc(ebx)
    .endw
    .while eax > 1000000
        sub ebx,50
        TestProc(ebx)
    .endw
    .while eax < 1000000
        add ebx,50
        TestProc(ebx)
    .endw
    .return ebx

Calibrate endp


main proc uses rsi argc:int_t, argv:array_t

    .new fp:ptr FILE = nullptr

    .if ( ecx < 2 )
        printf(
            "Usage: insttime instruction_list [ output_file ]\n"
            )
        exit(1)
    .endif
    mov instruction_list,[rdx+8]

    .if ( ecx == 3 )
        mov rsi,[rdx+16]
        mov fp,fopen(rsi, "wt")
        mov fpout,rax
        .if ( rax == NULL )
            perror(rsi)
            exit(1)
        .endif
    .else
        mov fpout,&stdout
    .endif

    GetCPU()
    GetAssembler()

    _mkdir("asm")
    _mkdir("tmp")

    .if LoadInstruction("mov", reg64, reg64, None, None, 0)

         TimeInstructions(Calibrate())
    .endif
    .if ( fp )
        fclose(fp)
    .endif
    .return 0

main endp

    end _tstart
