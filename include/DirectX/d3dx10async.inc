ifndef __D3DX10ASYNC_H__
define __D3DX10ASYNC_H__

include d3dx10.inc

D3DX10CompileFromFileA proto WINAPI :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
D3DX10CompileFromFileW proto WINAPI :LPCWSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10CompileFromFile   equ <D3DX10CompileFromFileW>
else
D3DX10CompileFromFile   equ <D3DX10CompileFromFileA>
endif

D3DX10CompileFromResourceA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
D3DX10CompileFromResourceW proto WINAPI :HMODULE, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10CompileFromResource equ <D3DX10CompileFromResourceW>
else
D3DX10CompileFromResource equ <D3DX10CompileFromResourceA>
endif

D3DX10CompileFromMemory proto WINAPI :LPCSTR, :size_t, :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectFromFileA proto WINAPI :LPCSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectFromFileW proto WINAPI :LPCWSTR, :ptr, :ptr, :LPCSTR,:UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectFromMemory proto WINAPI :ptr, :size_t, :LPCSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectFromResourceA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectFromResourceW proto WINAPI :HMODULE, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

ifdef _UNICODE
D3DX10CreateEffectFromFile equ <D3DX10CreateEffectFromFileW>
D3DX10CreateEffectFromResource equ <D3DX10CreateEffectFromResourceW>
else
D3DX10CreateEffectFromFile equ <D3DX10CreateEffectFromFileA>
D3DX10CreateEffectFromResource equ <D3DX10CreateEffectFromResourceA>
endif

D3DX10CreateEffectPoolFromFileA proto WINAPI :LPCSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectPoolFromFileW proto WINAPI :LPCWSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectPoolFromMemory proto WINAPI :ptr, :size_t, :LPCSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectPoolFromResourceA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateEffectPoolFromResourceW proto WINAPI :HMODULE, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10CreateEffectPoolFromFile equ <D3DX10CreateEffectPoolFromFileW>
D3DX10CreateEffectPoolFromResource equ <D3DX10CreateEffectPoolFromResourceW>
else
D3DX10CreateEffectPoolFromFile equ <D3DX10CreateEffectPoolFromFileA>
D3DX10CreateEffectPoolFromResource equ <D3DX10CreateEffectPoolFromResourceA>
endif

D3DX10PreprocessShaderFromFileA proto WINAPI :LPCSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10PreprocessShaderFromFileW proto WINAPI :LPCWSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10PreprocessShaderFromMemory proto WINAPI :LPCSTR, :size_t, :LPCSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10PreprocessShaderFromResourceA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10PreprocessShaderFromResourceW proto WINAPI :HMODULE, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

ifdef _UNICODE
D3DX10PreprocessShaderFromFile equ <D3DX10PreprocessShaderFromFileW>
D3DX10PreprocessShaderFromResource equ <D3DX10PreprocessShaderFromResourceW>
else
D3DX10PreprocessShaderFromFile equ <D3DX10PreprocessShaderFromFileA>
D3DX10PreprocessShaderFromResource equ <D3DX10PreprocessShaderFromResourceA>
endif

D3DX10CreateAsyncCompilerProcessor proto WINAPI :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr
D3DX10CreateAsyncEffectCreateProcessor proto WINAPI :LPCSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
D3DX10CreateAsyncEffectPoolCreateProcessor proto WINAPI :LPCSTR, :ptr, :ptr, :LPCSTR, :UINT, :UINT, :ptr, :ptr, :ptr
D3DX10CreateAsyncShaderPreprocessProcessor proto WINAPI :LPCSTR, :ptr, :ptr, :ptr, :ptr, :ptr
D3DX10CreateAsyncFileLoaderW proto WINAPI :LPCWSTR, :ptr
D3DX10CreateAsyncFileLoaderA proto WINAPI :LPCSTR, :ptr
D3DX10CreateAsyncMemoryLoader proto WINAPI :ptr, :size_t, :ptr
D3DX10CreateAsyncResourceLoaderW proto WINAPI :HMODULE, :LPCWSTR, :ptr
D3DX10CreateAsyncResourceLoaderA proto WINAPI :HMODULE, :LPCSTR, :ptr

ifdef _UNICODE
D3DX10CreateAsyncFileLoader equ <D3DX10CreateAsyncFileLoaderW>
D3DX10CreateAsyncResourceLoader equ <D3DX10CreateAsyncResourceLoaderW>
else
D3DX10CreateAsyncFileLoader equ <D3DX10CreateAsyncFileLoaderA>
D3DX10CreateAsyncResourceLoader equ <D3DX10CreateAsyncResourceLoaderA>
endif

D3DX10CreateAsyncTextureProcessor proto WINAPI :ptr, :ptr, :ptr
D3DX10CreateAsyncTextureInfoProcessor proto WINAPI :ptr, :ptr
D3DX10CreateAsyncShaderResourceViewProcessor proto WINAPI :ptr, :ptr, :ptr

endif
