ifndef __PANGO_ENGINE_H__
define __PANGO_ENGINE_H__

include pango/pango-types.inc
include pango/pango-item.inc
include pango/pango-font.inc
include pango/pango-glyph.inc
include pango/pango-script.inc

ifndef __GI_SCANNER__

ifndef PANGO_DISABLE_DEPRECATED
define PANGO_RENDER_TYPE_NONE <"PangoRenderNone">

define PANGO_TYPE_ENGINE <pango_engine_get_type ()>
PANGO_ENGINE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_ENGINE, PangoEngine))>
  endm
PANGO_IS_ENGINE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_ENGINE))>
  endm
PANGO_ENGINE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_ENGINE, PangoEngineClass))>
  endm
PANGO_IS_ENGINE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_ENGINE))>
  endm
PANGO_ENGINE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_ENGINE, PangoEngineClass))>
  endm

_PangoEngine            struct
parent_instance         GObject <>
_PangoEngine            ends
PangoEngine             typedef _PangoEngine

_PangoEngineClass       struct
parent_class            GObjectClass <>
_PangoEngineClass       ends
PangoEngineClass        typedef _PangoEngineClass

pango_engine_get_type proto

define PANGO_ENGINE_TYPE_LANG <"PangoEngineLang">

define PANGO_TYPE_ENGINE_LANG <pango_engine_lang_get_type ()>
PANGO_ENGINE_LANG macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_ENGINE_LANG, PangoEngineLang))>
  endm
PANGO_IS_ENGINE_LANG macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_ENGINE_LANG))>
  endm
PANGO_ENGINE_LANG_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_ENGINE_LANG, PangoEngineLangClass))>
  endm
PANGO_IS_ENGINE_LANG_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_ENGINE_LANG))>
  endm
PANGO_ENGINE_LANG_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_ENGINE_LANG, PangoEngineLangClass))>
  endm

_PangoEngineLang        struct
parent_instance         PangoEngine <>
_PangoEngineLang        ends

_PangoEngineLangClass   struct
parent_class            PangoEngineClass <>
script_break            proc :ptr, :ptr, :sdword, :ptr, :ptr, :sdword
_PangoEngineLangClass   ends
PangoEngineLangClass    typedef _PangoEngineLangClass

pango_engine_lang_get_type proto


define PANGO_ENGINE_TYPE_SHAPE <"PangoEngineShape">

define PANGO_TYPE_ENGINE_SHAPE <pango_engine_shape_get_type ()>
PANGO_ENGINE_SHAPE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_ENGINE_SHAPE, PangoEngineShape))>
  endm
PANGO_IS_ENGINE_SHAPE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_ENGINE_SHAPE))>
  endm
PANGO_ENGINE_SHAPE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_ENGINE_SHAPE, PangoEngine_ShapeClass))>
  endm
PANGO_IS_ENGINE_SHAPE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_ENGINE_SHAPE))>
  endm
PANGO_ENGINE_SHAPE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_ENGINE_SHAPE, PangoEngineShapeClass))>
  endm

_PangoEngineShape       struct
parent_instance         PangoEngine <>
_PangoEngineShape       ends

_PangoEngineShapeClass  struct
parent_class            PangoEngineClass <>
script_shape            proc :ptr, :ptr, :ptr, :dword, :ptr, :ptr, :ptr, :dword
covers                  proc :ptr, :ptr, :ptr, :gunichar
_PangoEngineShapeClass  ends
PangoEngineShapeClass   typedef _PangoEngineShapeClass

pango_engine_shape_get_type proto

_PangoEngineScriptInfo  struct
script                  PangoScript ?
langs                   ptr gchar ?
_PangoEngineScriptInfo  ends
PangoEngineScriptInfo   typedef _PangoEngineScriptInfo

_PangoEngineInfo        struct
id                      ptr gchar ?
engine_type             ptr gchar ?
render_type             ptr gchar ?
scripts                 ptr PangoEngineScriptInfo ?
n_scripts               gint ?
_PangoEngineInfo        ends
PangoEngineInfo         typedef _PangoEngineInfo


script_engine_list proto :ptr, :ptr
script_engine_init proto :ptr
script_engine_exit proto
script_engine_create proto :ptr

PANGO_ENGINE_DEFINE_TYPE macro name, prefix, class_init, instance_init, parent_type
  exitm<.err>
  endm


PANGO_ENGINE_LANG_DEFINE_TYPE macro name, prefix, class_init, instance_init
  exitm<.err>
  endm


PANGO_ENGINE_SHAPE_DEFINE_TYPE macro name, prefix, class_init, instance_init
  exitm<.err>
  endm

ifdef PANGO_MODULE_PREFIX
PANGO_MODULE_ENTRY macro func
  exitm<_PANGO_MODULE_ENTRY2(PANGO_MODULE_PREFIX,func)>
  endm
_PANGO_MODULE_ENTRY2 macro prefix,func
  exitm<_PANGO_MODULE_ENTRY3(prefix,func)>
  endm
_PANGO_MODULE_ENTRY3 macro prefix,func
  exitm<&prefix&_script_engine_&func&>
  endm
else
PANGO_MODULE_ENTRY macro func
  exitm<script_engine_##func>
  endm
endif

endif

endif

endif
