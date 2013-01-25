#!/usr/bin/python2

import os
import time
import json

import logging

from module.network.RequestFactory import RequestFactory

class Core:
	def __init__(self):
		self.log = logging.getLogger('log')
		self.config = {'download': {'limit_speed': False, 'interface': False, 'ipv6': False}, 'proxy': {'proxy': False}}
		self.eventManager = False
		self.interactionManager = False
		self.api = False
		self.requestFactory = RequestFactory(self)

class Manager:
	def __init__(self):
		self.core = Core()

manager = Manager()


providers = {
	'netload.in': 'NetloadIn',
	'rapidshare.com': 'RapidshareCom',
	'uploaded.to': 'UploadedTo',
}


def getRemoteInfo(provider, user, password):
	accounts = __import__('module.plugins.accounts', fromlist=[provider])
	mod = getattr(accounts, provider)
	cls = getattr(mod, provider)
	ac = cls(manager, user, password, {})
	ac.getAccountInfo(True)
	#print time.asctime(time.localtime(ac.validuntil))
	return {
		'valid': ac.valid, # in terms of right passwd
		'premium': ac.premium,
		'validuntil': ac.validuntil,
		'validuntil_p': time.asctime(time.localtime(ac.validuntil)),
		'trafficleft': ac.trafficleft,
	}

def fetch(account):
	provider = providers[account['type']]
	return getRemoteInfo(provider, account['user'], account['pass'])

json_info = None

def get(num):
	global json_info
	num = str(num)
	if not json_info:
		try:
			json_info = json.load(open('info.json'))
		except:
			json_info = {}
	return json_info.get(num, {})

def set(num, ainfo):
	global json_info
	num = str(num)
	if not json_info:
		try:
			json_info = json.load(open('info.json'))
		except:
			json_info = {}
	ainfo = {num: ainfo}
	json_info.update(ainfo)
	json.dump(json_info, open('info.json', 'w'))
