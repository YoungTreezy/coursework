#ifndef PRODUCT_H
#define PRODUCT_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class product;
}

class product : public QDialog
{
    Q_OBJECT

public:
    explicit product(QString name, bool isEditing);
    ~product();

private slots:
    void on_save_clicked();

private:
    Ui::product *ui;
    QString old_name;
    bool editing;
    QSqlDatabase db;
};

#endif // PRODUCT_H
