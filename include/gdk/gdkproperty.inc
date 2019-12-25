ifndef __GDK_PROPERTY_H__
__GDK_PROPERTY_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

.enum GdkPropMode {
  GDK_PROP_MODE_REPLACE,
  GDK_PROP_MODE_PREPEND,
  GDK_PROP_MODE_APPEND
}

;GdkAtom
gdk_atom_intern proto __cdecl \
             atom_name: ptr gchar,
        only_if_exists: gboolean

;GdkAtom
gdk_atom_intern_static_string proto __cdecl \
             atom_name: ptr gchar

;gchar*
gdk_atom_name proto __cdecl \
                  atom: GdkAtom

;gboolean
gdk_property_get proto __cdecl \
                window: ptr GdkWindow,
              property: GdkAtom,
                  type: GdkAtom,
               _offset: gulong,
                length: gulong,
               pdelete: gint,
  actual_property_type: ptr GdkAtom,
         actual_format: ptr gint,
         actual_length: ptr gint,
                  data: ptr guchar

gdk_property_change proto __cdecl \
                window: ptr GdkWindow,
              property: GdkAtom,
                  type: GdkAtom,
                format: gint,
                  mode: GdkPropMode,
                  data: ptr guchar,
             nelements: gint

gdk_property_delete proto __cdecl \
                window: ptr GdkWindow,
              property: GdkAtom

;gint
gdk_text_property_to_utf8_list_for_display proto __cdecl \
               display: ptr GdkDisplay,
              encoding: GdkAtom,
                format: gint,
                  text: ptr guchar,
                length: gint,
                  list: ptr gchar

;gchar
gdk_utf8_to_string_target proto __cdecl \
                  _str: ptr gchar

endif
