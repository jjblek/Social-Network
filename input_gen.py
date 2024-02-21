import random

NUM_USERS = 100
# PROBABILITY_OF_FOLLOW = 10000 * 2 / NUM_USERS
# if PROBABILITY_OF_FOLLOW < 1: PROBABILITY_OF_FOLLOW = 1
locations = ['Alabama', 'Alaska', 'Arizona', 'Arkansas', 'California', 'Colorado',
             'Connecticut', 'Washington DC', 'Delaware', 'Florida', 'Georgia', 'Hawaii',
             'Idaho', 'Illinois', 'Indiana', 'Iowa', 'Kansas', 'Kentucky', 'Louisiana', 'Maine',
             'Maryland', 'Massachusetts', 'Michigan', 'Minnesota', 'Mississippi', 'Missouri',
             'Montana', 'Nebraska', 'Nevada', 'New Hampshire', 'New Jersey', 'New Mexico',
             'New York', 'North Carolina', 'North Dakota', 'Ohio', 'Oklahoma', 'Oregon',
             'Pennsylvania', 'Rhode Island', 'South Carolina', 'South Dakota', 'Tennessee',
             'Texas', 'Utah', 'Vermont', 'Virginia', 'Washington', 'West Virginia', 'Wisconsin',
             'Wyoming', 'Canada', 'Mexico', 'Outer Space']


def qs(string):
    return '"' + string + '"'

# Read names from a text file
with open('names.txt', 'r') as file:
    names = [line.strip() for line in file]

print("{")
print("\"users\": [")
for i in range(1, NUM_USERS + 1):
    print('\t{')
    print("\t\t" + qs("id_str"), ':', qs(str(i)), ',')
    print("\t\t" + qs("name"), ':', qs(random.choice(names)), ',')
    print("\t\t" + qs("location"), ':', qs(random.choice(locations)), ',')
    print("\t\t" + qs("pic_url"), ':',
          qs("https://www.xat.com/web_gear/chat/av/{num}.png".format(num=random.randint(1, 1758))), ',')
    print("\t\t" + qs("follows"), ':', '[', end="")
    follow_count = 0
    for j in range(1, NUM_USERS + 1):
        if j != i:
            if follow_count > 0: print(",", end="")
            print(qs(str(j)), end="")
            follow_count += 1
    print(']')
    print('\t}', end="")
    if i < NUM_USERS:
        print(',')
print("\n]\n}")
