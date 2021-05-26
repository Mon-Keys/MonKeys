// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include <zbar.h>

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "terminalClient.hpp"

// using namespace cv;
// using namespace std;
// using namespace zbar;

int main(int argc, char **argv) {
  createConfigFile();

  cv::VideoCapture cap(0);  // open the video camera no. 0

  // cap.set(CV_CAP_PROP_FRAME_WIDTH,800);
  // cap.set(CV_CAP_PROP_FRAME_HEIGHT,640);

  if (!cap.isOpened())  // if not success, exit program
  {
    std::cout << "Cannot open the video cam" << std::endl;
    return -1;
  }

  zbar::ImageScanner scanner;
  scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

  double dWidth = cap.get(
      cv::CAP_PROP_FRAME_WIDTH);  // get the width of frames of the video
  double dHeight = cap.get(
      cv::CAP_PROP_FRAME_HEIGHT);  // get the height of frames of the video

  std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

  cv::namedWindow("MyVideo",
                  cv::WINDOW_AUTOSIZE);  // create a window called "MyVideo"

  std::string previousCode = "";
  while (1) {
    cv::Mat frame;

    bool bSuccess = cap.read(frame);  // read a new frame from video

    if (!bSuccess)  // if not success, break loop
    {
      std::cout << "Cannot read a frame from video stream" << std::endl;
      break;
    }

    cv::Mat grey;
    cv::cvtColor(frame, grey, cv::COLOR_BGR2GRAY);

    int width = frame.cols;
    int height = frame.rows;
    uchar *raw = (uchar *)grey.data;
    // wrap image data
    zbar::Image image(width, height, "Y800", raw, width * height);
    // scan the image for barcodes
    int n = scanner.scan(image);
    // extract results
    for (zbar::Image::SymbolIterator symbol = image.symbol_begin();
         symbol != image.symbol_end(); ++symbol) {
      std::vector<cv::Point> vp;
      // do something useful with results

      // save current code for stop requesting if prev and current code are
      // equal
      if (std::strcmp(previousCode.c_str(), symbol->get_data().c_str())) {
        // send http request to the server
        net::io_context ioc;
        std::make_shared<TerminalSession>(ioc)->run(
            "192.168.1.69", "8181", "/checktimecode", 11, symbol->get_data());
        ioc.run();
        previousCode = symbol->get_data();
      }
      int n = symbol->get_location_size();
      for (int i = 0; i < n; i++) {
        vp.push_back(
            cv::Point(symbol->get_location_x(i), symbol->get_location_y(i)));
      }
      cv::RotatedRect r = minAreaRect(vp);
      cv::Point2f pts[4];
      r.points(pts);
      for (int i = 0; i < 4; i++) {
        cv::line(frame, pts[i], pts[(i + 1) % 4], cv::Scalar(255, 0, 0), 3);
      }
    }

    cv::imshow("MyVideo", frame);  // show the frame in "MyVideo" window

    if (cv::waitKey(30) == 27)  // wait for 'esc' key press for 30ms. If 'esc'
                                // key is pressed, break loop
    {
      std::cout << "esc key is pressed by user" << std::endl;
      break;
    }
  }
  return EXIT_SUCCESS;
}
