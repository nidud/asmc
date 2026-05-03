ifndef __WBEMIDL_H_
define __WBEMIDL_H_
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
include wbemcli.inc
include wbemprov.inc
include wbemtran.inc
include wbemdisp.inc
endif
endif
