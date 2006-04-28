# $Id$
from basemul import BaseMul, getData


class Skill:
	def __init__(self, name, active, id=None):
		'''
		@param name: the name of skill
		@type name: string
		@param active: skill status (active/passive)
		@type active: boolean
		@param id: the id of the skill
		@type id: int
		'''
		self.id = id
		self.name = name
		self.active = active


class SkillGroup:
	def __init__(self, name, skills=None, id=None):
		self.id = id
		self.name = name
		if skills is None:
			self.skills = []
		else:
			self.skills = skills

	def addSkill(skill):
		pass

	def removeSkill(skill):
		pass


class SkillsMul(BaseMul):
	def __init__(self, file='skills.mul', indexfile='Skills.idx', groupsfile='skillgrp.mul'):
		BaseMul.__init__(self, file, indexfile)
		groups = SkillGrpMul(groupsfile)


class SkillGrpMul(BaseMul):
	def __init__(self, file='skillgrp.mul'):
		BaseMul.__init__(self, file)
		self.count = self.__getCount()
		self.groups = self.getGroups()

	def __getCount(self):
		pass

	def getGroups(self):
		pass

	def addGroup(self):
		pass

	def removeGroup(self):
		pass

