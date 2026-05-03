
include stdio.inc
include directxmath.inc

.code

main proc

   .new v4_i:XMUINT4  = {   5,   5,   5,   5 }
   .new v4_f:XMFLOAT4 = { 0.5, 0.5, 0.5, 0.5 }
   .new rc_1:float = XMConvertVectorFloatToInt(v4_f, 2)
   .new rc_2:float = XMConvertVectorIntToFloat(v4_i, 1)
   .new rc_3:float = XMVectorSin(v4_f)
   .new rc_4:float = XMVectorTan(v4_f)

    mov eax,rc_1
    printf(
        "XMConvertVectorFloatToInt(): %d\n"
        "XMConvertVectorIntToFloat(): %1f\n"
        "XMVectorSin():               %f\n"
        "XMVectorTan():               %f\n", eax, rc_2, rc_3, rc_4)
    xor eax,eax
    ret
    endp

    end
