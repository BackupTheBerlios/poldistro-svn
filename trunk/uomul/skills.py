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

	def __getMax(self):
		'''Determine the max number of skills'''
		valid = [entry for entry in self.entries if entry[0] > -1]
		return len(valid)
	
	def getSkill(self, id):
		'''Get skill name, and if active or not
		returns dict'''
		if id > self.max-1:
			return
		sidx = self.entries[id]
		skillt = unpack('b'+str(sidx[1]-1)+'s', self.data[sidx[0]:sidx[0]+sidx[1]])
		skill = {}
		skill['action'] = skillt[0]
		skill['name'] = skillt[1][:-1]
		return skill
	
	def setSkill(self, id, name, action):
		'''Replace an already existing skill, with a new one.'''

	def getSkills(self):
		skills = [self.getSkill(skill) for skill in range(0, self.max)]
		return skills


class SkillGrp:
	def __init__(self, file='SkillGrp.mul'):
		self.data = getData(file)

