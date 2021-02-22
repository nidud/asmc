
extern "C" { void *MemCopy( void *, void *, int ); }

int main(void)
{
    char src[512];
    char des[512];

    MemCopy( des, src, 127 );

    return 0;
}
