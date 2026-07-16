"""
Condition Utilities Module
Defines the preprocessor condition AST (Expr, Term, Not, And, Or)
and functions for condition parsing, negation, and simplification.
"""
import re

class Expr:
    pass

class Term(Expr):
    def __init__(self, value):
        self.value = value.strip()
    def __repr__(self):
        return f"Term({self.value!r})"
    def to_str(self):
        return self.value
    def __eq__(self, other):
        return isinstance(other, Term) and self.value == other.value
    def __hash__(self):
        return hash(self.value)

class Not(Expr):
    def __init__(self, child):
        self.child = child
    def __repr__(self):
        return f"Not({self.child!r})"
    def to_str(self):
        if isinstance(self.child, Term):
            return f"!{self.child.to_str()}"
        return f"!( {self.child.to_str()} )"
    def __eq__(self, other):
        return isinstance(other, Not) and self.child == other.child
    def __hash__(self):
        return hash(("Not", self.child))

class And(Expr):
    def __init__(self, children):
        self.children = children
    def __repr__(self):
        return f"And({self.children!r})"
    def to_str(self):
        parts = []
        for c in self.children:
            s = c.to_str()
            if isinstance(c, (Or, And)):
                parts.append(f"({s})")
            else:
                parts.append(s)
        return " && ".join(parts)
    def __eq__(self, other):
        return isinstance(other, And) and set(self.children) == set(other.children)
    def __hash__(self):
        return hash(("And", tuple(sorted(self.children, key=lambda x: str(x)))))

class Or(Expr):
    def __init__(self, children):
        self.children = children
    def __repr__(self):
        return f"Or({self.children!r})"
    def to_str(self):
        parts = []
        for c in self.children:
            s = c.to_str()
            if isinstance(c, (Or, And)):
                parts.append(f"({s})")
            else:
                parts.append(s)
        return " || ".join(parts)
    def __eq__(self, other):
        return isinstance(other, Or) and set(self.children) == set(other.children)
    def __hash__(self):
        return hash(("Or", tuple(sorted(self.children, key=lambda x: str(x)))))

def tokenize(s):
    # Capture comparison sub-expressions (e.g. "__ARM_ARCH >= 8") as single atomic tokens,
    # then defined(...), boolean operators, parentheses, and identifiers.
    pattern = r"([a-zA-Z_][a-zA-Z0-9_]*\s*(?:>=|<=|==|!=|>|<)\s*[a-zA-Z0-9_]+|defined\s*\(\s*[a-zA-Z0-9_]+\s*\)|&&|\|\||!|\(|\)|[a-zA-Z0-9_]+)"
    tokens = []
    for m in re.finditer(pattern, s):
        tokens.append(m.group(1))
    return tokens

def parse(tokens):
    pos = 0

    def parse_or():
        nonlocal pos
        left = parse_and()
        while pos < len(tokens) and tokens[pos] == "||":
            pos += 1
            right = parse_and()
            if isinstance(left, Or):
                if isinstance(right, Or):
                    left = Or(left.children + right.children)
                else:
                    left = Or(left.children + [right])
            elif isinstance(right, Or):
                left = Or([left] + right.children)
            else:
                left = Or([left, right])
        return left

    def parse_and():
        nonlocal pos
        left = parse_not()
        while pos < len(tokens) and tokens[pos] == "&&":
            pos += 1
            right = parse_not()
            if isinstance(left, And):
                if isinstance(right, And):
                    left = And(left.children + right.children)
                else:
                    left = And(left.children + [right])
            elif isinstance(right, And):
                left = And([left] + right.children)
            else:
                left = And([left, right])
        return left

    def parse_not():
        nonlocal pos
        if pos < len(tokens) and tokens[pos] == "!":
            pos += 1
            child = parse_primary()
            return Not(child)
        return parse_primary()

    def parse_primary():
        nonlocal pos
        if pos >= len(tokens):
            return Term("")
        
        tok = tokens[pos]
        if tok == "(":
            pos += 1
            expr = parse_or()
            if pos < len(tokens) and tokens[pos] == ")":
                pos += 1
            return expr
        else:
            pos += 1
            return Term(tok)

    return parse_or()

def substitute_known_true(expr, known_true_exprs):
    if not known_true_exprs:
        return expr
    for kt in known_true_exprs:
        if expr == kt:
            return Term("1")
    if isinstance(expr, Or):
        new_children = [substitute_known_true(c, known_true_exprs) for c in expr.children]
        result = Or(new_children)
        for kt in known_true_exprs:
            if result == kt:
                return Term("1")
        return result
    if isinstance(expr, And):
        new_children = [substitute_known_true(c, known_true_exprs) for c in expr.children]
        return And(new_children)
    if isinstance(expr, Not):
        new_child = substitute_known_true(expr.child, known_true_exprs)
        return Not(new_child)
    return expr

def simplify(expr):
    if isinstance(expr, Term):
        return expr
        
    if isinstance(expr, Not):
        child = simplify(expr.child)
        if isinstance(child, Not):
            return simplify(child.child)
        if child == Term("0"):
            return Term("1")
        if child == Term("1"):
            return Term("0")
        return Not(child)
        
    if isinstance(expr, And):
        new_children = []
        for c in expr.children:
            sc = simplify(c)
            if isinstance(sc, And):
                new_children.extend(sc.children)
            else:
                new_children.append(sc)
                
        unique_children = []
        seen = set()
        for c in new_children:
            if c not in seen:
                seen.add(c)
                unique_children.append(c)
                
        to_remove = set()
        for i, c in enumerate(unique_children):
            if isinstance(c, Not) and not isinstance(c.child, (And, Or)):
                for j, c2 in enumerate(unique_children):
                    if i != j and j not in to_remove and isinstance(c2, Not) and isinstance(c2.child, And):
                        if c.child in c2.child.children:
                            to_remove.add(j)
        for i, c in enumerate(unique_children):
            if i not in to_remove:
                for j, c2 in enumerate(unique_children):
                    if i != j and j not in to_remove and isinstance(c2, Or):
                        if c in c2.children:
                            to_remove.add(j)
        if to_remove:
            unique_children = [c for i, c in enumerate(unique_children) if i not in to_remove]
            seen = set(unique_children)

        has_contradiction = False
        for c in unique_children:
            if isinstance(c, Not):
                if c.child in seen:
                    has_contradiction = True
                    break
                if isinstance(c.child, And) and all(child in seen for child in c.child.children):
                    has_contradiction = True
                    break
            else:
                if Not(c) in seen:
                    has_contradiction = True
                    break
                    
        if has_contradiction or any(c == Term("0") for c in unique_children):
            return Term("0")
            
        unique_children = [c for c in unique_children if c != Term("1")]
        if not unique_children:
            return Term("1")
            
        if len(unique_children) == 1:
            return unique_children[0]
            
        return And(unique_children)

    if isinstance(expr, Or):
        new_children = []
        for c in expr.children:
            sc = simplify(c)
            if isinstance(sc, Or):
                new_children.extend(sc.children)
            else:
                new_children.append(sc)
                
        unique_children = []
        seen = set()
        for c in new_children:
            if c not in seen:
                seen.add(c)
                unique_children.append(c)

        to_remove = set()
        for i, c in enumerate(unique_children):
            for j, c2 in enumerate(unique_children):
                if i != j and j not in to_remove and isinstance(c2, And):
                    if c in c2.children:
                        to_remove.add(j)
        if to_remove:
            unique_children = [c for i, c in enumerate(unique_children) if i not in to_remove]

        changed_compl = True
        while changed_compl:
            changed_compl = False
            for i, c in enumerate(unique_children):
                if isinstance(c, Not) and not isinstance(c.child, (And, Or)):
                    neg_term = c.child
                    for j, c2 in enumerate(unique_children):
                        if i != j and isinstance(c2, And) and neg_term in c2.children:
                            remaining = [ch for ch in c2.children if ch != neg_term]
                            if not remaining:
                                unique_children[j] = Term("1")
                            elif len(remaining) == 1:
                                unique_children[j] = remaining[0]
                            else:
                                unique_children[j] = And(remaining)
                            changed_compl = True
                            break
                if changed_compl:
                    break
            if changed_compl:
                new_unique = []
                new_seen = set()
                for c in unique_children:
                    if c not in new_seen:
                        new_seen.add(c)
                        new_unique.append(c)
                unique_children = new_unique

        flat_children = []
        for c in unique_children:
            sc = simplify(c)
            if isinstance(sc, Or):
                flat_children.extend(sc.children)
            else:
                flat_children.append(sc)
        unique_children = []
        seen = set()
        for c in flat_children:
            if c not in seen:
                seen.add(c)
                unique_children.append(c)

        has_tautology = False
        for c in unique_children:
            if isinstance(c, Not):
                if c.child in seen:
                    has_tautology = True
                    break
                if isinstance(c.child, Or) and all(child in seen for child in c.child.children):
                    has_tautology = True
                    break
            else:
                if Not(c) in seen:
                    has_tautology = True
                    break
                    
        if has_tautology or any(c == Term("1") for c in unique_children):
            return Term("1")
            
        unique_children = [c for c in unique_children if c != Term("0")]
        if not unique_children:
            return Term("0")
            
        if len(unique_children) == 1:
            return unique_children[0]
            
        return Or(unique_children)

    return expr

def simplify_cond_str(s, known_true_conds=None):
    if not s or s.strip() == "":
        return ""
    tokens = tokenize(s)
    if not tokens:
        return s
    expr = parse(tokens)
    if known_true_conds:
        known_true_exprs = []
        for kt_str in known_true_conds:
            if kt_str and kt_str.strip():
                kt_tokens = tokenize(kt_str)
                if kt_tokens:
                    known_true_exprs.append(parse(kt_tokens))
        if known_true_exprs:
            expr = substitute_known_true(expr, known_true_exprs)
    simplified = simplify(expr)
    res = simplified.to_str()
    if res == "0":
        return "0"
    if res == "1":
        return ""
    return res

def negate_cond(c):
    if not c or c.strip() == "":
        return None
    return f"!( {c} )"

def are_conds_mutually_exclusive(c1, c2, known_true_conds=None):
    n1 = simplify_cond_str(c1, known_true_conds=known_true_conds)
    n2 = simplify_cond_str(c2, known_true_conds=known_true_conds)
    if n1 == "0" or n2 == "0":
        return True
    if n1 == "" or n2 == "":
        return False
    
    neg_n1 = negate_cond(n1)
    neg_n2 = negate_cond(n2)
    if n1 == neg_n2 or n2 == neg_n1:
        return True
    if n1.startswith("!") and simplify_cond_str(n1[1:], known_true_conds=known_true_conds) == n2:
        return True
    if n2.startswith("!") and simplify_cond_str(n2[1:], known_true_conds=known_true_conds) == n1:
        return True
    return False

def intersect_conds(c1, c2, known_true_conds=None):
    if c1 is None or c2 is None:
        return None
    if c1 == "":
        return c2
    if c2 == "":
        return c1
    if c1 == c2:
        return c1
    if are_conds_mutually_exclusive(c1, c2, known_true_conds):
        return None
    return f"({c1}) && ({c2})"

def _is_guard_dead_under_cond(guard, cond):
    if not guard or guard == "0" or not cond:
        return False
    neg_guard = f"!( {guard} )"
    return (neg_guard.replace(" ", "") == cond.replace(" ", ""))
