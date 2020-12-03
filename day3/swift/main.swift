// AoC day 3

import Foundation

extension String {
    subscript(offset: Int) -> Character {
        self[index(self.startIndex, offsetBy: offset)]
    }
}

func readFile(filename: String) -> [String] {
    do {
        let text = try String(contentsOfFile: filename, encoding: .ascii)
        let lines : [String] = text.components(separatedBy: "\n")
        return lines
    } catch let error as NSError{
        return[]
    }
}

func solve(lines: [String], xinc: Int, yinc: Int) -> Int {
    var xp = 0
    var count = 0
    let lineWidth = lines[0].trimmingCharacters(in: .whitespacesAndNewlines).count
    var y = yinc
    let lineCount = lines.count
    while(y < lineCount) {
        xp += xinc
        let actualXp = xp % lineWidth
        let prevLine = lines[y]
        if prevLine[actualXp] == "#" {
            count += 1
        }
        y += yinc
    }
    return count
}

let map = readFile(filename: "/Users/mikaelstalvik/Downloads/aoc3f.txt")

let res = solve(lines: map, xinc: 3, yinc: 1)

print("Solve part 1: Trees \(res)")

var nums: [Int] = []
nums.append(solve(lines: map, xinc: 1, yinc: 1))
nums.append(solve(lines: map, xinc: 3, yinc: 1))
nums.append(solve(lines: map, xinc: 5, yinc: 1))
nums.append(solve(lines: map, xinc: 7, yinc: 1))
nums.append(solve(lines: map, xinc: 1, yinc: 2))
var sum = 1
for num in nums {
    sum *= num
}
print(sum)

