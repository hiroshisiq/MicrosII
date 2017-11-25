#include <gui/mainwindow.h>
#include <QApplication>
#include <control/observer.h>
#include <control/controller.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Generate main Window
    MainWindow w;

//    a.setStyle("windows");
    Observer* b = new Observer();
    Controller* ctrl = new Controller(new Serial(), &w, b);
    emit ctrl->operate();

    w.show();

    // Close app when window is close
    qApp->quitOnLastWindowClosed();

    return a.exec();
}
