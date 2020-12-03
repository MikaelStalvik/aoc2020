// AoC day 2

import Foundation

extension String {
    func numberOfOccurances(string: String) -> Int {
        return self.components(separatedBy: string).count - 1
    }
    subscript(offset: Int) -> Character {
        self[index(self.startIndex, offsetBy: offset)]
    }
}

class passwordRule {
    var minOccurance: Int = 0
    var maxOccurance: Int = 0
    var pwdChar: String = ""
    
    func Validate(s: String) -> Bool {
        let occurances = s.numberOfOccurances(string: pwdChar)
        let minOk = occurances >= minOccurance
        let maxOk = occurances <= maxOccurance
        return minOk && maxOk
    }
    func Validate2(s: String) -> Bool {
        let c1 = s[minOccurance - 1]
        let c2 = s[maxOccurance - 1]
        let ok1 = String(c1) == pwdChar
        let ok2 = String(c2) == pwdChar
        let bothOk = ok1 && ok2
        return (ok1 || ok2) && !bothOk
    }
}

func parseRule(data: String) -> (rule: passwordRule, password: String) {
    let result = passwordRule()
    let parts = data.split(separator: " ")
    let ranges = parts[0].split(separator: "-")
    if let r1 = Int(ranges[0]) {
        result.minOccurance = r1
    }
    if let r2 = Int(ranges[1]) {
        result.maxOccurance = r2
    }
    result.pwdChar = parts[1].replacingOccurrences(of: ":", with: "")
    
    return (result, String(parts[2]))
}

func readFile(filename: String) -> [String] {
    do {
        let text = try String(contentsOfFile: filename, encoding: .utf8)
        let lines : [String] = text.components(separatedBy: "\n")
        return lines
    } catch let error as NSError{
        return[]
    }
}

func solve1() {
    let rawData = readFile(filename: "/Users/mikaelstalvik/Desktop/aoc/AoC2/aoc2.txt")
    
    var rules: [passwordRule] = []
    var passwords: [String] = []
    for item in rawData {
        if (!item.isEmpty) {
            let (rule, pwd) = parseRule(data: item)
            rules.append(rule)
            passwords.append(pwd)
        }
    }
    var res = 0
    var i = 0
    for password in passwords {
        if (rules[i].Validate(s: password)) {
            res += 1
        }
        i += 1
    }
    print("Valid: \(res)")
}

func solve2() {
    let rawData = readFile(filename: "/Users/mikaelstalvik/Desktop/aoc/AoC2/aoc2.txt")
    
    var rules: [passwordRule] = []
    var passwords: [String] = []
    for item in rawData {
        if (!item.isEmpty) {
            let (rule, pwd) = parseRule(data: item)
            rules.append(rule)
            passwords.append(pwd)
        }
    }
    var res = 0
    var i = 0
    for password in passwords {
        if (rules[i].Validate2(s: password)) {
            res += 1
        }
        i += 1
    }
    print("Valid: \(res)")
}

solve1()
solve2()

