ifndef __ATLSIMPSTR_H__
define __ATLSIMPSTR_H__

include atldef.inc
include atlcore.inc
include atlexcept.inc
include atlmem.inc

include intrin.inc

.pragma pack(push,_ATL_PACKING)

.class IAtlStringMgr

	Allocate	proc :int_t, :int_t
	Free		proc :ptr CStringData
	Reallocate	proc :ptr CStringData, :int_t, :int_t
	GetNilString	proc
	Clone		proc
	.ENDS


.template CStringData

	pStringMgr	LPIATLSTRINGMGR ?
	nDataLength	int_t ?
	nAllocLength	int_t ?
	nRefs		LONG ?
	_data		TCHAR ?

	.inline _data {
		lea rax,[this+CStringData]
		}
	.inline AddRef {
		.assert(nRefs > 0)
		_InterlockedIncrement(&[this].CStringData.nRefs)
		}
	.inline IsLocked {
		xor	eax,eax
		cmp	[this].CStringData.nRefs,0
		setl	al
		}
	.inline IsShared {
		xor	eax,eax
		cmp	[this].CStringData.nRefs,1
		setg	al
		}
	.inline _Lock {
		dec [this].CStringData.nRefs
		.if( [this].CStringData.nRefs == 0 )
			mov [this].CStringData.nRefs,-1
		.endif
		}
	.inline Release {
		.ifs ( _InterlockedDecrement( &[this].CStringData.nRefs ) <= 0 )
			[this].CStringData.pStringMgr.Free( this )
		.endif
		}
	.inline Unlock {
		.if([this].CStringData.IsLocked())
			inc [this].CStringData.nRefs
			.if( [this].CStringData.nRefs == 0 )
				mov [this].CStringData.nRefs,1
			.endif
		.endif
		}
	.ENDS


.class CNilStringData : public CStringData

	achNil wchar_t 2 dup(?)

	.inline CNilStringData {
		mov [this].CNilStringData.pStringMgr,NULL
		mov [this].CNilStringData.nRefs,2
		mov [this].CNilStringData.nDataLength,0
		mov [this].CNilStringData.nAllocLength,0
		mov [this].CNilStringData.achNil[0],0
		mov [this].CNilStringData.achNil[1],0
		}
	.inline SetManager :ptr IAtlStringMgr {
		mov [this].CNilStringData.pStringMgr,_1
		}
	.ENDS


.template CStaticString

	m_psz PTCHAR ?

	.inline CStaticString :ptr TCHAR {
		mov [this].CStaticString.m_psz,_1
		}
	.inline BaseType {
		mov rax,this
		}
	.ENDS

.pragma pack(pop)

endif
