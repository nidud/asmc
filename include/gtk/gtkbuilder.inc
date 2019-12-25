ifndef __GTK_BUILDER_H__
__GTK_BUILDER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkapplication.inc
include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_BUILDER equ <gtk_builder_get_type>
GTK_BUILDER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_BUILDER, GtkBuilder))>
	endm
GTK_BUILDER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_BUILDER, GtkBuilderClass))>
	endm
GTK_IS_BUILDER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BUILDER))>
	endm
GTK_IS_BUILDER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_BUILDER))>
	endm
GTK_BUILDER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_BUILDER, GtkBuilderClass))>
	endm

GTK_BUILDER_ERROR equ <gtk_builder_error_quarq>

.enum GtkBuilderError {
  GTK_BUILDER_ERROR_INVALID_TYPE_FUNCTION,
  GTK_BUILDER_ERROR_UNHANDLED_TAG,
  GTK_BUILDER_ERROR_MISSING_ATTRIBUTE,
  GTK_BUILDER_ERROR_INVALID_ATTRIBUTE,
  GTK_BUILDER_ERROR_INVALID_TAG,
  GTK_BUILDER_ERROR_MISSING_PROPERTY_VALUE,
  GTK_BUILDER_ERROR_INVALID_VALUE,
  GTK_BUILDER_ERROR_VERSION_MISMATCH,
  GTK_BUILDER_ERROR_DUPLICATE_ID,
  GTK_BUILDER_ERROR_OBJECT_TYPE_REFUSED,
  GTK_BUILDER_ERROR_TEMPLATE_MISMATCH,
  GTK_BUILDER_ERROR_INVALID_PROPERTY,
  GTK_BUILDER_ERROR_INVALID_SIGNAL,
  GTK_BUILDER_ERROR_INVALID_ID
}

;GQuark
gtk_builder_error_quark proto __cdecl

GtkBuilder		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkBuilder		ENDS

GtkBuilderClass		STRUC
parent_class		GObjectClass <>
get_type_from_name	proc :ptr GtkBuilder, :ptr
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkBuilderClass		ENDS

;GType
gtk_builder_get_type proto __cdecl
;GtkBuilder*
gtk_builder_new proto __cdecl

;guint
gtk_builder_add_from_file proto __cdecl \
	       builder: ptr GtkBuilder,
	      filename: ptr gchar,
		 error: ptr GError

;guint
gtk_builder_add_from_resource proto __cdecl \
	       builder: ptr GtkBuilder,
	 resource_path: ptr gchar,
		 error: ptr GError

;guint
gtk_builder_add_from_string proto __cdecl \
	       builder: ptr GtkBuilder,
		buffer: ptr gchar,
		length: gsize,
		 error: ptr GError

;guint
gtk_builder_add_objects_from_file proto __cdecl \
	       builder: ptr GtkBuilder,
	      filename: ptr gchar,
	    object_ids: ptr gchar,
		 error: ptr GError

;guint
gtk_builder_add_objects_from_resource proto __cdecl \
	       builder: ptr GtkBuilder,
	 resource_path: ptr gchar,
	    object_ids: ptr gchar,
		 error: ptr GError

;guint
gtk_builder_add_objects_from_string proto __cdecl \
	       builder: ptr GtkBuilder,
		buffer: ptr gchar,
		length: gsize,
	    object_ids: ptr gchar,
		 error: ptr GError

;GObject*
gtk_builder_get_object proto __cdecl \
	       builder: ptr GtkBuilder,
		  name: ptr gchar

;GSList*
gtk_builder_get_objects proto __cdecl \
	       builder: ptr GtkBuilder

;void
gtk_builder_expose_object proto __cdecl \
	       builder: ptr GtkBuilder,
		  name: ptr gchar,
		object: ptr GObject

;void
gtk_builder_connect_signals proto __cdecl \
	       builder: ptr GtkBuilder,
	     user_data: gpointer

;void
gtk_builder_connect_signals_full proto __cdecl \
	       builder: ptr GtkBuilder,
		  func: GtkBuilderConnectFunc,
	     user_data: gpointer

;void
gtk_builder_set_translation_domain proto __cdecl \
	       builder: ptr GtkBuilder,
		domain: ptr gchar

;const
gtk_builder_get_translation_domain proto __cdecl \
	       builder: ptr GtkBuilder

;GType
gtk_builder_get_type_from_name proto __cdecl \
	       builder: ptr GtkBuilder,
	     type_name: ptr char_t


;gboolean
gtk_builder_value_from_string proto __cdecl \
	       builder: ptr GtkBuilder,
		 pspec: ptr GParamSpec,
		string: ptr gchar,
		 value: ptr GValue,
		 error: ptr GError

;gboolean
gtk_builder_value_from_string_type proto __cdecl \
	       builder: ptr GtkBuilder,
		  type: GType,
		string: ptr gchar,
		 value: ptr GValue,
		 error: ptr GError

;GtkBuilder
gtk_builder_new_from_file proto __cdecl \
	      filename: ptr gchar

;GtkBuilder
gtk_builder_new_from_resource proto __cdecl \
	 resource_path: ptr gchar

;GtkBuilder
gtk_builder_new_from_string proto __cdecl \
		string: ptr gchar,
		length: gssize


;void
gtk_builder_add_callback_symbol proto __cdecl \
	       builder: ptr GtkBuilder,
	 callback_name: ptr gchar,
       callback_symbol: GCallback

;void
gtk_builder_add_callback_symbols proto _CDecl \
	       builder: ptr GtkBuilder,
   first_callback_name: ptr gchar,
 first_callback_symbol: GCallback,
		      : vararg

;GCallback
gtk_builder_lookup_callback_symbol proto __cdecl \
	       builder: ptr GtkBuilder,
	 callback_name: ptr gchar


;void
gtk_builder_set_application proto __cdecl \
	       builder: ptr GtkBuilder,
	   application: ptr GtkApplication


;GtkApplication
gtk_builder_get_application proto __cdecl \
	       builder: ptr GtkBuilder


GTK_BUILDER_WARN_INVALID_CHILD_TYPE macro object, type
	exitm<g_warning ("'%s' is not a valid child type of '%s'", type, g_type_name (G_OBJECT_TYPE (object)))>
	endm

G_END_DECLS

endif
