ifndef __G_DEBUG_CONTROLLER_H__
define __G_DEBUG_CONTROLLER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_DEBUG_CONTROLLER_EXTENSION_POINT_NAME <"gio-debug-controller">

define G_TYPE_DEBUG_CONTROLLER             <g_debug_controller_get_type ()>

G_DEBUG_CONTROLLER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DEBUG_CONTROLLER, GDebugController))>
  endm
G_IS_DEBUG_CONTROLLER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DEBUG_CONTROLLER))>
  endm
G_DEBUG_CONTROLLER_GET_INTERFACE macro o
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((o), G_TYPE_DEBUG_CONTROLLER, GDebugControllerInterface))>
  endm


GDebugControllerInterface struct
g_iface                 GTypeInterface <>
GDebugControllerInterface ends

g_debug_controller_get_debug_enabled proto :ptr
g_debug_controller_set_debug_enabled proto :ptr, :gboolean


endif
