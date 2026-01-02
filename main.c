#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>

void hex_dump(unsigned char *data, int size){
    for(int i = 0; i < size; i++){
        printf("%02X ", data[i]);
        if((i + 1) % 16 == 0){
            printf("\n");
        }
    }
    if(size % 16 != 0){
        printf("\n");
    }
}


int main(){

    int sockfd;
    unsigned char buffer[65536];
    struct iphdr *ip_header;
    if(((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)){
        perror("Socket creation failed");
        return -1;
    }

    while(1){
        int data_size = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        if(data_size < 0){
            perror("Packet receive failed");
            return -1;
        }
        
        // Check if packet is large enough for Ethernet + IP headers
        if(data_size < 34){
            continue; // Skip packet
        }
        
        // Check EtherType field (bytes 12-13) to ensure it's IPv4 (0x0800)
        unsigned short eth_type = (buffer[12] << 8) | buffer[13];
        if(eth_type != 0x0800){
            continue; // Not IPv4, skip packet
        }
        
        ip_header = (struct iphdr *)(buffer + 14);
        
        struct in_addr source;
        struct in_addr dest;
        
        source.s_addr = ip_header->saddr;
        dest.s_addr = ip_header->daddr;
        
        printf("Source IP: %s\n", inet_ntoa(source));
        printf("Destination IP: %s\n", inet_ntoa(dest));

        int protocol = ip_header->protocol;
        switch(protocol){
            case 1:
                printf("Protocol: ICMP\n");
                break;
            case 6:
                printf("Protocol: TCP\n");
                break;
            case 17:
                printf("Protocol: UDP\n");
                break;
            default:
                printf("Protocol: Unknown\n");
                break;
        }

        int payload_size = ntohs(ip_header->tot_len) - ip_header->ihl * 4;
        hex_dump(buffer + 14 + ip_header->ihl * 4, payload_size);
    }
}

