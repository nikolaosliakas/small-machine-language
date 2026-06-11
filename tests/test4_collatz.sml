@main:
    push 27
    invoke @collatz
    print
    push 1
    return

@collatz: n
    load n
    push 1
    if_cmplte L_done
    load n
    load n
    push 2
    div
    push 2
    mul
    sub
    push 0
    if_cmpgt L_odd
    load n
    push 2
    div
    invoke @collatz
    push 1
    add
    return

L_odd:
    load n
    push 3
    mul
    push 1
    add
    invoke @collatz
    push 1
    add
    return

L_done:
    push 0
    return
