ifndef __GTK_STACK_H__
define __GTK_STACK_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkselectionmodel.inc

define GTK_TYPE_STACK <gtk_stack_get_type ()>
GTK_STACK macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STACK, GtkStack))>
  endm
GTK_IS_STACK macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STACK))>
  endm

;GtkStack                typedef _GtkStack

define GTK_TYPE_STACK_PAGE <gtk_stack_page_get_type ()>
GTK_STACK_PAGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STACK_PAGE, GtkStackPage))>
  endm
GTK_IS_STACK_PAGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STACK_PAGE))>
  endm

;GtkStackPage            typedef _GtkStackPage

.enum GtkStackTransitionType {
  GTK_STACK_TRANSITION_TYPE_NONE,
  GTK_STACK_TRANSITION_TYPE_CROSSFADE,
  GTK_STACK_TRANSITION_TYPE_SLIDE_RIGHT,
  GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT,
  GTK_STACK_TRANSITION_TYPE_SLIDE_UP,
  GTK_STACK_TRANSITION_TYPE_SLIDE_DOWN,
  GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT,
  GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN,
  GTK_STACK_TRANSITION_TYPE_OVER_UP,
  GTK_STACK_TRANSITION_TYPE_OVER_DOWN,
  GTK_STACK_TRANSITION_TYPE_OVER_LEFT,
  GTK_STACK_TRANSITION_TYPE_OVER_RIGHT,
  GTK_STACK_TRANSITION_TYPE_UNDER_UP,
  GTK_STACK_TRANSITION_TYPE_UNDER_DOWN,
  GTK_STACK_TRANSITION_TYPE_UNDER_LEFT,
  GTK_STACK_TRANSITION_TYPE_UNDER_RIGHT,
  GTK_STACK_TRANSITION_TYPE_OVER_UP_DOWN,
  GTK_STACK_TRANSITION_TYPE_OVER_DOWN_UP,
  GTK_STACK_TRANSITION_TYPE_OVER_LEFT_RIGHT,
  GTK_STACK_TRANSITION_TYPE_OVER_RIGHT_LEFT,
  GTK_STACK_TRANSITION_TYPE_ROTATE_LEFT,
  GTK_STACK_TRANSITION_TYPE_ROTATE_RIGHT,
  GTK_STACK_TRANSITION_TYPE_ROTATE_LEFT_RIGHT
}

gtk_stack_page_get_type proto
gtk_stack_page_get_child proto :ptr
gtk_stack_page_get_visible proto :ptr
gtk_stack_page_set_visible proto :ptr, :gboolean
gtk_stack_page_get_needs_attention proto :ptr
gtk_stack_page_set_needs_attention proto :ptr, :gboolean
gtk_stack_page_get_use_underline proto :ptr
gtk_stack_page_set_use_underline proto :ptr, :gboolean
gtk_stack_page_get_name proto :ptr
gtk_stack_page_set_name proto :ptr, :ptr
gtk_stack_page_get_title proto :ptr
gtk_stack_page_set_title proto :ptr, :ptr
gtk_stack_page_get_icon_name proto :ptr
gtk_stack_page_set_icon_name proto :ptr, :ptr

gtk_stack_get_type proto

gtk_stack_new proto
gtk_stack_add_child proto :ptr, :ptr
gtk_stack_add_named proto :ptr, :ptr, :ptr
gtk_stack_add_titled proto :ptr, :ptr, :ptr, :ptr
gtk_stack_remove proto :ptr, :ptr

gtk_stack_get_page proto :ptr, :ptr
gtk_stack_get_child_by_name proto :ptr, :ptr
gtk_stack_set_visible_child proto :ptr, :ptr
gtk_stack_get_visible_child proto :ptr
gtk_stack_set_visible_child_name proto :ptr, :ptr
gtk_stack_get_visible_child_name proto :ptr
gtk_stack_set_visible_child_full proto :ptr, :ptr, :GtkStackTransitionType
gtk_stack_set_hhomogeneous proto :ptr, :gboolean
gtk_stack_get_hhomogeneous proto :ptr
gtk_stack_set_vhomogeneous proto :ptr, :gboolean
gtk_stack_get_vhomogeneous proto :ptr
gtk_stack_set_transition_duration proto :ptr, :guint
gtk_stack_get_transition_duration proto :ptr
gtk_stack_set_transition_type proto :ptr, :GtkStackTransitionType
gtk_stack_get_transition_type proto :ptr
gtk_stack_get_transition_running proto :ptr
gtk_stack_set_interpolate_size proto :ptr, :gboolean
gtk_stack_get_interpolate_size proto :ptr

gtk_stack_get_pages proto :ptr

endif
