#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("Authorization");
    MainWindow::move(QApplication::desktop()->width()/2, QApplication::desktop()->height()/2);
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
    login = "";
    password = "";
}


void MainWindow::on_login_button_clicked()
{
    login = ui -> login_lineEdit->text();
    password = ui ->password_lineEdit->text();
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("cash_information_system");
    db.setHostName("localhost");
    db.setUserName(login);
    db.setPassword(password);
    bool checker = db.open();
    if (checker && (login != "" || password != "")){
        mainMenu = new main_menu();
        mainMenu -> show();
        this->close();
    } else {
        QMessageBox::about(this, "Error", "Пароль/логин был введен не верно!");
    }
    ui ->password_lineEdit->setText("");
}

