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

;void
g_variant_unref proto __cdecl \
	 value: ptr GVariant

;GVariant
g_variant_ref proto __cdecl \
	 value: ptr GVariant

;GVariant
g_variant_ref_sink proto __cdecl \
	 value: ptr GVariant

;gboolean
g_variant_is_floating proto __cdecl \
	 value: ptr GVariant

;GVariant
g_variant_take_ref proto __cdecl \
	 value: ptr GVariant


;const
g_variant_get_type proto __cdecl \
	 value: ptr GVariant

;const
g_variant_get_type_string proto __cdecl \
	 value: ptr GVariant

;gboolean
g_variant_is_of_type proto __cdecl \
	 value: ptr GVariant,
	  type: ptr GVariantType

;gboolean
g_variant_is_container proto __cdecl \
	 value: ptr GVariant

;GVariantClass
g_variant_classify proto __cdecl \
	 value: ptr GVariant

;GVariant
g_variant_new_boolean proto __cdecl \
	 value: gboolean

;GVariant
g_variant_new_byte proto __cdecl \
	 value: guint8

;GVariant
g_variant_new_int16 proto __cdecl \
	 value: gint16

;GVariant
g_variant_new_uint16 proto __cdecl \
	 value: guint16

;GVariant
g_variant_new_int32 proto __cdecl \
	 value: gint32

;GVariant
g_variant_new_uint32 proto __cdecl \
	 value: guint32

;GVariant
g_variant_new_int64 proto __cdecl \
	 value: gint64

;GVariant
g_variant_new_uint64 proto __cdecl \
	 value: guint64

;GVariant
g_variant_new_handle proto __cdecl \
	 value: gint32

;GVariant
g_variant_new_double proto __cdecl \
	 value: gdouble

;GVariant
g_variant_new_string proto __cdecl \
	string: ptr gchar

;GVariant
g_variant_new_take_string proto __cdecl \
	string: ptr gchar

;GVariant
g_variant_new_printf proto __Cdecl \
     format_string: ptr gchar,
		  : vararg

;GVariant
g_variant_new_object_path proto __cdecl \
       object_path: ptr gchar

;gboolean
g_variant_is_object_path proto __cdecl \
	string: ptr gchar

;GVariant
g_variant_new_signature proto __cdecl \
	 signature: ptr gchar

;gboolean
g_variant_is_signature proto __cdecl \
	string: ptr gchar

;GVariant
g_variant_new_variant proto __cdecl \
	 value: ptr GVariant

;GVariant
g_variant_new_strv proto __cdecl \
	  strv: ptr gchar,
	length: gssize

;GVariant
g_variant_new_objv proto __cdecl \
	  strv: ptr gchar,
	length: gssize

;GVariant
g_variant_new_bytestring proto __cdecl \
	string: ptr gchar

;GVariant
g_variant_new_bytestring_array proto __cdecl \
	  strv: ptr gchar,
	length: gssize

;GVariant
g_variant_new_fixed_array proto __cdecl \
      element_type: ptr GVariantType,
	  elements: gconstpointer,
	n_elements: gsize,
      element_size: gsize

;gboolean
g_variant_get_boolean proto __cdecl \
	 value: ptr GVariant

;guint8
g_variant_get_byte proto __cdecl \
	 value: ptr GVariant

;gint16
g_variant_get_int16 proto __cdecl \
	 value: ptr GVariant

;guint16
g_variant_get_uint16 proto __cdecl \
	 value: ptr GVariant

;gint32
g_variant_get_int32 proto __cdecl \
	 value: ptr GVariant

;guint32
g_variant_get_uint32 proto __cdecl \
	 value: ptr GVariant

;gint64
g_variant_get_int64 proto __cdecl \
	 value: ptr GVariant

;guint64
g_variant_get_uint64 proto __cdecl \
	 value: ptr GVariant

;gint32
g_variant_get_handle proto __cdecl \
	 value: ptr GVariant

;gdouble
g_variant_get_double proto __cdecl \
	 value: ptr GVariant

;GVariant
g_variant_get_variant proto __cdecl \
	 value: ptr GVariant

;const
g_variant_get_string proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize

;gchar
g_variant_dup_string proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize

;const
g_variant_get_strv proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize

;gchar
g_variant_dup_strv proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize

;const
g_variant_get_objv proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize

;gchar
g_variant_dup_objv proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize

;const
g_variant_get_bytestring proto __cdecl \
	 value: ptr GVariant

;gchar
g_variant_dup_bytestring proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize

;const
g_variant_get_bytestring_array proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize

;gchar
g_variant_dup_bytestring_array proto __cdecl \
	 value: ptr GVariant,
	length: ptr gsize


;GVariant
g_variant_new_maybe proto __cdecl \
	child_type: ptr GVariantType,
	 child: ptr GVariant

;GVariant
g_variant_new_array proto __cdecl \
	child_type: ptr GVariantType,
	  children: ptr,
	n_children: gsize

;GVariant
g_variant_new_tuple proto __cdecl \
	  children: ptr,
	n_children: gsize

;GVariant
g_variant_new_dict_entry proto __cdecl \
	   key: ptr GVariant,
	 value: ptr GVariant


;GVariant
g_variant_get_maybe proto __cdecl \
	 value: ptr GVariant

;gsize
g_variant_n_children proto __cdecl \
	 value: ptr GVariant

;void
g_variant_get_child proto __Cdecl \
	 value: ptr GVariant,
	index_: gsize,
     format_string: ptr gchar,
	      : vararg

;GVariant
g_variant_get_child_value proto __cdecl \
	 value: ptr GVariant,
	index_: gsize

;gboolean
g_variant_lookup proto __Cdecl \
	dictionary: ptr GVariant,
	   key: ptr gchar,
     format_string: ptr gchar,
	      : vararg

;GVariant
g_variant_lookup_value proto __cdecl \
	dictionary: ptr GVariant,
	   key: ptr gchar,
     expected_type: ptr GVariantType

;gconstpointer
g_variant_get_fixed_array proto __cdecl \
	 value: ptr GVariant,
	n_elements: ptr gsize,
      element_size: gsize


;gsize
g_variant_get_size proto __cdecl \
	 value: ptr GVariant

;gconstpointer
g_variant_get_data proto __cdecl \
	 value: ptr GVariant

;GBytes
g_variant_get_data_as_bytes proto __cdecl \
	 value: ptr GVariant

;void
g_variant_store proto __cdecl \
	 value: ptr GVariant,
	  data: gpointer


;gchar
g_variant_print proto __cdecl \
	 value: ptr GVariant,
     type_annotate: gboolean

;GString
g_variant_print_string proto __cdecl \
	 value: ptr GVariant,
	string: ptr GString,
     type_annotate: gboolean


;guint
g_variant_hash proto __cdecl \
	 value: gconstpointer

;gboolean
g_variant_equal proto __cdecl \
	   one: gconstpointer,
	   two: gconstpointer


;GVariant
g_variant_get_normal_form proto __cdecl \
	 value: ptr GVariant

;gboolean
g_variant_is_normal_form proto __cdecl \
	 value: ptr GVariant

;GVariant
g_variant_byteswap proto __cdecl \
	 value: ptr GVariant


;GVariant
g_variant_new_from_bytes proto __cdecl \
	  type: ptr GVariantType,
	 bytes: ptr GBytes,
	   trusted: gboolean

;GVariant
g_variant_new_from_data proto __cdecl \
	  type: ptr GVariantType,
	  data: gconstpointer,
	  size: gsize,
	   trusted: gboolean,
	notify: GDestroyNotify,
	 user_data: gpointer


GVariantIter	    STRUC
x	    gsize 16 dup(?)
GVariantIter	    ENDS

;GVariantIter
g_variant_iter_new proto __cdecl \
	 value: ptr GVariant

;gsize
g_variant_iter_init proto __cdecl \
	  iter: ptr GVariantIter,
	 value: ptr GVariant

;GVariantIter
g_variant_iter_copy proto __cdecl \
	  iter: ptr GVariantIter

;gsize
g_variant_iter_n_children proto __cdecl \
	  iter: ptr GVariantIter

;void
g_variant_iter_free proto __cdecl \
	  iter: ptr GVariantIter

;GVariant
g_variant_iter_next_value proto __cdecl \
	  iter: ptr GVariantIter

;gboolean
g_variant_iter_next proto __Cdecl \
	  iter: ptr GVariantIter,
     format_string: ptr gchar,
	      : vararg

;gboolean
g_variant_iter_loop proto __Cdecl \
	  iter: ptr GVariantIter,
     format_string: ptr gchar,
	      : vararg



GVariantBuilder	    STRUC
UNION u
 STRUC s
  partial_magic	    gsize ?
  type		ptr GVariantType ?
  y	    gsize 14 dup(?)
 ENDS
 x	    gsize 16 dup(?)
ENDS
GVariantBuilder	    ENDS

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

;GLIB_DEPRECATED_IN_2_38_FOR(g_variant_parse_error_quark)

g_variant_parser_get_error_quark proto __cdecl

;GQuark
g_variant_parse_error_quark proto __cdecl

G_VARIANT_BUILDER_INIT macro variant_type
    exitm<.err>
    endm

;GVariantBuilder
g_variant_builder_new proto __cdecl \
	  type: ptr GVariantType

;void
g_variant_builder_unref proto __cdecl \
	   builder: ptr GVariantBuilder

;GVariantBuilder
g_variant_builder_ref proto __cdecl \
	   builder: ptr GVariantBuilder

;void
g_variant_builder_init proto __cdecl \
	   builder: ptr GVariantBuilder,
	  type: ptr GVariantType

;GVariant
g_variant_builder_end proto __cdecl \
	   builder: ptr GVariantBuilder

;void
g_variant_builder_clear proto __cdecl \
	   builder: ptr GVariantBuilder

;void
g_variant_builder_open proto __cdecl \
	   builder: ptr GVariantBuilder,
	  type: ptr GVariantType

;void
g_variant_builder_close proto __cdecl \
	   builder: ptr GVariantBuilder

;void
g_variant_builder_add_value proto __cdecl \
	   builder: ptr GVariantBuilder,
	 value: ptr GVariant

;void
g_variant_builder_add proto __Cdecl \
	   builder: ptr GVariantBuilder,
     format_string: ptr gchar,
	      : vararg

;void
g_variant_builder_add_parsed proto __Cdecl \
	   builder: ptr GVariantBuilder,
	format: ptr gchar,
	      : vararg


;GVariant
g_variant_new proto __Cdecl \
     format_string: ptr gchar,
	      : vararg

;void
g_variant_get proto __Cdecl \
	 value: ptr GVariant,
     format_string: ptr gchar,
	      : vararg

;GVariant
g_variant_new_va proto __cdecl \
     format_string: ptr gchar,
	endptr: ptr gchar,
	   app: ptr va_list

;void
g_variant_get_va proto __cdecl \
	 value: ptr GVariant,
     format_string: ptr gchar,
	endptr: ptr gchar,
	   app: ptr va_list

;gboolean
g_variant_check_format_string proto __cdecl \
	 value: ptr GVariant,
     format_string: ptr gchar,
	 copy_only: gboolean


;GVariant
g_variant_parse proto __cdecl \
	  type: ptr GVariantType,
	  text: ptr gchar,
	 limit: ptr gchar,
	endptr: ptr gchar,
	 error: ptr GError

;GVariant
g_variant_new_parsed proto __Cdecl \
	format: ptr gchar,
	      : vararg

;GVariant
g_variant_new_parsed_va proto __cdecl \
	format: ptr gchar,
	   app: ptr va_list


;gchar
g_variant_parse_error_print_context proto __cdecl \
	 error: ptr GError,
	source_str: ptr gchar


;gint
g_variant_compare proto __cdecl \
	   one: gconstpointer,
	   two: gconstpointer


GVariantDict	    STRUC
UNION u
 STRUC s
  asv		ptr GVariant ?
  partial_magic	    gsize ?
  y	    gsize 14 dup(?)
 ENDS
 x	    gsize 16 dup(?)
ENDS
GVariantDict	    ENDS

G_VARIANT_DICT_INIT macro asv
    exitm<.err>
    endm

;GVariantDict
g_variant_dict_new proto __cdecl \
	  from_asv: ptr GVariant


;void
g_variant_dict_init proto __cdecl \
	  dict: ptr GVariantDict,
	  from_asv: ptr GVariant


;gboolean
g_variant_dict_lookup proto __Cdecl \
	  dict: ptr GVariantDict,
	   key: ptr gchar,
     format_string: ptr gchar,
	      : vararg

;GVariant
g_variant_dict_lookup_value proto __cdecl \
	  dict: ptr GVariantDict,
	   key: ptr gchar,
     expected_type: ptr GVariantType

;gboolean
g_variant_dict_contains proto __cdecl \
	  dict: ptr GVariantDict,
	   key: ptr gchar

;void
g_variant_dict_insert proto __Cdecl \
	  dict: ptr GVariantDict,
	   key: ptr gchar,
     format_string: ptr gchar,
	      : vararg

;void
g_variant_dict_insert_value proto __cdecl \
	  dict: ptr GVariantDict,
	   key: ptr gchar,
	 value: ptr GVariant

;gboolean
g_variant_dict_remove proto __cdecl \
	  dict: ptr GVariantDict,
	   key: ptr gchar

;void
g_variant_dict_clear proto __cdecl \
	  dict: ptr GVariantDict

;GVariant
g_variant_dict_end proto __cdecl \
	  dict: ptr GVariantDict

;GVariantDict
g_variant_dict_ref proto __cdecl \
	  dict: ptr GVariantDict

;void
g_variant_dict_unref proto __cdecl \
	  dict: ptr GVariantDict


endif
