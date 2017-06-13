
#ifndef __ZAOS__SYSCALLS_H
#define __ZAOS__SYSCALLS_H
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <multitasking.h>

namespace zaos
{
    class SyscallHandler : public hardwarecommunication::InterruptHandler
    {
    public:
        SyscallHandler(hardwarecommunication::InterruptManager* interruptManager, zaos::common::uint8_t InterruptNumber);
        ~SyscallHandler();
        
        virtual zaos::common::uint32_t HandleInterrupt(zaos::common::uint32_t esp);
        
    };
    
}
#endif