package main

import(
    "fmt"
    "os"
    "bufio"
    "strings"
    "math/big"
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

    currents := []string{}

    scanner.Scan()
    for err == nil {
        scanner.Scan()
        reader = strings.NewReader(scanner.Text())

        var key, lvalue, rvalue string
        
        _, err = fmt.Fscanf(reader, "%s = %s %s", &key, &lvalue, &rvalue)

        if err == nil {
            if key[2] == 'A' {
                currents = append(currents, key)
            }
            
            lvalue = strings.Trim(lvalue, "(,) \r\n")
            rvalue = strings.Trim(rvalue, "(,) \r\n")

            pair := &Pair {
                left: lvalue,
                right: rvalue,
            }

            m[key] = *pair
        }
    }

    lengths := []int64{}

    for _, s := range currents {
        idx := 0
        var steps int64 = 0
        for s[2] != 'Z' {
            steps ++
            if idx >= len(lr) {
                idx = 0
            }

            if lr[idx] == 'L' { s = m[s].left }
            if lr[idx] == 'R' { s = m[s].right }

            idx++
        }

        lengths = append(lengths, steps)
    }

    lcm := big.NewInt(1)

    for _, l := range lengths {
        big_l := big.NewInt(l)
        gcd := big.NewInt(0)

        gcd.GCD(nil, nil, lcm, big_l)
        lcm.Div(lcm, gcd)
        lcm.Mul(big_l, lcm)
    }

    fmt.Printf("%v\n", lcm)
}
