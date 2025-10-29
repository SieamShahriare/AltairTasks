import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2


class VideoPublisher(Node):
    def __init__(self):
        super().__init__('video_publisher')
        
        self.publisher_ = self.create_publisher(Image, 'camera/image', 10)
        self.bridge = CvBridge()
        self.cap = cv2.VideoCapture(0)  # 0 = webcam, or use RTSP URL
        
        self.timer = self.create_timer(0.033, self.publish_frame)  # ~30 FPS

    def publish_frame(self):
        ret, frame = self.cap.read()
        if ret:
            msg = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
            self.publisher_.publish(msg)


def main():
    rclpy.init()
    node = VideoPublisher()
    rclpy.spin(node)
    node.cap.release()
    rclpy.shutdown()


if __name__ == '__main__':
    main()