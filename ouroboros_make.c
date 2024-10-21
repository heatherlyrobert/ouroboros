/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"

/*> int a_end                                                                         <*/

char
MAKE_gather             (char a_proj [LEN_LABEL], char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           =    0;
   char       *q           =  " ";
   char       *r           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce; if (a_proj == NULL || a_proj [0] == '\0') {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_proj"    , a_proj);
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce; if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_recd"    , a_recd);
   l = strlen (a_recd);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   --rce; if (l <= 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (x_recd, a_recd, LEN_RECD);
   if (x_recd [l - 1] == '\n')  x_recd [--l] = '\0';
   DEBUG_DATA   yLOG_info    ("x_recd"    , x_recd);
   /*---(find break)------------------*/
   p = strtok_r (x_recd, q, &r);
   DEBUG_DATA   yLOG_point   ("p"         , p);
   if (p == NULL) {
      DEBUG_DATA   yLOG_note    ("nothing to do with line, continue");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(find include)----------------*/
   DEBUG_DATA   yLOG_info    ("p"         , p);
   if (strcmp (p, "include") != 0) {
      DEBUG_DATA   yLOG_note    ("not an include line, continue");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(find zeno_make)--------------*/
   p = strtok_r (NULL, q, &r);
   DEBUG_DATA   yLOG_point   ("p"         , p);
   if (p == NULL) {
      DEBUG_DATA   yLOG_note    ("include without content, continue");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_DATA   yLOG_info    ("p"         , p);
   if (strcmp (p, "/usr/local/sbin/zeno_make") != 0) {
      DEBUG_DATA   yLOG_note    ("not specifically a zeno_make include line, continue");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle)----------------------*/
   rc = DEPS_force ("zenodotus", a_proj);
   DEBUG_DATA   yLOG_value   ("add"       , rc);
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 1;
}



