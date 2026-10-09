timeit:
        asmc64 -q -bin -Gw- -Fo 1 ../../../libc/math/cos.asm
        asmc64 -q -bin -Fo 2 fpu.asm
        asmc64 -q -pe $*.asm
        $*
        del *.bin
        del $*.exe
