
include string.inc

.pragma comment(linker,"/DEFAULTLIB:libcmtd.lib")

s1  struct
i32 int32_t ?
i64 int64_t ?
s1  ends

s2  struct
c   char_t 4 dup(?)
p   string_t ?
a   string_t 2 dup(?)
s   s1 <>
s2  ends

.template template
    val string_t ?

    .static SetVal string:string_t {
        mov this.val,string
        }
    .ends

    .code

main proc

  local s:s2, x:s1
  local t:template

    memset( &s, 0, sizeof(s) )

    t.SetVal("string")

    mov x.i32,32
    mov x.i64,64

    mov s.p,strcpy( &s.c, "123" )
    mov s.s.i32,32
    mov s.s.i64,64
    mov s.a[0],&@CStr( "String 1" )
    mov s.a[8],&@CStr( "String 2" )

    .return 0

main endp

    end
