class DisplayComponent
{
public:
  void initialize();

#ifdef GAUGE_DUAL_AFR_MOCK_DATA || GAUGE_DUAL_AFR  
public:
  void draw(History *pLeftHistory, History *pRightHistory);
private:  
  void drawHistory(History *pHistory, int color);
#endif

#ifdef COMBINATION_ALARM  
public:
  void draw(int temperature, int pressure, int knock);
#endif  
};

// Not sure why this is necessary, but it seems to be a bug in the library.
#define WTF_BLACK RGB565_WHITE
#define WTF_WHITE RGB565_BLACK
#define WTF_GREEN RGB565_RED
#define WTF_BLUE RGB565_GREEN
#define WTF_GREY RGB565_LIGHTGREY

