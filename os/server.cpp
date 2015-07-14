#include <iostream>


using namespace std;

int ConnectTCPSocket(int handle, const char *addr, int port)
{
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_pton(AF_INET, addr, serv_addr.sin_addr);

	int status = -1;
	if((status = connect(handle, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) == -1)
	{
		if(errno != EINPROGRESS && errno != EALREADY && errno != EISCONN)
		{
			return 0;
		}
	}

	if(status != -1 || errno == EISCONN || errno == EASSES)
	{
		return 1;
	}

	return -1;

}

int main(int argc, char const *argv[])
{
	struct sockaddr_in serv_addr;
	serv_add.sin_family = AF_INET;
	serv_add.sin_port = htons(999);
	serv_add.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&(serv_add.sin_zero), 8);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		cout << "socket create failed." << endl; 
	}

	fcntl(sockfd, F_SETEL, fcntl(sockfd, F_GETEL) | O_NONBLOCK);

	while(ConnectTCPSocket(sockfd, "127.0.0.1", 999) == -1)
	{
		usleep(10000);
	}


	//用select阻塞读，recv小于等于0时，就关闭socket
	//用select写


	return 0;
}



