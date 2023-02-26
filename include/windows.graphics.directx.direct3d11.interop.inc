include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

include inspectable.inc
include dxgi.inc

CreateDirect3D11DeviceFromDXGIDevice proto WINAPI :ptr, :ptr ptr
CreateDirect3D11SurfaceFromDXGISurface proto WINAPI :ptr, :ptr ptr

endif

