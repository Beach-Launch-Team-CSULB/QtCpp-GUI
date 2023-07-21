#ifndef DIRHELPER_HPP
#define DIRHELPER_HPP


#include <QObject>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

class DirHelper : public QObject
{

private:
    Q_OBJECT

    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(QStringList files READ files CONSTANT)

    QDir dir;
    QString path();
    void setPath(QString value);
    QStringList files();
public:
    explicit DirHelper(QObject *parent = nullptr);

signals:




};

#endif // DIRHELPER_HPP
