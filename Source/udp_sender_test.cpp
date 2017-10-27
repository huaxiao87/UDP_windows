/*Written by Hua Xiao on Oct 26, 2017
See: http://www.cnblogs.com/churi/archive/2013/02/27/2935427.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>       /* use time to be the seed for the function rand*/

#include "..\Headers\udp_sender.h"

int main(int argc, char argv[]) {
	char data1[512] = "Hi port 8889! ";
	char data2[512] = "Hi port 8890! ";

	//generate a random number to differentiate the data you send during every run;
	srand(time(0));
	int randomNumber = rand() % 10;
	data1[14] = '0' + randomNumber;
	data2[14] = '0' + randomNumber;

	//create the UDPSender and connect it to port 8889 at local host, i.e., 127.0.0.1
	UDPSender udpSender("127.0.0.1", 8889);
	udpSender.sendData(data1);
	
	//change port number to 8890 and send the content in data2 to it
	udpSender.bindTo("127.0.0.1", 8890);
	udpSender.sendData(data2);

	return 0;
}