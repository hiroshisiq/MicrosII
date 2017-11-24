#include <gui/mainwindow.h>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Generate main Window
    MainWindow w;
//    a.setStyle("windows");
    w.show();

    // Close app when window is close
    qApp->quitOnLastWindowClosed();

    return a.exec();
}
