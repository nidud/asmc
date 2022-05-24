ifndef __G_FILE_ICON_H__
define __G_FILE_ICON_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_FILE_ICON         <g_file_icon_get_type ()>
G_FILE_ICON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILE_ICON, GFileIcon))>
  endm
G_FILE_ICON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILE_ICON, GFileIconClass))>
  endm
G_IS_FILE_ICON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILE_ICON))>
  endm
G_IS_FILE_ICON_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILE_ICON))>
  endm
G_FILE_ICON_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILE_ICON, GFileIconClass))>
  endm


;GFileIconClass          typedef _GFileIconClass

g_file_icon_get_type proto
g_file_icon_new proto :ptr
g_file_icon_get_file proto :ptr

endif
