#include "FrameHandler.hpp"
//Don't include these anywhere else or there will/could be multiple duplications
#include "SensorObjectDefinitions.hpp"
#include "HPSensorObjectDefinitions.hpp"
#include "ValveObjectDefinitions.hpp"
#include "AutosequenceObjectDefinitions.hpp"
#include "TankPressControllerObjectDefinitions.hpp"
#include "EngineControllerObjectDefinitions.hpp"
FrameHandler::FrameHandler(QObject *parent)
    : QObject{parent}
{
    qDebug() << "Enter FrameHandler constructor"; // Note: because of threading, this might not be an accurate way of finding out where the program crashes
    foreach(const auto& sensorConstructingParameter, sensorConstructingParameters) //sensor key List
    {                                                                       //{"High_Press_Fuel"} {"High_Press_Lox"} {"Fuel_Tank_1"} {"Fuel_Tank_2"}
        _sensors.insert(sensorConstructingParameter.at(0).toString(),        //{"Lox_Tank_1"} {"Lox_Tank_2"} {"Fuel_Dome_Reg"} {"Lox_Dome_Reg"}
                        QVariant::fromValue<Sensor*>(new Sensor{this, sensorConstructingParameter}));       //{"Fuel_Prop_Inlet"} {"Lox_Prop_Inlet"} {"Fuel_Injector"}
    }                                                                       //{"LC1"} {"LC2"} {"LC3"} {"Chamber_1"} {"Chamber_2"} {"MV_Pneumatic}

    foreach(const auto& HPSensorConstructingParameter, HPSensorConstructingParameters)
    {
        _HPSensors.insert(HPSensorConstructingParameter.at(0).toString(),
                          QVariant::fromValue<HPSensor*>(new HPSensor{this, HPSensorConstructingParameter}));
    }

    foreach(const auto& valveConstructingParameter, valveConstructingParameters)  // valve key list
    {                                                                       //{"HV"} {"HP"} {"LDR"} {"FDR"} {"LDV"}
        _valves.insert(valveConstructingParameter.at(0).toString(),         // {"FDV"} {"LV"} {"FV"}
                       QVariant::fromValue<Valve*>(new Valve{this, valveConstructingParameter}));        //{"LMV"} {"FMV"} {"IGN1"} {"IGN2"}
    }

    foreach(const auto& autosequenceConstructingParameter, autosequenceConstructingParameters)
    {
        _autosequences.insert(autosequenceConstructingParameter.at(0).toString(),
                              QVariant::fromValue<Autosequence*>(new Autosequence{this, autosequenceConstructingParameter}));
    }

    foreach(const auto& tankPressControllerConstructingParameter, tankPressControllerConstructingParameters)
    {
        _tankPressControllers.insert(tankPressControllerConstructingParameter.at(0).toString(),
                                    QVariant::fromValue<TankPressController*>(new TankPressController{this, tankPressControllerConstructingParameter}));
    }

    foreach(const auto& engineControllerConstructingParameter, engineControllerConstructingParameters)
    {
        _engineControllers.insert(engineControllerConstructingParameter.at(0).toString(),
                                QVariant::fromValue<EngineController*>(new EngineController{this, engineControllerConstructingParameter}));
    }


    //Connect signals and slots
    foreach(const QString& sensorKey, _sensors.keys()) // iterating through QMap, value is assigned instead of the key
    {
        QObject::connect(this, &FrameHandler::sensorReceived, qvariant_cast<Sensor*>(_sensors.value(sensorKey)), &Sensor::onSensorReceived);
        QObject::connect(this, &FrameHandler::sensorReceivedFD, qvariant_cast<Sensor*>(_sensors.value(sensorKey)), &Sensor::onSensorReceivedFD);
        QObject::connect(&_sensorsTimer, &QTimer::timeout, qvariant_cast<Sensor*>(_sensors.value(sensorKey)), &Sensor::emitUpdateGraphQML_rawValue);
        QObject::connect(&_sensorsTimer, &QTimer::timeout, qvariant_cast<Sensor*>(_sensors.value(sensorKey)), &Sensor::emitUpdateGraphQML_convertedValue);
    }
    foreach(const QString& HPSensorKey, _HPSensors.keys()) // iterating through QMap, value is assigned instead of the key
    {
        QObject::connect(this, &FrameHandler::HPSensorReceivedFD, qvariant_cast<HPSensor*>(_HPSensors.value(HPSensorKey)), &HPSensor::onHPSensorReceivedFD);
        QObject::connect(&_HPSensorsTimer, &QTimer::timeout, qvariant_cast<HPSensor*>(_HPSensors.value(HPSensorKey)), &HPSensor::emitUpdateGraphQML_outputValue);
    }
    foreach(const QString& valveKey, _valves.keys()) // iterating through QMap, value is assigned instead of the key
    {
        QObject::connect(this, &FrameHandler::valveReceived, qvariant_cast<Valve*>(_valves.value(valveKey)), &Valve::onValveReceived);
        QObject::connect(this, &FrameHandler::valveReceivedFD, qvariant_cast<Valve*>(_valves.value(valveKey)), &Valve::onValveReceivedFD);
    }
    foreach(const QString& autosequenceKey, _autosequences.keys())
    {
        QObject::connect(this, &FrameHandler::autosequenceReceivedFD,
                         qvariant_cast<Autosequence*>(_autosequences.value(autosequenceKey)), &Autosequence::onAutosequenceReceivedFD);
    }
    foreach(const QString& tankPressControllerKey, _tankPressControllers.keys())
    {
        QObject::connect(this, &FrameHandler::tankPressControllerReceivedFD,
                         qvariant_cast<TankPressController*>(_tankPressControllers.value(tankPressControllerKey)), &TankPressController::onTankPressControllerReceivedFD);
    }
    foreach(const QString& engineControllerKey, _engineControllers.keys())
    {
        QObject::connect(this, &FrameHandler::engineControllerReceivedFD,
                         qvariant_cast<EngineController*>(_engineControllers.value(engineControllerKey)), &EngineController::onEngineControllerReceivedFD);
    }

    QObject::connect(this, &FrameHandler::started, this, &FrameHandler::onStarted);
    QObject::connect(this, &FrameHandler::stopped, this, &FrameHandler::onStopped);
    QObject::connect(this, &FrameHandler::paused, this, &FrameHandler::onPaused);
    QObject::connect(this, &FrameHandler::resumed, this, &FrameHandler::onResumed);
    QObject::connect(&_timer, &QTimer::timeout, this, &FrameHandler::timeout);

    _sensorsTimer.setInterval(100);
    _HPSensorsTimer.setInterval(100);
    _sensorsTimer.start(); // move this under the connectCan function in release
    _HPSensorsTimer.start();

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
    _can0 = QCanBus::instance()->createDevice(QStringLiteral("peakcan"), QStringLiteral("usb0"), &errorString);

    if(!_can0)
    {
        qDebug() << errorString;
        _logger.outputLogMessage("Error connecting CAN, error string: " + errorString);
        return false;
    }

    // check if these will crash the program after _can0 is actually created later on
    _can0->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant(500'000));
    _can0->setConfigurationParameter(QCanBusDevice::ReceiveOwnKey, QVariant(true));

    // canFD
    _can0->setConfigurationParameter(QCanBusDevice::CanFdKey, QVariant(true)); // can FD is only truly enabled if both hardware and driver support CAN FD
                                                                                // otherwise it falls back to can2.0b
    //_can0->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant(1'000'000));
    _can0->setConfigurationParameter(QCanBusDevice::DataBitRateKey, QVariant(5'000'000)); // Remeber to modify the _logger.outputLogMessage


    switch(_can0->state())
    {
    case QCanBusDevice::UnconnectedState:
        if(!_can0->connectDevice())
        {
            qDebug() << "Device could not be connected";
            _logger.outputLogMessage("CAN could not be connected");
            return false;
        }
        else
        {
            // connect signals and slots to the Can Bus here
            //QObject::connect(_can0, &QCanBusDevice::framesReceived, this, &FrameHandler::onFramesReceived,Qt::UniqueConnection); // Disable this for now and call manually in run(). Enable this later on and see
            QObject::connect(_can0, &QCanBusDevice::framesWritten, this, &FrameHandler::onFramesWritten,Qt::UniqueConnection);
            QObject::connect(_can0, &QCanBusDevice::errorOccurred, this, &FrameHandler::onErrorOccurred,Qt::UniqueConnection);
            QObject::connect(_can0, &QCanBusDevice::stateChanged, this, &FrameHandler::onStateChanged,Qt::UniqueConnection);
            qDebug() << "Can connected successfully";
            //_sensorsTimer.start();
            _logger.outputLogMessage("CAN connected successfully");
            _logger.outputLogMessage("CAN settings:\n   -Bit Rate Key: 0.5 Mbps\n   -Receive Own Key: true\n   -CanFD key: true\n   -DataBitRateKey:   5 Mbps");
            return true;
        }
        break;
    case QCanBusDevice::ConnectingState:
        qDebug() << "The device is being connected...";
        _logger.outputLogMessage("CAN is being connected...");
        return false;
        break;
    case QCanBusDevice::ConnectedState:
        qDebug() << "The device is already connected";
        _logger.outputLogMessage("CAN is already connected");
        return false;
        break;
    case QCanBusDevice::ClosingState:
        qDebug() << "The device is closing...";
        _logger.outputLogMessage("CAN is currently closing...");
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
        _logger.outputLogMessage("No CAN device to be disconnected");
        return false;
    }

    switch (_can0->state())
    {
    case QCanBusDevice::UnconnectedState:
        _logger.outputLogMessage("CAN is already unconnected");
        return false;
    case QCanBusDevice::ConnectingState:
        _logger.outputLogMessage("CAN is connecting...");
        return false;
    case QCanBusDevice::ConnectedState:
        //QObject::disconnect(_can0, &QCanBusDevice::framesReceived, this, &FrameHandler::onFramesReceived);
        QObject::disconnect(_can0, &QCanBusDevice::framesWritten, this, &FrameHandler::onFramesWritten);
        QObject::disconnect(_can0, &QCanBusDevice::errorOccurred, this, &FrameHandler::onErrorOccurred);
        QObject::disconnect(_can0, &QCanBusDevice::stateChanged, this, &FrameHandler::onStateChanged);
        _can0->disconnectDevice();
        delete _can0;
        _can0 = nullptr;
        //_sensorsTimer.stop();
        _logger.outputLogMessage("CAN has been disconnected...");
        return true;
    case QCanBusDevice::ClosingState:
        _logger.outputLogMessage("CAN is already closing...");
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
    qDebug() << "this line in FrameHandler::isOperational() function should not be reached!";
    return false;
}

void FrameHandler::onErrorOccurred(QCanBusDevice::CanBusError error)
{
    qDebug() << "Enter FrameHandler::onErrorOccured() function";
}


void FrameHandler::onFramesReceived() // In the future, might need to write frames data to a file
{
    qDebug() << "Enter FrameHandler::onFramesReceived() function";
    if(!this->isOperational())
    {
        qDebug() << "FrameHandler::onFramesReceived(): can not operational";
        return;
    }

    while (_can0->framesAvailable()) // while or if
    {
        QCanBusFrame dataFrame = _can0->readFrame();
        // dissect data from the frame then update the GUI
        if (!dataFrame.hasFlexibleDataRateFormat())
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
            const QByteArray payload {dataFrame.payload().toHex()}; // returns nibble by nibble. Two nibbles make a byte
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
                //_controller->setAutosequenceTime(dataFrame.payload().toFloat(nullptr)/1000000); // may need to convert this to int then cast it to float
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
                /*
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
                */
            }
            // states
            //if (frameID >= 2001 && frameID <= 3000)
            //{
            //    emit stateReceived(frameID, data);
            //}
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (dataFrame.hasFlexibleDataRateFormat())
        {
            quint32 id = dataFrame.frameId();
            quint16 engineNode = static_cast<quint16>(Node::NodeID::ENGINE_NODE);
            quint16 propNode = static_cast<quint16>(Node::NodeID::PROP_NODE);

            // Dissect payload:
            const QByteArray payload {dataFrame.payload().toHex()}; // returns nibble by nibble. Two nibbles make a byte
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

            for (int i {0}; i < payload.length(); i = i + 2)
            {
                QByteArray byte;
                byte.append(payload.at(i)); byte.append(payload.at(i+1)); // put 2 nibbles together to make a byte
                data.append(byte); // data.at(0) = Byte 1, data.at(1) = Byte 2, etc...
            }
            ///////////////////////////////////
            //WRITE FRAMES TO A FILE HERE

            ///////////////////////////////////
            // States
            if (PROP_NODE_STATE_ID_OFFSET <= id && id < PROP_NODE_STATE_ID_OFFSET + 10)
            {
                //QTimer timeout signal handler ?
                if (id == PROP_NODE_STATE_ID_OFFSET + engineNode)
                {
                    setNodeStatusRenegadeEngine(static_cast<FrameHandler::VehicleState>(data.at(0).toUInt(nullptr, 16)));
                    setMissionStatusRenegadeEngine(static_cast<FrameHandler::MissionState>(data.at(1).toUInt(nullptr, 16)));
                    setCurrentCommandRenegadeEngine(static_cast<FrameHandler::Command>(data.at(2).toUInt(nullptr, 16)));
                    return;
                }
                if (id == PROP_NODE_STATE_ID_OFFSET + propNode)
                {
                    setNodeStatusRenegadeProp(static_cast<FrameHandler::VehicleState>(data.at(0).toUInt(nullptr, 16)));
                    setMissionStatusRenegadeProp(static_cast<FrameHandler::MissionState>(data.at(1).toUInt(nullptr, 16)));
                    setCurrentCommandRenegadeProp(static_cast<FrameHandler::Command>(data.at(2).toUInt(nullptr, 16)));
                    return;
                }
            }

            if (AUTOSEQUENCE_ID_OFFSET <= id && id < AUTOSEQUENCE_ID_OFFSET + 10)
            {
                emit autosequenceReceivedFD(data);
                return;
            }

            // Sensors
            if (SENSOR_ID_OFFSET <= id && id < SENSOR_ID_OFFSET + 10)
            {
                emit sensorReceivedFD(data);
                return;
            }

            if (HP_SENSOR_ID_OFFSET <= id && id < HP_SENSOR_ID_OFFSET +10)
            {
                emit HPSensorReceivedFD(data);
                return;
            }

            if (HP_OBJECT_ID_OFFSET <= id && id < HP_OBJECT_ID_OFFSET + 10)
            {
                emit valveReceivedFD(data);
                return;
            }

            if (TANK_PRESS_CONTROLLER_ID_OFFSET <= id && id < TANK_PRESS_CONTROLLER_ID_OFFSET + 10)
            {
                emit tankPressControllerReceivedFD(data);
                return;
            }

            if (ENGINE_CONTROLLER_ID_OFFSET <= id && id < ENGINE_CONTROLLER_ID_OFFSET + 10)
            {
                emit engineControllerReceivedFD(data);
                return;
            }
        }
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
void FrameHandler::sendFrame(quint32 ID, QString dataHexString, QCanBusFrame::FrameType frameType,
                             bool bitRateSwitch, bool extendedFrameFormat, bool FlexibleDataRateFormat) //QCanBusFrame::FrameId or quint32
{
    // in QML, just concantenate all the strings to form a byte array represented as string and pass it in as an argument.
    qDebug() << "Enter FrameHandler::sendFrame() function";
/*
    if(!this->isOperational())
    {
        qInfo() << "FrameHandler::sendFrame(): Can not Operational";
        _logger.outputLogMessage("CAN not operational.............................................\n............................................................................\n...............................................");
        return;
    }
*/
    //dataHexString is passed from QML
    //QByteArray data {QByteArrayLiteral(dataHexString)};
    QByteArray data {QByteArray::fromHex(dataHexString.toLatin1())};
    QCanBusFrame dataFrame {ID, data};
    dataFrame.setFrameType(frameType);
    dataFrame.setBitrateSwitch(bitRateSwitch);
    dataFrame.setExtendedFrameFormat(extendedFrameFormat);
    dataFrame.setFlexibleDataRateFormat(FlexibleDataRateFormat);


    qInfo() << "frame ID: " << dataFrame.frameId();
    qInfo() << "QCanBusFrame dataFrame's payload in Hex: " << dataFrame.payload().toHex();
    qInfo() << "frame type: " << dataFrame.frameType();
    qInfo() << "bitRateSwitch: " << dataFrame.hasBitrateSwitch();
    qInfo() << "extendedFrameFormat: " << dataFrame.hasExtendedFrameFormat();
    qInfo() << "FlexibleDataRateFormat: " << dataFrame.hasFlexibleDataRateFormat();

    // for Virtual CAN Testing
    //remoteFrame.setErrorStateIndicator(false);
    //remoteFrame.setLocalEcho(false);

    _logger.outputLogMessage("(testing) CAN frame: " + QString::number(dataFrame.frameId()) + "-" + dataFrame.payload().toHex() + "-"
                             + QString::number(dataFrame.frameType()) + "-" + QString::number(dataFrame.hasBitrateSwitch()) + "-"
                             + QString::number(dataFrame.hasFlexibleDataRateFormat()));
    //_logger.outputLogMessage(&"Can frame sent: " [ _can0->writeFrame(dataFrame)]);

    if(!this->isOperational()) // delete this when deploy
    {
        qInfo() << "FrameHandler::sendFrame(): Can not Operational";
        return;
    }

    //_can0->writeFrame(dataFrame);
    if (_can0->writeFrame(dataFrame))
    {
        _logger.outputLogMessage("SUCCESS in sending CAN frame: " + QString::number(dataFrame.frameId()) + "-" + dataFrame.payload().toHex() + "-"
                                 + QString::number(dataFrame.frameType()) + "-" + QString::number(dataFrame.hasBitrateSwitch()) + "-"
                                 + QString::number(dataFrame.hasFlexibleDataRateFormat()));
    }
    else
    {
        _logger.outputLogMessage("FAILED to send CAN frame: " + QString::number(dataFrame.frameId()) + "-" + dataFrame.payload().toHex() + "-"
                                 + QString::number(dataFrame.frameType()) + "-" + QString::number(dataFrame.hasBitrateSwitch()) + "-"
                                 + QString::number(dataFrame.hasFlexibleDataRateFormat()));
    }
    //_logger.outputLogMessage(&"Can frame sent: " [ _can0->writeFrame(dataFrame)]);
}

void FrameHandler::onStarted()
{

}

void FrameHandler::onStopped()
{

}

void FrameHandler::onPaused()
{

}

void FrameHandler::onResumed()
{

}

void FrameHandler::timeout()
{

}

// Getters and Setters section

QQmlPropertyMap* FrameHandler::HPSensors()
{
    return &_HPSensors;
}

QQmlPropertyMap* FrameHandler::sensors()
{
    return &_sensors;
}

QQmlPropertyMap* FrameHandler::valves()
{
    return &_valves;
}

QQmlPropertyMap* FrameHandler::autosequences()
{
    return &_autosequences;
}


QQmlPropertyMap* FrameHandler::tankPressControllers()
{
    return &_tankPressControllers;
}

QQmlPropertyMap* FrameHandler::engineControllers()
{
    return &_engineControllers;
}

Logger *FrameHandler::logger()
{
    return &_logger;
}


FrameHandler::VehicleState FrameHandler::nodeStatusRenegadeEngine() const
{
    return _nodeStatusRenegadeEngine;
}

void FrameHandler::setNodeStatusRenegadeEngine(FrameHandler::VehicleState newNodeStatusRenegadeEngine)
{
    _nodeStatusRenegadeEngine = newNodeStatusRenegadeEngine;
    emit nodeStatusRenegadeEngineChanged();
    setNodeSyncStatus();
}

FrameHandler::VehicleState FrameHandler::nodeStatusRenegadeProp() const
{
    return _nodeStatusRenegadeProp;
}

void FrameHandler::setNodeStatusRenegadeProp(FrameHandler::VehicleState newNodeStatusRenegadeProp)
{
    _nodeStatusRenegadeProp = newNodeStatusRenegadeProp;
    emit nodeStatusRenegadePropChanged();
    setNodeSyncStatus();
}

FrameHandler::MissionState FrameHandler::missionStatusRenegadeEngine() const
{
    return _missionStatusRenegadeEngine;
}

void FrameHandler::setMissionStatusRenegadeEngine(FrameHandler::MissionState newMissionStatusRenegadeEngine)
{
    if (_missionStatusRenegadeEngine == newMissionStatusRenegadeEngine)
        return;
    _missionStatusRenegadeEngine = newMissionStatusRenegadeEngine;
    emit missionStatusRenegadeEngineChanged();
}

FrameHandler::MissionState FrameHandler::missionStatusRenegadeProp() const
{
    return _missionStatusRenegadeProp;
}

void FrameHandler::setMissionStatusRenegadeProp(FrameHandler::MissionState newMissionStatusRenegadeProp)
{
    if (_missionStatusRenegadeProp == newMissionStatusRenegadeProp)
        return;
    _missionStatusRenegadeProp = newMissionStatusRenegadeProp;
    emit missionStatusRenegadePropChanged();
}

FrameHandler::Command FrameHandler::currentCommandRenegadeEngine() const
{
    return _currentCommandRenegadeEngine;
}

void FrameHandler::setCurrentCommandRenegadeEngine(FrameHandler::Command newCurrentCommandRenegadeEngine)
{
    if (_currentCommandRenegadeEngine == newCurrentCommandRenegadeEngine)
        return;
    _currentCommandRenegadeEngine = newCurrentCommandRenegadeEngine;
    emit currentCommandRenegadeEngineChanged();
}

FrameHandler::Command FrameHandler::currentCommandRenegadeProp() const
{
    return _currentCommandRenegadeProp;
}

void FrameHandler::setCurrentCommandRenegadeProp(FrameHandler::Command newCurrentCommandRenegadeProp)
{
    if (_currentCommandRenegadeProp == newCurrentCommandRenegadeProp)
        return;
    _currentCommandRenegadeProp = newCurrentCommandRenegadeProp;
    emit currentCommandRenegadePropChanged();
}

FrameHandler::NodeSyncStatus FrameHandler::nodeSyncStatus() const
{
    return _nodeSyncStatus;
}

void FrameHandler::setNodeSyncStatus()
{
    if (_nodeStatusRenegadeEngine == _nodeStatusRenegadeProp)
    {
        _nodeSyncStatus = NodeSyncStatus::IN_SYNC;
        emit nodeSyncStatusChanged(); // in QML, say onNodeSyncStatusChanged: {} then _nodeSyncStatus
    }
    else if (_nodeStatusRenegadeEngine != _nodeStatusRenegadeProp)
    {
        _nodeSyncStatus = NodeSyncStatus::NOT_IN_SYNC;
        emit nodeSyncStatusChanged();
    }
    // need to expand
}

QString FrameHandler::busStatus() const
{
    return _busStatus;
}


void FrameHandler::setLoopToFalse()
{
    _loop = false;
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
    //qInfo() << this->controller()->IGN1Time();
    //_controller->setIGN1Time(5.2f);
    //qInfo() << _controller->IGN1Time();
    //this->connectCan(); // Do this via a menu button. Same for disconnect too

    // set up via buttons in qml instead

    QElapsedTimer timer1;
    QElapsedTimer timer2;
    timer1.start();
    timer2.start();
    quint64 timeStamp = 0;
    float num = 0;

    while(_loop)
    {
        if (timer1.elapsed() >= 10) // 1 or 5 or 10
        {
/*
            if(qvariant_cast<Valve*>(_valves.value("FDR"))->valveState() == 0)
            {
                qInfo() << "Valve State: " << qvariant_cast<Valve*>(_valves.value("FDR"))->valveState();
                qvariant_cast<Valve*>(_valves.value("FDR"))->setValveState(1);
            }
            else if(qvariant_cast<Valve*>(_valves.value("FDR"))->valveState() == 1)
            {
                qInfo() << "Valve State: " << qvariant_cast<Valve*>(_valves.value("FDR"))->valveState();
                qvariant_cast<Valve*>(_valves.value("FDR"))->setValveState(2);
            }
            else if(qvariant_cast<Valve*>(_valves.value("FDR"))->valveState() == 2)
            {
                qInfo() << "Valve State: " << qvariant_cast<Valve*>(_valves.value("FDR"))->valveState();
                qvariant_cast<Valve*>(_valves.value("FDR"))->setValveState(3);
            }
            else if(qvariant_cast<Valve*>(_valves.value("FDR"))->valveState() == 3)
            {
                qInfo() << "Valve State: " << qvariant_cast<Valve*>(_valves.value("FDR"))->valveState();
                qvariant_cast<Valve*>(_valves.value("FDR"))->setValveState(4);
            }
            else if(qvariant_cast<Valve*>(_valves.value("FDR"))->valveState() == 4)
            {
                qInfo() << "Valve State: " << qvariant_cast<Valve*>(_valves.value("FDR"))->valveState();
                qvariant_cast<Valve*>(_valves.value("FDR"))->setValveState(0);
            }
*/

            qvariant_cast<Sensor*>(_sensors.value("High_Press_Fuel"))->setConvertedValue(1100 - num*num);
            qvariant_cast<Sensor*>(_sensors.value("High_Press_Fuel"))->setTimestamp(timeStamp);
            qvariant_cast<Sensor*>(_sensors.value("High_Press_Fuel"))->setConvertedValue(1100 - num*num);
            qvariant_cast<Sensor*>(_sensors.value("High_Press_Lox"))->setTimestamp(timeStamp);
            qvariant_cast<Sensor*>(_sensors.value("High_Press_Lox"))->setConvertedValue(1100 - num*num);
            qvariant_cast<Sensor*>(_sensors.value("Chamber_1"))->setTimestamp(timeStamp);
            qvariant_cast<Sensor*>(_sensors.value("Chamber_1"))->setConvertedValue(1100 - num*num);
            qvariant_cast<Sensor*>(_sensors.value("Lox_Tank_1"))->setTimestamp(timeStamp);
            qvariant_cast<Sensor*>(_sensors.value("Lox_Tank_1"))->setRawValue(num);
            qvariant_cast<Sensor*>(_sensors.value("Lox_Tank_1"))->setConvertedValue(1100 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP1"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP1"))->setOutputValue(2000 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP2"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP2"))->setOutputValue(1900 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP3"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP3"))->setOutputValue(1800 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP4"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP4"))->setOutputValue(1700 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP5"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP5"))->setOutputValue(1600 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP6"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP6"))->setOutputValue(1500 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP7"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP7"))->setOutputValue(1400 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP8"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP8"))->setOutputValue(1300 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP9"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP9"))->setOutputValue(1200 - num*num);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP10"))->setTimestamp(timeStamp);
            qvariant_cast<HPSensor*>(_HPSensors.value("RenegadePropHP10"))->setOutputValue(1100 - num*num);


            //_logger.outputLogMessage(QString::number(rawValue));
            timeStamp = timeStamp + 10'000;
            num = num + 0.01; // Keep this for QML to keep track of performance issue, i.e. it lags if this number stutters
            timer1.restart();





        }



        if (timer2.elapsed() > 1000)
        {
            //_logger.outputLogMessage("Test message");
            //setNodeSyncStatus();
            if (_nodeStatusRenegadeEngine == VehicleState::HI_PRESS_PRESSURIZED)
            {
                setNodeStatusRenegadeEngine(VehicleState::HI_PRESS_ARM);
                setNodeStatusRenegadeProp(VehicleState::HI_PRESS_ARM);
            }
            else
            {
                setNodeStatusRenegadeEngine(VehicleState::HI_PRESS_PRESSURIZED);
                setNodeStatusRenegadeProp(VehicleState::HI_PRESS_PRESSURIZED);
            }
            timer2.restart();
            //num = num + 1;
            //qInfo() << num;
            //if (num >= 5) loop = false;
        }


    }

    //while (true) //
    //{
    //    if (this->isOperational())
    //    {
    //        this->onFramesReceived(); // might need to disconnect the signal connected to this slot since I don't know quite how that works
    //        //this->getBusStatus();  // this updates the string notifying the status of the can bus. might need to rework this
    //    }
    //}
}
