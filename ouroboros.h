/*===============================[[ beg code ]]===============================*/


/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "ut (unit testing)"
#define     P_SUBJECT   "master unit testing sequencer"
#define     P_PURPOSE   "provide simple unit testing framework for writing scripts"

#define     P_NAMESAKE  "ouroboros-aperantos (tail-eater)"
#define     P_HERITAGE  "the world serpent symbolizing eternal cyclic renewal"
#define     P_IMAGERY   "powerful, world-encircling serpent swallowing its own tail"
#define     P_REASON    "symbol of life, death, and renewal matching up with testing"

/* ouroboros literally means tail (oura) eater (boros)
 * aperantos is greek for vast, infinite, limitless */

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "ouroboros"
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
#define     P_VERMINOR  "0.2- adapt to new data requirements"
#define     P_VERNUM    "0.2a"
#define     P_VERTXT    "brought in yPARSE and new WAVE data format for better outcomes"


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
 * questions..
 *    -- keep a database?
 *    -- store program version?
 *    -- give scripts an enduring ID?
 *    -- keep old test results?
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
#include    <ySORT.h>        /* CUSTOM : heatherly sorting library            */
#include    <yPARSE.h>       /* CUSTOM : heatherly record parsing             */
#include    <yCOLOR_solo.h>  /* CUSTOM : heatherly colorization library       */
#include    <yDLST_solo.h>   /* CUSTOM : heatherly linked-list library        */

typedef struct dirent    tDIRENT;
typedef struct FILE      tFILE;



#define     F_DB          "/var/lib/ouroboros/ouroboros.db"

#define     RUN_HERE      'H'
#define     RUN_PURGE     'P'
#define     RUN_CREATE    'C'
#define     RUN_UPDATE    'U'
#define     RUN_REMOVE    'R'

#define     RUN_DUMP      'd'
#define     RUN_LIST      'l'
#define     RUN_SEQ       's'

typedef     struct cGLOBALS     tGLOBALS;
struct cGLOBALS
{
   /*---(general)--------------*/
   char        version     [LEN_FULL];      /* program version info           */
   char        unit_answer [LEN_RECD];      /* response from unit testing     */
   char        run_mode;
   char        path        [LEN_PATH];      /* base directory                 */
   char        proj        [LEN_LABEL];     /* project name                   */
   char        wave_min;
   char        wave_max;
   char        n_db        [LEN_PATH];      /* database name                  */
   FILE       *f_db;                        /* database file pointer          */
   /*---(statistics)-----------*/
   int         projs;
   int         units;
   int         scrps;
   int         conds;
   int         steps;
   /*---(results)--------------*/
   int         ready;
   int         pass;
   int         fail;
   int         badd;
   int         othr;
   /*---(done)-----------------*/
};
extern      tGLOBALS    my;

/*> typedef struct cPROJ  tPROJ;                                                      <* 
 *> struct cPROJ {                                                                    <* 
 *>    /+---(master)------------+/                                                    <* 
 *>    uchar       p_name      [LEN_TITLE];                                           <* 
 *>    uchar       p_path      [LEN_FULL];                                            <* 
 *>    /+---(testing)-----------+/                                                    <* 
 *>    long        p_time;                                                            <* 
 *>    uchar       p_resu;                                                            <* 
 *>    /+---(peers)-------------+/                                                    <* 
 *>    tPROJ      *p_next;                                                            <* 
 *>    tPROJ      *p_prev;                                                            <* 
 *>    /+---(units)-------------+/                                                    <* 
 *>    tUNIT      *p_head;                                                            <* 
 *>    tUNIT      *p_tail;                                                            <* 
 *>    short       p_units;                                                           <* 
 *>    /+---(sorted)------------+/                                                    <* 
 *>    tBTREE     *p_sort;                                                            <* 
 *>    /+---(done)--------------+/                                                    <* 
 *> };                                                                                <*/

/*> typedef struct cUNIT  tUNIT;                                                      <* 
 *> struct cUNIT {                                                                    <* 
 *>    /+---(parent)------------+/                                                    <* 
 *>    tPROJ      *u_parent;                                                          <* 
 *>    /+---(master)------------+/                                                    <* 
 *>    uchar       u_name      [LEN_TITLE];                                           <* 
 *>    /+---(testing)-----------+/                                                    <* 
 *>    long        u_time;                                                            <* 
 *>    uchar       u_resu;                                                            <* 
 *>    /+---(peers)-------------+/                                                    <* 
 *>    tUNIT      *u_next;                                                            <* 
 *>    tUNIT      *u_prev;                                                            <* 
 *>    /+---(waves)-------------+/                                                    <* 
 *>    tWAVE      *u_head;                                                            <* 
 *>    tWAVE      *u_tail;                                                            <* 
 *>    short       u_scrps;                                                           <* 
 *>    /+---(sorted)------------+/                                                    <* 
 *>    tBTREE     *u_sort;                                                            <* 
 *>    /+---(done)--------------+/                                                    <* 
 *> };                                                                                <*/

/*> typedef struct cSCRP  tSCRP;                                                      <* 
 *> struct cSCRP {                                                                    <* 
 *>    /+---(parent)------------+/                                                    <* 
 *>    tUNIT      *s_parent;                                                          <* 
 *>    /+---(master)------------+/                                                    <* 
 *>    uchar       u_name      [LEN_TITLE];                                           <* 
 *>    /+---(testing)-----------+/                                                    <* 
 *>    long        u_time;                                                            <* 
 *>    uchar       u_resu;                                                            <* 
 *>    /+---(peers)-------------+/                                                    <* 
 *>    tUNIT      *s_next;                                                            <* 
 *>    tUNIT      *s_prev;                                                            <* 
 *>    /+---(sorted)------------+/                                                    <* 
 *>    tBTREE     *s_sort;                                                            <* 
 *>    /+---(done)--------------+/                                                    <* 
 *> };                                                                                <*/


#define     B_WAVE         'w'


typedef struct cWAVE  tWAVE;
struct cWAVE {
   /*---(project)--------------*/
   char        w_hint      [LEN_SHORT];
   char        w_found;
   char        w_proj      [LEN_LABEL];
   /*---(unit)-----------------*/
   char        w_unit      [LEN_TITLE];
   /*---(script)---------------*/
   char        w_scrp;
   char        w_desc      [LEN_LONG];
   char        w_expe      [LEN_SHORT];
   short       w_expect;
   char        w_terse     [LEN_LABEL];
   /*---(sequencing)-----------*/
   char        w_wave;
   char        w_stage;
   /*---(statistics)-----------*/
   char        w_nunit;
   char        w_nscrp;
   short       w_ncond;
   short       w_nstep;
   /*---(results)--------------*/
   char        w_ready;
   char        w_time      [LEN_TITLE];
   long        w_last;
   short       w_actual;
   char        w_result;
   short       w_npass;
   short       w_nfail;
   short       w_nbadd;
   short       w_nvoid;
   /*---(project links)--------*/
   char        sort        [LEN_HUND];
   tWAVE      *p_prev;
   tWAVE      *p_next;
   /*---(script links)---------*/
   char        key         [LEN_HUND];
   tWAVE      *s_prev;
   tWAVE      *s_next;
   /*---(sorting)--------------*/
   char        w_unique    [LEN_HUND];
   tSORT      *w_ysort;
   /*---(done)-----------------*/
};

extern tWAVE     *p_head;
extern tWAVE     *p_tail;

extern tWAVE     *s_head;
extern tWAVE     *s_tail;



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
char        PROG_driver             (void);
/*---(shutdown)----------------*/
char        PROG__end               (void);
char        PROG_shutdown           (void);
/*---(unittest)----------------*/
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);
/*---(done)--------------------*/



/*---(support)-----------------*/
char        WAVE__wipe              (tWAVE *a_dst, char a_new);
char        WAVE__key               (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char r_key [LEN_LONG]);
char        WAVE__verify            (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_desc [LEN_LONG], char a_expect [LEN_SHORT], char a_terse [LEN_LABEL], char a_wave, char a_stage, char *r_key);
/*---(program)-----------------*/
char        WAVE_init               (void);
char        WAVE_purge_all          (void);
char        WAVE_purge_proj         (char a_proj [LEN_LABEL]);
char        WAVE_purge_unit         (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE]);
char        WAVE_purge_scrp         (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp);
char        WAVE_wrap               (void);

char        WAVE_pull               (cchar a_file [LEN_PATH]);

char        PROJ__hook              (tWAVE *a_ref, tWAVE *a_new);
char        WAVE__hook              (tWAVE *a_ref, tWAVE *a_new);
char        PROJ__unhook            (tWAVE *a_old);
char        WAVE__unhook            (tWAVE *a_old);
char        WAVE__populate          (tWAVE *a_new, uchar a_wave, uchar a_stage, char *a_unit, char a_scrp, char *a_desc, char *a_key);
/*---(memory)------------------*/
char        WAVE__new               (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_force, tWAVE **r_new);
char        WAVE_new                (tWAVE **a_new);
char        WAVE_force              (tWAVE **a_new);
char        WAVE__free              (tWAVE **a_old);
char        WAVE_purge              (void);
char        WAVE_purge_by_unit      (char *a_unit);
char        WAVE_purge_by_path      (char *a_path);
/*---(data)--------------------*/
char        WAVE_populate           (tWAVE *a_new, char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc);
char        WAVE_results            (tWAVE *x_wave, uchar a_resu, int a_cond, int a_test, int a_pass, int a_fail, int a_badd, int a_othr);
/*---(search)------------------*/
int         WAVE_count              (void);
char        WAVE_by_index           (int n, tWAVE **a_cur);
char        PROJ_by_index           (tWAVE **a_cur, int n);
char        WAVE_by_cursor          (tWAVE **a_cur, char a_move);
char        PROJ_by_cursor          (tWAVE **a_cur, char a_move);
char        WAVE_by_sortkey         (tWAVE **a_cur, char *a_name);
char        PROJ_by_sortkey         (tWAVE **a_cur, char *a_name);
/*---(import)------------------*/
char        WAVE_parse              (char *a_recd, char a_call);
char        WAVE_read               (char *a_name, char a_call);
char        WAVE_inventory          (char *a_path, char a_call);
char        WAVE_here               (void);
/*---(sort)--------------------*/
/*> char*       WAVE__key               (tWAVE *a_cur);                               <*/
char*       PROJ__key               (tWAVE *a_cur);
char        WAVE_gnome              (void);
/*---(unittest)----------------*/
char*       WAVE__unit              (char *a_question, int n);



char        RPTG_clear              (void);
char        RPTG_spread             (uchar a_wave, uchar a_stage);
char*       RPTG_spread_disp        (void);
char*       RPTG_line               (tWAVE *a_prv, tWAVE *a_cur, char *a_spec);
char        RPTG_heading            (void);
char        RPTG_dump               (void);


char        TEST_result             (tWAVE *a_cur);
char        TEST_run                (tWAVE *a_cur);
char*       TEST__unit              (char *a_question, int n);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        DB__open                (char a_mode, int *a_projs, int *a_units, int *a_scrps, int *a_conds, int *a_steps);
char        DB__close               (void);
char*       DB__unit                (char *a_question, int n);



#endif
/*============================[[ end-of-code ]]===============================*/
