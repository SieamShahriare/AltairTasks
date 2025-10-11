// Assuming that fact that the handleInterrupt fucntion was written seperately

Encoder::Encoder(int pinA, int pinB) : pinA(pinA), pinB(pinB), currentPosition(0), prevState(0) {
    Encoder::instance = this;
}

void Encoder::attach() {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    prevState = digitalRead(pinA);

    attachInterrupt(digitalPinToInterrupt(pinA), Encoder::handleInterrupt, CHANGE);
}

int Encoder::read() {
    return currentPosition;
}