ifndef FREETYPE_CONFIG_INTEGER_TYPES_H_
define FREETYPE_CONFIG_INTEGER_TYPES_H_

ifndef FT_CHAR_BIT
define FT_CHAR_BIT  CHAR_BIT
endif

ifndef FT_SIZEOF_INT
if FT_UINT_MAX EQ 0xFFFF
FT_SIZEOF_INT equ ( 16 / FT_CHAR_BIT )
elseif FT_UINT_MAX EQ 0xFFFFFFFF
FT_SIZEOF_INT equ ( 32 / FT_CHAR_BIT )
elseif FT_UINT_MAX GT 0xFFFFFFFF AND FT_UINT_MAX EQ 0xFFFFFFFFFFFFFFFF
FT_SIZEOF_INT equ ( 64 / FT_CHAR_BIT )
else
.err <"Unsupported size of `int' type!">
endif
endif

ifndef FT_SIZEOF_LONG
if FT_ULONG_MAX EQ 0xFFFFFFFF
FT_SIZEOF_LONG equ ( 32 / FT_CHAR_BIT )
elseif FT_ULONG_MAX GT 0xFFFFFFFF AND FT_ULONG_MAX EQ 0xFFFFFFFFFF
FT_SIZEOF_LONG equ ( 32 / FT_CHAR_BIT )
elseif FT_ULONG_MAX GT 0xFFFFFFFF AND FT_ULONG_MAX EQ 0xFFFFFFFFFFFFFFFF
FT_SIZEOF_LONG equ ( 64 / FT_CHAR_BIT )
else
.err <"Unsupported size of `long' type!">
endif
endif

ifndef FT_SIZEOF_LONG_LONG
if defined( FT_ULLONG_MAX ) AND FT_ULLONG_MAX GE 0xFFFFFFFFFFFFFFFF
FT_SIZEOF_LONG_LONG equ ( 64 / FT_CHAR_BIT )
else
define FT_SIZEOF_LONG_LONG  0
endif
endif
FT_Int16    typedef SWORD
FT_UInt16   typedef DWORD

if 0
FT_Int32    typedef signed XXX
FT_UInt32   typedef unsigned XXX
FT_Int64    typedef signed XXX
FT_UInt64   typedef unsigned XXX
endif

if FT_SIZEOF_INT EQ ( 32 / FT_CHAR_BIT )
FT_Int32    typedef SDWORD
FT_UInt32   typedef DWORD
elseif FT_SIZEOF_LONG EQ ( 32 / FT_CHAR_BIT )
FT_Int32    typedef SDWORD
FT_UInt32   typedef DWORD
else
.err <"no 32bit type found -- please check your configuration files">
endif

if FT_SIZEOF_INT GE ( 32 / FT_CHAR_BIT )
FT_Fast     typedef SDWORD
FT_UFast    typedef DWORD
elseif FT_SIZEOF_LONG GE ( 32 / FT_CHAR_BIT )
FT_Fast     typedef SDWORD
FT_UFast    typedef DWORD
endif

if FT_SIZEOF_LONG EQ ( 64 / FT_CHAR_BIT )
FT_INT64    typedef SDWORD
FT_UINT64   typedef DWORD
elseif FT_SIZEOF_LONG_LONG GE ( 64 / FT_CHAR_BIT )
FT_INT64    typedef SQWORD
FT_UINT64   typedef QWORD
elseif NOT defined( __STDC__ ) OR defined( FT_CONFIG_OPTION_FORCE_INT64 )
if defined( _MSC_VER ) AND _MSC_VER GE 900 ;; Visual C++ (and Intel C++)
FT_INT64    typedef SQWORD
FT_UINT64   typedef QWORD
elseif defined( __BORLANDC__ )  ;; Borland C++
FT_INT64    typedef SQWORD
FT_UINT64   typedef QWORD
elseif defined( __WATCOMC__ ) AND __WATCOMC__ GE 1100  ;; Watcom C++
FT_INT64    typedef SQWORD
FT_UINT64   typedef QWORD
elseif defined( __MWERKS__ )    ;; Metrowerks CodeWarrior
FT_INT64    typedef SQWORD
FT_UINT64   typedef QWORD
elseif defined( __GNUC__ )
FT_INT64    typedef SQWORD
FT_UINT64   typedef QWORD
endif
endif

ifdef FT_INT64
FT_Int64    typedef FT_INT64
FT_UInt64   typedef FT_UINT64
endif

endif
