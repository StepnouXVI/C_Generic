#include "../../support/types.h"
#include "../IEnumerator/IEnumerator.h"
#ifndef SELECT_MANY_ENUMERABLE
#define SELECT_MANY_ENUMERABLE

enumerator_t select_many(selector_many_t selector, enumerator_t *source);

#endif