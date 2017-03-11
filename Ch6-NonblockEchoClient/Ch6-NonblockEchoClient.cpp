#include "stdafx.h"
#include "Poco/Net/Net.h" 
#include "Poco/Net/StreamSocket.h" 
#include "Poco/Net/SocketAddress.h"
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"

const Poco::UInt16 PORT = 32452;

int main() {
  Poco::Net::StreamSocket ss;
  try {
    std::cout << "������ ���� �õ�..." << std::endl;
    ss.connectNB(Poco::Net::SocketAddress ("localhost", PORT));
    Poco::Timespan timeout(1, 0); // 1�� 
    while (ss.poll(timeout, Poco::Net::Socket::SELECT_WRITE) == false) {
      std::cout << "������ ���� ��..." << std::endl;
    }                                std::cout << "������ ���� �Ϸ�" << std::endl;
    // ������ �޽��� ������ 
    char szMessage[] = "Send Message From Client";
    auto nMsgLen = (int)strnlen_s(szMessage, 128 - 1);
    ss.sendBytes(szMessage, nMsgLen);
    std::cout << "������ ���� �޽���: " << szMessage << std::endl;
    // �������� �޽��� �ޱ�      
    Poco::DateTime now1;
    std::cout << "poll ����: " << now1.second() << std::endl;
    while (ss.poll(timeout, Poco::Net::Socket::SELECT_READ) == false) {
      std::cout << "receive ��� ��...: " << std::endl;
    }
    Poco::DateTime now2;
    std::cout << "poll �Ϸ�: " << now2.second() << std::endl;
    char buffer[256] = { 0, };
    auto len = ss.receiveBytes(buffer, sizeof(buffer));
    std::cout << "�����κ��� ���� �޽���: " << buffer << std::endl;
    // ���� ����                
    ss.close();
  } catch (Poco::Exception& exc) {
    std::cout << "���� ���� ����: " << exc.displayText() << std::endl;
  }
  getchar();
  return 0;
}