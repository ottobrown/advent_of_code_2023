max_red = 12
max_green = 13
max_blue = 14

input_file = open("input/2.txt", "r")
count = 0

def parse_set(set):
    number = 0
    color = ""
    for (i, word) in enumerate(set.strip().split(" ")):
        if i % 2 == 0:
            number = int(word.strip())
        else:
            color = word.replace(",", "").strip()
            if too_big(color, number):
                return False

    return True


def too_big(color, number):
    if color == "red" and number > max_red:
        return True
    if color == "blue" and number > max_blue:
        return True
    if color == "green" and number > max_green:
        return True

    return False


while True:
    line = input_file.readline()
    if not line:
        break

    words = line.split(" ", 2)
    game_id = int(words[1].strip().replace(":", ""))

    game_valid = True
    for set in words[2].split(";"):
        if not parse_set(set):
            game_valid = False

    if game_valid:
        count += game_id

print(count)
input_file.close()
