#include "WhereEnumerator.h"
#include "stdlib.h"
#include "string.h"

#define GET_PREDICATE(self) *(predicate_t * (self->data + sizeof(enumerator_t)))
#define GET_SOURCE_ENUMERATOR(self) ((enumerator_t *)self->data)

static void *current(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  return source->current(source);
}

static bool_t move_next(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  predicate_t predicate = GET_PREDICATE(self);

  if (!source->move_next(source)) {
    return false;
  }

  if (predicate(source->current(source))) {
    return true;
  } else {
    return false;
  }
}

static void reset(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  source->reset(source);
}

static void destruct(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  source->destruct(source);
  free(self->data);
}

enumerator_t take_while(predicate_t predicate, enumerator_t *enumerator_t) {
  void *data = malloc(sizeof(enumerator_t) + sizeof(predicate_t));
  memcpy(data, enumerator_t, sizeof(enumerator_t));
  memcpy(data + sizeof(enumerator_t), &predicate, sizeof(predicate_t));

  return {.current = current,
          .move_next = move_next,
          .reset = reset,
          .data = data,
          .destruct = destruct};
}
