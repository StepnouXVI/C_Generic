#ifndef LAST_OR_DEFAULT_H
#define LAST_OR_DEFAULT_H
#include "../../Enumerators/IEnumerator/IEnumerator.h"

void *last_or_default(const void *default, const enumerator_t *source) ;
void *last_with_predicate_or_default(const predicate_t predicate,
                                     const void *default,
                                     const enumerator_t *source);

#endif