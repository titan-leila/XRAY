#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

//What I need to do is to convert the image to a byte-array and then send this byte-array over the network. As we are using the Qt framework, I assume that the image is already a QImage object and the socket has been set-up by following the Simple chat example. Then sending the image is rather easy:
/*
// To load a QImage
//QImage image;        // See the documentation on how to use QImage objects
//image.load("test.png", "PNG");
// To set-up the socket
//socket->connectToHost(address, port, QIODevice::WriteOnly)

QByteArray ba;              // Construct a QByteArray object
QBuffer buffer(&ba);        // Construct a QBuffer object using the QbyteArray
image.save(&buffer, "PNG"); // Save the QImage data into the QBuffer
socket->write(ba);          // Send the QBuffer (QbyteArray) over a socket


// Available are:
//QTcpSocket* socket;
//QBuffer* buffer = buffers.value(socket);
qint64 bytes = buffer->write(socket->readAll()); // Read all the received bytes
buffer->seek(buffer->pos() - bytes);  // go back as many bytes as we just wrote so that it can be read
QImage image;                 // Construct a new QImage
image.loadFromData(buffer->buffer()); // Load the image from the receive buffer
if (image.isNull())           // Check if the image was indeed received
        qDebug("The image is null. Something failed.");
// If it did not fail, the image is now in the QImage object again
*/
