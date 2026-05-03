ifndef __SPECSTRINGS_STRICT_LEVEL
define __SPECSTRINGS_STRICT_LEVEL
endif
if (_MSC_VER GE 1400) AND NOT defined(__midl) AND NOT defined(_PREFAST_) AND (__SPECSTRINGS_STRICT_LEVEL GT 0)
include specstrings_undef.inc
endif
