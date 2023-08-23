#include <iostream>

#include "oatpp-swagger/Controller.hpp"
#include "rest_api/AppComponent.h"
#include <rest_api/ImageController.h>
#include <rest_api/MediaController.h>
#include "oatpp/network/Server.hpp"


#include <iostream>
#include <core/DependencyInjector.h>
#include <rest_api/VideoController.h>

void init_imagerepo(shared_ptr<DependencyInjector> di){
    string fileName = "test.db";

    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);
    di->install_video_repo(di);
    di->install_vlc_wrapper();
    auto db = di->get_data_base(di);
    db->init_db();

    auto multimedia_repo = di->get_multimedia_repo(di);
    Multimedia::install_repo(multimedia_repo);

    auto image_repo = di->get_image_repo(di);
    Image::install_repo(image_repo);

    auto video_repo = di->get_video_repo(di);
    Video::install_repo(video_repo);

}

void run(shared_ptr<DependencyInjector> di) {

    AppComponent components; // Create scope Environment components

    /* create ApiControllers and add endpoints to router */

    shared_ptr<oatpp::web::server::HttpRouter> router = components.httpRouter.getObject();

    oatpp::web::server::api::Endpoints endpoints;

    auto imageController = VideoController::createShared();
    router->addController(imageController);
    endpoints.append(imageController->getEndpoints());

    auto videoController = ImageController::createShared();
    router->addController(videoController);
    endpoints.append(videoController->getEndpoints());

    auto mediaController = MediaController::createShared();
    router->addController(mediaController);
    mediaController->setVlc(di->get_vlc_wrapper(di));
    mediaController->setDi(di);
    endpoints.append(mediaController->getEndpoints());

    auto swaggerController = oatpp::swagger::Controller::createShared(endpoints);
    router->addController(swaggerController);

    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    /* create server */
    oatpp::network::Server server(connectionProvider,
                                  connectionHandler);

    OATPP_LOGD("Server", "Running on port %s...", connectionProvider->getProperty("port").toString()->c_str());

    server.run();



}

/**
 *  main
 */
int main(int argc, const char * argv[]) {
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    init_imagerepo(di);

    oatpp::base::Environment::init();

    run(di);

    /* Print how much objects were created during app running, and what have left-probably leaked */
    /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

    return 0;
}
