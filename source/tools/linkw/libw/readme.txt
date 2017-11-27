
 JWlib is a fork of Open Watcom Wlib.

 The changes in the wlib sources are:

  - write the "short" format of COFF import libaries.
  - don't add "short" names to the "longnames" member. OTOH,
    the "longnames" member is ALWAYS written for COFF import libraries,
    even if it is empty.
  - new -i6 option to make import libs for AMD64 processor.


 LIBW is a fork of JWlib.

 The changes in the jwlib sources are:

  - accept wildargs as argument: LIBW my.lib *.obj
