/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"

char
MAKE_gather             (char a_recd [LEN_RECD], int x_end)
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
   rc = INCL_add_by_name ("zenodotus", x_end);
   DEBUG_DATA   yLOG_value   ("add"       , rc);
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 1;
}

/*> char                                                                              <* 
 *> MAKE_gather             (char a_proj [LEN_TITLE], char a_file [LEN_PATH])         <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    char       *rcp         = NULL;                                                <* 
 *>    char        x_temp      [LEN_LABEL] = "/tmp/ouroboros.txt";                    <* 
 *>    char        x_cmd       [LEN_RECD]  = "";                                      <* 
 *>    char        x_recd      [LEN_RECD]  = "";                                      <* 
 *>    FILE       *f           =    0;                                                <* 
 *>    int         c           =    0;                                                <* 
 *>    int         x_end       =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_DATA  yLOG_enter   (__FUNCTION__);                                       <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_DATA   yLOG_point   ("a_file"    , a_file);                              <* 
 *>    --rce; if (a_file == NULL) {                                                   <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_DATA   yLOG_info    ("a_file"    , a_file);                              <* 
 *>    /+---(add project)--------------------+/                                       <* 
 *>    x_end = GRAPH_add_node (a_proj);                                               <* 
 *>    DEBUG_DATA   yLOG_value   ("x_end"     , x_end);                               <* 
 *>    /+---(prepare)------------------------+/                                       <* 
 *>    sprintf (x_cmd, "grep \"^include \" %s > %s 2> /dev/null", a_file, x_temp);    <* 
 *>    rc = system (x_cmd);                                                           <* 
 *>    DEBUG_DATA   yLOG_value   ("grep"      , rc);                                  <* 
 *>    --rce; if (rc < 0) {                                                           <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    c = yENV_lines (x_temp);                                                       <* 
 *>    DEBUG_DATA   yLOG_value   ("c"         , c);                                   <* 
 *>    /+---(open)---------------------------+/                                       <* 
 *>    f = fopen (x_temp, "rt");                                                      <* 
 *>    DEBUG_DATA   yLOG_point   ("f"         , f);                                   <* 
 *>    --rce; if (f == NULL) {                                                        <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(pull)---------------------------+/                                       <* 
 *>    rcp = fgets (x_recd, LEN_RECD, f);                                             <* 
 *>    DEBUG_DATA   yLOG_point   ("fgets"     , rcp);                                 <* 
 *>    while (rcp != NULL) {                                                          <* 
 *>       if (feof (f)) {                                                             <* 
 *>          DEBUG_DATA   yLOG_note    ("end-of-file");                               <* 
 *>          break;                                                                   <* 
 *>       }                                                                           <* 
 *>       /+---(handle)----------------------+/                                       <* 
 *>       rc = MAKE__check (x_recd, x_end);                                           <* 
 *>       DEBUG_DATA   yLOG_value   ("rc"        , rc);                               <* 
 *>       /+---(next)------------------------+/                                       <* 
 *>       rcp  = fgets (x_recd, LEN_RECD, f);                                         <* 
 *>       DEBUG_DATA   yLOG_point   ("fgets"     , rcp);                              <* 
 *>       /+---(done)------------------------+/                                       <* 
 *>    }                                                                              <* 
 *>    /+---(close)--------------------------+/                                       <* 
 *>    rc = fclose (f);                                                               <* 
 *>    DEBUG_DATA   yLOG_value   ("close"     , rc);                                  <* 
 *>    --rce; if (rc < 0) {                                                           <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(clean-up)-----------------------+/                                       <* 
 *>    yENV_rm (x_temp);                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_DATA  yLOG_exit    (__FUNCTION__);                                       <* 
 *>    return c;                                                                      <* 
 *> }                                                                                 <*/



