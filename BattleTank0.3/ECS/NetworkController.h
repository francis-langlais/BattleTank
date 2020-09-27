//
// Created by eee466 on 11/06/19.
//

#pragma once

#include "ECS.h"
#include "../protocolbuffer/test.pb.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <zconf.h>
#include <sstream>

#define PORT        11111
#define BUFFERSIZE  2048

extern Manager manager;

class NetworkController : public Component
{
public:
    int test = 0;
    bool networkRunning = true;

    NetworkController()
    {
        if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            std::cout << "Cannot create socket" << std::endl;
        }

        memset((char *)&myaddr, 0, sizeof(myaddr));
        myaddr.sin_family = AF_INET;
        //myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        myaddr.sin_port = htons(PORT);
        if(inet_aton("127.0.0.1", &myaddr.sin_addr) == 0)
        {
            std::cout << "inet_aton failed" << std::endl;
        }

        if(bind(sock, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
        {
            std::cout << "Bind failed" << std::endl;
        }

        addrlen = sizeof(remaddr);
    }
    ~NetworkController()
    {
        close(sock);

    }

    void init() override
    {
        std::thread network(&NetworkController::ToDo, this);
        network.detach();
    }

    void ToDo()
    {
        while (networkRunning)
        {
            char* buff[BUFFERSIZE];
            int recvlen = recvfrom(sock, buff, BUFFERSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);

            buff[recvlen] = 0;

            const char* temp((const char*)buff);

            std::cout << "temp = " << temp << std::endl;

            IM.ParseFromString(temp);
            ExucutingMessage();

        }
    }

    void ExucutingMessage()
    {
        const char* toSend;
        std::string temp;
        switch (IM.code())
        {
            case test::InterfaceMessage::CREATE:

                switch(IM.type()){
                    case test::InterfaceMessage::Friendly:
                        temp = "player";
                        break;
                    case test::InterfaceMessage::Enemy:
                        temp = "enemy_shield";
                        break;
                    case test::InterfaceMessage::Rock:
                        break;
                    case test::InterfaceMessage::Marker:
                        break;
                    case test::InterfaceMessage::Explosion:
                        break;
                }

                std::cout << "Trying to create a new object" << std::endl;
                Game::CreateEntity(IM.xposition(), IM.yposition(), IM.rotation(), temp);
                toSend = intToString(Game::entityID - 1);
                sendto(sock, toSend, sizeof(toSend), 0, (struct sockaddr *)&remaddr, sizeof(remaddr));
                break;
            case test::InterfaceMessage::UPDATE:
                Game::UpdateEntity(IM.id(), IM.xposition(), IM.yposition(), IM.rotation(), IM.hp());
                break;
            case test::InterfaceMessage::DELETE:
                std::cout << "Trying to delete an Entity" << std::endl;
                Game::DestroyEntity(IM.id());
                break;
            case test::InterfaceMessage::SET_TEXT:
                Game::UpdateText(IM.newstring());
                break;
            case test::InterfaceMessage::MINIMAP:
                Game::UpdateMinimap(IM.xposition(), IM.yposition(), IM.color());
                test++;
                std::cout << test << std::endl;
                std::cout << "X = " << IM.xposition() << " Y = " << IM.yposition() << std::endl;
                break;
            default:
                break;
        }
    }

    const char* intToString(int i)
    {
        std::stringstream ss;
        ss << i;
        return ss.str().c_str();
    }
private:
    test::InterfaceMessage IM;

    int sock;

    struct sockaddr_in myaddr;
    struct sockaddr_in remaddr;

    socklen_t addrlen;

};
