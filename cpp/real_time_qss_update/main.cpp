#include "mainwindow.h"

#include <QApplication>
#include <QFileSystemWatcher>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QFileInfoList>
#include <QByteArray>

void loadQss(const QString &directoryPath) {
    QDir directory(directoryPath);
    QStringList filter;
    filter << "*.qss";

    QFileInfoList fileInfoList = directory.entryInfoList(filter, QDir::Files);
    qDebug() << fileInfoList.size();
    QString styleString;
    for (const auto &fileName : fileInfoList) {
        QFile styleFile(fileName.absoluteFilePath());
        if (styleFile.open(QFile::ReadOnly)) {
            QByteArray data = styleFile.readAll();
            styleString += QLatin1String(data);
        } else {
            qDebug("qss打开失败");
        }
        styleFile.close();
    }
    qobject_cast<QApplication*>(QApplication::instance())->setStyleSheet(styleString);
}

void realTimeUpdate(QWidget *obj) {
#ifdef QT_DEBUG
    QString directoryPath = "C:/Users/win-qt/Documents/real_qss_change/resources/qss";
    QDir directory(directoryPath);
    QStringList filePaths;
    QStringList filter;
    filter << "*.qss";

    QFileInfoList fileInfoList = directory.entryInfoList(filter, QDir::Files);
    for (const QFileInfo &fileInfo : fileInfoList) {
        filePaths.append(fileInfo.filePath());
    }

    auto fileWatcher = new QFileSystemWatcher(obj);
    fileWatcher->addPaths(filePaths);
    QObject::connect(fileWatcher, &QFileSystemWatcher::fileChanged, obj, [directoryPath](const QString &path){
        qDebug() << "重载！";
        loadQss(directoryPath);
    });
#endif
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    loadQss(":/qss/");
    realTimeUpdate(&w);
    return a.exec();
}


