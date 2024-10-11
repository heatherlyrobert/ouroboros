/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"

/*>                                                                                                                                                                                                                                                               <* 
 *> expected record (20 fields)                                                                                                                                                                                                                                   <*
 *>                                                                                                                                                                                                                                                               <*
 *> /+--    timestamp-----------------    epoch-----    project-------------    unit--------------------------   scrp   descrition-------------------------------------------------------    terse---------------   cond   step   est     insec   wav  sta   rs  pass   fair   badd   void   actual   <* 
 *> WAVE  24.04.09.04.37.46.2.15.100  1234567890  ouroboros             ouroboros_db.unit                1  (DB) verify openning and closing database                          access                123  123   0s  12345  ·  ·  y   123  123  123  123  12345                   <* 
 *>                                                                                                                                                                                                                                                               <*/

/*
 * wave
 *    0   within single object file (.o), can include external library calls
 *    1   all level 0 complete and only requires wave 0 outside object
 *
 *
 *
 *
 *   s    critical/frequent, but straight-forward, zero static/global data references
 *   M    critical/frequent, dynamic memory (alloc/free)     (can't get wrong)
 *   D    critical/frequent, input data parsing/filtering    (can't get wrong)
 *
 *
 *   A    complex and require tight scrutiny
 *   B    frequently used and so important
 *   C    used, but less common
 *   D    keepers, but limited use
 *   S    security infrastructure related
 *   o    old unit tests that need updating
 *   z    deprecated, on the way out, put to sleep
 *
 *
 *
 *
 *
 *
 */


tWAVE     *p_head   = NULL;
tWAVE     *p_tail   = NULL;

tWAVE     *s_head   = NULL;
tWAVE     *s_tail   = NULL;




#define      OURU_WAVE     0
#define      OURU_STAGE    1
#define      OURU_UNIT     2
#define      OURU_SCRP     3
#define      OURU_DESC     4



static   char        s_recd      [LEN_RECD]  = "";
static   char        s_wave      =  '-';
static   char        s_stage     =    0;
static   char        s_unit      [LEN_DESC]  = "";
static   char        s_scrp      =    0;
static   char        s_desc      [LEN_LONG]  = "";



/*====================------------------------------------====================*/
/*===----                        simple support                        ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
WAVE__wipe              (tWAVE *a_dst, char a_new)
{
   if (a_dst == NULL)  return -1;
   DEBUG_DATA   yLOG_snote   ("wipe");
   /*---(project)--------------*/
   if (a_new == 'y') {
      a_dst->w_verb      =  '·';
      a_dst->w_found     =  '·';
      strcpy (a_dst->w_hint   , "··");
      strcpy (a_dst->w_proj   , "·");
   }
   /*---(unit)-----------------*/
   if (a_new == 'y') {
      strcpy (a_dst->w_unit   , "·");
   }
   /*---(script)---------------*/
   if (a_new == 'y') {
      a_dst->w_scrp      =    0;
      a_dst->w_source    =  '·';
      strcpy (a_dst->w_desc   , "·");
      strcpy (a_dst->w_expe   , "·");
      a_dst->w_expect    =    0;
      strcpy (a_dst->w_terse  , "·");
   }
   /*---(sequencing)-----------*/
   if (a_new == 'y') {
      a_dst->w_wave      =  '·';
      a_dst->w_stage     =  '·';
      a_dst->w_rating    =  '·';
   }
   /*---(statistics)-----------*/
   if (a_new == 'y') {
      a_dst->w_nunit     =    0;
      a_dst->w_nscrp     =    0;
      a_dst->w_ncond     =    0;
      a_dst->w_nstep     =    0;
   }
   /*---(results)--------------*/
   a_dst->w_ready     =  '·';
   a_dst->w_last      =    0;
   strcpy (a_dst->w_time   , "·");
   a_dst->w_actual    =    0;
   a_dst->w_result    =  '·';
   a_dst->w_npass     =    0;
   a_dst->w_nfail     =    0;
   a_dst->w_nbadd     =    0;
   a_dst->w_nvoid     =    0;
   a_dst->w_nmiss     =    0;
   /*---(proj/unit only)-------*/
   a_dst->w_pass      =  '·';
   a_dst->w_fail      =  '·';
   a_dst->w_warn      =  '·';
   a_dst->w_none      =  '·';
   /*---(ysort)----------------*/
   if (a_new == 'y') {
      a_dst->w_unique[0] = '\0';
      a_dst->w_ysort     = NULL;
   }
   /*---(done)-----------------*/
   return 1;
}

char
WAVE__key               (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char r_key [LEN_LONG], char *r_verb)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_key       [LEN_LONG]  = "";
   char        x_verb      =  '·';
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_key  != NULL)  strcpy (r_key, "");
   /*---(check project)------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_proj"    , a_proj);
   l = strlen (a_proj);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   rc = ystrlgood (a_proj, ySTR_ALNUM, LEN_LABEL);
   DEBUG_DATA   yLOG_value   ("good"      , rc);
   --rce;  if (rc < 0 || l <= 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check unit)---------------------*/
   DEBUG_DATA   yLOG_point   ("a_unit"    , a_unit);
   --rce;  if (a_unit == NULL)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_unit"    , a_unit);
   l = strlen (a_unit);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   rc = ystrlgood (a_unit, ySTR_BASIC, LEN_TITLE);
   DEBUG_DATA   yLOG_value   ("good"      , rc);
   --rce;  if (rc < 0 && l > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check script)-------------------*/
   DEBUG_DATA   yLOG_value   ("a_scrp"    , a_scrp);
   --rce;  if (a_scrp < 0 || a_scrp > 50) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(make key)-----------------------*/
   if (strcmp (a_unit, "") == 0 || strcmp (a_unit, "·") == 0) {
      x_verb = ENTRY_PROG;
      sprintf (x_key, "%-20.20s                                  "  , a_proj);
   } else if (a_scrp == 0) {
      x_verb = ENTRY_UNIT; 
      sprintf (x_key, "%-20.20s %-30.30s   "  , a_proj, a_unit);
   } else {
      x_verb = ENTRY_WAVE;
      sprintf (x_key, "%-20.20s %-30.30s %02d", a_proj, a_unit, a_scrp);
   }
   DEBUG_DATA   yLOG_delim   ("x_key"     , x_key);
   /*---(save-back)----------------------*/
   if (r_key  != NULL)  ystrlcpy (r_key, x_key, LEN_LONG);
   if (r_verb != NULL)  *r_verb = x_verb;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
WAVE_init               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(ySORT tsae)---------------------*/
   rc = ySORT_btree (B_WAVE, "wave");
   DEBUG_PROG   yLOG_value   ("wave"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(yPARSE)-------------------------*/
   rc = yPARSE_config (YPARSE_MANUAL, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_FILL);
   DEBUG_PROG   yLOG_value   ("yparse"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_purge_all          (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tWAVE      *x_wave      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_cursor (B_WAVE, YDLST_HEAD, &x_wave);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_wave);
   while (rc >= 0 && x_wave != NULL) {
      rc = WAVE__free (&x_wave);
      if (rc < 0)  break;
      rc = ySORT_by_cursor (B_WAVE, YDLST_HEAD, &x_wave);
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_wave);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_purge_proj         (char a_proj [LEN_LABEL])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tWAVE      *x_wave      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_cursor (B_WAVE, YDLST_HEAD, &x_wave);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_wave);
   while (rc >= 0 && x_wave != NULL) {
      if (strcmp (x_wave->w_proj, a_proj) == 0) {
         rc = WAVE__free (&x_wave);
         if (rc < 0)  break;
         rc = ySORT_by_cursor (B_WAVE, YDLST_HEAD, &x_wave);
      } else {
         rc = ySORT_by_cursor (B_WAVE, YDLST_NEXT, &x_wave);
      }
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_wave);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_purge_unit         (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tWAVE      *x_wave      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_cursor (B_WAVE, YDLST_HEAD, &x_wave);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_wave);
   while (rc >= 0 && x_wave != NULL) {
      if (strcmp (x_wave->w_proj, a_proj) == 0) {
         if (strcmp (x_wave->w_unit, a_unit) == 0) {
            rc = WAVE__free (&x_wave);
            if (rc < 0)  break;
            rc = ySORT_by_cursor (B_WAVE, YDLST_HEAD, &x_wave);
         } else {
            rc = ySORT_by_cursor (B_WAVE, YDLST_NEXT, &x_wave);
         }
      } else {
         rc = ySORT_by_cursor (B_WAVE, YDLST_NEXT, &x_wave);
      }
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_wave);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_purge_scrp         (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tWAVE      *x_wave      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_cursor (B_WAVE, YDLST_HEAD, &x_wave);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_wave);
   while (rc >= 0 && x_wave != NULL) {
      if (strcmp (x_wave->w_proj, a_proj) == 0) {
         if (strcmp (x_wave->w_unit, a_unit) == 0) {
            if (x_wave->w_scrp == a_scrp) {
               rc = WAVE__free (&x_wave);
               if (rc < 0)  break;
               rc = ySORT_by_cursor (B_WAVE, YDLST_HEAD, &x_wave);
            } else {
               rc = ySORT_by_cursor (B_WAVE, YDLST_NEXT, &x_wave);
            }
         } else {
            rc = ySORT_by_cursor (B_WAVE, YDLST_NEXT, &x_wave);
         }
      } else {
         rc = ySORT_by_cursor (B_WAVE, YDLST_NEXT, &x_wave);
      }
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_wave);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_wrap               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(purge all)----------------------*/
   rc = WAVE_purge_all ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
WAVE__new               (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_gather, tWAVE **r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_key       [LEN_LONG]  = "";
   tWAVE      *x_new       = NULL;
   int         x_tries     =    0;
   char        x_verb      =  '·';
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default return)-----------------*/
   DEBUG_DATA   yLOG_point   ("r_new"     , r_new);
   --rce;  if (r_new != NULL)  {
      DEBUG_DATA   yLOG_point   ("*r_new"    , *r_new);
      DEBUG_DATA   yLOG_note    ("warning, r_new had previous data");
      *r_new = NULL;
   }
   /*---(check values)-------------------*/
   rc = WAVE__key (a_proj, a_unit, a_scrp, x_key, &x_verb);
   DEBUG_DATA   yLOG_value   ("key"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for duplicate)------------*/
   rc = ySORT_by_name (B_WAVE, x_key, &x_new);
   DEBUG_DATA   yLOG_point   ("x_exist"   , x_new);
   --rce;  if (x_new != NULL) {
      if (r_new != NULL)  *r_new = x_new;
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tWAVE *)  malloc (sizeof (tWAVE));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   WAVE__wipe (x_new, 'y');
   /*---(populate base)------------------*/
   x_new->w_verb = x_verb;
   ystrlcpy (x_new->w_proj  , a_proj, LEN_LABEL);
   ystrlcpy (x_new->w_unit  , a_unit, LEN_TITLE);
   x_new->w_scrp = a_scrp;
   ystrlcpy (x_new->w_unique, x_key , LEN_LONG);
   if (a_gather == 'y')  x_new->w_found = 'y';
   /*---(hook tsae)----------------------*/
   rc = ySORT_hook (B_WAVE, x_new, x_new->w_unique, &(x_new->w_ysort));
   DEBUG_DATA   yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ySORT_prepare (B_WAVE);
   DEBUG_DATA   yLOG_value   ("prep tsae" , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save return)--------------------*/
   if (r_new != NULL)  *r_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE__free              (tWAVE **r_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("r_old"     , r_old);
   --rce;  if (r_old == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*r_old"    , *r_old);
   --rce;  if (*r_old == NULL) {
      DEBUG_DATA   yLOG_note    ("never set");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ySORT_unhook (&((*r_old)->w_ysort));
   DEBUG_DATA   yLOG_value   ("wave"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = ySORT_prepare (B_WAVE);
   DEBUG_DATA   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear and free)-----------------*/
   free (*r_old);
   /*---(ground the pointer)-------------*/
   *r_old = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;

}



/*====================------------------------------------====================*/
/*===----                          yparse                              ----===*/
/*====================------------------------------------====================*/
static void  o___YPARSE__________o () { return; }

static   char   s_gather  =  '-';
static   int    s_central =    0;
static   int    s_read    =    0;

char
WAVE_handler            (int n, uchar a_verb [LEN_TERSE], char a_exist, void *a_handler)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tWAVE      *x_new       = NULL;
   char        x_time      [LEN_TITLE] = "·";
   long        x_epoch     =    0;
   char        x_proj      [LEN_LABEL] = "";
   char        x_unit      [LEN_TITLE] = "";
   short       x_scrp      =    0;
   char        x_source    =  '·';
   char        x_wave      =  '·';
   char        x_stage     =  '·';
   char        x_rating    =  '·';
   char        x_desc      [LEN_LONG]  = "·";
   char        x_terse     [LEN_LABEL] = "·";
   int         x_nunit     =    0;
   int         x_nscrp     =    0;
   int         x_ncond     =    0;
   int         x_nstep     =    0;
   char        x_expe      [LEN_SHORT] = "";
   int         x_expect    =    0;
   char        x_result    =  '-';
   int         x_npass     =    0;
   int         x_nfail     =    0;
   int         x_nbadd     =    0;
   int         x_nvoid     =    0;
   int         x_nmiss     =    0;
   int         x_actual    =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_verb"     , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_verb"     , a_verb);
   rc = yPARSE_ready (&c);
   DEBUG_CONF  yLOG_value   ("rc"         , rc);
   DEBUG_CONF  yLOG_value   ("c"          , c);
   /*---(read project)-------------------*/
   --rce; if (strncmp (a_verb, "PROJ", 4) == 0) {
      rc = yPARSE_scanf (a_verb, "--L-------------------"  , x_proj);
   }
   /*---(read unit test)-----------------*/
   else if   (strncmp (a_verb, "UNIT", 4) == 0) {
      rc = yPARSE_scanf (a_verb, "--L3------------------"  , x_proj, x_unit);
   }
   /*---(read wave entry)----------------*/
   else if   (strncmp (a_verb, "WAVE", 4) == 0) {
      switch (c) {
      case 23 : case 28 :
         rc = yPARSE_scanf (a_verb, "3lL3s7LCCiiiiSiCiiiiii"  , x_time, &x_epoch, x_proj, x_unit, &x_scrp, x_desc, x_terse, &x_wave, &x_stage, &x_nunit, &x_nscrp, &x_ncond, &x_nstep, x_expe, &x_expect, &x_result, &x_npass, &x_nfail, &x_nbadd, &x_nvoid, &x_nmiss, &x_actual);
         break;
      case 24 : case 29 :
         rc = yPARSE_scanf (a_verb, "3lL3s7LCCCiiiiSiCiiiiii" , x_time, &x_epoch, x_proj, x_unit, &x_scrp, x_desc, x_terse, &x_wave, &x_stage, &x_rating, &x_nunit, &x_nscrp, &x_ncond, &x_nstep, x_expe, &x_expect, &x_result, &x_npass, &x_nfail, &x_nbadd, &x_nvoid, &x_nmiss, &x_actual);
         break;
      case 25 : case 30 :
         rc = yPARSE_scanf (a_verb, "3lL3sC7LCCCiiiiSiCiiiiii", x_time, &x_epoch, x_proj, x_unit, &x_scrp, &x_source, x_desc, x_terse, &x_wave, &x_stage, &x_rating, &x_nunit, &x_nscrp, &x_ncond, &x_nstep, x_expe, &x_expect, &x_result, &x_npass, &x_nfail, &x_nbadd, &x_nvoid, &x_nmiss, &x_actual);
         break;
      }
   }
   /*---(read dependencies)--------------*/
   else if   (strncmp (a_verb, "DEPS", 4) == 0) {
      DEBUG_PROG  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(trouble)------------------------*/
   else {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_value   ("scanf"      , rc);
   if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add wave)-----------------------*/
   DEBUG_CONF  yLOG_info    ("x_proj"     , x_proj);
   DEBUG_CONF  yLOG_info    ("x_unit"     , x_unit);
   DEBUG_CONF  yLOG_value   ("x_stage"    , x_stage);
   rc = WAVE__new (x_proj, x_unit, x_scrp, s_gather, &x_new);
   DEBUG_CONF  yLOG_value   ("new"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(note)---------------------------*/
   if (rc == 0)  {
      DEBUG_PROG  yLOG_note    ("NEW");
   } else {
      DEBUG_PROG  yLOG_note    ("UPDATING");
   }
   /*---(save)---------------------------*/
   x_new->w_source  = x_source;
   ystrlcpy (x_new->w_time   , x_time   , LEN_TITLE);
   x_new->w_last    = x_epoch;
   x_new->w_wave    = x_wave;
   x_new->w_stage   = x_stage;
   x_new->w_rating  = x_rating;
   ystrlcpy (x_new->w_desc   , x_desc   , LEN_LONG);
   ystrlcpy (x_new->w_terse  , x_terse  , LEN_LABEL);
   x_new->w_nunit   = x_nunit;
   x_new->w_nscrp   = x_nscrp;
   x_new->w_ncond   = x_ncond;
   x_new->w_nstep   = x_nstep;
   ystrlcpy (x_new->w_expe   , x_expe   , LEN_SHORT);
   ystrlunage (x_expe, &x_expect);
   x_new->w_expect  = x_expect;
   x_new->w_result  = x_result;
   x_new->w_npass   = x_npass;
   x_new->w_nfail   = x_nfail;
   x_new->w_nbadd   = x_nbadd;
   x_new->w_nvoid   = x_nvoid;
   x_new->w_nmiss   = x_new->w_nstep - x_new->w_npass - x_new->w_nfail - x_new->w_nbadd - x_new->w_nvoid;
   x_new->w_actual  = x_actual;
   /*---(update totals)------------------*/
   if (strncmp (x_time, "··´", 3) == 0) {
      rc = WAVE__new (x_proj, x_unit, 0, '-', NULL);
   }
   /*---(update totals)------------------*/
   ++s_read;
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE__pull              (char a_gather, cchar a_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_gather = a_gather;
   /*---(purge the tables)---------------*/
   rc = yPARSE_reset_in ();
   DEBUG_DATA   yLOG_value   ("purge_in"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yPARSE_config (YPARSE_MANUAL, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_FILL);
   DEBUG_PROG   yLOG_value   ("yparse"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA  yLOG_point   ("a_full"     , a_full);
   --rce;  if (a_full == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA  yLOG_info    ("a_full"     , a_full);
   /*---(read all lines)-----------------*/
   rc = yPARSE_autoread (a_full, NULL, WAVE_handler);
   DEBUG_PROG  yLOG_value   ("read"      , rc);
   /*---(close)--------------------------*/
   rc = yPARSE_close ();
   DEBUG_DATA   yLOG_value   ("close"     , rc);
   --rce; if (rc < 0) {
      yURG_err ('f', "yPARSE failed closing configuration file");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_pull_local         (cchar a_file [LEN_PATH])
{
   char        rc          =    0;
   int         a           =    0;
   int         b           =    0;
   char        t           [LEN_SHORT] = "";
   if (s_central == s_read)   yURG_msg ('>', "gathering local files...");
   a  = s_read;
   rc = WAVE__pull ('y', a_file);
   b  = s_read;
   if (b - a > 0)  sprintf (t, "%2d", b - a);
   else            strcpy  (t, " ·");
   yURG_msg ('-', "read %2.2s from å%sæ", t, a_file);
   return rc;
}

char
WAVE_pull_central       (cchar a_file [LEN_PATH])
{
   char        rc          =    0;
   int         a           =    0;
   int         b           =    0;
   s_read = 0;
   yURG_msg ('>', "pull records from central database...");
   yURG_msg ('-', "database is å%sæ", a_file);
   a  = s_read;
   rc = WAVE__pull ('-', a_file);
   b  = s_read;
   yURG_msg ('-', "read %2d wave records", b - a);
   s_central = b;
   return rc;
}

char
WAVE_gather             (char a_proj [LEN_TITLE], char a_entry [LEN_TITLE], char a_full [LEN_PATH], char a_type)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c, x_before, x_after;
   char        x_name      [LEN_TITLE] = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce; if (a_proj == NULL  || a_proj [0]  == '\0') {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_proj"    , a_proj);
   DEBUG_DATA   yLOG_point   ("a_entry"   , a_entry);
   --rce; if (a_entry == NULL || a_entry [0] == '\0') {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_entry"   , a_entry);
   DEBUG_DATA   yLOG_point   ("a_full"    , a_full);
   --rce; if (a_full == NULL  || a_full [0]  == '\0') {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_full"    , a_full);
   DEBUG_DATA   yLOG_char    ("a_type"    , a_type);
   --rce; if (a_type != TYPE_WAVE) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_before = WAVE_count ();
   DEBUG_DATA   yLOG_value   ("x_before"  , x_before);
   /*---(verify/add project entry)-------*/
   rc = WAVE__new (a_proj, "" , 0, 'y', NULL);
   DEBUG_DATA   yLOG_value   ("project"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify/add unit entry)----------*/
   l = strlen (a_entry);
   ystrlcpy (x_name, a_entry, l - 4);
   rc = WAVE__new (a_proj, x_name, 0, 'y', NULL);
   DEBUG_DATA   yLOG_value   ("unit"      , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add records)--------------------*/
   rc = WAVE_pull_local (a_full);
   DEBUG_DATA   yLOG_value   ("pull"      , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(wrap)---------------------------*/
   x_after  = WAVE_count ();
   DEBUG_DATA   yLOG_value   ("x_after"   , x_after);
   c = x_after - x_before;
   DEBUG_DATA   yLOG_value   ("c"         , c);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                     searching and finding                    ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  WAVE_count     (void)                       { return  ySORT_count     (B_WAVE); }
char WAVE_by_index  (int n, tWAVE **r_cur)       { return  ySORT_by_index  (B_WAVE, n, r_cur); }
char WAVE_by_cursor (char a_dir, tWAVE **r_cur)  { return  ySORT_by_cursor (B_WAVE, a_dir, r_cur); }

char
WAVE_by_proj            (char a_proj [LEN_TITLE], tWAVE **r_cur)
{
   char        x_key       [LEN_LONG]  = "";
   WAVE__key (a_proj, "",  0, x_key, NULL);
   return  ySORT_by_name (B_WAVE, x_key, r_cur);
}



/*====================------------------------------------====================*/
/*===----                       data import                            ----===*/
/*====================------------------------------------====================*/
static void  o___IMPORT__________o () { return; }

char
WAVE_inventory          (char *a_path)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_entry     = NULL;          /* directory entry                */
   int         l           =    0;
   char        x_name      [LEN_PATH]  = "";
   char        x_keep      =  '-';
   int         x_end       =   -1;
   char        x_header    [LEN_TITLE] = "";
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (my.path, a_path, LEN_PATH);
   DEBUG_DATA   yLOG_info    ("a_path"    , a_path);
   /*---(get the home)-------------------*/
   rc = ystrlproj (my.path, my.proj);
   DEBUG_DATA   yLOG_value   ("strlhere"  , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("my.path"   , my.path);
   DEBUG_DATA   yLOG_info    ("my.proj"   , my.proj);
   sprintf (x_header, "%s.h", my.proj);
   DEBUG_DATA   yLOG_info    ("x_header"  , x_header);
   /*---(open directory)-----------------*/
   x_dir = opendir (a_path);
   DEBUG_DATA   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add project record)-------------*/
   rc = WAVE__new (my.proj, "" , 0, 'y', NULL);
   DEBUG_DATA   yLOG_value   ("project"   , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear include lists)------------*/
   INCL_clear ();
   /*---(walk entries)-------------------*/
   --rce; while (1) {
      /*---(prepare)---------------------*/
      x_keep = '-';
      /*---(read)------------------------*/
      x_entry = readdir (x_dir);
      if (x_entry == NULL)                            break;
      /*---(filter)----------------------*/
      if (x_entry->d_name   == NULL)                  continue;
      DEBUG_DATA   yLOG_info    ("d_name"    , x_entry->d_name);
      l = strlen (x_entry->d_name);
      /*---(filter obvious)--------------*/
      if      (strcmp  (x_entry->d_name, "."               ) == 0)     ;
      else if (strcmp  (x_entry->d_name, ".."              ) == 0)     ;
      else if (strncmp (x_entry->d_name, "."       , 1     ) == 0)     ;
      else if (strcmp  (x_entry->d_name + l - 1, "~"       ) == 0)     ;
      /*> else if (strcmp  (x_entry->d_name, "master.h"        ) == 0)          x_keep = TYPE_HEAD;   <*/
      else if (strncmp (x_entry->d_name, "master."     ,  7) == 0)     ;
      else if (strncmp (x_entry->d_name, "unit_daemon" , 11) == 0)     ;
      else if (strncmp (x_entry->d_name, "unit_badrc"  , 10) == 0)     ;
      /*---(filter extension)------------*/
      else if (l >= 8 && strcmp  (x_entry->d_name, "Makefile"       ) == 0)  x_keep = TYPE_MAKE;
      else if (l >= 8 && strcmp  (x_entry->d_name + l - 7, "_unit.c") == 0)  ;
      else if (l >= 6 && strcmp  (x_entry->d_name + l - 5, ".wave"  ) == 0)  x_keep = TYPE_WAVE;
      else if (l >= 6 && strcmp  (x_entry->d_name + l - 5, ".unit"  ) == 0)  x_keep = TYPE_UNIT;
      else if (l >= 7 && strcmp  (x_entry->d_name + l - 5, ".munit" ) == 0)  x_keep = TYPE_MUNIT;
      else if (l >= 3 && strcmp  (x_entry->d_name        , x_header ) == 0)  x_keep = TYPE_HEAD;
      else if (l >= 3 && strcmp  (x_entry->d_name + l - 7, "_priv.h") == 0)  x_keep = TYPE_HEAD;
      else if (l >= 3 && strcmp  (x_entry->d_name + l - 7, "_solo.h") == 0)  x_keep = TYPE_HEAD;
      else if (l >= 3 && strcmp  (x_entry->d_name + l - 7, "_uver.h") == 0)  x_keep = TYPE_HEAD;
      /*> else if (l >= 8 && strncmp (x_entry->d_name, "unit_", 5       ) == 0                   <* 
       *>                 && strcmp  (x_entry->d_name + l - 2, ".c"     ) == 0)  x_keep = TYPE_MUNIT;   <*/
      /*> else if (l >= 3 && strcmp  (x_entry->d_name + l - 2, ".c"     ) == 0)  x_keep = TYPE_CODE;   <*/
      if (x_keep == '-') {
         DEBUG_DATA   yLOG_note    ("skipping");
         continue;
      }
      /*---(handle)----------------------*/
      l = strlen (a_path);
      if (a_path [l - 1] == '/') sprintf (x_name, "%s%s" , a_path, x_entry->d_name);
      else                       sprintf (x_name, "%s/%s", a_path, x_entry->d_name);
      DEBUG_DATA   yLOG_char    ("x_keep"    , x_keep);
      switch (x_keep) {
      case TYPE_UNIT :
         DEBUG_DATA   yLOG_note    ("handle unit test file");
         ystrlcpy (x_name, x_entry->d_name, l - 4);
         rc = WAVE__new (my.proj, x_name, 0, 'y', NULL);
         DEBUG_DATA   yLOG_value   ("unit"      , rc);
         if (x_end < 0) {
            x_end = GRAPH_add_node (my.proj);
            rc = DEPS_add ("koios", my.proj);
            /*> GRAPH_edge_virt  ("koios", x_end);                                    <*/
         }
         break;
      case TYPE_MUNIT :
         DEBUG_DATA   yLOG_note    ("mini unit test file");
         if (x_end < 0) {
            x_end = GRAPH_add_node (my.proj);
            GRAPH_edge_virt ("yUNIT_solo", x_end);
            INCL_add  (-1, 'u', "yUNIT_solo", '-');
         }
         /*> rc = INCL_gather_in_c (my.proj, x_name);                                 <*/
         break;
      case TYPE_WAVE :
         DEBUG_DATA   yLOG_note    ("handle normal wave file");
         ++c;
         rc = WAVE_pull_local (x_name);
         break;
      case TYPE_CODE : case TYPE_HEAD :
         DEBUG_DATA   yLOG_note    ("handle inclusion file processing");
         /*> rc = INCL_gather_in_c (my.proj, x_name);                                 <*/
         break;
      }
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   closedir (x_dir);
   /*---(write includes)-----------------*/
   INCL_block (my.proj);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_here               (void)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rce         =  -10;                                                <* 
    *> char        rc          =    0;                                                <* 
    *> char       *p           = NULL;                                                <* 
    *> int         c           =    0;                                                <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_DATA   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(get the home)-------------------+/                                       <* 
    *> rc = ystrlhome (my.path);                                                      <* 
    *> DEBUG_DATA   yLOG_value   ("strlhere"  , rc);                                  <* 
    *> --rce;  if (rc < 0)  {                                                         <* 
    *>    DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> DEBUG_DATA   yLOG_info    ("my.path"   , my.path);                             <* 
    *> /+---(clear existing)-----------------+/                                       <* 
    *> WAVE_purge_by_path (my.path);                                                  <* 
    *> /+---(run inventory)------------------+/                                       <* 
    *> c = WAVE_inventory (my.path, 'y');                                             <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_DATA   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return c;                                                                      <*/
}



/*====================------------------------------------====================*/
/*===----                       data export                            ----===*/
/*====================------------------------------------====================*/
static void  o___EXPORT__________o () { return; }





/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*            /*--> unit test accessor ------------------------------*/
WAVE__unit              (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   char        s           [LEN_DESC]  = " -[]";
   char        t           [LEN_HUND]  = " -[]";
   char        u           [LEN_HUND]  = " -[]";
   tWAVE      *x_cur       = NULL;
   /*---(prepare)------------------------*/
   ystrlcpy  (my.unit_answer, "WAVE             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "parse"         )  == 0) {
      sprintf (s, "%2d[%.20s]", strlen (s_unit), s_unit);
      sprintf (t, "%2d[%.40s]", strlen (s_desc), s_desc);
      snprintf (my.unit_answer, LEN_RECD, "WAVE parse       : %c  %d  %-24.24s  %2d  %s",
            s_wave, s_stage, s, s_scrp, t);
   }
   else if (strcmp (a_question, "entry"         )  == 0) {
      WAVE_by_index (n, &x_cur);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "WAVE entry  (%2d) : -  -   -[]                       -   -[]", n);
      } else {
         if (x_cur->w_unit != NULL)  sprintf (s, "%2d[%.20s]", strlen (x_cur->w_unit), x_cur->w_unit);
         if (x_cur->w_desc != NULL)  sprintf (t, "%2d[%.40s]", strlen (x_cur->w_desc), x_cur->w_desc);
         snprintf (my.unit_answer, LEN_RECD, "WAVE entry  (%2d) : %c  %c  %-24.24s  %2d  %s",
               n, x_cur->w_wave, x_cur->w_stage, s, x_cur->w_scrp, t);
      }
   }
   else if (strcmp (a_question, "full"          )  == 0) {
      WAVE_by_index (n, &x_cur);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "WAVE full   (%2d) : · ·· ·               ·                     · · · ·            ·                                ·   ·   ·   ·   ·   ·  ·   ·   ·   ·   ·   ·  ·                          ·", n);
      } else {
         if (x_cur->w_nstep   >  0 )  sprintf  (t, "%3d %3d %3d %3d %3.3s %3d", x_cur->w_nunit, x_cur->w_nscrp, x_cur->w_ncond, x_cur->w_nstep, x_cur->w_expe, x_cur->w_expect);
         else                         strcpy   (t, "  ·   ·   ·   ·   ·   ·");
         if (x_cur->w_result != '·')  sprintf  (u, "%c %3d %3d %3d %3d %3d", x_cur->w_result, x_cur->w_npass, x_cur->w_nfail, x_cur->w_nbadd, x_cur->w_nvoid, x_cur->w_actual);
         else                         strcpy   (u, "·   ·   ·   ·   ·   ·");
         snprintf (my.unit_answer, LEN_RECD, "WAVE full   (%2d) : %c %-2.2s %-15.15s %-20.20s %2d %c %c %-12.12s %-30.30s %-23.23s  %-21.21s  %-26.26s %ld",
               n, x_cur->w_found, x_cur->w_hint, x_cur->w_proj, x_cur->w_unit, x_cur->w_scrp, x_cur->w_wave, x_cur->w_stage, x_cur->w_terse, x_cur->w_desc, t, u, x_cur->w_time, x_cur->w_last);
      }
   }
   /*> else if (strcmp (a_question, "project"       )  == 0) {                                                         <* 
    *>    PROJ_by_index (&x_cur, n);                                                                                   <* 
    *>    if (x_cur == NULL) {                                                                                         <* 
    *>       snprintf (my.unit_answer, LEN_RECD, "PROJ entry  (%2d) : -  -   -[]                       -   -[]", n);   <* 
    *>    } else {                                                                                                     <* 
    *>       if (x_cur->w_unit != NULL)  sprintf (s, "%2d[%.20s]", strlen (x_cur->w_unit), x_cur->w_unit);             <* 
    *>       if (x_cur->w_desc != NULL)  sprintf (t, "%2d[%.40s]", strlen (x_cur->w_desc), x_cur->w_desc);             <* 
    *>       snprintf (my.unit_answer, LEN_RECD, "PROJ entry  (%2d) : %c  %c  %-24.24s  %2d  %s",                      <* 
    *>             n, x_cur->w_wave, x_cur->w_stage, s, x_cur->w_scrp, t);                                             <* 
    *>    }                                                                                                            <* 
    *> }                                                                                                               <*/
   /*> else if (strcmp (a_question, "sortkey"       )  == 0) {                                                         <* 
    *>    WAVE_by_index (n, &x_cur);                                                                                   <* 
    *>    if (x_cur == NULL) {                                                                                         <* 
    *>       snprintf (my.unit_answer, LEN_RECD, "WAVE sortkey(%2d) :  -[]                                 -[]", n);   <* 
    *>    } else {                                                                                                     <* 
    *>       if (x_cur->key  != NULL)  sprintf (s, "%2d[%.30s]", strlen (x_cur->key ), x_cur->key );                   <* 
    *>       if (x_cur->sort != NULL)  sprintf (t, "%2d[%.40s]", strlen (x_cur->sort), x_cur->sort);                   <* 
    *>       snprintf (my.unit_answer, LEN_RECD, "WAVE sortkey(%2d) : %-34.34s  %s",                                   <* 
    *>             n, s, t);                                                                                           <* 
    *>    }                                                                                                            <* 
    *> }                                                                                                               <*/
   /*---(complete)-----------------------*/
   return my.unit_answer;
}



