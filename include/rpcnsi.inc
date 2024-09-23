ifndef __RPCNSI_H__
define __RPCNSI_H__
ifndef __LIBC_INC
 include libc.inc
endif

RPC_NS_HANDLE	typedef ptr

RPC_C_NS_SYNTAX_DEFAULT		equ 0
RPC_C_NS_SYNTAX_DCE		equ 3

RPC_C_PROFILE_DEFAULT_ELT	equ 0
RPC_C_PROFILE_ALL_ELT		equ 1
RPC_C_PROFILE_ALL_ELTS		equ RPC_C_PROFILE_ALL_ET
RPC_C_PROFILE_MATCH_BY_IF	equ 2
RPC_C_PROFILE_MATCH_BY_MBR	equ 3
RPC_C_PROFILE_MATCH_BY_BOTH	equ 4

RPC_C_NS_DEFAULT_EXP_AGE	equ -1


RpcNsBindingExportA proto WINAPI :DWORD, :LPBYTE, :RPC_IF_HANDLE, :ptr, :ptr
RpcNsBindingUnexportA proto WINAPI :DWORD, :LPBYTE, :RPC_IF_HANDLE, :ptr
ifdef RPC_UNICODE_SUPPORTED
RpcNsBindingExportW proto WINAPI :DWORD, :LPWORD, :RPC_IF_HANDLE, :ptr, :ptr
RpcNsBindingUnexportW proto WINAPI :DWORD, :LPWORD, :RPC_IF_HANDLE, :ptr
endif
RpcNsBindingLookupBeginA proto WINAPI :DWORD, :LPBYTE, :RPC_IF_HANDLE, :ptr, :DWORD, :ptr
ifdef RPC_UNICODE_SUPPORTED
RpcNsBindingLookupBeginW proto WINAPI :DWORD, :LPWORD, :RPC_IF_HANDLE, :ptr, :DWORD, :ptr
endif
RpcNsBindingLookupNext proto WINAPI :RPC_NS_HANDLE, :ptr
RpcNsBindingLookupDone proto WINAPI :ptr
RpcNsGroupDeleteA proto WINAPI :DWORD, :LPBYTE
RpcNsGroupMbrAddA proto WINAPI :DWORD, :LPBYTE, :DWORD, :LPBYTE
RpcNsGroupMbrRemoveA proto WINAPI :DWORD, :LPBYTE, :DWORD, :LPBYTE
RpcNsGroupMbrInqBeginA proto WINAPI :DWORD, :LPBYTE, :DWORD, :ptr
RpcNsGroupMbrInqNextA proto WINAPI :RPC_NS_HANDLE, :LPBYTE

ifdef RPC_UNICODE_SUPPORTED
RpcNsGroupDeleteW proto WINAPI :DWORD, :LPWORD
RpcNsGroupMbrAddW proto WINAPI :DWORD, :LPWORD, :DWORD, :LPWORD
RpcNsGroupMbrRemoveW proto WINAPI :DWORD, :LPWORD, :DWORD, :LPWORD
RpcNsGroupMbrInqBeginW proto WINAPI :DWORD, :LPWORD, :DWORD, :ptr
RpcNsGroupMbrInqNextW proto WINAPI :RPC_NS_HANDLE, :LPWORD
endif
RpcNsGroupMbrInqDone proto WINAPI :ptr
RpcNsProfileDeleteA proto WINAPI :DWORD, :LPBYTE
RpcNsProfileEltAddA proto WINAPI :DWORD, :LPBYTE, :ptr, :DWORD, :LPBYTE, :DWORD, :LPBYTE
RpcNsProfileEltRemoveA proto WINAPI :DWORD, :LPBYTE, :ptr, :DWORD, :LPBYTE
RpcNsProfileEltInqBeginA proto WINAPI :DWORD, :LPBYTE, :DWORD, :ptr, :DWORD, :DWORD, :LPBYTE, :ptr
RpcNsProfileEltInqNextA proto WINAPI :RPC_NS_HANDLE, :ptr, :LPBYTE, :LPDWORD, :LPBYTE

ifdef RPC_UNICODE_SUPPORTED
RpcNsProfileDeleteW proto WINAPI :DWORD, :LPWORD
RpcNsProfileEltAddW proto WINAPI :DWORD, :LPWORD, :ptr, :DWORD, :LPWORD, :DWORD, :LPWORD
RpcNsProfileEltRemoveW proto WINAPI :DWORD, :LPWORD, :ptr, :DWORD, :LPWORD
RpcNsProfileEltInqBeginW proto WINAPI :DWORD, :LPWORD, :DWORD, :ptr, :DWORD, :DWORD, :LPWORD, :ptr
RpcNsProfileEltInqNextW proto WINAPI :RPC_NS_HANDLE, :ptr, :LPWORD, :LPDWORD, :LPWORD
endif

RpcNsProfileEltInqDone proto WINAPI :ptr
RpcNsEntryObjectInqBeginA proto WINAPI :DWORD, :LPBYTE, :ptr
ifdef RPC_UNICODE_SUPPORTED
RpcNsEntryObjectInqBeginW proto WINAPI :DWORD, :LPWORD, :ptr
endif

RpcNsEntryObjectInqNext proto WINAPI :RPC_NS_HANDLE, :ptr
RpcNsEntryObjectInqDone proto WINAPI :ptr
RpcNsEntryExpandNameA proto WINAPI :DWORD, :LPBYTE, :LPBYTE
RpcNsMgmtBindingUnexportA proto WINAPI :DWORD, :LPBYTE, :ptr, :DWORD, :ptr
RpcNsMgmtEntryCreateA proto WINAPI :DWORD, :LPBYTE
RpcNsMgmtEntryDeleteA proto WINAPI :DWORD, :LPBYTE
RpcNsMgmtEntryInqIfIdsA proto WINAPI :DWORD, :LPBYTE, :ptr
RpcNsMgmtHandleSetExpAge proto WINAPI :RPC_NS_HANDLE, :DWORD
RpcNsMgmtInqExpAge proto WINAPI :LPDWORD
RpcNsMgmtSetExpAge proto WINAPI :DWORD

ifdef RPC_UNICODE_SUPPORTED
RpcNsEntryExpandNameW proto WINAPI :DWORD, :LPWORD, :LPWORD
RpcNsMgmtBindingUnexportW proto WINAPI :DWORD, :LPWORD, :ptr, :DWORD, :ptr
RpcNsMgmtEntryCreateW proto WINAPI :DWORD, :LPWORD
RpcNsMgmtEntryDeleteW proto WINAPI :DWORD, :LPWORD
RpcNsMgmtEntryInqIfIdsW proto WINAPI :DWORD, :LPWORD, :ptr
endif

RpcNsBindingImportBeginA proto WINAPI :DWORD, :LPBYTE, :RPC_IF_HANDLE, :ptr, :ptr
ifdef RPC_UNICODE_SUPPORTED
RpcNsBindingImportBeginW proto WINAPI :DWORD, :LPWORD, :RPC_IF_HANDLE, :ptr, :ptr
endif
RpcNsBindingImportNext proto WINAPI :RPC_NS_HANDLE, :ptr
RpcNsBindingImportDone proto WINAPI :ptr
RpcNsBindingSelect proto WINAPI :ptr, :ptr

ifdef _UNICODE

RpcNsBindingLookupBegin equ <RpcNsBindingLookupBeginW>
RpcNsBindingImportBegin equ <RpcNsBindingImportBeginW>
RpcNsBindingExport	equ <RpcNsBindingExportW>
RpcNsBindingUnexport	equ <RpcNsBindingUnexportW>
RpcNsGroupDelete	equ <RpcNsGroupDeleteW>
RpcNsGroupMbrAdd	equ <RpcNsGroupMbrAddW>
RpcNsGroupMbrRemove	equ <RpcNsGroupMbrRemoveW>
RpcNsGroupMbrInqBegin	equ <RpcNsGroupMbrInqBeginW>
RpcNsGroupMbrInqNext	equ <RpcNsGroupMbrInqNextW>
RpcNsEntryExpandName	equ <RpcNsEntryExpandNameW>
RpcNsEntryObjectInqBegin equ <RpcNsEntryObjectInqBeginW>
RpcNsMgmtBindingUnexport equ <RpcNsMgmtBindingUnexportW>
RpcNsMgmtEntryCreate	equ <RpcNsMgmtEntryCreateW>
RpcNsMgmtEntryDelete	equ <RpcNsMgmtEntryDeleteW>
RpcNsMgmtEntryInqIfIds	equ <RpcNsMgmtEntryInqIfIdsW>
RpcNsProfileDelete	equ <RpcNsProfileDeleteW>
RpcNsProfileEltAdd	equ <RpcNsProfileEltAddW>
RpcNsProfileEltRemove	equ <RpcNsProfileEltRemoveW>
RpcNsProfileEltInqBegin equ <RpcNsProfileEltInqBeginW>
RpcNsProfileEltInqNext	equ <RpcNsProfileEltInqNextW>

else

RpcNsBindingLookupBegin equ <RpcNsBindingLookupBeginA>
RpcNsBindingImportBegin equ <RpcNsBindingImportBeginA>
RpcNsBindingExport	equ <RpcNsBindingExportA>
RpcNsBindingUnexport	equ <RpcNsBindingUnexportA>
RpcNsGroupDelete	equ <RpcNsGroupDeleteA>
RpcNsGroupMbrAdd	equ <RpcNsGroupMbrAddA>
RpcNsGroupMbrRemove	equ <RpcNsGroupMbrRemoveA>
RpcNsGroupMbrInqBegin	equ <RpcNsGroupMbrInqBeginA>
RpcNsGroupMbrInqNext	equ <RpcNsGroupMbrInqNextA>
RpcNsEntryExpandName	equ <RpcNsEntryExpandNameA>
RpcNsEntryObjectInqBegin equ <RpcNsEntryObjectInqBeginA>
RpcNsMgmtBindingUnexport equ <RpcNsMgmtBindingUnexportA>
RpcNsMgmtEntryCreate	equ <RpcNsMgmtEntryCreateA>
RpcNsMgmtEntryDelete	equ <RpcNsMgmtEntryDeleteA>
RpcNsMgmtEntryInqIfIds	equ <RpcNsMgmtEntryInqIfIdsA>
RpcNsProfileDelete	equ <RpcNsProfileDeleteA>
RpcNsProfileEltAdd	equ <RpcNsProfileEltAddA>
RpcNsProfileEltRemove	equ <RpcNsProfileEltRemoveA>
RpcNsProfileEltInqBegin equ <RpcNsProfileEltInqBeginA>
RpcNsProfileEltInqNext	equ <RpcNsProfileEltInqNextA>

endif

endif

