#include "client_socket.h"
#include "server.h"

#include <signal.h>

#include <fstream>
#include <random>
#include <string>
#include <vector>

#include <iostream>

Server server;

static void handleExitSignal( int /* signal */ )
{
  server.close();
}

static const int port = 1031;

int main( int /* argc */, char** /* argv */ )
{
  signal( SIGINT, handleExitSignal );

  server.setPort( port );

  server.onRead( [&] ( std::weak_ptr<ClientSocket> socket )
  {
    if( auto s = socket.lock() )
    {
      auto data = s->read();
      s->write( data );
    }
  } );

  std::cout << "Echo server started at port " << port << std::endl;

  server.listen();

  return 0;
}
