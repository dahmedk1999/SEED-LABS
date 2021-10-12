#!/bin/env python3
from os import read
def freqanalysis(file):
    percent=[]
    alphabet="abcdefghijklmnopqrstuvwxyz"
    charcount=0
    total=0
    with open(file,'r')as worddict:
        wordstext=worddict.read().lower()
        total=len(wordstext)
        print("Total letters in file: "+str(total))

    for each_char in alphabet:
        for char in wordstext:
            if(each_char==char):
                charcount=charcount+1
        pct=round(charcount/total,4)
        percent.append([each_char,pct,charcount])
        charcount=0
    a=percent.sort(key=lambda l:l[1],reverse=True)
    for b in percent:
        print(b[0]+" : "+" Frequency : "+str(b[1])+"\t| "+str(b[2]))
    return a


words=freqanalysis('words.txt')
cipher=freqanalysis('ciphertext.txt')
