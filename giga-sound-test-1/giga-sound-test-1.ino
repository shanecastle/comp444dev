#include "AdvancedDAC.h"

AdvancedDAC dac1(A12);

void setup() {
  // put your setup code here, to run once:

  if (!dac1.begin(AN_RESOLUTION_12, 8000, 32, 64)) {
    Serial.println("Failed to start DAC!");
    while (1)
      ;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if (dac1.available()) {

    // Get a free buffer for writing
    SampleBuffer buf = dac1.dequeue();

    // Write data to buffer (this is really loud and screachy, careful about your ears.)
    for (int i = 0; i < buf.size(); i++) {
      buf.data()[i] = (i % 2 == 0) ? 0 : 0xfff;
    }

    // Write the buffer data to DAC
    dac1.write(buf);
  }
}
