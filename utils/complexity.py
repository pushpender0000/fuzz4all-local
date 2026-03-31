import re

def complexity_score_cpp(code: str) -> int:
    score = 0
    score += 3 * len(re.findall(r"\btemplate\b", code))
    score += 3 * len(re.findall(r"\bconstexpr\b|\bconsteval\b", code))
    score += 2 * len(re.findall(r"\bdecltype\b|\btype_traits\b|\bstd::is_", code))
    score += 2 * len(re.findall(r"\bconcept\b|\brequires\b", code))
    score += 1 * len(re.findall(r"\bvariant\b|\boptional\b|\btuple\b|\bspan\b|\bstring_view\b", code))
    score += 1 * code.count("::")
    score += 1 * (code.count("<") + code.count(">"))
    score += 1 * len(re.findall(r"\[\s*\]", code))
    return score

def complexity_score_c(code: str) -> int:
    score = 0
    score += 2 * len(re.findall(r"\btypedef\b|\bstruct\b|\bunion\b", code))
    score += 2 * len(re.findall(r"\b_Atomic\b|\brestrict\b|\binline\b", code))
    score += 2 * len(re.findall(r"\b__attribute__\b|\bpragma\b", code))
    score += 1 * len(re.findall(r"\bswitch\b|\bfor\b|\bwhile\b|\bdo\b", code))
    score += 1 * (code.count("*") + code.count("&"))
    score += 1 * code.count("->")
    return score

def complexity_score_smt2(code: str) -> int:
    score = 0
    score += 2 * len(re.findall(r"\(declare-fun\b|\(declare-const\b|\(define-fun\b", code))
    score += 2 * len(re.findall(r"\(assert\b", code))
    score += 2 * len(re.findall(r"\(forall\b|\(exists\b", code))
    score += 1 * (code.count("(") // 20)
    score += 1 * len(re.findall(r"\bBitVec\b|\bArray\b|\bReal\b|\bInt\b", code))
    return score
