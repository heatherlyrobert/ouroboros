/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



char
YUNIT_gather            (char a_proj [LEN_TITLE], char a_recd [LEN_RECD], int a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           =    0;
   char       *q           =  "§";
   char       *r           =    0;
   char        t           [LEN_TITLE] = "";
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
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
   ystrlcpy  (t, p, LEN_TITLE);
   ystrltrim (t, ySTR_BOTH, LEN_TITLE);
   /*---(find include)----------------*/
   DEBUG_DATA   yLOG_info    ("t"         , t);
   if (strcmp (t, "incl"   ) != 0) {
      DEBUG_DATA   yLOG_note    ("not an include line, continue");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(find header)-----------------*/
   p = strtok_r (NULL  , q, &r);
   DEBUG_DATA   yLOG_info    ("p"         , p);
   if (p == NULL) {
      DEBUG_DATA   yLOG_note    ("nothing to do with line, continue");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   ystrlcpy  (t, p, LEN_TITLE);
   ystrltrim (t, ySTR_BOTH, LEN_TITLE);
   if (t [0] == 'v') {
      p = strtok_r (NULL  , q, &r);
      if (p == NULL) {
         DEBUG_DATA   yLOG_note    ("nothing to do with line, continue");
         DEBUG_DATA   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   p = strtok_r (NULL  , q, &r);
   DEBUG_DATA   yLOG_point   ("p"         , p);
   if (p == NULL) {
      DEBUG_DATA   yLOG_note    ("nothing to do with line, continue");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   ystrlcpy  (t, p, LEN_TITLE);
   ystrltrim (t, ySTR_BOTH, LEN_TITLE);
   l = strlen (t);
   if (t > 2)  t [l - 2] = '\0';
   DEBUG_DATA   yLOG_info    ("t"         , t);
   /*---(find zeno_make)--------------*/
   if (strncmp (t, a_proj, strlen (a_proj)) == 0) {
      DEBUG_DATA   yLOG_note    ("private header, not to attach");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle)----------------------*/
   /*> rc = INCL_add_by_name (t, a_end);                                              <*/
   rc = DEPS_add (t, a_proj);
   DEBUG_DATA   yLOG_value   ("add"       , rc);
   /*> rc = GRAPH_edge_virt ("koios", a_end);                                         <*/
   /*> rc = INCL_add_by_name ("koios", a_end);                                        <*/
   rc = DEPS_add ("koios", a_proj);
   DEBUG_DATA   yLOG_value   ("koios"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 1;
}


