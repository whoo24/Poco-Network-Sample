#include "stdafx.h"
#include <iostream>
#include "Poco/Net/DNS.h"

using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;

int main (int argc, char** argv) {
  const HostEntry& entry = DNS::hostByName("www.appinf.com");
  std::cout << "Canonical Name: " << entry.name() << std::endl;
  const HostEntry::AliasList& aliases = entry.aliases();
  HostEntry::AliasList::const_iterator it = aliases.begin();
  for (; it != aliases.end(); ++it) {
    std::cout << "Alias: " << *it << std::endl;
  }
  const HostEntry::AddressList& addrs = entry.addresses();
  HostEntry::AddressList::const_iterator addr_it = addrs.begin();
  for (; addr_it != addrs.end(); ++addr_it) {
    std::cout << "Address: " << addr_it->toString() << std::endl;
  }
  return 0;
}