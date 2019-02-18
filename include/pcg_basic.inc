;;
;; PCG Random Number Generation for C.
;;
;; Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
;;
;; Licensed under the Apache License, Version 2.0 (the "License");
;; you may not use this file except in compliance with the License.
;; You may obtain a copy of the License at
;;
;;     http://www.apache.org/licenses/LICENSE-2.0
;;
;; Unless required by applicable law or agreed to in writing, software
;; distributed under the License is distributed on an "AS IS" BASIS,
;; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;; See the License for the specific language governing permissions and
;; limitations under the License.
;;
;; For additional information about the PCG random number generation scheme,
;; including its license and other licensing options, visit
;;
;;     http://www.pcg-random.org
;;

;;
;; This code is derived from the full C implementation, which is in turn
;; derived from the canonical C++ PCG implementation. The C++ version
;; has many additional features and is preferable if you can use C++ in
;; your project.
;;

ifndef PCG_BASIC_H_INCLUDED
PCG_BASIC_H_INCLUDED equ <>

include libc.inc
include stdint.inc
includelib pcg32.lib

pcg_state_setseq_64 struct
    state   uint64_t ?
    rngseq  uint64_t ?
pcg_state_setseq_64 ends

pcg32_random_t typedef pcg_state_setseq_64

PCG32_INITIALIZER   equ <{ 0x853c49e6748fea9b, 0xda3e39cb94b95bdb }>

pcg32_srandom       proto initstate:uint64_t, initseq:uint64_t
pcg32_srandom_r     proto rng:ptr pcg32_random_t, initstate:uint64_t, initseq:uint64_t
pcg32_random        proto
pcg32_random_r      proto rng:ptr pcg32_random_t
pcg32_boundedrand   proto _bound:uint32_t
pcg32_boundedrand_r proto rng:ptr pcg32_random_t, _bound:uint32_t

endif
