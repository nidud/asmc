ifndef __GTK_ASSISTANT_H__
__GTK_ASSISTANT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

G_BEGIN_DECLS

GTK_TYPE_ASSISTANT equ <gtk_assistant_get_type>
GTK_ASSISTANT macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_ASSISTANT, GtkAssistant))>
	endm
GTK_ASSISTANT_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_CAST	  ((c), GTK_TYPE_ASSISTANT, GtkAssistantClass))>
	endm
GTK_IS_ASSISTANT macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_ASSISTANT))>
	endm
GTK_IS_ASSISTANT_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_TYPE	  ((c), GTK_TYPE_ASSISTANT))>
	endm
GTK_ASSISTANT_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS  ((o), GTK_TYPE_ASSISTANT, GtkAssistantClass))>
	endm

.enum GtkAssistantPageType {
  GTK_ASSISTANT_PAGE_CONTENT,
  GTK_ASSISTANT_PAGE_INTRO,
  GTK_ASSISTANT_PAGE_CONFIRM,
  GTK_ASSISTANT_PAGE_SUMMARY,
  GTK_ASSISTANT_PAGE_PROGRESS,
  GTK_ASSISTANT_PAGE_CUSTOM
}

GtkAssistant		STRUC
parent			GtkWindow <>
priv			ptr_t ?
GtkAssistant		ENDS

GtkAssistantClass	STRUC
parent_class		GtkWindowClass <>
prepare			proc :ptr GtkAssistant, :ptr GtkWidget
apply			proc :ptr GtkAssistant
close			proc :ptr GtkAssistant
cancel			proc :ptr GtkAssistant
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
GtkAssistantClass	ENDS

CALLBACKC(GtkAssistantPageFunc, :gint, :gpointer)

;GType
gtk_assistant_get_type proto __cdecl
;GtkWidget
gtk_assistant_new proto __cdecl
;void
gtk_assistant_next_page proto __cdecl \
	     assistant: ptr GtkAssistant

;void
gtk_assistant_previous_page proto __cdecl \
	     assistant: ptr GtkAssistant

;gint
gtk_assistant_get_current_page proto __cdecl \
	     assistant: ptr GtkAssistant

;void
gtk_assistant_set_current_page proto __cdecl \
	     assistant: ptr GtkAssistant,
	      page_num: gint

;gint
gtk_assistant_get_n_pages proto __cdecl \
	     assistant: ptr GtkAssistant

;GtkWidget
gtk_assistant_get_nth_page proto __cdecl \
	     assistant: ptr GtkAssistant,
	      page_num: gint

;gint
gtk_assistant_prepend_page proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget

;gint
gtk_assistant_append_page proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget

;gint
gtk_assistant_insert_page proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget,
	      position: gint

;void
gtk_assistant_remove_page proto __cdecl \
	     assistant: ptr GtkAssistant,
	      page_num: gint

;void
gtk_assistant_set_forward_page_func proto __cdecl \
	     assistant: ptr GtkAssistant,
	     page_func: GtkAssistantPageFunc,
		  data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_assistant_set_page_type proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget,
		  type: GtkAssistantPageType

;GtkAssistantPageType
gtk_assistant_get_page_type proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget

;void
gtk_assistant_set_page_title proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget,
		 title: ptr gchar

;const
gtk_assistant_get_page_title proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget


;void
gtk_assistant_set_page_header_image proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget,
		pixbuf: ptr GdkPixbuf

;GdkPixbuf
gtk_assistant_get_page_header_image proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget

;void
gtk_assistant_set_page_side_image proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget,
		pixbuf: ptr GdkPixbuf

;GdkPixbuf
gtk_assistant_get_page_side_image proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget


;void
gtk_assistant_set_page_complete proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget,
	      complete: gboolean

;gboolean
gtk_assistant_get_page_complete proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget

;void
gtk_assistant_add_action_widget proto __cdecl \
	     assistant: ptr GtkAssistant,
		 child: ptr GtkWidget

;void
gtk_assistant_remove_action_widget proto __cdecl \
	     assistant: ptr GtkAssistant,
		 child: ptr GtkWidget


;void
gtk_assistant_update_buttons_state proto __cdecl \
	     assistant: ptr GtkAssistant

;void
gtk_assistant_commit proto __cdecl \
	     assistant: ptr GtkAssistant


;void
gtk_assistant_set_page_has_padding proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget,
	   has_padding: gboolean

;gboolean
gtk_assistant_get_page_has_padding proto __cdecl \
	     assistant: ptr GtkAssistant,
		  page: ptr GtkWidget

G_END_DECLS

endif
