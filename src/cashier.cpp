#include "cashier.h"
#include "ui_cashier.h"

cashier::cashier(QString lastname, bool isEditing) :
    ui(new Ui::cashier)
{
    ui->setupUi(this);
    cashier::setWindowTitle("Кассир");
    QSqlDatabase db = QSqlDatabase::database("cash_information_system");
    old_lastname = lastname;
    editing = isEditing;
    ui->lastname->setText(lastname);
    if (editing){
        QSqlQuery editQuery = QSqlQuery(db);
        editQuery.prepare("select firstname from cashier where lastname = :_current_lastname");
        editQuery.bindValue(":_current_lastname", old_lastname);
        editQuery.exec();
        editQuery.first();
        ui->firstname->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("select place_of_birth from cashier where lastname = :_current_lastname");
        editQuery.bindValue(":_current_lastname", old_lastname);
        editQuery.exec();
        editQuery.first();
        ui->place_of_birth->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("select gender from cashier where lastname = :_current_lastname");
        editQuery.bindValue(":_current_lastname", old_lastname);
        editQuery.exec();
        editQuery.first();
        ui->gender->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("select place_of_study from cashier where lastname = :_current_lastname");
        editQuery.bindValue(":_current_lastname", old_lastname);
        editQuery.exec();
        editQuery.first();
        ui->place_of_study->setText(editQuery.value(0).toString());

        editQuery = QSqlQuery(db);
        editQuery.prepare("select army from cashier where lastname = :_current_lastname");
        editQuery.bindValue(":_current_lastname", old_lastname);
        editQuery.exec();
        editQuery.first();
        ui->army->setChecked(editQuery.value(0).toBool());

        editQuery = QSqlQuery(db);
        editQuery.prepare("select age from cashier where lastname = :_current_lastname");
        editQuery.bindValue(":_current_lastname", old_lastname);
        editQuery.exec();
        editQuery.first();
        ui->age->setText(editQuery.value(0).toString());
    }
}

cashier::~cashier()
{
    delete ui;
}

void cashier::on_save_clicked()
{
    QSqlQuery queryModel = QSqlQuery(db);
    bool isOk = true;
    if (ui->firstname->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите имя кассира!");
    }
    if (ui->lastname->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите фамилию кассира!");
    }
    if (ui->place_of_birth->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите место рождения кассира!");
    }
    if (ui->place_of_study->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите место учебы кассира!");
    }
    if (ui->gender->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите пол кассира!");
    }
    if (ui->age->text() == ""){
        isOk = false;
        QMessageBox::about(this,"Error!", "Введите возраст кассира!");
    }
    if (isOk){
        if (!editing){
            queryModel.prepare("select * from add_cashier(:_firstname, :_lastname, :_age, :_place_of_birth, :_gender, :_place_of_study, :_army)");
            queryModel.bindValue(":_firstname", ui->firstname->text());
            queryModel.bindValue(":_lastname", ui->lastname->text());
            queryModel.bindValue(":_age", ui->age->text());
            queryModel.bindValue(":_place_of_birth", ui->place_of_birth->text());
            queryModel.bindValue(":_gender", ui->gender->text());
            queryModel.bindValue(":_place_of_study", ui->place_of_birth->text());
            queryModel.bindValue(":_army", ui->army->isChecked());
            isOk = queryModel.exec();
            if (isOk){
                QMessageBox::about(this,"Welcome!", "Новый кассир!");
                ui->firstname->setText("");
                ui->lastname->setText("");
                ui->age->setText("");
                ui->place_of_birth->setText("");
                ui->gender->setText("");
                ui->place_of_study->setText("");
                this->close();
            }
            else {
                QMessageBox::about(this,"Error!", "Кассир не был добавлен!");
            }
        }
        else{
            queryModel.prepare("select * from change_cashier(:_new_firstname, :_old_lastname, :_new_lastname, :_new_place_of_birth, :_new_gender, :_new_place_of_study, :_new_army, :_new_age)");
            queryModel.bindValue(":_new_firstname", ui->firstname->text());
            queryModel.bindValue(":_old_lastname", old_lastname);
            queryModel.bindValue(":_new_lastname", ui->lastname->text());
            queryModel.bindValue(":_new_place_of_birth", ui->place_of_birth->text());
            queryModel.bindValue(":_new_gender", ui->gender->text());
            queryModel.bindValue(":_new_place_of_study", ui->place_of_birth->text());
            queryModel.bindValue(":_new_army", ui->army->isChecked());
            queryModel.bindValue(":_new_age", ui->age->text());
            isOk = queryModel.exec();
            if (isOk){
                QMessageBox::about(this,"Welcome!", "Данные кассира были изменены!");
                ui->firstname->setText("");
                ui->lastname->setText("");
                ui->age->setText("");
                ui->place_of_birth->setText("");
                ui->gender->setText("");
                ui->place_of_study->setText("");
                this->close();
            }
            else {
                QMessageBox::about(this,"Error!", "Данные кассира не были изменены!");
            }
        }
    }
}

