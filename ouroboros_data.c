/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



char
DATA_file_type          (char a_proj [LEN_TITLE], char a_file [LEN_HUND], char *r_type)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         l           =    0;
   char        x_keep      =  'y';
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_type != NULL)  *r_type = '-';
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_proj"     , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_proj"     , a_proj);
   --rce;  if (a_proj [0] == '\0') {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_point   ("a_file"     , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_file"     , a_file);
   --rce;  if (a_file [0] == '\0') {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   l = strlen (a_file);
   DEBUG_CONF  yLOG_value   ("l"          , l);
   x_keep == 'y';
   /*---(simple)-------------------------*/
   if      (strcmp  (a_file, "."               ) == 0)   x_keep = '-';
   else if (strcmp  (a_file, ".."              ) == 0)   x_keep = '-';
   else if (strncmp (a_file, "."       , 1     ) == 0)   x_keep = '-';
   else if (strcmp  (a_file + l - 1, "~"       ) == 0)   x_keep = '-';
   DEBUG_CONF  yLOG_char    ("simple"     , x_keep);
   if (x_keep == '-') {
      DEBUG_PROG  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(specifically avoided)-----------*/
   /*> if      (strncmp (a_file, "unit_daemon" , 11) == 0)   x_keep = '-';            <* 
    *> else if (strncmp (a_file, "unit_badrc"  , 10) == 0)   x_keep = '-';            <* 
    *> DEBUG_CONF  yLOG_char    ("simple"     , x_keep);                              <* 
    *> if (x_keep == '-') {                                                           <* 
    *>    DEBUG_PROG  yLOG_exit    (__FUNCTION__);                                    <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*---(global names)----------------*/
   x_type == '-';
   if      (strcmp  (a_file, "Makefile"       ) == 0)    x_type = 'M';
   else if (strcmp  (a_file, "master.h"       ) == 0)    x_type = 'h';
   /*---(prefixed names)--------------*/
   if (strncmp (a_file, a_proj, strlen (a_proj)) == 0) {
      if      (l >= 6 && strcmp (a_file + l - 5, ".wave"  ) == 0)  x_type = 'w';
      else if (l >= 6 && strcmp (a_file + l - 5, ".unit"  ) == 0)  x_type = 'u';
      else if (l >= 7 && strcmp (a_file + l - 6, ".munit" ) == 0)  x_type = 'm';
      else if (l >= 3 && strcmp (a_file + l - 2, ".h"     ) == 0)  x_type = 'h';
      else if (l >= 3 && strcmp (a_file + l - 7, "_priv.h") == 0)  x_type = 'h';
      else if (l >= 3 && strcmp (a_file + l - 7, "_solo.h") == 0)  x_type = 'h';
      else if (l >= 3 && strcmp (a_file + l - 7, "_uver.h") == 0)  x_type = 'h';
      else if (l >= 8 && strcmp (a_file + l - 7, "_unit.c") == 0)  ;
      else if (l >= 3 && strcmp (a_file + l - 2, ".c"     ) == 0)  x_type = 'c';
   }
   DEBUG_CONF  yLOG_char    ("x_type"     , x_type);
   if (x_type == '-') {
      DEBUG_DATA   yLOG_note    ("not a selected type, skipping");
      DEBUG_PROG  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(save-back)----------------------*/
   if (r_type != NULL)  *r_type = x_type;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}


/*====================------------------------------------====================*/
/*===----                      pulling from database                   ----===*/
/*====================------------------------------------====================*/
static void  o___PULL____________o () { return; }

char
INCL_handler            (int n, uchar a_verb [LEN_TERSE], char a_exist, void *a_handler)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_deps      [LEN_RECD]  = "";
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
   --rce;  if (strcmp (a_verb, "DEPEND") != 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = yPARSE_ready (&c);
   DEBUG_CONF  yLOG_value   ("rc"         , rc);
   DEBUG_CONF  yLOG_value   ("c"          , c);
   /*---(read details)-------------------*/
   rc = yPARSE_scanf (a_verb, "R"  , x_deps);
   DEBUG_CONF  yLOG_value   ("scanf"      , rc);
   if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update depends)-----------------*/
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 0;
}


