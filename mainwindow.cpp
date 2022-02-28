#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), socket(this)
{
    ui->setupUi(this);
    delay = new QTimer(this);
    upload = new UploadFile;
    initWindow();
    connect(&socket, SIGNAL(connected()), this, SLOT(onReading()));
    connect(delay, SIGNAL(timeout()), this, SLOT(sendData()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if (upload) {
        delete upload;
    }
}

void MainWindow::start_timer()
{
    // start timer
    delay->start(1);
}

void MainWindow::stop_timer()
{
    // stop timer
    delay->stop();
}

void MainWindow::on_pushButton_fileupload_clicked()
{
    upload->callFromMain();
    ui->comboBox_urls->addItems(upload->combolist);
}

void MainWindow::onConnect()
{
    int comboindex = 0;

    switch (mode) {
    case 1:
        comboindex = ui->comboBox_urls->currentIndex();
        url = upload->urls.at(comboindex);
        port = upload->ports.at(comboindex);
        break;

    case 2:
        url = ui->lineEdit_ip->text();
        port = ui->spinBox_port->text().toInt();
        break;
    }
    qDebug() << url << port;
    if (url.isEmpty()) {
        QMessageBox::warning(this, "Error", "Not enter target.");
        return;
    }
    socket.connectToHost(url, port);
    if (socket.waitForConnected(1000)) //check connection
    {
        QMessageBox::information(this, "OK", "Connection established.");
        ui->pushButton_attack->setEnabled(false);
        ui->pushButton_stop->setEnabled(true);

    } else {
        QMessageBox::warning(this, "Error", "No response from host.");
    }
}

void MainWindow::onDisconnect()
{
    socket.disconnectFromHost();
    stop_timer();
    QMessageBox::information(this, "Disconnect", "Disconnected from host.");
    ui->pushButton_attack->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
}

void MainWindow::onReading()
{
    qDebug() << "read";
    start_timer();
}

void MainWindow::sendData()
{
    //    qDebug() << GetRandomString();
    QByteArray WriteArray;
    WriteArray.append(GetRandomString());
    socket.write(WriteArray);
    ui->textBrowser->append(WriteArray);
    WriteArray.clear();
}

QString MainWindow::GetRandomString()
{
    const QString possibleCharacters(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomStringLength = 64; // assuming you want random strings of 12 characters

    QString randomString;
    for (int i = 0; i < randomStringLength; ++i) {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

void MainWindow::on_pushButton_attack_clicked()
{
    onConnect();
}

void MainWindow::on_pushButton_stop_clicked()
{
    onDisconnect();
}

void MainWindow::on_radioButton_fromfile_clicked()
{
    mode = 1;
    ui->pushButton_fileupload->setEnabled(true);
    ui->lineEdit_ip->setEnabled(false);
    ui->spinBox_port->setEnabled(false);
    ui->comboBox_urls->setEnabled(true);
    ui->pushButton_attack->setEnabled(true);
    ui->pushButton_attack->setEnabled(false);
}

void MainWindow::on_radioButton_manual_clicked()
{
    mode = 2;
    ui->lineEdit_ip->setEnabled(true);
    ui->spinBox_port->setEnabled(true);
    ui->comboBox_urls->setEnabled(false);
    ui->pushButton_fileupload->setEnabled(false);
    ui->pushButton_attack->setEnabled(true);
    ui->pushButton_attack->setEnabled(false);
}

void MainWindow::initWindow()
{
    ui->lineEdit_ip->setEnabled(false);
    ui->spinBox_port->setEnabled(false);
    ui->pushButton_attack->setEnabled(false);
    ui->pushButton_fileupload->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
    ui->comboBox_urls->setEnabled(false);
}

void MainWindow::on_lineEdit_ip_textEdited()
{
    ui->pushButton_attack->setEnabled(true);
}
