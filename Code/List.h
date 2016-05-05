#ifndef _List_h_
#define _List_h_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifndef $
    #define $ ,
#endif

#define DefineList(T) \
    struct List_ ## T {\
        T*      data; \
        int     size; \
        int     storage; \
        T       __type_instance__; \
    }; \
    typedef struct List_ ## T * List_ ## T; \
    void Show_List_ ## T(List_ ## T list) { \
        fprintf(stdout, "["); \
        Each(list, element, index, { \
            Show_ ## T (element); \
            if(index < list->size - 1) { printf(", "); } \
        }); \
        fprintf(stdout, "]"); \
    }

#define List(T) List_ ## T
#define NewList(T) ({ \
    struct List_ ## T * __list_ ## T ## __; \
    __list_ ## T ## __ = (List_ ## T)malloc(sizeof(struct List_ ## T)); \
    __list_ ## T ## __->size = 0; \
    __list_ ## T ## __->storage = 0; \
    __list_ ## T ## __->data = NULL; \
    memset(&__list_ ## T ## __->__type_instance__, 0, sizeof(T)); \
    __list_ ## T ## __; \
})

#define Free(list) { free(list->data); free(list); list = NULL; }

#define Push(list, element) ({ \
    if(list->storage == 0) { \
        list->storage = 16; \
        list->data = (typeof(list->__type_instance__) *)malloc(sizeof(typeof(list->__type_instance__)) * list->storage); \
    } \
    else if(list->size >= list->storage){ \
        list->storage *= 2; \
        list->data = (typeof(list->__type_instance__) *)realloc(list->data, sizeof(typeof(list->__type_instance__)) * list->storage); \
    } \
    list->data[list->size++] = element; \
    list; })

#define Pop(list) ({ \
    assert(list->size > 0); \
    typeof(list->__type_instance__) elem = list->data[--list->size]; \
    if(list->size <= list->storage && list->storage > 16) { \
        list->storage /= 2; \
        list->data = (typeof(list->__type_instance__) *)realloc(list->data, sizeof(typeof(list->__type_instance__)) * list->storage); \
    } \
    if(list->size == 0) { \
        free(list->data); \
        list->storage = 0; \
    }; \
    elem; })

#define InsertAt(list, element, index) ({ \
    assert(index >= 0 && index < list->size); \
    assert(list->size > 0); \
    int __index_i_ ## __LINE__; \
    typeof(list->__type_instance__) insert = element; \
    typeof(list->__type_instance__) tmp; \
    for(__index_i_ ## __LINE__ = index; __index_i_ ## __LINE__ < list->size; ++__index_i_ ## __LINE__) { \
        tmp = list->data[__index_i_ ## __LINE__]; \
        list->data[__index_i_ ## __LINE__] = insert; \
        insert = tmp; \
    } \
    Append(list, insert); \
    list; })

#define RemoveAt(list, index) ({ \
    assert(index >= 0 && index < list->size); \
    assert(list->size > 0); \
    int __index_i_ ## __LINE__; \
    for(__index_i_ ## __LINE__ = index; __index_i_ ## __LINE__ < list->size - 1; ++__index_i_ ## __LINE__) { \
        list->data[__index_i_ ## __LINE__] = list->data[__index_i_ ## __LINE__+1]; \
    } \
    Pop(list); \
    list; })

#define Sort(list, first, second, comparator) ({ \
    if(list->size > 1) { \
        typeof(list->__type_instance__) tmp; \
        typeof(list->__type_instance__) first, second; \
        int __index_i_ ## __LINE__; \
        int __index_j_ ## __LINE__; \
        for(__index_i_ ## __LINE__ = 0; __index_i_ ## __LINE__ < list->size - 1; ++__index_i_ ## __LINE__) { \
            for(__index_j_ ## __LINE__ = __index_i_ ## __LINE__ + 1; __index_j_ ## __LINE__ < list->size; ++__index_j_ ## __LINE__) { \
                first = list->data[__index_i_ ## __LINE__]; \
                second = list->data[__index_j_ ## __LINE__]; \
                if( (comparator) ) { \
                    tmp = list->data[__index_i_ ## __LINE__]; \
                    list->data[__index_i_ ## __LINE__] = list->data[__index_j_ ## __LINE__]; \
                    list->data[__index_j_ ## __LINE__] = tmp; \
                } \
            } \
        } \
    } \
    list; })

#define Slice(T, list, start, end) ({ \
    assert(list->size); \
    int __start_ ## __LINE__; \
    int __end_ ## __LINE__; \
    int __step_ ## __LINE__; \
    start < 0 ? (__start_ ## __LINE__ = list->size + start) : (__start_ ## __LINE__ = start); \
    assert(__start_ ## __LINE__ < list->size && __start_ ## __LINE__ >= 0); \
    end < 0 ? __end_ ## __LINE__ = (list->size + end) : (__end_ ## __LINE__ = end); \
    assert(__end_ ## __LINE__ < list->size && __end_ ## __LINE__ >= 0); \
    __start_ ## __LINE__ <= __end_ ## __LINE__ ? (__step_ ## __LINE__ = 1) : (__step_ ## __LINE__ = -1); \
    List(T) slice = ListAlloc(T); \
    for(;;__start_ ## __LINE__ += __step_ ## __LINE__) { \
        ListPush(slice, list->data[__start_ ## __LINE__]); \
        if(__start_ ## __LINE__ == __end_ ## __LINE__) { break; } \
    } \
    slice; })

#define At(list, index) ({ \
    int __at_index__ ## __LINE__; \
    if(index >= 0) { \
        assert(index < list->size); \
        __at_index__ ## __LINE__ = index; \
    } else { \
        assert((list->size + index) >=0); \
        __at_index__ ## __LINE__ = list->size + index; \
    } \
    list->data[__at_index__ ## __LINE__]; })

#define Copy(T, list) ({ \
    assert(list != NULL); \
    List(T) copy = ListAlloc(T); \
    int __copy_index_i__ ## __LINE__; \
    for(__copy_index_i__ ## __LINE__ = 0; __copy_index_i__ ## __LINE__ < list->size; ++__copy_index_i__ ## __LINE__) { \
         Push(copy, AtList(list, __copy_index_i__ ## __LINE__)); \
    } \
    copy; })

#define Each(list, element, index, block) ({ \
    int __each_index__ ## __LINE__; \
    typeof(list->__type_instance__) element; \
    int index; \
    for(__each_index__ ## __LINE__ = 0; __each_index__ ## __LINE__ < list->size; ++__each_index__ ## __LINE__) { \
        element = At(list, __each_index__ ## __LINE__); \
        index = __each_index__ ## __LINE__; \
        (block); \
    } \
    list; })

#define Map(T, list, element, index, block) ({ \
    int __map_index__ ## __LINE__; \
    List(T) mapped ## __LINE__ = NewList(T); \
    typeof(list->__type_instance__) element; \
    int index; \
    for(__map_index__ ## __LINE__ = 0; __map_index__ ## __LINE__ < list->size; ++__map_index__ ## __LINE__) { \
        element = At(list, __map_index__ ## __LINE__); \
        index = __map_index__ ## __LINE__; \
        Push(mapped ## __LINE__, (block) ); \
    } \
    mapped ## __LINE__; })

#define Filter(T, list, element, index, block) ({ \
    int __filter_index__ ## __LINE__; \
    List(T) filtered = NewList(T); \
    typeof(list->__type_instance__) element; \
    int index; \
    for(__filter_index__ ## __LINE__ = 0; __filter_index__ ## __LINE__ < list->size; ++__filter_index__ ## __LINE__) { \
        element = At(list, __filter_index__ ## __LINE__); \
        index = __filter_index__ ## __LINE__; \
        if( (block) ) { \
            Push(filtered, element); \
        } \
    } \
    filtered; })

#define Reduce(T, list, memo, element, index, block, initial) ({ \
    int __reduce_index__ ## __LINE__; \
    T memo = initial; \
    typeof(list->__type_instance__) element; \
    int index; \
    for(__reduce_index__ ## __LINE__ = 0; __reduce_index__ ## __LINE__ < list->size; ++__reduce_index__ ## __LINE__) { \
        element = At(list, __reduce_index__ ## __LINE__); \
        index = __reduce_index__ ## __LINE__; \
        (block); \
    } \
    memo; })


#define Reverse(list) ({ \
    int __left__ ## __LINE__; \
    int __reverse ## __LINE__; \
    typeof(list->__type_instance__) tmp; \
    for( \
        __left__ ## __LINE__ = 0, __reverse ## __LINE__ = list->size - 1; \
        (__left__ ## __LINE__ != __reverse ## __LINE__) && (__left__ ## __LINE__ <= __reverse ## __LINE__); \
        ++__left__ ## __LINE__, --__reverse ## __LINE__ \
    ) { \
        tmp = list->data[__left__ ## __LINE__]; \
        list->data[__left__ ## __LINE__] = list->data[__reverse ## __LINE__]; \
        list->data[__reverse ## __LINE__] = tmp; \
    } \
    list; })

#endif
