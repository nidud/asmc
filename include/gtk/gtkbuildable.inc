ifndef __GTK_BUILDABLE_H__
__GTK_BUILDABLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbuilder.inc

G_BEGIN_DECLS

GTK_TYPE_BUILDABLE equ <gtk_buildable_get_type>
GTK_BUILDABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_BUILDABLE, GtkBuildable))>
	endm
GTK_BUILDABLE_CLASS macro obj
	exitm<(G_TYPE_CHECK_CLASS_CAST ((obj), GTK_TYPE_BUILDABLE, GtkBuildableIface))>
	endm
GTK_IS_BUILDABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BUILDABLE))>
	endm
GTK_BUILDABLE_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_BUILDABLE, GtkBuildableIface))>
	endm


GtkBuildableIface	STRUC
g_iface			GTypeInterface <>
set_name		proc :ptr GtkBuildable, :ptr gchar
get_name		proc :ptr GtkBuildable
add_child		proc :ptr GtkBuildable, :ptr GtkBuilder, :ptr GObject, :ptr
set_buildable_property	proc :ptr GtkBuildable, :ptr GtkBuilder, :ptr gchar, :ptr GValue
construct_child		proc :ptr GtkBuildable, :ptr GtkBuilder, :ptr gchar
custom_tag_start	proc :ptr GtkBuildable, :ptr GtkBuilder, :ptr GObject, :ptr gchar, :ptr GMarkupParser, :ptr gpointer
custom_tag_end		proc :ptr GtkBuildable, :ptr GtkBuilder, :ptr GObject, :ptr gchar, :ptr gpointer
custom_finished		proc :ptr GtkBuildable, :ptr GtkBuilder, :ptr GObject, :ptr gchar, :gpointer
parser_finished		proc :ptr GtkBuildable, :ptr GtkBuilder
get_internal_child	proc :ptr GtkBuildable, :ptr GtkBuilder, :ptr gchar
GtkBuildableIface	ENDS


;GType
gtk_buildable_get_type proto __cdecl

;void
gtk_buildable_set_name proto __cdecl \
	     buildable: ptr GtkBuildable,
		  name: ptr gchar

;const
gtk_buildable_get_name proto __cdecl \
	     buildable: ptr GtkBuildable

;void
gtk_buildable_add_child proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		 child: ptr GObject,
		  type: ptr gchar

;void
gtk_buildable_set_buildable_property proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		  name: ptr gchar,
		 value: ptr GValue

;GObject
gtk_buildable_construct_child proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		  name: ptr gchar

;gboolean
gtk_buildable_custom_tag_start proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		 child: ptr GObject,
	       tagname: ptr gchar,
		parser: ptr GMarkupParser,
		  data: ptr gpointer

;void
gtk_buildable_custom_tag_end proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		 child: ptr GObject,
	       tagname: ptr gchar,
		  data: ptr gpointer

;void
gtk_buildable_custom_finished proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
		 child: ptr GObject,
	       tagname: ptr gchar,
		  data: gpointer

;void
gtk_buildable_parser_finished proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder

;GObject
gtk_buildable_get_internal_child proto __cdecl \
	     buildable: ptr GtkBuildable,
	       builder: ptr GtkBuilder,
	     childname: ptr gchar


G_END_DECLS

endif
