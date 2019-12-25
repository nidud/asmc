ifndef __G_MARSHAL_H__
__G_MARSHAL_H__ equ <>

g_cclosure_marshal_VOID__VOID proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__VOIDv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__BOOLEAN proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__BOOLEANv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__CHAR proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__CHARv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__UCHAR proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__UCHARv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__INT proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__INTv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__UINT proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__UINTv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__LONG proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__LONGv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__ULONG proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__ULONGv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__ENUM proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__ENUMv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__FLAGS proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__FLAGSv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__FLOAT proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__FLOATv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__DOUBLE proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__DOUBLEv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__STRING proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__STRINGv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__PARAM proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__PARAMv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__BOXED proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__BOXEDv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__POINTER proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__POINTERv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__OBJECT proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__OBJECTv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__VARIANT proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__VARIANTv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_VOID__UINT_POINTER proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_VOID__UINT_POINTERv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_BOOLEAN__FLAGS proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_BOOLEAN__FLAGSv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_BOOL__FLAGS equ <g_cclosure_marshal_BOOLEAN__FLAGS>

g_cclosure_marshal_STRING__OBJECT_POINTER proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_STRING__OBJECT_POINTERv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_BOOLEAN__BOXED_BOXED proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
        n_param_values: guint,
          param_values: ptr GValue,
       invocation_hint: gpointer,
          marshal_data: gpointer

g_cclosure_marshal_BOOLEAN__BOXED_BOXEDv proto __cdecl \
               closure: ptr GClosure,
          return_value: ptr GValue,
              instance: gpointer,
                  args: va_list,
          marshal_data: gpointer,
              n_params: int_t,
           param_types: ptr GType

g_cclosure_marshal_BOOL__BOXED_BOXED equ <g_cclosure_marshal_BOOLEAN__BOXED_BOXED>

endif
