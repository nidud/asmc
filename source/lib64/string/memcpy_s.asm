; MEMCPY_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc

    .code

memcpy_s proc dst:ptr, sizeInBytes:size_t, src:ptr, count:size_t

    .if r9 == 0

        ;; nothing to do
        .return 0
    .endif

    ;; validation section
    .if rcx == NULL

        .return EINVAL
    .endif

    .if r8 == NULL || rdx < r9

        ;; zeroes the destination buffer
        memset(rcx, 0, rdx)

        .if src != NULL

            .return EINVAL
        .endif
        .if sizeInBytes >= count

            .return ERANGE
        .endif
        ;; useless, but prefast is confused
        .return EINVAL
    .endif

    xchg r8,r9
    memcpy(rcx, r9, r8)
    xor eax,eax
    ret

memcpy_s endp

    end
