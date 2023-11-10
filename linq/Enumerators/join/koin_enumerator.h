#include "../../support/types.h"
#include "../IEnumerator/IEnumerator.h"
#ifndef JOIN_ENUMERABLE
#define JOIN_ENUMERABLE

enumerator_t join(selector_t selector, enumerator_t* enumerator_t);

#endif