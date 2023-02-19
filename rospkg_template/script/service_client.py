#!/usr/bin/env python

import sys
import rospy
from rospkg_template_msgs.srv import *

def add_two_ints_client(x, y):
    rospy.wait_for_service('template_service', timeout=5.0)
    try:
        add_two_ints = rospy.ServiceProxy('template_service', SrvTemplate)
        resp1 = add_two_ints(x, y)
        return resp1.sum
    except rospy.ServiceException as e:
        print ("Service call failed: %s"%e)

def usage():
    return "%s [x y]"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 3:
        x = int(sys.argv[1])
        y = int(sys.argv[2])
    else:
        print(usage())
        sys.exit(1)
    print("Requesting %s+%s"%(x, y))
    print("%s + %s = %s"%(x, y, add_two_ints_client(x, y)))