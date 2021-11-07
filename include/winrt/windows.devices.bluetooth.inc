ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef __windows2Edevices2Ebluetooth_h__
define __windows2Edevices2Ebluetooth_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

endif
