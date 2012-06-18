#!/usr/bin/env python
#coding=utf-8

#from html.parser import HTMLParser
import HTMLParser

class MyParser(HTMLParser.HTMLParser):
	def __init__(self):
		#super(MyParser,self).__init__()
		HTMLParser.HTMLParser.__init__(self)

	def handle_starttag(self,tag,attrs):
		print 'encountered a %s start tag' %(tag) 

	def handle_endtag(self,tag):
		print 'encountered a %s end tag' %(tag) 

	def handle_data(self,data):
		print 'encountered a %s data' %(data) 

if __name__ == '__main__':
	page = '<html><title><p>fuck</p><title></html>'
	myparser = MyParser()
	myparser.feed(page)
