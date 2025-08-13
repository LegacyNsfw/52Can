class DisplayComponent
{
public:
  void initialize();

  void draw(History *pLeftHistory, History *pRightHistory);
  void drawAlarm(int value, char* label, int textColor, int backgroundColor);
  void draw(int temperature, int pressure, int knock);

private:  
  void drawHistory(History *pHistory, int color);
};

// Not sure why this is necessary, but it seems to be a bug in the library.
#define WTF_BLACK RGB565_WHITE
#define WTF_WHITE RGB565_BLACK
#define WTF_GREEN RGB565_RED
#define WTF_BLUE RGB565_GREEN
#define WTF_GREY RGB565_LIGHTGREY
#define WTF_RED RGB565_BLUE

