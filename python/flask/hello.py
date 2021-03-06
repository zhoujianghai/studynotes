#!/usr/bin/env python
#coding=utf-8

from flask import Flask,url_for,request,render_template,redirect,abort,escape,session
from werkzeug import secure_filename

print __name__
app = Flask(__name__)
app.secret_key = 'hello'

@app.route('/')
def index():
	return "hello flask"

@app.route('/user/<username>')
def show_username(username):
	return username

@app.route('/post/<int:post_id>')
def show_post(post_id):
	return 'post_id:%d' % post_id

#if you visit /projects will redirect /projects/
@app.route('/projects/')
def projects():
	return 'the project page'

#if you visit /about/ will return 404 error
@app.route('/about')
def about():
	return 'the about page'

@app.route('/upload/',methods=['GET','POST'])
def upload_file():
	if request.method == 'POST':
		f = request.files['the_file']
		f.save('./'+secure_filename(f.filename))
		return secure_filename(f.filename)
	else:
		return render_template('upload_file.html')

@app.route('/redirect/')
def test_redirect():
	return redirect(url_for('test_error'))

@app.route('/test_error/')
def test_error():
	#中断请求，并返回错误码
	abort(404)

@app.errorhandler(404)
def page_not_found(error):
	print error
	return render_template('page_not_found.html'),404
	
@app.route('/index/')
def test_session():
	if 'username' in session:
		return 'logged in as %s' % escape(session['username'])
	return redirect(url_for('login'))

@app.route('/login/',methods=['GET','POST'])
def login():
	print request.method
	if request.method == 'POST':
		session['username'] = request.form['username']
		return redirect(url_for('test_session'))
	else:
		print request.args.get('test',None)
		return '''
		<form action="/login/" method="post">
		<input type=text name=username>
		<input type=submit value=login>
		</form>
		'''
@app.route('/logout/')
def logout():
	session.pop('username',None)
	return redirect(url_for('test_session'))



with app.test_request_context():
	print url_for('index')
	print url_for('index',next='/')
	print url_for('show_username',username='alex')


if __name__ == '__main__':
	app.run(host="localhost",port=8888,debug=True)
