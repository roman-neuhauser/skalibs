/* ISC license. */

#include <errno.h>
#include <skalibs/uint64.h>
#include <skalibs/tai.h>

int tai_u64 (tai_t *t, uint64 u)
{
  if (u & ((uint64)1 << 63)) return (errno = EOVERFLOW, 0) ;
  t->x = u ;
  return 1 ;
}
