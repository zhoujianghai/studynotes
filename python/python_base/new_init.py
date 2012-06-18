#!/usr/bin/env python

class A(object):
	def __init__(self):
		print '_init_'

#if the method of __new__ have nothing return,the __init__ will be not invoke	
	def __new__(Class):
		obj = super(A,Class).__new__(Class)
		print '__new__'
		return obj

print __name__

if __name__ == '__main__':
	a = A()
	a.t = 2
	print '%d' % (a.t)
