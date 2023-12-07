input_file = open("input/5.txt", "r")

seeds = list(map(int, list(input_file.readline().split(" "))[1:]))
for i in range(len(seeds)):
    if (2*i+1 < len(seeds)):
        seeds[i] = [seeds[2*i], seeds[2*i] + seeds[2*i+1] - 1]
    else:
        seeds.pop()

def in_seed(n):
    for [l, r] in seeds:
        if l <= n <= r:
            return True
    return False;

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

def apply_map_reverse(m, inp):
    possible = []
    for r in m:
        [destination, source, length] = r
        if destination <= inp < destination + length:
            possible.append(source + (inp - destination))

    if not possible:
        possible.append(inp)
    return possible

# get the seed numbers that corresponds to the location number
def get_seed(maps, inp):
    possible = [inp]
    for m in reversed(maps):
        temp = []
        for p in possible:
            temp += apply_map_reverse(m, p)

        possible = temp

    return possible


maps = parse_all_maps()

i = 0
while True:
    for p in get_seed(maps, i):
        if in_seed(p):
            print(i)
            exit(0)
    i += 1
