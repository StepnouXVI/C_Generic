#include "last.h"
#include "../../support/check_arguments_helper.h"
#include "../../support/error.h"
#include "../foreach/foreach.h"

void *last(enumerator_t *source) {
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

  ERROR_MESSAGE("Enumerator is empty");
}

void *last_with_predicate(predicate_t predicate, enumerator_t *source) {
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
  if(found) return result;
  ERROR_MESSAGE("NO MATH");
}