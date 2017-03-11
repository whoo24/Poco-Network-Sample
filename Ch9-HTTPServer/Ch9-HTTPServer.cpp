// Ch9-HTTPServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <Poco/Net/HTTPServer.h> 
#include <Poco/Net/HTTPRequestHandler.h> 
#include <Poco/Net/HTTPRequestHandlerFactory.h> 
#include <Poco/Net/HTTPServerRequest.h> 
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/File.h>

class NotFileHandler : public Poco::Net::HTTPRequestHandler {
public:
  void handleRequest(Poco::Net::HTTPServerRequest&
                     request, Poco::Net::HTTPServerResponse& response) {
    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    response.setContentType("text/html");
    std::ostream& ostr = response.send();
    ostr << "<html><head>";
    ostr << "<title>Simple WebServer powered by POCO</title>";
    ostr << "</head><body>Error. No Fill<br />";
    ostr << "</body></html>";
  }
};

class FileRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
  void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
      std::cout << "FileRequestHandler: " << request.getURI() << std::endl;
      std::string fpass = "." + request.getURI();
      response.sendFile(fpass, "text/html");
    } catch (Poco::Exception& exc) { 
      std::cout << "FileRequestHandler: " << exc.displayText() << std::endl; 
    }
  }
};
class SimpleRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
  Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    std::cout << "SimpleRequestHandlerFactory: " << request.getURI() << std::endl;
    std::string fpass = "." + request.getURI();
    Poco::File f(fpass);
    if (!f.exists() || !f.isFile()) { 
      return new NotFileHandler();
    }
    return new FileRequestHandler();
  }
};
int main() {
  // Ŭ���̾�Ʈ�� �ִ� ���� ������ �� 
  int maxThreads = 1;
  // ���� ������ Ǯ �� ���� 
  Poco::ThreadPool::defaultPool().addCapacity (maxThreads);
  // ���� �� Ŭ����
  Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
  // �䱸 ��� �ִ� ��
  pParams->setMaxQueued(100);
  // �ִ� ���� ó�� �� 
  pParams->setMaxThreads(maxThreads);     
  // ������ port�� 19980   
  Poco::Net::ServerSocket svs(19980);
  // HTTP ���� Ŭ���� �ν��Ͻ�
  Poco::Net::HTTPServer srv(new SimpleRequestHandlerFactory(), svs, pParams);
  // ���� ����
  srv.start();
  std::cout << "Port 19980���� ���� ����" << std::endl;
  getchar();
  // ���� ���� �ߴ� 
  srv.stop();
  return 0;
}