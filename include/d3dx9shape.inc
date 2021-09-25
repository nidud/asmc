include d3dx9.inc
ifndef __D3DX9SHAPE_H__
define __D3DX9SHAPE_H__

;HRESULT
D3DXCreateBox proto WINAPI \
                device: ptr IDirect3DDevice9,
                 width: float,
                height: float,
                 depth: float,
                  mesh: ptr ID3DXMesh,
             adjacency: ptr ID3DXBuffer

;HRESULT
D3DXCreateCylinder proto WINAPI \
                device: ptr IDirect3DDevice9,
               radius1: float,
               radius2: float,
                length: float,
                slices: UINT,
                stacks: UINT,
                  mesh: ptr ID3DXMesh,
             adjacency: ptr ID3DXBuffer

;HRESULT
D3DXCreatePolygon proto WINAPI \
                device: ptr IDirect3DDevice9,
                length: float,
                 sides: UINT,
                  mesh: ptr ID3DXMesh,
             adjacency: ptr ID3DXBuffer

;HRESULT
D3DXCreateSphere proto WINAPI \
                device: ptr IDirect3DDevice9,
                radius: float,
                slices: UINT,
                stacks: UINT,
                  mesh: ptr ID3DXMesh,
             adjacency: ptr ID3DXBuffer

;HRESULT
D3DXCreateTeapot proto WINAPI \
                device: ptr IDirect3DDevice9,
                  mesh: ptr ID3DXMesh,
             adjacency: ptr ID3DXBuffer

;HRESULT
D3DXCreateTextA proto WINAPI \
                device: ptr IDirect3DDevice9,
                   hdc: HDC,
                  text: LPSTR,
             deviation: float,
             extrusion: float,
                  mesh: ptr ID3DXMesh,
             adjacency: ptr ID3DXBuffer,
          glyphmetrics: ptr GLYPHMETRICSFLOAT

;HRESULT
D3DXCreateTextW proto WINAPI \
                device: ptr IDirect3DDevice9,
                   hdc: HDC,
                  text: LPWSTR,
             deviation: float,
             extrusion: FLOAT,
                  mesh: ptr ID3DXMesh,
             adjacency: ptr ID3DXBuffer,
          glyphmetrics: ptr GLYPHMETRICSFLOAT

;HRESULT
D3DXCreateTorus proto WINAPI \
                device: ptr IDirect3DDevice9,
           innerradius: float,
           outerradius: float,
                 sides: UINT,
                 rings: UINT,
                  mesh: ptr ID3DXMesh,
             adjacency: ptr ID3DXBuffer

endif
