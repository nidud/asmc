ifndef __GTK_SCROLLED_WINDOW_H__
define __GTK_SCROLLED_WINDOW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_SCROLLED_WINDOW <gtk_scrolled_window_get_type>
GTK_SCROLLED_WINDOW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCROLLED_WINDOW, GtkScrolledWindow))>
  endm
GTK_IS_SCROLLED_WINDOW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCROLLED_WINDOW))>
  endm


;GtkScrolledWindow       typedef _GtkScrolledWindow


.enum GtkCornerType {
  GTK_CORNER_TOP_LEFT,
  GTK_CORNER_BOTTOM_LEFT,
  GTK_CORNER_TOP_RIGHT,
  GTK_CORNER_BOTTOM_RIGHT
}



.enum GtkPolicyType {
  GTK_POLICY_ALWAYS,
  GTK_POLICY_AUTOMATIC,
  GTK_POLICY_NEVER,
  GTK_POLICY_EXTERNAL
}


gtk_scrolled_window_get_type proto
gtk_scrolled_window_new proto
gtk_scrolled_window_set_hadjustment proto :ptr, :ptr
gtk_scrolled_window_set_vadjustment proto :ptr, :ptr
gtk_scrolled_window_get_hadjustment proto :ptr
gtk_scrolled_window_get_vadjustment proto :ptr
gtk_scrolled_window_get_hscrollbar proto :ptr
gtk_scrolled_window_get_vscrollbar proto :ptr
gtk_scrolled_window_set_policy proto :ptr, :GtkPolicyType, :GtkPolicyType
gtk_scrolled_window_get_policy proto :ptr, :ptr, :ptr
gtk_scrolled_window_set_placement proto :ptr, :GtkCornerType
gtk_scrolled_window_unset_placement proto :ptr

gtk_scrolled_window_get_placement proto :ptr
gtk_scrolled_window_set_has_frame proto :ptr, :gboolean
gtk_scrolled_window_get_has_frame proto :ptr

gtk_scrolled_window_get_min_content_width proto :ptr
gtk_scrolled_window_set_min_content_width proto :ptr, :sdword
gtk_scrolled_window_get_min_content_height proto :ptr
gtk_scrolled_window_set_min_content_height proto :ptr, :sdword
gtk_scrolled_window_set_kinetic_scrolling proto :ptr, :gboolean
gtk_scrolled_window_get_kinetic_scrolling proto :ptr

gtk_scrolled_window_set_overlay_scrolling proto :ptr, :gboolean
gtk_scrolled_window_get_overlay_scrolling proto :ptr

gtk_scrolled_window_set_max_content_width proto :ptr, :sdword
gtk_scrolled_window_get_max_content_width proto :ptr

gtk_scrolled_window_set_max_content_height proto :ptr, :sdword
gtk_scrolled_window_get_max_content_height proto :ptr

gtk_scrolled_window_set_propagate_natural_width proto :ptr, :gboolean
gtk_scrolled_window_get_propagate_natural_width proto :ptr

gtk_scrolled_window_set_propagate_natural_height proto :ptr, :gboolean
gtk_scrolled_window_get_propagate_natural_height proto :ptr

gtk_scrolled_window_set_child proto :ptr, :ptr
gtk_scrolled_window_get_child proto :ptr

endif
