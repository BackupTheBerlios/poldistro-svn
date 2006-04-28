# $Id$


def getData(file):
	'''Get the data of a file'''
	fsock = open(file, 'rb')
	data = fsock.read()
	fsock.close()
	return data


class BaseMul:
	'''TODO'''
	def __init__(self, datafile=None, indexfile=None):
		if datafile is not None:
			self.data = getData(datafile)
		if indexfile is not None:
			from index import Index
			idx = Index(indexfile)
			self.entries = idx.entries

