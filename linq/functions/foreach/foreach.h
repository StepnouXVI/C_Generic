#ifndef FOREACH_H
#define FOREACH_H

#define FOREACH(type_of_element, element_name, enumerator_t)             \
    while(enumerator_t->move_next(enumerator_t)) {
        type_of_element* = element_name = (type_of_element*)enumerator_t->current(enumerator_t);
    

#endif