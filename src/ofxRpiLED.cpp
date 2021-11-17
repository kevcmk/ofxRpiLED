#include "ofxRpiLED.h"


// Constructor
ofxRpiLED::ofxRpiLED() {}

// Desonstructor
ofxRpiLED::~ofxRpiLED() {
	canvas->Clear();
	delete canvas;
}

void ofxRpiLED::setup() {
    RGBMatrix::Options options;
    rgb_matrix::RuntimeOptions runtime;
    options.hardware_mapping = "adafruit-hat";
    options.rows = 32; // A 32x32 display. Use 16 when this is a 16x32 display.
    options.chain_length = 4; // Number of boards chained together.
    options.parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
    options.brightness = 50;
    setup(options, runtime);
}

void ofxRpiLED::setup(int _rows, int _chain, int _parallel) {
    RGBMatrix::Options options;
    rgb_matrix::RuntimeOptions runtime;
    options.hardware_mapping = "adafruit-hat";
    options.rows = _rows; // A 32x32 display. Use 16 when this is a 16x32 display.
    options.chain_length = _chain; // Number of boards chained together.
    options.parallel = _parallel; // Number of chains in parallel (1..3). > 1 for plus or Pi2
    options.brightness = 50;
    setup(options, runtime);
}

void ofxRpiLED::setup(RGBMatrix::Options options, rgb_matrix::RuntimeOptions runtime) {
	/*
	* Set up GPIO pins. This fails when not running as root.
	*/
    RGBMatrix * matrix = CreateMatrixFromOptions(options, runtime);
    if (matrix == NULL) {
        cout << "Creating matrix failed!" << endl;
        exit(1);
    }
    
    canvas = matrix; // Downcast to canvas;
	/* 
	* Clear and cache size 
	*/
	
	canvas->Fill(0,0,0);
	cW = canvas->width();
	cH = canvas->height();
}

void ofxRpiLED::clear(){
	canvas->Clear();
}

void ofxRpiLED::draw(ofPixels &p){
	int w = cW > p.getWidth()  ? cW : p.getWidth();
	int h = cH > p.getHeight() ? cH : p.getHeight();	
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			ofColor c = p.getColor(x, y);
			canvas->SetPixel(x, y, c.r, c.g, c.b);
		}
	}	
}

void ofxRpiLED::draw(ofImage &i){
	int w = cW > i.getWidth()  ? cW : i.getWidth();
	int h = cH > i.getHeight() ? cH : i.getHeight();	
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			ofColor c = i.getColor(x, y);
			canvas->SetPixel(x, y, c.r, c.g, c.b);
		}
	}	
}
