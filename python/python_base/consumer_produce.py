#!/usr/bin/env python
#coding=utf-8

from threading import Thread
from random import randint
from Queue import Queue
import time

class MyThread(Thread):
	def __init__(self,func,args,name):
		Thread.__init__(self)
		self.func = func
		self.args = args
		self.name = name
	
	def run(self):
		now_time = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
		print 'the thread %s starting: %s' %(self.name,now_time)
		#执行函数func
		apply(self.func,self.args)
		now_time = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
		print 'the thread %s finished: %s' %(self.name,now_time)

def put_to_Queue(queue):
	print 'put object to Queue'
	#put(item,block=0):block不为0,则会一直阻塞，直到有空间
	queue.put('xxx',1)
	print 'size of Queue : %d' %(queue.qsize())

def get_from_Queue(queue):
	print 'get object from Queue'
	o = queue.get(1)
	print 'size of Queue : %d' %(queue.qsize())

def product(queue,loops):
	for i in loops:
		put_to_Queue(queue)
		time.sleep(randint(1,3))

def consumer(queue,loops):
	for i in loops:
		get_from_Queue(queue)
		time.sleep(randint(3,5))

if __name__ == '__main__':
	funcs = [product,consumer]
	nfuncs = range(len(funcs))
	nloops = range(randint(2,5))
	q = Queue(32)
	threads = []
	#创建一个消费者线程和一个生产者线程
	for i in nfuncs:
		t = MyThread(funcs[i],(q,nloops),funcs[i].__name__)
		threads.append(t)
	
	for i in nfuncs:
		threads[i].start()

	for i in nfuncs:
		threads[i].join()
	
	print 'game over'

