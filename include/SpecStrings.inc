ifndef SPECSTRINGS_H
SPECSTRINGS_H equ <>
.pragma list(push, 0)

include sal_supp.inc
include specstrings_supp.inc
include sal.inc

ifndef __SAL_H_FULL_VER
__SAL_H_FULL_VER equ 140050727
endif

if __SAL_H_FULL_VER LE 140050727
if NOT defined(__midl) AND defined(_PREFAST_) AND _MSC_VER GE 1000
else
endif
endif

if (_MSC_VER GE 1000) AND NOT defined(__midl) AND defined(_PREFAST_)
if defined(_MSC_EXTENSIONS) OR defined(_PREFAST_) OR defined(OACR)
endif
else
endif

if defined(_MSC_EXTENSIONS) OR defined(_PREFAST_) OR defined(OACR)
else
endif

ifdef _PREFIX_
endif

ifndef SORTPP_PASS
include specstrings_strict.inc
endif
include driverspecs.inc

.pragma list(pop)
endif
