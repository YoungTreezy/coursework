#include "cashbox.h"
#include "ui_cashbox.h"

cashbox::cashbox(QString name, bool isEditing) :
ui(new Ui::cashbox)
{
    ui->setupUi(this);
    cashbox::setWindowTitle("Касса");
    old_name = name;
    editing = isEditing;
    QSqlDatabase db = QSqlDatabase::database("cash_information_system");
    products = new QSqlQueryModel;
    QSqlQuery get_products = QSqlQuery(db);
    get_products.prepare("select product_name from product");
    get_products.exec();
    products->setQuery(get_products);
    ui->product_name->setModel(products);
    if (editing){
        ui->product_name->setCurrentText(old_name);

        QSqlQuery editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT shop_price from cashbox WHERE product_name = :_current_product_name");
        editQuery.bindValue(":_current_product_name", old_name);
        editQuery.exec();
        editQuery.first();
        ui->shop_price->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT vat from cashbox WHERE product_name = :_current_product_name");
        editQuery.bindValue(":_current_product_name", old_name);
        editQuery.exec();
        editQuery.first();
        ui->vat->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT bank_name from cashbox WHERE product_name = :_current_product_name");
        editQuery.bindValue(":_current_product_name", old_name);
        editQuery.exec();
        editQuery.first();
        ui->bank_name->setText(editQuery.value(0).toString());
    }
}

cashbox::~cashbox()
{
delete ui;
}

void cashbox::on_save_clicked()
{
    QSqlQuery queryModel = QSqlQuery(db);
    bool isOk = true;
    if (ui->shop_price->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите магазинную цену!");
    }
    if (ui->vat->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите НДС!");
    }
    if (ui->bank_name->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите название банка!");
    }
    if (ui->product_name->currentText() == ""){
        QMessageBox::about(this,"Error!", "Сперва заполните таблицу Product!");
        this->close();
    }
    if (isOk){
        if (!editing){
            queryModel.prepare("select * from add_cashbox(:_product_name, :_shop_price, :_vat, :_bank_name)");
            queryModel.bindValue(":_product_name", ui->product_name->currentText());
            queryModel.bindValue(":_shop_price", ui->shop_price->text());
            queryModel.bindValue(":_vat", ui->vat->text());
            queryModel.bindValue(":_bank_name", ui->bank_name->text());
            isOk = queryModel.exec();
            if (isOk){
                QMessageBox::about(this,"Welcome!", "Новая пометка в кассе!");
                ui->shop_price->setText("");
                ui->vat->setText("");
                ui->bank_name->setText("");
                this->close();
            }
            else {
                QMessageBox::about(this,"Error!", "Пометка не была сделана!");
            }
        }
        else{
            queryModel.prepare("select * from change_cashbox(:_old_product_name, :_new_product_name, :_new_shop_price, :_new_vat, :_new_bank_name)");
            queryModel.bindValue(":_old_product_name", old_name);
            queryModel.bindValue(":_new_product_name", ui->product_name->currentText());
            queryModel.bindValue(":_new_shop_price", ui->shop_price->text());
            queryModel.bindValue(":_new_vat", ui->vat->text());
            queryModel.bindValue(":_new_bank_name", ui->bank_name->text());
            isOk = queryModel.exec();
            if (isOk){
                QMessageBox::about(this,"Welcome!", "Пометка в кассе была изменена!");
                ui->shop_price->setText("");
                ui->vat->setText("");
                ui->bank_name->setText("");
                this->close();
            }
            else {
                QMessageBox::about(this,"Error!", "Пометка не была изменена!");
            }

        }
    }
}
