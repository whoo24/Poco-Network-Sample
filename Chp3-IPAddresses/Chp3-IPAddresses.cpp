#include "stdafx.h"
#include <iostream>
#include "Poco/Net/DNS.h"

using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;

int main (int /*argc*/, char** /*argv*/) {
  //IPv4
  IPAddress ia2("192.168.1.120");
  if (ia2.family() == IPAddress::IPv4) { 
    std::cout << ia2.toString() << " is IPv4" << std::endl;
  }
  // IPv6 
  IPAddress ia3("1080:0:0:0:8:600:200a:425c"); 
  if (ia3.family() == IPAddress::IPv6) { // ok 
    std::cout << ia3.toString() << " is IPv6" << std::endl;
  }

  IPAddress ia1("127.0.0.1");
  if (ia1.toString() == "127.0.0.1") { // ok 
    std::cout << ia1.toString() << " is 127.0.0.1" << std::endl;
  }
  // broadcast 
  IPAddress ip2("255.255.255.255"); 
  std::cout << "Is " << ip2.toString() << " broadcast? " << ip2.isBroadcast() << std::endl; // true.
  // loopback 
  IPAddress ip3("127.0.0.1");
  std::cout << "Is " << ip3.toString() << " loopback? " << ip3.isLoopback() << std::endl; // true

  return 0;
}