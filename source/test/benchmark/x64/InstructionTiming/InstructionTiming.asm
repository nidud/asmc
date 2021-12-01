
include stdio.inc
include stdlib.inc
include direct.inc
include winbase.inc
include sselevel.inc

define max_proc_size 4096

.enum Operand {
    None,
    imm8,
    reg8,
    reg16,
    reg32,
    reg64,
    reg128,
    mem8,
    mem16,
    mem32,
    mem128,
    mem64,
    regcl,
    OperandCount
    }

.template Instruction
    name    string_t ?
    op1     Operand ?
    op2     Operand ?
    op3     Operand ?
    imm     int_t ?
   .ends

   .data
    align 16
    arg1 db 4096 dup(4)
    arg2 db 4096 dup(4)
    farg db "Instructions.txt"
         db 256-16 dup(0)
    Operands string_t \
     @CStr("imm8"),
     @CStr("reg8"),
     @CStr("reg16"),
     @CStr("reg32"),
     @CStr("reg64"),
     @CStr("reg128"),
     @CStr("mem8"),
     @CStr("mem16"),
     @CStr("mem32"),
     @CStr("mem64"),
     @CStr("mem128"),
     @CStr("regcl")

   .code

    align   16
    proc_b  db max_proc_size dup(0xCC)

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

CreateASM proc uses rsi rdi rbx file:string_t, inst:string_t, op_1:Operand, op_2:Operand, op_3:Operand, imm:int_t

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
    .endsw
    .switch pascal op_2
    .case reg8  : lea r9,@CStr("<bl,r12b,r13b,r14b,r15b,cl,dl,r8b,r9b,r10b,r11b,al>")
    .case reg16 : lea r9,@CStr("<bx,r12w,r13w,r14w,r15w,cx,dx,r8w,r9w,r10w,r11w,ax>")
    .case reg32 : lea r9,@CStr("<ebx,r12d,r13d,r14d,r15d,ecx,edx,r8d,r9d,r10d,r11d,eax>")
    .case reg128: lea r9,@CStr("<xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm6,xmm5,xmm4,xmm3>")
    .endsw

    fprintf(fp,
        "for op1,%s\n"
        "for op2,%s\n", r8, r9 )

    fprintf(fp, "%s", inst)
    .if ( op_1 )

        lea rdx,@CStr("op1")
        .switch pascal op_1
        .case mem8  : lea rdx,@CStr("byte ptr [rdi+I]")
        .case mem16 : lea rdx,@CStr("word ptr [rdi+I*2]")
        .case mem32 : lea rdx,@CStr("dword ptr [rdi+I*4]")
        .case mem64 : lea rdx,@CStr("qword ptr [rdi+I*8]")
        .case mem128: lea rdx,@CStr("oword ptr [rdi+I*16]")
        .endsw
        fprintf(fp, " %s", rdx)

        .if ( op_2 )

            .if ( op_2 == imm8 )
                fprintf(fp, ",%d", imm)
            .else
                lea rdx,@CStr("op2")
                .switch pascal op_2
                .case regcl : lea rdx,@CStr("cl")
                .case mem8  : lea rdx,@CStr("byte ptr [rsi+I]")
                .case mem16 : lea rdx,@CStr("word ptr [rsi+I*2]")
                .case mem32 : lea rdx,@CStr("dword ptr [rsi+I*4]")
                .case mem64 : lea rdx,@CStr("qword ptr [rsi+I*8]")
                .case mem128: lea rdx,@CStr("oword ptr [rdi+I*16]")
                .endsw
                fprintf(fp, ",%s", rdx)
            .endif

            .if ( op_3 )

                .if ( op_3 == imm8 )
                    fprintf(fp, ",%d", imm)
                .else
                    lea rdx,@CStr("op2")
                    .switch pascal op_3
                    .case regcl : lea rdx,@CStr("cl")
                    .case mem8  : lea rdx,@CStr("byte ptr [rsi+I]")
                    .case mem16 : lea rdx,@CStr("word ptr [rsi+I*2]")
                    .case mem32 : lea rdx,@CStr("dword ptr [rsi+I*4]")
                    .case mem64 : lea rdx,@CStr("qword ptr [rsi+I*8]")
                    .case mem128: lea rdx,@CStr("oword ptr [rdi+I*16]")
                    .endsw
                    fprintf(fp, ",%s", rdx)
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

    sprintf(&buffer, "asmtobin %s", name)
    system(&buffer)
    ret

CreateBIN endp

CALLBACK(PNTESTPROC, :ptr, :ptr)

TestProc proc uses rsi rdi rbx count:dword

  local p:PNTESTPROC

    mov p,&proc_b

    ; spin up..

    .for ( ebx = 4 : ebx : ebx-- )

        p(&arg1, &arg2)
    .endf


    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)

    xor eax,eax
    cpuid
    rdtsc
    mov edi,eax

    xor eax,eax
    cpuid
    .for ecx = count : ecx : ecx -= 1
    .endf

    xor eax,eax
    cpuid
    rdtsc
    sub eax,edi
    mov edi,eax

    xor eax,eax
    cpuid
    rdtsc
    mov esi,eax
    xor rax,rax
    cpuid

    .for ebx = count : ebx : ebx--

        p(&arg1, &arg2)
    .endf

    xor eax,eax
    cpuid
    rdtsc
    sub eax,edi
    sub eax,esi
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

LoadInstruction proc uses rsi inst:string_t, op_1:Operand, op_2:Operand, op_3:Operand, imm:int_t

  local name[128]:char_t

    mov rsi,strcpy(&name, "bin\\")
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
            .endif
        .endif
    .endif

    .if CreateASM(rsi, inst, op_1, op_2, op_3, imm) == false
        .return
    .endif
    CreateBIN(rsi)

    sub rsi,4
    strcat(rsi, ".bin")
    ReadProc(rsi)
    ret

LoadInstruction endp

TimeInstruction proc uses rsi rdi rbx name:string_t, op1:Operand, op2:Operand, op3:Operand, imm:int_t, count:uint_t

  local buffer[256]:char_t

    .return .if !LoadInstruction(rcx, edx, r8d, r9d, imm)

    sub eax,13
    xor edx,edx
    mov ecx,84
    div ecx
    mov ebx,eax
    mov esi,count

    TestProc(esi)
    mov rdi,TestProc(esi)
    add rdi,TestProc(esi)
    add rdi,TestProc(esi)
    add rdi,TestProc(esi)
    shr rdi,2
    mov eax,edi
    xor edx,edx
    mov ecx,1000000
    div ecx
    .if edx > 500000
        inc eax
    .endif
    mov edi,eax

    lea rsi,buffer
    sprintf(rsi, "%-8s", name)

    .if ( op1 )
        strcat(rsi, " ")
        AddOperator(rsi, op1)
        .if ( op2 )
            strcat(rsi, ",")
            AddOperator(rsi, op2)
            .if ( op3 )
                strcat(rsi, ",")
                AddOperator(rsi, op3)
            .endif
        .endif
    .endif
    printf("%-28s %2d %7d\n", rsi, ebx, edi)
    ret

TimeInstruction endp

strtoop proc string:string_t
    mov eax,[rcx]
    .switch pascal eax
    .case '8mmi': .return imm8
    .case '8ger': .return reg8
    .case '1ger'
        .if byte ptr [rcx+4] == '6'
            .return reg16
        .endif
        .return reg128
    .case '3ger': .return reg32
    .case '6ger': .return reg64
    .case '8mem': .return mem8
    .case '1mem'
        .if byte ptr [rcx+4] == '6'
            .return mem16
        .endif
        .return mem128
    .case '3mem': .return mem32
    .case '6mem': .return mem64
    .case 'cger': .return regcl
    .endsw
    .return None
strtoop endp

TimeInstructions proc uses rsi rdi rbx count:dword

    .new fp:ptr FILE = fopen(&farg, "rt")
    .if ( rax == NULL )
        perror(&farg)
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

        mov n.name,strtok(rsi, "\t ,")
        mov n.op1,strtoop(strtok(NULL, "\t ,"))
        mov n.op2,strtoop(strtok(NULL, "\t ,"))
        mov n.op3,strtoop(strtok(NULL, "\t ,"))
        mov n.imm,atol(strtok(NULL, "\t ,"))

        TimeInstruction(n.name, n.op1, n.op2, n.op3, n.imm, count)
    .endw
    fclose(fp)
    ret

TimeInstructions endp

;-------------------------------------------------------------------------------
; Startup and CPU detection
;-------------------------------------------------------------------------------

GetCPU proc

  local lpflOldProtect:qword, cpustring[80]:byte

    .ifd !( sselevel & SSE_SSE2 )

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

    .for ( rdx = &cpustring: byte ptr [rdx] == ' ' : rdx++ )
    .endf
    mov eax,sselevel
    lea r8,@CStr("SSE2")
    .switch
    .case eax & SSE_AVX512F: lea r8,@CStr("AVX512") : .endc
    .case eax & SSE_AVX2:    lea r8,@CStr("AVX2")   : .endc
    .case eax & SSE_AVX:     lea r8,@CStr("AVX")    : .endc
    .case eax & SSE_SSE42:   lea r8,@CStr("SSE4.2") : .endc
    .case eax & SSE_SSE41:   lea r8,@CStr("SSE4.1") : .endc
    .case eax & SSE_SSSE3:   lea r8,@CStr("SSSE3")  : .endc
    .case eax & SSE_SSE3:    lea r8,@CStr("SSE3")   : .endc
    .endsw

    printf(
        "%s (%s)\n"
        "------------------------------------------------\n"
        "Instr.     Operands         Bytes  Clocks\n"
        "------------------------------------------------\n", rdx, r8)

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


main proc argc:int_t, argv:array_t

    .if ( ecx == 2 )

        strcpy(&farg, [rdx+8])
    .endif
    GetCPU()

    _mkdir("asm")
    _mkdir("bin")

    .if LoadInstruction("mov", reg64, reg64, None, 0)

         TimeInstructions(Calibrate())
    .endif
    .return 0

main endp

    end
