#ifndef ARVAN_SOCKET
#define ARVAN_SOCKET


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <memory>
#include <arpa/inet.h>


const int MAX_LEN = 1024;

class Socket
{
public:
    Socket();
    Socket(const Socket&);
    Socket& operator=(const Socket&);
	virtual ~Socket();

	bool create(char protocol = 't');
    bool Bind_Socket(const int port);
    bool Listen_Socket() const;
    std::shared_ptr<Socket> Accept_Socket();
    bool connect_Socket(const std::string host, const int port);

    void send_to(std::string) const;
    std::string receive_from() const;
    int GetSockFD() {return socket_;}
    sockaddr_in GetAddr() {return addr_;}
    int GetPort() {return port_;}
    std::string GetIp() {return ip_;}

protected:
    void get_ip_port();

private:
    int socket_;
    struct sockaddr_in addr_;

    std::string ip_;
    int port_;
};


class MyException
{
public:
    MyException(std::string s) : err(s) {};
    ~MyException() {};

    std::string what_error() { return err; }

private:
    std::string err;

};

class ServerSocket : public Socket
{
public:
	ServerSocket(int port, char protocol = 't');
	ServerSocket() {};
	virtual ~ServerSocket();

};

class ClientSocket : public Socket
{
public:
	ClientSocket(std::string host, int port, char protocol = 't');
	virtual ~ClientSocket() {};

};
#endif //--- ARVAN_SOCKET
