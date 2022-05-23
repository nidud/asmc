ifndef __GTK_TOGGLE_BUTTON_H__
define __GTK_TOGGLE_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

define GTK_TYPE_TOGGLE_BUTTON <gtk_toggle_button_get_type>
GTK_TOGGLE_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TOGGLE_BUTTON, GtkToggleButton))>
  endm
GTK_TOGGLE_BUTTON_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TOGGLE_BUTTON, GtkToggleButtonClass))>
  endm
GTK_IS_TOGGLE_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TOGGLE_BUTTON))>
  endm
GTK_IS_TOGGLE_BUTTON_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TOGGLE_BUTTON))>
  endm
GTK_TOGGLE_BUTTON_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TOGGLE_BUTTON, GtkToggleButtonClass))>
  endm

_GtkToggleButton        struct
button                  GtkButton <>
_GtkToggleButton        ends
GtkToggleButton         typedef _GtkToggleButton

_GtkToggleButtonClass   struct
parent_class            GtkButtonClass <>
toggled                 proc :ptr
padding                 gpointer 8 dup(?)
_GtkToggleButtonClass   ends
GtkToggleButtonClass    typedef _GtkToggleButtonClass


gtk_toggle_button_get_type proto
gtk_toggle_button_new proto
gtk_toggle_button_new_with_label proto :ptr
gtk_toggle_button_new_with_mnemonic proto :ptr
gtk_toggle_button_set_active proto :ptr, :gboolean
gtk_toggle_button_get_active proto :ptr
gtk_toggle_button_toggled proto :ptr
gtk_toggle_button_set_group proto :ptr, :ptr

endif
