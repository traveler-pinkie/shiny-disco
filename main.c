#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>


int main(){

    int sockfd;
    unsigned char buffer[65536];
    struct iphdr *ip_header;
    if(((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)){
        return -1;
    }

    while(1){
        if(recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL) < 0){
            return -1;
        }
        ip_header = (struct iphdr *)(buffer + 14);
        
        struct in_addr source;
        struct in_addr dest;
        
        source.s_addr = ip_header->saddr;
        dest.s_addr = ip_header->daddr;
        
        printf("Source IP: %s\n", inet_ntoa(source));
        printf("Destination IP: %s\n", inet_ntoa(dest));
    }
}