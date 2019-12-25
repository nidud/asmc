ifndef __GTK_SELECTION_H__
__GTK_SELECTION_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtktextiter.inc

GtkTargetPair		STRUC
target			GdkAtom ?
flags			guint ?
info			guint ?
GtkTargetPair		ENDS

GTK_TYPE_SELECTION_DATA equ <gtk_selection_data_get_type>
GTK_TYPE_TARGET_LIST	equ <gtk_target_list_get_type>

GtkTargetEntry		STRUC
target			string_t ?
flags			guint ?
info			guint ?
GtkTargetEntry		ENDS

;GType
gtk_target_list_get_type proto __cdecl
;GtkTargetList
gtk_target_list_new proto __cdecl \
	       targets: ptr GtkTargetEntry,
	      ntargets: guint

;GtkTargetList
gtk_target_list_ref proto __cdecl \
		  list: ptr GtkTargetList

;void
gtk_target_list_unref proto __cdecl \
		  list: ptr GtkTargetList

;void
gtk_target_list_add proto __cdecl \
		  list: ptr GtkTargetList,
		target: GdkAtom,
		 flags: guint,
		  info: guint

;void
gtk_target_list_add_text_targets proto __cdecl \
		  list: ptr GtkTargetList,
		  info: guint

;void
gtk_target_list_add_rich_text_targets proto __cdecl \
		  list: ptr GtkTargetList,
		  info: guint,
	deserializable: gboolean,
		buffer: ptr GtkTextBuffer

;void
gtk_target_list_add_image_targets proto __cdecl \
		  list: ptr GtkTargetList,
		  info: guint,
	      writable: gboolean

;void
gtk_target_list_add_uri_targets proto __cdecl \
		  list: ptr GtkTargetList,
		  info: guint

;void
gtk_target_list_add_table proto __cdecl \
		  list: ptr GtkTargetList,
	       targets: ptr GtkTargetEntry,
	      ntargets: guint

;void
gtk_target_list_remove proto __cdecl \
		  list: ptr GtkTargetList,
		target: GdkAtom

;gboolean
gtk_target_list_find proto __cdecl \
		  list: ptr GtkTargetList,
		target: GdkAtom,
		  info: ptr guint


;GtkTargetEntry
gtk_target_table_new_from_list proto __cdecl \
		  list: ptr GtkTargetList,
	     n_targets: ptr gint

;void
gtk_target_table_free proto __cdecl \
	       targets: ptr GtkTargetEntry,
	     n_targets: gint


;gboolean
gtk_selection_owner_set proto __cdecl \
		widget: ptr GtkWidget,
	     selection: GdkAtom,
		 time_: guint32

;gboolean
gtk_selection_owner_set_for_display proto __cdecl \
	       display: ptr GdkDisplay,
		widget: ptr GtkWidget,
	     selection: GdkAtom,
		 time_: guint32


;void
gtk_selection_add_target proto __cdecl \
		widget: ptr GtkWidget,
	     selection: GdkAtom,
		target: GdkAtom,
		  info: guint

;void
gtk_selection_add_targets proto __cdecl \
		widget: ptr GtkWidget,
	     selection: GdkAtom,
	       targets: ptr GtkTargetEntry,
	      ntargets: guint

;void
gtk_selection_clear_targets proto __cdecl \
		widget: ptr GtkWidget,
	     selection: GdkAtom

;gboolean
gtk_selection_convert proto __cdecl \
		widget: ptr GtkWidget,
	     selection: GdkAtom,
		target: GdkAtom,
		 time_: guint32

;void
gtk_selection_remove_all proto __cdecl \
		widget: ptr GtkWidget


;GdkAtom
gtk_selection_data_get_selection proto __cdecl \
	selection_data: ptr GtkSelectionData

;GdkAtom
gtk_selection_data_get_target proto __cdecl \
	selection_data: ptr GtkSelectionData

;GdkAtom
gtk_selection_data_get_data_type proto __cdecl \
	selection_data: ptr GtkSelectionData

;gint
gtk_selection_data_get_format proto __cdecl \
	selection_data: ptr GtkSelectionData

;const
gtk_selection_data_get_data proto __cdecl \
	selection_data: ptr GtkSelectionData

;gint
gtk_selection_data_get_length proto __cdecl \
	selection_data: ptr GtkSelectionData

;const
gtk_selection_data_get_data_with_length proto __cdecl \
	selection_data: ptr GtkSelectionData,
		length: ptr gint


;GdkDisplay
gtk_selection_data_get_display proto __cdecl \
	selection_data: ptr GtkSelectionData


;void
gtk_selection_data_set proto __cdecl \
	selection_data: ptr GtkSelectionData,
		  type: GdkAtom,
		format: gint,
		  data: ptr guchar,
		length: gint

;gboolean
gtk_selection_data_set_text proto __cdecl \
	selection_data: ptr GtkSelectionData,
		  _str: ptr gchar,
		   len: gint

;guchar
gtk_selection_data_get_text proto __cdecl \
	selection_data: ptr GtkSelectionData

;gboolean
gtk_selection_data_set_pixbuf proto __cdecl \
	selection_data: ptr GtkSelectionData,
		pixbuf: ptr GdkPixbuf

;GdkPixbuf
gtk_selection_data_get_pixbuf proto __cdecl \
	selection_data: ptr GtkSelectionData

;gboolean
gtk_selection_data_set_uris proto __cdecl \
	selection_data: ptr GtkSelectionData,
		  uris: ptr gchar

;gchar
gtk_selection_data_get_uris proto __cdecl \
	selection_data: ptr GtkSelectionData


;gboolean
gtk_selection_data_get_targets proto __cdecl \
	selection_data: ptr GtkSelectionData,
	       targets: ptr GdkAtom,
	       n_atoms: ptr gint

;gboolean
gtk_selection_data_targets_include_text proto __cdecl \
	selection_data: ptr GtkSelectionData

;gboolean
gtk_selection_data_targets_include_rich_text proto __cdecl \
	selection_data: ptr GtkSelectionData,
		buffer: ptr GtkTextBuffer

;gboolean
gtk_selection_data_targets_include_image proto __cdecl \
	selection_data: ptr GtkSelectionData,
	      writable: gboolean

;gboolean
gtk_selection_data_targets_include_uri proto __cdecl \
	selection_data: ptr GtkSelectionData

;gboolean
gtk_targets_include_text proto __cdecl \
	       targets: ptr GdkAtom,
	     n_targets: gint

;gboolean
gtk_targets_include_rich_text proto __cdecl \
	       targets: ptr GdkAtom,
	     n_targets: gint,
		buffer: ptr GtkTextBuffer

;gboolean
gtk_targets_include_image proto __cdecl \
	       targets: ptr GdkAtom,
	     n_targets: gint,
	      writable: gboolean

;gboolean
gtk_targets_include_uri proto __cdecl \
	       targets: ptr GdkAtom,
	     n_targets: gint



;GType
gtk_selection_data_get_type proto __cdecl
;GtkSelectionData
gtk_selection_data_copy proto __cdecl \
		  data: ptr GtkSelectionData

;void
gtk_selection_data_free proto __cdecl \
		  data: ptr GtkSelectionData


;GType
gtk_target_entry_get_type proto __cdecl
;GtkTargetEntry
gtk_target_entry_new proto __cdecl \
		target: ptr gchar,
		 flags: guint,
		  info: guint

;GtkTargetEntry
gtk_target_entry_copy proto __cdecl \
		  data: ptr GtkTargetEntry

;void
gtk_target_entry_free proto __cdecl \
		  data: ptr GtkTargetEntry

endif
