#include "select_enumerator.h"

#define SELECTOR_IN_DATA sizeof(*enumerator_t)
#define GET_SELECTOR(self) *(selector_t * (self->data + PREDICATE_IN_DATA))
#define GET_SOURCE_ENUMERATOR(self) (enumerator_t *)self->data

static void *current(enumerator_t *self) {
  selector_t selector = GET_SELECTOR(self);
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);

  return selector(source->current(source));
}

static bool_t move_next(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);

  return source->move_next(source);
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

enumerator_t select(selector_t selector, enumerator_t *enumerator_t) {
  void *data = malloc(sizeof(enumerator_t) + sizeof(selector_t));
  memcpy(data, enumerator_t, sizeof(enumerator_t));
  memcpy(data + sizeof(enumerator_t), &selector, sizeof(selector_t));
  return {.current = current,
          .move_next = move_next,
          .reset = reset,
          .data = data,
          .destruct = destruct};
}
