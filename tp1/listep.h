#ifndef __LPOINT__
#define __LPOINT__


typedef struct EPOINT EPOINT; 

struct EPOINT {
  double x;
  double y;
  struct EPOINT * next;
};

typedef EPOINT * PLISTE;

#endif
