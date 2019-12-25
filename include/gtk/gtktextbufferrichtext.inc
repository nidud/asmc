ifndef __GTK_TEXT_BUFFER_RICH_TEXT_H__
__GTK_TEXT_BUFFER_RICH_TEXT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktextbuffer.inc

G_BEGIN_DECLS

CALLBACKC(GtkTextBufferSerializeFunc, :ptr GtkTextBuffer, \
                                      :ptr GtkTextBuffer, \
                                      :ptr GtkTextIter, \
                                      :ptr GtkTextIter, \
                                      :ptr gsize, \
                                      :gpointer)

CALLBACKC(GtkTextBufferDeserializeFunc, :ptr GtkTextBuffer, \
                                        :ptr GtkTextBuffer, \
                                        :ptr GtkTextIter, \
                                        :ptr guint8, \
                                        :gsize, \
                                        :gboolean, \
                                        :gpointer, \
                                        :ptr ptr GError)

;GdkAtom
gtk_text_buffer_register_serialize_format proto __cdecl \
                buffer: ptr GtkTextBuffer,
             mime_type: ptr gchar,
              function: GtkTextBufferSerializeFunc,
             user_data: gpointer,
     user_data_destroy: GDestroyNotify

;GdkAtom
gtk_text_buffer_register_serialize_tagset proto __cdecl \
                buffer: ptr GtkTextBuffer,
           tagset_name: ptr gchar


;GdkAtom
gtk_text_buffer_register_deserialize_format proto __cdecl \
                buffer: ptr GtkTextBuffer,
             mime_type: ptr gchar,
              function: GtkTextBufferDeserializeFunc,
             user_data: gpointer,
     user_data_destroy: GDestroyNotify

;GdkAtom
gtk_text_buffer_register_deserialize_tagset proto __cdecl \
                buffer: ptr GtkTextBuffer,
           tagset_name: ptr gchar


;void
gtk_text_buffer_unregister_serialize_format proto __cdecl \
                buffer: ptr GtkTextBuffer,
                format: GdkAtom

;void
gtk_text_buffer_unregister_deserialize_format proto __cdecl \
                buffer: ptr GtkTextBuffer,
                format: GdkAtom


;void
gtk_text_buffer_deserialize_set_can_create_tags proto __cdecl \
                buffer: ptr GtkTextBuffer,
                format: GdkAtom,
       can_create_tags: gboolean

;gboolean
gtk_text_buffer_deserialize_get_can_create_tags proto __cdecl \
                buffer: ptr GtkTextBuffer,
                format: GdkAtom


;GdkAtom
gtk_text_buffer_get_serialize_formats proto __cdecl \
                buffer: ptr GtkTextBuffer,
             n_formats: ptr gint

;GdkAtom
gtk_text_buffer_get_deserialize_formats proto __cdecl \
                buffer: ptr GtkTextBuffer,
             n_formats: ptr gint


;guint8
gtk_text_buffer_serialize proto __cdecl \
       register_buffer: ptr GtkTextBuffer,
        content_buffer: ptr GtkTextBuffer,
                format: GdkAtom,
                 start: ptr GtkTextIter,
                  _end: ptr GtkTextIter,
                length: ptr gsize

;gboolean
gtk_text_buffer_deserialize proto __cdecl \
       register_buffer: ptr GtkTextBuffer,
        content_buffer: ptr GtkTextBuffer,
                format: GdkAtom,
                  iter: ptr GtkTextIter,
                  data: ptr guint8,
                length: gsize,
                 error: ptr GError

G_END_DECLS

endif
