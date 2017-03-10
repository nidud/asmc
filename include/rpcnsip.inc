ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;; This file contains the types and function definitions to use the
;; to implement the autohandle features of the runtime.
;;
ifndef __RPCNSIP_H__
__RPCNSIP_H__ equ 1

PRPC_BINDING_VECTOR	typedef ptr RPC_BINDING_VECTOR

RPC_IMPORT_CONTEXT_P	STRUC
LookupContext		RPC_NS_HANDLE ?
ProposedHandle		RPC_BINDING_HANDLE ?
Bindings		PRPC_BINDING_VECTOR ?
RPC_IMPORT_CONTEXT_P	ENDS
PRPC_IMPORT_CONTEXT_P	typedef ptr RPC_IMPORT_CONTEXT_P


;; Stub Auto Binding routines.

;RPC_STATUS
I_RpcNsGetBuffer proto _CType \
	       Message: PRPC_MESSAGE

;RPC_STATUS
I_RpcNsSendReceive proto _CType \
	       Message: PRPC_MESSAGE,
		Handle: ptr RPC_BINDING_HANDLE

;void
I_RpcNsRaiseException proto _CType \
	       Message: PRPC_MESSAGE,
		Status: RPC_STATUS

;RPC_STATUS
I_RpcReBindBuffer proto _CType \
	       Message: PRPC_MESSAGE

;RPC_STATUS
I_NsServerBindSearch proto _CType

;RPC_STATUS
I_NsClientBindSearch proto _CType

;void
I_NsClientBindDone proto _CType


endif ;; __RPCNSIP_H__

.list
