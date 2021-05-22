
    .486
    .model flat, fastcall

S1 struct
    m db ?
    a proc
S1 ends

.template T1
    p ptr S1 ?
    a proc
   .ends
.template T2
    p ptr T1 ?
    a proc
   .ends
.template T3
    p ptr T2 ?
    a proc
   .ends
   .code

main proc

  .new a:T3
  .new b:S1
  .new p:ptr T3
  .new q:ptr S1

    a.p.a()
    a.p.p.a()
    a.p.p.p.a()

    q.a()
    p.p.a()
    p.p.p.a()
    p.p.p.p.a()
    ret

main endp

    end


a = 3555r
b = 1.0 / 3.0

%echo @CatStr(<a = >, %a)
%echo @CatStr(<b = >, %a)
end

include asmc.inc
include symbols.inc

.code

bar proc a:ptr
    ret
bar endp

foo proc p:ptr esym

    p.info.regslist()

    mov eax,1
    ret
foo endp
end
    mov ecx,p.segm.name()
    bar(bar(1))

    .return .if ( [eax].asym.scoped() )
    .return .if ( p.used() || [eax].asym.scoped() )

    p.set_used        (0)
    p.set_isdefined   (0)
    p.set_scoped      (0)
    p.set_iat_used    (0)
    p.set_isequate    (0)
    p.set_predefined  (0)
    p.set_variable    (0)
    p.set_ispublic    (0)

include ltype.inc
.code
main proc name:ptr sbyte
    .if ( islspace( edx ) )
        nop
    .endif

    mov name,ltokstart(name)
    ret

main endp

end
    .if ( !islspace( [edx] ) )
        .switch ( eax )
        .case 'T'
            nop
        .endsw
    .endif

.486
.model flat, c

n = -1.0e-1808
%echo @CatStr(%n)

.data
r3 real16 2.0

bytecount = typeof r3
%echo Size of bytecount = @CatStr(%bytecount)

end
if bytecount eq 17
echo Size of bytecount = 16
else
%echo Size of bytecount = @CatStr(%bytecount)
endif

type macro p
%echo @CatStr(%typeof(p))
endm

size macro p
%echo @CatStr(%bytecount)
endm

include stdio.inc

.template T watcall

    m db ?

    .inline m { retm<[eax].T.m> }

    .ends

    .code

main proc

  .new a:ptr T
  .new b:byte

    mov b,a.m()

    ret

main endp

    end

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    option win64:3

D0T typedef proto :ptr
D1T typedef proto :ptr, :ptr, :ptr, :ptr, :ptr
D0  typedef ptr D0T
D1  typedef ptr D1T

xx  struc
l1  D0 ?
l2  D1 ?
xx  ends

LPXX typedef ptr xx

.class Class
    l1  proc
    l2  D1 ?
   .ends
PCLASS typedef ptr Class

.data
p LPXX ?
q D1 ?
x xx <>
o PCLASS ?

type(r1)
type(r2)
type(r3)

size(r1)
size(r2)
size(r3)

.code
    o.l1()

    q( 0, 1, 2, 3, 4 )

    x.l1( 0 )
    x.l2( 0, 1, 2, 3, 4 )

    p.l1(0)
    p.l2( 0, 1, 2, 3, 4 )
    o.l2( 1, 2, 3, 4 )

    [rcx].Class.l1()
    [rcx].Class.l2(1, 2, 3, 4)

foo proc

  local lp:LPXX, lo:PCLASS

    q( 0, 1, 2, 3, 4 )

    p.l1(0)
    o.l1()
    p.l2( 0, 1, 2, 3, 4 )
    o.l2( 1, 2, 3, 4 )

    lp.l1(0)
    lo.l1()
    lp.l2( 0, 1, 2, 3, 4 )
    lo.l2( 1, 2, 3, 4 )

    [rax].Class.l1()
    [rax].Class.l2(1, 2, 3, 4)
    ret

foo endp

    end
    .386
    .MODEL FLAT, stdcall
    option casemap:none

S1 struct
    db ?
S1 ends

TM1 macro
    E1=E1+1
    exitm <E1>
    endm

    .data

E1 = 0
    S1 300 dup (<.LOW (TM1()+002+003)>)

    end

include limits.inc
include stdio.inc
include errno.inc
include string.inc
include quadmath.inc

    T equ <@CStr>

.template assert fastcall

    lastResult byte ?

    .static assert {

        mov this.lastResult,0
        ;_set_errno(0)
        }
;;;;;;;;

    .static mulq {
        this.__v(mulq, 0.0, 0.0, 0.0)
        }

    .static cqfcvt {
        this.__qd( 0.0,             T( "0" ) )
        this.__qd( 1.0,             T( "1" ) )
        this.__qd(-1.0,             T("-1" ) )
        this.__qd( 1.0,             T( "1.0" ), 0, 1 )
        this.__qd( 1.0e+100,        T( "1.0e+100" ), 'e', 1 )
        this.__qd( 1.0,             T( "1" ), 'g', 6 )
        this.__qd( 1.0,             T( "1.000000" ), 0, 6 )
        this.__qd( -9.0e28,         T( "-9.000000000000000000e+028" ), 'e', 18 )
        this.__qd( -9.0e-28,        T( "-9.00000000000000000000000000000000e-028" ), 'e', 32 )
        this.__qd( -9.0e+2888,      T( "-9.00000000000000000000000000000000e+2888" ), 'e', 32 )
        this.__qd( -9.0e+28,        T( "-90000000000000000000000000000" ) )
        this.__qd( -1.0e23,         T( "-100000000000000000000000" ) )
        this.__qd( -1.0e-23,        T( "-0.00000000000000000000001" ), 0, 23 )

        this.__qd( 100001.0e0,      T( "1.00001e+005" ),     'e', 5 )
        this.__qd( 100001.0e-1,     T( "1.00001e+004" ),     'e', 5 )
        this.__qd( 1000001.0e-1,    T( "1.000001e+005" ),    'e', 6 )
        this.__qd( 10000001.0e-1,   T( "1.0000001e+006" ),   'e', 7 )
        this.__qd( 100000001.0e-1,  T( "1.00000001e+007" ),  'e', 8 )
        this.__qd( 1000000001.0e-1, T( "1.000000001e+008" ), 'e', 9 )
        this.__qd( 1000000001.0e-1, T( "1.00000000100000000000000000000000e+008" ), 'e', 32 )

        this.__qd( 100001.0e1,      T( "1.00001e+006" ),     'e', 5 )
        this.__qd( 1000001.0e1,     T( "1.000001e+007" ),    'e', 6 )
        this.__qd( 10000001.0e1,    T( "1.0000001e+008" ),   'e', 7 )
        this.__qd( 100000001.0e1,   T( "1.00000001e+009" ),  'e', 8 )
        this.__qd( 1000000001.0e1,  T( "1.000000001e+010" ), 'e', 9 )

        this.__qd( 100000000000001.0e96,    T( "1.000000000000010e+110" ),  'e', 15 )
        this.__qd( 100000000000001.0e-96,   T( "1.000000000000010e-082" ),  'e', 15 )
        this.__qd( 100000000000001.0e4896,  T( "1.000000000000010e+4910" ), 'e', 15 )
        this.__qd( 100000000000001.0e-4896, T( "1.000000000000010e-4882" ), 'e', 15 )
        this.__qd( 123456789123456.1234567, T( "123456789123456.1234567" ),  0, 7 )
        this.__qd( 3.141592653589793238462643383279502884197169399375105820974945, T( "3.141592653589793238462643383279502" ), 0, 33 )

        }
        .static __qd :abs, :abs, :abs=<0>, :abs=<0>, :abs=<_ST_QUADFLOAT> {
            local a, b, c, p, f
            .data
                align 16
                a real16 _1
                b char_t 128 dup(?)
                c int_t _3 ; type char
                p int_t _4 ; precision value
                f int_t _5
            .code
            _cqcvt(addr a, addr b, c, p, f)
            .if strcmp(addr _2, addr b)
                printf(addr format, addr _2, addr b)
            .endif
            .assert( eax == 0 )
            }

    .ends
    .code

main proc

    .new this:assert()
    .new format[10]:byte

    ; */+-

    this.cqfcvt()

    ret

main endp

    end

;
; v2.30.10 - Name order..
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    ptr_t typedef ptr

.class C
    ;C   ptr_t ?
    Class   ptr_t ?
    C       proc :ptr
    Class   proc :ptr
    .ends

    .code

    option win64:2

    assume rcx:ptr C

foo proc

  local p:ptr C

    C(0)
    p.Class(1)
    [rcx].Class(3)
    mov rax,[rcx].Class

    ret

foo endp

C::C proc x:ptr
    ret
C::C endp

    end

include libc.inc

    .code

    option casemap:none, win64:auto

.template X
    atom byte ?
    .inline A :vararg { nop }
    .ends

.template Y : public X
    .inline B :vararg { nop }
    .ends

.template T : public Y
    .inline T :vararg {}
    .inline C :vararg { nop }
    .ends

    .code

main proc

  .new a:T()

    a.A() ; nop
    a.B() ; nop
    a.C() ; nop

    ret

main endp

    end


foo proc watcall a:dword, b:sdword
    mov eax,a
    mov eax,b
    ret
foo endp

bar proc a:byte, b:sbyte
    foo(a, b)
    ret
bar endp
end

foo proc p:ptr esym
    .return( 0 ) .if ( p.has_vararg() )
    mov eax,1
    ret
foo endp


foo proto a:byte {
    ;mov al,a
    retm<al !<= dl>
    }

.code
main proc
    local asmcall:byte
    .if foo(1)
    .endif
    ret
main endp
end