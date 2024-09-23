include d3dx9.inc
ifndef _D3DX9TEX_H
define _D3DX9TEX_H

D3DX_FILTER_NONE	equ 0x00000001
D3DX_FILTER_POINT	equ 0x00000002
D3DX_FILTER_LINEAR	equ 0x00000003
D3DX_FILTER_TRIANGLE	equ 0x00000004
D3DX_FILTER_BOX		equ 0x00000005
D3DX_FILTER_MIRROR_U	equ 0x00010000
D3DX_FILTER_MIRROR_V	equ 0x00020000
D3DX_FILTER_MIRROR_W	equ 0x00040000
D3DX_FILTER_MIRROR	equ 0x00070000
D3DX_FILTER_DITHER	equ 0x00080000
D3DX_FILTER_DITHER_DIFFUSION equ 0x00100000
D3DX_FILTER_SRGB_IN	equ 0x00200000
D3DX_FILTER_SRGB_OUT	equ 0x00400000
D3DX_FILTER_SRGB	equ 0x00600000

D3DX_SKIP_DDS_MIP_LEVELS_MASK equ 0x1f
D3DX_SKIP_DDS_MIP_LEVELS_SHIFT equ 26
D3DX_SKIP_DDS_MIP_LEVELS macro l, f
    if (f) EQ D3DX_DEFAULT
	exitm<((((l) AND D3DX_SKIP_DDS_MIP_LEVES_MASK) SHL D3DX_SKIP_DDS_MIP_LEVELS_SHIFT) OR D3DX_FILTER_BOX)>
    else
	exitm<((((l) AND D3DX_SKIP_DDS_MIP_LEVES_MASK) SHL D3DX_SKIP_DDS_MIP_LEVELS_SHIFT) OR (f))>
    endif
	endm

D3DX_NORMALMAP_MIRROR_U equ 0x00010000
D3DX_NORMALMAP_MIRROR_V equ 0x00020000
D3DX_NORMALMAP_MIRROR	equ 0x00030000
D3DX_NORMALMAP_INVERTSIGN equ 0x00080000
D3DX_NORMALMAP_COMPUTE_OCCLUSION equ 0x00100000

D3DX_CHANNEL_RED	equ 0x00000001
D3DX_CHANNEL_BLUE	equ 0x00000002
D3DX_CHANNEL_GREEN	equ 0x00000004
D3DX_CHANNEL_ALPHA	equ 0x00000008
D3DX_CHANNEL_LUMINANCE	equ 0x00000010

D3DXIMAGE_FILEFORMAT	typedef SDWORD
D3DXIFF_BMP		equ 0
D3DXIFF_JPG		equ 1
D3DXIFF_TGA		equ 2
D3DXIFF_PNG		equ 3
D3DXIFF_DDS		equ 4
D3DXIFF_PPM		equ 5
D3DXIFF_DIB		equ 6
D3DXIFF_HDR		equ 7
D3DXIFF_PFM		equ 8
D3DXIFF_FORCE_DWORD	equ 0x7fffffff

D3DXIMAGE_INFO		STRUC
Width			UINT ?
Height			UINT ?
Depth			UINT ?
MipLevels		UINT ?
Format			D3DFORMAT ?
ResourceType		D3DRESOURCETYPE ?
ImageFileFormat		D3DXIMAGE_FILEFORMAT ?
D3DXIMAGE_INFO		ENDS

CALLBACK(LPD3DXFILL2D, :ptr, :ptr, :ptr, :ptr)
CALLBACK(LPD3DXFILL3D, :ptr, :ptr, :ptr, :ptr)

D3DXGetImageInfoFromFileA proto WINAPI :LPSTR, :ptr
D3DXGetImageInfoFromFileW proto WINAPI :LPWSTR, :ptr
D3DXGetImageInfoFromResourceA proto WINAPI :HMODULE, :LPSTR, :ptr
D3DXGetImageInfoFromResourceW proto WINAPI :HMODULE, :LPWSTR, :ptr
D3DXGetImageInfoFromFileInMemory proto WINAPI :ptr, :UINT, :ptr
D3DXLoadSurfaceFromFileA proto WINAPI :ptr, :ptr, :ptr, :LPSTR, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadSurfaceFromFileW proto WINAPI :ptr, :ptr, :ptr, :LPWSTR, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadSurfaceFromResourceA proto WINAPI :ptr, :ptr, :ptr, :HMODULE, :LPSTR, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadSurfaceFromResourceW proto WINAPI :ptr, :ptr, :ptr, :HMODULE, :LPWSTR, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadSurfaceFromFileInMemory proto WINAPI :ptr, :ptr, :ptr, :ptr, :UINT, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadSurfaceFromSurface proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :DWORD, :D3DCOLOR
D3DXLoadSurfaceFromMemory proto WINAPI :ptr, :ptr, :ptr, :ptr, :D3DFORMAT, :UINT, :ptr, :ptr, :DWORD, :D3DCOLOR
D3DXSaveSurfaceToFileInMemory proto WINAPI :ptr, :D3DXIMAGE_FILEFORMAT, :ptr, :ptr, :ptr
D3DXSaveSurfaceToFileA proto WINAPI :LPSTR, :D3DXIMAGE_FILEFORMAT, :ptr, :ptr, :ptr
D3DXSaveSurfaceToFileW proto WINAPI :LPWSTR, :D3DXIMAGE_FILEFORMAT, :ptr, :ptr, :ptr
D3DXLoadVolumeFromFileA proto WINAPI :ptr, :ptr, :ptr, :LPSTR, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadVolumeFromFileW proto WINAPI :ptr, :ptr, :ptr, :LPWSTR, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadVolumeFromResourceA proto WINAPI :ptr, :ptr, :ptr, :HMODULE, :LPSTR, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadVolumeFromResourceW proto WINAPI :ptr, :ptr, :ptr, :HMODULE, :LPWSTR, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadVolumeFromFileInMemory proto WINAPI :ptr, :ptr, :ptr, :ptr, :UINT, :ptr, :DWORD, :D3DCOLOR, :ptr
D3DXLoadVolumeFromVolume proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :DWORD, :D3DCOLOR
D3DXLoadVolumeFromMemory proto WINAPI :ptr, :ptr, :ptr, :ptr, :D3DFORMAT, :UINT, :UINT, :ptr, :ptr, :DWORD, :D3DCOLOR
D3DXSaveVolumeToFileA proto WINAPI :LPSTR, :D3DXIMAGE_FILEFORMAT, :ptr, :ptr, :ptr
D3DXSaveVolumeToFileW proto WINAPI :LPWSTR, :D3DXIMAGE_FILEFORMAT, :ptr, :ptr, :ptr
D3DXCheckTextureRequirements proto WINAPI :ptr, :ptr, :ptr, :ptr, :DWORD, :ptr, :D3DPOOL
D3DXCheckCubeTextureRequirements proto WINAPI :ptr, :ptr, :ptr, :DWORD, :ptr, :D3DPOOL
D3DXCheckVolumeTextureRequirements proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :DWORD, :ptr, :D3DPOOL
D3DXCreateTexture proto WINAPI :ptr, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr
D3DXCreateCubeTexture proto WINAPI :ptr, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr
D3DXCreateVolumeTexture proto WINAPI :ptr, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr
D3DXCreateTextureFromFileA proto WINAPI :ptr, :LPSTR, :ptr
D3DXCreateTextureFromFileW proto WINAPI :ptr, :LPWSTR, :ptr
ifdef _UNICODE
D3DXCreateTextureFromFile equ <D3DXCreateTextureFromFileW>
else
D3DXCreateTextureFromFile equ <D3DXCreateTextureFromFileA>
endif

D3DXCreateCubeTextureFromFileA proto WINAPI :ptr, :LPSTR, :ptr
D3DXCreateCubeTextureFromFileW proto WINAPI :ptr, :LPWSTR, :ptr
D3DXCreateVolumeTextureFromFileA proto WINAPI :ptr, :LPSTR, :ptr
D3DXCreateVolumeTextureFromFileW proto WINAPI :ptr, :LPWSTR, :ptr
D3DXCreateTextureFromResourceA proto WINAPI :ptr, :HMODULE, :LPSTR, :ptr
D3DXCreateTextureFromResourceW proto WINAPI :ptr, :HMODULE, :LPWSTR, :ptr
D3DXCreateCubeTextureFromResourceA proto WINAPI :ptr, :HMODULE, :LPSTR, :ptr
D3DXCreateCubeTextureFromResourceW proto WINAPI :ptr, :HMODULE, :LPWSTR, :ptr
D3DXCreateVolumeTextureFromResourceA proto WINAPI :ptr, :HMODULE, :LPSTR, :ptr
D3DXCreateVolumeTextureFromResourceW proto WINAPI :ptr, :HMODULE, :LPWSTR, :ptr
D3DXCreateTextureFromFileExA proto WINAPI :ptr, :LPSTR, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateTextureFromFileExW proto WINAPI :ptr, :LPWSTR, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateCubeTextureFromFileExA proto WINAPI :ptr, :LPSTR, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateCubeTextureFromFileExW proto WINAPI :ptr, :LPWSTR, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateVolumeTextureFromFileExA proto WINAPI :ptr, :LPSTR, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateVolumeTextureFromFileExW proto WINAPI :ptr, :LPWSTR, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateTextureFromResourceExA proto WINAPI :ptr, :HMODULE, :LPSTR, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateTextureFromResourceExW proto WINAPI :ptr, :HMODULE, :LPWSTR, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateCubeTextureFromResourceExA proto WINAPI :ptr, :HMODULE, :LPSTR, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateCubeTextureFromResourceExW proto WINAPI :ptr, :HMODULE, :LPWSTR, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateVolumeTextureFromResourceExA proto WINAPI :ptr, :HMODULE, :LPSTR, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateVolumeTextureFromResourceExW proto WINAPI :ptr, :HMODULE, :LPWSTR, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateTextureFromFileInMemory proto WINAPI :ptr, :ptr, :UINT, :ptr
D3DXCreateCubeTextureFromFileInMemory proto WINAPI :ptr, :ptr, :UINT, :ptr
D3DXCreateVolumeTextureFromFileInMemory proto WINAPI :ptr, :ptr, :UINT, :ptr
D3DXCreateTextureFromFileInMemoryEx proto WINAPI :ptr, :ptr, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateCubeTextureFromFileInMemoryEx proto WINAPI :ptr, :ptr, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXCreateVolumeTextureFromFileInMemoryEx proto WINAPI :ptr, :ptr, :UINT, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :DWORD, :DWORD, :D3DCOLOR, :ptr, :ptr, :ptr
D3DXSaveTextureToFileInMemory proto WINAPI :ptr, :D3DXIMAGE_FILEFORMAT, :ptr, :ptr
D3DXSaveTextureToFileA proto WINAPI :LPSTR, :D3DXIMAGE_FILEFORMAT, :ptr, :ptr
D3DXSaveTextureToFileW proto WINAPI :LPWSTR, :D3DXIMAGE_FILEFORMAT, :ptr, :ptr
D3DXFilterTexture proto WINAPI :ptr, :ptr, :UINT, :DWORD

D3DXFilterCubeTexture	equ <D3DXFilterTexture>
D3DXFilterVolumeTexture equ <D3DXFilterTexture>

D3DXFillTexture proto WINAPI :ptr, :ptr
D3DXFillCubeTexture proto WINAPI :ptr, :ptr
D3DXFillVolumeTexture proto WINAPI :ptr, :ptr
D3DXFillTextureTX proto WINAPI :ptr, :ptr, :ptr, :UINT
D3DXFillCubeTextureTX proto WINAPI :ptr, :ptr, :ptr, :UINT
D3DXFillVolumeTextureTX proto WINAPI :ptr, :ptr, :ptr, :UINT
D3DXComputeNormalMap proto WINAPI :ptr, :ptr, :ptr, :DWORD, :DWORD, :float

endif
