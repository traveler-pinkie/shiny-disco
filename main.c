#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>


int main(){

    int sockfd;
    unsigned char buffer[65536];
    iphder_t struct ip_header;
    iphder_t *ip_header;
    if(((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)){
        return -1;
    }

    while(1){
        if(recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL) < 0){
            return -1;
        }
        ip_header = (iphder_t *)(buffer + 14);

    }
}