#include "FrameHandler.hpp"
#include "SensorObjectDefinitions.hpp"
#include "ValveObjectDefinitions.hpp"


FrameHandler::FrameHandler(QObject *parent)
    : QObject{parent}
{
    qDebug() << "Enter FrameHandler constructor"; // Note: because of threading, this might not be an accurate way of finding out where the program crashes
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

    QThread::currentThread()->setObjectName("Frame Handler thread");
    qInfo() << QThread::currentThread();
    qInfo() << QThread::currentThread();
    qInfo() << QThread::currentThread();
    qInfo() << QThread::currentThread();
}

FrameHandler::~FrameHandler()
{
    qDebug() << "Enter FrameHandler destructor";
    this->disconnectCan();
}


bool FrameHandler::connectCan() // need work
{
    qDebug() << "Enter FrameHandler::connectCan() function";
    QString errorString;
    _can0 = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
    // GO TO THE GITHUB QTSERIALBUS TO BUILD A PLUGGIN

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
                //QObject::connect(_can0, &QCanBusDevice::framesReceived, this, &FrameHandler::onFramesReceived,Qt::UniqueConnection); enable this later on and see
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
    qDebug() << "Enter FrameHandler::disconnectCan() function";
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
            //return false;
        case QCanBusDevice::ConnectedState:
            //QObject::disconnect(_can0, &QCanBusDevice::framesReceived, this, &FrameHandler::onFramesReceived);
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

void FrameHandler::getBusStatus() // Create a QML item displaying color for each state
{
    qDebug() << "Enter FrameHandler::getBusStatus() function";
    if(!_can0 || !_can0->hasBusStatus())
    {
        _busStatus = "No CAN bus status available.";
        emit busStatusChanged();
        return;
    }
    switch(_can0->busStatus())
    {
    case QCanBusDevice::CanBusStatus::Unknown: // Black
         _busStatus = "Can Bus Status: Unknown (Not supported by CAN pluggin)";
        emit busStatusChanged();
         return;
    case QCanBusDevice::CanBusStatus::Good: // Green
        _busStatus = "Can Bus Status: Fully operational";
        emit busStatusChanged();
        return;
    case QCanBusDevice::CanBusStatus::Warning: // Yellow
        _busStatus = "Can Bus Status: Warning";
        emit busStatusChanged();
        return;
    case QCanBusDevice::CanBusStatus::Error: // Red
        _busStatus = "Can Bus Status: Error";
        emit busStatusChanged();
        return;
    case QCanBusDevice::CanBusStatus::BusOff: // Blue
        _busStatus = "Can Bus Status: Bus disconnected";
        emit busStatusChanged();
        return;
    }
    _busStatus = "???";
    emit busStatusChanged();
    return;
}

bool FrameHandler::isOperational()
{
    qDebug() << "Enter FrameHandler::isOperational() function";
    if(!_can0 || !_can0->hasBusStatus() || !(_can0->state() == QCanBusDevice::ConnectedState))
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
    qDebug() << "Enter FrameHandler::onErrorOccured() function";
}

// TODO FOR TOMORROW: WORK ON VALVE STUFF, ID 546 & ID 547 & (maybe) ID 552
void FrameHandler::onFramesReceived() // In the future, might need to write frames data to a file
{
    qDebug() << "Enter FrameHandler::onFramesReceived() function";
    if(this->isOperational()) return;

    while (_can0->framesAvailable()) //
    {
        QCanBusFrame dataFrame = _can0->readFrame();

        // dissect data from the frame then update the GUI
        // CAN 2.0
        if (!dataFrame.hasExtendedFrameFormat())
        {
            QString frameIDBi;
            try
            {
                frameIDBi = {QString::number(dataFrame.frameId(), 2)}; // grab the ID in the form of binary
            }
            catch (...)
            {
                continue;
            }

            //const QString frameIDInt {QString::number(dataFrame.frameId(), 10)}; // grab the ID in the form of int
            //const QString frameIDHex {QString::number(dataFrame.frameId(), 16)}; // grab the ID in the form of hexadecimal

            // perform surgery on frameID
            // Get ID's A and B in both integer and binary forms
            QString ID_A_bin;
            QString ID_B_bin;
            quint16 ID_A;
            quint32 ID_B;
            if (dataFrame.hasExtendedFrameFormat())
            {
                ID_A_bin = frameIDBi.sliced(18); // extract the last 11 bits
                ID_B_bin = frameIDBi.sliced(0,18); // extract the first 18 bits
                ID_A = ID_A_bin.toInt(nullptr, 2);
                ID_B = ID_B_bin.toInt(nullptr, 2);
            }
            else // No extended format -> no ID B
            {
                ID_A_bin = frameIDBi;
                ID_A = ID_A_bin.toInt(nullptr,2);
            }

            // Dissect payload:
            // !!!this needs to be reworked. QByteArray is presented like a string, where each character represents a byte
            const QByteArray payload {dataFrame.payload().toHex(0)}; // returns nibble by nibble. Join two nibbles to make a byte
            QList<QByteArray> data;
            //QStack<QByteArray> data;
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

                for (int i {0}; i < payload.length(); i = i + 2) //
                {
                     QByteArray byte;
                     byte.append(payload.at(i)); byte.append(payload.at(i+1)); // put 2 nibbles together to make a byte

                     data.append(byte); // QByteArray doesn't seem too intuitive to work with so this is the way
                                        // it has to be :"(
                }

                // !! when concatenate byte, do the reverse like byte1 + byte0 ///////

            /*
            // handle byte order and join nibbles to make bytes
            for (qsizetype i {payload.length()}; i > 0; i = i - 2) //
                {
                    QByteArray byte;
                    byte.append(payload.at(i)); byte.append(payload.at(i-1)); // put 2 nibbles together to make a byte
                    data.append(byte);  // QByteArray doesn't seem too intuitive to work with so this is the way
                                        // it has to be :"(
                }
            */
            //}
            //else
            //{

            //}

            // might scrap everything below and move to CAN FD!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            // sensors
            if (ID_A >= 51 && ID_A <= 426) // find out the actual ID's of the devices and to an || operator
            {
                emit sensorReceived(ID_A, ID_B, data);
                return;
            }
            //Valve renegade engine
            if (ID_A == 546)
            {
                QString HP1_bin {ID_B_bin.sliced(11,8)}; // According to the python gui
                QString HP2_bin {ID_B_bin.sliced(3,8)}; // According to the python gui

                std::reverse(HP1_bin.begin(), HP1_bin.end());
                std::reverse(HP2_bin.begin(), HP2_bin.end());

                quint16 HP1 = HP1_bin.toInt(nullptr, 2);
                quint16 HP2 = HP2_bin.toInt(nullptr, 2);
                emit valveReceived(HP1, HP2, data);
                return;
            }
            // Valve renegade prop
            if (ID_A == 547)
            {
                // perform surgery on frameID
                QString HP1_bin {ID_B_bin.sliced(11,8)}; // According to the python gui
                QString HP2_bin {ID_B_bin.sliced(3,8)}; // According to the python gui

                std::reverse(HP1_bin.begin(), HP1_bin.end());
                std::reverse(HP2_bin.begin(), HP2_bin.end());

                quint16 HP1 = HP1_bin.toInt(nullptr, 2);
                quint16 HP2 = HP2_bin.toInt(nullptr, 2);
                emit valveReceived(HP1, HP2, data);
                return;
            }
            // Valves
            if (ID_A == 552)
            {
            // leave it blank here since it seems like it's not used
                return;
            }
            //"NODE STATE REPORT" "Bytes 1,2,3,4,5,6,7 are not used according to the python gui"
            //"Engine Node 2"
            //"Prop Node 3"
            if (ID_A > 510 && ID_A < 530)
            {
                try{
                    if (ID_A == 514)
                    {
                        setNodeStatusRenegadeEngine(_vehicleStates.at(data.at(0).toInt(nullptr,16))); // byte zero carries a value from 0 to 12
                        // catch the remaining bytes in the future. Don't wanna catch all of rest since I don't know many bytes there actually are
                        return;
                    }
                    if (ID_A == 515)
                    {
                        setNodeStatusRenegadeProp(_vehicleStates.at(data.at(0).toInt(nullptr,16)));
                        // catch the remaining bytes in the future. Don't wanna catch all of rest since I don't know many bytes there actually are
                        return;
                    }
                    if (ID_A == 520) // also Dan said there is no ID_A == 520
                    {
                        //setNodeStatusBang(_vehicleStates.at(data.at(0).toInt(nullptr,16)));
                        return;
                    }
                }
                catch (...)
                {
                    continue;
                }
            }
            if (ID_A == 1100)
            {
                _controller->setAutosequenceTime(dataFrame.payload().toFloat(nullptr)/1000000); // this wouldn't work. need to access each byte using the .at() function
                                                                                                // then squash those bits together
                return;
            }

            // switch to else if to get rid of uncessary returns???
            if (ID_A == 1506)
            {   // Commenting this out because in the python gui, throttlePoints is initially a dict,
                // but it's then set to a list when time is 0 ... seems like not used yet

                //quint32 time = (data.at(0) + data.at(1)).toInt(nullptr,16);
                //quint32 throttlePoint = (data.at(2) + data.at(3)).toInt(nullptr,16);
                //_throttlePoints.push(QVarLengthArray<quint32, 2>{time, throttlePoint});
                //try
                //{
                //    time = (data.at(4) + data.at(5)).toInt(nullptr,16);
                //    throttlePoint = (data.at(6) + data.at(7)).toInt(nullptr,16);
                //    _throttlePoints.push(QVarLengthArray<quint32, 2>{time, throttlePoint});
                //}
                //catch (...)
                //{
                //    continue;
                //}
            }

            if (data.length())
            {
                quint16 controllerID = ((((ID_A+49)/100)*100)-1000)/100; //(((ID_A+49)/100)*100) = round ID_A to the nearest hundred. It works trust me :)
                quint16 controllerIndex = ID_A % 100;
                if (data.length() == 8)
                {
                    if ((ID_A == 1502 || ID_A == 1504) && controllerID == _controller->_engineControllerID)
                    {
                        switch (controllerIndex)
                        {
                        case 2:
                            _controller->setFuelMVTime((data.at(0) + data.at(1) + data.at(2) + data.at(3)).toInt(nullptr,16));
                            _controller->setLOXMVTime((data.at(4) + data.at(5) + data.at(6) + data.at(7)).toInt(nullptr,16));
                            break;
                        case 4:
                            _controller->setIGN1Time((data.at(0) + data.at(1) + data.at(2) + data.at(3)).toInt(nullptr,16));
                            _controller->setIGN2Time((data.at(4) + data.at(5) + data.at(6) + data.at(7)).toInt(nullptr,16));
                            break;
                        }
                    }
                    // tank controller hiPress, LOX, fuel
                    //else if
                    //{
                    //
                    //}
                    //else
                    //{
                    //
                    //}
                }
                else //Node controller ????
                {

                }
            }
        }
        // CANFD
        else
        {

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
    qDebug() << "Enter FrameHandler::onFramesWritten() function";
}

void FrameHandler::onStateChanged(QCanBusDevice::CanBusDeviceState state)
{
    qDebug() << "Enter FrameHandler::onStateChanged() function";
}

// Expose the object to QML so that QML can use this function
void FrameHandler::sendFrame(quint32 ID, QString dataHexString) //QCanBusFrame::FrameId or quint32
{
    // in QML, just concantenate all the strings to form a byte array represented as string and pass it in as an argument.
    qDebug() << "Enter FrameHandler::sendFrame() function";
    if(!this->isOperational()) return;
    //dataHexString is passed from QML
    //QByteArray data {QByteArrayLiteral(dataHexString)};
    QByteArray data {QByteArray::fromHex(dataHexString.toLatin1())};
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
    nodeSynchronization();
}

FrameHandler::VehicleState FrameHandler::nodeStatusBang() const
{
    return _nodeStatusBang;
}

void FrameHandler::setNodeStatusBang(FrameHandler::VehicleState newNodeStatusBang)
{
    _nodeStatusBang = newNodeStatusBang;
    emit nodeStatusBangChanged();
    nodeSynchronization();
}

FrameHandler::VehicleState FrameHandler::currGUIState() const
{
    return _currGUIState;
}

void FrameHandler::setcurrGUIState(VehicleState newcurrGUIState)
{
    _currGUIState = newcurrGUIState;
    emit currGUIStateChanged();
}

FrameHandler::VehicleState FrameHandler::prevGUIState() const
{
    return _prevGUIState;
}

void FrameHandler::prevGUIState(VehicleState newPrevGUIState)
{
    _prevGUIState = newPrevGUIState;
    emit prevGUIStateChanged();
}

Controller* FrameHandler::controller() const
{
    return _controller;
}

void FrameHandler::nodeSynchronization()
{
    if (_nodeStatusRenegadeEngine == _nodeStatusRenegadeProp)
    {
        _nodeSyncStatus = NodeSyncStatus::IN_SYNC;
    }
    else if (_nodeStatusRenegadeEngine != _nodeStatusRenegadeProp)
    {
        _nodeSyncStatus = NodeSyncStatus::NOT_IN_SYNC;
    }
    // need to expand
}

QString FrameHandler::busStatus() const
{
    return _busStatus;
}

// run
void FrameHandler::run()
{
    qDebug() << "Enter FrameHandler::run() function";
    qInfo() << QThread::currentThread(); // Looks like it's a different thread when it's thread pooled
    qInfo() << QThread::currentThread();
    qInfo() << QThread::currentThread();
    qInfo() << QThread::currentThread();
    qInfo() << QThread::currentThread();
    qInfo() << QThread::currentThread();
    qInfo() << "Hello?";
    qInfo() << QThread::currentThread();
    qInfo() << this->controller()->IGN1Time();
    _controller->setIGN1Time(5.2f);
    qInfo() << _controller->IGN1Time();
    this->connectCan();

    //while (true) //
    //{
    //    if (this->isOperational())
    //    {
    //        this->onFramesReceived(); // might need to disconnect the signal connected to this slot since I don't know quite how that works
    //        //this->getBusStatus();  // this updates the string notifying the status of the can bus. might need to rework this
    //    }
    //}
}
// * When the function run
// so if _loop is false, this FrameHandler object/thread is guarenteed to be destroyed
// -> never set _loop to false???
