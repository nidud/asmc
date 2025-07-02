include d3dx10.inc

ifndef __D3DX10TEX_H__
define __D3DX10TEX_H__

.enum D3DX10_FILTER_FLAG {
    D3DX10_FILTER_NONE		  =   (1 shl 0),
    D3DX10_FILTER_POINT		  =   (2 shl 0),
    D3DX10_FILTER_LINEAR	  =   (3 shl 0),
    D3DX10_FILTER_TRIANGLE	  =   (4 shl 0),
    D3DX10_FILTER_BOX		  =   (5 shl 0),
    D3DX10_FILTER_MIRROR_U	  =   (1 shl 16),
    D3DX10_FILTER_MIRROR_V	  =   (2 shl 16),
    D3DX10_FILTER_MIRROR_W	  =   (4 shl 16),
    D3DX10_FILTER_MIRROR	  =   (7 shl 16),
    D3DX10_FILTER_DITHER	  =   (1 shl 19),
    D3DX10_FILTER_DITHER_DIFFUSION=   (2 shl 19),
    D3DX10_FILTER_SRGB_IN	  =   (1 shl 21),
    D3DX10_FILTER_SRGB_OUT	  =   (2 shl 21),
    D3DX10_FILTER_SRGB		  =   (3 shl 21),
    }

.enum D3DX10_NORMALMAP_FLAG {
    D3DX10_NORMALMAP_MIRROR_U	       =   (1 shl 16),
    D3DX10_NORMALMAP_MIRROR_V	       =   (2 shl 16),
    D3DX10_NORMALMAP_MIRROR	       =   (3 shl 16),
    D3DX10_NORMALMAP_INVERTSIGN	       =   (8 shl 16),
    D3DX10_NORMALMAP_COMPUTE_OCCLUSION =   (16 shl 16),
    }

.enum D3DX10_CHANNEL_FLAG {
    D3DX10_CHANNEL_RED		 =    (1 shl 0),
    D3DX10_CHANNEL_BLUE		 =    (1 shl 1),
    D3DX10_CHANNEL_GREEN	 =    (1 shl 2),
    D3DX10_CHANNEL_ALPHA	 =    (1 shl 3),
    D3DX10_CHANNEL_LUMINANCE	 =    (1 shl 4),
    }

.enum D3DX10_IMAGE_FILE_FORMAT {
    D3DX10_IFF_BMP	   = 0,
    D3DX10_IFF_JPG	   = 1,
    D3DX10_IFF_PNG	   = 3,
    D3DX10_IFF_DDS	   = 4,
    D3DX10_IFF_TIFF		  = 10,
    D3DX10_IFF_GIF		  = 11,
    D3DX10_IFF_WMP		  = 12,
    D3DX10_IFF_FORCE_DWORD = 0x7fffffff
    }

.enum D3DX10_SAVE_TEXTURE_FLAG {
    D3DX10_STF_USEINPUTBLOB	 = 0x0001,
    }

D3DX10_IMAGE_INFO	STRUC
Width			UINT ?
Height			UINT ?
Depth			UINT ?
ArraySize		UINT ?
MipLevels		UINT ?
MiscFlags		UINT ?
Format			DXGI_FORMAT ?
ResourceDimension	D3D10_RESOURCE_DIMENSION ?
ImageFileFormat		D3DX10_IMAGE_FILE_FORMAT ?
D3DX10_IMAGE_INFO	ENDS
LPD3DX10_IMAGE_INFO	typedef ptr D3DX10_IMAGE_INFO

D3DX10_IMAGE_LOAD_INFO	STRUC
Width			UINT ?
Height			UINT ?
Depth			UINT ?
FirstMipLevel		UINT ?
MipLevels		UINT ?
Usage			D3D10_USAGE ?
BindFlags		UINT ?
CpuAccessFlags		UINT ?
MiscFlags		UINT ?
Format			DXGI_FORMAT ?
Filter			UINT ?
MipFilter		UINT ?
pSrcInfo		LPD3DX10_IMAGE_INFO ?
D3DX10_IMAGE_LOAD_INFO	ENDS

D3DX10GetImageInfoFromFileA proto WINAPI :LPCSTR, :ptr, :ptr, :ptr
D3DX10GetImageInfoFromFileW proto WINAPI :LPCWSTR, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10GetImageInfoFromFile equ <D3DX10GetImageInfoFromFileW>
else
D3DX10GetImageInfoFromFile equ <D3DX10GetImageInfoFromFileA>
endif

D3DX10GetImageInfoFromResourceA proto WINAPI :HMODULE, :LPCSTR, :ptr, :ptr, :ptr
D3DX10GetImageInfoFromResourceW proto WINAPI :HMODULE, :LPCWSTR, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10GetImageInfoFromResource equ <D3DX10GetImageInfoFromResourceW>
else
D3DX10GetImageInfoFromResource equ <D3DX10GetImageInfoFromResourceA>
endif
D3DX10GetImageInfoFromMemory proto WINAPI :ptr, :size_t, :ptr, :ptr, :ptr
D3DX10CreateShaderResourceViewFromFileA proto WINAPI :ptr, :LPCSTR, :ptr, :ptr, :ptr, :ptr
D3DX10CreateShaderResourceViewFromFileW proto WINAPI :ptr, :LPCWSTR, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10CreateShaderResourceViewFromFile equ <D3DX10CreateShaderResourceViewFromFileW>
else
D3DX10CreateShaderResourceViewFromFile equ <D3DX10CreateShaderResourceViewFromFileA>
endif

D3DX10CreateTextureFromFileA proto WINAPI :ptr, :LPCSTR, :ptr, :ptr, :ptr, :ptr
D3DX10CreateTextureFromFileW proto WINAPI :ptr, :LPCWSTR, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10CreateTextureFromFile equ <D3DX10CreateTextureFromFileW>
else
D3DX10CreateTextureFromFile equ <D3DX10CreateTextureFromFileA>
endif

D3DX10CreateShaderResourceViewFromResourceA proto WINAPI :ptr, :HMODULE, :LPCSTR, :ptr, :ptr, :ptr, :ptr
D3DX10CreateShaderResourceViewFromResourceW proto WINAPI :ptr, :HMODULE, :LPCWSTR, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10CreateShaderResourceViewFromResource equ <D3DX10CreateShaderResourceViewFromResourceW>
else
D3DX10CreateShaderResourceViewFromResource equ <D3DX10CreateShaderResourceViewFromResourceA>
endif

D3DX10CreateTextureFromResourceA proto WINAPI :ptr, :HMODULE, :LPCSTR, :ptr, :ptr, :ptr, :ptr
D3DX10CreateTextureFromResourceW proto WINAPI :ptr, :HMODULE, :LPCWSTR, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10CreateTextureFromResource equ <D3DX10CreateTextureFromResourceW>
else
D3DX10CreateTextureFromResource equ <D3DX10CreateTextureFromResourceA>
endif

D3DX10CreateShaderResourceViewFromMemory proto WINAPI :ptr, :ptr, :size_t, :ptr, :ptr, :ptr, :ptr
D3DX10CreateTextureFromMemory proto WINAPI :ptr, :ptr, :size_t, :ptr, :ptr, :ptr, :ptr

LPD3D10_BOX		typedef ptr D3D10_BOX
D3DX10_TEXTURE_LOAD_INFO STRUC
pSrcBox			LPD3D10_BOX ?
pDstBox			LPD3D10_BOX ?
SrcFirstMip		UINT ?
DstFirstMip		UINT ?
NumMips			UINT ?
SrcFirstElement		UINT ?
DstFirstElement		UINT ?
NumElements		UINT ?
Filter			UINT ?
MipFilter		UINT ?
D3DX10_TEXTURE_LOAD_INFO ENDS

D3DX10LoadTextureFromTexture proto WINAPI :ptr, :ptr, :ptr
D3DX10FilterTexture proto WINAPI :ptr, :UINT, :UINT
D3DX10SaveTextureToFileA proto WINAPI :ptr, :D3DX10_IMAGE_FILE_FORMAT, :LPCSTR
D3DX10SaveTextureToFileW proto WINAPI :ptr, :D3DX10_IMAGE_FILE_FORMAT, :LPCWSTR
ifdef _UNICODE
D3DX10SaveTextureToFile equ <D3DX10SaveTextureToFileW>
else
D3DX10SaveTextureToFile equ <D3DX10SaveTextureToFileA>
endif

D3DX10SaveTextureToMemory proto WINAPI :ptr, :D3DX10_IMAGE_FILE_FORMAT, :ptr, :UINT
D3DX10ComputeNormalMap proto WINAPI :ptr, :UINT, :UINT, :FLOAT, :ptr
D3DX10SHProjectCubeMap proto WINAPI :UINT, :ptr, :ptr, :ptr, :ptr

endif
