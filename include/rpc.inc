ifndef __LIBC_INC
include libc.inc
endif
ifndef RPC_NO_WINDOWS_H
include windows.inc
endif
ifndef __RPC_H__
define __RPC_H__
ifdef _WIN32
define __RPC_WIN32__
else
define __RPC_WIN64__
endif

include basetsd.inc

I_RPC_HANDLE	typedef ptr
RPC_STATUS	typedef sdword

define RPC_UNICODE_SUPPORTED

.pragma comment(lib, rpcrt4)

include rpcdce.inc
include rpcnsi.inc
include rpcnterr.inc
include excpt.inc
include winerror.inc

CALLBACK(MACYIELDCALLBACK, :ptr sword)

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

endif
