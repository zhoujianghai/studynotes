#!/usr/bin/env python

stack = []

def pushit():
	stack.append(raw_input("enter new string: ").strip())

def popit():
	if len(stack) == 0:
		print "cannot pop from empty stack!"
	else:
		print 'remove [', `stack.pop()`, ' ]'

def viewstack():
	print stack

CMDS = {'u':pushit, 'o':popit, 'v':viewstack}

def showmenu():
	pr = '''
	p(u)sh
	p(o)p
	(v)iew
	(q)uit
	enter choice:
	'''
	while True:
		while True:
			try:
				choice = raw_input(pr).strip()[0].lower()
			except(EOFError,KeyboardInterrupt,IndexError):
				choice = 'q'

			print 'you choiced: [%s]' % choice
			if choice not in 'uovq':
				print 'invalid choice,try again'
			else:
				break
		if choice == 'q':
			break
	
		CMDS[choice]()

if __name__ == '__main__':
	showmenu()

