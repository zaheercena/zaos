
#ifndef __ZAOS__MEMORYMANAGEMENT_H
#define __ZAOS__MEMORYMANAGEMENT_H

#include <common/types.h>

namespace zaos
{
    struct MemoryChunk{
        MemoryChunk *next;
        MemoryChunk *prev;
        bool allocated;
        common::size_t size;
    };
    
    class MemoryManager{
    protected:
        MemoryChunk* first;
    public:
        static MemoryManager *activeMemoryManager;
        MemoryManager(common::size_t first, common::size_t size);
        ~MemoryManager();
        
        void* malloc(common::size_t size);
        void free(void* ptr);
    };
}
#endif