#include <stdlib.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <unistd.h> 
#include <string.h> 
#include <netdb.h>
#include <arpa/inet.h> 
#include <string.h> 


#include <sys/cdefs.h>  
#include <error.h> 
#include <errno.h>  


#if __STDC_VERSION__ < 201112L 
# error "C11 standard required"
#endif  


#ifdef  __ptr_t  
# define  nullptr (__ptr_t) 0 
#else 
# define  nullptr   NULL 
#endif 

#if __glibc_has_attribute(nonnull)  
#define __nnull  __attribute((nonnull)) 
#else  
#define __nnull
#endif 



#define err(__retcode , __fcall, ...)\
  do{error(__retcode, errno,#__fcall __VA_ARGS__);}while(0) 



char * poke_resolve_dns(char *__restrict__ __host_addr_service_name) __nnull;  
char * poke_reverse_dns(char *__restrict__ __host_addr_ipv4) __nnull;  

int
main(int ac , char **av, char **env) 
{
  int pokerc=EXIT_SUCCESS ;  

  int  pokesockfd= socket(PF_INET , SOCK_RAW , IPPROTO_ICMP); 
  if(~0  >= pokesockfd) 
  {
     err(pokerc=EXIT_FAILURE ,socket); 
     goto prolog ; 
  }
  
  char  *ip = poke_resolve_dns( *(av+(ac-1)) ) ; 

  char *service_name =  poke_reverse_dns(ip) ;  
  if (!service_name)  
  {
    fprintf(stdout , "Cannot resolve  dns  address\n") ; 
  }else 
  {
    fprintf(stdout , "poking on %s \n" ,service_name) ; 
  }

  

  close(pokesockfd) ; 

prolog: 
  return  pokerc; 
}


char *poke_resolve_dns(char * restrict host_addr_service_name) 
{
  struct hostent  *host_entity={nullptr} ;    
  host_entity = gethostbyname(host_addr_service_name) ; 
  if (!host_entity)  
    return nullptr ; 
   
  return inet_ntoa(*(struct in_addr *)  (host_entity->h_addr_list+0)) ;  
} 

char *poke_reverse_dns(char * restrict  host_addr_ipv4) 
{ 
  in_addr_t h_addr_ipv4lid = inet_addr(host_addr_ipv4) ; 
  if (~0  == (int) h_addr_ipv4lid)   
    return nullptr ; 

  struct  sockaddr_in service_addr_in = { 
    .sin_family=PF_INET, 
    .sin_addr.s_addr= htonl(h_addr_ipv4lid) , 
  } ; 
   
  socklen_t socksize = sizeof(service_addr_in) ; 
  char hostbuf[255]={0} ;  
  if (getnameinfo((struct sockaddr *) &service_addr_in  , socksize , hostbuf , sizeof(hostbuf),nullptr,0,NI_NAMEREQD)) 
    return nullptr ; 
 
  return strdup(hostbuf) ; 
}
