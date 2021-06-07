#ifndef CASHBOX_H
#define CASHBOX_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class cashbox;
}

class cashbox : public QDialog
{
    Q_OBJECT

public:
    explicit cashbox(QString name, bool isEditing);
    ~cashbox();

private slots:
    void on_save_clicked();

private:
    Ui::cashbox *ui;
    QString old_name;
    bool editing;
    QSqlQueryModel *products;
    QSqlDatabase db;
};

#endif // CASHBOX_H
