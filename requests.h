#ifndef REQUESTS_H
#define REQUESTS_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQueryModel>

namespace Ui {
class requests;
}

class requests : public QWidget
{
    Q_OBJECT

public:
    explicit requests(QWidget *parent = nullptr);
    ~requests();

private slots:
    void on_same_products_clicked();

    void on_corps_clicked();

    void on_full_price_clicked();

    void on_max_clicked();

    void on_quantity_clicked();

private:
    Ui::requests *ui;
    QSqlTableModel *same_prosuctsModel;
    QSqlTableModel *corpModel;
    QSqlTableModel *full_priceModel;
    QSqlTableModel *maxModel;
    QSqlTableModel *quantityModel;
};

#endif // REQUESTS_H
