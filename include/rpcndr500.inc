ifndef _RPCNDR500_
define _RPCNDR500_
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
ifndef COM_NO_WINDOWS_H
ifndef _WINDOWS_
include windows.inc
endif
ifndef _OLE2_H_
include ole2.inc
endif
endif
endif
