ifndef __GTK_BUILDER_H__
define __GTK_BUILDER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbuilderscope.inc
include gtk/gtkwidget.inc

define GTK_TYPE_BUILDER <gtk_builder_get_type ()>
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

define GTK_BUILDER_ERROR <gtk_builder_error_quark ()>

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
  GTK_BUILDER_ERROR_INVALID_ID,
  GTK_BUILDER_ERROR_INVALID_FUNCTION
}

gtk_builder_error_quark proto

gtk_builder_get_type proto
gtk_builder_new proto

gtk_builder_add_from_file proto :ptr, :ptr, :ptr
gtk_builder_add_from_resource proto :ptr, :ptr, :ptr
gtk_builder_add_from_string proto :ptr, :ptr, :gssize, :ptr
gtk_builder_add_objects_from_file proto :ptr, :ptr, :ptr, :ptr
gtk_builder_add_objects_from_resource proto :ptr, :ptr, :ptr, :ptr
gtk_builder_add_objects_from_string proto :ptr, :ptr, :gssize, :ptr, :ptr
gtk_builder_get_object proto :ptr, :ptr
gtk_builder_get_objects proto :ptr
gtk_builder_expose_object proto :ptr, :ptr, :ptr
gtk_builder_get_current_object proto :ptr
gtk_builder_set_current_object proto :ptr, :ptr
gtk_builder_set_translation_domain proto :ptr, :ptr
gtk_builder_get_translation_domain proto :ptr
gtk_builder_get_scope proto :ptr
gtk_builder_set_scope proto :ptr, :ptr
gtk_builder_get_type_from_name proto :ptr, :ptr

gtk_builder_value_from_string proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_builder_value_from_string_type proto :ptr, :GType, :ptr, :ptr, :ptr
gtk_builder_new_from_file proto :ptr
gtk_builder_new_from_resource proto :ptr
gtk_builder_new_from_string proto :ptr, :gssize

gtk_builder_create_closure proto :ptr, :ptr, :GtkBuilderClosureFlags, :ptr, :ptr

GTK_BUILDER_WARN_INVALID_CHILD_TYPE macro object, type
  exitm<g_warning ("'%s' is not a valid child type of '%s'", type, g_type_name (G_OBJECT_TYPE (object)))>
  endm

gtk_builder_extend_with_template proto :ptr, :ptr, :GType, :ptr, :gssize, :ptr

endif
