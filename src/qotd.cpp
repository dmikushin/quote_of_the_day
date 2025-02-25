#include "client_socket.h"
#include "server.h"

#include <signal.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

Server server;

static void handleExitSignal( int /* signal */ )
{
  server.close();
}

static void unescapeQuote( std::string& quote )
{
  std::size_t position    = 0;
  std::string target      = "\\n";
  std::string replacement = "\n";
  while( ( position = quote.find( target, position ) ) != std::string::npos )
  {
    quote.replace( position, target.length(), replacement );
    position += replacement.length();
  }
}

std::vector<std::string> readQuotes( const std::string& filename )
{
  std::ifstream in( filename );
  if( !in )
    return {};

  std::vector<std::string> quotes;
  std::string line;

  while( std::getline( in, line ) )
  {
    unescapeQuote( line );
    quotes.push_back( line );
  }

  return quotes;
}

static const int port = 1041;

int main( int argc, char** argv )
{
  std::vector<std::string> quotes;

  if( argc > 1 )
    quotes = readQuotes( argv[1] );
  else
    quotes = { "Sorry, no quote today, mate.\n" };

  std::random_device rd;
  std::mt19937 rng( rd() );
  std::uniform_int_distribution<std::size_t> distribution( 0, quotes.size() - 1 );

  signal( SIGINT, handleExitSignal );

  server.setPort( port );

  server.onAccept( [&] ( std::weak_ptr<ClientSocket> socket )
  {
    if( auto s = socket.lock() )
    {
      s->write( quotes.at( distribution( rng ) ) );
      s->close();
    }
  } );

  std::cout << "QOTD server started at port " << port << std::endl;  

  server.listen();

  return 0;
}
