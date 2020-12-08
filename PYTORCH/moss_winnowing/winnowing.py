import pygments.token
import pygments.lexers
import hashlib
from cleanUP import *

#sha-1 encoding is used to generate hash values
def hash(text):
    """!
    @brief generates hash value for a string

    @type text: str
    @param text: The input string to hash

    @rtype hashvl: int
    @return hashval: The mapped hash value of the string
    """
    
    hashval = hashlib.sha1(text.encode('utf-8'))
    hashval = hashval.hexdigest()[-4 :]
    hashval = int(hashval, 16)  #using last 16 bits of sha-1 digest
    return hashval

#function to form k-grams out of the cleaned up text
def kgrams(text, k = 25):
    """!
    @brief Generates list of kGrams and corresponding hash value for a specific string. 

    @type text: str
    @param text: string for which kgrams are generated

    @type k: int
    @param k: block size in generating kgrams

    @rtype kgrams: list
    @return kgrams: List of 4-tuples. The length of the list is equal to the number of kGrams of the string. Each element in the list is a 4-tuple - (kgram, hash_value, start_index, end_index)
    """

    tokenList = list(text)
    n = len(tokenList)
    kgrams = []
    for i in range(n - k + 1):
        kgram = ''.join(tokenList[i : i + k])
        hv = hash(kgram)
        kgrams.append((kgram, hv, i, i + k))  #k-gram, its hash value, starting and ending positions are stored
        #these help in marking the plagiarized content in the original code.
    return kgrams

#function that returns the index at which minimum value of a given list (window) is located
def minIndex(arr):
    """!
    @brief Finds index of leftmost minimum element in list

    @type arr: list

    @rtype minI: int
    """

    minI = 0
    minV = arr[0]
    n = len(arr)
    for i in range(n):
        if arr[i] < minV:
            minV = arr[i]
            minI = i
    return minI

#we form windows of hash values and use min-hash to limit the number of fingerprints
def fingerprints(arr, winSize = 4):
    """!
    @brief Performs winnowing and computes the fingerprint from a hashlist

    @detail For every window length subarray of the hash list take the leftmost minimum in the list if it is not alreasy taken

    @type arr: list
    @param arr: The hashlist for which the fingerprint is to be computed

    @type winSize: int
    @param winSize: The size of the window for winnowing. 

    @rtype fingerprintList: list
    @return fingerprintList: List of hash values in the fingerprint of the array    
    """

    arrLen = len(arr)
    prevMin = 0
    currMin = 0
    windows = []
    fingerprintList = []
    for i in range(arrLen - winSize):
        win = arr[i: i + winSize]  #forming windows
        windows.append(win)
        currMin = i + minIndex(win)
        if not currMin == prevMin:  #min value of window is stored only if it is not the same as min value of prev window
            fingerprintList.append(arr[currMin])  #reduces the number of fingerprints while maintaining guarantee
            prevMin = currMin  #refer to density of winnowing and guarantee threshold (Stanford paper)

    return fingerprintList

#takes k-gram list as input and returns a list of only hash values
def hashList(arr):
    """!
    @param arr : list of 4-tuples containing (k_gram, hash value, start_index, end_index)
    """

    HL = []
    for i in arr:
        HL.append(i[1])

    return HL


def getFingerPrints(filename, isLangSpec):
    """!
    @brief Calculate the tokenset of the file
    """
    if not isLangSpec:
        token = tokenize(filename)
    else:
        token = tokenize_for_java(filename)
    token_string = toText(token)
    kGrams = kgrams(token_string)
    HL = hashList(kGrams)
    fpList = fingerprints(HL)
    return (token, kGrams, HL, fpList)


def plagiarismCheck(file1, token1, kGrams1, HL1, fpList1, fpList2):
    """!
    @brief Calculates similarity between two code files
    
    @detail The similarity is calculated as length of similar code in file1/length of file1
    
    @type file1: str
    @param file1: name of the first file
    
    @type token1: list
    @param token1: list of tokens where each token is of the form (token_text, count1, count2)
    
    @type kGrams1: list
    @param kGrams1: list of kGrams for the first file. 
    
    @type HL1: list
    @param HL1: hash list of the first source code
    
    @type fpList1: list
    @param fpList1: list of fingerprints from the first file
    
    @type fpList2: list
    @param fpList2: list of fingerprints from the second file
    
    @rtype similarity: float
    @return similarity: the similarity between the two files
    
    @rtype newCode: str
    @return newCode: The content of first file with <b>mark<b> appended around every plagiarized(with respect to second file) block
    """
    
    f1 = open(file1, "r")
    
    start = []   #to store the start values corresponding to matching fingerprints
    end = []   #to store end values
    code = f1.read()  #original code
    newCode = ""   #code with marked plagiarized content
    points = []
    for i in fpList1:
        for j in fpList2:
            if i == j:   #fingerprints match
                flag = 0
                match = HL1.index(i)   #index of matching fingerprints in hash list, k-grams list
                newStart = kGrams1[match][2]   #start position of matched k-gram in cleaned up code
                newEnd = kGrams1[match][3]   #end position
                for k in token1:
                    if k[2] == newStart:   #linking positions in cleaned up code to original code
                        startx = k[1]
                        flag += 1
                    if k[2] == newEnd:
                        endx = k[1]
                        flag=flag+1
                if flag == 2:
                    points.append([startx, endx])
    points.sort(key = lambda x: x[0])
    if(len(points) > 1):

        points = points[1:]
        mergedPoints = []
        mergedPoints.append(points[0])
        for i in range(1, len(points)):
            last = mergedPoints[len(mergedPoints) - 1]
            if points[i][0] >= last[0] and points[i][0] <= last[1]: #merging overlapping regions
                if points[i][1] > last[1]:
                    mergedPoints = mergedPoints[: len(mergedPoints)-1]
                    mergedPoints.append([last[0], points[i][1]])
                else:
                    pass
            else:
                mergedPoints.append(points[i])
        newCode = code[: mergedPoints[0][0]]
        plagCount = 0
        for i in range(len(mergedPoints)):
            if mergedPoints[i][1] > mergedPoints[i][0]:
                plagCount += mergedPoints[i][1] - mergedPoints[i][0]
                newCode = newCode + '<mark>' + code[mergedPoints[i][0] : mergedPoints[i][1]] + "<mark>"
                if i < len(mergedPoints) - 1:
                    newCode = newCode + code[mergedPoints[i][1] : mergedPoints[i+1][0]]
                else:
                    newCode = newCode + code[mergedPoints[i][1] :]
        return plagCount/len(code), newCode

    else:
        return 0, code
    
