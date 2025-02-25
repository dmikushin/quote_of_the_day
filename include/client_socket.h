#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>

class Server;

class ClientSocket
{
public:
  ClientSocket( int fileDescriptor, Server& server );
  ~ClientSocket();

  int fileDescriptor() const;

  void close();
  void write( const std::string& data );

  std::string read();

  ClientSocket( const ClientSocket& )            = delete;
  ClientSocket& operator=( const ClientSocket& ) = delete;

private:
  int _fileDescriptor = -1;
  Server& _server;
};

#endif // CLIENT_SOCKET_H

