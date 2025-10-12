#define NUM_CHANNELS 8

int channels[NUM_CHANNELS];
bool newDataAvailable = false;
String serialBuffer = "";
bool readingData = false;

void setup() {
    Serial.begin(115200);
    
    for (int i = 0; i < NUM_CHANNELS; i++) {
        channels[i] = 1500;
    }
}

void loop() {
    readChannel();
    
    if (newDataAvailable) {
        Serial.print("Channels: ");
        for (int i = 0; i < NUM_CHANNELS; i++) {
            Serial.print(channels[i]);
            if (i < NUM_CHANNELS - 1) {
                Serial.print(" ");
            }
        }
        Serial.println();
        newDataAvailable = false;
    }
    
    delay(10);
}

void readChannel() {
    while (Serial1.available() > 0) {
        char incomingChar = Serial1.read();
        
        if (incomingChar == '<') {
            serialBuffer = "";
            readingData = true;
        }
        else if (incomingChar == '>' && readingData) {
            processChannelData(serialBuffer);
            serialBuffer = "";
            readingData = false;
        }
        else if (readingData) {
            serialBuffer += incomingChar;
        }
    }
}

void processChannelData(String data) {
    int tempChannels[NUM_CHANNELS];
    int channelIndex = 0;
    
    int startIndex = 0;
    int endIndex = data.indexOf(' ');
    
    while (endIndex != -1 && channelIndex < NUM_CHANNELS) {
        String valueStr = data.substring(startIndex, endIndex);
        tempChannels[channelIndex] = valueStr.toInt();
        channelIndex++;
        startIndex = endIndex + 1;
        endIndex = data.indexOf(' ', startIndex);
    }
    
    if (channelIndex < NUM_CHANNELS && startIndex < data.length()) {
        String valueStr = data.substring(startIndex);
        tempChannels[channelIndex] = valueStr.toInt();
        channelIndex++;
    }
    
    if (channelIndex == NUM_CHANNELS) {
        for (int i = 0; i < NUM_CHANNELS; i++) {
            channels[i] = tempChannels[i];
        }
        newDataAvailable = true;
    }
}