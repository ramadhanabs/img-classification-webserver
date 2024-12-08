#include "include/httplib.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

int main(){
    httplib::Server svr;

    svr.Get("/hello", [](const httplib::Request& req, httplib::Response& res) {
        json response_json = {{"message", "Hello World"}};
        res.set_content(response_json.dump(), "application/json");
    });

    svr.Post("/upload-image", [](const httplib::Request& req, httplib::Response& res) {
        
    });

    std::cout << "Server is running at http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);

    return 0;
}