#include "tracking.h"
#include "ui_tracking.h"

using namespace std;
using namespace cv;

tracking::tracking(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tracking)
{
    ui->setupUi(this);
}

tracking::~tracking()
{
    delete ui;
}

void tracking::on_pushButton_clicked()
{
    int count;
    double area, ar;
    Mat frame, fore, img, prevImg, temp, gray, vehicle_ROI, img_temp;

    // Read video file from file (.avi) or using webcam (cap(0))
    VideoCapture cap("./data/vtest.avi");
    //    VideoCapture cap(0);

    // Create a backgroundsubtractor and foreground contour
    Ptr<BackgroundSubtractor> pMOG2;
    pMOG2 = createBackgroundSubtractorMOG2();
    vector<vector<Point> > contours;

    // Start Reading video frame
    while(true)
    {
        count=0;
        cap >> frame;

        // Image preprocessing by bilateral filter
        cvtColor(frame, gray, CV_BGR2GRAY);
        gray.convertTo(temp, CV_8U);
        bilateralFilter(temp, img, 5, 20, 20);

        // Updating background
        pMOG2->apply(img, fore);

        // Process contour
        erode(fore,fore,Mat());
        dilate(fore,fore,Mat());
        findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

        vector<vector<Point> > contours_poly(contours.size());
        vector<Rect> boundRect(contours.size());

        for(size_t i = 0; i < contours.size(); i++ )
        {
            // Find a better contour to fit the object
            approxPolyDP( Mat(contours[i]), contours_poly[i], 10, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            rectangle( frame, boundRect[i].tl(), boundRect[i].br(), Scalar(255,0,0), 2, 8, 0 );

            // Filter the object with bounding box area
            vehicle_ROI = img(boundRect[i]);
            area = contourArea(contours[i], false);
            ar = vehicle_ROI.cols/vehicle_ROI.rows;
            if(area > 450 && ar > 0.8)
            {
                count=count+1;

            }
        }

        // Show and draw the filtered result on image
        string s = std::to_string(count);
        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 2;
        int thickness = 3;
        cv::Point textOrg(10, 130);
        cv::putText(frame, s, textOrg, fontFace, fontScale, Scalar(0,255,0), thickness,5);

        // Feature tracking used for Object Identification
        //        int win_size = 10;
        //        int maxCorners = 200;
        //        double qualityLevel = 0.01;
        //        double minDistance = 1;
        //        int blockSize = 3;
        //        double k = 0.04;
        //        vector<Point2f> img_corners;
        //        img_corners.reserve(maxCorners);
        //        vector<Point2f> prevImg_corners;
        //        prevImg_corners.reserve(maxCorners);

        //        goodFeaturesToTrack(img, img_corners, maxCorners,qualityLevel,minDistance,Mat(),blockSize,true);

        //        cornerSubPix( img, img_corners, Size( win_size, win_size ), Size( -1, -1 ),
        //                      TermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03 ) );

        //        vector<uchar> features_found;
        //        features_found.reserve(maxCorners);
        //        vector<float> feature_errors;
        //        feature_errors.reserve(maxCorners);
        //        calcOpticalFlowPyrLK( img, prevImg, img_corners, prevImg_corners, features_found, feature_errors ,
        //                              Size( win_size, win_size ), 3,
        //                              cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3 ), 0, k);
        //        for( int i=0; i < features_found.size(); i++ ){
        //            Point2f p0( ceil( img_corners[i].x ), ceil( img_corners[i].y ) );
        //            Point2f p1( ceil( prevImg_corners[i].x ), ceil( prevImg_corners[i].y ) );
        //            line( frame, p0, p1, CV_RGB(255,0,0), 5 );
        //        }
        //        prevImg = img;

        imshow("Frame",frame);  // Tracking result
        imshow("FORE",fore);    // Foreground

        if(frame.rows == 0 || frame.cols == 0)
            break;
        cv::waitKey(33);
    }
}

void tracking::on_pushButton_2_clicked()
{
    cv::Mat frame;
    cv::Rect2d roi;

    // Create a tracker using KCF algorithm
    cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();

    // Read video
    std::string filename = "./data/faceocc2.webm";
    //    cv::VideoCapture cap(0);
    cv::VideoCapture cap(filename);

    // Initialize object location manually
    cap >> frame;
    roi = cv::selectROI("tracker", frame);
    tracker->init(frame, roi);
    qDebug() << "open video";

    // Start reading video
    while(1){
        cap >> frame;
        if(frame.rows == 0 || frame.cols == 0)  break;

        // Update tracker using current roi
        tracker->update(frame, roi);
        cv::rectangle(frame, roi, cv::Scalar(255, 0, 0), 2, 1);
        cv::imshow("video", frame);
        cv::waitKey(33);
    }
}
