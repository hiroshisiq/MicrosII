#include <gui/mainwindow.h>
#include <serial/serial.h>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Init serial comunication
    Serial *serial = new Serial();

    // Init GUI
    MainWindow mainWindow;

//    mainWindow.setGeometry(QRect(0, 0, 300, 400));
    mainWindow.setWindowTitle("Step Motor Controller");
    mainWindow.setSerial(serial);

    mainWindow.show();

    return app.exec();
}
