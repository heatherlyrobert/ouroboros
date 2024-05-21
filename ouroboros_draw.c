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
   if (a_ornament == 'b') {
      /*---(top)-------------------------*/
      l = my.x_max - my.x_min + 2;
      sprintf (s, "É%*.*sÇ", l, l, YSTR_HORZ);
      yASCII_print (my.x_min - 2, 1, s, YASCII_CLEAR);
      /*---(middle)----------------------*/
      sprintf (s, "Å%*.*sÅ", l, l, YSTR_EMPTY);
      for (i = 2; i <= my.y_end - 2; ++i)  yASCII_print (my.x_min - 2 + 0, i, s, YASCII_CLEAR);
      /*---(bottom)----------------------*/
      sprintf (s, "Ñ%*.*sÖ", l, l, YSTR_HORZ);
      yASCII_print (my.x_min - 2, my.y_end - 1, s, YASCII_CLEAR);
      /*---(title)-----------------------*/
      sprintf (s, "ÉÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÇ");
      yASCII_print (my.x_min + 2, 0, s, YASCII_CLEAR);
      sprintf (s, "Ü I. FOUNDATION (14) á");
      yASCII_print (my.x_min + 2, 1, s, YASCII_CLEAR);
      sprintf (s, "ÑÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÖ");
      yASCII_print (my.x_min + 2, 2, s, YASCII_CLEAR);
      yASCII_print (my.x_min + 30, 0, "absolutely everything relies (or should rely) on this block", YASCII_CLEAR);
      /*---(header line)-----------------*/
      sprintf (s, "Å%*.*sÅ", l, l, YSTR_EDOTS);
      yASCII_print (my.x_min - 2 +  0,  4, s, YASCII_CLEAR);
      yASCII_print (my.x_min - 2 +  2,  4, "a)∑build∑base"                        , YASCII_CLEAR);
      yASCII_print (my.x_min - 2 + 17 + my.x_wide,  4, "b)∑unit∑testing∑framework", YASCII_CLEAR);
      yASCII_print (my.x_min - 2 + 62 + my.x_wide,  4, "c)∑execution∑logging"     , YASCII_CLEAR);
      yASCII_print (my.x_min - 2 + 92 + my.x_wide,  4, "d)∑core"                  , YASCII_CLEAR);
      /*---(footer line)-----------------*/
      yASCII_print (my.x_min - 2 +   7, my.y_end - 1, "00", YASCII_CLEAR);
      yASCII_print (my.x_min - 2 +  22, my.y_end - 1, "01", YASCII_CLEAR);
      yASCII_print (my.x_min - 2 +  37, my.y_end - 1, "02", YASCII_CLEAR);
      yASCII_print (my.x_min - 2 +  52, my.y_end - 1, "03", YASCII_CLEAR);
      yASCII_print (my.x_min - 2 +  67, my.y_end - 1, "04", YASCII_CLEAR);
      yASCII_print (my.x_min - 2 +  82, my.y_end - 1, "05", YASCII_CLEAR);
      yASCII_print (my.x_min - 2 +  97, my.y_end - 1, "06", YASCII_CLEAR);
      yASCII_print (my.x_min - 2 + 112, my.y_end - 1, "07", YASCII_CLEAR);
      /*---(nodes)-----------------------*/
      yASCII_node (0, 6, 'Ë');
      yASCII_node (my.x_end - 5, 6, 'È');
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
      DRAW_vertical (my.x_min - 2 + 13 + my.x_wide);
      DRAW_vertical (my.x_min - 2 + 58 + my.x_wide);
      DRAW_vertical (my.x_min - 2 + 88 + my.x_wide);
      /*> yASCII_print  (my.x_min - 2 + 13 + my.x_wide,  2, "â", YASCII_CLEAR);       <*/
      DRAW_hconnect (-1, 0, 0, 0);
      DRAW_hconnect ( 7, 0,66, 0);
      DRAW_hconnect ( 7, 1,66, 0);
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

char
DRAW_box                (char a_col, char a_row, char a_name [LEN_TITLE], char a_npred, char a_nsucc)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   short       x, y;
   char        x_line      [LEN_HUND]  = "";
   int         l           =    0;
   short       y_save      =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_complex ("a_args"    , "%2dc, %2dr", a_col, a_row);
   /*---(prepare)------------------------*/
   x = my.x_min + (a_col * my.x_wide);
   y = my.y_min + (a_row * my.y_tall);
   DEBUG_PROG   yLOG_complex ("coords"    , "%4dx, %4dy", x, y);
   y_save = y;
   /*---(top)----------------------------*/
   sprintf (x_line, "É%*.*sÇ", my.x_side, my.x_side, YSTR_HORZ);
   yASCII_print (x, y, x_line, YASCII_CLEAR);
   /*---(middle)-------------------------*/
   sprintf (x_line, "Å%*.*sÅ", my.x_side, my.x_side, YSTR_EMPTY);
   for (i = 1; i <= my.y_side; ++i) {
      yASCII_print (x, y + i, x_line, YASCII_CLEAR);
   }
   y += my.y_side;
   /*---(bottom)-------------------------*/
   sprintf (x_line, "Ñ%*.*sÖ", my.x_side, my.x_side, YSTR_HORZ);
   yASCII_print (x, ++y, x_line, YASCII_CLEAR);
   /*---(note)---------------------------*/
   if (strcmp (a_name, "yLOG_solo")  == 0)   yASCII_print (x + 4, y, "(uv)", YASCII_CLEAR);
   if (strcmp (a_name, "yURG_solo")  == 0)   yASCII_print (x + 4, y, "(uv)", YASCII_CLEAR);
   if (strcmp (a_name, "yUNIT_solo") == 0)   yASCII_print (x + 4, y, "(uv)", YASCII_CLEAR);
   if (strcmp (a_name, "yENV_solo")  == 0)   yASCII_print (x + 4, y, "(uv)", YASCII_CLEAR);
   /*---(title)--------------------------*/
   ystrlcpy (x_line, a_name, my.x_side + 1);
   l = strlen (x_line);
   yASCII_print (x + 1, y_save + 1, x_line, YASCII_CLEAR);
   /*---(stats)--------------------------*/
   if (my.y_gap > 0) {
      l = my.x_wide - my.x_gap - 2 - 6;
      sprintf (x_line, "%-3d%*.*s%3d", a_npred, l, l, YSTR_EMPTY, a_nsucc);
      yASCII_print (x + 1, y + 1, x_line, YASCII_CLEAR);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
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
               DRAW_box (x_node->n_level, x_node->n_row, x_node->n_name, x_node->n_pred, x_node->n_succ);
            }
            /*---(add connection)-----------*/
            if (strstr (x_miss, s) != NULL) {
               DRAW_box_layer (x_pred->e_nbeg);
               DRAW_hconnect (x_node->n_level, x_node->n_row, x_root->n_level, x_root->n_row);
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
         DRAW_box (x_node->n_level, x_node->n_row, x_node->n_name, x_node->n_pred, x_node->n_succ);
      }
      /*---(call pred)----------------*/
      DRAW_box_layer (x_pred->e_nbeg);
      /*---(add connection)-----------*/
      DRAW_hconnect (x_node->n_level, x_node->n_row, x_root->n_level, x_root->n_row);
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
   DRAW_box (x_node->n_level, x_node->n_row, x_node->n_name, x_node->n_pred, x_node->n_succ);
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

char
DRAW_xconnect           (short bx, short by, short ex, short ey, char a_tall, char a_blane, char a_vlane, char a_elane)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_dir       =    0;
   int         i           =    0;
   /*---(enter)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_complex ("a_args"    , "%3dbx, %3dby, %3dex, %3dey, %1dbl, %1dvl, %1del", bx, by, ex, ey, a_tall, a_blane, a_vlane, a_elane);
   /*---(direction)----------------------*/
   if      (by + a_blane == ey + a_elane)   x_dir = '÷';
   else if (by + a_blane <  ey + a_elane)   x_dir = '’';
   else                                     x_dir = '‘';
   DEBUG_PROG   yLOG_char    ("x_dir"     , x_dir);
   /*---(start)--------------------------*/
   if      (a_blane == 0)        yASCII_print (bx, by          , "â", YASCII_CLEAR); 
   else if (a_blane == a_tall)   yASCII_print (bx, by + a_tall , "à", YASCII_CLEAR); 
   else                          yASCII_print (bx, by + a_blane, "á", YASCII_CLEAR); 
   /*---(finish)-------------------------*/
   if      (a_elane == 0)        yASCII_print (ex, ey          , "â", YASCII_CLEAR); 
   else if (a_elane == a_tall)   yASCII_print (ex, ey + a_tall , "à", YASCII_CLEAR); 
   else                          yASCII_print (ex, ey + a_elane, "Ü", YASCII_CLEAR); 
   /*---(connect)------------------------*/
   switch (x_dir) {
   case '÷' : 
      DEBUG_PROG   yLOG_note    ("horizontal");
      for (i = bx + 1; i <= ex - 1; ++i)        DRAW_single ('≤', i, by + a_blane);
      break;
   case '‘' : 
      DEBUG_PROG   yLOG_note    ("ascending/upward line");
      for (i = bx + 1; i < ex - a_vlane; ++i)  DRAW_single ('≤', i, by + a_blane);
      DRAW_single ('Ö', ex - 2, by + a_blane);
      for (i = by + a_blane - 1; i >= ey + a_elane + 1; --i)  DRAW_single ('å', ex - a_vlane, i);
      DRAW_single ('É', ex - 2, ey + a_elane);
      break;
   case '’' :
      DEBUG_PROG   yLOG_note    ("descending/downward line");
      DRAW_single ('Ç', bx + a_vlane, by + a_blane);
      for (i = by + a_blane + 1; i <= ey + a_elane - 1; ++i)  DRAW_single ('å', bx + a_vlane, i);
      DRAW_single ('Ñ', bx + 2, ey + a_elane);
      for (i = bx + a_vlane + 1; i <= ex - 1; ++i)  DRAW_single ('≤', i, ey + a_elane);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_hconnect           (char a_bcol, char a_brow, char a_ecol, char a_erow)
{
   /*---(locals)-----------+-----+-----+-*/
   short       bx, by, ex, ey;
   /*---(beginning)----------------------*/
   if (a_bcol == -1)    bx = my.x_min - 4;
   else                 bx = my.x_min + (a_bcol * my.x_wide) + my.x_wide - my.x_gap - 1;
   by = my.y_min + (a_brow * my.y_tall);
   /*---(ending)-------------------------*/
   if (a_ecol == 66)    ex = my.x_max + 3;
   else                 ex = my.x_min + (a_ecol * my.x_wide);
   ey = my.y_min + (a_erow * my.y_tall);
   /*---(complete)-----------------------*/
   return DRAW_xconnect (bx, by, ex, ey, my.y_tall - my.y_gap, 1, 2, 1);
}

char
DRAW_hconnect_OLD       (char a_bcol, char a_brow, char a_ecol, char a_erow)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_dir       =    0;
   int         i           =    0;
   int         x_beg, x_end;
   short       bx, by, ex, ey;
   /*---(enter)--------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_complex ("a_args"    , "%2dbc, %2dbr, %2dec, %2der", a_bcol, a_brow, a_ecol, a_erow);
   /*---(prepare)------------------------*/
   bx = my.x_min + (a_bcol * my.x_wide) + my.x_wide - my.x_gap - 1;
   by = my.y_min + (a_brow * my.y_tall) + 1;
   ex = my.x_min + (a_ecol * my.x_wide);
   ey = my.y_min + (a_erow * my.y_tall) + 1;
   /*---(direction)----------------------*/
   if      (by == ey)  { x_dir = '÷';  x_beg = x_end = by;  }
   else if (by <  ey)  { x_dir = '’';  x_beg = by + 1;  x_end = ey - 1;  }
   else                { x_dir = '‘';  x_beg = ey + 1;  x_end = by - 1;  }
   /*---(always)-------------------------*/
   yASCII_print (bx    , by, "á≤", YASCII_CLEAR); 
   yASCII_print (ex - 1, ey, "≤Ü", YASCII_CLEAR); 
   /*---(ends)---------------------------*/
   switch (x_dir) {
   case '÷' : 
      DEBUG_PROG   yLOG_note    ("horizontal");
      for (i = bx + 2; i <= ex - 2; ++i)  DRAW_single ('≤', i, by);
      break;
   case '‘' : 
      DEBUG_PROG   yLOG_note    ("ascending/upward line");
      for (i = bx + 2; i <= ex - 3; ++i)  DRAW_single ('≤', i, by);
      DRAW_single ('Ö', ex - 2, by);
      for (i = by - 1; i >= ey + 1; --i)  DRAW_single ('å', ex - 2, i);
      DRAW_single ('É', ex - 2, ey);
      break;
   case '’' :
      DEBUG_PROG   yLOG_note    ("descending/downward line");
      DRAW_single ('Ç', bx + 2, by);
      for (i = by + 1; i <= ey - 1; ++i)  DRAW_single ('å', bx + 2, i);
      DRAW_single ('Ñ', bx + 2, ey);
      for (i = bx + 3; i <= ex - 2; ++i)  DRAW_single ('≤', i, ey);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
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




