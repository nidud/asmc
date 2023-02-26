
adc     reg64,reg64
adc     reg64,mem64
adc     reg64,1
adc     mem64,reg64
adc     mem64,1

add     reg64,reg64
add     reg64,mem64
add     reg64,1
add     mem64,reg64
add     mem64,1

and     reg64,reg64
and     reg64,mem64
and     reg64,1
and     mem64,reg64
and     mem64,1

bsf     reg64,reg64
bsf     reg64,mem64

bsr     reg64,reg64
bsr     reg64,mem64

bswap   reg32
bswap   reg64

bt      reg64,reg64
bt      reg64,1
bt      mem16,reg16
bt      mem16,1

btc     reg64,reg64
btc     reg64,1
btc     mem16,1

btr     reg64,reg64
btr     reg64,1
btr     mem16,1

bts     reg64,reg64
bts     reg64,1
bts     mem16,1

call    reg64 ; *

cbw
cdq
clc
cld

cmova   reg64,reg64
cmovae  reg64,reg64
cmovb   reg64,reg64
cmovbe  reg64,reg64
cmovc   reg64,reg64
cmove   reg64,reg64
cmovg   reg64,reg64
cmovge  reg64,reg64
cmovl   reg64,reg64
cmovle  reg64,reg64
cmovna  reg64,reg64
cmovnae reg64,reg64
cmovnb  reg64,reg64
cmovnbe reg64,reg64
cmovnc  reg64,reg64
cmovne  reg64,reg64
cmovng  reg64,reg64
cmovnge reg64,reg64
cmovnl  reg64,reg64
cmovnle reg64,reg64
cmovno  reg64,reg64
cmovnp  reg64,reg64
cmovns  reg64,reg64
cmovnz  reg64,reg64
cmovo   reg64,reg64
cmovp   reg64,reg64
cmovpe  reg64,reg64
cmovpo  reg64,reg64
cmovs   reg64,reg64
cmovz   reg64,reg64

cmovz   reg64,mem64
cmovnz  reg64,mem64

cmp     reg64,reg64
cmp     reg64,1
cmp     mem64,reg64
cmp     mem64,1

cmpsb
cmpsw
cmpsd

cmpxchg reg64,reg64
cmpxchg mem64,reg64

cwd
cwde

dec     reg8
dec     reg64
dec     mem8
dec     mem64

div     reg8  ;*
div     reg16 ;*
div     reg32 ;*
div     reg64 ;*

enter   imm8,imm8 ;*

idiv    reg8  ;*
idiv    reg16 ;*
idiv    reg32 ;*
idiv    reg64 ;*

imul    reg8
imul    reg16
imul    reg32
imul    reg64
imul    mem8
imul    mem16
imul    mem32
imul    mem64
imul    reg16,reg16
imul    reg32,reg32
imul    reg64,reg64
imul    reg16,reg16,2
imul    reg32,reg32,2
imul    reg64,reg64,2

inc     reg8
inc     reg64
inc     mem8
inc     mem64

;lahf
;lar     reg16,reg16
;lar     reg32,reg32

lea     reg64,mem64

lodsb
lodsw
lodsd

mov     reg64,reg64
mov     reg64,mem64
mov     reg64,10
mov     mem64,reg64
mov     mem64,imm8

movsb
movsw
movsd

movsx   reg32,reg8
movsx   reg32,mem8
movsx   reg64,reg16
movsx   reg64,mem16

movzx   reg32,reg8
movzx   reg32,mem8
movzx   reg64,reg16
movzx   reg64,mem16

mul     reg8
mul     reg16
mul     reg32
mul     reg64
mul     mem8
mul     mem16
mul     mem32
mul     mem64

neg     reg8
neg     reg64
neg     mem8
neg     mem64

nop

not     reg8
not     reg64
not     mem32
not     mem64

or      reg8,reg8
or      reg64,reg64
or      reg64,mem64
or      reg64,imm8
or      mem8,reg8
or      mem64,reg64
or      mem64,imm8

pop     reg64 ;*
popfq         ;*
push    reg64 ;*

push    mem64 ;*
pushfq        ;*

rcl     reg8,1
rcl     reg64,1
rcl     reg8,cl
rcl     reg64,cl
rcl     mem8,1
rcl     mem64,1

rcr     reg8,1
rcr     reg64,1
rcr     reg8,cl
rcr     reg64,cl
rcr     mem8,1
rcr     mem64,1

rol     reg8,1
rol     reg64,1
rol     reg8,cl
rol     reg64,cl
rol     mem8,1
rol     mem64,1

ror     reg8,1
ror     reg64,1
ror     reg8,cl
ror     reg64,cl
ror     mem8,1
ror     mem64,1

shl     reg8,1
shl     reg64,1
shl     reg8,cl
shl     reg64,cl
shl     mem8,1
shl     mem64,1

sar     reg8,1
sar     reg64,1
sar     reg8,cl
sar     reg64,cl
sar     mem8,1
sar     mem64,1

sbb     reg8,reg8
sbb     reg64,reg64
sbb     reg8,1
sbb     reg64,1
sbb     mem8,reg8
sbb     mem64,reg64
sbb     mem8,1
sbb     mem64,1

scasb
scasw
scasd

setae   reg8
setae   mem8
setb    reg8
setb    mem8
setg    reg8
setg    mem8
setng   reg8
setng   mem8

shr     reg8,1
shr     reg64,1
shr     reg8,cl
shr     reg64,cl
shr     mem8,1
shr     mem64,1

shld    reg16,reg16,1
shld    reg32,reg32,1
shld    reg64,reg64,1
shld    mem16,reg16,1
shld    mem64,reg64,1

shrd    reg16,reg16,1
shrd    reg32,reg32,1
shrd    reg64,reg64,1
shrd    mem16,reg16,1
shrd    mem64,reg64,1

smsw    reg32
smsw    reg64

stc
std ; *

stosb
stosw
stosd

str     reg16
str     reg32

sub     reg8,reg8
sub     reg64,reg64
sub     reg64,1
sub     reg64,mem64
sub     mem64,1
sub     mem64,reg64

test    reg8,reg8
test    reg64,reg64
test    reg64,1
test    reg64,mem64
test    mem64,1
test    mem64,reg64

xchg    reg8,reg8
xchg    reg64,reg64
xchg    reg64,mem64
xchg    mem64,reg64

xlat ; *
xlatb ; *

xor     reg8,reg8
xor     reg64,reg64
xor     reg64,mem64
xor     reg64,8
xor     mem8,reg8
xor     mem64,reg64
xor     mem64,8
