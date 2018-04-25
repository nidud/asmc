ifndef SPECSTRING_SUPP_H
SPECSTRING_SUPP_H equ <>
if NOT defined(__midl) AND defined(_PREFAST_) AND _MSC_VER GE 1000
include sal_supp.inc
else
endif
endif

