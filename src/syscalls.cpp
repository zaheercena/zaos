
#include <syscalls.h>
using namespace zaos;
using namespace zaos::common;
using namespace zaos::hardwarecommunication;


SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
:   InterruptHandler(interruptManager, InterruptNumber + interruptManager->HardwareInterruptOffset())
{
}
SyscallHandler::~SyscallHandler()
{
}
        
void printf(char*);
        
uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState* cpu = (CPUState*)esp; //esp pointer still points to the start to cpu state So we cast it
    
    switch(cpu->eax)
    {
        case 4:
            printf((char*)cpu->ebx);
            break;
            
        default:
            break;
    }
    
    
    return esp;
}
        