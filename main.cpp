#include <iostream>
#include <RestServer/AppComponent.h>
#include "oatpp-swagger/Controller.hpp"
#include "src/RestServer/Controller/ImageController.h"
#include "oatpp/network/Server.hpp"


#include <iostream>
#include <Entity/Contract/DependencyInjector.h>

void init_imagerepo(){
    string fileName = "test.db";
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);

    auto db = di->get_data_base(di);
    db->init_db();

    auto multimedia_repo = di->get_multimedia_repo(di);
    Multimedia::installRepo(multimedia_repo);

    auto image_repo = di->get_image_repo(di);
    Image::installRepo(image_repo);

}

void run() {

    AppComponent components; // Create scope Environment components

    /* create ApiControllers and add endpoints to router */

    auto router = components.httpRouter.getObject();
    auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();

    auto userController = ImageController::createShared();
    userController->addEndpointsToRouter(router);

    docEndpoints->pushBackAll(userController->getEndpoints());

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

    init_imagerepo();

    oatpp::base::Environment::init();

    run();

    /* Print how much objects were created during app running, and what have left-probably leaked */
    /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

    return 0;
}
