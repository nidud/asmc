ifndef __GTK_EXPRESSION_H__
define __GTK_EXPRESSION_H__

include gtk/gtktypes.inc

define GTK_TYPE_EXPRESSION <gtk_expression_get_type ()>
define GTK_TYPE_EXPRESSION_WATCH <gtk_expression_watch_get_type ()>

GTK_IS_EXPRESSION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_EXPRESSION))>
  endm
GTK_EXPRESSION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_EXPRESSION, GtkExpression))>
  endm

;GtkExpression           typedef _GtkExpression
;GtkExpressionWatch      typedef _GtkExpressionWatch

CALLBACK(GtkExpressionNotify, :gpointer)

gtk_expression_get_type proto
gtk_expression_ref proto :ptr
gtk_expression_unref proto :ptr
gtk_expression_get_value_type proto :ptr
gtk_expression_is_static proto :ptr
gtk_expression_evaluate proto :ptr, :gpointer, :ptr
gtk_expression_watch proto :ptr, :gpointer, :GtkExpressionNotify, :gpointer, :GDestroyNotify
gtk_expression_bind proto :ptr, :gpointer, :ptr, :gpointer
gtk_expression_watch_get_type proto
gtk_expression_watch_ref proto :ptr
gtk_expression_watch_unref proto :ptr
gtk_expression_watch_evaluate proto :ptr, :ptr
gtk_expression_watch_unwatch proto :ptr

define GTK_TYPE_PROPERTY_EXPRESSION <gtk_property_expression_get_type ()>
;GtkPropertyExpression   typedef _GtkPropertyExpression

gtk_property_expression_get_type proto
gtk_property_expression_new proto :GType, :ptr, :ptr
gtk_property_expression_new_for_pspec proto :ptr, :ptr
gtk_property_expression_get_expression proto :ptr
gtk_property_expression_get_pspec proto :ptr

define GTK_TYPE_CONSTANT_EXPRESSION <gtk_constant_expression_get_type ()>
;GtkConstantExpression   typedef _GtkConstantExpression

gtk_constant_expression_get_type proto
gtk_constant_expression_new proto :GType, :vararg
gtk_constant_expression_new_for_value proto :ptr
gtk_constant_expression_get_value proto :ptr

define GTK_TYPE_OBJECT_EXPRESSION <gtk_object_expression_get_type ()>
;GtkObjectExpression     typedef _GtkObjectExpression

gtk_object_expression_get_type proto
gtk_object_expression_new proto :ptr
gtk_object_expression_get_object proto :ptr

define GTK_TYPE_CLOSURE_EXPRESSION <gtk_closure_expression_get_type ()>
;GtkClosureExpression    typedef _GtkClosureExpression

gtk_closure_expression_get_type proto
gtk_closure_expression_new proto :GType, :ptr, :guint, :ptr

define GTK_TYPE_CCLOSURE_EXPRESSION <gtk_cclosure_expression_get_type ()>
;GtkCClosureExpression   typedef _GtkCClosureExpression

gtk_cclosure_expression_get_type proto
gtk_cclosure_expression_new proto :GType, :GClosureMarshal, :guint, :ptr, :GCallback, :gpointer, :GClosureNotify

GTK_VALUE_HOLDS_EXPRESSION macro value
  exitm<(G_VALUE_HOLDS ((value), GTK_TYPE_EXPRESSION))>
  endm

gtk_value_set_expression proto :ptr, :ptr
gtk_value_take_expression proto :ptr, :ptr
gtk_value_get_expression proto :ptr
gtk_value_dup_expression proto :ptr

define GTK_TYPE_PARAM_SPEC_EXPRESSION <gtk_param_expression_get_type ()>
GTK_PARAM_SPEC_EXPRESSION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PARAM_SPEC_EXPRESSION, GtkParamSpecExpression))>
  endm
GTK_IS_PARAM_SPEC_EXPRESSION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PARAM_SPEC_EXPRESSION))>
  endm

GtkParamSpecExpression  struct
parent_instance         GParamSpec <>
GtkParamSpecExpression  ends

gtk_param_expression_get_type proto
gtk_param_spec_expression proto :ptr, :ptr, :ptr, :GParamFlags

endif
