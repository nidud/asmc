ifndef __GTK_REVEALER_H__
__GTK_REVEALER_H__ equ <>

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_REVEALER equ <gtk_revealer_get_type>
GTK_REVEALER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_REVEALER, GtkRevealer))>
	endm
GTK_REVEALER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_REVEALER, GtkRevealerClass))>
	endm
GTK_IS_REVEALER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_REVEALER))>
	endm
GTK_IS_REVEALER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_REVEALER))>
	endm
GTK_REVEALER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_REVEALER, GtkRevealerClass))>
	endm

.enum GtkRevealerTransitionType {
  GTK_REVEALER_TRANSITION_TYPE_NONE,
  GTK_REVEALER_TRANSITION_TYPE_CROSSFADE,
  GTK_REVEALER_TRANSITION_TYPE_SLIDE_RIGHT,
  GTK_REVEALER_TRANSITION_TYPE_SLIDE_LEFT,
  GTK_REVEALER_TRANSITION_TYPE_SLIDE_UP,
  GTK_REVEALER_TRANSITION_TYPE_SLIDE_DOWN
}

GtkRevealer		STRUC
parent_instance		GtkBin <>
GtkRevealer		ENDS

GtkRevealerClass	STRUC
parent_class		GtkBinClass <>
GtkRevealerClass	ENDS

;GType
gtk_revealer_get_type proto __cdecl
;GtkWidget*
gtk_revealer_new proto __cdecl
;gboolean
gtk_revealer_get_reveal_child proto __cdecl \
	      revealer: ptr GtkRevealer

;void
gtk_revealer_set_reveal_child proto __cdecl \
	      revealer: ptr GtkRevealer,
	  reveal_child: gboolean

;gboolean
gtk_revealer_get_child_revealed proto __cdecl \
	      revealer: ptr GtkRevealer

;guint
gtk_revealer_get_transition_duration proto __cdecl \
	      revealer: ptr GtkRevealer

;void
gtk_revealer_set_transition_duration proto __cdecl \
	      revealer: ptr GtkRevealer,
	      duration: guint

;void
gtk_revealer_set_transition_type proto __cdecl \
	      revealer: ptr GtkRevealer,
	    transition: GtkRevealerTransitionType

;GtkRevealerTransitionType
gtk_revealer_get_transition_type proto __cdecl \
	      revealer: ptr GtkRevealer

G_END_DECLS

endif
