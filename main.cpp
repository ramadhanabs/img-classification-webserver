#include "include/httplib.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ostream>

using json = nlohmann::json;
using namespace std;
namespace fs = filesystem;

string get_unix_timestamp() {
  auto now = chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();

  return to_string(millis);
}

string get_file_extension(const string &filename) {
  size_t pos = filename.rfind(".");
  if (pos != std::string::npos) {
    return filename.substr(pos); // Get the extension (e.g., ".jpg")
  }
  return ".unknown";
}

int main() {
  httplib::Server svr;

  svr.Post("/upload", [](const httplib::Request &req, httplib::Response &res) {
    if (req.has_file("image")) {
      const httplib::MultipartFormData &file = req.get_file_value("image");
      string timestamp = get_unix_timestamp();
      string extension = get_file_extension(file.filename);

      cout << "Received file: " << file.filename << endl;
      cout << "File size: " << file.content.length() << " bytes" << endl;
      cout << "Current fs: " << fs::current_path() << endl;

      string formatted_filename =
          "../uploads/" + file.filename + "_" + timestamp + extension;
      cout << "Formatted filename: " << formatted_filename << endl;

      // save file to disk
      ofstream out_file(formatted_filename, ios::binary);
      out_file.write(file.content.c_str(), file.content.size());
      if (!out_file.good()) {
        res.set_content("Upload image failed", "text/plain");
      } else {
        res.set_content("Image uploaded succesfully", "text/plain");
      }
      out_file.close();
    } else {
      res.status = 400;
      res.set_content("No Image File Provided", "text/plain");
    }
  });

  cout << "Server is running at http://localhost:8080\n";
  svr.listen("0.0.0.0", 8080);

  return 0;
}