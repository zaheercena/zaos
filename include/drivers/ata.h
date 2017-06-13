#ifndef __ZAOS__DRIVERS__ATA_H
#define __ZAOS__DRIVERS__ATA_H

#include <hardwarecommunication/port.h>
#include <common/types.h>

namespace zaos
{
    namespace drivers 
    {
        class AdvancedTechnologyAttachment
        {
        protected:
            hardwarecommunication::Port16Bit dataPort;
            hardwarecommunication::Port8Bit errorPort;
            hardwarecommunication::Port8Bit sectorCountPort;
            hardwarecommunication::Port8Bit lbaLowPort;
            hardwarecommunication::Port8Bit lbaMidPort;
            hardwarecommunication::Port8Bit lbaHiPort;
            hardwarecommunication::Port8Bit devicePort;
            hardwarecommunication::Port8Bit commandPort;
            hardwarecommunication::Port8Bit controlPort;
            
            bool master;
            common::uint16_t bytesPerSector;
        public:
            AdvancedTechnologyAttachment(common::uint16_t portBase, bool master);
            ~AdvancedTechnologyAttachment();
            
            void Identify();
            void Read28(common::uint32_t sector, common::uint8_t* data, int count);
            void Write28(common::uint32_t sector, common::uint8_t* data, int count);
            void Flush();
        };
    }
}

#endif