#include <iostream>
#include <RestServer/AppComponent.h>
#include "oatpp-swagger/Controller.hpp"
#include "src/RestServer/Controller/ImageController.h"
#include <RestServer/Controller/MediaController.h>
#include "oatpp/network/Server.hpp"


#include <iostream>
#include <Shared/DependencyInjector.h>
#include <RestServer/Controller/VideoController.h>

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
    Multimedia::installRepo(multimedia_repo);

    auto image_repo = di->get_image_repo(di);
    Image::installRepo(image_repo);

    auto video_repo = di->get_video_repo(di);
    Video::installRepo(video_repo);

}

void run(shared_ptr<DependencyInjector> di) {

    AppComponent components; // Create scope Environment components

    /* create ApiControllers and add endpoints to router */

    auto router = components.httpRouter.getObject();
    auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();

    auto imageController = VideoController::createShared();
    imageController->addEndpointsToRouter(router);
    docEndpoints->pushBackAll(imageController->getEndpoints());

    auto videoController = ImageController::createShared();
    videoController->addEndpointsToRouter(router);
    docEndpoints->pushBackAll(videoController->getEndpoints());

    auto mediaController = MediaController::createShared();
    mediaController->addEndpointsToRouter(router);
    mediaController->setVlc(di->get_vlc_wrapper(di));
    mediaController->setDi(di);
    docEndpoints->pushBackAll(mediaController->getEndpoints());

    auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints);
    swaggerController->addEndpointsToRouter(router);



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
