//01 00 5E 00 00 09     DESTIN
//C2 01 17 23 00 00     SOURCE
//08 00                 LENGTH

//Source will always be unicast.
//Destination may be unicast, broadcast or multicast.

#include <stdio.h>

typedef struct Header
{
    unsigned long int destination : 48 ;
    unsigned long int source : 48 ;
    unsigned short int lenght : 16 ;
}Header;

void parseheader(Header obj)
{
    printf("\nDetails of Ethernet header below, all in Hex Format\n");
    printf("Destination MAC: %lx\n",obj.destination);
    printf("Source MAC: %lx\n",obj.source);
    printf("Length of Frame: %x\n",obj.lenght);
}

void parseLE(Header obj)
{
    printf("\nDetails in Little Endian HEX Format\n");
    __uint8_t Db0 = 0xFF & ((obj.destination)>>40);
    __uint8_t Db1 = 0xFF & ((obj.destination)>>32);
    __uint8_t Db2 = 0xFF & ((obj.destination)>>24);
    __uint8_t Db3 = 0xFF & ((obj.destination)>>16);
    __uint8_t Db4 = 0xFF & ((obj.destination)>>8);
    __uint8_t Db5 = 0xFF & ((__uint8_t)obj.destination);
    printf("Destination MAC: %x%x%x%x%x%x",Db5,Db4,Db3,Db2,Db1,Db0);
    printf("\n");
    __uint8_t Sb0 = 0xFF & ((obj.source)>>40);
    __uint8_t Sb1 = 0xFF & ((obj.source)>>32);
    __uint8_t Sb2 = 0xFF & ((obj.source)>>24);
    __uint8_t Sb3 = 0xFF & ((obj.source)>>16);
    __uint8_t Sb4 = 0xFF & ((obj.source)>>8);
    __uint8_t Sb5 = 0xFF & ((__uint8_t)obj.source);
    printf("Source MAC: %x%x%x%x%x%x",Sb5,Sb4,Sb3,Sb2,Sb1,Sb0);
    printf("\n");
    __uint8_t Lb0 = 0xFF & ((obj.lenght)>>8);
    __uint8_t Lb1 = 0xFF & ((__uint8_t)obj.lenght);
    printf("Length: %x%x",Lb1,Lb0);
    printf("\n");
}

void typecheck(Header obj)
{
    __uint8_t mask = 0xFF & ((obj.destination)>>40);
    if (mask == 0xFF)
    {
        printf("\nAdress is broadcast!\n");
        return;
    }
    if (mask % 2)
    {
        printf("\nAdress is multicast\n");
    }
    if ((mask % 2) == 0)
    {
        printf("\nAdress is unicast!\n");
    }
}

int main()
{
    Header H1 = {0x01005E000009,0xC20117230123,0x0800};
    Header H2 = {0xC001A3023215,0xD11725631020,0x0650};
    Header H3 = {0xFFFFFFFFFFFF,0xE52432350302,0x1100};
    parseheader(H2);
    parseLE(H2);
    typecheck(H2);
}
