ifndef __GTK_SHORTCUT_CONTROLLER_H__
define __GTK_SHORTCUT_CONTROLLER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkeventcontroller.inc

define GTK_TYPE_SHORTCUT_CONTROLLER <gtk_shortcut_controller_get_type>
GTK_SHORTCUT_CONTROLLER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_SHORTCUT_CONTROLLER, GtkShortcutController))>
  endm
GTK_SHORTCUT_CONTROLLER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_SHORTCUT_CONTROLLER, GtkShortcutControllerClass))>
  endm
GTK_IS_SHORTCUT_CONTROLLER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_SHORTCUT_CONTROLLER))>
  endm
GTK_IS_SHORTCUT_CONTROLLER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_SHORTCUT_CONTROLLER))>
  endm
GTK_SHORTCUT_CONTROLLER_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_SHORTCUT_CONTROLLER, GtkShortcutControllerClass))>
  endm

;GtkShortcutController   typedef _GtkShortcutController
;GtkShortcutControllerClass typedef _GtkShortcutControllerClass

gtk_shortcut_controller_get_type proto
gtk_shortcut_controller_new proto
gtk_shortcut_controller_new_for_model proto :ptr
gtk_shortcut_controller_set_mnemonics_modifiers proto :ptr, :GdkModifierType
gtk_shortcut_controller_get_mnemonics_modifiers proto :ptr
gtk_shortcut_controller_set_scope proto :ptr, :GtkShortcutScope
gtk_shortcut_controller_get_scope proto :ptr
gtk_shortcut_controller_add_shortcut proto :ptr, :ptr
gtk_shortcut_controller_remove_shortcut proto :ptr, :ptr

endif
