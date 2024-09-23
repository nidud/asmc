include d3dx9.inc
ifndef __D3DX9SHAPE_H__
define __D3DX9SHAPE_H__

D3DXCreateBox proto WINAPI :ptr, :float, :float, :float, :ptr, :ptr
D3DXCreateCylinder proto WINAPI :ptr, :float, :float, :float, :UINT, :UINT, :ptr, :ptr
D3DXCreatePolygon proto WINAPI :ptr, :float, :UINT, :ptr, :ptr
D3DXCreateSphere proto WINAPI :ptr, :float, :UINT, :UINT, :ptr, :ptr
D3DXCreateTeapot proto WINAPI :ptr, :ptr, :ptr
D3DXCreateTextA proto WINAPI :ptr, :HDC, :LPSTR, :float, :float, :ptr, :ptr, :ptr
D3DXCreateTextW proto WINAPI :ptr, :HDC, :LPWSTR, :float, :FLOAT, :ptr, :ptr, :ptr
D3DXCreateTorus proto WINAPI :ptr, :float, :float, :UINT, :UINT, :ptr, :ptr

endif
