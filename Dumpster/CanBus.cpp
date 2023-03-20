#include "CanBus.hpp"

extern QList<const QCanBusFrame> listOfErrorFrames_globalVar;

CanBus::CanBus(QObject *parent)
    : QCanBusDevice{parent}
{
    // connect signals and slots between the same can0 object
    QObject::connect(this, &QCanBusDevice::errorOccurred, this, &CanBus::onErrorOccurred,Qt::UniqueConnection);
    QObject::connect(this, &QCanBusDevice::framesReceived, this, &CanBus::onFramesReceived, Qt::UniqueConnection);
    QObject::connect(this, &QCanBusDevice::stateChanged, this, &CanBus::onStateChanged, Qt::UniqueConnection);
}

void CanBus::onErrorOccurred()
{

}

void CanBus::onFramesReceived()
{
    if(this->framesAvailable())
    {
        this->_dataFrameList = this->readAllFrames();
        // dissect data from the frames then update the GUI
        foreach(QCanBusFrame dataFrame, _dataFrameList)
        {
            quint32 frameID {dataFrame.frameId()};
            // perform surgery on frameID



            QByteArray data {dataFrame.payload()};
            // perform surgery on data




            // sensors
            if (frameID >= 0 && frameID <= 1000) // find out the actual ID's of the devices and to an || operator
            {
                emit sensorReceived(frameID, data);
            }

            // valves
            if (frameID >= 1001 && frameID <= 2000)
            {
                emit valveReceived(frameID, data);
            }

            // states
            if (frameID >= 2001 && frameID <= 3000)
            {
                emit stateReceived(frameID, data);
            }

        }
    }
    else
    {

    }

}

void CanBus::onFramesWritten()
{

}

void CanBus::onStateChanged(QCanBusDevice::CanBusDeviceState state)
{

}

QCanBusFrame remoteFrameConstruct(QCanBusFrame::FrameId ID, const QByteArray& data) //QCanBusFrame::FrameId or quint32
{
    QCanBusFrame remoteFrame {ID, data};
    remoteFrame.setFrameType(QCanBusFrame::RemoteRequestFrame);

    remoteFrame.setBitrateSwitch(false);
    remoteFrame.setExtendedFrameFormat(false);
    remoteFrame.setFlexibleDataRateFormat(false);


    // for Virtual CAN Testing
    //remoteFrame.setErrorStateIndicator(false);
    //remoteFrame.setLocalEcho(false);

    return remoteFrame;
}


bool CanBus::state() const
{
    return _state;
}

void CanBus::setState(bool newState)
{
    _state = newState;
}



void CanBus::run()
{
    QThread *thread = QThread::currentThread();

    qInfo() << "Starting" << thread;
    for (int i = 0; i <10 ; i++)
    {
        qInfo() << i << "on" << thread;
    }
    qInfo() << "Finished" << thread;
}
