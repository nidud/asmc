ifndef __RPCNSIP_H__
define __RPCNSIP_H__
ifndef __LIBC_INC
include libc.inc
endif

PRPC_BINDING_VECTOR	typedef ptr RPC_BINDING_VECTOR

RPC_IMPORT_CONTEXT_P	STRUC
LookupContext		RPC_NS_HANDLE ?
ProposedHandle		RPC_BINDING_HANDLE ?
Bindings		PRPC_BINDING_VECTOR ?
RPC_IMPORT_CONTEXT_P	ENDS
PRPC_IMPORT_CONTEXT_P	typedef ptr RPC_IMPORT_CONTEXT_P

I_RpcNsGetBuffer proto WINAPI :PRPC_MESSAGE
I_RpcNsSendReceive proto WINAPI :PRPC_MESSAGE, :ptr
I_RpcNsRaiseException proto WINAPI :PRPC_MESSAGE, :RPC_STATUS
I_RpcReBindBuffer proto WINAPI :PRPC_MESSAGE
I_NsServerBindSearch proto WINAPI
I_NsClientBindSearch proto WINAPI
I_NsClientBindDone proto WINAPI

endif
