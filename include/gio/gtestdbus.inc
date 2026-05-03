ifndef __G_TEST_DBUS_H__
define __G_TEST_DBUS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_TEST_DBUS     <g_test_dbus_get_type ()>
G_TEST_DBUS macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_TEST_DBUS, GTestDBus))>
  endm
G_IS_TEST_DBUS macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_TEST_DBUS))>
  endm

g_test_dbus_get_type proto
g_test_dbus_new proto :GTestDBusFlags
g_test_dbus_get_flags proto :ptr
g_test_dbus_get_bus_address proto :ptr
g_test_dbus_add_service_dir proto :ptr, :ptr
g_test_dbus_up proto :ptr
g_test_dbus_stop proto :ptr
g_test_dbus_down proto :ptr
g_test_dbus_unset proto

endif
