; DUP.ASM--
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/dup-dup2?view=msvc-170
;
; This program uses the variable old to save
; the original stdout. It then opens a new file named
; DataFile and forces stdout to refer to it. Finally, it
; restores stdout to its original state.

include io.inc
include stdlib.inc
include stdio.inc
include tchar.inc

.code

_tmain proc

  .new old:int_t
  .new DataFile:ptr FILE

   mov old,_dup( 1 )    ; "old" now refers to "stdout"
                        ; Note:  file descriptor 1 == "stdout"
   .if ( old == -1 )

      perror( "_dup( 1 ) failure" )
      exit( 1 )
   .endif
   _write( old, "This goes to stdout first\n", 26 )
   mov DataFile,fopen( "data", "w" )
   .if ( rax == NULL )

      puts( "Can't open file 'data'\n" )
      exit( 1 )
   .endif

   ; stdout now refers to file "data"
   .ifd ( _dup2( _fileno( DataFile ), 1 ) == -1 )

      perror( "Can't _dup2 stdout" )
      exit( 1 )
   .endif
   puts( "This goes to file 'data'\n" );

   ; Flush stdout stream buffer so it goes to correct file
   fflush( stdout )
   fclose( DataFile )

   ; Restore original stdout
   _dup2( old, 1 )
   puts( "This goes to stdout\n" )
   puts( "The file 'data' contains:" )
   _flushall()
   system( "type data" )
   ret

_tmain endp

    end _tstart
