#include "../../support/check_arguments_helper.h"
#include "../../support/error.h"
#include "../foreach/foreach.h"
#include "last.h"

void *first(enumerator_t *source) {
  if (IS_NULL(enumerator_t)) {
    NULL_ARGUMENT_ERROR("source");
    return NULL;
  }

  if (source->move_next(source)) {
    return source->current(source);
  }

  ERROR_MESSAGE("Enumerator is empty");
}

void *last_with_predicate(predicate_t predicate, enumerator_t *enumerator_t) {
  if (IS_NULL(enumerator_t)) {
    NULL_ARGUMENT_ERROR("enumerator_t");
    return NULL;
  }
  if (IS_NULL(predicate)) {
    NULL_ARGUMENT_ERROR("predicate");
    return NULL;
  }

  FOREACH(void, element, enumerator_t) {
    if (predicate(element))
      return element;
  }

  ERROR_MESSAGE("NO MATH");
}