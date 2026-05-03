ifndef __PANGO_TABS_H__
define __PANGO_TABS_H__

include pango/pango-types.inc

.enum PangoTabAlign {
    PANGO_TAB_LEFT,
    PANGO_TAB_RIGHT,
    PANGO_TAB_CENTER,
    PANGO_TAB_DECIMAL
    }

define PANGO_TYPE_TAB_ARRAY <pango_tab_array_get_type ()>

pango_tab_array_new proto __cdecl :gint, :gboolean
pango_tab_array_new_with_positions proto __cdecl :gint, :gboolean, :PangoTabAlign, :gint, :vararg
pango_tab_array_get_type proto __cdecl
pango_tab_array_copy proto __cdecl :ptr
pango_tab_array_free proto __cdecl :ptr
pango_tab_array_get_size proto __cdecl :ptr
pango_tab_array_resize proto __cdecl :ptr, :gint
pango_tab_array_set_tab proto __cdecl :ptr, :gint, :PangoTabAlign, :gint
pango_tab_array_get_tab proto __cdecl :ptr, :gint, :ptr, :ptr
pango_tab_array_get_tabs proto __cdecl :ptr, :ptr, :ptr
pango_tab_array_get_positions_in_pixels proto __cdecl
pango_tab_array_set_positions_in_pixels proto __cdecl :ptr, :gboolean
pango_tab_array_to_string proto __cdecl :ptr
pango_tab_array_from_string proto __cdecl :ptr
pango_tab_array_set_decimal_point proto __cdecl :ptr, :SINT, :gunichar
pango_tab_array_get_decimal_point proto __cdecl :ptr, :SINT
pango_tab_array_sort proto __cdecl :ptr

G_DEFINE_AUTOPTR_CLEANUP_FUNC(PangoTabArray, pango_tab_array_free)

endif
