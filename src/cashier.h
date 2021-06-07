#ifndef CASHIER_H
#define CASHIER_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class cashier;
}

class cashier : public QDialog
{
    Q_OBJECT

public:
    explicit cashier(QString lastname, bool isEditing);
    ~cashier();

private slots:
    void on_save_clicked();

private:
    Ui::cashier *ui;
    QString old_lastname;
    bool editing;
    QSqlDatabase db;
};

#endif // CASHIER_H
