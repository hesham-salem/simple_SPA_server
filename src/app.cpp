#include "app.h"

int main()
{
  httplib::Server server;
  
  server.Get("/",serve_static_file("./public/index.html"));

  server.Post("/add",controllers::add);
  server.Post("/subtract",controllers::subtract);
  server.Post("/multiply",controllers::multiply);
  server.Post("/divide",controllers::divide);


  server.listen("localhost", 8080);

  return 0;
}
