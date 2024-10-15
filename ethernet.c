//01 00 5E 00 00 09     DESTIN
//C2 01 17 23 00 00     SOURCE
//08 00                 LENGTH

//Source will always be unicast.
//Destination may be unicast, broadcast or multicast.

#include <stdio.h>

typedef struct Header
{
    unsigned long int destination;
    unsigned long int source;
    unsigned short int lenght;
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
    __uint64_t Db0 = 0x00000000000000FF & (obj.destination>>40);
    __uint64_t Db1 = 0x000000000000FF00 & (obj.destination>>24);
    __uint64_t Db2 = 0x0000000000FF0000 & (obj.destination>>8);
    __uint64_t Db3 = 0x00000000FF000000 & (obj.destination<<8);
    __uint64_t Db4 = 0x000000FF00000000 & (obj.destination<<24);
    __uint64_t Db5 = 0x0000FF0000000000 & (obj.destination<<40);
    __uint64_t socket = Db0 | Db1 | Db2 | Db3 | Db4 | Db5 ;
    printf("Destination MAC: %lx",socket);
    printf("\n");
    __uint64_t Sb0 = 0x00000000000000FF & (obj.source>>40);
    __uint64_t Sb1 = 0x000000000000FF00 & (obj.source>>24);
    __uint64_t Sb2 = 0x0000000000FF0000 & (obj.source>>8);
    __uint64_t Sb3 = 0x00000000FF000000 & (obj.source<<8);
    __uint64_t Sb4 = 0x000000FF00000000 & (obj.source<<24);
    __uint64_t Sb5 = 0x0000FF0000000000 & (obj.source<<40);
    __uint64_t socket1 = Sb0 | Sb1 | Sb2 | Sb3 | Sb4 | Sb5 ;
    printf("Source MAC: %lx",socket1);
    printf("\n");
    __uint16_t Lb0 = 0x00FF & (obj.lenght>>8);
    __uint16_t Lb1 = 0xFF00 & (obj.lenght<<8);
    __uint16_t socket2 = Lb0 | Lb1;
    printf("Length: %lx",socket2);
    printf("\n");
}

void typecheck(Header obj)
{
    __uint8_t mask = 0xFF & ((obj.destination)>>40);
    if (mask == 0xFF)
    {
        printf("\nAdress is broadcast\n");
        return;
    }
    if (mask % 2)
    {
        printf("\nAdress is multicast\n");
    }
    if ((mask % 2) == 0)
    {
        printf("\nAdress is unicast\n");
    }
}

void next_proto(Header obj)
{
    if (obj.lenght == (0x0800)) 
        printf("Next protocol header is IPv4\n");
    if (obj.lenght == (0x0806)) 
        printf("Next protocol header is ARP\n");
    if (obj.lenght == (0x86DD)) 
        printf("Next protocol header is IPv6\n");
    if (obj.lenght == (0x22F0))
        printf("Next protocol header is AVTP\n");
    if (obj.lenght == (0x8100))
        printf("Next protocol header is VLAN\n");
}

int main()
{
    Header H1 = {0x01005E000009,0xC20117230123,0x0800};
    Header H2 = {0xC001A3023215,0xD11725631020,0x0650};
    Header H3 = {0xFFFFFFFFFFFF,0xE52432350302,0x1100};
    parseheader(H1);
    parseLE(H1);
    typecheck(H1);
    next_proto(H1);
}
