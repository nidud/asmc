ifndef __GTK_ACCEL_GROUP_H__
define __GTK_ACCEL_GROUP_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

gtk_accelerator_valid proto :guint, :GdkModifierType
gtk_accelerator_parse proto :ptr, :ptr, :ptr
gtk_accelerator_parse_with_keycode proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_accelerator_name proto :guint, :GdkModifierType
gtk_accelerator_name_with_keycode proto :ptr, :guint, :guint, :GdkModifierType
gtk_accelerator_get_label proto :guint, :GdkModifierType
gtk_accelerator_get_label_with_keycode proto :ptr, :guint, :guint, :GdkModifierType
gtk_accelerator_get_default_mod_mask proto

endif
