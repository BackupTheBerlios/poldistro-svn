# $Id$
from index import Index
from struct import unpack, pack


def getData(file):
	'''Get the data of a file'''
	#TODO: Probably move this to some place generic
	fsock = open(file, 'rb')
	data = fsock.read()
	fsock.close()
	return data


class Skills(Index):
	'''TODO'''
	def __init__(self, file='skills.mul', indexfile='Skills.idx'):
		Index.__init__(self, indexfile)
		self.data = getData(file)
		self.max = self.__getMax()
		self.newentries = []
		self.newdata = ''

	def __getMax(self):
		'''Calculate the max number of skills.
		@return: then max skill number
		@rtype: integer
		'''
		# if index lookup is -1 it's invalid
		valid = [entry for entry in self.entries if entry[0] > -1]
		return len(valid)
	
	def __flushData(self):
		'''Copy the new data/entries to the cache and clean the new*'''
		self.entries = self.newentries[:]
		self.newentries = []
		self.data = self.newdata[:]
		self.newdata = ''

	def getSkill(self, id):
		'''Get skill name.
		@param id: the id of the skill who's name we want
		@type id: integer
		@return: the name of the skill and if active/passive
		@rtype: dictionary
		'''
		if id > self.max-1:
			#TODO Define a custom class Exception SkillError
			raise NameError('Skill ID is out of range.')
		skillsidx = self.entries[id]
		unpacked = unpack('b%ds' % (skillsidx[1]-1),
			self.data[skillsidx[0]:skillsidx[0]+skillsidx[1]])
		skill = {}
		skill['active'] = bool(unpacked[0])
		skill['name'] = unpacked[1][:-1]
		return skill
	
	def setSkill(self, id, name, active):
		'''Replace a skill with a new one.
		@param id: the id of the skill to replace
		@type id: integer
		@param name: the name of new skill
		@type name: string
		@param active: wether the skill is active/passive
		@type active: boolean
		'''
		if len(self.newentries) == 0:
			self.newentries = self.entries[:]
		if len(self.newdata) == 0:
			self.newdata = self.data[:]
		self.newentries = [list(entry) for entry in self.newentries]
		idxold = self.newentries.pop(id)
		idxnew = [idxold[0], len(name)+2, 0] # we +2 for action and null char
		self.newentries.insert(id, idxnew)
		charodds = idxnew[1] - idxold[1]
		for i in range(id+1, self.max):
			self.newentries[i][0] += charodds
		packed = pack('b%ds' % (idxnew[1]-2), int(active), name) + '\x00'
		tempdata = self.newdata[:idxold[0]] + packed + self.newdata[idxold[0]+idxold[1]:]
		self.newdata = tempdata

	def getSkills(self):
		'''Get a list of all the skills'''
		skills = [self.getSkill(skill) for skill in range(0, self.max)]
		return skills

	def writeSkills(self, flush=True):
		'''Write the changes to the files.
		@param flush: wether to flush the old data on not
		@type flush: boolean
		'''
		idxpacked = pack('%di' % (len(self.newentries)*3),
			*(i for entry in self.newentries for i in entry))
		fsock = open('Skills.idx', 'wb')
		fsock.write(idxpacked)
		fsock.close()
		fsock = open('skills.mul', 'wb')
		fsock.write(self.newdata)
		fsock.close()
		if flush is True:
			self.__flushData()


class SkillGrp:
	'''TODO'''
	NAME_LEN = 17

	def __init__(self, file='SkillGrp.mul'):
		self.data = getData(file)
		self.count = self.__getGroupCount();
		#self.groupnames = self.__getGroupNames()

	def __getGroupCount(self):
		count = unpack('i', self.data[:4])
		return count[0]

	'''def __getGroupNames(self):
		groupnames = unpack('%ds' % (NAME_LEN*self.count), self.data[self.count:NAME_LEN*self.count])
		return groupnames'''

	def getGroupName(self, id):
		if id > count-1:
			raise NameError('Skill Group ID is out of range.')
		groupname = unpack('17s', self.data[4+id*17:])

