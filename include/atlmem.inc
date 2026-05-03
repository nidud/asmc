ifndef __ATLMEM_H__
define __ATLMEM_H__

include atlcore.inc
include limits.inc

.pragma pack(push,_ATL_PACKING)

AtlAlignUp proto :ptr, :ULONG {
    int 3
}

AtlAlignDown proto :ptr, :ULONG {
    int 3
}

DEFINE_IIDX(IAtlMemMgr, "654F7EF5-CFDF-4df9-A450-6C6A13C622C0")

.comdef IAtlMemMgr

	Allocate	proc :size_t
	Free		proc :ptr
	Reallocate	proc :ptr, :size_t
	GetSize		proc :ptr
	.ENDS

.class CCRTHeap : public IAtlMemMgr

	.ENDS

.class CWin32Heap : public IAtlMemMgr

	m_hHeap HANDLE ?
	m_bOwnHeap BOOL ?

	CWin32Heap	proc
	.ENDS

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

.class CLocalHeap : public IAtlMemMgr

	.ENDS

.class CGlobalHeap : public IAtlMemMgr

	.ENDS
endif

.pragma pack(pop)

ifdef _OBJBASE_H_
include atlcommem.inc
endif

endif
