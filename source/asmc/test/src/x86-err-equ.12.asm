
;--- v2.15: don't change type of EQU constant to assembly-time variable
;--- just because the value doesn't change!
;--- Masm complains as well.

x1 equ 1
x1 = 1
x1 = 2

end
