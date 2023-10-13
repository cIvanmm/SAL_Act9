#include "mainwindow.h"
#include "./ui_mainwindow.h"
#define button_size_x 111
#define button_size_y 31
#define line_size_x 113
#define line_size_y 24

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui ->pushButton_salir_lista ->setFixedSize(0, 0);
    ui ->pushButton_buscar ->setFixedSize(0, 0);
    ui ->pushButton_salir_tabla ->setFixedSize(0, 0);
    ui ->pushButton_salir_mostrar ->setFixedSize(0, 0);
    ui ->plainTextEdit_lista ->setFixedSize(0, 0);
    ui ->line_buscar ->setFixedSize(0, 0);
    ui ->tableWidget_tabla ->setColumnCount(7);
    QString str1 ="Id", str2 ="Voltaje", str3 ="X", str4 ="Y", str5 ="Red", str6 ="Green", str7 ="Blue";
    QStringList labels =(QStringList() <<str1 <<str2 <<str3 <<str4 <<str5 <<str6 <<str7);
    ui ->tableWidget_tabla ->setHorizontalHeaderLabels(labels);
    ui ->tableWidget_tabla ->setFixedSize(0, 0);
    ui ->graphicsViews_ellipses ->setFixedSize(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGuardar_triggered()
{
    QString filename =QFileDialog::getOpenFileName(this, tr("Open File"),"C:/Users/Ivan/Downloads", tr("Text Files(*.txt)"));
    QFile archivo(filename);
    if(!archivo.open(QFile::WriteOnly |QFile::Text)){
        QMessageBox::warning(this, "title", "No se pudo abrir el archivo...");
    }
    QTextStream out(&archivo);
    QString datos;
    if(lista.cant_neuronas() ==0){
        datos =QString("");
    }
    else{
        for(size_t i =0; i <lista.cant_neuronas(); i ++){
            datos =QString("%1;%2;%3;%4;%5;%6;%7\n").arg(lista.getnid(i))
                        .arg(lista.getnvoltaje(i)).arg(lista.getnx(i))
                        .arg(lista.getny(i)).arg(lista.getnred(i))
                        .arg(lista.getngreen(i)).arg(lista.getnblue(i));
            out <<datos;
        }
    }
    archivo.close();
}

void MainWindow::on_actionCargar_triggered()
{
    QString filename =QFileDialog::getOpenFileName(this, tr("Open File"),"C:/Users/Ivan/Downloads", tr("Text Files(*.txt)"));
    QFile archivo(filename);
    if(!archivo.open(QFile::ReadOnly |QFile::Text)){
        QMessageBox::warning(this, "title", "No se pudo abrir el archivo...");
    }
    QTextStream in(&archivo);
    QString datos;
    int pyc1, pyc2;
    while(!in.atEnd()){
        datos =in.readLine();
        pyc1 =0;
        pyc2 =delimitador(pyc1 +1, datos);
        ui ->line_id ->setText(datos.sliced(pyc1, (pyc2 -pyc1)));
        pyc2 ++;
        pyc1 =delimitador(pyc2 +1, datos);
        ui ->line_voltaje ->setText(datos.sliced(pyc2, (pyc1 -pyc2)));
        pyc1 ++;
        pyc2 =delimitador(pyc1 +1, datos);
        ui ->line_x ->setText(datos.sliced(pyc1, (pyc2 -pyc1)));
        pyc2 ++;
        pyc1 =delimitador(pyc2 +1, datos);
        ui ->line_y ->setText(datos.sliced(pyc2, (pyc1 -pyc2)));
        pyc1 ++;
        pyc2 =delimitador(pyc1 +1, datos);
        ui ->line_red ->setText(datos.sliced(pyc1, (pyc2 -pyc1)));
        pyc2 ++;
        pyc1 =delimitador(pyc2 +1, datos);
        ui ->line_green ->setText(datos.sliced(pyc2, (pyc1 -pyc2)));
        pyc1 ++;
        pyc2 =delimitador(pyc1 +1, datos);
        ui ->line_blue ->setText(datos.sliced(pyc1, (pyc2 -pyc1)));
        on_pushButton_addf_clicked();
    }
    archivo.close();
}

int MainWindow::delimitador(int pyc, QString datos){
    for(; pyc <datos.length(); pyc ++){
        if(datos[pyc] ==';'){
            return pyc;
        }
    }
    return pyc;
}

void MainWindow::on_pushButton_add_clicked()
{
    QString id, voltaje, x, y, red, green, blue;
    id =ui ->line_id ->text();
    voltaje =ui ->line_voltaje ->text();
    x =ui ->line_x ->text();
    y =ui ->line_y ->text();
    red =ui ->line_red ->text();
    green =ui ->line_green ->text();
    blue =ui ->line_blue ->text();
    Neurona neurona(id.toInt(), voltaje.toFloat(), x.toInt(), y.toInt(), red.toInt(), green.toInt(), blue.toInt());
    lista.agregar_inicio(neurona);
    ui ->line_id ->setText("");
    ui ->line_voltaje ->setText("");
    ui ->line_x ->setText("");
    ui ->line_y ->setText("");
    ui ->line_red ->setText("");
    ui ->line_green ->setText("");
    ui ->line_blue ->setText("");
}

void MainWindow::on_pushButton_addf_clicked()
{
    QString id, voltaje, x, y, red, green, blue;
    id =ui ->line_id ->text();
    voltaje =ui ->line_voltaje ->text();
    x =ui ->line_x ->text();
    y =ui ->line_y ->text();
    red =ui ->line_red ->text();
    green =ui ->line_green ->text();
    blue =ui ->line_blue ->text();
    Neurona neurona(id.toInt(), voltaje.toFloat(), x.toInt(), y.toInt(), red.toInt(), green.toInt(), blue.toInt());
    lista.agregar_final(neurona);
    ui ->line_id ->setText("");
    ui ->line_voltaje ->setText("");
    ui ->line_x ->setText("");
    ui ->line_y ->setText("");
    ui ->line_red ->setText("");
    ui ->line_green ->setText("");
    ui ->line_blue ->setText("");
}

void MainWindow::on_pushButton_lista_clicked()
{
    ui ->label_id ->setText("");
    ui ->label_voltaje ->setText("");
    ui ->label_x ->setText("");
    ui ->label_y ->setText("");
    ui ->label_r ->setText("");
    ui ->label_g ->setText("");
    ui ->label_b ->setText("");
    ui ->line_id ->setFixedSize(0, 0);
    ui ->line_voltaje ->setFixedSize(0, 0);
    ui ->line_x ->setFixedSize(0, 0);
    ui ->line_y ->setFixedSize(0, 0);
    ui ->line_red ->setFixedSize(0, 0);
    ui ->line_green ->setFixedSize(0, 0);
    ui ->line_blue ->setFixedSize(0, 0);
    ui ->pushButton_add ->setFixedSize(0, 0);
    ui ->pushButton_addf ->setFixedSize(0, 0);
    ui ->pushButton_lista ->setFixedSize(0, 0);
    ui ->pushButton_tabla ->setFixedSize(0, 0);
    ui ->pushButton_mostrar ->setFixedSize(0, 0);
    ui ->pushButton_salir ->setFixedSize(0, 0);
    ui ->pushButton_salir_lista ->setFixedSize(button_size_x, button_size_y);
    ui ->plainTextEdit_lista ->setFixedSize(251, 291);
    if(lista.cant_neuronas() ==0)
        ui ->plainTextEdit_lista ->setPlainText("No hay ninguna neurona registrada...");
    else{
        QString cadena;
        for(size_t i =0; i <lista.cant_neuronas(); i ++){
            cadena =QString("Neurona: %1\nVoltaje: %2\nPosicion: ("
                             "%3, %4)\nRGB: (%5, %6, %7)\n\n").arg(lista.getnid(i))
                         .arg(lista.getnvoltaje(i)).arg(lista.getnx(i))
                         .arg(lista.getny(i)).arg(lista.getnred(i))
                         .arg(lista.getngreen(i)).arg(lista.getnblue(i));
            ui ->plainTextEdit_lista ->insertPlainText(cadena);
        }
    }
}

void MainWindow::on_pushButton_salir_clicked()
{
    close();
}

void MainWindow::on_pushButton_salir_lista_clicked()
{
    ui ->label_id ->setText("Id:");
    ui ->label_voltaje ->setText("Voltaje:");
    ui ->label_x ->setText("Posicion X:");
    ui ->label_y ->setText("Posicion Y:");
    ui ->label_r ->setText("Red:");
    ui ->label_g ->setText("Green:");
    ui ->label_b ->setText("Blue:");
    ui ->line_id ->setFixedSize(line_size_x, line_size_y);
    ui ->line_voltaje ->setFixedSize(line_size_x, line_size_y);
    ui ->line_x ->setFixedSize(line_size_x, line_size_y);
    ui ->line_y ->setFixedSize(line_size_x, line_size_y);
    ui ->line_red ->setFixedSize(line_size_x, line_size_y);
    ui ->line_green ->setFixedSize(line_size_x, line_size_y);
    ui ->line_blue ->setFixedSize(line_size_x, line_size_y);
    ui ->pushButton_add ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_addf ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_lista ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_tabla ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_mostrar ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_salir ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_salir_lista ->setFixedSize(0, 0);
    ui ->plainTextEdit_lista ->setPlainText("");
    ui ->plainTextEdit_lista ->setFixedSize(0, 0);
}

void MainWindow::on_pushButton_tabla_clicked()
{
    ui ->tableWidget_tabla ->setFixedSize(891, 291);
    ui ->label_id ->setText("");
    ui ->label_voltaje ->setText("");
    ui ->label_x ->setText("");
    ui ->label_y ->setText("");
    ui ->label_r ->setText("");
    ui ->label_g ->setText("");
    ui ->label_b ->setText("");
    ui ->line_id ->setFixedSize(0, 0);
    ui ->line_voltaje ->setFixedSize(0, 0);
    ui ->line_x ->setFixedSize(0, 0);
    ui ->line_y ->setFixedSize(0, 0);
    ui ->line_red ->setFixedSize(0, 0);
    ui ->line_green ->setFixedSize(0, 0);
    ui ->line_blue ->setFixedSize(0, 0);
    ui ->pushButton_add ->setFixedSize(0, 0);
    ui ->pushButton_addf ->setFixedSize(0, 0);
    ui ->pushButton_lista ->setFixedSize(0, 0);
    ui ->pushButton_tabla ->setFixedSize(0, 0);
    ui ->pushButton_mostrar ->setFixedSize(0, 0);
    ui ->pushButton_salir ->setFixedSize(0, 0);
    ui ->line_buscar ->setFixedSize(line_size_x, line_size_y);
    ui ->pushButton_buscar ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_salir_tabla ->setFixedSize(button_size_x, button_size_y);
    ui ->tableWidget_tabla ->setRowCount(lista.cant_neuronas());
    QString cadena;
    size_t i, j;
    QTableWidgetItem *item;
    for(i =0; i <lista.cant_neuronas(); i ++){
        j =0;
        cadena =QString("%1").arg(lista.getnid(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getnvoltaje(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getnx(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getny(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getnred(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getngreen(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getnblue(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
    }
}

void MainWindow::on_pushButton_buscar_clicked()
{
    int rows =0, j;
    ui ->tableWidget_tabla ->clearContents();
    ui ->tableWidget_tabla ->setRowCount(0);
    if(lista.cant_neuronas() !=0){
        QTableWidgetItem *item;
        QString buscado =ui ->line_buscar ->text(), cadena;
        for(size_t i =0; i <lista.cant_neuronas(); i ++){
            cadena =QString("%1").arg(lista.getnid(i));
            if(buscado ==cadena){
                rows ++;
                j =0;
                ui ->tableWidget_tabla ->setRowCount(rows);
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getnvoltaje(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getnx(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getny(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getnred(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getngreen(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getnblue(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
            }
        }
    }
}

void MainWindow::on_pushButton_salir_tabla_clicked()
{
    ui ->tableWidget_tabla ->clearContents();
    ui ->tableWidget_tabla ->setFixedSize(0, 0);
    ui ->label_id ->setText("Id:");
    ui ->label_voltaje ->setText("Voltaje:");
    ui ->label_x ->setText("Posicion X:");
    ui ->label_y ->setText("Posicion Y:");
    ui ->label_r ->setText("Red:");
    ui ->label_g ->setText("Green:");
    ui ->label_b ->setText("Blue:");
    ui ->line_id ->setFixedSize(line_size_x, line_size_y);
    ui ->line_voltaje ->setFixedSize(line_size_x, line_size_y);
    ui ->line_x ->setFixedSize(line_size_x, line_size_y);
    ui ->line_y ->setFixedSize(line_size_x, line_size_y);
    ui ->line_red ->setFixedSize(line_size_x, line_size_y);
    ui ->line_green ->setFixedSize(line_size_x, line_size_y);
    ui ->line_blue ->setFixedSize(line_size_x, line_size_y);
    ui ->pushButton_add ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_addf ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_lista ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_tabla ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_mostrar ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_salir ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_buscar ->setFixedSize(0, 0);
    ui ->pushButton_salir_tabla ->setFixedSize(0, 0);
    ui ->line_buscar ->setFixedSize(0, 0);
    ui ->line_buscar ->setText("");
}

void MainWindow::on_pushButton_mostrar_clicked()
{
    ui ->label_id ->setText("");
    ui ->label_voltaje ->setText("");
    ui ->label_x ->setText("");
    ui ->label_y ->setText("");
    ui ->label_r ->setText("");
    ui ->label_g ->setText("");
    ui ->label_b ->setText("");
    ui ->line_id ->setFixedSize(0, 0);
    ui ->line_voltaje ->setFixedSize(0, 0);
    ui ->line_x ->setFixedSize(0, 0);
    ui ->line_y ->setFixedSize(0, 0);
    ui ->line_red ->setFixedSize(0, 0);
    ui ->line_green ->setFixedSize(0, 0);
    ui ->line_blue ->setFixedSize(0, 0);
    ui ->pushButton_add ->setFixedSize(0, 0);
    ui ->pushButton_addf ->setFixedSize(0, 0);
    ui ->pushButton_lista ->setFixedSize(0, 0);
    ui ->pushButton_tabla ->setFixedSize(0, 0);
    ui ->pushButton_mostrar ->setFixedSize(0, 0);
    ui ->pushButton_salir ->setFixedSize(0, 0);
    ui ->graphicsViews_ellipses ->setFixedSize(621, 221);
    ui ->pushButton_salir_mostrar ->setFixedSize(button_size_x, button_size_y);
    if(lista.cant_neuronas()){
        QGraphicsScene *scene;
        scene =new QGraphicsScene();
        QGraphicsEllipseItem *ellipse;
        QPen pen;
        int voltaje;
        ui ->graphicsViews_ellipses ->setScene(scene);
        for(size_t i =0; i <lista.cant_neuronas(); i ++){
            QColor color(lista.getnred(i), lista.getngreen(i), lista.getnblue(i));
            QBrush brush(color);
            voltaje =lista.getnvoltaje(i);ellipse =scene ->addEllipse(lista.getnx(i), lista.getny(i), voltaje, voltaje, pen, brush);
        }
    }
}


void MainWindow::on_pushButton_salir_mostrar_clicked()
{
    ui ->label_id ->setText("Id:");
    ui ->label_voltaje ->setText("Voltaje:");
    ui ->label_x ->setText("Posicion X:");
    ui ->label_y ->setText("Posicion Y:");
    ui ->label_r ->setText("Red:");
    ui ->label_g ->setText("Green:");
    ui ->label_b ->setText("Blue:");
    ui ->line_id ->setFixedSize(line_size_x, line_size_y);
    ui ->line_voltaje ->setFixedSize(line_size_x, line_size_y);
    ui ->line_x ->setFixedSize(line_size_x, line_size_y);
    ui ->line_y ->setFixedSize(line_size_x, line_size_y);
    ui ->line_red ->setFixedSize(line_size_x, line_size_y);
    ui ->line_green ->setFixedSize(line_size_x, line_size_y);
    ui ->line_blue ->setFixedSize(line_size_x, line_size_y);
    ui ->pushButton_add ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_addf ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_lista ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_tabla ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_mostrar ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_salir ->setFixedSize(button_size_x, button_size_y);
    ui ->graphicsViews_ellipses ->setFixedSize(0, 0);
    ui ->pushButton_salir_mostrar ->setFixedSize(0, 0);
    ui ->graphicsViews_ellipses ->resetCachedContent();
}

