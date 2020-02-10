import csv
from random import randint
with open('1ml without weight', 'r') as csvinput, open('1mln+w', 'w') as csvoutput:
    writer = csv.writer(csvoutput, delimiter=' ', lineterminator='\n')
    reader = csv.reader(csvinput, delimiter=' ', lineterminator='\n')
    all = []
    row = next(reader)
    row.append(randint(2, 50))
    all.append(row)
    for row in reader:
        row.append(randint(2, 50))
        all.append(row)

    writer.writerows(all)
