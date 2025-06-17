#include "miniMachineBLE.h"
#include <NimBLEDevice.h>
#include <ArduinoJson.h>

#define SERVICE_UUID "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcd1234-5678-90ab-cdef-1234567890ab"

static DirCallback staticDirCallback;

class MyServerCallbacks : public NimBLEServerCallbacks
{
    void onConnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo)
    {
        Serial.println("🔗 BLE conectado!");
    }
    void onDisconnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo, int reason)
    {
        Serial.println("❌ BLE desconectado!");
        NimBLEDevice::startAdvertising();
    }
};

class MyCallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *pCharacteristic, NimBLEConnInfo &connInfo)
    {
        std::string value = pCharacteristic->getValue();
        Serial.print("JSON recebido: ");
        Serial.println(value.c_str()); // <-- imprime o JSON recebido
        JsonDocument doc;
        if (deserializeJson(doc, value))
            return;
        if (doc["dir"] && staticDirCallback)
        {
            staticDirCallback(doc["dir"].as<String>());
        }
    }
};

void miniMachineBLE_begin(const char *deviceName, DirCallback cb)
{
    staticDirCallback = cb;
    NimBLEDevice::init(deviceName);
    NimBLEServer *pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    NimBLEService *pService = pServer->createService(SERVICE_UUID);
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);
    pCharacteristic->setCallbacks(new MyCallbacks());
    pService->start();
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID); // só um UUID
    pAdvertising->setName(deviceName);          // nome curto
    pAdvertising->start();
    Serial.println("🟢 BLE pronto e anunciando!");
}