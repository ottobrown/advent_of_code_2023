package main

import (
    "fmt"
    "os"
    "bufio"
    "strings"
    "math"
    "io"
)

func scan_list(reader io.Reader) []int {
    var ret []int
    for  {
        var k int
        _, err := fmt.Fscanf(reader, "%d", &k)
        if (err != nil) { break }
        ret = append(ret, k)
    }

    return ret
}

func main() {
    input_file, open_err := os.Open("input/6.txt")

    if open_err != nil {
        fmt.Println("error opening file")
        return;
    }

    scanner := bufio.NewScanner(input_file)

    scanner.Scan()
    reader := strings.NewReader(scanner.Text())
    fmt.Fscanf(reader, "Time:");

    times := scan_list(reader)

    scanner.Scan()
    reader = strings.NewReader(scanner.Text())
    fmt.Fscanf(reader, "Distance:");

    distances := scan_list(reader)

    prod := 1
    for i := 0; i < len(distances); i++ {
        t := times[i]
        d := distances[i]
        span := 0

        sq := math.Sqrt(float64(t*t - 4*d))
        left := 0.5*float64(t) - 0.5*sq
        right := 0.5*float64(t) + 0.5*sq

        int_l := int(math.Floor(left))
        for float64(int_l) <= left {
            int_l ++
        }

        int_r := int(math.Ceil(right))
        for float64(int_r) >= right {
            int_r --
        }

        span = int_r - int_l + 1

        prod *= span
    }

    fmt.Printf("%v\n", prod)
}
