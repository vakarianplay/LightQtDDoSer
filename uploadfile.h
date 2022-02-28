#ifndef UPLOADFILE_H
#define UPLOADFILE_H
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QObject>
#include <QWidget>

class UploadFile : public QObject
{
    Q_OBJECT
public:
    UploadFile(QObject *parent = 0);
    ~UploadFile();

    void callFromMain();
    QVector<QString> urls;
    QVector<int> ports;
    QStringList combolist;

private:
    void addVectors(QStringList split_string);
    void filedialog();
};

#endif // UPLOADFILE_H
