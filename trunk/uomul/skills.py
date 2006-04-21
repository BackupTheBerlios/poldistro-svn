from index import Index
from struct import unpack, pack


def getData(file):
	fsock = open(file, 'rb')
	data = fsock.read()
	fsock.close()
	return data


class Skills(Index):
	def __init__(self, file='skills.mul', indexfile='Skills.idx'):
		Index.__init__(self, indexfile)
		self.data = getData(file)
		self.max = self.__getMax()
		self.newentries = []
		self.newdata = ''

	def __getMax(self):
		'''Determine the max number of skills'''
		# if index lookup is -1 it's invalid
		valid = [entry for entry in self.entries if entry[0] > -1]
		return len(valid)
	
	def getSkill(self, id):
		'''Get skill name, and if active or not
		returns dict'''
		if id > self.max-1:
			#TODO Define a custom class Exception SkillError
			raise NameError('Skill ID is out of range.')
		skillsidx = self.entries[id]
		unpacked = unpack('b'+str(skillsidx[1]-1)+'s',
			self.data[skillsidx[0]:skillsidx[0]+skillsidx[1]])
		skill = {}
		skill['active'] = unpacked[0]
		skill['name'] = unpacked[1][:-1]
		return skill
	
	def setSkill(self, id, name, active):
		'''Replace an already existing skill, with a new one'''
		if len(self.newentries) == 0:
			self.newentries = self.entries[:]
		if len(self.newdata) == 0:
			self.newdata = self.data[:]
		self.newentries = [list(entry) for entry in self.newentries]
		idxold = self.newentries.pop(id)
		idxnew = [idxold[0], len(name), 0]
		idxntemp = idxnew[:]
		idxntemp[1] += 2
		self.newentries.insert(id, idxntemp)
		temp = idxold[1] - idxnew[1]
		for i in range(id+1, self.max):
			self.newentries[i][0] += temp
		packed = pack('b'+str(idxnew[1])+'s', active, name) + '\x00'
		temp = self.newdata[:idxold[0]] + packed + self.newdata[idxold[0]+idxold[1]:]
		self.newdata = temp
		return packed

	def getSkills(self):
		skills = [self.getSkill(skill) for skill in range(0, self.max)]
		return skills

	#def writeSkills(self, entries=self.newentries, data=self.newdata):
	#	fsock = open('Skills.idx', 'w')
	#	fsock.close()

class SkillGrp:
	def __init__(self, file='SkillGrp.mul'):
		self.data = getData(file)

