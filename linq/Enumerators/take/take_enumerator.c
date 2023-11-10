#include "take_enumerator.h"

#include "stdlib.h"
#include "string.h"

#define GET_count(self) ((size_t *)(self->data + sizeof(enumerator_t)))
#define GET_SOURCE_ENUMERATOR(self) ((enumerator_t *)self->data)
#define GET_DEFAULT_count(self) \
  ((size_t *)(self->data + sizeof(enumerator_t) + sizeof(size_t)))

static void *current(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  return source->current(source);
}

static bool_t move_next(enumerator_t *self) {
  size_t *count = GET_count(self);
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);

  if (*count == 0) return false;

  *count -= 1;
  if (source->move_next(source)) {
    return true;
  }

  *count = 0;
  return false;
}

static void reset(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  source->reset(source);

  *GET_count(self) = *GET_DEFAULT_count(self);
}

static void destruct(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  source->destruct(source);
  free(self->data);
}

enumerator_t take(size_t count, enumerator_t *enumerator_t) {
  void *data = malloc(sizeof(enumerator_t) + sizeof(size_t) + sizeof(size_t));
  memcpy(data, enumerator_t, sizeof(enumerator_t));
  memcpy(data + sizeof(enumerator_t), &count, sizeof(size_t));
  memcpy(data + sizeof(enumerator_t) + sizeof(size_t), &count, sizeof(size_t));

  return {.current = current,
          .move_next = move_next,
          .reset = reset,
          .data = data,
          .destruct = destruct};
}
