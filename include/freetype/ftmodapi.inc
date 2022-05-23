ifndef FTMODAPI_H_
define FTMODAPI_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_MODULE_FONT_DRIVER	     1
define FT_MODULE_RENDERER	     2
define FT_MODULE_HINTER		     4
define FT_MODULE_STYLER		     8

define FT_MODULE_DRIVER_SCALABLE      0x100
define FT_MODULE_DRIVER_NO_OUTLINES   0x200
define FT_MODULE_DRIVER_HAS_HINTER    0x400
define FT_MODULE_DRIVER_HINTS_LIGHTLY 0x800

define ft_module_font_driver	     FT_MODULE_FONT_DRIVER
define ft_module_renderer	     FT_MODULE_RENDERER
define ft_module_hinter		     FT_MODULE_HINTER
define ft_module_styler		     FT_MODULE_STYLER

define ft_module_driver_scalable       FT_MODULE_DRIVER_SCALABLE
define ft_module_driver_no_outlines    FT_MODULE_DRIVER_NO_OUTLINES
define ft_module_driver_has_hinter     FT_MODULE_DRIVER_HAS_HINTER
define ft_module_driver_hints_lightly  FT_MODULE_DRIVER_HINTS_LIGHTLY

FT_Module_Interface	typedef FT_Pointer

CALLBACKC(FT_Module_Constructor, :FT_Module)
CALLBACKC(FT_Module_Destructor, :FT_Module)
CALLBACKC(FT_Module_Requester, :FT_Module, :ptr)

FT_Module_Class		STRUC
module_flags		FT_ULong ?
module_size		FT_Long ?
module_name		ptr FT_String ?
module_version		FT_Fixed ?
module_requires		FT_Fixed ?
module_interface	ptr ?
module_init		FT_Module_Constructor ?
module_done		FT_Module_Destructor ?
get_interface		FT_Module_Requester ?
FT_Module_Class		ENDS

FT_Add_Module proto \
	       library: FT_Library,
		 clazz: ptr FT_Module_Class

FT_Get_Module proto \
	       library: FT_Library,
	   module_name: ptr

FT_Remove_Module proto \
	       library: FT_Library,
		module: FT_Module

FT_FACE_DRIVER_NAME macro face
	exitm<.err>
	endm

FT_Property_Set proto \
	       library: FT_Library,
	   module_name: ptr FT_String,
	 property_name: ptr FT_String,

FT_Property_Get proto \
	       library: FT_Library,
	   module_name: ptr FT_String,
	 property_name: ptr FT_String,


FT_Set_Default_Properties proto \
	       library: FT_Library

FT_Reference_Library proto \
	       library: FT_Library

FT_New_Library proto \
		memory: FT_Memory,
	      alibrary: ptr FT_Library

FT_Done_Library proto \
	       library: FT_Library

CALLBACKC(FT_DebugHook_Func, :ptr)

define FT_DEBUG_HOOK_TRUETYPE  0

FT_Set_Debug_Hook proto \
	       library: FT_Library,
	    hook_index: FT_UInt,
	    debug_hook: FT_DebugHook_Func

FT_Add_Default_Modules proto \
	       library: FT_Library

.enum FT_TrueTypeEngineType {
    FT_TRUETYPE_ENGINE_TYPE_NONE = 0,
    FT_TRUETYPE_ENGINE_TYPE_UNPATENTED,
    FT_TRUETYPE_ENGINE_TYPE_PATENTED
    }

FT_Get_TrueType_Engine_Type proto \
	       library: FT_Library

endif
