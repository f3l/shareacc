#!/usr/bin/python2

import yaml
import info
import cgi

print "Status: 302 Found\r\nLocation: /\r\n\r\n"

accounts = yaml.load(open('accounts.yaml').read())
form = cgi.FieldStorage()

for account in accounts:
	ainfo = info.get(account['num'])
	ainfo.update({ 'used': (form.getvalue("u%s" % account['num'], 'off') == 'on') })
	info.set(account['num'], ainfo)
