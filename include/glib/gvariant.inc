ifndef __G_VARIANT_H__
define __G_VARIANT_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gvarianttype.inc
include glib/gstring.inc
include glib/gbytes.inc

.enum GVariantClass {
    G_VARIANT_CLASS_BOOLEAN   = 'b',
    G_VARIANT_CLASS_BYTE      = 'y',
    G_VARIANT_CLASS_INT16     = 'n',
    G_VARIANT_CLASS_UINT16    = 'q',
    G_VARIANT_CLASS_INT32     = 'i',
    G_VARIANT_CLASS_UINT32    = 'u',
    G_VARIANT_CLASS_INT64     = 'x',
    G_VARIANT_CLASS_UINT64    = 't',
    G_VARIANT_CLASS_HANDLE    = 'h',
    G_VARIANT_CLASS_DOUBLE    = 'd',
    G_VARIANT_CLASS_STRING    = 's',
    G_VARIANT_CLASS_OBJECT_PATH	  = 'o',
    G_VARIANT_CLASS_SIGNATURE	  = 'g',
    G_VARIANT_CLASS_VARIANT   = 'v',
    G_VARIANT_CLASS_MAYBE     = 'm',
    G_VARIANT_CLASS_ARRAY     = 'a',
    G_VARIANT_CLASS_TUPLE     = '(',
    G_VARIANT_CLASS_DICT_ENTRY	  = '{'
    }

g_variant_unref proto __cdecl :ptr
g_variant_ref proto __cdecl :ptr
g_variant_ref_sink proto __cdecl :ptr
g_variant_is_floating proto __cdecl :ptr
g_variant_take_ref proto __cdecl :ptr
g_variant_get_type proto __cdecl :ptr
g_variant_get_type_string proto __cdecl :ptr
g_variant_is_of_type proto __cdecl :ptr, :ptr
g_variant_is_container proto __cdecl :ptr
g_variant_classify proto __cdecl :ptr
g_variant_new_boolean proto __cdecl :gboolean
g_variant_new_byte proto __cdecl :guint8
g_variant_new_int16 proto __cdecl :gint16
g_variant_new_uint16 proto __cdecl :guint16
g_variant_new_int32 proto __cdecl :gint32
g_variant_new_uint32 proto __cdecl :guint32
g_variant_new_int64 proto __cdecl :gint64
g_variant_new_uint64 proto __cdecl :guint64
g_variant_new_handle proto __cdecl :gint32
g_variant_new_double proto __cdecl :gdouble
g_variant_new_string proto __cdecl :ptr
g_variant_new_take_string proto __cdecl :ptr
g_variant_new_printf proto __Cdecl :ptr, :vararg
g_variant_new_object_path proto __cdecl :ptr
g_variant_is_object_path proto __cdecl :ptr
g_variant_new_signature proto __cdecl :ptr
g_variant_is_signature proto __cdecl :ptr
g_variant_new_variant proto __cdecl :ptr
g_variant_new_strv proto __cdecl :ptr, :gssize
g_variant_new_objv proto __cdecl :ptr, :gssize
g_variant_new_bytestring proto __cdecl :ptr
g_variant_new_bytestring_array proto __cdecl :ptr, :gssize
g_variant_new_fixed_array proto __cdecl :ptr, :gconstpointer, :gsize, :gsize
g_variant_get_boolean proto __cdecl :ptr
g_variant_get_byte proto __cdecl :ptr
g_variant_get_int16 proto __cdecl :ptr
g_variant_get_uint16 proto __cdecl :ptr
g_variant_get_int32 proto __cdecl :ptr
g_variant_get_uint32 proto __cdecl :ptr
g_variant_get_int64 proto __cdecl :ptr
g_variant_get_uint64 proto __cdecl :ptr
g_variant_get_handle proto __cdecl :ptr
g_variant_get_double proto __cdecl :ptr
g_variant_get_variant proto __cdecl :ptr
g_variant_get_string proto __cdecl :ptr, :ptr
g_variant_dup_string proto __cdecl :ptr, :ptr
g_variant_get_strv proto __cdecl :ptr, :ptr
g_variant_dup_strv proto __cdecl :ptr, :ptr
g_variant_get_objv proto __cdecl :ptr, :ptr
g_variant_dup_objv proto __cdecl :ptr, :ptr
g_variant_get_bytestring proto __cdecl :ptr
g_variant_dup_bytestring proto __cdecl :ptr, :ptr
g_variant_get_bytestring_array proto __cdecl :ptr, :ptr
g_variant_dup_bytestring_array proto __cdecl :ptr, :ptr
g_variant_new_maybe proto __cdecl :ptr, :ptr
g_variant_new_array proto __cdecl :ptr, :ptr, :gsize
g_variant_new_tuple proto __cdecl :ptr, :gsize
g_variant_new_dict_entry proto __cdecl :ptr, :ptr

g_variant_get_maybe proto __cdecl :ptr
g_variant_n_children proto __cdecl :ptr
g_variant_get_child proto __Cdecl :ptr, :gsize, :ptr, :vararg
g_variant_get_child_value proto __cdecl :ptr, :gsize
g_variant_lookup proto __Cdecl :ptr, :ptr, :ptr, :vararg
g_variant_lookup_value proto __cdecl :ptr, :ptr, :ptr
g_variant_get_fixed_array proto __cdecl :ptr, :ptr, :gsize
g_variant_get_size proto __cdecl :ptr
g_variant_get_data proto __cdecl :ptr
g_variant_get_data_as_bytes proto __cdecl :ptr
g_variant_store proto __cdecl :ptr, :ptr
g_variant_print proto __cdecl :ptr, :gboolean
g_variant_print_string proto __cdecl :ptr, :ptr, :gboolean
g_variant_hash proto __cdecl :ptr
g_variant_equal proto __cdecl :ptr, :ptr
g_variant_get_normal_form proto __cdecl :ptr
g_variant_is_normal_form proto __cdecl :ptr
g_variant_byteswap proto __cdecl :ptr
g_variant_new_from_bytes proto __cdecl :ptr, :ptr, :gboolean
g_variant_new_from_data proto __cdecl :ptr, :ptr, :gsize, :gboolean, :GDestroyNotify, :ptr

GVariantIter	    STRUC
x	    gsize 16 dup(?)
GVariantIter	    ENDS

g_variant_iter_new proto __cdecl :ptr
g_variant_iter_init proto __cdecl :ptr, :ptr
g_variant_iter_copy proto __cdecl :ptr
g_variant_iter_n_children proto __cdecl :ptr
g_variant_iter_free proto __cdecl :ptr
g_variant_iter_next_value proto __cdecl :ptr
g_variant_iter_next proto __Cdecl :ptr, :ptr, :vararg
g_variant_iter_loop proto __Cdecl :ptr, :ptr, :vararg

GVariantBuilder		STRUC
UNION u
 STRUC s
  partial_magic		gsize ?
  type			ptr GVariantType ?
  y			gsize 14 dup(?)
 ENDS
 x			gsize 16 dup(?)
ENDS
GVariantBuilder		ENDS

.enum GVariantParseError {
    G_VARIANT_PARSE_ERROR_FAILED,
    G_VARIANT_PARSE_ERROR_BASIC_TYPE_EXPECTED,
    G_VARIANT_PARSE_ERROR_CANNOT_INFER_TYPE,
    G_VARIANT_PARSE_ERROR_DEFINITE_TYPE_EXPECTED,
    G_VARIANT_PARSE_ERROR_INPUT_NOT_AT_END,
    G_VARIANT_PARSE_ERROR_INVALID_CHARACTER,
    G_VARIANT_PARSE_ERROR_INVALID_FORMAT_STRING,
    G_VARIANT_PARSE_ERROR_INVALID_OBJECT_PATH,
    G_VARIANT_PARSE_ERROR_INVALID_SIGNATURE,
    G_VARIANT_PARSE_ERROR_INVALID_TYPE_STRING,
    G_VARIANT_PARSE_ERROR_NO_COMMON_TYPE,
    G_VARIANT_PARSE_ERROR_NUMBER_OUT_OF_RANGE,
    G_VARIANT_PARSE_ERROR_NUMBER_TOO_BIG,
    G_VARIANT_PARSE_ERROR_TYPE_ERROR,
    G_VARIANT_PARSE_ERROR_UNEXPECTED_TOKEN,
    G_VARIANT_PARSE_ERROR_UNKNOWN_KEYWORD,
    G_VARIANT_PARSE_ERROR_UNTERMINATED_STRING_CONSTANT,
    G_VARIANT_PARSE_ERROR_VALUE_EXPECTED,
    G_VARIANT_PARSE_ERROR_RECURSION
    }
G_VARIANT_PARSE_ERROR	equ (g_variant_parse_error_quark ())


g_variant_parser_get_error_quark proto __cdecl
g_variant_parse_error_quark proto __cdecl

g_variant_builder_new proto __cdecl :ptr
g_variant_builder_unref proto __cdecl :ptr
g_variant_builder_ref proto __cdecl :ptr
g_variant_builder_init proto __cdecl :ptr, :ptr
g_variant_builder_end proto __cdecl :ptr
g_variant_builder_clear proto __cdecl :ptr
g_variant_builder_open proto __cdecl :ptr, :ptr
g_variant_builder_close proto __cdecl :ptr
g_variant_builder_add_value proto __cdecl :ptr, :ptr
g_variant_builder_add proto __Cdecl :ptr, :ptr, :vararg
g_variant_builder_add_parsed proto __Cdecl :ptr, :ptr, :vararg

g_variant_new proto __Cdecl :ptr, :vararg
g_variant_get proto __Cdecl :ptr, :ptr, :vararg
g_variant_new_va proto __cdecl :ptr, :ptr, :ptr

g_variant_get_va proto __cdecl :ptr, :ptr, :ptr, :ptr
g_variant_check_format_string proto __cdecl :ptr, :ptr, :gboolean
g_variant_parse proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_variant_new_parsed proto __Cdecl :ptr, :vararg
g_variant_new_parsed_va proto __cdecl :ptr, :ptr

g_variant_parse_error_print_context proto __cdecl :ptr, :ptr
g_variant_compare proto __cdecl :ptr, :ptr

GVariantDict		STRUC
UNION u
 STRUC s
  asv			ptr GVariant ?
  partial_magic		gsize ?
  y			gsize 14 dup(?)
 ENDS
 x			gsize 16 dup(?)
ENDS
GVariantDict		ENDS

g_variant_dict_new proto __cdecl :ptr
g_variant_dict_init proto __cdecl :ptr, :ptr
g_variant_dict_lookup proto __Cdecl :ptr, :ptr, :ptr, :vararg
g_variant_dict_lookup_value proto __cdecl :ptr, :ptr, :ptr
g_variant_dict_contains proto __cdecl :ptr, :ptr
g_variant_dict_insert proto __Cdecl :ptr, :ptr, :ptr, :vararg
g_variant_dict_insert_value proto __cdecl :ptr, :ptr, :ptr
g_variant_dict_remove proto __cdecl :ptr, :ptr
g_variant_dict_clear proto __cdecl :ptr
g_variant_dict_end proto __cdecl :ptr
g_variant_dict_ref proto __cdecl :ptr
g_variant_dict_unref proto __cdecl :ptr

endif
