
#ifndef AUTOSEQUENCE_HPP
#define AUTOSEQUENCE_HPP


#include <QObject>


class Autosequence : public QObject
{
    Q_OBJECT
public:
    explicit Autosequence(QObject *parent = nullptr);

signals:

};

#endif // AUTOSEQUENCE_HPP
