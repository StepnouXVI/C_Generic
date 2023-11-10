#include "../../support/check_arguments_helper.h"
#include "../../support/error.h"
#include "../foreach/foreach.h"
#include "last.h"

void *last_or_default(const void *default, const enumerator_t *source) {
  if (IS_NULL(source)) {
    NULL_ARGUMENT_ERROR("source");
    return NULL;
  }

  if (source->move_next(source)) {
    void *current = source->current(source);
    do {
      current = source->current(source);
    } while (source->move_next(source));
    return current;
  }

  return default;
}

void *last_with_predicate_or_default(const predicate_t predicate,
                                     const void *default,
                                     const enumerator_t *source) {
  if (IS_NULL(source)) {
    NULL_ARGUMENT_ERROR("source");
    return NULL;
  }
  if (IS_NULL(predicate)) {
    NULL_ARGUMENT_ERROR("predicate");
    return NULL;
  }

  void *result = NULL;
  bool_t found = false;
  FOREACH(void, element, source) {
    if (predicate(element)) {
      found = true;
      result = element;
    }
  }
  if (found)
    return result;
  else
    return default;
}