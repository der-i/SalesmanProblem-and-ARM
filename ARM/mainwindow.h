#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>  //для создания окон и редактирования в ui
#include <QtWidgets>

#include <QSqlDatabase> //для работы с базой данных
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtSql>
#include <QDebug>

#include <QTableWidgetItem> //дополнение к виджетам

#include <QtNetwork>        //для работы с инттернет соединением
#include <QTcpSocket>
#include <QTextStream>
#include <QAbstractSocket>

#include <QDesktopServices> //для открытия приложения, чтобы в нем отправить письмо
#include <QUrl>

#include <QDialog>          //для диалоговых окон

#include <QtCharts/QChartView>  //для построения графика
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QPixmap>              //для вывода картинки

#include "testforclient.h"      //для взаимодействия окон

class CustomSqlTableModel : public QSqlTableModel       //класс кастомной таблицы для отображения данных из базы данных
{
public:
    CustomSqlTableModel(QObject* parent = nullptr, QSqlDatabase db = QSqlDatabase())
            : QSqlTableModel(parent, db)
        {
            // Дополнительная инициализация вашей модели
        }

    Qt::ItemFlags flags(const QModelIndex& index) const override        //добавлен новый метод для того, чтобы запретить при двойном клике редактировать таблицу
    {
        Qt::ItemFlags flags = QSqlTableModel::flags(index);
        return flags & ~Qt::ItemIsEditable;
    }
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots://слоты описанны в cpp файле
    void on_addButton_clicked();

    void on_tablePerson_clicked(const QModelIndex &index);

    void on_deleteButton_clicked();

    void on_calendarWidget_selectionChanged();

    void on_pushEmail_clicked();

    void on_pushButtonOpen_clicked();

    void on_pushButtonF5_clicked();

    void on_pushButton_clicked();

    void on_tablePerson_doubleClicked(const QModelIndex &index);

private:
    //дополниетельные переменные и методы для взаимодействия окон / работы главного окна
    Ui::MainWindow *ui;

     void VectorDataSaved(const std::vector<int> data) {this->rasstroystva_ball = data;}

    QSqlDatabase db;            //база данных
    QSqlQuery* query;           //таблица базы данных
    CustomSqlTableModel *model; //модель базы данных
    int row;

    testForClient* windowWithTest;  //окно для теста
    std::vector<int> rasstroystva_ball; //вектор для подсчета диагноза
    std::vector<QString> rasstroystva = {"Депресивное растройство", "Тревожное растройство", "Растройство пищевого поведения", "Растройство адаптации", "Скизофрения",
                                         "Растройство внимания и гепиреактивности", "Растройство сна.", "Наркологическое растройство."};


    std::vector<std::vector<int>> matrix;
    void createGraphic();
    void createGrahpicStart();
};
#endif // MAINWINDOW_H
