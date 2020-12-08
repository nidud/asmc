.data
symbol1 db "Hello world"
symbol2 db 1,2,3
symbol3 db 4
.code

mainCRTStartup proc
  
  mov eax,1
  sub eax,1
  ret
mainCRTStartup endp

END
