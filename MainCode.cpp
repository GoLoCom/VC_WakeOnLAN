#include <Windows.h>
#include <WinSock.h>
#pragma comment(lib,"Ws2_32.lib")
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	WSADATA WsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int Temp;
	BOOL BroadCast=true;
	BYTE PackData[102];
	BYTE MacAddress[6]={0x28,0xd2,0x44,0x76,0x5a,0xfe};//������װ��MAC��ַ
	WSAStartup(MAKEWORD(2,2),&WsaData);
	SockAddr.sin_addr.S_un.S_addr=inet_addr("255.255.255.255");
	SockAddr.sin_family=AF_INET;
	SockAddr.sin_port=htons(5050);//���񲻹��ĸ��˿ڶ�����
	Socket=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(Socket,SOL_SOCKET,SO_BROADCAST,(char*)&BroadCast,sizeof(BOOL));//�����׽ӿڴ����㲥��Ϣ
	for(Temp=0;Temp<6;Temp++)
		PackData[Temp]=0xff;
	for(Temp=0;Temp<16;Temp++)
		CopyMemory(&PackData[6+Temp*6],MacAddress,6);
	//for(Temp=0;Temp<6;Temp++)
	//	PackData[102+Temp]=0x00;
	//��������
	sendto(Socket,(const char*)PackData,102,0,(SOCKADDR*)&SockAddr,sizeof(SockAddr));
	//MessageBox(NULL,L"",L"",0);
	WSACleanup();
	return 0;
}