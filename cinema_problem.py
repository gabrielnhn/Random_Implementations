"""
The cinema problem!
We have a group of 5 people: 3 boys and 2 girls.
All of them want to sit together in the same row,
but the 2 girls must sit next to each other.
In how many different ways can we sort the row?

This solution was implemented by Gabriel Hishida.
"""


class Person:
    """Class used to represent both boys and girls"""

    def __init__(self, gender, id):
        self.gender = gender
        self.id = id

    def __str__(self):
        """Prints self"""
        return("{}{}".format(self.gender[0], self.id))

    def __repr__(self):
        """Prints self as well"""
        return self.__str__()

    last_row = [] # checks the last row the person was put in

a = Person('boy', 1)
b = Person('boy', 2)
c = Person('boy', 3)
d = Person('Girl', 4)
e = Person('Girl', 5)
people = [a,b,c,d,e] # hardcoded list of people

good_rows = [] # rows in which 2 girls are next to each other

# Guys are both boys and girls :P

def put_next(guy, row):
    """Main recursive function"""
    guy.last_row = list(row) # records the last row this person was put in
    row.append(guy) # puts a new person in the row

    if len(row) == len(people) and (row not in good_rows):
    # a new full row, check it out
        for sit in range(len(row) - 1):
            if (row[sit].gender == 'Girl') and (row[sit + 1].gender == 'Girl'):
            # if 2 girls are next to each other:
                good_rows.append(list(row))
                break

    else:
    # row isn't full yet
        for i in people:
            if (i not in row) and (i.last_row != (row)):
            # if person 'i' was never put in a row like this:
                put_next(i, row) # try putting them!

                row.pop(-1) # already tried putting 'i'

for guy in people:
# apply the function above with all 5 different initial cases
# basically, apply the function with a different person in the first seat each time
    row = []
    put_next(guy, row)


for r in good_rows:
# print every good row
    print(r)

print("Answer: {} different ways".format(len(good_rows)))
# print the amount of good rows