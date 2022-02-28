#include "uploadfile.h"

UploadFile::UploadFile(QObject *parent) : QObject(parent)
{
    qDebug() << "vitki class";
}

UploadFile::~UploadFile()
{
    qDebug() << "delete class";
}

void UploadFile::filedialog()
{
    QString filename = QFileDialog::getOpenFileName(0, "File targets", "",
                                                    "*.txt"); //open file
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QString read_string = file.readLine(); // read one line from file
        read_string.remove("\n");
        combolist.append(read_string);
        QStringList split_string = read_string.split(":");
        addVectors(split_string);
        split_string.clear();
        read_string.clear();
    }
}

void UploadFile::addVectors(QStringList split_string)
{
    urls.append(split_string.at(0));
    ports.append(split_string.at(1).toInt());
}

void UploadFile::callFromMain()
{
    filedialog();
    qDebug() << urls << ports;
}
