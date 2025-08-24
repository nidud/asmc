ifndef __GTK_SHORTCUT_LABEL_H__
define __GTK_SHORTCUT_LABEL_H__

include gtk/gtkwidget.inc

define GTK_TYPE_SHORTCUT_LABEL <gtk_shortcut_label_get_type ()>
GTK_SHORTCUT_LABEL macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SHORTCUT_LABEL, GtkShortcutLabel))>
  endm
GTK_IS_SHORTCUT_LABEL macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SHORTCUT_LABEL))>
  endm

gtk_shortcut_label_get_type proto
gtk_shortcut_label_new proto :ptr
gtk_shortcut_label_get_accelerator proto :ptr
gtk_shortcut_label_set_accelerator proto :ptr, :ptr
gtk_shortcut_label_get_disabled_text proto :ptr
gtk_shortcut_label_set_disabled_text proto :ptr, :ptr

endif
