#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtSql>
#include <QDebug>

#include <QTableWidgetItem>

#include <QtNetwork>
#include <QTcpSocket>
#include <QTextStream>
#include <QAbstractSocket>

#include <QDesktopServices> //для открытия приложения, чтобы в нем отправить письмо
#include <QUrl>

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QPixmap>

#include "testforclient.h"

class CustomSqlTableModel : public QSqlTableModel
{
public:
    CustomSqlTableModel(QObject* parent = nullptr, QSqlDatabase db = QSqlDatabase())
            : QSqlTableModel(parent, db)
        {
            // Дополнительная инициализация вашей модели
        }

    Qt::ItemFlags flags(const QModelIndex& index) const override
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

private slots:
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
    Ui::MainWindow *ui;

     void VectorDataSaved(const std::vector<int> data) {this->rasstroystva_ball = data;}

    QSqlDatabase db;
    QSqlQuery* query;
    CustomSqlTableModel *model;
    int row;

    testForClient* windowWithTest;
    std::vector<int> rasstroystva_ball;
    std::vector<QString> rasstroystva = {"Депресивное растройство", "Тревожное растройство", "Растройство пищевого поведения", "Растройство адаптации", "Скизофрения",
                                         "Растройство внимания и гепиреактивности", "Растройство сна.", "Наркологическое растройство."};


    std::vector<std::vector<int>> matrix;
    void createGraphic();
    void createGrahpicStart();
};
#endif // MAINWINDOW_H
