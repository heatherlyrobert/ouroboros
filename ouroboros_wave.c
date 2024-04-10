/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"

/*>                                                                                                                                                                                                                                                               <* 
 *> expected record (20 fields)                                                                                                                                                                                                                                   <*
 *>                                                                                                                                                                                                                                                               <*
 *> /+--    timestamp-----------------    epoch-----    project-------------    unit--------------------------   scrp   descrition-------------------------------------------------------    terse---------------   cond   step   est     insec   wav  sta   rs  pass   fair   badd   void   actual   <* 
 *> WAVE  24.04.09.04.37.46.2.15.100  1234567890  ouroboros             ouroboros_db.unit                1  (DB) verify openning and closing database                          access                123  123   0s  12345  ·  ·  y   123  123  123  123  12345                   <* 
 *>                                                                                                                                                                                                                                                               <*/

/*
 *  0) read in master.unit entries for stage/wave
 *
 *  1) take in all *.wave files
 *  2) execute as requested
 *  3) report out
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
      strcpy (a_dst->w_hint   , "··");
      a_dst->w_found     =  '·';
      strcpy (a_dst->w_proj   , "·");
   }
   /*---(unit)-----------------*/
   if (a_new == 'y') {
      strcpy (a_dst->w_unit   , "·");
   }
   /*---(script)---------------*/
   if (a_new == 'y') {
      a_dst->w_scrp      =    0;
      strcpy (a_dst->w_desc   , "·");
      strcpy (a_dst->w_expe   , "·");
      a_dst->w_expect    =    0;
      strcpy (a_dst->w_terse  , "·");
   }
   /*---(sequencing)-----------*/
   if (a_new == 'y') {
      a_dst->w_wave      =  '·';
      a_dst->w_stage     =  '·';
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
   /*---(ysort)----------------*/
   if (a_new == 'y') {
      a_dst->w_unique[0] = '\0';
      a_dst->w_ysort     = NULL;
   }
   /*---(done)-----------------*/
   return 1;
}

char
WAVE__key               (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char r_key [LEN_LONG])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_key       [LEN_LONG]  = "";
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
   if (a_scrp == 0)  sprintf (x_key, "%-20.20s %-30.30s   ", a_proj, a_unit);
   else              sprintf (x_key, "%-20.20s %-30.30s %02d", a_proj, a_unit, a_scrp);
   DEBUG_DATA   yLOG_info    ("x_key"     , x_key);
   /*---(save-back)----------------------*/
   if (r_key  != NULL)  ystrlcpy (r_key, x_key, LEN_LONG);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
WAVE__verify            (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_desc [LEN_LONG], char a_expect [LEN_SHORT], char a_terse [LEN_LABEL], char a_wave, char a_stage, char *r_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tWAVE      *x_old       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(sequencing)---------------------*/
   DEBUG_DATA   yLOG_schar   (a_wave);
   --rce;  if (strchr ("·" YSTR_NUMBER, a_wave) == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_schar   (a_stage);
   --rce;  if (strchr ("·" YSTR_LOWER, a_stage) == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_unit);
   --rce;  if (a_unit == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_sint    (a_scrp);
   --rce;  if (a_scrp < 1 || a_scrp > 99) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_desc);
   --rce;  if (a_desc == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for existing)-------------*/
   sprintf (r_key , "%c.%c.%-20.20s.%02d", a_wave, a_stage, a_unit, a_scrp);
   WAVE_by_sortkey (&x_old, r_key);
   --rce;  if (x_old != NULL) {
      return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
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
WAVE__new               (char a_proj [LEN_LABEL], char a_unit [LEN_TITLE], char a_scrp, char a_force, tWAVE **r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_key       [LEN_LONG]  = "";
   tWAVE      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_char    ("a_force"   , a_force);
   /*---(default return)-----------------*/
   DEBUG_DATA   yLOG_point   ("r_new"     , r_new);
   --rce;  if (r_new != NULL)  {
      DEBUG_DATA   yLOG_point   ("*r_new"    , *r_new);
      if (*r_new != NULL && a_force != 'y') {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      *r_new = NULL;
   }
   /*---(check values)-------------------*/
   rc = WAVE__key (a_proj, a_unit, a_scrp, x_key);
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
   ystrlcpy (x_new->w_proj  , a_proj, LEN_LABEL);
   ystrlcpy (x_new->w_unit  , a_unit, LEN_TITLE);
   x_new->w_scrp = a_scrp;
   ystrlcpy (x_new->w_unique, x_key , LEN_LONG);
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

char WAVE_new      (tWAVE **a_new) { return WAVE__new (a_new, '-', NULL, NULL, 0); }
char WAVE_force    (tWAVE **a_new) { return WAVE__new (a_new, 'y', NULL, NULL, 0); }

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

/*
 *> /+--    timestamp-----------------    epoch-----    project-------------    unit--------------------------   scrp   descrition-------------------------------------------------------    terse---------------   unit   scrp   cond   step   expect  wav  sta   rs  pass   fair   badd   void   actual   <* 
 *> WAVE  24.04.09.04.37.46.2.15.100  1234567890  ouroboros             ouroboros_db.unit                1  a  1  (DB) verify openning and closing database                          access                123  123  123  123  12345  y   123  123  123  123  12345                   <* 
 */

char
WAVE_handler            (int n, uchar a_verb [LEN_TERSE], char a_exist, void *a_handler)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tWAVE      *x_new       = NULL;
   char        x_time      [LEN_TITLE] = "";
   long        x_epoch     =    0;
   char        x_proj      [LEN_LABEL] = "";
   char        x_unit      [LEN_TITLE] = "";
   short       x_scrp      =    0;
   char        x_wave, x_stage;
   char        x_desc      [LEN_LONG]  = "";
   char        x_terse     [LEN_LABEL] = "";
   short       x_nunit, x_nscrp, x_ncond, x_nstep;
   char        x_expe      [LEN_SHORT] = "";
   long        x_expect, x_actual;
   char        x_result;
   short       x_npass, x_nfail, x_nbadd, x_nvoid;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_verb"     , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_verb"     , a_verb);
   --rce;  if (strcmp (a_verb, "WAVE") != 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read details)-------------------*/
   rc = yPARSE_scanf (a_verb, "3lL3s7LCCssssSsCsssss"  , x_time, &x_epoch, x_proj, x_unit, &x_scrp, x_desc, x_terse, &x_wave, &x_stage, &x_nunit, &x_nscrp, &x_ncond, &x_nstep, x_expe, &x_expect, &x_result, &x_npass, &x_nfail, &x_nbadd, &x_nvoid, &x_actual);
   DEBUG_CONF  yLOG_value   ("scanf"      , rc);
   if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add wave)-----------------------*/
   DEBUG_CONF  yLOG_info    ("x_proj"     , x_proj);
   DEBUG_CONF  yLOG_info    ("x_unit"     , x_unit);
   DEBUG_CONF  yLOG_value   ("x_stage"    , x_stage);
   rc = WAVE__new (x_proj, x_unit, x_scrp, '-', &x_new);
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
   ystrlcpy (x_new->w_time   , x_time   , LEN_TITLE);
   x_new->w_last    = x_epoch;
   x_new->w_wave    = x_wave;
   x_new->w_stage   = x_stage;
   ystrlcpy (x_new->w_desc   , x_desc   , LEN_LONG);
   ystrlcpy (x_new->w_terse  , x_terse  , LEN_LABEL);
   x_new->w_nunit   = x_nunit;
   x_new->w_nscrp   = x_nscrp;
   x_new->w_ncond   = x_ncond;
   x_new->w_nstep   = x_nstep;
   ystrlcpy (x_new->w_expe   , x_expe   , LEN_SHORT);
   x_new->w_expect  = x_expect;
   x_new->w_result  = x_result;
   x_new->w_npass   = x_npass;
   x_new->w_nfail   = x_nfail;
   x_new->w_nbadd   = x_nbadd;
   x_new->w_nvoid   = x_nvoid;
   x_new->w_actual  = x_actual;
   /*> DEBUG_CONF  yLOG_info    ("x_full"     , x_time);                              <*/
   /*> DEBUG_CONF  yLOG_value   ("x_epoch"    , x_epoch);                             <*/
   /*> DEBUG_CONF  yLOG_info    ("x_terse"    , x_terse);                             <*/
   /*> DEBUG_CONF  yLOG_info    ("x_written"  , x_written);                           <*/
   /*> ystrlcpy (s_tsae, x_full, LEN_TERSE);                                          <*/
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_pull               (cchar a_file [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "reading wave file...");
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
   /*> rc = DATA_purge ();                                                            <*/
   /*> DEBUG_DATA   yLOG_value   ("purge"     , rc);                                  <*/
   /*---(defense)------------------------*/
   DEBUG_DATA  yLOG_point   ("a_file"     , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA  yLOG_info    ("a_file"     , a_file);
   /*---(read all lines)-----------------*/
   rc = yPARSE_autoread (a_file, NULL, WAVE_handler);
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

/*> char                                                                              <* 
 *> WAVE_purge              (void)                                                    <* 
 *> {                                                                                 <* 
 *>    tWAVE      *x_cur       = NULL;                                                <* 
 *>    tWAVE      *x_next      = NULL;                                                <* 
 *>    x_cur = s_head;                                                                <* 
 *>    while (x_cur != NULL) {                                                        <* 
 *>       x_next = x_cur->s_next;                                                     <* 
 *>       WAVE_free (&x_cur);                                                         <* 
 *>       x_cur = x_next;                                                             <* 
 *>    }                                                                              <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

char
WAVE_purge_by_unit      (char *a_unit)
{
   tWAVE      *x_cur       = NULL;
   tWAVE      *x_next      = NULL;
   int         c           =    0;
   char        x_unit      [LEN_TITLE] = "";
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   ystrlcpy (x_unit, a_unit, LEN_TITLE);
   DEBUG_DATA   yLOG_complex ("x_unit"    , "%2d[%s]", strlen (x_unit), x_unit);
   x_cur = s_head;
   while (x_cur != NULL) {
      x_next = x_cur->s_next;
      DEBUG_DATA   yLOG_complex ("current"   , "%-10p, %-10p, %2d[%s], %s", x_cur, x_next, strlen (x_cur->w_unit), x_cur->w_unit, x_cur->w_desc);
      if (strcmp (x_unit, x_cur->w_unit) == 0) {
         WAVE__free (&x_cur);
         ++c;
      }
      x_cur = x_next;
   }
   if (c > 0)  --my.units;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_purge_by_path      (char *a_path)
{
   tWAVE      *x_cur       = NULL;
   tWAVE      *x_next      = NULL;
   int         c           =    0;
   char        x_path      [LEN_PATH] = "";
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   ystrlcpy (x_path, a_path, LEN_PATH);
   DEBUG_DATA   yLOG_info    ("x_path"    , x_path);
   x_cur = s_head;
   while (x_cur != NULL) {
      x_next = x_cur->s_next;
      /*> if (strcmp (x_path, x_cur->w_path) == 0) {                                  <* 
       *>    c += WAVE_purge_by_unit (x_cur->w_unit);                                 <* 
       *>    x_cur = x_next = s_head;                                                 <* 
       *> }                                                                           <*/
      x_cur = x_next;
   }
   if (c > 0)  --my.projs;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                    hooking and unhooking                     ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
WAVE__hook              (tWAVE *a_ref, tWAVE *a_cur)
{
   /*---(into wave list)-----------------*/
   /*> DEBUG_DATA   yLOG_point   ("head"      , s_head);                              <*/
   /*> DEBUG_DATA   yLOG_point   ("tail"      , s_tail);                              <*/
   /*> DEBUG_DATA   yLOG_snote   (__FUNCTION__);                                      <*/
   /*---(append normally)---------------*/
   if (a_ref == NULL) {
      if (s_head  == NULL) {
         /*> DEBUG_DATA   yLOG_note    ("first");                                     <*/
         s_head  = s_tail  = a_cur;
      } else {
         /*> DEBUG_DATA   yLOG_note    ("append");                                    <*/
         a_cur->s_prev   = s_tail;
         s_tail->s_next  = a_cur;
         s_tail          = a_cur;
      }
   }
   /*---(insert before ref)--------------*/
   else {
      if (a_ref->s_prev != NULL)   a_ref->s_prev->s_next = a_cur;
      else                         s_head                = a_cur;
      a_cur->s_prev   = a_ref->s_prev;
      a_cur->s_next   = a_ref;
      a_ref->s_prev   = a_cur;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
PROJ__hook              (tWAVE *a_ref, tWAVE *a_cur)
{
   /*---(into project list)--------------*/
   /*> DEBUG_DATA   yLOG_point   ("head"      , p_head);                              <*/
   /*> DEBUG_DATA   yLOG_point   ("tail"      , p_tail);                              <*/
   /*> DEBUG_DATA   yLOG_snote   (__FUNCTION__);                                      <*/
   /*---(append normally)---------------*/
   if (a_ref == NULL) {
      if (p_head  == NULL) {
         /*> DEBUG_DATA   yLOG_note    ("first");                                     <*/
         p_head  = p_tail  = a_cur;
      } else {
         /*> DEBUG_DATA   yLOG_note    ("append");                                    <*/
         a_cur->p_prev   = p_tail;
         p_tail->p_next  = a_cur;
         p_tail          = a_cur;
      }
   }
   /*---(insert before ref)--------------*/
   else {
      if (a_ref->p_prev != NULL)   a_ref->p_prev->p_next = a_cur;
      else                         p_head                = a_cur;
      a_cur->p_prev   = a_ref->p_prev;
      a_cur->p_next   = a_ref;
      a_ref->p_prev   = a_cur;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
WAVE__unhook            (tWAVE *a_cur)
{
   /*---(out of linked list)-------------*/
   /*> DEBUG_DATA   yLOG_spoint  (s_head);                                            <*/
   /*> DEBUG_DATA   yLOG_spoint  (s_tail);                                            <*/
   /*> DEBUG_DATA   yLOG_snote   (__FUNCTION__);                                      <*/
   if (a_cur->s_next != NULL)  a_cur->s_next->s_prev = a_cur->s_prev;
   else                        s_tail                = a_cur->s_prev;
   if (a_cur->s_prev != NULL)  a_cur->s_prev->s_next = a_cur->s_next;
   else                        s_head                = a_cur->s_next;
   /*---(complete)-----------------------*/
   return 0;
}

char
PROJ__unhook            (tWAVE *a_cur)
{
   /*---(out of linked list)-------------*/
   /*> DEBUG_DATA   yLOG_spoint  (p_head);                                            <*/
   /*> DEBUG_DATA   yLOG_spoint  (p_tail);                                            <*/
   /*> DEBUG_DATA   yLOG_snote   (__FUNCTION__);                                      <*/
   if (a_cur->p_next != NULL)  a_cur->p_next->p_prev = a_cur->p_prev;
   else                        p_tail                = a_cur->p_prev;
   if (a_cur->p_prev != NULL)  a_cur->p_prev->p_next = a_cur->p_next;
   else                        p_head                = a_cur->p_next;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      data maintainence                       ----===*/
/*====================------------------------------------====================*/
static void  o___DATA____________o () { return; }

char
WAVE__populate          (tWAVE *a_new, uchar a_wave, uchar a_stage, char *a_unit, char a_scrp, char *a_desc, char *a_key)
{
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(populate)-----------------------*/
   a_new->w_wave  = a_wave;
   a_new->w_stage = a_stage;
   ystrlcpy (a_new->w_unit, a_unit , LEN_LABEL);
   a_new->w_scrp  = a_scrp;
   ystrlcpy (a_new->w_desc, a_desc , LEN_LONG);
   /*---(sorting)------------------------*/
   sprintf (a_new->sort, "%-15.15s.%-20.20s.%02d", my.proj, a_unit, a_scrp);
   ystrlcpy (a_new->key , a_key  , LEN_HUND);
   /*---(reporting)----------------------*/
   RPTG_spread (a_wave, a_stage);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
WAVE_populate           (tWAVE *a_new, char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_key       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   /*> rc = WAVE__verify (a_wave, a_stage, a_unit, a_scrp, a_desc, x_key);            <*/
   DEBUG_DATA   yLOG_value   ("verify"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   rc = WAVE__populate (a_new, a_wave, a_stage, a_unit, a_scrp, a_desc, x_key);
   DEBUG_DATA   yLOG_value   ("populate"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_results            (tWAVE *x_wave, uchar a_resu, int a_cond, int a_test, int a_pass, int a_fail, int a_badd, int a_othr)
{
   x_wave->w_result  = a_resu;
   x_wave->w_ncond   = a_cond;
   x_wave->w_nstep   = a_test;
   x_wave->w_npass   = a_pass;
   x_wave->w_nfail   = a_fail;
   x_wave->w_nbadd   = a_badd;
   x_wave->w_nvoid   = a_othr;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     searching and finding                    ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

#define     IF_SCRP   (a_type == 's') ? 

char
WAVE__by_index           (char a_type, tWAVE **a_cur, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         c           =    0;
   tWAVE      *x_cur       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_cur);
   --rce;  if (a_cur == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   *a_cur = NULL;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_sint    (n);
   --rce;  if (n < 0 || n >= my.scrps) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   x_cur = IF_SCRP  s_head : p_head;
   while (x_cur != NULL) {
      if (n == c) {
         DEBUG_DATA   yLOG_snote   ("FOUND");
         *a_cur = x_cur;
         DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      x_cur = IF_SCRP x_cur->s_next : x_cur->p_next;
      ++c;
   }
   /*---(no match)-----------------------*/
   DEBUG_DATA   yLOG_snote   ("no match");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

int  WAVE_count     (void)                  { return  ySORT_count    (B_WAVE); }
char WAVE_by_index  (int n, tWAVE **a_cur)  { return  ySORT_by_index (B_WAVE, n, a_cur); }
char PROJ_by_index  (tWAVE **a_cur, int n)  { return  WAVE__by_index ('p', a_cur, n); }

char
WAVE__by_cursor          (char a_type, tWAVE **a_cur, char a_move)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         c           =    0;
   tWAVE      *x_cur       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_sint    (my.scrps);
   DEBUG_DATA   yLOG_spoint  (a_cur);
   --rce;  if (a_cur == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_cur = *a_cur;
   DEBUG_DATA   yLOG_spoint  (x_cur);
   --rce;  if (x_cur == NULL) {
      /*---(non-bounce)------------------*/
      if (strchr ("Ö´Õ", a_move) != NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(bounce types)----------------*/
      x_cur = IF_SCRP  s_head : p_head;
      DEBUG_DATA   yLOG_spoint  (x_cur);
      if (x_cur == NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(move)---------------------------*/
   DEBUG_DATA   yLOG_schar   (a_move);
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DHEAD :
      x_cur = IF_SCRP  s_head : p_head;
      break;
   case YDLST_PREV : case YDLST_DPREV :
      x_cur = IF_SCRP  x_cur->s_prev : x_cur->p_prev;
      break;
   case YDLST_CURR : case YDLST_DCURR :
      x_cur = x_cur;
      break;
   case YDLST_NEXT : case YDLST_DNEXT :
      x_cur = IF_SCRP  x_cur->s_next : x_cur->p_next;
      break;
   case YDLST_TAIL : case YDLST_DTAIL :
      x_cur = IF_SCRP  s_tail : p_tail;
      break;
   default  :
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check end)----------------------*/
   DEBUG_DATA   yLOG_spoint  (x_cur);
   --rce;  if (x_cur == NULL) {
      /*---(non-bounce)------------------*/
      if (strchr ("ºÖ´Õ»", a_move) != NULL) {
         *a_cur = x_cur;
      }
      /*---(all types)-------------------*/
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   *a_cur = x_cur;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char WAVE_by_cursor (tWAVE **a_cur, char a_move)  { return  WAVE__by_cursor ('s', a_cur, a_move); }
char PROJ_by_cursor (tWAVE **a_cur, char a_move)  { return  WAVE__by_cursor ('p', a_cur, a_move); }

char
WAVE__by_sortkey         (char a_type, tWAVE **a_cur, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         c           =    0;
   tWAVE      *x_cur       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_cur);
   --rce;  if (a_cur == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   *a_cur = NULL;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_name);
   /*---(walk)---------------------------*/
   x_cur = IF_SCRP s_head : p_head;
   while (x_cur != NULL) {
      if (x_cur->key != NULL && x_cur->sort != NULL) {
         if (strcmp (a_name, IF_SCRP x_cur->key : x_cur->sort) == 0) {
            DEBUG_DATA   yLOG_snote   ("FOUND");
            *a_cur = x_cur;
            DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
            return 0;
         }
      }
      x_cur = IF_SCRP x_cur->s_next : x_cur->p_next;
      ++c;
   }
   /*---(no match)-----------------------*/
   DEBUG_DATA   yLOG_snote   ("no match");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char WAVE_by_sortkey (tWAVE **a_cur, char *a_sortkey)  { return  WAVE__by_sortkey ('s', a_cur, a_sortkey); }
char PROJ_by_sortkey (tWAVE **a_cur, char *a_sortkey)  { return  WAVE__by_sortkey ('p', a_cur, a_sortkey); }



/*====================------------------------------------====================*/
/*===----                       data import                            ----===*/
/*====================------------------------------------====================*/
static void  o___IMPORT__________o () { return; }

char
WAVE_parse              (char *a_recd, char a_call)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   int         i           =    0;
   char       *p           = NULL;
   char       *q           = "";
   char       *r           = NULL;
   char        t           [LEN_RECD]  = "";
   tWAVE      *x_wave      = NULL;
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   s_wave  = '-';
   s_stage =  0;
   ystrlcpy (s_unit , "", LEN_LABEL);
   s_scrp  =  0;
   ystrlcpy (s_desc , "", LEN_LONG);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_info    ("a_recd"    , a_recd);
   c = ystrldcnt (a_recd, '', LEN_RECD);
   DEBUG_ENVI   yLOG_value   ("c"         , c);
   --rce;  if (c < 4) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (t, a_recd, LEN_RECD);
   p = strtok_r (t, q, &r);
   c = 0;
   /*---(walk fields)--------------------*/
   --rce;  for (i = 0; i < 5; ++i) {
      DEBUG_DATA   yLOG_point   ("p"         , p);
      if (p == NULL) {
         DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ystrltrim (p, ySTR_BOTH, LEN_RECD);
      DEBUG_DATA   yLOG_info    ("p"         , p);
      /*---(handle fields)---------------*/
      switch (i) {
      case OURU_WAVE  :
         s_wave  = p [0];
         DEBUG_DATA   yLOG_char    ("s_wave"    , s_wave);
         break;
      case OURU_STAGE :
         s_stage = p [0];
         DEBUG_DATA   yLOG_char    ("s_stage"   , s_stage);
         break;
      case OURU_UNIT  :
         ystrlcpy (s_unit, p, LEN_LABEL);
         DEBUG_DATA   yLOG_info    ("s_unit"    , s_unit);
         break;
      case OURU_SCRP  :
         s_scrp  = atoi (p);
         DEBUG_DATA   yLOG_char    ("s_scrp"    , s_scrp);
         break;
      case OURU_DESC  :
         ystrlcpy (s_desc, p, LEN_LONG);
         DEBUG_DATA   yLOG_info    ("s_desc"    , s_desc);
         break;
      }
      /*---(next record)-----------------*/
      p = strtok_r (NULL  , q, &r);
      ++c;
   } 
   /*---(call new)-----------------------*/
   DEBUG_ENVI   yLOG_value   ("c"         , c);
   DEBUG_ENVI   yLOG_char    ("a_call"    , a_call);
   if (a_call == 'y') {
      rc = WAVE_new      (&x_wave);
      DEBUG_ENVI   yLOG_value   ("new"       , rc);
      rc = WAVE_populate (x_wave, s_wave, s_stage, s_unit, s_scrp, s_desc);
      DEBUG_ENVI   yLOG_value   ("populate"  , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_read               (char *a_name, char a_call)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   FILE       *f           = NULL;
   int         l           =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_info    ("a_name"    , a_name);
   /*---(open to read)-------------------*/
   f = fopen (a_name, "rt");
   DEBUG_ENVI   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk entries)-------------------*/
   --rce; while (1) {
      fgets (s_recd, LEN_RECD, f);
      if (feof (f))  {
         DEBUG_ENVI   yLOG_note    ("end-of-file");
         break;
      }
      if (s_recd [0] == '#' )  continue;
      if (s_recd [0] == '\0')  continue;
      /*---(trim newline)----------------*/
      l = strlen (s_recd);
      if (l <= 0)              continue;
      s_recd [--l] = '\0';
      /*---(call parse)------------------*/
      ++c;
      if (a_call == 'y')  WAVE_parse (s_recd, a_call);
   }
   /*---(close reading)------------------*/
   rc = fclose (f);
   --rce;  if (rc != 0) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update globals)-----------------*/
   ++my.units;
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_inventory          (char *a_path, char a_call)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_entry     = NULL;          /* directory entry                */
   char        x_name      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (my.path, a_path, LEN_PATH);
   DEBUG_ENVI   yLOG_info    ("a_path"    , a_path);
   /*---(get the home)-------------------*/
   rc = ystrlproj (my.path, my.proj);
   DEBUG_DATA   yLOG_value   ("strlhere"  , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("my.path"   , my.path);
   DEBUG_DATA   yLOG_info    ("my.proj"   , my.proj);
   /*---(open directory)-----------------*/
   x_dir = opendir (a_path);
   DEBUG_ENVI   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk entries)-------------------*/
   --rce; while (1) {
      /*---(read)------------------------*/
      x_entry = readdir (x_dir);
      DEBUG_ENVI   yLOG_point   ("X_ENTRY"   , x_entry);
      if (x_entry == NULL)                            break;
      /*---(filter)----------------------*/
      if (x_entry->d_name   == NULL)                  continue;
      DEBUG_ENVI   yLOG_info    ("d_name"    , x_entry->d_name);
      if (strcmp (x_entry->d_name, "."    ) == 0)     continue;
      if (strcmp (x_entry->d_name, ".."   ) == 0)     continue;
      if (strstr (x_entry->d_name, ".wave") == NULL)  continue;
      /*---(process)---------------------*/
      ++c;
      sprintf (x_name, "%s/%s", a_path, x_entry->d_name);
      /*> printf ("%s\n", x_name);                                                    <*/
      if (a_call == 'y')  WAVE_read (x_name, a_call);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   closedir (x_dir);
   /*---(sort)---------------------------*/
   /*> WAVE_gnome ();                                                                 <*/
   /*> rc = ySORT_troll (YSORT_NONE, YSORT_ASCEND, &(a_parent->c_head), &(a_parent->c_tail));   <*/
   WAVE_gnome ();
   /*---(update globals)-----------------*/
   ++my.projs;
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_here               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(get the home)-------------------*/
   rc = ystrlhome (my.path);
   DEBUG_DATA   yLOG_value   ("strlhere"  , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("my.path"   , my.path);
   /*---(clear existing)-----------------*/
   WAVE_purge_by_path (my.path);
   /*---(run inventory)------------------*/
   c = WAVE_inventory (my.path, 'y');
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                          sorting                             ----===*/
/*====================------------------------------------====================*/
static void  o___SORT____________o () { return; }

/*> char* WAVE__key   (tWAVE *a_cur) { return (a_cur != NULL) ? a_cur->key  : ""; }   <*/
char* PROJ__key   (tWAVE *a_cur) { return (a_cur != NULL) ? a_cur->sort : ""; }

char
WAVE_hints              (void)
{
   char        rc          =    0;
   int         p           =   -1;
   int         u           =   -1;
   int         s           =   -1;
   tWAVE      *x_prv       = NULL;
   tWAVE      *x_cur       = NULL;
   rc = PROJ_by_cursor (&x_cur, '[');
   /*> while (rc >= 0 && x_cur != NULL) {                                                                           <* 
    *>    if (x_prv == NULL || strcmp (x_prv->w_proj, x_cur->w_proj) != 0) ystrlhint (++p, "99", x_cur->w_phint);   <* 
    *>    else                                                         ystrlhint (p  , "99", x_cur->w_phint);       <* 
    *>    if (x_prv == NULL || strcmp (x_prv->w_unit, x_cur->w_unit) != 0) ystrlhint (++u, "uu", x_cur->w_uhint);   <* 
    *>    else                                                         ystrlhint (u  , "uu", x_cur->w_uhint);       <* 
    *>    ystrlhint (++s, "ll", x_cur->w_shint);                                                                    <* 
    *>    /+> printf ("%s\n", x_cur->sort);                                               <+/                       <* 
    *>    x_prv = x_cur;                                                                                            <* 
    *>    rc = PROJ_by_cursor (&x_cur, '>');                                                                        <* 
    *> }                                                                                                            <*/
   return 0;
}

char
WAVE_gnome              (void)
{
   ySORT_pixie  (WAVE_by_cursor, WAVE__key, WAVE__unhook, WAVE__hook);
   ySORT_pixie  (PROJ_by_cursor, PROJ__key, PROJ__unhook, PROJ__hook);
   WAVE_hints ();
   return 0;
}



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
   else if (strcmp (a_question, "project"       )  == 0) {
      PROJ_by_index (&x_cur, n);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "PROJ entry  (%2d) : -  -   -[]                       -   -[]", n);
      } else {
         if (x_cur->w_unit != NULL)  sprintf (s, "%2d[%.20s]", strlen (x_cur->w_unit), x_cur->w_unit);
         if (x_cur->w_desc != NULL)  sprintf (t, "%2d[%.40s]", strlen (x_cur->w_desc), x_cur->w_desc);
         snprintf (my.unit_answer, LEN_RECD, "PROJ entry  (%2d) : %c  %c  %-24.24s  %2d  %s",
               n, x_cur->w_wave, x_cur->w_stage, s, x_cur->w_scrp, t);
      }
   }
   else if (strcmp (a_question, "sortkey"       )  == 0) {
      WAVE_by_index (n, &x_cur);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "WAVE sortkey(%2d) :  -[]                                 -[]", n);
      } else {
         if (x_cur->key  != NULL)  sprintf (s, "%2d[%.30s]", strlen (x_cur->key ), x_cur->key );
         if (x_cur->sort != NULL)  sprintf (t, "%2d[%.40s]", strlen (x_cur->sort), x_cur->sort);
         snprintf (my.unit_answer, LEN_RECD, "WAVE sortkey(%2d) : %-34.34s  %s",
               n, s, t);
      }
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}



