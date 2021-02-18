
#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>

typedef struct{
    uint8_t dataLenght;
    uint32_t numMaxElements;
    uint32_t lastRegister;
    void *elements;
}List;

int8_t createNewList(uint8_t data_lenght, uint32_t num_elements, List *listObject);

int8_t addElementToList(List *listObject, uint64_t data);

int8_t getElementFromList(List *listObject, uint32_t index, void *out);

#endif // _LIST_H_