#ifndef __LPOINT__
#define __LPOINT__


typedef struct EPOINT EPOINT; 

struct EPOINT {
  double x;
  double y;
  struct EPOINT * next;
};

typedef EPOINT * PLISTE;

//Type 'bool' où false = 0 et true = 1
typedef enum {
  false, true
} bool;

#endif
