# $Id$
from struct import unpack
from basemul import getData


class Index:
	'''TODO'''
	def __init__(self, file):
		self.entries = self.__getEntries(file)

	def __getEntries(self, file):
		entries = []
		data = getData(file)
		data = unpack('%di' % (len(data)/4), data)
		for i in range(0, len(data), 3):
			entries.append(data[i:i+3])
		return entries 

