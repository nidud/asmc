ifndef _RPC500_
define _RPC500_
ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif
ifndef __RPC_H__
include rpc.inc
endif
ifndef __RPCNDR_H__
include rpcndr.inc
endif
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif
endif
