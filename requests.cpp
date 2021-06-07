#include "requests.h"
#include "ui_requests.h"

requests::requests(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::requests)
{
    requests::setWindowTitle("Запросы");
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database("cash_information_system");
}

requests::~requests()
{
    delete ui;
}

void requests::on_same_products_clicked()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT product_name, "
        "SUM (CASE "
          "WHEN id_product = 13 THEN 1 "
          "ELSE 0 "
          "END "
        ") AS suquantitym_of_products "
        "FROM product, receipt "
        "WHERE receipt.id_product = product.id AND product.id = 13 "
        "GROUP BY product_name");
    ui->tableView->setModel(queryModel);
}


void requests::on_corps_clicked()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT * FROM num_of_products ORDER BY quantity");
    ui->tableView->setModel(queryModel);
}


void requests::on_full_price_clicked()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT receipt.id, receipt.quantity,"
        "(SELECT shop_price FROM cashbox WHERE cashbox.id = receipt.id_cashbox),"
        "(SELECT product_name FROM product WHERE product.id = receipt.id_product),"
          "cashbox.shop_price * receipt.quantity AS full_price "
          "FROM cashbox, receipt "
        "where receipt.quantity > (select sum(receipt.quantity)/count(receipt.quantity) from receipt)");
    ui->tableView->setModel(queryModel);
}


void requests::on_max_clicked()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT id_product, MAX(quantity), product_name "
        "FROM receipt, product "
        "WHERE product.id = receipt.id_product "
        "GROUP BY id_product, product_name "
        "HAVING (MAX(quantity) >= 4)");
    ui->tableView->setModel(queryModel);
}


void requests::on_quantity_clicked()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT quantity, timestamp FROM receipt "
           "WHERE id_product = any(select id from product where corporation_name='H&M')");
    ui->tableView->setModel(queryModel);
}

