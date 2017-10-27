/*Written by Hua Xiao on Oct 26, 2017
See: http://www.cnblogs.com/churi/archive/2013/02/27/2935427.html
*/

#include <stdio.h>
#include "..\Headers\udp_receiver.h"

int main(int argc, char* argv[])
{
	UDPReceiver udpReceiver(8887, 512);
	int count = 0;

	// wait for the messages sent to port 8887, after received 5 pieces of messages change port
	while (count != 5) {
		if(udpReceiver.receiveData()) count++;
	}
	
	//change port to 8888 and keep on receiving messages from that port
	udpReceiver.bindTo(8888);
	while (true) {
		if (udpReceiver.receiveData()) count++;
	}
	return 0;
}