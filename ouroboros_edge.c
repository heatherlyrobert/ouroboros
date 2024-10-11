/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



tEDGE   g_edges   [MAX_EDGE];
int     g_nedge     =  0;
char    g_maxlvl    =  0;




/*====================------------------------------------====================*/
/*===----                     create and destroy                       ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
EDGE__wipe              (tEDGE *a_dst)
{
   /*---(link)--------------*/
   a_dst->e_source     = NULL;
   a_dst->e_target     = NULL;
   /*---(working)-----------*/
   a_dst->e_filled     = '-';
   a_dst->e_type       = '-';
   a_dst->e_used       = '-';
   /*---(predecessors)------*/
   a_dst->e_pprev      = NULL;
   a_dst->e_pnext      = NULL;
   /*---(successors)--------*/
   a_dst->e_sprev      = NULL;
   a_dst->e_snext      = NULL;
   /*---(sorting)-----------*/
   a_dst->e_unique [0] = '\0';
   a_dst->e_ysort      = NULL;
   /*---(done)--------------*/
   return 0;
}

char
EDGE__new               (tNODE *a_source, tNODE *a_target, char a_force, tEDGE **r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_unique    [LEN_DESC]  = "";
   tEDGE      *x_new       = NULL;
   int         x_tries     =    0;
   char        x_verb      =  '·';
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default return)-----------------*/
   DEBUG_DATA   yLOG_point   ("r_new"     , r_new);
   --rce;  if (r_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*r_new"    , *r_new);
   DEBUG_DATA   yLOG_char    ("a_force"   , a_force);
   if (a_force == 'y' && *r_new != NULL) {
      *r_new = NULL;
      DEBUG_DATA   yLOG_note    ("force mode grounds existing pointer");
   }
   --rce;  if (*r_new != NULL)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->n_name"  , a_source->n_name);
   DEBUG_DATA   yLOG_point   ("a_target"  , a_target);
   --rce;  if (a_target == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->n_name"  , a_target->n_name);
   /*---(make key)-----------------------*/
   snprintf (x_unique, LEN_DESC, "%-20.20s Ö %s", a_source->n_name, a_target->n_name);
   DEBUG_DATA   yLOG_info    ("x_unique"  , x_unique);
   /*---(check for duplicate)------------*/
   rc = ySORT_by_name (B_EDGE, x_unique, &x_new);
   DEBUG_DATA   yLOG_point   ("x_exist"   , x_new);
   --rce;  if (x_new != NULL) {
      if (r_new != NULL)  *r_new = x_new;
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tEDGE *)  malloc (sizeof (tEDGE));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   EDGE__wipe (x_new);
   /*---(populate base)------------------*/
   x_new->e_source = a_source;
   x_new->e_target = a_target;
   ystrlcpy (x_new->e_unique, x_unique, LEN_DESC);
   /*---(hook tsae)----------------------*/
   rc = ySORT_hook (B_EDGE, x_new, x_new->e_unique, &(x_new->e_ysort));
   DEBUG_DATA   yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ySORT_prepare (B_EDGE);
   DEBUG_DATA   yLOG_value   ("prep edges", rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save return)--------------------*/
   if (r_new != NULL)  *r_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE__free              (tEDGE **r_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("r_old"     , r_old);
   --rce;  if (r_old == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*r_old"    , *r_old);
   --rce;  if (*r_old == NULL) {
      DEBUG_DATA   yLOG_note    ("never set");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ySORT_unhook (&((*r_old)->e_ysort));
   DEBUG_DATA   yLOG_value   ("wave"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = ySORT_prepare (B_EDGE);
   DEBUG_DATA   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear and free)-----------------*/
   free (*r_old);
   /*---(ground the pointer)-------------*/
   *r_old = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      program level                           ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
EDGE_init               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ySORT_btree (B_EDGE, "edges");
   DEBUG_PROG   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE_wrap               (void)
{
   EDGE_purge ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       edge handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___EDGES___________o () { return; }

char
EDGE__hook_source       (tNODE *a_source, tEDGE *a_edge)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("source"    , a_source->n_name);
   DEBUG_PROG   yLOG_point   ("a_edge"    , a_edge);
   --rce;  if (a_edge == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update edge with node)----------*/
   a_edge->e_source = a_source;
   /*---(beg-point on node)--------------*/
   if (a_source->n_hsucc == NULL) { /* first */
      DEBUG_PROG   yLOG_note    ("first successor");
      a_source->n_hsucc = a_edge;
   } else {  /*----------------------- append */
      DEBUG_PROG   yLOG_note    ("append successor");
      a_edge->e_sprev              = a_source->n_tsucc;
      (a_source->n_tsucc)->e_snext = a_edge;
   }
   a_source->n_tsucc = a_edge;
   /*---(update node count)--------------*/
   ++(a_source->n_csucc);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE__hook_target       (tNODE *a_target, tEDGE *a_edge)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_target"  , a_target);
   --rce;  if (a_target == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("target"    , a_target->n_name);
   DEBUG_PROG   yLOG_point   ("a_edge"    , a_edge);
   --rce;  if (a_edge == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update edge with node)----------*/
   a_edge->e_target = a_target;
   /*---(end-point on node)--------------*/
   if (a_target->n_hpred == NULL) { /* first */
      DEBUG_PROG   yLOG_note    ("first predecessor");
      a_target->n_hpred = a_edge;
   } else {  /*----------------------- append */
      DEBUG_PROG   yLOG_note    ("append predecessor");
      a_edge->e_pprev              = a_target->n_tpred;
      (a_target->n_tpred)->e_pnext = a_edge;
   }
   a_target->n_tpred = a_edge;
   /*---(update node count)--------------*/
   ++(a_target->n_cpred);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE_add                (tNODE *a_source, tNODE *a_target, char a_type, tEDGE **r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEDGE      *x_edge      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("source"    , a_source->n_name);
   DEBUG_PROG   yLOG_point   ("a_target"  , a_target);
   --rce;  if (a_target == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("target"    , a_target->n_name);
   --rce;  if (a_source == a_target) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(filter)-------------------------*/
   rc = EDGE__new (a_source, a_target, '-', &x_edge);
   DEBUG_PROG   yLOG_value   ("new"       , rc);
   DEBUG_PROG   yLOG_point   ("x_edge"    , x_edge);
   --rce;  if (rc < 0 || x_edge == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(hook)---------------------------*/
   rc = EDGE__hook_source (a_source, x_edge);
   DEBUG_PROG   yLOG_value   ("source"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = EDGE__hook_target (a_target, x_edge);
   DEBUG_PROG   yLOG_value   ("target"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_new != NULL)  *r_new = x_edge;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE_add_by_names       (char a_source [LEN_LABEL], char a_target [LEN_LABEL], char a_type, tEDGE **r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_source    = NULL;
   tNODE      *x_target    = NULL;
   tEDGE      *x_edge      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_target"  , a_target);
   --rce;  if (a_target == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find)---------------------------*/
   rc = NODE_by_name (a_source, &x_source);
   DEBUG_PROG   yLOG_value   ("source"    , rc);
   --rce;  if (rc < 0 || x_source == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("source"    , x_source->n_name);
   rc = NODE_by_name (a_target, &x_target);
   DEBUG_PROG   yLOG_value   ("target"    , rc);
   --rce;  if (rc < 0 || a_target == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("target"    , x_target->n_name);
   /*---(add)----------------------------*/
   rc = EDGE_add (x_source, x_target, a_type, &x_edge);
   DEBUG_PROG   yLOG_value   ("add"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_new != NULL)  *r_new = x_edge;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE__unhook_source     (tEDGE *a_edge)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   tNODE      *x_source    = NULL;
   tEDGE      *x_curr      = NULL;
   tEDGE      *x_prev      = NULL;
   tEDGE      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_edge"    , a_edge);
   --rce;  if (a_edge == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_source = a_edge->e_source;
   DEBUG_PROG   yLOG_point   ("x_source"  , x_source);
   --rce;  if (x_source == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("x_source"  , x_source);
   /*---(find link)----------------------*/
   x_curr = x_source->n_hsucc;
   while (x_curr != a_edge) {
      DEBUG_PROG   yLOG_complex ("x_curr"    , "%2d, %p", i++, x_curr);
      if (x_curr == NULL)  break;
      x_curr = x_curr->e_snext;
   }
   --rce;  if (x_curr   == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get key pointers)---------------*/
   x_prev = x_curr->e_sprev;
   x_next = x_curr->e_snext;
   DEBUG_PROG   yLOG_complex ("edges"     , "%p <- %p -> %p", x_prev, x_curr, x_next);
   /*---(unhook)-------------------------*/
   if (x_next != NULL)  x_next->e_sprev    = x_curr->e_sprev;
   else                 x_source->n_tsucc  = x_curr->e_sprev;
   if (x_prev != NULL)  x_prev->e_snext    = x_curr->e_snext;
   else                 x_source->n_hsucc  = x_curr->e_snext;
   /*---(cleanse)------------------------*/
   a_edge->e_source = NULL;
   a_edge->e_sprev  = NULL;
   a_edge->e_snext  = NULL;
   /*---(update node count)--------------*/
   --(x_source->n_csucc);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE__unhook_target     (tEDGE *a_edge)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   tNODE      *x_target    = NULL;
   tEDGE      *x_curr      = NULL;
   tEDGE      *x_prev      = NULL;
   tEDGE      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_edge"    , a_edge);
   --rce;  if (a_edge == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_target = a_edge->e_target;
   DEBUG_PROG   yLOG_point   ("x_target"  , x_target);
   --rce;  if (x_target == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("x_target"  , x_target);
   /*---(find link)----------------------*/
   x_curr = x_target->n_hpred;
   while (x_curr != a_edge) {
      DEBUG_PROG   yLOG_complex ("x_curr"    , "%2d, %p", i++, x_curr);
      if (x_curr == NULL)  break;
      x_curr = x_curr->e_pnext;
   }
   --rce;  if (x_curr   == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get key pointers)---------------*/
   x_prev = x_curr->e_pprev;
   x_next = x_curr->e_pnext;
   DEBUG_PROG   yLOG_complex ("edges"     , "%p <- %p -> %p", x_prev, x_curr, x_next);
   /*---(unhook)-------------------------*/
   if (x_next != NULL)  x_next->e_pprev    = x_curr->e_pprev;
   else                 x_target->n_tpred  = x_curr->e_pprev;
   if (x_prev != NULL)  x_prev->e_pnext    = x_curr->e_pnext;
   else                 x_target->n_hpred  = x_curr->e_pnext;
   /*---(cleanse)------------------------*/
   a_edge->e_target = NULL;
   a_edge->e_pprev  = NULL;
   a_edge->e_pnext  = NULL;
   /*---(update node count)--------------*/
   --(x_target->n_cpred);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE_remove             (tEDGE **b_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEDGE      *x_edge      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("b_old"     , b_old);
   --rce;  if (b_old == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("*b_old"    , *b_old);
   --rce;  if (*b_old == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(simplify pointer ref)-----------*/
   x_edge = *b_old;
   DEBUG_PROG   yLOG_info    ("unique"    , x_edge->e_unique);
   /*---(unhook)-------------------------*/
   rc = EDGE__unhook_source (x_edge);
   DEBUG_PROG   yLOG_value   ("source"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = EDGE__unhook_target (x_edge);
   DEBUG_PROG   yLOG_value   ("target"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   rc = EDGE__free (&x_edge);
   DEBUG_PROG   yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   if (b_old != NULL)  *b_old = NULL;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE_purge              (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tEDGE      *x_edge      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_cursor (B_EDGE, YDLST_HEAD, &x_edge);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_edge);
   while (rc >= 0 && x_edge != NULL) {
      rc = EDGE_remove (&x_edge);
      if (rc < 0)  break;
      rc = ySORT_by_cursor (B_EDGE, YDLST_HEAD, &x_edge);
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_edge);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE_purge_for_node     (tNODE *a_node)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         n           =    0;
   tEDGE      *x_edge      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_index  (B_EDGE, n, &x_edge);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_edge);
   while (rc >= 0 && x_edge != NULL) {
      if (x_edge->e_source == a_node || x_edge->e_target == a_node) {
         rc = EDGE_remove (&x_edge);
      } else ++n;
      if (rc < 0)  break;
      rc = ySORT_by_index  (B_EDGE, n, &x_edge);
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_edge);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                     searching and finding                    ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  EDGE_count     (void)                                    { return  ySORT_count     (B_EDGE); }
char EDGE_by_path   (char a_path [LEN_DESC] , tEDGE **r_cur)  { return  ySORT_by_name   (B_EDGE, a_path, r_cur); }
int  EDGE_by_index  (int  n                 , tEDGE **r_cur)  { return  ySORT_by_index  (B_EDGE, n     , r_cur); }
char EDGE_by_cursor (char a_dir             , tEDGE **r_cur)  { return  ySORT_by_cursor (B_EDGE, a_dir , r_cur); }





/*> /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *> char        rce         =  -10;                                                          <* 
 *> int         x_beg       =    0;                                                          <* 
 *> /+---(header)-------------------------+/                                                 <* 
 *> DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                <* 
 *> /+---(defense)------------------------+/                                                 <* 
 *> /+---(check for duplicate)------------+/                                                 <* 
 *> x_pred = g_nodes [a_end].n_hpred;                                                        <* 
 *> while (x_pred != NULL) {                                                                 <* 
 *>    if (strcmp (x_pred->e_beg->n_name, a_beg) == 0) {                                     <* 
 *>       DEBUG_PROG   yLOG_note    ("found pre-existing, duplicate edge");                  <* 
 *>       DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                          <* 
 *>       return 1;                                                                          <* 
 *>    }                                                                                     <* 
 *>    x_pred = x_pred->e_pnext;                                                             <* 
 *> }                                                                                        <* 
 *> DEBUG_PROG   yLOG_note    ("not duplicate");                                             <* 
 *> /+---(beg-point on edge)--------------+/                                                 <* 
 *> x_beg = GRAPH_add_node (a_beg);                                                          <* 
 *> DEBUG_PROG   yLOG_value   ("x_beg"     , x_beg);                                         <* 
 *> --rce;  if (x_beg < 0) {                                                                 <* 
 *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>    return rce;                                                                           <* 
 *> }                                                                                        <* 
 *> --rce;  if (x_beg == a_end) {                                                            <* 
 *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>    return rce;                                                                           <* 
 *> }                                                                                        <* 
 *> /+---(set type)-----------------------+/                                                 <* 
 *> g_edges [g_nedge].e_type = a_type;                                                       <* 
 *> /+---(beg-point on edge)--------------+/                                                 <* 
 *> g_edges [g_nedge].e_nbeg = x_beg;                                                        <* 
 *> g_edges [g_nedge].e_beg  = &(g_nodes [x_beg]);                                           <* 
 *> /+---(beg-point on node)--------------+/                                                 <* 
 *> if (g_nodes [x_beg].n_hsucc == NULL) { /+ first +/                                       <* 
 *>    DEBUG_PROG   yLOG_note    ("first successor");                                        <* 
 *>    g_nodes [x_beg].n_hsucc = &(g_edges [g_nedge]);                                       <* 
 *> } else {  /+                          append +/                                          <* 
 *>    DEBUG_PROG   yLOG_note    ("append successor");                                       <* 
 *>    (g_nodes [x_beg].n_tsucc)->e_snext = &(g_edges [g_nedge]);                            <* 
 *> }                                                                                        <* 
 *> g_nodes [x_beg].n_tsucc = &(g_edges [g_nedge]);                                          <* 
 *> ++(g_nodes [x_beg].n_csucc);                                                             <* 
 *> /+---(end-point on edge)--------------+/                                                 <* 
 *> g_edges [g_nedge].e_nend = a_end;                                                        <* 
 *> g_edges [g_nedge].e_end  = &(g_nodes [a_end]);                                           <* 
 *> /+---(end-point on node)--------------+/                                                 <* 
 *> if (g_nodes [a_end].n_hpred == NULL) { /+ first +/                                       <* 
 *>    DEBUG_PROG   yLOG_note    ("first predecessor");                                      <* 
 *>    g_nodes [a_end].n_hpred = &(g_edges [g_nedge]);                                       <* 
 *> } else {  /+                          append +/                                          <* 
 *>    DEBUG_PROG   yLOG_note    ("append predecessor");                                     <* 
 *>    (g_nodes [a_end].n_tpred)->e_pnext = &(g_edges [g_nedge]);                            <* 
 *> }                                                                                        <* 
 *> g_nodes [a_end].n_tpred = &(g_edges [g_nedge]);                                          <* 
 *> ++(g_nodes [a_end].n_cpred);                                                             <* 
 *> /+---(counter)------------------------+/                                                 <* 
 *> ++g_nedge;                                                                               <* 
 *> DEBUG_PROG   yLOG_value   ("g_nedge"   , g_nedge);                                       <* 
 *> /+---(check for solo)-----------------+/                                                 <* 
 *> /+> DEBUG_PROG   yLOG_info    ("b_name"    , g_nodes [x_beg].n_name);              <+/   <* 
 *> /+> DEBUG_PROG   yLOG_info    ("e_name"    , g_nodes [a_end].n_name);              <+/   <* 
 *> /+> if (strcmp (g_nodes [x_beg].n_name, "zenodotus") == 0) {                       <*    <* 
 *>  *>    if (strstr (g_nodes [a_end].n_name, "_solo") != NULL) {                     <*    <* 
 *>  *>       DEBUG_PROG   yLOG_note    ("call to add tie to _solo");                  <*    <* 
 *>  *>    }                                                                           <*    <* 
 *>  *> }                                                                              <+/   <* 
 *> /+---(complete)-----------------------+/                                           
 *> DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                <* 
 *> return 0;                                                                                <*/

/*> char EDGE_real         (char a_beg [LEN_TITLE], int a_end) { return EDGE_add ('r', a_beg, a_end); }   <*/
/*> char EDGE_virt         (char a_beg [LEN_TITLE], int a_end) { return EDGE_add ('v', a_beg, a_end); }   <*/



/*====================------------------------------------====================*/
/*===----                        report/dumping                        ----===*/
/*====================------------------------------------====================*/
static void  o___REPORT__________o () { return; }

/*  123456789-123456789-123456789-123456789-123456789- */
/*> SRC  123456789-123456789-  2 ° ´ · · · · · · · ·  */

char*
EDGE_line               (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEDGE      *x_edge      = NULL;
   tEDGE      *x_curr      = NULL;
   tNODE      *x_node      = NULL;
   int         x_count     =    0;
   int         i           =    0;
   char        x_unique    [LEN_RECD]  = "";
   char        x_source    [LEN_RECD]  = "";
   char        x_target    [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(find node)----------------------*/
   rc = EDGE_by_index (n, &x_edge);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4drc, %p", rc, x_edge);
   if (rc < 0 || x_edge == NULL) {
      DEBUG_PROG   yLOG_note    ("edge not found");
      snprintf (my.unit_answer, LEN_RECD, "EDGE full   (%2d) : ·    ·                     - · · · · · · · · · ·   · · ·   ·    ·                     - · · · · · · · · · ·   åæ", n);
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return my.unit_answer;
   }
   /*---(source)-------------------------*/
   x_node = x_edge->e_source;
   DEBUG_PROG   yLOG_point   ("x_node"    , x_node);
   if (x_node == NULL)    snprintf (x_source, LEN_RECD, "SRC  (null)");
   else {
      x_count = x_node->n_csucc;
      DEBUG_PROG   yLOG_complex ("edges"     , "%2d, %-10.10p, %p", x_count, x_node->n_hsucc, x_node->n_tsucc);
      if (x_count == 0)   snprintf (x_source, LEN_RECD, "SRC  %-20.20s  - · · · · · · · · · ·", x_node->n_name);
      else {
         snprintf (x_source, LEN_RECD, "SRC  %-20.20s %2d", x_node->n_name, x_count);
         x_curr = x_node->n_hsucc;
         for (i = 0; i < 10; ++i) {
            DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %4d, %-10.10p, %p", i, x_count, x_edge, x_curr);
            if      (i >= x_count)       ystrlcat (x_source, " ·", LEN_RECD);
            else if (x_curr == x_edge)   ystrlcat (x_source, " °", LEN_RECD);
            else if (x_curr == NULL)     ystrlcat (x_source, " ¢", LEN_RECD);
            else                         ystrlcat (x_source, " ´", LEN_RECD);
            if (x_curr != NULL)          x_curr = x_curr->e_snext;
         }
      }
   }
   /*---(target)-------------------------*/
   x_node = x_edge->e_target;
   DEBUG_PROG   yLOG_point   ("x_node"    , x_node);
   if (x_node == NULL)    snprintf (x_target, LEN_RECD, "TRG  (null)");
   else {
      x_count = x_node->n_cpred;
      DEBUG_PROG   yLOG_complex ("edges"     , "%2d, %-10.10p, %p", x_count, x_node->n_hpred, x_node->n_tpred);
      if (x_count == 0)   snprintf (x_target, LEN_RECD, "TRG  %-20.20s  - · · · · · · · · · ·", x_node->n_name);
      else {
         snprintf (x_target, LEN_RECD, "TRG  %-20.20s %2d", x_node->n_name, x_count);
         x_curr = x_node->n_hpred;
         for (i = 0; i < 10; ++i) {
            DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %4d, %-10.10p, %p", i, x_count, x_edge, x_curr);
            if      (i >= x_count)       ystrlcat (x_target, " ·", LEN_RECD);
            else if (x_curr == x_edge)   ystrlcat (x_target, " °", LEN_RECD);
            else if (x_curr == NULL)     ystrlcat (x_target, " ¢", LEN_RECD);
            else                         ystrlcat (x_target, " ´", LEN_RECD);
            if (x_curr != NULL)          x_curr = x_curr->e_pnext;
         }
      }
   }
   /*---(concatenate)--------------------*/
   sprintf (x_unique, "å%sæ", x_edge->e_unique);
   snprintf (my.unit_answer, LEN_RECD, "EDGE full   (%2d) : %-50.50s %c %c %c   %-50.50s %s", n, x_source, x_edge->e_filled, x_edge->e_type, x_edge->e_used, x_target, x_unique);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return my.unit_answer;
}

/*> EDGE nodes  ( 0) : src  2 ´ Ï                   tar  2 Ï ´                                                     <*/


char
EDGE_dump               (void)
{
   /*> int         i           =    0;                                                                                                                                        <* 
    *> DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                                                                                              <* 
    *> DEBUG_PROG   yLOG_value   ("g_nedge"   , g_nedge);                                                                                                                     <* 
    *> for (i = 0; i <  g_nedge; ++i) {                                                                                                                                       <* 
    *>    printf ("%3d  %3d %-25.25s  %3d %-25.25s¦", i, g_edges [i].e_nbeg, g_nodes [g_edges [i].e_nbeg].n_name, g_edges [i].e_nend, g_nodes [g_edges [i].e_nend].n_name);   <* 
    *> }                                                                                                                                                                      <* 
    *> DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                                                                                              <* 
    *> return 0;                                                                                                                                                              <*/
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*
EDGE__unit              (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   char        s           [LEN_DESC]  = "";
   char        t           [LEN_HUND]  = "";
   char        u           [LEN_HUND]  = "";
   tEDGE      *x_cur       = NULL;
   char        i           =    0;
   char        x_focus     =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (my.unit_answer, "EDGE             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if (strcmp (a_question, "full"          )  == 0) {
      rc = EDGE_by_index (n, &x_cur);
      ystrlcpy (my.unit_answer, EDGE_line (n), LEN_RECD);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}

