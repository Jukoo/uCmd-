/* @file clear.c
 * @brief  clear the terminal
 * @author Umar Ba <jUmarB@protonmail.com>
 * */
#include <stdio.h> 
#include <term.h> 
#include <curses.h>
#include <sys/cdefs.h>
#include <string.h>
#include <stdlib.h> 

#if defined(NCURSES_VERSION) 
# define VERSION NCURSES_VERSION
#else 
# define VERSION "unknow" 
#endif 

#define nptr NULL 

#define CURSES_CLSCR_OP  ((TERMTYPE*)(cur_term))->Strings[5] 
#define CLEAR_EXEC tputs(CURSES_CLSCR_OP , 1 , putchar)

#define USAGE \
"Usage: ucls [options]\n"\
"Options:\n"\
"--version -v           print curses-version\n"\
"--help    -h           print this help \n"

#define ARGSHIFT(__argcount , __argvector) ((__argcount--> 0 ) ? *__argvector++ :(void *)0) 


static void clsargparse(int ac  , char **av) ; 
static void parse(const char *restrict source ) ; 
int
main(int ac , char **av , char **env) 
{
  setvbuf(stdout , nptr , _IONBF, 0) ; 
  if(ac > 1)
    clsargparse(ac , av) ; 
 
  int pclear_status = 0;  

  int terminal_setup = setupterm(nptr , 1 ,  &pclear_status) ; 
  if(ERR == terminal_setup && 1 != pclear_status) 
  {
    pclear_status=ERR; 
    goto __prlg; 
  }

  CLEAR_EXEC ;  
__prlg: 
  return pclear_status ;  
}


static void clsargparse(int ac , char **av) 
{
  char *s = (void *)0 ; 
  while (s = ARGSHIFT(ac , av))
  {
    parse(s) ; 
  }
}

static void parse(const char * restrict  source) 
{
  struct args { 
    char arguments_name_short[100] ; 
    char arguments_name_long[100] ; 
  } arguments[2] = {
    {"--version" , "-v"}, 
    {"--help", "-h"} 
  } ;  
  int i = ~0  ; 
  while (++i  < 2) 
  {
    int status = strcmp((arguments+i)->arguments_name_short , source) ; 
    status = strcmp((arguments+i)->arguments_name_long , source) ; 
 
    if(!status)
       switch(i) 
      {
        case 0 :  
          printf("Based on ncurses v%s\n",VERSION) ;
          exit(EXIT_SUCCESS) ; 
          break ; 
        case 1 : 
          printf("%s\n" , USAGE) ; 
          exit(EXIT_SUCCESS) ; 
          break;  
      }
    } 
  
}
