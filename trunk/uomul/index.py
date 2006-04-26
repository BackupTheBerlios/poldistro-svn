# $Id$
from struct import unpack


class Index:
	def __init__(self, fname):
		self.entries = self.__getEntries(fname)

	def __getEntries(self, fname):
		li = []
		fsock = open(fname, 'rb')
		data = fsock.read()
		fsock.close()
		data = unpack(str(len(data)/4)+'i', data)
		for i in range(0, len(data), 3):
			li.append(data[i:i+3])
		return li

