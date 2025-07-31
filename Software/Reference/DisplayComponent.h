class DisplayComponent
{
public:
  void initialize();
  void draw(History *pHistory, int temperature);
private:
  void drawHistoryTop(History *pHistory, uint16_t color);
  void drawHistoryBottom(History *pHistory, uint16_t color);
};
