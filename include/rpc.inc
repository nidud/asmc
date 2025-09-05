if not defined(RPC_NO_WINDOWS_H) and not defined(_KRPCENV_)
ifndef _WINDOWS_
include windows.inc
endif
endif
ifndef __RPC_H__
define __RPC_H__

if defined(_M_IA64) or defined(_M_AMD64)
define __RPC_WIN64__
else
define __RPC_WIN32__
endif

ifndef _BASETSD_
include basetsd.inc
endif
ifdef __RPC_WIN64__
.pragma pack(push, 8)
endif

I_RPC_HANDLE	typedef ptr
RPC_STATUS	typedef sdword

define RPC_UNICODE_SUPPORTED

.pragma comment(lib, rpcrt4)

include rpcdce.inc
ifndef _KRPCENV_
include rpcnsi.inc
endif
include rpcnterr.inc
ifndef _EXCPT_
include excpt.inc
endif
ifndef _KRPCENV_
ifndef _WINERROR_
include winerror.inc
endif
endif

define RpcExceptionCode <GetExceptionCode>
define RpcAbnormalTermination <AbnormalTermination>

if not defined(RPC_NO_WINDOWS_H) or defined(RPC_NEED_RPCASYNC_H) or defined(_KRPCENV_)
include rpcasync.inc
endif

ifdef __RPC_WIN64__
.pragma pack(pop)
endif

endif
