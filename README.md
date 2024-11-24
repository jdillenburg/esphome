# John's ESPHome Devices
Welsome to my ESPhome configuration directory.  This file contains the ESPhome devices I use in my home:

* [Garage Door Controller](http://...#garage-door-controller)

## <a name="garage-door-controller">Garage Door Controller</a>
### Features
* TFmini-S Sensor code to measure vehcile's distance from front of garage.  
* LED Strip to display green for pulling vehicle into garage, yellow to slow down, and red to stop.
* Sensor to read door open/close status.
* Relay to push garage door controller button to open/close garage door.

### Files

| File                          | Description                     |
|-------------------------------|--------------------------------|
| garage-door-controller.yaml   | ESPHome Code for garage door controller                 |
| TFmini.h                      | Reads TFmini-S distance to car as a custom component    |

