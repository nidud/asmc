;;
;; PCG Random Number Generation for C.
;;
;; Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
;;
;; Licensed under the Apache License, Version 2.0 (the "License");
;; you may not use this file except in compliance with the License.
;; You may obtain a copy of the License at
;;
;;     http://www.apache.org/licenses/LICENSE-2.0
;;
;; Unless required by applicable law or agreed to in writing, software
;; distributed under the License is distributed on an "AS IS" BASIS,
;; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;; See the License for the specific language governing permissions and
;; limitations under the License.
;;
;; For additional information about the PCG random number generation scheme,
;; including its license and other licensing options, visit
;;
;;       http://www.pcg-random.org
;;

;;
;; This code is derived from the full C implementation, which is in turn
;; derived from the canonical C++ PCG implementation. The C++ version
;; has many additional features and is preferable if you can use C++ in
;; your project.
;;

pcg_state_setseq_64 struct
    state   dq ?
    _inc    dq ?
pcg_state_setseq_64 ends

pcg32_random_t typedef pcg_state_setseq_64

.data
pcg32_global pcg32_random_t { 0x853c49e6748fea9b, 0xda3e39cb94b95bdb }

.code

pcg32_srandom::

    mov     r8,rdx
    mov     rdx,rcx
    lea     rcx,pcg32_global

pcg32_srandom_r::

    push    rdx
    push    rcx
    add     r8,r8
    or      r8,1
    xor     eax,eax
    mov     [rcx].pcg32_random_t._inc,r8
    mov     [rcx].pcg32_random_t.state,rax
    call    pcg32_random_r
    pop     rcx
    pop     rdx
    add     [rcx].pcg32_random_t.state,rdx
    jmp     pcg32_random_r

pcg32_random::

    lea     rcx,pcg32_global

pcg32_random_r::

    mov     r8,[rcx].pcg32_random_t.state
    mov     rax,6364136223846793005
    mul     r8
    add     rax,[rcx].pcg32_random_t._inc
    mov     [rcx].pcg32_random_t.state,rax

    mov     rax,r8
    sar     rax,18
    xor     rax,r8
    sar     rax,27

    mov     rcx,r8
    shr     rcx,59
    mov     rdx,rax
    shr     rdx,cl
    neg     ecx
    and     ecx,31
    shl     eax,cl
    or      eax,edx
    ret

pcg32_boundedrand::

    mov     edx,ecx
    lea     rcx,pcg32_global

pcg32_boundedrand_r::

    mov     eax,edx
    neg     eax
    mov     r9d,edx
    xor     edx,edx
    div     r9d
    mov     r11d,edx
    mov     r10,rcx

    .for (::)

        mov rcx,r10
        pcg32_random_r()

        .continue(0) .if (eax < r11d)

        xor edx,edx
        div r9d
        mov eax,edx
        ret
    .endf

    end
