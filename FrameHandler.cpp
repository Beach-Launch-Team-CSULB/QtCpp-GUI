#include "FrameHandler.hpp"
#include "SensorObjectDefinitions.hpp"
#include "ValveObjectDefinitions.hpp"


FrameHandler::FrameHandler(QObject *parent)
    : QObject{parent}
{
    foreach(auto& sensorContructingParameter, sensorConstructingParameters) //sensor key List
    {                                                                       //{"High_Press 1"} {"High_Press 2"} {"Fuel_Tank 1"} {"Fuel_Tank 2"}
        _sensors.insert(sensorContructingParameter.at(0).toString(),        //{"Lox_Tank 1"} {"Lox_Tank 2"} {"Fuel_Dome_Reg"} {"Lox_Dome_Reg"}
                       new Sensor{this, sensorContructingParameter});       //{"Fuel_Prop_Inlet"} {"Lox_Prop_Inlet"} {"Fuel Injector"}
    }                                                                       //{"LC1"} {"LC2"} {"LC3"} {"Chamber_1"} {"Chamber_2"} {"MV_Pneumatic}

    foreach(auto& valveConstructingParameter, valveConstructingParameters)  // valve key list
    {                                                                       //{"HV"} {"HP"} {"LDR"} {"FDR"} {"LDV"}
        _valves.insert(valveConstructingParameter.at(0).toString(),         // {"FDV"} {"LV"} {"FV"}
                       new Valve{this, valveConstructingParameter});        //{"LMV"} {"FMV"} {"IGN1"} {"IGN2"}
    }

    //Connect signals and slots
    foreach(Sensor* sensor, _sensors) // iterating through QMap, value is assigned instead of the key
    {
       QObject::connect(this, &FrameHandler::sensorReceived, sensor, &Sensor::onSensorReceived);
    }
    foreach(Valve* valve, _valves) // iterating through QMap, value is assigned instead of the key
    {
       QObject::connect(this, &FrameHandler::valveReceived, valve, &Valve::onValveReceived);
    }
}

FrameHandler::~FrameHandler()
{
    this->_loop = false;
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

    // check if these will crash the program after _can0 is actually created later on
    _can0->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant(500000));
    _can0->setConfigurationParameter(QCanBusDevice::CanFdKey, QVariant(true)); // can FD is only truly enabled if both hardware and driver support CAN FD

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
            qDebug() << "The device is already connected";
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
    if(!_can0 || !_can0->hasBusStatus())
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

bool FrameHandler::isOperational()
{
    if(!_can0 || !_can0->hasBusStatus())
        return false;

    switch(_can0->busStatus())
    {
    case QCanBusDevice::CanBusStatus::Unknown: // Black
        return false;
    case QCanBusDevice::CanBusStatus::Good: // Green
    case QCanBusDevice::CanBusStatus::Warning: // Yellow
        return true;
    case QCanBusDevice::CanBusStatus::Error: // Red
    case QCanBusDevice::CanBusStatus::BusOff: // Blue
        return false;
    }
    return false;
}

void FrameHandler::onErrorOccurred(QCanBusDevice::CanBusError error)
{

}

// TODO FOR TOMORROW: WORK ON VALVE STUFF, ID 546 & ID 547 & (maybe) ID 552
void FrameHandler::onFramesReceived() // In the future, might need to write frames data to a file
{
    //if(!_can0) return;

    while (_can0->framesAvailable()) // while
    {
        QCanBusFrame dataFrame = _can0->readFrame();
        // dissect data from the frames then update the GUI

        const QString frameIDBi {QString::number(dataFrame.frameId(), 2)}; // grab the ID in the form of binary
        //const QString frameIDInt {QString::number(dataFrame.frameId(), 10)}; // grab the ID in the form of int
        //const QString frameIDHex {QString::number(dataFrame.frameId(), 16)}; // grab the ID in the form of hexadecimal

        // perform surgery on frameID
        QString ID_A_bin;
        QString ID_B_bin;
        quint16 ID_A;
        quint32 ID_B;
        //get ID_A and/or ID_B
        if (dataFrame.hasExtendedFrameFormat())
        {
            ID_A_bin = frameIDBi.mid(18);
            ID_B_bin = frameIDBi.mid(0,18);
            ID_A = frameIDBi.mid(18).toInt(nullptr, 2);
            ID_B = frameIDBi.mid(0,18).toInt(nullptr, 2);
        }
        else
        {
            ID_A_bin = frameIDBi;
            ID_A = frameIDBi.toInt(nullptr,2);
        }

        const QByteArray payload {dataFrame.payload().toHex()}; // returns nibble by nibble. Two nibbles make a byte
        QList<QByteArray> data;

        QString payloadErrorString;
        // perform surgery on data
        if (dataFrame.frameType() == QCanBusFrame::InvalidFrame)
        {
            payloadErrorString = _can0->interpretErrorFrame(dataFrame);
            return;
        }
        // constructing the bytes this way so that the program wouldn't crash
        // so scuffed, might need to rework this
        //if (!dataFrame.hasFlexibleDataRateFormat())
        //{
            for (int i {0}; i < payload.length(); i = i + 2)
            {
                 QByteArray byte;
                 byte.append(payload.at(i)); byte.append(payload.at(i+1)); // put 2 nibbles together to make a byte
                 data.append(byte);
            }
        //}
        //else
        //{

        //}

        // sensors
        if (ID_A >= 51 && ID_A <= 426) // find out the actual ID's of the devices and to an || operator
        {
            emit sensorReceived(ID_A, ID_B, data);
            return;
        }

        //Valve renegade Engine
        if (ID_A == 546)
        {
            // perform surgery on frameID
        }

        // Valve renegade prop
        if (ID_A == 547)
        {
            // perform surgery on frameID
        }

        //

        // Valves
        if (ID_A == 552)
        {

        }



        //"NODE STATE REPORT" "Bytes 1,2,3,4,5,6,7 are not used"
        //"Engine Node 2"
        //"Prop Node 3"
        if (ID_A > 510 && ID_A < 530)
        {
            if (ID_A == 514)
            {
                //_nodeStatusRenegadeEngine = cursed.at(data.at(0).toInt(nullptr,16)); // byte zero should go from 0 to 12
                setNodeStatusRenegadeEngine(cursed.at(data.at(0).toInt(nullptr,16)));
                return;
            }
            if (ID_A == 515)
            {
                //_nodeStatusRenegadeProp = cursed.at(data.at(0).toInt(nullptr,16));
                setNodeStatusRenegadeProp(cursed.at(data.at(0).toInt(nullptr,16)));
                return;
            }
            if (ID_A == 520)
            {
                setNodeStatusBang(cursed.at(data.at(0).toInt(nullptr,16)));
                return;
            }
            //emit valveReceived(ID_A, ID_B , data);
        }

        if (ID_A == 1100)
        {
            setAutosequenceTime(dataFrame.payload().toFloat(nullptr)/1000000);
            return;
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
void FrameHandler::sendFrame(quint32 ID, const char* dataHexString) //QCanBusFrame::FrameId or quint32
{
    if(!isOperational() || !(_can0->state() == QCanBusDevice::ConnectedState)) return;
    //dataHexString is passed from QML
    QByteArray data {QByteArrayLiteral(dataHexString)};
    //QByteArray data {QByteArray::fromHex(dataHexString.toLatin1())}; //ChatGPT gave me this line // need to test this
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

QMap<QString, Sensor *> FrameHandler::sensors() const
{
    return _sensors;
}

QMap<QString, Valve *> FrameHandler::valves() const
{
    return _valves;
}

float FrameHandler::autosequenceTime() const
{
    return _autosequenceTime;
}

void FrameHandler::setAutosequenceTime(float newAutosequenceTime)
{
    _autosequenceTime = newAutosequenceTime;
    emit autosequenceTimeChanged();
}

FrameHandler::VehicleState FrameHandler::nodeStatusRenegadeEngine() const
{
    return _nodeStatusRenegadeEngine;
}

void FrameHandler::setNodeStatusRenegadeEngine(FrameHandler::VehicleState newNodeStatusRenegadeEngine)
{
    _nodeStatusRenegadeEngine = newNodeStatusRenegadeEngine;
    emit nodeStatusRenegadeEngineChanged();
}

FrameHandler::VehicleState FrameHandler::nodeStatusRenegadeProp() const
{
    return _nodeStatusRenegadeProp;
}

void FrameHandler::setNodeStatusRenegadeProp(FrameHandler::VehicleState newNodeStatusRenegadeProp)
{
    _nodeStatusRenegadeProp = newNodeStatusRenegadeProp;
    emit nodeStatusRenegadePropChanged();
}

FrameHandler::VehicleState FrameHandler::nodeStatusBang() const
{
    return _nodeStatusBang;
}

void FrameHandler::setNodeStatusBang(FrameHandler::VehicleState newNodeStatusBang)
{
    _nodeStatusBang = newNodeStatusBang;
    emit nodeStatusBangChanged();
}

// run
void FrameHandler::run()
{
    qInfo() << "Hello?";
    this->connectCan();

    while (_loop)
    {
        // CAN stuff
        if (this->isOperational() && _can0->state() == QCanBusDevice::ConnectedState)
        {
            this->onFramesReceived(); // might need to disconnect the signal connected to this slot since I don't know quite how that works
        }

        // GNC stuff
        if (true)
        {

        }
    }
}

