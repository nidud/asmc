ifndef _THREADS_H
define _THREADS_H
include time.inc

.enum {
    mtx_plain     = 0,
    mtx_recursive = 1 shl 0,
    mtx_timed     = 1 shl 1,
    }

mtx_t   struct
_Type   uintptr_t ?
_Ptr    ptr ?
_Cv     ptr ?
_Owner  uint32_t ?
_Cnt    uint32_t ?
mtx_t   ends

mtx_destroy proto __cdecl :ptr
mtx_init proto __cdecl :ptr, :sdword
mtx_lock proto __cdecl :ptr

_mtx_timedlock32 proto __cdecl :ptr, :ptr
_mtx_timedlock64 proto __cdecl :ptr, :ptr
ifndef _CRT_NO_TIME_T
ifdef _USE_32BIT_TIME_T
mtx_timedlock proto _Mtx:ptr mtx_t, _Ts:ptr timespec {
    _mtx_timedlock32(_Mtx, _Ts)
    }
else
mtx_timedlock proto _Mtx:ptr mtx_t, _Ts:ptr timespec {
    _mtx_timedlock64(_Mtx, _Ts)
    }
endif
endif

mtx_trylock proto __cdecl :ptr
mtx_unlock proto __cdecl :ptr

cnd_t struct
_Ptr  ptr ?
cnd_t ends

cnd_broadcast proto __cdecl :ptr
cnd_destroy proto __cdecl :ptr
cnd_init proto __cdecl :ptr
cnd_signal proto __cdecl :ptr

_cnd_timedwait32 proto __cdecl :ptr, :ptr, :ptr
_cnd_timedwait64 proto __cdecl :ptr, :ptr, :ptr
ifndef _CRT_NO_TIME_T
ifdef _USE_32BIT_TIME_T
cnd_timedwait proto asmcall _Cond:ptr cnd_t, _Mtx:ptr mtx_t, _Ts:ptr timespec {
    _cnd_timedwait32(_Cond, _Mtx, _Ts)
    }
else
cnd_timedwait proto _Cond:ptr cnd_t, _Mtx:ptr mtx_t, _Ts:ptr timespec {
    _cnd_timedwait64(_Cond, _Mtx, _Ts)
    }
endif
endif
cnd_wait proto __cdecl :ptr, :ptr

thrd_t  struct
_Handle ptr ?
_Tid    uint32_t ?
thrd_t  ends

.enum { thrd_success, thrd_nomem, thrd_timedout, thrd_busy, thrd_error }

CALLBACKC(thrd_start_t, :ptr)

thrd_create proto __cdecl :ptr thrd_t, :thrd_start_t, :ptr
thrd_current proto __cdecl
thrd_detach proto __cdecl :ptr thrd_t
thrd_equal proto __cdecl :ptr thrd_t, :ptr thrd_t

thrd_exit proto __cdecl :int_t
thrd_join proto __cdecl :ptr thrd_t, :ptr int_t

_thrd_sleep32 proto __cdecl :ptr _timespec32, :ptr _timespec32
_thrd_sleep64 proto __cdecl :ptr _timespec64, :ptr _timespec64
ifndef _CRT_NO_TIME_T
ifdef _USE_32BIT_TIME_T
thrd_sleep proto asmcall duration:ptr timespec, remaining:ptr timespec {
    _thrd_sleep32(duration, remaining)
    }
else
thrd_sleep proto asmcall duration:ptr timespec, remaining:ptr timespec {
    _thrd_sleep64(duration, remaining)
    }
endif
endif

thrd_yield proto __cdecl

define TSS_DTOR_ITERATIONS 1

tss_t struct
_Idx  uint32_t ?
tss_t ends

CALLBACKC(tss_dtor_t, :ptr)

tss_create proto __cdecl :ptr, :tss_dtor_t
tss_delete proto __cdecl :tss_t
tss_get proto __cdecl :tss_t
tss_set proto __cdecl :tss_t, :ptr

once_flag struct
_Opaque   ptr ?
once_flag ends

call_once proto __cdecl :ptr, :tss_dtor_t

define ONCE_FLAG_INIT <{0}>

endif

