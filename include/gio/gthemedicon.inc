ifndef __G_THEMED_ICON_H__
define __G_THEMED_ICON_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_THEMED_ICON         <g_themed_icon_get_type>
G_THEMED_ICON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_THEMED_ICON, GThemedIcon))>
  endm
G_THEMED_ICON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_THEMED_ICON, GThemedIconClass))>
  endm
G_IS_THEMED_ICON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_THEMED_ICON))>
  endm
G_IS_THEMED_ICON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_THEMED_ICON))>
  endm
G_THEMED_ICON_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_THEMED_ICON, GThemedIconClass))>
  endm


;GThemedIconClass        typedef _GThemedIconClass

g_themed_icon_get_type proto
g_themed_icon_new proto :ptr
g_themed_icon_new_with_default_fallbacks proto :ptr
g_themed_icon_new_from_names proto :ptr, :sdword
g_themed_icon_prepend_name proto :ptr, :ptr
g_themed_icon_append_name proto :ptr, :ptr
g_themed_icon_get_names proto :ptr

endif
