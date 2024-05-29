/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



char
DATA_file_type          (char a_proj [LEN_TITLE], char a_file [LEN_HUND], char *r_type)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         l           =    0;
   char        x_keep      =  'y';
   char        x_type      = TYPE_NONE;
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_type != NULL)  *r_type = TYPE_NONE;
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_proj"     , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_proj"     , a_proj);
   --rce;  if (a_proj [0] == '\0') {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_point   ("a_file"     , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_file"     , a_file);
   --rce;  if (a_file [0] == '\0') {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   l = strlen (a_file);
   DEBUG_CONF  yLOG_value   ("l"          , l);
   x_keep == 'y';
   /*---(simple)-------------------------*/
   if      (strcmp  (a_file, "."               ) == 0)   x_keep = '-';
   else if (strcmp  (a_file, ".."              ) == 0)   x_keep = '-';
   else if (strncmp (a_file, "."       , 1     ) == 0)   x_keep = '-';
   else if (strcmp  (a_file + l - 1, "~"       ) == 0)   x_keep = '-';
   DEBUG_CONF  yLOG_char    ("simple"     , x_keep);
   if (x_keep == '-') {
      DEBUG_PROG  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(global names)----------------*/
   x_type == TYPE_NONE;
   if      (strcmp  (a_file, "Makefile"       ) == 0)    x_type = TYPE_MAKE;
   else if (strcmp  (a_file, "master.h"       ) == 0)    x_type = TYPE_HEAD;
   /*---(prefixed names)--------------*/
   if (strncmp (a_file, a_proj, strlen (a_proj)) == 0) {
      if      (l >= 6 && strcmp (a_file + l - 5, ".wave"   ) == 0)  x_type = TYPE_WAVE;
      else if (l >= 6 && strcmp (a_file + l - 5, ".unit"   ) == 0)  x_type = TYPE_UNIT;
      else if (l >= 7 && strcmp (a_file + l - 6, ".munit"  ) == 0)  x_type = TYPE_MUNIT;
      else if (l >= 3 && strcmp (a_file + l - 2, ".h"      ) == 0)  x_type = TYPE_HEAD;
      else if (l >= 3 && strcmp (a_file + l - 7, "_priv.h" ) == 0)  x_type = TYPE_HEAD;
      else if (l >= 3 && strcmp (a_file + l - 7, "_solo.h" ) == 0)  x_type = TYPE_HEAD;
      else if (l >= 3 && strcmp (a_file + l - 7, "_uver.h" ) == 0)  x_type = TYPE_HEAD;
      else if (l >= 8 && strcmp (a_file + l - 7, "_unit.c" ) == 0)  ;
      else if (l >= 3 && strcmp (a_file + l - 2, ".c"      ) == 0)  x_type = TYPE_CODE;
   }
   DEBUG_CONF  yLOG_char    ("x_type"     , x_type);
   if (x_type == TYPE_NONE) {
      DEBUG_DATA   yLOG_note    ("not a selected type, skipping");
      DEBUG_PROG  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(save-back)----------------------*/
   if (r_type != NULL)  *r_type = x_type;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
DATA_gather_prep        (char a_file [LEN_PATH], char a_type, char r_file [LEN_PATH])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_temp      [LEN_LABEL] = "/tmp/ouroboros.txt";
   char        x_cmd       [LEN_RECD]  = "";
   char        x_file      [LEN_PATH]  = "";
   int         c           =    0;
   /*---(default)------------------------*/
   if (r_file != NULL)  strcpy (r_file, "");
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL || a_file [0] == '\0') {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_file"    , a_file);
   DEBUG_DATA   yLOG_char    ("a_type"    , a_type);
   if (a_type == '\0' || strchr (TYPES_VALID, a_type) == NULL) {
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check file)---------------------*/
   rc = yENV_exists (a_file);
   DEBUG_DATA   yLOG_char    ("exists"    , rc);
   --rce;  if (rc == YENV_NONE) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   switch (a_type) {
   case TYPE_MAKE :
      sprintf (x_cmd, "grep \"^include \" %s > %s 2> /dev/null", a_file, x_temp);
      break;
   case TYPE_UNIT :
      sprintf (x_cmd, "grep \"^   incl \" %s > %s 2> /dev/null", a_file, x_temp);
      break;
   case TYPE_WAVE :
      sprintf (x_cmd, "grep \"^WAVE \"    %s > %s 2> /dev/null", a_file, x_temp);
      break;
   case TYPE_HEAD :  case TYPE_MUNIT :  case TYPE_CODE : default  :
      sprintf (x_cmd, "grep \"^#include\" %s > %s 2> /dev/null", a_file, x_temp);
      break;
   }
   DEBUG_DATA   yLOG_info    ("x_cmd"     , x_cmd);
   /*---(execute)------------------------*/
   ystrlcpy (x_file, x_temp, LEN_PATH);
   rc = system (x_cmd);
   DEBUG_DATA   yLOG_value   ("grep"      , rc);
   --rce; if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check result file)--------------*/
   rc = yENV_exists (x_file);
   DEBUG_DATA   yLOG_char    ("exists"    , rc);
   --rce;  if (rc == YENV_NONE) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check lines)--------------------*/
   c = yENV_lines (x_file);
   DEBUG_DATA   yLOG_value   ("c"         , c);
   --rce; if (c < 0) {
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(default)------------------------*/
   if (c > 0 && r_file != NULL)  ystrlcpy (r_file, x_file, LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}

char
DATA_gather_file        (char a_proj [LEN_TITLE], char a_file [LEN_PATH], char a_type)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_file      [LEN_PATH]  = "";
   int         c           =    0;
   int         x_end       =    0;
   FILE       *f           =    0;
   char       *rcp         = NULL;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char        x_temp      [LEN_LABEL] = "/tmp/ouroboros.txt";
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = DATA_gather_prep (a_file, a_type, x_file);
   DEBUG_DATA   yLOG_value   ("prep"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (rc == 0) {
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(add project)--------------------*/
   x_end = GRAPH_add_node (a_proj);
   DEBUG_DATA   yLOG_value   ("x_end"     , x_end);
   --rce; if (x_end < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open file)----------------------*/
   f = fopen (x_file, "rt");
   DEBUG_DATA   yLOG_point   ("f"         , f);
   --rce; if (f == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(first)---------------------------*/
   rcp = fgets (x_recd, LEN_RECD, f);
   DEBUG_DATA   yLOG_point   ("fgets"     , rcp);
   c = 0;
   /*---(walk records)-------------------*/
   while (rcp != NULL) {
      if (feof (f)) {
         DEBUG_DATA   yLOG_note    ("end-of-file");
         break;
      }
      l = strlen (x_recd);
      /*---(trim)------------------------*/
      if (l > 0 && x_recd [l - 1] == '\n')  x_recd [--l] = '\0';
      DEBUG_DATA   yLOG_info    ("x_recd"    , x_recd);
      /*---(handle)----------------------*/
      switch (a_type) {
      case TYPE_MAKE :
         rc = MAKE_gather (x_recd, x_end);
         break;
      case TYPE_WAVE :
         break;
      default  :
         break;
      }
      DEBUG_DATA   yLOG_value   ("rc"        , rc);
      if (rc >= 0)  ++c;
      /*---(next)------------------------*/
      rcp  = fgets (x_recd, LEN_RECD, f);
      DEBUG_DATA   yLOG_point   ("fgets"     , rcp);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = fclose (f);
   DEBUG_DATA   yLOG_value   ("close"     , rc);
   --rce; if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clean-up)-----------------------*/
   yENV_rm (x_temp);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}

char
DATA_gather_project     (char a_proj [LEN_TITLE], char a_path [LEN_PATH])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_entry     = NULL;          /* directory entry                */
   char        x_type      = TYPE_NONE;
   int         l           =    0;
   char        x_name      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_path"    , a_path);
   /*---(open directory)-----------------*/
   x_dir = opendir (a_path);
   DEBUG_DATA   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk entries)-------------------*/
   --rce; while (1) {
      /*---(read)------------------------*/
      x_entry = readdir (x_dir);
      DEBUG_DATA   yLOG_point   ("x_entry"   , x_entry);
      if (x_entry == NULL) {
         DEBUG_DATA   yLOG_note    ("file entry is null, end of entiers, break");
         break;
      }
      /*---(filter)----------------------*/
      if (x_entry->d_name   == NULL) {
         DEBUG_DATA   yLOG_note    ("file name is null, continue");
         continue;
      }
      DEBUG_DATA   yLOG_info    ("d_name"    , x_entry->d_name);
      /*---(filter)----------------------*/
      rc = DATA_file_type (a_proj, x_entry->d_name, &x_type);
      DEBUG_DATA   yLOG_value   ("file_type" , rc);
      if (x_type == TYPE_NONE) {
         DEBUG_DATA   yLOG_note    ("file type is not useful, continue");
         continue;
      }
      /*---(dispatch)--------------------*/
      l = strlen (x_entry->d_name);
      DEBUG_DATA   yLOG_value   ("l"         , l);
      if (a_path [l - 1] == '/') sprintf (x_name, "%s%s" , a_path, x_entry->d_name);
      else                       sprintf (x_name, "%s/%s", a_path, x_entry->d_name);
      DEBUG_DATA   yLOG_info    ("x_name"    , x_name);
      rc = DATA_gather_file (a_proj, x_name, x_type);
      DEBUG_DATA   yLOG_value   ("dispatch"  , rc);
      if (rc < 0) {
         DEBUG_DATA   yLOG_note    ("file was not handled successfully, continue");
         continue;
      }
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_DATA   yLOG_value   ("closedir"  , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                      pulling from database                   ----===*/
/*====================------------------------------------====================*/
static void  o___PULL____________o () { return; }

char
INCL_handler            (int n, uchar a_verb [LEN_TERSE], char a_exist, void *a_handler)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_deps      [LEN_RECD]  = "";
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_verb"     , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_verb"     , a_verb);
   --rce;  if (strcmp (a_verb, "DEPEND") != 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = yPARSE_ready (&c);
   DEBUG_CONF  yLOG_value   ("rc"         , rc);
   DEBUG_CONF  yLOG_value   ("c"          , c);
   /*---(read details)-------------------*/
   rc = yPARSE_scanf (a_verb, "R"  , x_deps);
   DEBUG_CONF  yLOG_value   ("scanf"      , rc);
   if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update depends)-----------------*/
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return 0;
}


