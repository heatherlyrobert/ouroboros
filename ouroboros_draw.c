/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



static char s_print    [LEN_RECD]  = "";
static char s_cols     [MAX_LEVEL] = { 0, 0, 0, 0, 0 };
static int  s_boxes  = 0;


static struct {
   char        b_abbr;
   char        b_pred      [LEN_LABEL];
   char        b_title     [LEN_TITLE];
   char        b_sources   [LEN_HUND];
   char        b_1col;
   char        b_1name     [LEN_TITLE];
   char        b_2col;
   char        b_2name     [LEN_TITLE];
   char        b_3col;
   char        b_3name     [LEN_TITLE];
   char        b_4col;
   char        b_4name     [LEN_TITLE];
   char        b_deps      [LEN_RECD];
} zASCII_blocks [LEN_LABEL] = {
   /*----- --pred-- ---title-------------- ---sources--------------------------------- -1- ---label-------------------- -2- ---label-------------------- -3- ---label-------------------- -4- ---label--------------------- deps */
   { 'è' , ""      , ""                   , ""                                        , -1, ""                         , -1, ""                         , -1, ""                         , -1, ""                          , ""},
   { 'é' , "è"     , "I) FOUNDATION"      , "ySTR,yENV"                               , -1, "a) build·base"            ,  1, "b)·unit·testing·framework",  4, "c)·execution·logging"     ,  6, "d)·core"                   , ""},
   { 'ê' , ""      , "II) VIKEYS I"       , "yKEYS"                                   , -1, ""                         , -1, ""                         , -1, ""                         , -1, ""                          , ""},
   { 'ê' , ""      , "III) VIKEYS II"     , "yCMD,yMARK,yGOD"                         , -1, ""                         , -1, ""                         , -1, ""                         , -1, ""                          , ""},
   { 'ì' , ""      , "IV) DOERS"          , "yEXEC,ySCHED,yDLST,yASCII"               , -1, ""                         , -1, ""                         , -1, ""                         , -1, ""                          , ""},
   { 'í' , ""      , "V) YJOBS"           , "yJOBS"                                   , -1, ""                         , -1, ""                         , -1, ""                         , -1, ""                          , ""},
   { 'î' , ""      , "VI) BRUTES"         , "eos,kharon,khronos,helios,hestia"        , -1, ""                         , -1, ""                         , -1, ""                         , -1, ""                          , ""},
   { 'ï' , ""      , ""                   , ""                                        , -1, ""                         , -1, ""                         , -1, ""                         , -1, ""                          , ""},
   { '\0', ""      , "end"                , ""                                        , -1, ""                         , -1, ""                         , -1, ""                         , -1, ""                          , ""},
};



/*====================------------------------------------====================*/
/*===----                     line drawing version                     ----===*/
/*====================------------------------------------====================*/
static void  o___LINEDRAW________o () { return; }

char
DRAW_init               (char a_layout, char a_size, char a_decor, char a_cols, char a_rows)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_lvl       =    0;
   int         i           =    0;
   int         l           =    0;
   char        s           [LEN_RECD]  = "";
   char        x_horz, x_topp, x_bott;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_complex ("args"      , "%c %c %c %2d %2d", a_layout, a_size, a_decor, a_cols, a_rows);
   /*---(style-hints)--------------------*/
   my.d_layout   = a_layout;
   my.d_size     = a_size;
   my.d_decor    = a_decor;
   /*---(grid sizing)--------------------*/
   switch (a_size) {
   case YASCII_MICRO  : my.x_side =  2; my.x_wide =  7; my.x_gap =  3; my.y_side = 1; my.y_tall = 3; my.y_gap = 0;  break;
   case YASCII_LARGE  : my.x_side = 15; my.x_wide = 23; my.x_gap =  6; my.y_side = 2; my.y_tall = 6; my.y_gap = 2;  break;
   case YASCII_HUGE   : my.x_side = 16; my.x_wide = 30; my.x_gap = 12; my.y_side = 3; my.y_tall = 8; my.y_gap = 3;  break;
   default            : my.x_side = 10; my.x_wide = 15; my.x_gap =  3; my.y_side = 1; my.y_tall = 5; my.y_gap = 2;  break;
   }
   /*---(save row/col)-------------------*/
   if      (a_cols <= 0)          my.x_cols = 1;
   else if (a_cols >  MAX_LEVEL)  my.x_cols = MAX_LEVEL;
   else                           my.x_cols = a_cols;
   if      (a_rows <= 0)          my.y_rows = 1;
   else if (a_rows >  50)         my.x_cols = 50;
   else                           my.y_rows = a_rows;
   DEBUG_PROG   yLOG_complex ("grid"      , "x %2d %2d %2d   y %2d %2d %2d", my.x_side, my.x_wide, my.x_gap, my.y_side, my.y_tall, my.y_gap);
   /*---(full sizing)--------------------*/
   switch (a_layout) {
   case 's'  :
      x_horz   =  0;
      x_topp   =  0;
      x_bott   =  0;
      my.x_min = x_horz;
      my.x_max = my.x_min + my.x_wide * my.x_cols - my.x_gap;
      if (my.x_max < 80)  my.x_max = 80;
      my.x_end = my.x_max + x_horz;
      my.y_min =  5;
      my.y_max = my.y_min + my.y_tall * my.y_rows - my.y_gap;
      my.y_end = my.y_max + 2;
      yASCII_grid_new_custom (a_size, a_decor, a_cols, a_rows, my.x_min, my.x_end - my.x_max, my.y_min, my.y_end - my.y_max, my.x_end, my.y_end);
      break;
   case 'b'  :
      x_horz   =  8;
      x_topp   =  6;
      x_bott   =  3;
      my.x_min = x_horz;
      my.x_max = my.x_min + my.x_wide * my.x_cols - my.x_gap;
      my.x_end = my.x_max + x_horz;
      my.y_min = x_topp;
      my.y_max = my.y_min + my.y_tall * my.y_rows - my.y_gap;
      my.y_end = my.y_max + x_bott;
      yASCII_grid_new_full (a_size, a_decor, a_cols, a_rows, my.x_min, my.x_end - my.x_max, my.y_min, my.y_end - my.y_max);
      break;
   default   :
      x_horz   =  0;
      x_topp   =  0;
      x_bott   =  0;
      my.x_min = x_horz;
      my.x_max = my.x_min + my.x_wide * my.x_cols - my.x_gap;
      my.x_end = my.x_max + x_horz;
      my.y_min = x_topp;
      my.y_max = my.y_min + my.y_tall * my.y_rows - my.y_gap;
      my.y_end = my.y_max + x_bott;
      yASCII_grid_new_full (a_size, a_decor, a_cols, a_rows, my.x_min, my.x_end - my.x_max, my.y_min, my.y_end - my.y_max);
      break;
   }
   DEBUG_PROG   yLOG_complex ("full"      , "x %2d %2d %2d   y %2d %2d %2d", my.x_min, my.x_max, my.x_end, my.y_min, my.y_max, my.y_end);
   /*---(globals)------------------------*/
   for (i = 0; i < LEN_LABEL; ++i) {
      strcpy (zASCII_blocks [i].b_deps, "");
   }
   /*---(title block)--------------------*/
   if (strchr ("fs", a_layout) != NULL) {
      DEBUG_PROG   yLOG_note    ("write title block");
      sprintf (s, "#!%s", P_FULLPATH);
      yASCII_print (0, 0, s, YASCII_CLEAR);
      sprintf (s, "## %s", P_ONELINE);
      yASCII_print (0, 1, s, YASCII_CLEAR);
   }
   /*---(headers)------------------------*/
   if (strchr ("fs", a_layout) != NULL) {
      DEBUG_PROG   yLOG_note    ("write headers");
      for (x_lvl = 0; x_lvl < a_cols; ++x_lvl) {
         switch (a_size) {
         case YASCII_MICRO : sprintf (s, "[-%02d-]", x_lvl);      break;
         case YASCII_LARGE : sprintf (s, "[------%02d-------]", x_lvl); break;
         default  : sprintf (s, "[----%02d----]", x_lvl);      break;
         }
         yASCII_print (x_lvl * my.x_wide, 3, s, YASCII_CLEAR);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_wrap               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   short       a           =    0;
   int         i           =    0;
   char        s           [LEN_RECD]  = "";
   if (strchr ("fs", my.d_layout) != NULL) {
      yASCII_print (my.x_min, my.y_end - 1, "## end-of-file.  done, finito, completare, whimper [Ï´···", YASCII_CLEAR);
   }
   else if (my.d_layout == 'b') {
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
DRAW_block_by_abbr      (char a_block)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =   -1;
   for (i = 0; i < LEN_LABEL; ++i) {
      if (zASCII_blocks [i].b_abbr == '\0')    break;
      if (zASCII_blocks [i].b_abbr != a_block) continue;
      return i;
      break;
   }
   return --rce;
}

char
DRAW_block              (char a_block)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =   1;
   char        x_pred      [LEN_DESC]  = "";
   char        x_title     [LEN_TITLE] = "";
   char       *p           = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   s_boxes = 0;
   i = 1;
   ystrlcpy (x_pred, zASCII_blocks [i].b_sources, LEN_DESC);
   DEBUG_PROG   yLOG_info    ("x_pred"    , x_pred);
   p = strtok_r (x_pred, q, &r);
   while (p != NULL) {
      DEBUG_PROG   yLOG_info    ("p"         , p);
      DRAW_block_source ('é', p);
      p = strtok_r (NULL, q, &r);
   }
   sprintf (x_title, "%s (%d)", zASCII_blocks [i].b_title, s_boxes);
   DEBUG_PROG   yLOG_info    ("x_title"   , x_title);
   yASCII_frame_full (0, 0, 7, 7, x_title, zASCII_blocks [i].b_1col, zASCII_blocks [i].b_1name, zASCII_blocks [i].b_2col, zASCII_blocks [i].b_2name, zASCII_blocks [i].b_3col, zASCII_blocks [i].b_3name, zASCII_blocks [i].b_4col, zASCII_blocks [i].b_4name);
   yASCII_node_grid (-1, 0, 'è');
   yASCII_node_grid ( 8, 0, 'é');
   yASCII_tie_grid  (-1, 0, 0, 0);
   yASCII_tie_grid  ( 7, 0, 8, 0);
   yASCII_tie_grid  ( 7, 1, 8, 0);
   DRAW_wrap    ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_main               (char a_layout, char a_size, char a_decor)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =   1;
   char        x_pred      [LEN_DESC]  = "";
   char        x_title     [LEN_TITLE] = "";
   char       *p           = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DRAW_init    (a_layout, a_size, a_decor, 15, 10);
   s_boxes = 0;
   i = 1;
   ystrlcpy (x_pred, zASCII_blocks [i].b_sources, LEN_DESC);
   DEBUG_PROG   yLOG_info    ("x_pred"    , x_pred);
   p = strtok_r (x_pred, q, &r);
   while (p != NULL) {
      DEBUG_PROG   yLOG_info    ("p"         , p);
      DRAW_block_source ('é', p);
      p = strtok_r (NULL, q, &r);
   }
   sprintf (x_title, "%s (%d)", zASCII_blocks [i].b_title, s_boxes);
   DEBUG_PROG   yLOG_info    ("x_title"   , x_title);
   yASCII_frame_full (0, 0, 7, 7, x_title, zASCII_blocks [i].b_1col, zASCII_blocks [i].b_1name, zASCII_blocks [i].b_2col, zASCII_blocks [i].b_2name, zASCII_blocks [i].b_3col, zASCII_blocks [i].b_3name, zASCII_blocks [i].b_4col, zASCII_blocks [i].b_4name);
   yASCII_node_grid (-1, 0, 'è');
   yASCII_node_grid ( 8, 0, 'é');
   yASCII_tie_grid  (-1, 0, 0, 0);
   yASCII_tie_grid  ( 7, 0, 8, 0);
   yASCII_tie_grid  ( 7, 1, 8, 0);
   DRAW_wrap    ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_main_OLD           (char a_layout, char a_size, char a_decor)
{
   int         i           =   1;
   char        x_title     [LEN_TITLE] = "";
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DRAW_init    (a_layout, a_size, a_decor, 15, 10);
   /*---(foundation)---------------------*/
   /*> DRAW_block_source ('é', "koios");                                              <*/
   s_boxes = 0;
   DRAW_block_source ('é', "ySTR");
   DRAW_block_source ('é', "yENV");
   printf ("BOXES = %d\n", s_boxes);
   /*> yASCII_frame_full (0, 0, 7, 7, "I. FOUNDATION (14)", -1, "a)·build·base", 1, "b)·unit·testing·framework", 4, "c)·execution·logging", 6, "d)·core");   <*/
   i = 1;
   sprintf (x_title, "%s (%d)", zASCII_blocks [i].b_title, s_boxes);
   yASCII_frame_full (0, 0, 7, 7, x_title, zASCII_blocks [i].b_1col, zASCII_blocks [i].b_1name, zASCII_blocks [i].b_2col, zASCII_blocks [i].b_2name, zASCII_blocks [i].b_3col, zASCII_blocks [i].b_3name, zASCII_blocks [i].b_4col, zASCII_blocks [i].b_4name);
   yASCII_node_grid (-1, 0, 'è');
   yASCII_node_grid ( 8, 0, 'é');
   yASCII_tie_grid  (-1, 0, 0, 0);
   yASCII_tie_grid  ( 7, 0, 8, 0);
   yASCII_tie_grid  ( 7, 1, 8, 0);
   DRAW_wrap    ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_box                (char a_block, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_complex ("a_args"    , "%c %d", a_block, n);
   /*---(defence)------------------------*/
   DEBUG_PROG   yLOG_value   ("g_nnode"   , g_nnode);
   --rce;  if (n < 0 || n >= g_nnode) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_node = &(g_nodes [n]);
   DEBUG_PROG   yLOG_point   ("x_node"    , x_node);
   --rce;  if (x_node == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defence)------------------------*/
   DEBUG_PROG   yLOG_complex ("node"      , "%2dl, %c, %s", x_node->n_level, x_node->n_block, x_node->n_name);
   if (x_node->n_block == '-') {
      DEBUG_PROG   yLOG_note    ("node block not assigned, set it now");
      x_node->n_block = a_block;
   }
   /*---(set-row)------------------------*/
   DEBUG_PROG   yLOG_value   ("n_row bef" , x_node->n_row);
   if (x_node->n_row >= 0) {
      DEBUG_PROG   yLOG_note    ("box already drawn");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(assign row)---------------------*/
   x_node->n_row = s_cols [x_node->n_level];
   DEBUG_PROG   yLOG_value   ("n_row aft" , x_node->n_row);
   ++(s_cols [x_node->n_level]);
   /*---(show box)-----------------------*/
   yASCII_box_grid (x_node->n_level, x_node->n_row, x_node->n_name, "", '-', x_node->n_cpred, x_node->n_csucc);
   /*---(increment boxes)----------------*/
   ++s_boxes;
   DEBUG_PROG   yLOG_value   ("s_boxes"   , s_boxes);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_block_layer        (char a_block, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   tNODE      *x_root      = NULL;
   tEDGE      *x_pred      = NULL;
   tNODE      *x_node      = NULL;
   char        c           =    0;
   char        x_miss      [LEN_RECD]  = "";
   char        s           [LEN_TITLE] = "";
   char        x_lvl       =    0;
   char        x_heavy     = YASCII_DOTTED;
   int         i           =   -1;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_complex ("a_args"    , "%2db, %2dn", a_block, n);
   /*---(mark)------------------------*/
   x_root = &(g_nodes [n]);
   DEBUG_PROG   yLOG_info    ("name"      , g_nodes [n].n_name);
   ystrlcpy (x_miss, x_root->n_miss, LEN_RECD);
   DEBUG_PROG   yLOG_info    ("n_deps"    , x_root->n_deps);
   DEBUG_PROG   yLOG_info    ("x_miss"    , x_miss);
   /*---(walk predessors)-------------*/
   for (x_lvl = x_root->n_level - 1; x_lvl >= 0; --x_lvl) {
      x_pred = x_root->n_hpred;
      DEBUG_PROG   yLOG_point   ("head"      , x_pred);
      while (x_pred != NULL) {
         x_node = x_pred->e_beg;
         DEBUG_PROG   yLOG_complex ("detail"    , "%2d %s", x_node->n_level, x_node->n_name);
         if (x_node->n_level == x_lvl) {
            /*---(prepare)------------------*/
            sprintf  (s, ",%s,", x_node->n_name);
            DEBUG_PROG   yLOG_info    ("s"         , s);
            /*---(draw box)-----------------*/
            rc = DRAW_box (a_block, x_node->n_self);
            DEBUG_PROG   yLOG_value   ("box"       , rc);
            /*> if (x_node->n_row < 0) {                                                                                        <* 
             *>    x_node->n_row = s_cols [x_node->n_level];                                                                    <* 
             *>    ++(s_cols [x_node->n_level]);                                                                                <* 
             *>    yASCII_box_grid (x_node->n_level, x_node->n_row, x_node->n_name, "", '-', x_node->n_cpred, x_node->n_csucc);   <* 
             *>    ++s_boxes;                                                                                                   <* 
             *> }                                                                                                               <*/
            /*---(add connection)-----------*/
            if (strstr (x_miss, s) != NULL) {
               DRAW_block_layer (a_block, x_pred->e_nbeg);
               DEBUG_PROG   yLOG_char    ("e_type"    , x_pred->e_type);
               switch (x_pred->e_type) {
               case 'v' : x_heavy = YASCII_WAVY;    break;
               default  : x_heavy = YASCII_DOTTED;  break;
               }
               rc = yASCII_tie_grid_heavy (x_heavy, x_node->n_level, x_node->n_row, x_root->n_level, x_root->n_row);
               DEBUG_PROG   yLOG_value   ("tie"       , rc);
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
   i = DRAW_block_by_abbr (a_block);
   if (i >= 0) {
      DEPS_merge (g_nodes [n].n_cumd, zASCII_blocks [i].b_deps);
      sprintf (s, ",%s,", g_nodes [n].n_name);
      DEPS_merge (s, zASCII_blocks [i].b_deps);
      /*> printf ("%c %-20.20s  %s  å%sæ¦", zASCII_blocks [i].b_abbr, zASCII_blocks [i].b_title, g_nodes [n].n_name, zASCII_blocks [i].b_deps);   <*/
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
}

char
DRAW_block_source       (char a_block, char a_prog [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         b           =   -1;
   int         n           =   -1;
   tNODE      *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_char    ("a_block"   , a_block);
   --rce;  if (a_block == 0 || strchr (YSTR_GREEK, a_block) == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
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
   /*---(get block)----------------------*/
   --rce;  for (b = 0; b < LEN_LABEL; ++b) {
      if (zASCII_blocks [b].b_abbr == '\0') {
         DEBUG_PROG   yLOG_note    ("block not found");
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (zASCII_blocks [b].b_abbr != a_block)  continue;
      break;
   }
   DEBUG_PROG   yLOG_value   ("b"         , b);
   /*---(get root)-----------------------*/
   n = GRAPH_by_name (a_prog);
   DEBUG_PROG   yLOG_value   ("n"         , n);
   --rce;  if (n <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update root)--------------------*/
   rc = DRAW_box (a_block, n);
   DEBUG_PROG   yLOG_value   ("box"       , rc);
   /*> x_node = &(g_nodes [n]);                                                                                     <* 
    *> x_node->n_row = s_cols [x_node->n_level];                                                                    <* 
    *> ++(s_cols [x_node->n_level]);                                                                                <* 
    *> yASCII_box_grid (x_node->n_level, x_node->n_row, x_node->n_name, "", '-', x_node->n_cpred, x_node->n_csucc);   <* 
    *> ++s_boxes;                                                                                                   <*/
   /*---(start process)------------------*/
   DRAW_block_layer (a_block, n);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                                          <* 
 *> DRAW_block              (char a_block)                                                                        <* 
 *> {                                                                                                             <* 
 *>    char        rce         =  -10;                                                                            <* 
 *>    int         i           =    0;                                                                            <* 
 *>    int         n           =    0;                                                                            <* 
 *>    tNODE      *x_node      = NULL;                                                                            <* 
 *>    for (i = 0; i < MAX_INCL; ++i) {                                                                           <* 
 *>       if (g_incls [i].i_cat == 0)   break;                                                                    <* 
 *>       if (a_block != g_incls [i].i_block)  continue;                                                          <* 
 *>       n = GRAPH_by_name (g_incls [i].i_name);                                                                 <* 
 *>       x_node = &(g_nodes [n]);                                                                                <* 
 *>       x_node->n_row = s_cols [x_node->n_level];                                                               <* 
 *>       ++(s_cols [x_node->n_level]);                                                                           <* 
 *>       yASCII_box_grid (x_node->n_level, x_node->n_row, x_node->n_name, "", x_node->n_cpred, x_node->n_csucc);   <* 
 *>    }                                                                                                          <* 
 *>    return 0;                                                                                                  <* 
 *> }                                                                                                             <*/

char
DRAW_box_clear          (void)
{
   int         i           =    0;
   /*---(reset)--------------------------*/
   for (i = 0; i < MAX_LEVEL; ++i) s_cols  [i]         =   0;
   for (i = 0; i < g_nnode; ++i)   g_nodes [i].n_row   =  -1;
   for (i = 0; i < g_nnode; ++i)   g_nodes [i].n_block = '-';
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

char
GRAPH_dump_placement    (void)
{
   int         i           =    0;
   char        x_lvl       =    0;
   int         c           =    0;
   tEDGE      *x_pred      = NULL;
   printf ("\n\nouroboros drawing placement\n\n");
   for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) {
      for (i = 0; i <  g_nnode; ++i) {
         if (g_nodes [i].n_level != x_lvl)  continue;
         printf ("%3d  %3d  %3d  %-25.25s", i, g_nodes [i].n_level, g_nodes [i].n_row, g_nodes [i].n_name);
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
DRAW__unit              (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         i           =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (my.unit_answer, "DRAW             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if (strcmp (a_question, "sizing"        )  == 0) {
      snprintf (my.unit_answer, LEN_RECD, "DRAW sizing      : %c %c %c   H %3d# %3dn %3dx %3dr %3ds %3dw %3dg   V %3d# %3dn %3dx %3db %3ds %3dt %3dg",
            my.d_layout, my.d_size, my.d_decor,
            my.x_cols, my.x_min, my.x_max, my.x_end, my.x_side, my.x_wide, my.x_gap,
            my.y_rows, my.y_min, my.y_max, my.y_end, my.y_side, my.y_tall, my.y_gap);
   }
   else if (strcmp (a_question, "block_deps"    )  == 0) {
      i = DRAW_block_by_abbr (n);
      if (i >= 0) snprintf (my.unit_answer, LEN_RECD, "DRAW deps    (%c) : %s", n, zASCII_blocks [i].b_deps);
      else        snprintf (my.unit_answer, LEN_RECD, "DRAW deps    (%c) : (n/a)", n);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}




