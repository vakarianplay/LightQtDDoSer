#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), socket(this)
{
    ui->setupUi(this);
    upload = new UploadFile;
    connect(&socket, SIGNAL(readyRead()), this, SLOT(onReading()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if (upload) {
        delete upload;
    }
}

void MainWindow::on_pushButton_fileupload_clicked()
{
    upload->callFromMain();
    ui->comboBox_urls->addItems(upload->combolist);
}
