ifndef __GTK_STACK_SWITCHER_H__
__GTK_STACK_SWITCHER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbox.inc
include gtk/gtkstack.inc

G_BEGIN_DECLS

GTK_TYPE_STACK_SWITCHER equ <gtk_stack_switcher_get_type>
GTK_STACK_SWITCHER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STACK_SWITCHER, GtkStackSwitcher))>
	endm
GTK_STACK_SWITCHER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_STACK_SWITCHER, GtkStackSwitcherClass))>
	endm
GTK_IS_STACK_SWITCHER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STACK_SWITCHER))>
	endm
GTK_IS_STACK_SWITCHER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_STACK_SWITCHER))>
	endm
GTK_STACK_SWITCHER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_STACK_SWITCHER, GtkStackSwitcherClass))>
	endm

GtkStackSwitcher	STRUC
widget			GtkBox <>
GtkStackSwitcher	ENDS

GtkStackSwitcherClass	STRUC
parent_class		GtkBoxClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkStackSwitcherClass	ENDS

;GType
gtk_stack_switcher_get_type proto __cdecl
;GtkWidget
gtk_stack_switcher_new proto __cdecl
;void
gtk_stack_switcher_set_stack proto __cdecl \
	      switcher: ptr GtkStackSwitcher,
		 stack: ptr GtkStack

;GtkStack
gtk_stack_switcher_get_stack proto __cdecl \
	      switcher: ptr GtkStackSwitcher


G_END_DECLS

endif
