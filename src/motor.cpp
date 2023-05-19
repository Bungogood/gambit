#include <Arduino.h>
#include "motor.hpp"

Motor::Motor(int enablePin, int dirPin, int stepPin, int stepsPerRevolution)
    : enablePin(enablePin), dirPin(dirPin), stepPin(stepPin), stepsPerRevolution(stepsPerRevolution)
{
    pinMode(enablePin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    disable();
    setDirection(CW);
}

void Motor::stepInit() {
    digitalWrite(stepPin, HIGH);
}

void Motor::stepEnd() {
    digitalWrite(stepPin, LOW);
    position += direction ? 1 : -1;
}

/**
 * @brief Motor moves one step
 * 
 * @param interval 
 */
void Motor::step(int interval) {
    stepInit();
    delayMicroseconds(1000);
    stepEnd();
    delayMicroseconds(1000);
}

/**
 * @brief Steps the motor a certain amount of steps
 * 
 * @param steps number of steps to take
 * @param interval
 */
void Motor::steps(int steps, int interval) {
    enable();
    for(int i = 0; i < steps; i++) {
        step(interval);
    }
}

/**
 * @brief Sets the direction of the motor
 * 
 * @param dir true being clockwise, false being counter-clockwise
 */
void Motor::setDirection(bool dir) {
    digitalWrite(dirPin, dir);
    direction = dir;
}
