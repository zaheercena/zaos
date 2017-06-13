
#ifndef __ZAOS__DRIVERS__MOUSE_H
#define __ZAOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace zaos
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(zaos::common::uint8_t button);
            virtual void OnMouseUp(zaos::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public zaos::hardwarecommunication::InterruptHandler, public Driver
        {
            zaos::hardwarecommunication::Port8Bit dataport;
            zaos::hardwarecommunication::Port8Bit commandport;
            zaos::common::uint8_t buffer[3];
            zaos::common::uint8_t offset;
            zaos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(zaos::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual zaos::common::uint32_t HandleInterrupt(zaos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif
