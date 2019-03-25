;
; http://masm32.com/board/index.php?topic=7762.msg85094#msg85094
;

;; 10.000 digits of PI

include stdio.inc
include time.inc
include tchar.inc

f equ 10000 ;; Number of digits
e equ (f*4) ;; f*4

.code

main proc argc:int_t, argv:array_t

  local stream:ptr FILE
  local l,i,j,z,a,b,s,p[f+1],r[e+1]
  local ticks:clock_t

    printf("Begin of calculating Pi\n\n");

    mov ticks,clock()

    .for (eax = 0 : eax <= e : eax++)

	mov r[rax*4],2
    .endf
    .for (eax = 0 : eax <= f : eax++)

	mov p[rax*4],0
    .endf

    ;; Start calc
    .for (edi = 1 : edi <= f : edi++)

	xor ebx,ebx
	.for (ecx = e : ecx >= 2 : ecx--)

	    lea	 rsi,[rcx-1]
	    lea	 rsi,[rsi*2+1]
	    mov	 eax,r[rcx*4]
	    imul eax,eax,10
	    add	 eax,ebx
	    cdq
	    div esi
	    mov r[rcx*4],edx
	    dec ecx
	    mul ecx
	    inc ecx
	    mov ebx,eax
	.endf

	mov eax,r[rcx*4]
	imul eax,eax,10
	add eax,ebx
	cdq
	mov ecx,10
	div ecx
	mov p[rdi*4],eax
	mov r[4],edx

	;; Digit correction
	mov ecx,edi
	.while (p[rcx*4] > 9)

	    sub p[rcx*4],10
	    dec ecx
	    inc p[rcx*4]
	.endw

	mov eax,edi
	cdq
	mov ecx,1000
	div ecx
	.if (edx==0)
	    printf("Got %5d digits of Pi\n", edi)
	.endif

    .endf
    printf("\nEnd of calculating Pi\n\n")

    clock()
    sub eax,ticks
    printf("in %lu ms\n", eax)

    ;; Output
    LINE_LNG equ 100
    mov stream,fopen("Pi.txt","w")
    setvbuf(stream, NULL, _IOFBF, 4096)

    .for (edi = 0 : edi <= (f/LINE_LNG-1) : edi++)

	.for (esi = 1 : esi <= LINE_LNG : esi++)

	    imul eax,edi,LINE_LNG
	    add	 eax,esi
	    fprintf(stream,"%d",p[rax*4])
	.endf
	fprintf(stream,"\n")
    .endf

    fclose(stream)
    printf("Printed Pi to Pi.txt\n\n")
    xor eax,eax
    ret

main endp

    end
