class MockAfrData
{
public:
    uint16_t value1;
    int rise1;

    uint16_t value2;
    int rise2;

    int16_t delta;


    MockAfrData() {
    }

    void initialize();

    void loop();
};