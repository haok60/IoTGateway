#ifndef FILEDATA_H
#define FILEDATA_H

#include <QFile>

class FileData
{
public:
    FileData(QString);

private:
    QString fname;

public:
    void writeAppend(QString);
    QString readLine(int);
    int getLine(int);
    void deleteLine(int);
    void deleteByMac(int);
    QString searchByMac(int);
    QString searchByMacString(int);
    void EditLine(int, QString);
    void EditByMac(int, QString);
    int length();
};

#endif // FILEDATA_H
