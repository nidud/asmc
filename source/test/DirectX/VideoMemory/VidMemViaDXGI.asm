;;----------------------------------------------------------------------------
;; File: VidMemViaDXGI.asm
;;
;; DXGI is only available on Windows Vista or later. This method returns the
;; amount of dedicated video memory, the amount of dedicated system memory,
;; and the amount of shared system memory. DXGI is more reflective of the true
;; system configuration than the previous 4 methods.
;;
;;-----------------------------------------------------------------------------
WIN32_LEAN_AND_MEAN equ 1
include windows.inc
include string.inc
include stdio.inc
include assert.inc
include dxgi.inc

;;-----------------------------------------------------------------------------
;; Defines, and constants
;;-----------------------------------------------------------------------------
ifndef SAFE_RELEASE
SAFE_RELEASE proto p:abs {
    .if p
        p.Release()
        mov p,NULL
    .endif
    }
endif

CALLBACK(LPCREATEDXGIFACTORY, :REFIID, :ptr ptr)

ifdef __CV8__
.data
IID_IDXGIFactory GUID {0x7b7166ec,0x21c7,0x44ae,{0xb2,0x1a,0xc9,0xae,0x32,0x1a,0xe3,0x69}}
endif
.code

GetVideoMemoryViaDXGI proc  hMonitor:HMONITOR,
                            pDedicatedVideoMemory:ptr SIZE_T,
                            pDedicatedSystemMemory:ptr SIZE_T,
                            pSharedSystemMemory:ptr SIZE_T

    .new hr:HRESULT
    .new bGotMemory:BOOL = FALSE

    xor eax,eax
    mov [rdx],rax
    mov [r8],rax
    mov [r9],rax

    .new hDXGI:HINSTANCE = LoadLibrary( "dxgi.dll" )
    .if( rax )

        .new pCreateDXGIFactory:LPCREATEDXGIFACTORY = NULL
        .new pDXGIFactory:ptr IDXGIFactory = NULL

        mov pCreateDXGIFactory,GetProcAddress( hDXGI, "CreateDXGIFactory" )
        pCreateDXGIFactory( &IID_IDXGIFactory, &pDXGIFactory )

        .new index:int_t
        .for( index = 0: : ++index )

           .new bFoundMatchingAdapter:BOOL = FALSE
           .new pAdapter:ptr IDXGIAdapter = NULL
            mov hr,pDXGIFactory.EnumAdapters( index, &pAdapter )
            .break .if (FAILED(hr)) ;; DXGIERR_NOT_FOUND is expected when the end of the list is hit

            .new iOutput:int_t
            .for( iOutput = 0: : ++iOutput )

               .new pOutput:ptr IDXGIOutput = NULL
                mov hr,pAdapter.EnumOutputs( iOutput, &pOutput )
                .break .if (FAILED(hr)) ;; DXGIERR_NOT_FOUND is expected when the end of the list is hit

                mov rax,pOutput
               .new outputDesc:DXGI_OUTPUT_DESC
                ZeroMemory( &outputDesc, DXGI_OUTPUT_DESC )

                pOutput.GetDesc( &outputDesc )
                .if( SUCCEEDED( eax ) )

                    .if( hMonitor == outputDesc._Monitor )
                        mov bFoundMatchingAdapter,TRUE
                    .endif

                .endif
                SAFE_RELEASE( pOutput )
            .endf

            .if( bFoundMatchingAdapter )

                .new desc:DXGI_ADAPTER_DESC
                ZeroMemory( &desc, sizeof( DXGI_ADAPTER_DESC ) )
                pAdapter.GetDesc( &desc )
                .if( SUCCEEDED( eax ) )

                    mov bGotMemory,TRUE
                    mov rcx,pDedicatedVideoMemory
                    mov [rcx],desc.DedicatedVideoMemory
                    mov rcx,pDedicatedSystemMemory
                    mov [rcx],desc.DedicatedSystemMemory
                    mov rcx,pSharedSystemMemory
                    mov [rcx],desc.SharedSystemMemory
                .endif
                .break
            .endif
        .endf
        FreeLibrary( hDXGI )
    .endif
    xor eax,eax
    mov ecx,E_FAIL
    cmp eax,bGotMemory
    cmove eax,ecx
    ret

GetVideoMemoryViaDXGI endp

    end
