
#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>

using namespace folly;
using namespace proxygen;

class MyHandler : public RequestHandler
{
public:
    explicit MyHandler() {};

    void onRequest(std::unique_ptr<HTTPMessage>) noexcept override {};

    void onBody(std::unique_ptr<IOBuf>) noexcept override {};

    void onEOM() noexcept override {
        ResponseBuilder(downstream_)
            .status(200, "OK")
            .body("Hello world")
            .sendWithEOM();
    };

    void onUpgrade(UpgradeProtocol) noexcept override {};

    void requestComplete() noexcept override {
        delete this;
    };

    void onError(ProxygenError) noexcept override {
        delete this;
    };
};

class MyHandlerFactory : public RequestHandlerFactory
{
public:
    void onServerStart(EventBase *) noexcept override {}

    void onServerStop() noexcept override {}

    RequestHandler *onRequest(RequestHandler *, HTTPMessage *) noexcept override
    {
        return new MyHandler();
    }
};

int main(int argc, char *argv[])
{
    HTTPServerOptions options;
    options.threads = static_cast<size_t>(sysconf(_SC_NPROCESSORS_ONLN));
    options.idleTimeout = std::chrono::milliseconds(60000);
    options.shutdownOn = {SIGINT, SIGTERM};
    options.enableContentCompression = false;
    options.handlerFactories = RequestHandlerChain()
                                   .addThen<MyHandlerFactory>()
                                   .build();
    options.initialReceiveWindow = uint32_t(1 << 20);
    options.receiveStreamWindowSize = uint32_t(1 << 20);
    options.receiveSessionWindowSize = 10 * (1 << 20);
    options.h2cEnabled = true;

    HTTPServer server(std::move(options));
    server.bind({{SocketAddress("0.0.0.0", 80, true), HTTPServer::Protocol::HTTP}});

    std::thread t([&]() {
        server.start();
    });

    t.join();
    return 0;
}