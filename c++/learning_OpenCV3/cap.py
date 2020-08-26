import numpy as np
import cv2 as cv

if __name__ == "__main__":
    # 'vtest.avi'
    video="c++/learning_OpenCV3/file/video/v_test.mp4"
    cap = cv.VideoCapture(video)
    while cap.isOpened():
        ret, frame = cap.read()
        # if frame is read correctly ret is True
        if not ret:
            print("Can't receive frame (stream end?). Exiting ...")
            break
        # gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        cv.imshow('frame', frame)
        if cv.waitKey(1) == ord('q'):
            break
    cap.release()
    cv.destroyAllWindows()
