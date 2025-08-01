class History
{
private:
  int size;
  int* buffer;
  int currentIndex;

public:
  History(int _size)
  {
    size = _size;
    buffer = new int[_size];
    currentIndex = 0;
        
    for(int i = 0; i < _size; i++) {
      buffer[i] = 0;
    }
  }
  
  ~History()
  {
    delete[] buffer;
  }

  void debug();

  int get(int index)
  {
    int start = currentIndex;
    int actualIndex = start - index;
    if (actualIndex < 0)
    {
      actualIndex += size;
    }
    return buffer[actualIndex];
  }

  int push(int value)
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