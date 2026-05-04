
; 2.38.05 - const from type

.386
.model flat
ifdef __ASMC__
option masm:on
endif
CHAR_T EQU SBYTE
WCHAR_T EQU WORD
.code
 mov eax,size CHAR_T	    ; 1
 mov eax,size WCHAR_T	    ; 2
 mov eax,sizeof CHAR_T	    ; 1
 mov eax,sizeof WCHAR_T	    ; 2
 mov eax,type CHAR_T	    ; 0
 mov eax,type WCHAR_T	    ; 0
 mov eax,length CHAR_T	    ; 1
 mov eax,length WCHAR_T	    ; 2
ifdef __ASMC__
 mov eax,lengthof CHAR_T    ; 1
 mov eax,lengthof WCHAR_T   ; 2
 mov eax,typeof CHAR_T	    ; 0
 mov eax,typeof WCHAR_T	    ; 0
endif
 end
