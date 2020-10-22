// ArvanProxy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common/Socket.h"
#include "Common/INIReader.h"
#include "Common/log.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <map>
#include <chrono>
#include <mutex> 
#include <condition_variable>
#include<atomic>

int         portUp;
std::string addrUp;
std::string proxy_protocol;
int         portProxy;
int			upstream_timeout;
std::chrono::system_clock::time_point _time;

struct time_out_stc
{
    int key_;
	std::condition_variable cv_;
    Socket* so_;
    std::atomic<bool> do_upstream;
    ~time_out_stc()
    {
        do_upstream.store(false);
        key_ = 0;
        so_ = nullptr;//--- not need to delete
    }
	time_out_stc()
    {
        do_upstream.store(false);
        key_ = 0;
        so_ = nullptr;
	}
	time_out_stc(const time_out_stc& tos)
	{
        do_upstream.store(tos.do_upstream);
        key_ = tos.key_;
        so_ = tos.so_;
	}
	time_out_stc& operator=(const time_out_stc& tos)
	{
        do_upstream.store(tos.do_upstream);
		key_ = tos.key_;
		so_ = tos.so_;

		return *this;
	}
};

void upstream_thread(std::shared_ptr<time_out_stc> stc, std::string msg)
{
    if(stc == nullptr)
        return;

    if (msg.find("zon") == std::string::npos) //--- proxy condition (for example)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(stc->do_upstream == false)
        {
            stc->do_upstream = true;
            stc->so_->send_to(msg);
            stc->cv_.notify_all();
        }
    }
    else
    {
        std::cerr << "receive an invalid message to send" << std::endl;
        //--- not response
    }
    std::cerr << "return upstream thread" << std::endl;
}

void RunProxyThread(std::shared_ptr<Socket> s_client)
{
    std::stringstream ss;
    ss << s_client->GetIp() << ":" << s_client->GetPort() << " connectd";
    log(ss.str());

    std::mutex mut_;
    try
    {
        while (true)
        {
            std::string line = s_client->receive_from();
            std::cerr << "receive line: " << line << std::endl;
            if(line == "") break;

            std::shared_ptr<time_out_stc> stc = std::shared_ptr<time_out_stc>(new time_out_stc);
            stc->key_ = s_client->GetSockFD();
            stc->so_ = s_client.get();

            std::unique_lock<std::mutex> l(mut_);
            std::thread up_t(upstream_thread, stc, line);
            up_t.detach();
            std::cerr << "waiting...." << std::endl;
            stc->cv_.wait_for(l, std::chrono::seconds(upstream_timeout));
            std::cerr << "after wait" << std::endl;

            if(stc->do_upstream == false)
            {
                stc->do_upstream = true;
                std::cerr << "to disconnectt" << std::endl;
                break; //--- to disconnect
            }
            std::cerr << "continue for this client" << std::endl;
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
        std::cerr << "Unkown exception" << std::endl;
    }

    ss.str("");
    ss << s_client->GetIp() << ":" << s_client->GetPort() << " disconnectd";
    log(ss.str());
}

int main(int argc, char* argv[]) 
{
    std::string ip_port;
    if (argc < 2)
    {
        std::cerr << std::endl;
        std::cerr << "enter config file's path as parameter" << std::endl;
        std::cerr << std::endl;
    }
    else
    {//--- read config file
        INIReader cfg(argv[1]);
        if (cfg.ParseError() < 0) {
            std::cerr << "Can't load 'config.ini'\n";
            return 1;
        }
        std::stringstream st;
        st << cfg.Get("upstream", "timeout", "UNKNOWN").c_str();
        st >> upstream_timeout;
        ip_port = cfg.Get("upstream", "address", "UNKNOWN");
        size_t pos = ip_port.find(":");
        if (pos != std::string::npos)
        {
            std::stringstream ss;
            ss << ip_port.substr(pos + 1);
            ss >> portUp;
            addrUp = ip_port.substr(0, pos);
        }
        proxy_protocol = cfg.Get("server", "protocol", "UNKNOWN");
        ip_port = cfg.Get("server", "address", "UNKNOWN");
        pos = ip_port.find(":");
        if (pos != std::string::npos)
        {
            std::stringstream ss;
            ss << ip_port.substr(pos + 1);
            ss >> portProxy;
        }
    }

    try
    {
        std::cerr << "proxy is running..." << std::endl;
        _time = std::chrono::system_clock::now();

        std::vector<std::thread> connections;
        ServerSocket in(portProxy, proxy_protocol[0]);
        while (true)
        {
            auto s = in.Accept_Socket();

            connections.push_back(std::thread(RunProxyThread, s));
        }
        for (auto& t : connections)
            t.join();
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
        std::cerr << "Unkown exception" << std::endl;
    }
    std::cerr << "Server exited" << std::endl;
    return 0;
}
