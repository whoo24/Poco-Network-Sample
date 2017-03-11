#include "stdafx.h"
#include <iostream>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h> 
#include <Poco/Net/HTTPServerRequest.h> 
#include <Poco/Net/HTTPServerResponse.h> 
#include <Poco/Net/HTMLForm.h>

class FormRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
  void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
      std::cout << "FormRequestHandler: " << request.getURI() << std::endl;
      Poco::Net::HTMLForm form(request, request.stream());
      if (!form.empty()) {
        Poco::Net::NameValueCollection::ConstIterator itr = form.begin();
        Poco::Net::NameValueCollection::ConstIterator end = form.end();
        for (; itr != end; ++itr) {
          std::cout << itr->first << ", " << itr->second << std::endl;
        }
      }
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
      const char * data = "Ok.\n";
      response.sendBuffer(data, strlen(data));
    } catch (Poco::Exception& exc) {
      std::cout << "FormRequestHandler: " << exc.displayText() << std::endl;
    }
  }
};

class SimpleRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
  Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    return new FormRequestHandler();
  }
};

int main() {        // Ŭ���̾�Ʈ�� �ִ� ���� ������ �� 
  int maxThreads = 1;
  // ���� ������ Ǯ �� ����
  Poco::ThreadPool::defaultPool().addCapacity (maxThreads);
  // ���� �� Ŭ����
  Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
  // ������ port�� 19980 
  Poco::Net::ServerSocket svs(19980);
  // HTTP ���� Ŭ���� �ν��Ͻ�
  Poco::Net::HTTPServer    srv(new SimpleRequestHandlerFactory(), svs, pParams);
  // ���� ���� 
  srv.start();
  std::cout << "Port 19980���� ���� ����" << std::endl;
  getchar();
  // ���� ���� �ߴ� 
  srv.stop();
  return 0;
}
