ifndef __GTK_SHORTCUT_ACTION_H__
define __GTK_SHORTCUT_ACTION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

define GTK_TYPE_SHORTCUT_ACTION <gtk_shortcut_action_get_type>

CALLBACK(GtkShortcutFunc, :ptr, :ptr, :gpointer)

.enum GtkShortcutActionFlags {
  GTK_SHORTCUT_ACTION_EXCLUSIVE = 1 shl 0
}

gtk_shortcut_action_to_string proto :ptr
gtk_shortcut_action_parse_string proto :ptr

gtk_shortcut_action_print proto :ptr, :ptr
gtk_shortcut_action_activate proto :ptr, :GtkShortcutActionFlags, :ptr, :ptr

define GTK_TYPE_NOTHING_ACTION <gtk_nothing_action_get_type>

gtk_nothing_action_get proto

define GTK_TYPE_CALLBACK_ACTION <gtk_callback_action_get_type>

gtk_callback_action_new proto :GtkShortcutFunc, :gpointer, :GDestroyNotify

define GTK_TYPE_MNEMONIC_ACTION <gtk_mnemonic_action_get_type>

gtk_mnemonic_action_get proto

define GTK_TYPE_ACTIVATE_ACTION <gtk_activate_action_get_type>

gtk_activate_action_get proto

define GTK_TYPE_SIGNAL_ACTION <gtk_signal_action_get_type>

gtk_signal_action_new proto :ptr
gtk_signal_action_get_signal_name proto :ptr

define GTK_TYPE_NAMED_ACTION <gtk_named_action_get_type>

gtk_named_action_new proto :ptr
gtk_named_action_get_action_name proto :ptr

endif
