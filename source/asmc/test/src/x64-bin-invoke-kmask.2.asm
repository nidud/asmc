
; v2.40.04: optimization for KMASK register

.pragma aux(k1)

foo_b proto asmcall :byte {}
foo_w proto asmcall :word {}
foo_d proto asmcall :dword {}
foo_q proto asmcall :qword {}

.code
 main proc ; KXNORx k1,k1,k1
    foo_b(-1)
    foo_w(-1)
    foo_d(-1)
    foo_q(-1)
    foo_b(0xFF)
    foo_w(0xFF)
    foo_d(0xFF)
    foo_q(0xFF)
    foo_b(0xFFFF)
    foo_w(0xFFFF)
    foo_d(0xFFFF)
    foo_q(0xFFFF)
    foo_b(0xFFFFFFFF)
    foo_w(0xFFFFFFFF)
    foo_d(0xFFFFFFFF)
    foo_q(0xFFFFFFFF)
    ret
    endp
    end
