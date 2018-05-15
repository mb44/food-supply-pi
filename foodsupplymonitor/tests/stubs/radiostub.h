#ifndef RF24_ADAPTER_H
#define RF24_ADAPTER_H

#include "../../../RF24.h"
#include "../../radio/iradio.h"

#define MIN_PAYLOAD_SIZE 1
#define MAX_RCV_PAYLOAD_SIZE 7
#define MAX_SEND_PAYLOAD_SIZE 7
#define PAYLOAD_SIZE_INCREMENTS_BY 1
#define NEXT_PAYLOAD_SIZE 1

class RadioStub : public IRadio {
  private:
    int minPayloadSize;
    int maxPayloadSize;
    int payloadSizeIncrementsBy;
    int nextPayloadSize;
    uint64_t radioPipes[2];
    // Adapting to this radio
    char receivePayload[MAX_RCV_PAYLOAD_SIZE+1];
    void setupRadio();

  public:
    char sendPayload[MAX_SEND_PAYLOAD_SIZE+1];

    RadioStub(const uint64_t pipes[2]);
    ~RadioStub();
    uint8_t receive(int *scaleId, uint8_t *messageType, int *data) override;
    uint8_t setUpdateFrequency(const int scaleId, const int updateFrequency) override;
    uint8_t powerDown(const int scaleId) override;
};

#endif  // RF24_ADAPTER_H 
