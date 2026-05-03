ifndef __GDK_KEYS_H__
define __GDK_KEYS_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

gdk_keyval_name proto :guint

gdk_keyval_from_name proto :ptr
gdk_keyval_convert_case proto :guint, :ptr, :ptr
gdk_keyval_to_upper proto :guint
gdk_keyval_to_lower proto :guint
gdk_keyval_is_upper proto :guint
gdk_keyval_is_lower proto :guint

gdk_keyval_to_unicode proto :guint
gdk_unicode_to_keyval proto :guint32

endif
