
#ifndef __ZAOS__HARDWARECOMMUNICATION__PORT_H
#define __ZAOS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace zaos
{
    namespace hardwarecommunication
    {

        class Port
        {
            protected:
                Port(zaos::common::uint16_t portnumber);
                // FIXME: Must be virtual (currently isnt because the kernel has no memory management yet)
                ~Port();
                zaos::common::uint16_t portnumber;
        };

        
        class Port8Bit : public Port
        {
            public:
                Port8Bit(zaos::common::uint16_t portnumber);
                ~Port8Bit();

                virtual zaos::common::uint8_t Read();
                virtual void Write(zaos::common::uint8_t data);

            protected:
                static inline zaos::common::uint8_t Read8(zaos::common::uint16_t _port)
                {
                    zaos::common::uint8_t result;
                    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write8(zaos::common::uint16_t _port, zaos::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port8BitSlow : public Port8Bit
        {
            public:
                Port8BitSlow(zaos::common::uint16_t portnumber);
                ~Port8BitSlow();

                virtual void Write(zaos::common::uint8_t data);
            protected:
                static inline void Write8Slow(zaos::common::uint16_t _port, zaos::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
                }

        };



        class Port16Bit : public Port
        {
            public:
                Port16Bit(zaos::common::uint16_t portnumber);
                ~Port16Bit();

                virtual zaos::common::uint16_t Read();
                virtual void Write(zaos::common::uint16_t data);

            protected:
                static inline zaos::common::uint16_t Read16(zaos::common::uint16_t _port)
                {
                    zaos::common::uint16_t result;
                    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write16(zaos::common::uint16_t _port, zaos::common::uint16_t _data)
                {
                    __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port32Bit : public Port
        {
            public:
                Port32Bit(zaos::common::uint16_t portnumber);
                ~Port32Bit();

                virtual zaos::common::uint32_t Read();
                virtual void Write(zaos::common::uint32_t data);

            protected:
                static inline zaos::common::uint32_t Read32(zaos::common::uint16_t _port)
                {
                    zaos::common::uint32_t result;
                    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write32(zaos::common::uint16_t _port, zaos::common::uint32_t _data)
                {
                    __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
                }
        };

    }
}


#endif
