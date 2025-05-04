#include "arduino.h"


Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
    return serial;
}
int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts())
    {
<<<<<<< HEAD
        if (serial_port_info.portName() == "COM9")
=======
        if (serial_port_info.portName() == "COM10")
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
        {
            arduino_is_available = true;
            arduino_port_name = serial_port_info.portName();
        }
    }

    if (arduino_is_available)
    {
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite))
        {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "Arduino connected on port:" << arduino_port_name;
            return 0;
        }
        else
        {
            qDebug() << "Failed to open serial port";
            return 1;
        }
    }
    else
    {
        qDebug() << "Arduino not found!";
        return -1;
    }
}

int Arduino::close_arduino()

{

    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;


}


QByteArray Arduino::read_from_arduino()
{
    QByteArray data;
    if (serial->isReadable()) {
        data = serial->readAll(); // Récupérer les données reçues
    }
    return data; // Retourne soit les données, soit un QByteArray vide
}



void Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
}


}
