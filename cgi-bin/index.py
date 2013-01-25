#!/usr/bin/python2

import yaml
import info

print "Content-type: text/html\n"

print """
<head>
	<title>F3L - One Click Hoster</title>
	<link href="/static/style.css" rel="stylesheet" type="text/css">
</head>
"""

print """
<body>
	<h3>F3L - One Click Hoster</h3>
	<div class="main">
		<form method="post" action="/cgi-bin/switch.py">
			<table>
				<tr>
					<th>Nr</th>
					<th>Type</th>
					<th>Owner</th>
					<th>User</th>
					<th>Password</th>
					<th>Valid until</th>
					<th>Traffic</th>
					<th colspan="2">In Usage?</th>
				</tr>
"""


accounts = yaml.load(open('accounts.yaml').read())

for account in accounts:
	ainfo = info.get(account['num'])

	trafficleft = ainfo.get('trafficleft', -1)
	trafficleft = "%i GB" % (trafficleft / 1000000) if trafficleft > 0 else "n/a"

	account.update({
		'css_expired': '' if ainfo.get('premium', True) else 'expired',
		'css_invalid': '' if ainfo.get('valid', True) else 'invalid',
		'valid': ainfo.get('validuntil_p', 'n/a') if ainfo.get('premium', True) else '<div title="%s">expired</div>' % ainfo.get('validuntil_p', ''),
		'traffic': trafficleft,
		'used_icon': 'busy' if ainfo.get('used', False) else 'online',
		'used_text': 'Yes' if ainfo.get('used', False) else 'No',
		'used_checked': 'checked="checked"' if ainfo.get('used', False) else '',
	})
	print """
				<tr class="%(css_invalid)s %(css_expired)s">
					<td>%(num)i</td>
					<td>%(type)s</td>
					<td>%(owner)s</td>
					<td>%(user)s</td>
					<td>%(pass)s</td>
					<td>%(valid)s</td>
					<td>%(traffic)s</td>
					<td><img src="/img/%(used_icon)s.png" width="16" height="16">&nbsp;%(used_text)s</td>
					<td><input type="checkbox" onchange="document.forms[0].submit()" name="u%(num)i" %(used_checked)s /></td>
				</tr>
	""" % account


print """
		</table>
		<p><input type="submit" value="Change value" style="display: none;" /></p>
		</form>
	</div>
	<div class="footer">
		<a rel="nofollow" href="/cgi-bin/fetch.py">Refresh account details</a><br />
		Status will be reset every 12 hours.
	</div>
</body>
"""
