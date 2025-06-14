
;--- comparison of pointer types
;--- did only partially work prior to v2.10
ifdef __ASMC__
option masm:on
endif

_DATA segment

T1  typedef ptr DWORD
T2  typedef ptr SDWORD
T11 typedef ptr T1
T21 typedef ptr T2

v1	T1 0
v2	T2 0
v11	T11 0
v21	T21 0

	db (TYPE T1) EQ (TYPE T2)
	db T1	     EQ T2	; the simpler variant ( no TYPE operator needed to compare types )
	db (TYPE v1) EQ (TYPE v2)

;--- increase level of indirection

	db (TYPE T11) EQ (TYPE T21)
	db T11	      EQ T21
	db (TYPE v11) EQ (TYPE v21)


;--- target is equal, but different level of indirection

	db (TYPE T11) EQ (TYPE T1)
	db T11	      EQ T1
	db (TYPE v11) EQ (TYPE v1)

;--- compare types that ARE equal

T3 typedef ptr DWORD
T4 typedef ptr DWORD
T31 typedef ptr T3
T41 typedef ptr T4

v3	T3 0
v4	T4 0
v31	T31 0
v41	T41 0

	db (TYPE T3) EQ (TYPE T4)
	db T3	     EQ T4
	db (TYPE v3) EQ (TYPE v4)

	db (TYPE T31) EQ (TYPE T41)
	db T31	      EQ T41
	db (TYPE v31) EQ (TYPE v41)

_DATA ends

end
