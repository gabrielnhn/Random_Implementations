"""
Given a string S consisting of letters 'a' & 'b',
we want to split it into three separate non-empty parts.
The length of the parts can differ from each other.
In how many ways can you split S into three parts,
such that each part contains the same number of letters 'a'?
"""


def add_char(i, string, parts):
    global total


    parts[-1].append(string[i])
    # add char to last part

    if i == (len(string) -1):
        # no char left in string to process

        if len(parts) == 3:
            # sanity check

            flag = True
            for part in parts:
                if part.count('a') != max_as:
                    # there's a part where the number of 'a's is not correct
                    flag = False

            if flag:
                # it's a valid line of parts
                total += 1
                # print it:
                for part in parts:
                    for letter in part:
                        print(letter, end='')
                    print(' | ',end='')
                print('')
            
    else:
        # there are chars left in the string to process:

        if parts[-1].count('a') == max_as:
            # part has all the 'a's necessary

            if len(parts) < 3:
                # make new part and process it
                parts.append([])
                add_char(i + 1, string, parts)

                # part was processed, throw it away
                parts.pop(-1)

                if string[i + 1] != 'a':
                    # adapt current part, even though there are 
                    # already enough 'a's

                    add_char(i + 1, string, parts)

            else: # there are already 3 parts, but there's still
                # input to process (just put it in the last part)
                add_char(i + 1, string, parts)
        
        else: # part doesn't have enough 'a's
            add_char(i + 1, string, parts)

# MAIN:

string = "abbaba"
# string to be processed

if string.count('a') % 3 != 0:

    print('Impossible to split')

else:

    max_as = string.count('a') // 3
    # max amount of as per part

    parts=[[]]
    # line of parts, starting off with an empty part

    total = 0
    # holds the number of solutions

    add_char(0, string, parts)
    # main recursive function

    print("The string can be splitted in {} different ways".format(total))