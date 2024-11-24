#include "esphome.h"
using namespace esphome;

int uart_value[9];          // save data measured by LiDAR
float distance;
const int HEADER = 0x59;    // frame header of data package
int rec_debug_state = 0x01; // receive state for frame
unsigned char check; 

class TFminiSensor : public Component, public sensor::Sensor, public UARTDevice{
public:
    TFminiSensor(UARTComponent *parent) : Component(), UARTDevice(parent) {}

    float get_setup_priority() const override { 
        return esphome::setup_priority::AFTER_CONNECTION; 
    }
    
    void setup() override {
        parent_->set_baud_rate(115200);
        // standard 9-byte output format (cm)
        // see Evernote https://share.evernote.com/note/b3d7af2b-81af-b69e-6d41-41705b77493f        
        const uint8_t standard_mode[5] = {0x5A, 0x05, 0x05, 0x01, 0x65};
        for (int i = 0;  i < 5;  i++) {
            write(standard_mode[i]);
        }
        // set refresh rate to 100Hz (1000/0x0A = 100)
        const uint8_t rate500[6] = {0x5A, 0x06, 0x03, 0x0A, 0x00, 0x6D};
        for (int i = 0;  i < 6;  i++) {
            write(rate500[i]);
        }
        // save the refresh rate, must wait 1 second after this for the sensor to come back online
        const uint8_t save_setting[5] = {0x5A, 0x04, 0x11, 0x6F};
        for (int i = 0;  i < 5;  i++) {
            write(save_setting[i]);
        }
        flush();
    }

    void loop() override {
        update();
    }

    void update() {
        if (!available()) return;
        if (rec_debug_state == 0x01) {
            uart_value[0] = read();
            if (uart_value[0] == HEADER) {
                check = uart_value[0];
                rec_debug_state = 0x02;
            }
        }
        else if (rec_debug_state == 0x02) {
            uart_value[1] = read();
            if (uart_value[1] == HEADER) {
                check += uart_value[1];
                rec_debug_state = 0x03;
            }
            else {
                rec_debug_state = 0x01;
            }
        }
        else if (rec_debug_state == 0x03) {
            uart_value[2] = read();
            check += uart_value[2];
            rec_debug_state = 0x04;
        }
        else if (rec_debug_state == 0x04) {
            uart_value[3] = read();
            check += uart_value[3];
            rec_debug_state = 0x05;
        }
        else if (rec_debug_state == 0x05) {
            uart_value[4] = read();
            check += uart_value[4];
            rec_debug_state = 0x06;
        }
        else if (rec_debug_state == 0x06) {
            uart_value[5] = read();
            check += uart_value[5];
            rec_debug_state = 0x07;
        }
        else if (rec_debug_state == 0x07) {
            uart_value[6] = read();
            check += uart_value[6];
            rec_debug_state = 0x08;
        }
        else if (rec_debug_state == 0x08) {
            uart_value[7] = read();
            check += uart_value[7];
            rec_debug_state = 0x09;
        }
        else if (rec_debug_state == 0x09) {
            uart_value[8] = read();
            if (uart_value[8] == check) {
                distance = uart_value[2] + uart_value[3]*256;
                int strength = uart_value[4] + uart_value[5]*256;
                float temprature = uart_value[6] + uart_value[7] *256;
                temprature = temprature/8 - 256;                              
                publish_state(distance); 
                //while (available()) {
                //    read();
                //}
            }
            rec_debug_state = 0x01;
        }
    }
};