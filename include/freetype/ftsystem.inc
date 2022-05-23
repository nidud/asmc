
ifndef FTSYSTEM_H_
define FTSYSTEM_H_

FT_BEGIN_HEADER

FT_Memory		typedef ptr FT_MemoryRec

CALLBACKC(FT_Alloc_Func, :FT_Memory, :sdword)
CALLBACKC(FT_Free_Func, :FT_Memory, :ptr)
CALLBACKC(FT_Realloc_Func, :FT_Memory, :sdword, :sdword, :ptr)

FT_MemoryRec		STRUC
user			ptr ?
alloc			FT_Alloc_Func ?
free			FT_Free_Func ?
realloc			FT_Realloc_Func ?
FT_MemoryRec		ENDS
FT_Stream		typedef ptr FT_StreamRec

FT_StreamDesc		UNION
value			sdword ?
pointer			ptr ?
FT_StreamDesc		ENDS

CALLBACKC(FT_Stream_IoFunc, :FT_Stream, :dword, :ptr, :dword)
CALLBACKC(FT_Stream_CloseFunc, :FT_Stream)

FT_StreamRec		STRUC
base			ptr byte ?
size			dd ?
pos			dd ?
descriptor		FT_StreamDesc <>
pathname		FT_StreamDesc <>
read			FT_Stream_IoFunc ?
close			FT_Stream_CloseFunc ?
memory			FT_Memory ?
cursor			ptr byte ?
limit			ptr byte ?
FT_StreamRec		ENDS

FT_END_HEADER

endif
