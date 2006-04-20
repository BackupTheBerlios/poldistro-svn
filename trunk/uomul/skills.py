from index import Index
from struct import unpack


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
		skillidx = self.entries[id]
		unpacked = unpack('b'+str(skillidx[1]-1)+'s',
			self.data[skillidx[0]:skillidx[0]+skillidx[1]])
		skill = {}
		skill['active'] = unpacked[0]
		skill['name'] = unpacked[1][:-1]
		return skill
	
	def setSkill(self, id, name, active):
		'''Replace an already existing skill, with a new one'''
		if len(self.newentries) == 0:
			self.newentries = self.entries[:]
		self.newentries = [list(entry) for entry in self.newentries]
		idxold = self.newentries.pop(id)
		idxnew = (idxold[0], len(name), 0)
		self.newentries.insert(id, idxnew)
		temp = idxold[1] - idxnew[1]
		for i in range(id+1, self.max):
			self.newentries[i][0] += temp
		return self.newentries

	def getSkills(self):
		skills = [self.getSkill(skill) for skill in range(0, self.max)]
		return skills

	def writeSkills(self, entries=self.newentries, data):
		fsock = open('Skills.idx', 'w')
		fsock.close()

class SkillGrp:
	def __init__(self, file='SkillGrp.mul'):
		self.data = getData(file)

