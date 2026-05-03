ifndef __G_ACTION_GROUP_EXPORTER_H__
define __G_ACTION_GROUP_EXPORTER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

g_dbus_connection_export_action_group proto :ptr, :ptr, :ptr, :ptr
g_dbus_connection_unexport_action_group proto :ptr, :guint

endif
