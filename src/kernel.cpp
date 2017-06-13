
#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <syscalls.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/ata.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <multitasking.h>

using namespace zaos;
using namespace zaos::common;
using namespace zaos::drivers;
using namespace zaos::hardwarecommunication;



void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void printfHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    printf(foo);
}




class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
    void OnKeyDown(char c)
    {
        char* foo = " ";
        foo[0] = c;
        printf(foo);
    }
};

class MouseToConsole : public MouseEventHandler
{
    int8_t x, y;
public:
    
    MouseToConsole()
    {
        uint16_t* VideoMemory = (uint16_t*)0xb8000;
        x = 40;
        y = 12;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);        
    }
    
    virtual void OnMouseMove(int xoffset, int yoffset)
    {
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);

        x += xoffset;
        if(x >= 80) x = 79;
        if(x < 0) x = 0;
        y += yoffset;
        if(y >= 25) y = 24;
        if(y < 0) y = 0;

        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);
    }
    
};

void sysprintf(char* str)
{
    asm("int $0x80" : : "a" (4), "b" (str));
}

void taskA()
{
    while(true)
        sysprintf("A");
}
void taskB()
{
    while(true)
        sysprintf("B");
}






typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    printf("[[[-------------------------Welcome To ThunderLand---------------------------]]]");
    printf("               This is BinfeOS and Creater is Zaheer Ahmed Gujjar               ");
    printf("               Zaheer's Encryption is Abiffs and Ahmed's is Binfe               ");
    printf("__________________________http://zaheercena.online/_____________________________\n");

    GlobalDescriptorTable gdt;
    
    TaskManager taskManager; //scheduling Multitasking Section
    Task task1(&gdt, taskA);
    Task task2(&gdt, taskB);
    taskManager.AddTask(&task1);
    taskManager.AddTask(&task2);
    
    InterruptManager interrupts(0x20, &gdt, &taskManager);
    SyscallHandler syscalls(&interrupts, 0x80);
    
    
    printf("Initializing Hardware, Stage 1\n");
    
    DriverManager drvManager;
    
        PrintfKeyboardEventHandler kbhandler;
        KeyboardDriver keyboard(&interrupts, &kbhandler);
        drvManager.AddDriver(&keyboard);
    
        MouseToConsole mousehandler;
        MouseDriver mouse(&interrupts, &mousehandler);
        drvManager.AddDriver(&mouse);
        
        PeripheralComponentInterconnectController PCIController;
        PCIController.SelectDrivers(&drvManager, &interrupts);
        
        printf("Initializing Hardware, Stage 2\n");
        drvManager.ActivateAll();
            
        printf("Initializing Hardware, Stage 3\n");
        //Hard drive Section
  /*      AdvancedTechnologyAttachment ata0m(0x1F0, true); ///Primary master
        printf("ATA Primary Master: ");
        ata0m.Identify();
        char* atabuffer = "Zaheer isn't Blackhat: ";     ///write something to disk(hard disk)
        ata0m.Write28(0, (uint8_t*)atabuffer, 21);
        ata0m.Flush();
        ata0m.Read28(0, (uint8_t*)atabuffer, 21);
        
        AdvancedTechnologyAttachment ata0s(0x1F0, false); ///Primary slave
        printf("ATA Primary Slave: ");
        ata0s.Identify();
        
        AdvancedTechnologyAttachment ata1m(0x170, true); ///Secondry Master
        printf("ATA Secondry Master: ");
        ata1m.Identify();
        AdvancedTechnologyAttachment ata1s(0x170, false); ///Secondry Slave
        printf("ATA Secondry Slave: ");
        ata1s.Identify();
        
    */    
  
        
        interrupts.Activate();
//     printf("  VGA Mode:       press 'V'\n");
//     printf("  CLI Mode:       press any other key\n");
//     if(keyboard.modeSwitch(&interrupts, &kbhandler) == true)
//     {
//         printf("Zaheer Pressed V\n");
//     }
//     printf("Zaheer Welcome to Shell:$\n");
    
    while(1);
}
