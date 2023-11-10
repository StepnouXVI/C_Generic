#include "../../support/types.h"
#include "../IEnumerator/IEnumerator.h"
#ifndef SELECT_ENUMERABLE
#define SELECT_ENUMERABLE

enumerator_t select(selector_t selector, enumerator_t* enumerator_t);

#endif