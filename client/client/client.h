#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_client.h"

class client : public QMainWindow
{
	Q_OBJECT

public:
	client(QWidget *parent = 0);
	~client();

private:
	Ui::clientClass ui;
};

#endif // CLIENT_H
