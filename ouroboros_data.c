/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"




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


