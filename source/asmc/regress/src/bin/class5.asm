
; v2.31.02 - : public class with empty base error

    .x64
    .model flat, fastcall

.comdef IUnknown
    Release proc
    .ends
.comdef ID3D11DeviceChild : public IUnknown
    GetDevice proc :ptr
    .ends
.comdef ID3D11Resource : public ID3D11DeviceChild
    GetType proc
    .ends
.comdef ID3D11Buffer : public ID3D11Resource
    GetDesc proc :ptr
    .ends
.comdef ID3D11Texture2D : public ID3D11Buffer
    .ends

    .code

    mov al,ID3D11Texture2DVtbl

    .data

    ID3D11Texture2D { ; *this
        {             ; .D3D11Buffer
            {         ; ..ID3D11Resource
                {     ; ...ID3D11DeviceChild
                    { ; ....IUnknown
                        0
                    }
                }
            }
        }
    },{
        {{{{1}}}}
    }

    end
