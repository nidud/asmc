ifndef FTLIST_H_
define FTLIST_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_List_Find proto \
                  list: FT_List,

FT_List_Add proto \
                  list: FT_List,
                  node: FT_ListNode

FT_List_Insert proto \
                  list: FT_List,
                  node: FT_ListNode

FT_List_Remove proto \
                  list: FT_List,
                  node: FT_ListNode

FT_List_Up proto \
                  list: FT_List,
                  node: FT_ListNode

CALLBACKC(FT_List_Iterator, :FT_ListNode, :ptr)

FT_List_Iterate proto \
                  list: FT_List,
              iterator: FT_List_Iterator,

CALLBACKC(FT_List_Destructor, :FT_Memory, :ptr, :ptr)

FT_List_Finalize proto \
                  list: FT_List,
               destroy: FT_List_Destructor,
                memory: FT_Memory,

endif
