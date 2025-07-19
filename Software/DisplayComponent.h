// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

#define RGB(red,green,blue) (((red & 0xf8)<<8) + ((green & 0xfc)<<3)+(blue>>3))
#define GREY      RGB(0x80, 0x80, 0x80)
#define LIGHTGREY RGB(0x40, 0x40, 0x40)
#define VERYLIGHTGREY RGB(0x20, 0x20, 0x20) // barely visible
#define LIGHTBLUE RGB(0x40, 0x40, 0xFF)

const int width = 160;
const int height = 128;

class DisplayComponent
{
public:
  void initialize();
  void draw(History *pHistory, int temperature);
private:
  void drawHistoryTop(History *pHistory, uint16_t color);
  void drawHistoryBottom(History *pHistory, uint16_t color);
};
