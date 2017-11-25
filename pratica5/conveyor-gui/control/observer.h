#ifndef OBSERVER_H
#define OBSERVER_H

#include <QMutex>

class Observer{

private:
    // Normal running
    static bool _rejectMetal;
    static bool _rejectNonMetal;
    static bool _normalStart;

    // Sensor info
    static bool _capSensor;
    static bool _indSensor;
    static bool _optSensor;

    // Test
    static bool _testStart;
    static bool _turnLeft;
    static bool _advancePiston;

    QMutex* m;

public:
    Observer() { m = new QMutex(); }

    /// Getters
    // Normal running
    static bool getRejectMetal() { return _rejectMetal; }
    static bool getRejectNonMetal() { return _rejectNonMetal; }
    static bool getNormalStart() { return _normalStart; }

    // Sensor info
    static bool getCapSensor() { return _capSensor;}
    static bool getIndSensor() { return _indSensor;}
    static bool getOptSensor() { return _optSensor;}

    // Test
    static bool getTestStart() { return _testStart; }
    static bool getTurnLeft() { return _turnLeft; }
    static bool getAdvancePiston() { return _advancePiston; }

    /// Setters
    // Normal running
    static void setRejectMetal(bool status) { _rejectMetal = status; }
    static void setRejectNonMetal(bool status) { _rejectNonMetal = status; }
    static void setNormalStart(bool status) { _normalStart = status; }

    // Sensor info
//    void setCapSensor(bool status) { /*m->lock();*/ _capSensor = status; /*m->unlock();*/}
    static void setCapSensor(bool status) { _capSensor = status; }
    static void setIndSensor(bool status) { _indSensor = status; }
    static void setOptSensor(bool status) { _optSensor = status; }

    // Test
    static void setTestStart(bool status) { _testStart = status; }
    static void setTurnLeft(bool status) { _turnLeft  = status; }
    static void setAdvancePiston(bool status) { _advancePiston = status; }
};

#endif // OBSERVER_H
