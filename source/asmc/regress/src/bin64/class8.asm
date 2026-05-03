
    ; 2.37.30 - assume class:reg

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

SafeRelease proto fastcall p:abs {
    mov rax,p
    .if rax
        mov p,0
        [rax].@SubStr(typeid(p), 4).Release()
    .endif
    }

.comdef C0
    Release proc
    Method1 proc :ptr
    Method2 proc :ptr, :ptr
   .ends

.class c1 : public C0
    p2 ptr C2 ?
    Method3 proc :ptr, :ptr, :ptr
   .ends

.class c2
    p0 ptr C0 ?
    p1 ptr C1 ?
    Release proc
   .ends

   .code

    option win64:3

    assume class:rbx

C0::Release proc
    Method1(1)
    Method2(1, 2)
    ret
C0::Release endp

C0::Method1 proc a:ptr
    Release()
    Method2(1, 2)
    ret
C0::Method1 endp

C0::Method2 proc a:ptr, b:ptr
    Release()
    Method1(1)
    ret
C0::Method2 endp

C1::Method3 proc a:ptr, b:ptr, c:ptr
    Release()
    SafeRelease(p2)
    ret
C1::Method3 endp

C2::Release proc
    p0.Release()
    p1.Release()
    p1.p2.Release()
    p1.Method3(1, 2, 3)
    SafeRelease(p0)
    SafeRelease(p1)
    ret
C2::Release endp

    end
