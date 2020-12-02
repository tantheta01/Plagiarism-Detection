import pygments.tokens
import pygments.lexers


def tokenize_file(filename):
	"""
	This function takes a file containing the original code and returns the tokens of the form : (token, string)
	"""
	with open(filename) as f:
		file_text = f.read()
	lexer = pygments.lexers.guess_lexer_from_filename(filename)
	tokens = lexer.get_tokens()
	tokens = list(tokens) # [(type_of_token, token) -> (Token.Comment.Single, #this is  laudalassan comment in the file filename)]
	return tokens
	count1=0
	count2=0

	for token in tokens:
		if token[0] == 
