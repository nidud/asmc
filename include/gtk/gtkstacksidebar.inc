ifndef __GTK_STACK_SIDEBAR_H__
__GTK_STACK_SIDEBAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc
include gtk/gtkstack.inc

G_BEGIN_DECLS

GTK_TYPE_STACK_SIDEBAR equ <gtk_stack_sidebar_get_type>
GTK_STACK_SIDEBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STACK_SIDEBAR, GtkStackSidebar))>
	endm
GTK_IS_STACK_SIDEBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STACK_SIDEBAR))>
	endm
GTK_STACK_SIDEBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_STACK_SIDEBAR, GtkStackSidebarClass))>
	endm
GTK_IS_STACK_SIDEBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_STACK_SIDEBAR))>
	endm
GTK_STACK_SIDEBAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_STACK_SIDEBAR, GtkStackSidebarClass))>
	endm

GtkStackSidebar		STRUC
parent			GtkBin <>
GtkStackSidebar		ENDS

GtkStackSidebarClass	STRUC
parent_class		GtkBinClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkStackSidebarClass	ENDS

;GType
gtk_stack_sidebar_get_type proto __cdecl
;GtkWidget
gtk_stack_sidebar_new proto __cdecl
;void
gtk_stack_sidebar_set_stack proto __cdecl \
	       sidebar: ptr GtkStackSidebar,
		 stack: ptr GtkStack

;GtkStack
gtk_stack_sidebar_get_stack proto __cdecl \
	       sidebar: ptr GtkStackSidebar


G_END_DECLS

endif
