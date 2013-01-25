#!/usr/bin/python2

import yaml
import info

print "Status: 302 Found\r\nLocation: /\r\n\r\n"

accounts = yaml.load(open('accounts.yaml').read())

for account in accounts:
	oldinfo = info.get(account['num'])
	try:
		ainfo = info.fetch(account)
	except NameError:
		# workaround for non-existing error function
		ainfo = {'valid': False}
	oldinfo.update(ainfo)
	info.set(account['num'], oldinfo)
