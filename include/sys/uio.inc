; UIO.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __UIO_INC
define __UIO_INC

include sys/types.inc

iovec       struc
iov_base    ptr_t ?     ; Starting address
iov_len     size_t ?    ; Number of bytes
iovec       ends

readv       proto __cdecl :int_t, :ptr iovec, :int_t
writev      proto __cdecl :int_t, :ptr iovec, :int_t
preadv      proto __cdecl :int_t, :ptr iovec, :int_t, :off_t
pwritev     proto __cdecl :int_t, :ptr iovec, :int_t, :off_t
preadv2     proto __cdecl :int_t, :ptr iovec, :int_t, :off_t, :int_t
pwritev2    proto __cdecl :int_t, :ptr iovec, :int_t, :off_t, :int_t

endif

