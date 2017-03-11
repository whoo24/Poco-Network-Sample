#include "stdafx.h"
#include <iostream>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketAcceptor.h>

const Poco::UInt16 PORT = 32452;
class Session {
public:
  Session(Poco::Net::StreamSocket& socket, Poco::Net::SocketReactor& reactor) 
    : m_Socket(socket),
    m_Reactor(reactor) {
      m_PeerAddress = socket.peerAddress().toString();
      std::cout << "connection from " << m_PeerAddress << " ..." << std::endl;
      m_Reactor.addEventHandler(m_Socket, Poco::Observer<Session, Poco::Net::ReadableNotification>(*this, &Session::onReadable));
  }

  ~Session() {
    std::cout << m_PeerAddress << " disconnected ..." << std::endl;
    m_Reactor.removeEventHandler(m_Socket, Poco::Observer<Session, Poco::Net::ReadableNotification>(*this, &Session::onReadable));
  }

  void onReadable(Poco::Net::ReadableNotification* pNotification) {
    pNotification->release();
    try {
      char buffer[256] = { 0, };
      int n = m_Socket.receiveBytes(buffer, sizeof (buffer));
      if (n > 0) {
        char szSendMessage[256] = { 0, };
        sprintf_s(szSendMessage, 128 - 1, "Re:% s", buffer);
        int nMsgLen = (int)strnlen_s (szSendMessage, 256 - 1);
        m_Socket.sendBytes(szSendMessage, nMsgLen);
        std::cout << "Ŭ���̾�Ʈ���� ���� �޽���: " << buffer << std::endl;
      } else {
        m_Socket.shutdown();
        delete this;  // �޸� �������� ������ �Ҹ��ڰ� ȣ����� �ʴ´�.
      }
    } catch (Poco::Exception& exc) {
      std::cerr << "EchoServer: " << exc.displayText() << std::endl;
      m_Socket.shutdown();
      delete this;
    }
  }

private:
  Poco::Net::StreamSocket   m_Socket;
  std::string m_PeerAddress;
  Poco::Net::SocketReactor& m_Reactor;
};

int main() {
  Poco::Net::SocketReactor reactor;
  Poco::Net::ServerSocket serverSocket(PORT);
  Poco::Net::SocketAcceptor<Session> acceptor (serverSocket, reactor);
  std::cout << "Reactor: starting..." << std::endl;
  reactor.run();
  std::cout << "Reactor: ����..." << std::endl;
  getchar();
  return 0;
}
