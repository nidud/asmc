; STREAM.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include iostream.inc

.code

main proc argc:int32_t, argv:ptr_t

  local s1:ptr iostream
  local s2:ptr bitstream

    .assert ( iostream::iostream( &s1, "stream", IO_WRONLY ) )
    .assertd ( s1.Putc(1) )
    .assertd ( s1.Putc(1) )
    .assertd ( s1.Putc(0) )
    s1.Release()

    .assert ( iostream::iostream( &s1, "stream", IO_RDONLY ) )
    .assertd ( s1.Getc() == 1 )
    .assertd ( s1.Getc() == 1 )
    .assertd ( s1.Getc() == 0 )
    s1.Release()

    .assert ( bitstream::bitstream( &s2, "stream", IO_WRONLY, 0 ) )
    .assertd ( s2.Putbits(1, 1) )
    .assertd ( s2.Putbits(1, 1) )
    s2.Release()

    .assert ( bitstream::bitstream( &s2, "stream", IO_RDONLY, 0 ) )
    .assertd ( s2.Getbits(1) == 1 )
    .assertd ( s2.Getbits(1) == 1 )
    .assertd ( s2.Getbits(1) == 0 )
    s2.Release()

    remove( "stream" )

    .assert ( bitstream::bitstream( &s2, "\x02", IO_RDONLY or IO_STRBUF, 2 ) )
    .assertd ( s2.Getbits(1) == 0 )
    .assertd ( s2.Getbits(1) == 1 )
    .assertd ( s2.Getbits(1) == 0 )
    .assertd ( s2.Getbits(13) == 0 )
    mov rbx,s2
    .assertd ( !( [rbx].bitstream.flags & IO_EOF ) )
    .assertd ( s2.Getbits(1) == 0 )
    .assertd ( ( [rbx].bitstream.flags & IO_EOF ) )
    s2.Release()

    ret

main endp

    end
