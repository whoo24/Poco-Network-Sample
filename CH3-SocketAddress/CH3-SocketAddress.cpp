#include "stdafx.h"
#include <iostream>
#include "Poco/Net/DialogSocket.h"
#include "Poco/Net/DNS.h"

using Poco::Net::DialogSocket;
using Poco::Net::SocketAddress;

int main (int /*argc*/, char** /*argv*/) {
  DialogSocket ds;
  ds.connect(SocketAddress("localhost", 9911));

  return 0;
}