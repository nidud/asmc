ifndef _INC_MBDATA
define _INC_MBDATA

include crtdefs.inc

ifdef _WIN32
define NUM_ULINFO 6
else
define NUM_ULINFO 12
endif

externdef __mdcodepage:int_t
externdef __ismbcodepage:int_t
externdef __mbulinfo:ushort_t
externdef __ptmbcinfo:pthreadmbcinfo

__updatetmbcinfo proto __cdecl

define _MBHIRALOW	0x829f
define _MBHIRAHIGH	0x82f1
define _MBKATALOW	0x8340
define _MBKATAHIGH	0x8396
define _MBKATAEXCEPT	0x837f
define _MBKIGOULOW	0x8141
define _MBKIGOUHIGH	0x81ac
define _MBKIGOUEXCEPT	0x817f

endif
