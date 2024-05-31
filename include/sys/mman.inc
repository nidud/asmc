; MMAN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __MMAN_INC
define __MMAN_INC

include libc.inc

define PROT_READ        0x01
define PROT_WRITE       0x02
define MAP_PRIVATE      0x02
define MAP_ANON         0x20
define MAP_ANONYMOUS    MAP_ANON
define MMAP_FLAGS       (MAP_PRIVATE or MAP_ANONYMOUS)
define MMAP_PROT        (PROT_READ or PROT_WRITE)
define MAP_FAILED       (-1)

CALL_MMAP macro s
    exitm<sys_mmap(0, (s), MMAP_PROT, MMAP_FLAGS, -1, 0)>
    endm

mprotect    proto __cdecl :ptr, :size_t, :int_t

endif

