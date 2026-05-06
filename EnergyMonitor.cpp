#include <iostream>   
#include <map>        
#include <string>     
#include "EnergyMonitor.h"
#include "Device.h"


EnergyMonitor::EnergyMonitor() {

}

void EnergyMonitor::addDevice(int id, std::string name, double power, std::string room) {
    devices[id] = Device(id, name, power, room);
}