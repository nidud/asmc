ifdef  __D3DX10_INTERNAL__
.err <Incorrect D3DX10 header used>
endif

ifndef __D3DX10_H__
define __D3DX10_H__

include limits.inc
include float.inc

D3DX10_DEFAULT		equ (-1)
D3DX10_FROM_FILE	equ (-3)
DXGI_FORMAT_FROM_FILE	equ (-3)

ifndef D3DX10INLINE
ifdef _MSC_VER
if (_MSC_VER GE 1200)
D3DX10INLINE		equ <__forceinline>
else
D3DX10INLINE		equ <__inline>
endif
else
ifdef __cplusplus
D3DX10INLINE		equ <inline>
else
D3DX10INLINE equ 1
endif
endif
endif

include d3d10.inc
include d3dx10.inc
include d3dx10math.inc
include d3dx10core.inc
include d3dx10tex.inc
include d3dx10mesh.inc
include d3dx10async.inc


_FACDD equ 0x876
MAKE_DDHRESULT macro code
	exitm<MAKE_HRESULT( 1, _FACDD, code )>
	endm

.enum D3DX10_ERR {
    D3DX10_ERR_CANNOT_MODIFY_INDEX_BUFFER	= MAKE_DDHRESULT(2900),
    D3DX10_ERR_INVALID_MESH			= MAKE_DDHRESULT(2901),
    D3DX10_ERR_CANNOT_ATTR_SORT			= MAKE_DDHRESULT(2902),
    D3DX10_ERR_SKINNING_NOT_SUPPORTED		= MAKE_DDHRESULT(2903),
    D3DX10_ERR_TOO_MANY_INFLUENCES		= MAKE_DDHRESULT(2904),
    D3DX10_ERR_INVALID_DATA			= MAKE_DDHRESULT(2905),
    D3DX10_ERR_LOADED_MESH_HAS_NO_DATA		= MAKE_DDHRESULT(2906),
    D3DX10_ERR_DUPLICATE_NAMED_FRAGMENT		= MAKE_DDHRESULT(2907),
    D3DX10_ERR_CANNOT_REMOVE_LAST_ITEM		= MAKE_DDHRESULT(2908),
    }


endif

