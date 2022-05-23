ifndef __GDK_DISPLAY_MANAGER_H__
define __GDK_DISPLAY_MANAGER_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkdisplay.inc

define GDK_TYPE_DISPLAY_MANAGER              <gdk_display_manager_get_type>
GDK_DISPLAY_MANAGER macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_DISPLAY_MANAGER, GdkDisplayManager))>
  endm
GDK_IS_DISPLAY_MANAGER macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_DISPLAY_MANAGER))>
  endm

gdk_display_manager_get_type proto
gdk_display_manager_get proto
gdk_display_manager_get_default_display proto :ptr
gdk_display_manager_set_default_display proto :ptr, :ptr
gdk_display_manager_list_displays proto :ptr
gdk_display_manager_open_display proto :ptr, :ptr
gdk_set_allowed_backends proto :ptr

endif
