ifdef name
flags = -DFUNC=$(name) -DVALUE=$(value)
ifdef value2
flags += -DVALUE2=$(value2)
endif
endif

all: cos cosf sin sinf acos acosf asin asinf atan atanf tan tanf _hypot _hypotf
cos:
        make -h -s name=$* value=1.0 test
cosf:
        make -h -s name=$* value=1.0 testf
sin:
        make -h -s name=$* value=1.0 test
sinf:
        make -h -s name=$* value=1.0 testf
acos:
        make -h -s name=$* value=0.0 test
acosf:
        make -h -s name=$* value=0.6 testf
asin:
        make -h -s name=$* value=1.0 test
asinf:
        make -h -s name=$* value=1.0 testf
atan:
        make -h -s name=$* value=1.0 test
atanf:
        make -h -s name=$* value=1.0 testf
tan:
        make -h -s name=$* value=1.0 test
tanf:
        make -h -s name=$* value=1.0 testf
_hypot:
        make -h -s name=$* value=2.0 value2=3.0 test
_hypotf:
        make -h -s name=$* value=2.0 value2=3.0 testf
test:
        asmc64 -q -bin -Gw- -Fo 1 ../../../libc/math/$(name).asm
        asmc64 -q -bin -Gw- -Fo 2 ../../../libc/intrin/__vdecl_$(name)2.asm
        asmc64 -q -bin -home -Fo 3 fpu/$(name).asm
        asmc64 -q -pe $(flags) timeit.asm
        timeit $(name).txt
        del *.bin
        del timeit.exe
testf:
        asmc64 -q -bin -Gw- -Fo 1 ../../../libc/math/$(name).asm
        asmc64 -q -bin -Gw- -Fo 2 ../../../libc/intrin/__vdecl_$(name)4.asm
        asmc64 -q -bin -home -Fo 3 fpu/$(name).asm
        asmc64 -q -pe $(flags) -DISFLOAT timeit.asm
        timeit $(name).txt
        del *.bin
        del timeit.exe
