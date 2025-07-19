class History
{
private:
  int size;
  int *buffer;
  int currentIndex;

public:
  History(int _size)
  {
    size = _size;
    buffer = new int[size];
    currentIndex = 0;
  }

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
    currentIndex++;
    if (currentIndex == size)
    {
      currentIndex = 0;
    }
    buffer[currentIndex] = value;
  }
};

void TestHistory();