ifndef __LIBC_INC
 include libc.inc
endif
ifndef __RPCNSIP_H__
__RPCNSIP_H__ equ 1
.xlist

PRPC_BINDING_VECTOR	typedef ptr RPC_BINDING_VECTOR

RPC_IMPORT_CONTEXT_P	STRUC
LookupContext		RPC_NS_HANDLE ?
ProposedHandle		RPC_BINDING_HANDLE ?
Bindings		PRPC_BINDING_VECTOR ?
RPC_IMPORT_CONTEXT_P	ENDS
PRPC_IMPORT_CONTEXT_P	typedef ptr RPC_IMPORT_CONTEXT_P



;RPC_STATUS
I_RpcNsGetBuffer proto WINAPI \
	       Message: PRPC_MESSAGE

;RPC_STATUS
I_RpcNsSendReceive proto WINAPI \
	       Message: PRPC_MESSAGE,
		Handle: ptr RPC_BINDING_HANDLE

;void
I_RpcNsRaiseException proto WINAPI \
	       Message: PRPC_MESSAGE,
		Status: RPC_STATUS

;RPC_STATUS
I_RpcReBindBuffer proto WINAPI \
	       Message: PRPC_MESSAGE

;RPC_STATUS
I_NsServerBindSearch proto WINAPI

;RPC_STATUS
I_NsClientBindSearch proto WINAPI

;void
I_NsClientBindDone proto WINAPI

.list
endif
