.pragma list(push, 0)
ifndef _LM_
define _LM_
.pragma comment(lib, netapi32)

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

endif
.pragma list(pop)

