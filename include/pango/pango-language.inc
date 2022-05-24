ifndef __PANGO_LANGUAGE_H__
define __PANGO_LANGUAGE_H__

include glib.inc
include glib-object.inc

include pango/pango-types.inc
include pango/pango-version-macros.inc
include pango/pango-script.inc

PANGO_TYPE_LANGUAGE equ <pango_language_get_type ()>

pango_language_get_type proto __cdecl
pango_language_get_default proto __cdecl
pango_language_get_preferred proto __cdecl

pango_language_from_string proto __cdecl \
	      language: string_t

pango_language_to_string proto __cdecl \
	      language: ptr PangoLanguage


pango_language_to_string macro language
	exitm<(language)>
	endm

pango_language_get_sample_string proto __cdecl \
	      language: ptr PangoLanguage

pango_language_matches proto __cdecl \
	      language: ptr PangoLanguage,
	    range_list: ptr char_t

pango_language_includes_script proto __cdecl \
	      language: ptr PangoLanguage,
		script: PangoScript

pango_language_get_scripts proto __cdecl \
	      language: ptr PangoLanguage,
	   num_scripts: ptr int_t

endif
