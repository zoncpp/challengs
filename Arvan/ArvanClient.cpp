// ArvanClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Common/INIReader.h"
#include "Common/Socket.h"
#include "Common/log.h"

#include <iostream>
#include <sstream>
#include <thread>


int         portProxy;
std::string addrProxy;
std::string proxy_protocol;

int main(int argc, char* argv[])
{
    std::string ip_port ;
    if (argc < 2)
    {
        std::cout << std::endl;
        std::cout << "enter config file's path as parameter" << std::endl;
        std::cout << std::endl;
    }
    else
    {//--- read config file
        INIReader cfg(argv[1]);
        if (cfg.ParseError() < 0)
        {
            std::cout << "Can't load 'config.ini'\n";
            return 1;
        }
        proxy_protocol = cfg.Get("server", "protocol", "UNKNOWN");
        ip_port = cfg.Get("server", "address", "UNKNOWN");
        size_t pos = ip_port.find(":");
        if (pos != std::string::npos)
        {
            std::stringstream ss;
            ss << ip_port.substr(pos + 1);
            ss >> portProxy;
            addrProxy = ip_port.substr(0, pos);
        }
    }

    try
    {
        ClientSocket s(addrProxy, portProxy, proxy_protocol[0]);

        s.send_to("hello serverrrrrrrrrrrrrrr");
        std::cerr << "sent" << std::endl;

        while (5*3==15)
        {
            std::string l = s.receive_from();

            std::cerr << "receive: " << l.c_str() << std::endl;
            if (l.empty()) break;
        }
    }
    catch (MyException sex)
    {
        std::cerr << sex.what_error() << std::endl;
    }
    catch (std::exception ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unhandled exception" << std::endl;
    }

    std::cerr << "Client exited" << std::endl;
    return 0;
}
