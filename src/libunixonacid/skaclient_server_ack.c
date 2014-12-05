/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/djbunix.h>
#include <skalibs/error.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>
#include <skalibs/webipc.h>

int skaclient_server_ack (unixmessage_t const *clientmsg, unixmessage_sender_t *out, unixmessage_sender_t *asyncout, char const *before, unsigned int beforelen, char const *after, unsigned int afterlen)
{
  int fd[2] ;
  unixmessage_t m = { .s = (char *)after, .len = afterlen, .fds = fd, .nfds = 1 } ;
  static unsigned char const bits = 0xff ;
  if (clientmsg->nfds
   || clientmsg->len != beforelen
   || byte_diff(clientmsg->s, beforelen, before)) return (errno = EPROTO, 0) ;
  if (ipc_pair_nbcoe(fd) < 0) return 0 ;
  unixmessage_sender_init(asyncout, fd[1]) ;
  if (!unixmessage_put_and_close(out, &m, &bits))
  {
    int e = errno ;
    fd_close(fd[1]) ;
    fd_close(fd[0]) ;
    errno = e ;
    return 0 ;
  }
  return 1 ;
}