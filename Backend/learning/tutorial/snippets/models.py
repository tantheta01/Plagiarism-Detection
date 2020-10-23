from django.db import models

# Create your models here.


class Snippet(models.Model):
	"""docstring for Snippet"""
	
	created = models.DateTimeField(auto_now_add=True)
	class Meta:
		ordering=['created']	



