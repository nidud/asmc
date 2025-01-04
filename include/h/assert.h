#undef	assert
#ifdef	NDEBUG
#define assert(exp)	((void)0)
#else
#ifdef	__cplusplus
extern "C" {
#endif
_CRTIMP void __cdecl _assert(void *, void *, unsigned);
#ifdef	__cplusplus
}
#endif
#define assert(exp) (void)( (exp) || (_assert(#exp, __FILE__, __LINE__), 0) )
#endif
