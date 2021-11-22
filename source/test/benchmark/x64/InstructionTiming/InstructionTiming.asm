
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
    mem8,
    mem16,
    mem32,
    mem64
    }

    .data
     arg1 db 4096 dup(4)
     arg2 db 4096 dup(4)
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

    .if ( op_2 == reg8 && op_3 == 0 && imm )
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
    .case reg8 : lea r8,@CStr("<cl,dl,r8b,r9b,r10b,r11b,al>")
    .case reg16: lea r8,@CStr("<cx,dx,r8w,r9w,r10w,r11w,ax>")
    .case reg32: lea r8,@CStr("<ecx,edx,r8d,r9d,r10d,r11d,eax>")
    .endsw
    .switch pascal op_2
    .case reg8 : lea r9,@CStr("<bl,r12b,r13b,r14b,r15b,cl,dl,r8b,r9b,r10b,r11b,al>")
    .case reg16: lea r9,@CStr("<bx,r12w,r13w,r14w,r15w,cx,dx,r8w,r9w,r10w,r11w,ax>")
    .case reg32: lea r9,@CStr("<ebx,r12d,r13d,r14d,r15d,ecx,edx,r8d,r9d,r10d,r11d,eax>")
    .endsw

    fprintf(fp,
        "for op1,%s\n"
        "for op2,%s\n", r8, r9 )

    fprintf(fp, "%s", inst)
    .if ( op_1 )

        fprintf(fp, " ")
        .switch op_1
        .case reg8
        .case reg16
        .case reg32
        .case reg64
            fprintf(fp, "op1")
            .endc
        .case mem8
            fprintf(fp, "byte ptr [rdi+I]")
            .endc
        .case mem16
            fprintf(fp, "word ptr [rdi+I*2]")
            .endc
        .case mem32
            fprintf(fp, "dword ptr [rdi+I*4]")
            .endc
        .case mem64
            fprintf(fp, "qword ptr [rdi+I*8]")
            .endc
        .endsw

        .if ( op_2 )

            fprintf(fp, ",")
            .switch op_2
            .case reg8
                .if ( op_3 == 0 && imm )
                    fprintf(fp, "cl")
                    .endc
                .endif
            .case reg16
            .case reg32
            .case reg64
                fprintf(fp, "op2")
                .endc
            .case mem8
                fprintf(fp, "byte ptr [rsi+I]")
                .endc
            .case mem16
                fprintf(fp, "word ptr [rsi+I*2]")
                .endc
            .case mem32
                fprintf(fp, "dword ptr [rsi+I*4]")
                .endc
            .case mem64
                fprintf(fp, "qword ptr [rsi+I*8]")
                .endc
            .case imm8
                fprintf(fp, "%d", imm)
                .endc
            .endsw

            .if ( op_3 )

                fprintf(fp, ",")
                .switch op_3
                .case reg8
                .case reg16
                .case reg32
                .case reg64
                    fprintf(fp, "op2")
                    .endc
                .case mem8
                    fprintf(fp, "byte ptr [rsi+I]")
                    .endc
                .case mem16
                    fprintf(fp, "word ptr [rsi+I*2]")
                    .endc
                .case mem32
                    fprintf(fp, "dword ptr [rsi+I*4]")
                    .endc
                .case mem64
                    fprintf(fp, "qword ptr [rsi+I*8]")
                    .endc
                .case imm8
                    fprintf(fp, "%d", imm)
                    .endc
                .endsw
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

    sprintf(&buffer, "asmc64 -q -bin -Fo bin\\%s.bin asm\\%s.asm", name, name)
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

    .switch pascal edx
    .case imm8:    strcat(rcx, "imm8")
    .case reg8:    strcat(rcx, "reg8")
    .case reg16:   strcat(rcx, "reg16")
    .case reg32:   strcat(rcx, "reg32")
    .case reg64:   strcat(rcx, "reg64")
    .case mem8:    strcat(rcx, "mem8")
    .case mem16:   strcat(rcx, "mem16")
    .case mem32:   strcat(rcx, "mem32")
    .case mem64:   strcat(rcx, "mem64")
    .endsw
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

TI proc uses rsi rdi rbx name:string_t, op1:Operand, op2:Operand, op3:Operand, imm:int_t

  local buffer[256]:char_t

    .return .if !LoadInstruction(rcx, edx, r8d, r9d, imm)

    sub eax,13
    xor edx,edx
    mov ecx,84
    div ecx
    mov ebx,eax

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

TI endp

TimeInstructions proc uses rsi rdi rbx count:dword
    mov esi,ecx
include Instructions.inc
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

    .for rax = &cpustring: byte ptr [rax] == ' ' : rax++
    .endf
    printf("%s (", rax)

    mov eax,sselevel
    .switch
    .case eax & SSE_AVX512F: printf("AVX512") : .endc
    .case eax & SSE_AVX2:    printf("AVX2")   : .endc
    .case eax & SSE_AVX:     printf("AVX")    : .endc
    .case eax & SSE_SSE42:   printf("SSE4.2") : .endc
    .case eax & SSE_SSE41:   printf("SSE4.1") : .endc
    .case eax & SSE_SSSE3:   printf("SSSE3")  : .endc
    .case eax & SSE_SSE3:    printf("SSE3")   : .endc
    .default
        printf( "SSE2" )
    .endsw
    printf(
        ")\n"
        "------------------------------------------------\n"
        "Instr.     Operands         Bytes  Clocks\n"
        "------------------------------------------------\n")

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
    .while TestProc(ebx) < 1000000
        add ebx,5000
    .endw
    .while TestProc(ebx) > 1000000
        sub ebx,500
    .endw
    .while TestProc(ebx) < 1000000
        add ebx,500
    .endw
    .while TestProc(ebx) > 1000000
        sub ebx,50
    .endw
    .while TestProc(ebx) < 1000000
        add ebx,50
    .endw
    .return ebx

Calibrate endp


main proc uses rbx

    GetCPU()

    _mkdir("asm")
    _mkdir("bin")

   .if LoadInstruction("mov", reg64, reg64, None, 0)

         TimeInstructions(Calibrate())
  .endif
    ret

main endp

    end
