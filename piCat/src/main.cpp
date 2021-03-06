#include <ctime>
#include <iostream>
#include "raspicam_cv.h"

using namespace std;

int main(int argc, char **argv) {

	time_t timer_begin, timer_end;
	raspicam::RaspiCam_Cv Camera;
	cv::Mat image;
	int nCount = 100;

	//set capture params
	Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);

	double frameWidth	= Camera.get(CV_CAP_PROP_FRAME_WIDTH);
	double frameHeight	= Camera.get(CV_CAP_PROP_FRAME_HEIGHT);
	double format		= Camera.get(CV_CAP_PROP_FORMAT);
	double brightness	= Camera.get(CV_CAP_PROP_BRIGHTNESS);
	double contrast		= Camera.get(CV_CAP_PROP_CONTRAST);
	double saturation	= Camera.get(CV_CAP_PROP_SATURATION);
	double gain			= Camera.get(CV_CAP_PROP_GAIN);
	double exposure		= Camera.get(CV_CAP_PROP_EXPOSURE);
	double whiteBalR	= Camera.get(CV_CAP_PROP_WHITE_BALANCE_RED_V);
	double whiteBalB	= Camera.get(CV_CAP_PROP_WHITE_BALANCE_BLUE_U);
	double mode			= Camera.get(CV_CAP_PROP_MODE);

	//Open camera
	cout << "Opening Camera..." << endl;
	if (!Camera.open()) { cerr << "Error opening the camera" << endl; return -1; }

	//Start capture
	cout << "Capturing " << nCount << " frames ...." << endl;
	time(&timer_begin);
	for (int i = 0; i<nCount; i++) {
		Camera.grab();
		Camera.retrieve(image);
		if (i % 5 == 0)  cout << "\r captured " << i << " images" << std::flush;
	}
	cout << "Stop camera..." << endl;
	Camera.release();

	//show time statistics
	time(&timer_end); /* get current time; same as: timer = time(NULL)  */
	double secondsElapsed = difftime(timer_end, timer_begin);
	cout << secondsElapsed << " seconds for " << nCount << "  frames : FPS = " << (float)((float)(nCount) / secondsElapsed) << endl;

	//save image 
	cv::imwrite("raspicam_cv_image.jpg", image);
	cout << "Image saved at raspicam_cv_image.jpg" << endl;
}