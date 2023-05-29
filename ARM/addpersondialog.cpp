#include "addpersondialog.h"
#include "ui_addpersondialog.h"
#include <QDate>


addPersonDialog::addPersonDialog(QWidget *parent, CustomSqlTableModel *model) :
    QDialog(parent),
    ui(new Ui::addPersonDialog)
{
    ui->setupUi(this);
    this->model = model;
    QDate currentDate = QDate::currentDate();
    FillComboBox(currentDate);
    ui->lineEdit->setText(currentDate.toString("dd.MM.yyyy"));
}

addPersonDialog::~addPersonDialog()
{
    delete ui;
}

void addPersonDialog::FillComboBox(QDate date)
{
    QStringList blockTimeList = getFreeTimeList(date);
    QStringList freeTimeList = list_time;
    for (auto& i : blockTimeList) {
        auto it = std::find(freeTimeList.begin(), freeTimeList.end(), i);
        if(it != freeTimeList.end())
            freeTimeList.erase(it);
    }
    ui->comboBoxTime->clear();
    for (auto& time : freeTimeList) {
        ui->comboBoxTime->addItem(time);
    }
}

QStringList addPersonDialog::getFreeTimeList(QDate date)
{
    QStringList freeTimeList;

    QString queryStr = "SELECT Время FROM Client WHERE Дата = '" + date.toString("dd.MM.yyyy") + "'";

    QSqlQuery query;
    query.prepare(queryStr);
    if(query.exec()){
        while (query.next()) {
            QString time = query.value(0).toString();
            freeTimeList.append(time);
        }
    }
    else{
        qDebug() << "Ошибка выполнения запроса" << query.lastError().text();
    }
    return freeTimeList;
}


//// Использование делегата для QComboBox
//QComboBox* comboBox = new QComboBox(this);
//comboBox->setItemDelegate(new DateComboBoxDelegate(comboBox));

//// Пример добавления даты в QComboBox
//QDate date = QDate::currentDate();
//comboBox->addItem(date.toString("dd.MM.yyyy"), date);

void addPersonDialog::on_calendarWidget_selectionChanged()
{
    FillComboBox(ui->calendarWidget->selectedDate());
    ui->lineEdit->setText(ui->calendarWidget->selectedDate().toString("dd.MM.yyyy"));
}


void addPersonDialog::on_saveChangeButton_clicked()
{
    QString date = ui->lineEdit->text();
    QString time = ui->comboBoxTime->currentText();
    QString name = ui->lineEditName->text();
    if(date == "")
        QMessageBox::information(nullptr, "Внимание", "Выберите дату на календаре");
    if(time == "")
        QMessageBox::information(nullptr, "Внимание", "Выберите время из выпадающего списка");
    if(name == "")
        QMessageBox::information(nullptr, "Внимание", "Введите имя пациента для записи.");
    if(date != "" && name != "" && time != "") {
        QSqlQuery query;
        query.prepare("INSERT INTO Client (Дата, Время, ФИО) VALUES (?, ?, ?)");
        query.addBindValue(date);
        query.addBindValue(time);
        query.addBindValue(name);

        if(query.exec()){
            qDebug("Успешно");
            this->model->select();
            accept();
        }
        else{
            qDebug("Ошибка");
        }
    }

}


void addPersonDialog::on_unsaveChangeButton_clicked()
{
    reject();
}

