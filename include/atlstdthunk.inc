ifndef __ATLSTDTHUNK_H__
__ATLSTDTHUNK_H__ equ <>

include atldef.inc

ifndef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
.err <This file is not compatible with the current WINAPI_FAMILY>
endif


ifdef _M_IX86

__AllocStdCallThunk proto stdcall
__FreeStdCallThunk  proto stdcall :ptr

.pragma pack(push,1)

.template _stdcallthunk watcall

    m_mov	dd ?
    m_this	dd ?
    m_jmp	db ?
    m_relproc	dd ?

    .operator Init :ptr, :ptr {

	push ebx
	mov ebx,this
	mov [ebx]._stdcallthunk.m_mov,0x042444C7
	mov [ebx]._stdcallthunk.m_this,_2
	mov [ebx]._stdcallthunk.m_jmp,0xe9
	add this,sizeof(_stdcallthunk)
	sub _1,this
	mov [ebx]._stdcallthunk.m_relproc,_1
	FlushInstructionCache(GetCurrentProcess(), ebx, sizeof(_stdcallthunk))
	pop ebx
	mov eax,TRUE
	}

    .operator GetCodeAddress {
	mov eax,this
	}
    .operator new :size_t {
	__AllocStdCallThunk()
	}
    .operator delete :ptr {
	__FreeStdCallThunk(_1)
	}
    .ENDS

.pragma pack(pop)

elseifdef _M_IA64

.pragma pack(push,8)

_StdCallThunkProcProc proto

_FuncDesc	struct
pfn		PVOID ?
gp		PVOID ?
_FuncDesc	ends

.template _stdcallthunk

    m_funcdesc	_FuncDesc <>
    m_pFunc	PVOID ?
    m_pThis	PVOID ?

    .operator Init :ptr, :ptr {
       .new This:ptr
	mov This,this
	lea rax,_StdCallThunkProcProc
	mov rax,[rax]._FuncDesc.pfn
	mov [this]._stdcallthunk.m_funcdesc.pfn,rax
	lea rax,&[this]._stdcallthunk.m_pFunc
	mov [this]._stdcallthunk.m_funcdesc.gp,rax
	mov [this]._stdcallthunk.m_pFunc,_1
	mov [this]._stdcallthunk.m_pThis,_2
	FlushInstructionCache( GetCurrentProcess(), This, sizeof( _stdcallthunk ) )
	mov eax,TRUE
	}
    .operator GetCodeAddress {
	mov rax,this
	}
    .ENDS

.pragma pack(pop)

else
.err <Only IA64 and X86 supported>
endif


if defined(_M_IX86) or defined (_M_AMD64) or defined(_M_ARM)

.pragma pack(push,8)

LPSTDCALLTHUNK typedef ptr _stdcallthunk

.template CDynamicStdCallThunk

    pThunk LPSTDCALLTHUNK ?

    .operator CDynamicStdCallThunk {
	mov [this].CDynamicStdCallThunk.pThunk,NULL
	}

    .operator Init :ptr, :ptr {

	mov eax,[this].CDynamicStdCallThunk.pThunk
	.if eax
	    [eax]._stdcallthunk.Init(_1, _2)
	.endif
	}

    .operator GetCodeAddress {
	mov rax,[this].CDynamicStdCallThunk.pThunk
	[eax]._stdcallthunk.GetCodeAddress()
	}
    .ENDS

.pragma pack(pop)
CStdCallThunk typedef CDynamicStdCallThunk
else
CStdCallThunk typedef _stdcallthunk
endif

endif
