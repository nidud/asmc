#include <stdio.h>

void __vectorcall XMScalarSinCos(float* pSin, float* pCos, float  Value);

int main(void)
{

  float pSin, pCos, Value;
  double Sin, Cos;

    Value = 0.5f;

    XMScalarSinCos(&pSin, &pCos, Value);

    Sin = (double)pSin;
    Cos = (double)pCos;

    printf("Sin: %f\nCos: %f\n", Sin, Cos);

    return 0;
}
