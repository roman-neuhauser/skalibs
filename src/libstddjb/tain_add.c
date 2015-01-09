/* ISC license. */

#include <skalibs/tai.h>

int tain_add (tain_t *t, tain_t const *u, tain_t const *v)
{
  tain_t tt = *u ;
  if (!tai_add(&tt.sec, &u->sec, &v->sec)) return 0 ;
  tt.nano = u->nano + v->nano ;
  if (tt.nano > 999999999U)
  {
    if (!tai_u64(&tt.sec, tai_sec(&tt.sec) + 1)) return 0 ;
    tt.nano -= 1000000000U ;
  }
  *t = tt ;
  return 1 ;
}
