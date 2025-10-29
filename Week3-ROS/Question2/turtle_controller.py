import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import time

class SimpleTurtleController(Node):
    def __init__(self):
        super().__init__('turtle_controller')
        self.pub = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        self.control_loop()

    def control_loop(self):
        while True:
            cmd = input("Command (A=Circle, B=Square, C=Spiral, Q=Quit): ").upper()
            
            if cmd == 'Q':
                self.pub.publish(Twist())
                break
            elif cmd == 'A':
                self.circle()
            elif cmd == 'B':
                self.square()
            elif cmd == 'C':
                self.spiral()

    def circle(self):
        msg = Twist()
        msg.linear.x, msg.angular.z = 2.0, 1.5
        self.pub.publish(msg)

    def square(self):
        msg = Twist()
        msg.linear.x = 1.5
        self.pub.publish(msg)
        time.sleep(2)
        
        msg = Twist()
        msg.angular.z = 1.57
        self.pub.publish(msg)
        time.sleep(1)
        
        self.pub.publish(Twist())

    def spiral(self):
        msg = Twist()
        for i in range(10):
            msg.linear.x, msg.angular.z = 1.0, 0.5 + i * 0.3
            self.pub.publish(msg)
            time.sleep(1)

def main():
    rclpy.init()
    SimpleTurtleController()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
    
