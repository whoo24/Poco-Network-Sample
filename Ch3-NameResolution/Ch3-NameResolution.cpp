// http://poco.roundsquare.net/2011/03/13/poconetdns/ // 에 있는 코드를 참고 했습니다
#include "stdafx.h"
#include <Poco/Net/DNS.h>
#include <Poco/Logger.h>
#include <string>

void ShowHostEntryItems(const Poco::Net::HostEntry& he) {
  std::cout << Poco::format("       name: %s", he.name()) << std::endl;
  for (Poco::Net::HostEntry::AddressList::const_iterator itr = he.addresses().begin();
       itr != he.addresses().end(); ++itr) {
    std::cout << Poco::format("  address#%d: %s",
                              static_cast<int>(itr - he.addresses().begin()),
                              itr->toString()) << std::endl;
  }
  for (Poco::Net::HostEntry::AliasList::const_iterator itr = he.aliases().begin();
       itr != he.aliases().end(); ++itr) {
    std::cout << Poco::format("    alias#%d: %s",
                              static_cast<int>(itr - he.aliases().begin()), *itr) << std::endl;
  }
}

int main() {
  std::cout << "test 1" << std::endl;
  std::cout << "Poco::Net::DNS::hostName()" << std::endl;
  std::cout << Poco::format("  %s", Poco::Net::DNS:: hostName()) << std::endl;
  std::cout << std::endl;
  const std::string hostname("www.google.com");
  Poco::Net::DNS::flushCache();
  std::cout << "test 2" << std::endl;
  std::cout << Poco::format("Poco::Net::DNS:: hostByName(\"%s\")", hostname) << std::endl;
  ShowHostEntryItems(Poco::Net::DNS::hostByName(hostname));
  std::cout << std::endl;
  std::cout << "test 2" << std::endl;
  const std::string hostaddress(Poco::Net::DNS::hostByName(hostname).addresses().begin()->toString());
  const Poco::Net::IPAddress ipaddress(hostaddress);
  std::cout << Poco::format("Poco::Net::DNS:: hostByAddress(Poco::Net::IPAddress(\"%s\"))",
                            ipaddress.toString()) << std::endl;
  ShowHostEntryItems(Poco::Net::DNS::hostByAddress(ipaddress));
  std::cout << std::endl;
  std::cout << "test 3" << std::endl;
  std::cout << Poco::format("Poco::Net::DNS::resolve(\"%s\")", hostname) << std::endl;
  ShowHostEntryItems(Poco::Net::DNS::resolve(hostname));
  std::cout << std::endl;
  std::cout << "test 4" << std::endl;
  std::cout << Poco::format("Poco::Net::DNS::resolve(\"%s\")", hostaddress) << std::endl;
  ShowHostEntryItems(Poco::Net::DNS::resolve(hostaddress));
  return 0;
}
