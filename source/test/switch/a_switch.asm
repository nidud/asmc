;
; $endsw - (endsw-case)
;
;   lea     r11, [@C0018]
;   movzx   r10, byte ptr [r11+rax-15H]
;   sub     r11, r10
;   jmp     r11

.code

switch1 proc val:sdword
    ldr eax,val
    .switch eax
    .case  0: .return( 8 )
    .case  1: .return( 7 )
    .case  2: .return( 6 )
    .case  3: .return( 5 )
    .case  4: .return( 5 )
    .case  5: .return( 3 )
    .case  6: .return( 2 )
    .case  7: .return( 1 )
    .case  8: .return( 20 )
    .case  9: .return( 30 )
    .case 10: .return( 40 )
    .case 11: .return( 50 )
    .case 12: .return( 60 )
    .case 13: .return( 70 )
    .case 14: .return( 80 )
    .case 15: .return( 90 )
    .case 16: .return( 100 )
    .case 17: .return( 101 )
    .case 18: .return( 200 )
    .case 19: .return( 300 )
    .case 20: .return( 400 )
    .endsw
    .return( 0 )
switch1 endp
end
