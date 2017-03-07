// Ch2-Read-ini.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <sstream>
#include "Poco/Util/IniFileConfiguration.h"

int main() {
  try {
    std::istringstream ini_content("[ZoneServer]\n"
                                   "CHANNEL_COUNT = 10\n"
                                   "CHANNEL_USER_COUNT = 200\n");
    Poco::AutoPtr<Poco::Util::IniFileConfiguration> pZoneServerConf(new
        Poco::Util::IniFileConfiguration(ini_content));
    int nMaxChannelCount = pZoneServerConf->getInt("ZoneServer.CHANNEL_COUNT");
    int nMaxChannelUserCount = pZoneServerConf->getInt("ZoneServer.CHANNEL_USER_COUNT");
    std::cout << "ZoneServer.CHANNEL_COUNT=" << nMaxChannelCount << std::endl;
    std::cout << "ZoneServer.CHANNEL_USER_COUNT=" << nMaxChannelUserCount << std::endl;
  } catch (Poco::FileNotFoundException e) { // 파일이 없는 경우
    std::cout << "Init LOG_LEVEL::error, " << e.displayText() << std::endl;
    return false;
  } catch (Poco::NotFoundException& e) { // 설정 키워드가 없는 경우
    std::cout << "Init LOG_LEVEL::error, " << e.displayText() << std::endl;
    return false;
  }
  return 0;
}

