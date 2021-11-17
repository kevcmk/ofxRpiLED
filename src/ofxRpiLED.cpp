#include "ofxRpiLED.h"


// Constructor
ofxRpiLED::ofxRpiLED() {
	rows = 32;    // A 32x32 display. Use 16 when this is a 16x32 display.
	chain = 4;    // Number of boards chained together.
	parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
}

// Desonstructor
ofxRpiLED::~ofxRpiLED() {
	canvas->Clear();
	delete canvas;
}

void ofxRpiLED::setup() {
	/*
	* Set up GPIO pins. This fails when not running as root.
	*/
	RGBMatrix::Options options;
    rgb_matrix::RuntimeOptions runtime;
/*
-e MATRIX_WIDTH=32
-e MATRIX_HEIGHT=160
-e RUN_ARG_LED_CHAIN=5
-e RUN_ARG_LED_PIXEL_MAPPER=Rotate:270
-e RUN_ARG_LED_GPIO_MAPPING=adafruit-hat
-e RUN_ARG_LED_SLOWDOWN_GPIO=2

 */
    
    options.hardware_mapping = "adafruit-hat";
    options.rows = 32;
    options.cols = 32;
    options.chain_length = 1;
    options.parallel = 1;
    options.brightness = 50;
    options.pixel_mapper_config = "Rotate:270";
        
    runtime.gpio_slowdown = 2;
    
    int argc = 0;
    char * argv[] = {const_cast<char*>("blah"),const_cast<char*>("blah"), NULL};
    
//    if (!rgb_matrix::ParseOptionsFromFlags(&argc, (char***) &argv, &options, &runtime)) {
//        cout << "Verifying parameters..." << endl;
//        rgb_matrix::PrintMatrixFlags(stderr);
//        exit(1);
//    }
    
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

void ofxRpiLED::setup(int _rows, int _chain, int _parallel){
	rows 		= _rows;
	chain 		= _chain;
	parallel 	= _parallel;
	setup();
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
