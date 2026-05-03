ifndef s_addr

IN_ADDR struct
union
 struct S_un_b
  s_b1	db ?
  s_b2	db ?
  s_b3	db ?
  s_b4	db ?
 ends
 struct S_un_w
  s_w1	db ?
  s_w2	db ?
 ends
 S_addr dd ?
ends
IN_ADDR ends
S_un	typedef IN_ADDR

PIN_ADDR	typedef ptr IN_ADDR
LPIN_ADDR	typedef ptr IN_ADDR

s_addr		equ S_un.S_addr
s_host		equ S_un.S_un_b.s_b2
s_net		equ S_un.S_un_b.s_b1
s_imp		equ S_un.S_un_w.s_w2
s_impno		equ S_un.S_un_b.s_b4
s_lh		equ S_un.S_un_b.s_b3

endif
