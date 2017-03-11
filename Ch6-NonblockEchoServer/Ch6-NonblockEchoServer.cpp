#include "stdafx.h"
#include <algorithm>

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"
const Poco::UInt16 PORT = 32452;
int main() {
  std::cout << "���� �ʱ�ȭ ����" << std::endl;
  Poco::Net::SocketAddress server_add(PORT);
  Poco::Net::ServerSocket server_sock(server_add);
  std::cout << "���� �ʱ�ȭ �Ϸ�. Ŭ���̾�Ʈ ���� ��� ��..." << std::endl;
  Poco::Net::Socket::SocketList connectedSockList;
  connectedSockList.push_back(server_sock);
  while (true) {
    Poco::Net::Socket::SocketList readList (connectedSockList.begin(), connectedSockList.end());
    Poco::Net::Socket::SocketList writeList (connectedSockList.begin(), connectedSockList.end());
    Poco::Net::Socket::SocketList exceptList (connectedSockList.begin(), connectedSockList.end());
    Poco::Timespan timeout(1);
    auto count = Poco::Net::Socket::select(readList, writeList, exceptList, timeout);
    if (count == 0) {
      continue;
    }
    Poco::Net::Socket::SocketList delSockList;
    for (auto& readSock : readList) {
      if (server_sock == readSock) {
        auto newSock = server_sock.acceptConnection();
        connectedSockList.push_back (newSock);
        std::cout << "�� Ŭ���̾�Ʈ���� ����" << std::endl;
      } else {
        char buffer[256] = { 0, };
        auto n = ((Poco::Net::StreamSocket*) &readSock)->receiveBytes(buffer, sizeof(buffer));
        if (n > 0) {
          std::cout << "Ŭ���̾�Ʈ���� ���� �޽���: " << buffer << std::endl;
          char szSendMessage[256] = { 0, };
          sprintf_s(szSendMessage, 128 - 1, "Re:%s", buffer);
          int nMsgLen = static_cast<int>(strnlen_s (szSendMessage, 256 - 1));
          ((Poco::Net::StreamSocket*) &readSock)->sendBytes(szSendMessage, nMsgLen);
        } else {
          std::cout << "Ŭ���̾�Ʈ�� ������ ���������ϴ�" << std::endl;
          delSockList.push_back(readSock);
        }
      }
    }
    for (auto& delSock : delSockList) {
      auto delIter = std::find_if(connectedSockList.begin(), connectedSockList.end(), [&delSock](auto& sock) {
        return delSock == sock ? true : false;
      });
      if (delIter != connectedSockList.end()) {
        connectedSockList.erase(delIter);
        std::cout << "connectedSockList ���� socket ����" << std::endl;
      }
    }
  }
  getchar();
  return 0;
}