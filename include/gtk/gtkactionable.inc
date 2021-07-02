ifndef __GTK_ACTIONABLE_H__
__GTK_ACTIONABLE_H__ equ <>

include glib-object.inc
include gdk/gdk.inc

G_BEGIN_DECLS

GTK_TYPE_ACTIONABLE equ <gtk_actionable_get_type>
GTK_ACTIONABLE macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), GTK_TYPE_ACTIONABLE, GtkActionable))>
	endm

GTK_IS_ACTIONABLE macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), GTK_TYPE_ACTIONABLE, GtkActionableInterface))>
	endm
GTK_ACTIONABLE_GET_IFACE macro inst
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_ACTIONABLE, GtkActionableInterface))>
	endm


GtkActionableInterface	STRUC
g_iface			GTypeInterface <>
get_action_name		proc :ptr GtkActionable
set_action_name		proc :ptr GtkActionable, :ptr gchar
get_action_target_value proc :ptr GtkActionable
set_action_target_value proc :ptr GtkActionable, :ptr GVariant
GtkActionableInterface	ENDS

;GType
gtk_actionable_get_type proto __cdecl

gtk_actionable_get_action_name proto __cdecl \
	    actionable: ptr GtkActionable

gtk_actionable_set_action_name proto __cdecl \
	    actionable: ptr GtkActionable,
	   action_name: ptr gchar

;GVariant
gtk_actionable_get_action_target_value proto __cdecl \
	    actionable: ptr GtkActionable

gtk_actionable_set_action_target_value proto __cdecl \
	    actionable: ptr GtkActionable,
	  target_value: ptr GVariant

gtk_actionable_set_action_target proto _CDecl \
	    actionable: ptr GtkActionable,
	 format_string: ptr gchar,
		      : vararg

gtk_actionable_set_detailed_action_name proto __cdecl \
	    actionable: ptr GtkActionable,
  detailed_action_name: ptr gchar


G_END_DECLS

endif
