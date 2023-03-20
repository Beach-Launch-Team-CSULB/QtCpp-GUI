#include "FrameHandler.hpp"

FrameHandler::FrameHandler(QObject *parent)
    : QObject{parent}
{

}

FrameHandler::~FrameHandler()
{
    this->disconnectCan();
}

bool FrameHandler::connectCan() // need work
{
    QString errorString;
    _can0 = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);

    if(!_can0)
    {
        qDebug() << errorString;
        return false;
    }

    switch(_can0->state())
    {
        case QCanBusDevice::UnconnectedState:
            if(!_can0->connectDevice())
            {
                qDebug() << "Device could not be connected";
                return false;
            }
            else
            {
                // connect signals and slots to the Can Bus here
                QObject::connect(_can0, &QCanBusDevice::framesReceived, this, &FrameHandler::onFramesReceived,Qt::UniqueConnection);
                QObject::connect(_can0, &QCanBusDevice::framesWritten, this, &FrameHandler::onFramesWritten,Qt::UniqueConnection);
                QObject::connect(_can0, &QCanBusDevice::errorOccurred, this, &FrameHandler::onErrorOccurred,Qt::UniqueConnection);
                QObject::connect(_can0, &QCanBusDevice::stateChanged, this, &FrameHandler::onStateChanged,Qt::UniqueConnection);
                qDebug() << "Can connected successfully";
                return true;
            }
            break;
        case QCanBusDevice::ConnectingState:
            qDebug() << "The device is being connected...";
            return false;
            break;
        case QCanBusDevice::ConnectedState:
            qDebug() << "The device is already";
            return false;
            break;
        case QCanBusDevice::ClosingState:
            qDebug() << "The device is closing...";
            return false;
            break;
    }
    return false;
}

bool FrameHandler::disconnectCan() // might need more work
{
    if(!_can0)
    {
        qDebug() << "No can device to be disconnected";
        return false;
    }
    switch (_can0->state())
    {
        case QCanBusDevice::UnconnectedState:
            return false;
        case QCanBusDevice::ConnectingState:
            return false;
        case QCanBusDevice::ConnectedState:
            QObject::disconnect(_can0, &QCanBusDevice::framesReceived, this, &FrameHandler::onFramesReceived);
            QObject::disconnect(_can0, &QCanBusDevice::framesWritten, this, &FrameHandler::onFramesWritten);
            QObject::disconnect(_can0, &QCanBusDevice::errorOccurred, this, &FrameHandler::onErrorOccurred);
            QObject::disconnect(_can0, &QCanBusDevice::stateChanged, this, &FrameHandler::onStateChanged);
            _can0->disconnectDevice();
            delete _can0;
            _can0 = nullptr;
            return true;
        case QCanBusDevice::ClosingState:
            return false;
    }
    return false;
}

QString FrameHandler::getBusStatus() // Create a QML item displaying color for each state
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
    return "???";
}


void FrameHandler::onErrorOccurred(QCanBusDevice::CanBusError error)
{

}

// TODO FOR TOMORROW: THIS FUNCTION
void FrameHandler::onFramesReceived() // In the future, might need to write frames data to a file
{
    if(!_can0) return;

    while (_can0->framesAvailable()) // while
    {
        this->_dataFrame = _can0->readFrame(); // Should
        // dissect data from the frames then update the GUI

        const QString frameIDBi {QString::number(_dataFrame.frameId(), 2)}; // grab the ID in the form of binary
        const QString frameIDInt {QString::number(_dataFrame.frameId(), 10)}; // grab the ID in the form of int
        const QString frameIDHex {QString::number(_dataFrame.frameId(), 16)}; // grab the ID in the form of hexadecimal

        //QString ID_A_bin;
        //QString ID_B_bin;
        quint32 ID_A;
        quint32 ID_B;
        //get ID_A and ID_B
        if (_dataFrame.hasExtendedFrameFormat())
        {
            //const QString ID_A_bin = frameIDBi.mid(18);
            //const QString ID_B_bin = frameIDBi.mid(0,18);
            ID_A = frameIDBi.mid(18).toInt(nullptr, 2);
            ID_B = frameIDBi.mid(0,18).toInt(nullptr, 2);
        }
        else
        {
            ID_A = frameIDBi.toInt(nullptr,2);
        }

        // perform surgery on frameID
        const QByteArray payload {_dataFrame.payload().toHex()};
        QString payloadString;
        QList<QByteArray> data;
        // perform surgery on data
        if (_dataFrame.frameType() == QCanBusFrame::InvalidFrame)
        {
            payloadString = _can0->interpretErrorFrame(_dataFrame);
            return;
        }
        // constructing the bytes this way so that the program wouldn't crash
        // so scuffed, might need to rework this
        for (int i {0}; i < payload.length(); i = i + 2)
        {
             QByteArray byte;
             byte.append(payload.at(i)); byte.append(payload.at(i+1));
             data.append(byte);
             qInfo() << i;
        }
        // might need to check for ID first before doing this
        // Using for loop is not recommended
        //QByteArray byte1;
        //byte1.append(payload.at(0)); byte1.append(payload.at(1));
        //QByteArray byte2;
        //byte2.append(payload.at(2)); byte2.append(payload.at(3));
        //QByteArray byte3;
        //byte3.append(payload.at(4)); byte3.append(payload.at(5));
        //QByteArray byte4;
        //byte4.append(payload.at(6)); byte4.append(payload.at(7));
        //QByteArray byte5;
        //byte5.append(payload.at(8)); byte5.append(payload.at(9));
        //QByteArray byte6;
        //byte6.append(payload.at(10)); byte6.append(payload.at(11));
        //QByteArray byte7;
        //byte7.append(payload.at(12)); byte7.append(payload.at(13));
        //QByteArray byte8;
        //byte8.append(payload.at(14)); byte8.append(payload.at(15));
        //QList<QByteArray> data {byte1,byte2,byte3,byte4,byte5,byte6,byte7,byte8};


        // sensors
        if (ID_A >= 51 && ID_A <= 426) // find out the actual ID's of the devices and to an || operator
        {
            emit sensorReceived(ID_A, ID_B, data);
        }

        //Valve renegade Engine
        if (ID_A == 546)
        {

        }

        // Valve renegade prop
        if (ID_A == 547)
        {

        }

        //

        // Valves
        if (ID_A == 552)
        {

        }



        //"NODE STATES"
        //"Engine Node 2"
        //"Prop Node 3"
        if (ID_A > 510 && ID_A < 530)
        {
            if (ID_A == 514)
            {

            }
            if (ID_A == 515)
            {

            }
            if (ID_A == 520)
            {

            }
            emit valveReceived(ID_A, ID_B , data);
        }



        // states
        //if (frameID >= 2001 && frameID <= 3000)
        //{
        //    emit stateReceived(frameID, data);
        //}


    }

}

void FrameHandler::onFramesWritten(quint64 framesCount)
{

}

void FrameHandler::onStateChanged(QCanBusDevice::CanBusDeviceState state)
{

}

// Expose the object to QML so that QML can use this function
void FrameHandler::sendFrame(quint32 ID, QString dataHexString) //QCanBusFrame::FrameId or quint32
{
    if(!_can0) return;
    //dataHexString is passed from QML
    QByteArray data {QByteArray::fromHex(dataHexString.toLatin1())}; //ChatGPT gave me this line // need to test this
    QCanBusFrame remoteFrame {ID, data};
    remoteFrame.setFrameType(QCanBusFrame::RemoteRequestFrame);

    remoteFrame.setBitrateSwitch(false);
    remoteFrame.setExtendedFrameFormat(false);
    remoteFrame.setFlexibleDataRateFormat(false);


    // for Virtual CAN Testing
    //remoteFrame.setErrorStateIndicator(false);
    //remoteFrame.setLocalEcho(false);

    _can0->writeFrame(remoteFrame);
}

// Getters and Setters section

CommandAuthority FrameHandler::getCommandMode() const
{
    return _commandMode;
}

void FrameHandler::setCommandMode(CommandAuthority newCommandMode)
{
    _commandMode = newCommandMode;
}

GuiVehicleState FrameHandler::getVehicleState() const
{
    return _vehicleState;
}

void FrameHandler::setVehicleState(GuiVehicleState newVehicleState)
{
    _vehicleState = newVehicleState;
}

// run
void FrameHandler::run()
{
    qInfo() << "Hello?";
}

