#!/usr/bin/env python

db = {}

def newuser():
	username = 'username: '
	while True:
		name = raw_input(username)
		if db.has_key(name):
			print 'the username has already exists,try again'
			continue
		else:
			break

	pwd = raw_input('password: ')
	db[name] = pwd

def olduser():
	name = raw_input('longname: ')
	pwd = raw_input('pwd: ')
	passwd = db.get(name)
	if pwd == passwd:
		print 'welcome back:',name
	else:
		print 'login incorrent'

CMDs = {'n':newuser,'e':olduser}

def showmenu():
	prompt = '''
	(n)ew user login
	(e)xisting user login
	(q)uit
	enter choice:
	'''

	while True:
		while True:
			try:
				choice = raw_input(prompt).strip()[0].lower()
			except(EOFError,KeyboardInterrupt):
				choice = 'q'

			print '\nyou choiced [%s]' % choice

			if choice not in 'neq':
				print 'invalid choice,try again'
			else :
				break

		if choice == 'q':
			break

		CMDs[choice]()	


if __name__ == '__main__':
	showmenu()
