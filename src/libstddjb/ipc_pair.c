/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <skalibs/djbunix.h>
#include <skalibs/webipc.h>

int ipc_pair_internal (int *sv, unsigned int flags)
{
  return socketpair_internal(AF_UNIX, SOCK_STREAM, 0, flags, sv) ;
}
