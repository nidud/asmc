;
; v2.30.20 - .enum
;
    .x64
    .model flat
    .code

    .enum
        y,
        n

    .enum C {
        a,
        b
    }

    .enum Day {
         Sat=1, Sun, Mon, Tue, Wed, Thu, Fri }

    mov al,y
    mov al,n
    mov al,a
    mov al,b
    mov al,Sat
    mov al,Sun
    mov al,Mon
    mov al,Tue
    mov al,Wed
    mov al,Thu
    mov al,Fri

    end
