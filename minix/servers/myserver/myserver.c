#include "inc.h"
#include "myserver.h"


/*===========================================================================*
 *			    sef_cb_init_fresh				     *
 *===========================================================================*/
int sef_cb_init_fresh(int UNUSED(type), sef_init_info_t *info)
{
  return(OK);
}


/*===========================================================================*
 *				do_*				     *
 *===========================================================================*/
int do_sys1(message *m_ptr)
{
  //OpenSSL_add_all_algorithms();
  printf("%u\n",getuid());
  printf("invoked the syscall 01\n");
  return(OK);
}

