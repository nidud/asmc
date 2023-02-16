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

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __objidlbase_h__
define __objidlbase_h__

include unknwnbase.inc
include winapifamily.inc

if(NTDDI_VERSION GE NTDDI_VISTA AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0600
endif
if(NTDDI_VERSION GE NTDDI_WS03 AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0502
endif
if(NTDDI_VERSION GE NTDDI_WINXP AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0501
endif
if(NTDDI_VERSION GE NTDDI_WIN2K AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0500
endif

include limits.inc

ifndef _OBJIDLBASE_
include objidlbase
endif

endif ;; __objidlbase_h__
