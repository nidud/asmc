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

pango_tab_array_new proto __cdecl \
	  initial_size: gint,
   positions_in_pixels: gboolean

pango_tab_array_new_with_positions proto __cdecl \
		  size: gint,
   positions_in_pixels: gboolean,
       first_alignment: PangoTabAlign,
	first_position: gint,
		      : vararg

pango_tab_array_get_type proto __cdecl

pango_tab_array_copy proto __cdecl \
	     tab_array: ptr PangoTabArray

;void
pango_tab_array_free proto __cdecl \
	     tab_array: ptr PangoTabArray


pango_tab_array_get_size proto __cdecl \
	     tab_array: ptr PangoTabArray

;void
pango_tab_array_resize proto __cdecl \
	     tab_array: ptr PangoTabArray,
	      new_size: gint

;void
pango_tab_array_set_tab proto __cdecl \
	     tab_array: ptr PangoTabArray,
	     tab_index: gint,
	     alignment: PangoTabAlign,
	      location: gint

;void
pango_tab_array_get_tab proto __cdecl \
	     tab_array: ptr PangoTabArray,
	     tab_index: gint,
	     alignment: ptr PangoTabAlign,
	      location: ptr gint

;void
pango_tab_array_get_tabs proto __cdecl \
	     tab_array: ptr PangoTabArray,
	    alignments: ptr PangoTabAlign,
	     locations: ptr gint


pango_tab_array_get_positions_in_pixels proto __cdecl


;void
pango_tab_array_set_positions_in_pixels proto __cdecl \
	     tab_array: ptr PangoTabArray,
   positions_in_pixels: gboolean



pango_tab_array_to_string proto __cdecl \
	     tab_array: ptr PangoTabArray

pango_tab_array_from_string proto __cdecl \
		      : ptr

;void
pango_tab_array_set_decimal_point proto __cdecl \
	     tab_array: ptr PangoTabArray,
	     tab_index: SINT,
	 decimal_point: gunichar


pango_tab_array_get_decimal_point proto __cdecl \
	     tab_array: ptr PangoTabArray,
	     tab_index: SINT

;void
pango_tab_array_sort proto __cdecl \
	     tab_array: ptr PangoTabArray

G_DEFINE_AUTOPTR_CLEANUP_FUNC(PangoTabArray, pango_tab_array_free)

endif
