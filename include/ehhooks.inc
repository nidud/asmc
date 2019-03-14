
CALLBACKC(_inconsistency_function)
_inconsistency proto WINAPI
__set_inconsistency proto __cdecl :_inconsistency_function

ifdef _MT
else
externdef __pTerminate:terminate_function
externdef __pUnexpected:unexpected_function
externdef __pSETranslator:_se_translator_function
endif

externdef __pInconsistency:_inconsistency_function

__CxxUnhandledExceptionFilter proto WINAPI \
                      : LPEXCEPTION_POINTERS
