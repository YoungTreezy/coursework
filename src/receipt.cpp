#include "receipt.h"
#include "ui_receipt.h"

receipt::receipt(int id, bool isEditing) :
    ui(new Ui::receipt)
{
    receipt::setWindowTitle("Чек");
    ui->setupUi(this);
    editing = isEditing;
    receiptId = id;
    QSqlDatabase db = QSqlDatabase::database("cash_information_system");

    products = new QSqlQueryModel;
    QSqlQuery get_products = QSqlQuery(db);
    get_products.prepare("select product_name from product");
    get_products.exec();
    products->setQuery(get_products);
    ui->id_product->setModel(products);

    cashboxes = new QSqlQueryModel;
    QSqlQuery get_cashbox = QSqlQuery(db);
    get_cashbox.prepare("select product_name from cashbox");
    get_cashbox.exec();
    cashboxes->setQuery(get_cashbox);
    ui->id_cashbox->setModel(cashboxes);

    cashiers = new QSqlQueryModel;
    QSqlQuery get_cashier = QSqlQuery(db);
    get_cashier.prepare("select lastname from cashier");
    get_cashier.exec();
    cashiers->setQuery(get_cashier);
    ui->id_cashier->setModel(cashiers);

    if (editing){
        QSqlQuery editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT shop_name from receipt WHERE id = :_current_id");
        editQuery.bindValue(":_current_id", receiptId);
        editQuery.exec();
        editQuery.first();
        ui->shop_name->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT address from receipt WHERE id = :_current_id");
        editQuery.bindValue(":_current_id", receiptId);
        editQuery.exec();
        editQuery.first();
        ui->address->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT inn from receipt WHERE id = :_current_id");
        editQuery.bindValue(":_current_id", receiptId);
        editQuery.exec();
        editQuery.first();
        ui->inn->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT quantity from receipt WHERE id = :_current_id");
        editQuery.bindValue(":_current_id", receiptId);
        editQuery.exec();
        editQuery.first();
        ui->quantity->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT product_name from cashbox WHERE id = (select id_cashbox from receipt where id = :_current_id)");
        editQuery.bindValue(":_current_id", receiptId);
        editQuery.exec();
        editQuery.first();
        cashboxes->setQuery(editQuery);
        ui->id_cashbox->setModel(cashboxes);

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT product_name from product WHERE id = (select id_product from receipt where id = :_current_id)");
        editQuery.bindValue(":_current_id", receiptId);
        editQuery.exec();
        editQuery.first();
        products->setQuery(editQuery);
        ui->id_product->setModel(products);

        editQuery = QSqlQuery(db);
        editQuery.prepare("SELECT lastname from cashier WHERE id = (select id_cashier from receipt where id = :_current_id)");
        editQuery.bindValue(":_current_id", receiptId);
        editQuery.exec();
        editQuery.first();
        cashiers->setQuery(editQuery);
        ui->id_cashier->setModel(cashiers);
    }
}

receipt::~receipt()
{
    delete ui;
}

void receipt::on_Save_clicked()
{
    QSqlQuery queryModel = QSqlQuery(db);
    bool isOk = true;
    if (ui->shop_name->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите название магазина!");
    }
    if (ui->address->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите адрес!");
    }
    if (ui->inn->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите inn!");
    }
    if (ui->id_cashbox->currentText() == ""){
        QMessageBox::about(this,"Error!", "Сперва заполните таблицу Cashbox!");
        this->close();
    }
    if (ui->quantity->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите количество продуктов!");
    }
    if (ui->id_cashier->currentText() == ""){
        QMessageBox::about(this,"Error!", "Сперва заполните таблицу Cashier!");
        this->close();
    }
    if (ui->id_product->currentText() == ""){
        QMessageBox::about(this,"Error!", "Сперва заполните таблицу Product!");
        this->close();
    }
    if (isOk){
        if (!editing){
            queryModel.prepare("select * from add_receipt(:_shop_name, :_address, :_inn, :_quantity, :_new_cashbox, :_new_cashier, :_new_product)");
            queryModel.bindValue(":_shop_name", ui->shop_name->text());
            queryModel.bindValue(":_address", ui->address->text());
            queryModel.bindValue(":_inn", ui->inn->text());
            queryModel.bindValue(":_quantity", ui->quantity->text());
            queryModel.bindValue(":_new_cashbox", ui->id_cashbox->currentText());
            queryModel.bindValue(":_new_cashier", ui->id_cashier->currentText());
            queryModel.bindValue(":_new_product", ui->id_product->currentText());
            isOk = queryModel.exec();
            if (isOk){
                QMessageBox::about(this,"Welcome!", "Добавлен новый чек!");
                ui->shop_name->setText("");
                ui->address->setText("");
                ui->inn->setText("");
                ui->quantity->setText("");
                this->close();
            }
            else {
                QMessageBox::about(this,"Error!", "Новый чек не был добавлен!");
                this->close();
            }
        }
        else {
            queryModel.prepare("select * from change_receipt(:_id, :_new_shop_name, :_new_address, :_new_inn, :_new_quantity, :_new_cashbox, :_new_cashier, :_new_product);");
            queryModel.bindValue(":_id", receiptId);
            queryModel.bindValue(":_new_shop_name", ui->shop_name->text());
            queryModel.bindValue(":_new_address", ui->address->text());
            queryModel.bindValue(":_new_inn", ui->inn->text());
            queryModel.bindValue(":_new_quantity", ui->quantity->text());
            queryModel.bindValue(":_new_cashbox", ui->id_cashbox->currentText());
            queryModel.bindValue(":_new_cashier", ui->id_cashier->currentText());
            queryModel.bindValue(":_new_product", ui->id_product->currentText());
            isOk = queryModel.exec();
            if (isOk){
                QMessageBox::about(this,"Welcome!", "Чек был изменен!");
                ui->shop_name->setText("");
                ui->address->setText("");
                ui->inn->setText("");
                ui->quantity->setText("");
                this->close();
            }
            else {
                QMessageBox::about(this,"Error!", "Чек не был изменен!");
                this->close();
            }
        }
    }
}

