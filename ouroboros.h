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
#define     P_VERNUM    "0.1d"
#define     P_VERTXT    "TEST run and check basic code and unit testing done"


/*
 *  GRAND PLAN
 *
 *  start with reading wave files put out by koios
 *
 *  then incorporate wave/stage descriptors from master.unit
 *
 *  control execution of scripts in order
 *
 *  controllable reporting on results
 *
 *  then create a central database of outcomes
 *
 *  pull sequences/dependencies between programs
 *
 *  control full code-base wide execution of unit tests
 *
 *  central reporting on code readiness
 *
 *
 *
 */

/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YORUBOROS
#define YORUBOROS  loaded



/*===[[ STANDARD C LIBRARIES ]]===============================================*/
#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include    <string.h>       /* C_ANSI : printf, snprintf, fgets, fopen, ...  */
#include    <dirent.h>       /* POSIX  (11) opendir, readdir, alphasort       */
#include    <unistd.h>       /* POSIX  (11) opendir, readdir, alphasort       */

/*===[[ CUSTOM LIBRARIES ]]===================================================*/
#include    <yUNIT.h>        /* CUSTOM : heatherly unit testing               */
#include    <yLOG.h>         /* CUSTOM : heatherly program logging            */
#include    <ySTR.h>         /* CUSTOM : heatherly safer string handling      */
#include    <yURG.h>         /* CUSTOM : heatherly urgent processing          */
#include    <yCOLOR_solo.h>  /* CUSTOM : heatherly colorization library       */

typedef struct dirent    tDIRENT;
typedef struct FILE      tFILE;

typedef     struct cGLOBALS     tGLOBALS;
struct cGLOBALS
{
   /*---(general)---------------*/
   char        version     [LEN_FULL];      /* program version info           */
   char        unit_answer [LEN_RECD];      /* response from unit testing     */
   char        path        [LEN_PATH];      /* base directory                 */
   char        wave_min;
   char        wave_max;
   /*---(done)------------------*/
};
extern      tGLOBALS    my;


extern char      *g_greek;


typedef struct cWAVE  tWAVE;
struct cWAVE {
   uchar       wave;
   uchar       stage;
   uchar      *path;
   uchar      *unit;
   uchar       scrp;
   uchar      *desc;
   uchar      *key;
   uchar       resu;
   int         cond;
   int         test;
   int         pass;
   int         fail;
   int         badd;
   int         othr;
   tWAVE      *s_next;
   tWAVE      *s_prev;
};
extern tWAVE     *g_head;
extern tWAVE     *g_tail;
extern int        g_count;
extern int        g_curr;



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
/*---(unittest)----------------*/
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);
/*---(done)--------------------*/



char        WAVE__wipe              (tWAVE *a_dst, char a_new);
char        WAVE__verify            (char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc, char *a_key);
char        WAVE__hook              (tWAVE *a_new);
char        WAVE__unhook            (tWAVE *a_old);
char        WAVE__populate          (tWAVE *a_new, char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc, char *a_key);
char        WAVE_new                (tWAVE **a_new, char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc);
char        WAVE_force              (tWAVE **a_new, char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc);
char        WAVE_free               (tWAVE **a_old);
char        WAVE_purge              (void);
char        WAVE_by_index           (tWAVE **a_cur, int n);
char        WAVE_by_cursor          (tWAVE **a_cur, char a_move);
char        WAVE_by_name            (tWAVE **a_cur, char *a_name);
char        WAVE_parse              (char *a_recd, char a_call);
char        WAVE_read               (char *a_name, char a_call);
char        WAVE_inventory          (char *a_path, char a_call);
char        WAVE_here               (void);
char        WAVE_swap               (tWAVE *a_one, tWAVE *a_two);
char        WAVE_gnome              (void);
char*       WAVE__unit              (char *a_question, int n);



char        RPTG_clear              (void);
char        RPTG_spread             (char a_wave, char a_stage);
char        RPTG_heading            (void);


char        TEST_result             (tWAVE *a_cur);
char        TEST_run                (tWAVE *a_cur);
char*       TEST__unit              (char *a_question, int n);

#endif
/*============================[[ end-of-code ]]===============================*/
