// AoC day 1

import Foundation

let answer = 2020

func solvePart1(input: [Int]) -> Int {
    for item1 in input {
        for item2 in input {
            if item1 + item2 == answer {
                return item1 * item2
            }
        }
    }
    return -1
}

let input = [
    1721,
    979,
    366,
    299,
    675,
    1456
]

print(solvePart1(input: input))
