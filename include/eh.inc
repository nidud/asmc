
include crtdefs.inc

ifndef _INC_EH
define _INC_EH
ifndef RC_INVOKED

.pragma pack(push, _CRT_PACKING)

ifndef _M_CEE_PURE
CALLBACKC(terminate_function)
CALLBACKC(terminate_handler)
CALLBACKC(unexpected_function)
CALLBACKC(unexpected_handler)
else
CALLBACK(terminate_function)
CALLBACK(terminate_handler)
CALLBACK(unexpected_function)
CALLBACK(unexpected_handler)
endif

ifdef _M_CEE
CALLBACK(__terminate_function_m)
CALLBACK(__terminate_handler_m)
CALLBACK(__unexpected_function_m)
CALLBACK(__unexpected_handler_m)
endif

ifndef _M_CEE_PURE
CALLBACKC(_se_translator_function, :uint_t, :ptr_t) ;struct _EXCEPTION_POINTERS *
endif

terminate               proto __cdecl
unexpected              proto __cdecl
_is_exception_typeof    proto __cdecl :ptr_t, :ptr_t

ifndef _M_CEE_PURE
set_terminate           proto __cdecl :terminate_function
_get_terminate          proto __cdecl
set_unexpected          proto __cdecl :unexpected_function
_get_unexpected         proto __cdecl
endif

ifndef _M_CEE_PURE
_set_se_translator      proto __cdecl :_se_translator_function
endif
__uncaught_exception    proto __cdecl

ifdef _M_CEE
set_terminate           proto __cdecl :int_t
set_unexpected          proto __cdecl :int_t
endif

.pragma pack(pop)
endif ;; RC_INVOKED
endif ;; _INC_EH
