include ctype.inc
include string.inc
include crtl.inc

include asmc.inc

TB_LD	struc
m	dq ?
e	dw ?
TB_LD	ends

u192	union
m64	dq 3 dup(?)
m32	dd 6 dup(?)
u192	ends

u96	union
m32	dd 3 dup(?)
u96	ends
;
; extended (112-bit, 96+16) long double
;
ELD	struc
m32	dd 3 dup(?)
e	dw ?
ELD	ends

EXPONENT_BIAS equ 0x3FFF

MAX_EXP_INDEX equ 13 ; # of items in tab_plus_exp[] and tab_minus_exp[]

.data

tab_plus_exp label ELD
    ELD <<0x00000000, 0x00000000, 0xA0000000>, 0x4002>	; 1e1L
    ELD <<0x00000000, 0x00000000, 0xC8000000>, 0x4005>	; 1e2L
    ELD <<0x00000000, 0x00000000, 0x9C400000>, 0x400C>	; 1e4L
    ELD <<0x00000000, 0x00000000, 0xBEBC2000>, 0x4019>	; 1e8L
    ELD <<0x00000000, 0x04000000, 0x8E1BC9BF>, 0x4034>	; 1e16L
    ELD <<0xF0200000, 0x2B70B59D, 0x9DC5ADA8>, 0x4069>	; 1e32L
    ELD <<0x3CBF6B71, 0xFFCFA6D5, 0xC2781F49>, 0x40D3>	; 1e64L
    ELD <<0xC66F336B, 0x80E98CDF, 0x93BA47C9>, 0x41A8>	; 1e128L
    ELD <<0xDDBB9018, 0x9DF9DE8D, 0xAA7EEBFB>, 0x4351>	; 1e256L
    ELD <<0xCC655C4B, 0xA60E91C6, 0xE319A0AE>, 0x46A3>	; 1e512L
    ELD <<0x650D3D17, 0x81750C17, 0xC9767586>, 0x4D48>	; 1e1024L
    ELD <<0xA74D28B1, 0xC53D5DE4, 0x9E8b3B5D>, 0x5A92>	; 1e2048L
    ELD <<0xC94C14F7, 0x8A20979A, 0xC4605202>, 0x7525>	; 1e4096L

tab_minus_exp label ELD
    ELD <<0xCCCCCCCD, 0xCCCCCCCC, 0xCCCCCCCC>, 0x3FFB>	; 1e-1L
    ELD <<0x3D70A3D7, 0x70A3D70A, 0xA3D70A3D>, 0x3FF8>	; 1e-2L
    ELD <<0xD3C36113, 0xE219652B, 0xD1B71758>, 0x3FF1>	; 1e-4L
    ELD <<0xFDC20D2A, 0x8461CEFC, 0xABCC7711>, 0x3FE4>	; 1e-8L
    ELD <<0x4C2EBE65, 0xC44DE15B, 0xE69594BE>, 0x3FC9>	; 1e-16L
    ELD <<0x67DE18E7, 0x453994BA, 0xCFB11EAD>, 0x3F94>	; 1e-32L
    ELD <<0x3F2398CC, 0xA539E9A5, 0xA87FEA27>, 0x3F2A>	; 1e-64L
    ELD <<0xAC7CB3D9, 0x64BCE4A0, 0xDDD0467C>, 0x3E55>	; 1e-128L
    ELD <<0xFA911122, 0x637A1939, 0xC0314325>, 0x3CAC>	; 1e-256L
    ELD <<0x7132D2E4, 0xDB23D21C, 0x9049EE32>, 0x395A>	; 1e-512L
    ELD <<0x87A600A6, 0xDA57C0BD, 0xA2A682A5>, 0x32B5>	; 1e-1024L
    ELD <<0x4925110F, 0x34362DE4, 0xCEAE534F>, 0x256B>	; 1e-2048L
    ELD <<0x2DE37E46, 0xD2CE9FDE, 0xA6DD04C8>, 0x0AD8>	; 1e-4096L

.code

option proc:private

cmp_u96_max proc fastcall x
;
;    compare u96 with maximum value before u96
;    overflow after multiply by 10
;
    xor eax,eax
    .switch
      .case [ecx].u96.m32[2*4] > 0x19999999: inc eax: .endc
      .case [ecx].u96.m32[2*4] < 0x19999999: dec eax: .endc
      .case [ecx].u96.m32[1*4] > 0x99999999: inc eax: .endc
      .case [ecx].u96.m32[1*4] < 0x99999999: dec eax: .endc
      .case [ecx].u96.m32[0*4] > 0x99999998: inc eax: .endc
      .case [ecx].u96.m32[0*4] < 0x99999998: dec eax: .endc
    .endsw
    ret

cmp_u96_max endp

add_check_u96_overflow proc fastcall x, _c
;
;   test u96 overflow after multiply by 10
;   add one decimal digit to u96
;
    .if cmp_u96_max( ecx ) != 1

	push esi
	push edi
	push ebx

	.for edi=_c, ebx=10, ecx=&[ecx].u96.m32, esi=0: esi < 3: esi++, ecx+=4

		xor edx,edx
		mov eax,[ecx]
		mul ebx
		add edi,eax
		adc edx,0
		mov [ecx],edi
		mov edi,edx
	.endf
	pop ebx
	pop edi
	pop esi
	xor eax,eax
    .endif
    ret

add_check_u96_overflow endp


bitsize32 proc fastcall x
;
;    calculate bitsize for uint_32
;
    .for eax = 32: !(ecx & 0x80000000), eax: eax--
	shl ecx,1
    .endf
    ret

bitsize32 endp

bitsize64 proc x:qword
;
;    calculate bitsize for uint_64
;
    mov ecx,dword ptr x
    mov edx,dword ptr x[4]
    .for eax = 64: !(edx & 0x80000000), eax: eax--
	shld edx,ecx,1
	shl ecx,1
    .endf
    ret

bitsize64 endp


m2m macro a,b
    mov eax,dword ptr b
    mov dword ptr a,eax
    endm

U96LD proc fastcall uses esi op, res
;
;    convert u96 into internal extended long double
;
    mov esi,res
    mov eax,[ecx]
    mov edx,[ecx+4]
    mov ecx,[ecx+8]
    mov [esi],eax
    mov [esi+4],edx
    mov [esi+8],ecx
    add bitsize32(ecx),64

    .if eax == 64
	mov [esi].ELD.m32[2*4],edx ; [esi].ELD.m32[1*4]
	m2m [esi].ELD.m32[1*4],[esi].ELD.m32[0*4]
	mov [esi].ELD.m32[0*4],0
	add bitsize32([esi].ELD.m32[2*4]),32
    .endif
    .if eax == 32
	m2m [esi].ELD.m32[2*4],[esi].ELD.m32[1*4]
	m2m [esi].ELD.m32[1*4],[esi].ELD.m32[0*4]
	mov [esi].ELD.m32[0*4],0
	bitsize32([esi].ELD.m32[2*4])
    .endif
    .if !eax
	mov [esi].ELD.e,ax
    .else
	lea ecx,[eax - 1 + EXPONENT_BIAS]
	mov [esi].ELD.e,cx
	and eax,0x3F ; bs %= 32;
	.if eax
	    mov ecx,32
	    sub ecx,eax
	    shl [esi].ELD.m32[2*4],cl
	    mov edx,[esi].ELD.m32[1*4]
	    xchg eax,ecx
	    shr edx,cl
	    or [esi].ELD.m32[2*4],edx
	    xchg eax,ecx
	    shl [esi].ELD.m32[1*4],cl
	    mov edx,[esi].ELD.m32[0*4]
	    xchg eax,ecx
	    shr edx,cl
	    or [esi].ELD.m32[1*4],edx
	    xchg eax,ecx
	    shl [esi].ELD.m32[0*4],cl
	.endif
    .endif
    xor eax,eax
    ret
U96LD endp

m2m64 macro a,b
    mov eax,dword ptr b[4]
    mov dword ptr a[4],eax
    mov eax,dword ptr b
    mov dword ptr a,eax
    endm

normalize proc fastcall uses esi edi ebx res
;
;    normalize internal extended long double u192
;    return exponent shift
;
    mov esi,res
    add bitsize64([esi].u192.m64[2*8]),128
    mov edi,eax

    .if eax == 128
	m2m64 [esi].u192.m64[2*8],[esi].u192.m64[1*8]
	m2m64 [esi].u192.m64[1*8],[esi].u192.m64[0*8]
	mov dword ptr [esi].u192.m64[0],0
	mov dword ptr [esi].u192.m64[4],0
	add bitsize64([esi].u192.m64[2*8]),64
	mov edi,eax
    .endif

    .if edi == 64
	m2m64 [esi].u192.m64[2*8],[esi].u192.m64[1*8]
	m2m64 [esi].u192.m64[1*8],[esi].u192.m64[0*8]
	mov dword ptr [esi].u192.m64[0],0
	mov dword ptr [esi].u192.m64[4],0
	mov edi,bitsize64([esi].u192.m64[2*8])
    .endif
    mov eax,edi
    .if eax

	push eax

	and eax,0x8000007F ; bs %= 64;
	jns @F
	dec eax
	or  eax,0xFFFFFFC0
	inc eax
	@@:

	.if eax

	    mov ebx,64
	    sub ebx,eax
	    mov edi,eax

	    mov ecx,ebx
	    mov eax,dword ptr [esi].u192.m64[2*8]
	    mov edx,dword ptr [esi].u192.m64[2*8][4]
	    call _allshl
	    mov dword ptr [esi].u192.m64[2*8],eax
	    mov dword ptr [esi].u192.m64[2*8][4],edx

	    mov ecx,edi
	    mov eax,dword ptr [esi].u192.m64[1*8]
	    mov edx,dword ptr [esi].u192.m64[1*8][4]
	    call _aullshr
	    or dword ptr [esi].u192.m64[2*8],eax
	    or dword ptr [esi].u192.m64[2*8][4],edx

	    mov ecx,ebx
	    mov eax,dword ptr [esi].u192.m64[1*8]
	    mov edx,dword ptr [esi].u192.m64[1*8][4]
	    call _allshl
	    mov dword ptr [esi].u192.m64[1*8],eax
	    mov dword ptr [esi].u192.m64[1*8][4],edx

	    mov ecx,edi
	    mov eax,dword ptr [esi].u192.m64[0*8]
	    mov edx,dword ptr [esi].u192.m64[0*8][4]
	    call _aullshr
	    or dword ptr [esi].u192.m64[1*8],eax
	    or dword ptr [esi].u192.m64[1*8][4],edx

	    mov ecx,ebx
	    mov eax,dword ptr [esi].u192.m64[0*8]
	    mov edx,dword ptr [esi].u192.m64[0*8][4]
	    call _allshl
	    mov dword ptr [esi].u192.m64[0*8],eax
	    mov dword ptr [esi].u192.m64[0*8][4],edx
	.endif
	pop eax
	sub eax,192
    .endif
    ret
normalize endp

add192 proc uses esi edi ebx res:ptr, x:qword, pos
;
;    add uint_64 to u192 on uint_32 position
;
    xor edx,edx
    mov eax,dword ptr x
    mov esi,res
    mov edi,32

    .for ebx = pos: ebx < 6: ebx++
	add eax,[esi].u192.m32[ebx*4]
	adc edx,0
	mov [esi].u192.m32[ebx*4],eax
	mov ecx,edi
	call _aullshr
    .endf

    mov eax,dword ptr x
    mov edx,dword ptr x[4]
    mov ecx,edi
    call _aullshr
    mov ebx,pos
    inc ebx

    .for : ebx < 6: ebx++
	add eax,[esi].u192.m32[ebx*4]
	adc edx,0
	mov [esi].u192.m32[ebx*4],eax
	mov ecx,edi
	call _aullshr
    .endf
    xor eax,eax
    ret
add192 endp

multiply proc uses esi edi ebx op1, op2, res
;
;    multiply u96 by u96 into u96
;    normalize and round result
;
local exp:dword, r1:u192

    mov ebx,op1
    mov edi,op2
    lea esi,r1

    mov ax,[ebx].ELD.e
    mov dx,[edi].ELD.e
    and eax,0x7FFF
    and edx,0x7FFF
    lea eax,[eax+edx-EXPONENT_BIAS+1]
    mov exp,eax

    mov eax,[ebx].ELD.m32
    mul [edi].ELD.m32
    mov dword ptr r1.m64,eax
    mov dword ptr r1.m64[4],edx
    mov eax,[ebx].ELD.m32[1*4]
    mul [edi].ELD.m32[1*4]
    mov dword ptr r1.m64[1*8],eax
    mov dword ptr r1.m64[1*8][4],edx
    mov eax,[ebx].ELD.m32[2*4]
    mul [edi].ELD.m32[2*4]
    mov dword ptr r1.m64[2*8],eax
    mov dword ptr r1.m64[2*8][4],edx

    mov eax,[ebx].ELD.m32[1*4]
    mul [edi].ELD.m32[0*4]
    add192( esi, edx::eax, 1 )
    mov eax,[ebx].ELD.m32[0*4]
    mul [edi].ELD.m32[1*4]
    add192( esi, edx::eax, 1 )
    mov eax,[ebx].ELD.m32[0*4]
    mul [edi].ELD.m32[2*4]
    add192( esi, edx::eax, 2 )
    mov eax,[ebx].ELD.m32[2*4]
    mul [edi].ELD.m32[0*4]
    add192( esi, edx::eax, 2 )
    mov eax,[ebx].ELD.m32[1*4]
    mul [edi].ELD.m32[2*4]
    add192( esi, edx::eax, 3 )
    mov eax,[ebx].ELD.m32[2*4]
    mul [edi].ELD.m32[1*4]
    add192( esi, edx::eax, 3 )
    add exp,normalize( esi )
    ;
    ; round result
    ;
    .if r1.m32[2*4] & 0x80000000

	or eax,-1
	.if r1.m32[5*4] == eax && r1.m32[4*4] == eax && r1.m32[3*4] == eax
	    xor eax,eax
	    mov r1.m32[3*4],eax
	    mov r1.m32[4*4],eax
	    mov r1.m32[5*4],0x80000000
	    inc exp
	.else
	    add192( esi, 1, 3 )
	.endif
    .endif

    mov ebx,res
    m2m [ebx].ELD.m32[0*4],r1.m32[3*4]
    m2m [ebx].ELD.m32[1*4],r1.m32[4*4]
    m2m [ebx].ELD.m32[2*4],r1.m32[5*4]
    mov eax,exp
    mov [ebx].ELD.e,ax
    xor eax,eax
    ret
multiply endp

TB_create proc uses esi edi ebx value:ptr u96, exponent:sdword, ld:ptr TB_LD
;
;    create tbyte/long double from u96 value and
;    decimal exponent, round result
;
    local res:ELD

    mov edi,exponent
    .ifs edi < 0
	neg edi
	lea esi,tab_minus_exp
    .else
	lea esi,tab_plus_exp
    .endif

    U96LD(value, addr res)

    .for ebx = 0: ebx < MAX_EXP_INDEX: ebx++
	.if edi & 1
	    imul ecx,ebx,sizeof(ELD)
	    multiply(addr res, addr [esi+ecx], addr res)
	.endif
	shr edi,1
	.break .ifz
    .endf
if 0
    .if edi
	;
	; exponent overflow
	;
    .endif
endif
    mov ebx,ld
    mov ax,res.e
    mov [ebx].TB_LD.e,ax

    mov eax,res.m32[1*4]
    mov edx,res.m32[2*4]
    mov dword ptr [ebx].TB_LD.m,eax
    mov dword ptr [ebx].TB_LD.m[4],edx
    ;
    ; round result
    ;
    .if res.m32[0*4] & 0x80000000
	.if dword ptr [ebx].TB_LD.m == -1 && dword ptr [ebx].TB_LD.m[4] == -1
	    mov dword ptr [ebx].TB_LD.m,0
	    mov dword ptr [ebx].TB_LD.m[4],0x80000000
	    inc [ebx].TB_LD.e
	.else
	    add dword ptr [ebx].TB_LD.m,1
	    adc dword ptr [ebx].TB_LD.m[4],0
	.endif
    .endif
    xor eax,eax
    ret

TB_create endp

strtotb proc public uses esi edi ebx p:LPSTR, ld:ptr TB_LD, negative:sbyte
;
;    convert string into tbyte/long double
;    set result sign
;
local	sign,
	exp_sign,
	exp_value,
	exponent,
	exp1,
	exponent_tmp,
	overflow,
	value:u96,
	value_tmp:u96

    mov sign,1
    mov exp_sign,1
    mov esi,p
    movzx eax,byte ptr [esi]
    .while _ctype[eax*2+2] & _SPACE
	inc esi
	mov al,[esi]
    .endw
    .switch al
      .case '-'
	mov sign,-1
      .case '+'
	inc esi
    .endsw
    .if negative
	neg sign
    .endif

    xor eax,eax
    lea edi,value_tmp
    mov ecx,((sizeof(u96) * 2) / 4) + 3
    rep stosd
    mov al,[esi]
    sub al,'0'

    .while al < 10
	.if overflow
	    inc exponent_tmp
	    inc exp1
	.else
	    .if add_check_u96_overflow(addr value_tmp, eax)
		mov overflow,1
		inc exponent_tmp
		inc exp1
	    .elseif byte ptr [esi] != '0'
		memcpy(addr value, addr value_tmp, sizeof(u96))
		mov exp1,0
	    .elseif value.m32[0*4] || value.m32[1*4] || value.m32[2*4]
		inc exp1
	    .endif
	.endif
	inc esi
	movzx eax,byte ptr [esi]
	sub al,'0'
    .endw

    mov eax,exp1
    mov exponent,eax
    .if byte ptr [esi] == '.'
	inc esi
	movzx eax,byte ptr [esi]
	sub al,'0'
	.while al < 10
	    .if overflow == 0
		.if add_check_u96_overflow(addr value_tmp, eax )
		    mov overflow,1
		.else
		    dec exponent_tmp
		    .if byte ptr [esi] != '0'
			memcpy(addr value, addr value_tmp, sizeof(u96))
			mov eax,exponent_tmp
			mov exponent,eax
		    .endif
		.endif
	    .endif
	    inc esi
	    movzx eax,byte ptr [esi]
	    sub al,'0'
	.endw
    .endif
    mov exp_value,0
    movzx eax,byte ptr [esi]
    or	al,0x20
    .if al == 'e'
	inc esi
	mov al,[esi]
	.switch al
	.case '-'
	    mov exp_sign,-1
	.case '+'
	    inc esi
	    .endc
	.case '0'..'9'
	    .endc
	.default
	    mov eax,ld
	    mov dword ptr [eax].TB_LD.m,0
	    mov dword ptr [eax].TB_LD.m[4],0
	    mov [eax].TB_LD.e,0
	    .ifs sign < 0
		or [eax].ELD.e,0x8000
	    .endif
	    jmp toend
	.endsw
	.for al=[esi], al-='0': al < 10: esi++, al=[esi], al-='0'
	    mov ecx,exp_value
	    lea edx,[ecx*8+ecx]
	    add ecx,edx
	    add ecx,eax
	    mov exp_value,ecx
	.endf
	.ifs exp_sign < 0
	    neg exp_value
	.endif
    .endif
    mov edx,exp_value
    add edx,exponent
    TB_create(addr value, edx, ld)
    mov eax,ld
    .ifs sign < 0
	or [eax].ELD.e,0x8000
    .endif
toend:
	ret
strtotb endp

	END
