/**************************************************************************************
 * 文件:    demo/net.c
 *
 * 说明:    网络功能演示
 *
 * 作者:    Jun
 *
 * 时间:    2010-12-18
**************************************************************************************/
#define  DEMO_NET_C
#include <includes.h>
#include "common.h"


void fingerd_dispatcher_1000(INT08S __far * ip_pkt, INT16S len)
{
    ip_pkt[len]=0;
    printf("UDP.finger(1000) received(%d):\n", len);
    printf("%s", ip_pkt+28);
    printf("\nEnd.\n");
}

__int port_2000_rxed = 0;
INT32U target_ip;
INT16U target_port;

void dispatcher_2000(INT08S __far * ip_pkt, INT16S len) /*dispatcher() for udp port 2000*/
{
	struct iphdr __far * ip_hdr;
	struct udphdr __far * udp_hdr;

	ip_hdr = (struct iphdr __far *)ip_pkt;
	udp_hdr = (struct udphdr __far *)(ip_pkt+20);
	lock_kernel();
	printf("%08lX, to %u, from %u\n", ip_hdr->saddr, INT16XCHG(udp_hdr->dest), INT16XCHG(udp_hdr->source));
	target_ip = ip_hdr->saddr;
	target_port = INT16XCHG(udp_hdr->source);
	port_2000_rxed = 1;
	unlock_kernel();

    len = len; /* prevent warning */
}

void task_udp_port(void __far * data) /*task() for udp port 2000*/
{
		INT08S buf[]="Hello, Friends!\n";

        data = data; /* prevent warning */
        
		for(;;){
    		if(port_2000_rxed){
			port_2000_rxed = 0;
        			send_udp(target_ip, target_port, 2000, buf, sizeof(buf));
   			}
   	 		TaskSleep(10L);
		}
}

void example_init_udp_port(void) /*example*/
{
		if(!open_udp_port(2000, dispatcher_2000)){ /*open udp port*/
    		printf("open_udp_port(2000) failed\n");
    		getch();
		}
	TaskCreate(task_udp_port,NULL, "task_udp_port", 2048, 6, 0);
	/*TaskSleep(60000L); /*last 1 minute for demo*/
	/*(void)close_udp_port(2000); /*close udp port*/
}


/*=====================================================================================
 * 
 * 本文件结束: demo/net.c
 * 
**===================================================================================*/

