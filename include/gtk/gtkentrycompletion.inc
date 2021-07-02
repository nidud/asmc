ifndef __GTK_ENTRY_COMPLETION_H__
__GTK_ENTRY_COMPLETION_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktreemodel.inc
include gtk/gtkliststore.inc
include gtk/gtkcellarea.inc
include gtk/gtktreeviewcolumn.inc
include gtk/gtktreemodelfilter.inc

G_BEGIN_DECLS

GTK_TYPE_ENTRY_COMPLETION equ <gtk_entry_completion_get_type>
GTK_ENTRY_COMPLETION macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ENTRY_COMPLETION, GtkEntryCompletion))>
	endm
GTK_ENTRY_COMPLETION_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ENTRY_COMPLETION, GtkEntryCompletionClass))>
	endm
GTK_IS_ENTRY_COMPLETION macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ENTRY_COMPLETION))>
	endm
GTK_IS_ENTRY_COMPLETION_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ENTRY_COMPLETION))>
	endm
GTK_ENTRY_COMPLETION_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ENTRY_COMPLETION, GtkEntryCompletionClass))>
	endm

CALLBACKC(GtkEntryCompletionMatchFunc, :ptr GtkEntryCompletion, :ptr gchar, :ptr GtkTreeIter, :gpointer)

GtkEntryCompletion	STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkEntryCompletion	ENDS

GtkEntryCompletionClass STRUC
parent_class		GObjectClass <>
match_selected		proc :ptr GtkEntryCompletion, :ptr GtkTreeModel, :ptr GtkTreeIter
action_activated	proc :ptr GtkEntryCompletion, :gint
insert_prefix		proc :ptr GtkEntryCompletion, :ptr gchar
cursor_on_match		proc :ptr GtkEntryCompletion, :ptr GtkTreeModel, :ptr GtkTreeIter
no_matches		proc :ptr GtkEntryCompletion
_gtk_reserved0		proc
_gtk_reserved1		proc
_gtk_reserved2		proc
GtkEntryCompletionClass ENDS

;GType
gtk_entry_completion_get_type proto __cdecl
;GtkEntryCompletion
gtk_entry_completion_new proto __cdecl
;GtkEntryCompletion
gtk_entry_completion_new_with_area proto __cdecl \
		  area: ptr GtkCellArea


;GtkWidget
gtk_entry_completion_get_entry proto __cdecl \
	    completion: ptr GtkEntryCompletion


;void
gtk_entry_completion_set_model proto __cdecl \
	    completion: ptr GtkEntryCompletion,
		 model: ptr GtkTreeModel

;GtkTreeModel
gtk_entry_completion_get_model proto __cdecl \
	    completion: ptr GtkEntryCompletion


;void
gtk_entry_completion_set_match_func proto __cdecl \
	    completion: ptr GtkEntryCompletion,
		  func: GtkEntryCompletionMatchFunc,
	     func_data: gpointer,
	   func_notify: GDestroyNotify

;void
gtk_entry_completion_set_minimum_key_length proto __cdecl \
	    completion: ptr GtkEntryCompletion,
		length: gint

;gint
gtk_entry_completion_get_minimum_key_length proto __cdecl \
	    completion: ptr GtkEntryCompletion

;gchar
gtk_entry_completion_compute_prefix proto __cdecl \
	    completion: ptr GtkEntryCompletion,
		   key: ptr char_t

;void
gtk_entry_completion_complete proto __cdecl \
	    completion: ptr GtkEntryCompletion

;void
gtk_entry_completion_insert_prefix proto __cdecl \
	    completion: ptr GtkEntryCompletion


;void
gtk_entry_completion_insert_action_text proto __cdecl \
	    completion: ptr GtkEntryCompletion,
		index_: gint,
		  text: ptr gchar

;void
gtk_entry_completion_insert_action_markup proto __cdecl \
	    completion: ptr GtkEntryCompletion,
		index_: gint,
		markup: ptr gchar

;void
gtk_entry_completion_delete_action proto __cdecl \
	    completion: ptr GtkEntryCompletion,
		index_: gint


;void
gtk_entry_completion_set_inline_completion proto __cdecl \
	    completion: ptr GtkEntryCompletion,
     inline_completion: gboolean

;gboolean
gtk_entry_completion_get_inline_completion proto __cdecl \
	    completion: ptr GtkEntryCompletion

;void
gtk_entry_completion_set_inline_selection proto __cdecl \
	    completion: ptr GtkEntryCompletion,
      inline_selection: gboolean

;gboolean
gtk_entry_completion_get_inline_selection proto __cdecl \
	    completion: ptr GtkEntryCompletion

;void
gtk_entry_completion_set_popup_completion proto __cdecl \
	    completion: ptr GtkEntryCompletion,
      popup_completion: gboolean

;gboolean
gtk_entry_completion_get_popup_completion proto __cdecl \
	    completion: ptr GtkEntryCompletion

;void
gtk_entry_completion_set_popup_set_width proto __cdecl \
	    completion: ptr GtkEntryCompletion,
       popup_set_width: gboolean

;gboolean
gtk_entry_completion_get_popup_set_width proto __cdecl \
	    completion: ptr GtkEntryCompletion

;void
gtk_entry_completion_set_popup_single_match proto __cdecl \
	    completion: ptr GtkEntryCompletion,
    popup_single_match: gboolean

;gboolean
gtk_entry_completion_get_popup_single_match proto __cdecl \
	    completion: ptr GtkEntryCompletion


;const
gtk_entry_completion_get_completion_prefix proto __cdecl \
	    completion: ptr GtkEntryCompletion

;void
gtk_entry_completion_set_text_column proto __cdecl \
	    completion: ptr GtkEntryCompletion,
		column: gint

;gint
gtk_entry_completion_get_text_column proto __cdecl \
	    completion: ptr GtkEntryCompletion


G_END_DECLS

endif
