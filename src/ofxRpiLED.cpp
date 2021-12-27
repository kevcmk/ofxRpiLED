#include "ofxRpiLED.h"
#include <stdexcept>

// Constructor
ofxRpiLED::ofxRpiLED() {}

// Desonstructor
ofxRpiLED::~ofxRpiLED() {
    matrix->Clear();
    delete matrix;
}

void ofxRpiLED::setup(std::string hardwareMapping, int columns, int rows, int chain, int parallel, int brightness, int gpioSlowdown, std::string pixelMapperConfig, std::string ledRgbSequence) {
    
    rgb_matrix::RGBMatrix::Options options;
    rgb_matrix::RuntimeOptions runtime;
    
    const std::string::size_type hardwareMappingSize = hardwareMapping.size();
    char *hardwareMappingBuffer = new char[hardwareMappingSize + 1]; //we need extra char for NUL
    memcpy(hardwareMappingBuffer, hardwareMapping.c_str(), hardwareMappingSize + 1);
    // This looks like it gets prematurely deallocated without a copy
    options.hardware_mapping = hardwareMappingBuffer; // {hardware_mapping = 0x8358d0 "\030\270>\266",
    
    options.rows = rows; // Default
    options.cols = columns; // Default
    options.chain_length = chain;
    options.parallel = parallel;
    options.brightness = brightness;
    
    const std::string::size_type pixelMapperConfigSize = pixelMapperConfig.size();
    char *pixelMapperConfigBuffer = new char[pixelMapperConfigSize + 1]; //we need extra char for NUL
    memcpy(pixelMapperConfigBuffer, pixelMapperConfig.c_str(), pixelMapperConfigSize + 1);
    // This looks like it gets prematurely deallocated without a copy
    options.pixel_mapper_config = pixelMapperConfigBuffer;
    
    runtime.gpio_slowdown = gpioSlowdown;
    
    std::string err = "";
    if (!options.Validate(&err)) {
        throw new std::invalid_argument("Invalid LED Options: " + err);
    };
    
    matrix = rgb_matrix::CreateMatrixFromOptions(options, runtime);
    if (matrix == NULL) {
        cout << "Creating matrix failed!" << endl;
        exit(1);
    }
    
    cW = matrix->width();
    cH = matrix->height();

    matrix->Fill(0,0,0);
    
    off_screen_canvas = matrix->CreateFrameCanvas();
    
    canvas = matrix;

}

void ofxRpiLED::clear(){
	matrix->Clear();
}

void ofxRpiLED::draw(ofPixels &p){
	int w = cW > p.getWidth()  ? cW : p.getWidth();
	int h = cH > p.getHeight() ? cH : p.getHeight();	
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			ofColor c = p.getColor(x, y);
            matrix->SetPixel(x, y, c.r, c.g, c.b);
		}
	}
}

void ofxRpiLED::draw(ofImage &i){
	int w = cW > i.getWidth()  ? cW : i.getWidth();
	int h = cH > i.getHeight() ? cH : i.getHeight();	
	for (int x = 0; x < w; x++) {
		for (unsigned int y = 0; y < h; y++) {
			ofColor c = i.getColor(x, y);
            matrix->SetPixel(x, y, c.r, c.g, c.b);
		}
	}
}
