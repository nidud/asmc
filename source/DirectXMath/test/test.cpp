#include <stdio.h>
#include <DirectXMath.h>

void main()
{

    float Sin, Cos;

    DirectX::XMVECTOR C1, C2;
    DirectX::XMVECTORF32 R, R2;
    DirectX::XMVECTORF32 V = {{{ 0.5, 1.0, 3.0, 4.0 }}};
    DirectX::XMVECTORF32 V2 = {{{ 5.0, 6.0, 7.0, 8.0 }}};

    DirectX::XMScalarSinCos(&Sin, &Cos, 0.5f);
    printf("XMScalarSinCos:\t\t%f, %f\n", Sin, Cos);
    DirectX::XMVectorSinCosEst(&C1, &C2, V);
    _mm_castsi128_ps(R) = C1;
    _mm_castsi128_ps(R2) = C2;

    printf("XMVectorSinCosEst:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    printf("XMVectorSinCosEst:\t%f, %f, %f, %f\n", R2.f[0], R2.f[1], R2.f[2], R2.f[3]);
    R.v = DirectX::XMVectorModAngles( V );
    printf("XMVectorModAngles:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);

    R.v = DirectX::XMVectorLog( V );
    printf("XMVectorLog:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorSin( V );
    printf("XMVectorSin:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorSinH( V );
    printf("XMVectorSinH:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorCos( V );
    printf("XMVectorCos:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorCosH( V );
    printf("XMVectorCosH:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorExp( V );
    printf("XMVectorExp:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorTan( V );
    printf("XMVectorTan:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorTanH( V );
    printf("XMVectorTanH:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorASin( V );
    printf("XMVectorASin:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorACos( V );
    printf("XMVectorACos:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorATan( V );
    printf("XMVectorATan:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorATan2( V, V );
    printf("XMVectorATan2:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorSinEst( V );
    printf("XMVectorSinEst:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorCosEst( V );
    printf("XMVectorCosEst:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVectorTanEst( V );
    printf("XMVectorTanEst:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVector3Normalize( V );
    printf("XMVector3Normalize:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVector3Cross( V, V2 );
    printf("XMVector3Cross:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);
    R.v = DirectX::XMVector3Dot( V, V2 );
    printf("XMVector3Dot:\t%f, %f, %f, %f\n", R.f[0], R.f[1], R.f[2], R.f[3]);

}

