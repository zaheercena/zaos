 
#ifndef __ZAOS__HARDWARECOMMUNICATION__PCI_H
#define __ZAOS__HARDWARECOMMUNICATION__PCI_H

#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>


namespace zaos
{
    namespace hardwarecommunication
    {
        enum BaseAddressRegisterType
        {
            MemoryMapping = 0,
            InputOutput = 0
        };
        
        class BaseAddressRegister
        {
        public:
            bool prefetchable;
            zaos::common::uint8_t* address;
            zaos::common::uint32_t size;
            BaseAddressRegisterType type;
        };
        
        
        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            zaos::common::uint32_t portBase;
            zaos::common::uint32_t interrupt;
            
            zaos::common::uint16_t bus;
            zaos::common::uint16_t device;
            zaos::common::uint16_t function;

            zaos::common::uint16_t vendor_id;
            zaos::common::uint16_t device_id;
            
            zaos::common::uint8_t class_id;
            zaos::common::uint8_t subclass_id;
            zaos::common::uint8_t interface_id;

            zaos::common::uint8_t revision;
            
            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();
            
        };


        class PeripheralComponentInterconnectController
        {
            Port32Bit dataPort;
            Port32Bit commandPort;
            
        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();
            
            zaos::common::uint32_t Read(zaos::common::uint16_t bus, zaos::common::uint16_t device, zaos::common::uint16_t function, zaos::common::uint32_t registeroffset);
            
            void Write(zaos::common::uint16_t bus, zaos::common::uint16_t device, zaos::common::uint16_t function, zaos::common::uint32_t registeroffset, zaos::common::uint32_t value);
            
            bool DeviceHasFunctions(zaos::common::uint16_t bus, zaos::common::uint16_t device);
            
            void SelectDrivers(zaos::drivers::DriverManager* driverManager, zaos::hardwarecommunication::InterruptManager* interrupts);
            
            zaos::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, zaos::hardwarecommunication::InterruptManager* interrupts);
            
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(zaos::common::uint16_t bus, zaos::common::uint16_t device, zaos::common::uint16_t function);
            
            BaseAddressRegister GetBaseAddressRegister(zaos::common::uint16_t bus, zaos::common::uint16_t device, zaos::common::uint16_t function, zaos::common::uint16_t bar);
            
        };

    }
}
    
#endif
