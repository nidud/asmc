

  1. About JWlink

  JWlink is a linker for x86 that can create 16-, 32- and 64-bit binaries.
  It's a modified Open Watcom Wlink. Some features have been added and a
  few bugs have been fixed. Generally, it has been made more compatible with
  the MS linker (the cmdline syntax is still quite different).
 
  Besides JWlink's source code there are also precompiled binaries available
  for Windows, DOS and Linux. The packages containing precompiled binaries
  also include a Manual (in HtmlHelp format for Windows, else in plain Html).


  2. Installation

  There's no installation procedure for JWlink. If JWlink is to be used
  frequently, it might be a good idea to copy the binary to a directory that
  is included in the PATH environment variable.
 
  Besides JWlink there are 2 additional binaries;
 
    JWlib[.exe]: this tool is launched by JWlink when it has to create an
     import library. It's an improved version of OW's WLib. 
    cvpack[.exe]: this tool is launched by JWlink when the CVPACK option
     has been set.
 
  Note: the names of the DOS versions of those binaries have a 'd' suffix 
  (JWlibd.exe, cvpackd.exe). This suffix must be removed.


  3. Changes in Detail

  PE binaries: 
 
    JWlink is able to produce PE32+ binaries for Win64. This format is
    automatically enabled when a PE32+ object module is detected.
 
    new options LARGEaddressaware (32-bit Windows PE) and NOLARGEaddressaware
    (64-bit Windows PE32+).
 
    constant data is put into the readonly section "rdata" ( MS link 
    compatible ) [ OW WLink writes it into read-write section DGROUP ].
 
    .idata section - which is used to store import information - is merged
    with ".rdata" ( MS link compatible ). [ OW Wlink creates a separate 
    section for .idata ].
 
    .edata section - which is used to store export information - is merged
    with ".rdata" ( MS link compatible ). [ OW Wlink creates a separate
    section for .edata ].
 
    linker "-export" directives in section ".drectve" ( COFF modules only )
    may contain an "internal name" addition ( MS link compatible ). Example:
    "-export:MyFunc1=_MyFunc1@4"
 
    linker "-entry" directive in section ".drectve" ( COFF modules only )
    doesn't need a leading underscore, it is added internally ( MS link
    compatible ). This eliminates the need to use JWasm's -zzs option.
 
    linker "-defaultlib" directive in section ".drectve" ( COFF/ELF modules
    only ) is able to handle directory names enclosed in double quotes.
 
    linker will understand directive "-import" read from section
    ".drectve" ( COFF/ELF modules only ).
 
    if the linker finds a directive in section ".drectve" that it doesn't
    understand, it will emit warning "unknown directive '-%s' ignored".
 
    for dlls, the base relocation table isn't removed if no relocations
    exist. Instead an empty table is written.
 
    if an import library is to be written, format COFF is used now as
    default if a PE binary is linked. To actually write the library,
    the external tool JWLib is used.
 
    JWlib.exe: if COFF import libraries are to be created, the "short"
    format is used now, which reduces the file size significantly.
 
    default base for dlls is 0x10000000 ( MS link compatible ).
 
    new SEGMENT attributes EXECUTABLE and WRITABLE to allow to make 
    data sections executable or code sections writable.
 
    new option NXCompat.
 
    directive ANONYMOUSEXPORT works with PE format.
 
    new option FUZZYEXPORT to allow undecorated names with EXPORT directive.
 
    unused entries in the linker-generated transfer table are no longer written.
 
  ELF binaries: 
 
    Support for 64-bit ELF binaries has been added. This format is
    automatically enabled when a 64-bit object module is detected.
 
    if no start address has been defined, symbol _start will be set as
    start address automatically.
 
    It is ensured that file alignment ( option ALIGNMENT ) won't violate
    segment alignment requirements. Also, default for file alignment is
    0 ( means no alignment ). Default for object alignment ( option OBJALIGN )
    is still 0x1000.
 
  DOS binaries: 
 
    new option KNOWEAS for DOS binaries to make the linker create
    full-sized (size >= 0x40) MZ headers for stubs.
 
    no minimum stack size for MZ binaries.
 
    no warning is displayed if a 32bit module is linked into the binary.
 
  Other: 
 
    If multiple starting points are defined, JWlink will warn only and
    use the first that was defined.
 
    File arguments may be enclosed in double quotes.
 
    the rudimentary support for Tenberry's 16-bit extender DOS/16M has
    been removed.
 
    JWlink is able to handle OMF LIDATA records with relocations.
 
    The EXPORT directive got a new attribute, NONAME, that makes it work
    similiar to ANONYMOUSEXPORT.


  4. How to create the JWlink binaries

  You'll need:
  - the JWlink source package
  - Open Watcom (v1.8 or newer)
  - if the DOS binary is to be build, the HX development package
 
  To create the jwlink binary:
  - Win32, DOS: Adjust the path for the Watcom root directory ( variable WATCOM )
    in file Makefile. If no DOS version of jwlink is to be created, set variable DOS = 0.
    Then run 'wmake'.
  - Linux: Adjust the path for the Watcom root directory ( variable WATCOM )
    in file OWLinux.mak. Then run 'wmake -f OWLinux.mak'.
 

  5. Examples

  The JWlink commandline options are vast and the syntax, which is inherited
  from Wlink, is a bit strange. As a start, here are some examples for the
  most common cases:
 
    - Win32/Win64 console application, one object module (sample.obj):
 
     jwlink format windows pe file sample.obj
 
    - Win32/Win64 GUI application, one object module (sample.obj):
 
     jwlink format windows pe runtime windows file sample.obj
 
    - Win32/Win64 dynamic link library, one object module (sample.obj):
 
     jwlink format windows pe dll file sample.obj
 
    - Win32/Win64 console application with multiple object modules,
    file1.obj and file2.obj, name of the resulting binary will be sample.exe:
 
     jwlink format windows pe dll file file1.obj, file2.obj name sample.exe
 
    - Win32/Win64 console application with one object module,
    emit symbolic debugging info and create a map file:
 
     jwlink debug c format windows pe file sample.obj op cvp, map
 
    - Win32/Win64 console application without base relocations:
 
     jwlink format windows pe file sample.obj op noreloc
 
    - Win32/Win64 dll and set the preferred base address:
 
     jwlink format windows pe dll file sample.obj op offset=0x20000000
 
    - Win32/Win64 dll and write an import library:
 
     jwlink format windows pe dll file sample.obj op implib=sample.lib
 
    - Win32 console application compiled with MS VC++:
 
     jwlink format windows pe file sample.obj op eliminate, start=_mainCRTStartup, noreloc
 
    - 32- or 64-bit ELF application:
 
     jwlink format elf file sample.obj op noreloc

