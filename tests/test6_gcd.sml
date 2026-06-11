@main:
    push 252
    push 105
    invoke @gcd
    print
    push 1
    return

@gcd: a b
L1: load b
    push 0
    if_cmplte L_done
    load a
    load a
    load b
    div
    load b
    mul
    sub
    store r
    load b
    store a
    load r
    store b
    goto L1
L_done: load a
    return
