ifndef _INC_CMSGS
define _INC_CMSGS

ifndef _CRTBLD
.err <ERROR: Use of C runtime library internal header file.>
endif

EOL                 equ <"\r\n">

_RT_STACK_TXT       equ <L"R6000" EOL "- stack overflow" EOL>
_RT_FLOAT_TXT       equ <L"R6002" EOL "- floating point support not loaded" EOL>
_RT_INTDIV_TXT      equ <L"R6003" EOL "- integer divide by 0" EOL>
_RT_SPACEARG_TXT    equ <L"R6008" EOL "- not enough space for arguments" EOL>
_RT_SPACEENV_TXT    equ <L"R6009" EOL "- not enough space for environment" EOL>
_RT_ABORT_TXT       equ <L"R6010" EOL "- abort() has been called" EOL>
_RT_THREAD_TXT      equ <L"R6016" EOL "- not enough space for thread data" EOL>
_RT_LOCK_TXT        equ <L"R6017" EOL "- unexpected multithread lock error" EOL>
_RT_HEAP_TXT        equ <L"R6018" EOL "- unexpected heap error" EOL>
_RT_OPENCON_TXT     equ <L"R6019" EOL "- unable to open console device" EOL>
_RT_NONCONT_TXT     equ <L"R6022" EOL "- non-continuable exception" EOL>
_RT_INVALDISP_TXT   equ <L"R6023" EOL "- invalid exception disposition" EOL>

_RT_ONEXIT_TXT      equ <L"R6024" EOL "- not enough space for _onexit/atexit table" EOL>
_RT_PUREVIRT_TXT    equ <L"R6025" EOL "- pure virtual function call" EOL>
_RT_STDIOINIT_TXT   equ <L"R6026" EOL "- not enough space for stdio initialization" EOL>
_RT_LOWIOINIT_TXT   equ <L"R6027" EOL "- not enough space for lowio initialization" EOL>
_RT_HEAPINIT_TXT    equ <L"R6028" EOL "- unable to initialize heap" EOL>
_RT_CRT_NOTINIT_TXT equ <L"R6030" EOL "- CRT not initialized" EOL>

_RT_CRT_INIT_CONFLICT_TXT equ <L"R6031" EOL "- Attempt to initialize the CRT more than once.\n" \
    "This indicates a bug in your application." EOL>
_RT_LOCALE_TXT      equ <L"R6032" EOL "- not enough space for locale information" EOL>

_RT_CRT_INIT_MANAGED_CONFLICT_TXT equ <L"R6033" EOL "- Attempt to use MSIL code from this assembly during native code initialization\n" \
    "This indicates a bug in your application. It is most likely the result of calling an MSIL-compiled (/clr) function from a native constructor or from DllMain." EOL>

_RT_ONEXIT_VAR_TXT  equ <L"R6034" EOL "- inconsistent onexit begin-end variables" EOL>

_RT_COOKIE_INIT_TXT equ <L"Microsoft Visual C++ Runtime Library, Error R6035 - " \
                          "A module in this application is initializing the module's " \
                          "global security cookie while a function relying on that " \
                          "security cookie is active.  Call __security_init_cookie earlier.">

_RT_DOMAIN_TXT      equ <L"DOMAIN error">
_RT_SING_TXT        equ <L"SING error">
_RT_TLOSS_TXT       equ <L"TLOSS error">

_RT_CRNL_TXT        equ <L"\r\n">
_RT_BANNER_TXT      equ <L"runtime error ">


endif ;; _INC_CMSGS
