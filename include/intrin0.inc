ifndef __INTRIN0_H_
__INTRIN0_H_ equ <>

__MACHINEZ macro X:vararg
	exitm<>
	endm
__MACHINE macro X:vararg
	exitm<>;&X>
	endm
__MACHINEWVMPURE macro X:vararg
	exitm<__MACHINEZ(&X)>
	endm

if NOT defined(_M_IX86) OR defined(_CHPE_ONLY_)
__MACHINEX86		equ <__MACHINEZ>
else
__MACHINEX86		equ <__MACHINE>
endif
ifndef _M_X64
__MACHINEX64		equ <__MACHINEZ>
else
__MACHINEX64		equ <__MACHINE>
endif
if NOT (defined(_M_IX86) OR defined(_M_X64)) OR defined(_CHPE_ONLY_)
__MACHINEX86_X64	equ <__MACHINEZ>
else
__MACHINEX86_X64	equ <__MACHINE>
endif

__MACHINE(_InterlockedAnd proto :ptr sdword, :sdword)
__MACHINE(_InterlockedAnd16 proto :ptr sword, :sword)
__MACHINE(_InterlockedAnd8 proto :ptr sbyte, :sbyte)
__MACHINE(_InterlockedCompareExchange proto :ptr sdword, :sdword, :sdword)
__MACHINE(_InterlockedCompareExchange16 proto :ptr sword, :sword, :sword)
__MACHINE(_InterlockedCompareExchange64 proto :ptr sqword, :sqword, :sqword)
__MACHINE(_InterlockedCompareExchange8 proto :ptr sbyte, :sbyte, :sbyte)
__MACHINE(_InterlockedDecrement proto :ptr sdword)
__MACHINE(_InterlockedExchange proto :ptr sdword, :sdword)
__MACHINE(_InterlockedExchange16 proto :ptr sword, :sword)
__MACHINE(_InterlockedExchange8 proto :ptr sbyte, :sbyte)
__MACHINE(_InterlockedExchangeAdd proto :ptr sdword, :sdword)
__MACHINE(_InterlockedExchangeAdd16 proto :ptr sword, :sword)
__MACHINE(_InterlockedExchangeAdd8 proto :ptr sbyte, :sbyte)
__MACHINE(_InterlockedIncrement proto :ptr sdword)
__MACHINE(_InterlockedOr proto :ptr sdword, :sdword)
__MACHINE(_InterlockedOr16 proto :ptr sword, :sword)
__MACHINE(_InterlockedOr8 proto :ptr sbyte, :sbyte)
__MACHINE(_InterlockedXor proto :ptr sdword, :sdword)
__MACHINE(_InterlockedXor16 proto :ptr sword, :sword)
__MACHINE(_InterlockedXor8 proto :ptr sbyte, :sbyte)
__MACHINE(_ReadWriteBarrier proto)
__MACHINE(_interlockedbittestandset proto :ptr, :sdword)

endif
