#include "stdafx.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

const Poco::UInt16 PORT = 32452;

int main() {
  std::cout << "������ ���� �õ�..." << std::endl;
  Poco::Net::StreamSocket ss;
  try {
    ss.connect(Poco::Net::SocketAddress("localhost", PORT));
    for (int i = 0; i < 7; ++i) {
      char szMessage[128] = { 0, };
      sprintf_s(szMessage, 128 - 1, "%d - Send Message", i);
      int nMsgLen = static_cast<int>(strnlen_s(szMessage, 128 - 1));
      ss.sendBytes(szMessage, nMsgLen);
      std::cout << "������ ���� �޽���: " << szMessage << std::endl;
      char buffer[256] = { 0, };
      auto len = ss.receiveBytes(buffer, sizeof (buffer));
      if (len <= 0) {
        std::cout << "������ ������ ���������ϴ�" << std::endl;
        break;
      }
      std::cout << "�����κ��� ���� �޽���: " << buffer << std::endl;
    }
    ss.close();
  } catch (Poco::Exception& exc) {
    std::cout << "���� ���� ����: " << exc.displayText() << std::endl; 
  }
  getchar();
  return 0;
}
