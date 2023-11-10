

#ifndef I_ENUMERATOR_H
#define I_ENUMERATOR_H
#include "../../../support/bool_t.h"

typedef struct i_enumerator {
  void* (*current)(struct i_enumerator* self);
  bool_t (*move_next)(struct i_enumerator* self);
  void (*reset)(struct i_enumerator* self);
  void (*destruct)(struct i_enumerator* self);
  void* data;
} enumerator_t;

#endif