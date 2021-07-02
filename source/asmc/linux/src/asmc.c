#include <malloc.h>
#include <signal.h>
#include <globals.h>
#include <input.h>

#if defined(__UNIX__) //|| defined(__CYGWIN__)
#define WILDCARDS 0
#define CATCHBREAK 0
#else
#define WILDCARDS 1
#ifdef __POCC__
#define CATCHBREAK 0
#else
#define CATCHBREAK 1
#endif
#endif
#if WILDCARDS
 #ifdef __UNIX__
  #include <unistd.h>
 #else
  #include <io.h>
 #endif
#endif

void CmdlineFini( void );
char *ParseCmdline( char **, int * );
void define_name( char *, char * );

char *strfcat( char *buffer, const char *path, const char *file )
{
    char *p = buffer;

    if ( path ) {
	while( *path )
	    *p++ = *path++;
	*p++ = '\0';
    } else {
	while( *p ) p++;
    }
    if ( p != buffer && *(p-1) != '/' && *(p-1) != '\\' )
#ifdef __UNIX__
	*p++ = '/';
#else
	*p++ = '\\';
#endif
    do {
	*p++ = *file;
    } while ( *file++ );
    return buffer;
}

static int AssembleSubdir( char *directory, char *wild )
{
    int rc;
#if defined( __UNIX__ )
    rc = AssembleModule( Options.names[ASM] );
#else
    char path[_MAX_PATH];
    intptr_t h;
    struct _finddata_t ff;

    rc = 0;
    if ( (h = _findfirst( strfcat( path, directory, wild ), &ff )) != -1 ) {
	do {
	    if ( !( ff.attrib & _A_SUBDIR ) )
		rc = AssembleModule( strfcat( path, directory, ff.name ) );
	} while ( _findnext( h, &ff ) != -1 );
	_findclose( h );
    }

    if ( Options.process_subdir ) {

	if ( ( h = _findfirst( strfcat( path, directory, "*.*" ), &ff ) ) != -1 ) {
	    do {
		if ( ( ff.attrib & _A_SUBDIR ) &&
		    !( ff.name[0] == '.' && ff.name[1] == 0 ) &&
		    !( ff.name[0] == '.' && ff.name[1] == '.' && ff.name[2] == 0 ) ) {
			if ( AssembleSubdir( strfcat( path, directory, ff.name ), wild ) ) {
			    rc = 1;
			}
		}
	    } while ( _findnext( h, &ff ) != -1 );
	    _findclose( h );
	}
    }
#endif
    return rc;
}

#if 0
typedef struct {
 void  *ExceptionRecord;
 void  *ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;
extern EXCEPTION_POINTERS *pCurrentException;
#endif

void PrintContext(void *, void *);

static void GeneralFailure( int signo )
{
#if CATCHBREAK
    if ( signo != SIGBREAK ) {
#else
    if ( signo != SIGTERM ) {
#endif

	//PrintContext( pCurrentException->ContextRecord, pCurrentException->ExceptionRecord );
	asmerr( 1901 );
    }
}

int main( int argc, char **argv )
{
    int rc = 0;
    int numArgs = 0;
    int numFiles = 0;
    char *p;
#if WILDCARDS
   /* v2.11: _findfirst/next/close() handle, should be of type intptr_t.
    * since this type isn't necessarily defined, type long is used as substitute.
    */
    struct _finddata_t ff;
    size_t h;
    char name[_MAX_PATH];
#endif
    p = getenv( "ASMC" );
    if ( p == NULL )
	p = "";
    argv[0] = p;

#ifndef DEBUG
    signal(SIGSEGV, GeneralFailure);
#endif
#if CATCHBREAK
    signal(SIGBREAK, GeneralFailure);
#else
    signal(SIGTERM, GeneralFailure);
#endif
#ifdef __ASMC64__
    define_name( "_WIN64", "1" );
#endif

    while ( ParseCmdline( argv, &numArgs ) ) {

	numFiles++;
	write_logo();
#if WILDCARDS

	if ( Options.process_subdir == 0 ) {

	    if ( (h = _findfirst( Options.names[ASM], &ff )) == -1 ) {
		asmerr( 1000, Options.names[ASM] );
		break;
	    }
	    _findclose( h );
	}

	if ( (p = strchr( strcpy( name, Options.names[ASM] ), '*' )) == NULL )
	    p = strchr( name, '?' );

	if ( p ) {
	    if ( (p = GetFNamePart( name )) > name )
		p--;
	    *p = 0;
	    rc = AssembleSubdir( name, GetFNamePart( Options.names[ASM] ) );
	} else {
	    rc = AssembleModule( Options.names[ASM] );
	}
#else
	    rc = AssembleModule( Options.names[ASM] );
#endif
	}

	CmdlineFini();
	if ( numArgs == 0 ) {
	    write_usage();
	} else if ( numFiles == 0 ) {
	    asmerr( 1017 );
	}
	return ( 1 - rc );
}
