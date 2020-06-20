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

        // указали имя к какому порту будем подключаться
        serialPort.setPortName(this->ui->txtPort->text());
        // указали скорость
        serialPort.setBaudRate(QSerialPort::Baud9600);

        // пробуем подключится
        if (!serialPort.open(QIODevice::ReadWrite)) {
            // если подключится не получится, то покажем сообщение с ошибкой
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }

        // отправляем строку с b нашей арудинкой
        serialPort.write("b"); // очень важно, что именно двойные кавычки
        serialPort.waitForBytesWritten(); // ждем пока дойдет

        // и не знаю с чем тут связано, но, чтобы сообщение дошло
        // надо обязательно прочитать не пришло ли нам чего в ответ
        //
        // функция waitForReadyRead(10) проверят не появилось
        // в ближайшие 10 миллисекунд чего-нибудь в ответ
        while (serialPort.waitForReadyRead(10)) {
            // и если появилось мы просто это читаем в пустоту
            serialPort.readAll();

            // сам while необходим для того что ответ приходит порциями
            // и мы хотим считать все что отправилось
        }

        // ну и закрываем порт
        serialPort.close();

}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Сообщение BLUE", "Ура! Нажали кнопку 2!");
}
