ifndef __G_SRV_TARGET_H__
define __G_SRV_TARGET_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

g_srv_target_get_type proto
define G_TYPE_SRV_TARGET <g_srv_target_get_type ()>

g_srv_target_new proto :ptr, :guint16, :guint16, :guint16
g_srv_target_copy proto :ptr
g_srv_target_free proto :ptr
g_srv_target_get_hostname proto :ptr
g_srv_target_get_port proto :ptr
g_srv_target_get_priority proto :ptr
g_srv_target_get_weight proto :ptr
g_srv_target_list_sort proto :ptr

endif
