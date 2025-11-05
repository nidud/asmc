; RESOURCE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef _RESOURCE_
define _RESOURCE_

include menu.inc

define CP_OK            <L" &OK ">
define CP_CANCEL        <L"&Cancel">
define CP_ABORT         <L"&Abort">
define CP_RETRY         <L"&Retry">
define CP_IGNORE        <L"&Ignore">
define CP_YES           <L"&Yes">
define CP_NO            <L"&No">
define CP_TRYAGAIN      <L"&Try Again">
define CP_CONTINUE      <L"C&ontinue">
define CP_ERROR         <L"Error">
define CP_WARNING       <L"Warning">

define CP_EXIT          <L"Exit">
define CP_EXITPROGRAM   <L"Exit program ?">

define CP_JAN           <L"January">
define CP_FEB           <L"February">
define CP_MAR           <L"March">
define CP_APR           <L"April">
define CP_MAY           <L"May">
define CP_JUN           <L"June">
define CP_JUL           <L"July">
define CP_AUG           <L"August">
define CP_SEP           <L"September">
define CP_OCT           <L"October">
define CP_NOV           <L"November">
define CP_DEC           <L"December">

.template IDD
    ip    PIDD ?
    id    dd ?
   .ends

externdef Resource:IDD

endif
