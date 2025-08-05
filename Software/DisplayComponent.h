class DisplayComponent
{
public:
  void initialize();
  void draw(History *pHistory, int temperature);
private:
  void drawHistory(History *pHistory, uint16_t temperature);
};
