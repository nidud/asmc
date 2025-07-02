ifndef __D3DX11ASYNC_H__
define __D3DX11ASYNC_H__

include d3dx11.inc

D3DX11CompileFromFileA proto WINAPI :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
D3DX11CompileFromFileW proto WINAPI :LPCWSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX11CompileFromFile   equ <D3DX11CompileFromFileW>
else
D3DX11CompileFromFile   equ <D3DX11CompileFromFileA>
endif

D3DX11CompileFromResourceA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
D3DX11CompileFromResourceW proto WINAPI :HMODULE, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX11CompileFromResource equ <D3DX11CompileFromResourceW>
else
D3DX11CompileFromResource equ <D3DX11CompileFromResourceA>
endif

D3DX11CompileFromMemory proto WINAPI :LPCSTR, :size_t, :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
D3DX11PreprocessShaderFromFileA proto WINAPI :LPCSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX11PreprocessShaderFromFileW proto WINAPI :LPCWSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX11PreprocessShaderFromMemory proto WINAPI :LPCSTR, :size_t, :LPCSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX11PreprocessShaderFromResourceA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX11PreprocessShaderFromResourceW proto WINAPI :HMODULE, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX11PreprocessShaderFromFile equ <D3DX11PreprocessShaderFromFileW>
D3DX11PreprocessShaderFromResource equ <D3DX11PreprocessShaderFromResourceW>
else
D3DX11PreprocessShaderFromFile equ <D3DX11PreprocessShaderFromFileA>
D3DX11PreprocessShaderFromResource equ <D3DX11PreprocessShaderFromResourceA>
endif

D3DX11CreateAsyncCompilerProcessor proto WINAPI :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr
D3DX11CreateAsyncShaderPreprocessProcessor proto WINAPI :LPCSTR, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX11CreateAsyncFileLoaderW proto WINAPI :LPCWSTR, :ptr
D3DX11CreateAsyncFileLoaderA proto WINAPI :LPCSTR, :ptr
D3DX11CreateAsyncMemoryLoader proto WINAPI :ptr, :size_t, :ptr
D3DX11CreateAsyncResourceLoaderW proto WINAPI :HMODULE, :LPCWSTR, :ptr
D3DX11CreateAsyncResourceLoaderA proto WINAPI :HMODULE, :LPCSTR, :ptr
ifdef _UNICODE
D3DX11CreateAsyncFileLoader equ <D3DX11CreateAsyncFileLoaderW>
D3DX11CreateAsyncResourceLoader equ <D3DX11CreateAsyncResourceLoaderW>
else
D3DX11CreateAsyncFileLoader equ <D3DX11CreateAsyncFileLoaderA>
D3DX11CreateAsyncResourceLoader equ <D3DX11CreateAsyncResourceLoaderA>
endif
D3DX11CreateAsyncTextureProcessor proto WINAPI :ptr, :ptr, :ptr
D3DX11CreateAsyncTextureInfoProcessor proto WINAPI :ptr, :ptr
D3DX11CreateAsyncShaderResourceViewProcessor proto WINAPI :ptr, :ptr, :ptr

endif
