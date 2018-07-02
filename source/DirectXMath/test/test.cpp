#include <stdio.h>
#include <DirectXMath.h>

void main()
{

    float Sin, Cos;

    DirectX::XMVECTORF32 R;
    DirectX::XMVECTORF32 V = {{{ 1.0, 2.0, 3.0, 4.0 }}};

    DirectX::XMScalarSinCos(&Sin, &Cos, 0.5f);
    printf("XMScalarSinCos:\t%f, %f\n", Sin, Cos);

    R.v = DirectX::XMVectorLog( V );
    printf("XMVectorLog:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorSin( V );
    printf("XMVectorSin:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorCos( V );
    printf("XMVectorCos:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorTan( V );
    printf("XMVectorTan:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);

}

