#include "DirHelper.hpp"


DirHelper::DirHelper(QObject *parent)
    : QObject{parent}
{

}


QString DirHelper::path()
{
    return dir.path();
}

void DirHelper::setPath(QString value)
{
    dir.setPath(value); // Set to a destination on the hard drive, or a network
}

QStringList DirHelper::files()
{
    QFileInfoList list = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Files); // All files in the dir directory
    QStringList filelist;

    foreach(QFileInfo info, list){
        filelist.append(info.filePath());
    }

    return filelist;
}
