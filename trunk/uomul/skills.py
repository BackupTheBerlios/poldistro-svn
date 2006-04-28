# $Id$


class Skill:
	def __init__(self, name, active, id=None):
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


class SkillsMul:
	def __init__(self, file='skills.mul', indexfile='Skills.idx', groupsfile='skillgrp.mul'):

