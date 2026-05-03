ifndef __G_MARSHAL_H__
define __G_MARSHAL_H__

g_cclosure_marshal_VOID__VOID proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__VOIDv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__BOOLEAN proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__BOOLEANv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__CHAR proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__CHARv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__UCHAR proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__UCHARv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__INT proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__INTv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__UINT proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__UINTv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__LONG proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__LONGv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__ULONG proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__ULONGv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__ENUM proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__ENUMv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__FLAGS proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__FLAGSv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__FLOAT proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__FLOATv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__DOUBLE proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__DOUBLEv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__STRING proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__STRINGv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__PARAM proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__PARAMv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__BOXED proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__BOXEDv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__POINTER proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__POINTERv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__OBJECT proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__OBJECTv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__VARIANT proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__VARIANTv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_VOID__UINT_POINTER proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_VOID__UINT_POINTERv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_BOOLEAN__FLAGS proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_BOOLEAN__FLAGSv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

define g_cclosure_marshal_BOOL__FLAGS <q_cclosure_marshal_BOOLEAN__FLAGS>

g_cclosure_marshal_STRING__OBJECT_POINTER proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_STRING__OBJECT_POINTERv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

g_cclosure_marshal_BOOLEAN__BOXED_BOXED proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_BOOLEAN__BOXED_BOXEDv proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

define g_cclosure_marshal_BOOL__BOXED_BOXED <q_cclosure_marshal_BOOLEAN__BOXED_BOXED>

endif
