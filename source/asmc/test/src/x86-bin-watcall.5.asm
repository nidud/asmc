
; 2.39 -- 64-bit byte register was used (SIL/DIL/..)

.286
.model small
 foo proto watcall :byte {
    nop
    }
.code
 foo(ax)    ; --
 foo(bx)    ; al,bl
 foo(si)    ; ax,si / ah,0
 foo(bp)    ; ax,bp / ah,0
.386
 foo(eax)   ; --
 foo(ebx)   ; movzx eax,bl
 foo(esi)   ; eax,esi / movzx eax,al
 foo(ebp)   ; eax,ebp / movzx eax,al
 end
