from index import Index


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
		skill = {}
		skill['action'] = self.data[self.entries[id][0]]
		skill['name'] = 'a'
		return skill
	
	def getSkills(self):
		pass


class SkillGrp:
	def __init__(self, file):
		self.data = getData(file)
		self.count = self.getCount()
		pass

	def getCount():
		count = unpack('i', self.data[:4][0])
		return count

