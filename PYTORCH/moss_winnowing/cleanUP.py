import pygments.token
import pygments.lexers


def tokenize(filename):
    """
    ! @brief Tokenie input file
    
    @detail Remove comments, Replace every variable/class/any other user defined name by N, Replace every string literal by S, Replace every function name by F
    
    @type filename: str
    @param filename: path of the file to be tokenized
    
    @rtype result: list
    @return result: Every token is a string, obtained by stripping the file content to words and performing the cleaning described. The starting index of the token in the cleaned code and actual code are also stored
    """
    file = open(filename, "r")
    text = file.read()
    file.close()
    lexer = pygments.lexers.guess_lexer_for_filename(filename, text)
    tokens = lexer.get_tokens(text)
    tokens = list(tokens)
    result = []
    lenT = len(tokens)
    count1 = 0    #tag to store corresponding position of each element in original code file
    count2 = 0    #tag to store position of each element in cleaned up code text
    # these tags are used to mark the plagiarized content in the original code files.
    for i in range(lenT):
        if tokens[i][0] == pygments.token.Name and not i == lenT - 1 and not tokens[i + 1][1] == '(':
            result.append(('N', count1, count2))  #all variable names as 'N'
            count2 += 1
        elif tokens[i][0] in pygments.token.Literal.String:
            result.append(('S', count1, count2))  #all strings as 'S'
            count2 += 1
        elif tokens[i][0] in pygments.token.Name.Function:
            result.append(('F', count1, count2))   #user defined function names as 'F'
            count2 += 1
        elif tokens[i][0] == pygments.token.Text or tokens[i][0] in pygments.token.Comment:
            pass   #whitespaces and comments ignored
        else:
            result.append((tokens[i][1], count1, count2))  
            #tuples in result-(each element e.g 'def', its position in original code file, position in cleaned up code/text) 
            count2 += len(tokens[i][1])
        count1 += len(tokens[i][1])

    return result

def toText(arr):
    """
    ! @brief Convert list of tokens to string
    
    @type arr: list
    @param arr: List of tuples obtained from @ref tokenize
    
    @rtype cleanText: str
    @return cleanText: code obtained by joining all tokens and removing comments and whitespaces
    """
    cleanText = ''.join(str(x[0]) for x in arr)
    return cleanText



