#ifndef PROXY_H
#define PROXY_H

#include <QtWidgets/QMainWindow>
#include "ui_proxy.h"

class proxy : public QMainWindow
{
	Q_OBJECT

public:
	proxy(QWidget *parent = 0);
	~proxy();

private:
	Ui::proxyClass ui;
};

#endif // PROXY_H
