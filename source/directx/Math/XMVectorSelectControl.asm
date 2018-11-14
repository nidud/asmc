; XMVECTORSELECTCONTROL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:nosave noauto

XMVectorSelectControl proc XM_CALLCONV VectorIndex0:uint32_t, VectorIndex1:uint32_t, VectorIndex2:uint32_t, VectorIndex3:uint32_t

  local ControlVector:XMFLOAT4
  local ControlElement[2]:uint32_t

    .assert(rcx < 2)
    .assert(rdx < 2)
    .assert(r8  < 2)
    .assert(r9  < 2)

    mov ControlElement[0],XM_SELECT_0
    mov ControlElement[4],XM_SELECT_1

    mov eax,ControlElement[rcx*4]
    mov ControlVector.x,eax
    mov eax,ControlElement[rdx*4]
    mov ControlVector.y,eax
    mov eax,ControlElement[r8*4]
    mov ControlVector.z,eax
    mov eax,ControlElement[r9*4]
    mov ControlVector.w,eax

    _mm_store_ps(xmm0, ControlVector)
    ret

XMVectorSelectControl endp

    end
