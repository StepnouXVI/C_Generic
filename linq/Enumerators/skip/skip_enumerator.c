#include "skip_enumerator.h"

#include "stdlib.h"
#include "string.h"

#define GET_count(self) ((size_t *)(self->data + sizeof(enumerator_t)))
#define GET_SOURCE_ENUMERATOR(self) ((enumerator_t *)self->data)

static void *current(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  return source->current(source);
}

static bool_t move_next(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  return source->move_next(source);
}

static void reset(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  source->reset(source);
  for (size_t i = 0; i < *GET_count(self); i++) {
    source->move_next(source);
  }
}

static void destruct(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  source->destruct(source);
  free(self->data);
}

enumerator_t skip(size_t count, enumerator_t *enumerator_t) {
  void *data = malloc(sizeof(enumerator_t) + sizeof(size_t));
  memcpy(data, enumerator_t, sizeof(enumerator_t));
  memcpy(data + sizeof(enumerator_t), &count, sizeof(size_t));

  for (size_t i = 0; i < count; i++) {
    source->move_next(source);
  }

  return {.current = current,
          .move_next = move_next,
          .reset = reset,
          .data = data,
          .destruct = destruct};
}
