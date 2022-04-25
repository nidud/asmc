include Windows.inc
include crtdbg.inc
include intrin.inc
include malloc.inc
include stdlib.inc
include vcruntime.inc

ifndef __UNIX__
externdef __ImageBase:IMAGE_DOS_HEADER
endif
