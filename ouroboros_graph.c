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

struct {
   char        o_name      [LEN_TITLE];
   char        o_block;
   char        o_col;
   char        o_row;
   char        o_run;
} zASCII_order [LEN_HUND] = {
   /* BLOCK é FOUNDATION ------------------*/
   /* level 00 ···········  blk  col  row  */
   { "zenodotus"          , 'é',  0 ,  0 , '·'  },
   /* level 01 ···········  blk  col  row  */
   { "ySTR_solo"          , 'é',  1 ,  0 , '·'  },
   { "yUNIT_solo"         , 'é',  1 ,  1 , '·'  },
   { "yCOLOR_solo"        , 'é',  1 ,  2 , '·'  },
   { "yENV_solo"          , 'é',  1 ,  3 , '·'  },
   { "yLOG_solo"          , 'é',  1 ,  4 , '·'  },
   { "yDLST_solo"         , 'é',  1 ,  5 , '·'  },
   /* level 02 ···········  blk  col  row  */
   { "yVAR"               , 'é',  2 ,  0 , '·'  },
   /* level 03 ···········  blk  col  row  */
   { "yUNIT"              , 'é',  3 ,  0 , '·'  },
   /* level 04 ···········  blk  col  row  */
   { "koios"              , 'é',  4 ,  0 , '·'  },
   /* level 05 ···········  blk  col  row  */
   { "yLOG"               , 'é',  5 ,  0 , '·'  },
   /* level 06 ···········  blk  col  row  */
   { "yURG"               , 'é',  6 ,  0 , '·'  },
   /* level 07 ···········  blk  col  row  */
   { "ySTR"               , 'é',  7 ,  0 , 'Ï'  },
   { "yENV"               , 'é',  7 ,  1 , 'Ï'  },
   /* BLOCK ê VIKEYS ----------------------*/
   { "yVIHUB"             , 'ê',  8 ,  0 , '·'  },
   { "yMODE"              , 'ê',  9 ,  0 , '·'  },
   { "yKEYS"              , 'ê', 10 ,  0 , '·'  },
   { "yVIEW"              , 'ê', 11 ,  0 , '·'  },
   { "yFILE"              , 'ê', 11 ,  1 , '·'  },
   { "ySRC"               , 'ê', 11 ,  2 , '·'  },
   { "yMAP"               , 'ê', 11 ,  3 , '·'  },
   { "yMACRO"             , 'ê', 11 ,  4 , '·'  },
   { "yCMD"               , 'ê', 12 ,  0 , 'Ï'  },
   { "yMARK"              , 'ê', 12 ,  1 , 'Ï'  },
   { "yGOD"               , 'ê', 12 ,  2 , 'Ï'  },
   /* BLOCK ÷ PRETTY ----------------------*/
   { "yVICURSES"          , 'ê', 13 ,  0 , '·'  },
   { "gyges"              , 'ê', 14 ,  0 , 'Ï'  },
   { "yVICURSES"          , 'ê', 13 ,  1 , '·'  },
   { "gregg"              , 'ê', 14 ,  1 , 'Ï'  },
   { "metis"              , 'ê', 14 ,  2 , 'Ï'  },
   { "arachne"            , 'ê', 14 ,  3 , 'Ï'  },
   { "petal"              , 'ê', 14 ,  4 , 'Ï'  },
   { "kairos"             , 'ê', 14 ,  5 , 'Ï'  },
   { "pacer"              , 'ê', 14 ,  6 , 'Ï'  },
   /* BLOCK ñ KEYSTONES -------------------*/
   { "yPARSE"             , 'ñ',  8 ,  5 , '·'  },
   { "ySORT"              , 'ñ',  8 ,  6 , '·'  },
   { "yREGEX"             , 'ñ',  8 ,  7 , '·'  },
   { "yDLST"              , 'ñ',  8 ,  8 , 'Ï'  },
   { "ySCHED"             , 'ñ',  8 ,  9 , 'Ï'  },
   { "ySEC"               , 'ñ',  8 , 10 , 'Ï'  },
   { "yEXEC"              , 'ñ',  9 ,  5 , '·'  },
   { "yJOBS"              , 'ñ', 10 ,  5 , 'Ï'  },
   /* BLOCK ë DAEMONISH -------------------*/
   { "eos"                , 'ë', 11 ,  5 , 'Ï'  },
   { "heracles"           , 'ë', 12 ,  5 , 'Ï'  },
   { "kharon"             , 'ë', 11 ,  6 , 'Ï'  },
   { "khronos"            , 'ë', 11 ,  7 , 'Ï'  },
   { "helios"             , 'ë', 11 ,  8 , 'Ï'  },
   { "hermes"             , 'ë', 11 ,  9 , 'Ï'  },
   { "hestia"             , 'ë', 11 , 10 , 'Ï'  },
   { "hearth"             , 'ë', 12 , 10 , 'Ï'  },
};


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
      g_edges [i].e_type     = '-';
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
      g_nodes [i].n_block    = '-';
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
   /*> GRAPH_add_node ("zenodotus");                                                  <*/
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
   /*---(filter)-------------------------*/
   if (strcmp (a_name, "yVIHUB_solo") == 0) {
      DEBUG_PROG  yLOG_note    ("always ignore yVIHUB_solo");
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   n = GRAPH_by_name (a_name);
   DEBUG_PROG   yLOG_value   ("n"         , n);
   if (n < 0) {
      DEBUG_PROG  yLOG_note    ("can't find, add new node");
      ystrlcpy (g_nodes [g_nnode].n_name, a_name, LEN_TITLE);
      n = g_nnode;
      ++g_nnode;
      DEBUG_PROG   yLOG_value   ("n"         , n);
   }
   /*> if (strcmp (a_name, "zenodotus") != 0) {                                       <* 
    *>    DEBUG_PROG   yLOG_note    ("create a link back to zenodotus");              <* 
    *>    INCL_add_by_name ("zenodotus", n);                                          <* 
    *>    GRAPH_edge_add   ("zenodotus", n);                                          <* 
    *> }                                                                              <*/
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
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
GRAPH_edge_add          (char a_type, char a_beg [LEN_TITLE], int a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_beg       =    0;
   tEDGE      *x_pred      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_beg"     , a_beg);
   --rce;  if (a_beg == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_beg"     , a_beg);
   --rce;  if (strcmp (a_beg, "") == 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_end < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_end >= g_nnode) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for duplicate)------------*/
   x_pred = g_nodes [a_end].n_phead;
   while (x_pred != NULL) {
      if (strcmp (x_pred->e_beg->n_name, a_beg) == 0) {
         DEBUG_PROG   yLOG_note    ("found pre-existing, duplicate edge");
         DEBUG_PROG   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      x_pred = x_pred->e_pnext;
   }
   /*---(beg-point on edge)--------------*/
   x_beg = GRAPH_add_node (a_beg);
   --rce;  if (x_beg < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_beg == a_end) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set type)-----------------------*/
   g_edges [g_nedge].e_type = a_type;
   /*---(beg-point on edge)--------------*/
   g_edges [g_nedge].e_nbeg = x_beg;
   g_edges [g_nedge].e_beg  = &(g_nodes [x_beg]);
   /*---(beg-point on node)--------------*/
   if (g_nodes [x_beg].n_shead == NULL) { /* first */
      g_nodes [x_beg].n_shead = &(g_edges [g_nedge]);
   } else {  /*                          append */
      (g_nodes [x_beg].n_stail)->e_snext = &(g_edges [g_nedge]);
   }
   g_nodes [x_beg].n_stail = &(g_edges [g_nedge]);
   ++(g_nodes [x_beg].n_succ);
   /*---(end-point on edge)--------------*/
   g_edges [g_nedge].e_nend = a_end;
   g_edges [g_nedge].e_end  = &(g_nodes [a_end]);
   /*---(end-point on node)--------------*/
   if (g_nodes [a_end].n_phead == NULL) { /* first */
      g_nodes [a_end].n_phead = &(g_edges [g_nedge]);
   } else {  /*                          append */
      (g_nodes [a_end].n_ptail)->e_pnext = &(g_edges [g_nedge]);
   }
   g_nodes [a_end].n_ptail = &(g_edges [g_nedge]);
   ++(g_nodes [a_end].n_pred);
   /*---(counter)------------------------*/
   ++g_nedge;
   /*---(check for solo)-----------------*/
   DEBUG_PROG   yLOG_info    ("b_name"    , g_nodes [x_beg].n_name);
   DEBUG_PROG   yLOG_info    ("e_name"    , g_nodes [a_end].n_name);
   if (strcmp (g_nodes [x_beg].n_name, "zenodotus") == 0) {
      if (strstr (g_nodes [a_end].n_name, "_solo") != NULL) {
         DEBUG_PROG   yLOG_note    ("call to add tie to _solo");
         INCL_add_by_name ("zenodotus", a_end);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char GRAPH_edge_real   (char a_beg [LEN_TITLE], int a_end) { return GRAPH_edge_add ('r', a_beg, a_end); }
char GRAPH_edge_virt   (char a_beg [LEN_TITLE], int a_end) { return GRAPH_edge_add ('v', a_beg, a_end); }

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
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
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
   DEBUG_PROG   yLOG_point   ("r_miss"    , r_miss);
   --rce;  if (r_miss == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strcpy (r_miss, "");
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
            if (strstr (a_cumd, s) == NULL) {
               DEBUG_PROG   yLOG_note    ("add as miss");
               if (strcmp (r_miss, "")  == 0)  strcpy (r_miss, ",");
               if (strcmp (r_miss, "´") == 0)  strcpy (r_miss, ",");
               ystrlcat (r_miss, s + 1, LEN_RECD);
               ++c;
            }
         }
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





