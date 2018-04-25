ifndef DRIVERSPECS_H
DRIVERSPECS_H equ <>
.pragma list(push, 0)
ifndef SPECSTRINGS_H
include specstrings.inc
endif
include sdv_driverspecs.inc

if (_MSC_VER GE 1000) AND NOT defined(__midl) AND defined(_PREFAST_)
else
endif

if (_MSC_VER GE 1000) AND NOT defined(__midl) AND defined(_PREFAST_) AND defined(_MSC_EXTENSIONS)
else
endif

.pragma list(pop)
endif

