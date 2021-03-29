; VECTOR.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

.template byte fastcall

    .operator = :byte {
        movzx   eax,cl
        }
    .operator + :byte {
        add     al,cl
        }
    .operator - :byte {
        sub     al,cl
        }
    .operator * :byte {
        mul     cl
        }
    .operator / :byte {
        movzx   eax,cl
        div     cl
        movzx   edx,ah
        movzx   eax,al
        }
    .operator << :byte {
        shl     al,cl
        }
    .operator >> :byte {
        shr     al,cl
        }
    .operator ++ {
        inc     al
        }
    .operator -- {
        dec     al
        }
    .operator == :byte {
        cmp     al,cl
        sete    al
        movzx   eax,al
        }
    .ends

.template sbyte fastcall

    .operator = :sbyte {
        mov     al,cl
        }
    .operator + :sbyte {
        add     al,cl
        }
    .operator - :sbyte {
        sub     al,cl
        }
    .operator * :sbyte {
        imul    cl
        movsx   eax,ax
        }
    .operator << :sbyte {
        shl     al,cl
        }
    .operator >> :sbyte {
        sar     al,cl
        }
    .operator ++ {
        inc     al
        }
    .operator -- {
        dec     al
        }
    .operator == :sbyte {
        cmp     al,cl
        sete    al
        movzx   eax,al
        }
    .operator / :sbyte {
        mov     ah,0
        idiv    cl
        movzx   edx,ah
        movsx   eax,al
        }
    .ends

.template word fastcall

    .operator = :word {
        movzx   eax,cx
        }
    .operator + :word {
        add     ax,cx
        }
    .operator - :word {
        sub     ax,cx
        }
    .operator * :word {
        mul     cx
        shld    edx,eax,16
        mov     eax,edx
        }
    .operator / :word {
        movzx   eax,cx
        div     cx
        movzx   edx,dx
        }
    .operator << :byte {
        shl     ax,cl
        }
    .operator >> :byte {
        shr     ax,cl
        }
    .operator ++ {
        inc     ax
        }
    .operator -- {
        dec     ax
        }
    .operator == :word {
        cmp     ax,cx
        sete    al
        movzx   eax,al
        }
    .ends

.template sword fastcall

    .operator = :sword {
        mov     ax,cx
        }
    .operator + :sword {
        add     ax,cx
        }
    .operator - :sword {
        sub     ax,cx
        }
    .operator * :sword {
        imul    cx
        shld    edx,eax,16
        mov     eax,edx
        }
    .operator << :byte {
        shl     ax,cl
        }
    .operator >> :byte {
        sar     ax,cl
        }
    .operator ++ {
        inc     ax
        }
    .operator -- {
        dec     ax
        }
    .operator == :sword {
        cmp     ax,cx
        sete    al
        movzx   eax,al
        }
    .operator / :sword {
        xor     edx,edx
        idiv    cx
        movsx   eax,ax
        }
    .ends

.template dword fastcall

    .operator = :dword {
        mov     eax,ecx
        }
    .operator + :dword {
        add     eax,ecx
        }
    .operator - :dword {
        sub     eax,ecx
        }
    .operator * :dword {
        mul     ecx
        shld    rdx,rax,32
        mov     rax,rdx
        }
    .operator / :dword {
        div     ecx
        }
    .operator << :byte {
        shl     eax,cl
        }
    .operator >> :byte {
        shr     eax,cl
        }
    .operator ++ {
        inc     eax
        }
    .operator -- {
        dec     eax
        }
    .operator == :dword {
        cmp     eax,ecx
        sete    al
        movzx   eax,al
        }
    .ends

.template sdword fastcall

    .operator = :sdword {
        mov     eax,ecx
        }
    .operator + :sdword {
        add     eax,ecx
        }
    .operator - :sdword {
        sub     eax,ecx
        }
    .operator * :sdword {
        imul    ecx
        shld    rdx,rax,32
        mov     rax,rdx
        }
    .operator << :byte {
        shl     eax,cl
        }
    .operator >> :byte {
        sar     eax,cl
        }
    .operator ++ {
        inc     eax
        }
    .operator -- {
        dec     eax
        }
    .operator == :sdword {
        cmp     eax,ecx
        sete    al
        movzx   eax,al
        }
    .operator / :sdword {
        xor     edx,edx
        idiv    ecx
        }
    .ends

.template qword fastcall

    .operator = :qword {
        mov     rax,rcx
        }
    .operator + :qword {
        add     rax,rcx
        }
    .operator - :qword {
        sub     rax,rcx
        }
    .operator * :qword {
        mul     rcx
        }
    .operator / :qword {
        div     rcx
        }
    .operator << :byte {
        shl     rax,cl
        }
    .operator >> :byte {
        shr     rax,cl
        }
    .operator ++ {
        inc     rax
        }
    .operator -- {
        dec     rax
        }
    .operator == :qword {
        cmp     rax,rcx
        sete    al
        movzx   eax,al
        }
    .ends

.template sqword fastcall

    .operator = :sqword {
        mov     rax,rcx
        }
    .operator + :sqword {
        add     rax,rcx
        }
    .operator - :sqword {
        sub     rax,rcx
        }
    .operator * :sqword {
        imul    rcx
        }
    .operator << :byte {
        shl     rax,cl
        }
    .operator >> :byte {
        sar     rax,cl
        }
    .operator ++ {
        inc     rax
        }
    .operator -- {
        dec     rax
        }
    .operator == :sqword {
        cmp     rax,rcx
        sete    al
        movzx   eax,al
        }
    .operator / :sqword {
        xor     edx,edx
        idiv    rcx
        }
    .ends


.template real4 fastcall

    .operator = :real4 {
        movss   xmm0,xmm1
        }
    .operator + :real4 {
        addss   xmm0,xmm1
        }
    .operator - :real4 {
        subss   xmm0,xmm1
        }
    .operator * :real4 {
        mulss   xmm0,xmm1
        }
    .operator / :real4 {
        divss   xmm0,xmm1
        }
    .operator ++ {
        addss   xmm0,1.0
        }
    .operator -- {
        subss   xmm0,1.0
        }
    .inline load :ptr {
        movss   xmm0,[rcx]
        }
    .inline store :ptr {
        movss   [rcx],xmm0
        }
    .inline real8 {
        cvtss2sd xmm0,xmm0
        }
    .ends

.template real8 fastcall

    .operator = :real8 {
        movsd   xmm0,xmm1
        }
    .operator + :real8 {
        addsd   xmm0,xmm1
        }
    .operator - :real8 {
        subsd   xmm0,xmm1
        }
    .operator * :real8 {
        mulsd   xmm0,xmm1
        }
    .operator / :real8 {
        divsd   xmm0,xmm1
        }
    .operator ++ {
        addsd   xmm0,1.0
        }
    .operator -- {
        subsd   xmm0,1.0
        }
    .inline load :ptr {
        movsd   xmm0,[rcx]
        }
    .inline store :ptr {
        movsd   [rcx],xmm0
        }
    .inline real4 {
        cvtsd2ss xmm0,xmm0
        }
    .ends
