#!/bin/python3

import math
import os
import random
import re
import sys



class Multiset:

    def __init__(self):
        self.data = []
        pass


    def add(self, val):
        self.data.append(val)
        pass

    def remove(self, val):
        # removes one occurrence of val from the multiset, if any
        if(val in self.data):
           self.data.remove(val)
        pass

    def __contains__(self, val):
        # returns True when val is in the multiset, else returns False
        if(val in self.data):
            return True
        return False

    def __len__(self):
        # returns the number of elements in the multiset
        return len(self.data)


class Car:

    def __init__(self, velocity, units):
        self.velocity = velocity
        self.units = units

    def __repr__(self):
        x = str(self.velocity)
        return "Car with the maximum speed of " + x + " " +self.units
    pass


class Boat:
    def __init__(self, speed):
        self.speed = speed
        
        
    def __repr__(self):
        x = str(self.speed)
        return "Boat with the maximum speed of " + x + " knots"
    pass