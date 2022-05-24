ifndef __GSK_GL_SHADER_H__
define __GSK_GL_SHADER_H__

if not defined (__GSK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gsk/gsk.h can be included directly.">
endif

include stdarg.inc

include gsk/gsktypes.inc
include gsk/gskenums.inc

define GSK_TYPE_SHADER_ARGS_BUILDER <gsk_shader_args_builder_get_type ()>

;GskShaderArgsBuilder    typedef _GskShaderArgsBuilder

define GSK_TYPE_GL_SHADER <gsk_gl_shader_get_type ()>

gsk_gl_shader_new_from_bytes proto :ptr
gsk_gl_shader_new_from_resource proto :ptr
gsk_gl_shader_compile proto :ptr, :ptr, :ptr
gsk_gl_shader_get_source proto :ptr
gsk_gl_shader_get_resource proto :ptr
gsk_gl_shader_get_n_textures proto :ptr
gsk_gl_shader_get_n_uniforms proto :ptr
gsk_gl_shader_get_uniform_name proto :ptr, :sdword
gsk_gl_shader_find_uniform_by_name proto :ptr, :ptr
gsk_gl_shader_get_uniform_type proto :ptr, :sdword
gsk_gl_shader_get_uniform_offset proto :ptr, :sdword
gsk_gl_shader_get_args_size proto :ptr

gsk_gl_shader_format_args_va proto :ptr, :va_list
gsk_gl_shader_format_args proto :ptr, :vararg

gsk_gl_shader_get_arg_float proto :ptr, :ptr, :sdword
gsk_gl_shader_get_arg_int proto :ptr, :ptr, :sdword
gsk_gl_shader_get_arg_uint proto :ptr, :ptr, :sdword
gsk_gl_shader_get_arg_bool proto :ptr, :ptr, :sdword
gsk_gl_shader_get_arg_vec2 proto :ptr, :ptr, :sdword, :ptr
gsk_gl_shader_get_arg_vec3 proto :ptr, :ptr, :sdword, :ptr
gsk_gl_shader_get_arg_vec4 proto :ptr, :ptr, :sdword, :ptr

gsk_shader_args_builder_get_type proto

gsk_shader_args_builder_new proto :ptr, :ptr
gsk_shader_args_builder_to_args proto :ptr
gsk_shader_args_builder_free_to_args proto :ptr
gsk_shader_args_builder_ref proto :ptr
gsk_shader_args_builder_unref proto :ptr

gsk_shader_args_builder_set_float proto :ptr, :sdword, :real4
gsk_shader_args_builder_set_int proto :ptr, :sdword, :gint32
gsk_shader_args_builder_set_uint proto :ptr, :sdword, :guint32
gsk_shader_args_builder_set_bool proto :ptr, :sdword, :gboolean
gsk_shader_args_builder_set_vec2 proto :ptr, :sdword, :ptr
gsk_shader_args_builder_set_vec3 proto :ptr, :sdword, :ptr
gsk_shader_args_builder_set_vec4 proto :ptr, :sdword, :ptr

endif
