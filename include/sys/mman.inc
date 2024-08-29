; MMAN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __MMAN_INC
define __MMAN_INC

include libc.inc

define PROT_NONE        0x00
define PROT_READ        0x01
define PROT_WRITE       0x02
define PROT_EXEC        0x04

define MAP_SHARED       0x01
define MAP_PRIVATE      0x02
define MAP_ANON         0x20
define MAP_ANONYMOUS    MAP_ANON

define MAP_HUGE_SHIFT   0x1A
define MAP_HUGE_2MB     (21 shl MAP_HUGE_SHIFT)
define MAP_HUGE_1GB     (30 shl MAP_HUGE_SHIFT)
define MAP_HUGETLB      0x40000

define MMAP_FLAGS       (MAP_PRIVATE or MAP_ANONYMOUS)
define MMAP_PROT        (PROT_READ or PROT_WRITE)
define MAP_FAILED       (-1)

CALL_MMAP macro s
    exitm<sys_mmap(0, (s), MMAP_PROT, MMAP_FLAGS, -1, 0)>
    endm

mprotect    proto __cdecl :ptr, :size_t, :int_t

endif

