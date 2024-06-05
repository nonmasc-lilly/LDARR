
#ifndef LDARR_INCLUDE
#define LDARR_INCLUDE
#include <stdlib.h>
#include <string.h>

struct LR_darr {
    void *values;       /*          stored value array */
    unsigned int
        element_size,   /*    size of a single element */
        length,         /*          length in elements */
        block_size,     /* size of a block in elements */
        block_number;   /*  number of allocated blocks */
};

enum LR_status {
    LR_OKAY,            /*                     no error */
    LR_BOUNDS_ERROR     /* accessing dissallowed memory */
};

struct LR_darr LR_create(
    unsigned int element_size,   /*  element size in bytes */
    unsigned int block_size      /* block size in elements */
);

#define LR_GET(darr, index, type)\
    *((type*)LR_get_element((darr), (index)))
/* returns a pointer to the element */
void *LR_get_element(
    struct LR_darr darr, /*      arr to edit */
    unsigned int index   /* index of element */
);
#define LR_SET(darr, index, valuep)\
    LR_set_element(darr, index, valuep)
void LR_set_element(
    struct LR_darr darr, /*                   arr to edit */
    unsigned int index,  /*              index of element */
    void *element        /* pointer to element to copy in */
);
#define LR_PUSH(darr, valuep)\
    LR_push_element(darr, valuep)
void LR_push_element(
    struct LR_darr *darr, /*               arr to edit */
    void *element         /* pointer to element to add */
);

#define LR_POP(darrp) LR_pop_element(darrp)
enum LR_status LR_pop_element(
    struct LR_darr *darr /* arr to edit */
);

void LR_destroy(
    struct LR_darr *darr
);

#endif /* INCLUDE */

#ifdef LDARR_IMPLEMENTATION

struct LR_darr LR_create(
        unsigned int element_size,
        unsigned int block_size) {
    struct LR_darr ret = {
        malloc(block_size*element_size), element_size, 0, block_size, 1
    };
    return ret;
}

void *LR_get_element(
        struct LR_darr darr,
        unsigned int index) {
    return ((char*)darr.values)+index*darr.element_size;
}

void LR_set_element(
        struct LR_darr darr,
        unsigned int index,
        void *element) {
    memcpy((char*)(darr.values)+index*darr.element_size, (char*)element, darr.element_size);
}

void LR_push_element(
        struct LR_darr *darr,
        void *element) {
    if(++darr->length > darr->block_size*darr->block_number)
        darr->values = realloc(darr->values, (++darr->block_number)*darr->block_size*darr->element_size);
    LR_set_element(*darr, darr->length-1, element);
}

enum LR_status LR_pop_element(
        struct LR_darr *darr) {
    if(darr->length == 0)
        return LR_BOUNDS_ERROR;
    return (--darr->length, LR_OKAY);
}

void LR_destroy(
        struct LR_darr *darr) {
    free(darr->values);
}

#endif
