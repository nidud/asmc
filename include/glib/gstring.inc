ifndef __G_STRING_H__
define __G_STRING_H__

if not defined(__GLIB_H_INSIDE__) and not defined(GLIB_COMPILATION)
.err<"Only <glib.h> can be included directly.">
endif

include glib/gtypes.inc
include glib/gunicode.inc
include glib/gbytes.inc
include glib/gutils.inc

.template GString
  strp          ptr gchar ?
  len           gsize ?
  allocated_len gsize ?
 .ends


g_string_new            proto __cdecl :ptr
g_string_new_len        proto __cdecl :ptr, :gssize
g_string_sized_new      proto __cdecl :gsize
g_string_free           proto __cdecl :ptr, :gboolean
g_string_free_to_bytes  proto __cdecl :ptr
g_string_equal          proto __cdecl :ptr, :ptr
g_string_hash           proto __cdecl :ptr
g_string_assign         proto __cdecl :ptr, :ptr
g_string_truncate       proto __cdecl :ptr, :gsize
g_string_set_size       proto __cdecl :ptr, :gsize
g_string_insert_len     proto __cdecl :ptr, :gssize, :ptr, :gssize
g_string_append         proto __cdecl :ptr, :ptr
g_string_append_len     proto __cdecl :ptr, :ptr, :gssize
g_string_append_unichar proto __cdecl :ptr, :gunichar
g_string_prepend        proto __cdecl :ptr, :ptr
g_string_prepend_c      proto __cdecl :ptr, :gchar
g_string_prepend_unichar proto __cdecl :ptr, :gunichar
g_string_prepend_len    proto __cdecl :ptr, :ptr, :gssize
g_string_insert         proto __cdecl :ptr, :gssize, :ptr
g_string_insert_c       proto __cdecl :ptr, :gssize, :gchar
g_string_insert_unichar proto __cdecl :ptr, :gssize, :gunichar
g_string_overwrite      proto __cdecl :ptr, :gsize, :ptr
g_string_overwrite_len  proto __cdecl :ptr, :gsize, :ptr, :gssize
g_string_erase          proto __cdecl :ptr, :gssize, :gssize
g_string_replace        proto __cdecl :ptr, :ptr, :ptr, :guint
g_string_ascii_down     proto __cdecl :ptr
g_string_ascii_up       proto __cdecl :ptr
g_string_vprintf        proto __cdecl :ptr, :ptr, :ptr
g_string_printf         proto __cdecl :ptr, :ptr, :vararg
g_string_append_vprintf proto __cdecl :ptr, :ptr, :ptr
g_string_append_printf  proto __cdecl :ptr, :ptr, :vararg
g_string_append_uri_escaped proto __cdecl :ptr, :ptr, :ptr, :gboolean

ifdef G_CAN_INLINE
g_string_append_c_inline proto fastcall :ptr, :gchar {
  .new gstring:ptr GString = _1
   mov eax,[_1].GString.len
   inc eax
  .if ( eax < [_1].GString.allocated_len )
      mov [_1].GString.len,eax
      mov rcx,[_1].GString.strp
      mov [rcx+rax-1],dl
      mov gchar ptr [rcx+rax],0
  .else
    g_string_insert_c(_1, -1, _2)
  .endif
  mov rax,gstring
  }
define g_string_append_c <g_string_append_c_inline>
else
g_string_append_c       proto __cdecl :ptr, :gchar
endif


g_string_down proto __cdecl :ptr
g_string_up   proto __cdecl :ptr

endif
