ifndef FREETYPE_CONFIG_PUBLIC_MACROS_H_
define FREETYPE_CONFIG_PUBLIC_MACROS_H_

ifndef FT_BEGIN_HEADER
ifdef __cplusplus
define FT_BEGIN_HEADER	<extern "C" {>
else
define FT_BEGIN_HEADER	<>
endif
endif

ifndef FT_END_HEADER
ifdef __cplusplus
define FT_END_HEADER  <}>
else
define FT_END_HEADER  <>
endif
endif

FT_BEGIN_HEADER

ifdef _WIN32
if defined( FT2_BUILD_LIBRARY ) AND defined( DLL_EXPORT )
FT_PUBLIC_FUNCTION_ATTRIBUTE equ <__declspec( dllexport )>
elseif defined( DLL_IMPORT )
FT_PUBLIC_FUNCTION_ATTRIBUTE equ <__declspec( dllimport )>
endif
elseif ( defined( __GNUC__ ) AND __GNUC__ GE 4 ) OR defined( __clang__ )
define FT_PUBLIC_FUNCTION_ATTRIBUTE <__attribute__((visibility( "default" ) ))>
elseif defined( __SUNPRO_C ) AND __SUNPRO_C GE 0x550
define FT_PUBLIC_FUNCTION_ATTRIBUTE  <__global>
endif

ifndef FT_PUBLIC_FUNCTION_ATTRIBUTE
define FT_PUBLIC_FUNCTION_ATTRIBUTE  <>
endif

FT_EXPORT macro x
	exitm<FT_PUBLIC_FUNCTION_ATTRIBUTE extern x>
	endm

ifndef FT_UNUSED
FT_UNUSED macro arg
	exitm<( (arg) = (arg) )>
	endm
endif

FT_STATIC_CAST macro type, var
	exitm<(var)>
	endm
FT_REINTERPRET_CAST macro type, var
	exitm<(var)>
	endm
FT_STATIC_BYTE_CAST macro type, var
	exitm<(var)>
	endm

FT_END_HEADER

endif
