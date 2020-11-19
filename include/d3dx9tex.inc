include d3dx9.inc
ifndef _D3DX9TEX_H
_D3DX9TEX_H equ <>

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

;; Typedefs for callback functions

CALLBACK(LPD3DXFILL2D, :ptr D3DXVECTOR4, :ptr D3DXVECTOR2, :ptr D3DXVECTOR2, :PVOID)
CALLBACK(LPD3DXFILL3D, :ptr D3DXVECTOR4, :ptr D3DXVECTOR3, :ptr D3DXVECTOR3, :PVOID)

;; Image Information
;HRESULT
D3DXGetImageInfoFromFileA proto WINAPI \
		  file: LPSTR,
		  info: ptr D3DXIMAGE_INFO

;HRESULT
D3DXGetImageInfoFromFileW proto WINAPI \
		  file: LPWSTR,
		  info: ptr D3DXIMAGE_INFO

;HRESULT
D3DXGetImageInfoFromResourceA proto WINAPI \
		module: HMODULE,
	      resource: LPSTR,
		  info: ptr D3DXIMAGE_INFO

;HRESULT
D3DXGetImageInfoFromResourceW proto WINAPI \
		module: HMODULE,
	      resource: LPWSTR,
		  info: ptr D3DXIMAGE_INFO

;HRESULT
D3DXGetImageInfoFromFileInMemory proto WINAPI \
		 _data: PVOID,
	     data_size: UINT,
		  info: ptr D3DXIMAGE_INFO

;; Surface Loading/Saving
;HRESULT
D3DXLoadSurfaceFromFileA proto WINAPI \
	   destsurface: ptr IDirect3DSurface9,
	   destpalette: ptr PALETTEENTRY,
	      destrect: ptr RECT,
	       srcfile: LPSTR,
	       srcrect: ptr RECT,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadSurfaceFromFileW proto WINAPI \
	   destsurface: ptr IDirect3DSurface9,
	   destpalette: ptr PALETTEENTRY,
	      destrect: ptr RECT,
	       srcfile: LPWSTR,
	       srcrect: ptr RECT,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadSurfaceFromResourceA proto WINAPI \
	   destsurface: ptr IDirect3DSurface9,
	   destpalette: ptr PALETTEENTRY,
	      destrect: ptr RECT,
	     srcmodule: HMODULE,
	      resource: LPSTR,
	       srcrect: ptr RECT,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadSurfaceFromResourceW proto WINAPI \
	   destsurface: ptr IDirect3DSurface9,
	   destpalette: ptr PALETTEENTRY,
	      destrect: ptr RECT,
	     srcmodule: HMODULE,
	      resource: LPWSTR,
	       srcrect: ptr RECT,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadSurfaceFromFileInMemory proto WINAPI \
	   destsurface: ptr IDirect3DSurface9,
	   destpalette: ptr PALETTEENTRY,
	      destrect: ptr RECT,
	       srcdata: PVOID,
	   srcdatasize: UINT,
	       srcrect: ptr RECT,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadSurfaceFromSurface proto WINAPI \
	   destsurface: ptr IDirect3DSurface9,
	   destpalette: ptr PALETTEENTRY,
	      destrect: ptr RECT,
	    srcsurface: ptr IDirect3DSurface9,
	    srcpalette: ptr PALETTEENTRY,
	       srcrect: ptr RECT,
		filter: DWORD,
	      colorkey: D3DCOLOR

;HRESULT
D3DXLoadSurfaceFromMemory proto WINAPI \
	   dst_surface: ptr IDirect3DSurface9,
	   dst_palette: ptr PALETTEENTRY,
	      dst_rect: ptr RECT,
	    src_memory: PVOID,
	    src_format: D3DFORMAT,
	     src_pitch: UINT,
	   src_palette: ptr PALETTEENTRY,
	      src_rect: ptr RECT,
		filter: DWORD,
	     color_key: D3DCOLOR

;HRESULT
D3DXSaveSurfaceToFileInMemory proto WINAPI \
	    destbuffer: ptr ID3DXBuffer,
	    destformat: D3DXIMAGE_FILEFORMAT,
	    srcsurface: ptr IDirect3DSurface9,
	    srcpalette: ptr PALETTEENTRY,
	       srcrect: ptr RECT


;HRESULT
D3DXSaveSurfaceToFileA proto WINAPI \
	      destfile: LPSTR,
	    destformat: D3DXIMAGE_FILEFORMAT,
	    srcsurface: ptr IDirect3DSurface9,
	    srcpalette: ptr PALETTEENTRY,
	       srcrect: ptr RECT

;HRESULT
D3DXSaveSurfaceToFileW proto WINAPI \
	      destfile: LPWSTR,
	    destformat: D3DXIMAGE_FILEFORMAT,
	    srcsurface: ptr IDirect3DSurface9,
	    srcpalette: ptr PALETTEENTRY,
	       srcrect: ptr RECT


;; Volume Loading/Saving
;HRESULT
D3DXLoadVolumeFromFileA proto WINAPI \
	    destvolume: ptr IDirect3DVolume9,
	   destpalette: ptr PALETTEENTRY,
	       destbox: ptr D3DBOX,
	       srcfile: LPSTR,
		srcbox: ptr D3DBOX,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadVolumeFromFileW proto WINAPI \
	    destvolume: ptr IDirect3DVolume9,
	   destpalette: ptr PALETTEENTRY,
	       destbox: ptr D3DBOX,
	       srcfile: LPWSTR,
		srcbox: ptr D3DBOX,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadVolumeFromResourceA proto WINAPI \
	    destvolume: ptr IDirect3DVolume9,
	   destpalette: ptr PALETTEENTRY,
	       destbox: ptr D3DBOX,
	     srcmodule: HMODULE,
	      resource: LPSTR,
		srcbox: ptr D3DBOX,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadVolumeFromResourceW proto WINAPI \
	    destvolume: ptr IDirect3DVolume9,
	   destpalette: ptr PALETTEENTRY,
	       destbox: ptr D3DBOX,
	     srcmodule: HMODULE,
	      resource: LPWSTR,
		srcbox: ptr D3DBOX,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO

;HRESULT
D3DXLoadVolumeFromFileInMemory proto WINAPI \
	    destvolume: ptr IDirect3DVolume9,
	   destpalette: ptr PALETTEENTRY,
	       destbox: ptr D3DBOX,
	       srcdata: PVOID,
	   srcdatasize: UINT,
		srcbox: ptr D3DBOX,
		filter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO


;HRESULT
D3DXLoadVolumeFromVolume proto WINAPI \
	    destvolume: ptr IDirect3DVolume9,
	   destpalette: ptr PALETTEENTRY,
	       destbox: ptr D3DBOX,
	     srcvolume: ptr IDirect3DVolume9,
	    srcpalette: ptr PALETTEENTRY,
		srcbox: ptr D3DBOX,
		filter: DWORD,
	      colorkey: D3DCOLOR


;HRESULT
D3DXLoadVolumeFromMemory proto WINAPI \
	    destvolume: ptr IDirect3DVolume9,
	   destpalette: ptr PALETTEENTRY,
	       destbox: ptr D3DBOX,
	     srcmemory: PVOID,
	     srcformat: D3DFORMAT,
	   srcrowpitch: UINT,
	 srcslicepitch: UINT,
	    srcpalette: ptr PALETTEENTRY,
		srcbox: ptr D3DBOX,
		filter: DWORD,
	      colorkey: D3DCOLOR


;HRESULT
D3DXSaveVolumeToFileA proto WINAPI \
	      destfile: LPSTR,
	    destformat: D3DXIMAGE_FILEFORMAT,
	     srcvolume: ptr IDirect3DVolume9,
	    srcpalette: ptr PALETTEENTRY,
		srcbox: ptr D3DBOX

;HRESULT
D3DXSaveVolumeToFileW proto WINAPI \
	      destfile: LPWSTR,
	    destformat: D3DXIMAGE_FILEFORMAT,
	     srcvolume: ptr IDirect3DVolume9,
	    srcpalette: ptr PALETTEENTRY,
		srcbox: ptr D3DBOX


;; Texture, cube texture and volume texture creation
;HRESULT
D3DXCheckTextureRequirements proto WINAPI \
		device: ptr IDirect3DDevice9,
		 width: ptr UINT,
		height: ptr UINT,
	     miplevels: ptr UINT,
		 usage: DWORD,
		format: ptr D3DFORMAT,
		  pool: D3DPOOL

;HRESULT
D3DXCheckCubeTextureRequirements proto WINAPI \
		device: ptr IDirect3DDevice9,
		  size: ptr UINT,
	     miplevels: ptr UINT,
		 usage: DWORD,
		format: ptr D3DFORMAT,
		  pool: D3DPOOL

;HRESULT
D3DXCheckVolumeTextureRequirements proto WINAPI \
		device: ptr IDirect3DDevice9,
		 width: ptr UINT,
		height: ptr UINT,
		 depth: ptr UINT,
	     miplevels: ptr UINT,
		 usage: DWORD,
		format: ptr D3DFORMAT,
		  pool: D3DPOOL

;HRESULT
D3DXCreateTexture proto WINAPI \
		device: ptr IDirect3DDevice9,
		 width: UINT,
		height: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
	       texture: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateCubeTexture proto WINAPI \
		device: ptr IDirect3DDevice9,
		  size: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateVolumeTexture proto WINAPI \
		device: ptr IDirect3DDevice9,
		 width: UINT,
		height: UINT,
		 depth: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		volume: ptr IDirect3DVolumeTexture9


;HRESULT
D3DXCreateTextureFromFileA proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPSTR,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateTextureFromFileW proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPWSTR,
	       texture: ptr IDirect3DTexture9
ifdef _UNICODE
D3DXCreateTextureFromFile equ <D3DXCreateTextureFromFileW>
else
D3DXCreateTextureFromFile equ <D3DXCreateTextureFromFileA>
endif

;HRESULT
D3DXCreateCubeTextureFromFileA proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPSTR,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateCubeTextureFromFileW proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPWSTR,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateVolumeTextureFromFileA proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPSTR,
		volume: ptr IDirect3DVolumeTexture9

;HRESULT
D3DXCreateVolumeTextureFromFileW proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPWSTR,
		volume: ptr IDirect3DVolumeTexture9

;HRESULT
D3DXCreateTextureFromResourceA proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPSTR,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateTextureFromResourceW proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPWSTR,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateCubeTextureFromResourceA proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPSTR,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateCubeTextureFromResourceW proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPWSTR,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateVolumeTextureFromResourceA proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPSTR,
		volume: ptr IDirect3DVolumeTexture9

;HRESULT
D3DXCreateVolumeTextureFromResourceW proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPWSTR,
		volume: ptr IDirect3DVolumeTexture9

;HRESULT
D3DXCreateTextureFromFileExA proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPSTR,
		 width: UINT,
		height: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateTextureFromFileExW proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPWSTR,
		 width: UINT,
		height: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateCubeTextureFromFileExA proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPSTR,
		  size: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateCubeTextureFromFileExW proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPWSTR,
		  size: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateVolumeTextureFromFileExA proto WINAPI \
		device: ptr IDirect3DDevice9,
	      resource: LPSTR,
		 width: UINT,
		height: UINT,
		 depth: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		volume: ptr IDirect3DVolumeTexture9

;HRESULT
D3DXCreateVolumeTextureFromFileExW proto WINAPI \
		device: ptr IDirect3DDevice9,
	      resource: LPWSTR,
		 width: UINT,
		height: UINT,
		 depth: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		volume: ptr IDirect3DVolumeTexture9

;HRESULT
D3DXCreateTextureFromResourceExA proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPSTR,
		 width: UINT,
		height: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateTextureFromResourceExW proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPWSTR,
		 width: UINT,
		height: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateCubeTextureFromResourceExA proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPSTR,
		  size: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateCubeTextureFromResourceExW proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPWSTR,
		  size: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateVolumeTextureFromResourceExA proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPSTR,
		 width: UINT,
		height: UINT,
		 depth: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		volume: ptr IDirect3DVolumeTexture9

;HRESULT
D3DXCreateVolumeTextureFromResourceExW proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	      resource: LPWSTR,
		 width: UINT,
		height: UINT,
		 depth: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		volume: ptr IDirect3DVolumeTexture9

;HRESULT
D3DXCreateTextureFromFileInMemory proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcdata: PVOID,
	   srcdatasize: UINT,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateCubeTextureFromFileInMemory proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcdata: PVOID,
	   srcdatasize: UINT,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateVolumeTextureFromFileInMemory proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcdata: PVOID,
	   srcdatasize: UINT,
		volume: ptr IDirect3DVolumeTexture9


;HRESULT
D3DXCreateTextureFromFileInMemoryEx proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcdata: PVOID,
	   srcdatasize: UINT,
		 width: UINT,
		height: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
	       texture: ptr IDirect3DTexture9

;HRESULT
D3DXCreateCubeTextureFromFileInMemoryEx proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcdata: PVOID,
	   srcdatasize: UINT,
		  size: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		  cube: ptr IDirect3DCubeTexture9

;HRESULT
D3DXCreateVolumeTextureFromFileInMemoryEx proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcdata: PVOID,
	   srcdatasize: UINT,
		 width: UINT,
		height: UINT,
		 depth: UINT,
	     miplevels: UINT,
		 usage: DWORD,
		format: D3DFORMAT,
		  pool: D3DPOOL,
		filter: DWORD,
	     mipfilter: DWORD,
	      colorkey: D3DCOLOR,
	       srcinfo: ptr D3DXIMAGE_INFO,
	       palette: ptr PALETTEENTRY,
		volume: ptr IDirect3DVolumeTexture9


;HRESULT
D3DXSaveTextureToFileInMemory proto WINAPI \
		device: ptr IDirect3DDevice9,
	    destformat: D3DXIMAGE_FILEFORMAT,
	    srctexture: ptr IDirect3DBaseTexture9,
	    srcpalette: ptr PALETTEENTRY

;HRESULT
D3DXSaveTextureToFileA proto WINAPI \
	      destfile: LPSTR,
	    destformat: D3DXIMAGE_FILEFORMAT,
	    srctexture: ptr IDirect3DBaseTexture9,
	    srcpalette: ptr PALETTEENTRY

;HRESULT
D3DXSaveTextureToFileW proto WINAPI \
	      destfile: LPWSTR,
	    destformat: D3DXIMAGE_FILEFORMAT,
	    srctexture: ptr IDirect3DBaseTexture9,
	    srcpalette: ptr PALETTEENTRY

;; Other functions
;HRESULT
D3DXFilterTexture proto WINAPI \
	       texture: ptr IDirect3DBaseTexture9,
	       palette: ptr PALETTEENTRY,
	      srclevel: UINT,
		filter: DWORD

D3DXFilterCubeTexture	equ <D3DXFilterTexture>
D3DXFilterVolumeTexture equ <D3DXFilterTexture>

;HRESULT
D3DXFillTexture proto WINAPI \
	       texture: ptr IDirect3DTexture9,
	      function: LPD3DXFILL2D

;HRESULT
D3DXFillCubeTexture proto WINAPI \
		  cube: ptr IDirect3DCubeTexture9,
	      function: LPD3DXFILL3D

;HRESULT
D3DXFillVolumeTexture proto WINAPI \
		volume: ptr IDirect3DVolumeTexture9,
	      function: LPD3DXFILL3D


;HRESULT
D3DXFillTextureTX proto WINAPI \
	       texture: ptr IDirect3DTexture9,
	      function: ptr DWORD,
	     constants: ptr D3DXVECTOR4,
	  numconstants: UINT

;HRESULT
D3DXFillCubeTextureTX proto WINAPI \
		  cube: ptr IDirect3DCubeTexture9,
	      function: ptr DWORD,
	     constants: ptr D3DXVECTOR4,
	  numconstants: UINT

;HRESULT
D3DXFillVolumeTextureTX proto WINAPI \
		volume: ptr IDirect3DVolumeTexture9,
	      function: ptr DWORD,
	     constants: ptr D3DXVECTOR4,
	  numconstants: UINT


;HRESULT
D3DXComputeNormalMap proto WINAPI \
	       texture: ptr IDirect3DTexture9,
	    srctexture: ptr IDirect3DTexture9,
	    srcpalette: ptr IDirect3DVolumeTexture9,
		 flags: DWORD,
	       channel: DWORD,
	     amplitude: float

endif
