#include "WhereEnumerator.h"

#include "stdlib.h"
#include "string.h"

#define PREDICATE_IN_DATA sizeof(enumerator_t)
#define GET_PREDICATE(self) *(predicate_t * (self->data + PREDICATE_IN_DATA))
#define GET_SOURCE_ENUMERATOR(self) (enumerator_t*)self->data

static void* current(enumerator_t* self) {
  enumerator_t* source = GET_SOURCE_ENUMERATOR(self);
  return source->current(source);
}

static bool_t move_next(enumerator_t* self) {
  predicate_t predicate = GET_PREDICATE(self);
  enumerator_t* source = GET_SOURCE_ENUMERATOR(self);

  bool_t status = true;
  do {
    status = source->move_next(source);
    void* current = source->current(source);
  } while (status && !predicate(current));

  return status;
}

static void reset(enumerator_t* self) {
  enumerator_t* source = GET_SOURCE_ENUMERATOR(self);
  source->reset(source);
}

static void destruct(enumerator_t* self) {
  enumerator_t* source = GET_SOURCE_ENUMERATOR(self);
  source->destruct(source);
  free(self->data);
}

enumerator_t where(enumerator_t* enumerator_t, predicate_t predicate) {
  void* data = malloc(sizeof(enumerator_t) + sizeof(predicate));
  memcpy(data, enumerator_t, sizeof(enumerator_t));
  memcpy(data + sizeof(enumerator_t), &predicate, sizeof(predicate_t));
  return {.current = current,
          .move_next = move_next,
          .reset = reset,
          .data = data,
          .destruct = destruct};
}
