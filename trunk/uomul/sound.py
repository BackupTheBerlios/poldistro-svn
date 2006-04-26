# $Id$
from index import Index


class Sound(Index):
	def __init__(self, file='sound.mul', indexfile='soundidx.mul'):
		Index.__init__(self, indexfile)

