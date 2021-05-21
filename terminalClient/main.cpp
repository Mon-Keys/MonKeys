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

  double dWidth =
      cap.get(cv::CAP_PROP_FRAME_WIDTH);  // get the width of frames of the video
  double dHeight =
      cap.get(cv::CAP_PROP_FRAME_HEIGHT);  // get the height of frames of the video

  std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

  cv::namedWindow("MyVideo", cv::WINDOW_AUTOSIZE);  // create a window called "MyVideo"

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
          std::cout << symbol->get_data() << "\n";
        // send http request to the server
        net::io_context ioc;
        std::make_shared<TerminalSession>(ioc)->run(
            "127.0.0.2", "8181", "/checktimecode", 11, symbol->get_data());
        ioc.run();
        previousCode = symbol->get_data();
      }

      //   cout << "decoded " << symbol->get_type_name() << " symbol \""
      //    << symbol->get_data() << '"' << " " << endl;
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

      // cout<<"Angle: "<<r.angle<<endl;
    }

    cv::imshow("MyVideo", frame);  // show the frame in "MyVideo" window

    if (cv::waitKey(30) == 27)  // wait for 'esc' key press for 30ms. If 'esc' key
                            // is pressed, break loop
    {
      std::cout << "esc key is pressed by user" << std::endl;
      break;
    }
  }
  return EXIT_SUCCESS;

  // Check command line arguments.
  //   if (argc != 4 && argc != 5) {
  //     std::cerr << "Usage: http-client-async <host> <port> <target> [<HTTP "
  //                  "version: 1.0 or 1.1(default)>]\n"
  //               << "Example:\n"
  //               << "    http-client-async www.example.com 80 /\n"
  //               << "    http-client-async www.example.com 80 / 1.0\n";
  //     return EXIT_FAILURE;
  //   }
  //   auto const host = argv[1];
  //   auto const port = argv[2];
  //   auto const target = argv[3];
  //   int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;

  //   // The io_context is required for all I/O
  //   net::io_context ioc;

  //   // Launch the asynchronous operation
  //   std::make_shared<TerminalSession>(ioc)->run(host, port, target, version);
  //   // std::make_shared<Session>(ioc)->run("127.0.0.1", "8080", "/auth", 11);

  //   // Run the I/O service. The call will return when
  //   // the get operation is complete.
  //   ioc.run();

  //   return EXIT_SUCCESS;
}
