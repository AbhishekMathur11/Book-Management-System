#include <iostream>
#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

using namespace std;
using namespace cv;

int main() {
    // Load the face detection model from Dlib
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();

    // Load the facial landmarks model from Dlib
    dlib::shape_predictor shapePredictor;
    dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> shapePredictor;

    // Open a camera
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Couldn't open the camera." << endl;
        return -1;
    }

    // Create a window for displaying the camera feed
    namedWindow("Face Recognition", WINDOW_NORMAL);

    while (true) {
        Mat frame;
        cap >> frame;

        // Convert OpenCV Mat to Dlib image
        dlib::cv_image<dlib::bgr_pixel> dlibImage(frame);

        // Detect faces
        std::vector<dlib::rectangle> faces = detector(dlibImage);

        // Loop over each detected face
        for (const auto& face : faces) {
            // Find the facial landmarks
            dlib::full_object_detection landmarks = shapePredictor(dlibImage, face);

            // Draw a rectangle around the face
            rectangle(frame, Point(face.left(), face.top()), Point(face.right(), face.bottom()), Scalar(0, 255, 0), 2);

            // Display the facial landmarks
            for (unsigned long i = 0; i < landmarks.num_parts(); ++i) {
                circle(frame, Point(landmarks.part(i).x(), landmarks.part(i).y()), 3, Scalar(0, 0, 255), -1);
            }

            // Add your face recognition logic here
            // You may compare the facial features with a known dataset or perform additional checks
            // For simplicity, this example only displays the face landmarks.
        }

        // Display the frame
        imshow("Face Recognition", frame);

        // Break the loop when 'Esc' key is pressed
        if (waitKey(1) == 27) {
            break;
        }
    }

    // Release the camera
    cap.release();

    // Destroy the window
    destroyWindow("Face Recognition");

    return 0;
}
