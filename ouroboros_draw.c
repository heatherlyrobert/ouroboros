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
} s_blocks [LEN_LABEL] = {
   /*----- -block-  ---title------------- ---focus----------- -a- ---label----------------- -a- ---label----------------- -a- ---label----------------- -a- ---label----------------- */
   { 'F' , "I"    , "FOUNDATION"         , "ySTR,yENV"       ,  1, "build∑base"            ,  4, "unit∑testing∑framework",  6, "execution∑logging"     , 99, "core"                   },
   { '\0', ""     , "end"                , ""                , -1, ""                      , -1, ""                      , -1, ""                      , -1, ""                       },
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
   yASCII_grid (a_ornament, my.x_min, my.y_min);
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
DRAW_vertical           (short x)
{
   int         i           =    0;
   DRAW_single ('â', x,  1);
   for (i = 2; i <= my.y_end - 2; ++i) DRAW_single ('Å', x,  i);
   DRAW_single ('ä', x,  4);
   DRAW_single ('à', x,  my.y_end - 1);
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
      yASCII_print (my.x_min, my.y_end - 1, "## end-of-file.  done, finito, completare, whimper [œ¥∑∑∑", YASCII_CLEAR);
   }
   else if (my.d_ornament == 'b') {
      yASCII_frame_full (0, 0, 7, 5, "I. FOUNDATION (14)", -1, "a)∑build∑base", 1, "b)∑unit∑testing∑framework", 4, "c)∑execution∑logging", 6, "d)∑core");
      yASCII_node (0, 6, 'Ë');
      yASCII_node (my.x_end - 5, 6, 'È');
      yASCII_tie_grid (-1, 0, 0, 0);
      yASCII_tie_grid ( 7, 0, 8, 0);
      yASCII_tie_grid ( 7, 1, 8, 0);
   }
   rc = yASCII_write (YSTR_CLIP);
   rc = yASCII_free  ();
   return 0;
}

char
DRAW_main               (char a_ornament, char a_style)
{
   DRAW_init    (a_ornament, a_style,  8,  6);
   DRAW_box_rooted ("ySTR");
   DRAW_box_rooted ("yENV");
   /*> DRAW_box_rooted ("ySTR_solo");                                                 <*/
   DRAW_wrap    ();
   return 0;
}

char
DRAW_boxes_OLD          (void)
{
   char        rc          =    0;
   int         i           =    0;
   char        x_name      [LEN_LABEL] = "testing";
   char        x_lvl       =    0;
   int         l           =    0;
   int         c           =    0;
   tEDGE      *x_pred      = NULL;
   yASCII_new (500,100);
   yASCII_print (0, 0, "ouroboros sequencing solution", YASCII_CLEAR);
   for (x_lvl = 0; x_lvl < g_maxlvl; ++x_lvl) {
      sprintf (x_name, "[----%02d----]", x_lvl);
      yASCII_print (x_lvl * 16, 2, x_name, YASCII_CLEAR);
   }
   for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) {
      c = 0;
      for (i = 0; i <  g_nnode; ++i) {
         /*---(filter)-------------------*/
         if (g_nodes [i].n_level != x_lvl)  continue;
         if (g_nodes [i].n_focus != '∞')    continue;
         /*---(make box)-----------------*/
         yASCII_print ((x_lvl * 16), 5 + (c * 5), "ÉÄÄÄÄÄÄÄÄÄÄÇ", YASCII_CLEAR);
         yASCII_print ((x_lvl * 16), 6 + (c * 5), "Å          Å", YASCII_CLEAR);
         yASCII_print ((x_lvl * 16), 7 + (c * 5), "ÑÄÄÄÄÄÄÄÄÄÄÖ", YASCII_CLEAR);
         ystrlcpy (x_name, g_nodes [i].n_name, 11);
         l = strlen (x_name);
         l = 6 - (l / 2);
         yASCII_print ((x_lvl * 16) + l, 6 + (c * 5), x_name, YASCII_CLEAR);
         /*> yASCII_connector    (x_left + 56, x_topp + 18, '÷', x_left + 71, x_topp + 18, '-', "mate"      , x_left + 61, x_topp + 17);   <*/
         ++c;
      }
   }
   /*> yASCII_uconnect (12,  6, '÷', 16,  6);                                         <*/
   /*> yASCII_uconnect (12, 11, '÷', 14,  6);                                         <*/
   rc = yASCII_write (YSTR_CLIP);
   rc = yASCII_free  ();
   return 0;
}

char
DRAW_boxes         (char a_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_lvl       =    0;
   char        x_name      [LEN_LABEL] = "testing";
   char        x_topp, x_wide, x_left, x_tall;
   /*---(prepare)------------------------*/
   switch (a_style) {
   case 'u'  : x_topp =  2; x_wide =  7; x_left = 1; x_tall = 3;  break;
   case '-'  : x_topp = 10; x_wide = 16; x_left = 1; x_tall = 5;  break;
   case 'l'  : x_topp = 15; x_wide = 23; x_left = 2; x_tall = 6;  break;
   }
   rc = yASCII_new (x_wide * g_maxlvl, 100);
   rc = yASCII_print (0, 0, "ouroboros sequencing solution", YASCII_CLEAR);
   /*---(create)-------------------------*/
   for (x_lvl = 0; x_lvl < g_maxlvl; ++x_lvl) {
      switch (a_style) {
      case 'u' : sprintf (x_name, "[-%02d-]", x_lvl);      break;
      case '-' : sprintf (x_name, "[----%02d----]", x_lvl);      break;
      case 'l' : sprintf (x_name, "[------%02d-------]", x_lvl); break;
      }
      yASCII_print (x_lvl * x_wide, 2, x_name, YASCII_CLEAR);
   }
   /*---(save)---------------------------*/
   rc = yASCII_write (YSTR_CLIP);
   rc = yASCII_free  ();
   /*---(complete)-----------------------*/
   return 0;
}

/*> char                                                                              <* 
 *> DRAW_node               (short x, short y, char a)                                <* 
 *> {                                                                                 <* 
 *>    char        s           [LEN_SHORT] = "";                                      <* 
 *>    yASCII_print (x, y    , "ÉÄÄÄÇ", YASCII_CLEAR);                                <* 
 *>    yASCII_print (x, y + 1, "Å   Å", YASCII_CLEAR);                                <* 
 *>    yASCII_print (x, y + 2, "ÑÄÄÄÖ", YASCII_CLEAR);                                <* 
 *>    sprintf (s, "%c", a);                                                          <* 
 *>    yASCII_print (x + 2, y + 1, s, YASCII_CLEAR);                                  <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                    <* 
 *> DRAW_box                (char a_col, char a_row, char a_name [LEN_TITLE], char a_npred, char a_nsucc)   <* 
 *> {                                                                                                       <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                             <* 
 *>    int         i           =    0;                                                                      <* 
 *>    short       x, y;                                                                                    <* 
 *>    char        x_line      [LEN_HUND]  = "";                                                            <* 
 *>    int         l           =    0;                                                                      <* 
 *>    short       y_save      =    0;                                                                      <* 
 *>    /+---(header)-------------------------+/                                                             <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                            <* 
 *>    DEBUG_PROG   yLOG_complex ("a_args"    , "%2dc, %2dr", a_col, a_row);                                <* 
 *>    /+---(prepare)------------------------+/                                                             <* 
 *>    x = my.x_min + (a_col * my.x_wide);                                                                  <* 
 *>    y = my.y_min + (a_row * my.y_tall);                                                                  <* 
 *>    DEBUG_PROG   yLOG_complex ("coords"    , "%4dx, %4dy", x, y);                                        <* 
 *>    y_save = y;                                                                                          <* 
 *>    /+---(top)----------------------------+/                                                             <* 
 *>    sprintf (x_line, "É%*.*sÇ", my.x_side, my.x_side, YSTR_HORZ);                                        <* 
 *>    yASCII_print (x, y, x_line, YASCII_CLEAR);                                                           <* 
 *>    /+---(middle)-------------------------+/                                                             <* 
 *>    sprintf (x_line, "Å%*.*sÅ", my.x_side, my.x_side, YSTR_EMPTY);                                       <* 
 *>    for (i = 1; i <= my.y_side; ++i) {                                                                   <* 
 *>       yASCII_print (x, y + i, x_line, YASCII_CLEAR);                                                    <* 
 *>    }                                                                                                    <* 
 *>    y += my.y_side;                                                                                      <* 
 *>    /+---(bottom)-------------------------+/                                                             <* 
 *>    sprintf (x_line, "Ñ%*.*sÖ", my.x_side, my.x_side, YSTR_HORZ);                                        <* 
 *>    yASCII_print (x, ++y, x_line, YASCII_CLEAR);                                                         <* 
 *>    /+---(note)---------------------------+/                                                             <* 
 *>    if (strcmp (a_name, "yLOG_solo")  == 0)   yASCII_print (x + 4, y, "(uv)", YASCII_CLEAR);             <* 
 *>    if (strcmp (a_name, "yURG_solo")  == 0)   yASCII_print (x + 4, y, "(uv)", YASCII_CLEAR);             <* 
 *>    if (strcmp (a_name, "yUNIT_solo") == 0)   yASCII_print (x + 4, y, "(uv)", YASCII_CLEAR);             <* 
 *>    if (strcmp (a_name, "yENV_solo")  == 0)   yASCII_print (x + 4, y, "(uv)", YASCII_CLEAR);             <* 
 *>    /+---(title)--------------------------+/                                                             <* 
 *>    ystrlcpy (x_line, a_name, my.x_side + 1);                                                            <* 
 *>    l = strlen (x_line);                                                                                 <* 
 *>    yASCII_print (x + 1, y_save + 1, x_line, YASCII_CLEAR);                                              <* 
 *>    /+---(stats)--------------------------+/                                                             <* 
 *>    if (my.y_gap > 0) {                                                                                  <* 
 *>       l = my.x_wide - my.x_gap - 2 - 6;                                                                 <* 
 *>       sprintf (x_line, "%-3d%*.*s%3d", a_npred, l, l, YSTR_EMPTY, a_nsucc);                             <* 
 *>       yASCII_print (x + 1, y + 1, x_line, YASCII_CLEAR);                                                <* 
 *>    }                                                                                                    <* 
 *>    /+---(complete)-----------------------+/                                                             <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                            <* 
 *>    return 0;                                                                                            <* 
 *> }                                                                                                       <*/

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
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
}

char
DRAW_box_layer_old      (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   tNODE      *x_root      = NULL;
   tEDGE      *x_pred      = NULL;
   tNODE      *x_node      = NULL;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(mark)------------------------*/
   DEBUG_PROG   yLOG_value   ("n"         , n);
   x_root = &(g_nodes [n]);
   DEBUG_PROG   yLOG_info    ("name"      , g_nodes [n].n_name);
   x_pred = x_root->n_phead;
   DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
   /*---(bottom)----------------------*/
   if (x_pred == NULL) {
      DEBUG_PROG   yLOG_note    ("hit start, tie to pre-node");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(walk predessors)-------------*/
   while (x_pred != NULL) {
      /*---(draw box)-----------------*/
      x_node = x_pred->e_beg;
      if (x_node->n_row < 0) {
         x_node->n_row = s_cols [x_node->n_level];
         ++(s_cols [x_node->n_level]);
         yASCII_box_grid (x_node->n_level, x_node->n_row, x_node->n_name, "", x_node->n_pred, x_node->n_succ);
      }
      /*---(call pred)----------------*/
      DRAW_box_layer (x_pred->e_nbeg);
      /*---(add connection)-----------*/
      yASCII_tie_grid (x_node->n_level, x_node->n_row, x_root->n_level, x_root->n_row);
      /*---(next)---------------------*/
      x_pred->e_used = 'y';
      ++c;
      x_pred = x_pred->e_pnext;
      DEBUG_PROG   yLOG_point   ("x_pred"    , x_pred);
      /*---(done)---------------------*/
   }
   DEBUG_PROG   yLOG_value   ("c"         , c);
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
/*===----                     line drawing version                     ----===*/
/*====================------------------------------------====================*/
static void  o__CONNECTOR________o () { return; }

/*
 *    É≤≤≤Ü   á≤≤≤Ç        É≤≤âÄÄÄâ≤≤Ç
 *    åÉ≤≤Ü   á≤≤Çå        åÉ≤Ü   á≤Çå
 *  á≤ÖåÉ≤Ü   á≤ÇåÑ≤Ü   ÄÄâÖåÉàÄÄÄàÇåÑâÄÄ
 *  á≤≤Öå       åÑ≤≤Ü     á≤Öå     åÑ≤Ü
 *  á≤≤≤Ö       Ñ≤≤≤Ü   ÄÄà≤≤Ö     Ñ≤≤àÄÄ   
 *
 *  á≤≤≤Ç       É≤≤≤Ü   ÄÄâ≤≤Ç     É≤≤âÄÄ
 *  á≤≤Çå       åÉ≤≤Ü     á≤Çå     åÉ≤Ü
 *  á≤ÇåÑ≤Ü   á≤ÖåÉ≤Ü   ÄÄàÇåÑâÄÄÄâÖåÉàÄÄ
 *    åÑ≤≤Ü   á≤≤Öå        åÑ≤Ü   á≤Öå 
 *    Ñ≤≤≤Ü   á≤≤≤Ö        Ñ≤≤àÄÄÄà≤≤Ö
 */
/*
 *  ∑ ≤  å  Ç  Ö  Ü  á  ä  â  à
 *
 *     
 *  á≤ ≤Ü      ≤
 *
 *
 *    å                   å
 *  á≤å≤Ü      ä        á≤å
 *    å                   Ñ≤Ü
 *                        
 *    å
 *  á≤Ö≤Ü      à
 *
 *
 *
 *  á≤≤≤Ü      ≤
 *
 *
 *
 *  á≤Ç≤Ü      â
 *    å
 *
 *    å
 *  á≤Ü≤Ü      ä
 *    å
 *
 */

static char s_mapping [LEN_LABEL][LEN_TITLE] = {
   /*            ------------- old ------------ */
   /*            123456789-123456789-123456789- */
   /* new */  { "  ≤ å Ä Å É Ö Ñ Ç Ü á â à ä ∑ " },
   /*  ≤  */  { "≤ ≤ ä Ä ä â à à â ä ä â à ä ≤ " },
   /*  å  */  { "å ä å ä Å á Ü á Ü Ü á ä ä ä å " },
   /*  Ä  */  { "Ä ≤ ä Ä ä â à à â ä ä â à ä Ä " },
   /*  Å  */  { "Å ä Å ä Å á Ü á Ü Ü á ä ä ä Å " },
   /*  É  */  { "É â á â á É ä á ä Ü á â ä ä É " },
   /*  Ö  */  { "Ö à Ü à Ü ä Ö ä Ü Ü ä ä à ä Ö " },
   /*  Ñ  */  { "Ñ à á à á á ä Ñ ä ä á ä à ä Ñ " },
   /*  Ç  */  { "Ç â Ü â Ü ä Ü ä Ü Ü ä â ä ä Ç " },
   /*  Ü  */  { "Ü ä Ü ä Ü ä Ü ä Ü Ü ä ä ä ä Ü " },
   /*  á  */  { "á ä á ä á á ä á ä ä á ä ä ä á " },
   /*  â  */  { "â â ä â ä â ä ä â ä ä â ä ä â " },
   /*  à  */  { "à à ä à ä ä à à ä ä ä ä à ä à " },
   /*  ä  */  { "ä ä ä ä ä ä ä ä ä ä ä ä ä ä ä " },
};

char
DRAW_single             (char a_new, short x, short y)
{
   /*---(locals)-----------+-----+-----+-*/
   char        c           =  '-';
   char        x_old       =   -1;
   char        x_new       =   -1;
   char       *p           = NULL;
   char        x_valid     [LEN_TITLE] = "";
   char        t           [LEN_SHORT] = "";
   /*---(enter)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_complex ("a_args"    , "%c, %3dx, %3dy", a_new, x, y);
   /*---(prepare)------------------------*/
   ystrlcpy (x_valid, s_mapping [0], LEN_TITLE);
   /*---(get old)------------------------*/
   c = yASCII_get (x, y);
   DEBUG_PROG   yLOG_complex ("c"         , "%3d/%c", c, ychrvisible (c));
   DEBUG_PROG   yLOG_value   ("c"         , c);
   DEBUG_PROG   yLOG_info    ("x_valid"   , x_valid);
   p = strchr (x_valid, c);
   DEBUG_PROG   yLOG_point   ("p"         , p);
   if (p == NULL) {
      DEBUG_PROG   yLOG_note    ("skip");
      /*> sprintf (t, "%c", a_new);                                                   <* 
       *> yASCII_print (x, y, t, YASCII_CLEAR);                                       <*/
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   x_old = p - x_valid;
   DEBUG_PROG   yLOG_value   ("x_old"     , x_old);
   /*---(get new)------------------------*/
   p = strchr (x_valid, a_new);
   DEBUG_PROG   yLOG_point   ("p"         , p);
   if (p == NULL) {
      DEBUG_PROG   yLOG_note    ("skip");
      /*> sprintf (t, "%c", a_new);                                                   <* 
       *> yASCII_print (x, y, t, YASCII_CLEAR);                                       <*/
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   x_new = (p - x_valid) / 2;
   DEBUG_PROG   yLOG_value   ("x_new"     , x_new);
   /*---(replace)------------------------*/
   ystrlcpy (x_valid, s_mapping [x_new], LEN_TITLE);
   DEBUG_PROG   yLOG_info    ("x_valid"   , x_valid);
   c = x_valid [x_old];
   DEBUG_PROG   yLOG_complex ("c"         , "%3d/%c", c, ychrvisible (c));
   sprintf (t, "%c", c);
   yASCII_print (x, y, t, YASCII_CLEAR);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return c;
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




