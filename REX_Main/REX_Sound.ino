// REX_Sound.ino
// Arduino Giga R1 code to play music and voice files on R.E.X. Model 1
// COMP444 - Shane Castle #2621506 - August, 2023

// based on Arduino.cc sample code

#include <Arduino_AdvancedAnalog.h>
#include <DigitalOut.h>
#include <FATFileSystem.h>

AdvancedDAC dac1(A12);
int sample_size = 0;
int samples_count = 0;

struct wav_header_t {
  char chunkID[4];              //"RIFF" = 0x46464952
  unsigned long chunkSize;      //28 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes] + sum(sizeof(chunk.id) + sizeof(chunk.size) + chunk.size)
  char format[4];               //"WAVE" = 0x45564157
  char subchunk1ID[4];          //"fmt " = 0x20746D66
  unsigned long subchunk1Size;  //16 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
  unsigned short audioFormat;
  unsigned short numChannels;
  unsigned long sampleRate;
  unsigned long byteRate;
  unsigned short blockAlign;
  unsigned short bitsPerSample;
};

wav_header_t header;

//Find the data section of the WAV file.
struct chunk_t {
  char ID[4];
  unsigned long size;
};

char msg[64] = { 0 };
chunk_t chunk;
char fullFilename[255] = { 0 };

// play 16-bit PCM Mono 16kHz realigned files
void playSoundFile(const char *filename) {
  logDebug("[SOUND] Starting sound");

  // 16-bit PCM Mono 16kHz realigned noise reduction
  snprintf(fullFilename, sizeof(fullFilename), "/USB_DRIVE/%s", filename);
  logDebug("[SOUND] Opening audio file " + String(fullFilename));
  file = fopen(fullFilename, "rb");
  if (file == nullptr) {
    logDebug("[SOUND] Error opening audio file: " + String(strerror(errno)));
    delay(5000);
    return;
  }

  logDebug("[SOUND] Reading audio header ...");
  fread(&header, sizeof(header), 1, file);

  //showHeaderInfo();
  findDataChunk();

  // Configure the advanced DAC.
  logDebug("[SOUND] Setting up DAC1");
  dac1.stop();
  if (!dac1.begin(AN_RESOLUTION_12, header.sampleRate, 256, 16)) {
    logDebug("[SOUND] Failed to start DAC1 !");
    return;
  }

  writeDataToBuffer();

  logDebug("[SOUND] Done playing file. Closing file");
  if (feof(file)) {
    fclose(file);
  }
}

void findDataChunk() {
  while (true) {
    fread(&chunk, sizeof(chunk), 1, file);
    snprintf(msg, sizeof(msg), "[SOUND] %c%c%c%c\t"
                               "%li",
             chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
    //Serial.println(msg);
    if (*(unsigned int *)&chunk.ID == 0x61746164)
      break;
    // Skip chunk data bytes.
    fseek(file, chunk.size, SEEK_CUR);
  }

  // Determine number of samples.
  sample_size = header.bitsPerSample / 8;
  samples_count = chunk.size * 8 / header.bitsPerSample;
  snprintf(msg, sizeof(msg), "[SOUND] Sample size = %i", sample_size);
  logDebug(msg);
  snprintf(msg, sizeof(msg), "[SOUND] Samples count = %i", samples_count);
  logDebug(msg);
}

void writeDataToBuffer() {
  logDebug("[SOUND] DAC1 available: " + String(dac1.available()));
  logDebug("[SOUND] File eof:" + String(feof(file)));

  if (dac1.available() && !feof(file)) {
    logDebug("[SOUND] Playing sound file");
    while (!feof(file)) {
      /* Read data from file. */
      uint16_t sample_data[256] = { 0 };
      fread(sample_data, sample_size, 256, file);

      /* Get a free buffer for writing. */
      SampleBuffer buf = dac1.dequeue();

      /* Write data to buffer. */
      for (size_t i = 0; i < buf.size(); i++) {
        /* Scale down to 12 bit. */
        uint16_t const dac_val = ((static_cast<unsigned int>(sample_data[i]) + 32768) >> 4) & 0x0fff;
        buf[i] = dac_val;
      }

      /* Write the buffer to DAC. */
      dac1.write(buf);
    }
  } else {
    logDebug("Error playing Sound file");
    logDebug("DAC1 available: " + String(dac1.available()));
    logDebug("File eof:" + String(feof(file)));
  }
}

void showHeaderInfo() {
  Serial.println("[SOUND] WAV File Header read:");
  snprintf(msg, sizeof(msg), "File Type: %s", header.chunkID);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "File Size: %ld", header.chunkSize);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "WAV Marker: %s", header.format);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "Format Name: %s", header.subchunk1ID);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "Format Length: %ld", header.subchunk1Size);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "Format Type: %hd", header.audioFormat);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "Number of Channels: %hd", header.numChannels);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "Sample Rate: %ld", header.sampleRate);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "Sample Rate * Bits/Sample * Channels / 8: %ld", header.byteRate);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "Bits per Sample * Channels / 8: %hd", header.blockAlign);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "Bits per Sample: %hd", header.bitsPerSample);
  Serial.println(msg);
  snprintf(msg, sizeof(msg), "[SOUND] id\t"
                             "size");
  logDebug(msg);
}
