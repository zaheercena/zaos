#ifndef __ZAOS__GDT_H
#define __ZAOS__GDT_H

#include <common/types.h>

namespace zaos
{
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    zaos::common::uint16_t limit_lo;
                    zaos::common::uint16_t base_lo;
                    zaos::common::uint8_t base_hi;
                    zaos::common::uint8_t type;
                    zaos::common::uint8_t limit_hi;
                    zaos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(zaos::common::uint32_t base, zaos::common::uint32_t limit, zaos::common::uint8_t type);
                    zaos::common::uint32_t Base();
                    zaos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            zaos::common::uint16_t CodeSegmentSelector();
            zaos::common::uint16_t DataSegmentSelector();
    };

}
    
#endif
