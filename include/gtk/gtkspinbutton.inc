ifndef __GTK_SPIN_BUTTON_H__
define __GTK_SPIN_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_SPIN_BUTTON <gtk_spin_button_get_type ()>
GTK_SPIN_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SPIN_BUTTON, GtkSpinButton))>
  endm
GTK_IS_SPIN_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SPIN_BUTTON))>
  endm

define GTK_INPUT_ERROR -1

.enum GtkSpinButtonUpdatePolicy {
  GTK_UPDATE_ALWAYS,
  GTK_UPDATE_IF_VALID
}

.enum GtkSpinType {
  GTK_SPIN_STEP_FORWARD,
  GTK_SPIN_STEP_BACKWARD,
  GTK_SPIN_PAGE_FORWARD,
  GTK_SPIN_PAGE_BACKWARD,
  GTK_SPIN_HOME,
  GTK_SPIN_END,
  GTK_SPIN_USER_DEFINED
}

gtk_spin_button_get_type proto
gtk_spin_button_configure proto :ptr, :ptr, :real8, :guint
gtk_spin_button_new proto :ptr, :real8, :guint
gtk_spin_button_new_with_range proto :real8, :real8, :real8
gtk_spin_button_set_adjustment proto :ptr, :ptr
gtk_spin_button_get_adjustment proto :ptr
gtk_spin_button_set_digits proto :ptr, :guint
gtk_spin_button_get_digits proto :ptr
gtk_spin_button_set_increments proto :ptr, :real8, :real8
gtk_spin_button_get_increments proto :ptr, :ptr, :ptr
gtk_spin_button_set_range proto :ptr, :real8, :real8
gtk_spin_button_get_range proto :ptr, :ptr, :ptr
gtk_spin_button_get_value proto :ptr
gtk_spin_button_get_value_as_int proto :ptr
gtk_spin_button_set_value proto :ptr, :real8
gtk_spin_button_set_update_policy proto :ptr, :GtkSpinButtonUpdatePolicy
gtk_spin_button_get_update_policy proto :ptr
gtk_spin_button_set_numeric proto :ptr, :gboolean
gtk_spin_button_get_numeric proto :ptr
gtk_spin_button_spin proto :ptr, :GtkSpinType, :real8
gtk_spin_button_set_wrap proto :ptr, :gboolean
gtk_spin_button_get_wrap proto :ptr
gtk_spin_button_set_snap_to_ticks proto :ptr, :gboolean
gtk_spin_button_get_snap_to_ticks proto :ptr
gtk_spin_button_set_climb_rate proto :ptr, :real8
gtk_spin_button_get_climb_rate proto :ptr
gtk_spin_button_update proto :ptr

endif
