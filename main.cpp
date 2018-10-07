#include <stdio.h>
#include <cmath>
#include <math.h>

#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat src_8uc3_img = cv::imread( "/Users/tugrulbayrak/Desktop/ImageProcessing/Exercise1/Exercise1/images/valve.png", CV_LOAD_IMAGE_COLOR );

    if (src_8uc3_img.empty()) {
        printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
    }

    cv::Mat gray_src_8uc1_img;
    cv::cvtColor(src_8uc3_img, gray_src_8uc1_img, CV_BGR2GRAY);

    cv::Mat gray_32fc1_img;
    gray_src_8uc1_img.convertTo(gray_32fc1_img,CV_32FC1, 1.0 / 255.0);

    cv::Mat dst;
    //cv::Mat dst = gray_32fc1_img.clone();
    gray_32fc1_img.copyTo(dst);

    for(int k = 0 ; k<1000 ; k++) {

    for (int i = 1;i<gray_32fc1_img.rows-1;i++){
        for (int j = 1;j<gray_32fc1_img.cols-1;j++){
         float cN, cS, cE, cW;
         float deltacN, deltacS, deltacE, deltacW;

         deltacN = dst.at<float>(i,j-1) - dst.at<float>(i,j);
         deltacS = dst.at<float>(i,j+1) - dst.at<float>(i,j);
         deltacE = dst.at<float>(i+1,j) - dst.at<float>(i,j);
         deltacW = dst.at<float>(i-1,j) - dst.at<float>(i,j);

         cN = abs(exp(-1 * (deltacN * deltacN / (0.015 * 0.015) )));
         cS = abs(exp(-1 * (deltacS * deltacS / (0.015 * 0.015) )));
         cE = abs(exp(-1 * (deltacE * deltacE / (0.015 * 0.015) )));
         cW = abs(exp(-1 * (deltacW * deltacW / (0.015 * 0.015) )));

         dst.at<float>(i,j) =  dst.at<float>(i,j) * ( 1 - 0.1 *(cN + cS + cE + cW)  )+
                   0.1 *( cN * dst.at<float>(i,j-1) + cS * dst.at<float>(i,j+1)
                        + cE * dst.at<float>(i+1,j) + cW * dst.at<float>(i-1,j) );
        }
    }

 }

    cv::imshow( "Original Valve gray", gray_32fc1_img);
    cv::imshow( "Filtered Valve gray", dst);

    cv::waitKey( 0 ); // wait until keypressed

    return 0;
}
