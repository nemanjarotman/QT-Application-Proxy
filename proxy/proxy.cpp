#include "proxy.h"
#include <iostream>



AppProxy::AppProxy(QObject * parent):QObject(parent)
{
    buffer = (char* ) malloc(sizeof(char*) * 2048);
    response = (char* ) malloc(sizeof(char*) * 2048);
    clients["uros"] = "xddd";
    clients["deki"] = "lolz";
    clients["roki"] = "roki94";

    connect(this, SIGNAL(startSignalArrived()), this, SLOT(startProxy()));
    connect(&socket, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    connect(this, SIGNAL(firstMessageArived()), this, SLOT(readFirstMessage()));
    connect(this, SIGNAL(autheticationArived()), this, SLOT(autheticationConfirmed()));
    connect(this, SIGNAL(serverInfoRecieved()), this, SLOT(connectToServer()));
    connect(this, SIGNAL(filePartArrived()), this, SLOT(sendToServer()));
}

AppProxy::~AppProxy()
{
    socket.close();
}

void AppProxy::start()
{

    emit startSignalArrived();

}
void AppProxy::startProxy()
{
    socket.listen(QHostAddress::Any, 1080);
    cout << "listen" << endl;

}

void AppProxy::acceptConnection()
{
    clientSocket = socket.nextPendingConnection();
    cout << "accept" << endl;


    if(clientSocket->waitForReadyRead() == true)
    {
        emit firstMessageArived();
        clientSocket->waitForBytesWritten();
    }
}

void AppProxy::readFirstMessage()
{
    int ret = 0;
    ret = clientSocket->read(buffer, clientSocket->bytesAvailable());
    cout << "read first "<< endl;
    if(ret != 0)
    {
        buffer[ret] = '\0';
        cout << ret << " First client message: "<<endl;;
        cout << hex <<(int)buffer[0] << endl;
        cout << hex <<(int)buffer[1] << endl;
        cout << hex <<(int)buffer[2] << endl;
        cout << hex <<(int)buffer[3] << endl;
    }

    if(buffer[0] != 5)
    {
        response[0] = 5;
        response[1] = 0xff;
        clientSocket->write(response, 2);
        socket.close();
        emit startSignalArrived();
    }else if (((buffer[1] == 1) && ((buffer[2] == 0) || (buffer[2] == 2)))
              || ((buffer[1] == 2) && ((buffer[2] == 0) && (buffer[3] == 2))))
    {
        cout << "send response" << endl;
        response[0] = 5;
        response[1] = 0x02;
        clientSocket->write(response, 2);
        if(clientSocket->waitForReadyRead() == true)
        {
            emit autheticationArived();
            clientSocket->waitForBytesWritten();
        }

    }else
    {
        response[0] = 5;
        response[1] = 0xff;
        clientSocket->write(response, 2);
        socket.close();
        emit startSignalArrived();
    }
}

void AppProxy::autheticationConfirmed()
{
    int ret = clientSocket->read(buffer, clientSocket->bytesAvailable());
    cout << "authentication" << endl;
    int usernameLen = buffer[1];
    int passwordLen = buffer[2+usernameLen];
    string username ="";
    string password ="";
    if(ret != 0)
    {
        buffer[ret] = '\0';
        cout << dec << ret << " Authentication message: "<< endl;
        std::cout.copyfmt(std::ios(NULL));
        for(int i = 0; i<usernameLen; i++)
        {
            username += buffer[2+i];
        }
        for(int i = 0; i<passwordLen; i++)
        {
            password += buffer[3+usernameLen+i];
        }
        cout<<username<<endl;
        cout<<password<<endl;
    }
    map<string, string>::iterator it;
    it = clients.find(username);
    if(it !=clients.end())
    {
        if(clients[username] == password)
        {
            response[0] = 0x01;
            response[1] = 0x00;
            clientSocket->write(response, 2);

            if(clientSocket->waitForReadyRead() == true)
            {
                emit serverInfoRecieved();
                clientSocket->waitForBytesWritten();
            }

        }else
        {
            response[0] = 0x01;
            response[1] = 0xff;
            clientSocket->write(response, 2);
            socket.close();
            emit startSignalArrived();
        }
    }else
    {
        response[0] = 0x01;
        response[1] = 0xff;
        clientSocket->write(response, 2);
        socket.close();
        emit startSignalArrived();
    }

}

void AppProxy::connectToServer()
{
    int ret = clientSocket->read(buffer, clientSocket->bytesAvailable());
    cout << ret << " connecting to server" << endl;
    qint16 portNum;
    qint32 firstOctet = (int)buffer[4];
    qint32 secondOctet = (int)buffer[5];
    qint32 thirdOctet = (int)buffer[6];
    qint32 fourthOctet = (int)buffer[7];
    qint32 ipv4 = (firstOctet * 16777216)
            + (secondOctet * 65536)
            + (thirdOctet * 256)
            + (fourthOctet);
    unsigned char lowerPart = (buffer[9]);
    unsigned char upperPart = (buffer[8]);
    portNum = (upperPart << 8) + lowerPart;
    cout <<portNum<<endl;
    QHostAddress addr(ipv4);
    serverSocket.connectToHost(addr, portNum);
    serverSocket.waitForConnected();
    if(serverSocket.waitForConnected() == false)
    {
        response[0] = 5;
        response[1] = 0xff;
        response[2] = 0x00;
        response[3]= 0x01; //IPv4
        for(int i=0;i<4;i++)
        {
            response[4+i] = buffer[4+i];
        }
        response[8] = buffer[8]; //first part of port
        response[9] = buffer[9]; //second part of port
        clientSocket->write(response, 10);
        socket.close();
        emit startSignalArrived();

    }else
    {
        cout << "Request to connect correct" <<endl;
        response[0] = 5;
        response[1] = 0x00;
        response[2] = 0x00;
        response[3]= 0x01; //IPv4
        for(int i=0;i<4;i++)
        {
            response[4+i] = buffer[4+i];
        }
        response[8] = buffer[8]; //first part of port
        response[9] = buffer[9]; //second part of port
        clientSocket->write(response, 10);

        if(clientSocket->waitForReadyRead() == true)
        {
            emit filePartArrived();
            serverSocket.waitForBytesWritten();
        }

    }

}
void AppProxy::sendToServer()
{
    cout << "Receiving file from client and sending to server" <<endl;
    int ret = 0;
    int ret1 = 0;
    int fileSize = 0;
    //Recieve size of file
    ret = clientSocket->read(buffer, 4);
    unsigned char firstOctet = (int)buffer[0];
    unsigned char secondOctet = (int)buffer[1];
    unsigned char thirdOctet = (int)buffer[2];
    unsigned char fourthOctet = (int)buffer[3];

    fileSize = (firstOctet << 24) + (secondOctet << 16) + (thirdOctet << 8) + fourthOctet;
    cout << fileSize << endl;

    while(fileSize > 0)
    {
        clientSocket->waitForReadyRead();
        ret = clientSocket->read(buffer, 512);
        response = buffer;
        serverSocket.waitForBytesWritten();
        ret1 = serverSocket.write(response, 512);
        clientSocket->waitForBytesWritten();
        clientSocket->write(buffer, 1);
        fileSize-=ret1;
    }
    socket.close();
    serverSocket.close();
    emit startSignalArrived();

}

