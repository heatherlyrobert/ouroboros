/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



static char s_print    [LEN_RECD]  = "";
static char s_cols     [MAX_LEVEL] = { 0, 0, 0, 0, 0 };


static struct {
   char        b_abbr;
   char        b_block     [LEN_TERSE];
   char        b_title     [LEN_TITLE];
   char        b_focus     [LEN_TITLE];
   char        b_1st;
   char        b_1st_title [LEN_TITLE];
   char        b_2nd;
   char        b_1nd_title [LEN_TITLE];
   char        b_3rd;
   char        b_3rd_title [LEN_TITLE];
   char        b_4th;
   char        b_4th_title [LEN_TITLE];
   char        b_deps      [LEN_RECD];
} s_blocks [LEN_LABEL] = {
   /*----- -block-  ---title------------- ---focus----------- -a- ---label----------------- -a- ---label----------------- -a- ---label----------------- -a- ---label----------------- */
   { 'è' , ""     , ""                   , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       , ""},
   { 'é' , "I"    , "FOUNDATION"         , "ySTR,yENV"       ,  1, "build·base"            ,  4, "unit·testing·framework",  6, "execution·logging"     , 99, "core"                   , ""},
   { 'ê' , ""     , ""                   , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       , ""},
   { 'ê' , ""     , ""                   , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       , ""},
   { 'ì' , ""     , ""                   , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       , ""},
   { 'í' , ""     , ""                   , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       , ""},
   { 'î' , ""     , ""                   , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       , ""},
   { 'ï' , ""     , ""                   , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       , ""},
   { '\0', ""     , "end"                , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       , ""},
};




/*====================------------------------------------====================*/
/*===----                     line drawing version                     ----===*/
/*====================------------------------------------====================*/
static void  o___LINEDRAW________o () { return; }

char
DRAW_init               (char a_ornament, char a_style, char a_cols, char a_rows)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_lvl       =    0;
   int         i           =    0;
   int         l           =    0;
   char        s           [LEN_RECD]  = "";
   /*---(style-hints)--------------------*/
   my.d_ornament = a_ornament;
   my.d_style    = a_style;
   /*---(grid sizing)--------------------*/
   switch (a_style) {
   case 'u'  : my.x_side =  2; my.x_wide =  7; my.x_gap =  3; my.y_side = 1; my.y_tall = 3; my.y_gap = 0;  break;
   case 'l'  : my.x_side = 15; my.x_wide = 23; my.x_gap =  6; my.y_side = 2; my.y_tall = 6; my.y_gap = 2;  break;
   case 'H'  : my.x_side = 16; my.x_wide = 30; my.x_gap = 12; my.y_side = 3; my.y_tall = 8; my.y_gap = 3;  break;
   default   : my.x_side = 10; my.x_wide = 15; my.x_gap =  3; my.y_side = 1; my.y_tall = 5; my.y_gap = 2;  break;
   }
   /*---(save row/col)-------------------*/
   if      (a_cols <= 0)          my.x_cols = 1;
   else if (a_cols >  MAX_LEVEL)  my.x_cols = MAX_LEVEL;
   else                           my.x_cols = a_cols;
   if      (a_rows <= 0)          my.y_rows = 1;
   else if (a_rows >  50)         my.x_cols = 50;
   else                           my.y_rows = a_rows;
   /*---(full sizing)--------------------*/
   switch (a_ornament) {
   case 's'  :
      my.x_min =  0;
      my.x_max = my.x_min + my.x_wide * my.x_cols - my.x_gap;
      if (my.x_max < 80)  my.x_max = 80;
      my.x_end = my.x_max;
      my.y_min =  5;
      my.y_max = my.y_min + my.y_tall * my.y_rows - my.y_gap;
      my.y_end = my.y_max + 2;
      break;
   case 'b'  :
      my.x_min =  8;
      my.x_max = my.x_min + my.x_wide * my.x_cols - my.x_gap;
      my.x_end = my.x_max + 8;
      my.y_min =  6;
      my.y_max = my.y_min + my.y_tall * my.y_rows - my.y_gap;
      my.y_end = my.y_max + 3;
      break;
   default   :
      my.x_min =  0;
      my.x_max = my.x_min + my.x_wide * my.x_cols - my.x_gap;
      my.x_end = my.x_max;
      my.y_min =  0;
      my.y_max = my.y_min + my.y_tall * my.y_rows - my.y_gap;
      my.y_end = my.y_max;
      break;
   }
   /*---(create)-------------------------*/
   rc = yASCII_new (my.x_end, my.y_end);
   yASCII_grid (a_style, my.x_min, my.y_min);
   /*---(title block)--------------------*/
   if (strchr ("fs", a_ornament) != NULL) {
      sprintf (s, "#!%s", P_FULLPATH);
      yASCII_print (0, 0, s, YASCII_CLEAR);
      sprintf (s, "## %s", P_ONELINE);
      yASCII_print (0, 1, s, YASCII_CLEAR);
   }
   /*---(headers)------------------------*/
   if (strchr ("fs", a_ornament) != NULL) {
      for (x_lvl = 0; x_lvl < a_cols; ++x_lvl) {
         switch (a_style) {
         case 'u' : sprintf (s, "[-%02d-]", x_lvl);      break;
         case 'l' : sprintf (s, "[------%02d-------]", x_lvl); break;
         default  : sprintf (s, "[----%02d----]", x_lvl);      break;
         }
         yASCII_print (x_lvl * my.x_wide, 3, s, YASCII_CLEAR);
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
DRAW_wrap               (void)
{
   char        rc          =    0;
   short       a           =    0;
   int         i           =    0;
   char        s           [LEN_RECD]  = "";
   if (strchr ("fs", my.d_ornament) != NULL) {
      yASCII_print (my.x_min, my.y_end - 1, "## end-of-file.  done, finito, completare, whimper [Ï´···", YASCII_CLEAR);
   }
   else if (my.d_ornament == 'b') {
      /*> yASCII_frame_full (0, 0, 7, 5, "I. FOUNDATION (14)", -1, "a)·build·base", 1, "b)·unit·testing·framework", 4, "c)·execution·logging", 6, "d)·core");   <* 
       *> yASCII_node (0, 6, 'è');                                                                                                                              <* 
       *> yASCII_node (my.x_end - 5, 6, 'é');                                                                                                                   <* 
       *> yASCII_tie_grid (-1, 0, 0, 0);                                                                                                                        <* 
       *> yASCII_tie_grid ( 7, 0, 8, 0);                                                                                                                        <* 
       *> yASCII_tie_grid ( 7, 1, 8, 0);                                                                                                                        <*/
   }
   rc = yASCII_write (YSTR_CLIP);
   rc = yASCII_free  ();
   return 0;
}

char
DRAW_main               (char a_ornament, char a_style)
{
   /*> DRAW_init    (a_ornament, a_style,  8,  6);                                    <*/
   DRAW_init    (a_ornament, a_style, 30, 20);
   /*---(foundation)---------------------*/
   DRAW_box_rooted ("ySTR");
   DRAW_box_rooted ("yENV");
   yASCII_frame_full (0, 0, 7, 5, "I. FOUNDATION (14)", -1, "a)·build·base", 1, "b)·unit·testing·framework", 4, "c)·execution·logging", 6, "d)·core");
   yASCII_node_grid (-1, 0, 'è');
   yASCII_node_grid ( 8, 0, 'é');
   yASCII_tie_grid  (-1, 0, 0, 0);
   yASCII_tie_grid  ( 7, 0, 8, 0);
   yASCII_tie_grid  ( 7, 1, 8, 0);
   yASCII_grid  (a_style, YASCII_NODE, 0);
   DRAW_box_rooted ("yKEYS");
   /*> DRAW_box_rooted ("yJOBS");                                                     <*/
   /*> DRAW_box_rooted ("gregg");                                                     <*/
   /*> DRAW_block ('é');                                                              <*/
   DRAW_wrap    ();
   return 0;
}

char
DRAW_box_layer          (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   tNODE      *x_root      = NULL;
   tEDGE      *x_pred      = NULL;
   tNODE      *x_node      = NULL;
   char        c           =    0;
   char        x_miss      [LEN_RECD]  = "";
   char        s           [LEN_TITLE] = "";
   char        x_lvl       =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(mark)------------------------*/
   DEBUG_PROG   yLOG_value   ("n"         , n);
   x_root = &(g_nodes [n]);
   DEBUG_PROG   yLOG_info    ("name"      , g_nodes [n].n_name);
   ystrlcpy (x_miss, x_root->n_miss, LEN_RECD);
   DEBUG_PROG   yLOG_info    ("x_miss"    , x_miss);
   /*---(walk predessors)-------------*/
   for (x_lvl = x_root->n_level - 1; x_lvl >= 0; --x_lvl) {
      x_pred = x_root->n_phead;
      DEBUG_PROG   yLOG_point   ("head"      , x_pred);
      while (x_pred != NULL) {
         x_node = x_pred->e_beg;
         DEBUG_PROG   yLOG_complex ("detail"    , "%2d %s", x_node->n_level, x_node->n_name);
         if (x_node->n_level == x_lvl) {
            /*---(prepare)------------------*/
            sprintf  (s, ",%s,", x_node->n_name);
            DEBUG_PROG   yLOG_info    ("s"         , s);
            /*---(draw box)-----------------*/
            if (x_node->n_row < 0) {
               x_node->n_row = s_cols [x_node->n_level];
               ++(s_cols [x_node->n_level]);
               yASCII_box_grid (x_node->n_level, x_node->n_row, x_node->n_name, "", x_node->n_pred, x_node->n_succ);
            }
            /*---(add connection)-----------*/
            if (strstr (x_miss, s) != NULL) {
               DRAW_box_layer (x_pred->e_nbeg);
               yASCII_tie_grid (x_node->n_level, x_node->n_row, x_root->n_level, x_root->n_row);
            }
            /*---(next)---------------------*/
            x_pred->e_used = 'y';
            ++c;
            /*---(done)---------------------*/
         }
         x_pred = x_pred->e_pnext;
         DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
      }
   }
   DEBUG_PROG   yLOG_value   ("c"         , c);
   /*---(merge into node)----------------*/
   if (strcmp (g_nodes [n].n_name, "ySTR") == 0 || strcmp (g_nodes [n].n_name, "yENV") == 0) {
      GRAPH_deps_merge (g_nodes [n].n_cumd, s_blocks [1].b_deps);
      sprintf (s, ",%s,", g_nodes [n].n_name);
      GRAPH_deps_merge (s, s_blocks [1].b_deps);
      printf ("FOUNDATION %c  %s  å%sæ\n", s_blocks [1].b_abbr, g_nodes [n].n_name, s_blocks [1].b_deps);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
}

char
DRAW_box_rooted         (char a_prog [LEN_TITLE])
{
   char        rce         =  -10;
   int         n           =    0;
   tNODE      *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
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
   /*---(get root)-----------------------*/
   n = GRAPH_by_name (a_prog);
   DEBUG_PROG   yLOG_value   ("n"         , n);
   --rce;  if (n <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update root)--------------------*/
   x_node = &(g_nodes [n]);
   x_node->n_row = s_cols [x_node->n_level];
   ++(s_cols [x_node->n_level]);
   yASCII_box_grid (x_node->n_level, x_node->n_row, x_node->n_name, "", x_node->n_pred, x_node->n_succ);
   /*---(start process)------------------*/
   DRAW_box_layer (n);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_block              (char a_block)
{
   char        rce         =  -10;
   int         i           =    0;
   int         n           =    0;
   tNODE      *x_node      = NULL;
   for (i = 0; i < MAX_INCL; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      if (a_block != g_incls [i].i_block)  continue;
      n = GRAPH_by_name (g_incls [i].i_name);
      x_node = &(g_nodes [n]);
      x_node->n_row = s_cols [x_node->n_level];
      ++(s_cols [x_node->n_level]);
      yASCII_box_grid (x_node->n_level, x_node->n_row, x_node->n_name, "", x_node->n_pred, x_node->n_succ);
   }
   return 0;
}

char
DRAW_box_clear          (void)
{
   int         i           =    0;
   /*---(reset)--------------------------*/
   for (i = 0; i < MAX_LEVEL; ++i) s_cols  [i]       = 0;
   for (i = 0; i < g_nnode; ++i)   g_nodes [i].n_row = -1;
   /*---(complete)-----------------------*/
   return 0;
}

char
GRAPH_box_deps          (char a_name [LEN_TITLE], char r_deps [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =    0;
   char        c           =    0;
   char        x_miss      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   char        a           =    0;
   char        x_lvl       =    0;
   char        s           [LEN_TITLE] = "";
   char        x_deps      [LEN_RECD]  = ",";
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(place predessors)---------------*/
   DEBUG_PROG   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name     == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_name"    , a_name);
   --rce;  if (a_name [0] == '\0') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("r_deps"    , r_deps);
   --rce;  if (r_deps     == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get base)-----------------------*/
   n = GRAPH_by_name (a_name);
   DEBUG_PROG   yLOG_value   ("n"         , n);
   --rce;  if (n <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(identify missing)---------------*/
   ystrlcpy (x_miss, g_nodes [n].n_miss, LEN_RECD);
   strcpy   (r_deps, ",");
   p = strtok_r (x_miss, q, &r);
   while (p != NULL) {
      a = GRAPH_by_name (p);
      if (a >= 0) {
         x_lvl = g_nodes [a].n_level;
         sprintf  (s, "%02d:%s,", x_lvl, p);
         ystrlcat (r_deps, s, LEN_RECD);
         ++c;
      }
      p = strtok_r (NULL, q, &r);
   }
   if (strcmp (r_deps, ",") == 0)  strcmp (r_deps, "");
   DEBUG_PROG   yLOG_value   ("c"         , c);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
}

char
GRAPH_dump_box_pretty   (int a_node)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =    0;
   char        x_lvl       =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(reset)--------------------------*/
   for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) s_cols [x_lvl] = 0;
   /*---(place)--------------------------*/
   for (x_lvl = 1; x_lvl < MAX_LEVEL; ++x_lvl) {
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*            /*--> unit test accessor ------------------------------*/
DRAW__unit              (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (my.unit_answer, "DRAW             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if (strcmp (a_question, "sizing"        )  == 0) {
      snprintf (my.unit_answer, LEN_RECD, "DRAW sizing      : %c %c   H %3d# %3dn %3dx %3dr %3ds %3dw %3dg   V %3d# %3dn %3dx %3db %3ds %3dt %3dg",
            my.d_ornament, my.d_style,
            my.x_cols, my.x_min, my.x_max, my.x_end, my.x_side, my.x_wide, my.x_gap,
            my.y_rows, my.y_min, my.y_max, my.y_end, my.y_side, my.y_tall, my.y_gap);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}




