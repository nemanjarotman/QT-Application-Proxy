#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_server.h"

class server : public QMainWindow
{
	Q_OBJECT

public:
	server(QWidget *parent = 0);
	~server();

private:
	Ui::serverClass ui;
};

#endif // SERVER_H
