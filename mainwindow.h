#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "uploadfile.h"
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QTimer>

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
    void on_pushButton_fileupload_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
    UploadFile *upload = nullptr;
};
#endif // MAINWINDOW_H
