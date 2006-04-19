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
		self.count = len(self.entries)
	
	def getSkill(self, id):
		'''Get skill name, and if active or not
		returns dict'''
		sidx = self.entries[id]
		skillt = unpack('b'+str(sidx[1]-1)+'s', self.data[sidx[0]:sidx[0]+sidx[1]])
		skill = {}
		skill['action'] = skillt[0]
		skill['name'] = skillt[1][:-1]
		return skill
	
	def getSkills(self):
		#TODO: Calculate the _actual_ range of the index, 'cause index
		# seems to have alot of empty stuff.
		skills = [self.getSkill(skill) for skill in range(0, 15)]
		return skills


class SkillGrp:
	def __init__(self, file='SkillGrp.mul'):
		self.data = getData(file)

