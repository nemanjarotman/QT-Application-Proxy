#include <QCoreApplication>
#include "proxy.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Proxy proxy;


    return a.exec();
}
