ifndef __GTK_TABLE_H__
__GTK_TABLE_H__ equ <>

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only <gtk/gtk.h> can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_TABLE equ <gtk_table_get_type>
GTK_TABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TABLE, GtkTable))>
	endm
GTK_TABLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TABLE, GtkTableClass))>
	endm
GTK_IS_TABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TABLE))>
	endm
GTK_IS_TABLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TABLE))>
	endm
GTK_TABLE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TABLE, GtkTableClass))>
	endm

GtkTable		STRUC
  container		GtkContainer <>
  priv			ptr_t ?
GtkTable		ENDS

GtkTableClass		STRUC
  parent_class		GtkContainerClass <>
  _gtk_reserved1	proc
  _gtk_reserved2	proc
  _gtk_reserved3	proc
  _gtk_reserved4	proc
GtkTableClass		ENDS

GtkTableChild		STRUC
  widget		ptr_t ?
  left_attach		guint16 ?
  right_attach		guint16 ?
  top_attach		guint16 ?
  bottom_attach		guint16 ?
  xpadding		guint16 ?
  ypadding		guint16 ?
  xexpand		guint ? ; : 1;
  ;guint yexpand : 1;
  ;guint xshrink : 1;
  ;guint yshrink : 1;
  ;guint xfill : 1;
  ;guint yfill : 1;
GtkTableChild		ENDS

GtkTableRowCol		STRUC
  requisition		guint16 ?
  allocation		guint16 ?
  spacing		guint16 ?
  need_expand		guint ? ; : 1;
  ;guint need_shrink : 1;
  ;guint expand : 1;
  ;guint shrink : 1;
  ;guint empty : 1;
GtkTableRowCol		ENDS

.enum GtkAttachOptions {
  GTK_EXPAND = 1 shl 0,
  GTK_SHRINK = 1 shl 1,
  GTK_FILL   = 1 shl 2
}


;GType
gtk_table_get_type		proto
;GtkWidget*
gtk_table_new			proto :guint, :guint, :gboolean
gtk_table_resize		proto :ptr GtkTable, :guint, :guint
gtk_table_attach		proto :ptr GtkTable, :ptr GtkWidget, :guint,
					:guint, :guint, :guint, :GtkAttachOptions,
					:GtkAttachOptions, :guint, :guint
gtk_table_attach_defaults	proto :ptr GtkTable, :ptr GtkWidget, :guint,
					:guint, :guint, :guint
gtk_table_set_row_spacing	proto :ptr GtkTable, :guint, :guint
;guint
gtk_table_get_row_spacing	proto :ptr GtkTable, :guint
gtk_table_set_col_spacing	proto :ptr GtkTable, :guint, :guint
;guint
gtk_table_get_col_spacing	proto :ptr GtkTable, :guint
gtk_table_set_row_spacings	proto :ptr GtkTable, :guint
;guint
gtk_table_get_default_row_spacing proto :ptr GtkTable
gtk_table_set_col_spacings	proto :ptr GtkTable, :guint
;guint
gtk_table_get_default_col_spacing proto :ptr GtkTable
gtk_table_set_homogeneous	proto :ptr GtkTable, :gboolean
;gboolean
gtk_table_get_homogeneous	proto :ptr GtkTable
gtk_table_get_size		proto :ptr GtkTable, :ptr guint, :ptr guint

G_END_DECLS

endif
