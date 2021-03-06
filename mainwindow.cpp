#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>

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
   //    QString port = ui->txtPort->text();
        // QString очень крутой класс, и позволяет нам склеивать строки на лету
        // т.е.  "Выбранный порт: " + port -- означает подклеить содержимое txtPort к фразе "Выбранный порт"
   //    QMessageBox::information(this, "Сообщение RED-2", "Выбранный порт: " + port);

    // создали экземпляр для общения по последовательному порту
        QSerialPort serialPort;


        serialPort.setPortName(this->ui->txtPort->text());          // указали имя к какому порту будем подключаться
        serialPort.setBaudRate(QSerialPort::Baud9600);

        if (!serialPort.open(QIODevice::ReadWrite)) {
            // если подключится не получится, то покажем сообщение с ошибкой
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }

        serialPort.write("r"); // очень важно, что именно двойные кавычки
        serialPort.waitForBytesWritten(); // ждем пока дойдет

        // и не знаю с чем тут связано, но, чтобы сообщение дошло
        // надо обязательно прочитать не пришло ли нам чего в ответ
        //
        // функция waitForReadyRead(10) проверят не появилось
        // в ближайшие 10 миллисекунд чего-нибудь в ответ

        QByteArray data;  // специальный тип QT для хранения последовательности байтов

        while (serialPort.waitForReadyRead(10)) {
            // и если появилось мы просто это читаем в пустоту
            //  serialPort.readAll();
            data.append(serialPort.readAll());

            // сам while необходим для того что ответ приходит порциями
            // и мы хотим считать все что отправилось
        }
        ui->txtOutput->append(data);
        serialPort.close();

}

void MainWindow::on_pushButton_2_clicked()
{
    //  QMessageBox::information(this, "Сообщение BLUE", "Ура! Нажали кнопку 2!");
    QSerialPort serialPort;

        serialPort.setPortName(this->ui->txtPort->text());
        serialPort.setBaudRate(QSerialPort::Baud9600);

        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }

        serialPort.write("b");
        serialPort.waitForBytesWritten();

        QByteArray data;
        while (serialPort.waitForReadyRead(100)) {
            data.append(serialPort.readAll());
        }

        ui->txtOutput->append(data);
        serialPort.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSerialPort serialPort;

        serialPort.setPortName(this->ui->txtPort->text());
        serialPort.setBaudRate(QSerialPort::Baud9600);

        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }

        serialPort.write("p"); // меняем тут на p
        serialPort.waitForBytesWritten();

        QByteArray data;
        while (serialPort.waitForReadyRead(10)) {
            data.append(serialPort.readAll());
        }

        //ui->txtOutput->append(data);
        ui->txtLight->setText(data); // тут вставляем значение в txtLight
        serialPort.close();
}

void MainWindow::on_pushButton_4_clicked()
{
    //  QMessageBox::information(this, "Сообщение BLUE", "Ура! Нажали кнопку 2!");
    QSerialPort serialPort;

        serialPort.setPortName(this->ui->txtPort->text());
        serialPort.setBaudRate(QSerialPort::Baud9600);

        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }

        serialPort.write("e");
        serialPort.waitForBytesWritten();

        QByteArray data;
        while (serialPort.waitForReadyRead(100)) {
            data.append(serialPort.readAll());
        }

        ui->txtOutput->append(data);
        //ui->txtLight->setText(data); // тут вставляем значение в txtLight
        serialPort.close();
}
