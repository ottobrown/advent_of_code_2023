input_file = open("input/5.txt", "r")

seeds = list(map(int, list(input_file.readline().split(" "))[1:]))

def parse_map(input_file):
    new_map = []

    input_file.readline()

    line = ""
    while True:
        line = input_file.readline()
        if not line.strip():
            break;
        new_map.append(list(map(int,line.split(" "))))

    return new_map

def parse_all_maps():
    input_file.readline()

    return [
        parse_map(input_file),
        parse_map(input_file),
        parse_map(input_file),
        parse_map(input_file),
        parse_map(input_file),
        parse_map(input_file),
        parse_map(input_file),
    ]

def apply_map(m, inp):
    for r in m:
        [destination, source, length] = r
        if source <= inp < source + length:
            return destination + (inp - source)

    return inp

def get_location(maps, inp):
    value = inp
    for m in maps:
        value = apply_map(m, value)

    return value

maps = parse_all_maps()
min_location = -1;
for seed in seeds:
    location = get_location(maps, seed)

    if min_location == -1 or location < min_location:
        min_location = location

print(min_location)
