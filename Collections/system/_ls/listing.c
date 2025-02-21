/*  @file listing.c  list  directory content 
 *  @brief like ls 
 *  @authors Umar Ba <jUmarB@protonmail.com> 
 */

#define _GNU_SOURCE   
#include <stdlib.h> 
#include <stdio.h> 
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h> 
#include <error.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/stat.h> 
#include <pwd.h> 

#define  _nptr      (void*) 0
#define  _required  [static 1] //!  non nullable parameters 
#define  _nullable  


#define  hdl_error(__err , __fcall, ...)\
  do{error(__err, 0 , #__fcall #__VA_ARGS__);}while(0) 

/*
 * @fn get_ownership(dirent_item _required) 
 * @brief  get ownership of the file 
 *         the dirent_item should be a absolute path
 * @parm   char * dirent_item  [non-null] 
 * @return the owner
 */
char *get_ownership(char dirent_item  _required); 

int
main(int ac, char **av, char**env) 
{
  int progamme_status=EXIT_SUCCESS;
  char *current_work_directory=get_current_dir_name() ;  

  if(!current_work_directory) 
  {
    hdl_error(progamme_status=errno, get_current_dir_name); 
    goto __prlg ; 
  }

  printf("current work directory %s \n", current_work_directory) ; 
  DIR * dir=  opendir(current_work_directory) ;  
  if(!dir) 
  {
    hdl_error(progamme_status=errno, opendir) ; 
    free(current_work_directory) ; 
    goto __prlg; 
  }
  struct dirent *dirent = _nptr ; 

  while(_nptr != (dirent=readdir(dir)) )
  { 
    char *s = dirent->d_name ; 
    printf("%s/%s\n", current_work_directory , s ) ; 
    //get_ownership(fpath) ; 
    //bzero(fpath , 4096); 
  }
  free(current_work_directory) ; 
  current_work_directory=0 ; 

__prlg: 
  return progamme_status ; 

}

char *get_ownership(char dirent_item _required) 
{
  struct stat st_buff ; 
  if(access(dirent_item , F_OK)) 
    return _nptr ; 

  if(stat(dirent_item, &st_buff )) 
    return (char *) ~0; 
  
  //!getting uid of the owner 
  uid_t  owner_uid  =  st_buff.st_uid; 
  
  struct passwd *pwnd_owner=getpwuid(owner_uid) ; 
  if (!pwnd_owner)
    return _nptr ;
  
  return strdup(pwnd_owner->pw_name) ;   
  
}
