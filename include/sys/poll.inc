; POLL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __POLL_INC
define __POLL_INC

include libc.inc

nfds_t      typedef dword

pollfd      struct
fd          int_t ?     ; File descriptor to poll
events      short_t ?   ; Types of events poller cares about
revents     short_t ?   ; Types of events that actually occurred
pollfd      ends

poll        proto __cdecl :ptr pollfd, :nfds_t, :int_t

endif
