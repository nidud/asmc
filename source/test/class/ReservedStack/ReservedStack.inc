; RESERVEDSTACK.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    stack typedef ptr qword

.template stack

    .operator stack {
        mov rax,rsp
        }

    .operator enter :abs=<16> {
        mov rax,rsp
        sub rsp,(32+((_1+15) and -16))
        mov [rsp+@ReservedStack][0*8],rax
        mov [rsp+@ReservedStack][1*8],rsi
        mov [rsp+@ReservedStack][2*8],rdi
        mov [rsp+@ReservedStack][3*8],rbx
        lea rax,[rsp+@ReservedStack+32]
        }

    .operator leave {
        mov rsi,[rsp+@ReservedStack][1*8]
        mov rdi,[rsp+@ReservedStack][2*8]
        mov rbx,[rsp+@ReservedStack][3*8]
        mov rsp,[rsp+@ReservedStack][0*8]
        }

    .operator alloc :dword {
        add ecx,16-1
        and ecx,-16
        .while ecx > 0x1000
            sub ecx,0x1000
            sub rsp,0x1000
            test eax,[rsp]
        .endw
        sub rsp,rcx
        lea rax,[rsp+@ReservedStack]
        }

    .operator free :dword {
        add ecx,16-1
        and ecx,-16
        add rsp,rcx
        }

    .operator push {
        mov rax,rsp
        sub rsp,32
        mov [rsp+@ReservedStack][0*8],rax
        mov [rsp+@ReservedStack][1*8],rsi
        mov [rsp+@ReservedStack][2*8],rdi
        mov [rsp+@ReservedStack][3*8],rbx
        }

    .operator pop {
        mov rsi,[rsp+@ReservedStack][1*8]
        mov rdi,[rsp+@ReservedStack][2*8]
        mov rbx,[rsp+@ReservedStack][3*8]
        mov rsp,[rsp+@ReservedStack][0*8]
        }

    .operator param_count {
        mov eax,@ReservedStack / 8
        }

    .operator param_size {
        mov eax,@ReservedStack
        }

    .operator local_size {
        mov rax,rbp
        sub rax,rsp
        sub eax,@ReservedStack
        }

    .operator total_size {
        mov rax,rbp
        sub rax,rsp
        }

    .ends

