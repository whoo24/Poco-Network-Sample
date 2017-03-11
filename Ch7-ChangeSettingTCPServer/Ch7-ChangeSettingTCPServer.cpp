#include "stdafx.h"
#include <iostream>

#include <Poco/Net/TCPServer.h> 
#include <Poco/Net/TCPServerConnection.h> 
#include <Poco/Net/TCPServerConnectionFactory.h> 
#include <Poco/Thread.h>

const Poco::UInt16 SERVER_PORT = 32452;
class Session : public Poco::Net::TCPServerConnection {
public:
  Session(const Poco::Net::StreamSocket &socket) : TCPServerConnection(socket) {}
  virtual ~Session() {}
  void run() override {
    try {
      int recvSize = 0;
      do {
        char buffer[256] = { 0, };
        recvSize = socket().receiveBytes(buffer, sizeof(buffer));
        std::cout << "Ŭ���̾�Ʈ���� ���� �޽���: " << buffer << std::endl;
        char szSendMessage[256] = { 0, };
        sprintf_s(szSendMessage, 128 - 1, "Re:% s", buffer);
        int nMsgLen = (int)strnlen_s (szSendMessage, 256 - 1);
        socket().sendBytes(szSendMessage, nMsgLen);
      } while (recvSize > 0);
      std::cout << "Ŭ���̾�Ʈ�� ������ ���������ϴ�" << std::endl;
    } catch (Poco::Exception& exc) { std::cerr << "Session: " << exc.displayText() << std::endl; }
  }
};

class SessionFactory : public Poco::Net::TCPServerConnectionFactory {
public:
  SessionFactory() {}
  virtual ~SessionFactory() {}
  Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket &socket) override { return new Session(socket); }
};

void PrintServerStatus(Poco::Net::TCPServer& server) {
  printf("maxThreads:%d, maxConcurrentConnections:% d\n", server.maxThreads(), server.maxConcurrentConnections());
  printf("currentThreads:%d, currentConnections:%d\n", server.currentThreads(), server.currentConnections());
  printf("queuedConnections:%d, totalConnections:% d\n\n", server.queuedConnections(), server.totalConnections());
}

int main() {
  Poco::Net::ServerSocket sock(SERVER_PORT);
  auto pParams = new Poco::Net::TCPServerParams;
  pParams->setMaxThreads(4);
  pParams->setMaxQueued(4);
  Poco::Net::TCPServer server(new SessionFactory(), sock, pParams);
  std::cout << "Simple TCP Server Application." << std::endl;
  std::cout << "maxThreads: " << server.maxThreads() << std::endl;
  std::cout << "maxConcurrentConnections: " << server.maxConcurrentConnections() << std::endl;
  server.start();
  std::cout << "start() �� ���α׷� ���ᰡ ���� �ʵ��� ��� �� ��" << std::endl;
  while (true) {
    Poco::Thread::sleep(2000);
    PrintServerStatus(server);
  }
  return 0;
}
