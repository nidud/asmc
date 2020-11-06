include d3dx11.inc

ifndef __D3DX11TEX_H__
__D3DX11TEX_H__ equ <>

.enum D3DX11_FILTER_FLAG {
    D3DX11_FILTER_NONE		  =   (1 shl 0),
    D3DX11_FILTER_POINT		  =   (2 shl 0),
    D3DX11_FILTER_LINEAR	  =   (3 shl 0),
    D3DX11_FILTER_TRIANGLE	  =   (4 shl 0),
    D3DX11_FILTER_BOX		  =   (5 shl 0),
    D3DX11_FILTER_MIRROR_U	  =   (1 shl 16),
    D3DX11_FILTER_MIRROR_V	  =   (2 shl 16),
    D3DX11_FILTER_MIRROR_W	  =   (4 shl 16),
    D3DX11_FILTER_MIRROR	  =   (7 shl 16),
    D3DX11_FILTER_DITHER	  =   (1 shl 19),
    D3DX11_FILTER_DITHER_DIFFUSION=   (2 shl 19),
    D3DX11_FILTER_SRGB_IN	  =   (1 shl 21),
    D3DX11_FILTER_SRGB_OUT	  =   (2 shl 21),
    D3DX11_FILTER_SRGB		  =   (3 shl 21),
    }

.enum D3DX11_NORMALMAP_FLAG {
    D3DX11_NORMALMAP_MIRROR_U	       =   (1 shl 16),
    D3DX11_NORMALMAP_MIRROR_V	       =   (2 shl 16),
    D3DX11_NORMALMAP_MIRROR	       =   (3 shl 16),
    D3DX11_NORMALMAP_INVERTSIGN	       =   (8 shl 16),
    D3DX11_NORMALMAP_COMPUTE_OCCLUSION =   (16 shl 16),
    }

.enum D3DX11_CHANNEL_FLAG {
    D3DX11_CHANNEL_RED		 =    (1 shl 0),
    D3DX11_CHANNEL_BLUE		 =    (1 shl 1),
    D3DX11_CHANNEL_GREEN	 =    (1 shl 2),
    D3DX11_CHANNEL_ALPHA	 =    (1 shl 3),
    D3DX11_CHANNEL_LUMINANCE	 =    (1 shl 4),
    }

.enum D3DX11_IMAGE_FILE_FORMAT {
    D3DX11_IFF_BMP	   = 0,
    D3DX11_IFF_JPG	   = 1,
    D3DX11_IFF_PNG	   = 3,
    D3DX11_IFF_DDS	   = 4,
    D3DX11_IFF_TIFF	   = 10,
    D3DX11_IFF_GIF	   = 11,
    D3DX11_IFF_WMP	   = 12,
    D3DX11_IFF_FORCE_DWORD = 0x7fffffff
    }

.enum D3DX11_SAVE_TEXTURE_FLAG {
    D3DX11_STF_USEINPUTBLOB	 = 0x0001,
    }

D3DX11_IMAGE_INFO	STRUC
Width			UINT ?
Height			UINT ?
Depth			UINT ?
ArraySize		UINT ?
MipLevels		UINT ?
MiscFlags		UINT ?
Format			DXGI_FORMAT ?
ResourceDimension	D3D11_RESOURCE_DIMENSION ?
ImageFileFormat		D3DX11_IMAGE_FILE_FORMAT ?
D3DX11_IMAGE_INFO	ENDS
LPD3DX11_IMAGE_INFO	typedef ptr D3DX11_IMAGE_INFO

D3DX11_IMAGE_LOAD_INFO	STRUC
Width			UINT ?
Height			UINT ?
Depth			UINT ?
FirstMipLevel		UINT ?
MipLevels		UINT ?
Usage			D3D11_USAGE ?
BindFlags		UINT ?
CpuAccessFlags		UINT ?
MiscFlags		UINT ?
Format			DXGI_FORMAT ?
Filter			UINT ?
MipFilter		UINT ?
pSrcInfo		LPD3DX11_IMAGE_INFO ?
ifdef __cplusplus
endif
D3DX11_IMAGE_LOAD_INFO	ENDS


D3DX11GetImageInfoFromFileA proto WINAPI \
	      pSrcFile: LPCSTR,
		 pPump: ptr ID3DX11ThreadPump,
	      pSrcInfo: ptr D3DX11_IMAGE_INFO,
	      pHResult: ptr HRESULT


D3DX11GetImageInfoFromFileW proto WINAPI \
	      pSrcFile: LPCWSTR,
		 pPump: ptr ID3DX11ThreadPump,
	      pSrcInfo: ptr D3DX11_IMAGE_INFO,
	      pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11GetImageInfoFromFile equ <D3DX11GetImageInfoFromFileW>
else
D3DX11GetImageInfoFromFile equ <D3DX11GetImageInfoFromFileA>
endif

D3DX11GetImageInfoFromResourceA proto WINAPI \
	    hSrcModule: HMODULE,
	  pSrcResource: LPCSTR,
		 pPump: ptr ID3DX11ThreadPump,
	      pSrcInfo: ptr D3DX11_IMAGE_INFO,
	      pHResult: ptr HRESULT

D3DX11GetImageInfoFromResourceW proto WINAPI \
	    hSrcModule: HMODULE,
	  pSrcResource: LPCWSTR,
		 pPump: ptr ID3DX11ThreadPump,
	      pSrcInfo: ptr D3DX11_IMAGE_INFO,
	      pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11GetImageInfoFromResource equ <D3DX11GetImageInfoFromResourceW>
else
D3DX11GetImageInfoFromResource equ <D3DX11GetImageInfoFromResourceA>
endif


D3DX11GetImageInfoFromMemory proto WINAPI \
	      pSrcData: LPCVOID,
	   SrcDataSize: SIZE_T,
		 pPump: ptr ID3DX11ThreadPump,
	      pSrcInfo: ptr D3DX11_IMAGE_INFO,
	      pHResult: ptr HRESULT


D3DX11CreateShaderResourceViewFromFileA proto WINAPI \
	       pDevice: ptr ID3D11Device,
	      pSrcFile: LPCSTR,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
  ppShaderResourceView: ptr ptr ID3D11ShaderResourceView,
	      pHResult: ptr HRESULT

D3DX11CreateShaderResourceViewFromFileW proto WINAPI \
	       pDevice: ptr ID3D11Device,
	      pSrcFile: LPCWSTR,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
  ppShaderResourceView: ptr ptr ID3D11ShaderResourceView,
	      pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11CreateShaderResourceViewFromFile equ <D3DX11CreateShaderResourceViewFromFileW>
else
D3DX11CreateShaderResourceViewFromFile equ <D3DX11CreateShaderResourceViewFromFileA>
endif

D3DX11CreateTextureFromFileA proto WINAPI \
	       pDevice: ptr ID3D11Device,
	      pSrcFile: LPCSTR,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
	     ppTexture: ptr ptr ID3D11Resource,
	      pHResult: ptr HRESULT

D3DX11CreateTextureFromFileW proto WINAPI \
	       pDevice: ptr ID3D11Device,
	      pSrcFile: LPCWSTR,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
	     ppTexture: ptr ptr ID3D11Resource,
	      pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11CreateTextureFromFile equ <D3DX11CreateTextureFromFileW>
else
D3DX11CreateTextureFromFile equ <D3DX11CreateTextureFromFileA>
endif


D3DX11CreateShaderResourceViewFromResourceA proto WINAPI \
	       pDevice: ptr ID3D11Device,
	    hSrcModule: HMODULE,
	  pSrcResource: LPCSTR,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
  ppShaderResourceView: ptr ptr ID3D11ShaderResourceView,
	      pHResult: ptr HRESULT


D3DX11CreateShaderResourceViewFromResourceW proto WINAPI \
	       pDevice: ptr ID3D11Device,
	    hSrcModule: HMODULE,
	  pSrcResource: LPCWSTR,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
  ppShaderResourceView: ptr ptr ID3D11ShaderResourceView,
	      pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11CreateShaderResourceViewFromResource equ <D3DX11CreateShaderResourceViewFromResourceW>
else
D3DX11CreateShaderResourceViewFromResource equ <D3DX11CreateShaderResourceViewFromResourceA>
endif

D3DX11CreateTextureFromResourceA proto WINAPI \
	       pDevice: ptr ID3D11Device,
	    hSrcModule: HMODULE,
	  pSrcResource: LPCSTR,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
	     ppTexture: ptr ptr ID3D11Resource,
	      pHResult: ptr HRESULT

D3DX11CreateTextureFromResourceW proto WINAPI \
	       pDevice: ptr ID3D11Device,
	    hSrcModule: HMODULE,
	  pSrcResource: LPCWSTR,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
	     ppTexture: ptr ptr ID3D11Resource,
	      pHResult: ptr HRESULT


ifdef _UNICODE
D3DX11CreateTextureFromResource equ <D3DX11CreateTextureFromResourceW>
else
D3DX11CreateTextureFromResource equ <D3DX11CreateTextureFromResourceA>
endif


D3DX11CreateShaderResourceViewFromMemory proto WINAPI \
	       pDevice: ptr ID3D11Device,
	      pSrcData: LPCVOID,
	   SrcDataSize: SIZE_T,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
  ppShaderResourceView: ptr ptr ID3D11ShaderResourceView,
	      pHResult: ptr HRESULT


D3DX11CreateTextureFromMemory proto WINAPI \
	       pDevice: ptr ID3D11Device,
	      pSrcData: LPCVOID,
	   SrcDataSize: SIZE_T,
	     pLoadInfo: ptr D3DX11_IMAGE_LOAD_INFO,
		 pPump: ptr ID3DX11ThreadPump,
	     ppTexture: ptr ptr ID3D11Resource,
	      pHResult: ptr HRESULT

LPD3D11_BOX		typedef ptr D3D11_BOX
D3DX11_TEXTURE_LOAD_INFO STRUC
pSrcBox			LPD3D11_BOX ?
pDstBox			LPD3D11_BOX ?
SrcFirstMip		UINT ?
DstFirstMip		UINT ?
NumMips			UINT ?
SrcFirstElement		UINT ?
DstFirstElement		UINT ?
NumElements		UINT ?
Filter			UINT ?
MipFilter		UINT ?
ifdef __cplusplus
endif
D3DX11_TEXTURE_LOAD_INFO ENDS

D3DX11LoadTextureFromTexture proto WINAPI \
	      pContext: ptr ID3D11DeviceContext,
	   pSrcTexture: ptr ID3D11Resource,
	     pLoadInfo: ptr D3DX11_TEXTURE_LOAD_INFO,
	   pDstTexture: ptr ID3D11Resource


D3DX11FilterTexture proto WINAPI \
	      pContext: ptr ID3D11DeviceContext,
	      pTexture: ptr ID3D11Resource,
	      SrcLevel: UINT,
	     MipFilter: UINT

D3DX11SaveTextureToFileA proto WINAPI \
	      pContext: ptr ID3D11DeviceContext,
	   pSrcTexture: ptr ID3D11Resource,
	    DestFormat: D3DX11_IMAGE_FILE_FORMAT,
	     pDestFile: LPCSTR

D3DX11SaveTextureToFileW proto WINAPI \
	      pContext: ptr ID3D11DeviceContext,
	   pSrcTexture: ptr ID3D11Resource,
	    DestFormat: D3DX11_IMAGE_FILE_FORMAT,
	     pDestFile: LPCWSTR

ifdef _UNICODE
D3DX11SaveTextureToFile equ <D3DX11SaveTextureToFileW>
else
D3DX11SaveTextureToFile equ <D3DX11SaveTextureToFileA>
endif

D3DX11SaveTextureToMemory proto WINAPI \
	      pContext: ptr ID3D11DeviceContext,
	   pSrcTexture: ptr ID3D11Resource,
	    DestFormat: D3DX11_IMAGE_FILE_FORMAT,
	     ppDestBuf: ptr ptr ID3D10Blob,
		 Flags: UINT


D3DX11ComputeNormalMap proto WINAPI \
	      pContext: ptr ID3D11DeviceContext,
	   pSrcTexture: ptr ID3D11Texture2D,
		 Flags: UINT,
	       Channel: UINT,
	     Amplitude: FLOAT,
	  pDestTexture: ptr ID3D11Texture2D


D3DX11SHProjectCubeMap proto WINAPI \
	      pContext: ptr ID3D11DeviceContext,
		 Order: UINT,
	      pCubeMap: ptr ID3D11Texture2D,
		 pROut: ptr FLOAT,
		 pGOut: ptr FLOAT,
		      : ptr FLOAT

endif

