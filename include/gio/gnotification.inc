ifndef __G_NOTIFICATION_H__
define __G_NOTIFICATION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc
include gio/gioenums.inc

define G_TYPE_NOTIFICATION         <g_notification_get_type ()>
G_NOTIFICATION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_NOTIFICATION, GNotification))>
  endm
G_IS_NOTIFICATION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_NOTIFICATION))>
  endm

g_notification_get_type proto
g_notification_new proto :ptr
g_notification_set_title proto :ptr, :ptr
g_notification_set_body proto :ptr, :ptr
g_notification_set_icon proto :ptr, :ptr
g_notification_set_urgent proto :ptr, :gboolean
g_notification_set_priority proto :ptr, :GNotificationPriority
g_notification_set_category proto :ptr, :ptr
g_notification_add_button proto :ptr, :ptr, :ptr
g_notification_add_button_with_target proto :ptr, :ptr, :ptr, :ptr, :vararg
g_notification_add_button_with_target_value proto :ptr, :ptr, :ptr, :ptr
g_notification_set_default_action proto :ptr, :ptr
g_notification_set_default_action_and_target proto :ptr, :ptr, :ptr, :vararg
g_notification_set_default_action_and_target_value proto :ptr, :ptr, :ptr

endif
