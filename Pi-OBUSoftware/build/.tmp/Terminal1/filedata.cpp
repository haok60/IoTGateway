#include "filedata.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

FileData::FileData(QString f)
{
    fname = f;
}

void FileData::writeAppend(QString s)
{

    QFile file(fname);
    if(file.open(QIODevice::Append))
    {
        QTextStream out(&file);
        out << s << endl;
        file.close();
    }
}

QString FileData::readLine(int lineNo)
{
    QFile file(fname);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        int count = 0;
        QString line;
        while(!in.atEnd()){
            line = in.readLine();
            count++;
            if(count == lineNo){
                file.close();
                return line;
            }
        }
        file.close();
    }
    return "";
}

int FileData::getLine(int mac)
{
    QFile file(fname);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        int count=0;
        while(!in.atEnd()){
            count++;
            QString line = in.readLine();
            QStringList list = line.split(",");
            if(list.value(0).toInt() == mac){
                file.close();
                return count;
            }
        }
        file.close();
    }
    return -1;
}

void FileData::deleteLine(int lineNo)
{
    QFile file(fname);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream in(&file);
        int count = 0;
        QString newfile;
        QString line;
        while(!in.atEnd()){
            line = in.readLine();
            count++;
            if(count != lineNo){
                newfile += line;
                newfile += "\n";
            }
        }
        file.seek(0);
        QTextStream out(&file);
        out << newfile;
        file.close();
    }
}

void FileData::deleteByMac(int mac)
{
    int lineNo = getLine(mac);
    QFile file(fname);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream in(&file);
        int count = 0;
        QString newfile;
        QString line;
        while(!in.atEnd()){
            line = in.readLine();
            count++;
            if(count != lineNo){
                newfile += line;
                newfile += "\n";
            }
        }
        file.seek(0);
        QTextStream out(&file);
        out << newfile;
        file.close();
    }
}

QString FileData::searchByMacString(int m)
{
    QFile file(fname);
    QString mac = QString::number(m);
    if(mac.toInt()<10)mac="0"+mac;
    if(file.open(QIODevice::ReadOnly))
    {

        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList list = line.split(",");
            if(!list.value(0).compare(mac)){
                file.close();
                return line;
            }
        }
        file.close();
    }
    return "";
}

QString FileData::searchByMac(int m)
{
    QFile file(fname);
    QString mac = QString::number(m);
    if(mac.toInt()<10)mac="0"+mac;
    if(file.open(QIODevice::ReadOnly))
    {

        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList list = line.split(",");
            if(!list.value(0).compare(mac)){
                file.close();
                return line;
            }
        }
        file.close();
    }
    return "";
}

void FileData::EditLine(int lineNo, QString content)
{
    QFile file(fname);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream in(&file);
        int count = 0;
        QString newfile;
        QString line;
        while(!in.atEnd()){
            line = in.readLine();
            count++;
            if(count == lineNo){
                newfile += content;
                newfile += "\n";
            } else {
                newfile += line;
                newfile += "\n";
            }
        }
        file.seek(0);
        QTextStream out(&file);
        out << newfile;
        file.close();
    }
}

void FileData::EditByMac(int mac, QString content)
{
    int lineNo = getLine(mac);
    QFile file(fname);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream in(&file);
        int count = 0;
        QString newfile;
        QString line;
        while(!in.atEnd()){
            line = in.readLine();
            count++;
            if(count == lineNo){
                newfile += content;
                newfile += "\n";
            } else {
                newfile += line;
                newfile += "\n";
            }
        }
        file.seek(0);
        QTextStream out(&file);
        out << newfile;
        file.close();
    }
}

int FileData::length()
{
    QFile file(fname);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        int count = 0;
        while(!in.atEnd())
        {
            if(!in.readLine().isEmpty())
            count++;
        }
        file.close();
        return count;
    }
    return -1;
}
