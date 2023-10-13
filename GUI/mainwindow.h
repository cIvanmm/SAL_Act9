#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"neurona.h"
#include"listaneuronas.h"
#include<QMainWindow>
#include<QFileDialog>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QVector>
#include<QString>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QGraphicsScene>
#include<QGraphicsEllipseItem>
#include<QBrush>
#include<QPen>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ListaNeuronas lista;

private slots:
    void on_actionGuardar_triggered();

    void on_actionCargar_triggered();

    int delimitador(int, QString);

    void on_pushButton_add_clicked();

    void on_pushButton_addf_clicked();

    void on_pushButton_lista_clicked();

    void on_pushButton_salir_clicked();

    void on_pushButton_salir_lista_clicked();

    void on_pushButton_tabla_clicked();

    void on_pushButton_buscar_clicked();

    void on_pushButton_salir_tabla_clicked();

    void on_pushButton_mostrar_clicked();

    void on_pushButton_salir_mostrar_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
