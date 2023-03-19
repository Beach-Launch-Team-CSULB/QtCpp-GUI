#include "FrameHandler.hpp"


FrameHandler::FrameHandler(QObject *parent)
    : QObject{parent}
{

}


bool FrameHandler::connectCan() //
{
    QString errorString;
    _can0 = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
    // connect signals and slots to the Can Bus here

    if(!_can0)
    {
        qDebug() << errorString;
        return false;
    }
    else
    {
        QObject::connect(_can0, &QCanBusDevice::framesReceived, this, &FrameHandler::onFramesReceived);
        QObject::connect(_can0, &QCanBusDevice::framesWritten, this, &FrameHandler::onFramesWritten);
        QObject::connect(_can0, &QCanBusDevice::errorOccurred, this, &FrameHandler::onErrorOccurred);
        QObject::connect(_can0, &QCanBusDevice::stateChanged, this, &FrameHandler::onStateChanged);

        qDebug() << "Can connected successfully";
        _can0->connectDevice();
        return true;
    }
}

bool FrameHandler::disconnectCan()
{
    if(!_can0)
        return false;
    else
        _can0->disconnectDevice();
    return true;
}

QString FrameHandler::busStatus() // Create a QML item displaying color for each state
{
    if(!_can0 || _can0->hasBusStatus())
        return "No CAN bus status available.";

    switch(_can0->busStatus())
    {
    case QCanBusDevice::CanBusStatus::Unknown: // Black
        return "Can Bus Status: Unknown (Not supported by CAN pluggin)";
    case QCanBusDevice::CanBusStatus::Good: // Green
        return "Can Bus Status: Fully operational";
    case QCanBusDevice::CanBusStatus::Warning: // Yellow
        return "Can Bus Status: Warning";
    case QCanBusDevice::CanBusStatus::Error: // Red
        return "Can Bus Status: Error";
    case QCanBusDevice::CanBusStatus::BusOff: // Blue
        return "Can Bus Status: Bus disconnected";
    }
}


void FrameHandler::onErrorOccurred()
{

}

void FrameHandler::onFramesReceived()
{
    if(!_can0) return;

    if (_can0->framesAvailable()) // while or if
    {
        this->_dataFrameList = _can0->readAllFrames(); // Should
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

}

void FrameHandler::onFramesWritten()
{

}

void FrameHandler::onStateChanged(QCanBusDevice::CanBusDeviceState state)
{

}


void FrameHandler::sendFrame(const QCanBusFrame frame) const
{
    if(!_can0) return;

    _can0->writeFrame(frame);
}


QCanBusFrame FrameHandler::remoteFrameConstruct(QCanBusFrame::FrameId ID, const QByteArray& data) //QCanBusFrame::FrameId or quint32
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



CommandAuthority FrameHandler::getCommandMode() const
{
    return commandMode;
}

void FrameHandler::setCommandMode(CommandAuthority newCommandMode)
{
    commandMode = newCommandMode;
}


void FrameHandler::run()
{

}

