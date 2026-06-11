@main:
    push 10
    invoke @factorial
    print
    push 1
    return

@factorial: n
    load n
    push 1
    if_cmplte L_base
    load n
    push 1
    sub
    invoke @factorial
    load n
    mul
    return
L_base: push 1
    return
