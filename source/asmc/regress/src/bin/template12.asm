
.486
.model flat, c

.template item

    atom byte ?

    .inline get fastcall {
        mov al,[this].item.atom
        }
   .ends
   .data
   T ptr item ?
   .code

foo proc
    mov cl,T.get()
    ret
foo endp

   end
