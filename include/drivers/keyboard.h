
#ifndef __ZAOS__DRIVERS__KEYBOARD_H
#define __ZAOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace zaos
{
    namespace drivers
    {
    
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public zaos::hardwarecommunication::InterruptHandler, public Driver
        {
            zaos::hardwarecommunication::Port8Bit dataport;
            zaos::hardwarecommunication::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(zaos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            zaos::common::uint8_t modeSwitch(zaos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            virtual zaos::common::uint32_t HandleInterrupt(zaos::common::uint32_t esp);
            virtual void Activate();
            
        };

    }
}
    
#endif
