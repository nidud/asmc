ifndef __G_VARIANT_TYPE_H__
define __G_VARIANT_TYPE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

define G_VARIANT_TYPE_BOOLEAN       <"b">
define G_VARIANT_TYPE_BYTE          <"y">
define G_VARIANT_TYPE_INT16         <"n">
define G_VARIANT_TYPE_UINT16        <"q">
define G_VARIANT_TYPE_INT32         <"i">
define G_VARIANT_TYPE_UINT32        <"u">
define G_VARIANT_TYPE_INT64         <"x">
define G_VARIANT_TYPE_UINT64        <"t">
define G_VARIANT_TYPE_DOUBLE        <"d">
define G_VARIANT_TYPE_STRING        <"s">
define G_VARIANT_TYPE_OBJECT_PATH   <"o">
define G_VARIANT_TYPE_SIGNATURE     <"g">
define G_VARIANT_TYPE_VARIANT       <"v">
define G_VARIANT_TYPE_HANDLE        <"h">
define G_VARIANT_TYPE_UNIT          <"()">
define G_VARIANT_TYPE_ANY           <"*">
define G_VARIANT_TYPE_BASIC         <"?">
define G_VARIANT_TYPE_MAYBE         <"m*">
define G_VARIANT_TYPE_ARRAY         <"a*">
define G_VARIANT_TYPE_TUPLE         <"r">
define G_VARIANT_TYPE_DICT_ENTRY    <"{?*}">
define G_VARIANT_TYPE_DICTIONARY    <"a{?*}">
define G_VARIANT_TYPE_STRING_ARRAY  <"as">
define G_VARIANT_TYPE_OBJECT_PATH_ARRAY <"ao">
define G_VARIANT_TYPE_BYTESTRING    <"ay">
define G_VARIANT_TYPE_BYTESTRING_ARRAY <"aay">
define G_VARIANT_TYPE_VARDICT       <"a{sv}">

ifndef G_DISABLE_CHECKS
 define G_VARIANT_TYPE (g_variant_type_checked_ ())
else
 G_VARIANT_TYPE macro type_string
    exitm<(type_string)>
    endm
endif


;gboolean
g_variant_type_string_is_valid proto WINAPI \
           type_string: ptr gchar

;gboolean
g_variant_type_string_scan proto WINAPI \
                string: ptr gchar,
                 limit: ptr gchar,
                endptr: ptr gchar



;void
g_variant_type_free proto WINAPI \
                  type: ptr GVariantType

;GVariantType
g_variant_type_copy proto WINAPI \
                  type: ptr GVariantType

;GVariantType
g_variant_type_new proto WINAPI \
           type_string: ptr gchar



;gsize
g_variant_type_get_string_length proto WINAPI \
                  type: ptr GVariantType

;const
g_variant_type_peek_string proto WINAPI \
                  type: ptr GVariantType

;gchar
g_variant_type_dup_string proto WINAPI \
                  type: ptr GVariantType



;gboolean
g_variant_type_is_definite proto WINAPI \
                  type: ptr GVariantType

;gboolean
g_variant_type_is_container proto WINAPI \
                  type: ptr GVariantType

;gboolean
g_variant_type_is_basic proto WINAPI \
                  type: ptr GVariantType

;gboolean
g_variant_type_is_maybe proto WINAPI \
                  type: ptr GVariantType

;gboolean
g_variant_type_is_array proto WINAPI \
                  type: ptr GVariantType

;gboolean
g_variant_type_is_tuple proto WINAPI \
                  type: ptr GVariantType

;gboolean
g_variant_type_is_dict_entry proto WINAPI \
                  type: ptr GVariantType

;gboolean
g_variant_type_is_variant proto WINAPI \
                  type: ptr GVariantType



;guint
g_variant_type_hash proto WINAPI \
                  type: gconstpointer

;gboolean
g_variant_type_equal proto WINAPI \
                 type1: gconstpointer,
                 type2: gconstpointer



;gboolean
g_variant_type_is_subtype_of proto WINAPI \
                  type: ptr GVariantType,
             supertype: ptr GVariantType



;const
g_variant_type_element proto WINAPI \
                  type: ptr GVariantType

;const
g_variant_type_first proto WINAPI \
                  type: ptr GVariantType

;const
g_variant_type_next proto WINAPI \
                  type: ptr GVariantType

;gsize
g_variant_type_n_items proto WINAPI \
                  type: ptr GVariantType

;const
g_variant_type_key proto WINAPI \
                  type: ptr GVariantType

;const
g_variant_type_value proto WINAPI \
                  type: ptr GVariantType



;GVariantType
g_variant_type_new_array proto WINAPI \
               element: ptr GVariantType

;GVariantType
g_variant_type_new_maybe proto WINAPI \
               element: ptr GVariantType

;GVariantType
g_variant_type_new_tuple proto WINAPI \
                 items: ptr GVariantType,
                length: gint

;GVariantType
g_variant_type_new_dict_entry proto WINAPI \
                   key: ptr GVariantType,
                 value: ptr GVariantType



;const
g_variant_type_checked_ proto WINAPI \
                      : ptr gchar

;gsize
g_variant_type_string_get_depth_ proto WINAPI \
           type_string: ptr gchar


endif
