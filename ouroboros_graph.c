/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"


/*
 *   I.    FOUNDATIONAL
 *         purpose is unit testing, logging, tracing, and debugging
 *         includes two other core libraries at end
 *         ends with ySTR and yENV
 *         presently 7 columns by 6 rows
 *
 *
 *
 *
 */



tNODE   g_nodes   [MAX_NODE];
int     g_nnode     =  0;
int     g_ready     =  0;


tEDGE   g_edges   [MAX_EDGE];
int     g_nedge     =  0;
char    g_maxlvl    =  0;


/*====================------------------------------------====================*/
/*===----                      program level                           ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
GRAPH_purge             (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_EDGE; ++i) {
      /*---(ends)--------------*/
      g_edges [i].e_nbeg     = 0;
      g_edges [i].e_beg      = NULL;
      g_edges [i].e_filled   = '-';
      g_edges [i].e_nend     = 0;
      g_edges [i].e_end      = NULL;
      /*---(working)-----------*/
      g_edges [i].e_used     = '-';
      /*---(beg-point list)----*/
      g_edges [i].e_pprev    = NULL;
      g_edges [i].e_pnext    = NULL;
      /*---(end-point list)----*/
      g_edges [i].e_sprev    = NULL;
      g_edges [i].e_snext    = NULL;
      /*---(done)--------------*/
   }
   g_nedge = 0;
   for (i = 0; i < MAX_NODE; ++i) {
      /*---(data)--------------*/
      g_nodes [i].n_name [0] = '\0';
      g_nodes [i].n_deps [0] = '\0';
      g_nodes [i].n_cumd [0] = '\0';
      g_nodes [i].n_miss [0] = '\0';
      g_nodes [i].n_focus    = '-';
      /*---(working)-----------*/
      g_nodes [i].n_level    = -1;
      g_nodes [i].n_row      = -1;
      /*---(predecessors)------*/
      g_nodes [i].n_pred     = 0;
      g_nodes [i].n_phead    = NULL;
      g_nodes [i].n_ptail    = NULL;
      g_nodes [i].n_filled   = 0;
      g_nodes [i].n_ready    = '-';
      /*---(successors)--------*/
      g_nodes [i].n_succ     = 0;
      g_nodes [i].n_shead    = NULL;
      g_nodes [i].n_stail    = NULL;
      /*---(done)--------------*/
   }
   g_nnode = 0;
   g_ready = 0;
   return 0;
}

char
GRAPH_init              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(purge)--------------------------*/
   rc = GRAPH_purge ();
   DEBUG_PROG   yLOG_value   ("purge"     , rc);
   /*---(set up drawing)-----------------*/
   yASCII_displayer (yASCII_print);
   /*---(prepare)------------------------*/
   GRAPH_add_node ("zenodotus");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       node handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___NODES___________o () { return; }

int
GRAPH_by_name           (char a_name [LEN_TITLE])
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_name == NULL)            return rce;
   --rce;  if (strcmp (a_name, "") == 0)  return rce;
   for (i = 0; i < g_nnode; ++i) {
      if (strcmp (g_nodes [i].n_name, a_name) != 0)  continue;
      return i;
   }
   return --rce;
}

int
GRAPH_add_node          (char a_name [LEN_TITLE])
{
   char        rce         =  -10;
   int         n           =    0;
   --rce;  if (a_name == NULL)            return rce;
   --rce;  if (strcmp (a_name, "") == 0)  return rce;
   /*---(filter)-------------------------*/
   if (strcmp (a_name, "yVIHUB_solo") == 0) {
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   n = GRAPH_by_name (a_name);
   if (n < 0) {
      ystrlcpy (g_nodes [g_nnode].n_name, a_name, LEN_TITLE);
      n = g_nnode;
      ++g_nnode;
   }
   if (strcmp (a_name, "zenodotus") != 0) {
      INCL_add_by_name (n, "zenodotus");
      GRAPH_add_edge ("zenodotus", n);
   }
   return n;
}

char
GRAPH_cum_deps          (void)
{
   int         i           =    0;
   char        x_lvl       =    0;
   int         c           =    0;
   tEDGE      *x_pred      = NULL;
   char        x_cumd      [LEN_RECD]  = "";
   for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) {
      for (i = 0; i <  g_nnode; ++i) {
         if (g_nodes [i].n_level != x_lvl)  continue;
         printf ("%3d  %3d  %-25.25s   %3dp  ", i, g_nodes [i].n_level, g_nodes [i].n_name, g_nodes [i].n_pred);
         if (g_nodes [i].n_pred > 0)  {
            x_pred = g_nodes [i].n_phead;
            while (x_pred != NULL) {
               printf (" %-15.15s", (x_pred->e_beg)->n_name);
               x_pred = x_pred->e_pnext;
            }
         }
         printf ("\n");
         ++c;
      }
      printf ("\n");
      if (c == g_nnode)  break;
   }
   return 0;
}

char*
GRAPH_node_line         (int n)
{
   char        s           [LEN_DESC]  = "";
   char        t           [LEN_HUND]  = "";
   char        u           [LEN_HUND]  = "";
   if (g_nodes [n].n_pred > 0)  sprintf (t, "%2d %-20.20s %-20.20s %2d %c", g_nodes [n].n_pred, ((g_nodes [n].n_phead)->e_beg)->n_name, ((g_nodes [n].n_ptail)->e_beg)->n_name, g_nodes [n].n_filled, g_nodes [n].n_ready);
   else                         strcpy  (t, " · ·                    ·                     · ·");
   if (g_nodes [n].n_succ > 0)  sprintf (u, "%2d %-20.20s %-20.20s", g_nodes [n].n_succ, ((g_nodes [n].n_shead)->e_end)->n_name, ((g_nodes [n].n_stail)->e_end)->n_name);
   else                         strcpy  (u, " · ·                    ·                     ·");
   if      (g_nodes [n].n_level <  0)  strcpy (s, "-");
   else if (g_nodes [n].n_level >  9)  strcpy (s, "Ï");
   else                                sprintf (s, "%c", g_nodes [n].n_level + '0');
   snprintf (my.unit_answer, LEN_RECD, "GRAPH node  (%2d) : %-20.20s %c %-1.1s %-49.49s   %-44.44s   ´", n, g_nodes [n].n_name, g_nodes [n].n_focus, s, t, u);
   return my.unit_answer;
}

char
GRAPH_dump_nodes        (void)
{
   int         i           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_value   ("g_nnode"   , g_nnode);
   for (i = 0; i <  g_nnode; ++i) {
      DEBUG_PROG   yLOG_complex ("node"      , "%3d  %-25.25s   %3dp   %3ds", i, g_nodes [i].n_name, g_nodes [i].n_pred, g_nodes [i].n_succ);
      printf ("%s\n", GRAPH_node_line (i));
   }
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       edge handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___EDGES___________o () { return; }

char
GRAPH_add_edge          (char a_name [LEN_TITLE], int e)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         b           =    0;
   tEDGE      *x_pred      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_name"    , a_name);
   --rce;  if (strcmp (a_name, "") == 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (e < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (e >= g_nnode) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for duplicate)------------*/
   x_pred = g_nodes [e].n_phead;
   while (x_pred != NULL) {
      if (strcmp (x_pred->e_beg->n_name, a_name) == 0) {
         DEBUG_PROG   yLOG_note    ("found pre-existing, duplicate edge");
         DEBUG_PROG   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      x_pred = x_pred->e_pnext;
   }
   /*---(beg-point on edge)--------------*/
   b = GRAPH_add_node (a_name);
   --rce;  if (b < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (b == e) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(updage edge)--------------------*/
   g_edges [g_nedge].e_nbeg = b;
   g_edges [g_nedge].e_beg  = &(g_nodes [b]);
   /*---(beg-point on node)--------------*/
   if (g_nodes [b].n_shead == NULL) { /* first */
      g_nodes [b].n_shead = &(g_edges [g_nedge]);
   } else {  /*                          append */
      (g_nodes [b].n_stail)->e_snext = &(g_edges [g_nedge]);
   }
   g_nodes [b].n_stail = &(g_edges [g_nedge]);
   ++(g_nodes [b].n_succ);
   /*---(end-point on edge)--------------*/
   g_edges [g_nedge].e_nend = e;
   g_edges [g_nedge].e_end  = &(g_nodes [e]);
   /*---(end-point on node)--------------*/
   if (g_nodes [e].n_phead == NULL) { /* first */
      g_nodes [e].n_phead = &(g_edges [g_nedge]);
   } else {  /*                          append */
      (g_nodes [e].n_ptail)->e_pnext = &(g_edges [g_nedge]);
   }
   g_nodes [e].n_ptail = &(g_edges [g_nedge]);
   ++(g_nodes [e].n_pred);
   /*---(counter)------------------------*/
   ++g_nedge;
   /*---(check for solo)-----------------*/
   DEBUG_PROG   yLOG_info    ("b_name"    , g_nodes [b].n_name);
   DEBUG_PROG   yLOG_info    ("e_name"    , g_nodes [e].n_name);
   if (strcmp (g_nodes [b].n_name, "zenodotus") == 0) {
      if (strstr (g_nodes [e].n_name, "_solo") != NULL) {
         DEBUG_PROG   yLOG_note    ("call to add tie to _solo");
         INCL_add_by_name (e, "zenodotus");
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
GRAPH_dump_edges        (void)
{
   int         i           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_value   ("g_nedge"   , g_nedge);
   for (i = 0; i <  g_nedge; ++i) {
      printf ("%3d  %3d %-25.25s  %3d %-25.25s\n", i, g_edges [i].e_nbeg, g_nodes [g_edges [i].e_nbeg].n_name, g_edges [i].e_nend, g_nodes [g_edges [i].e_nend].n_name);
   }
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}




/*====================------------------------------------====================*/
/*===----                       dependency lists                       ----===*/
/*====================------------------------------------====================*/
static void  o___DEPS____________o () { return; }

char
GRAPH_deps_add          (char a_name [LEN_TITLE], char a_deps [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)            return rce;
   --rce;  if (strcmp (a_name, "") == 0)  return rce;
   --rce;  if (a_deps == NULL)            return rce;
   --rce;  if (strcmp (a_deps, "") == 0)  return rce;
   /*---(add deps)-----------------------*/
   n = GRAPH_by_name (a_name);
   --rce;  if (n <  0)  return rce;
   /*---(add deps)-----------------------*/
   ystrlcpy (g_nodes [n].n_deps, a_deps, LEN_RECD);
   /*---(complete)-----------------------*/
   return 0;
}

char
GRAPH_deps_merge        (char a_deps [LEN_RECD], char r_cumd [LEN_RECD])
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
GRAPH_deps_preds        (int n)
{
   tEDGE      *x_pred      = NULL;
   char        c           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(mark)------------------------*/
   DEBUG_PROG   yLOG_value   ("n"         , n);
   strcpy (g_nodes [n].n_cumd, "");
   DEBUG_PROG   yLOG_info    ("n_name"    , g_nodes [n].n_name);
   printf ("SOLVING     : %s\n", g_nodes [n].n_name);
   /*---(fill successors)-------------*/
   x_pred = g_nodes [n].n_phead;
   DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
   while (x_pred != NULL) {
      DEBUG_PROG   yLOG_info    ("n_pred"    , x_pred->e_beg->n_name);
      GRAPH_deps_merge (x_pred->e_beg->n_cumd, g_nodes [n].n_cumd);
      ++c;
      x_pred = x_pred->e_pnext;
      DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
   }
   DEBUG_PROG   yLOG_value   ("c"         , c);
   printf ("  PREDS     : %4då%sæ\n", strlen (g_nodes [n].n_cumd), g_nodes [n].n_cumd);
   printf ("  DEPS      : %4då%sæ\n", strlen (g_nodes [n].n_deps), g_nodes [n].n_deps);
   GRAPH_deps_missing (g_nodes [n].n_deps, g_nodes [n].n_cumd, g_nodes [n].n_miss);
   printf ("  MISS      : %4då%sæ\n", strlen (g_nodes [n].n_miss), g_nodes [n].n_miss);
   GRAPH_deps_merge   (g_nodes [n].n_miss, g_nodes [n].n_cumd);
   printf ("  CUMPD     : %4då%sæ\n", strlen (g_nodes [n].n_cumd), g_nodes [n].n_cumd);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
}

char
GRAPH_deps_missing      (char a_deps [LEN_RECD], char a_cumd [LEN_RECD], char r_miss [LEN_RECD])
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
   --rce;  if (a_cumd == NULL)             return rce;
   --rce;  if (r_miss == NULL)             return rce;
   strcpy (r_miss, "");
   /*---(merge up)-----------------------*/
   ystrlcpy (x_deps, a_deps, LEN_RECD);
   p = strtok_r (x_deps, q, &r);
   while (p != NULL) {
      /*---(check)-----------------------*/
      if (p [0] == 'y' || strcmp (p, "koios") == 0 || strcmp (p, "zenodotus") == 0) {
         if (strcmp (p, "yVIHUB_solo") != 0) {
            sprintf (s, ",%s,", p);
            if (strstr (a_cumd, s) == NULL) {
               if (strcmp (r_miss, "")  == 0)  strcpy (r_miss, ",");
               if (strcmp (r_miss, "´") == 0)  strcpy (r_miss, ",");
               ystrlcat (r_miss, s + 1, LEN_RECD);
               ++c;
            }
         }
      }
      /*---(next)------------------------*/
      p = strtok_r (NULL  , q, &r);
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   return c;
}

char
GRAPH_deps_solve        (void)
{
   char        rc          =    0;
   int         i           =    0;
   char        x_lvl       =    0;
   int         c           =    0;
   tEDGE      *x_pred      = NULL;
   for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) {
      c = 0;
      for (i = 0; i <  g_nnode; ++i) {
         if (g_nodes [i].n_level != x_lvl)  continue;
         GRAPH_deps_preds (i);
         ++c;
      }
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         sequencing                           ----===*/
/*====================------------------------------------====================*/
static void  o___SEQUENCE________o () { return; }

char
GRAPH_seq_clear         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   for (i = 0; i < g_nedge; ++i) {
      g_edges [i].e_filled  = '-';
   }
   for (i = 0; i < g_nnode; ++i) {
      g_nodes [i].n_level   = -1;
      g_nodes [i].n_filled  =  0;
      g_nodes [i].n_ready   = '-';
   }
   g_ready  = 0;
   g_maxlvl = 0;
   return 0;
}

char
GRAPH_solve_layer       (char a_mark, char a_lvl)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         c           =    0;
   tEDGE      *x_succ      = NULL;
   /*---(prepare)------------------------*/
   for (i = 0; i < g_nnode; ++i) {
      if (g_nodes [i].n_filled == g_nodes [i].n_pred) {
         g_nodes [i].n_ready = 'y';
      }
   }
   /*---(walk)---------------------------*/
   for (i = 0; i < g_nnode; ++i) {
      /*---(filter)----------------------*/
      if (g_nodes [i].n_level >= 0)                   continue;
      if (g_nodes [i].n_ready != 'y')                 continue;
      /*---(mark at level)---------------*/
      g_nodes [i].n_level = a_lvl;
      ++c;
      ++g_ready;
      /*---(fill successors)-------------*/
      x_succ = g_nodes [i].n_shead;
      while (x_succ != NULL) {
         x_succ->e_filled = 'y';
         ++((x_succ->e_end)->n_filled);
         x_succ = x_succ->e_snext;
      }
      /*---(done)------------------------*/
   }
   return c;
}

char
GRAPH_solve             (char a_mark)
{
   char        x_lvl       =    0;
   int         c           =    0;
   GRAPH_seq_clear ();
   for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) {
      c += GRAPH_solve_layer (a_mark, x_lvl);
      if (c == g_nnode)  break;
   }
   g_maxlvl = x_lvl;
   return 0;
}

char
GRAPH_focus_pred        (int n)
{
   tEDGE      *x_pred      = NULL;
   char        c           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(mark)------------------------*/
   DEBUG_PROG   yLOG_value   ("n"         , n);
   g_nodes [n].n_focus = '°';
   /*---(fill successors)-------------*/
   x_pred = g_nodes [n].n_phead;
   DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
   while (x_pred != NULL) {
      GRAPH_focus_pred (x_pred->e_nbeg);
      ++c;
      x_pred = x_pred->e_pnext;
      DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
   }
   DEBUG_PROG   yLOG_value   ("c"         , c);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
}

char
GRAPH_focus_on          (char a_prog [LEN_TITLE])
{
   char        rce         =  -10;
   int         n           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_point   ("a_prog"    , a_prog);
   --rce;  if (a_prog     == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_prog"    , a_prog);
   --rce;  if (a_prog [0] == '\0') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   n = GRAPH_by_name (a_prog);
   DEBUG_PROG   yLOG_value   ("n"         , n);
   --rce;  if (n <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   GRAPH_focus_pred (n);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
GRAPH_focus_all         (void)
{
   int         i           =    0;
   for (i = 0; i <  g_nnode; ++i) {
      g_nodes [i].n_focus = '°';
   }
   return 0;
}

char
GRAPH_dump_seq          (void)
{
   int         i           =    0;
   char        x_lvl       =    0;
   int         c           =    0;
   tEDGE      *x_pred      = NULL;
   printf ("\n\nouroboros sequence solution\n\n");
   for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) {
      for (i = 0; i <  g_nnode; ++i) {
         if (g_nodes [i].n_level != x_lvl)  continue;
         printf ("%3d  %3d  %-25.25s   %3dp  ", i, g_nodes [i].n_level, g_nodes [i].n_name, g_nodes [i].n_pred);
         if (g_nodes [i].n_pred > 0)  {
            x_pred = g_nodes [i].n_phead;
            while (x_pred != NULL) {
               printf (" %-15.15s", (x_pred->e_beg)->n_name);
               x_pred = x_pred->e_pnext;
            }
         }
         printf ("\n");
         ++c;
      }
      printf ("\n");
      if (c == g_nnode)  break;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*            /*--> unit test accessor ------------------------------*/
GRAPH__unit             (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   char        s           [LEN_DESC]  = "";
   char        t           [LEN_HUND]  = "";
   char        u           [LEN_HUND]  = "";
   tWAVE      *x_cur       = NULL;
   char        i           =    0;
   char        x_focus     =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (my.unit_answer, "GRAPH            : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if (strcmp (a_question, "full"          )  == 0) {
      WAVE_by_index (n, &x_cur);
      if (n >= g_nnode) {
         snprintf (my.unit_answer, LEN_RECD, "GRAPH node  (%2d) : ·                    · ·  · ·                    ·                     · ·    · ·                    ·                      ´", n);
      } else {
         if (g_nodes [n].n_pred > 0)  sprintf (t, "%2d %-20.20s %-20.20s %2d %c", g_nodes [n].n_pred, ((g_nodes [n].n_phead)->e_beg)->n_name, ((g_nodes [n].n_ptail)->e_beg)->n_name, g_nodes [n].n_filled, g_nodes [n].n_ready);
         else                         strcpy  (t, " · ·                    ·                     · ·");
         if (g_nodes [n].n_succ > 0)  sprintf (u, "%2d %-20.20s %-20.20s", g_nodes [n].n_succ, ((g_nodes [n].n_shead)->e_end)->n_name, ((g_nodes [n].n_stail)->e_end)->n_name);
         else                         strcpy  (u, " · ·                    ·                     ·");
         if      (g_nodes [n].n_level <  0)  strcpy (s, "-");
         else if (g_nodes [n].n_level >  9)  strcpy (s, "Ï");
         else                                sprintf (s, "%c", g_nodes [n].n_level + '0');
         snprintf (my.unit_answer, LEN_RECD, "GRAPH node  (%2d) : %-20.20s %c %-1.1s %-49.49s   %-44.44s   ´", n, g_nodes [n].n_name, g_nodes [n].n_focus, s, t, u);
      }
   }
   else if (strcmp (a_question, "count"         )  == 0) {
      if      (g_nnode == 0)          strcpy (s, "empty");
      else if (g_nnode == g_ready)    strcpy (s, "SOLVED");
      else if (g_ready >  0)          strcpy (s, "in-process");
      else                            strcpy (s, "clear");
      for (i = 0; i <  g_nnode; ++i) {
         if (g_nodes [i].n_focus  != '-')  ++x_focus;
      }
      snprintf (my.unit_answer, LEN_RECD, "GRAPH count      : %3dn, %3de, %3dr, %3df, %s", g_nnode, g_nedge, g_ready, x_focus, s);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}





