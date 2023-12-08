package main

import (
    "fmt"
    "os"
    "math"
    "bufio"
)

func main() {
    input_file, open_err := os.Open("input/6.txt")

    if open_err != nil {
        fmt.Println("error opening file")
        return;
    }

    t, d := 0, 0
    second := false
    reader := bufio.NewReader(input_file)

    var b byte
    var err error
    
    for err == nil {
        b, err = reader.ReadByte()
        if b == byte('\n') {
            second = true
        }

        if b - byte('0') <= 9 {
            if !second {
                t *= 10
                t += int(b - byte('0'))
            } else {
                d *= 10
                d += int(b - byte('0'))
            }
        }
    }

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

    fmt.Printf("%v\n", span)
}
