# $Id$
from struct import unpack


class Index:
	'''TODO'''
	def __init__(self, file):
		self.entries = self.__getEntries(file)

	def __getEntries(self, file):
		entries = []
		fsock = open(file, 'rb')
		data = fsock.read()
		fsock.close()
		data = unpack('%di' % (len(data)/4), data)
		for i in range(0, len(data), 3):
			entries.append(data[i:i+3])
		return entries 

