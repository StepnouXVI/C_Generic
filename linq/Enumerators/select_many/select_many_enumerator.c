#include "select_many_enumerator.h"

#include <stdio.h>

#define SELECTOR_IN_DATA sizeof(enumerator_t)
#define GET_SELECTOR(self) *((selector_many_t *)(self->data + SELECTOR_IN_DATA))
#define GET_SOURCE_ENUMERATOR(self) ((enumerator_t *)self->data)
#define GET_CURRENT_SUB_ENUMERATOR(self) \
  (enumerator_t * (self->data + SELECTOR_IN_DATA + sizeof(selector_many_t)))

static void *current(enumerator_t *self) {
  enumerator_t *current_sub_enumerator = GET_CURRENT_SUB_ENUMERATOR(self);
  if (current_sub_enumerator->current != NULL)
    return current_sub_enumerator->current(current_sub_enumerator);

  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  selector_many_t selector = GET_SELECTOR(self);

  enumerator_t new_sub_enumerator = selector(source->current(source));
  memcpy(current_sub_enumerator, &new_sub_enumerator, sizeof(enumerator_t));

  return current_sub_enumerator->current(current_sub_enumerator);
}

static bool_t move_next(enumerator_t *self) {
  enumerator_t *current_sub_enumerator = GET_CURRENT_SUB_ENUMERATOR(self);

  if (current_sub_enumerator->move_next(current_sub_enumerator)) return true;

  selector *selector = GET_SELECTOR(self);
  enumerable *source = GET_SOURCE_ENUMERATOR(self);
  current_sub_enumerator->destruct(current_sub_enumerator);

  if (!source->move_next(source)) return false;

  enumerator_t new_sub_enumerator = selector(source->current(source));
  memcpy(current_sub_enumerator, &new_sub_enumerator, sizeof(enumerator_t));
  return true;
}

static void reset(enumerator_t *self) {
  enumerator_t *current_sub_enumerator = GET_CURRENT_SUB_ENUMERATOR(self);
  current_sub_enumerator->destruct(current_sub_enumerator);

  enumerator_t source = GET_SOURCE_ENUMERATOR(self);
  selector_many_t selector = GET_SELECTOR(self);
  source->reset(source);

  enumerator_t new_sub_enumerator = selector(source->current(source));
  memcpy(current_sub_enumerator, &new_sub_enumerator, sizeof(enumerator_t));
}

static void destruct(enumerator_t *self) {
  enumerator_t *sub_enumerator = GET_CURRENT_SUB_ENUMERATOR(self);
  sub_enumerator->destruct(sub_enumerator);
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  source->destruct(source);
  free(self->data);
}

enumerator_t select_many(selector_many_t selector, enumerator_t *source) {
  void *data = malloc(sizeof(enumerator_t) * 2 + sizeof(selector_many_t));
  memcpy(data, source, sizeof(enumerator_t));
  memcpy(data + sizeof(enumerator_t), &selector, sizeof(selector_many_t));
  memset(data + sizeof(enumerator_t) + sizeof(selector_many_t), 0,
         sizeof(enumerator_t));
  enumerator_t select_many_enumerator = {.current = current,
                                       .move_next = move_next,
                                       .reset = reset,
                                       .data = data,
                                       .destruct = destruct};
  return select_many_enumerator;
}
