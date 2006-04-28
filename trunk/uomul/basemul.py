# $Id$


class BaseMul:
	'''TODO'''
	def __init__(self, datafile=None, indexfile=None):
		if datafile is not None:
			self.data = self.__getData
		if indexfile is not None:
			self.entries =

	def getData(self, file):
		'''Get the data of a file'''
		fsock = open(file, 'rb')
		data = fsock.read()
		fsock.close()
		return data

