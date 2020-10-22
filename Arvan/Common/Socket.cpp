#include "Socket.h"

#include <iostream>
#include <string.h>
#include <thread>

std::string get_line_number(std::string str, int line_number)
{
	std::string ret = "";
	size_t pos = str.find("\n");
        while (line_number-- > 0 && pos != std::string::npos)
	{
		ret = str.substr(0, pos);
		str = str.substr(pos + 1);

		pos = str.find("\n");
	}

	return ret;
}

Socket::Socket() : socket_(-1), ip_(""), port_(0)
{
    memset(&addr_,	0, sizeof(addr_));
}
Socket::Socket(const Socket& o)
{
    ip_ = o.ip_;
    port_ = o.port_;
    socket_ = o.socket_;
//    memcpy(&addr_, &o.addr_, sizeof(o.addr_));

    memset(&addr_,	0, sizeof(addr_));
}
Socket& Socket::operator=(const Socket& o)
{
    ip_ = o.ip_;
    port_ = o.port_;
    socket_ = o.socket_;
    memcpy(&addr_, &o.addr_, sizeof(o.addr_));

    return *this;
}
Socket::~Socket()
{
    std::cerr << "destructor socket " << socket_ << std::endl;
    if (socket_ != -1)
        close(socket_);
}

bool Socket::create(char protocol /*= 't'*/)
{
    int ret = -1;
    switch (protocol)
    {
        case 't':
        ret = socket_ = socket(AF_INET, SOCK_STREAM, 0);
        break;
        case 'u':
        ret = socket_ = socket(AF_INET, SOCK_DGRAM, 0);
        break;
    }

    if (ret == 0)
    {
        std::cerr << "socket failed";
        return false;
    }

    int opt = 1;
    if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "setsockopt error";
        return false;
    }

    return true;
}

bool Socket::Bind_Socket(const int port)
{
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = htons( port );

    if (bind(socket_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
    {
        std::cerr << "bind failed";
        return false;
    }
    return true;

}

bool Socket::Listen_Socket() const
{
    if (listen(socket_, 3) < 0)
    {
        std::cerr << "listen";
        return false;
    }
    return true;

}

std::shared_ptr<Socket> Socket::Accept_Socket()
{
    std::shared_ptr<Socket> p_new_socket = std::make_shared<Socket>();
    int len = sizeof(p_new_socket->addr_);
    p_new_socket->socket_ = accept(socket_, (sockaddr*)& p_new_socket->addr_, (socklen_t*)& len);
    if (p_new_socket->socket_ > 0)
    {
        p_new_socket->get_ip_port();

        return p_new_socket;
    }
    else
        return nullptr;
}
void Socket::get_ip_port()
{
    if(port_ == 0 || ip_ == "")
    {
        struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&addr_;
        struct in_addr ipAddr = pV4Addr->sin_addr;
        char str[INET_ADDRSTRLEN];
        inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );

        port_ = ipAddr.s_addr;
        ip_ = str;
    }
}
bool Socket::connect_Socket(const std::string host, const int port)
{
    bool ret = false;
    if (socket_ != -1)
    {
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        inet_pton(AF_INET, host.c_str(), &addr_.sin_addr);

        if (connect(socket_, (sockaddr*)& addr_, sizeof(addr_)) == 0)
            ret = true;
    }
    return ret;
}

void Socket::send_to(const std::string s) const
{
    if (send(socket_, s.c_str(), s.length()+1, 0) == -1)
    {
        throw MyException("Could not write to socket.");
    }
}


std::string Socket::receive_from() const
{
    std::string s = "";
    char buf[MAX_LEN];
    memset(buf, 0, MAX_LEN);

//    ::read(socket_, buf, MAX_LEN)
    if (recv(socket_, buf, MAX_LEN, 0) != -1)
    {
        s = buf;
    }

	return s;
}
//--------------------------------------------
ServerSocket::ServerSocket(int port, char protocol /*= 't'*/)
{
    if (!Socket::create(protocol))
    {
        throw MyException("Could not create server socket.");
    }

    if (!Socket::Bind_Socket(port))
    {
        throw MyException("Could not bind to port.");
    }

    if (!Socket::Listen_Socket())
    {
        throw MyException("Could not listen to socket.");
    }
}

ServerSocket::~ServerSocket()
{
}

//-----------------------------------------------
ClientSocket::ClientSocket(std::string host, int port, char protocol /*= 't'*/)
{
    if (!Socket::create(protocol))
	{
        throw MyException("Could not create client socket.");
	}

    if (!Socket::connect_Socket(host, port))
	{
        throw MyException("Could not connect to server.");
	}

}
