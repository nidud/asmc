ifndef __ATLTRACE_H__
__ATLTRACE_H__ equ <>

include atldef.inc
include atlconv.inc
include crtdbg.inc
include stdio.inc
include stdarg.inc
include tchar.inc

.pragma pack(push,_ATL_PACKING)

.enum TraceCategories {
    TraceGeneral = 0x000001,
    TraceCom = 0x000002,
    TraceQI = 0x000004,
    TraceRegistrar = 0x000008,
    TraceRefcount = 0x000010,
    TraceWindowing = 0x000020,
    TraceControls = 0x000040,
    TraceHosting = 0x000080,
    TraceDBClient = 0x000100,
    TraceDBProvider = 0x000200,
    TraceSnapin = 0x000400,
    TraceNotImpl = 0x000800,
    TraceAllocation = 0x001000,
    TraceException = 0x002000,
    TraceTime = 0x004000,
    TraceCache = 0x008000,
    TraceStencil = 0x010000,
    TraceString = 0x020000,
    TraceMap = 0x040000,
    TraceUtil = 0x080000,
    TraceSecurity = 0x100000,
    TraceSync = 0x200000,
    TraceISAPI = 0x400000,
    TraceUser = 0x80000
    }

.template CTraceCategoryEx

    traceCategory int_t ?
    traceLevel int_t ?

    .inline CTraceCategoryEx :abs=<NULL>, :abs=<0x80000>, :abs=<0> {
        mov [this].CTraceCategoryEx.traceCategory,_2
        mov [this].CTraceCategoryEx.traceLevel,_3
        }
ifdef _DEBUG
    .inline GetLevel {
        mov eax,traceLevel
        }
    .inline GetCategory {
        mov eax,traceCategory
        }
endif
    .ENDS

.template CTraceCategory : public CTraceCategoryEx

    .inline CTraceCategory :abs=<NULL> {
        CTraceCategoryEx::CTraceCategoryEx(this, _1)
        }
    .ENDS

if 0
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceGeneral> atlTraceGeneral(_T("atlTraceGeneral"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceCom> atlTraceCOM(_T("atlTraceCOM"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceQI> atlTraceQI(_T("atlTraceQI"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceRegistrar> atlTraceRegistrar(_T("atlTraceRegistrar"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceRefcount> atlTraceRefcount(_T("atlTraceRefcount"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceWindowing> atlTraceWindowing(_T("atlTraceWindowing"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceControls> atlTraceControls(_T("atlTraceControls"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceHosting> atlTraceHosting(_T("atlTraceHosting"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceDBClient> atlTraceDBClient(_T("atlTraceDBClient"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceDBProvider> atlTraceDBProvider(_T("atlTraceDBProvider"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceSnapin> atlTraceSnapin(_T("atlTraceSnapin"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceNotImpl> atlTraceNotImpl(_T("atlTraceNotImpl"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceAllocation> atlTraceAllocation(_T("atlTraceAllocation"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceException> atlTraceException(_T("atlTraceException"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceTime> atlTraceTime(_T("atlTraceTime"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceCache> atlTraceCache(_T("atlTraceCache"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceStencil> atlTraceStencil(_T("atlTraceStencil"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceString> atlTraceString(_T("atlTraceString"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceMap> atlTraceMap(_T("atlTraceMap"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceUtil> atlTraceUtil(_T("atlTraceUtil"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceSecurity> atlTraceSecurity(_T("atlTraceSecurity"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceSync> atlTraceSync(_T("atlTraceSync"));
__declspec(selectany) CTraceCategoryEx<CTraceCategoryEx<>::TraceISAPI> atlTraceISAPI(_T("atlTraceISAPI"));
endif

ifdef _DEBUG

else

IsTracingEnabled proto :DWORD_PTR, :UINT {
    mov eax,FALSE
    }

endif


ifdef _DEBUG

else

AtlTraceNull    proto :vararg {}
AtlTraceA       proto :LPCSTR, :vararg {}
AtlTrace2A      proto :DWORD_PTR, :UINT, :LPCSTR, :vararg {}
AtlTraceW       proto :LPCWSTR, :vararg {}
AtlTrace2W      proto :DWORD_PTR, :UINT, :LPCWSTR, :vararg {}
ifdef _UNICODE
AtlTrace        equ <AtlTraceW>
else
AtlTrace        equ <AtlTraceA>
endif

ifndef ATLTRACE
ATLTRACE  equ <>
ATLTRACE2 equ <>
endif

ATLTRACENOTIMPL macro funcname
    mov eax,E_NOTIMPL
    retm<eax>
    endm
DECLARE_NOUIASSERT macro
    exitm<>
    endm

endif

ifdef _DEBUG
DECLARE_TRACE_CATEGORY macro name
    exitm<extern name:CTraceCategory>
    endm
else
DECLARE_TRACE_CATEGORY macro name
    exitm<CTraceCategory equ <name>>
    endm
endif

.pragma pack(pop)

endif
