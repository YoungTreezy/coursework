#include "main_menu.h"
#include "ui_main_menu.h"

main_menu::main_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_menu)
{
    ui->setupUi(this);
    main_menu::setWindowTitle("Coursework");
    QSqlDatabase db = QSqlDatabase::database("cash_information_system");
    chosen_table = "none";
    cashboxForm = new cashbox("", false);
    cashierForm = new cashier("", false);
    receiptForm = new receipt(0, false);
    productForm = new product("", false);
    requestForm = new requests();
}

main_menu::~main_menu()
{
    delete ui;
}

void main_menu::on_cashbox_clicked()
{
    main_menu::setWindowTitle("Cashboxes");
    cashboxModel = new QSqlTableModel(this, db);
    cashboxModel -> setTable("cashbox");
    cashboxModel -> select();
    ui -> tableView -> setModel(cashboxModel);
    chosen_table = "cashbox";

    combo_box_model = new QSqlQueryModel;
    QSqlQuery get_cashbox = QSqlQuery(db);
    get_cashbox.prepare("SELECT product_name FROM cashbox");
    get_cashbox.exec();
    combo_box_model->setQuery(get_cashbox);
    ui -> comboBox->setModel(combo_box_model);
}


void main_menu::on_receipt_clicked()
{
    ui->comboBox->setCurrentIndex(0);
    main_menu::setWindowTitle("Receipt");
    receiptModel = new QSqlTableModel(this, db);
    receiptModel -> setTable("receipt");
    receiptModel ->select();
    ui -> tableView -> setModel(receiptModel);
    chosen_table = "receipt";

    combo_box_model = new QSqlQueryModel;
    QSqlQuery get_receipt = QSqlQuery(db);
    get_receipt.prepare("SELECT id FROM receipt");
    get_receipt.exec();
    combo_box_model->setQuery(get_receipt);
    ui -> comboBox->setModel(combo_box_model);
}


void main_menu::on_cashier_clicked()
{
    main_menu::setWindowTitle("Cashiers");
    cashierModel = new QSqlTableModel(this, db);
    cashierModel -> setTable("cashier");
    cashierModel -> select();
    ui -> tableView -> setModel(cashierModel);
    chosen_table = "cashier";

    combo_box_model = new QSqlQueryModel;
    QSqlQuery get_cashier = QSqlQuery(db);
    get_cashier.prepare("SELECT lastname FROM cashier");
    get_cashier.exec();
    combo_box_model->setQuery(get_cashier);
    ui -> comboBox->setModel(combo_box_model);
}


void main_menu::on_log_clicked()
{
    main_menu::setWindowTitle("Logs");
    logModel = new QSqlTableModel(this, db);
    logModel -> setTable("log");
    logModel -> select();
    ui -> tableView -> setModel(logModel);
    combo_box_model = new QSqlQueryModel;
    ui->comboBox->setModel(combo_box_model);
}


void main_menu::on_product_clicked()
{
    main_menu::setWindowTitle("Products");
    productModel = new QSqlTableModel(this, db);
    productModel -> setTable("product");
    productModel -> select();
    ui -> tableView -> setModel(productModel);
    chosen_table = "product";

    combo_box_model = new QSqlQueryModel;
    QSqlQuery get_product = QSqlQuery(db);
    get_product.prepare("SELECT product_name FROM product");
    get_product.exec();
    combo_box_model->setQuery(get_product);
    ui -> comboBox->setModel(combo_box_model);
}


void main_menu::on_add_clicked()
{
    if (chosen_table == "none"){
        QMessageBox::about(this, "Error", "Выберите таблицу которую хотите изменить!");
    }
    if (chosen_table == "cashbox"){
        cashboxForm = new cashbox("", false);
        cashboxForm->show();
    }
    if (chosen_table == "product"){
        productForm = new product("", false);
        productForm->show();
    }
    if (chosen_table == "receipt"){
        receiptForm->show();
    }
    if (chosen_table == "cashier"){
        cashierForm = new cashier("", false);
        cashierForm->show();
    }
}


void main_menu::on_edit_clicked()
{
    if (chosen_table == "none"){
        QMessageBox::about(this, "Error", "Выберите таблицу которую хотите изменить!");
    }
    if (chosen_table == "cashbox"){
        cashboxForm = new cashbox(ui->comboBox->currentText(), true);
        cashboxForm->show();
    }
    if (chosen_table == "product"){
        productForm = new product(ui->comboBox->currentText(), true);
        productForm->show();
    }
    if (chosen_table == "receipt"){
        receiptForm = new receipt(ui->comboBox->currentText().toInt(), true);
        receiptForm->show();
    }
    if (chosen_table == "cashier"){
        cashierForm = new cashier(ui->comboBox->currentText(), true);
        cashierForm->show();
    }
}


void main_menu::on_requests_clicked()
{
    requestForm->show();
}


void main_menu::on_delete_2_clicked()
{
    QSqlQuery deleteQuery = QSqlQuery(db);
    QString item = ui->comboBox->currentText();
    bool checker;
    if (chosen_table == "cashbox"){
        deleteQuery.prepare("SELECT * FROM public.delete_cashbox(:_name)");
        deleteQuery.bindValue(":_name", item);
        checker = deleteQuery.exec();
        if (!checker){
            QMessageBox::about(this,"Error", "Ошибка! Касса " + item + " не была удалена!");

        }
    }
    if (chosen_table == "product"){
        deleteQuery.prepare("SELECT * FROM public.delete_product(:_product_name)");
        deleteQuery.bindValue(":_product_name", item);
        checker = deleteQuery.exec();
        if (!checker){
            QMessageBox::about(this,"Error", "Ошибка! Продукт " + item + " не был удален!");

        }
    }
    if (chosen_table == "cashier"){
        deleteQuery.prepare("SELECT * FROM public.delete_cashier(:_lastname)");
        deleteQuery.bindValue(":_lastname", item);
        checker = deleteQuery.exec();
        if (!checker){
            QMessageBox::about(this,"Error", "Ошибка! Кассир " + item + " не был удален!");

        }
    }
    if (chosen_table == "receipt"){
        deleteQuery.prepare("SELECT * FROM public.delete_receipt(:_id)");
        deleteQuery.bindValue(":_id", item.toInt());
        checker = deleteQuery.exec();
        if (!checker){
            QMessageBox::about(this,"Error", "Ошибка! Чек " + item + " не был удален!");

        }
    }
}

