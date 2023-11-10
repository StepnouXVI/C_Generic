#ifndef ERROR_H
#define ERROR_H


#include<stdio.h>

#define ERROR_MESSAGE(message) fprintf(stderr, "[ERROR]: %s\n", message);
#define NULL_ARGUMENT_ERROR(variable) fprintf(stderr, "[NULL ARGUMENT ERROR]:  %s is NULL\n", variable);

#endif