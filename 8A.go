package main

import(
    "fmt"
    "os"
    "bufio"
    "strings"
)

type Pair struct {
    left string
    right string
}

func main() {
    input_file, open_err := os.Open("input/8.txt")

    if open_err != nil {
        fmt.Println("error opening file")
        return;
    }

    scanner := bufio.NewScanner(input_file)
    scanner.Scan()
    reader := strings.NewReader(scanner.Text())

    var lr string
    m := make(map[string]Pair)
    
    _, err := fmt.Fscanf(reader, "%s\n\n", &lr)

    scanner.Scan()
    for err == nil {
        scanner.Scan()
        reader = strings.NewReader(scanner.Text())

        var key, lvalue, rvalue string
        _, err = fmt.Fscanf(reader, "%s = %s %s", &key, &lvalue, &rvalue)

        if err == nil {
            lvalue = strings.Trim(lvalue, "(,) \r\n")
            rvalue = strings.Trim(rvalue, "(,) \r\n")

            pair := &Pair {
                left: lvalue,
                right: rvalue,
            }

            m[key] = *pair
        }
    }

    current := "AAA"

    steps := 0
    i := 0
    for current != "ZZZ" {
        steps ++
        if i >= len(lr) {
            i = 0
        }

        if lr[i] == 'L' { current = m[current].left }
        if lr[i] == 'R' { current = m[current].right }
        i++
    }

    fmt.Printf("%v\n", steps)
}
