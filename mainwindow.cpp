#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // QMessageBox::information(this, "Сообщение RED", "Ура! Нажали кнопку 1!");

    // У QT свой тип для работы со строками QString
       // обращением к элементам на форме всегда идет через ui
       // очевидно что ui->txtPort -- это указатель на поле для ввода порта
       // ну а ui->txtPort->text() -- это вызов функции которая вернет текстовое содержимое поля
       QString port = ui->txtPort->text();
       // QString очень крутой класс, и позволяет нам склеивать строки на лету
       // т.е.  "Выбранный порт: " + port -- означает подклеить содержимое txtPort к фразе "Выбранный порт"
       QMessageBox::information(this, "Сообщение RED-2", "Выбранный порт: " + port);

}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Сообщение BLUE", "Ура! Нажали кнопку 2!");
}
