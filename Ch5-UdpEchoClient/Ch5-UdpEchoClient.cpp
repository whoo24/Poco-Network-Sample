// Ch5-UdpEchoClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/DatagramSocket.h>

const Poco::UInt16 MY_PORT = 32451;
const Poco::UInt16 OTHER_PORT = 32452;

int main() {
  Poco::Net::DatagramSocket sock(MY_PORT);
  try {
    for (int i = 0; i < 7; ++i) {
      char szMessage[256] = { 0, };
      sprintf_s(szMessage, 256 - 1, "%d - Send Message", i);
      int nMsgLen = (int)strnlen_s(szMessage, 256 - 1);
      sock.sendTo(szMessage, nMsgLen, Poco::Net::SocketAddress("localhost", OTHER_PORT));
      std::cout << "������ ���� �޽���: " << szMessage << std::endl;
      char buffer[256] = { 0, };
      Poco::Net::SocketAddress sender;
      auto len = sock.receiveFrom(buffer, sizeof (buffer), sender);
      if (len > 0) {
        std::cout << "�����κ��� ���� �޽���: " << buffer << std::endl;
      }
    }
  } catch (Poco::Exception& exc) {
    std::cout << "���� ���� ����: " << exc.displayText() << std::endl;
  }
  getchar();
  return 0;
}