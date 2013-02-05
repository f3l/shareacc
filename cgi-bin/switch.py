#!/usr/bin/python2

import yaml
import info
import cgi
import time

print "Status: 302 Found\r\nLocation: /\r\n\r\n"

accounts = yaml.load(open('accounts.yaml').read())
form = cgi.FieldStorage()

for account in accounts:
	ainfo = info.get(account['num'])
	ainfo.update({ 'used': int(time.time()) if (form.getvalue("u%s" % account['num'], 'off') == 'on') else False })
	info.set(account['num'], ainfo)
