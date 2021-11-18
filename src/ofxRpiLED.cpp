#include "ofxRpiLED.h"


// Constructor
ofxRpiLED::ofxRpiLED() {}

// Desonstructor
ofxRpiLED::~ofxRpiLED() {
    off_screen_canvas->Clear();
    matrix->Clear();
    delete matrix;
}

void ofxRpiLED::setup(std::string hardwareMapping, int columns, int rows, int chain, int parallel, int brightness, int gpioSlowdown) {
	/*
	* Set up GPIO pins. This fails when not running as root.
	*/
    
    rgb_matrix::RGBMatrix::Options options;
    rgb_matrix::RuntimeOptions runtime;
    
    options.hardware_mapping = hardwareMapping.c_str();
    options.rows = rows; // Default
    options.cols = columns; // Default
    options.chain_length = chain;
    options.parallel = parallel;
    options.brightness = brightness;
    // options.pixel_mapper_config = "Rotate:270";
    runtime.gpio_slowdown = gpioSlowdown;
    
    matrix = CreateMatrixFromOptions(options, runtime);
    if (matrix == NULL) {
        cout << "Creating matrix failed!" << endl;
        exit(1);
    }
    
	/* 
	* Clear and cache size 
	*/
	
    //	canvas->Fill(0,0,0);
	cW = matrix->width();
	cH = matrix->height();
    
    off_screen_canvas = matrix->CreateFrameCanvas();

}

void ofxRpiLED::clear(){
	matrix->Clear();
}

void ofxRpiLED::draw(ofPixels &p){
	int w = cW > p.getWidth()  ? cW : p.getWidth();
	int h = cH > p.getHeight() ? cH : p.getHeight();	
	for (unsigned int x = 0; x < w; x++) {
		for (unsigned int y = 0; y < h; y++) {
			ofColor c = p.getColor(x, y);
            off_screen_canvas->SetPixel(x, y, c.r, c.g, c.b);
		}
	}
    off_screen_canvas = matrix->SwapOnVSync(off_screen_canvas);
}

void ofxRpiLED::draw(ofImage &i){
	int w = cW > i.getWidth()  ? cW : i.getWidth();
	int h = cH > i.getHeight() ? cH : i.getHeight();	
	for (unsigned int x = 0; x < w; x++) {
		for (unsigned int y = 0; y < h; y++) {
			ofColor c = i.getColor(x, y);
            off_screen_canvas->SetPixel(x, y, c.r, c.g, c.b);
		}
	}
    off_screen_canvas = matrix->SwapOnVSync(off_screen_canvas);
}
