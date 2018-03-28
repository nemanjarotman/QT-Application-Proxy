#include "proxy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	proxy w;
	w.show();
	return a.exec();
}
