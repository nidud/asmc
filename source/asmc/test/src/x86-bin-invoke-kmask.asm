
; v2.40.01: .pragma aux(pop) and KMASK

.686
.model flat, c
.xmm

.pragma aux(k1)

foo_b proto asmcall :byte {}
foo_w proto asmcall :word {}
foo_d proto asmcall :dword {}
foo_q proto asmcall :qword {}

.pragma aux(pop)

bar_b proto asmcall :byte {}
bar_w proto asmcall :word {}
bar_d proto asmcall :dword {}
bar_q proto asmcall :qword {}

baz proto vectorcall :byte, :byte, :byte, :byte, :byte {}

.code
 main proc
    ; load KMASK
    foo_b([edx])
    foo_w([edx])
    foo_d([edx])
    foo_q([edx])
    foo_b(k0)
    foo_w(k0)
    foo_d(k0)
    foo_q(k0)
    foo_b(1)
    foo_w(1)
    foo_d(1)
    foo_q(1)
    foo_q(0x7FFFFFFFFFFF)
    ; KMASK to GPR
    bar_b(k0)
    bar_w(k0)
    bar_d(k0)
    bar_q(k0)
    ; KMASK to stack
    baz(k0,k1,k2,k3,k4)
    ret
    endp
    end
