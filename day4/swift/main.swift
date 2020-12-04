// AoC day 4

import Foundation

func readFile(filename: String) -> [String] {
    do {
        let text = try String(contentsOfFile: filename, encoding: .ascii)
        let lines : [String] = text.components(separatedBy: "\n")
        return lines
    } catch let _ as NSError{
        return[]
    }
}

func isValidHex(input: String) -> Bool {
    for c in input {
        if !c.isHexDigit {
            return false
        }
    }
    return true
}

class Passport {
    var birthYear = ""
    var issueYear = ""
    var expireYear = ""
    var height = ""
    var hairColor = ""
    var eyeColor = ""
    var passportId = ""
    var countryId = ""
    
    func naiveValidate() -> Bool {
        var fieldsPresent = 0;
        if !birthYear.isEmpty {
            fieldsPresent += 1
        }
        if !issueYear.isEmpty {
            fieldsPresent += 1
        }
        if !expireYear.isEmpty {
            fieldsPresent += 1
        }
        if !height.isEmpty {
            fieldsPresent += 1
        }
        if !hairColor.isEmpty {
            fieldsPresent += 1
        }
        if !eyeColor.isEmpty {
            fieldsPresent += 1
        }
        if !passportId.isEmpty {
            fieldsPresent += 1
        }
        if !countryId.isEmpty {
            fieldsPresent += 1
        }
        
        let allFieldsPresent = fieldsPresent == 8
        let missingCid = fieldsPresent == 7 && countryId.isEmpty
        return allFieldsPresent || missingCid
    }
    
    func validRange(input: String, start: Int, end: Int) -> Bool {
        if let y = Int(input) {
            return y >= start && y <= end
        }
        return false
    }
    func validate() -> Bool {
        let birthYearValid = validRange(input: birthYear, start: 1920, end: 2002)
        let issueYearValid = validRange(input: issueYear, start: 2010, end: 2020)
        let expireYearValid = validRange(input: expireYear, start: 2020, end: 2030)
        
        var heightValid = false
        let isCm = height.contains("cm")
        let isIn = height.contains("in")
        if isCm {
            let tmp = height.replacingOccurrences(of: "cm", with: "")
            if let x = Int(tmp) {
                heightValid = x >= 150 && x <= 193
            }
        }
        if isIn {
            let tmp = height.replacingOccurrences(of: "in", with: "")
            if let x = Int(tmp) {
                heightValid = x >= 59 && x <= 76
            }
        }
        var hairColorValid = false
        if (hairColor.starts(with: "#")) {
            hairColorValid = isValidHex(input: hairColor.replacingOccurrences(of: "#", with: ""))
        }
        
        let validColors = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
        let eyeColorValid = validColors.contains(eyeColor)
        
        var passportIdValid = false
        if (passportId.count == 9) {
            if let _ = Int(passportId) {
                passportIdValid = true
            }
        }
        
        return birthYearValid &&
        issueYearValid &&
        expireYearValid &&
        heightValid &&
        hairColorValid &&
        eyeColorValid &&
        passportIdValid
    }
}

func parseData(input: [String]) -> Passport {
    let res = Passport()
    for item in input {
        let pairs = item.split(separator: " ")
        for pair in pairs {
            let kvp = pair.split(separator: ":")
            let key = String(kvp[0]).lowercased()
            let value = String(kvp[1])
            switch key {
            case "byr":
                res.birthYear = value
            case "iyr":
                res.issueYear = value
            case "eyr":
                res.expireYear = value
            case "hgt":
                res.height = value
            case "ecl":
                res.eyeColor = value
            case "hcl":
                res.hairColor = value
            case "pid":
                res.passportId = value
            case "cid":
                res.countryId = value
            default:
                break
            }
        }
    }
    return res
}

func parsePassports(lines: [String]) -> [Passport] {
    var passports: [Passport] = []
    var input: [String] = []
    for line in lines {
        if line.isEmpty {
            passports.append(parseData(input: input));
            input = []
        }
        else {
            input.append(line)
        }
    }
    if !input.isEmpty {
        passports.append(parseData(input: input));
    }
    return passports
}


let lines = readFile(filename: "/Users/mikaelstalvik/Downloads/aoc4f.txt")

let passports = parsePassports(lines: lines)

var valid = 0
for passport in passports {
    if passport.naiveValidate() {
        valid += 1
    }
}
print("Valid: \(valid) shall be 192")

valid = 0
for passport in passports {
    if passport.validate() {
        valid += 1
    }
}
print("Valid: \(valid) shall be 101")
