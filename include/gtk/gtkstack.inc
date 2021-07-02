ifndef __GTK_STACK_H__
__GTK_STACK_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_STACK equ <gtk_stack_get_type>
GTK_STACK macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STACK, GtkStack))>
	endm
GTK_STACK_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_STACK, GtkStackClass))>
	endm
GTK_IS_STACK macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STACK))>
	endm
GTK_IS_STACK_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_STACK))>
	endm
GTK_STACK_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_STACK, GtkStackClass))>
	endm

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
  GTK_STACK_TRANSITION_TYPE_OVER_RIGHT_LEFT
}

GtkStack		STRUC
parent_instance		GtkContainer <>
GtkStack		ENDS

GtkStackClass		STRUC
parent_class		GtkContainerClass <>
GtkStackClass		ENDS

;GType
gtk_stack_get_type proto __cdecl

;GtkWidget
gtk_stack_new proto __cdecl
;void
gtk_stack_add_named proto __cdecl \
		 stack: ptr GtkStack,
		 child: ptr GtkWidget,
		  name: ptr gchar

;void
gtk_stack_add_titled proto __cdecl \
		 stack: ptr GtkStack,
		 child: ptr GtkWidget,
		  name: ptr gchar,
		 title: ptr gchar

;GtkWidget
gtk_stack_get_child_by_name proto __cdecl \
		 stack: ptr GtkStack,
		  name: ptr gchar

;void
gtk_stack_set_visible_child proto __cdecl \
		 stack: ptr GtkStack,
		 child: ptr GtkWidget

;GtkWidget
gtk_stack_get_visible_child proto __cdecl \
		 stack: ptr GtkStack

;void
gtk_stack_set_visible_child_name proto __cdecl \
		 stack: ptr GtkStack,
		  name: ptr gchar

;const
gtk_stack_get_visible_child_name proto __cdecl \
		 stack: ptr GtkStack

;void
gtk_stack_set_visible_child_full proto __cdecl \
		 stack: ptr GtkStack,
		  name: ptr gchar,
	    transition: GtkStackTransitionType

;void
gtk_stack_set_homogeneous proto __cdecl \
		 stack: ptr GtkStack,
	   homogeneous: gboolean

;gboolean
gtk_stack_get_homogeneous proto __cdecl \
		 stack: ptr GtkStack

;void
gtk_stack_set_hhomogeneous proto __cdecl \
		 stack: ptr GtkStack,
	  hhomogeneous: gboolean

;gboolean
gtk_stack_get_hhomogeneous proto __cdecl \
		 stack: ptr GtkStack

;void
gtk_stack_set_vhomogeneous proto __cdecl \
		 stack: ptr GtkStack,
	  vhomogeneous: gboolean

;gboolean
gtk_stack_get_vhomogeneous proto __cdecl \
		 stack: ptr GtkStack

;void
gtk_stack_set_transition_duration proto __cdecl \
		 stack: ptr GtkStack,
	      duration: guint

;guint
gtk_stack_get_transition_duration proto __cdecl \
		 stack: ptr GtkStack

;void
gtk_stack_set_transition_type proto __cdecl \
		 stack: ptr GtkStack,
	    transition: GtkStackTransitionType

;GtkStackTransitionType
gtk_stack_get_transition_type proto __cdecl \
		 stack: ptr GtkStack

;gboolean
gtk_stack_get_transition_running proto __cdecl \
		 stack: ptr GtkStack

;void
gtk_stack_set_interpolate_size proto __cdecl \
		 stack: ptr GtkStack,
      interpolate_size: gboolean

;gboolean
gtk_stack_get_interpolate_size proto __cdecl \
		 stack: ptr GtkStack

G_END_DECLS

endif
