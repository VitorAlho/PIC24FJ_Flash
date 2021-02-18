
#include "list.h"
#include <stdint.h>
#include <stdlib.h>

int8_t createNewList(uint8_t data_lenght, uint32_t num_elements, List *listObject){
                
    if( data_lenght == sizeof(uint8_t) || data_lenght == sizeof(uint16_t) || data_lenght == sizeof(uint32_t) || data_lenght == sizeof(uint64_t) ){
        listObject->dataLenght = data_lenght;
        listObject->lastRegister = 0;
        listObject->numMaxElements = num_elements;
        if(listObject->elements != 0){
            free( listObject ); 
        }
        listObject->elements = malloc( num_elements * data_lenght );   
    }
    else{
        return -1;
    }
    return 0;
}

int8_t addElementToList(List *listObject, uint64_t data){
    
    if( listObject->lastRegister < listObject->numMaxElements ){
        
        switch( listObject->dataLenght ){
            case sizeof(uint8_t):
                ((uint8_t*) listObject->elements)[listObject->lastRegister] = (uint8_t) data;
                break;
            case sizeof(uint16_t):
                ((uint16_t*) listObject->elements)[listObject->lastRegister] = (uint16_t) data;
                break;
            case sizeof(uint32_t):
                ((uint32_t*) listObject->elements)[listObject->lastRegister] = (uint32_t) data;
                break;
            case sizeof(uint64_t):
                ((uint64_t*) listObject->elements)[listObject->lastRegister] = (uint64_t) data;
                break;            
        }    
        
        listObject->lastRegister++;
    }
    else{
        return -1;
    }
    return 0;
}

int8_t getElementFromList(List *listObject, uint32_t index, void *out){
            
    if( listObject != 0 && index >= 0 && index < listObject->numMaxElements && out != 0 ){
        
        switch( listObject->dataLenght ){
            case sizeof(uint8_t):
                (*(uint8_t*)out) = ((uint8_t*) listObject->elements)[index];
                break;
            case sizeof(uint16_t):
                (*(uint16_t*)out) = ((uint16_t*) listObject->elements)[index];
                break;
            case sizeof(uint32_t):
                (*(uint32_t*)out) = ((uint32_t*) listObject->elements)[index];
                break;
            case sizeof(uint64_t):
                (*(uint64_t*)out) = ((uint64_t*) listObject->elements)[index];
                break;            
        }    
        
    }
    else{
        return -1;
    }        
    
    return 0;
    
}