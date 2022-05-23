ifndef __PANGO_BREAK_H__
define __PANGO_BREAK_H__

include glib.inc
include pango/pango-item.inc

_PangoLogAttr           struct
RECORD
is_line_break           guint :  1 ?
is_mandatory_break      guint :  1 ?
is_char_break           guint :  1 ?
is_white                guint :  1 ?
is_cursor_position      guint :  1 ?
is_word_start           guint :  1 ?
is_word_end             guint :  1 ?
is_sentence_boundary    guint :  1 ?
is_sentence_start       guint :  1 ?
is_sentence_end         guint :  1 ?
backspace_deletes_character guint :  1 ?
is_expandable_space     guint :  1 ?
is_word_boundary        guint :  1 ?
break_inserts_hyphen    guint :  1 ?
break_removes_preceding guint :  1 ?
reserved                guint : 17 ?
ENDS
_PangoLogAttr           ends

pango_break proto :ptr, :sdword, :ptr, :ptr, :sdword
pango_get_log_attrs proto :ptr, :sdword, :sdword, :ptr, :ptr, :sdword
pango_default_break proto :ptr, :sdword, :ptr, :ptr, :sdword
pango_tailor_break proto :ptr, :sdword, :ptr, :sdword, :ptr, :sdword
pango_attr_break proto :ptr, :sdword, :ptr, :sdword, :ptr, :sdword

endif
