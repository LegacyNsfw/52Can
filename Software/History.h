class History
{
private:
  int size;
  uint16_t *buffer;
  int currentIndex;

public:
  History(int _size)
  {
    size = _size;
    buffer = new uint16_t[_size];
    currentIndex = 0;
  }
  
  ~History()
  {
    delete[] buffer;
  }

  void initialize();

  void debug();

  uint16_t get(int index)
  {
    int start = currentIndex;
    int actualIndex = start - index;
    if (actualIndex < 0)
    {
      actualIndex += size;
    }
    return buffer[actualIndex];
  }

  int push(uint16_t value)
  {
    if (buffer == nullptr || size == 0) {
      Serial.println("ERROR: Cannot push to null buffer!");
      return -1;
    }
    
    currentIndex++;
    if (currentIndex >= size)
    {
      currentIndex = 0;
    }

    buffer[currentIndex] = value;
    return currentIndex;
  }
};

void TestHistory();