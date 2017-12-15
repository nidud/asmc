ifndef __LIBC_INC
 include libc.inc
endif
ifndef RPC_NO_WINDOWS_H
include windows.inc
endif
ifndef __RPC_H__
.xlist
__RPC_H__ equ 1

ifdef _WIN32
__RPC_WIN32__ equ 1
else
__RPC_WIN64__ equ 1
endif
include basetsd.inc
.xlist

STDMETHOD macro name, arguments:VARARG
	local __type, __ptr
ifnb <arguments>
	__type typedef proto WINAPI :ptr, &arguments
else
	__type typedef proto WINAPI :ptr
endif
	__ptr typedef ptr __type
	name __ptr ?
	endm

ifndef __MIDL_USER_DEFINED
midl_user_allocate	equ <MID_user_allocate>
midl_user_free		equ <MID_user_free>
__MIDL_USER_DEFINED	equ 1
endif

I_RPC_HANDLE		typedef ptr
RPC_STATUS		typedef sdword
RPC_UNICODE_SUPPORTED	equ 1

if (_MSC_VER GE 800) OR defined(_STDCALL_SUPPORTED)
__RPC_FAR		equ <>
__RPC_API		equ <stdcall>
__RPC_USER		equ <stdcall>
__RPC_STUB		equ <stdcall>
RPC_ENTRY		equ <stdcall>
else
__RPC_FAR		equ <>
__RPC_API		equ <>
__RPC_USER		equ <>
__RPC_STUB		equ <>
endif

if defined(_RPCRT4_) or defined(__PE__)
option dllimport:<rpcrt4>
endif

include rpcdce.inc
include rpcnsi.inc
include rpcnterr.inc
include excpt.inc
include winerror.inc
.xlist

CALLBACK(MACYIELDCALLBACK, :ptr sword)
;RPC_ENTRY		typedef ptr MACYIELDCALLBACK

;RPC_ENTRY
RpcMacSetYieldInfo proto WINAPI \
	    pfnCallback: MACYIELDCALLBACK

RpcExceptionCode macro
	exitm<GetExceptionCode()>
	endm
RpcAbnormalTermination macro
	exitm<AbnormalTermination()>
	endm

;RPC_ENTRY
RpcImpersonateClient proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE

;RPC_ENTRY
RpcRevertToSelfEx proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE

;RPC_ENTRY
RpcRevertToSelf proto WINAPI

;long
I_RpcMapWin32Status proto WINAPI \
		Status: RPC_STATUS

ifndef RPC_NO_WINDOWS_H
include rpcasync.inc
endif

.list
endif


