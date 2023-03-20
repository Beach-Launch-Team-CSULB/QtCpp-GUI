#ifndef GRAPH_I_HPP
#define GRAPH_I_HPP

#include <QObject>

// Actually use QML for this. QML grabs data from objects.
// Define functions like a filter EMA function in Javascript to filter incoming data
// then display that on graphs.
class Graph_I : public QObject
{
private:
    Q_OBJECT

public:
    explicit Graph_I(QObject *parent = nullptr);


signals:

};

#endif // GRAPH_I_HPP
