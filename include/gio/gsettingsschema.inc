ifndef __G_SETTINGS_SCHEMA_H__
define __G_SETTINGS_SCHEMA_H__

include glib-object.inc

define G_TYPE_SETTINGS_SCHEMA_SOURCE                   <g_settings_schema_source_get_type ()>
g_settings_schema_source_get_type proto

g_settings_schema_source_get_default proto
g_settings_schema_source_ref proto :ptr
g_settings_schema_source_unref proto :ptr
g_settings_schema_source_new_from_directory proto :ptr, :ptr, :gboolean, :ptr
g_settings_schema_source_lookup proto :ptr, :ptr, :gboolean
g_settings_schema_source_list_schemas proto :ptr, :gboolean, :ptr, :ptr

define G_TYPE_SETTINGS_SCHEMA                          <g_settings_schema_get_type ()>
g_settings_schema_get_type proto

g_settings_schema_ref proto :ptr
g_settings_schema_unref proto :ptr
g_settings_schema_get_id proto :ptr
g_settings_schema_get_path proto :ptr
g_settings_schema_get_key proto :ptr, :ptr
g_settings_schema_has_key proto :ptr, :ptr
g_settings_schema_list_keys proto :ptr
g_settings_schema_list_children proto :ptr

define G_TYPE_SETTINGS_SCHEMA_KEY                      <g_settings_schema_key_get_type ()>
g_settings_schema_key_get_type proto

g_settings_schema_key_ref proto :ptr
g_settings_schema_key_unref proto :ptr

g_settings_schema_key_get_value_type proto :ptr
g_settings_schema_key_get_default_value proto :ptr
g_settings_schema_key_get_range proto :ptr
g_settings_schema_key_range_check proto :ptr, :ptr

g_settings_schema_key_get_name proto :ptr
g_settings_schema_key_get_summary proto :ptr
g_settings_schema_key_get_description proto :ptr

endif
