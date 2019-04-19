
;--- comparison of pointer types
;--- did only partially work prior to v2.10

_DATA segment

T1  typedef ptr DWORD
T2  typedef ptr SDWORD
T11 typedef ptr T1
T21 typedef ptr T2

v1	T1 0
v2	T2 0
v11	T11 0
v21	T21 0

	db (typeof T1) EQ (typeof T2)
	db T1	     EQ T2	; the simpler variant ( no TYPEOF operator needed to compare types )
	db (typeof v1) EQ (typeof v2)

;--- increase level of indirection

	db (typeof T11) EQ (typeof T21)
	db T11	      EQ T21
	db (typeof v11) EQ (typeof v21)


;--- target is equal, but different level of indirection

	db (typeof T11) EQ (typeof T1)
	db T11	      EQ T1
	db (typeof v11) EQ (typeof v1)

;--- compare types that ARE equal

T3 typedef ptr DWORD
T4 typedef ptr DWORD
T31 typedef ptr T3
T41 typedef ptr T4

v3	T3 0
v4	T4 0
v31	T31 0
v41	T41 0

	db (typeof T3) EQ (typeof T4)
	db T3	     EQ T4
	db (typeof v3) EQ (typeof v4)

	db (typeof T31) EQ (typeof T41)
	db T31	      EQ T41
	db (typeof v31) EQ (typeof v41)

_DATA ends

end
