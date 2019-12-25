ifndef __GTK_EDITABLE_H__
__GTK_EDITABLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_EDITABLE equ <gtk_editable_get_type>
GTK_EDITABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_EDITABLE, GtkEditable))>
	endm
GTK_IS_EDITABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_EDITABLE))>
	endm
GTK_EDITABLE_GET_IFACE macro inst
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_EDITABLE, GtkEditableInterface))>
	endm

GtkEditableInterface	STRUC
base_iface		GTypeInterface <>
insert_text		proc :ptr GtkEditable, :ptr gchar, :gint, :ptr gint
delete_text		proc :ptr GtkEditable, :gint, :gint
changed			proc :ptr GtkEditable
do_insert_text		proc :ptr GtkEditable, :ptr gchar, :gint, :ptr gint
do_delete_text		proc :ptr GtkEditable, :gint, :gint
get_chars		proc :ptr GtkEditable, :gint, :gint
set_selection_bounds	proc :ptr GtkEditable, :gint, :gint
get_selection_bounds	proc :ptr GtkEditable, :ptr gint, :ptr gint
set_position		proc :ptr GtkEditable, :gint
get_position		proc :ptr GtkEditable
GtkEditableInterface	ENDS

;GType
gtk_editable_get_type proto __cdecl
;void
gtk_editable_select_region proto __cdecl \
	      editable: ptr GtkEditable,
	     start_pos: gint,
	       end_pos: gint

;gboolean
gtk_editable_get_selection_bounds proto __cdecl \
	      editable: ptr GtkEditable,
	     start_pos: ptr gint,
	       end_pos: ptr gint

;void
gtk_editable_insert_text proto __cdecl \
	      editable: ptr GtkEditable,
	      new_text: ptr gchar,
       new_text_length: gint,
	      position: ptr gint

;void
gtk_editable_delete_text proto __cdecl \
	      editable: ptr GtkEditable,
	     start_pos: gint,
	       end_pos: gint

;gchar*
gtk_editable_get_chars proto __cdecl \
	      editable: ptr GtkEditable,
	     start_pos: gint,
	       end_pos: gint

;void
gtk_editable_cut_clipboard proto __cdecl \
	      editable: ptr GtkEditable

;void
gtk_editable_copy_clipboard proto __cdecl \
	      editable: ptr GtkEditable

;void
gtk_editable_paste_clipboard proto __cdecl \
	      editable: ptr GtkEditable

;void
gtk_editable_delete_selection proto __cdecl \
	      editable: ptr GtkEditable

;void
gtk_editable_set_position proto __cdecl \
	      editable: ptr GtkEditable,
	      position: gint

;gint
gtk_editable_get_position proto __cdecl \
	      editable: ptr GtkEditable

;void
gtk_editable_set_editable proto __cdecl \
	      editable: ptr GtkEditable,
	   is_editable: gboolean

;gboolean
gtk_editable_get_editable proto __cdecl \
	      editable: ptr GtkEditable


G_END_DECLS

endif
