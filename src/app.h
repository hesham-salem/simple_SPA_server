#include <cmath>
#include <iostream>
#include <exception>

#include "httplib.h"
#include "json.hpp"
#include <stdexcept>

using json = nlohmann::json;
namespace controllers{
void add(const httplib::Request& req, httplib::Response& res)
{
    //take get value from request body json format
    json request = json::parse(req.body);
     double operand1 = request["operand1"];
     double operand2 = request["operand2"];

     //do operation 
     double result=operand1 + operand2;

    // responece in body json format
      json response;
     response["result"] = result;
    res.set_content(response.dump(), "application/json");
}

void  subtract(const httplib::Request& req, httplib::Response& res)
{
    json request = json::parse(req.body);
     double operand1 = request["operand1"];
     double operand2 = request["operand2"];

     double result=operand1 - operand2;

      json response;
     response["result"] = result;
    res.set_content(response.dump(), "application/json");
}

void  multiply(const httplib::Request& req, httplib::Response& res)
{
    json request = json::parse(req.body);
     double operand1 = request["operand1"];
     double operand2 = request["operand2"];

     double result=operand1 * operand2;

      json response;
     response["result"] = result;
    res.set_content(response.dump(), "application/json");
}

void divide(const httplib::Request& req, httplib::Response& res)
{

        json request = json::parse(req.body);
     double operand1 = request["operand1"];
     double operand2 = request["operand2"];

       if ((int)operand2 == 0) {
            throw std::runtime_error("Division by zero!");
}
    double result= operand1/operand2;
 
      json response;
     response["result"] = result;
    res.set_content(response.dump(), "application/json");

}

}


httplib::Server::Handler serve_static_file(const std::string& file_path) {
    // Read contents of the static file
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open static file: " << file_path << std::endl;
        throw std::runtime_error("file not exit"); // Return empty response if file can't be opened
    }

    // Get length of file
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate buffer to hold file contents
    std::string file_contents;
    file_contents.resize(file_size);

    // Read file contents into buffer
    file.read(&file_contents[0], file_size);
    file.close();

    // Return lambda function to serve static file
    return [=](const httplib::Request& req, httplib::Response& res) {
        res.set_content(file_contents, "html"); // Set response content to file contents
    };
}
