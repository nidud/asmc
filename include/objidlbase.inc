ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __objidlbase_h__
define __objidlbase_h__

ifndef __unknwnbase_h__
include unknwnbase.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

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

ifndef _LIMITS_
include limits.inc
endif
ifndef _OBJIDLBASE_
include objidlbase
endif

endif
