;
; v2.36.36 - XACQUIRE and XRELEASE prefix
;
ifndef __ASMC64__
    .x64
    .model flat
endif

.data
    mem dq 0
.code

    LOCK ADD mem,rax
    LOCK ADC mem,rax
    LOCK AND mem,rax
    LOCK BTC mem,1
    LOCK BTR mem,1
    LOCK BTS mem,1
    LOCK CMPXCHG mem,rax
    LOCK CMPXCHG8B mem
    LOCK DEC mem
    LOCK INC mem
    LOCK NEG mem
    LOCK NOT mem
    LOCK OR  mem,rax
    LOCK SBB mem,rax
    LOCK SUB mem,rax
    LOCK XOR mem,rax
    LOCK XADD mem,rax

    XCHG mem,rax
    LOCK XCHG mem,rax

    XACQUIRE ADD mem,rax
    XACQUIRE ADC mem,rax
    XACQUIRE AND mem,rax
    XACQUIRE BTC mem,1
    XACQUIRE BTR mem,1
    XACQUIRE BTS mem,1
    XACQUIRE CMPXCHG mem,rax
    XACQUIRE CMPXCHG8B mem
    XACQUIRE DEC mem
    XACQUIRE INC mem
    XACQUIRE NEG mem
    XACQUIRE NOT mem
    XACQUIRE OR  mem,rax
    XACQUIRE SBB mem,rax
    XACQUIRE SUB mem,rax
    XACQUIRE XOR mem,rax
    XACQUIRE XADD mem,rax
    XACQUIRE XCHG mem,rax

    XRELEASE ADD mem,rax
    XRELEASE ADC mem,rax
    XRELEASE AND mem,rax
    XRELEASE BTC mem,1
    XRELEASE BTR mem,1
    XRELEASE BTS mem,1
    XRELEASE CMPXCHG mem,rax
    XRELEASE CMPXCHG8B mem
    XRELEASE DEC mem
    XRELEASE INC mem
    XRELEASE NEG mem
    XRELEASE NOT mem
    XRELEASE OR  mem,rax
    XRELEASE SBB mem,rax
    XRELEASE SUB mem,rax
    XRELEASE XOR mem,rax
    XRELEASE XADD mem,rax
    XRELEASE XCHG mem,rax
    XRELEASE MOV mem,0
    XRELEASE MOV mem,rax

    XACQUIRE LOCK ADD mem,rax
    XACQUIRE LOCK ADC mem,rax
    XACQUIRE LOCK AND mem,rax
    XACQUIRE LOCK BTC mem,1
    XACQUIRE LOCK BTR mem,1
    XACQUIRE LOCK BTS mem,1
    XACQUIRE LOCK CMPXCHG mem,rax
    XACQUIRE LOCK CMPXCHG8B mem
    XACQUIRE LOCK DEC mem
    XACQUIRE LOCK INC mem
    XACQUIRE LOCK NEG mem
    XACQUIRE LOCK NOT mem
    XACQUIRE LOCK OR  mem,rax
    XACQUIRE LOCK SBB mem,rax
    XACQUIRE LOCK SUB mem,rax
    XACQUIRE LOCK XOR mem,rax
    XACQUIRE LOCK XADD mem,rax
    XACQUIRE LOCK XCHG mem,rax ; LOCK prefix removed

    XRELEASE LOCK ADD mem,rax
    XRELEASE LOCK ADC mem,rax
    XRELEASE LOCK AND mem,rax
    XRELEASE LOCK BTC mem,1
    XRELEASE LOCK BTR mem,1
    XRELEASE LOCK BTS mem,1
    XRELEASE LOCK CMPXCHG mem,rax
    XRELEASE LOCK CMPXCHG8B mem
    XRELEASE LOCK DEC mem
    XRELEASE LOCK INC mem
    XRELEASE LOCK NEG mem
    XRELEASE LOCK NOT mem
    XRELEASE LOCK OR  mem,rax
    XRELEASE LOCK SBB mem,rax
    XRELEASE LOCK SUB mem,rax
    XRELEASE LOCK XOR mem,rax
    XRELEASE LOCK XADD mem,rax
    XRELEASE LOCK XCHG mem,rax ; LOCK prefix removed

    XRELEASE MOV mem,0
    XRELEASE MOV mem,rax
    XRELEASE LOCK MOV mem,0   ; LOCK prefix removed
    XRELEASE LOCK MOV mem,rax ; LOCK prefix removed

    end
