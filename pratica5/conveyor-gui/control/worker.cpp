#include "worker.h"
#include <unistd.h>

void Worker::doWork() {
    while(true) {
        // Update gui
        if(_main != NULL) {
            _main->updateInfo();
        }

        // Wait 100ms
        usleep(100*1000);
    }

    emit resultReady();
}
