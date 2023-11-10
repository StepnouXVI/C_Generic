#include "skip_while_enumerator.h"

#include "stdlib.h"
#include "string.h"

// static IEnumerable<TSource> SkipWhileIterator<TSource>(IEnumerable<TSource>
// source, Func<TSource, bool_t> predicate) {
//     bool_t yielding = false;
//     foreach (TSource element in source) {
//         if (!yielding && !predicate(element)) yielding = true;
//         if (yielding) yield return element;
//     }
// }

#define GET_PREDICATE(self) *(predicate_t * (self->data + sizeof(enumerator_t)))
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

  bool_t yielding = false;
  while (!yielding && source->move_next(source)) {
    yielding = !predicate(source->current(source));
  }
}

static void destruct(enumerator_t *self) {
  enumerator_t *source = GET_SOURCE_ENUMERATOR(self);
  source->destruct(source);
  free(self->data);
}

enumerator_t skip_while(predicate_t predicate, enumerator_t *source) {
  void *data = malloc(sizeof(enumerator_t) + sizeof(predicate_t));
  memcpy(data, source, sizeof(enumerator_t));
  memcpy(data + sizeof(enumerator_t), &predicate, sizeof(predicate_t));

  bool_t yielding = false;
  source = GET_SOURCE_ENUMERATOR(data);
  while (!yielding && source->move_next(source)) {
    yielding = !predicate(source->current(source));
  }

  return {.current = current,
          .move_next = move_next,
          .reset = reset,
          .data = data,
          .destruct = destruct};
}
