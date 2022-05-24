ifndef __GTK_REVEALER_H__
define __GTK_REVEALER_H__

include gtk/gtkwidget.inc

define GTK_TYPE_REVEALER <gtk_revealer_get_type ()>
GTK_REVEALER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_REVEALER, GtkRevealer))>
  endm
GTK_IS_REVEALER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_REVEALER))>
  endm

;GtkRevealer             typedef _GtkRevealer

.enum GtkRevealerTransitionType {
  GTK_REVEALER_TRANSITION_TYPE_NONE,
  GTK_REVEALER_TRANSITION_TYPE_CROSSFADE,
  GTK_REVEALER_TRANSITION_TYPE_SLIDE_RIGHT,
  GTK_REVEALER_TRANSITION_TYPE_SLIDE_LEFT,
  GTK_REVEALER_TRANSITION_TYPE_SLIDE_UP,
  GTK_REVEALER_TRANSITION_TYPE_SLIDE_DOWN,
  GTK_REVEALER_TRANSITION_TYPE_SWING_RIGHT,
  GTK_REVEALER_TRANSITION_TYPE_SWING_LEFT,
  GTK_REVEALER_TRANSITION_TYPE_SWING_UP,
  GTK_REVEALER_TRANSITION_TYPE_SWING_DOWN
}

gtk_revealer_get_type proto
gtk_revealer_new proto
gtk_revealer_get_reveal_child proto :ptr
gtk_revealer_set_reveal_child proto :ptr, :gboolean
gtk_revealer_get_child_revealed proto :ptr
gtk_revealer_get_transition_duration proto :ptr
gtk_revealer_set_transition_duration proto :ptr, :guint
gtk_revealer_set_transition_type proto :ptr, :GtkRevealerTransitionType
gtk_revealer_get_transition_type proto :ptr

gtk_revealer_set_child proto :ptr, :ptr
gtk_revealer_get_child proto :ptr

endif
