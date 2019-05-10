include string.inc
include stdio.inc
include malloc.inc

TEST_OVERLAP    equ 1
size_s          equ 4096*128    ; copy size

.data?
null    db 1024 dup(?)
ALIGN   16
src_1   db size_s dup(?)
ALIGN   16
dst_1   db size_s dup(?)
        db 1024 dup(?)

.data
ALIGN   4
arg_1   dq dst_1
arg_2   dq src_1
arg_3   dq size_s

nerror  dd 0

    .code

validate proc uses rsi rdi rbx d:qword, s:qword, z:qword

    mov rdi,d
    mov rcx,z
    mov rax,'x'
    inc rcx
    mov rsi,rdi
    rep stosb
    .if memcpy( rsi, s, z ) != rsi
        printf( "error return value: eax = %06X (%06X) memcpy\n", rax, d )
        inc nerror
    .endif
    mov rcx,z
    xor rdx,rdx
    xor rax,rax
    .repeat
        lodsb
        or rdx,rax
    .untilcxz
    .if rdx
        printf( "error data not zero: (%d) memcpy\n", z )
        inc nerror
    .endif
    .if BYTE PTR [rsi] != 'x'
        printf( "error data zero: memcpy\n" )
        inc nerror
    .endif
    ret
validate ENDP

validate_copy_M_M3 proc uses rsi rdi rbx ; copy(m, m+3, A..Z)
    lea rdi,dst_1
    xor rax,rax
    mov rcx,16
    rep stosd
    lea rdi,dst_1
    lea rcx,[rdi+3]
    mov rbx,rdi
    mov rax,'A'
    .repeat
        stosb
        inc rax
    .until  rax > 'z'
    mov rdx,rcx
    memcpy( rbx, rdx, 'z' - 'A' - 2 )
    xor rdx,rdx
    mov rcx,'z' - 'A' - 2
    mov rax,'z'
    .repeat
        mov dl,[rbx+rcx-1]
        sub dl,al
        dec rax
        .break .if rdx
    .untilcxz
    mov rax,[rbx + 'z' - 'A' - 2 - 1]
    .if rax != 'zyxz'
        inc rdx
    .endif
    mov rax,rcx
    ret
validate_copy_M_M3 endp

main proc

    .for(edi=1, rbx=&dst_1 : edi < 128 : edi++, rbx++)

        validate(rbx, &null, rdi)
    .endf

    lea rdi,src_1
    mov rcx,size_s
    mov rax,'x'
    rep stosb

    .for ( ebx=1 : ebx < 66, nerror <= 10 : ebx++ )

        lea rdi,dst_1
        mov al,'?'
        lea rcx,[rbx+16]
        rep stosb

        memcpy( arg_1, arg_2, rbx )

        xor edx,edx
        .if rax != arg_1
            inc edx
        .else
            .for ( ecx=ebx : ecx : ecx-- )
                .if BYTE PTR [rax+rcx-1] != 'x'
                    inc edx
                .endif
            .endf
            .for ( rdi=&[rax+rbx], ecx=16 : ecx : ecx-- )
                .if BYTE PTR [rdi+rcx-1] != '?'
                    inc edx
                .endif
            .endf
        .endif
        .if edx
            printf( "error: eax %06X [%06X] (%d) memcpy\n", rax, &dst_1, rbx )
            inc nerror
        .endif
    .endf

    .if !nerror

        .if validate_copy_M_M3()
            printf( "error(m,m+3,%d): memcpy: %s\n", 'z' - 'A' - 2, &dst_1 )
            inc nerror
        .endif
    .endif

    mov eax,nerror
    ret

main endp

    end
