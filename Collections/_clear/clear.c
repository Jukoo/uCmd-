/* @file clear.c
 * @brief  clear the terminal
 * @author Umar Ba <jUmarB@protonmail.com>
 * */
#include <stdio.h> 
#include <term.h> 
#include <curses.h>
#include <sys/cdefs.h>

#if defined(NCURSES_VERSION) 
# define VERSION NCURSES_VERSION
#else 
# define VERSION "unknow" 
#endif 

#define nptr NULL 
#define SETUPTERMARG  nptr,1,&erret 

static void clsterm(void); 


static  int erret=0; 

int
main(void) 
{
  int pclear_status = 0 ; 

  int terminal_setup = setupterm(SETUPTERMARG) ; 
  if(ERR == terminal_setup && 1 != erret) 
  {
    pclear_status=ERR; 
    goto __prlg; 
  }

  clsterm(); 


   

__prlg: 
  return pclear_status ;  
}

static void clsterm(void) 
{
  (void) tputs(clear_screen , 1 , putchar) ; 
}

