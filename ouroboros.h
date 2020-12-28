/*===============================[[ beg code ]]===============================*/


/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "ut (unit testing)"
#define     P_SUBJECT   "master unit testing sequencer"
#define     P_PURPOSE   "provide simple unit testing framework for writing scripts"

#define     P_NAMESAKE  "ouroboros (tail-eater)"
#define     P_HERITAGE  "the world serpent symbolizing eternal cyclic renewal"
#define     P_IMAGERY   "powerful, world-encircling serpent swallowing its own tail"
#define     P_REASON    "symbol of life, death, and renewal matching up with testing"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2020-12"

#define     P_VERMAJOR  "0.-- preparing for production use"
#define     P_VERMINOR  "0.1- build framework"
#define     P_VERNUM    "0.1b"
#define     P_VERTXT    "PROG and MAIN basics.  now compilies, but gutless"


/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YORUBOROS
#define YORUBOROS  loaded



/*===[[ STANDARD C LIBRARIES ]]===============================================*/
#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include    <string.h>       /* C_ANSI : printf, snprintf, fgets, fopen, ...  */

/*===[[ CUSTOM LIBRARIES ]]===================================================*/
#include    <yUNIT.h>        /* CUSTOM : heatherly unit testing               */
#include    <yLOG.h>         /* CUSTOM : heatherly program logging            */
#include    <ySTR.h>         /* CUSTOM : heatherly safer string handling      */
#include    <yURG.h>         /* CUSTOM : heatherly urgent processing          */


typedef     struct cGLOBALS     tGLOBALS;
struct cGLOBALS
{
   /*---(general)---------------*/
   char        version     [LEN_FULL];      /* program version info           */
   /*---(done)------------------*/
};
extern      tGLOBALS    my;


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(support)-----------------*/
char*       PROG_version            (void);
/*---(startup)-----------------*/
char        PROG__init              (void);
char        PROG__args              (int a_argc, char *a_argv[]);
char        PROG__begin             (void);
char        PROG_startup            (int a_argc, char *a_argv[]);
char        PROG_final              (void);
/*---(drivers)-----------------*/
/*---(shutdown)----------------*/
char        PROG__end               (void);
char        PROG_shutdown           (void);
/*---(done)--------------------*/



#endif
/*============================[[ end-of-code ]]===============================*/
