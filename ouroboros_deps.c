/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



/*
 * file        : ouroboros_deps.c
 * subject     : links two nodes together, or a header and a node
 *
 * terms       : source     beginning of the edge (as 20 char text string)
 *               target     ending of the edge    (as 20 char text string)
 *               deps       new sources required for a node
 *               cumd       cumulative source required for a node
 *               miss       nodes that need creating for a node (not in cum)
 *
 *
 */



/*====================------------------------------------====================*/
/*===----                     new dependencies                         ----===*/
/*====================------------------------------------====================*/
static void  o___SINGLE__________o () { return; }

char
DEPS__defense           (char a_source [LEN_LABEL], char a_target [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL) {
      DEBUG_PROG   yLOG_note    ("null dependency source");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_source"  , a_source);
   --rce;  if (a_source [0] == '\0') {
      DEBUG_PROG   yLOG_note    ("empty dependency source");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_target"  , a_target);
   --rce;  if (a_target == NULL) {
      DEBUG_PROG   yLOG_note    ("null dependency target");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_target"  , a_target);
   --rce;  if (a_target [0] == '\0') {
      DEBUG_PROG   yLOG_note    ("empty dependency target");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strcmp (a_source, a_target) == 0) {
      DEBUG_PROG   yLOG_note    ("circular dependency requested");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DEPS__ends              (char a_source [LEN_LABEL], char a_target [LEN_LABEL], char a_force, int *r_beg, tNODE **r_src, tNODE **r_trg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_beg       =   -1;
   tNODE      *x_src       = NULL;
   tNODE      *x_trg       = NULL;
   char        x_draw      =  '-';
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_beg  != NULL)  *r_beg = -1;
   if (r_src  != NULL)  *r_src = NULL;
   if (r_trg  != NULL)  *r_trg = NULL;
   /*---(check for target)---------------*/
   rc = NODE_by_name (a_target, &x_trg);
   DEBUG_PROG   yLOG_complex ("trg"       , "%4d, %p", rc, x_trg);
   --rce;  if (rc < 0 || x_trg == NULL) {
      DEBUG_PROG   yLOG_char    ("a_force"   , a_force);
      if (a_force != 'y') {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = NODE_add (a_target, &x_trg);
      DEBUG_PROG   yLOG_complex ("force"     , "%4d, %p", rc, x_trg);
      if (rc < 0 || x_trg == NULL) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check for source)---------------*/
   x_beg = INCL_by_name (a_source);
   DEBUG_PROG   yLOG_value   ("x_beg"     , x_beg);
   rc    = INCL_data (x_beg, NULL, NULL, NULL, NULL, NULL, &x_draw, NULL, NULL);
   DEBUG_PROG   yLOG_char    ("x_draw"    , x_draw);
   /*---(invisible include)--------------*/
   --rce;  if (x_beg >= 0 && strchr ("yv", x_draw) == NULL) {
      DEBUG_PROG   yLOG_note    ("a_source is an invisible include file");
   }
   /*---(visible include)----------------*/
   else {
      if (x_beg >= 0)  {
         DEBUG_PROG   yLOG_note    ("a_source is a new/existing node");
         rc = NODE_by_name (a_source, &x_src);
         DEBUG_PROG   yLOG_complex ("src"       , "%4d, %p", rc, x_src);
      } else {
         DEBUG_PROG   yLOG_note    ("a_source is a non-existant include, so create");
      }
      if (x_src != NULL) {
         DEBUG_PROG   yLOG_note    ("exists, already created");
      } else {
         rc = NODE_add (a_source, &x_src);
         DEBUG_PROG   yLOG_complex ("create"    , "%4d, %p", rc, x_src);
         if (rc < 0 || x_src == NULL) {
            DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
   }
   /*---(save-back)----------------------*/
   if (r_beg  != NULL)  *r_beg = x_beg;
   if (r_src  != NULL)  *r_src = x_src;
   if (r_trg  != NULL)  *r_trg = x_trg;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DEPS__list              (char a_source [LEN_LABEL], tNODE *a_trg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_HUND]  = "";
   char       *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(prepare list update)------------*/
   sprintf (t, ",%s,", a_source);
   DEBUG_PROG   yLOG_info    ("t"         , t);
   x_list = a_trg->n_deps;
   DEBUG_PROG   yLOG_info    ("x_list"    , x_list);
   /*---(check for dup)------------------*/
   if (strstr (x_list, t) != NULL) {
      DEBUG_PROG   yLOG_note    ("already in list, just a duplicate");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 2;
   }
   /*---(append new)---------------------*/
   switch (x_list [0]) {
   case '\0' :
   case '´'  :
      ystrlcpy (x_list   , ",", LEN_RECD);
      break;
   }
   ystrlcat (x_list, t + 1, LEN_RECD);
   DEBUG_PROG   yLOG_info    ("x_list"    , x_list);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DEPS__add               (char a_source [LEN_LABEL], char a_target [LEN_LABEL], char a_force)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *x_list      = NULL;
   int         x_beg       =   -1;
   int         x_end       =   -1;
   char        t           [LEN_HUND]  = "";
   tNODE      *x_src       = NULL;
   tNODE      *x_trg       = NULL;
   char        x_draw      =  '-';
   char        x_zeno      =  '-';
   tNODE      *x_mak       = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = DEPS__defense (a_source, a_target);
   DEBUG_PROG   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(identify ends)------------------*/
   rc = DEPS__ends    (a_source, a_target, a_force, &x_beg, &x_src, &x_trg);
   DEBUG_PROG   yLOG_value   ("ends"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare list update)------------*/
   rc = DEPS__list (a_source, x_trg);
   DEBUG_PROG   yLOG_value   ("list"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (rc == 2) {
      DEBUG_PROG   yLOG_note    ("duplicate dependency");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 2;
   }
   /*---(increment counters)-------------*/
   if (x_beg >= 0)   rc = INCL_add (x_beg, 0, NULL);
   else              rc = INCL_add (-1, DEPWTF, a_source);
   DEBUG_PROG   yLOG_value   ("incl_add"  , rc);
   /*---(decide whether to draw)---------*/
   if (x_src == NULL) {
      DEBUG_PROG   yLOG_note    ("invisible include tie, no edge");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(create edge)--------------------*/
   if (x_beg >= 0)  INCL_data (x_beg, NULL, NULL, NULL, NULL, NULL, &x_draw, NULL, &x_zeno);
   else             x_draw  = 'y';
   DEBUG_PROG   yLOG_char    ("x_draw"    , x_draw);
   rc = EDGE_add (x_src, x_trg, x_draw, NULL);
   DEBUG_PROG   yLOG_value   ("edge"      , rc);
   /*---(check for uver)-----------------*/
   DEBUG_PROG   yLOG_char    ("x_zeno"    , x_zeno);
   if (x_zeno == 'y') {
      DEBUG_PROG   yLOG_note    ("add zenodotus to the header");
      rc = NODE_add ("zenodotus", &x_mak);
      DEBUG_PROG   yLOG_value   ("node"      , rc);
      if (rc < 0 || x_mak == NULL) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = DEPS__list ("zenodotus", x_src);
      DEBUG_PROG   yLOG_value   ("list"      , rc);
      if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = EDGE_add (x_mak, x_src, 'v', NULL);
      DEBUG_PROG   yLOG_value   ("edge"      , rc);
      if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 3;
}

char DEPS_add         (char a_source [LEN_LABEL], char a_target [LEN_LABEL]) { return DEPS__add (a_source, a_target, '-'); }
char DEPS_force       (char a_source [LEN_LABEL], char a_target [LEN_LABEL]) { return DEPS__add (a_source, a_target, 'y'); }



/*====================------------------------------------====================*/
/*===----                        dependency lists                      ----===*/
/*====================------------------------------------====================*/
static void  o___LISTS___________o () { return; }

char
DEPS_merge              (char a_deps [LEN_RECD], char r_cumd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *p           = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   char        x_deps      [LEN_RECD]  = "";
   char        s           [LEN_TITLE] = "";
   char        c           =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_deps == NULL)             return rce;
   --rce;  if (r_cumd == NULL)             return rce;
   /*---(quick out)----------------------*/
   if (strcmp (a_deps, "")  == 0)  return 0;
   if (strcmp (a_deps, "´") == 0)  return 0;
   if (strcmp (r_cumd, "")  == 0)  strcpy (r_cumd, ",");
   if (strcmp (r_cumd, "´") == 0)  strcpy (r_cumd, ",");
   /*---(merge up)-----------------------*/
   ystrlcpy (x_deps, a_deps, LEN_RECD);
   p = strtok_r (x_deps, q, &r);
   while (p != NULL) {
      /*---(check)-----------------------*/
      sprintf (s, ",%s,", p);
      if (strstr (r_cumd, s) == NULL) {
         ystrlcat (r_cumd, s + 1, LEN_RECD);
         ++c;
      }
      /*---(next)------------------------*/
      p = strtok_r (NULL  , q, &r);
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   return c;
}

char
DEPS_missing            (char a_deps [LEN_RECD], char a_cumd [LEN_RECD], char a_block [LEN_RECD], char r_miss [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   char        x_deps      [LEN_RECD]  = "";
   char        x_cumd      [LEN_RECD]  = "";
   char        s           [LEN_TITLE] = "";
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_miss != NULL)  strcpy (r_miss, "");
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_deps"    , a_deps);
   --rce;  if (a_deps == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_cumd"    , a_cumd);
   --rce;  if (a_cumd == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_block"   , a_block);
   --rce;  if (a_block == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("r_miss"    , r_miss);
   --rce;  if (r_miss == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (x_cumd, a_cumd, LEN_RECD);
   DEBUG_PROG   yLOG_point   ("x_cumd"    , x_cumd);
   rc = DEPS_merge (a_block, x_cumd);
   DEBUG_PROG   yLOG_value   ("merge"     , rc);
   DEBUG_PROG   yLOG_point   ("x_cumd"    , x_cumd);
   ystrlcpy (x_deps, a_deps, LEN_RECD);
   p = strtok_r (x_deps, q, &r);
   /*---(merge up)-----------------------*/
   DEBUG_PROG   yLOG_point   ("head"      , p);
   while (p != NULL) {
      DEBUG_PROG   yLOG_info    ("p"         , p);
      /*---(check)-----------------------*/
      if (p [0] == 'y' || strcmp (p, "koios") == 0 || strcmp (p, "zenodotus") == 0) {
         if (strcmp (p, "yVIHUB_solo") != 0) {
            sprintf (s, ",%s,", p);
            DEBUG_PROG   yLOG_info    ("s"         , s);
            if (strstr (x_cumd, s) == NULL) {
               DEBUG_PROG   yLOG_note    ("add as miss");
               if (strcmp (r_miss, "")  == 0)  strcpy (r_miss, ",");
               if (strcmp (r_miss, "´") == 0)  strcpy (r_miss, ",");
               ystrlcat (r_miss, s + 1, LEN_RECD);
               ++c;
            } else {
               DEBUG_PROG   yLOG_note    ("already exists");
            }
         } else {
            DEBUG_PROG   yLOG_note    ("skipping, yVIHUB_solo is not reportable");
         }
      } else {
         DEBUG_PROG   yLOG_note    ("skipping, not koios, zenodotus, or my libs");
      }
      /*---(next)------------------------*/
      p = strtok_r (NULL  , q, &r);
      DEBUG_PROG   yLOG_point   ("next"      , p);
      /*---(done)------------------------*/
   }
   DEBUG_PROG   yLOG_info    ("r_miss"    , r_miss);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                     pulling from solution                    ----===*/
/*====================------------------------------------====================*/
static void  o___GATHER__________o () { return; }

char
DEPS__layer             (int n)
{
   tEDGE_OLD  *x_pred      = NULL;
   char        c           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(mark)------------------------*/
   DEBUG_PROG   yLOG_value   ("n"         , n);
   strcpy (g_nodes [n].n_cumd, "");
   DEBUG_PROG   yLOG_info    ("n_name"    , g_nodes [n].n_name);
   /*> printf ("SOLVING     : %s¦", g_nodes [n].n_name);                             <*/
   /*---(fill successors)-------------*/
   x_pred = g_nodes [n].n_hpred;
   DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
   while (x_pred != NULL) {
      DEBUG_PROG   yLOG_info    ("n_cpred"    , x_pred->e_beg->n_name);
      DEPS_merge (x_pred->e_beg->n_cumd, g_nodes [n].n_cumd);
      ++c;
      x_pred = x_pred->e_pnext;
      DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
   }
   DEBUG_PROG   yLOG_value   ("c"         , c);
   /*> printf ("  PREDS     : %4då%sæ¦", strlen (g_nodes [n].n_cumd), g_nodes [n].n_cumd);   <*/
   /*> printf ("  DEPS      : %4då%sæ¦", strlen (g_nodes [n].n_deps), g_nodes [n].n_deps);   <*/
   DEPS_missing (g_nodes [n].n_deps, g_nodes [n].n_cumd, g_deps_block, g_nodes [n].n_miss);
   /*> printf ("  MISS      : %4då%sæ¦", strlen (g_nodes [n].n_miss), g_nodes [n].n_miss);   <*/
   DEPS_merge   (g_nodes [n].n_miss, g_nodes [n].n_cumd);
   /*> printf ("  CUMPD     : %4då%sæ¦", strlen (g_nodes [n].n_cumd), g_nodes [n].n_cumd);   <*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
}

char
DEPS_gather             (void)
{
   char        rc          =    0;
   int         i           =    0;
   char        x_lvl       =    0;
   int         c           =    0;
   tEDGE_OLD  *x_pred      = NULL;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) {
      DEBUG_PROG   yLOG_value   ("x_lvl"     , x_lvl);
      c = 0;
      for (i = 0; i <  g_nnode; ++i) {
         if (g_nodes [i].n_level != x_lvl)  continue;
         DEBUG_PROG   yLOG_complex ("node"      , "%3d, %s", i, g_nodes [i].n_name);
         DEPS__layer (i);
         ++c;
      }
   }
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        reporting                             ----===*/
/*====================------------------------------------====================*/
static void  o___REPORT__________o () { return; }

char
DEPS_dump               (void)
{
   int         i           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_value   ("g_nnode"   , g_nnode);
   for (i = 0; i <  g_nnode; ++i) {
      printf ("%3d  %-25.25s  %s¦", i, g_nodes [i].n_name, g_nodes [i].n_deps);
   }
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


