ifndef __INTRIN0_H_
define __INTRIN0_H_
if defined(_M_IX86) and not defined(_CHPE_ONLY_)
define __MACHINEX86
endif
ifdef _M_X64
define __MACHINEX64
endif
if (defined(_M_IX86) OR defined(_M_X64)) and not defined(_CHPE_ONLY_)
define __MACHINEX86_X64
endif
endif
