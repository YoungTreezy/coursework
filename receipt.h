#ifndef RECEIPT_H
#define RECEIPT_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class receipt;
}

class receipt : public QDialog
{
    Q_OBJECT

public:
    explicit receipt(int id, bool isEditing);
    ~receipt();

private slots:
    void on_Save_clicked();

private:
    Ui::receipt *ui;
    bool editing;
    QSqlQueryModel *products;
    QSqlQueryModel *cashboxes;
    QSqlQueryModel *cashiers;
    QSqlDatabase db;
    int receiptId;
};

#endif // RECEIPT_H
