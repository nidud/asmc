; IOSTREAM.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc
include stdint.inc

IO_RDONLY   equ 0x0000
IO_WRONLY   equ 0x0001
IO_STRBUF   equ 0x0002
IO_EOF      equ 0x4000
IO_ERROR    equ 0x8000

ptr_t       typedef ptr

.classdef   iostream syscall :ptr sbyte, :uint32_t

  base      ptr_t ?
  index     size_t ?
  count     size_t ?
  bsize     size_t ?
  file      int32_t ?
  flags     uint32_t ?

  Read      proc
  Write     proc :ptr_t, :size_t
  Flush     proc
  Getc      proc
  Putc      proc :int8_t

  .ends

.classdef   bitstream syscall :ptr sbyte, :uint32_t, :uint64_t

  base      ptr_t ?
  index     size_t ?
  count     size_t ?
  bsize     size_t ?
  file      int32_t ?
  flags     uint32_t ?
  bb        size_t ?
  bk        int8_t ?

  Read      proc
  Flush     proc
  Getbits   proc :int8_t
  Putbits   proc :size_t, :int8_t

  .ends
