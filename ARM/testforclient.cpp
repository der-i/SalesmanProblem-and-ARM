#include "testforclient.h"
#include "ui_testforclient.h"

testForClient::testForClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testForClient)
{
    ui->setupUi(this);
    ui->labelQuestions->setText(questions[0]);
    current_question = 0;
}

testForClient::~testForClient()
{
    delete ui;
}


//при нажатии на кнопку меняем вопрос
void testForClient::on_pushAnswer_clicked()
{
    bool checked = false;
    if(current_question == countQuestions)
    {
        emit this->VectorSaved(this->answers_balance);      //когда вопросы закончильсь отправляем данные в главное окно
        close();
    }
    else {
        if(ui->radioButtonNioigda->isChecked()){            //выполнение тестирования
            this->answers_balance.push_back(0);
            checked = true;
        }
        else if(ui->radioButtonRedko->isChecked()){
            this->answers_balance.push_back(1);
            checked = true;
        }
        else if(ui->radioButtonChasto->isChecked()){
            this->answers_balance.push_back(2);
            checked = true;
        }
        else if(ui->radioButtonPostoyanno->isChecked()){
            this->answers_balance.push_back(3);
            checked = true;
        }
        if(!checked){
            QMessageBox::warning(this, "Предупреждение.", "Выберите ответ.");
        }
        else {
            // Очистка выбора вариантов ответа
            ui->radioButtonNioigda->setChecked(false);
            ui->radioButtonRedko->setChecked(false);
            ui->radioButtonChasto->setChecked(false);
            ui->radioButtonPostoyanno->setChecked(false);

            if(current_question < countQuestions)
                ui->labelQuestions->setText(questions[this->current_question]);
            ++this->current_question;
        }
    }

}

