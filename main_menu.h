#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQueryModel>
#include <cashbox.h>
#include <product.h>
#include <receipt.h>
#include <cashier.h>
#include <requests.h>
#include <QSystemTrayIcon>

namespace Ui {
class main_menu;
}

class main_menu : public QWidget
{
    Q_OBJECT

public:
    explicit main_menu(QWidget *parent = nullptr);
    ~main_menu();

private slots:
    void on_cashbox_clicked();

    void on_receipt_clicked();

    void on_cashier_clicked();

    void on_log_clicked();

    void on_product_clicked();

    void on_add_clicked();

    void on_edit_clicked();

    void on_requests_clicked();

    void on_delete_2_clicked();

private:
    Ui::main_menu *ui;
    QSqlDatabase db;
    QSqlTableModel *cashboxModel;
    QSqlTableModel *productModel;
    QSqlTableModel *receiptModel;
    QSqlTableModel *cashierModel;
    QSqlTableModel *logModel;
    QSqlQueryModel *combo_box_model;
    QString chosen_table;
    cashbox *cashboxForm;
    product *productForm;
    receipt *receiptForm;
    cashier *cashierForm;
    requests *requestForm;
    QSystemTrayIcon* trayIcon;
};

#endif // MAIN_MENU_H
