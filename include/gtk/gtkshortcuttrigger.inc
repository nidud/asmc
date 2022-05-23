ifndef __GTK_SHORTCUT_TRIGGER_H__
define __GTK_SHORTCUT_TRIGGER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

define GTK_TYPE_SHORTCUT_TRIGGER <gtk_shortcut_trigger_get_type>

gtk_shortcut_trigger_parse_string proto :ptr
gtk_shortcut_trigger_to_string proto :ptr
gtk_shortcut_trigger_print proto :ptr, :ptr
gtk_shortcut_trigger_to_label proto :ptr, :ptr
gtk_shortcut_trigger_print_label proto :ptr, :ptr, :ptr
gtk_shortcut_trigger_hash proto :gconstpointer
gtk_shortcut_trigger_equal proto :gconstpointer, :gconstpointer
gtk_shortcut_trigger_compare proto :gconstpointer, :gconstpointer
gtk_shortcut_trigger_trigger proto :ptr, :ptr, :gboolean

define GTK_TYPE_NEVER_TRIGGER <gtk_never_trigger_get_type>

gtk_never_trigger_get proto

define GTK_TYPE_KEYVAL_TRIGGER <gtk_keyval_trigger_get_type>

gtk_keyval_trigger_new proto :guint, :GdkModifierType
gtk_keyval_trigger_get_modifiers proto :ptr
gtk_keyval_trigger_get_keyval proto :ptr

define GTK_TYPE_MNEMONIC_TRIGGER <gtk_mnemonic_trigger_get_type>

gtk_mnemonic_trigger_new proto :guint
gtk_mnemonic_trigger_get_keyval proto :ptr

define GTK_TYPE_ALTERNATIVE_TRIGGER <gtk_alternative_trigger_get_type>

gtk_alternative_trigger_new proto :ptr, :ptr
gtk_alternative_trigger_get_first proto :ptr
gtk_alternative_trigger_get_second proto :ptr

endif
