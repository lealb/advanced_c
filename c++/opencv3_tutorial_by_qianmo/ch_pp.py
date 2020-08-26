
import cv2 as cv


def test_canny(img):
    src_img = cv.imread(img)
    gray_img = cv.cvtColor(src_img, cv.COLOR_BGR2GRAY)
    cv.imshow("src_img", src_img)
    cv.imshow("gray_img", gray_img)
    cv.waitKey(0)
    cv.destroyAllWindows()


if __name__ == "__main__":
    # D:/02-Money/leetcode/c++/opencv3_tutorial_by_qianmo/file/img/tt.jpg
    img = "D:/02-Money/leetcode/c++/opencv3_tutorial_by_qianmo/file/img/tt.jpg"
    test_canny(img)
