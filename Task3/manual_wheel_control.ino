#define NUM_CHANNELS 8
#define SERIAL_BUFFER_SIZE 64

int channels[NUM_CHANNELS];
char serialBuffer[SERIAL_BUFFER_SIZE];
int bufferIndex = 0;
bool insidePacket = false;

void readChannel() {
  while (Serial1.available() > 0) {
    char incomingChar = Serial1.read();

    if (incomingChar == '<') {
      bufferIndex = 0;
      insidePacket = true;
      continue;
    }

    if (insidePacket) {
      if (incomingChar == '>') {
        serialBuffer[bufferIndex] = '\0';
        parsePacket(serialBuffer);
        insidePacket = false;
        bufferIndex = 0;
      }
      else if (bufferIndex < SERIAL_BUFFER_SIZE - 1) {
        serialBuffer[bufferIndex] = incomingChar;
        bufferIndex++;
      } else {
        insidePacket = false;
        bufferIndex = 0;
      }
    }
  }
}

void parsePacket(char* packetString) {
  char* token = strtok(packetString, " ");
  int chanIndex = 0;

  while (token != NULL && chanIndex < NUM_CHANNELS) {
    channels[chanIndex] = atoi(token);
    chanIndex++;
    token = strtok(NULL, " ");
  }
}