ifndef _MM3DNOW_H_INCLUDED
_MM3DNOW_H_INCLUDED equ <>
.pragma list(push, 0)

ifndef _M_IX86
.err <This header is specific to X86 targets>
endif

include vcruntime.inc
include mmintrin.inc
include xmmintrin.inc

_m_femms        proto WINAPI
_m_pavgusb      proto :qword, :qword
_m_pf2id        proto :qword
_m_pfacc        proto :qword, :qword
_m_pfadd        proto :qword, :qword
_m_pfcmpeq      proto :qword, :qword
_m_pfcmpge      proto :qword, :qword
_m_pfcmpgt      proto :qword, :qword
_m_pfmax        proto :qword, :qword
_m_pfmin        proto :qword, :qword
_m_pfmul        proto :qword, :qword
_m_pfrcp        proto :qword
_m_pfrcpit1     proto :qword, :qword
_m_pfrcpit2     proto :qword, :qword
_m_pfrsqrt      proto :qword
_m_pfrsqit1     proto :qword, :qword
_m_pfsub        proto :qword, :qword
_m_pfsubr       proto :qword, :qword
_m_pi2fd        proto :qword
_m_pmulhrw      proto :qword, :qword
_m_prefetch     proto
_m_prefetchw    proto :ptr

_m_from_float   proto :real4
_m_to_float     proto :qword
_m_pf2iw        proto :qword
_m_pfnacc       proto :qword, :qword
_m_pfpnacc      proto :qword, :qword
_m_pi2fw        proto :qword
_m_pswapd       proto :qword

.pragma list(pop)
endif
