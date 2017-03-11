#include "stdafx.h"
#include <iostream>
#include <Poco/Net/TCPServer.h> 
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/TCPServerConnectionFactory.h> 
#include <Poco/Thread.h>

const Poco::UInt16 SERVER_PORT = 32452;

class Session : public Poco::Net::TCPServerConnection {
public:
  Session(const Poco::Net::StreamSocket &socket) : TCPServerConnection(socket) {
    std::cout << "Session ��ü ����" << std::endl;
  }
  virtual ~Session() {
    std::cout << "Session ��ü �Ҹ�" << std::endl;
  }
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
    } catch (Poco::Exception& exc) {
      std::cerr << "Session: " << exc.displayText() << std::endl;
    }
  }
};

class SessionFactory : public Poco::Net::TCPServerConnectionFactory {
public:
  SessionFactory() {}
  virtual ~SessionFactory() {}
  Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket &socket) override {
    return new Session(socket);
  }
};

int main() {
  Poco::Net::ServerSocket sock(SERVER_PORT);
  Poco::Net::TCPServer server(new SessionFactory(), sock);
  std::cout << "Simple TCP Server Application." << std::endl;
  std::cout << "maxThreads: " << server.maxThreads() << std::endl;
  std::cout << "maxConcurrentConnections: " << server.maxConcurrentConnections() << std::endl;
  server.start();
  std::cout << "start() �� ���α׷� ���ᰡ ���� �ʵ��� ��� �ϱ�" << std::endl;
  while (true) {
    Poco::Thread::sleep(1);
  }
  return 0;
}
