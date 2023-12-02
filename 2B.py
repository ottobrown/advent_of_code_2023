input_file = open("input/2.txt", "r")
count = 0

def parse_set(set, maxes):
    number = 0
    color = ""
    for (i, word) in enumerate(set.strip().split(" ")):
        if i % 2 == 0:
            number = int(word.strip())
        else:
            color = word.replace(",", "").strip()
            if number > maxes[color]:
                maxes[color] = number

    return True

while True:
    line = input_file.readline()
    if not line:
        break

    maxes = {
        "red": 0,
        "green": 0,
        "blue": 0,
    }

    words = line.split(" ", 2)
    game_id = int(words[1].strip().replace(":", ""))

    for set in words[2].split(";"):
        parse_set(set, maxes)

    count += maxes["red"] * maxes["blue"] * maxes["green"]


print(count)
input_file.close()
