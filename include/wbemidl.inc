.pragma list(push, 0)
ifndef __WBEMIDL_H_
define __WBEMIDL_H_
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include wbemcli.inc
include wbemprov.inc
include wbemtran.inc
include wbemdisp.inc

endif
endif
.pragma list(pop)