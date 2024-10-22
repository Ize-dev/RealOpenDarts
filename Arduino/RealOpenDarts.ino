//This is for an 8x8 Dart-Matrix, adjust accordingly
//The Output will be in the form of "2,4" meaning the lines which are connected to your arduino / esp32 on GPIO 2 & 4 made a connection
//In the Dart-software you just have to map the board accordingly so for example 2,4 = Tripple 20, 1,9 = Bullseye etc.

int masterLines = 8; //Change here to the number of lines of your Master Layer
int slaveLines = 8; //Change here to the number of lines of your Slave Layer

int matrixMaster[] = {23, 22, 19, 18, 5, 17, 16, 4}; //Put here the pins you connected the lines of your Master Layer
int matrixSlave[] = {12, 14, 27, 26, 25, 33, 32, 13}; //Put here the pins you connected the lines of your Slave Layer

#include "BluetoothSerial.h"  // Header-File for Bluetooth Serial

BluetoothSerial SerialBT;     // Create new Bluetooth-Serial-Instance

void setup() {
    Serial.begin(115200);
    Serial.println("RealOpenDarts"); //This line is not necessary, is just here for debug purposes

    for(int i = 0; i < slaveLines; i++){
        pinMode(matrixSlave[i], INPUT_PULLUP);
    }

    for(int i = 0; i < masterLines; i++){
        pinMode(matrixMaster[i], OUTPUT);
        digitalWrite(matrixMaster[i], HIGH);
    }

    SerialBT.begin("RealOpenDarts"); // Start bluetooth with devicename "RealOpenDarts"
    Serial.println("Ready.");
}

void loop() {
    for(int i = 0; i < masterLines; i++){
        digitalWrite(matrixMaster[i], LOW);
        for(int j = 0; j < slaveLines; j++){
            if(digitalRead(matrixSlave[j]) == LOW){
                Serial.print(j);
                Serial.print(",");
                Serial.println(i);
                String msg = String(j) + "," + String(i);
                SerialBT.println(msg);     // Send data via bluetooth
                Serial.println("Send: " + msg);
                delay(500);
                break;
            }
        }
        digitalWrite(matrixMaster[i], HIGH);
    }
}
