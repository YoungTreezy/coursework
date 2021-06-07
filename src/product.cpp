#include "product.h"
#include "ui_product.h"

product::product(QString name, bool isEditing) :
    ui(new Ui::product)
{
    ui->setupUi(this);
    product::setWindowTitle("Продукты");
    QSqlDatabase db = QSqlDatabase::database("cash_information_system");
    old_name = name;
    ui->product_name->setText(name);
    editing = isEditing;

    if (editing){
        QSqlQuery editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT corporation_name from product WHERE product_name = :_current_product_name");
        editQuery.bindValue(":_current_product_name", old_name);
        editQuery.exec();
        editQuery.first();
        ui->corp_name->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT shelf_life from product WHERE product_name = :_current_product_name");
        editQuery.bindValue(":_current_product_name", old_name);
        editQuery.exec();
        editQuery.first();
        ui->shelf_life->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT factory_price from product WHERE product_name = :_current_product_name");
        editQuery.bindValue(":_current_product_name", old_name);
        editQuery.exec();
        editQuery.first();
        ui->factory_price->setText(editQuery.value(0).toString());
    }
}

product::~product()
{
    delete ui;
}

void product::on_save_clicked()
{
    QSqlQuery queryModel = QSqlQuery(db);
    bool isOk = true;
    if (ui->corp_name->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите название фирмы!");
    }
    if (ui->product_name->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите название продукта!");
    }
    if (ui->shelf_life->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите срок годности!");
    }
    if (ui->factory_price->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите заводские цены!");
    }
    if (isOk){
        if (!editing){
            queryModel.prepare("select * from add_product(:_corp_name, :_product_name, :_shelf_life, :_factory_price)");
            queryModel.bindValue(":_corp_name", ui->corp_name->text());
            queryModel.bindValue(":_product_name", ui->product_name->text());
            queryModel.bindValue(":_shelf_life", ui->shelf_life->text());
            queryModel.bindValue(":_factory_price", ui->factory_price->text());
            isOk = queryModel.exec();
            if (isOk){
                QMessageBox::about(this,"Welcome!", "Новый продукт!");
                ui->corp_name->setText("");
                ui->product_name->setText("");
                ui->shelf_life->setText("");
                ui->factory_price->setText("");
                this->close();
            }
            else {
                QMessageBox::about(this,"Error!", "Продукт не был добавлен!");
            }
        }
        else{
            queryModel.prepare("select * from change_product(:_new_corp_name, :_old_product_name, :_new_product_name, :_new_shelf_life, :_new_factory_price)");
            queryModel.bindValue(":_new_corp_name", ui->corp_name->text());
            queryModel.bindValue(":_old_product_name", old_name);
            queryModel.bindValue(":_new_product_name", ui->product_name->text());
            queryModel.bindValue(":_new_shelf_life", ui->shelf_life->text());
            queryModel.bindValue(":_new_factory_price", ui->factory_price->text());
            isOk = queryModel.exec();
            if (isOk){
                QMessageBox::about(this,"Welcome!", "Параметры продукта были изменены!");
                ui->corp_name->setText("");
                ui->product_name->setText("");
                ui->shelf_life->setText("");
                ui->factory_price->setText("");
                this->close();
            }
            else {
                QMessageBox::about(this,"Error!", "Параметры не были изменены!");
            }
        }
    }
}

