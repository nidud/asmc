ifndef _LM_
_LM_ equ <>
.pragma list(push, 0)

ifdef __PE__
option importlib:<netapi32>
else
includelib netapi32.lib
endif

include lmcons.inc
include lmerr.inc

include lmaccess.inc
include lmalert.inc
include lmshare.inc
include lmmsg.inc
include lmremutl.inc
include lmrepl.inc
include lmserver.inc
include lmsvc.inc
include lmuse.inc
include lmwksta.inc
include lmapibuf.inc
include lmerrlog.inc
include lmconfig.inc
include lmstats.inc
include lmaudit.inc
include lmjoin.inc

.pragma list(pop)
endif

