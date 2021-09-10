
include iostream
include iomanip
include windows.inc
include assert.inc
include SearchAPI.inc

.pragma warning(disable: 6004) ; procedure argument or local not referenced
.pragma warning(disable: 7007) ; .CASE without .ENDC: assumed fall through

;; Base abstract class for command line parsing classes

.class CParamBase

    m_fExists BOOL ?

    .inline CParamBase {
        mov [this].CParamBase.m_fExists,FALSE
        }

    Init proc argc:int_t, argv:ptr ptr wchar_t, :ptr int_t

    .inline Exists {
        mov eax,[this].CParamBase.m_fExists
        }

    .ENDS
    LPCPARAMBASE typedef ptr CParamBase

;; Simple flag-type parameter, no value, just
;; checking if it's present in command line or not.

.class CFlagParam: public CParamBase

    m_szParamName PCWSTR ?

    .inline CFlagParam :PCWSTR {
        mov [this].CFlagParam.m_szParamName,_1
        }
    .ENDS

;; Parameter with two alternative values, one value is associated with TRUE,
;; another one is FALSE correspondingly.

.class CExclFlagParam : public CParamBase

    m_fFlag BOOL ?
    m_szTrueParamName PCWSTR ?
    m_szFalseParamName PCWSTR ?

    .inline CExclFlagParam :PCWSTR, :PCWSTR {
        mov [this].CExclFlagParam.m_fFlag,FALSE
        mov [this].CExclFlagParam.m_szTrueParamName,_1
        mov [this].CExclFlagParam.m_szFalseParamName,_2
        }

    .inline Get {
        mov eax,[this].CExclFlagParam.m_fFlag
        }
    .ENDS

;; Parameter followed by some value

.class CSetValueParam : public CParamBase

    m_szParamName PCWSTR ?
    m_szValue PCWSTR ?

    .inline CSetValueParam :PCWSTR {
        mov [this].CSetValueParam.m_szParamName,_1
        mov [this].CSetValueParam.m_szValue,NULL
        }

    .inline Get {
        mov rax,[this].CSetValueParam.m_szValue
        }
    .ENDS

;; Command line parsing function

ParseParams proto :ptr ptr CParamBase, :DWORD, :int_t, :ptr ptr WCHAR

CFlagParam::Init proto :int_t, :ptr ptr wchar_t, :ptr int_t
CExclFlagParam::Init proto :int_t, :ptr ptr wchar_t, :ptr int_t
CSetValueParam::Init proto :int_t, :ptr ptr wchar_t, :ptr int_t
