import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2


class VideoSubscriber(Node):
    def __init__(self):
        super().__init__('video_subscriber')
        
        self.subscription = self.create_subscription(
            Image, 'camera/image', self.image_callback, 10)
        self.bridge = CvBridge()

    def image_callback(self, msg):
        frame = self.bridge.imgmsg_to_cv2(msg, 'bgr8')
        cv2.imshow('Camera', frame)
        cv2.waitKey(1)


def main():
    rclpy.init()
    node = VideoSubscriber()
    rclpy.spin(node)
    cv2.destroyAllWindows()
    rclpy.shutdown()


if __name__ == '__main__':
    main()