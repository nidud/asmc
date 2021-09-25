ifndef __ATLCONV_H__
define __ATLCONV_H__

include atldef.inc
include stddef.inc
include atlalloc.inc

ifndef __wtypes_h__

if not defined(_X86_) and not defined(_IA64_) and not defined(_AMD64_) and defined(_M_IX86)
define _X86_
endif

if not defined(_X86_) and not defined(_IA64_) and not defined(_AMD64_) and defined(_M_AMD64)
define _AMD64_
endif

if not defined(_X86_) and not defined(_M_IX86) and not defined(_AMD64_) and defined(_M_IA64)
if not defined(_IA64_)
define _IA64_
endif
endif

include stdarg.inc
include windef.inc
include winbase.inc
include winnls.inc

if not defined(OLE2ANSI)

OLECHAR		typedef WCHAR
LPOLESTR	typedef ptr OLECHAR
LPCOLESTR	typedef ptr OLECHAR

OLESTR macro s
exitm<L&s>
endm

else

OLECHAR		typedef SBYTE
LPOLESTR	typedef LPSTR
LPCOLESTR	typedef LPCSTR
OLESTR macro s
exitm<s>
endm

endif
endif

ifndef _OLEAUTO_H_
BSTR typedef LPWSTR
endif

ifdef _M_IX86
undef InterlockedExchangePointer
InterlockedExchangePointer proto fastcall :ptr, :ptr {
    InterlockedExchange(this, _1)
    }
endif

ATLCONV_DEADLAND_FILL equ _SECURECRT_FILL_BUFFER_PATTERN

.pragma pack(push, _ATL_PACKING)

_AtlGetConversionACP macro
ifdef _CONVERSION_DONT_USE_THREAD_LOCALE
	exitm<CP_ACP>
else
	exitm<CP_THREAD_ACP>
endif
endm

.pragma pack(pop)

endif
