;
; v2.39: APX GPR
;
ifdef __ASMC__
ifndef __ASMC64__
.x64
.model flat
endif
endif
.code
 mov r31,1          ; D5 19 C7 C7 00000001
 mov r16,[rbx+rcx]
 mov rbx,[r16]      ; D5 18 8B 18
 mov [r16],rbx      ; D5 18 89 18
 mov rbx,r16        ; D5 18 8B D8
 mov r16,rbx        ; D5 48 8B C3
 mov r16,[r17+r18]  ; D5 78 8B 04 11
 mov rax,[r16+r17]  ; D5 38 8B 04 08
 mov rax,[rax+r17]  ; D5 28 8B 04 18
 mov r16,[r16+rbx]  ; D5 58 8B 04 18
 mov r16,[rbx+r17]  ; D5 68 8B 04 0B
 end
