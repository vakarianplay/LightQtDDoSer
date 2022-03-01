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
    void onConnect();
    void onReading();
    void sendData();
    void onDisconnect();
    void initWindow();
    void clearText();
    QString GetRandomString();

    void on_pushButton_attack_clicked();
    void on_pushButton_stop_clicked();
    void on_radioButton_fromfile_clicked();
    void on_radioButton_manual_clicked();
    void on_lineEdit_ip_textEdited();

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
    UploadFile *upload = nullptr;
    QTimer *delay;
    QTimer *delay_clear;
    QString url;

    int port;
    int mode;

    void start_timer();
    void stop_timer();
};
#endif // MAINWINDOW_H
