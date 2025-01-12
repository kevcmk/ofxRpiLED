#include "ofMain.h"
#include "../libs/rgb_matrix/include/led-matrix.h"
#include "../libs/rgb_matrix/include/graphics.h"

class ofxRpiLED {
    
private:
	int 		rows;		// A 32x32 display. Use 16 when this is a 16x32 display.
	int 		chain;		// Number of boards chained together.
	int 		parallel;	// Number of chains in parallel (1..3). > 1 for plus or Pi2
	int 		cW;
	int 		cH;
        rgb_matrix::RGBMatrix   *matrix;
        rgb_matrix::Canvas      *canvas;

public:
	ofxRpiLED();
	~ofxRpiLED();
    void setup(std::string hardwareMapping,
               int columns,
               int rows,
               int chain,
               int parallel,
               int brightness,
               int gpioSlowdown,
               std::string pixelMapperConfig = std::string(""),
               std::string ledRgbSequence = std::string("RGB")
               );
	void clear();
    uint8_t getBrightness();
    void setBrightness(uint8_t brightness);
	void draw(ofImage &i);
	void draw(ofPixels &p);
    
};
